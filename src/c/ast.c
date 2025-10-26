#include "../headers/ast.h"
#include "../headers/tokens.h"

/* AST Node Creation Functions */
ast_node_t* create_select_stmt(column_list_t* columns, table_ref_t* from_table) {
    ast_node_t* node = malloc(sizeof(ast_node_t));
    if (!node) return NULL;
    
    node->type = NODE_SELECT_STMT;
    node->data.select_stmt.columns = columns;
    node->data.select_stmt.from_table = from_table;
    node->data.select_stmt.joins = NULL;
    node->data.select_stmt.where_clause = NULL;
    node->data.select_stmt.group_by = NULL;
    node->data.select_stmt.having_clause = NULL;
    node->data.select_stmt.order_by = NULL;
    node->data.select_stmt.limit_count = -1;
    node->data.select_stmt.offset_count = -1;
    node->data.select_stmt.distinct = 0;
    
    return node;
}

ast_node_t* create_insert_stmt(char* table_name, column_list_t* columns, value_list_t* values) {
    ast_node_t* node = malloc(sizeof(ast_node_t));
    if (!node) return NULL;
    
    node->type = NODE_INSERT_STMT;
    node->data.insert_stmt.table_name = strdup(table_name);
    node->data.insert_stmt.columns = columns;
    node->data.insert_stmt.values = values;
    
    return node;
}

ast_node_t* create_update_stmt(char* table_name, column_list_t* set_columns, value_list_t* set_values, expression_t* where_clause) {
    ast_node_t* node = malloc(sizeof(ast_node_t));
    if (!node) return NULL;
    
    node->type = NODE_UPDATE_STMT;
    node->data.update_stmt.table_name = strdup(table_name);
    node->data.update_stmt.set_columns = set_columns;
    node->data.update_stmt.set_values = set_values;
    node->data.update_stmt.where_clause = where_clause;
    
    return node;
}

ast_node_t* create_delete_stmt(char* table_name, expression_t* where_clause) {
    ast_node_t* node = malloc(sizeof(ast_node_t));
    if (!node) return NULL;
    
    node->type = NODE_DELETE_STMT;
    node->data.delete_stmt.table_name = strdup(table_name);
    node->data.delete_stmt.where_clause = where_clause;
    
    return node;
}

ast_node_t* create_create_table_stmt(char* table_name, column_def_t* columns) {
    ast_node_t* node = malloc(sizeof(ast_node_t));
    if (!node) return NULL;
    
    node->type = NODE_CREATE_TABLE_STMT;
    node->data.create_table_stmt.table_name = strdup(table_name);
    node->data.create_table_stmt.columns = columns;
    
    return node;
}

ast_node_t* create_drop_table_stmt(char* table_name) {
    ast_node_t* node = malloc(sizeof(ast_node_t));
    if (!node) return NULL;
    
    node->type = NODE_DROP_TABLE_STMT;
    node->data.drop_table_stmt.table_name = strdup(table_name);
    
    return node;
}

/* Expression Creation Functions */
expression_t* create_identifier_expr(char* identifier) {
    expression_t* expr = malloc(sizeof(expression_t));
    if (!expr) return NULL;
    
    expr->type = EXPR_IDENTIFIER;
    expr->data.identifier = strdup(identifier);
    
    return expr;
}

expression_t* create_literal_expr(literal_value_t value, int literal_type) {
    expression_t* expr = malloc(sizeof(expression_t));
    if (!expr) return NULL;
    
    expr->type = EXPR_LITERAL;
    expr->data.literal = value;
    
    return expr;
}

expression_t* create_binary_op_expr(expression_t* left, expression_t* right, int operator) {
    expression_t* expr = malloc(sizeof(expression_t));
    if (!expr) return NULL;
    
    expr->type = EXPR_BINARY_OP;
    expr->data.binary_op.left = left;
    expr->data.binary_op.right = right;
    expr->data.binary_op.operator = operator;
    
    return expr;
}

expression_t* create_unary_op_expr(expression_t* operand, int operator) {
    expression_t* expr = malloc(sizeof(expression_t));
    if (!expr) return NULL;
    
    expr->type = EXPR_UNARY_OP;
    expr->data.unary_op.operand = operand;
    expr->data.unary_op.operator = operator;
    
    return expr;
}

