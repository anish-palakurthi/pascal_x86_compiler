/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parse.y"
     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 30 Jul 13   */

/* Copyright (c) 2013 Gordon S. Novak Jr. and
   The University of Texas at Austin. */


/* 14 Feb 01; 01 Oct 04; 02 Mar 07; 27 Feb 08; 24 Jul 09; 02 Aug 12 */

/*
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.

; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.

; You should have received a copy of the GNU General Public License
; along with this program; if not, see <http://www.gnu.org/licenses/>.
  */


/* NOTE:   Copy your lexan.l lexical analyzer to this directory.      */

       /* To use:
                     make pars1y              has 1 shift/reduce conflict
                     pars1y                   execute the parser
                     i:=j .
                     ^D                       control-D to end input

                     pars1y                   execute the parser
                     begin i:=j; if i+j then x:=a+b*c else x:=a*b+c; k:=i end.
                     ^D

                     pars1y                   execute the parser
                     if x+y then if y+z then i:=j else k:=2.
                     ^D

           You may copy pars1.y to be parse.y and extend it for your
           assignment.  Then use   make parser   as above.
        */

        /* Yacc reports 1 shift/reduce conflict, due to the ELSE part of
           the IF statement, but Yacc's default resolves it in the right way.*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexan.h"
#include "symtab.h"
#include "parse.h"

        /* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN

TOKEN parseresult;


#line 133 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    STRING = 259,
    NUMBER = 260,
    PLUS = 261,
    MINUS = 262,
    TIMES = 263,
    DIVIDE = 264,
    ASSIGN = 265,
    EQ = 266,
    NE = 267,
    LT = 268,
    LE = 269,
    GE = 270,
    GT = 271,
    POINT = 272,
    DOT = 273,
    AND = 274,
    OR = 275,
    NOT = 276,
    DIV = 277,
    MOD = 278,
    IN = 279,
    COMMA = 280,
    SEMICOLON = 281,
    COLON = 282,
    LPAREN = 283,
    RPAREN = 284,
    LBRACKET = 285,
    RBRACKET = 286,
    DOTDOT = 287,
    ARRAY = 288,
    BEGINBEGIN = 289,
    CASE = 290,
    CONST = 291,
    DO = 292,
    DOWNTO = 293,
    ELSE = 294,
    END = 295,
    FILEFILE = 296,
    FOR = 297,
    FUNCTION = 298,
    GOTO = 299,
    IF = 300,
    LABEL = 301,
    NIL = 302,
    OF = 303,
    PACKED = 304,
    PROCEDURE = 305,
    PROGRAM = 306,
    RECORD = 307,
    REPEAT = 308,
    SET = 309,
    THEN = 310,
    TO = 311,
    TYPE = 312,
    UNTIL = 313,
    VAR = 314,
    WHILE = 315,
    WITH = 316
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define STRING 259
#define NUMBER 260
#define PLUS 261
#define MINUS 262
#define TIMES 263
#define DIVIDE 264
#define ASSIGN 265
#define EQ 266
#define NE 267
#define LT 268
#define LE 269
#define GE 270
#define GT 271
#define POINT 272
#define DOT 273
#define AND 274
#define OR 275
#define NOT 276
#define DIV 277
#define MOD 278
#define IN 279
#define COMMA 280
#define SEMICOLON 281
#define COLON 282
#define LPAREN 283
#define RPAREN 284
#define LBRACKET 285
#define RBRACKET 286
#define DOTDOT 287
#define ARRAY 288
#define BEGINBEGIN 289
#define CASE 290
#define CONST 291
#define DO 292
#define DOWNTO 293
#define ELSE 294
#define END 295
#define FILEFILE 296
#define FOR 297
#define FUNCTION 298
#define GOTO 299
#define IF 300
#define LABEL 301
#define NIL 302
#define OF 303
#define PACKED 304
#define PROCEDURE 305
#define PROGRAM 306
#define RECORD 307
#define REPEAT 308
#define SET 309
#define THEN 310
#define TO 311
#define TYPE 312
#define UNTIL 313
#define VAR 314
#define WHILE 315
#define WITH 316

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

#define YYUNDEFTOK  2
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    82,    82,    85,    86,    89,    91,    92,    94,    95,
      96,    97,    98,   100,   102,   103,   105,   106,   108,   110,
     111,   113,   115,   116,   118,   119,   121,   122,   124,   125,
     127,   128,   130,   131,   133,   135,   136,   137,   138,   141,
     142,   144,   145,   146,   149,   151,   152,   153,   154,   155,
     156,   158,   159,   160,   162,   164,   165,   167,   168,   170,
     173,   174,   176,   177,   180,   181,   182,   183,   186,   187,
     190,   191,   194,   195,   196,   197,   198,   199,   200,   201,
     204,   205,   208,   209,   210,   211,   212,   213,   215,   216,
     217,   218,   219,   220,   221
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "NUMBER", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "ASSIGN", "EQ", "NE", "LT", "LE", "GE", "GT",
  "POINT", "DOT", "AND", "OR", "NOT", "DIV", "MOD", "IN", "COMMA",
  "SEMICOLON", "COLON", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "DOTDOT", "ARRAY", "BEGINBEGIN", "CASE", "CONST", "DO", "DOWNTO", "ELSE",
  "END", "FILEFILE", "FOR", "FUNCTION", "GOTO", "IF", "LABEL", "NIL", "OF",
  "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET", "THEN",
  "TO", "TYPE", "UNTIL", "VAR", "WHILE", "WITH", "$accept", "program",
  "idlist", "cdef", "clist", "constant", "tdef", "tlist", "statementList",
  "fieldsList", "multiFieldsList", "label", "labelsList", "lblock",
  "cblock", "tblock", "vblock", "varspecs", "vargroup", "type",
  "basicList", "basicType", "block", "statement", "functionCall",
  "endpart", "endif", "assignment", "variable", "signedExpression",
  "signedTerm", "sign", "expr", "expressionList", "term", "factor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316
};
# endif

#define YYPACT_NINF (-153)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-10)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -30,    22,    32,    10,  -153,    44,    38,    39,    44,    43,
    -153,   141,    12,    85,    91,    87,    44,    94,  -153,  -153,
    -153,  -153,    93,    92,   139,   143,   126,    12,   126,  -153,
    -153,    98,  -153,  -153,   178,   135,   123,     1,   125,   127,
     140,   129,   -23,   130,   122,   132,  -153,   126,    12,  -153,
     104,  -153,  -153,  -153,  -153,  -153,   131,   126,  -153,  -153,
      49,    80,  -153,   131,    37,   118,  -153,   128,   150,    69,
      12,  -153,  -153,   126,  -153,   182,   126,    24,    85,  -153,
      91,    86,   111,    87,  -153,   111,  -153,    44,   204,   160,
    -153,   126,  -153,   198,   131,   131,   131,   118,   126,   126,
     126,   126,   126,   126,   126,    12,   131,   131,   131,   131,
     131,   126,    12,    12,    98,   219,  -153,   159,  -153,  -153,
    -153,  -153,    17,  -153,  -153,  -153,   162,   188,    44,   167,
      44,   169,  -153,  -153,  -153,  -153,  -153,   126,  -153,   168,
    -153,   118,   118,   118,    80,    80,    80,    80,    80,    80,
      80,   163,  -153,  -153,  -153,  -153,  -153,   219,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,   170,   165,   176,   180,   164,
      24,  -153,    12,    12,  -153,  -153,   190,   199,   111,    44,
    -153,  -153,  -153,  -153,   175,   165,  -153,  -153,   111,  -153,
    -153
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     4,     0,     0,     0,
       3,     0,     0,     0,     0,     0,     0,     0,    25,    27,
      29,    31,    60,     0,     0,     0,     0,     0,     0,    53,
      45,     0,    48,    47,     0,     0,     0,     0,    23,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     0,    60,
       0,    51,    89,    90,    70,    71,     0,     0,    91,    92,
      88,    79,    64,     0,     0,    69,    87,     0,    17,     0,
       0,    56,    44,     0,    62,     0,     0,     0,     7,    26,
       0,     0,     0,    15,    28,     0,    30,    33,    81,     0,
      21,     0,    94,     0,     0,     0,     0,    68,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    59,    63,     0,     9,    12,
      11,     5,     0,     6,    22,    24,    41,     0,     0,     0,
       0,     0,    13,    35,    14,    34,    32,     0,    54,     0,
      93,    65,    66,    67,    72,    75,    73,    76,    77,    74,
      78,    58,    82,    83,    84,    85,    86,    50,    16,    52,
      55,    61,     8,    10,    36,     0,     0,     0,    20,     0,
       0,    80,     0,     0,    46,    43,     0,    40,     0,     0,
      38,    42,    49,    57,     0,     0,    18,    19,     0,    39,
      37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,    -5,  -153,   147,   -59,  -153,   124,   114,  -153,
      65,  -153,   166,  -153,   171,   208,   205,   161,  -153,   -80,
      64,  -152,    -3,    -6,    -8,   136,  -153,   227,   -11,   138,
    -153,   -75,    -2,   -67,   -51,   -33
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    43,    36,    37,   131,    41,    42,    67,   168,
     169,    29,    39,    17,    18,    19,    20,    44,    45,   132,
     176,   133,    30,    68,    59,    72,   174,    33,    60,    61,
      62,    63,    88,    89,    65,    66
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    34,   122,    10,    32,   135,    31,   122,    21,   117,
     122,    12,    97,    34,   177,    22,    34,    23,   121,    32,
     162,     1,   163,    92,    64,     3,    69,   118,   119,   120,
      54,    55,     4,   177,    21,    12,    16,    34,     5,    21,
      32,    86,    90,   141,   142,   143,    12,     6,    98,    99,
     100,   101,   102,   103,    24,    93,    25,    26,    15,    34,
      16,   104,    32,     8,   114,    27,    74,    75,     9,    11,
     171,   115,    28,   152,   153,   154,   155,   156,    21,    76,
      98,    99,   100,   101,   102,   103,    94,    95,    35,   139,
      40,   122,   105,   104,    34,   122,    38,    32,   186,   151,
      96,    34,    34,   122,    32,    32,   113,   159,   190,   157,
     122,   181,    46,   122,   126,   119,   120,    54,    55,    48,
      12,    47,    13,   165,    70,   167,   106,   107,   127,    22,
      52,    53,    54,    55,    22,    52,    53,   108,    71,   128,
     109,   110,    49,    15,   129,    16,    77,    56,    51,    78,
      80,    82,    56,    81,    57,    83,    12,    85,    87,    57,
      91,    34,    34,   130,    32,    32,   182,   183,   126,   119,
     120,    54,    55,    58,   167,    12,   112,    13,    58,    98,
      99,   100,   101,   102,   103,   116,   111,    14,    73,   138,
     161,   164,   104,   128,    -9,    74,    75,   166,    15,   175,
      16,   170,   173,   178,   180,   172,   179,   134,    76,    98,
      99,   100,   101,   102,   103,    98,    99,   100,   101,   102,
     103,   184,   104,   188,   185,   123,   158,   140,   104,   137,
      98,    99,   100,   101,   102,   103,   144,   145,   146,   147,
     148,   149,   150,   104,   187,    79,   124,    84,   136,   189,
     160,    50,   125
};

static const yytype_uint8 yycheck[] =
{
       5,    12,    77,     8,    12,    85,    12,    82,    11,    76,
      85,    34,    63,    24,   166,     3,    27,     5,    77,    27,
       3,    51,     5,    56,    26,     3,    28,     3,     4,     5,
       6,     7,     0,   185,    37,    34,    59,    48,    28,    42,
      48,    44,    48,    94,    95,    96,    34,     3,    11,    12,
      13,    14,    15,    16,    42,    57,    44,    45,    57,    70,
      59,    24,    70,    25,    70,    53,    17,    18,    29,    26,
     137,    73,    60,   106,   107,   108,   109,   110,    81,    30,
      11,    12,    13,    14,    15,    16,     6,     7,     3,    91,
       3,   166,    55,    24,   105,   170,     5,   105,   178,   105,
      20,   112,   113,   178,   112,   113,    37,   113,   188,   111,
     185,   170,    18,   188,     3,     4,     5,     6,     7,    27,
      34,    28,    36,   128,    26,   130,     8,     9,    17,     3,
       4,     5,     6,     7,     3,     4,     5,    19,    40,    28,
      22,    23,     3,    57,    33,    59,    11,    21,     5,    26,
      25,    11,    21,    26,    28,    26,    34,    27,    26,    28,
      56,   172,   173,    52,   172,   173,   172,   173,     3,     4,
       5,     6,     7,    47,   179,    34,    26,    36,    47,    11,
      12,    13,    14,    15,    16,     3,    58,    46,    10,    29,
      31,     3,    24,    28,    32,    17,    18,    30,    57,    29,
      59,    32,    39,    27,    40,    37,    26,    83,    30,    11,
      12,    13,    14,    15,    16,    11,    12,    13,    14,    15,
      16,    31,    24,    48,    25,    78,   112,    29,    24,    25,
      11,    12,    13,    14,    15,    16,    98,    99,   100,   101,
     102,   103,   104,    24,   179,    37,    80,    42,    87,   185,
     114,    24,    81
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    63,     3,     0,    28,     3,    64,    25,    29,
      64,    26,    34,    36,    46,    57,    59,    75,    76,    77,
      78,    84,     3,     5,    42,    44,    45,    53,    60,    73,
      84,    85,    86,    89,    90,     3,    65,    66,     5,    74,
       3,    68,    69,    64,    79,    80,    18,    28,    27,     3,
      89,     5,     4,     5,     6,     7,    21,    28,    47,    86,
      90,    91,    92,    93,    94,    96,    97,    70,    85,    94,
      26,    40,    87,    10,    17,    18,    30,    11,    26,    77,
      25,    26,    11,    26,    78,    27,    84,    26,    94,    95,
      85,    56,    97,    94,     6,     7,    20,    96,    11,    12,
      13,    14,    15,    16,    24,    55,     8,     9,    19,    22,
      23,    58,    26,    37,    85,    94,     3,    95,     3,     4,
       5,    67,    93,    66,    74,    76,     3,    17,    28,    33,
      52,    67,    81,    83,    69,    81,    79,    25,    29,    94,
      29,    96,    96,    96,    91,    91,    91,    91,    91,    91,
      91,    85,    97,    97,    97,    97,    97,    94,    70,    85,
      87,    31,     3,     5,     3,    64,    30,    64,    71,    72,
      32,    95,    37,    39,    88,    29,    82,    83,    27,    26,
      40,    67,    85,    85,    31,    25,    81,    72,    48,    82,
      81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    66,    66,    67,    67,
      67,    67,    67,    68,    69,    69,    70,    70,    71,    72,
      72,    73,    74,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    80,    81,    81,    81,    81,    82,
      82,    83,    83,    83,    84,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    86,    87,    87,    88,    88,    89,
      90,    90,    90,    90,    91,    91,    91,    91,    92,    92,
      93,    93,    94,    94,    94,    94,    94,    94,    94,    94,
      95,    95,    96,    96,    96,    96,    96,    96,    97,    97,
      97,    97,    97,    97,    97
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     3,     1,     3,     3,     2,     2,     1,
       2,     1,     1,     3,     3,     2,     3,     1,     3,     3,
       1,     3,     3,     1,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     3,     1,     2,     6,     3,     3,
       1,     1,     3,     3,     3,     1,     5,     1,     1,     6,
       4,     2,     4,     1,     4,     3,     1,     2,     0,     3,
       1,     4,     2,     3,     1,     3,     3,     3,     2,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 82 "parse.y"
                                                                            { parseresult = makeprogram(yyvsp[-6], yyvsp[-4], yyvsp[-1]); }
#line 1625 "y.tab.c"
    break;

  case 3:
#line 85 "parse.y"
                                        { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1631 "y.tab.c"
    break;

  case 4:
#line 86 "parse.y"
                              { yyval = cons(yyvsp[0], NULL); }
#line 1637 "y.tab.c"
    break;

  case 5:
#line 89 "parse.y"
                                       { instconst(yyvsp[-2], yyvsp[0]); }
#line 1643 "y.tab.c"
    break;

  case 8:
#line 94 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1649 "y.tab.c"
    break;

  case 10:
#line 96 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1655 "y.tab.c"
    break;

  case 13:
#line 100 "parse.y"
                                       { insttype(yyvsp[-2], yyvsp[0]); }
#line 1661 "y.tab.c"
    break;

  case 16:
#line 105 "parse.y"
                                                              { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1667 "y.tab.c"
    break;

  case 17:
#line 106 "parse.y"
                                           { yyval = cons(yyvsp[0], NULL); }
#line 1673 "y.tab.c"
    break;

  case 18:
#line 108 "parse.y"
                                                  { yyval = instfields(yyvsp[-2], yyvsp[0]); }
#line 1679 "y.tab.c"
    break;

  case 19:
#line 110 "parse.y"
                                                            { yyval = nconc(yyvsp[-2], yyvsp[0]); }
#line 1685 "y.tab.c"
    break;

  case 21:
#line 113 "parse.y"
                                                { yyval = dolabel(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1691 "y.tab.c"
    break;

  case 22:
#line 115 "parse.y"
                                            { instlabel(yyvsp[-2]); }
#line 1697 "y.tab.c"
    break;

  case 23:
#line 116 "parse.y"
                                      { instlabel(yyvsp[0]); }
#line 1703 "y.tab.c"
    break;

  case 24:
#line 118 "parse.y"
                                                   { yyval = yyvsp[0]; }
#line 1709 "y.tab.c"
    break;

  case 26:
#line 121 "parse.y"
                                                { yyval = yyvsp[0]; }
#line 1715 "y.tab.c"
    break;

  case 28:
#line 124 "parse.y"
                                        { yyval = yyvsp[0]; }
#line 1721 "y.tab.c"
    break;

  case 30:
#line 127 "parse.y"
                                         { yyval = yyvsp[0]; }
#line 1727 "y.tab.c"
    break;

  case 34:
#line 133 "parse.y"
                                  { instvars(yyvsp[-2], yyvsp[0]); }
#line 1733 "y.tab.c"
    break;

  case 36:
#line 136 "parse.y"
                                                              { yyval = instpoint(yyvsp[-1], yyvsp[0]); }
#line 1739 "y.tab.c"
    break;

  case 37:
#line 137 "parse.y"
                                                            { yyval = instarray(yyvsp[-3], yyvsp[0]); }
#line 1745 "y.tab.c"
    break;

  case 38:
#line 138 "parse.y"
                                                                    { yyval = instrec(yyvsp[-2], yyvsp[-1]); }
#line 1751 "y.tab.c"
    break;

  case 39:
#line 141 "parse.y"
                                          { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1757 "y.tab.c"
    break;

  case 40:
#line 142 "parse.y"
                                         { yyval = cons(yyvsp[0], NULL); }
#line 1763 "y.tab.c"
    break;

  case 41:
#line 144 "parse.y"
                            { yyval = findtype(yyvsp[0]); }
#line 1769 "y.tab.c"
    break;

  case 42:
#line 145 "parse.y"
                                             { yyval = instdotdot(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1775 "y.tab.c"
    break;

  case 43:
#line 146 "parse.y"
                                             { yyval = instenum(yyvsp[-1]); }
#line 1781 "y.tab.c"
    break;

  case 44:
#line 149 "parse.y"
                                               { yyval = makeprogn(yyvsp[-2], cons(yyvsp[-1], yyvsp[0])); }
#line 1787 "y.tab.c"
    break;

  case 46:
#line 152 "parse.y"
                                              { yyval = makeif(yyvsp[-4], yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 1793 "y.tab.c"
    break;

  case 49:
#line 155 "parse.y"
                                                     { yyval = makefor(1, yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1799 "y.tab.c"
    break;

  case 50:
#line 156 "parse.y"
                                                            { yyval =
            makerepeat(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1806 "y.tab.c"
    break;

  case 51:
#line 158 "parse.y"
                                            { yyval = dogoto(yyvsp[-1], yyvsp[0]); }
#line 1812 "y.tab.c"
    break;

  case 52:
#line 159 "parse.y"
                                             { yyval = makewhile(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1818 "y.tab.c"
    break;

  case 54:
#line 162 "parse.y"
                                                                { yyval = makefuncall(yyvsp[-2], yyvsp[-3], yyvsp[-1]); }
#line 1824 "y.tab.c"
    break;

  case 55:
#line 164 "parse.y"
                                               { yyval = cons(yyvsp[-1], yyvsp[0]); }
#line 1830 "y.tab.c"
    break;

  case 56:
#line 165 "parse.y"
                                               { yyval = NULL; }
#line 1836 "y.tab.c"
    break;

  case 57:
#line 167 "parse.y"
                                               { yyval = yyvsp[0]; }
#line 1842 "y.tab.c"
    break;

  case 58:
#line 168 "parse.y"
                                               { yyval = NULL; }
#line 1848 "y.tab.c"
    break;

  case 59:
#line 170 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1854 "y.tab.c"
    break;

  case 60:
#line 173 "parse.y"
                                                      { yyval = findid(yyvsp[0]); }
#line 1860 "y.tab.c"
    break;

  case 61:
#line 174 "parse.y"
                                                            { yyval = arrayref(yyvsp[-3], yyvsp[-2],
             yyvsp[-1], yyvsp[0]); }
#line 1867 "y.tab.c"
    break;

  case 62:
#line 176 "parse.y"
                                                       { yyval = dopoint(yyvsp[-1], yyvsp[0]); }
#line 1873 "y.tab.c"
    break;

  case 63:
#line 177 "parse.y"
                                                       { yyval = reducedot(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1879 "y.tab.c"
    break;

  case 65:
#line 181 "parse.y"
                                                           { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1885 "y.tab.c"
    break;

  case 66:
#line 182 "parse.y"
                                                            { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1891 "y.tab.c"
    break;

  case 67:
#line 183 "parse.y"
                                                         { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1897 "y.tab.c"
    break;

  case 68:
#line 186 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1903 "y.tab.c"
    break;

  case 72:
#line 194 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1909 "y.tab.c"
    break;

  case 73:
#line 195 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1915 "y.tab.c"
    break;

  case 74:
#line 196 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1921 "y.tab.c"
    break;

  case 75:
#line 197 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1927 "y.tab.c"
    break;

  case 76:
#line 198 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1933 "y.tab.c"
    break;

  case 77:
#line 199 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1939 "y.tab.c"
    break;

  case 78:
#line 200 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1945 "y.tab.c"
    break;

  case 80:
#line 204 "parse.y"
                                                         { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1951 "y.tab.c"
    break;

  case 81:
#line 205 "parse.y"
                                            { yyval = cons(yyvsp[0], NULL); }
#line 1957 "y.tab.c"
    break;

  case 82:
#line 208 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1963 "y.tab.c"
    break;

  case 83:
#line 209 "parse.y"
                                                { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1969 "y.tab.c"
    break;

  case 84:
#line 210 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1975 "y.tab.c"
    break;

  case 85:
#line 211 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1981 "y.tab.c"
    break;

  case 86:
#line 212 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1987 "y.tab.c"
    break;

  case 93:
#line 220 "parse.y"
                                               { yyval = yyvsp[-1]; }
#line 1993 "y.tab.c"
    break;

  case 94:
#line 221 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1999 "y.tab.c"
    break;


#line 2003 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 222 "parse.y"


/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.
  */

