# SQL Parser and Lexer Makefile
# Builds a toy SQL parser using yacc/bison and flex

# Compiler and tools
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L
FLEX = flex
YACC = bison
YACCFLAGS = -d -v

# Source files for lexer only
LEX_FILE = src/lex/sql_lexer.l
LEXER_C_FILES = src/c/tokens.c
LEXER_GENERATED_C = lex.yy.c
LEXER_TARGET = sql_lexer

# Source files for parser
PARSER_LEX_FILE = src/lex/sql_parser_lexer.l
PARSER_YACC_FILE = src/yacc/sql_parser.y
PARSER_C_FILES = src/c/tokens.c src/c/ast.c src/c/sql_parser.c src/c/table_engine.c src/c/relational_algebra.c
PARSER_GENERATED_C = lex.yy.c y.tab.c
PARSER_GENERATED_H = y.tab.h
PARSER_TARGET = sql_parser

# Header files
HEADER_FILES = src/headers/tokens.h src/headers/ast.h src/headers/table_engine.h src/headers/relational_algebra.h

# Object files
LEXER_OBJECTS = $(LEXER_C_FILES:.c=.o) $(LEXER_GENERATED_C:.c=.o)
PARSER_OBJECTS = $(PARSER_C_FILES:.c=.o) $(PARSER_GENERATED_C:.c=.o)

# Default target - build both lexer and parser
all: $(LEXER_TARGET) $(PARSER_TARGET)

# Build lexer only
lexer: $(LEXER_TARGET)

# Build parser only
parser: $(PARSER_TARGET)

# Generate lexer C code from flex file
lexer_lex.yy.c: $(LEX_FILE) $(HEADER_FILES)
	$(FLEX) -o lexer_lex.yy.c $(LEX_FILE)

# Generate parser files from yacc and flex
parser_lex.yy.c sql_parser.tab.c sql_parser.tab.h: $(PARSER_YACC_FILE) $(PARSER_LEX_FILE) $(HEADER_FILES)
	$(YACC) $(YACCFLAGS) $(PARSER_YACC_FILE)
	$(FLEX) -o parser_lex.yy.c $(PARSER_LEX_FILE)

# Compile C source files with proper include paths
%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -Isrc/headers -c $< -o $@

# Compile generated files with special handling
lexer_lex.yy.o: lexer_lex.yy.c
	$(CC) $(CFLAGS) -Isrc/headers -c lexer_lex.yy.c -o $@

parser_lex.yy.o: parser_lex.yy.c
	$(CC) $(CFLAGS) -Isrc/headers -c parser_lex.yy.c -o $@

sql_parser.tab.o: sql_parser.tab.c
	$(CC) $(CFLAGS) -Isrc/headers -c sql_parser.tab.c -o $@

# Build the lexer executable  
$(LEXER_TARGET): $(LEXER_C_FILES:.c=.o) lexer_lex.yy.o
	$(CC) $(CFLAGS) -o $@ $^

# Build the parser executable
$(PARSER_TARGET): $(PARSER_C_FILES:.c=.o) parser_lex.yy.o sql_parser.tab.o
	$(CC) $(CFLAGS) -o $@ $^

# Clean build artifacts
clean:
	rm -f $(LEXER_C_FILES:.c=.o) $(PARSER_C_FILES:.c=.o)
	rm -f lexer_lex.yy.c lexer_lex.yy.o parser_lex.yy.c parser_lex.yy.o sql_parser.tab.c sql_parser.tab.h sql_parser.tab.o
	rm -f $(LEXER_TARGET) $(PARSER_TARGET) sql_parser.output

# Remove all generated files
distclean: clean
	rm -f *~

# Test the lexer with sample files
test-lexer: $(LEXER_TARGET)
	@echo "Testing lexer with sample SQL files..."
	@if [ -f tests/test_simple.sql ]; then \
		echo "=== Testing tests/test_simple.sql ==="; \
		./$(LEXER_TARGET) tests/test_simple.sql; \
		echo; \
	fi
	@if [ -f tests/test_complex.sql ]; then \
		echo "=== Testing tests/test_complex.sql ==="; \
		./$(LEXER_TARGET) tests/test_complex.sql; \
		echo; \
	fi
	@if [ -f tests/test_ddl.sql ]; then \
		echo "=== Testing tests/test_ddl.sql ==="; \
		./$(LEXER_TARGET) tests/test_ddl.sql; \
		echo; \
	fi

