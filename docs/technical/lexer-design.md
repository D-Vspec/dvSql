# Lexer Design Specification

Technical specification of the dvSQL lexer implementation.

## Overview

The dvSQL lexer is implemented using flex (Fast Lexical Analyzer Generator) and follows a traditional finite state automaton design for tokenizing SQL input.

## Lexer Architecture

### State Machine Design

```
┌─────────────┐    input    ┌──────────────┐    tokens    ┌─────────────┐
│   Input     │────────────▶│    Lexer     │─────────────▶│   Output    │
│   Stream    │             │ (Flex FSA)   │              │   Stream    │
└─────────────┘             └──────────────┘              └─────────────┘
                                    │
                                    ▼
                            ┌──────────────┐
                            │   Token      │
                            │ Recognition  │
                            │   Rules      │
                            └──────────────┘
```

### Core Components

1. **Input Processing**
   - Character stream handling
   - Buffer management
   - Position tracking

2. **Pattern Matching**
   - Regular expression engine
   - Longest match algorithm
   - Priority-based selection

3. **Token Generation**
   - Type classification
   - Value extraction
   - Position annotation

## Token Recognition Algorithm

### Matching Strategy

The lexer uses the **longest match** principle:

1. **Scan input** character by character
2. **Build candidate matches** for all applicable patterns
3. **Select longest match** when no further extension possible
4. **Generate token** and advance input position
5. **Repeat** until end of input

### Pattern Priority

When multiple patterns match the same length:

1. **Earlier rule wins** (flex rule ordering)
2. **Keywords** take precedence over identifiers
3. **Specific patterns** before general patterns

Example:
```flex
"SELECT"        { return SELECT; }      /* Higher priority */
{IDENTIFIER}    { return IDENTIFIER; }  /* Lower priority */
```

Input `"SELECT"` matches both patterns, but keyword rule wins.

## Regular Expression Patterns

### Character Classes

```flex
DIGIT           [0-9]                    /* Single digit */
LETTER          [a-zA-Z]                 /* Alphabetic character */
UNDERSCORE      [_]                      /* Underscore character */
ALPHANUMERIC    [a-zA-Z0-9_]            /* Identifier character */
```

### Compound Patterns

```flex
IDENTIFIER      {LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*
INTEGER         {DIGIT}+
DECIMAL         {DIGIT}+\.{DIGIT}+
STRING          '[^']*'|\"[^\"]*\"
```

### Complex Patterns

**Comments**:
```flex
COMMENT_LINE    --[^\r\n]*              /* Line comment */
COMMENT_BLOCK   \/\*([^*]|\*[^/])*\*\/  /* Block comment */
```

**Whitespace**:
```flex
WHITESPACE      [ \t]+                   /* Spaces and tabs */
NEWLINE         \n|\r\n|\r              /* Platform-independent newlines */
```

## State Management

### Position Tracking

The lexer maintains several position counters:

```c
int yylineno = 1;    /* Current line (1-based) */
int yycolno = 1;     /* Current column (1-based) */
```

**Update Rules**:
- `yylineno++` on newline characters
- `yycolno += yyleng` for regular tokens
- `yycolno = 1` when line increments

### Buffer Management

Flex manages input through internal buffers:

- **Buffer size**: Default 16KB, expandable
- **Lookahead**: Single character for pattern completion
- **Input sources**: Files, strings, or custom input functions

## Token Generation Process

### Recognition Flow

```
Input: "SELECT id FROM users"

Step 1: Scan "SELECT"
├─ Match keyword pattern
├─ Generate SELECT token
└─ Advance position

Step 2: Skip whitespace
├─ Match WHITESPACE pattern
├─ No token generated
└─ Advance position

Step 3: Scan "id"
├─ Match IDENTIFIER pattern
├─ Generate IDENTIFIER token
└─ Advance position

... continue for remaining input
```

### Token Structure

Each token contains:

```c
typedef struct {
    int type;           /* Token type constant */
    char* text;         /* Token text (yytext) */
    int length;         /* Token length (yyleng) */
    int line;           /* Line number */
    int column;         /* Column position */
} Token;
```

## Performance Characteristics

### Time Complexity

- **Best case**: O(n) where n = input length
- **Average case**: O(n) linear scan
- **Worst case**: O(n) - no backtracking

### Space Complexity

- **Token storage**: O(1) per token
- **Buffer space**: O(k) where k = buffer size
- **Pattern storage**: O(p) where p = number of patterns

### Optimization Techniques

1. **DFA Construction**: Flex builds optimized finite automaton
2. **State Minimization**: Reduces number of states
3. **Table Compression**: Compact transition tables
4. **Buffer Optimization**: Efficient I/O handling

## Error Handling

