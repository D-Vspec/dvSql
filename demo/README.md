# dvSQL Demo Queries

This folder contains demonstration SQL queries showcasing the capabilities of dvSQL, a toy SQL parser and execution engine built with Flex and Bison.

## Running the Demos

You can run any demo file using:

```bash
./dvsql demo/filename.sql
```

Or run them interactively:

```bash
./dvsql
dvSQL> <paste query here>
```

## Demo Files Overview

### Basic Queries (01-06)
- **01_basic_select.sql** - Simple SELECT * query
- **02_select_specific_columns.sql** - SELECT with specific columns
- **03_where_equality.sql** - WHERE with equality operator (=)
- **04_where_comparison.sql** - WHERE with comparison operators (>, <)
- **05_where_range.sql** - WHERE with range conditions (>=, <=)
- **06_where_string.sql** - WHERE with string comparison

### Logical Operators (07-09)
- **07_where_and.sql** - WHERE with AND operator
- **08_where_or.sql** - WHERE with OR operator
- **09_where_complex.sql** - Complex WHERE with multiple conditions

### Data Manipulation (10-11)
- **10_insert.sql** - INSERT new records
- **11_create_table.sql** - CREATE TABLE statement

### Meta Commands (12-13)
- **12_show_tables.sql** - SHOW TABLES command
- **13_describe_table.sql** - DESCRIBE table structure

### Advanced Comparisons (14-15)
- **14_inequality.sql** - WHERE with not equal (<>)
- **15_less_equal.sql** - WHERE with less than or equal (<=)

## Quick Demo Script

Run multiple queries in sequence:

```bash
# Show all users
./dvsql demo/01_basic_select.sql

# Filter by condition
./dvsql demo/03_where_equality.sql

# Complex filtering
./dvsql demo/09_where_complex.sql

# Show table structure
./dvsql demo/13_describe_table.sql
```

## Interactive Demo

```bash
./dvsql
dvSQL> SELECT * FROM users WHERE age > 25;
dvSQL> SELECT name, email FROM users WHERE id = 1 OR id = 4;
dvSQL> DESC users;
dvSQL> SHOW TABLES;
```

## Features Demonstrated

✅ **SQL Parsing** - Flex/Bison-based lexer and parser  
✅ **SELECT Queries** - Column projection and filtering  
✅ **WHERE Clauses** - Comparison and logical operators  
✅ **Relational Algebra** - Query execution via RA operations  
✅ **DDL Statements** - CREATE TABLE, DROP TABLE  
✅ **DML Statements** - INSERT, UPDATE, DELETE  
✅ **Meta Commands** - SHOW TABLES, DESCRIBE  

## Supported Operators

**Comparison Operators:**
- `=` - Equal to
- `<>` or `!=` - Not equal to
- `<` - Less than
- `>` - Greater than
- `<=` - Less than or equal to
- `>=` - Greater than or equal to

**Logical Operators:**
- `AND` - Logical AND
- `OR` - Logical OR
- `NOT` - Logical NOT

## Data Types

- INT / INTEGER
- VARCHAR(n)
- CHAR(n)
- TEXT
- DECIMAL / NUMERIC
- FLOAT / REAL
- DATE
- TIME
- TIMESTAMP
- BOOLEAN

## Example Output

```
dvSQL> select * from users where age > 25;

Parsed AST:
===========
SELECT *
FROM users
WHERE (age GREATER_THAN literal)


Query Results:
==============
id              | name            | email           | age             | created_at     
----------------+-----------------+-----------------+-----------------+----------------
2               | Jane Smith      | jane@example.com | 28              | 2023-02-01 09:15:00
3               | Bob Johnson     | bob@test.org    | 35              | 2023-03-15 14:20:30

2 row(s) returned.
```

## Notes

- The parser displays the AST (Abstract Syntax Tree) for educational purposes
- Query execution uses relational algebra operations
- Data is stored in CSV format with JSON schemas
- All queries are case-insensitive

## Architecture

```
SQL Query → Lexer (Flex) → Parser (Bison) → AST → Relational Algebra → Execution Engine → Results
```

For more details, see the main project documentation in the `/docs` folder.
