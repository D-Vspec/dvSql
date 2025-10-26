#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../headers/tokens.h"
#include "../headers/ast.h"
#include "../headers/table_engine.h"
#include "../headers/relational_algebra.h"

/* External variables from lexer and parser */
extern FILE* yyin;
extern int yyparse();
extern ast_node_t* ast_root;
extern int yylineno;

/* Function prototypes */
void print_usage(const char* program_name);
int parse_file(const char* filename);
int parse_stdin();

int main(int argc, char** argv) {
    int opt;
    int verbose = 0;
    int show_ast = 1;
    int show_ra = 0;        /* Show relational algebra */
    int ra_only = 0;        /* Show only relational algebra */
    int execute_stmt = 1;   /* Execute statements by default */
    const char* input_file = NULL;
    
    /* Initialize table engine */
    table_result_t init_result = table_engine_init();
    if (init_result != TABLE_SUCCESS) {
        fprintf(stderr, "Failed to initialize table engine: %s\n", table_error_string(init_result));
        return 1;
    }
    
    /* Parse command line options */
    while ((opt = getopt(argc, argv, "hvqnraf:")) != -1) {
        switch (opt) {
            case 'h':
                print_usage(argv[0]);
                return 0;
            case 'v':
                verbose = 1;
                break;
            case 'q':
                show_ast = 0;
                break;
            case 'n':
                execute_stmt = 0;  /* Parse only, don't execute */
                break;
            case 'r':
                show_ra = 1;       /* Show relational algebra */
                break;
            case 'a':
                ra_only = 1;       /* Show only relational algebra */
                show_ast = 0;
                show_ra = 1;
                execute_stmt = 0;
                break;
            case 'f':
                input_file = optarg;
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }
    
    /* If no file specified and no additional arguments, check for file argument */
    if (!input_file && optind < argc) {
        input_file = argv[optind];
    }
    
    if (verbose) {
        printf("dvSQL Parser v1.0\n");
        printf("================\n");
        if (input_file) {
            printf("Parsing file: %s\n", input_file);
        } else {
            printf("Parsing from standard input\n");
        }
        printf("\n");
    }
    
    int result;
    if (input_file) {
        result = parse_file(input_file);
    } else {
        result = parse_stdin();
    }
    
    if (result == 0 && ast_root) {
        if (show_ast) {
            printf("\nParsed AST:\n");
            printf("===========\n");
            print_ast(ast_root, 0);
            printf("\n");
        }
        
        /* Convert to relational algebra if requested */
        if (show_ra) {
            ra_node_t* ra_tree = sql_to_relational_algebra(ast_root);
            if (ra_tree) {
                printf("\nRelational Algebra:\n");
                printf("==================\n");
                
                printf("Tree Format:\n");
                print_ra_tree(ra_tree, 0);
                printf("\n");
                
                printf("Mathematical Notation:\n");
                print_ra_mathematical(ra_tree);
                printf("\n\n");
                
                printf("Linear Notation:\n");
                print_ra_linear(ra_tree);
                printf("\n\n");
                
                /* Clean up RA tree */
                free_ra_node(ra_tree);
            } else {
                printf("\nCould not convert to relational algebra (unsupported statement type)\n\n");
            }
        }
        
        /* Execute statement if requested */
        if (execute_stmt) {
            table_result_t exec_result = TABLE_SUCCESS;
            
            switch (ast_root->type) {
                case NODE_CREATE_TABLE_STMT:
                    if (verbose) printf("Executing CREATE TABLE...\n");
                    exec_result = execute_create_table(ast_root);
                    break;
                    
                case NODE_DROP_TABLE_STMT:
                    if (verbose) printf("Executing DROP TABLE...\n");
                    exec_result = execute_drop_table(ast_root);
                    break;
                    
                case NODE_INSERT_STMT:
                    if (verbose) printf("Executing INSERT...\n");
                    exec_result = execute_insert(ast_root);
                    break;
                    
                case NODE_SELECT_STMT:
                    if (verbose) printf("Executing SELECT...\n");
                    exec_result = execute_select(ast_root);
                    break;
                    
                case NODE_DESC_STMT:
                    if (verbose) printf("Executing DESC...\n");
                    exec_result = execute_desc(ast_root);
                    break;
                    
                case NODE_SHOW_TABLES_STMT:
                    if (verbose) printf("Executing SHOW TABLES...\n");
                    exec_result = execute_show_tables(ast_root);
                    break;
                    
                case NODE_UPDATE_STMT:
                case NODE_DELETE_STMT:
                    if (verbose) printf("Statement parsed successfully (execution not yet implemented).\n");
                    break;
                    
                default:
                    if (verbose) printf("Unknown statement type.\n");
                    break;
            }
            
            if (exec_result != TABLE_SUCCESS) {
                print_table_error(exec_result, "statement execution");
            }
        }
        
        if (verbose) {
            printf("Parse completed successfully.\n");
        }
        
        /* Clean up memory */
        free_ast(ast_root);
        ast_root = NULL;
    } else if (result != 0) {
        fprintf(stderr, "Parse failed with errors.\n");
        return 1;
    } else {
        fprintf(stderr, "No valid SQL statement found.\n");
        return 1;
    }
    
    return 0;
}

void print_usage(const char* program_name) {
    printf("Usage: %s [OPTIONS] [file]\n", program_name);
    printf("\nOPTIONS:\n");
    printf("  -h          Show this help message\n");
    printf("  -v          Verbose output\n");
    printf("  -q          Quiet mode (don't print AST)\n");
    printf("  -n          Parse only (don't execute statements)\n");
    printf("  -r          Show relational algebra conversion\n");
    printf("  -a          Show only relational algebra (implies -q -n -r)\n");
    printf("  -f file     Parse the specified file\n");
    printf("\nEXAMPLES:\n");
    printf("  %s query.sql           # Parse and execute query.sql\n", program_name);
    printf("  %s -f query.sql        # Parse and execute query.sql (explicit)\n", program_name);
    printf("  %s -v query.sql        # Parse and execute with verbose output\n", program_name);
    printf("  echo 'SELECT * FROM users;' | %s  # Parse from stdin\n", program_name);
    printf("  %s -q query.sql        # Parse and execute without printing AST\n", program_name);
    printf("  %s -n query.sql        # Parse only without executing\n", program_name);
    printf("  %s -r query.sql        # Show relational algebra conversion\n", program_name);
    printf("  %s -a query.sql        # Show only relational algebra\n", program_name);
    printf("\nSUPPORTED SQL STATEMENTS:\n");
    printf("  - SELECT (with WHERE, JOIN, ORDER BY, GROUP BY, HAVING) [fully functional]\n");
    printf("  - INSERT INTO ... VALUES [fully functional]\n");
    printf("  - UPDATE ... SET ... WHERE [parse only]\n");
    printf("  - DELETE FROM ... WHERE [parse only]\n");
    printf("  - CREATE TABLE [fully functional]\n");
    printf("  - DROP TABLE [fully functional]\n");
    printf("\nRELATIONAL ALGEBRA CONVERSION:\n");
    printf("  Supports conversion of SELECT statements to relational algebra notation\n");
    printf("  including σ (selection), π (projection), ⋈ (join), × (cartesian product)\n");
    printf("\nDATA STORAGE:\n");
    printf("  - Table schemas: data/schemas/\n");
    printf("  - Table data: data/tables/\n");
}

int parse_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        return 1;
    }
    
    yyin = file;
    yylineno = 1;  /* Reset line number */
    
    int result = yyparse();
    
    fclose(file);
    return result;
}

int parse_stdin() {
    printf("Enter SQL statement (end with semicolon and Ctrl+D):\n");
    printf("> ");
    fflush(stdout);
    
    yyin = stdin;
    yylineno = 1;  /* Reset line number */
    
    int result = yyparse();
    
    return result;
}