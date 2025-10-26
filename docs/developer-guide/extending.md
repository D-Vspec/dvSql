# Extending the Lexer

Guide for developers who want to extend or modify the dvSQL lexer.

## Architecture Overview

The lexer consists of several key components:

```
src/
├── lex/
│   └── sql_lexer.l      # Flex lexer specification
├── headers/
│   └── tokens.h         # Token type definitions
└── c/
    └── tokens.c         # Token utility functions
```

## Adding New Tokens

### Step 1: Define the Token Type

Add the new token to the enum in `src/headers/tokens.h`:

```c
typedef enum {
    // ... existing tokens ...
    
    // Your new tokens (add before UNKNOWN_TOKEN)
    TRUNCATE = 350,
    CASCADE,
    RESTRICT,
    
    /* Special tokens */
    UNKNOWN_TOKEN
} token_type_t;
```

**Important**: 
- Add new tokens before `UNKNOWN_TOKEN`
- Use sequential values or let the compiler assign them
- Choose descriptive names in ALL_CAPS

### Step 2: Add Token Name Mapping

Update the `get_token_name()` function in `src/c/tokens.c`:

```c
const char* get_token_name(int token) {
    switch (token) {
        // ... existing cases ...
        
        case TRUNCATE: return "TRUNCATE";
        case CASCADE: return "CASCADE";
        case RESTRICT: return "RESTRICT";
        
        default: return "UNKNOWN";
    }
}
```

### Step 3: Add Lexer Rules

Add recognition patterns in `src/lex/sql_lexer.l`:

```flex
/* Add to the rules section (after %%) */
"TRUNCATE"      { update_column(); print_token(TRUNCATE, yytext); return TRUNCATE; }
"CASCADE"       { update_column(); print_token(CASCADE, yytext); return CASCADE; }
"RESTRICT"      { update_column(); print_token(RESTRICT, yytext); return RESTRICT; }
```

### Step 4: Test and Build

```bash
make clean
make
echo "TRUNCATE TABLE users CASCADE;" | ./sql_lexer
```

## Adding New Token Categories

### Example: Adding Mathematical Functions

1. **Define tokens** in `tokens.h`:
```c
/* Mathematical Functions */
SIN,
COS,
TAN,
SQRT,
```

2. **Add to token names** in `tokens.c`:
```c
case SIN: return "SIN";
case COS: return "COS";
case TAN: return "TAN";
case SQRT: return "SQRT";
```

3. **Add lexer rules** in `sql_lexer.l`:
```flex
/* Mathematical Functions */
"SIN"           { update_column(); print_token(SIN, yytext); return SIN; }
"COS"           { update_column(); print_token(COS, yytext); return COS; }
"TAN"           { update_column(); print_token(TAN, yytext); return TAN; }
"SQRT"          { update_column(); print_token(SQRT, yytext); return SQRT; }
```

## Advanced Pattern Matching

### Custom Literal Types

Add support for hexadecimal numbers:

1. **Define the token**:
```c
HEX_LITERAL,
```

2. **Add pattern definition** in `sql_lexer.l`:
```flex
/* Add to definitions section */
HEX_DIGIT       [0-9a-fA-F]
HEX_NUMBER      0[xX]{HEX_DIGIT}+
```

3. **Add recognition rule**:
```flex
{HEX_NUMBER}    { update_column(); print_token(HEX_LITERAL, yytext); return HEX_LITERAL; }
```

### Complex String Patterns

Support for quoted identifiers:

