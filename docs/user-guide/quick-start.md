# Quick Start Guide

Get up and running with the dvSQL lexer in 5 minutes.

## 1. Build the Lexer

```bash
cd dvSql
make
```

Expected output:
```
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -Isrc/headers -c src/c/tokens.c -o src/c/tokens.o
flex src/lex/sql_lexer.l
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -Isrc/headers -c lex.yy.c -o lex.yy.o
gcc -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L -o sql_lexer src/c/tokens.o lex.yy.o
```

## 2. Run Your First Test

```bash
echo "SELECT id, name FROM users WHERE age > 18;" | ./sql_lexer
```

You'll see detailed token output:
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

## 3. Test with Sample Files

Run the included test suite:

```bash
make test
```

This runs three test files:
- **Simple queries** - Basic SELECT, FROM, WHERE
- **Complex queries** - JOINs, subqueries, aggregates
- **DDL statements** - CREATE TABLE, INSERT, UPDATE

## 4. Try Interactive Mode

Start the lexer without arguments for interactive input:

```bash
./sql_lexer
```

Then type SQL statements:
```sql
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);
```

Press `Ctrl+D` when finished.

## 5. Analyze a SQL File

Create a SQL file and analyze it:

```bash
cat > my_query.sql << EOF
SELECT DISTINCT 
    u.name,
    COUNT(p.id) as post_count
FROM users u
LEFT JOIN posts p ON u.id = p.user_id
WHERE u.active = TRUE
GROUP BY u.id, u.name
HAVING COUNT(p.id) > 5
ORDER BY post_count DESC
LIMIT 10;
EOF

./sql_lexer my_query.sql
```

## What You'll See

The lexer identifies and categorizes every element:

| Token Type | Example | Description |
|------------|---------|-------------|
| Keywords | `SELECT`, `FROM`, `WHERE` | SQL reserved words |
| Identifiers | `users`, `name`, `id` | Table/column names |
| Operators | `=`, `>`, `<=`, `!=` | Comparison operators |
| Literals | `'John'`, `42`, `3.14` | String, integer, decimal values |
| Punctuation | `(`, `)`, `,`, `;` | Structure elements |
| Data Types | `INTEGER`, `VARCHAR`, `DATE` | SQL data types |
| Functions | `COUNT`, `SUM`, `AVG` | Aggregate functions |

## Understanding the Output

Each token shows:
- **Line number** - Where the token appears
- **Column number** - Position within the line  
- **Token type** - Category of the token
- **Token value** - The actual text

Example:
```
Line 1, Col 8: IDENTIFIER 'users'
│      │  │     │          │
│      │  │     │          └── Actual text found
│      │  │     └──────────── Token category
│      │  └───────────────── Character position
│      └─────────────────── Line number
└───────────────────────── "Line" label
```

## Next Steps

- **Learn more**: Read the [Usage Examples](examples.md)
- **Command line options**: See [CLI Reference](cli.md)  
- **Extend the lexer**: Check [Developer Guide](../developer-guide/extending.md)
- **API details**: Browse [API Documentation](../api/tokens.md)

## Common First Steps

1. **Test your SQL**: Paste your queries and see how they tokenize
2. **Learn token types**: Study the output to understand SQL structure
3. **Try edge cases**: Test comments, strings with quotes, complex expressions
4. **Measure performance**: Time the lexer on large SQL files

## Getting Help

- **Installation issues**: See [Installation Guide](installation.md)
- **Usage questions**: Check [Examples](examples.md)
- **Technical details**: Read [API Documentation](../api/)
- **Development**: Visit [Developer Guide](../developer-guide/)