#define DEBUG           0             /* set bits here for debugging, 0 = off  */
#define DB_CONS         0             /* bit to trace cons */
#define DB_BINOP        0             /* bit to trace binop */
#define DB_MAKEIF       0             /* bit to trace makeif */
#define DB_MAKEPROGN    0             /* bit to trace makeprogn */
#define DB_PARSERES     0             /* bit to trace parseresult */
#define DB_MAKEPROGRAM  0
#define DB_MAKEINTC     0
#define DB_MAKELABEL    0
#define DB_MAKEOP       0
#define DB_MAKECOPY     0
#define DB_MAKEGOTO     0
#define DB_MAKEFOR      0
#define DB_MAKEWHILE    0
#define DB_MAKEFUNCALL  0
#define DB_UNOP         0
#define DB_FINDID       0  
#define DB_INSTCONST    0  
#define DB_INSTLABEL    0   
#define DB_FINDLABEL    0 
#define DB_FINDTYPE     0 
#define DB_REDUCEDOT    1
#define DB_ARRAYREF     1
#define DB_MAKEREPEAT   0
#define DB_MAKESUB      0
#define DB_MAKEAREF     1
#define DB_DOLABEL      0
#define DB_DOGOTO       0
#define DB_DOPOINT      0
#define DB_INSTTYPE     0
#define DB_INSTENUM     0
#define DB_INSTDOTDOT   0
#define DB_INSTARRAY    0
#define DB_INSTFIELD    0
#define DB_NCONC        0
#define DB_INSTREC      0
#define DB_INSTPOINT    0

 int labelnumber = 0; 
 int labels[50];

   /*  Note: you should add to the above values and insert debugging
       printouts in your routines similar to those that are shown here.     */

