#ifndef TOKENS_H
#define TOKENS_H

/* Token type definitions */
typedef enum {
    /* SQL Keywords */
    SELECT = 256,
    FROM,
    WHERE,
    INSERT,
    INTO,
    VALUES,
    UPDATE,
    SET,
    DELETE,
    CREATE,
    TABLE,
    DROP,
    ALTER,
    AND,
    OR,
    NOT,
    NULL_TOK,
    TRUE_TOK,
    FALSE_TOK,
    AS,
    ORDER,
    BY,
    GROUP,
    HAVING,
    LIMIT,
    OFFSET,
    JOIN,
    INNER,
    LEFT,
    RIGHT,
    OUTER,
    ON,
    USING,
    DISTINCT,
    ALL,
    IN,
    EXISTS,
    BETWEEN,
    LIKE,
    IS,
    UNION,
    INTERSECT,
    EXCEPT,

    /* Data Types */
    INT_TYPE,
    INTEGER_TYPE,
    VARCHAR_TYPE,
    CHAR_TYPE,
    TEXT_TYPE,
    DECIMAL_TYPE,
    NUMERIC_TYPE,
    FLOAT_TYPE,
    REAL_TYPE,
    DATE_TYPE,
    TIME_TYPE,
    TIMESTAMP_TYPE,
    BOOLEAN_TYPE,

    /* Constraints */
    PRIMARY,
    KEY,
    FOREIGN,
    REFERENCES,
    UNIQUE,
    CHECK,
    DEFAULT,
    AUTO_INCREMENT,

    /* Operators */
    EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    LESS_EQUAL,
    GREATER_EQUAL,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,

    /* Punctuation */
    LPAREN,
    RPAREN,
    COMMA,
    SEMICOLON,
    DOT,

    /* Aggregate Functions */
    COUNT,
    SUM,
    AVG,
    MIN,
    MAX,

    /* Literals */
    INTEGER_LITERAL,
    DECIMAL_LITERAL,
    STRING_LITERAL,

    /* Identifiers */
    IDENTIFIER,

    /* Special tokens */
    UNKNOWN_TOKEN
} token_type_t;

/* Function to get token name for debugging */
const char* get_token_name(int token);

#endif /* TOKENS_H */