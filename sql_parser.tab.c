/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/yacc/sql_parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/ast.h"

/* External variables from lexer */
extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;

/* Error handling */
void yyerror(const char* s);

/* Global AST root */
ast_node_t* ast_root = NULL;

#line 90 "sql_parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "sql_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 4,             /* STRING_LITERAL  */
  YYSYMBOL_INTEGER_LITERAL = 5,            /* INTEGER_LITERAL  */
  YYSYMBOL_DECIMAL_LITERAL = 6,            /* DECIMAL_LITERAL  */
  YYSYMBOL_SELECT = 7,                     /* SELECT  */
  YYSYMBOL_FROM = 8,                       /* FROM  */
  YYSYMBOL_WHERE = 9,                      /* WHERE  */
  YYSYMBOL_INSERT = 10,                    /* INSERT  */
  YYSYMBOL_INTO = 11,                      /* INTO  */
  YYSYMBOL_VALUES = 12,                    /* VALUES  */
  YYSYMBOL_UPDATE = 13,                    /* UPDATE  */
  YYSYMBOL_SET = 14,                       /* SET  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_CREATE = 16,                    /* CREATE  */
  YYSYMBOL_TABLE = 17,                     /* TABLE  */
  YYSYMBOL_DROP = 18,                      /* DROP  */
  YYSYMBOL_ALTER = 19,                     /* ALTER  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_OR = 21,                        /* OR  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_NULL_TOK = 23,                  /* NULL_TOK  */
  YYSYMBOL_TRUE_TOK = 24,                  /* TRUE_TOK  */
  YYSYMBOL_FALSE_TOK = 25,                 /* FALSE_TOK  */
  YYSYMBOL_AS = 26,                        /* AS  */
  YYSYMBOL_ORDER = 27,                     /* ORDER  */
  YYSYMBOL_BY = 28,                        /* BY  */
  YYSYMBOL_GROUP = 29,                     /* GROUP  */
  YYSYMBOL_HAVING = 30,                    /* HAVING  */
  YYSYMBOL_LIMIT = 31,                     /* LIMIT  */
  YYSYMBOL_OFFSET = 32,                    /* OFFSET  */
  YYSYMBOL_JOIN = 33,                      /* JOIN  */
  YYSYMBOL_INNER = 34,                     /* INNER  */
  YYSYMBOL_LEFT = 35,                      /* LEFT  */
  YYSYMBOL_RIGHT = 36,                     /* RIGHT  */
  YYSYMBOL_OUTER = 37,                     /* OUTER  */
  YYSYMBOL_ON = 38,                        /* ON  */
  YYSYMBOL_USING = 39,                     /* USING  */
  YYSYMBOL_DISTINCT = 40,                  /* DISTINCT  */
  YYSYMBOL_ALL = 41,                       /* ALL  */
  YYSYMBOL_IN = 42,                        /* IN  */
  YYSYMBOL_EXISTS = 43,                    /* EXISTS  */
  YYSYMBOL_BETWEEN = 44,                   /* BETWEEN  */
  YYSYMBOL_LIKE = 45,                      /* LIKE  */
  YYSYMBOL_IS = 46,                        /* IS  */
  YYSYMBOL_UNION = 47,                     /* UNION  */
  YYSYMBOL_INTERSECT = 48,                 /* INTERSECT  */
  YYSYMBOL_EXCEPT = 49,                    /* EXCEPT  */
  YYSYMBOL_INT_TYPE = 50,                  /* INT_TYPE  */
  YYSYMBOL_INTEGER_TYPE = 51,              /* INTEGER_TYPE  */
  YYSYMBOL_VARCHAR_TYPE = 52,              /* VARCHAR_TYPE  */
  YYSYMBOL_CHAR_TYPE = 53,                 /* CHAR_TYPE  */
  YYSYMBOL_TEXT_TYPE = 54,                 /* TEXT_TYPE  */
  YYSYMBOL_DECIMAL_TYPE = 55,              /* DECIMAL_TYPE  */
  YYSYMBOL_NUMERIC_TYPE = 56,              /* NUMERIC_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 57,                /* FLOAT_TYPE  */
  YYSYMBOL_REAL_TYPE = 58,                 /* REAL_TYPE  */
  YYSYMBOL_DATE_TYPE = 59,                 /* DATE_TYPE  */
  YYSYMBOL_TIME_TYPE = 60,                 /* TIME_TYPE  */
  YYSYMBOL_TIMESTAMP_TYPE = 61,            /* TIMESTAMP_TYPE  */
  YYSYMBOL_BOOLEAN_TYPE = 62,              /* BOOLEAN_TYPE  */
  YYSYMBOL_PRIMARY = 63,                   /* PRIMARY  */
  YYSYMBOL_KEY = 64,                       /* KEY  */
  YYSYMBOL_FOREIGN = 65,                   /* FOREIGN  */
  YYSYMBOL_REFERENCES = 66,                /* REFERENCES  */
  YYSYMBOL_UNIQUE = 67,                    /* UNIQUE  */
  YYSYMBOL_CHECK = 68,                     /* CHECK  */
  YYSYMBOL_DEFAULT = 69,                   /* DEFAULT  */
  YYSYMBOL_AUTO_INCREMENT = 70,            /* AUTO_INCREMENT  */
  YYSYMBOL_EQUAL = 71,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 72,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS_THAN = 73,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 74,              /* GREATER_THAN  */
  YYSYMBOL_LESS_EQUAL = 75,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 76,             /* GREATER_EQUAL  */
  YYSYMBOL_PLUS = 77,                      /* PLUS  */
  YYSYMBOL_MINUS = 78,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 79,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 80,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 81,                    /* MODULO  */
  YYSYMBOL_LPAREN = 82,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 83,                    /* RPAREN  */
  YYSYMBOL_COMMA = 84,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 85,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 86,                       /* DOT  */
  YYSYMBOL_COUNT = 87,                     /* COUNT  */
  YYSYMBOL_SUM = 88,                       /* SUM  */
  YYSYMBOL_AVG = 89,                       /* AVG  */
  YYSYMBOL_MIN = 90,                       /* MIN  */
  YYSYMBOL_MAX = 91,                       /* MAX  */
  YYSYMBOL_UNKNOWN_TOKEN = 92,             /* UNKNOWN_TOKEN  */
  YYSYMBOL_YYACCEPT = 93,                  /* $accept  */
  YYSYMBOL_program = 94,                   /* program  */
  YYSYMBOL_statement_list = 95,            /* statement_list  */
  YYSYMBOL_statement = 96,                 /* statement  */
  YYSYMBOL_select_statement = 97,          /* select_statement  */
  YYSYMBOL_select_column_list = 98,        /* select_column_list  */
  YYSYMBOL_column_list = 99,               /* column_list  */
  YYSYMBOL_table_reference = 100,          /* table_reference  */
  YYSYMBOL_optional_join_clause_list = 101, /* optional_join_clause_list  */
  YYSYMBOL_join_clause_list = 102,         /* join_clause_list  */
  YYSYMBOL_join_clause = 103,              /* join_clause  */
  YYSYMBOL_join_type = 104,                /* join_type  */
  YYSYMBOL_where_clause = 105,             /* where_clause  */
  YYSYMBOL_order_by_clause = 106,          /* order_by_clause  */
  YYSYMBOL_insert_statement = 107,         /* insert_statement  */
  YYSYMBOL_value_list = 108,               /* value_list  */
  YYSYMBOL_update_statement = 109,         /* update_statement  */
  YYSYMBOL_update_column_list = 110,       /* update_column_list  */
  YYSYMBOL_delete_statement = 111,         /* delete_statement  */
  YYSYMBOL_create_table_statement = 112,   /* create_table_statement  */
  YYSYMBOL_column_definition_list = 113,   /* column_definition_list  */
  YYSYMBOL_column_definition = 114,        /* column_definition  */
  YYSYMBOL_data_type = 115,                /* data_type  */
  YYSYMBOL_drop_table_statement = 116,     /* drop_table_statement  */
  YYSYMBOL_expression = 117,               /* expression  */
  YYSYMBOL_condition = 118,                /* condition  */
  YYSYMBOL_literal = 119,                  /* literal  */
  YYSYMBOL_column_reference = 120,         /* column_reference  */
  YYSYMBOL_function_call = 121             /* function_call  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   305

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  208

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   347


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,    95,    99,   100,   104,   105,   106,   107,   108,
     109,   114,   122,   135,   139,   143,   147,   153,   156,   159,
     165,   166,   170,   174,   178,   181,   187,   188,   189,   190,
     191,   195,   196,   205,   206,   211,   214,   220,   224,   231,
     238,   242,   249,   256,   262,   266,   270,   273,   277,   281,
     285,   289,   293,   300,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   327,   334,   335,
     336,   337,   340,   343,   346,   349,   352,   356,   359,   362,
     365,   368,   371,   374,   377,   380,   383,   384,   388,   393,
     398,   403,   408,   413,   421,   424,   430,   433,   451,   454,
     459,   464,   469,   474
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "STRING_LITERAL", "INTEGER_LITERAL", "DECIMAL_LITERAL", "SELECT", "FROM",
  "WHERE", "INSERT", "INTO", "VALUES", "UPDATE", "SET", "DELETE", "CREATE",
  "TABLE", "DROP", "ALTER", "AND", "OR", "NOT", "NULL_TOK", "TRUE_TOK",
  "FALSE_TOK", "AS", "ORDER", "BY", "GROUP", "HAVING", "LIMIT", "OFFSET",
  "JOIN", "INNER", "LEFT", "RIGHT", "OUTER", "ON", "USING", "DISTINCT",
  "ALL", "IN", "EXISTS", "BETWEEN", "LIKE", "IS", "UNION", "INTERSECT",
  "EXCEPT", "INT_TYPE", "INTEGER_TYPE", "VARCHAR_TYPE", "CHAR_TYPE",
  "TEXT_TYPE", "DECIMAL_TYPE", "NUMERIC_TYPE", "FLOAT_TYPE", "REAL_TYPE",
  "DATE_TYPE", "TIME_TYPE", "TIMESTAMP_TYPE", "BOOLEAN_TYPE", "PRIMARY",
  "KEY", "FOREIGN", "REFERENCES", "UNIQUE", "CHECK", "DEFAULT",
  "AUTO_INCREMENT", "EQUAL", "NOT_EQUAL", "LESS_THAN", "GREATER_THAN",
  "LESS_EQUAL", "GREATER_EQUAL", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "MODULO", "LPAREN", "RPAREN", "COMMA", "SEMICOLON", "DOT", "COUNT",
  "SUM", "AVG", "MIN", "MAX", "UNKNOWN_TOKEN", "$accept", "program",
  "statement_list", "statement", "select_statement", "select_column_list",
  "column_list", "table_reference", "optional_join_clause_list",
  "join_clause_list", "join_clause", "join_type", "where_clause",
  "order_by_clause", "insert_statement", "value_list", "update_statement",
  "update_column_list", "delete_statement", "create_table_statement",
  "column_definition_list", "column_definition", "data_type",
  "drop_table_statement", "expression", "condition", "literal",
  "column_reference", "function_call", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-112)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     191,     2,     3,    18,    26,    28,    36,    63,   191,     0,
    -112,  -112,  -112,  -112,  -112,  -112,   -51,  -112,  -112,  -112,
    -112,  -112,  -112,    72,  -112,   170,     4,     6,    16,    21,
      23,   109,    48,   -61,  -112,  -112,  -112,   132,   138,   150,
     166,   169,  -112,    92,  -112,    96,   177,   173,   -40,   123,
     170,   170,   170,   170,   179,   170,   170,   170,   170,   170,
     170,    -9,   185,   180,   114,  -112,  -112,  -112,   -55,   -61,
    -112,   179,  -112,   108,    30,    87,   197,   204,   211,    10,
      89,   -61,   -14,   -14,  -112,  -112,  -112,   115,   170,   128,
      -5,   133,  -112,   200,  -112,   170,    89,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,   205,   179,  -112,   163,   181,   180,
      89,  -112,   183,   170,    32,   170,   214,  -112,   133,   133,
     192,    49,   175,    47,  -112,   -61,   180,  -112,   213,  -112,
    -112,   222,  -112,   179,    50,   207,   -61,   182,  -112,   167,
     -11,   170,   170,   170,   170,   170,   170,   133,   133,  -112,
    -112,   172,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,     1,  -112,   200,   222,   133,   227,  -112,   218,
    -112,   215,   170,  -112,   -61,   -61,   -61,   -61,   -61,   -61,
    -112,   242,   274,   263,   229,  -112,  -112,   290,  -112,  -112,
      49,   170,   133,   170,   -61,   216,  -112,  -112,   217,    48,
      49,    66,    -7,  -112,  -112,   273,  -112,  -112
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     2,     0,
       5,     6,     7,     8,     9,    10,    94,    90,    88,    89,
      91,    92,    93,     0,    13,     0,     0,     0,     0,     0,
       0,     0,    14,    16,    68,    69,    70,     0,     0,     0,
       0,     0,     1,     0,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,     0,    67,     3,    96,     0,    38,
      95,     0,    76,     0,     0,     0,     0,     0,     0,    17,
      21,    15,    71,    72,    73,    74,    75,     0,     0,     0,
      32,     0,    42,     0,    97,     0,    21,    98,    99,   100,
     101,   102,   103,    19,     0,     0,    26,    27,    28,    32,
      20,    23,     0,     0,     0,     0,     0,    39,     0,     0,
      87,    31,     0,     0,    45,    37,    32,    18,     0,    29,
      30,    34,    22,     0,     0,     0,    41,     0,    85,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    46,    43,     0,    34,     0,     0,    11,     0,
      36,     0,     0,    86,    77,    78,    79,    80,    81,    82,
      83,    84,     0,     0,     0,    50,    51,     0,    44,    12,
      25,     0,     0,     0,    40,     0,    49,    48,     0,    33,
      24,     0,     0,    47,    35,     0,    53,    52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -112,  -112,  -112,   293,  -112,   275,   -87,   -59,   206,  -112,
     193,  -112,   -79,   139,  -112,  -111,  -112,  -112,  -112,  -112,
    -112,   141,  -112,  -112,    -1,   -86,  -112,  -112,  -112
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    31,    32,    80,   109,   110,
     111,   112,    92,   168,    11,    68,    12,    90,    13,    14,
     123,   124,   162,    15,   120,   121,    34,    35,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      33,   114,   134,    87,    91,    16,    17,    18,    19,   147,
     148,   117,    96,   103,    37,   205,    56,    57,    58,    59,
      60,    38,    33,   183,    48,    20,    21,    22,    94,    95,
     131,    45,   138,   140,    39,    46,   104,    56,    57,    58,
      59,    60,    23,    72,    69,    40,   128,   165,    74,    75,
      76,    77,    78,    41,    81,    82,    83,    84,    85,    86,
     206,   180,   181,    42,   184,    58,    59,    60,   185,   147,
     148,   186,   173,    88,   169,    16,    17,    18,    19,   116,
     190,    24,   201,   187,    25,    44,    49,    33,    50,    26,
      27,    28,    29,    30,   125,    20,    21,    22,    51,    16,
      17,    18,    19,    52,   199,    53,   200,    56,    57,    58,
      59,    60,    69,    98,   136,   135,    55,    54,   139,    20,
      21,    22,   105,   106,   107,   108,    16,    17,    18,    19,
     163,   164,    55,   170,    95,    61,    16,    17,    18,    19,
     174,   175,   176,   177,   178,   179,    20,    21,    22,   204,
      95,    24,    62,    63,    25,   118,    20,    21,    22,    26,
      27,    28,    29,    30,    56,    57,    58,    59,    60,    64,
      99,   194,    65,    16,    17,    18,    19,    66,    25,    67,
      70,    71,    79,    26,    27,    28,    29,    30,    89,    91,
      33,    97,    69,    20,    21,    22,    93,   113,     1,   115,
     129,     2,    73,   122,     3,    25,     4,     5,   127,     6,
      26,    27,    28,    29,    30,   119,   133,   137,   130,   171,
      26,    27,    28,    29,    30,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   141,   142,
     143,   144,   145,   146,    56,    57,    58,    59,    60,   167,
      72,   166,    25,   172,   182,   191,   192,    26,    27,    28,
      29,    30,   147,   141,   142,   143,   144,   145,   146,    56,
      57,    58,    59,    60,    56,    57,    58,    59,    60,   195,
     100,    56,    57,    58,    59,    60,   196,   101,    56,    57,
      58,    59,    60,   197,   102,   198,   207,   193,    47,   202,
     203,    43,   126,   132,   189,   188
};

static const yytype_uint8 yycheck[] =
{
       1,    88,   113,    12,     9,     3,     4,     5,     6,    20,
      21,    90,    71,     3,    11,    22,    77,    78,    79,    80,
      81,     3,    23,    22,    25,    23,    24,    25,    83,    84,
     109,    82,   118,   119,     8,    86,    26,    77,    78,    79,
      80,    81,    40,    83,    45,    17,   105,   126,    49,    50,
      51,    52,    53,    17,    55,    56,    57,    58,    59,    60,
      67,   147,   148,     0,    63,    79,    80,    81,    67,    20,
      21,    70,    83,    82,   133,     3,     4,     5,     6,    84,
     166,    79,   193,    82,    82,    85,    82,    88,    82,    87,
      88,    89,    90,    91,    95,    23,    24,    25,    82,     3,
       4,     5,     6,    82,   191,    82,   192,    77,    78,    79,
      80,    81,   113,    83,   115,    83,    84,     8,   119,    23,
      24,    25,    33,    34,    35,    36,     3,     4,     5,     6,
      83,    84,    84,    83,    84,     3,     3,     4,     5,     6,
     141,   142,   143,   144,   145,   146,    23,    24,    25,    83,
      84,    79,    14,     3,    82,    22,    23,    24,    25,    87,
      88,    89,    90,    91,    77,    78,    79,    80,    81,     3,
      83,   172,     3,     3,     4,     5,     6,    85,    82,    83,
       3,     8,     3,    87,    88,    89,    90,    91,     3,     9,
     191,    83,   193,    23,    24,    25,    82,    82,     7,    71,
      37,    10,    79,     3,    13,    82,    15,    16,     3,    18,
      87,    88,    89,    90,    91,    82,    33,     3,    37,    12,
      87,    88,    89,    90,    91,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    27,
      83,    38,    82,    71,    82,    28,    38,    87,    88,    89,
      90,    91,    20,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    77,    78,    79,    80,    81,     5,
      83,    77,    78,    79,    80,    81,    23,    83,    77,    78,
      79,    80,    81,    64,    83,     5,    23,    82,    23,    83,
      83,     8,    96,   110,   165,   164
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    10,    13,    15,    16,    18,    94,    95,    96,
      97,   107,   109,   111,   112,   116,     3,     4,     5,     6,
      23,    24,    25,    40,    79,    82,    87,    88,    89,    90,
      91,    98,    99,   117,   119,   120,   121,    11,     3,     8,
      17,    17,     0,    96,    85,    82,    86,    98,   117,    82,
      82,    82,    82,    82,     8,    84,    77,    78,    79,    80,
      81,     3,    14,     3,     3,     3,    85,    83,   108,   117,
       3,     8,    83,    79,   117,   117,   117,   117,   117,     3,
     100,   117,   117,   117,   117,   117,   117,    12,    82,     3,
     110,     9,   105,    82,    83,    84,   100,    83,    83,    83,
      83,    83,    83,     3,    26,    33,    34,    35,    36,   101,
     102,   103,   104,    82,    99,    71,    84,   105,    22,    82,
     117,   118,     3,   113,   114,   117,   101,     3,   100,    37,
      37,   105,   103,    33,   108,    83,   117,     3,   118,   117,
     118,    71,    72,    73,    74,    75,    76,    20,    21,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,   115,    83,    84,   105,    38,    27,   106,   100,
      83,    12,    71,    83,   117,   117,   117,   117,   117,   117,
     118,   118,    82,    22,    63,    67,    70,    82,   114,   106,
     118,    28,    38,    82,   117,     5,    23,    64,     5,    99,
     118,   108,    83,    83,    83,    22,    67,    23
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    93,    94,    95,    95,    96,    96,    96,    96,    96,
      96,    97,    97,    98,    98,    99,    99,   100,   100,   100,
     101,   101,   102,   102,   103,   103,   104,   104,   104,   104,
     104,   105,   105,   106,   106,   107,   107,   108,   108,   109,
     110,   110,   111,   112,   113,   113,   114,   114,   114,   114,
     114,   114,   114,   114,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   116,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   119,   119,
     119,   119,   119,   119,   120,   120,   121,   121,   121,   121,
     121,   121,   121,   121
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     7,     8,     1,     1,     3,     1,     1,     3,     2,
       1,     0,     2,     1,     5,     4,     1,     1,     1,     2,
       2,     2,     0,     3,     0,    10,     7,     3,     1,     5,
       5,     3,     4,     6,     3,     1,     2,     5,     4,     4,
       3,     3,     7,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     4,     4,     4,
       4,     4,     4,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* statement_list: statement_list statement SEMICOLON  */