TOKEN cons(TOKEN item, TOKEN list)            /* add item to front of list */
  { item->link = list;
    if (DEBUG & DB_CONS)
       { printf("cons\n");
         dbugprinttok(item);
         dbugprinttok(list);
       };
    return item;
  }


/* nconc concatenates two token lists, destructively, by making the last link
   of lista point to listb.
   (nconc '(a b) '(c d e))  =  (a b c d e)  */
/* nconc is useful for putting together two fieldlist groups to
   make them into a single list in a record declaration. */
TOKEN nconc(TOKEN lista, TOKEN listb) {
  TOKEN temp = lista;
  while(temp->link) {
    temp = temp->link;
  }
  temp->link = listb;
  if (DEBUG & DB_NCONC) {
   printf("nconc\n");
   dbugprinttok(temp);
  };
  return temp;
}

int  checkReal(TOKEN tok) {
  return (tok->basicdt == REAL);

}

int checkInt(TOKEN tok) {
  return (tok->basicdt == INTEGER);

}


/* unaryop links a unary operator op to one operand, lhs */
TOKEN unaryop(TOKEN op, TOKEN lhs) {
  op->operands = lhs;
  lhs->link = NULL;
  if (DEBUG & DB_UNOP)
     { printf("unaryop\n");
       dbugprinttok(op);
       dbugprinttok(lhs);
     };
  return op;  
}



