#include "../headers/relational_algebra.h"
#include "../headers/tokens.h"

/* Constructor functions for RA nodes */
ra_node_t* create_ra_relation(const char* name, const char* alias) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_RELATION;
    node->data.relation.name = strdup(name);
    node->data.relation.alias = alias ? strdup(alias) : NULL;
    
    return node;
}

ra_node_t* create_ra_selection(ra_condition_t* condition, ra_node_t* input) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_SELECTION;
    node->data.selection.condition = condition;
    node->data.selection.input = input;
    
    return node;
}

ra_node_t* create_ra_projection(ra_attribute_list_t* attributes, ra_node_t* input) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_PROJECTION;
    node->data.projection.attributes = attributes;
    node->data.projection.input = input;
    
    return node;
}

ra_node_t* create_ra_cartesian(ra_node_t* left, ra_node_t* right) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_CARTESIAN;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->data.binary_op.condition = NULL;
    
    return node;
}

ra_node_t* create_ra_natural_join(ra_node_t* left, ra_node_t* right) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_NATURAL_JOIN;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->data.binary_op.condition = NULL;
    
    return node;
}

ra_node_t* create_ra_theta_join(ra_node_t* left, ra_node_t* right, ra_condition_t* condition) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_THETA_JOIN;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->data.binary_op.condition = condition;
    
    return node;
}

ra_node_t* create_ra_left_join(ra_node_t* left, ra_node_t* right, ra_condition_t* condition) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_LEFT_JOIN;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->data.binary_op.condition = condition;
    
    return node;
}

ra_node_t* create_ra_right_join(ra_node_t* left, ra_node_t* right, ra_condition_t* condition) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_RIGHT_JOIN;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->data.binary_op.condition = condition;
    
    return node;
}

ra_node_t* create_ra_union(ra_node_t* left, ra_node_t* right) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_UNION;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->data.binary_op.condition = NULL;
    
    return node;
}

ra_node_t* create_ra_intersection(ra_node_t* left, ra_node_t* right) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_INTERSECTION;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->data.binary_op.condition = NULL;
    
    return node;
}

ra_node_t* create_ra_difference(ra_node_t* left, ra_node_t* right) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_DIFFERENCE;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->data.binary_op.condition = NULL;
    
    return node;
}

ra_node_t* create_ra_rename(const char* new_name, ra_attribute_list_t* attr_mappings, ra_node_t* input) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_RENAME;
    node->data.rename.new_name = new_name ? strdup(new_name) : NULL;
    node->data.rename.attribute_mappings = attr_mappings;
    node->data.rename.input = input;
    
    return node;
}

ra_node_t* create_ra_aggregation(ra_attribute_list_t* group_by, ra_attribute_list_t* aggregates, ra_node_t* input) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_AGGREGATION;
    node->data.aggregation.group_by_attrs = group_by;
    node->data.aggregation.aggregate_attrs = aggregates;
    node->data.aggregation.input = input;
    
    return node;
}

ra_node_t* create_ra_sorting(ra_attribute_list_t* sort_attrs, ra_node_t* input) {
    ra_node_t* node = malloc(sizeof(ra_node_t));
    if (!node) return NULL;
    
    node->type = RA_SORTING;
    node->data.sorting.sort_attrs = sort_attrs;
    node->data.sorting.input = input;
    
    return node;
}

/* Helper functions for attributes and conditions */
ra_attribute_t* create_ra_attribute(const char* name, const char* alias, const char* table_name) {
    ra_attribute_t* attr = malloc(sizeof(ra_attribute_t));
    if (!attr) return NULL;
    
    attr->name = strdup(name);
    attr->alias = alias ? strdup(alias) : NULL;
    attr->table_name = table_name ? strdup(table_name) : NULL;
    attr->expression = NULL;
    attr->next = NULL;
    
    return attr;
}