# Test the parser with sample files
test-parser: $(PARSER_TARGET)
	@echo "Testing parser with sample SQL files..."
	@if [ -f tests/parser_test_select.sql ]; then \
		echo "=== Testing tests/parser_test_select.sql ==="; \
		./$(PARSER_TARGET) tests/parser_test_select.sql; \
		echo; \
	fi
	@if [ -f tests/parser_test_insert.sql ]; then \
		echo "=== Testing tests/parser_test_insert.sql ==="; \
		./$(PARSER_TARGET) tests/parser_test_insert.sql; \
		echo; \
	fi
	@if [ -f tests/parser_test_create.sql ]; then \
		echo "=== Testing tests/parser_test_create.sql ==="; \
		./$(PARSER_TARGET) tests/parser_test_create.sql; \
		echo; \
	fi

# Test both lexer and parser
test: test-lexer test-parser

# Test relational algebra conversion
test-ra: $(PARSER_TARGET)
	@echo "Testing relational algebra conversion..."
	@if [ -f tests/ra_test_basic_select.sql ]; then \
		echo "=== Testing tests/ra_test_basic_select.sql ==="; \
		./$(PARSER_TARGET) -a tests/ra_test_basic_select.sql; \
		echo; \
	fi
	@if [ -f tests/ra_test_select_where.sql ]; then \
		echo "=== Testing tests/ra_test_select_where.sql ==="; \
		./$(PARSER_TARGET) -a tests/ra_test_select_where.sql; \
		echo; \
	fi
	@if [ -f tests/ra_test_join.sql ]; then \
		echo "=== Testing tests/ra_test_join.sql ==="; \
		./$(PARSER_TARGET) -a tests/ra_test_join.sql; \
		echo; \
	fi
	@if [ -f tests/ra_test_complex.sql ]; then \
		echo "=== Testing tests/ra_test_complex.sql ==="; \
		./$(PARSER_TARGET) -a tests/ra_test_complex.sql; \
		echo; \
	fi

# Interactive test for lexer
interactive-lexer: $(LEXER_TARGET)
	@echo "Starting interactive lexer test..."
	@echo "Type SQL statements and press Ctrl+D when done:"
	./$(LEXER_TARGET)

# Interactive test for parser
interactive-parser: $(PARSER_TARGET)
	@echo "Starting interactive parser test..."
	@echo "Type SQL statements and press Ctrl+D when done:"
	./$(PARSER_TARGET)

# Install dependencies (for Ubuntu/Debian)
install-deps:
	@echo "Installing flex, bison and build-essential..."
	sudo apt-get update
	sudo apt-get install flex bison build-essential

# Check if dependencies are installed
check-deps:
	@echo "Checking dependencies..."
	@which flex > /dev/null && echo "✓ flex is installed" || echo "✗ flex is not installed - run 'make install-deps'"
	@which bison > /dev/null && echo "✓ bison is installed" || echo "✗ bison is not installed - run 'make install-deps'"
	@which gcc > /dev/null && echo "✓ gcc is installed" || echo "✗ gcc is not installed - run 'make install-deps'"

# Show help
help:
	@echo "SQL Parser and Lexer Makefile"
	@echo "============================"
	@echo "Available targets:"
	@echo "  all              - Build both lexer and parser (default)"
	@echo "  lexer            - Build lexer only"
	@echo "  parser           - Build parser only"
	@echo "  clean            - Remove object files and executables"
	@echo "  distclean        - Remove all generated files"
	@echo "  test             - Run tests for both lexer and parser"
	@echo "  test-lexer       - Run tests for lexer only"
	@echo "  test-parser      - Run tests for parser only"
	@echo "  test-ra          - Run relational algebra conversion tests"
	@echo "  interactive-lexer    - Start interactive lexer test"
	@echo "  interactive-parser   - Start interactive parser test"
	@echo "  install-deps     - Install required dependencies (Ubuntu/Debian)"
	@echo "  check-deps       - Check if dependencies are installed"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "Usage examples:"
	@echo "  make                     # Build both lexer and parser"
	@echo "  make parser              # Build parser only"
	@echo "  make test-parser         # Run parser tests"
	@echo "  make test-ra             # Run relational algebra tests"
	@echo "  make interactive-parser  # Interactive parser testing"
	@echo "  ./sql_lexer file.sql     # Tokenize a file with lexer"
	@echo "  ./sql_parser file.sql    # Parse a file and show AST"
	@echo "  ./sql_parser -v file.sql # Parse with verbose output"
	@echo "  ./sql_parser -q file.sql # Parse without showing AST"
	@echo "  ./sql_parser -r file.sql # Show relational algebra conversion"
	@echo "  ./sql_parser -a file.sql # Show only relational algebra"
	@echo "  echo 'SELECT * FROM users;' | ./sql_parser  # Parse from stdin"

# Declare phony targets
.PHONY: all lexer parser clean distclean test test-lexer test-parser test-ra
.PHONY: interactive-lexer interactive-parser install-deps check-deps help