/* binop links a binary operator op to two operands, lhs and rhs. */
TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs){ 
    
    if (lhs->tokentype == NUMBERTOK){

    lhs->link = rhs;             
    rhs->link = NULL;           
    op->operands = lhs; 

    //handles type casting
    int lhType;
    int rhType;

    //define our variables for specifying type
    if (lhs->basicdt == INTEGER) {
      lhType = 1;
    } else {
      //REAL
      lhType = 0;
    }
    if (rhs->basicdt == INTEGER) {
      rhType = 1;
    } else {
      //REAL
      rhType = 0;
    }

    //left hand = integer; right hand = float
    if (lhType == 1 && rhType == 0) {


      TOKEN temptoken = talloc();

      // computation operation
      if (op->whichval != ASSIGNOP){

        op->basicdt = REAL;
        TOKEN temptoken = makefloat(lhs);
        temptoken->link = rhs;
      }

      // assignment operation
      else{
        op->basicdt = INTEGER;
        TOKEN temptoken = makefix(rhs);
        lhs->link = temptoken;
      }
    }

    //both real
    else if (lhType == 0 && rhType == 0) {
      op->basicdt = REAL;
    }

    //left hand = int; right hand = real
    else if (lhType == 0 && rhType == 1) {
      TOKEN floatToken = makefloat(rhs);
      lhs->link = floatToken;
      op->basicdt = REAL;

    }

    //nothing needed for both int

    //deciding what to set op datatype to
    if (DEBUG & DB_BINOP)
       { printf("binop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
         dbugprinttok(rhs);
       };
    
    return op;
    }
      if (rhs->whichval == (NIL - RESERVED_BIAS)) {
        rhs = makeintc(0);
    }

    op->operands = lhs; // Link operands to operator.
    lhs->link = rhs; // Link second operand to first.
    rhs->link = NULL; // Terminate operand list.



      // Existing logic
      if (checkReal(lhs) && checkReal(rhs)) {
          op->basicdt = REAL;
      } else if (checkReal(lhs) && checkInt(rhs)) {
          op->basicdt = REAL;
          TOKEN ftok = makefloat(rhs);
          lhs->link = ftok;
      } else if (checkInt(lhs) && checkReal(rhs)) {
          if (op->whichval == ASSIGNOP) {
              op->basicdt = INTEGER;
          } else {
              op->basicdt = REAL;
          }
      }
    

    if (DEBUG & DB_BINOP) {
        printf("binop - final type handling\n");
        dbugprinttok(op);
    }

    return op;
    }


/* makefloat forces the item tok to be floating, by floating a constant
   or by inserting a FLOATOP operator */
TOKEN makefloat(TOKEN tok) {
  if(tok->tokentype == NUMBERTOK) {
    tok->basicdt = REAL;
    tok->realval = (double) tok->intval;
    return tok;
  } else {
    TOKEN floatop = makeop(FLOATOP);
    floatop->operands = tok;
    return floatop;
  }
  
}


/* makefix forces the item tok to be integer, by truncating a constant
   or by inserting a FIXOP operator */
TOKEN makefix(TOKEN tok) {
  if(tok->tokentype == NUMBERTOK) {
    tok->basicdt = INTEGER;
    tok->intval = (int) tok->realval;
    // printf("was numbertoken so truncated\n");
    return tok;
  } else { 
    TOKEN fixop = makeop(FIXOP);
    fixop->operands = tok;
    return fixop;
  }
}



/* makeop makes a new operator token with operator number opnum.
   Example:  makeop(FLOATOP)  */
TOKEN makeop(int op){
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = op;
    if (DEBUG & DB_MAKEOP) {
      printf("makeop\n");
      dbugprinttok(tok);
    }
    return tok;
}

/* copytok makes a new token that is a copy of origtok */
TOKEN copytok(TOKEN target) {
  TOKEN copy = talloc();
  copy->tokentype = target->tokentype;
  copy->basicdt = target->basicdt;
  copy->symtype = target->symtype;
  copy->symentry = target->symentry;
  copy->link = target->link;
  for (int i = 0; i < 16; i++){
    copy->stringval[i] = target->stringval[i];
  }
  
  if (DEBUG & DB_MAKECOPY) {
    printf("copytok\n");
    dbugprinttok(copy);
  }
  return copy;
}

TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  tok->tokentype = OPERATOR;  /* Make it look like an operator   */
     tok->whichval = IFOP;
     if (elsepart != NULL) elsepart->link = NULL;
     thenpart->link = elsepart;
     exp->link = thenpart;
     tok->operands = exp;
     if (DEBUG & DB_MAKEIF)
        { printf("makeif\n");
          dbugprinttok(tok);
          dbugprinttok(exp);
          dbugprinttok(thenpart);
          dbugprinttok(elsepart);
        };
     return tok;
   }

