#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward declarations */
typedef struct ast_node ast_node_t;
typedef struct column_def column_def_t;
typedef struct expression expression_t;
typedef struct column_list column_list_t;
typedef struct value_list value_list_t;
typedef struct table_ref table_ref_t;
typedef struct join_clause join_clause_t;
typedef struct condition condition_t;

/* External function for token name conversion */
const char* get_token_name(int token);

/* AST Node Types */
typedef enum {
    NODE_SELECT_STMT,
    NODE_INSERT_STMT,
    NODE_UPDATE_STMT,
    NODE_DELETE_STMT,
    NODE_CREATE_TABLE_STMT,
    NODE_DROP_TABLE_STMT,
    NODE_DESC_STMT,
    NODE_SHOW_TABLES_STMT,
    
    NODE_COLUMN_LIST,
    NODE_VALUE_LIST,
    NODE_TABLE_REF,
    NODE_JOIN_CLAUSE,
    NODE_CONDITION,
    NODE_EXPRESSION,
    NODE_COLUMN_DEF,
    NODE_IDENTIFIER,
    NODE_LITERAL,
    NODE_OPERATOR
} ast_node_type_t;

/* Expression types */
typedef enum {
    EXPR_IDENTIFIER,
    EXPR_LITERAL,
    EXPR_BINARY_OP,
    EXPR_UNARY_OP,
    EXPR_FUNCTION_CALL,
    EXPR_COLUMN_REF
} expression_type_t;

/* Join types */
typedef enum {
    JOIN_INNER,
    JOIN_LEFT,
    JOIN_RIGHT,
    JOIN_OUTER
} join_type_t;

/* Data types for column definitions */
typedef enum {
    DATA_TYPE_INT,
    DATA_TYPE_VARCHAR,
    DATA_TYPE_CHAR,
    DATA_TYPE_TEXT,
    DATA_TYPE_DECIMAL,
    DATA_TYPE_FLOAT,
    DATA_TYPE_DATE,
    DATA_TYPE_TIME,
    DATA_TYPE_TIMESTAMP,
    DATA_TYPE_BOOLEAN
} data_type_t;

/* Literal value union */
typedef union {
    int int_val;
    double float_val;
    char* string_val;
} literal_value_t;

/* Expression structure */
struct expression {
    expression_type_t type;
    int literal_type;  /* Only used for EXPR_LITERAL */
    union {
        char* identifier;
        literal_value_t literal;
        struct {
            expression_t* left;
            expression_t* right;
            int operator;
        } binary_op;
        struct {
            expression_t* operand;
            int operator;
        } unary_op;
        struct {
            char* function_name;
            expression_t** args;
            int arg_count;
        } function_call;
        struct {
            char* table_name;
            char* column_name;
        } column_ref;
    } data;
};

/* Column definition structure */
struct column_def {
    char* column_name;
    data_type_t data_type;
    int size;           /* For VARCHAR(n), CHAR(n), DECIMAL(p,s) */
    int precision;      /* For DECIMAL(p,s) */
    int is_primary_key;
    int is_not_null;
    int is_unique;
    int has_auto_increment;
    expression_t* default_value;
    column_def_t* next;
};

/* Column list structure */
struct column_list {
    expression_t* column;
    column_list_t* next;
};

/* Value list structure */
struct value_list {
    expression_t* value;
    value_list_t* next;
};

/* Table reference structure */
struct table_ref {
    char* table_name;
    char* alias;
    table_ref_t* next;
};

/* Join clause structure */
struct join_clause {
    join_type_t join_type;
    table_ref_t* table;
    expression_t* on_condition;
    join_clause_t* next;
};

/* Main AST node structure */
struct ast_node {
    ast_node_type_t type;
    union {
        struct {
            column_list_t* columns;
            table_ref_t* from_table;
            join_clause_t* joins;
            expression_t* where_clause;
            column_list_t* group_by;
            expression_t* having_clause;
            column_list_t* order_by;
            int limit_count;
            int offset_count;
            int distinct;
        } select_stmt;
        
        struct {
            char* table_name;
            column_list_t* columns;
            value_list_t* values;
        } insert_stmt;
        
        struct {
            char* table_name;
            column_list_t* set_columns;
            value_list_t* set_values;
            expression_t* where_clause;
        } update_stmt;
        
        struct {
            char* table_name;
            expression_t* where_clause;
        } delete_stmt;
        
        struct {
            char* table_name;
            column_def_t* columns;
        } create_table_stmt;
        
        struct {
            char* table_name;
        } drop_table_stmt;
        
        struct {
            char* table_name;
        } desc_stmt;
        
        struct {
            /* No additional data needed for SHOW TABLES */
        } show_tables_stmt;
    } data;
};

/* AST utility functions */
ast_node_t* create_select_stmt(column_list_t* columns, table_ref_t* from_table);
ast_node_t* create_insert_stmt(char* table_name, column_list_t* columns, value_list_t* values);
ast_node_t* create_update_stmt(char* table_name, column_list_t* set_columns, value_list_t* set_values, expression_t* where_clause);
ast_node_t* create_delete_stmt(char* table_name, expression_t* where_clause);
ast_node_t* create_create_table_stmt(char* table_name, column_def_t* columns);
ast_node_t* create_drop_table_stmt(char* table_name);
ast_node_t* create_desc_stmt(char* table_name);
ast_node_t* create_show_tables_stmt(void);

expression_t* create_identifier_expr(char* identifier);
expression_t* create_literal_expr(literal_value_t value, int literal_type);
expression_t* create_binary_op_expr(expression_t* left, expression_t* right, int operator);
expression_t* create_unary_op_expr(expression_t* operand, int operator);
expression_t* create_function_call_expr(char* function_name, expression_t** args, int arg_count);
expression_t* create_column_ref_expr(char* table_name, char* column_name);

column_def_t* create_column_def(char* column_name, data_type_t data_type);
column_list_t* create_column_list(expression_t* column);
value_list_t* create_value_list(expression_t* value);
table_ref_t* create_table_ref(char* table_name, char* alias);
join_clause_t* create_join_clause(join_type_t join_type, table_ref_t* table, expression_t* on_condition);

void add_column_to_list(column_list_t** list, expression_t* column);
void add_value_to_list(value_list_t** list, expression_t* value);
void add_table_to_ref(table_ref_t** ref, table_ref_t* table);
void add_join_to_clause(join_clause_t** clause, join_clause_t* join);
void add_column_to_def(column_def_t** def, column_def_t* column);

void print_ast(ast_node_t* node, int indent);
void free_ast(ast_node_t* node);
void free_expression(expression_t* expr);
void free_column_def(column_def_t* def);
void free_column_list(column_list_t* list);
void free_value_list(value_list_t* list);
void free_table_ref(table_ref_t* ref);
void free_join_clause(join_clause_t* clause);

#endif /* AST_H */