ra_attribute_t* create_ra_attribute_from_expr(expression_t* expr, const char* alias) {
    ra_attribute_t* attr = malloc(sizeof(ra_attribute_t));
    if (!attr) return NULL;
    
    attr->name = NULL;
    attr->alias = alias ? strdup(alias) : NULL;
    attr->table_name = NULL;
    attr->expression = expr;  /* Note: we don't copy, just reference */
    attr->next = NULL;
    
    /* Extract name from expression if it's an identifier or column reference */
    if (expr->type == EXPR_IDENTIFIER) {
        attr->name = strdup(expr->data.identifier);
    } else if (expr->type == EXPR_COLUMN_REF) {
        attr->name = strdup(expr->data.column_ref.column_name);
        if (expr->data.column_ref.table_name) {
            attr->table_name = strdup(expr->data.column_ref.table_name);
        }
    }
    
    return attr;
}

ra_attribute_list_t* create_ra_attribute_list() {
    ra_attribute_list_t* list = malloc(sizeof(ra_attribute_list_t));
    if (!list) return NULL;
    
    list->attributes = NULL;
    list->count = 0;
    
    return list;
}

void add_ra_attribute(ra_attribute_list_t* list, ra_attribute_t* attr) {
    if (!list || !attr) return;
    
    if (!list->attributes) {
        list->attributes = attr;
    } else {
        ra_attribute_t* current = list->attributes;
        while (current->next) {
            current = current->next;
        }
        current->next = attr;
    }
    list->count++;
}

ra_condition_t* create_ra_condition(expression_t* expr, const char* description) {
    ra_condition_t* condition = malloc(sizeof(ra_condition_t));
    if (!condition) return NULL;
    
    condition->expression = expr;  /* Reference, not copy */
    condition->description = description ? strdup(description) : NULL;
    
    return condition;
}

/* SQL AST to Relational Algebra conversion functions */
ra_node_t* sql_to_relational_algebra(ast_node_t* sql_ast) {
    if (!sql_ast) return NULL;
    
    switch (sql_ast->type) {
        case NODE_SELECT_STMT:
            return convert_select_stmt(sql_ast);
        case NODE_INSERT_STMT:
            return convert_insert_stmt(sql_ast);
        case NODE_UPDATE_STMT:
            return convert_update_stmt(sql_ast);
        case NODE_DELETE_STMT:
            return convert_delete_stmt(sql_ast);
        default:
            return NULL;  /* Unsupported statement type for RA conversion */
    }
}

ra_node_t* convert_select_stmt(ast_node_t* select_stmt) {
    if (!select_stmt || select_stmt->type != NODE_SELECT_STMT) return NULL;
    
    ra_node_t* result = NULL;
    
    /* Step 1: Build FROM clause (tables and joins) */
    if (select_stmt->data.select_stmt.from_table) {
        result = build_from_clause(select_stmt->data.select_stmt.from_table, 
                                   select_stmt->data.select_stmt.joins);
    } else {
        return NULL;  /* SELECT without FROM not supported in basic RA */
    }
    
    /* Step 2: Add WHERE clause (selection) */
    if (select_stmt->data.select_stmt.where_clause) {
        ra_condition_t* condition = convert_expression_to_condition(select_stmt->data.select_stmt.where_clause);
        result = create_ra_selection(condition, result);
    }
    
    /* Step 3: Add SELECT clause (projection) */
    if (select_stmt->data.select_stmt.columns) {
        ra_attribute_list_t* attrs = convert_column_list_to_attributes(select_stmt->data.select_stmt.columns);
        if (attrs && !is_star_projection(attrs)) {
            result = create_ra_projection(attrs, result);
        } else if (attrs) {
            free_ra_attribute_list(attrs);  /* Free the * projection attributes */
        }
    }
    
    /* Step 4: Add GROUP BY (aggregation) */
    if (select_stmt->data.select_stmt.group_by) {
        ra_attribute_list_t* group_attrs = convert_column_list_to_attributes(select_stmt->data.select_stmt.group_by);
        ra_attribute_list_t* agg_attrs = create_ra_attribute_list();  /* TODO: Extract aggregates from SELECT */
        result = create_ra_aggregation(group_attrs, agg_attrs, result);
    }
    
    /* Step 5: Add ORDER BY (sorting) */
    if (select_stmt->data.select_stmt.order_by) {
        ra_attribute_list_t* sort_attrs = convert_column_list_to_attributes(select_stmt->data.select_stmt.order_by);
        result = create_ra_sorting(sort_attrs, result);
    }
    
    return result;
}

ra_node_t* convert_insert_stmt(ast_node_t* insert_stmt) {
    /* INSERT operations are not typically represented in pure relational algebra */
    /* This would require extending RA with update operations */
    return NULL;
}

