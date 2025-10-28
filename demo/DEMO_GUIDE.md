# dvSQL Project Demo Guide

## Quick Start Demo (1 minute)

The fastest way to see dvSQL in action:

```bash
cd /path/to/dvSql
./dvsql demo/01_basic_select.sql
./dvsql demo/03_where_equality.sql
./dvsql demo/07_where_and.sql
```

## Complete Demo (5 minutes)

Run the interactive demo script:

```bash
./demo/quick_demo.sh
```

This will walk you through:
1. Table listing (SHOW TABLES)
2. Table structure (DESC)
3. Basic SELECT
4. WHERE clauses with different operators
5. Complex queries with AND/OR

## Full Demo Presentation (15 minutes)

Run all demos at once:

```bash
./demo/run_all_demos.sh
```

## Interactive Demo Session

Start the SQL shell and try queries manually:

```bash
./dvsql
```

Then paste these queries one by one:

```sql
-- See what tables exist
SHOW TABLES;

-- Examine table structure
DESC users;

-- Basic query
SELECT * FROM users;

-- Filtered query
SELECT * FROM users WHERE age > 25;

-- Complex query
SELECT name, age FROM users WHERE (age > 20 AND age < 30) OR id = 3;
```

## Demo Scenarios

### Scenario 1: Database Exploration
```bash
./dvsql demo/12_show_tables.sql      # List tables
./dvsql demo/13_describe_table.sql   # Show structure
./dvsql demo/01_basic_select.sql     # View all data
```

### Scenario 2: Simple Filtering
```bash
./dvsql demo/03_where_equality.sql   # Find by ID
./dvsql demo/06_where_string.sql     # Find by name
./dvsql demo/04_where_comparison.sql # Age filter
```

### Scenario 3: Advanced Queries
```bash
./dvsql demo/05_where_range.sql      # Range query
./dvsql demo/07_where_and.sql        # Multiple conditions
./dvsql demo/08_where_or.sql         # Alternative conditions
./dvsql demo/09_where_complex.sql    # Nested conditions
```

### Scenario 4: All Operators
```bash
./dvsql demo/03_where_equality.sql   # = operator
./dvsql demo/14_inequality.sql       # <> operator
./dvsql demo/04_where_comparison.sql # > operator
./dvsql demo/15_less_equal.sql       # <= operator
```

## Live Coding Demo

Show how to build queries step by step:

```bash
./dvsql
```

```sql
-- Start simple
SELECT * FROM users;

-- Add specific columns
SELECT name, email FROM users;

-- Add one condition
SELECT name, email FROM users WHERE age > 25;

-- Add second condition
SELECT name, email FROM users WHERE age > 25 AND id < 4;

-- Show the power of OR
SELECT * FROM users WHERE id = 1 OR id = 4;

-- Complex nested conditions
SELECT name, age, email FROM users 
WHERE (age > 20 AND age < 30) OR id = 3;
```

## Feature Highlights for Presentation

### ✅ What Works Well

1. **Complete SQL Parsing**
   - SELECT with column projection
   - WHERE with multiple operators
   - AND/OR logical operators
   - Comparison operators: =, <>, <, >, <=, >=

2. **AST Visualization**
   - Shows parsed query structure
   - Educational for understanding SQL

3. **Relational Algebra**
   - Converts SQL to RA operations
   - Efficient query execution

4. **Data Persistence**
   - JSON schemas for table definitions
   - CSV format for data storage
   - Easy to inspect and debug

5. **Meta Commands**
   - SHOW TABLES
   - DESCRIBE table
   - CREATE TABLE
   - INSERT INTO

### 📊 Demo Data

The `users` table has 4 records perfect for demos:
- ID range: 1-4
- Ages: 22, 25, 28, 35
- Good variety for comparison demos

### 🎯 Best Demos for Showcasing

**For technical audience:**
- Show the AST output
- Explain the relational algebra conversion
- Demonstrate parser flexibility

**For general audience:**
- Focus on query results
- Use `-q` flag to hide AST: `./dvsql -q demo/01_basic_select.sql`
- Show practical filtering examples

**For recruiters/managers:**
- Run `./demo/quick_demo.sh`
- Show the README.md
- Highlight the technology stack (Flex, Bison, C)

## Troubleshooting Demo Issues

If something doesn't work during the demo:

```bash
# Rebuild the project
make clean && make

# Check if data files exist
ls -la data/tables/users.csv
ls -la data/schemas/users.json

# Test basic functionality
echo "SELECT * FROM users;" | ./dvsql
```

## Post-Demo Resources

Point viewers to:
- `demo/README.md` - Complete demo documentation
- `docs/` - Full technical documentation
- `tests/` - Test SQL files
- GitHub repository (if public)

## Tips for Live Demos

1. **Have queries ready to copy-paste** - Use `demo_session.txt`
2. **Test beforehand** - Run through once before presenting
3. **Have a backup terminal** - In case one hangs
4. **Use large terminal font** - For visibility in presentations
5. **Prepare for questions** - Common ones:
   - "How does parsing work?" → Show lexer/parser files
   - "What's relational algebra?" → Use `-a` flag to show RA tree
   - "Can it handle JOINs?" → Explain it's in the parser, execution WIP
   - "What's next?" → Discuss TODO items in docs

## Quick Command Reference

```bash
# Build
make

# Run file
./dvsql demo/file.sql

# Interactive mode
./dvsql

# Quiet mode (no AST)
./dvsql -q demo/file.sql

# Show relational algebra
./dvsql -a demo/file.sql

# Verbose mode
./dvsql -v demo/file.sql
```

Good luck with your demo! 🚀
