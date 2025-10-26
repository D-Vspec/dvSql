#ifndef TABLE_ENGINE_H
#define TABLE_ENGINE_H

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Table engine return codes */
typedef enum {
    TABLE_SUCCESS = 0,
    TABLE_ERROR_FILE_IO = 1,
    TABLE_ERROR_INVALID_SCHEMA = 2,
    TABLE_ERROR_TABLE_EXISTS = 3,
    TABLE_ERROR_TABLE_NOT_FOUND = 4,
    TABLE_ERROR_MEMORY = 5
} table_result_t;

/* Table engine configuration */
#define DATA_DIR "data"
#define SCHEMAS_DIR "data/schemas"
#define TABLES_DIR "data/tables"
#define MAX_FILENAME_LEN 256

/* Table metadata structure for storage */
typedef struct {
    char* table_name;
    int column_count;
    column_def_t* columns;
    char* created_at;  /* timestamp string */
} table_metadata_t;

/* Function prototypes */

/* Initialize table engine - create directories if needed */
table_result_t table_engine_init(void);

/* Execute CREATE TABLE statement */
table_result_t execute_create_table(ast_node_t* create_stmt);

/* Execute DROP TABLE statement */
table_result_t execute_drop_table(ast_node_t* drop_stmt);

/* Execute INSERT statement */
table_result_t execute_insert(ast_node_t* insert_stmt);

/* Execute SELECT statement */
table_result_t execute_select(ast_node_t* select_stmt);

/* Execute SELECT statement using relational algebra */
table_result_t execute_select_with_ra(ast_node_t* select_stmt);

/* Execute DESC statement */
table_result_t execute_desc(ast_node_t* desc_stmt);

/* Execute SHOW TABLES statement */
table_result_t execute_show_tables(ast_node_t* show_tables_stmt);

/* Check if table exists */
int table_exists(const char* table_name);

/* Load table metadata from disk */
table_metadata_t* load_table_metadata(const char* table_name);

/* Save table metadata to disk */
table_result_t save_table_metadata(const table_metadata_t* metadata);

/* Free table metadata memory */
void free_table_metadata(table_metadata_t* metadata);

/* Utility functions */
table_result_t create_data_directories(void);
char* get_schema_filename(const char* table_name);
char* get_table_filename(const char* table_name);
const char* data_type_to_json_string(data_type_t type);
data_type_t json_string_to_data_type(const char* type_str);
char* get_current_timestamp(void);

/* Data validation and conversion */
table_result_t validate_insert_data(table_metadata_t* metadata, value_list_t* values);
char* expression_to_csv_string(expression_t* expr);
table_result_t append_row_to_table(const char* table_name, value_list_t* values);

/* SELECT helper functions */
table_result_t read_table_data(const char* table_name, int* row_count, char*** rows);
void free_table_rows(char** rows, int row_count);
int matches_where_clause(char** row_data, column_def_t* columns, expression_t* where_clause);
void print_table_results(char** column_names, int column_count, char*** rows, int row_count);

/* Error handling */
const char* table_error_string(table_result_t result);
void print_table_error(table_result_t result, const char* context);

#endif /* TABLE_ENGINE_H */