#line 99 "src/yacc/sql_parser.y"
                                       { ast_root = (yyvsp[-1].ast_node); }
#line 1368 "sql_parser.tab.c"
    break;

  case 4: /* statement_list: statement SEMICOLON  */
#line 100 "src/yacc/sql_parser.y"
                          { ast_root = (yyvsp[-1].ast_node); }
#line 1374 "sql_parser.tab.c"
    break;

  case 5: /* statement: select_statement  */
#line 104 "src/yacc/sql_parser.y"
                     { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1380 "sql_parser.tab.c"
    break;

  case 6: /* statement: insert_statement  */
#line 105 "src/yacc/sql_parser.y"
                       { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1386 "sql_parser.tab.c"
    break;

  case 7: /* statement: update_statement  */
#line 106 "src/yacc/sql_parser.y"
                       { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1392 "sql_parser.tab.c"
    break;

  case 8: /* statement: delete_statement  */
#line 107 "src/yacc/sql_parser.y"
                       { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1398 "sql_parser.tab.c"
    break;

  case 9: /* statement: create_table_statement  */
#line 108 "src/yacc/sql_parser.y"
                             { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1404 "sql_parser.tab.c"
    break;

  case 10: /* statement: drop_table_statement  */
#line 109 "src/yacc/sql_parser.y"
                           { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1410 "sql_parser.tab.c"
    break;

  case 11: /* select_statement: SELECT select_column_list FROM table_reference optional_join_clause_list where_clause order_by_clause  */
#line 114 "src/yacc/sql_parser.y"
                                                                                                          {
        (yyval.ast_node) = create_select_stmt((yyvsp[-5].column_list), (yyvsp[-3].table_ref));
        if ((yyval.ast_node)) {
            (yyval.ast_node)->data.select_stmt.joins = (yyvsp[-2].join_clause);
            (yyval.ast_node)->data.select_stmt.where_clause = (yyvsp[-1].expression);
            (yyval.ast_node)->data.select_stmt.order_by = (yyvsp[0].column_list);
        }
    }
#line 1423 "sql_parser.tab.c"
    break;

  case 12: /* select_statement: SELECT DISTINCT select_column_list FROM table_reference optional_join_clause_list where_clause order_by_clause  */
#line 122 "src/yacc/sql_parser.y"
                                                                                                                     {
        (yyval.ast_node) = create_select_stmt((yyvsp[-5].column_list), (yyvsp[-3].table_ref));
        if ((yyval.ast_node)) {
            (yyval.ast_node)->data.select_stmt.distinct = 1;
            (yyval.ast_node)->data.select_stmt.joins = (yyvsp[-2].join_clause);
            (yyval.ast_node)->data.select_stmt.where_clause = (yyvsp[-1].expression);
            (yyval.ast_node)->data.select_stmt.order_by = (yyvsp[0].column_list);
        }
    }
#line 1437 "sql_parser.tab.c"
    break;

  case 13: /* select_column_list: MULTIPLY  */
#line 135 "src/yacc/sql_parser.y"
             {
        expression_t* expr = create_identifier_expr("*");
        (yyval.column_list) = create_column_list(expr);
    }
#line 1446 "sql_parser.tab.c"
    break;

  case 14: /* select_column_list: column_list  */
#line 139 "src/yacc/sql_parser.y"
                  { (yyval.column_list) = (yyvsp[0].column_list); }
#line 1452 "sql_parser.tab.c"
    break;

  case 15: /* column_list: column_list COMMA expression  */
#line 143 "src/yacc/sql_parser.y"
                                 {
        add_column_to_list(&(yyvsp[-2].column_list), (yyvsp[0].expression));
        (yyval.column_list) = (yyvsp[-2].column_list);
    }
#line 1461 "sql_parser.tab.c"
    break;

  case 16: /* column_list: expression  */
#line 147 "src/yacc/sql_parser.y"
                 {
        (yyval.column_list) = create_column_list((yyvsp[0].expression));
    }
#line 1469 "sql_parser.tab.c"
    break;

  case 17: /* table_reference: IDENTIFIER  */
#line 153 "src/yacc/sql_parser.y"
               {
        (yyval.table_ref) = create_table_ref((yyvsp[0].string_val), NULL);
    }
#line 1477 "sql_parser.tab.c"
    break;

  case 18: /* table_reference: IDENTIFIER AS IDENTIFIER  */
#line 156 "src/yacc/sql_parser.y"
                               {
        (yyval.table_ref) = create_table_ref((yyvsp[-2].string_val), (yyvsp[0].string_val));
    }
#line 1485 "sql_parser.tab.c"
    break;

  case 19: /* table_reference: IDENTIFIER IDENTIFIER  */
#line 159 "src/yacc/sql_parser.y"
                            {
        (yyval.table_ref) = create_table_ref((yyvsp[-1].string_val), (yyvsp[0].string_val));
    }
#line 1493 "sql_parser.tab.c"
    break;

  case 20: /* optional_join_clause_list: join_clause_list  */
#line 165 "src/yacc/sql_parser.y"
                     { (yyval.join_clause) = (yyvsp[0].join_clause); }
#line 1499 "sql_parser.tab.c"
    break;

  case 21: /* optional_join_clause_list: %empty  */
#line 166 "src/yacc/sql_parser.y"
                  { (yyval.join_clause) = NULL; }
#line 1505 "sql_parser.tab.c"
    break;

  case 22: /* join_clause_list: join_clause_list join_clause  */
#line 170 "src/yacc/sql_parser.y"
                                 {
        add_join_to_clause(&(yyvsp[-1].join_clause), (yyvsp[0].join_clause));
        (yyval.join_clause) = (yyvsp[-1].join_clause);
    }
#line 1514 "sql_parser.tab.c"
    break;

  case 23: /* join_clause_list: join_clause  */
#line 174 "src/yacc/sql_parser.y"
                  { (yyval.join_clause) = (yyvsp[0].join_clause); }
#line 1520 "sql_parser.tab.c"
    break;

  case 24: /* join_clause: join_type JOIN table_reference ON condition  */
#line 178 "src/yacc/sql_parser.y"
                                                {
        (yyval.join_clause) = create_join_clause((yyvsp[-4].join_type), (yyvsp[-2].table_ref), (yyvsp[0].expression));
    }
#line 1528 "sql_parser.tab.c"
    break;

  case 25: /* join_clause: JOIN table_reference ON condition  */
#line 181 "src/yacc/sql_parser.y"
                                        {
        (yyval.join_clause) = create_join_clause(JOIN_INNER, (yyvsp[-2].table_ref), (yyvsp[0].expression));
    }
#line 1536 "sql_parser.tab.c"
    break;

  case 26: /* join_type: INNER  */
#line 187 "src/yacc/sql_parser.y"
          { (yyval.join_type) = JOIN_INNER; }
#line 1542 "sql_parser.tab.c"
    break;

  case 27: /* join_type: LEFT  */
#line 188 "src/yacc/sql_parser.y"
           { (yyval.join_type) = JOIN_LEFT; }
#line 1548 "sql_parser.tab.c"
    break;

  case 28: /* join_type: RIGHT  */
#line 189 "src/yacc/sql_parser.y"
            { (yyval.join_type) = JOIN_RIGHT; }
#line 1554 "sql_parser.tab.c"
    break;

  case 29: /* join_type: LEFT OUTER  */
#line 190 "src/yacc/sql_parser.y"
                 { (yyval.join_type) = JOIN_LEFT; }
#line 1560 "sql_parser.tab.c"
    break;

  case 30: /* join_type: RIGHT OUTER  */
#line 191 "src/yacc/sql_parser.y"
                  { (yyval.join_type) = JOIN_RIGHT; }
#line 1566 "sql_parser.tab.c"
    break;

  case 31: /* where_clause: WHERE condition  */
#line 195 "src/yacc/sql_parser.y"
                    { (yyval.expression) = (yyvsp[0].expression); }
#line 1572 "sql_parser.tab.c"
    break;

  case 32: /* where_clause: %empty  */
#line 196 "src/yacc/sql_parser.y"
                  { (yyval.expression) = NULL; }
#line 1578 "sql_parser.tab.c"
    break;

  case 33: /* order_by_clause: ORDER BY column_list  */
#line 205 "src/yacc/sql_parser.y"
                         { (yyval.column_list) = (yyvsp[0].column_list); }
#line 1584 "sql_parser.tab.c"
    break;

  case 34: /* order_by_clause: %empty  */
#line 206 "src/yacc/sql_parser.y"
                  { (yyval.column_list) = NULL; }
#line 1590 "sql_parser.tab.c"
    break;

  case 35: /* insert_statement: INSERT INTO IDENTIFIER LPAREN column_list RPAREN VALUES LPAREN value_list RPAREN  */
#line 211 "src/yacc/sql_parser.y"
                                                                                     {
        (yyval.ast_node) = create_insert_stmt((yyvsp[-7].string_val), (yyvsp[-5].column_list), (yyvsp[-1].value_list));
    }
#line 1598 "sql_parser.tab.c"
    break;

  case 36: /* insert_statement: INSERT INTO IDENTIFIER VALUES LPAREN value_list RPAREN  */
#line 214 "src/yacc/sql_parser.y"
                                                             {
        (yyval.ast_node) = create_insert_stmt((yyvsp[-4].string_val), NULL, (yyvsp[-1].value_list));
    }
#line 1606 "sql_parser.tab.c"
    break;

  case 37: /* value_list: value_list COMMA expression  */
#line 220 "src/yacc/sql_parser.y"
                                {
        add_value_to_list(&(yyvsp[-2].value_list), (yyvsp[0].expression));
        (yyval.value_list) = (yyvsp[-2].value_list);
    }
#line 1615 "sql_parser.tab.c"
    break;

  case 38: /* value_list: expression  */
#line 224 "src/yacc/sql_parser.y"
                 {
        (yyval.value_list) = create_value_list((yyvsp[0].expression));
    }
#line 1623 "sql_parser.tab.c"
    break;

  case 39: /* update_statement: UPDATE IDENTIFIER SET update_column_list where_clause  */
#line 231 "src/yacc/sql_parser.y"
                                                          {
        /* Note: update_column_list now contains the values, not column names */
        (yyval.ast_node) = create_update_stmt((yyvsp[-3].string_val), NULL, (yyvsp[-1].value_list), (yyvsp[0].expression));
    }
#line 1632 "sql_parser.tab.c"
    break;

  case 40: /* update_column_list: update_column_list COMMA IDENTIFIER EQUAL expression  */
#line 238 "src/yacc/sql_parser.y"
                                                         {
        add_value_to_list(&(yyvsp[-4].value_list), (yyvsp[0].expression));  /* Add the expression value */
        (yyval.value_list) = (yyvsp[-4].value_list);
    }
#line 1641 "sql_parser.tab.c"
    break;

  case 41: /* update_column_list: IDENTIFIER EQUAL expression  */
#line 242 "src/yacc/sql_parser.y"
                                  {
        (yyval.value_list) = create_value_list((yyvsp[0].expression));  /* Start with the expression value */
    }
#line 1649 "sql_parser.tab.c"
    break;

  case 42: /* delete_statement: DELETE FROM IDENTIFIER where_clause  */
#line 249 "src/yacc/sql_parser.y"
                                        {
        (yyval.ast_node) = create_delete_stmt((yyvsp[-1].string_val), (yyvsp[0].expression));
    }
#line 1657 "sql_parser.tab.c"
    break;

  case 43: /* create_table_statement: CREATE TABLE IDENTIFIER LPAREN column_definition_list RPAREN  */
#line 256 "src/yacc/sql_parser.y"
                                                                 {
        (yyval.ast_node) = create_create_table_stmt((yyvsp[-3].string_val), (yyvsp[-1].column_def));
    }
#line 1665 "sql_parser.tab.c"
    break;

  case 44: /* column_definition_list: column_definition_list COMMA column_definition  */
#line 262 "src/yacc/sql_parser.y"
                                                   {
        add_column_to_def(&(yyvsp[-2].column_def), (yyvsp[0].column_def));
        (yyval.column_def) = (yyvsp[-2].column_def);
    }
#line 1674 "sql_parser.tab.c"
    break;

  case 45: /* column_definition_list: column_definition  */
#line 266 "src/yacc/sql_parser.y"
                        { (yyval.column_def) = (yyvsp[0].column_def); }
#line 1680 "sql_parser.tab.c"
    break;

  case 46: /* column_definition: IDENTIFIER data_type  */
#line 270 "src/yacc/sql_parser.y"
                         {
        (yyval.column_def) = create_column_def((yyvsp[-1].string_val), (yyvsp[0].data_type));
    }
#line 1688 "sql_parser.tab.c"
    break;

  case 47: /* column_definition: IDENTIFIER data_type LPAREN INTEGER_LITERAL RPAREN  */
#line 273 "src/yacc/sql_parser.y"
                                                         {
        (yyval.column_def) = create_column_def((yyvsp[-4].string_val), (yyvsp[-3].data_type));
        if ((yyval.column_def)) (yyval.column_def)->size = (yyvsp[-1].int_val);
    }
#line 1697 "sql_parser.tab.c"
    break;

  case 48: /* column_definition: IDENTIFIER data_type PRIMARY KEY  */
#line 277 "src/yacc/sql_parser.y"
                                       {
        (yyval.column_def) = create_column_def((yyvsp[-3].string_val), (yyvsp[-2].data_type));
        if ((yyval.column_def)) (yyval.column_def)->is_primary_key = 1;
    }
#line 1706 "sql_parser.tab.c"
    break;

  case 49: /* column_definition: IDENTIFIER data_type NOT NULL_TOK  */
#line 281 "src/yacc/sql_parser.y"
                                        {
        (yyval.column_def) = create_column_def((yyvsp[-3].string_val), (yyvsp[-2].data_type));
        if ((yyval.column_def)) (yyval.column_def)->is_not_null = 1;
    }
#line 1715 "sql_parser.tab.c"
    break;

  case 50: /* column_definition: IDENTIFIER data_type UNIQUE  */
#line 285 "src/yacc/sql_parser.y"
                                  {
        (yyval.column_def) = create_column_def((yyvsp[-2].string_val), (yyvsp[-1].data_type));
        if ((yyval.column_def)) (yyval.column_def)->is_unique = 1;
    }
#line 1724 "sql_parser.tab.c"
    break;

  case 51: /* column_definition: IDENTIFIER data_type AUTO_INCREMENT  */
#line 289 "src/yacc/sql_parser.y"
                                          {
        (yyval.column_def) = create_column_def((yyvsp[-2].string_val), (yyvsp[-1].data_type));
        if ((yyval.column_def)) (yyval.column_def)->has_auto_increment = 1;
    }
#line 1733 "sql_parser.tab.c"
    break;

  case 52: /* column_definition: IDENTIFIER VARCHAR_TYPE LPAREN INTEGER_LITERAL RPAREN NOT NULL_TOK  */
#line 293 "src/yacc/sql_parser.y"
                                                                         {
        (yyval.column_def) = create_column_def((yyvsp[-6].string_val), DATA_TYPE_VARCHAR);
        if ((yyval.column_def)) {
            (yyval.column_def)->size = (yyvsp[-3].int_val);
            (yyval.column_def)->is_not_null = 1;
        }
    }
#line 1745 "sql_parser.tab.c"
    break;

  case 53: /* column_definition: IDENTIFIER VARCHAR_TYPE LPAREN INTEGER_LITERAL RPAREN UNIQUE  */
#line 300 "src/yacc/sql_parser.y"
                                                                   {
        (yyval.column_def) = create_column_def((yyvsp[-5].string_val), DATA_TYPE_VARCHAR);
        if ((yyval.column_def)) {
            (yyval.column_def)->size = (yyvsp[-2].int_val);
            (yyval.column_def)->is_unique = 1;
        }
    }
#line 1757 "sql_parser.tab.c"
    break;

  case 54: /* data_type: INT_TYPE  */
#line 310 "src/yacc/sql_parser.y"
             { (yyval.data_type) = DATA_TYPE_INT; }
#line 1763 "sql_parser.tab.c"
    break;

  case 55: /* data_type: INTEGER_TYPE  */
#line 311 "src/yacc/sql_parser.y"
                   { (yyval.data_type) = DATA_TYPE_INT; }
#line 1769 "sql_parser.tab.c"
    break;

  case 56: /* data_type: VARCHAR_TYPE  */
#line 312 "src/yacc/sql_parser.y"
                   { (yyval.data_type) = DATA_TYPE_VARCHAR; }
#line 1775 "sql_parser.tab.c"
    break;

  case 57: /* data_type: CHAR_TYPE  */
#line 313 "src/yacc/sql_parser.y"
                { (yyval.data_type) = DATA_TYPE_CHAR; }
#line 1781 "sql_parser.tab.c"
    break;

  case 58: /* data_type: TEXT_TYPE  */
#line 314 "src/yacc/sql_parser.y"
                { (yyval.data_type) = DATA_TYPE_TEXT; }
#line 1787 "sql_parser.tab.c"
    break;

  case 59: /* data_type: DECIMAL_TYPE  */
#line 315 "src/yacc/sql_parser.y"
                   { (yyval.data_type) = DATA_TYPE_DECIMAL; }
#line 1793 "sql_parser.tab.c"
    break;

  case 60: /* data_type: NUMERIC_TYPE  */
#line 316 "src/yacc/sql_parser.y"
                   { (yyval.data_type) = DATA_TYPE_DECIMAL; }
#line 1799 "sql_parser.tab.c"
    break;

  case 61: /* data_type: FLOAT_TYPE  */
#line 317 "src/yacc/sql_parser.y"
                 { (yyval.data_type) = DATA_TYPE_FLOAT; }
#line 1805 "sql_parser.tab.c"
    break;

  case 62: /* data_type: REAL_TYPE  */
#line 318 "src/yacc/sql_parser.y"
                { (yyval.data_type) = DATA_TYPE_FLOAT; }
#line 1811 "sql_parser.tab.c"
    break;

  case 63: /* data_type: DATE_TYPE  */
#line 319 "src/yacc/sql_parser.y"
                { (yyval.data_type) = DATA_TYPE_DATE; }
#line 1817 "sql_parser.tab.c"
    break;

  case 64: /* data_type: TIME_TYPE  */
#line 320 "src/yacc/sql_parser.y"
                { (yyval.data_type) = DATA_TYPE_TIME; }
#line 1823 "sql_parser.tab.c"
    break;

  case 65: /* data_type: TIMESTAMP_TYPE  */
#line 321 "src/yacc/sql_parser.y"
                     { (yyval.data_type) = DATA_TYPE_TIMESTAMP; }
#line 1829 "sql_parser.tab.c"
    break;

  case 66: /* data_type: BOOLEAN_TYPE  */
#line 322 "src/yacc/sql_parser.y"
                   { (yyval.data_type) = DATA_TYPE_BOOLEAN; }
#line 1835 "sql_parser.tab.c"
    break;

  case 67: /* drop_table_statement: DROP TABLE IDENTIFIER  */
#line 327 "src/yacc/sql_parser.y"
                          {
        (yyval.ast_node) = create_drop_table_stmt((yyvsp[0].string_val));
    }
#line 1843 "sql_parser.tab.c"
    break;

  case 68: /* expression: literal  */
#line 334 "src/yacc/sql_parser.y"
            { (yyval.expression) = (yyvsp[0].expression); }
#line 1849 "sql_parser.tab.c"
    break;

  case 69: /* expression: column_reference  */
#line 335 "src/yacc/sql_parser.y"
                       { (yyval.expression) = (yyvsp[0].expression); }
#line 1855 "sql_parser.tab.c"
    break;

  case 70: /* expression: function_call  */
#line 336 "src/yacc/sql_parser.y"
                    { (yyval.expression) = (yyvsp[0].expression); }
#line 1861 "sql_parser.tab.c"
    break;

  case 71: /* expression: expression PLUS expression  */
#line 337 "src/yacc/sql_parser.y"
                                 {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), PLUS);
    }
#line 1869 "sql_parser.tab.c"
    break;

  case 72: /* expression: expression MINUS expression  */
#line 340 "src/yacc/sql_parser.y"
                                  {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), MINUS);
    }
#line 1877 "sql_parser.tab.c"
    break;

  case 73: /* expression: expression MULTIPLY expression  */
#line 343 "src/yacc/sql_parser.y"
                                     {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), MULTIPLY);
    }