/* makeintc makes a new token with num as its value */
TOKEN makeintc(int number) {
  TOKEN tok = talloc();
  tok->tokentype = NUMBERTOK;
  tok->basicdt = INTEGER;
  tok->intval = number;
  if (DEBUG & DB_MAKEINTC) {
      printf("makeintc\n");
      dbugprinttok(tok);
  }
  return tok;
}

/* makelabel makes a new label, using labelnumber++ */
TOKEN makelabel() {
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = LABELOP;
  tok->operands = makeintc(labelnumber++);
  if (DEBUG & DB_MAKELABEL) {
      printf("makelabel\n");
      dbugprinttok(tok);
  }
  return tok;
}

/* makegoto makes a GOTO operator to go to the specified label.
   The label number is put into a number token. */
TOKEN makegoto(int num){
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = GOTOOP;
  tok->operands = makeintc(num);
  if (DEBUG && DB_MAKEGOTO) {
      printf("makegoto\n");
      dbugprinttok(tok);
  }
  return tok;
}


TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok){
  
  TOKEN finalOffset = off; // Start with the assumption we'll use the provided offset

  if (var->link){
    
    if (var->link->tokentype == NUMBERTOK){
    finalOffset->intval = var->link->intval + off->intval;
    }
    else if(var->link->tokentype == IDENTIFIERTOK){
      TOKEN plusop = makeop(PLUSOP);
      plusop->operands = var->link;
      plusop->link = off;
      finalOffset = plusop;
      finalOffset->tokentype = IDENTIFIERTOK;
    }
    
  }

  if (var->whichval == AREFOP && off->basicdt == INTEGER) {
    
    TOKEN off1 = var->operands->link;
    if (off1->tokentype == NUMBERTOK) { // Assuming off1 is the offset in the nested AREF
      // Directly sum the integer values of the offsets
      int sumOffsets = off1->intval + off->intval;
      finalOffset = makeintc(sumOffsets); // Use this new offset for the final AREF
    }
  }

  // Now, we create the AREF operation using the possibly updated finalOffset
  TOKEN areftok = makeop(AREFOP);
  if (var->whichval == AREFOP) { // If nesting was detected, link directly to the array part of the nested AREF
    if(var->link == NULL || var->link->tokentype != IDENTIFIERTOK){
      var = var->operands;

    }
  }

  if (finalOffset != 0){
    var->link = finalOffset; // Link the final offset

  }

  if (var->link->tokentype == IDENTIFIERTOK){
    return var;
  }
  else{
    areftok->operands = var;
  }
  
  areftok->symtype = var->symtype;
  
  if (var->symtype && var->symtype->datatype) {
    areftok->basicdt = var->symtype->datatype->basicdt;
  }

  if (DEBUG && DB_MAKEAREF) {
      printf("makearef - possibly merged\n");
      dbugprinttok(areftok);
  }

  return areftok;
}



/* makefor makes structures for a for statement.
   sign is 1 for normal loop, -1 for downto.
   asg is an assignment statement, e.g. (:= i 1)
   endexpr is the end expression
   tok, tokb and tokc are (now) unused tokens that are recycled. */
