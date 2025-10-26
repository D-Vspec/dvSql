#ifndef RELATIONAL_ALGEBRA_H
#define RELATIONAL_ALGEBRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* Forward declarations */
typedef struct ra_node ra_node_t;
typedef struct ra_attribute ra_attribute_t;
typedef struct ra_attribute_list ra_attribute_list_t;
typedef struct ra_condition ra_condition_t;

/* Relational Algebra Operator Types */
typedef enum {
    RA_RELATION,        /* Base relation (table) */
    RA_SELECTION,       /* σ (sigma) - Selection operation */
    RA_PROJECTION,      /* π (pi) - Projection operation */
    RA_CARTESIAN,       /* × (times) - Cartesian product */
    RA_NATURAL_JOIN,    /* ⋈ (bowtie) - Natural join */
    RA_THETA_JOIN,      /* ⋈θ - Theta join (join with condition) */
    RA_LEFT_JOIN,       /* ⟕ - Left outer join */
    RA_RIGHT_JOIN,      /* ⟖ - Right outer join */
    RA_UNION,           /* ∪ - Union */
    RA_INTERSECTION,    /* ∩ - Intersection */
    RA_DIFFERENCE,      /* - - Set difference */
    RA_RENAME,          /* ρ (rho) - Rename operation */
    RA_AGGREGATION,     /* γ - Aggregation (group by) */
    RA_SORTING,         /* τ - Sorting (order by) */
    RA_DESC,            /* Meta operation - Describe table */
    RA_SHOW_TABLES      /* Meta operation - Show tables */
} ra_operator_type_t;

/* Attribute structure for projections and renamings */
struct ra_attribute {
    char* name;                 /* Attribute name */
    char* alias;               /* Alias name (for renaming) */
    char* table_name;          /* Optional table qualification */
    expression_t* expression;   /* For computed attributes */
    ra_attribute_t* next;
};

/* Attribute list structure */
struct ra_attribute_list {
    ra_attribute_t* attributes;
    int count;
};

/* Condition structure for selections and joins */
struct ra_condition {
    expression_t* expression;   /* The condition expression from AST */
    char* description;         /* Human-readable description */
};

/* Main Relational Algebra node structure */
struct ra_node {
    ra_operator_type_t type;
    union {
        /* Base relation */
        struct {
            char* name;
            char* alias;
        } relation;
        
        /* Selection (σ) */
        struct {
            ra_condition_t* condition;
            ra_node_t* input;
        } selection;
        
        /* Projection (π) */
        struct {
            ra_attribute_list_t* attributes;
            ra_node_t* input;
        } projection;
        
        /* Binary operations (joins, union, etc.) */
        struct {
            ra_node_t* left;
            ra_node_t* right;
            ra_condition_t* condition;  /* For theta joins */
        } binary_op;
        
        /* Rename (ρ) */
        struct {
            char* new_name;
            ra_attribute_list_t* attribute_mappings;  /* For attribute renaming */
            ra_node_t* input;
        } rename;
        
        /* Aggregation (γ) */
        struct {
            ra_attribute_list_t* group_by_attrs;
            ra_attribute_list_t* aggregate_attrs;
            ra_node_t* input;
        } aggregation;
        
        /* Sorting (τ) */
        struct {
            ra_attribute_list_t* sort_attrs;
            ra_node_t* input;
        } sorting;
        
        /* Describe table (meta operation) */
        struct {
            char* table_name;
        } desc;
        
        /* Show tables (meta operation) */
        struct {
            /* No additional data needed */
        } show_tables;
    } data;
};

/* Constructor functions for RA nodes */
ra_node_t* create_ra_relation(const char* name, const char* alias);
ra_node_t* create_ra_selection(ra_condition_t* condition, ra_node_t* input);
ra_node_t* create_ra_projection(ra_attribute_list_t* attributes, ra_node_t* input);
ra_node_t* create_ra_cartesian(ra_node_t* left, ra_node_t* right);
ra_node_t* create_ra_natural_join(ra_node_t* left, ra_node_t* right);
ra_node_t* create_ra_theta_join(ra_node_t* left, ra_node_t* right, ra_condition_t* condition);
ra_node_t* create_ra_left_join(ra_node_t* left, ra_node_t* right, ra_condition_t* condition);
ra_node_t* create_ra_right_join(ra_node_t* left, ra_node_t* right, ra_condition_t* condition);
ra_node_t* create_ra_union(ra_node_t* left, ra_node_t* right);
ra_node_t* create_ra_intersection(ra_node_t* left, ra_node_t* right);
ra_node_t* create_ra_difference(ra_node_t* left, ra_node_t* right);
ra_node_t* create_ra_rename(const char* new_name, ra_attribute_list_t* attr_mappings, ra_node_t* input);
ra_node_t* create_ra_aggregation(ra_attribute_list_t* group_by, ra_attribute_list_t* aggregates, ra_node_t* input);
ra_node_t* create_ra_sorting(ra_attribute_list_t* sort_attrs, ra_node_t* input);
ra_node_t* create_ra_desc(const char* table_name);
ra_node_t* create_ra_show_tables(void);