#line 1885 "sql_parser.tab.c"
    break;

  case 74: /* expression: expression DIVIDE expression  */
#line 346 "src/yacc/sql_parser.y"
                                   {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), DIVIDE);
    }
#line 1893 "sql_parser.tab.c"
    break;

  case 75: /* expression: expression MODULO expression  */
#line 349 "src/yacc/sql_parser.y"
                                   {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), MODULO);
    }
#line 1901 "sql_parser.tab.c"
    break;

  case 76: /* expression: LPAREN expression RPAREN  */
#line 352 "src/yacc/sql_parser.y"
                               { (yyval.expression) = (yyvsp[-1].expression); }
#line 1907 "sql_parser.tab.c"
    break;

  case 77: /* condition: expression EQUAL expression  */
#line 356 "src/yacc/sql_parser.y"
                                {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), EQUAL);
    }
#line 1915 "sql_parser.tab.c"
    break;

  case 78: /* condition: expression NOT_EQUAL expression  */
#line 359 "src/yacc/sql_parser.y"
                                      {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), NOT_EQUAL);
    }
#line 1923 "sql_parser.tab.c"
    break;

  case 79: /* condition: expression LESS_THAN expression  */
#line 362 "src/yacc/sql_parser.y"
                                      {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), LESS_THAN);
    }
