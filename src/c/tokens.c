#include <stdio.h>
#include <string.h>
#include "../headers/tokens.h"

/* Function to get token name for debugging */
const char* get_token_name(int token) {
    switch (token) {
        /* SQL Keywords */
        case SELECT: return "SELECT";
        case FROM: return "FROM";
        case WHERE: return "WHERE";
        case INSERT: return "INSERT";
        case INTO: return "INTO";
        case VALUES: return "VALUES";
        case UPDATE: return "UPDATE";
        case SET: return "SET";
        case DELETE: return "DELETE";
        case CREATE: return "CREATE";
        case TABLE: return "TABLE";
        case DROP: return "DROP";
        case ALTER: return "ALTER";
        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";
        case NULL_TOK: return "NULL";
        case TRUE_TOK: return "TRUE";
        case FALSE_TOK: return "FALSE";
        case AS: return "AS";
        case ORDER: return "ORDER";
        case BY: return "BY";
        case GROUP: return "GROUP";
        case HAVING: return "HAVING";
        case LIMIT: return "LIMIT";
        case OFFSET: return "OFFSET";
        case JOIN: return "JOIN";
        case INNER: return "INNER";
        case LEFT: return "LEFT";
        case RIGHT: return "RIGHT";
        case OUTER: return "OUTER";
        case ON: return "ON";
        case USING: return "USING";
        case DISTINCT: return "DISTINCT";
        case ALL: return "ALL";
        case IN: return "IN";
        case EXISTS: return "EXISTS";
        case BETWEEN: return "BETWEEN";
        case LIKE: return "LIKE";
        case IS: return "IS";
        case UNION: return "UNION";
        case INTERSECT: return "INTERSECT";
        case EXCEPT: return "EXCEPT";

        /* Data Types */
        case INT_TYPE: return "INT_TYPE";
        case INTEGER_TYPE: return "INTEGER_TYPE";
        case VARCHAR_TYPE: return "VARCHAR_TYPE";
        case CHAR_TYPE: return "CHAR_TYPE";
        case TEXT_TYPE: return "TEXT_TYPE";
        case DECIMAL_TYPE: return "DECIMAL_TYPE";
        case NUMERIC_TYPE: return "NUMERIC_TYPE";
        case FLOAT_TYPE: return "FLOAT_TYPE";
        case REAL_TYPE: return "REAL_TYPE";
        case DATE_TYPE: return "DATE_TYPE";
        case TIME_TYPE: return "TIME_TYPE";
        case TIMESTAMP_TYPE: return "TIMESTAMP_TYPE";
        case BOOLEAN_TYPE: return "BOOLEAN_TYPE";

        /* Constraints */
        case PRIMARY: return "PRIMARY";
        case KEY: return "KEY";
        case FOREIGN: return "FOREIGN";
        case REFERENCES: return "REFERENCES";
        case UNIQUE: return "UNIQUE";
        case CHECK: return "CHECK";
        case DEFAULT: return "DEFAULT";
        case AUTO_INCREMENT: return "AUTO_INCREMENT";

        /* Operators */
        case EQUAL: return "EQUAL";
        case NOT_EQUAL: return "NOT_EQUAL";
        case LESS_THAN: return "LESS_THAN";
        case GREATER_THAN: return "GREATER_THAN";
        case LESS_EQUAL: return "LESS_EQUAL";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MULTIPLY: return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case MODULO: return "MODULO";

        /* Punctuation */
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case COMMA: return "COMMA";
        case SEMICOLON: return "SEMICOLON";
        case DOT: return "DOT";

        /* Aggregate Functions */
        case COUNT: return "COUNT";
        case SUM: return "SUM";
        case AVG: return "AVG";
        case MIN: return "MIN";
        case MAX: return "MAX";

        /* Literals */
        case INTEGER_LITERAL: return "INTEGER_LITERAL";
        case DECIMAL_LITERAL: return "DECIMAL_LITERAL";
        case STRING_LITERAL: return "STRING_LITERAL";

        /* Identifiers */
        case IDENTIFIER: return "IDENTIFIER";

        /* Special tokens */
        case UNKNOWN_TOKEN: return "UNKNOWN_TOKEN";

        default: return "UNKNOWN";
    }
}