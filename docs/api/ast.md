# AST Node Types

This document describes the Abstract Syntax Tree (AST) node types used by the dvSQL parser.

## Overview

The AST represents the hierarchical structure of parsed SQL statements. Each node in the tree represents a language construct, from high-level statements to individual expressions and identifiers.

## Node Type Hierarchy

### Statement Nodes

#### `NODE_SELECT_STMT`
Represents a SELECT statement with all its clauses.

**Structure:**
```c
struct {
    column_list_t* columns;      // SELECT column list
    table_ref_t* from_table;     // FROM clause
    join_clause_t* joins;        // JOIN clauses
    expression_t* where_clause;  // WHERE condition
    column_list_t* group_by;     // GROUP BY columns
    expression_t* having_clause; // HAVING condition
    column_list_t* order_by;     // ORDER BY columns
    int limit_count;             // LIMIT value (-1 if none)
    int offset_count;            // OFFSET value (-1 if none)
    int distinct;                // 1 if DISTINCT, 0 otherwise
} select_stmt;
```

**Example:**
```sql
SELECT DISTINCT name, age FROM users WHERE age > 18 ORDER BY name LIMIT 10;
```

#### `NODE_INSERT_STMT`
Represents an INSERT statement.

**Structure:**
```c
struct {
    char* table_name;           // Target table name
    column_list_t* columns;     // Column list (NULL for INSERT without columns)
    value_list_t* values;       // VALUES list
} insert_stmt;
```

**Example:**
```sql
INSERT INTO users (name, email, age) VALUES ('John', 'john@example.com', 25);
```

#### `NODE_UPDATE_STMT`
Represents an UPDATE statement.

**Structure:**
```c
struct {
    char* table_name;           // Target table name
    column_list_t* set_columns; // SET column list
    value_list_t* set_values;   // SET value list
    expression_t* where_clause; // WHERE condition
} update_stmt;
```

**Example:**
```sql
UPDATE users SET email = 'newemail@example.com' WHERE id = 1;
```

#### `NODE_DELETE_STMT`
Represents a DELETE statement.

**Structure:**
```c
struct {
    char* table_name;           // Target table name
    expression_t* where_clause; // WHERE condition
} delete_stmt;
```

**Example:**
```sql
DELETE FROM users WHERE age < 18;
```

#### `NODE_CREATE_TABLE_STMT`
Represents a CREATE TABLE statement.

**Structure:**
```c
struct {
    char* table_name;          // New table name
    column_def_t* columns;     // Column definitions
} create_table_stmt;
```

**Example:**
```sql
CREATE TABLE users (
    id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(255) UNIQUE
);
```

#### `NODE_DROP_TABLE_STMT`
Represents a DROP TABLE statement.

**Structure:**
```c
struct {
    char* table_name;          // Table to drop
} drop_table_stmt;
```

**Example:**
```sql
DROP TABLE old_users;
```

### Expression Nodes

#### `EXPR_IDENTIFIER`
Simple identifier (column name, table name, etc.).

**Structure:**
```c
char* identifier;  // The identifier string
```

#### `EXPR_LITERAL`
Literal values (numbers, strings, boolean, NULL).

**Structure:**
```c
literal_value_t literal;  // Union containing the literal value
```

#### `EXPR_BINARY_OP`
Binary operations (arithmetic, comparison, logical).

**Structure:**
```c
struct {
    expression_t* left;    // Left operand
    expression_t* right;   // Right operand
    int operator;          // Operator token (PLUS, EQUAL, AND, etc.)
} binary_op;
```

#### `EXPR_UNARY_OP`
Unary operations (NOT, negation).

**Structure:**
```c
struct {
    expression_t* operand; // The operand
    int operator;          // Operator token (NOT, MINUS)
} unary_op;
```

#### `EXPR_FUNCTION_CALL`
Function calls (COUNT, SUM, AVG, etc.).

**Structure:**
```c
struct {
    char* function_name;      // Function name
    expression_t** args;      // Array of arguments
    int arg_count;           // Number of arguments
} function_call;
```