#line 1931 "sql_parser.tab.c"
    break;

  case 80: /* condition: expression GREATER_THAN expression  */
#line 365 "src/yacc/sql_parser.y"
                                         {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), GREATER_THAN);
    }
#line 1939 "sql_parser.tab.c"
    break;

  case 81: /* condition: expression LESS_EQUAL expression  */
#line 368 "src/yacc/sql_parser.y"
                                       {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), LESS_EQUAL);
    }
#line 1947 "sql_parser.tab.c"
    break;

  case 82: /* condition: expression GREATER_EQUAL expression  */
#line 371 "src/yacc/sql_parser.y"
                                          {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), GREATER_EQUAL);
    }
#line 1955 "sql_parser.tab.c"
    break;

  case 83: /* condition: condition AND condition  */
#line 374 "src/yacc/sql_parser.y"
                              {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), AND);
    }
#line 1963 "sql_parser.tab.c"
    break;

  case 84: /* condition: condition OR condition  */
#line 377 "src/yacc/sql_parser.y"
                             {
        (yyval.expression) = create_binary_op_expr((yyvsp[-2].expression), (yyvsp[0].expression), OR);
    }
#line 1971 "sql_parser.tab.c"
    break;

  case 85: /* condition: NOT condition  */
#line 380 "src/yacc/sql_parser.y"
                    {
        (yyval.expression) = create_unary_op_expr((yyvsp[0].expression), NOT);
    }
