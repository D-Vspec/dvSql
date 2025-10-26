#define _POSIX_C_SOURCE 200809L
#include "../headers/table_engine.h"
#include "../headers/tokens.h"
#include "../headers/relational_algebra.h"
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

/* Initialize table engine */
table_result_t table_engine_init(void) {
    return create_data_directories();
}

/* Execute CREATE TABLE statement */
table_result_t execute_create_table(ast_node_t* create_stmt) {
    if (!create_stmt || create_stmt->type != NODE_CREATE_TABLE_STMT) {
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    char* table_name = create_stmt->data.create_table_stmt.table_name;
    column_def_t* columns = create_stmt->data.create_table_stmt.columns;
    
    if (!table_name || !columns) {
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    /* Check if table already exists */
    if (table_exists(table_name)) {
        printf("Table '%s' already exists.\n", table_name);
        return TABLE_ERROR_TABLE_EXISTS;
    }
    
    /* Count columns */
    int column_count = 0;
    column_def_t* current = columns;
    while (current) {
        column_count++;
        current = current->next;
    }
    
    /* Create table metadata */
    table_metadata_t metadata;
    metadata.table_name = table_name;
    metadata.column_count = column_count;
    metadata.columns = columns;
    metadata.created_at = get_current_timestamp();
    
    /* Save metadata to disk */
    table_result_t result = save_table_metadata(&metadata);
    
    if (result == TABLE_SUCCESS) {
        /* Create empty table data file */
        char* table_file = get_table_filename(table_name);
        if (table_file) {
            FILE* fp = fopen(table_file, "w");
            if (fp) {
                /* Write header indicating empty table */
                fprintf(fp, "# Table: %s\n", table_name);
                fprintf(fp, "# Created: %s\n", metadata.created_at);
                fprintf(fp, "# Columns: %d\n", column_count);
                fprintf(fp, "# Data format: CSV\n");
                fprintf(fp, "# Column headers:\n");
                
                /* Write column headers */
                current = columns;
                while (current) {
                    fprintf(fp, "# %s (%s", current->column_name, 
                           data_type_to_json_string(current->data_type));
                    if (current->size > 0) {
                        fprintf(fp, "(%d)", current->size);
                    }
                    if (current->is_primary_key) fprintf(fp, " PRIMARY KEY");
                    if (current->is_not_null) fprintf(fp, " NOT NULL");
                    if (current->is_unique) fprintf(fp, " UNIQUE");
                    fprintf(fp, ")\n");
                    current = current->next;
                }
                fprintf(fp, "# --- DATA START ---\n");
                
                fclose(fp);
                printf("Table '%s' created successfully.\n", table_name);
            } else {
                printf("Error: Could not create table data file.\n");
                result = TABLE_ERROR_FILE_IO;
            }
            free(table_file);
        }
    }
    
    free(metadata.created_at);
    return result;
}

/* Execute DROP TABLE statement */
table_result_t execute_drop_table(ast_node_t* drop_stmt) {
    if (!drop_stmt || drop_stmt->type != NODE_DROP_TABLE_STMT) {
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    char* table_name = drop_stmt->data.drop_table_stmt.table_name;
    
    if (!table_exists(table_name)) {
        printf("Table '%s' does not exist.\n", table_name);
        return TABLE_ERROR_TABLE_NOT_FOUND;
    }
    
    /* Delete schema file */
    char* schema_file = get_schema_filename(table_name);
    if (schema_file) {
        if (unlink(schema_file) != 0) {
            printf("Warning: Could not delete schema file.\n");
        }
        free(schema_file);
    }
    
    /* Delete table data file */
    char* table_file = get_table_filename(table_name);
    if (table_file) {
        if (unlink(table_file) != 0) {
            printf("Warning: Could not delete table data file.\n");
        }
        free(table_file);
    }
    
    printf("Table '%s' dropped successfully.\n", table_name);
    return TABLE_SUCCESS;
}

/* Execute INSERT statement */
table_result_t execute_insert(ast_node_t* insert_stmt) {
    if (!insert_stmt || insert_stmt->type != NODE_INSERT_STMT) {
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    char* table_name = insert_stmt->data.insert_stmt.table_name;
    value_list_t* values = insert_stmt->data.insert_stmt.values;
    
    if (!table_name || !values) {
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    /* Check if table exists */
    if (!table_exists(table_name)) {
        printf("Table '%s' does not exist.\n", table_name);
        return TABLE_ERROR_TABLE_NOT_FOUND;
    }
    
    /* Load table metadata for validation */
    table_metadata_t* metadata = load_table_metadata(table_name);
    if (!metadata) {
        printf("Error: Could not load table metadata for '%s'.\n", table_name);
        return TABLE_ERROR_FILE_IO;
    }
    
    /* Count values */
    int value_count = 0;
    value_list_t* current = values;
    while (current) {
        value_count++;
        current = current->next;
    }
    
    /* Validate value count matches column count */
    if (value_count != metadata->column_count) {
        printf("Error: Expected %d values, got %d.\n", metadata->column_count, value_count);
        free_table_metadata(metadata);
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    /* Append row to table file */
    table_result_t result = append_row_to_table(table_name, values);
    
    if (result == TABLE_SUCCESS) {
        printf("1 row inserted into table '%s'.\n", table_name);
    }
    
    free_table_metadata(metadata);
    return result;
}

/* Execute SELECT statement */
table_result_t execute_select(ast_node_t* select_stmt) {
    /* Use the new relational algebra execution engine */
    return execute_select_with_ra(select_stmt);
}

/* Execute SELECT statement using relational algebra */
table_result_t execute_select_with_ra(ast_node_t* select_stmt) {
    if (!select_stmt || select_stmt->type != NODE_SELECT_STMT) {
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    /* Convert SQL to relational algebra */
    ra_node_t* ra_tree = sql_to_relational_algebra(select_stmt);
    if (!ra_tree) {
        printf("Error: Could not convert SQL to relational algebra.\n");
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    /* Execute the relational algebra tree */
    ra_result_set_t* result_set = execute_ra_node(ra_tree);
    
    if (result_set) {
        /* Display results */
        print_ra_result_set(result_set);
        
        /* Clean up */
        free_ra_result_set(result_set);
        free_ra_node(ra_tree);
        return TABLE_SUCCESS;
    } else {
        printf("Error: Failed to execute query.\n");
        free_ra_node(ra_tree);
        return TABLE_ERROR_FILE_IO;
    }
}

/* Check if table exists */
int table_exists(const char* table_name) {
    char* schema_file = get_schema_filename(table_name);
    if (!schema_file) return 0;
    
    int exists = (access(schema_file, F_OK) == 0);
    free(schema_file);
    return exists;
}

/* Save table metadata to disk as JSON */
table_result_t save_table_metadata(const table_metadata_t* metadata) {
    if (!metadata || !metadata->table_name) {
        return TABLE_ERROR_INVALID_SCHEMA;
    }
    
    char* filename = get_schema_filename(metadata->table_name);
    if (!filename) {
        return TABLE_ERROR_MEMORY;
    }
    
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        free(filename);
        return TABLE_ERROR_FILE_IO;
    }
    
    /* Write JSON metadata */
    fprintf(fp, "{\n");
    fprintf(fp, "  \"table_name\": \"%s\",\n", metadata->table_name);
    fprintf(fp, "  \"created_at\": \"%s\",\n", metadata->created_at);
    fprintf(fp, "  \"column_count\": %d,\n", metadata->column_count);
    fprintf(fp, "  \"columns\": [\n");
    
    column_def_t* current = metadata->columns;
    int col_index = 0;
    while (current) {
        fprintf(fp, "    {\n");
        fprintf(fp, "      \"name\": \"%s\",\n", current->column_name);
        fprintf(fp, "      \"type\": \"%s\",\n", data_type_to_json_string(current->data_type));
        
        if (current->size > 0) {
            fprintf(fp, "      \"size\": %d,\n", current->size);
        }
        if (current->precision > 0) {
            fprintf(fp, "      \"precision\": %d,\n", current->precision);
        }
        
        fprintf(fp, "      \"primary_key\": %s,\n", current->is_primary_key ? "true" : "false");
        fprintf(fp, "      \"not_null\": %s,\n", current->is_not_null ? "true" : "false");
        fprintf(fp, "      \"unique\": %s,\n", current->is_unique ? "true" : "false");
        fprintf(fp, "      \"auto_increment\": %s\n", current->has_auto_increment ? "true" : "false");
        
        fprintf(fp, "    }");
        if (current->next) {
            fprintf(fp, ",");
        }
        fprintf(fp, "\n");
        
        current = current->next;
        col_index++;
    }
    
    fprintf(fp, "  ]\n");
    fprintf(fp, "}\n");
    
    fclose(fp);
    free(filename);
    return TABLE_SUCCESS;
}

/* Create data directories if they don't exist */
table_result_t create_data_directories(void) {
    struct stat st;
    
    /* Create main data directory */
    if (stat(DATA_DIR, &st) == -1) {
        if (mkdir(DATA_DIR, 0755) == -1) {
            return TABLE_ERROR_FILE_IO;
        }
    }
    
    /* Create schemas directory */
    if (stat(SCHEMAS_DIR, &st) == -1) {
        if (mkdir(SCHEMAS_DIR, 0755) == -1) {
            return TABLE_ERROR_FILE_IO;
        }
    }
    
    /* Create tables directory */
    if (stat(TABLES_DIR, &st) == -1) {
        if (mkdir(TABLES_DIR, 0755) == -1) {
            return TABLE_ERROR_FILE_IO;
        }
    }
    
    return TABLE_SUCCESS;
}

/* Get schema filename for a table */
char* get_schema_filename(const char* table_name) {
    if (!table_name) return NULL;
    
    char* filename = malloc(MAX_FILENAME_LEN);
    if (!filename) return NULL;
    
    snprintf(filename, MAX_FILENAME_LEN, "%s/%s.json", SCHEMAS_DIR, table_name);
    return filename;
}

/* Get table data filename for a table */
char* get_table_filename(const char* table_name) {
    if (!table_name) return NULL;
    
    char* filename = malloc(MAX_FILENAME_LEN);
    if (!filename) return NULL;
    
    snprintf(filename, MAX_FILENAME_LEN, "%s/%s.csv", TABLES_DIR, table_name);
    return filename;
}

/* Convert data type to JSON string representation */
const char* data_type_to_json_string(data_type_t type) {
    switch (type) {
        case DATA_TYPE_INT: return "INTEGER";
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

/* Convert JSON string to data type */
data_type_t json_string_to_data_type(const char* type_str) {
    if (!type_str) return DATA_TYPE_INT;
    
    if (strcmp(type_str, "INTEGER") == 0) return DATA_TYPE_INT;
    if (strcmp(type_str, "VARCHAR") == 0) return DATA_TYPE_VARCHAR;
    if (strcmp(type_str, "CHAR") == 0) return DATA_TYPE_CHAR;
    if (strcmp(type_str, "TEXT") == 0) return DATA_TYPE_TEXT;
    if (strcmp(type_str, "DECIMAL") == 0) return DATA_TYPE_DECIMAL;
    if (strcmp(type_str, "FLOAT") == 0) return DATA_TYPE_FLOAT;
    if (strcmp(type_str, "DATE") == 0) return DATA_TYPE_DATE;
    if (strcmp(type_str, "TIME") == 0) return DATA_TYPE_TIME;
    if (strcmp(type_str, "TIMESTAMP") == 0) return DATA_TYPE_TIMESTAMP;
    if (strcmp(type_str, "BOOLEAN") == 0) return DATA_TYPE_BOOLEAN;
    
    return DATA_TYPE_INT;  /* default */
}

/* Get current timestamp as string */
char* get_current_timestamp(void) {
    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    
    char* timestamp = malloc(32);
    if (!timestamp) return NULL;
    
    strftime(timestamp, 32, "%Y-%m-%d %H:%M:%S", timeinfo);
    return timestamp;
}

/* Error handling functions */
const char* table_error_string(table_result_t result) {
    switch (result) {
        case TABLE_SUCCESS: return "Success";
        case TABLE_ERROR_FILE_IO: return "File I/O error";
        case TABLE_ERROR_INVALID_SCHEMA: return "Invalid table schema";
        case TABLE_ERROR_TABLE_EXISTS: return "Table already exists";
        case TABLE_ERROR_TABLE_NOT_FOUND: return "Table not found";
        case TABLE_ERROR_MEMORY: return "Memory allocation error";
        default: return "Unknown error";
    }
}

void print_table_error(table_result_t result, const char* context) {
    if (result != TABLE_SUCCESS) {
        printf("Error");
        if (context) {
            printf(" in %s", context);
        }
        printf(": %s\n", table_error_string(result));
    }
}

/* Load table metadata from disk (improved implementation) */
table_metadata_t* load_table_metadata(const char* table_name) {
    char* filename = get_schema_filename(table_name);
    if (!filename) return NULL;
    
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        free(filename);
        return NULL;
    }
    
    table_metadata_t* metadata = malloc(sizeof(table_metadata_t));
    if (!metadata) {
        fclose(fp);
        free(filename);
        return NULL;
    }
    
    /* Initialize metadata */
    metadata->table_name = strdup(table_name);
    metadata->created_at = NULL;
    metadata->column_count = 0;
    metadata->columns = NULL;
    
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "\"column_count\":")) {
            sscanf(line, " \"column_count\": %d,", &metadata->column_count);
            break;
        }
    }
    
    fclose(fp);
    free(filename);
    
    /* If we couldn't get column count, cleanup and return NULL */
    if (metadata->column_count == 0) {
        free_table_metadata(metadata);
        return NULL;
    }
    
    /* For now, create dummy column structure just for count validation */
    /* In a full implementation, we would parse the JSON to get column details */
    
    return metadata;
}

/* Free table metadata memory */
void free_table_metadata(table_metadata_t* metadata) {
    if (!metadata) return;
    
    free(metadata->table_name);
    free(metadata->created_at);
    /* Note: columns are owned by the AST, so we don't free them here */
    free(metadata);
}

/* Append row to table CSV file */
table_result_t append_row_to_table(const char* table_name, value_list_t* values) {
    char* filename = get_table_filename(table_name);
    if (!filename) {
        return TABLE_ERROR_MEMORY;
    }
    
    FILE* fp = fopen(filename, "a");
    if (!fp) {
        free(filename);
        return TABLE_ERROR_FILE_IO;
    }
    
    /* Write values as CSV */
    value_list_t* current = values;
    int first = 1;
    while (current) {
        if (!first) fprintf(fp, ",");
        
        char* value_str = expression_to_csv_string(current->value);
        if (value_str) {
            fprintf(fp, "%s", value_str);
            free(value_str);
        } else {
            fprintf(fp, "NULL");
        }
        
        first = 0;
        current = current->next;
    }
    fprintf(fp, "\n");
    
    fclose(fp);
    free(filename);
    return TABLE_SUCCESS;
}

/* Convert expression to CSV string representation */
char* expression_to_csv_string(expression_t* expr) {
    if (!expr) return NULL;
    
    char* result = malloc(256);  /* Max string length */
    if (!result) return NULL;
    
    switch (expr->type) {
        case EXPR_LITERAL:
            switch (expr->literal_type) {
                case INTEGER_LITERAL:
                    snprintf(result, 256, "%d", expr->data.literal.int_val);
                    break;
                case DECIMAL_LITERAL:
                    snprintf(result, 256, "%.2f", expr->data.literal.float_val);
                    break;
                case STRING_LITERAL:
                    if (expr->data.literal.string_val) {
                        snprintf(result, 256, "%s", expr->data.literal.string_val);
                    } else {
                        snprintf(result, 256, "NULL");
                    }
                    break;
                case NULL_TOK:
                    snprintf(result, 256, "NULL");
                    break;
                case TRUE_TOK:
                    snprintf(result, 256, "1");
                    break;
                case FALSE_TOK:
                    snprintf(result, 256, "0");
                    break;
                default:
                    /* Handle token values that don't match enum constants */
                    if (expr->literal_type == 260) {  /* INTEGER_LITERAL token value */
                        snprintf(result, 256, "%d", expr->data.literal.int_val);
                    } else if (expr->literal_type == 259) {  /* STRING_LITERAL token value */
                        if (expr->data.literal.string_val) {
                            snprintf(result, 256, "%s", expr->data.literal.string_val);
                        } else {
                            snprintf(result, 256, "NULL");
                        }
                    } else if (expr->literal_type == 261) {  /* DECIMAL_LITERAL token value */
                        snprintf(result, 256, "%.2f", expr->data.literal.float_val);
                    } else {
                        snprintf(result, 256, "NULL");
                    }
                    break;
            }
            break;
        case EXPR_IDENTIFIER:
            snprintf(result, 256, "%s", expr->data.identifier);
            break;
        default:
            snprintf(result, 256, "NULL");
            break;
    }
    
    return result;
}

/* Read table data from CSV file */
table_result_t read_table_data(const char* table_name, int* row_count, char*** rows) {
    char* filename = get_table_filename(table_name);
    if (!filename) {
        return TABLE_ERROR_MEMORY;
    }
    
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        free(filename);
        return TABLE_ERROR_FILE_IO;
    }
    
    char line[1024];
    char** data_rows = NULL;
    int count = 0;
    int capacity = 10;
    
    data_rows = malloc(capacity * sizeof(char*));
    if (!data_rows) {
        fclose(fp);
        free(filename);
        return TABLE_ERROR_MEMORY;
    }
    
    /* Skip header lines (lines starting with #) */
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] != '#') {
            /* Remove newline */
            char* newline = strchr(line, '\n');
            if (newline) *newline = '\0';
            
            /* Skip empty lines */
            if (strlen(line) == 0) continue;
            
            /* Expand array if needed */
            if (count >= capacity) {
                capacity *= 2;
                char** new_rows = realloc(data_rows, capacity * sizeof(char*));
                if (!new_rows) {
                    free_table_rows(data_rows, count);
                    fclose(fp);
                    free(filename);
                    return TABLE_ERROR_MEMORY;
                }
                data_rows = new_rows;
            }
            
            /* Store the row */
            data_rows[count] = strdup(line);
            if (!data_rows[count]) {
                free_table_rows(data_rows, count);
                fclose(fp);
                free(filename);
                return TABLE_ERROR_MEMORY;
            }
            count++;
        }
    }
    
    fclose(fp);
    free(filename);
    
    *row_count = count;
    *rows = data_rows;
    return TABLE_SUCCESS;
}

/* Free table rows memory */
void free_table_rows(char** rows, int row_count) {
    if (!rows) return;
    
    for (int i = 0; i < row_count; i++) {
        free(rows[i]);
    }
    free(rows);
}