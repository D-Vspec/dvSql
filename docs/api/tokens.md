# Token Types Reference

Complete reference for all token types recognized by the dvSQL lexer.

## Token Categories

### SQL Keywords

#### Data Manipulation Language (DML)
| Token | Value | Description |
|-------|--------|-------------|
| `SELECT` | 256 | Retrieve data from tables |
| `FROM` | 257 | Specify source tables |
| `WHERE` | 258 | Filter conditions |
| `INSERT` | 259 | Add new records |
| `INTO` | 260 | Target table for insertion |
| `VALUES` | 261 | Specify insertion values |
| `UPDATE` | 262 | Modify existing records |
| `SET` | 263 | Assign new values |
| `DELETE` | 264 | Remove records |

#### Data Definition Language (DDL)
| Token | Value | Description |
|-------|--------|-------------|
| `CREATE` | 265 | Create database objects |
| `TABLE` | 266 | Table definition |
| `DROP` | 267 | Remove database objects |
| `ALTER` | 268 | Modify database objects |

#### Logical Operators
| Token | Value | Description |
|-------|--------|-------------|
| `AND` | 269 | Logical AND |
| `OR` | 270 | Logical OR |
| `NOT` | 271 | Logical NOT |
| `IN` | 285 | Value in set |
| `EXISTS` | 286 | Subquery existence test |
| `BETWEEN` | 287 | Range comparison |
| `LIKE` | 288 | Pattern matching |
| `IS` | 289 | Null comparison |

#### Query Modifiers
| Token | Value | Description |
|-------|--------|-------------|
| `DISTINCT` | 283 | Remove duplicates |
| `ALL` | 284 | Include all rows (default) |
| `AS` | 279 | Column/table alias |
| `ORDER` | 280 | Sort specification |
| `BY` | 281 | Sort/group column list |
| `GROUP` | 282 | Group rows |
| `HAVING` | 283 | Group filter conditions |
| `LIMIT` | 284 | Restrict result count |
| `OFFSET` | 285 | Skip initial rows |

#### Join Operations
| Token | Value | Description |
|-------|--------|-------------|
| `JOIN` | 290 | Table join operation |
| `INNER` | 291 | Inner join type |
| `LEFT` | 292 | Left outer join |
| `RIGHT` | 293 | Right outer join |
| `OUTER` | 294 | Outer join qualifier |
| `ON` | 295 | Join condition |
| `USING` | 296 | Join using column list |

#### Set Operations
| Token | Value | Description |
|-------|--------|-------------|
| `UNION` | 297 | Combine result sets |
| `INTERSECT` | 298 | Common rows between sets |
| `EXCEPT` | 299 | Rows in first set but not second |

#### Literals and Constants
| Token | Value | Description |
|-------|--------|-------------|
| `NULL_TOK` | 272 | Null value |
| `TRUE_TOK` | 273 | Boolean true |
| `FALSE_TOK` | 274 | Boolean false |

### Data Types

| Token | Value | Description |
|-------|--------|-------------|
| `INT_TYPE` | 300 | Integer type |
| `INTEGER_TYPE` | 301 | Integer type (full name) |
| `VARCHAR_TYPE` | 302 | Variable character string |
| `CHAR_TYPE` | 303 | Fixed character string |
| `TEXT_TYPE` | 304 | Text type |
| `DECIMAL_TYPE` | 305 | Decimal number |
| `NUMERIC_TYPE` | 306 | Numeric type |
| `FLOAT_TYPE` | 307 | Floating point |
| `REAL_TYPE` | 308 | Real number |
| `DATE_TYPE` | 309 | Date type |
| `TIME_TYPE` | 310 | Time type |
| `TIMESTAMP_TYPE` | 311 | Timestamp type |
| `BOOLEAN_TYPE` | 312 | Boolean type |

### Constraints and Modifiers

| Token | Value | Description |
|-------|--------|-------------|
| `PRIMARY` | 313 | Primary key constraint |
| `KEY` | 314 | Key constraint |
| `FOREIGN` | 315 | Foreign key constraint |
| `REFERENCES` | 316 | Foreign key reference |
| `UNIQUE` | 317 | Unique constraint |
| `CHECK` | 318 | Check constraint |
| `DEFAULT` | 319 | Default value |
| `AUTO_INCREMENT` | 320 | Auto-incrementing column |

