#!/bin/bash
# Quick 5-minute demo script

echo "╔════════════════════════════════════════╗"
echo "║     dvSQL - Quick Demo (5 minutes)    ║"
echo "╔════════════════════════════════════════╗"
echo ""

if [ ! -f "./dvsql" ]; then
    echo "❌ Error: dvsql not found. Run 'make' first."
    exit 1
fi

echo "1️⃣  Show all tables"
echo "   Query: SHOW TABLES;"
./dvsql demo/12_show_tables.sql 2>&1 | grep -A 10 "Tables:"
echo ""
read -p "Press Enter to continue..."

echo ""
echo "2️⃣  Describe users table structure"
echo "   Query: DESC users;"
./dvsql demo/13_describe_table.sql 2>&1 | grep -A 15 "Table:"
echo ""
read -p "Press Enter to continue..."

echo ""
echo "3️⃣  Basic SELECT - all data"
echo "   Query: SELECT * FROM users;"
./dvsql demo/01_basic_select.sql 2>&1 | grep -A 12 "Query Results:"
echo ""
read -p "Press Enter to continue..."

echo ""
echo "4️⃣  WHERE with equality"
echo "   Query: SELECT * FROM users WHERE id = 2;"
./dvsql demo/03_where_equality.sql 2>&1 | grep -A 10 "Query Results:"
echo ""
read -p "Press Enter to continue..."

echo ""
echo "5️⃣  WHERE with comparison"
echo "   Query: SELECT name, age FROM users WHERE age > 25;"
./dvsql demo/04_where_comparison.sql 2>&1 | grep -A 10 "Query Results:"
echo ""
read -p "Press Enter to continue..."

echo ""
echo "6️⃣  WHERE with AND operator"
echo "   Query: SELECT * FROM users WHERE age > 25 AND id < 4;"
./dvsql demo/07_where_and.sql 2>&1 | grep -A 10 "Query Results:"
echo ""
read -p "Press Enter to continue..."

echo ""
echo "7️⃣  WHERE with OR operator"
echo "   Query: SELECT * FROM users WHERE id = 1 OR id = 4;"
./dvsql demo/08_where_or.sql 2>&1 | grep -A 10 "Query Results:"
echo ""
read -p "Press Enter to continue..."

echo ""
echo "8️⃣  Complex query"
echo "   Query: SELECT name, age, email FROM users"
echo "          WHERE (age > 20 AND age < 30) OR id = 3;"
./dvsql demo/09_where_complex.sql 2>&1 | grep -A 12 "Query Results:"
echo ""

echo "╔════════════════════════════════════════╗"
echo "║          Demo Complete! ✨             ║"
echo "╚════════════════════════════════════════╝"
echo ""
echo "📝 Next steps:"
echo "   • Run './dvsql' for interactive mode"
echo "   • Check 'demo/README.md' for more examples"
echo "   • See 'docs/' for full documentation"
echo ""