#### `EXPR_COLUMN_REF`
Column references with optional table qualifier.

**Structure:**
```c
struct {
    char* table_name;        // Table name (NULL if not qualified)
    char* column_name;       // Column name
} column_ref;
```

### List Structures

#### `column_list_t`
Linked list of columns in SELECT, GROUP BY, ORDER BY clauses.

```c
struct column_list {
    expression_t* column;
    column_list_t* next;
};
```

#### `value_list_t`
Linked list of values in INSERT VALUES clause.

```c
struct value_list {
    expression_t* value;
    value_list_t* next;
};
```

#### `table_ref_t`
Table references with optional aliases.

```c
struct table_ref {
    char* table_name;
    char* alias;           // NULL if no alias
    table_ref_t* next;
};
```

#### `join_clause_t`
JOIN clauses with type and condition.

```c
struct join_clause {
    join_type_t join_type;     // INNER, LEFT, RIGHT, OUTER
    table_ref_t* table;        // Joined table
    expression_t* on_condition; // ON condition
    join_clause_t* next;
};
```

#### `column_def_t`
Column definitions for CREATE TABLE.

```c
struct column_def {
    char* column_name;
    data_type_t data_type;     // INT, VARCHAR, etc.
    int size;                  // For VARCHAR(n), CHAR(n)
    int precision;             // For DECIMAL(p,s)
    int is_primary_key;
    int is_not_null;
    int is_unique;
    int has_auto_increment;
    expression_t* default_value;
    column_def_t* next;
};
```

## Data Types

### `data_type_t`
Enumeration of supported SQL data types:
- `DATA_TYPE_INT`
- `DATA_TYPE_VARCHAR`
- `DATA_TYPE_CHAR`
- `DATA_TYPE_TEXT`
- `DATA_TYPE_DECIMAL`
- `DATA_TYPE_FLOAT`
- `DATA_TYPE_DATE`
- `DATA_TYPE_TIME`
- `DATA_TYPE_TIMESTAMP`
- `DATA_TYPE_BOOLEAN`

### `join_type_t`
Enumeration of JOIN types:
- `JOIN_INNER`
- `JOIN_LEFT`
- `JOIN_RIGHT`
- `JOIN_OUTER`

### `literal_value_t`
Union for literal values:
```c
typedef union {
    int int_val;
    double float_val;
    char* string_val;
} literal_value_t;
```

## Memory Management

### Allocation Functions
- `create_*()` functions allocate and initialize AST nodes
- All string values are duplicated using `strdup()`
- Lists are built using linked structures

### Deallocation Functions
- `free_ast()` recursively frees an entire AST
- `free_expression()` frees expression trees
- `free_*()` functions for specific list types
- All dynamically allocated strings are freed

## Traversal and Printing

### `print_ast(ast_node_t* node, int indent)`
Pretty-prints the AST structure with proper indentation.

### `print_expression(expression_t* expr, int indent)`
Prints expression trees in a readable format.

## Example AST Structure

For the SQL statement:
```sql
SELECT u.name, p.title FROM users u JOIN posts p ON u.id = p.user_id WHERE u.age > 18;
```

The resulting AST structure would be:
```
NODE_SELECT_STMT
├── columns: column_list_t
│   ├── column: EXPR_COLUMN_REF (u.name)
│   └── next: column_list_t
│       └── column: EXPR_COLUMN_REF (p.title)
├── from_table: table_ref_t (users AS u)
├── joins: join_clause_t
│   ├── join_type: JOIN_INNER
│   ├── table: table_ref_t (posts AS p)
│   └── on_condition: EXPR_BINARY_OP (EQUAL)
│       ├── left: EXPR_COLUMN_REF (u.id)
│       └── right: EXPR_COLUMN_REF (p.user_id)
└── where_clause: EXPR_BINARY_OP (GREATER_THAN)
    ├── left: EXPR_COLUMN_REF (u.age)
    └── right: EXPR_LITERAL (18)
```

## See Also

- [Parser API Reference](parser.md)
- [Token Types](tokens.md)
- [Grammar Definition](../technical/grammar.md)