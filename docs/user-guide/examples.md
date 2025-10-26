# Usage Examples

Comprehensive examples showing how to use the dvSQL lexer in various scenarios.

## Basic Usage

### Simple Query Analysis

```bash
# Analyze a simple SELECT statement
echo "SELECT id, name FROM users WHERE active = true;" | ./sql_lexer
```

**Output**:
```
Line 1, Col 1: SELECT          'SELECT'
Line 1, Col 8: IDENTIFIER      'id'
Line 1, Col 10: COMMA           ','
Line 1, Col 12: IDENTIFIER      'name'
Line 1, Col 17: FROM            'FROM'
Line 1, Col 22: IDENTIFIER      'users'
Line 1, Col 28: WHERE           'WHERE'
Line 1, Col 34: IDENTIFIER      'active'
Line 1, Col 41: EQUAL           '='
Line 1, Col 43: TRUE_TOK        'true'
Line 1, Col 47: SEMICOLON       ';'
```

### File Processing

```bash
# Create a SQL file
cat > sample.sql << EOF
-- User management queries
SELECT COUNT(*) FROM users;
INSERT INTO users (name, email) VALUES ('John', 'john@example.com');
EOF

# Analyze the file
./sql_lexer sample.sql
```

## Complex Queries

### JOIN Operations

```sql
SELECT DISTINCT 
    u.id,
    u.name,
    p.title,
    COUNT(c.id) as comment_count
FROM users u
INNER JOIN posts p ON u.id = p.user_id
LEFT JOIN comments c ON p.id = c.post_id
WHERE u.created_date >= '2023-01-01'
  AND p.published = TRUE
GROUP BY u.id, u.name, p.title
HAVING COUNT(c.id) > 5
ORDER BY comment_count DESC, u.name ASC
LIMIT 20 OFFSET 10;
```

**Key tokens identified**:
- **JOIN keywords**: `INNER`, `LEFT`, `JOIN`
- **Functions**: `COUNT`, `DISTINCT`
- **Operators**: `>=`, `=`, `>`
- **Literals**: `'2023-01-01'`, `TRUE`, `5`, `20`, `10`
- **Identifiers**: `users`, `posts`, `comments`, `user_id`

### Subqueries and Set Operations

```sql
-- Complex subquery example
SELECT name, email
FROM users
WHERE id IN (
    SELECT user_id 
    FROM posts 
    WHERE likes > (
        SELECT AVG(likes) 
        FROM posts
    )
)
UNION ALL
SELECT name, email
FROM archived_users
WHERE last_login < '2022-01-01';
```

**Advanced features**:
- **Subqueries**: Nested `SELECT` statements
- **Set operations**: `UNION ALL`
- **Aggregate functions**: `AVG`
- **Comparison operators**: `>`, `<`

## Data Definition Language (DDL)

### Table Creation

```sql
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash CHAR(64) NOT NULL,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    age INT CHECK (age >= 0 AND age <= 150),
    balance DECIMAL(10,2) DEFAULT 0.00,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP
);
```

**DDL tokens recognized**:
- **Commands**: `CREATE`, `TABLE`
- **Data types**: `INTEGER`, `VARCHAR`, `CHAR`, `DECIMAL`, `BOOLEAN`, `TIMESTAMP`
- **Constraints**: `PRIMARY KEY`, `UNIQUE`, `NOT NULL`, `CHECK`, `DEFAULT`
- **Modifiers**: `AUTO_INCREMENT`

### Foreign Key Relationships

```sql
CREATE TABLE posts (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    user_id INTEGER NOT NULL,
    title VARCHAR(255) NOT NULL,
    content TEXT,
    published BOOLEAN DEFAULT FALSE,
    created_date DATE,
    FOREIGN KEY (user_id) REFERENCES users(id)
);
```

## Data Manipulation Examples

### Insert Operations

```sql
-- Single row insert
INSERT INTO users (username, email, first_name, last_name, age)
VALUES ('john_doe', 'john@example.com', 'John', 'Doe', 30);

-- Multiple row insert
INSERT INTO posts (user_id, title, content, published) VALUES
    (1, 'First Post', 'This is my first post!', TRUE),
    (1, 'Second Post', 'Another great post', TRUE),
    (2, 'Draft Post', 'Work in progress', FALSE);
```

### Update and Delete

```sql
-- Update with conditions
UPDATE users 
SET balance = balance + 100.00,
    updated_at = CURRENT_TIMESTAMP
WHERE username = 'john_doe' AND is_active = TRUE;

-- Conditional delete
DELETE FROM posts 
WHERE published = FALSE 
  AND created_date < '2023-01-01';
```

## Comment Handling

The lexer properly handles both line and block comments:

```sql
-- This is a line comment
SELECT id, /* inline comment */ name
FROM users /* another comment */
WHERE active = TRUE;

/*
 * Multi-line block comment
 * These are ignored by the lexer
 * Useful for documentation
 */
SELECT COUNT(*) FROM posts;
```