### Operators

#### Comparison Operators
| Token | Value | Symbol | Description |
|-------|--------|--------|-------------|
| `EQUAL` | 321 | `=` | Equality |
| `NOT_EQUAL` | 322 | `<>`, `!=` | Inequality |
| `LESS_THAN` | 323 | `<` | Less than |
| `GREATER_THAN` | 324 | `>` | Greater than |
| `LESS_EQUAL` | 325 | `<=` | Less than or equal |
| `GREATER_EQUAL` | 326 | `>=` | Greater than or equal |

#### Arithmetic Operators
| Token | Value | Symbol | Description |
|-------|--------|--------|-------------|
| `PLUS` | 327 | `+` | Addition |
| `MINUS` | 328 | `-` | Subtraction |
| `MULTIPLY` | 329 | `*` | Multiplication |
| `DIVIDE` | 330 | `/` | Division |
| `MODULO` | 331 | `%` | Modulo operation |

### Punctuation

| Token | Value | Symbol | Description |
|-------|--------|--------|-------------|
| `LPAREN` | 332 | `(` | Left parenthesis |
| `RPAREN` | 333 | `)` | Right parenthesis |
| `COMMA` | 334 | `,` | Comma separator |
| `SEMICOLON` | 335 | `;` | Statement terminator |
| `DOT` | 336 | `.` | Dot notation |

### Aggregate Functions

| Token | Value | Description |
|-------|--------|-------------|
| `COUNT` | 337 | Count rows/values |
| `SUM` | 338 | Sum numeric values |
| `AVG` | 339 | Average of values |
| `MIN` | 340 | Minimum value |
| `MAX` | 341 | Maximum value |

### Literals

| Token | Value | Description | Example |
|-------|--------|-------------|---------|
| `INTEGER_LITERAL` | 342 | Integer numbers | `42`, `0`, `999` |
| `DECIMAL_LITERAL` | 343 | Decimal numbers | `3.14`, `0.5`, `100.00` |
| `STRING_LITERAL` | 344 | Quoted strings | `'hello'`, `"world"` |

### Identifiers

| Token | Value | Description | Example |
|-------|--------|-------------|---------|
| `IDENTIFIER` | 345 | User-defined names | `users`, `name`, `user_id` |

### Special Tokens

| Token | Value | Description |
|-------|--------|-------------|
| `UNKNOWN_TOKEN` | 346 | Unrecognized input |

## Token Value Ranges

Tokens are assigned values starting from 256 to avoid conflicts with ASCII character codes:

- **256-299**: SQL Keywords
- **300-312**: Data Types  
- **313-320**: Constraints
- **321-331**: Operators
- **332-336**: Punctuation
- **337-341**: Functions
- **342-346**: Literals and Special

## Usage in Code

```c
#include "src/headers/tokens.h"

// Check token type
if (token == SELECT) {
    printf("Found SELECT keyword\n");
}

// Get token name for debugging
const char* name = get_token_name(token);
printf("Token: %s\n", name);
```

## Token Recognition Rules

1. **Case Insensitive**: Keywords match regardless of case (`SELECT` = `select`)
2. **Longest Match**: Lexer chooses longest possible token
3. **Keyword Priority**: Keywords take precedence over identifiers
4. **Context Free**: Each token recognized independently

## Examples

```sql
SELECT user_id, COUNT(*) as total
FROM users 
WHERE age >= 18;
```

Tokens produced:
```
SELECT          -> SELECT (256)
user_id         -> IDENTIFIER (345)
,               -> COMMA (334)
COUNT           -> COUNT (337)
(               -> LPAREN (332)
*               -> MULTIPLY (329)
)               -> RPAREN (333)
as              -> AS (279)
total           -> IDENTIFIER (345)
FROM            -> FROM (257)
users           -> IDENTIFIER (345)
WHERE           -> WHERE (258)
age             -> IDENTIFIER (345)
>=              -> GREATER_EQUAL (326)
18              -> INTEGER_LITERAL (342)
;               -> SEMICOLON (335)
```

## See Also

- [Lexer Functions](lexer.md) - Functions for working with tokens
- [Usage Examples](../user-guide/examples.md) - Practical examples
- [Grammar Definition](../technical/grammar.md) - Formal grammar specification