TOKEN makefor(int sign, TOKEN tok, TOKEN assign, TOKEN tokb, TOKEN expr, TOKEN tokc, TOKEN statements) {
    // Initial assignment
    tok = makeprogn(tok, assign);

    // Setting up the loop label token
    TOKEN loopLabel = makelabel();


    // Linking the loop initialization to the label
    assign->link = loopLabel;

    // build loop body's statements tree
    TOKEN loopBody = talloc();
    loopBody = makeprogn(loopBody, statements);

    // Creating the conditional check for the loop
    TOKEN leOperator = makeop(LEOP);
    TOKEN conditional = talloc();
    conditional = makeif(conditional, leOperator, loopBody, NULL);

    // Handling the loop variable and its increment
    TOKEN varCopy = copytok(assign->operands);
    varCopy->link = expr;
    leOperator->operands = varCopy;

    TOKEN incrementStep = copytok(varCopy);
    TOKEN incrementVar = copytok(varCopy);

    TOKEN incrementOp = makeplus(NULL, NULL, NULL);
    TOKEN incrementAssign = makeop(ASSIGNOP);

    incrementOp->operands = incrementStep;
    incrementVar->link = incrementOp;
    incrementStep->link = makeintc(1);
    incrementAssign->operands = incrementVar;

    // Setting up the goto operation for loop continuation
    TOKEN gotoOperation = makegoto(labelnumber - 1);

    // Linking the increment operation and the goto for the loop's next iteration
    statements->link = incrementAssign;
    incrementAssign->link = gotoOperation;

    // Final assembly of the loop's conditional and body components
    loopLabel->link = conditional;
    leOperator->link = loopBody;
    conditional->operands = leOperator;

    // Debugging output, if enabled
    if (DEBUG && DB_MAKEFOR) {
        dbugprinttok(tok);
    }

    return tok;
}
/* makeplus makes a + operator.
  tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makeplus(TOKEN lhs, TOKEN rhs, TOKEN tok) {

	TOKEN ret = makeop(PLUSOP);

  ret->operands = lhs;
  lhs->link = rhs;
  rhs->link = NULL;


	return ret;
}

/* makewhile makes structures for a while statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makewhile(TOKEN tok, TOKEN expr, TOKEN tokb, TOKEN statement) {
  
  TOKEN loopLabel = makelabel();
  tok = makeprogn(tok, loopLabel);

  TOKEN body = makeprogn(tokb, statement);

  TOKEN ifTok = talloc();
  ifTok = makeif(ifTok, expr, body, NULL);
  loopLabel->link = ifTok;

  statement->link = makegoto(labelnumber - 1);


  return tok;
  
}

/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args) {

  
  fn->link = args;
  tok->tokentype = OPERATOR;  
  tok->operands = fn;
  tok->whichval = FUNCALLOP;
  tok->basicdt = args->basicdt;

  if (strcmp(fn->stringval, "writeln") == 0) {
    int argType = args->basicdt;


    int typeIndex = 7; 
    switch (argType) {
        case REAL:
            if (strcmp(fn->stringval, "writeln") == 0) {
                fn->stringval[typeIndex] = 'f';
                fn->stringval[typeIndex + 1] = '\0';
            }
            break;
        case INTEGER:
            if (strcmp(fn->stringval, "writeln") == 0) {
                fn->stringval[typeIndex] = 'i';
                fn->stringval[typeIndex + 1] = '\0';
            }
            break;
        default:
            break;
    }
  }

  else if (strcmp(fn->stringval, "new") == 0) {
    tok = makeop(ASSIGNOP);
    tok->operands = args;

    TOKEN funcOp = makeop(FUNCALLOP);
    fn->link = makeintc(args->symtype->datatype->size);
    funcOp->operands = fn;
    funcOp->basicdt = args->symtype->datatype->basicdt;
    args->link = funcOp;

    return tok;
  } 


     if (DEBUG & DB_MAKEFUNCALL)
        { 
          printf("makefuncall\n");
          dbugprinttok(tok);
          dbugprinttok(fn);
          dbugprinttok(args);
        };
    
    
  return tok;
}

/* makerepeat makes structures for a repeat statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr) {

  //set label token for the start
  TOKEN repeatStart = makelabel();
   
   
   tok = makeprogn(tok, repeatStart);

   //set up the repeat body token
   TOKEN shellBody = makeprogn(tokb, statements);
   repeatStart->link = shellBody;

   //set up the go to token for looping
   TOKEN repeatStartGoTo = makegoto(labelnumber - 1);
   TOKEN filler = makeprogn(talloc(), NULL);
   filler->link = repeatStartGoTo;

   //conditional token
   TOKEN ifs = makeif(talloc(), expr, filler, repeatStartGoTo);
   shellBody->link = ifs;


   return tok;  
}

/* makesubrange makes a SUBRANGE symbol table entry, puts the pointer to it
   into tok, and returns tok. */
TOKEN makesubrange(TOKEN tok, int low, int high) {

  SYMBOL subrange = symalloc();
  subrange->kind = SUBRANGE;
  subrange->basicdt = INTEGER;
  subrange->lowbound = low;
  subrange->highbound = high;
  subrange->size = basicsizes[INTEGER];
  tok->symtype = subrange;

  if (DEBUG & DB_MAKESUB) {
    printf("making subrange\n");
    dbugprinttok(tok);
  }

  return tok;
}


TOKEN makeprogn(TOKEN tok, TOKEN statements)
  {  tok->tokentype = OPERATOR;
     tok->whichval = PROGNOP;
     tok->operands = statements;
     if (DEBUG & DB_MAKEPROGN)
       { printf("makeprogn\n");
         dbugprinttok(tok);
         dbugprinttok(statements);
       };
     return tok;
   }

/* makeprogram makes the tree structures for the top-level program */
TOKEN makeprogram(TOKEN name, TOKEN args, TOKEN statements)
  {
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = PROGRAMOP;
    tok->operands = name;
    
    TOKEN nameArgs = talloc();
    nameArgs = makeprogn(nameArgs, args);
    name->link = nameArgs;
    nameArgs->link = statements;

    if(DEBUG & DB_MAKEPROGRAM){
      printf("makeprogram\n");
      dbugprinttok(tok);
      dbugprinttok(args);
    }
    return tok;
  
  } 


/* findid finds an identifier in the symbol table, sets up symbol table
   pointers, changes a constant to its number equivalent */
TOKEN findid(TOKEN tok) { /* the ID token */
    SYMBOL sym, typ;
    sym = searchst(tok->stringval);
    tok->symentry = sym;
    // tok->symtype = sym;

    
    if (sym->kind == CONSTSYM) {
      if (sym->basicdt == REAL) {
        tok->tokentype = NUMBERTOK;
        tok->basicdt = REAL;
        tok->realval = sym->constval.realnum;
      }
      else if (sym->basicdt == INTEGER) {
        tok->tokentype = NUMBERTOK;
        tok->basicdt = INTEGER;
        tok->intval = sym->constval.intnum;
      }

      if (DEBUG & DB_FINDID) { 
        printf("hit constant\n");
        dbugprinttok(sym);
        dbugprinttok(tok);
      };
      return tok;
    }

    typ = sym->datatype;
    tok->symtype = typ;
    if ( typ->kind == BASICTYPE ||
         typ->kind == POINTERSYM)
        tok->basicdt = typ->basicdt;

    if (DEBUG & DB_FINDID) { 
      printf("hit identifier\n");
      dbugprinttok(sym);
      dbugprinttok(tok);
    };

    return tok;
  }

/* findtype looks up a type name in the symbol table, puts the pointer
   to its type into tok->symtype, returns tok. */

TOKEN findtype(TOKEN tok) {
    SYMBOL sym = searchst(tok->stringval);
    if (sym->kind == TYPESYM) {
      sym = sym->datatype;
   }
    tok->symtype = sym;
    if (DEBUG & DB_FINDTYPE) {
      printf("finding type\n");
      dbugprinttok(tok);
    }
    return tok;
  }