**Comment behavior**:
- Line comments (`--`) are skipped entirely
- Block comments (`/* */`) are skipped, including newlines
- Comments don't affect line/column tracking

## String Literals and Escaping

```sql
-- Single and double quotes
SELECT 'John''s Book', "She said ""Hello""" FROM examples;

-- Various string examples
INSERT INTO messages (content) VALUES
    ('Simple string'),
    ('String with ''escaped quotes'''),
    ("Double quoted string"),
    ('String with
     multiple lines');
```

## Numeric Literals

```sql
-- Integer literals
SELECT 0, 42, 999, 1000000 FROM numbers;

-- Decimal literals
SELECT 3.14, 0.5, 100.00, 0.001 FROM decimals;

-- Usage in calculations
UPDATE accounts 
SET balance = balance * 1.05  -- 5% increase
WHERE account_type = 'savings';
```

## Edge Cases and Error Handling

### Unrecognized Tokens

```sql
-- This contains invalid characters
SELECT id, name FROM users WHERE age > 18@;
```

**Output includes**:
```
Line 1, Col 40: GREATER_THAN    '>'
Line 1, Col 42: INTEGER_LITERAL '18'
Line 1, Col 44: UNKNOWN_TOKEN   '@'
Line 1, Col 45: SEMICOLON       ';'
```

### Mixed Case Keywords

```sql
-- Keywords are case-insensitive
Select Id, Name From Users Where Age > 18;
sElEcT id, name fRoM users wHeRe age > 18;
```

Both produce identical token output.

## Interactive Mode Examples

Start interactive mode:
```bash
./sql_lexer
```

Try these inputs:

1. **Simple query**:
   ```sql
   SELECT * FROM users;
   ```

2. **Complex expression**:
   ```sql
   WHERE (age BETWEEN 18 AND 65) AND (status IN ('active', 'pending'));
   ```

3. **Function calls**:
   ```sql
   SELECT COUNT(*), AVG(salary), MAX(hire_date) FROM employees;
   ```

Press `Ctrl+D` to exit.

## Performance Testing

### Large File Analysis

```bash
# Create a large SQL file
for i in {1..1000}; do
    echo "INSERT INTO users (name, email) VALUES ('User$i', 'user$i@example.com');"
done > large_file.sql

# Time the lexer
time ./sql_lexer large_file.sql > /dev/null
```

### Memory Usage Monitoring

```bash
# Monitor memory usage during lexing
/usr/bin/time -v ./sql_lexer large_file.sql > /dev/null
```

## Integration Examples

### Shell Scripting

```bash
#!/bin/bash
# Count different token types in a SQL file

sql_file="$1"
if [ ! -f "$sql_file" ]; then
    echo "Usage: $0 <sql_file>"
    exit 1
fi

echo "Token analysis for: $sql_file"
echo "=========================="

# Count SELECT statements
select_count=$(./sql_lexer "$sql_file" | grep -c "SELECT")
echo "SELECT statements: $select_count"

# Count identifiers
identifier_count=$(./sql_lexer "$sql_file" | grep -c "IDENTIFIER")
echo "Identifiers: $identifier_count"

# Find unknown tokens
unknown_tokens=$(./sql_lexer "$sql_file" | grep "UNKNOWN_TOKEN" | wc -l)
if [ $unknown_tokens -gt 0 ]; then
    echo "WARNING: $unknown_tokens unknown tokens found!"
    ./sql_lexer "$sql_file" | grep "UNKNOWN_TOKEN"
fi
```

### Python Integration

```python
#!/usr/bin/env python3
import subprocess
import re

def analyze_sql_file(filename):
    """Analyze SQL file and return token statistics."""
    result = subprocess.run(['./sql_lexer', filename], 
                          capture_output=True, text=True)
    
    if result.returncode != 0:
        return None
    
    tokens = {}
    for line in result.stdout.split('\n'):
        match = re.match(r'Line \d+, Col \d+: (\w+)', line)
        if match:
            token_type = match.group(1)
            tokens[token_type] = tokens.get(token_type, 0) + 1
    
    return tokens

# Usage
stats = analyze_sql_file('sample.sql')
if stats:
    print("Token distribution:")
    for token, count in sorted(stats.items()):
        print(f"  {token}: {count}")
```

## Troubleshooting Examples

### Common Issues

1. **File not found**:
   ```bash
   ./sql_lexer nonexistent.sql
   # Error: Cannot open file nonexistent.sql
   ```

2. **Empty input**:
   ```bash
   echo "" | ./sql_lexer
   # Reading from standard input...
   # ----------------------------------------
   # Tokenization complete.
   ```

3. **Very long lines**:
   ```sql
   SELECT very_long_identifier_name_that_exceeds_normal_length_but_should_still_work FROM table_with_extremely_long_name;
   ```

## Next Steps

- **API Programming**: See [Lexer Functions](../api/lexer.md)
- **Extending**: Read [Developer Guide](../developer-guide/extending.md)
- **Performance**: Check [Technical Specs](../technical/performance.md)
- **Command Line**: Review [CLI Reference](cli.md)