ra_node_t* convert_update_stmt(ast_node_t* update_stmt) {
    /* UPDATE operations are not typically represented in pure relational algebra */
    /* This would require extending RA with update operations */
    return NULL;
}

ra_node_t* convert_delete_stmt(ast_node_t* delete_stmt) {
    /* DELETE can be represented as a difference operation in RA */
    if (!delete_stmt || delete_stmt->type != NODE_DELETE_STMT) return NULL;
    
    /* This is a simplified representation - would need more complex logic for full implementation */
    return NULL;
}

/* Helper conversion functions */
ra_attribute_list_t* convert_column_list_to_attributes(column_list_t* columns) {
    if (!columns) return NULL;
    
    ra_attribute_list_t* attr_list = create_ra_attribute_list();
    if (!attr_list) return NULL;
    
    column_list_t* current = columns;
    while (current) {
        ra_attribute_t* attr = convert_expression_to_attribute(current->column);
        if (attr) {
            add_ra_attribute(attr_list, attr);
        }
        current = current->next;
    }
    
    return attr_list;
}

ra_node_t* build_from_clause(table_ref_t* from_table, join_clause_t* joins) {
    if (!from_table) return NULL;
    
    /* Start with the first table */
    ra_node_t* result = create_ra_relation(from_table->table_name, from_table->alias);
    if (!result) return NULL;
    
    /* Process joins */
    join_clause_t* current_join = joins;
    while (current_join) {
        ra_node_t* right_table = create_ra_relation(current_join->table->table_name, 
                                                   current_join->table->alias);
        if (!right_table) {
            free_ra_node(result);
            return NULL;
        }
        
        ra_condition_t* join_condition = NULL;
        if (current_join->on_condition) {
            join_condition = convert_expression_to_condition(current_join->on_condition);
        }
        
        /* Create appropriate join type */
        switch (current_join->join_type) {
            case JOIN_INNER:
                if (join_condition) {
                    result = create_ra_theta_join(result, right_table, join_condition);
                } else {
                    result = create_ra_natural_join(result, right_table);
                }
                break;
            case JOIN_LEFT:
                result = create_ra_left_join(result, right_table, join_condition);
                break;
            case JOIN_RIGHT:
                result = create_ra_right_join(result, right_table, join_condition);
                break;
            default:
                result = create_ra_theta_join(result, right_table, join_condition);
                break;
        }
        
        current_join = current_join->next;
    }
    
    return result;
}

ra_condition_t* convert_expression_to_condition(expression_t* expr) {
    if (!expr) return NULL;
    
    char* desc = expression_to_string(expr);
    ra_condition_t* condition = create_ra_condition(expr, desc);
    free(desc);
    
    return condition;
}

ra_attribute_t* convert_expression_to_attribute(expression_t* expr) {
    if (!expr) return NULL;
    
    return create_ra_attribute_from_expr(expr, NULL);
}

/* Display functions */
const char* ra_operator_to_symbol(ra_operator_type_t type) {
    switch (type) {
        case RA_RELATION: return "R";
        case RA_SELECTION: return "σ";
        case RA_PROJECTION: return "π";
        case RA_CARTESIAN: return "×";
        case RA_NATURAL_JOIN: return "⋈";
        case RA_THETA_JOIN: return "⋈θ";
        case RA_LEFT_JOIN: return "⟕";
        case RA_RIGHT_JOIN: return "⟖";
        case RA_UNION: return "∪";
        case RA_INTERSECTION: return "∩";
        case RA_DIFFERENCE: return "-";
        case RA_RENAME: return "ρ";
        case RA_AGGREGATION: return "γ";
        case RA_SORTING: return "τ";
        default: return "?";
    }
}

