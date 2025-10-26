# dvSQL Architecture: Complete System Overview

## Table of Contents
- [Overview](#overview)
- [System Architecture](#system-architecture)
- [Component Deep Dive](#component-deep-dive)
- [Data Flow](#data-flow)
- [Code Examples](#code-examples)
- [Advanced Features](#advanced-features)
- [Performance Considerations](#performance-considerations)

## Overview

dvSQL is a complete SQL parser and execution engine built from scratch using flex, bison, and C. What makes this project unique is its implementation of **relational algebra as the primary execution engine** - SQL queries are converted to relational algebra trees and then executed using proper algebraic operations.

### Key Features
- ✅ **Complete SQL Parsing** - Lexical analysis, syntax parsing, and AST generation
- ✅ **Relational Algebra Conversion** - SQL → RA tree transformation  
- ✅ **RA-Based Execution** - Data fetching using relational algebra operations
- ✅ **CSV Storage Engine** - File-based table storage with JSON metadata
- ✅ **Multiple Output Formats** - Tree view, mathematical notation, linear notation

## System Architecture

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   SQL Input     │───▶│   Flex Lexer    │───▶│     Tokens      │
│ "SELECT * FROM  │    │                 │    │   [SELECT]      │
│     users;"     │    │   sql_lexer.l   │    │   [FROM]        │
└─────────────────┘    └─────────────────┘    │   [IDENTIFIER]  │
                                              └─────────────────┘
                                                       │
                                                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│  Query Results  │◀───│ RA Execution    │◀───│  Bison Parser   │
│                 │    │    Engine       │    │                 │
│  id | name      │    │                 │    │ sql_parser.y    │
│ ────┼────       │    │ execute_ra_*()  │    │                 │
│  1  │ John      │    └─────────────────┘    └─────────────────┘
│  2  │ Jane      │             ▲                       │
└─────────────────┘             │                       ▼
                                │              ┌─────────────────┐
                                │              │   AST Tree      │
                                │              │                 │
                                │              │ NODE_SELECT_STMT│
                                │              │  ├─columns      │
                                │              │  ├─from_table   │
                                │              │  └─where_clause │
                                │              └─────────────────┘
                                │                       │
                                │                       ▼
                        ┌─────────────────┐    ┌─────────────────┐
                        │ Data Storage    │    │ Relational      │
                        │                 │    │   Algebra       │
                        │ users.csv       │    │                 │
                        │ users.json      │    │ π(σ(R(users)))  │
                        └─────────────────┘    └─────────────────┘
```

## Component Deep Dive

### 1. Lexical Analysis (Flex)

**File**: `src/lex/sql_lexer.l`, `src/lex/sql_parser_lexer.l`

The lexer breaks SQL text into tokens using regular expressions:

```c
// Token definitions in sql_lexer.l
"SELECT"        { return SELECT; }
"FROM"          { return FROM; }
"WHERE"         { return WHERE; }
[a-zA-Z_][a-zA-Z0-9_]*  { 
    yylval.string = strdup(yytext); 
    return IDENTIFIER; 
}
[0-9]+          { 
    yylval.integer = atoi(yytext); 
    return INTEGER_LITERAL; 
}
```

**Token Processing Flow**:
1. Input: `"SELECT name FROM users;"`
2. Lexer output: `[SELECT] [IDENTIFIER:"name"] [FROM] [IDENTIFIER:"users"] [SEMICOLON]`
3. Each token includes position information for error reporting

### 2. Syntax Analysis (Bison/Yacc)

**File**: `src/yacc/sql_parser.y`

The parser builds an Abstract Syntax Tree (AST) using grammar rules:

```yacc
select_stmt:
    SELECT column_list FROM table_ref optional_where optional_group_by optional_order_by {
        $$ = create_select_stmt($2, $4, $5, $6, $7);
    }
;

column_list:
    column_list COMMA column_expr {
        $$ = append_column_list($1, $3);
    }
    | column_expr {
        $$ = create_column_list($1);
    }
;
```

**AST Structure Example**:
```c
// For: SELECT name, age FROM users WHERE age > 25
ast_node_t* select_node = {
    .type = NODE_SELECT_STMT,
    .data.select_stmt = {
        .columns = column_list,        // [name, age]
        .from_table = table_ref,       // users
        .where_clause = expression,    // age > 25
        .group_by = NULL,
        .order_by = NULL
    }
};
```

### 3. AST Data Structures

**File**: `src/headers/ast.h`, `src/c/ast.c`

The AST represents the parsed SQL in a tree structure:

```c
typedef enum {
    NODE_SELECT_STMT,
    NODE_INSERT_STMT,
    NODE_CREATE_TABLE_STMT,
    NODE_DROP_TABLE_STMT,
    // ... more node types
} ast_node_type_t;

typedef struct ast_node {
    ast_node_type_t type;
    union {
        select_stmt_t select_stmt;
        insert_stmt_t insert_stmt;
        create_table_stmt_t create_table_stmt;
        // ... more statement types
    } data;
} ast_node_t;
```

**Expression Handling**:
```c
typedef enum {
    EXPR_BINARY_OP,      // age > 25
    EXPR_IDENTIFIER,     // name
    EXPR_LITERAL,        // 25, "John"
    EXPR_COLUMN_REF,     // users.name
    EXPR_FUNCTION_CALL   // COUNT(*)
} expression_type_t;

typedef struct expression {
    expression_type_t type;
    union {
        binary_op_t binary_op;      // left_expr OP right_expr
        char* identifier;           // column name
        literal_value_t literal;    // constant value
        column_ref_t column_ref;    // table.column
        function_call_t function_call;
    } data;
} expression_t;
```

### 4. SQL to Relational Algebra Conversion

**File**: `src/c/relational_algebra.c`

This is where the magic happens - SQL AST is converted to relational algebra operations:

```c
ra_node_t* convert_select_stmt(ast_node_t* select_stmt) {
    ra_node_t* result = NULL;
    
    // Step 1: Build FROM clause (base relations and joins)
    if (select_stmt->data.select_stmt.from_table) {
        result = build_from_clause(
            select_stmt->data.select_stmt.from_table, 
            select_stmt->data.select_stmt.joins
        );
    }
    
    // Step 2: Add WHERE clause (selection σ)
    if (select_stmt->data.select_stmt.where_clause) {
        ra_condition_t* condition = convert_expression_to_condition(
            select_stmt->data.select_stmt.where_clause
        );
        result = create_ra_selection(condition, result);
    }
    
    // Step 3: Add SELECT clause (projection π)
    if (select_stmt->data.select_stmt.columns) {
        ra_attribute_list_t* attrs = convert_column_list_to_attributes(
            select_stmt->data.select_stmt.columns
        );
        if (!is_star_projection(attrs)) {
            result = create_ra_projection(attrs, result);
        }
    }
    
    return result;
}
```

**RA Node Structure**:
```c
typedef enum {
    RA_RELATION,        // Base table: R(users)
    RA_SELECTION,       // σ_{condition}(input)
    RA_PROJECTION,      // π_{columns}(input)
    RA_THETA_JOIN,      // ⋈θ_{condition}(left, right)
    RA_CARTESIAN,       // ×(left, right)
    // ... more operations
} ra_operator_type_t;

typedef struct ra_node {
    ra_operator_type_t type;
    union {
        struct { char* name; char* alias; } relation;
        struct { ra_condition_t* condition; ra_node_t* input; } selection;
        struct { ra_attribute_list_t* attributes; ra_node_t* input; } projection;
        struct { ra_node_t* left; ra_node_t* right; ra_condition_t* condition; } binary_op;
    } data;
} ra_node_t;
```

### 5. Relational Algebra Execution Engine

**File**: `src/c/relational_algebra.c` (execution functions)

The execution engine processes RA trees to fetch actual data:

```c
ra_result_set_t* execute_ra_node(ra_node_t* node) {
    switch (node->type) {
        case RA_RELATION:
            return execute_ra_relation(node);
        case RA_SELECTION:
            return execute_ra_selection(node);
        case RA_PROJECTION:
            return execute_ra_projection(node);
        case RA_THETA_JOIN:
            return execute_ra_join(node);
        default:
            return NULL;
    }
}
```

**Base Relation Loading**:
```c
ra_result_set_t* execute_ra_relation(ra_node_t* node) {
    const char* table_name = node->data.relation.name;
    
    // 1. Load table metadata
    table_metadata_t* metadata = load_table_metadata(table_name);
    
    // 2. Read CSV data
    char** rows;
    int row_count;
    read_table_data(table_name, &row_count, &rows);
    
    // 3. Create result set
    ra_result_set_t* result_set = create_ra_result_set();
    
    // 4. Add columns
    add_ra_column(result_set, create_ra_column("id", table_name));
    add_ra_column(result_set, create_ra_column("name", table_name));
    // ... more columns
    
    // 5. Parse and add rows
    for (int i = 0; i < row_count; i++) {
        ra_row_t* row = create_ra_row(metadata->column_count);
        // Parse CSV: "1,John,john@test.com,25,now"
        char* token = strtok(rows[i], ",");
        int col_index = 0;
        while (token && col_index < metadata->column_count) {
            row->values[col_index] = strdup(token);
            token = strtok(NULL, ",");
            col_index++;
        }
        add_ra_row(result_set, row);
    }
    
    return result_set;
}
```

**Selection Operation (WHERE clause)**:
```c
ra_result_set_t* execute_ra_selection(ra_node_t* node) {
    // 1. Get input data
    ra_result_set_t* input_set = execute_ra_node(node->data.selection.input);
    
    // 2. Create output with same columns
    ra_result_set_t* result_set = create_ra_result_set();
    copy_column_structure(input_set, result_set);
    
    // 3. Filter rows
    ra_row_t* current_row = input_set->rows;
    while (current_row) {
        if (evaluate_ra_condition(node->data.selection.condition, 
                                 current_row, input_set)) {
            // Copy qualifying row
            ra_row_t* new_row = copy_ra_row(current_row);
            add_ra_row(result_set, new_row);
        }
        current_row = current_row->next;
    }
    
    return result_set;
}
```

**Projection Operation (SELECT columns)**:
```c
ra_result_set_t* execute_ra_projection(ra_node_t* node) {
    ra_result_set_t* input_set = execute_ra_node(node->data.projection.input);
    
    // Handle SELECT *
    if (is_star_projection(node->data.projection.attributes)) {
        return input_set;
    }
    
    // Create output with projected columns only
    ra_result_set_t* result_set = create_ra_result_set();
    
    // Map projected columns
    ra_attribute_t* attr = node->data.projection.attributes->attributes;
    int* column_indices = malloc(attr_count * sizeof(int));
    
    while (attr) {
        int col_index = find_column_index(attr->name, attr->table_name, input_set);
        if (col_index >= 0) {
            column_indices[valid_columns] = col_index;
            add_ra_column(result_set, create_ra_column(attr->name, NULL));
            valid_columns++;
        }
        attr = attr->next;
    }
    
    // Project data
    ra_row_t* current_row = input_set->rows;
    while (current_row) {
        ra_row_t* new_row = create_ra_row(valid_columns);
        for (int i = 0; i < valid_columns; i++) {
            new_row->values[i] = strdup(current_row->values[column_indices[i]]);
        }
        add_ra_row(result_set, new_row);
        current_row = current_row->next;
    }
    
    return result_set;
}
```

### 6. Data Storage System

**Files**: `src/c/table_engine.c`, `src/headers/table_engine.h`

The storage engine manages table metadata and data:

**Table Metadata (JSON)**:
```json
// data/schemas/users.json
{
  "table_name": "users",
  "created_at": "2025-10-26 11:36:45",
  "column_count": 5,
  "columns": [
    {
      "name": "id",
      "type": "INTEGER",
      "primary_key": true,
      "not_null": true,
      "unique": false,
      "auto_increment": false
    },
    {
      "name": "name",
      "type": "VARCHAR",
      "size": 100,
      "primary_key": false,
      "not_null": true,
      "unique": false,
      "auto_increment": false
    }
  ]
}
```

**Table Data (CSV)**:
```csv
# data/tables/users.csv
# Table: users
# Created: 2025-10-26 11:36:45
# Columns: 5
# Data format: CSV
# --- DATA START ---
1,John,john@test.com,25,now
2,Jane Smith,jane@example.com,28,2023-02-01 09:15:00
3,Bob Johnson,bob@test.org,35,2023-03-15 14:20:30
```

**Storage Functions**:
```c
table_result_t execute_create_table(ast_node_t* create_stmt) {
    // 1. Validate table doesn't exist
    if (table_exists(table_name)) {
        return TABLE_ERROR_TABLE_EXISTS;
    }
    
    // 2. Create metadata structure
    table_metadata_t metadata = {
        .table_name = table_name,
        .column_count = count_columns(columns),
        .columns = columns,
        .created_at = get_current_timestamp()
    };
    
    // 3. Save JSON schema
    save_table_metadata(&metadata);
    
    // 4. Create empty CSV file
    create_table_data_file(table_name, &metadata);
    
    return TABLE_SUCCESS;
}

table_result_t execute_insert(ast_node_t* insert_stmt) {
    // 1. Validate table exists and load metadata
    table_metadata_t* metadata = load_table_metadata(table_name);
    
    // 2. Validate value count matches column count
    if (value_count != metadata->column_count) {
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    // 3. Convert values to CSV format and append
    append_row_to_table(table_name, values);
    
    return TABLE_SUCCESS;
}
```

## Data Flow

Let's trace a complete query execution:

### Example Query: `SELECT name, email FROM users WHERE age > 25;`

**Step 1: Lexical Analysis**
```
Input: "SELECT name, email FROM users WHERE age > 25;"
Tokens: [SELECT] [IDENTIFIER:"name"] [COMMA] [IDENTIFIER:"email"] 
        [FROM] [IDENTIFIER:"users"] [WHERE] [IDENTIFIER:"age"] 
        [GREATER_THAN] [INTEGER_LITERAL:25] [SEMICOLON]
```

**Step 2: Syntax Analysis**
```c
ast_node_t* select_stmt = {
    .type = NODE_SELECT_STMT,
    .data.select_stmt = {
        .columns = {
            .column = { .type = EXPR_IDENTIFIER, .data.identifier = "name" },
            .next = {
                .column = { .type = EXPR_IDENTIFIER, .data.identifier = "email" },
                .next = NULL
            }
        },
        .from_table = {
            .table_name = "users",
            .alias = NULL
        },
        .where_clause = {
            .type = EXPR_BINARY_OP,
            .data.binary_op = {
                .left = { .type = EXPR_IDENTIFIER, .data.identifier = "age" },
                .operator = GREATER_THAN,
                .right = { .type = EXPR_LITERAL, .data.literal.int_val = 25 }
            }
        }
    }
};
```

**Step 3: Relational Algebra Conversion**
```c
// Input AST → Output RA Tree
ra_node_t* ra_tree = {
    .type = RA_PROJECTION,
    .data.projection = {
        .attributes = ["name", "email"],
        .input = {
            .type = RA_SELECTION,
            .data.selection = {
                .condition = "age > 25",
                .input = {
                    .type = RA_RELATION,
                    .data.relation = { .name = "users" }
                }
            }
        }
    }
};
```

**Mathematical Notation**: `π_{name,email}(σ_{age>25}(users))`

**Step 4: Execution**
```c
// 1. Execute base relation
ra_result_set_t* users_data = execute_ra_relation(users_node);
// Result: All users loaded from CSV

// 2. Execute selection
ra_result_set_t* filtered_data = execute_ra_selection(selection_node);
// Result: Only users with age > 25

// 3. Execute projection  
ra_result_set_t* final_result = execute_ra_projection(projection_node);
// Result: Only name and email columns
```

**Step 5: Output**
```
Query Results:
==============
name            | email          
----------------+----------------
Jane Smith      | jane@example.com
Bob Johnson     | bob@test.org   

2 row(s) returned.
```

## Code Examples

### Creating and Executing Queries

**Basic SELECT**:
```bash
# Direct execution
echo "SELECT * FROM users;" | ./sql_parser

# With relational algebra display
echo "SELECT name, email FROM users;" | ./sql_parser -r

# Only relational algebra (no execution)
echo "SELECT * FROM users;" | ./sql_parser -a
```

**CREATE TABLE**:
```sql
CREATE TABLE products (
    id INTEGER PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    price DECIMAL(10,2),
    category VARCHAR(50)
);
```

**INSERT Data**:
```sql
INSERT INTO users VALUES (5, 'Charlie', 'charlie@test.com', 30, '2023-05-01');
```

### Programmatic Usage

**Parsing SQL in C**:
```c
#include "sql_parser.h"
#include "relational_algebra.h"

int main() {
    // Parse SQL
    yy_scan_string("SELECT name FROM users;");
    yyparse();
    
    // Convert to RA
    ra_node_t* ra_tree = sql_to_relational_algebra(ast_root);
    
    // Execute
    ra_result_set_t* results = execute_ra_node(ra_tree);
    
    // Display
    print_ra_result_set(results);
    
    // Cleanup
    free_ra_result_set(results);
    free_ra_node(ra_tree);
    free_ast(ast_root);
    
    return 0;
}
```

### Custom RA Operations

**Adding New Operations**:
```c
// 1. Add to enum
typedef enum {
    RA_RELATION,
    RA_SELECTION,
    RA_PROJECTION,
    RA_UNION,        // New operation
    // ...
} ra_operator_type_t;

// 2. Add to union
typedef struct ra_node {
    ra_operator_type_t type;
    union {
        // ... existing operations
        struct {
            ra_node_t* left;
            ra_node_t* right;
        } union_op;
    } data;
} ra_node_t;

// 3. Implement execution
ra_result_set_t* execute_ra_union(ra_node_t* node) {
    ra_result_set_t* left_set = execute_ra_node(node->data.union_op.left);
    ra_result_set_t* right_set = execute_ra_node(node->data.union_op.right);
    
    // Merge compatible result sets
    ra_result_set_t* result = merge_result_sets(left_set, right_set);
    
    return result;
}
```

## Advanced Features

### Expression Evaluation

The system supports complex WHERE clause evaluation:

```c
int evaluate_expression(expression_t* expr, ra_row_t* row, ra_result_set_t* context) {
    switch (expr->type) {
        case EXPR_BINARY_OP:
            return evaluate_binary_operation(expr, row, context);
        case EXPR_IDENTIFIER:
            return get_column_value_as_int(expr->data.identifier, row, context);
        case EXPR_LITERAL:
            return expr->data.literal.int_val;
        default:
            return 0;
    }
}

int evaluate_binary_operation(expression_t* expr, ra_row_t* row, ra_result_set_t* context) {
    int left_val = evaluate_expression(expr->data.binary_op.left, row, context);
    int right_val = evaluate_expression(expr->data.binary_op.right, row, context);
    
    switch (expr->data.binary_op.operator) {
        case GREATER_THAN:
            return left_val > right_val;
        case LESS_THAN:
            return left_val < right_val;
        case EQUAL:
            return left_val == right_val;
        case AND:
            return left_val && right_val;
        case OR:
            return left_val || right_val;
        default:
            return 0;
    }
}
```

### Join Operations

Basic join implementation:

```c
ra_result_set_t* execute_ra_theta_join(ra_node_t* node) {
    ra_result_set_t* left_set = execute_ra_node(node->data.binary_op.left);
    ra_result_set_t* right_set = execute_ra_node(node->data.binary_op.right);
    ra_condition_t* condition = node->data.binary_op.condition;
    
    ra_result_set_t* result = create_ra_result_set();
    
    // Add columns from both tables
    copy_columns(left_set, result);
    copy_columns(right_set, result);
    
    // Nested loop join
    ra_row_t* left_row = left_set->rows;
    while (left_row) {
        ra_row_t* right_row = right_set->rows;
        while (right_row) {
            // Create combined row
            ra_row_t* combined = combine_rows(left_row, right_row);
            
            // Test join condition
            if (evaluate_ra_condition(condition, combined, result)) {
                add_ra_row(result, combined);
            } else {
                free_ra_row(combined);
            }
            
            right_row = right_row->next;
        }
        left_row = left_row->next;
    }
    
    return result;
}
```

### Query Optimization

Basic optimization rules can be applied to RA trees:

```c
void optimize_ra_tree(ra_node_t** node) {
    if (!node || !*node) return;
    
    // Rule 1: Push selections down (selection pushdown)
    if ((*node)->type == RA_SELECTION) {
        push_selection_down(node);
    }
    
    // Rule 2: Combine adjacent projections
    if ((*node)->type == RA_PROJECTION) {
        combine_projections(node);
    }
    
    // Rule 3: Convert cartesian product + selection to join
    if ((*node)->type == RA_SELECTION && 
        (*node)->data.selection.input->type == RA_CARTESIAN) {
        convert_to_join(node);
    }
    
    // Recursively optimize children
    optimize_children(*node);
}
```

## Performance Considerations

### Memory Management

The system uses careful memory management:

```c
void free_ra_result_set(ra_result_set_t* result_set) {
    if (!result_set) return;
    
    // Free all columns
    ra_column_t* current_col = result_set->columns;
    while (current_col) {
        ra_column_t* next_col = current_col->next;
        free(current_col->name);
        free(current_col->table_name);
        free(current_col);
        current_col = next_col;
    }
    
    // Free all rows
    ra_row_t* current_row = result_set->rows;
    while (current_row) {
        ra_row_t* next_row = current_row->next;
        for (int i = 0; i < current_row->column_count; i++) {
            free(current_row->values[i]);
        }
        free(current_row->values);
        free(current_row);
        current_row = next_row;
    }
    
    free(result_set);
}
```

### Scalability

For large datasets, consider:

1. **Streaming Processing**: Process rows one at a time instead of loading all into memory
2. **Index Support**: Add B-tree or hash indexes for faster lookups
3. **Buffer Management**: Implement page-based buffer management
4. **Query Planning**: Add cost-based query optimization

### File I/O Optimization

```c
// Buffered CSV reading for large files
typedef struct csv_reader {
    FILE* file;
    char* buffer;
    size_t buffer_size;
    size_t buffer_pos;
    size_t buffer_end;
} csv_reader_t;

char* read_csv_line(csv_reader_t* reader) {
    // Efficient buffered reading implementation
    // Returns next CSV line without loading entire file
}
```

## Conclusion

dvSQL demonstrates a complete implementation of database fundamentals:

1. **Lexical & Syntactic Analysis**: Professional-grade parsing using industry-standard tools
2. **Semantic Analysis**: AST construction and validation
3. **Relational Algebra**: Faithful implementation of Codd's relational model
4. **Query Execution**: Algebraic operations on actual data
5. **Storage Management**: File-based storage with metadata management

The system serves as both an educational tool for understanding database internals and a foundation for building more sophisticated database features.

### Key Takeaways

- **Modularity**: Each component (lexer, parser, RA engine, storage) is independent and testable
- **Extensibility**: New SQL features can be added by extending the grammar and RA operations
- **Standards Compliance**: Follows relational algebra principles and SQL standards
- **Performance**: Designed with optimization and scalability in mind

This architecture provides a solid foundation for understanding how modern database systems work under the hood.