/* reducedot handles a record reference.
   dot is a (now) unused token that is recycled. */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field) {
  
  


  SYMBOL recordSymbol = var->symtype;
  SYMBOL moverField;
  printf("recordSymbol->kind: %d\n", recordSymbol->kind);
  
  if(recordSymbol->kind == ARRAYSYM){
    
    recordSymbol = recordSymbol->datatype;
    // moverField = recordSymbol->datatype;
    moverField = recordSymbol->datatype;
  }

  else if (recordSymbol->kind != RECORDSYM){
    recordSymbol = recordSymbol->datatype;
    // moverField = recordSymbol->datatype;
    moverField = recordSymbol->datatype->datatype;
  }


  else{
    moverField = recordSymbol->datatype;
  }

  
  printf("field->stringval: %s\n", field->stringval);
  



  int fieldOffset = 0;
  while (moverField != NULL){
    
    printf("moverField->namestring: %s\n", moverField->namestring);
    
    if (strcmp(moverField->namestring, field->stringval) == 0){
      var->symtype = moverField;

      fieldOffset = moverField->offset;
      break;
    }
    moverField = moverField->link;
  }

  printf("fieldOffset: %d\n", fieldOffset);
  

  TOKEN offsetToken = makeintc(fieldOffset);

  TOKEN referenceTok = makearef(var, offsetToken, NULL);

  if (moverField) {
    
    referenceTok->symtype = moverField;
    referenceTok->basicdt = referenceTok->symtype->datatype->basicdt;
  }
  else{
    printf("moverField is null\n");
    
  }


  return referenceTok;
 
}


/* arrayref processes an array reference a[i]
   subs is a list of subscript expressions.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN arrayref(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb) {
  if (subs->link){
    

  TOKEN curArr = copytok(arr);
  TOKEN retTok;
  TOKEN variableTree = NULL;
  
  int rollingOffset = 0;
  int count = 0;

  while (subs) {
    
    int low = curArr->symtype->lowbound;
    int high = curArr->symtype->highbound;
    int size;
    
    if (low == 1){
      size = (curArr->symtype->size / (high + low - 1));
    }

    else{
      size = (curArr->symtype->size / (high + low + 1));
    }
    TOKEN elesize = makeintc(size);
    printf("low: %d\n", low);
    printf("high: %d\n", high);
    printf("size: %d\n", size);

    TOKEN indexTok;
    TOKEN timesop = makeop(TIMESOP);

    if (subs->tokentype == NUMBERTOK) {
      rollingOffset += size * subs->intval - size * low;;
    }

    else if (subs->tokentype == IDENTIFIERTOK){
      indexTok = talloc();
      indexTok->tokentype = IDENTIFIERTOK;
      strcpy(indexTok->stringval, subs->stringval);
      indexTok->basicdt = STRINGTYPE;
      elesize->link = indexTok;
      timesop->operands = elesize;
    }



    if (low == 1){
      rollingOffset -= size;
    }
    

    retTok = makearef(curArr, makeintc(rollingOffset), NULL);
    retTok->symtype = curArr->symtype->datatype;


    curArr = retTok;



    if (subs->tokentype == NUMBERTOK) {
      int offset = size * subs->intval - size * low;
      retTok->link = makeintc(offset);
      retTok->link->tokentype = NUMBERTOK;
    }
    else if (subs->tokentype == IDENTIFIERTOK) {
        if (variableTree){
          TOKEN varPlus = makeop(PLUSOP);
          varPlus->operands = variableTree;
          varPlus->operands->link = timesop;
      }
      else{
        variableTree = timesop;
      }
    }


    subs = subs->link;
    count += 1;
  }

  printf("rolling offset: %d\n", rollingOffset);
  if(variableTree != NULL){
    ppexpr(variableTree);
  }

  TOKEN finalOffset = makeop(PLUSOP);

  finalOffset->operands = makeintc(rollingOffset);
  finalOffset->operands->link = variableTree;

  TOKEN dimensionalToken =  makearef(arr, finalOffset, NULL);
  // dimensionalToken->symtype = dimensionalToken->symtype->symtype;
  return dimensionalToken;

  }


  
  else{
    printf("subs is null\n");

    TOKEN timesop = makeop(TIMESOP);
    int low = arr->symtype->lowbound;
    int high = arr->symtype->highbound;
    int size;
    
    size = (arr->symtype->size / (high - low + 1));
    TOKEN elesize = makeintc(size);


    TOKEN indexTok;

    if (subs->tokentype == NUMBERTOK) {
      indexTok = makeintc(subs->intval);
    }

    else if (subs->tokentype == IDENTIFIERTOK){
      indexTok = talloc();
      indexTok->tokentype = IDENTIFIERTOK;
      strcpy(indexTok->stringval, subs->stringval);
      indexTok->basicdt = STRINGTYPE;
    }


    elesize->link = indexTok;
    timesop->operands = elesize;
    TOKEN nsize;




    nsize = makeintc(-size * low);
    nsize->link = timesop;
    
    TOKEN plusop = makeop(PLUSOP);
    plusop->operands = nsize;
    

    TOKEN offsetTok;
    if (subs->tokentype == NUMBERTOK) {
      printf("subs->intval: %d\n", subs->intval);
      printf("size: %d\n", size);
      printf("subs->intval * size: %d\n", indexTok->intval * size + nsize->intval);
      offsetTok = makeintc(indexTok->intval * size + nsize->intval);
    }

    else if (subs->tokentype == IDENTIFIERTOK){
      offsetTok = plusop;
    }

    TOKEN retTok = makearef(arr, offsetTok, tokb);
    retTok->symtype->datatype = retTok->symtype->datatype->datatype;


    if (subs->tokentype == IDENTIFIERTOK){
      retTok->link = indexTok;
      retTok->link->tokentype = IDENTIFIERTOK;

    }


    printf("retTok\n");
    ppexpr(retTok);
    printf("\n");


    return retTok;
  }


}
  

TOKEN dolabel(TOKEN labeltok, TOKEN tok, TOKEN statement) {
    // Convert label value to index in the labels array.
    int labelValue = labeltok->intval;
    int labelIndex = -1;
    
    // Search for the label index.
    for(int i = 0; i < i < sizeof(labels) / sizeof(labels[0]); i++) {
        if (labels[i] == labelValue) {
            labelIndex = i;
            break;
        }
    }
    if (labelIndex == -1){
      
      return NULL;
    }

    // Construct the label token with the found index.
    TOKEN indexToken = makeintc(labelIndex);
    labeltok = makeop(LABELOP); // Assuming LABELOP is defined correctly elsewhere.
    labeltok->link = statement;
    
    labeltok->operands = indexToken;
    
    // Link the label operation with the provided statement using progn.
    tok = makeprogn(tok, labeltok);
    
    return tok;
}

/* dogoto is the action for a goto statement.
   tok is a (now) unused token that is recycled. */
TOKEN dogoto(TOKEN tok, TOKEN labeltok) {
    int labelValue = labeltok->intval;
    int labelIndex = -1;
    
    // Search for the label index.
    for(int i = 0; i < i < sizeof(labels) / sizeof(labels[0]); i++) {
        if (labels[i] == labelValue) {
            labelIndex = i;
            break;
        }
    }
    if (labelIndex == -1){
      
      return NULL;
    }


    return (makegoto(labelIndex));


}


