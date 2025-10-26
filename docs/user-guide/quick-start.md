# Quick Start Guide

Get up and running with the dvSQL parser and lexer in 5 minutes.

## 1. Build the Parser and Lexer

```bash
cd dvSql
make
```

Expected output:
```
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -Isrc/headers -c src/c/tokens.c -o src/c/tokens.o
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -Isrc/headers -c src/c/ast.c -o src/c/ast.o
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -Isrc/headers -c src/c/sql_parser.c -o src/c/sql_parser.o
bison -d -v src/yacc/sql_parser.y
flex src/lex/sql_parser_lexer.l
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -Isrc/headers -c lex.yy.c -o lex.yy.o
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -Isrc/headers -c y.tab.c -o y.tab.o
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -o sql_parser src/c/tokens.o src/c/ast.o src/c/sql_parser.o lex.yy.o y.tab.o
flex src/lex/sql_lexer.l
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -Isrc/headers -c lex.yy.c -o lex.yy.o
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -o sql_lexer src/c/tokens.o lex.yy.o
```

This builds both:
- **`sql_parser`** - Full SQL parser that creates AST
- **`sql_lexer`** - Token analyzer for development/debugging

## 2. Parse Your First SQL Statement

```bash
echo "SELECT id, name FROM users WHERE age > 18;" | ./sql_parser
```

You'll see the parsed AST structure:
```
Enter SQL statement (end with semicolon and Ctrl+D):
> 
Parsed AST:
===========
SELECT id, name
FROM users
WHERE (age > literal)
```

## 3. Try the Lexer for Token Analysis

```bash
echo "SELECT id, name FROM users WHERE age > 18;" | ./sql_lexer
```

See detailed token breakdown:
```
Reading from standard input...
Enter SQL statements (Ctrl+D to end):
----------------------------------------
Line 1, Col 1: SELECT          'SELECT'
Line 1, Col 8: IDENTIFIER      'id'
Line 1, Col 10: COMMA           ','
Line 1, Col 12: IDENTIFIER      'name'
Line 1, Col 17: FROM            'FROM'
Line 1, Col 22: IDENTIFIER      'users'
Line 1, Col 28: WHERE           'WHERE'
Line 1, Col 34: IDENTIFIER      'age'
Line 1, Col 38: GREATER_THAN    '>'
Line 1, Col 40: INTEGER_LITERAL '18'
Line 1, Col 42: SEMICOLON       ';'
----------------------------------------
Tokenization complete.
```

## 4. Test with Sample Files

Run the included test suite:

```bash
make test
```

This tests both parser and lexer with various SQL statements:
- **SELECT statements** - Simple and complex queries
- **INSERT statements** - Data insertion 
- **UPDATE/DELETE** - Data modification
- **CREATE TABLE** - Schema definition
- **Aggregate functions** - COUNT, SUM, AVG, etc.

## 5. Parse Complex SQL

Create a complex SQL file and parse it:

```bash
cat > complex_query.sql << EOF
SELECT DISTINCT 
    u.name,
    COUNT(p.id) as post_count
FROM users u
LEFT JOIN posts p ON u.id = p.user_id
WHERE u.active = 1 AND p.published = 1
ORDER BY u.name;
EOF

./sql_parser complex_query.sql
```

Output shows the complete AST structure:
```
Parsed AST:
===========
SELECT DISTINCT u.name, COUNT(p.id)
FROM users AS u
LEFT JOIN posts AS p ON (u.id = p.user_id)
WHERE ((u.active = literal) AND (p.published = literal))
ORDER BY u.name
```

## 6. Interactive Parser Mode

Start the parser without arguments:

```bash
./sql_parser
```

Then type SQL statements:
```sql
CREATE TABLE users (
    id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(255) UNIQUE
);
```

Press `Ctrl+D` when finished to see the parsed CREATE TABLE AST.

## Parser Command Line Options

The parser supports several useful options:

```bash
# Verbose output with parsing details
./sql_parser -v query.sql

# Quiet mode (parse without showing AST)
./sql_parser -q query.sql

# Help information
./sql_parser -h
```

## What You'll See

### Parser Output (AST)
The parser shows the hierarchical structure of your SQL:

```
CREATE TABLE users (
  id INT PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  email VARCHAR(255) UNIQUE
)
```

### Lexer Output (Tokens)
The lexer identifies every element:

| Token Type | Example | Description |
|------------|---------|-------------|
| Keywords | `SELECT`, `FROM`, `WHERE` | SQL reserved words |
| Identifiers | `users`, `name`, `id` | Table/column names |
| Operators | `=`, `>`, `<=`, `!=` | Comparison operators |
| Literals | `'John'`, `42`, `3.14` | String, integer, decimal values |
| Punctuation | `(`, `)`, `,`, `;` | Structure elements |
| Data Types | `INTEGER`, `VARCHAR`, `DATE` | SQL data types |
| Functions | `COUNT`, `SUM`, `AVG` | Aggregate functions |

## Supported SQL Features

### ✅ Fully Supported
- **SELECT** with columns, WHERE, JOIN, ORDER BY
- **INSERT** with explicit columns and VALUES
- **UPDATE** with SET and WHERE clauses  
- **DELETE** with WHERE conditions
- **CREATE TABLE** with column definitions and constraints
- **DROP TABLE** statements
- **Aggregate functions** (COUNT, SUM, AVG, MIN, MAX)
- **JOIN types** (INNER, LEFT, RIGHT, OUTER)
- **Data types** (INT, VARCHAR, CHAR, TEXT, DECIMAL, etc.)
- **Operators** (arithmetic, comparison, logical)
- **Constraints** (PRIMARY KEY, NOT NULL, UNIQUE)

### ⚠️ Limitations
- No subqueries/nested queries
- No views (CREATE VIEW)
- No stored procedures
- No transactions
- No indexes

## Understanding Parser Output

The AST shows the logical structure:

```sql
SELECT u.name FROM users u WHERE u.age > 18;
```

Becomes:
```
SELECT_STMT
├── columns: COLUMN_LIST(u.name)
├── from_table: TABLE_REF(users AS u)  
└── where_clause: BINARY_OP(>)
    ├── left: COLUMN_REF(u.age)
    └── right: LITERAL(18)
```

## Next Steps

- **Learn more**: Read the [Usage Examples](examples.md)
- **Parser API**: See [Parser API Reference](../api/parser.md)
- **AST structure**: Study [AST Node Types](../api/ast.md)
- **Command line options**: Check [CLI Reference](cli.md)
- **Extend the parser**: Read [Developer Guide](../developer-guide/extending.md)

## Common Use Cases

1. **SQL Analysis**: Understand query structure and complexity
2. **Syntax Validation**: Check SQL for parse errors
3. **AST Processing**: Build tools that analyze or transform SQL
4. **Learning**: Study how SQL statements are structured
5. **Development**: Debug and test SQL parsing logic

## Getting Help

- **Installation issues**: See [Installation Guide](installation.md)
- **Usage questions**: Check [Examples](examples.md)
- **Parser API**: Read [API Documentation](../api/)
- **Development**: Visit [Developer Guide](../developer-guide/)