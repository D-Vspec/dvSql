%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/ast.h"

/* External variables from lexer */
extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;

/* Error handling */
void yyerror(const char* s);

/* Global AST root */
ast_node_t* ast_root = NULL;
%}

/* Define YYSTYPE union for semantic values */
%union {
    int int_val;
    double float_val;
    char* string_val;
    ast_node_t* ast_node;
    expression_t* expression;
    column_def_t* column_def;
    column_list_t* column_list;
    value_list_t* value_list;
    table_ref_t* table_ref;
    join_clause_t* join_clause;
    literal_value_t literal;
    data_type_t data_type;
    join_type_t join_type;
}

/* Token declarations */
%token <string_val> IDENTIFIER STRING_LITERAL
%token <int_val> INTEGER_LITERAL
%token <float_val> DECIMAL_LITERAL

%token SELECT FROM WHERE INSERT INTO VALUES UPDATE SET DELETE
%token CREATE TABLE DROP ALTER AND OR NOT NULL_TOK TRUE_TOK FALSE_TOK
%token AS ORDER BY GROUP HAVING LIMIT OFFSET
%token JOIN INNER LEFT RIGHT OUTER ON USING DISTINCT ALL
%token IN EXISTS BETWEEN LIKE IS UNION INTERSECT EXCEPT

%token INT_TYPE INTEGER_TYPE VARCHAR_TYPE CHAR_TYPE TEXT_TYPE
%token DECIMAL_TYPE NUMERIC_TYPE FLOAT_TYPE REAL_TYPE
%token DATE_TYPE TIME_TYPE TIMESTAMP_TYPE BOOLEAN_TYPE

%token PRIMARY KEY FOREIGN REFERENCES UNIQUE CHECK DEFAULT AUTO_INCREMENT

%token EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%token PLUS MINUS MULTIPLY DIVIDE MODULO

%token LPAREN RPAREN COMMA SEMICOLON DOT

%token COUNT SUM AVG MIN MAX

%token UNKNOWN_TOKEN

/* Type declarations for non-terminals */
%type <ast_node> statement select_statement insert_statement update_statement
%type <ast_node> delete_statement create_table_statement drop_table_statement

%type <column_list> column_list select_column_list update_column_list
%type <value_list> value_list update_value_list
%type <table_ref> table_reference from_clause
%type <join_clause> join_clause_list join_clause
%type <expression> expression condition where_clause having_clause
%type <expression> literal function_call column_reference
%type <column_def> column_definition_list column_definition
%type <data_type> data_type
%type <join_type> join_type
%type <literal> literal_value

/* Operator precedence and associativity */
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT
%left DOT

/* Start symbol */
%start program

%%

program:
    statement_list
    ;

statement_list:
    statement_list statement SEMICOLON { ast_root = $2; }
    | statement SEMICOLON { ast_root = $1; }
    ;

statement:
    select_statement { $$ = $1; }
    | insert_statement { $$ = $1; }
    | update_statement { $$ = $1; }
    | delete_statement { $$ = $1; }
    | create_table_statement { $$ = $1; }
    | drop_table_statement { $$ = $1; }
    ;

/* SELECT statement */
select_statement:
    SELECT select_column_list from_clause where_clause {
        $$ = create_select_stmt($2, $3);
        if ($$) $$->data.select_stmt.where_clause = $4;
    }
    | SELECT select_column_list from_clause {
        $$ = create_select_stmt($2, $3);
    }
    | SELECT DISTINCT select_column_list from_clause where_clause {
        $$ = create_select_stmt($3, $4);
        if ($$) {
            $$->data.select_stmt.distinct = 1;
            $$->data.select_stmt.where_clause = $5;
        }
    }
    | SELECT DISTINCT select_column_list from_clause {
        $$ = create_select_stmt($3, $4);
        if ($$) $$->data.select_stmt.distinct = 1;
    }
    ;

select_column_list:
    MULTIPLY {
        expression_t* expr = create_identifier_expr("*");
        $$ = create_column_list(expr);
    }
    | column_list { $$ = $1; }
    ;

column_list:
    column_list COMMA expression {
        add_column_to_list(&$1, $3);
        $$ = $1;
    }
    | expression {
        $$ = create_column_list($1);
    }
    ;

from_clause:
    FROM table_reference join_clause_list {
        $$ = $2;
        if ($$) $$->next = (table_ref_t*)$3;
    }
    | FROM table_reference {
        $$ = $2;
    }
    ;

table_reference:
    IDENTIFIER {
        $$ = create_table_ref($1, NULL);
    }
    | IDENTIFIER AS IDENTIFIER {
        $$ = create_table_ref($1, $3);
    }
    | IDENTIFIER IDENTIFIER {
        $$ = create_table_ref($1, $2);
    }
    ;