/* Helper functions for attributes and conditions */
ra_attribute_t* create_ra_attribute(const char* name, const char* alias, const char* table_name);
ra_attribute_t* create_ra_attribute_from_expr(expression_t* expr, const char* alias);
ra_attribute_list_t* create_ra_attribute_list();
void add_ra_attribute(ra_attribute_list_t* list, ra_attribute_t* attr);
ra_condition_t* create_ra_condition(expression_t* expr, const char* description);

/* SQL AST to Relational Algebra conversion functions */
ra_node_t* sql_to_relational_algebra(ast_node_t* sql_ast);
ra_node_t* convert_select_stmt(ast_node_t* select_stmt);
ra_node_t* convert_insert_stmt(ast_node_t* insert_stmt);
ra_node_t* convert_update_stmt(ast_node_t* update_stmt);
ra_node_t* convert_delete_stmt(ast_node_t* delete_stmt);
ra_node_t* convert_desc_stmt(ast_node_t* desc_stmt);
ra_node_t* convert_show_tables_stmt(ast_node_t* show_tables_stmt);

/* Helper conversion functions */
ra_attribute_list_t* convert_column_list_to_attributes(column_list_t* columns);
ra_node_t* build_from_clause(table_ref_t* from_table, join_clause_t* joins);
ra_condition_t* convert_expression_to_condition(expression_t* expr);
ra_attribute_t* convert_expression_to_attribute(expression_t* expr);

/* Display functions */
void print_ra_tree(ra_node_t* node, int indent);
void print_ra_mathematical(ra_node_t* node);
void print_ra_linear(ra_node_t* node);
const char* ra_operator_to_symbol(ra_operator_type_t type);
const char* ra_operator_to_name(ra_operator_type_t type);

/* Memory management */
void free_ra_node(ra_node_t* node);
void free_ra_attribute(ra_attribute_t* attr);
void free_ra_attribute_list(ra_attribute_list_t* list);
void free_ra_condition(ra_condition_t* condition);

/* Utility functions */
int is_star_projection(ra_attribute_list_t* attrs);
char* expression_to_string(expression_t* expr);
void optimize_ra_tree(ra_node_t** node);  /* Optional: basic optimizations */

/* Data structures for RA execution results */
typedef struct ra_column {
    char* name;                 /* Column name */
    char* table_name;          /* Table name (for qualified names) */
    struct ra_column* next;
} ra_column_t;

typedef struct ra_row {
    char** values;              /* Array of string values */
    int column_count;
    struct ra_row* next;
} ra_row_t;

typedef struct ra_result_set {
    ra_column_t* columns;       /* Column metadata */
    ra_row_t* rows;            /* Row data */
    int column_count;
    int row_count;
} ra_result_set_t;

/* RA execution engine functions */
ra_result_set_t* execute_ra_node(ra_node_t* node);
ra_result_set_t* execute_ra_relation(ra_node_t* node);
ra_result_set_t* execute_ra_selection(ra_node_t* node);
ra_result_set_t* execute_ra_projection(ra_node_t* node);
ra_result_set_t* execute_ra_join(ra_node_t* node);

/* Result set management functions */
ra_result_set_t* create_ra_result_set(void);
ra_column_t* create_ra_column(const char* name, const char* table_name);
ra_row_t* create_ra_row(int column_count);
void add_ra_column(ra_result_set_t* result_set, ra_column_t* column);
void add_ra_row(ra_result_set_t* result_set, ra_row_t* row);
void free_ra_result_set(ra_result_set_t* result_set);
void free_ra_column(ra_column_t* column);
void free_ra_row(ra_row_t* row);

/* RA expression evaluation */
int evaluate_ra_condition(ra_condition_t* condition, ra_row_t* row, ra_result_set_t* context);
char* get_column_value(ra_row_t* row, const char* column_name, const char* table_name, ra_result_set_t* context);
int find_column_index(const char* column_name, const char* table_name, ra_result_set_t* context);

/* Display functions for result sets */
void print_ra_result_set(ra_result_set_t* result_set);

#endif /* RELATIONAL_ALGEBRA_H */