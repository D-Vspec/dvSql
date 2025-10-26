/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SQL_PARSER_TAB_H_INCLUDED
# define YY_YY_SQL_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING_LITERAL = 259,          /* STRING_LITERAL  */
    INTEGER_LITERAL = 260,         /* INTEGER_LITERAL  */
    DECIMAL_LITERAL = 261,         /* DECIMAL_LITERAL  */
    SELECT = 262,                  /* SELECT  */
    FROM = 263,                    /* FROM  */
    WHERE = 264,                   /* WHERE  */
    INSERT = 265,                  /* INSERT  */
    INTO = 266,                    /* INTO  */
    VALUES = 267,                  /* VALUES  */
    UPDATE = 268,                  /* UPDATE  */
    SET = 269,                     /* SET  */
    DELETE = 270,                  /* DELETE  */
    CREATE = 271,                  /* CREATE  */
    TABLE = 272,                   /* TABLE  */
    DROP = 273,                    /* DROP  */
    ALTER = 274,                   /* ALTER  */
    AND = 275,                     /* AND  */
    OR = 276,                      /* OR  */
    NOT = 277,                     /* NOT  */
    NULL_TOK = 278,                /* NULL_TOK  */
    TRUE_TOK = 279,                /* TRUE_TOK  */
    FALSE_TOK = 280,               /* FALSE_TOK  */
    AS = 281,                      /* AS  */
    ORDER = 282,                   /* ORDER  */
    BY = 283,                      /* BY  */
    GROUP = 284,                   /* GROUP  */
    HAVING = 285,                  /* HAVING  */
    LIMIT = 286,                   /* LIMIT  */
    OFFSET = 287,                  /* OFFSET  */
    JOIN = 288,                    /* JOIN  */
    INNER = 289,                   /* INNER  */
    LEFT = 290,                    /* LEFT  */
    RIGHT = 291,                   /* RIGHT  */
    OUTER = 292,                   /* OUTER  */
    ON = 293,                      /* ON  */
    USING = 294,                   /* USING  */
    DISTINCT = 295,                /* DISTINCT  */
    ALL = 296,                     /* ALL  */
    IN = 297,                      /* IN  */
    EXISTS = 298,                  /* EXISTS  */
    BETWEEN = 299,                 /* BETWEEN  */
    LIKE = 300,                    /* LIKE  */
    IS = 301,                      /* IS  */
    UNION = 302,                   /* UNION  */
    INTERSECT = 303,               /* INTERSECT  */
    EXCEPT = 304,                  /* EXCEPT  */
    DESC = 305,                    /* DESC  */
    SHOW = 306,                    /* SHOW  */
    TABLES = 307,                  /* TABLES  */
    INT_TYPE = 308,                /* INT_TYPE  */
    INTEGER_TYPE = 309,            /* INTEGER_TYPE  */
    VARCHAR_TYPE = 310,            /* VARCHAR_TYPE  */
    CHAR_TYPE = 311,               /* CHAR_TYPE  */
    TEXT_TYPE = 312,               /* TEXT_TYPE  */
    DECIMAL_TYPE = 313,            /* DECIMAL_TYPE  */
    NUMERIC_TYPE = 314,            /* NUMERIC_TYPE  */
    FLOAT_TYPE = 315,              /* FLOAT_TYPE  */
    REAL_TYPE = 316,               /* REAL_TYPE  */
    DATE_TYPE = 317,               /* DATE_TYPE  */
    TIME_TYPE = 318,               /* TIME_TYPE  */
    TIMESTAMP_TYPE = 319,          /* TIMESTAMP_TYPE  */
    BOOLEAN_TYPE = 320,            /* BOOLEAN_TYPE  */
    PRIMARY = 321,                 /* PRIMARY  */
    KEY = 322,                     /* KEY  */
    FOREIGN = 323,                 /* FOREIGN  */
    REFERENCES = 324,              /* REFERENCES  */
    UNIQUE = 325,                  /* UNIQUE  */
    CHECK = 326,                   /* CHECK  */
    DEFAULT = 327,                 /* DEFAULT  */
    AUTO_INCREMENT = 328,          /* AUTO_INCREMENT  */
    EQUAL = 329,                   /* EQUAL  */
    NOT_EQUAL = 330,               /* NOT_EQUAL  */
    LESS_THAN = 331,               /* LESS_THAN  */
    GREATER_THAN = 332,            /* GREATER_THAN  */
    LESS_EQUAL = 333,              /* LESS_EQUAL  */
    GREATER_EQUAL = 334,           /* GREATER_EQUAL  */
    PLUS = 335,                    /* PLUS  */
    MINUS = 336,                   /* MINUS  */
    MULTIPLY = 337,                /* MULTIPLY  */
    DIVIDE = 338,                  /* DIVIDE  */
    MODULO = 339,                  /* MODULO  */
    LPAREN = 340,                  /* LPAREN  */
    RPAREN = 341,                  /* RPAREN  */
    COMMA = 342,                   /* COMMA  */
    SEMICOLON = 343,               /* SEMICOLON  */
    DOT = 344,                     /* DOT  */
    COUNT = 345,                   /* COUNT  */
    SUM = 346,                     /* SUM  */
    AVG = 347,                     /* AVG  */
    MIN = 348,                     /* MIN  */
    MAX = 349,                     /* MAX  */
    UNKNOWN_TOKEN = 350            /* UNKNOWN_TOKEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "src/yacc/sql_parser.y"

    int int_val;
    double float_val;
    char* string_val;
    ast_node_t* ast_node;
    expression_t* expression;
    column_def_t* column_def;
    column_list_t* column_list;
    value_list_t* value_list;
    table_ref_t* table_ref;
    join_clause_t* join_clause;
    literal_value_t literal;
    data_type_t data_type;
    join_type_t join_type;

#line 175 "sql_parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SQL_PARSER_TAB_H_INCLUDED  */
