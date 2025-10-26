# Relational Algebra Execution Tutorial

This tutorial demonstrates how dvSQL uses relational algebra to execute queries, showing the step-by-step process from SQL to results.

## Setup

```bash
# Build the project
cd /path/to/dvSql
make clean && make

# Verify sample data exists
cat data/tables/users.csv
```

You should see sample user data like:
```csv
# Table: users
# --- DATA START ---
1,John,john@test.com,25,now
2,Jane Smith,jane@example.com,28,2023-02-01 09:15:00
3,Bob Johnson,bob@test.org,35,2023-03-15 14:20:30
4,Alice Brown,alice@demo.com,22,2023-04-10 16:45:00
```

## Example 1: Basic Selection (WHERE clause)

### SQL Query
```sql
SELECT * FROM users WHERE age > 25;
```

### Step 1: See the Relational Algebra
```bash
echo "SELECT * FROM users WHERE age > 25;" | ./sql_parser -r
```

**Expected Output:**
```
Relational Algebra:
==================
Tree Format:
σ (SELECTION) [age > 25]
  R (RELATION) users

Mathematical Notation:
σ_{age > 25}(users)

Query Results:
==============
id              | name            | email          | age            | created_at     
----------------+-----------------+----------------+----------------+----------------
1               | John            | john@test.com  | 25             | now            
2               | Jane Smith      | jane@example.com| 28             | 2023-02-01     
3               | Bob Johnson     | bob@test.org   | 35             | 2023-03-15     
4               | Alice Brown     | alice@demo.com | 22             | 2023-04-10     

4 row(s) returned.
```

### What Happened?
1. **SQL Parsing**: Query converted to AST
2. **RA Conversion**: AST → `σ_{age > 25}(users)`
3. **RA Execution**:
   - `execute_ra_relation("users")` - Load all user data from CSV
   - `execute_ra_selection(age > 25)` - Filter rows by age condition
4. **Results**: Filtered data displayed

## Example 2: Projection (SELECT specific columns)

### SQL Query
```sql
SELECT name, email FROM users;
```

### Step 1: See the Relational Algebra
```bash
echo "SELECT name, email FROM users;" | ./sql_parser -r
```

**Expected Output:**
```
Relational Algebra:
==================
Tree Format:
π (PROJECTION) [name, email]
  R (RELATION) users

Mathematical Notation:
π_{name, email}(users)

Query Results:
==============
name            | email          
----------------+----------------
John            | john@test.com  
Jane Smith      | jane@example.com
Bob Johnson     | bob@test.org   
Alice Brown     | alice@demo.com 

4 row(s) returned.
```

### What Happened?
1. **RA Conversion**: AST → `π_{name, email}(users)`
2. **RA Execution**:
   - `execute_ra_relation("users")` - Load all user data
   - `execute_ra_projection(name, email)` - Select only name and email columns
3. **Results**: Only requested columns shown

## Example 3: Combined Selection and Projection

### SQL Query
```sql
SELECT name, email FROM users WHERE age > 25;
```

### Step 1: See the Relational Algebra
```bash
echo "SELECT name, email FROM users WHERE age > 25;" | ./sql_parser -r
```

**Expected Output:**
```
Relational Algebra:
==================
Tree Format:
π (PROJECTION) [name, email]
  σ (SELECTION) [age > 25]
    R (RELATION) users

Mathematical Notation:
π_{name, email}(σ_{age > 25}(users))

Query Results:
==============
name            | email          
----------------+----------------
Jane Smith      | jane@example.com
Bob Johnson     | bob@test.org   

2 row(s) returned.
```

### What Happened?
1. **RA Conversion**: AST → `π_{name, email}(σ_{age > 25}(users))`
2. **RA Execution** (bottom-up):
   - `execute_ra_relation("users")` - Load all user data
   - `execute_ra_selection(age > 25)` - Filter by age condition
   - `execute_ra_projection(name, email)` - Select only name and email columns
3. **Results**: Filtered and projected data

## Example 4: Only Show Relational Algebra (No Execution)

If you want to see just the relational algebra conversion without execution:

