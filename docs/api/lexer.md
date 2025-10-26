# Lexer Functions API

Documentation for the lexer functions and interfaces.

## Core Functions

### `yylex()`

Primary lexer function that tokenizes input.

```c
int yylex(void);
```

**Returns**: Token type constant (e.g., `SELECT`, `IDENTIFIER`) or 0 for end of input.

**Description**: Reads the next token from the input stream and returns its type. The token text is available in the global variable `yytext`, and the token length in `yyleng`.

**Example**:
```c
int token;
while ((token = yylex()) != 0) {
    printf("Token: %d, Text: '%s'\n", token, yytext);
}
```

### `get_token_name()`

Get human-readable name for a token type.

```c
const char* get_token_name(int token);
```

**Parameters**:
- `token`: Token type constant

**Returns**: String representation of the token type.

**Example**:
```c
int token = yylex();
printf("Found token: %s\n", get_token_name(token));
// Output: "Found token: SELECT"
```

## Global Variables

### Input Control

#### `yyin`
```c
extern FILE* yyin;
```
Input file stream. Set this to read from a file instead of stdin.

**Example**:
```c
FILE* file = fopen("query.sql", "r");
if (file) {
    yyin = file;
    // Now yylex() reads from the file
}
```

#### `yytext`
```c
extern char* yytext;
```
Contains the text of the current token.

**Example**:
```c
int token = yylex();
printf("Token text: '%s'\n", yytext);
```

#### `yyleng`
```c
extern int yyleng;
```
Length of the current token text.

**Example**:
```c
int token = yylex();
printf("Token '%.*s' has length %d\n", yyleng, yytext, yyleng);
```

### Position Tracking

#### `yylineno`
```c
extern int yylineno;
```
Current line number (1-based).

**Example**:
```c
printf("Error at line %d\n", yylineno);
```

#### `yycolno`
```c
extern int yycolno;
```
Current column number (1-based). This is maintained by the lexer's helper functions.

**Example**:
```c
printf("Error at line %d, column %d\n", yylineno, yycolno);
```

## Helper Functions

### Position Tracking

#### `update_column()`
```c
void update_column(void);
```
Updates the column number based on the current token length. Called automatically by token rules.

#### `update_line()`
```c
void update_line(void);
```
Increments line number and resets column to 1. Called automatically when newlines are encountered.

### Debug Output

#### `print_token()`
```c
void print_token(int token, const char* text);
```

**Parameters**:
- `token`: Token type constant
- `text`: Token text

Prints formatted token information with position data.

**Example Output**:
```
Line 1, Col 8: IDENTIFIER      'users'
```

## Usage Patterns

### Basic Tokenization

```c
#include "src/headers/tokens.h"

int main() {
    int token;
    while ((token = yylex()) != 0) {
        printf("%s: '%s'\n", get_token_name(token), yytext);
    }
    return 0;
}
```

### File Processing

```c
#include "src/headers/tokens.h"

int process_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Cannot open %s\n", filename);
        return 1;
    }
    
    yyin = file;
    
    int token;
    while ((token = yylex()) != 0) {
        // Process token
        if (token == SELECT) {
            printf("Found SELECT at line %d\n", yylineno);
        }
    }
    
    fclose(file);
    return 0;
}
```

### Error Handling

```c
int parse_with_errors() {
    int token;
    int error_count = 0;
    
    while ((token = yylex()) != 0) {
        if (token == UNKNOWN_TOKEN) {
            fprintf(stderr, "Unknown token '%s' at line %d, col %d\n",
                    yytext, yylineno, yycolno);
            error_count++;
        }
        // Handle other tokens...
    }
    
    return error_count;
}
```

### Token Collection

```c
typedef struct {
    int type;
    char* text;
    int line;
    int column;
} Token;

Token* collect_tokens(int* count) {
    Token* tokens = NULL;
    int capacity = 0;
    *count = 0;
    
    int token_type;
    while ((token_type = yylex()) != 0) {
        if (*count >= capacity) {
            capacity = capacity ? capacity * 2 : 100;
            tokens = realloc(tokens, capacity * sizeof(Token));
        }
        
        tokens[*count].type = token_type;
        tokens[*count].text = strdup(yytext);
        tokens[*count].line = yylineno;
        tokens[*count].column = yycolno - yyleng;
        (*count)++;
    }
    
    return tokens;
}
```

## Integration Points

### Custom Input Sources

The lexer can be configured to read from custom sources by setting `yyin`:

```c
// Read from string (requires custom setup)
// Read from network socket
// Read from memory buffer
```

### Token Processing Pipeline

```c
typedef struct {
    int (*filter)(int token, const char* text);
    void (*handler)(int token, const char* text);
} TokenProcessor;

void process_tokens(TokenProcessor* proc) {
    int token;
    while ((token = yylex()) != 0) {
        if (!proc->filter || proc->filter(token, yytext)) {
            if (proc->handler) {
                proc->handler(token, yytext);
            }
        }
    }
}
```

## Thread Safety

**Warning**: The lexer is **not thread-safe**. Global variables like `yytext`, `yyleng`, and position counters are shared. For multi-threaded applications:

1. Use separate lexer instances per thread
2. Protect lexer calls with mutexes
3. Consider reentrant alternatives

## Memory Management

- `yytext` points to internal lexer buffer - do not free
- Token text is valid until next `yylex()` call
- Make copies if you need to store token text
- `yyin` file handles must be managed by caller

## Performance Considerations

- Lexer uses internal buffering for efficiency
- Large tokens may require buffer expansion
- File I/O is buffered by the C runtime
- Position tracking adds minimal overhead

## See Also

- [Token Types](tokens.md) - Complete token reference
- [Usage Examples](../user-guide/examples.md) - Practical examples
- [Lexer Design](../technical/lexer-design.md) - Implementation details