```flex
/* Quoted identifiers with backticks */
`[^`]+`         { update_column(); print_token(QUOTED_IDENTIFIER, yytext); return QUOTED_IDENTIFIER; }
```

## Customizing Behavior

### Case Sensitivity Control

Make specific keywords case-sensitive:

```flex
/* Remove %option case-insensitive and use explicit patterns */
"SELECT"|"select"|"Select"  { update_column(); print_token(SELECT, yytext); return SELECT; }

/* Or use pattern matching */
[sS][eE][lL][eE][cC][tT]    { update_column(); print_token(SELECT, yytext); return SELECT; }
```

### Custom Error Handling

Enhance error reporting:

```flex
/* Add to the end of rules section */
.               { 
                  update_column(); 
                  fprintf(stderr, "Lexical error at line %d, column %d: unexpected character '%s'\n",
                          yylineno, yycolno - yyleng, yytext);
                  print_token(UNKNOWN_TOKEN, yytext);
                  return UNKNOWN_TOKEN; 
                }
```

### Multi-character Operators

Add support for `<=>` (null-safe equality):

```flex
"<=>"           { update_column(); print_token(NULL_SAFE_EQUAL, yytext); return NULL_SAFE_EQUAL; }
```

## Modifying Existing Behavior

### Changing Comment Handling

Store comments instead of ignoring them:

1. **Define comment token**:
```c
COMMENT_TOKEN,
```

2. **Modify comment rules**:
```flex
{COMMENT_LINE}  { 
                  update_column(); 
                  print_token(COMMENT_TOKEN, yytext); 
                  return COMMENT_TOKEN; 
                }
```

### Enhanced Position Tracking

Add character position within file:

1. **Add global variable**:
```c
int yycharno = 1;  // Total character position
```

2. **Update tracking functions**:
```c
void update_column() {
    yycolno += yyleng;
    yycharno += yyleng;
}

void update_line() {
    yylineno++;
    yycolno = 1;
    yycharno++;
}
```

## Testing Extensions

### Unit Tests

Create test cases for new tokens:

```bash
# Create test file
cat > test_new_tokens.sql << EOF
TRUNCATE TABLE users CASCADE;
SELECT SIN(angle), COS(angle) FROM measurements;
EOF

# Test
./sql_lexer test_new_tokens.sql
```

### Automated Testing

Add to the Makefile:

```makefile
test-extensions: $(TARGET)
	@echo "Testing new token extensions..."
	@echo "TRUNCATE TABLE test CASCADE;" | ./$(TARGET) | grep -q "TRUNCATE"
	@echo "SELECT SIN(x) FROM math;" | ./$(TARGET) | grep -q "SIN"
	@echo "Extension tests passed!"
```

## Performance Considerations

### Rule Ordering

- Place most common tokens first
- Put longer patterns before shorter ones that could match
- Group related patterns together

```flex
/* Good: specific before general */
"SELECT"        { /* action */ }
"SELECTED"      { /* action */ }  
{IDENTIFIER}    { /* action */ }

/* Bad: general before specific */
{IDENTIFIER}    { /* action */ }  // Would match "SELECT" first
"SELECT"        { /* never reached */ }
```

### Pattern Efficiency

Use character classes efficiently:

```flex
/* Efficient */
[0-9]+          { /* integer */ }

/* Less efficient */
(0|1|2|3|4|5|6|7|8|9)+  { /* integer */ }
```

## Debugging Extensions

### Flex Debug Mode

Enable flex debugging:

```bash
# Add to sql_lexer.l
%option debug

# Set environment variable
export FLEX_DEBUG=1
./sql_lexer test.sql
```

### Custom Debug Output

Add conditional debugging:

```c
#ifdef DEBUG_LEXER
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

/* In token actions */
"SELECT"        { 
                  DEBUG_PRINT("Found SELECT at %d:%d\n", yylineno, yycolno);
                  update_column(); 
                  print_token(SELECT, yytext); 
                  return SELECT; 
                }
```

Build with debugging:
```bash
make CFLAGS="-DDEBUG_LEXER -g"
```

## Common Patterns

### Database-Specific Keywords

Add MySQL-specific keywords:

```flex
"AUTOCOMMIT"    { update_column(); print_token(AUTOCOMMIT, yytext); return AUTOCOMMIT; }
"ENGINE"        { update_column(); print_token(ENGINE, yytext); return ENGINE; }
"CHARSET"       { update_column(); print_token(CHARSET, yytext); return CHARSET; }
```

### SQL Standard Compliance

Add SQL:2016 keywords:

```flex
"LISTAGG"       { update_column(); print_token(LISTAGG, yytext); return LISTAGG; }
"WITHIN"        { update_column(); print_token(WITHIN, yytext); return WITHIN; }
"FILTER"        { update_column(); print_token(FILTER, yytext); return FILTER; }
```

### Custom Data Types

Add PostgreSQL-specific types:

```flex
"JSONB"         { update_column(); print_token(JSONB_TYPE, yytext); return JSONB_TYPE; }
"UUID"          { update_column(); print_token(UUID_TYPE, yytext); return UUID_TYPE; }
"INET"          { update_column(); print_token(INET_TYPE, yytext); return INET_TYPE; }
```

## Integration with Parser

If building a parser (yacc/bison):

1. **Include token definitions**:
```yacc
%{
#include "src/headers/tokens.h"
%}

%token SELECT FROM WHERE IDENTIFIER
```

2. **Define grammar rules**:
```yacc
select_statement:
    SELECT column_list FROM table_name where_clause
    ;
```

3. **Connect lexer and parser**:
```c
extern int yylex();
int yyparse();

int main() {
    return yyparse();
}
```

## Best Practices

1. **Maintain compatibility**: Don't change existing token values
2. **Document changes**: Update documentation when adding features
3. **Test thoroughly**: Create comprehensive test cases
4. **Follow conventions**: Use consistent naming and patterns
5. **Consider performance**: Profile changes on large files
6. **Version control**: Commit logical changes separately

## Contributing Guidelines

When submitting extensions:

1. **Follow the established patterns**
2. **Add appropriate tests**
3. **Update documentation**
4. **Ensure backward compatibility**
5. **Include performance analysis if significant**

## See Also

- [Token Types](../api/tokens.md) - Complete token reference
- [Lexer Design](../technical/lexer-design.md) - Implementation details
- [Building Guide](building.md) - Build system details
- [Architecture](architecture.md) - System overview