#line 1979 "sql_parser.tab.c"
    break;

  case 86: /* condition: LPAREN condition RPAREN  */
#line 383 "src/yacc/sql_parser.y"
                              { (yyval.expression) = (yyvsp[-1].expression); }
#line 1985 "sql_parser.tab.c"
    break;

  case 87: /* condition: expression  */
#line 384 "src/yacc/sql_parser.y"
                 { (yyval.expression) = (yyvsp[0].expression); }
#line 1991 "sql_parser.tab.c"
    break;

  case 88: /* literal: INTEGER_LITERAL  */
#line 388 "src/yacc/sql_parser.y"
                    {
        literal_value_t val;
        val.int_val = (yyvsp[0].int_val);
        (yyval.expression) = create_literal_expr(val, INTEGER_LITERAL);
    }
#line 2001 "sql_parser.tab.c"
    break;

  case 89: /* literal: DECIMAL_LITERAL  */
#line 393 "src/yacc/sql_parser.y"
                      {
        literal_value_t val;
        val.float_val = (yyvsp[0].float_val);
        (yyval.expression) = create_literal_expr(val, DECIMAL_LITERAL);
    }
#line 2011 "sql_parser.tab.c"
    break;

  case 90: /* literal: STRING_LITERAL  */
#line 398 "src/yacc/sql_parser.y"
                     {
        literal_value_t val;
        val.string_val = (yyvsp[0].string_val);
        (yyval.expression) = create_literal_expr(val, STRING_LITERAL);
    }