expression_t* create_function_call_expr(char* function_name, expression_t** args, int arg_count) {
    expression_t* expr = malloc(sizeof(expression_t));
    if (!expr) return NULL;
    
    expr->type = EXPR_FUNCTION_CALL;
    expr->data.function_call.function_name = strdup(function_name);
    expr->data.function_call.args = args;
    expr->data.function_call.arg_count = arg_count;
    
    return expr;
}

expression_t* create_column_ref_expr(char* table_name, char* column_name) {
    expression_t* expr = malloc(sizeof(expression_t));
    if (!expr) return NULL;
    
    expr->type = EXPR_COLUMN_REF;
    expr->data.column_ref.table_name = table_name ? strdup(table_name) : NULL;
    expr->data.column_ref.column_name = strdup(column_name);
    
    return expr;
}

/* List Creation Functions */
column_def_t* create_column_def(char* column_name, data_type_t data_type) {
    column_def_t* def = malloc(sizeof(column_def_t));
    if (!def) return NULL;
    
    def->column_name = strdup(column_name);
    def->data_type = data_type;
    def->size = 0;
    def->precision = 0;
    def->is_primary_key = 0;
    def->is_not_null = 0;
    def->is_unique = 0;
    def->has_auto_increment = 0;
    def->default_value = NULL;
    def->next = NULL;
    
    return def;
}

column_list_t* create_column_list(expression_t* column) {
    column_list_t* list = malloc(sizeof(column_list_t));
    if (!list) return NULL;
    
    list->column = column;
    list->next = NULL;
    
    return list;
}

value_list_t* create_value_list(expression_t* value) {
    value_list_t* list = malloc(sizeof(value_list_t));
    if (!list) return NULL;
    
    list->value = value;
    list->next = NULL;
    
    return list;
}

table_ref_t* create_table_ref(char* table_name, char* alias) {
    table_ref_t* ref = malloc(sizeof(table_ref_t));
    if (!ref) return NULL;
    
    ref->table_name = strdup(table_name);
    ref->alias = alias ? strdup(alias) : NULL;
    ref->next = NULL;
    
    return ref;
}

join_clause_t* create_join_clause(join_type_t join_type, table_ref_t* table, expression_t* on_condition) {
    join_clause_t* clause = malloc(sizeof(join_clause_t));
    if (!clause) return NULL;
    
    clause->join_type = join_type;
    clause->table = table;
    clause->on_condition = on_condition;
    clause->next = NULL;
    
    return clause;
}

/* List Manipulation Functions */
void add_column_to_list(column_list_t** list, expression_t* column) {
    if (!list || !column) return;
    
    column_list_t* new_item = create_column_list(column);
    if (!new_item) return;
    
    if (!*list) {
        *list = new_item;
    } else {
        column_list_t* current = *list;
        while (current->next) {
            current = current->next;
        }
        current->next = new_item;
    }
}

void add_value_to_list(value_list_t** list, expression_t* value) {
    if (!list || !value) return;
    
    value_list_t* new_item = create_value_list(value);
    if (!new_item) return;
    
    if (!*list) {
        *list = new_item;
    } else {
        value_list_t* current = *list;
        while (current->next) {
            current = current->next;
        }
        current->next = new_item;
    }
}

void add_table_to_ref(table_ref_t** ref, table_ref_t* table) {
    if (!ref || !table) return;
    
    if (!*ref) {
        *ref = table;
    } else {
        table_ref_t* current = *ref;
        while (current->next) {
            current = current->next;
        }
        current->next = table;
    }
}

void add_join_to_clause(join_clause_t** clause, join_clause_t* join) {
    if (!clause || !join) return;
    
    if (!*clause) {
        *clause = join;
    } else {
        join_clause_t* current = *clause;
        while (current->next) {
            current = current->next;
        }
        current->next = join;
    }
}

void add_column_to_def(column_def_t** def, column_def_t* column) {
    if (!def || !column) return;
    
    if (!*def) {
        *def = column;
    } else {
        column_def_t* current = *def;
        while (current->next) {
            current = current->next;
        }
        current->next = column;
    }
}

/* Pretty Printing Functions */
static void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

