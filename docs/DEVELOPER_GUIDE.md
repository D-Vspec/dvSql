# dvSQL Developer Quick Start Guide

## Overview

dvSQL is a SQL parser and execution engine that uses **relational algebra** for data fetching. This guide shows you how to use and extend the system.

## Quick Setup

```bash
# Build the project
make clean && make

# Test basic functionality
echo "SELECT * FROM users;" | ./sql_parser

# Show relational algebra conversion
echo "SELECT name, email FROM users;" | ./sql_parser -r
```

## Understanding the Flow

### 1. SQL Input → Tokens
```sql
SELECT name FROM users WHERE age > 25;
```
↓
```
[SELECT] [IDENTIFIER:"name"] [FROM] [IDENTIFIER:"users"] 
[WHERE] [IDENTIFIER:"age"] [GREATER_THAN] [INTEGER:25] [SEMICOLON]
```

### 2. Tokens → AST
```c
ast_node_t {
    type: NODE_SELECT_STMT,
    columns: ["name"],
    from_table: "users",
    where_clause: "age > 25"
}
```

### 3. AST → Relational Algebra
```
π_{name}(σ_{age>25}(users))
```

### 4. RA → Data Execution
```c
execute_ra_projection(
    execute_ra_selection(
        execute_ra_relation("users")
    )
)
```

### 5. Result → Output
```
name
----
Jane Smith
Bob Johnson
```

## Key Components

### Parser Entry Point
**File**: `src/c/sql_parser.c`
```c
int main(int argc, char** argv) {
    // Parse command line options
    // Initialize table engine
    // Parse SQL (file or stdin)
    
    if (ast_root) {
        // Convert to RA if requested
        ra_node_t* ra_tree = sql_to_relational_algebra(ast_root);
        
        // Execute statement
        execute_select_with_ra(ast_root);  // Uses RA engine
    }
}
```

### RA Execution Engine
**File**: `src/c/relational_algebra.c`
```c
// Main dispatcher
ra_result_set_t* execute_ra_node(ra_node_t* node) {
    switch (node->type) {
        case RA_RELATION:   return execute_ra_relation(node);
        case RA_SELECTION:  return execute_ra_selection(node);
        case RA_PROJECTION: return execute_ra_projection(node);
        case RA_THETA_JOIN: return execute_ra_join(node);
    }
}

// Load table data
ra_result_set_t* execute_ra_relation(ra_node_t* node) {
    // 1. Load metadata: users.json
    // 2. Read CSV data: users.csv  
    // 3. Create result set with columns and rows
    // 4. Return structured data
}

// Filter rows (WHERE clause)
ra_result_set_t* execute_ra_selection(ra_node_t* node) {
    // 1. Get input data
    // 2. Evaluate condition for each row
    // 3. Keep only matching rows
    // 4. Return filtered result set
}

// Select columns (SELECT clause)
ra_result_set_t* execute_ra_projection(ra_node_t* node) {
    // 1. Get input data
    // 2. Map requested columns
    // 3. Create new result set with subset of columns
    // 4. Copy data for selected columns only
}
```

## Data Structures

### Result Set (Query Results)
```c
typedef struct ra_result_set {
    ra_column_t* columns;    // Column metadata
    ra_row_t* rows;         // Row data
    int column_count;       // Number of columns
    int row_count;          // Number of rows
} ra_result_set_t;

typedef struct ra_column {
    char* name;             // Column name
    char* table_name;       // Table qualifier
    struct ra_column* next; // Linked list
} ra_column_t;

typedef struct ra_row {
    char** values;          // Array of string values
    int column_count;       // Number of values
    struct ra_row* next;    // Linked list
} ra_row_t;
```

### Relational Algebra Node
```c
typedef struct ra_node {
    ra_operator_type_t type;  // RA_RELATION, RA_SELECTION, etc.
    union {
        // Base relation: users
        struct {
            char* name;       // Table name
            char* alias;      // Optional alias
        } relation;
        
        // Selection: σ_{condition}(input)
        struct {
            ra_condition_t* condition;  // WHERE clause
            ra_node_t* input;          // Input operation
        } selection;
        
        // Projection: π_{columns}(input)
        struct {
            ra_attribute_list_t* attributes;  // Column list
            ra_node_t* input;                 // Input operation
        } projection;
    } data;
} ra_node_t;
```

## Common Usage Patterns

### 1. Execute Query with RA Display
```bash
echo "SELECT id, name FROM users WHERE age > 25;" | ./sql_parser -r
```
Output:
```
Relational Algebra:
π_{id,name}(σ_{age>25}(users))

Query Results:
id | name
---+----
2  | Jane Smith
3  | Bob Johnson
```

### 2. Parse from File
```bash
./sql_parser tests/parser_test_select.sql
```

### 3. Only Show RA (No Execution)
```bash
echo "SELECT * FROM users;" | ./sql_parser -a
```

### 4. Verbose Mode
```bash
echo "SELECT * FROM users;" | ./sql_parser -v
```

## Adding New Features

### 1. Add New SQL Syntax