/* dopoint handles a ^ operator.
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok) {
  tok->symtype = var->symtype->datatype->datatype;
  // ppexpr(tok);
  // printf("\n");
  tok->operands = var;
  

  return tok;
}

/* install variables in symbol table */
void instvars(TOKEN idlist, TOKEN typetok)
  {  SYMBOL sym, typesym; int align;
     typesym = typetok->symtype;
     align = alignsize(typesym);
     while ( idlist != NULL )   /* for each id */
       {  sym = insertsym(idlist->stringval);
          sym->kind = VARSYM;
          sym->offset =
              wordaddress(blockoffs[blocknumber],
                          align);
          sym->size = typesym->size;
          blockoffs[blocknumber] =
                         sym->offset + sym->size;
          sym->datatype = typesym;
          sym->basicdt = typesym->basicdt;
          idlist = idlist->link;
        };
  }

/* instconst installs a constant in the symbol table */
void instconst(TOKEN idtok, TOKEN consttok) {
  SYMBOL sym;
  sym = insertsym(idtok->stringval);
  sym->kind = CONSTSYM;
  sym->basicdt = consttok->basicdt;
  if(sym->basicdt == REAL) {
      sym->constval.realnum = consttok->realval;
  }

  if(sym->basicdt == INTEGER) 
  {
      sym->constval.intnum = consttok->intval;
  }
  if (DEBUG & DB_INSTCONST) {
    printf("install const\n");
    dbugprinttok(sym);
  }
}

/* instlabel installs a user label into the label table */
void  instlabel (TOKEN num) {
  labels[labelnumber++] = num->intval;  

}

/* instenum installs an enumerated subrange in the symbol table,
   e.g., type color = (red, white, blue)
   by calling makesubrange and returning the token it returns. */
TOKEN instenum(TOKEN idlist) {
  int count = 0;

  TOKEN list = copytok(idlist);
  while (list) {
    instconst(list, makeintc(count));
    count ++;
    list = list->link;
  }

  TOKEN tok = makesubrange(idlist, 0, count - 1);
  if (DEBUG & DB_INSTENUM) {
    printf("install enum\n");
    dbugprinttok(idlist);
  }

  return tok;
}

/* instdotdot installs a .. subrange in the symbol table.
   dottok is a (now) unused token that is recycled. */
TOKEN instdotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok) {
  int low = lowtok->intval;
  int high = hightok->intval;

  if (DEBUG & DB_INSTDOTDOT) {
    printf("install dot dot\n");
    dbugprinttok(lowtok);
    dbugprinttok(hightok);
  }

  return makesubrange(dottok, low, high);
}

/* instarray installs an array declaration into the symbol table.
   bounds points to a SUBRANGE symbol table entry.
   The symbol table pointer is returned in token typetok. */
TOKEN instarray(TOKEN bounds, TOKEN typetok) {
    // Temporary variables to store bounds and dimensions information
    TOKEN boundsList[100];  // Assuming a maximum of 100 dimensions for simplicity
    int numDimensions = 0;
    
    // First pass: collect bounds information and count dimensions
    for (TOKEN curr_bound = bounds; curr_bound != NULL; curr_bound = curr_bound->link) {
        boundsList[numDimensions++] = curr_bound;
    }

    // Reverse the process: start installing from the last dimension to the first
    for (int i = numDimensions - 1; i >= 0; --i) {
        TOKEN curr_bound = boundsList[i];
        int low = curr_bound->symtype->lowbound;
        int high = curr_bound->symtype->highbound;
        SYMBOL typesym = (i == numDimensions - 1) ? searchst(typetok->stringval) : typetok->symtype;
        
        // Allocate a new symbol for the current array dimension
        SYMBOL arraysym = symalloc();
        arraysym->kind = ARRAYSYM;
        arraysym->datatype = typesym; // Link to the next dimension or base type
        
        // Set bounds and size for the current dimension
        arraysym->lowbound = low;
        arraysym->highbound = high;
        arraysym->size = (high - low + 1) * ((typesym->kind == ARRAYSYM) ? typesym->size : typesym->size); // Adjust this calculation based on your type system

        // Update typetok to reflect the newest dimension
        typetok->symtype = arraysym;
    }

    if (DEBUG & DB_INSTARRAY) {
        printf("Finished instarray() iteratively with correct dimension order.\n");
        dbugprint1tok(typetok);
    }

    return typetok;
}


/* instfields will install type in a list idlist of field name tokens:
   re, im: real    put the pointer to REAL in the RE, IM tokens.
   typetok is a token whose symtype is a symbol table pointer.
   Note that nconc() can be used to combine these lists after instrec() */
TOKEN instfields(TOKEN idlist, TOKEN typetok) {

  SYMBOL symtypeTypeTok = searchst(typetok->stringval);
  TOKEN mover = idlist;

  while(mover != NULL){
    mover->symtype = symtypeTypeTok;
    mover = mover->link;
  }


  return idlist;
}

/* instrec will install a record definition.  Each token in the linked list
   argstok has a pointer its type.  rectok is just a trash token to be
   used to return the result in its symtype */
TOKEN instrec(TOKEN rectok, TOKEN argstok) {

  SYMBOL recordSymbol = symalloc();
  recordSymbol->kind = RECORDSYM;
  rectok->symtype = recordSymbol;


  int curOffset = 0;

  SYMBOL prev = NULL;

  while (argstok) {

    SYMBOL field = makesym(argstok->stringval);
    field->datatype = argstok->symtype;
    field->size = argstok->symtype->size;
    int newSize = wordaddress(curOffset, alignsize(argstok->symtype));
    field->offset = newSize;
    curOffset = newSize + argstok->symtype->size;

    if (prev == NULL) {
      recordSymbol->datatype = field;
    } 
    else {
      prev->link = field;

    }
    prev = field;
    field->link = NULL;
    argstok = argstok->link;
    
  }

  recordSymbol->size = wordaddress(curOffset, 16); 

  return rectok;
}


/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename) {

  SYMBOL typesym = searchins(typename->stringval);


  SYMBOL pointsym = symalloc();
  pointsym->datatype = typesym;
  pointsym->size = basicsizes[POINTER];
  pointsym->kind = POINTERSYM;
  pointsym->basicdt = POINTER;

  tok->symtype = pointsym;
  

  return tok;
}


/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void insttype(TOKEN typename, TOKEN typetok) {
  SYMBOL typesym = searchins(typename->stringval);
  typesym->datatype = typetok->symtype;
  // printf("typesym->datatype->namestring: %s\n", typesym->datatype->namestring);
  typesym->size = typetok->symtype->size;
  typesym->kind = TYPESYM;
  typesym->basicdt = typetok->symtype->basicdt;


  if (DEBUG & DB_INSTTYPE) {
    printf("install type\n");
    dbugprinttok(typename);
    dbugprinttok(typetok);
  }
}


int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 
yyerror(s)
  char * s;
  { 
  fputs(s,stderr); putc('\n',stderr);
  }

int main(void)          /*  */
  { int res;
    initsyms();
    res = yyparse();
    printf("yyparse result = %8d\n", res);
    printst();
    // printstlevel(1);    /* to see level 0 too, change to:   printst();  */

    if (DEBUG & DB_PARSERES){ 

      dbugprinttok(parseresult);
    }

    ppexpr(parseresult);           /* Pretty-print the result tree */

    /* uncomment following to call code generator. */
     
    // gencode(parseresult, blockoffs[blocknumber], labelnumber);
 
  }
