#ifndef TOKENS_H
#define TOKENS_H

/* Token type definitions - must match the Bison-generated values */
typedef enum {
    /* Identifiers and Literals */
    IDENTIFIER = 258,
    STRING_LITERAL = 259,
    INTEGER_LITERAL = 260,
    DECIMAL_LITERAL = 261,
    
    /* SQL Keywords */
    SELECT = 262,
    FROM = 263,
    WHERE = 264,
    INSERT = 265,
    INTO = 266,
    VALUES = 267,
    UPDATE = 268,
    SET = 269,
    DELETE = 270,
    CREATE = 271,
    TABLE = 272,
    DROP = 273,
    ALTER = 274,
    AND = 275,
    OR = 276,
    NOT = 277,
    NULL_TOK = 278,
    TRUE_TOK = 279,
    FALSE_TOK = 280,
    AS = 281,
    ORDER = 282,
    BY = 283,
    GROUP = 284,
    HAVING = 285,
    LIMIT = 286,
    OFFSET = 287,
    JOIN = 288,
    INNER = 289,
    LEFT = 290,
    RIGHT = 291,
    OUTER = 292,
    ON = 293,
    USING = 294,
    DISTINCT = 295,
    ALL = 296,
    IN = 297,
    EXISTS = 298,
    BETWEEN = 299,
    LIKE = 300,
    IS = 301,
    UNION = 302,
    INTERSECT = 303,
    EXCEPT = 304,
    DESC = 305,
    SHOW = 306,
    TABLES = 307,

    /* Data Types */
    INT_TYPE = 308,
    INTEGER_TYPE = 309,
    VARCHAR_TYPE = 310,
    CHAR_TYPE = 311,
    TEXT_TYPE = 312,
    DECIMAL_TYPE = 313,
    NUMERIC_TYPE = 314,
    FLOAT_TYPE = 315,
    REAL_TYPE = 316,
    DATE_TYPE = 317,
    TIME_TYPE = 318,
    TIMESTAMP_TYPE = 319,
    BOOLEAN_TYPE = 320,

    /* Constraints */
    PRIMARY = 321,
    KEY = 322,
    FOREIGN = 323,
    REFERENCES = 324,
    UNIQUE = 325,
    CHECK = 326,
    DEFAULT = 327,
    AUTO_INCREMENT = 328,

    /* Operators */
    EQUAL = 329,
    NOT_EQUAL = 330,
    LESS_THAN = 331,
    GREATER_THAN = 332,
    LESS_EQUAL = 333,
    GREATER_EQUAL = 334,
    PLUS = 335,
    MINUS = 336,
    MULTIPLY = 337,
    DIVIDE = 338,
    MODULO = 339,

    /* Punctuation */
    LPAREN = 340,
    RPAREN = 341,
    COMMA = 342,
    SEMICOLON = 343,
    DOT = 344,

    /* Aggregate Functions */
    COUNT = 345,
    SUM = 346,
    AVG = 347,
    MIN = 348,
    MAX = 349,

    /* Special tokens */
    UNKNOWN_TOKEN = 350
} token_type_t;

/* Function to get token name for debugging */
const char* get_token_name(int token);

#endif /* TOKENS_H */