join_clause_list:
    join_clause_list join_clause {
        add_join_to_clause(&$1, $2);
        $$ = $1;
    }
    | join_clause { $$ = $1; }
    ;

join_clause:
    join_type JOIN table_reference ON condition {
        $$ = create_join_clause($1, $3, $5);
    }
    | JOIN table_reference ON condition {
        $$ = create_join_clause(JOIN_INNER, $2, $4);
    }
    ;

join_type:
    INNER { $$ = JOIN_INNER; }
    | LEFT { $$ = JOIN_LEFT; }
    | RIGHT { $$ = JOIN_RIGHT; }
    | LEFT OUTER { $$ = JOIN_LEFT; }
    | RIGHT OUTER { $$ = JOIN_RIGHT; }
    ;

where_clause:
    WHERE condition { $$ = $2; }
    | /* empty */ { $$ = NULL; }
    ;

having_clause:
    HAVING condition { $$ = $2; }
    | /* empty */ { $$ = NULL; }
    ;

/* INSERT statement */
insert_statement:
    INSERT INTO IDENTIFIER LPAREN column_list RPAREN VALUES LPAREN value_list RPAREN {
        $$ = create_insert_stmt($3, $5, $9);
    }
    | INSERT INTO IDENTIFIER VALUES LPAREN value_list RPAREN {
        $$ = create_insert_stmt($3, NULL, $6);
    }
    ;

value_list:
    value_list COMMA expression {
        add_value_to_list(&$1, $3);
        $$ = $1;
    }
    | expression {
        $$ = create_value_list($1);
    }
    ;

/* UPDATE statement */
update_statement:
    UPDATE IDENTIFIER SET update_column_list where_clause {
        /* Extract values from update_column_list for set_values */
        value_list_t* values = NULL;
        column_list_t* current = $4;
        while (current) {
            if (!values) {
                values = create_value_list(current->column);
            } else {
                add_value_to_list(&values, current->column);
            }
            current = current->next;
        }
        $$ = create_update_stmt($2, $4, values, $5);
    }
    ;

update_column_list:
    update_column_list COMMA IDENTIFIER EQUAL expression {
        expression_t* col_expr = create_identifier_expr($3);
        add_column_to_list(&$1, col_expr);
        $$ = $1;
    }
    | IDENTIFIER EQUAL expression {
        expression_t* col_expr = create_identifier_expr($1);
        $$ = create_column_list(col_expr);
    }
    ;

/* DELETE statement */
delete_statement:
    DELETE FROM IDENTIFIER where_clause {
        $$ = create_delete_stmt($3, $4);
    }
    ;

/* CREATE TABLE statement */
create_table_statement:
    CREATE TABLE IDENTIFIER LPAREN column_definition_list RPAREN {
        $$ = create_create_table_stmt($3, $5);
    }
    ;

column_definition_list:
    column_definition_list COMMA column_definition {
        add_column_to_def(&$1, $3);
        $$ = $1;
    }
    | column_definition { $$ = $1; }
    ;

column_definition:
    IDENTIFIER data_type {
        $$ = create_column_def($1, $2);
    }
    | IDENTIFIER data_type LPAREN INTEGER_LITERAL RPAREN {
        $$ = create_column_def($1, $2);
        if ($$) $$->size = $4;
    }
    | IDENTIFIER data_type PRIMARY KEY {
        $$ = create_column_def($1, $2);
        if ($$) $$->is_primary_key = 1;
    }
    | IDENTIFIER data_type NOT NULL_TOK {
        $$ = create_column_def($1, $2);
        if ($$) $$->is_not_null = 1;
    }
    | IDENTIFIER data_type UNIQUE {
        $$ = create_column_def($1, $2);
        if ($$) $$->is_unique = 1;
    }
    | IDENTIFIER data_type AUTO_INCREMENT {
        $$ = create_column_def($1, $2);
        if ($$) $$->has_auto_increment = 1;
    }
    ;

data_type:
    INT_TYPE { $$ = DATA_TYPE_INT; }
    | INTEGER_TYPE { $$ = DATA_TYPE_INT; }
    | VARCHAR_TYPE { $$ = DATA_TYPE_VARCHAR; }
    | CHAR_TYPE { $$ = DATA_TYPE_CHAR; }
    | TEXT_TYPE { $$ = DATA_TYPE_TEXT; }
    | DECIMAL_TYPE { $$ = DATA_TYPE_DECIMAL; }
    | NUMERIC_TYPE { $$ = DATA_TYPE_DECIMAL; }
    | FLOAT_TYPE { $$ = DATA_TYPE_FLOAT; }
    | REAL_TYPE { $$ = DATA_TYPE_FLOAT; }
    | DATE_TYPE { $$ = DATA_TYPE_DATE; }
    | TIME_TYPE { $$ = DATA_TYPE_TIME; }
    | TIMESTAMP_TYPE { $$ = DATA_TYPE_TIMESTAMP; }
    | BOOLEAN_TYPE { $$ = DATA_TYPE_BOOLEAN; }
    ;

