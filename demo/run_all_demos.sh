#!/bin/bash
# Script to run all demo queries and show their output

echo "========================================"
echo "   dvSQL Demo - Query Showcase"
echo "========================================"
echo ""

# Array of demo files with descriptions
declare -a demos=(
    "01_basic_select.sql:Basic SELECT - All columns"
    "02_select_specific_columns.sql:SELECT - Specific columns"
    "03_where_equality.sql:WHERE - Equality (=)"
    "04_where_comparison.sql:WHERE - Comparison (>)"
    "05_where_range.sql:WHERE - Range (AND)"
    "06_where_string.sql:WHERE - String match"
    "07_where_and.sql:WHERE - AND operator"
    "08_where_or.sql:WHERE - OR operator"
    "09_where_complex.sql:WHERE - Complex conditions"
    "13_describe_table.sql:DESCRIBE - Table structure"
    "12_show_tables.sql:SHOW TABLES - List all tables"
    "14_inequality.sql:WHERE - Not equal (<>)"
    "15_less_equal.sql:WHERE - Less or equal (<=)"
)

# Check if dvsql executable exists
if [ ! -f "./dvsql" ]; then
    echo "Error: dvsql executable not found!"
    echo "Please run 'make' first to build the project."
    exit 1
fi

# Run each demo
for demo in "${demos[@]}"; do
    IFS=':' read -r file description <<< "$demo"
    
    if [ -f "demo/$file" ]; then
        echo "----------------------------------------"
        echo "Demo: $description"
        echo "File: demo/$file"
        echo "----------------------------------------"
        
        # Show the query
        echo -e "\nQuery:"
        grep -v "^--" "demo/$file" | grep -v "^$" | head -3
        
        echo -e "\nOutput:"
        ./dvsql "demo/$file" 2>&1 | grep -A 100 "Query Results:" | head -20
        echo ""
        
        # Small delay for readability
        sleep 0.5
    fi
done

echo "========================================"
echo "   Demo Complete!"
echo "========================================"
echo ""
echo "To run individual demos:"
echo "  ./dvsql demo/<filename>.sql"
echo ""
echo "To run interactively:"
echo "  ./dvsql"
echo ""
