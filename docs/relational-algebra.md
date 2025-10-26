# Relational Algebra Conversion

This document describes the relational algebra conversion feature of the dvSQL parser.

## Overview

The dvSQL parser can convert SQL SELECT statements into equivalent relational algebra expressions. This is useful for:

- **Educational purposes** - Understanding query evaluation and optimization
- **Query analysis** - Visualizing the logical structure of queries  
- **Academic work** - Converting between SQL and formal relational algebra notation
- **Database theory** - Working with the mathematical foundation of databases

## Supported Operations

### Core Relational Algebra Operators

| Operator | Symbol | SQL Equivalent | Description |
|----------|--------|----------------|-------------|
| Selection | σ | WHERE clause | Filter rows based on conditions |
| Projection | π | SELECT columns | Select specific columns |
| Join | ⋈ | JOIN | Combine tables based on conditions |
| Theta Join | ⋈θ | JOIN ... ON | Join with explicit conditions |
| Cartesian Product | × | FROM t1, t2 | Cross product of tables |
| Union | ∪ | UNION | Combine results from multiple queries |
| Rename | ρ | AS alias | Rename tables or columns |

### SQL Features Supported

- **Basic SELECT** - Column selection and table references
- **WHERE clauses** - Converted to selection (σ) operations
- **JOIN operations** - Inner, left, right joins with ON conditions
- **Table aliases** - Preserved in relational algebra output
- **Column references** - Qualified (table.column) and unqualified
- **Complex conditions** - Multiple predicates with AND/OR

## Usage

### Command Line Options

```bash
# Show relational algebra alongside AST
./sql_parser -r query.sql

# Show only relational algebra (no AST or execution)
./sql_parser -a query.sql

# Parse from stdin with relational algebra
echo "SELECT * FROM users;" | ./sql_parser -a
```

### Output Formats

The parser provides three different output formats for relational algebra:

#### 1. Tree Format
Shows the hierarchical structure of operations:
```
π (PROJECTION) [name, email]
  σ (SELECTION) [age > 18]
    R (RELATION) users
```

#### 2. Mathematical Notation
Standard mathematical relational algebra notation:
```
π_{name, email}(σ_{age > 18}(users))
```

#### 3. Linear Notation
Same as mathematical notation but in a single line for easy copying.

## Examples

### Example 1: Basic Selection and Projection

**SQL:**
```sql
SELECT name, email FROM users WHERE age > 18;
```

**Relational Algebra:**
```
π_{name, email}(σ_{age > 18}(users))
```

### Example 2: Join with Condition

**SQL:**
```sql
SELECT u.name, p.title 
FROM users u 
JOIN posts p ON u.id = p.user_id;
```

**Relational Algebra:**
```
π_{u.name, p.title}((users(u) ⋈θ_{u.id = p.user_id} posts(p)))
```

### Example 3: Complex Query with Join and Selection

**SQL:**
```sql
SELECT u.name, p.title 
FROM users u 
JOIN posts p ON u.id = p.user_id 
WHERE u.age > 21 AND p.published = 1;
```

**Relational Algebra:**
```
π_{u.name, p.title}(σ_{u.age > 21 ∧ p.published = 1}((users(u) ⋈θ_{u.id = p.user_id} posts(p))))
```

## Testing

Run the relational algebra test suite:

```bash
# Test relational algebra conversion
make test-ra

# Test specific cases
./sql_parser -a tests/ra_test_basic_select.sql
./sql_parser -a tests/ra_test_join.sql
./sql_parser -a tests/ra_test_complex.sql
```

## Limitations

Current limitations of the relational algebra converter:

1. **INSERT/UPDATE/DELETE** - Only SELECT statements are supported
2. **Aggregate functions** - GROUP BY and aggregation functions need enhancement
3. **Subqueries** - Nested queries are not yet supported
4. **Set operations** - UNION, INTERSECT, EXCEPT need implementation
5. **ORDER BY** - Sorting operations (τ) are partially implemented

## Implementation Details

### Architecture

The conversion process follows these steps:

1. **Parse SQL** - Generate AST from SQL statement
2. **Convert AST** - Transform SQL AST to relational algebra tree
3. **Build operations** - Create appropriate RA operators (σ, π, ⋈, etc.)
4. **Generate output** - Format in tree, mathematical, or linear notation

### Key Functions

- `sql_to_relational_algebra()` - Main conversion entry point
- `convert_select_stmt()` - Convert SELECT statements
- `build_from_clause()` - Handle FROM and JOIN clauses
- `convert_expression_to_condition()` - Convert WHERE conditions
- `print_ra_mathematical()` - Generate mathematical notation

### Memory Management

The relational algebra tree is completely separate from the SQL AST:
- RA nodes reference but don't own SQL expression objects
- Proper cleanup with `free_ra_node()` function
- Memory-safe string operations throughout

## Future Enhancements

Planned improvements:

1. **Query Optimization** - Push selections down, join reordering
2. **Extended Operations** - Full support for aggregation (γ), sorting (τ)
3. **Subquery Support** - Nested relational algebra expressions  
4. **Cost Estimation** - Basic cost models for educational purposes
5. **Graphical Output** - Generate visual trees and graphs
6. **LaTeX Export** - Export mathematical notation to LaTeX format

## Academic References

This implementation follows standard relational algebra notation from:

- *Database Systems: The Complete Book* by Garcia-Molina, Ullman, and Widom
- *Fundamentals of Database Systems* by Elmasri and Navathe
- *Database Management Systems* by Ramakrishnan and Gehrke