#line 2021 "sql_parser.tab.c"
    break;

  case 91: /* literal: NULL_TOK  */
#line 403 "src/yacc/sql_parser.y"
               {
        literal_value_t val;
        val.string_val = NULL;
        (yyval.expression) = create_literal_expr(val, NULL_TOK);
    }
#line 2031 "sql_parser.tab.c"
    break;

  case 92: /* literal: TRUE_TOK  */
#line 408 "src/yacc/sql_parser.y"
               {
        literal_value_t val;
        val.int_val = 1;
        (yyval.expression) = create_literal_expr(val, TRUE_TOK);
    }
#line 2041 "sql_parser.tab.c"
    break;

  case 93: /* literal: FALSE_TOK  */
#line 413 "src/yacc/sql_parser.y"
                {
        literal_value_t val;
        val.int_val = 0;
        (yyval.expression) = create_literal_expr(val, FALSE_TOK);
    }
#line 2051 "sql_parser.tab.c"
    break;

  case 94: /* column_reference: IDENTIFIER  */
#line 421 "src/yacc/sql_parser.y"
               {
        (yyval.expression) = create_identifier_expr((yyvsp[0].string_val));
    }
#line 2059 "sql_parser.tab.c"
    break;

  case 95: /* column_reference: IDENTIFIER DOT IDENTIFIER  */
