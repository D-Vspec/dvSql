# Parser Design

This document describes the design and implementation of the dvSQL parser.

## Overview

The dvSQL parser is a recursive descent parser built using yacc/bison. It transforms SQL statements into Abstract Syntax Trees (AST) that can be used for analysis, optimization, or execution.

## Architecture

### Two-Phase Processing

1. **Lexical Analysis** (Flex/Lex)
   - Converts input text into tokens
   - Handles keywords, identifiers, literals, operators
   - Strips whitespace and comments

2. **Syntactic Analysis** (Yacc/Bison)
   - Parses token stream according to SQL grammar
   - Builds Abstract Syntax Tree (AST)
   - Handles operator precedence and associativity

### Component Interaction

```
SQL Text → Lexer → Token Stream → Parser → AST
```

## Grammar Design

### Grammar Structure

The grammar is organized into several levels:

1. **Program Level**: Complete SQL statements
2. **Statement Level**: SELECT, INSERT, UPDATE, DELETE, CREATE, DROP
3. **Clause Level**: FROM, WHERE, ORDER BY, GROUP BY, JOIN
4. **Expression Level**: Arithmetic, comparison, logical operations
5. **Atomic Level**: Identifiers, literals, function calls

### Production Rules

#### Program Structure
```yacc
program: statement_list
statement_list: statement_list statement SEMICOLON
             | statement SEMICOLON
statement: select_statement | insert_statement | update_statement
         | delete_statement | create_table_statement | drop_table_statement
```

#### SELECT Statement Grammar
```yacc
select_statement: SELECT select_column_list from_clause where_clause
                | SELECT DISTINCT select_column_list from_clause where_clause

select_column_list: MULTIPLY | column_list
column_list: column_list COMMA expression | expression
from_clause: FROM table_reference join_clause_list | FROM table_reference
where_clause: WHERE condition | /* empty */
```

#### Expression Grammar
```yacc
expression: literal | column_reference | function_call
          | expression PLUS expression
          | expression MINUS expression
          | LPAREN expression RPAREN

condition: expression comparison_op expression
         | condition AND condition
         | condition OR condition
         | NOT condition
```

### Operator Precedence

The parser handles operator precedence through yacc declarations:

```yacc
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT
%left DOT
```

## AST Design

### Node Types

The AST uses a discriminated union approach:

```c
typedef enum {
    NODE_SELECT_STMT,
    NODE_INSERT_STMT,
    NODE_UPDATE_STMT,
    // ... other node types
} ast_node_type_t;

struct ast_node {
    ast_node_type_t type;
    union {
        struct { /* SELECT fields */ } select_stmt;
        struct { /* INSERT fields */ } insert_stmt;
        // ... other statement types
    } data;
};
```

### Memory Management

- **Allocation**: Each node is individually malloc'd
- **Ownership**: Parent nodes own their children
- **Cleanup**: Recursive freeing from root node
- **Strings**: All strings are duplicated with strdup()

### Tree Structure

Example AST for `SELECT name FROM users WHERE age > 18`:

```
SELECT_STMT
├── columns: COLUMN_LIST
│   └── column: IDENTIFIER("name")
├── from_table: TABLE_REF("users")
└── where_clause: BINARY_OP(GREATER_THAN)
    ├── left: IDENTIFIER("age")
    └── right: LITERAL(18)
```

## Supported SQL Features

### SELECT Statements
- Column lists with aliases
- Wildcard selection (*)
- Table joins (INNER, LEFT, RIGHT, OUTER)
- WHERE conditions with complex expressions
- GROUP BY and HAVING clauses
- ORDER BY with multiple columns
- LIMIT and OFFSET
- DISTINCT keyword
- Aggregate functions (COUNT, SUM, AVG, MIN, MAX)

### INSERT Statements
- INSERT with explicit column list
- INSERT with VALUES clause
- Multiple value insertion

### UPDATE Statements
- SET clause with multiple assignments
- WHERE conditions
- Table aliases

### DELETE Statements
- WHERE conditions
- Table references

### CREATE TABLE Statements
- Column definitions with data types
- Primary key constraints
- NOT NULL constraints
- UNIQUE constraints
- AUTO_INCREMENT
- Default values

### DROP TABLE Statements
- Simple table dropping

## Error Handling

### Lexical Errors
- Unknown characters
- Unterminated strings
- Invalid number formats

### Syntax Errors
- Missing keywords
- Unbalanced parentheses
- Invalid token sequences
- Missing semicolons

### Error Recovery
- Parser stops at first error
- Error location reported with line number
- Current token context provided

## Performance Characteristics

### Time Complexity
- **Lexical Analysis**: O(n) where n is input length
- **Parsing**: O(n) for unambiguous grammar
- **AST Construction**: O(n) where n is number of nodes

### Space Complexity
- **Token Storage**: O(1) with streaming lexer
- **AST Storage**: O(n) where n is number of AST nodes
- **Parser Stack**: O(d) where d is maximum nesting depth

### Memory Usage
- Each AST node: ~100-200 bytes (varies by type)
- String storage: Proportional to identifier/literal length
- Total memory: Roughly 2-3x the input size for typical SQL

## Limitations

### Current Limitations
1. **No nested queries**: Subqueries not supported
2. **Limited data types**: Basic types only
3. **No views**: CREATE VIEW not implemented
4. **No indexes**: CREATE INDEX not supported
5. **No procedures**: Stored procedures not supported
6. **No transactions**: BEGIN/COMMIT not implemented

### Grammar Limitations
1. **Case sensitivity**: Keywords must be uppercase in grammar (lexer converts)
2. **Comment handling**: Only line and block comments
3. **String escaping**: Basic escape sequences only
4. **Numeric precision**: Limited by C data types

## Extension Points

### Adding New Statement Types
1. Add token definitions to lexer
2. Add production rules to grammar
3. Create AST node type
4. Implement creation/printing/freeing functions
5. Update main parser program

### Adding New Expression Types
1. Define expression type in enum
2. Add creation function
3. Update printing and freeing functions
4. Add grammar productions

### Adding New Data Types
1. Add to data_type_t enum
2. Update grammar productions
3. Update string conversion functions

## Testing Strategy

### Unit Tests
- Individual AST node creation
- Memory management functions
- Expression evaluation
- Error condition handling

### Integration Tests
- Complete SQL statement parsing
- AST structure verification
- Error message validation
- Memory leak detection

### Performance Tests
- Large query parsing
- Deep nesting scenarios
- Memory usage profiling
- Parse time measurement

## Future Enhancements

### Short Term
- Subquery support
- More SQL functions
- Better error messages
- Performance optimizations

### Long Term
- SQL standard compliance
- Query optimization
- Code generation
- Multiple SQL dialects

## References

- [Yacc/Bison Manual](https://www.gnu.org/software/bison/manual/)
- [Flex Manual](https://github.com/westes/flex/files/981163/flex.pdf)
- [SQL-92 Standard](https://www.contrib.andrew.cmu.edu/~shadow/sql/sql1992.txt)
- [Compilers: Principles, Techniques, and Tools](https://en.wikipedia.org/wiki/Compilers:_Principles,_Techniques,_and_Tools)

## See Also

- [AST Node Types](../api/ast.md)
- [Parser API Reference](../api/parser.md)
- [Grammar Definition](grammar.md)
- [Token Specification](token-spec.md)