static void print_expression(expression_t* expr, int indent) {
    if (!expr) return;
    
    switch (expr->type) {
        case EXPR_IDENTIFIER:
            printf("%s", expr->data.identifier);
            break;
            
        case EXPR_LITERAL:
            printf("literal");
            break;
            
        case EXPR_BINARY_OP:
            printf("(");
            print_expression(expr->data.binary_op.left, 0);
            printf(" %s ", get_token_name(expr->data.binary_op.operator));
            print_expression(expr->data.binary_op.right, 0);
            printf(")");
            break;
            
        case EXPR_UNARY_OP:
            printf("(%s ", get_token_name(expr->data.unary_op.operator));
            print_expression(expr->data.unary_op.operand, 0);
            printf(")");
            break;
            
        case EXPR_FUNCTION_CALL:
            printf("%s(", expr->data.function_call.function_name);
            for (int i = 0; i < expr->data.function_call.arg_count; i++) {
                if (i > 0) printf(", ");
                print_expression(expr->data.function_call.args[i], 0);
            }
            printf(")");
            break;
            
        case EXPR_COLUMN_REF:
            if (expr->data.column_ref.table_name) {
                printf("%s.%s", expr->data.column_ref.table_name, expr->data.column_ref.column_name);
            } else {
                printf("%s", expr->data.column_ref.column_name);
            }
            break;
    }
}

static void print_column_list(column_list_t* list, int indent) {
    column_list_t* current = list;
    while (current) {
        print_expression(current->column, indent);
        if (current->next) printf(", ");
        current = current->next;
    }
}

static void print_value_list(value_list_t* list, int indent) {
    value_list_t* current = list;
    while (current) {
        print_expression(current->value, indent);
        if (current->next) printf(", ");
        current = current->next;
    }
}

static void print_table_ref(table_ref_t* ref, int indent) {
    if (!ref) return;
    
    printf("%s", ref->table_name);
    if (ref->alias) {
        printf(" AS %s", ref->alias);
    }
}

static const char* data_type_to_string(data_type_t type) {
    switch (type) {
        case DATA_TYPE_INT: return "INT";
        case DATA_TYPE_VARCHAR: return "VARCHAR";
        case DATA_TYPE_CHAR: return "CHAR";
        case DATA_TYPE_TEXT: return "TEXT";
        case DATA_TYPE_DECIMAL: return "DECIMAL";
        case DATA_TYPE_FLOAT: return "FLOAT";
        case DATA_TYPE_DATE: return "DATE";
        case DATA_TYPE_TIME: return "TIME";
        case DATA_TYPE_TIMESTAMP: return "TIMESTAMP";
        case DATA_TYPE_BOOLEAN: return "BOOLEAN";
        default: return "UNKNOWN";
    }
}

static void print_column_def(column_def_t* def, int indent) {
    column_def_t* current = def;
    while (current) {
        print_indent(indent);
        printf("%s %s", current->column_name, data_type_to_string(current->data_type));
        
        if (current->size > 0) {
            printf("(%d)", current->size);
        }
        
        if (current->is_primary_key) printf(" PRIMARY KEY");
        if (current->is_not_null) printf(" NOT NULL");
        if (current->is_unique) printf(" UNIQUE");
        if (current->has_auto_increment) printf(" AUTO_INCREMENT");
        
        if (current->next) printf(",");
        printf("\n");
        current = current->next;
    }
}

void print_ast(ast_node_t* node, int indent) {
    if (!node) return;
    
    print_indent(indent);
    
    switch (node->type) {
        case NODE_SELECT_STMT:
            printf("SELECT");
            if (node->data.select_stmt.distinct) printf(" DISTINCT");
            printf(" ");
            print_column_list(node->data.select_stmt.columns, 0);
            printf("\n");
            
            if (node->data.select_stmt.from_table) {
                print_indent(indent);
                printf("FROM ");
                print_table_ref(node->data.select_stmt.from_table, 0);
                printf("\n");
            }
            
            if (node->data.select_stmt.where_clause) {
                print_indent(indent);
                printf("WHERE ");
                print_expression(node->data.select_stmt.where_clause, 0);
                printf("\n");
            }
            break;
            
        case NODE_INSERT_STMT:
            printf("INSERT INTO %s", node->data.insert_stmt.table_name);
            if (node->data.insert_stmt.columns) {
                printf(" (");
                print_column_list(node->data.insert_stmt.columns, 0);
                printf(")");
            }
            printf("\n");
            print_indent(indent);
            printf("VALUES (");
            print_value_list(node->data.insert_stmt.values, 0);
            printf(")\n");
            break;
            
        case NODE_UPDATE_STMT:
            printf("UPDATE %s\n", node->data.update_stmt.table_name);
            print_indent(indent);
            printf("SET ");
            print_column_list(node->data.update_stmt.set_columns, 0);
            printf("\n");
            
            if (node->data.update_stmt.where_clause) {
                print_indent(indent);
                printf("WHERE ");
                print_expression(node->data.update_stmt.where_clause, 0);
                printf("\n");
            }
            break;
            
        case NODE_DELETE_STMT:
            printf("DELETE FROM %s\n", node->data.delete_stmt.table_name);
            
            if (node->data.delete_stmt.where_clause) {
                print_indent(indent);
                printf("WHERE ");
                print_expression(node->data.delete_stmt.where_clause, 0);
                printf("\n");
            }
            break;
            
        case NODE_CREATE_TABLE_STMT:
            printf("CREATE TABLE %s (\n", node->data.create_table_stmt.table_name);
            print_column_def(node->data.create_table_stmt.columns, indent + 1);
            print_indent(indent);
            printf(")\n");
            break;
            
        case NODE_DROP_TABLE_STMT:
            printf("DROP TABLE %s\n", node->data.drop_table_stmt.table_name);
            break;
            
        default:
            printf("Unknown AST node type\n");
            break;
    }
}

