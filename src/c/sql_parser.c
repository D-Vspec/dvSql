#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../headers/tokens.h"
#include "../headers/ast.h"

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
    const char* input_file = NULL;
    
    /* Parse command line options */
    while ((opt = getopt(argc, argv, "hvqf:")) != -1) {
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
    printf("  -f file     Parse the specified file\n");
    printf("\nEXAMPLES:\n");
    printf("  %s query.sql           # Parse query.sql\n", program_name);
    printf("  %s -f query.sql        # Parse query.sql (explicit)\n", program_name);
    printf("  %s -v query.sql        # Parse with verbose output\n", program_name);
    printf("  echo 'SELECT * FROM users;' | %s  # Parse from stdin\n", program_name);
    printf("  %s -q query.sql        # Parse without printing AST\n", program_name);
    printf("\nSUPPORTED SQL STATEMENTS:\n");
    printf("  - SELECT (with WHERE, JOIN, ORDER BY, GROUP BY, HAVING)\n");
    printf("  - INSERT INTO ... VALUES\n");
    printf("  - UPDATE ... SET ... WHERE\n");
    printf("  - DELETE FROM ... WHERE\n");
    printf("  - CREATE TABLE\n");
    printf("  - DROP TABLE\n");
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