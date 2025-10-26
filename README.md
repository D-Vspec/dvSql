# SQL Lexer

A toy SQL lexer implemented using flex (lex) that tokenizes SQL statements and identifies various SQL language constructs.

## Features

The lexer recognizes and tokenizes the following SQL elements:

### Keywords
- **DML**: SELECT, INSERT, UPDATE, DELETE, FROM, WHERE, VALUES, SET
- **DDL**: CREATE, DROP, ALTER, TABLE
- **Logical**: AND, OR, NOT, IN, EXISTS, BETWEEN, LIKE, IS
- **Clauses**: ORDER BY, GROUP BY, HAVING, LIMIT, OFFSET
- **Joins**: JOIN, INNER, LEFT, RIGHT, OUTER, ON, USING
- **Set Operations**: UNION, INTERSECT, EXCEPT
- **Modifiers**: DISTINCT, ALL, AS
- **Literals**: NULL, TRUE, FALSE

### Data Types
- INT, INTEGER, VARCHAR, CHAR, TEXT
- DECIMAL, NUMERIC, FLOAT, REAL
- DATE, TIME, TIMESTAMP, BOOLEAN

### Constraints & Modifiers
- PRIMARY KEY, FOREIGN KEY, REFERENCES
- UNIQUE, CHECK, DEFAULT, AUTO_INCREMENT

### Operators
- Comparison: =, <>, !=, <, >, <=, >=
- Arithmetic: +, -, *, /, %

### Aggregate Functions
- COUNT, SUM, AVG, MIN, MAX

### Literals & Identifiers
- Integer literals (e.g., 123, 0, 999)
- Decimal literals (e.g., 3.14, 0.5, 100.00)
- String literals (single or double quoted)
- Identifiers (table names, column names, etc.)

### Punctuation
- Parentheses: ( )
- Comma: ,
- Semicolon: ;
- Dot: .

### Comments
- Line comments: `-- comment text`
- Block comments: `/* comment text */`

## Prerequisites

- **flex** (Fast Lexical Analyzer Generator)
- **gcc** (GNU Compiler Collection)
- **make** (Build automation tool)

### Installing Dependencies

#### Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install flex build-essential
```

#### macOS (with Homebrew):
```bash
brew install flex
```

#### Check if dependencies are installed:
```bash
make check-deps
```

## Building

1. Clone or download the project files
2. Navigate to the project directory
3. Build the lexer:

```bash
make
```

This will:
- Generate the lexer C code from `sql_lexer.l` using flex
- Compile the generated code along with `tokens.c`
- Create the `sql_lexer` executable

## Usage

### Tokenize a SQL file:
```bash
./sql_lexer filename.sql
```

### Tokenize from standard input:
```bash
./sql_lexer
# Then type SQL statements and press Ctrl+D when done
```

### Pipe SQL to the lexer:
```bash
echo "SELECT * FROM users WHERE age > 18;" | ./sql_lexer
```

## Testing

The project includes several test SQL files:

### Run all tests:
```bash
make test
```

### Interactive testing:
```bash
make interactive
```

### Test files included:
- `tests/test_simple.sql` - Basic SELECT query
- `tests/test_complex.sql` - Complex queries with joins, subqueries, aggregates
- `tests/test_ddl.sql` - Data Definition Language examples (CREATE, INSERT, etc.)

## Output Format

The lexer outputs each token with its location information:

```
Line 1, Col 1:  SELECT          'SELECT'
Line 1, Col 8:  IDENTIFIER      'id'
Line 1, Col 10: COMMA           ','
Line 1, Col 12: IDENTIFIER      'name'
Line 1, Col 17: FROM            'FROM'
Line 1, Col 22: IDENTIFIER      'users'
Line 1, Col 27: SEMICOLON       ';'
```

## Project Structure

```
dvSql/
├── src/                    # Source code directory
│   ├── lex/               # Flex/Lex files
│   │   └── sql_lexer.l    # Flex lexer specification
│   ├── yacc/              # Yacc/Bison files (for future parser)
│   ├── c/                 # C source files
│   │   └── tokens.c       # Token name mapping functions
│   └── headers/           # Header files
│       └── tokens.h       # Token type definitions
├── tests/                 # Test files
│   ├── test_simple.sql    # Simple test queries
│   ├── test_complex.sql   # Complex test queries
│   └── test_ddl.sql       # DDL test statements
├── Makefile               # Build configuration
└── README.md              # This file
```

## Makefile Targets

- `make` or `make all` - Build the lexer
- `make clean` - Remove object files and executable
- `make distclean` - Remove all generated files
- `make test` - Run tests with sample files
- `make interactive` - Start interactive testing
- `make install-deps` - Install dependencies (Ubuntu/Debian)
- `make check-deps` - Check if dependencies are installed
- `make help` - Show available targets

## Lexer Design

The lexer is implemented using flex with the following key features:

1. **Case-insensitive** keyword matching
2. **Line and column tracking** for error reporting
3. **Comment handling** (both line and block comments)
4. **String literal support** with single and double quotes
5. **Numeric literal recognition** (integers and decimals)
6. **Comprehensive operator support**
7. **Error handling** for unknown tokens
8. **Modular structure** with organized source files

## Extending the Lexer

To add new tokens:

1. Add the token constant to `src/headers/tokens.h`
2. Add the token name mapping in `src/c/tokens.c`
3. Add the lexer rule in `src/lex/sql_lexer.l`
4. Rebuild with `make`

## Future Expansion

The project structure is designed to accommodate future additions:

- **yacc directory**: Ready for yacc/bison parser files
- **Modular C code**: Easy to add new source files
- **Organized headers**: Clean separation of interface definitions
- **Test framework**: Expandable test suite structure

## Example Usage

```sql
-- Example SQL statement
SELECT u.name, COUNT(p.id) as post_count
FROM users u
LEFT JOIN posts p ON u.id = p.user_id
WHERE u.age BETWEEN 18 AND 65
GROUP BY u.id, u.name
HAVING COUNT(p.id) > 5
ORDER BY post_count DESC;
```

This will be tokenized into keywords (SELECT, FROM, etc.), identifiers (u, name, posts), operators (>, =), literals (18, 65, 5), and punctuation.

## License

This is a toy/educational project. Feel free to use and modify as needed.