**Step 1**: Extend lexer (`src/lex/sql_parser_lexer.l`)
```c
"LIMIT"         { return LIMIT; }
```

**Step 2**: Extend parser (`src/yacc/sql_parser.y`)
```yacc
select_stmt:
    SELECT column_list FROM table_ref optional_where optional_limit {
        $$ = create_select_stmt($2, $4, $5, NULL, $6);
    }
;

optional_limit:
    LIMIT INTEGER_LITERAL { $$ = $2; }
    | /* empty */ { $$ = -1; }
;
```

**Step 3**: Extend AST (`src/headers/ast.h`)
```c
typedef struct select_stmt {
    column_list_t* columns;
    table_ref_t* from_table;
    expression_t* where_clause;
    int limit;              // New field
} select_stmt_t;
```

### 2. Add New RA Operation

**Step 1**: Add to enum (`src/headers/relational_algebra.h`)
```c
typedef enum {
    RA_RELATION,
    RA_SELECTION,
    RA_PROJECTION,
    RA_LIMIT,        // New operation
} ra_operator_type_t;
```

**Step 2**: Extend RA node structure
```c
typedef struct ra_node {
    ra_operator_type_t type;
    union {
        // ... existing operations
        struct {
            int count;           // Number of rows to limit
            ra_node_t* input;    // Input operation
        } limit;
    } data;
} ra_node_t;
```

**Step 3**: Implement execution
```c
ra_result_set_t* execute_ra_limit(ra_node_t* node) {
    ra_result_set_t* input_set = execute_ra_node(node->data.limit.input);
    ra_result_set_t* result_set = create_ra_result_set();
    
    // Copy column structure
    copy_columns(input_set, result_set);
    
    // Copy limited number of rows
    ra_row_t* current = input_set->rows;
    int count = 0;
    while (current && count < node->data.limit.count) {
        add_ra_row(result_set, copy_ra_row(current));
        current = current->next;
        count++;
    }
    
    free_ra_result_set(input_set);
    return result_set;
}
```

### 3. Add New Data Type

**Step 1**: Extend enum (`src/headers/ast.h`)
```c
typedef enum {
    DATA_TYPE_INT,
    DATA_TYPE_VARCHAR,
    DATA_TYPE_BOOLEAN,     // New type
} data_type_t;
```

**Step 2**: Update conversion functions (`src/c/table_engine.c`)
```c
const char* data_type_to_json_string(data_type_t type) {
    switch (type) {
        case DATA_TYPE_INT: return "INTEGER";
        case DATA_TYPE_VARCHAR: return "VARCHAR";
        case DATA_TYPE_BOOLEAN: return "BOOLEAN";  // New case
        default: return "UNKNOWN";
    }
}
```

## Testing

### Unit Tests
```bash
# Test specific SQL files
./sql_parser tests/parser_test_select.sql
./sql_parser tests/parser_test_create.sql
./sql_parser tests/parser_test_insert.sql

# Test with different options
./sql_parser -r tests/parser_test_join_simple.sql
./sql_parser -a tests/parser_test_select_complex.sql
```

### Manual Testing
```bash
# Create table
echo "CREATE TABLE test (id INTEGER, name VARCHAR(50));" | ./sql_parser

# Insert data
echo "INSERT INTO test VALUES (1, 'Alice');" | ./sql_parser

# Query data
echo "SELECT * FROM test;" | ./sql_parser -r
```

### Debug Mode
```bash
# Verbose output
echo "SELECT * FROM users;" | ./sql_parser -v

# Parse only (no execution)
echo "SELECT * FROM users;" | ./sql_parser -n
```

## Memory Management

Always clean up resources:

```c
// In your code
ra_node_t* ra_tree = sql_to_relational_algebra(ast_root);
ra_result_set_t* results = execute_ra_node(ra_tree);

// Use results...

// Cleanup
free_ra_result_set(results);
free_ra_node(ra_tree);
free_ast(ast_root);
```

## Common Pitfalls

1. **Memory Leaks**: Always free AST, RA trees, and result sets
2. **NULL Checks**: Check for NULL before dereferencing pointers
3. **String Handling**: Use `strdup()` for string copying, `free()` for cleanup
4. **CSV Parsing**: Handle edge cases like empty fields and quotes
5. **Type Safety**: Cast appropriately when working with unions

## Architecture Summary

```
SQL Input → Lexer → Parser → AST → RA Converter → RA Executor → Results

Files:
├── Lexer:        src/lex/sql_parser_lexer.l
├── Parser:       src/yacc/sql_parser.y  
├── AST:          src/headers/ast.h, src/c/ast.c
├── RA Convert:   src/c/relational_algebra.c (convert_* functions)
├── RA Execute:   src/c/relational_algebra.c (execute_* functions)
└── Storage:      src/c/table_engine.c
```

This architecture makes it easy to:
- Add new SQL syntax by extending lexer/parser
- Add new RA operations by extending the execution engine
- Optimize queries by manipulating RA trees
- Debug by examining intermediate representations

Happy coding! 🚀