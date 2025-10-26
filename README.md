# dvSQL Lexer

A comprehensive SQL lexer implemented using flex that tokenizes SQL statements and identifies various SQL language constructs.

## Quick Start

```bash
# Build the lexer
make

# Test with a simple query
echo "SELECT id, name FROM users WHERE age > 18;" | ./sql_lexer

# Run comprehensive tests
make test
```

## Features

- **50+ SQL keywords** - SELECT, JOIN, CREATE, etc.
- **Data types** - INTEGER, VARCHAR, TIMESTAMP, etc.  
- **Operators** - Comparison, arithmetic, logical
- **Literals** - Strings, numbers, booleans
- **Comments** - Line (`--`) and block (`/* */`) comments
- **Position tracking** - Line and column information
- **Error handling** - Unknown token detection

## Output Example

```
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
sudo apt-get install flex build-essential
```

**macOS:**
```bash
brew install flex
```

**Check installation:**
```bash
make check-deps
```

## Usage

### Basic Usage

```bash
# Tokenize from standard input
./sql_lexer
# Type SQL and press Ctrl+D when done

# Tokenize a file
./sql_lexer filename.sql

# Pipe SQL to lexer
echo "CREATE TABLE users (id INT, name VARCHAR(50));" | ./sql_lexer
```

### Command Line Options

```bash
make                    # Build the lexer
make test              # Run all tests  
make clean             # Clean build files
make interactive       # Interactive mode
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