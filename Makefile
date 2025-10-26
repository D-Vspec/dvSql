# SQL Lexer Makefile
# Builds a toy SQL lexer using flex and gcc

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99 -D_POSIX_C_SOURCE=200809L
FLEX = flex

# Source files
LEX_FILE = src/lex/sql_lexer.l
C_FILES = src/c/tokens.c
GENERATED_C = lex.yy.c
HEADER_FILES = src/headers/tokens.h

# Output executable
TARGET = sql_lexer

# Object files
OBJECTS = $(C_FILES:.c=.o) $(GENERATED_C:.c=.o)

# Default target
all: $(TARGET)

# Generate lexer C code from flex file
$(GENERATED_C): $(LEX_FILE) $(HEADER_FILES)
	$(FLEX) $(LEX_FILE)

# Compile C source files
%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -Isrc/headers -c $< -o $@

# Build the lexer executable  
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(GENERATED_C) $(TARGET)

# Remove all generated files
distclean: clean
	rm -f *~

# Test the lexer with sample files
test: $(TARGET)
	@echo "Testing with sample SQL files..."
	@if [ -f tests/test_simple.sql ]; then \
		echo "=== Testing tests/test_simple.sql ==="; \
		./$(TARGET) tests/test_simple.sql; \
		echo; \
	fi
	@if [ -f tests/test_complex.sql ]; then \
		echo "=== Testing tests/test_complex.sql ==="; \
		./$(TARGET) tests/test_complex.sql; \
		echo; \
	fi
	@if [ -f tests/test_ddl.sql ]; then \
		echo "=== Testing tests/test_ddl.sql ==="; \
		./$(TARGET) tests/test_ddl.sql; \
		echo; \
	fi

# Interactive test
interactive: $(TARGET)
	@echo "Starting interactive lexer test..."
	@echo "Type SQL statements and press Ctrl+D when done:"
	./$(TARGET)

# Install dependencies (for Ubuntu/Debian)
install-deps:
	@echo "Installing flex and build-essential..."
	sudo apt-get update
	sudo apt-get install flex build-essential

# Check if dependencies are installed
check-deps:
	@echo "Checking dependencies..."
	@which flex > /dev/null && echo "✓ flex is installed" || echo "✗ flex is not installed - run 'make install-deps'"
	@which gcc > /dev/null && echo "✓ gcc is installed" || echo "✗ gcc is not installed - run 'make install-deps'"

# Show help
help:
	@echo "SQL Lexer Makefile"
	@echo "=================="
	@echo "Available targets:"
	@echo "  all          - Build the lexer (default)"
	@echo "  clean        - Remove object files and executable"
	@echo "  distclean    - Remove all generated files"
	@echo "  test         - Run tests with sample SQL files"
	@echo "  interactive  - Start interactive lexer test"
	@echo "  install-deps - Install required dependencies (Ubuntu/Debian)"
	@echo "  check-deps   - Check if dependencies are installed"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Usage examples:"
	@echo "  make                    # Build the lexer"
	@echo "  make test               # Run automated tests"
	@echo "  make interactive        # Interactive testing"
	@echo "  ./sql_lexer file.sql    # Tokenize a specific file"
	@echo "  echo 'SELECT * FROM users;' | ./sql_lexer  # Tokenize from stdin"

# Declare phony targets
.PHONY: all clean distclean test interactive install-deps check-deps help