/* DROP TABLE statement */
drop_table_statement:
    DROP TABLE IDENTIFIER {
        $$ = create_drop_table_stmt($3);
    }
    ;

/* Expressions and conditions */
expression:
    literal { $$ = $1; }
    | column_reference { $$ = $1; }
    | function_call { $$ = $1; }
    | expression PLUS expression {
        $$ = create_binary_op_expr($1, $3, PLUS);
    }
    | expression MINUS expression {
        $$ = create_binary_op_expr($1, $3, MINUS);
    }
    | expression MULTIPLY expression {
        $$ = create_binary_op_expr($1, $3, MULTIPLY);
    }
    | expression DIVIDE expression {
        $$ = create_binary_op_expr($1, $3, DIVIDE);
    }
    | expression MODULO expression {
        $$ = create_binary_op_expr($1, $3, MODULO);
    }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

condition:
    expression EQUAL expression {
        $$ = create_binary_op_expr($1, $3, EQUAL);
    }
    | expression NOT_EQUAL expression {
        $$ = create_binary_op_expr($1, $3, NOT_EQUAL);
    }
    | expression LESS_THAN expression {
        $$ = create_binary_op_expr($1, $3, LESS_THAN);
    }
    | expression GREATER_THAN expression {
        $$ = create_binary_op_expr($1, $3, GREATER_THAN);
    }
    | expression LESS_EQUAL expression {
        $$ = create_binary_op_expr($1, $3, LESS_EQUAL);
    }
    | expression GREATER_EQUAL expression {
        $$ = create_binary_op_expr($1, $3, GREATER_EQUAL);
    }
    | condition AND condition {
        $$ = create_binary_op_expr($1, $3, AND);
    }
    | condition OR condition {
        $$ = create_binary_op_expr($1, $3, OR);
    }
    | NOT condition {
        $$ = create_unary_op_expr($2, NOT);
    }
    | LPAREN condition RPAREN { $$ = $2; }
    | expression { $$ = $1; }
    ;

literal:
    INTEGER_LITERAL {
        literal_value_t val;
        val.int_val = $1;
        $$ = create_literal_expr(val, INTEGER_LITERAL);
    }
    | DECIMAL_LITERAL {
        literal_value_t val;
        val.float_val = $1;
        $$ = create_literal_expr(val, DECIMAL_LITERAL);
    }
    | STRING_LITERAL {
        literal_value_t val;
        val.string_val = $1;
        $$ = create_literal_expr(val, STRING_LITERAL);
    }
    | NULL_TOK {
        literal_value_t val;
        val.string_val = NULL;
        $$ = create_literal_expr(val, NULL_TOK);
    }
    | TRUE_TOK {
        literal_value_t val;
        val.int_val = 1;
        $$ = create_literal_expr(val, TRUE_TOK);
    }
    | FALSE_TOK {
        literal_value_t val;
        val.int_val = 0;
        $$ = create_literal_expr(val, FALSE_TOK);
    }
    ;

column_reference:
    IDENTIFIER {
        $$ = create_identifier_expr($1);
    }
    | IDENTIFIER DOT IDENTIFIER {
        $$ = create_column_ref_expr($1, $3);
    }
    ;

function_call:
    IDENTIFIER LPAREN RPAREN {
        $$ = create_function_call_expr($1, NULL, 0);
    }
    | IDENTIFIER LPAREN value_list RPAREN {
        /* Convert value_list to expression array */
        int count = 0;
        value_list_t* current = $3;
        while (current) {
            count++;
            current = current->next;
        }
        
        expression_t** args = malloc(count * sizeof(expression_t*));
        current = $3;
        for (int i = 0; i < count; i++) {
            args[i] = current->value;
            current = current->next;
        }
        
        $$ = create_function_call_expr($1, args, count);
    }
    | COUNT LPAREN MULTIPLY RPAREN {
        $$ = create_function_call_expr("COUNT", NULL, 0);
    }
    | COUNT LPAREN expression RPAREN {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = $3;
        $$ = create_function_call_expr("COUNT", args, 1);
    }
    | SUM LPAREN expression RPAREN {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = $3;
        $$ = create_function_call_expr("SUM", args, 1);
    }
    | AVG LPAREN expression RPAREN {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = $3;
        $$ = create_function_call_expr("AVG", args, 1);
    }
    | MIN LPAREN expression RPAREN {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = $3;
        $$ = create_function_call_expr("MIN", args, 1);
    }
    | MAX LPAREN expression RPAREN {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = $3;
        $$ = create_function_call_expr("MAX", args, 1);
    }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s near '%s'\n", yylineno, s, yytext);
}