const char* ra_operator_to_name(ra_operator_type_t type) {
    switch (type) {
        case RA_RELATION: return "RELATION";
        case RA_SELECTION: return "SELECTION";
        case RA_PROJECTION: return "PROJECTION";
        case RA_CARTESIAN: return "CARTESIAN_PRODUCT";
        case RA_NATURAL_JOIN: return "NATURAL_JOIN";
        case RA_THETA_JOIN: return "THETA_JOIN";
        case RA_LEFT_JOIN: return "LEFT_JOIN";
        case RA_RIGHT_JOIN: return "RIGHT_JOIN";
        case RA_UNION: return "UNION";
        case RA_INTERSECTION: return "INTERSECTION";
        case RA_DIFFERENCE: return "DIFFERENCE";
        case RA_RENAME: return "RENAME";
        case RA_AGGREGATION: return "AGGREGATION";
        case RA_SORTING: return "SORTING";
        default: return "UNKNOWN";
    }
}

static void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

static void print_ra_attributes(ra_attribute_list_t* attrs) {
    if (!attrs || !attrs->attributes) {
        printf("*");
        return;
    }
    
    ra_attribute_t* current = attrs->attributes;
    int first = 1;
    while (current) {
        if (!first) printf(", ");
        first = 0;
        
        if (current->table_name) {
            printf("%s.%s", current->table_name, current->name ? current->name : "?");
        } else if (current->name) {
            printf("%s", current->name);
        } else {
            printf("expr");
        }
        
        if (current->alias) {
            printf(" AS %s", current->alias);
        }
        
        current = current->next;
    }
}

static void print_ra_condition(ra_condition_t* condition) {
    if (!condition) return;
    
    if (condition->description) {
        printf("%s", condition->description);
    } else {
        printf("condition");
    }
}

void print_ra_tree(ra_node_t* node, int indent) {
    if (!node) return;
    
    print_indent(indent);
    printf("%s (%s)", ra_operator_to_symbol(node->type), ra_operator_to_name(node->type));
    
    switch (node->type) {
        case RA_RELATION:
            printf(" %s", node->data.relation.name);
            if (node->data.relation.alias) {
                printf(" AS %s", node->data.relation.alias);
            }
            printf("\n");
            break;
            
        case RA_SELECTION:
            printf(" [");
            print_ra_condition(node->data.selection.condition);
            printf("]\n");
            print_ra_tree(node->data.selection.input, indent + 1);
            break;
            
        case RA_PROJECTION:
            printf(" [");
            print_ra_attributes(node->data.projection.attributes);
            printf("]\n");
            print_ra_tree(node->data.projection.input, indent + 1);
            break;
            
        case RA_CARTESIAN:
        case RA_NATURAL_JOIN:
        case RA_UNION:
        case RA_INTERSECTION:
        case RA_DIFFERENCE:
            printf("\n");
            print_ra_tree(node->data.binary_op.left, indent + 1);
            print_ra_tree(node->data.binary_op.right, indent + 1);
            break;
            
        case RA_THETA_JOIN:
        case RA_LEFT_JOIN:
        case RA_RIGHT_JOIN:
            printf(" [");
            print_ra_condition(node->data.binary_op.condition);
            printf("]\n");
            print_ra_tree(node->data.binary_op.left, indent + 1);
            print_ra_tree(node->data.binary_op.right, indent + 1);
            break;
            
        case RA_RENAME:
            printf(" [%s", node->data.rename.new_name ? node->data.rename.new_name : "?");
            if (node->data.rename.attribute_mappings) {
                printf(": ");
                print_ra_attributes(node->data.rename.attribute_mappings);
            }
            printf("]\n");
            print_ra_tree(node->data.rename.input, indent + 1);
            break;
            
        case RA_AGGREGATION:
            printf(" [GROUP BY: ");
            print_ra_attributes(node->data.aggregation.group_by_attrs);
            printf(", AGG: ");
            print_ra_attributes(node->data.aggregation.aggregate_attrs);
            printf("]\n");
            print_ra_tree(node->data.aggregation.input, indent + 1);
            break;
            
        case RA_SORTING:
            printf(" [ORDER BY: ");
            print_ra_attributes(node->data.sorting.sort_attrs);
            printf("]\n");
            print_ra_tree(node->data.sorting.input, indent + 1);
            break;
            
        default:
            printf(" [UNKNOWN]\n");
            break;
    }
}