```bash
echo "SELECT name FROM users WHERE age > 30;" | ./sql_parser -a
```

**Expected Output:**
```
Relational Algebra:
==================
Tree Format:
π (PROJECTION) [name]
  σ (SELECTION) [age > 30]
    R (RELATION) users

Mathematical Notation:
π_{name}(σ_{age > 30}(users))

Linear Notation:
π_{name}(σ_{age > 30}(users))
```

## Understanding the RA Tree Structure

### Tree Format Explanation
```
π (PROJECTION) [name, email]           ← Top level: Select columns
  σ (SELECTION) [age > 25]             ← Middle level: Filter rows  
    R (RELATION) users                 ← Bottom level: Load table
```

**Execution Order**: Bottom to top (users → filter → project)

### Mathematical Notation
- **π** (pi) = Projection (SELECT columns)
- **σ** (sigma) = Selection (WHERE clause)
- **R** = Relation (table)
- **Subscript** = Operation parameters

### Operations Supported
- **RA_RELATION**: Load table data from CSV
- **RA_SELECTION**: Filter rows (WHERE clause)
- **RA_PROJECTION**: Select columns (SELECT clause)
- **RA_THETA_JOIN**: Join with condition (JOIN ... ON)
- **RA_CARTESIAN**: Cartesian product (cross join)

## Behind the Scenes: Code Execution

### 1. Relation Loading (`execute_ra_relation`)
```c
// Load users table
ra_result_set_t* users_data = execute_ra_relation(users_node);
```
- Reads `data/schemas/users.json` for metadata
- Reads `data/tables/users.csv` for data
- Creates result set with 5 columns × 4 rows

### 2. Selection (`execute_ra_selection`)
```c
// Filter WHERE age > 25
ra_result_set_t* filtered_data = execute_ra_selection(selection_node);
```
- Evaluates condition for each row
- Keeps only rows where age > 25
- Returns subset of input rows

### 3. Projection (`execute_ra_projection`)
```c
// Select name, email columns
ra_result_set_t* final_result = execute_ra_projection(projection_node);
```
- Maps column names to indices
- Creates new result set with subset of columns
- Copies data for selected columns only

## Advanced Examples

### Complex WHERE Clause
```bash
echo "SELECT name FROM users WHERE age > 25 AND name LIKE 'J%';" | ./sql_parser -r
```

### Multiple Tables (Future Feature)
```sql
-- This will work when JOIN execution is fully implemented
SELECT u.name, p.title 
FROM users u 
JOIN posts p ON u.id = p.user_id 
WHERE u.age > 25;
```

Expected RA:
```
π_{u.name, p.title}(σ_{u.age > 25}(users(u) ⋈θ_{u.id = p.user_id} posts(p)))
```

## Comparison: Traditional vs RA Execution

### Traditional Database Approach
```
SQL → Query Planner → Optimized Plan → Execution Engine → Results
```

### dvSQL Approach
```
SQL → AST → Relational Algebra Tree → RA Execution Engine → Results
```

**Benefits of RA Approach:**
- ✅ **Educational**: Shows theoretical foundations
- ✅ **Modular**: Each RA operation is independent
- ✅ **Optimizable**: RA trees can be algebraically optimized
- ✅ **Extensible**: New operations are easy to add

## Troubleshooting

### No Results Displayed
- Check if table exists: `ls data/tables/`
- Verify table has data: `cat data/tables/users.csv`
- Try simpler query: `echo "SELECT * FROM users;" | ./sql_parser`

### Compilation Errors
```bash
make clean && make
```

### Debug Mode
```bash
echo "SELECT * FROM users;" | ./sql_parser -v
```

## Next Steps

1. **Try Your Own Queries**: Experiment with different WHERE conditions
2. **Create New Tables**: Use CREATE TABLE and INSERT statements
3. **Examine the Code**: Look at `src/c/relational_algebra.c` execution functions
4. **Extend the System**: Add new RA operations like UNION or ORDER BY

The relational algebra execution engine demonstrates how theoretical computer science concepts translate into practical database systems!