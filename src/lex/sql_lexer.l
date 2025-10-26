%{
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tokens.h"

extern int yylineno;
int yycolno = 1;

void update_column() {
    yycolno += yyleng;
}

void update_line() {
    yylineno++;
    yycolno = 1;
}

void print_token(int token, const char* text) {
    printf("Line %d, Col %d: %-15s '%s'\n", yylineno, yycolno - yyleng, 
           get_token_name(token), text);
}
%}

%option noyywrap
%option case-insensitive
%option yylineno

DIGIT           [0-9]
LETTER          [a-zA-Z]
UNDERSCORE      [_]
IDENTIFIER      {LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*
INTEGER         {DIGIT}+
DECIMAL         {DIGIT}+\.{DIGIT}+
STRING          '[^']*'|\"[^\"]*\"
WHITESPACE      [ \t]+
NEWLINE         \n|\r\n|\r
COMMENT_LINE    --[^\r\n]*
COMMENT_BLOCK   \/\*([^*]|\*[^/])*\*\/

%%

"SELECT"        { update_column(); print_token(SELECT, yytext); return SELECT; }
"FROM"          { update_column(); print_token(FROM, yytext); return FROM; }
"WHERE"         { update_column(); print_token(WHERE, yytext); return WHERE; }
"INSERT"        { update_column(); print_token(INSERT, yytext); return INSERT; }
"INTO"          { update_column(); print_token(INTO, yytext); return INTO; }
"VALUES"        { update_column(); print_token(VALUES, yytext); return VALUES; }
"UPDATE"        { update_column(); print_token(UPDATE, yytext); return UPDATE; }
"SET"           { update_column(); print_token(SET, yytext); return SET; }
"DELETE"        { update_column(); print_token(DELETE, yytext); return DELETE; }
"CREATE"        { update_column(); print_token(CREATE, yytext); return CREATE; }
"TABLE"         { update_column(); print_token(TABLE, yytext); return TABLE; }
"DROP"          { update_column(); print_token(DROP, yytext); return DROP; }
"ALTER"         { update_column(); print_token(ALTER, yytext); return ALTER; }
"AND"           { update_column(); print_token(AND, yytext); return AND; }
"OR"            { update_column(); print_token(OR, yytext); return OR; }
"NOT"           { update_column(); print_token(NOT, yytext); return NOT; }
"NULL"          { update_column(); print_token(NULL_TOK, yytext); return NULL_TOK; }
"TRUE"          { update_column(); print_token(TRUE_TOK, yytext); return TRUE_TOK; }
"FALSE"         { update_column(); print_token(FALSE_TOK, yytext); return FALSE_TOK; }
"AS"            { update_column(); print_token(AS, yytext); return AS; }
"ORDER"         { update_column(); print_token(ORDER, yytext); return ORDER; }
"BY"            { update_column(); print_token(BY, yytext); return BY; }
"GROUP"         { update_column(); print_token(GROUP, yytext); return GROUP; }
"HAVING"        { update_column(); print_token(HAVING, yytext); return HAVING; }
"LIMIT"         { update_column(); print_token(LIMIT, yytext); return LIMIT; }
"OFFSET"        { update_column(); print_token(OFFSET, yytext); return OFFSET; }
"JOIN"          { update_column(); print_token(JOIN, yytext); return JOIN; }
"INNER"         { update_column(); print_token(INNER, yytext); return INNER; }
"LEFT"          { update_column(); print_token(LEFT, yytext); return LEFT; }
"RIGHT"         { update_column(); print_token(RIGHT, yytext); return RIGHT; }
"OUTER"         { update_column(); print_token(OUTER, yytext); return OUTER; }
"ON"            { update_column(); print_token(ON, yytext); return ON; }
"USING"         { update_column(); print_token(USING, yytext); return USING; }
"DISTINCT"      { update_column(); print_token(DISTINCT, yytext); return DISTINCT; }
"ALL"           { update_column(); print_token(ALL, yytext); return ALL; }
"IN"            { update_column(); print_token(IN, yytext); return IN; }
"EXISTS"        { update_column(); print_token(EXISTS, yytext); return EXISTS; }
"BETWEEN"       { update_column(); print_token(BETWEEN, yytext); return BETWEEN; }
"LIKE"          { update_column(); print_token(LIKE, yytext); return LIKE; }
"IS"            { update_column(); print_token(IS, yytext); return IS; }
"UNION"         { update_column(); print_token(UNION, yytext); return UNION; }
"INTERSECT"     { update_column(); print_token(INTERSECT, yytext); return INTERSECT; }
"EXCEPT"        { update_column(); print_token(EXCEPT, yytext); return EXCEPT; }