void print_ra_mathematical(ra_node_t* node) {
    if (!node) return;
    
    switch (node->type) {
        case RA_RELATION:
            printf("%s", node->data.relation.name);
            if (node->data.relation.alias) {
                printf("(%s)", node->data.relation.alias);
            }
            break;
            
        case RA_SELECTION:
            printf("%s_{", ra_operator_to_symbol(node->type));
            print_ra_condition(node->data.selection.condition);
            printf("}(");
            print_ra_mathematical(node->data.selection.input);
            printf(")");
            break;
            
        case RA_PROJECTION:
            printf("%s_{", ra_operator_to_symbol(node->type));
            print_ra_attributes(node->data.projection.attributes);
            printf("}(");
            print_ra_mathematical(node->data.projection.input);
            printf(")");
            break;
            
        case RA_CARTESIAN:
        case RA_NATURAL_JOIN:
        case RA_UNION:
        case RA_INTERSECTION:
        case RA_DIFFERENCE:
            printf("(");
            print_ra_mathematical(node->data.binary_op.left);
            printf(" %s ", ra_operator_to_symbol(node->type));
            print_ra_mathematical(node->data.binary_op.right);
            printf(")");
            break;
            
        case RA_THETA_JOIN:
        case RA_LEFT_JOIN:
        case RA_RIGHT_JOIN:
            printf("(");
            print_ra_mathematical(node->data.binary_op.left);
            printf(" %s_{", ra_operator_to_symbol(node->type));
            print_ra_condition(node->data.binary_op.condition);
            printf("} ");
            print_ra_mathematical(node->data.binary_op.right);
            printf(")");
            break;
            
        case RA_RENAME:
            printf("%s_{%s", ra_operator_to_symbol(node->type), 
                   node->data.rename.new_name ? node->data.rename.new_name : "?");
            if (node->data.rename.attribute_mappings) {
                printf("(");
                print_ra_attributes(node->data.rename.attribute_mappings);
                printf(")");
            }
            printf("}(");
            print_ra_mathematical(node->data.rename.input);
            printf(")");
            break;
            
        case RA_AGGREGATION:
            printf("%s_{", ra_operator_to_symbol(node->type));
            print_ra_attributes(node->data.aggregation.group_by_attrs);
            printf(";");
            print_ra_attributes(node->data.aggregation.aggregate_attrs);
            printf("}(");
            print_ra_mathematical(node->data.aggregation.input);
            printf(")");
            break;
            
        case RA_SORTING:
            printf("%s_{", ra_operator_to_symbol(node->type));
            print_ra_attributes(node->data.sorting.sort_attrs);
            printf("}(");
            print_ra_mathematical(node->data.sorting.input);
            printf(")");
            break;
            
        default:
            printf("UNKNOWN");
            break;
    }
}

void print_ra_linear(ra_node_t* node) {
    if (!node) return;
    
    /* Linear notation is just the mathematical notation on one line */
    print_ra_mathematical(node);
}

/* Memory management */
void free_ra_node(ra_node_t* node) {
    if (!node) return;
    
    switch (node->type) {
        case RA_RELATION:
            free(node->data.relation.name);
            free(node->data.relation.alias);
            break;
            
        case RA_SELECTION:
            free_ra_condition(node->data.selection.condition);
            free_ra_node(node->data.selection.input);
            break;
            
        case RA_PROJECTION:
            free_ra_attribute_list(node->data.projection.attributes);
            free_ra_node(node->data.projection.input);
            break;
            
        case RA_CARTESIAN:
        case RA_NATURAL_JOIN:
        case RA_THETA_JOIN:
        case RA_LEFT_JOIN:
        case RA_RIGHT_JOIN:
        case RA_UNION:
        case RA_INTERSECTION:
        case RA_DIFFERENCE:
            free_ra_node(node->data.binary_op.left);
            free_ra_node(node->data.binary_op.right);
            free_ra_condition(node->data.binary_op.condition);
            break;
            
        case RA_RENAME:
            free(node->data.rename.new_name);
            free_ra_attribute_list(node->data.rename.attribute_mappings);
            free_ra_node(node->data.rename.input);
            break;
            
        case RA_AGGREGATION:
            free_ra_attribute_list(node->data.aggregation.group_by_attrs);
            free_ra_attribute_list(node->data.aggregation.aggregate_attrs);
            free_ra_node(node->data.aggregation.input);
            break;
            
        case RA_SORTING:
            free_ra_attribute_list(node->data.sorting.sort_attrs);
            free_ra_node(node->data.sorting.input);
            break;
    }
    
    free(node);
}