#line 424 "src/yacc/sql_parser.y"
                                {
        (yyval.expression) = create_column_ref_expr((yyvsp[-2].string_val), (yyvsp[0].string_val));
    }
#line 2067 "sql_parser.tab.c"
    break;

  case 96: /* function_call: IDENTIFIER LPAREN RPAREN  */
#line 430 "src/yacc/sql_parser.y"
                             {
        (yyval.expression) = create_function_call_expr((yyvsp[-2].string_val), NULL, 0);
    }
#line 2075 "sql_parser.tab.c"
    break;

  case 97: /* function_call: IDENTIFIER LPAREN value_list RPAREN  */
#line 433 "src/yacc/sql_parser.y"
                                          {
        /* Convert value_list to expression array */
        int count = 0;
        value_list_t* current = (yyvsp[-1].value_list);
        while (current) {
            count++;
            current = current->next;
        }
        
        expression_t** args = malloc(count * sizeof(expression_t*));
        current = (yyvsp[-1].value_list);
        for (int i = 0; i < count; i++) {
            args[i] = current->value;
            current = current->next;
        }
        
        (yyval.expression) = create_function_call_expr((yyvsp[-3].string_val), args, count);
    }
#line 2098 "sql_parser.tab.c"
    break;

  case 98: /* function_call: COUNT LPAREN MULTIPLY RPAREN  */