/* Memory Management Functions */
void free_expression(expression_t* expr) {
    if (!expr) return;
    
    switch (expr->type) {
        case EXPR_IDENTIFIER:
            free(expr->data.identifier);
            break;
            
        case EXPR_LITERAL:
            if (expr->data.literal.string_val) {
                free(expr->data.literal.string_val);
            }
            break;
            
        case EXPR_BINARY_OP:
            free_expression(expr->data.binary_op.left);
            free_expression(expr->data.binary_op.right);
            break;
            
        case EXPR_UNARY_OP:
            free_expression(expr->data.unary_op.operand);
            break;
            
        case EXPR_FUNCTION_CALL:
            free(expr->data.function_call.function_name);
            for (int i = 0; i < expr->data.function_call.arg_count; i++) {
                free_expression(expr->data.function_call.args[i]);
            }
            free(expr->data.function_call.args);
            break;
            
        case EXPR_COLUMN_REF:
            free(expr->data.column_ref.table_name);
            free(expr->data.column_ref.column_name);
            break;
    }
    
    free(expr);
}

void free_column_def(column_def_t* def) {
    while (def) {
        column_def_t* next = def->next;
        free(def->column_name);
        free_expression(def->default_value);
        free(def);
        def = next;
    }
}

void free_column_list(column_list_t* list) {
    while (list) {
        column_list_t* next = list->next;
        free_expression(list->column);
        free(list);
        list = next;
    }
}

void free_value_list(value_list_t* list) {
    while (list) {
        value_list_t* next = list->next;
        free_expression(list->value);
        free(list);
        list = next;
    }
}

void free_table_ref(table_ref_t* ref) {
    while (ref) {
        table_ref_t* next = ref->next;
        free(ref->table_name);
        free(ref->alias);
        free(ref);
        ref = next;
    }
}

void free_join_clause(join_clause_t* clause) {
    while (clause) {
        join_clause_t* next = clause->next;
        free_table_ref(clause->table);
        free_expression(clause->on_condition);
        free(clause);
        clause = next;
    }
}

void free_ast(ast_node_t* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_SELECT_STMT:
            free_column_list(node->data.select_stmt.columns);
            free_table_ref(node->data.select_stmt.from_table);
            free_join_clause(node->data.select_stmt.joins);
            free_expression(node->data.select_stmt.where_clause);
            free_column_list(node->data.select_stmt.group_by);
            free_expression(node->data.select_stmt.having_clause);
            free_column_list(node->data.select_stmt.order_by);
            break;
            
        case NODE_INSERT_STMT:
            free(node->data.insert_stmt.table_name);
            free_column_list(node->data.insert_stmt.columns);
            free_value_list(node->data.insert_stmt.values);
            break;
            
        case NODE_UPDATE_STMT:
            free(node->data.update_stmt.table_name);
            free_column_list(node->data.update_stmt.set_columns);
            free_value_list(node->data.update_stmt.set_values);
            free_expression(node->data.update_stmt.where_clause);
            break;
            
        case NODE_DELETE_STMT:
            free(node->data.delete_stmt.table_name);
            free_expression(node->data.delete_stmt.where_clause);
            break;
            
        case NODE_CREATE_TABLE_STMT:
            free(node->data.create_table_stmt.table_name);
            free_column_def(node->data.create_table_stmt.columns);
            break;
            
        case NODE_DROP_TABLE_STMT:
            free(node->data.drop_table_stmt.table_name);
            break;
            
        default:
            break;
    }
    
    free(node);
}