void free_ra_attribute(ra_attribute_t* attr) {
    if (!attr) return;
    
    free(attr->name);
    free(attr->alias);
    free(attr->table_name);
    /* Note: we don't free expression as it's owned by the AST */
    free(attr);
}

void free_ra_attribute_list(ra_attribute_list_t* list) {
    if (!list) return;
    
    ra_attribute_t* current = list->attributes;
    while (current) {
        ra_attribute_t* next = current->next;
        free_ra_attribute(current);
        current = next;
    }
    
    free(list);
}

void free_ra_condition(ra_condition_t* condition) {
    if (!condition) return;
    
    free(condition->description);
    /* Note: we don't free expression as it's owned by the AST */
    free(condition);
}

/* Utility functions */
int is_star_projection(ra_attribute_list_t* attrs) {
    if (!attrs || !attrs->attributes) return 0;
    
    /* Check if the only attribute is "*" */
    if (attrs->count == 1 && attrs->attributes->name && 
        strcmp(attrs->attributes->name, "*") == 0) {
        return 1;
    }
    
    return 0;
}

/* Helper function to get operator symbol for relational algebra display */
static const char* get_operator_symbol(int token) {
    switch (token) {
        case EQUAL: return "=";
        case NOT_EQUAL: return "≠";
        case LESS_THAN: return "<";
        case GREATER_THAN: return ">";
        case LESS_EQUAL: return "≤";
        case GREATER_EQUAL: return "≥";
        case PLUS: return "+";
        case MINUS: return "-";
        case MULTIPLY: return "*";
        case DIVIDE: return "/";
        case MODULO: return "%";
        case AND: return "∧";
        case OR: return "∨";
        case NOT: return "¬";
        default: return get_token_name(token);
    }
}

char* expression_to_string(expression_t* expr) {
    if (!expr) return strdup("NULL");
    
    char* result = NULL;
    
    switch (expr->type) {
        case EXPR_IDENTIFIER:
            return strdup(expr->data.identifier);
            
        case EXPR_COLUMN_REF:
            if (expr->data.column_ref.table_name) {
                result = malloc(strlen(expr->data.column_ref.table_name) + 
                                    strlen(expr->data.column_ref.column_name) + 2);
                sprintf(result, "%s.%s", expr->data.column_ref.table_name, 
                       expr->data.column_ref.column_name);
                return result;
            } else {
                return strdup(expr->data.column_ref.column_name);
            }
            
        case EXPR_BINARY_OP: {
            char* left_str = expression_to_string(expr->data.binary_op.left);
            char* right_str = expression_to_string(expr->data.binary_op.right);
            const char* op_str = get_operator_symbol(expr->data.binary_op.operator);
            
            result = malloc(strlen(left_str) + strlen(right_str) + strlen(op_str) + 4);
            sprintf(result, "%s %s %s", left_str, op_str, right_str);
            
            free(left_str);
            free(right_str);
            return result;
        }
        
        case EXPR_LITERAL:
            if (expr->literal_type == STRING_LITERAL) {
                result = malloc(strlen(expr->data.literal.string_val) + 3);
                sprintf(result, "'%s'", expr->data.literal.string_val);
                return result;
            } else {
                return strdup("literal");
            }
            
        case EXPR_UNARY_OP: {
            char* operand_str = expression_to_string(expr->data.unary_op.operand);
            const char* op_str = get_operator_symbol(expr->data.unary_op.operator);
            
            result = malloc(strlen(operand_str) + strlen(op_str) + 3);
            sprintf(result, "%s %s", op_str, operand_str);
            
            free(operand_str);
            return result;
        }
        
        case EXPR_FUNCTION_CALL: {
            char* result = malloc(256); /* Fixed size buffer for simplicity */
            snprintf(result, 256, "%s(...)", expr->data.function_call.function_name);
            return result;
        }
            
        default:
            return strdup("expression");
    }
}

void optimize_ra_tree(ra_node_t** node) {
    /* Basic optimization placeholder - can be extended later */
    if (!node || !*node) return;
    
    /* Potential optimizations:
     * - Push selections down
     * - Combine adjacent projections
     * - Reorder joins based on selectivity
     * - Convert cartesian products + selections to joins
     */
}