#line 451 "src/yacc/sql_parser.y"
                                   {
        (yyval.expression) = create_function_call_expr("COUNT", NULL, 0);
    }
#line 2106 "sql_parser.tab.c"
    break;

  case 99: /* function_call: COUNT LPAREN expression RPAREN  */
#line 454 "src/yacc/sql_parser.y"
                                     {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = (yyvsp[-1].expression);
        (yyval.expression) = create_function_call_expr("COUNT", args, 1);
    }
#line 2116 "sql_parser.tab.c"
    break;

  case 100: /* function_call: SUM LPAREN expression RPAREN  */
#line 459 "src/yacc/sql_parser.y"
                                   {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = (yyvsp[-1].expression);
        (yyval.expression) = create_function_call_expr("SUM", args, 1);
    }
#line 2126 "sql_parser.tab.c"
    break;

  case 101: /* function_call: AVG LPAREN expression RPAREN  */
#line 464 "src/yacc/sql_parser.y"
                                   {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = (yyvsp[-1].expression);
        (yyval.expression) = create_function_call_expr("AVG", args, 1);
    }
#line 2136 "sql_parser.tab.c"
    break;

  case 102: /* function_call: MIN LPAREN expression RPAREN  */
#line 469 "src/yacc/sql_parser.y"
                                   {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = (yyvsp[-1].expression);
        (yyval.expression) = create_function_call_expr("MIN", args, 1);
    }
#line 2146 "sql_parser.tab.c"
    break;

  case 103: /* function_call: MAX LPAREN expression RPAREN  */
#line 474 "src/yacc/sql_parser.y"
                                   {
        expression_t** args = malloc(sizeof(expression_t*));
        args[0] = (yyvsp[-1].expression);
        (yyval.expression) = create_function_call_expr("MAX", args, 1);
    }
#line 2156 "sql_parser.tab.c"
    break;


#line 2160 "sql_parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 481 "src/yacc/sql_parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s near '%s'\n", yylineno, s, yytext);
}
