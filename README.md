# dvSQL Parser

A comprehensive SQL parser with relational algebra conversion implemented using flex and yacc/bison that parses SQL statements, builds Abstract Syntax Trees (AST), and converts queries to relational algebra notation.

## Quick Start

```bash
# Build the parser
make

# Parse and show AST
echo "SELECT id, name FROM users WHERE age > 18;" | ./sql_parser

# Convert to relational algebra
echo "SELECT id, name FROM users WHERE age > 18;" | ./sql_parser -a

# Parse and execute query
./sql_parser tests/parser_test_select.sql

# Run comprehensive tests
make test
```

## Features

- **Complete SQL parsing** - SELECT, INSERT, CREATE, DROP, etc.
- **Abstract Syntax Tree (AST)** - Full AST generation and pretty printing
- **Relational Algebra Conversion** - Convert SELECT queries to relational algebra notation
- **Query Execution** - Execute parsed queries on CSV data storage
- **Position tracking** - Line and column information for errors
- **Comprehensive testing** - Extensive test suite included

## Relational Algebra Support

The parser can convert SQL SELECT statements to relational algebra notation supporting:

- **σ (Selection)** - WHERE clause conditions
- **π (Projection)** - SELECT column lists  
- **⋈ (Join)** - Inner, left, right joins with conditions
- **× (Cartesian Product)** - Cross joins
- **Multiple output formats** - Tree view, mathematical notation, linear notation

### Example

```sql
SELECT u.name, p.title 
FROM users u 
JOIN posts p ON u.id = p.user_id 
WHERE u.age > 18;
```

**Converts to:**
```
π_{u.name, p.title}(σ_{u.age > 18}((users(u) ⋈θ_{u.id = p.user_id} posts(p))))
```

## Command Line Options

```bash
./sql_parser [OPTIONS] [file]

OPTIONS:
  -h          Show help message
  -v          Verbose output  
  -q          Quiet mode (don't print AST)
  -n          Parse only (don't execute statements)
  -r          Show relational algebra conversion
  -a          Show only relational algebra (implies -q -n -r)
  -f file     Parse the specified file

EXAMPLES:
  ./sql_parser query.sql           # Parse and execute
  ./sql_parser -r query.sql        # Show relational algebra  
  ./sql_parser -a query.sql        # Show only relational algebra
  echo 'SELECT * FROM users;' | ./sql_parser -a  # Pipe to parser
```

## Documentation

📚 **[Complete Documentation](docs/)** - Comprehensive guides and references

### Quick Links

| Document | Description |
|----------|-------------|
| **[Quick Start](docs/user-guide/quick-start.md)** | Get running in 5 minutes |
| **[Installation](docs/user-guide/installation.md)** | Setup and dependencies |
| **[Examples](docs/user-guide/examples.md)** | Practical usage examples |
| **[API Reference](docs/api/tokens.md)** | Token types and functions |
| **[Extending](docs/developer-guide/extending.md)** | Add new features |

### Documentation Structure

- **[User Guide](docs/user-guide/)** - Installation, usage, examples
- **[API Documentation](docs/api/)** - Functions and token reference  
- **[Developer Guide](docs/developer-guide/)** - Contributing and extending
- **[Technical Specs](docs/technical/)** - Implementation details

## Prerequisites

- **flex** (Fast Lexical Analyzer Generator)
- **gcc** (GNU Compiler Collection)  
- **make** (Build automation tool)

### Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get install flex bison build-essential
```

**macOS:**
```bash
brew install flex bison
```

**Check installation:**
```bash
make check-deps
```

## Usage

### Basic Usage

```bash
# Parse and execute from file
./sql_parser query.sql

# Parse from standard input  
./sql_parser
# Type SQL and press Ctrl+D when done

# Show relational algebra conversion
./sql_parser -a query.sql

# Parse only without execution
./sql_parser -n query.sql
```

### Relational Algebra Mode

```bash
# Show tree format, mathematical and linear notation
./sql_parser -r query.sql

# Show only relational algebra (no AST or execution)  
./sql_parser -a query.sql

# Test relational algebra conversion
make test-ra
```

## Project Structure

```
dvSql/
├── src/                    # Source code
│   ├── lex/               # Flex/Lex files
│   │   └── sql_lexer.l    # Lexer specification
│   ├── yacc/              # Yacc/Bison files (ready for parser)
│   ├── c/                 # C source files
│   │   └── tokens.c       # Token utilities
│   └── headers/           # Header files
│       └── tokens.h       # Token definitions
├── tests/                 # Test files
│   ├── test_simple.sql    # Basic tests
│   ├── test_complex.sql   # Advanced queries
│   └── test_ddl.sql       # DDL statements
├── docs/                  # Documentation
├── Makefile               # Build configuration
└── README.md              # This file
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

## Contributing

Contributions are welcome! Please see our [Developer Guide](docs/developer-guide/) for:

- [Architecture Overview](docs/developer-guide/architecture.md)
- [Extending the Lexer](docs/developer-guide/extending.md)  
- [Contributing Guidelines](docs/developer-guide/contributing.md)

## License

This is an educational/toy project. Feel free to use and modify as needed.

---

**[📖 View Full Documentation](docs/)** | **[🚀 Quick Start Guide](docs/user-guide/quick-start.md)** | **[🔧 API Reference](docs/api/)**