"INT"           { update_column(); print_token(INT_TYPE, yytext); return INT_TYPE; }
"INTEGER"       { update_column(); print_token(INTEGER_TYPE, yytext); return INTEGER_TYPE; }
"VARCHAR"       { update_column(); print_token(VARCHAR_TYPE, yytext); return VARCHAR_TYPE; }
"CHAR"          { update_column(); print_token(CHAR_TYPE, yytext); return CHAR_TYPE; }
"TEXT"          { update_column(); print_token(TEXT_TYPE, yytext); return TEXT_TYPE; }
"DECIMAL"       { update_column(); print_token(DECIMAL_TYPE, yytext); return DECIMAL_TYPE; }
"NUMERIC"       { update_column(); print_token(NUMERIC_TYPE, yytext); return NUMERIC_TYPE; }
"FLOAT"         { update_column(); print_token(FLOAT_TYPE, yytext); return FLOAT_TYPE; }
"REAL"          { update_column(); print_token(REAL_TYPE, yytext); return REAL_TYPE; }
"DATE"          { update_column(); print_token(DATE_TYPE, yytext); return DATE_TYPE; }
"TIME"          { update_column(); print_token(TIME_TYPE, yytext); return TIME_TYPE; }
"TIMESTAMP"     { update_column(); print_token(TIMESTAMP_TYPE, yytext); return TIMESTAMP_TYPE; }
"BOOLEAN"       { update_column(); print_token(BOOLEAN_TYPE, yytext); return BOOLEAN_TYPE; }

"PRIMARY"       { update_column(); print_token(PRIMARY, yytext); return PRIMARY; }
"KEY"           { update_column(); print_token(KEY, yytext); return KEY; }
"FOREIGN"       { update_column(); print_token(FOREIGN, yytext); return FOREIGN; }
"REFERENCES"    { update_column(); print_token(REFERENCES, yytext); return REFERENCES; }
"UNIQUE"        { update_column(); print_token(UNIQUE, yytext); return UNIQUE; }
"CHECK"         { update_column(); print_token(CHECK, yytext); return CHECK; }
"DEFAULT"       { update_column(); print_token(DEFAULT, yytext); return DEFAULT; }
"AUTO_INCREMENT" { update_column(); print_token(AUTO_INCREMENT, yytext); return AUTO_INCREMENT; }

"="             { update_column(); print_token(EQUAL, yytext); return EQUAL; }
"<>"            { update_column(); print_token(NOT_EQUAL, yytext); return NOT_EQUAL; }
"!="            { update_column(); print_token(NOT_EQUAL, yytext); return NOT_EQUAL; }
"<"             { update_column(); print_token(LESS_THAN, yytext); return LESS_THAN; }
">"             { update_column(); print_token(GREATER_THAN, yytext); return GREATER_THAN; }
"<="            { update_column(); print_token(LESS_EQUAL, yytext); return LESS_EQUAL; }
">="            { update_column(); print_token(GREATER_EQUAL, yytext); return GREATER_EQUAL; }
"+"             { update_column(); print_token(PLUS, yytext); return PLUS; }
"-"             { update_column(); print_token(MINUS, yytext); return MINUS; }
"*"             { update_column(); print_token(MULTIPLY, yytext); return MULTIPLY; }
"/"             { update_column(); print_token(DIVIDE, yytext); return DIVIDE; }
"%"             { update_column(); print_token(MODULO, yytext); return MODULO; }

"("             { update_column(); print_token(LPAREN, yytext); return LPAREN; }
")"             { update_column(); print_token(RPAREN, yytext); return RPAREN; }
","             { update_column(); print_token(COMMA, yytext); return COMMA; }
";"             { update_column(); print_token(SEMICOLON, yytext); return SEMICOLON; }
"."             { update_column(); print_token(DOT, yytext); return DOT; }

"COUNT"         { update_column(); print_token(COUNT, yytext); return COUNT; }
"SUM"           { update_column(); print_token(SUM, yytext); return SUM; }
"AVG"           { update_column(); print_token(AVG, yytext); return AVG; }
"MIN"           { update_column(); print_token(MIN, yytext); return MIN; }
"MAX"           { update_column(); print_token(MAX, yytext); return MAX; }

{INTEGER}       { update_column(); print_token(INTEGER_LITERAL, yytext); return INTEGER_LITERAL; }
{DECIMAL}       { update_column(); print_token(DECIMAL_LITERAL, yytext); return DECIMAL_LITERAL; }
{STRING}        { update_column(); print_token(STRING_LITERAL, yytext); return STRING_LITERAL; }

{IDENTIFIER}    { update_column(); print_token(IDENTIFIER, yytext); return IDENTIFIER; }

{COMMENT_LINE}  { update_column(); }
{COMMENT_BLOCK} { 
                  char *p = yytext;
                  while (*p) {
                    if (*p == '\n') {
                      update_line();
                    } else {
                      yycolno++;
                    }
                    p++;
                  }
                }

{WHITESPACE}    { update_column(); }
{NEWLINE}       { update_line(); }

.               { 
                  update_column(); 
                  printf("Line %d, Col %d: UNKNOWN_TOKEN '%s'\n", 
                         yylineno, yycolno - yyleng, yytext); 
                  return UNKNOWN_TOKEN; 
                }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
        printf("Tokenizing file: %s\n", argv[1]);
        printf("----------------------------------------\n");
    } else {
        printf("Reading from standard input...\n");
        printf("----------------------------------------\n");
    }

    int token;
    while ((token = yylex()) != 0) {
        /* Token processing is done in the rules above */
    }

    if (argc > 1) {
        fclose(yyin);
    }

    printf("----------------------------------------\n");
    printf("Tokenization complete.\n");
    return 0;
}