### Error Detection

```flex
.               { 
                  /* Catch-all for unrecognized characters */
                  print_error("Unknown character", yytext);
                  return UNKNOWN_TOKEN; 
                }
```

### Error Recovery

The lexer employs **panic mode recovery**:

1. **Detect error** (unrecognized character)
2. **Generate error token**
3. **Continue scanning** from next character
4. **Report position** for debugging

### Error Reporting

```c
void lexer_error(const char* message, const char* text) {
    fprintf(stderr, "Lexical error at line %d, column %d: %s '%s'\n",
            yylineno, yycolno - yyleng, message, text);
}
```

## Memory Management

### Static Allocation

- **Token constants**: Compile-time constants
- **Pattern tables**: Generated by flex
- **State machines**: Static transition tables

### Dynamic Allocation

- **Input buffers**: Managed by flex
- **Token text**: Points to internal buffer (no allocation)
- **Position counters**: Simple integer variables

### Buffer Lifecycle

```
1. Buffer allocation    ─┐
2. Input reading        │ ← Managed by flex
3. Token extraction     │
4. Buffer cleanup       ─┘
```

## Integration Points

### Flex Integration

```c
/* Generated by flex */
extern int yylex(void);          /* Main lexer function */
extern char* yytext;             /* Current token text */
extern int yyleng;               /* Current token length */
extern FILE* yyin;               /* Input stream */
```

### Parser Integration

For integration with yacc/bison:

```c
/* Token values passed to parser */
#define YYSTYPE TokenValue

typedef union {
    int integer;
    double decimal;
    char* string;
} TokenValue;
```

## Thread Safety

### Limitations

The lexer is **not thread-safe** due to:

- Global variables (`yytext`, `yyleng`, `yylineno`)
- Static internal state
- Shared input buffer

### Thread-Safe Usage

```c
/* Option 1: Mutex protection */
pthread_mutex_t lexer_mutex = PTHREAD_MUTEX_INITIALIZER;

int safe_yylex() {
    pthread_mutex_lock(&lexer_mutex);
    int token = yylex();
    pthread_mutex_unlock(&lexer_mutex);
    return token;
}

/* Option 2: Separate lexer instances */
/* Requires reentrant lexer configuration */
```

## Extension Points

### Custom Patterns

Add new recognition patterns:

```flex
/* Custom date format */
DATE_LITERAL    {DIGIT}{4}-{DIGIT}{2}-{DIGIT}{2}
```

### Custom Actions

Enhance token processing:

```flex
{DATE_LITERAL}  { 
                  validate_date(yytext);
                  update_column(); 
                  print_token(DATE_LITERAL, yytext); 
                  return DATE_LITERAL; 
                }
```

### Input Sources

Customize input handling:

```c
/* Custom input function */
int custom_input(char* buffer, int max_size) {
    /* Read from custom source */
    return bytes_read;
}

/* Install custom input */
YY_INPUT(buffer, result, max_size) {
    result = custom_input(buffer, max_size);
}
```

## Debugging and Profiling

### Debug Mode

Enable flex debugging:

```flex
%option debug
```

```bash
export FLEX_DEBUG=1
./sql_lexer input.sql
```

### Performance Profiling

```bash
# Profile with gprof
make CFLAGS="-pg"
./sql_lexer large_file.sql
gprof sql_lexer gmon.out > profile.txt

# Memory profiling with valgrind
valgrind --tool=massif ./sql_lexer input.sql
```

### Metrics Collection

```c
/* Add counters for analysis */
static int token_counts[UNKNOWN_TOKEN + 1] = {0};

void count_token(int token) {
    if (token <= UNKNOWN_TOKEN) {
        token_counts[token]++;
    }
}

void print_statistics() {
    for (int i = 256; i <= UNKNOWN_TOKEN; i++) {
        if (token_counts[i] > 0) {
            printf("%s: %d\n", get_token_name(i), token_counts[i]);
        }
    }
}
```

## Limitations and Constraints

### Input Size Limits

- **Maximum token length**: Limited by flex buffer size
- **File size**: Constrained by available memory
- **Line length**: No explicit limit

### Pattern Complexity

- **Regular expression features**: Limited to flex-supported syntax
- **Lookahead**: Single character only
- **Context sensitivity**: Limited support

### Character Encoding

- **Default**: ASCII/UTF-8 compatible
- **Extended characters**: Requires careful pattern design
- **Locale sensitivity**: Depends on system configuration

## See Also

- [Token Specification](token-spec.md) - Detailed token definitions
- [Grammar Definition](grammar.md) - SQL grammar rules
- [Performance Analysis](performance.md) - Benchmarks and optimization
- [API Reference](../api/lexer.md) - Function documentation