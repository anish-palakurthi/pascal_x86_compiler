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
     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 10 Jan 24   */

/* Copyright (c) 2023 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/* 14 Feb 01; 01 Oct 04; 02 Mar 07; 27 Feb 08; 24 Jul 09; 02 Aug 12;
   30 Jul 13; 25 Jul 19 ; 28 Feb 22; 08 Jul 22; 13 Nov 23 */

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


#line 134 "y.tab.c"

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
#define YYLAST   251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  192

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
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    85,    86,    89,    90,    91,    94,    97,
      98,   103,   106,   107,   110,   112,   113,   121,   122,   123,
     124,   126,   127,   129,   130,   131,   134,   135,   139,   140,
     143,   144,   147,   148,   152,   153,   155,   156,   158,   159,
     162,   165,   168,   171,   172,   173,   174,   175,   176,   177,
     178,   180,   182,   185,   186,   189,   190,   193,   195,   196,
     199,   200,   201,   202,   203,   204,   205,   206,   210,   211,
     212,   213,   216,   217,   218,   219,   220,   221,   225,   226,
     229,   230,   233,   234,   237,   238,   242,   243,   244,   245,
     246,   247,   248,   252,   253,   255,   256
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
  "idlist", "constantVal", "constant", "statementList", "tdef", "fields",
  "field_list", "type", "stype_list", "simpletype", "tblock", "cblock",
  "constantList", "vblock", "lblock", "labelValList", "varspecs", "label",
  "vargroup", "block", "statement", "functionCall", "endpart", "endif",
  "assignment", "expressionList", "expr", "signedExpression", "term",
  "sign", "signedId", "signedNumber", "signedTerm", "factor", "variable", YY_NULLPTR
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

#define YYPACT_NINF (-149)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-82)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -28,    53,    24,    35,  -149,    72,    54,    60,    72,    56,
    -149,    18,    65,    85,    73,  -149,    66,    81,    97,   106,
      11,    65,    11,  -149,  -149,     0,  -149,  -149,   111,    87,
      93,  -149,    11,    65,  -149,    67,  -149,  -149,  -149,  -149,
    -149,   148,    11,  -149,  -149,   134,   158,   171,   148,  -149,
    -149,   137,    64,   100,   159,    65,  -149,  -149,    11,  -149,
     130,    11,    85,    38,   113,   213,  -149,    11,  -149,   192,
      11,    11,    11,    11,    11,    11,    11,    65,   148,   148,
     148,   148,   148,   148,   148,   148,   171,    11,    65,    65,
       0,   219,  -149,   108,  -149,   141,   181,    72,  -149,  -149,
    -149,  -149,  -149,    11,   186,  -149,   158,   158,   158,   158,
     158,   158,   158,   101,   171,   171,   171,  -149,  -149,  -149,
    -149,  -149,   219,  -149,  -149,  -149,  -149,   145,   135,   -14,
     149,  -149,  -149,    14,   181,    16,  -149,  -149,   136,   132,
     142,  -149,    65,    65,  -149,   181,   141,  -149,   110,  -149,
    -149,  -149,  -149,   110,  -149,    72,  -149,  -149,  -149,  -149,
      -2,   178,    72,   152,    72,   160,   165,  -149,  -149,  -149,
    -149,   180,    31,   184,   187,   172,   181,  -149,  -149,   183,
     190,   110,    72,  -149,  -149,   169,    31,  -149,  -149,   110,
    -149,  -149
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     4,     0,     0,     0,
       3,     0,     0,     0,     0,    35,    93,     0,     0,     0,
       0,     0,     0,    51,    43,     0,    46,    45,     0,    37,
       0,     2,     0,     0,    93,     0,    50,    87,    88,    78,
      79,     0,     0,    89,    90,     0,    67,    85,     0,    68,
      77,    86,     0,    10,     0,     0,    54,    42,     0,    96,
       0,     0,     0,     0,     0,    59,    40,     0,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    84,     0,     0,     0,
       0,    57,    95,     0,    36,     0,     0,     0,    29,    34,
      27,    33,    52,     0,     0,    91,    60,    63,    61,    64,
      65,    62,    66,    56,    69,    70,    71,    72,    73,    76,
      74,    75,    48,     9,    49,    53,    94,     0,     0,     0,
      81,     5,    83,     0,    13,     0,     6,     7,     0,     0,
       0,    58,     0,     0,    44,     0,    31,    28,     0,    26,
      12,    80,    82,     0,    32,    39,    47,    55,     8,    30,
      23,     0,     0,     0,     0,     0,     0,    17,    41,    38,
      20,     0,     0,     0,    16,     0,     0,    11,    24,     0,
      22,     0,     0,    19,    25,     0,     0,    14,    15,     0,
      21,    18
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -149,  -149,    -5,   -84,  -149,   131,  -149,  -149,    36,  -148,
      34,  -144,   107,  -149,    76,   109,  -149,   177,    86,  -149,
    -149,    -9,    -6,    -8,   150,  -149,   233,   -50,     9,   174,
       7,   -88,  -149,  -149,  -149,    21,   -11
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,   138,   165,   128,    52,   134,   174,   175,   166,
     179,   167,    98,    99,   129,   100,    14,    30,   139,    23,
     140,    24,    53,    44,    57,   144,    27,    64,    65,    46,
      47,    48,   136,   137,    49,    50,    51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    28,    15,    10,    26,   168,    25,    28,   135,   148,
      28,    93,   133,    26,    16,    37,    38,    39,    40,   151,
      12,   152,    28,     1,     4,    26,    55,    66,   180,    45,
     -81,    54,    41,   187,   160,   131,   132,    39,    40,    42,
      56,   191,   180,    96,    28,    97,   135,    26,    12,    90,
     150,    69,    12,   141,   101,    86,     3,   135,    43,   162,
     135,   158,    68,     5,    13,   135,    28,    91,    16,    26,
      17,   113,    12,    97,    95,     6,   104,    28,    28,     8,
      26,    26,    11,   124,   135,   114,   115,   116,   135,     9,
      29,    31,   184,   135,    32,    96,   122,    97,   135,    12,
      34,   135,   117,   118,   119,   120,   121,    18,    33,    19,
      20,    36,    62,   160,   131,   132,    39,    40,    21,    63,
     101,    58,    87,    67,   101,    22,    88,   161,    59,    60,
     154,    28,    28,    92,    26,    26,   156,   157,   162,   126,
     143,    61,   102,   163,   127,    70,    71,    72,    73,    74,
      75,    16,    37,    38,    59,    60,   145,   171,    76,   173,
     148,   146,   164,   153,    78,    79,    12,    61,   155,    41,
      70,    71,    72,    73,    74,    75,    42,   173,    80,    81,
      82,   170,   172,    76,   130,   131,   132,    39,    40,    77,
      83,   177,   176,    84,    85,    43,    89,    70,    71,    72,
      73,    74,    75,    70,    71,    72,    73,    74,    75,   178,
      76,   181,   183,   182,   185,   186,    76,   189,   188,   123,
     190,   105,   159,   142,    70,    71,    72,    73,    74,    75,
      70,    71,    72,    73,    74,    75,   147,    76,   103,    94,
     125,   169,   149,    76,   106,   107,   108,   109,   110,   111,
     112,    35
};

static const yytype_uint8 yycheck[] =
{
       5,    12,    11,     8,    12,   153,    12,    18,    96,    11,
      21,    61,    96,    21,     3,     4,     5,     6,     7,     3,
      34,     5,    33,    51,     0,    33,    26,    33,   172,    20,
      32,    22,    21,   181,     3,     4,     5,     6,     7,    28,
      40,   189,   186,    57,    55,    59,   134,    55,    34,    55,
     134,    42,    34,   103,    63,    48,     3,   145,    47,    28,
     148,   145,    41,    28,    46,   153,    77,    58,     3,    77,
       5,    77,    34,    59,    36,     3,    67,    88,    89,    25,
      88,    89,    26,    89,   172,    78,    79,    80,   176,    29,
       5,    18,   176,   181,    28,    57,    87,    59,   186,    34,
       3,   189,    81,    82,    83,    84,    85,    42,    27,    44,
      45,     5,    25,     3,     4,     5,     6,     7,    53,    26,
     129,    10,    58,    56,   133,    60,    26,    17,    17,    18,
     139,   142,   143,     3,   142,   143,   142,   143,    28,    31,
      39,    30,    29,    33,     3,    11,    12,    13,    14,    15,
      16,     3,     4,     5,    17,    18,    11,   162,    24,   164,
      11,    26,    52,    27,     6,     7,    34,    30,    26,    21,
      11,    12,    13,    14,    15,    16,    28,   182,    20,     8,
       9,     3,    30,    24,     3,     4,     5,     6,     7,    55,
      19,    26,    32,    22,    23,    47,    37,    11,    12,    13,
      14,    15,    16,    11,    12,    13,    14,    15,    16,    29,
      24,    27,    40,    26,    31,    25,    24,    48,   182,    88,
     186,    29,   146,    37,    11,    12,    13,    14,    15,    16,
      11,    12,    13,    14,    15,    16,   129,    24,    25,    62,
      90,   155,   133,    24,    70,    71,    72,    73,    74,    75,
      76,    18
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    63,     3,     0,    28,     3,    64,    25,    29,
      64,    26,    34,    46,    78,    83,     3,     5,    42,    44,
      45,    53,    60,    81,    83,    84,    85,    88,    98,     5,
      79,    18,    28,    27,     3,    88,     5,     4,     5,     6,
       7,    21,    28,    47,    85,    90,    91,    92,    93,    96,
      97,    98,    67,    84,    90,    26,    40,    86,    10,    17,
      18,    30,    25,    26,    89,    90,    84,    56,    97,    90,
      11,    12,    13,    14,    15,    16,    24,    55,     6,     7,
      20,     8,     9,    19,    22,    23,    92,    58,    26,    37,
      84,    90,     3,    89,    79,    36,    57,    59,    74,    75,
      77,    83,    29,    25,    90,    29,    91,    91,    91,    91,
      91,    91,    91,    84,    92,    92,    92,    97,    97,    97,
      97,    97,    90,    67,    84,    86,    31,     3,    66,    76,
       3,     4,     5,    65,    68,    93,    94,    95,    64,    80,
      82,    89,    37,    39,    87,    11,    26,    74,    11,    77,
      65,     3,     5,    27,    83,    26,    84,    84,    65,    76,
       3,    17,    28,    33,    52,    65,    71,    73,    71,    80,
       3,    64,    30,    64,    69,    70,    32,    26,    29,    72,
      73,    27,    26,    40,    65,    31,    25,    71,    70,    48,
      72,    71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    65,    66,    67,
      67,    68,    65,    65,    69,    70,    70,    71,    71,    71,
      71,    72,    72,    73,    73,    73,    74,    74,    75,    75,
      76,    76,    77,    77,    78,    78,    79,    79,    80,    80,
      81,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    85,    86,    86,    87,    87,    88,    89,    89,
      90,    90,    90,    90,    90,    90,    90,    90,    91,    91,
      91,    91,    92,    92,    92,    92,    92,    92,    93,    93,
      94,    94,    95,    95,    96,    96,    97,    97,    97,    97,
      97,    97,    97,    98,    98,    98,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     3,     1,     1,     1,     1,     3,     3,
       1,     4,     2,     1,     3,     3,     1,     1,     6,     3,
       2,     3,     1,     1,     3,     3,     3,     1,     3,     1,
       3,     2,     3,     1,     4,     1,     3,     1,     3,     2,
       3,     3,     3,     1,     5,     1,     1,     6,     4,     4,
       2,     1,     4,     3,     1,     2,     0,     3,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       2,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     4,     3,     2
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
#line 83 "parse.y"
                                                                          { parseresult = makeprogram(yyvsp[-6], yyvsp[-4], yyvsp[-1]); }
#line 1626 "y.tab.c"
    break;

  case 3:
#line 85 "parse.y"
                                      { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1632 "y.tab.c"
    break;

  case 4:
#line 86 "parse.y"
                             { yyval = cons(yyvsp[0], NULL); }
#line 1638 "y.tab.c"
    break;

  case 8:
#line 94 "parse.y"
                                          { instconst(yyvsp[-2], yyvsp[0]); }
#line 1644 "y.tab.c"
    break;

  case 9:
#line 97 "parse.y"
                                                           { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1650 "y.tab.c"
    break;

  case 11:
#line 103 "parse.y"
                                                { insttype(yyvsp[-3], yyvsp[-1]); }
#line 1656 "y.tab.c"
    break;

  case 14:
#line 110 "parse.y"
                                              { yyval = instfields(yyvsp[-2], yyvsp[0]); }
#line 1662 "y.tab.c"
    break;

  case 15:
#line 112 "parse.y"
                                              { yyval = nconc(yyvsp[-2], yyvsp[0]); }
#line 1668 "y.tab.c"
    break;

  case 18:
#line 122 "parse.y"
                                                             { yyval = instarray(yyvsp[-3], yyvsp[0]); }
#line 1674 "y.tab.c"
    break;

  case 19:
#line 123 "parse.y"
                                                               { yyval = instrec(yyvsp[-2], yyvsp[-1]); }
#line 1680 "y.tab.c"
    break;

  case 20:
#line 124 "parse.y"
                                                              { yyval = instpoint(yyvsp[-1], yyvsp[0]); }
#line 1686 "y.tab.c"
    break;

  case 21:
#line 126 "parse.y"
                                             { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1692 "y.tab.c"
    break;

  case 22:
#line 127 "parse.y"
                                          { yyval = cons(yyvsp[0], NULL); }
#line 1698 "y.tab.c"
    break;

  case 23:
#line 129 "parse.y"
                             { yyval = findtype(yyvsp[0]); }
#line 1704 "y.tab.c"
    break;

  case 24:
#line 130 "parse.y"
                                             { yyval = instenum(yyvsp[-1]); }
#line 1710 "y.tab.c"
    break;

  case 25:
#line 131 "parse.y"
                                                   { yyval = instdotdot(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1716 "y.tab.c"
    break;

  case 26:
#line 134 "parse.y"
                                              { yyval = yyvsp[0]; }
#line 1722 "y.tab.c"
    break;

  case 28:
#line 139 "parse.y"
                                                       { yyval = yyvsp[0]; }
#line 1728 "y.tab.c"
    break;

  case 32:
#line 147 "parse.y"
                                         { yyval = yyvsp[0]; }
#line 1734 "y.tab.c"
    break;

  case 34:
#line 152 "parse.y"
                                                     { yyval = yyvsp[0]; }
#line 1740 "y.tab.c"
    break;

  case 36:
#line 155 "parse.y"
                                                { instlabel(yyvsp[-2]); }
#line 1746 "y.tab.c"
    break;

  case 37:
#line 156 "parse.y"
                                     { instlabel(yyvsp[0]); }
#line 1752 "y.tab.c"
    break;

  case 40:
#line 162 "parse.y"
                                                { yyval = dolabel(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1758 "y.tab.c"
    break;

  case 41:
#line 165 "parse.y"
                                  { instvars(yyvsp[-2], yyvsp[0]); }
#line 1764 "y.tab.c"
    break;

  case 42:
#line 168 "parse.y"
                                               { yyval = makeprogn(yyvsp[-2],cons(yyvsp[-1], yyvsp[0])); }
#line 1770 "y.tab.c"
    break;

  case 44:
#line 172 "parse.y"
                                              { yyval = makeif(yyvsp[-4], yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 1776 "y.tab.c"
    break;

  case 47:
#line 175 "parse.y"
                                                     { yyval = makefor(1, yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1782 "y.tab.c"
    break;

  case 48:
#line 176 "parse.y"
                                                            { yyval = makerepeat(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1788 "y.tab.c"
    break;

  case 49:
#line 177 "parse.y"
                                             { yyval = makewhile(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1794 "y.tab.c"
    break;

  case 50:
#line 178 "parse.y"
                                            { yyval = dogoto(yyvsp[-1], yyvsp[0]); }
#line 1800 "y.tab.c"
    break;

  case 52:
#line 182 "parse.y"
                                                                { yyval = makefuncall(yyvsp[-2], yyvsp[-3], yyvsp[-1]); }
#line 1806 "y.tab.c"
    break;

  case 53:
#line 185 "parse.y"
                                               { yyval = cons(yyvsp[-1], yyvsp[0]); }
#line 1812 "y.tab.c"
    break;

  case 54:
#line 186 "parse.y"
                                               { yyval = NULL; }
#line 1818 "y.tab.c"
    break;

  case 55:
#line 189 "parse.y"
                                               { yyval = yyvsp[0]; }
#line 1824 "y.tab.c"
    break;

  case 56:
#line 190 "parse.y"
                                               { yyval = NULL; }
#line 1830 "y.tab.c"
    break;

  case 57:
#line 193 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1836 "y.tab.c"
    break;

  case 58:
#line 195 "parse.y"
                                                         { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1842 "y.tab.c"
    break;

  case 60:
#line 199 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1848 "y.tab.c"
    break;

  case 61:
#line 200 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1854 "y.tab.c"
    break;

  case 62:
#line 201 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1860 "y.tab.c"
    break;

  case 63:
#line 202 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1866 "y.tab.c"
    break;

  case 64:
#line 203 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1872 "y.tab.c"
    break;

  case 65:
#line 204 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1878 "y.tab.c"
    break;

  case 66:
#line 205 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1884 "y.tab.c"
    break;

  case 69:
#line 211 "parse.y"
                                                           { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1890 "y.tab.c"
    break;

  case 70:
#line 212 "parse.y"
                                                            { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1896 "y.tab.c"
    break;

  case 71:
#line 213 "parse.y"
                                                         { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1902 "y.tab.c"
    break;

  case 72:
#line 216 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1908 "y.tab.c"
    break;

  case 73:
#line 217 "parse.y"
                                                { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1914 "y.tab.c"
    break;

  case 74:
#line 218 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1920 "y.tab.c"
    break;

  case 75:
#line 219 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1926 "y.tab.c"
    break;

  case 76:
#line 220 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1932 "y.tab.c"
    break;

  case 80:
#line 229 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1938 "y.tab.c"
    break;

  case 82:
#line 233 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1944 "y.tab.c"
    break;

  case 84:
#line 237 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1950 "y.tab.c"
    break;

  case 91:
#line 247 "parse.y"
                                               { yyval = yyvsp[-1]; }
#line 1956 "y.tab.c"
    break;

  case 92:
#line 248 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1962 "y.tab.c"
    break;

  case 93:
#line 252 "parse.y"
                                                      { yyval = findid(yyvsp[0]); }
#line 1968 "y.tab.c"
    break;

  case 94:
#line 253 "parse.y"
                                                           { yyval = arrayref(yyvsp[-3], yyvsp[-2],
             yyvsp[-1], yyvsp[0]); }
#line 1975 "y.tab.c"
    break;

  case 95:
#line 255 "parse.y"
                                                       { yyval = reducedot(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1981 "y.tab.c"
    break;

  case 96:
#line 256 "parse.y"
                                                       { yyval = dopoint(yyvsp[-1], yyvsp[0]); }
#line 1987 "y.tab.c"
    break;


#line 1991 "y.tab.c"

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
#line 258 "parse.y"



#define DEBUG           31             /* set bits here for debugging, 0 = off  */
#define DB_CONS         0             /* bit to trace cons */
#define DB_BINOP        0             /* bit to trace binop */
#define DB_MAKEIF       0             /* bit to trace makeif */
#define DB_MAKEPROGN    0             /* bit to trace makeprogn */
#define DB_PARSERES     0             /* bit to trace parseresult */
#define DB_MAKEPROGRAM  0
#define DB_MAKENUM      0
#define DB_MAKECOPY     0
#define DB_MAKEFOR      0
#define DB_MAKEFUNCALL  0

 int labelnumber = 0;  
 int labels[100];

/* cons links a new item onto the front of a list.  Equivalent to a push.
   (cons 'a '(b c))  =  (a b c)    */
TOKEN cons(TOKEN item, TOKEN list)           /* add item to front of list */
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

  return temp;
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


    
  

/* unaryop links a unary operator op to one operand, lhs */
TOKEN unaryop(TOKEN op, TOKEN lhs){
  lhs->link = NULL;
  op->operands = lhs;
  if (DEBUG & DB_BINOP)
       { printf("unaryop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
       };
  return op;
}


/* makeop makes a new operator token with operator number opnum.
   Example:  makeop(FLOATOP)  */
TOKEN makeop(int op){
    TOKEN tok = talloc();
    tok->whichval = op;
    tok->tokentype = OPERATOR;

    return tok;
}

/* makefloat forces the item tok to be floating, by floating a constant
   or by inserting a FLOATOP operator */
TOKEN makefloat(TOKEN tok){
  if (tok->tokentype == NUMBERTOK){
    tok->realval = (double) tok->intval;
    tok->basicdt = REAL;
    return tok;
  }
  TOKEN floatToken = makeop(FLOATOP);
  floatToken->operands = tok;
  return floatToken;
    

}



/* makefix forces the item tok to be integer, by truncating a constant
   or by inserting a FIXOP operator */
TOKEN makefix(TOKEN tok){
  if(tok->tokentype == NUMBERTOK){
    tok->intval = (int) tok->realval;
    tok->basicdt = INTEGER;
    return tok;
  } else{
    TOKEN fixToken = makeop(FIXOP);
    fixToken->operands = tok;
    return fixToken;
  }
}

/* makeintc makes a new integer number token with num as its value */
TOKEN makeintc(int num) {
  TOKEN tok = talloc();
  tok->intval = num;
  tok->tokentype = NUMBERTOK;
  tok->basicdt = INTEGER;
  if (DEBUG & DB_MAKENUM) {
      printf("makeintc\n");
      dbugprinttok(tok);
  }
  return tok;
}


/* copytok makes a new token that is a copy of origtok */
TOKEN copytok(TOKEN target) {
  TOKEN copy = talloc();
  copy->tokentype = target->tokentype;
  copy->symentry = target->symentry;
  copy->basicdt = target->basicdt;
  copy->link = target->link;
  copy->whichval = target->whichval;
  copy->intval = target->intval;
  copy->realval = target->realval;
  copy->symtype = target->symtype;

  return copy;
}


/* makeif makes an IF operator and links it to its arguments.
   tok is a (now) unused token that is recycled to become an IFOP operator */
TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  //decomposing if token
     tok->tokentype = OPERATOR;  

    //determining expression
     tok->operands = exp;
     tok->whichval = IFOP;

     //exp->thenpart->elsepart
     thenpart->link = elsepart;
     exp->link = thenpart;
     if (DEBUG & DB_MAKEIF)
        { printf("makeif\n");
          dbugprinttok(tok);
          dbugprinttok(exp);
          dbugprinttok(thenpart);
          dbugprinttok(elsepart);
        };
     return tok;
   }


/* makeprogn makes a PROGN operator and links it to the list of statements.
   tok is a (now) unused token that is recycled. */
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


/* makelabel makes a new label, using labelnumber++ */
TOKEN makelabel(){
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = LABELOP;
  tok->operands = makeintc(labelnumber++);
  return tok;

}

/* Corrected dolabel function. Assumes labels and labelnumber are correctly declared and accessible. */
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

/* instlabel installs a user label into the label table */
void instlabel (TOKEN num) {
  labels[labelnumber++] = num->intval;  

}


/* makegoto makes a GOTO operator to go to the specified label.
   The label number is put into a number token. */
TOKEN makegoto(int label){
  TOKEN tok = makeop(GOTOOP);
  tok->operands = makeintc(label);
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



/* findid finds an identifier in the symbol table, sets up symbol table
   pointers, changes a constant to its number equivalent */
TOKEN findid(TOKEN tok) { /* the ID token */
    SYMBOL symbol =  searchst(tok->stringval);
    tok->symentry = symbol;
    

    if (symbol->kind == CONSTSYM) {
      tok->tokentype = NUMBERTOK;
      switch(symbol->basicdt){
        case INTEGER:
          tok->intval = symbol->constval.intnum;
          tok->basicdt = INTEGER;
          break;
        case REAL:
          tok->realval = symbol->constval.realnum;
          tok->basicdt = REAL;
          break;
        default:
          break;
      }

      return tok;
    }
    
    tok->symtype = symbol->datatype;
    if ( symbol->datatype->kind == BASICTYPE ||
         symbol->datatype->kind == POINTERSYM)
        tok->basicdt = symbol->datatype->basicdt;


    return tok;
  }



/* instconst installs a constant in the symbol table */
void instconst(TOKEN idtok, TOKEN consttok){

  //create and return the symbol table entry
  SYMBOL constSymbol = insertsym(idtok->stringval);

  //update the symbol table entry to reflect the token's value and data type
  constSymbol->basicdt = consttok->basicdt;
  constSymbol->kind = CONSTSYM;

  int type = consttok->basicdt;
  if (type == INTEGER){
    constSymbol->constval.intnum = consttok->intval;
  }
  else if (type == REAL){
    constSymbol->constval.realnum = consttok->realval;
  }
  else {
    return;
  }
}


/* makesubrange makes a SUBRANGE symbol table entry, puts the pointer to it
   into tok, and returns tok. */
TOKEN makesubrange(TOKEN tok, int low, int high) {

  SYMBOL rangeSym = symalloc();
  tok->symtype = rangeSym;

  rangeSym->lowbound = low;
  rangeSym->highbound = high;
  rangeSym->basicdt = INTEGER;
  rangeSym->kind = SUBRANGE;
  rangeSym->size = sizeof(INTEGER);

  return tok;
}



/* instenum installs an enumerated subrange in the symbol table,
   e.g., type color = (red, white, blue)
   by calling makesubrange and returning the token it returns. */
TOKEN instenum(TOKEN idlist){
  int numOptions = 0;

  TOKEN traversal = copytok(idlist);

  while (traversal != NULL) {
    instconst(traversal, makeintc(numOptions++));
    traversal = traversal->link;
  }

  TOKEN enumRange = makesubrange(idlist, 0, numOptions - 1);


  return enumRange;
}



/* instdotdot installs a .. subrange in the symbol table.
   dottok is a (now) unused token that is recycled. */
TOKEN instdotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok){

  return makesubrange(dottok, lowtok->intval,  hightok->intval);
}



/* findtype looks up a type name in the symbol table, puts the pointer
   to its type into tok->symtype, returns tok. */
TOKEN findtype(TOKEN tok){
  SYMBOL sym = searchst(tok->stringval);
  if (sym->kind == TYPESYM) {
      sym = sym->datatype;
   }
  tok->symtype = sym;
  return tok;
}

/* wordaddress pads the offset n to be a multiple of wordsize.
   wordsize should be 4 for integer, 8 for real and pointers,
   16 for records and arrays */
int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 


/* instvars will install variables in symbol table.
   typetok is a token containing symbol table pointer for type. */
void instvars(TOKEN idlist, TOKEN typetok)
  {  
    SYMBOL sym, typesym; int align;
    typesym = typetok->symtype;
    align = alignsize(typesym);
    while ( idlist != NULL )   /* for each id */
      {  sym = insertsym(idlist->stringval);
        sym->kind = VARSYM;
        sym->offset =     /* "next" */
            wordaddress(blockoffs[blocknumber],
                        align);
        sym->size = typesym->size;
        blockoffs[blocknumber] =   /* "next" */
                        sym->offset + sym->size;
        sym->datatype = typesym;
        sym->basicdt = typesym->basicdt;
        idlist = idlist->link;
      };
  }


/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void  insttype(TOKEN typename, TOKEN typetok) {
  SYMBOL typesym = searchins(typename->stringval);
  typesym->kind = TYPESYM;
  typesym->datatype = typetok->symtype;
  typesym->size = typetok->symtype->size;


}


/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename) {

  SYMBOL typeSymbol = searchins(typename->stringval);


  SYMBOL pointSymbol = symalloc();
  pointSymbol->kind = POINTERSYM;
  pointSymbol->basicdt = POINTER;
  pointSymbol->datatype = typeSymbol;
  pointSymbol->size = sizeof(POINTER);

  tok->symtype = pointSymbol;



  return tok;
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

  recordSymbol->size = wordaddress(curOffset, 8); 

  return rectok;
}



/* instfields will install type in a list idlist of field name tokens:
   re, im: real    put the pointer to REAL in the RE, IM tokens.
   typetok is a token whose symtype is a symbol table pointer.
   Note that nconc() can be used to combine these lists after instrec() */
TOKEN instfields(TOKEN idlist, TOKEN typetok){

  TOKEN mover = idlist;

  while(mover != NULL){
    mover->symtype = typetok->symtype;
    mover = mover->link;
  }

  return idlist;
  
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


/* makearef makes an array reference operation.
   off is be an integer constant token
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok){
  
  TOKEN finalOffset = off; // Start with the assumption we'll use the provided offset

  if (var->link){
    
    if (var->link->tokentype == NUMBERTOK){
    finalOffset->intval = var->link->intval + off->intval;
    }
    else if(var->link->tokentype == IDENTIFIERTOK){
      TOKEN plusOp = makeop(PLUSOP);
      plusOp->operands = var->link;
      plusOp->link = off;
      finalOffset = plusOp;
      finalOffset->tokentype = IDENTIFIERTOK;
    }
    
  }

  if (off->basicdt == INTEGER  &&  var->whichval == AREFOP) {
    
    TOKEN secondOffset = var->operands->link;
    if (secondOffset->tokentype == NUMBERTOK) { // Assuming secondOffset is the offset in the nested AREF
      // Directly sum the integer values of the offsets
      int sumOffsets = secondOffset->intval + off->intval;
      finalOffset = makeintc(sumOffsets); // Use this new offset for the final AREF
    }
  }

  // Now, we create the AREF operation using the possibly updated finalOffset
  TOKEN arefTok = makeop(AREFOP);
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
  
  arefTok->operands = var;
  
  
  arefTok->symentry = var->symentry;
  
  if (var->symentry && var->symentry->datatype) {
    arefTok->basicdt = var->symentry->datatype->basicdt;
  }

  

  return arefTok;
}









/* reducedot handles a record reference.
   dot is a (now) unused token that is recycled. */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field) {



  SYMBOL recordSymbol = var->symentry;
  SYMBOL moverField = recordSymbol->datatype->datatype;

  int fieldOffset = 0;
  while (moverField != NULL){
    if (strcmp(moverField->namestring, field->stringval) == 0){
      var->symentry = moverField;

      fieldOffset = moverField->offset;
      break;
    }
    moverField = moverField->link;
  }

  TOKEN offsetToken = makeintc(fieldOffset);

  TOKEN referenceTok = makearef(var, offsetToken, NULL);

  if (moverField) {
    referenceTok->basicdt = moverField->datatype->basicdt;
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
      TOKEN unitSize = makeintc(size);


      TOKEN indexTok;
      TOKEN timesOp = makeop(TIMESOP);

      if (subs->tokentype == NUMBERTOK) {
        rollingOffset += size * subs->intval - size * low;;
      }

      else if (subs->tokentype == IDENTIFIERTOK){
        indexTok = talloc();
        indexTok->tokentype = IDENTIFIERTOK;
        strcpy(indexTok->stringval, subs->stringval);
        indexTok->basicdt = STRINGTYPE;
        unitSize->link = indexTok;
        timesOp->operands = unitSize;
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
            varPlus->operands->link = timesOp;
        }
        else{
          variableTree = timesOp;
        }
      }


      subs = subs->link;
      count += 1;
    }

    
    TOKEN finalOffset = makeplus(makeintc(rollingOffset),variableTree, NULL);


    return makearef(arr, finalOffset, NULL);

  }
  else{
    TOKEN timesOp = makeop(TIMESOP);
    int low = arr->symtype->lowbound;
    int high = arr->symtype->highbound;
    int size;
    
    if (low == 1){
      size = (arr->symtype->size / (high + low - 1));
    }
    else{
      size = (arr->symtype->size / (high + low + 1));
    }
    TOKEN unitSize = makeintc(size);


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


    unitSize->link = indexTok;
    timesOp->operands = unitSize;
    TOKEN negativeUnit;




    negativeUnit = makeintc(-1 * size);
    negativeUnit->link = timesOp;
    
    TOKEN plusOp = makeop(PLUSOP);
    plusOp->operands = negativeUnit;
    


    TOKEN retTok = makearef(arr, plusOp, tokb);

    if (subs->tokentype == NUMBERTOK) {
      int offset = size * subs->intval - size * low;
      retTok->link = makeintc(offset);
      retTok->link->tokentype = NUMBERTOK;
    }

    else if (subs->tokentype == IDENTIFIERTOK){
      retTok->link = indexTok;
      retTok->link->tokentype = IDENTIFIERTOK;

    }


    return retTok;
  }


}


int  checkReal(TOKEN tok) {
  return (tok->basicdt == REAL);

}

int checkInt(TOKEN tok) {
  return (tok->basicdt == INTEGER);

}





/* dopoint handles a ^ operator.
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok) {
  tok->operands = var;
  tok->symentry = var->symentry->datatype->datatype;
  
  return tok;
}




/* instarray installs an array declaration into the symbol table.
   bounds points to a SUBRANGE symbol table entry.
   The symbol table pointer is returned in token typetok. */
TOKEN instarray(TOKEN bounds, TOKEN typetok) {
  
  if (bounds->link) {
    typetok = instarray(bounds->link, typetok);
  } 
  SYMBOL arrSymbol = symalloc();
  arrSymbol->kind = ARRAYSYM;
  arrSymbol->datatype = typetok->symtype;

  
  arrSymbol->lowbound = bounds->symtype->lowbound;
  arrSymbol->highbound = bounds->symtype->highbound;

  
  if (bounds->link){
    arrSymbol->size = (arrSymbol->lowbound + arrSymbol->highbound - 1) * (typetok->symtype->size);
  }
  else{
    arrSymbol->size = (arrSymbol->highbound - arrSymbol->lowbound +  1) * (typetok->symtype->size);

  }


  typetok->symtype = arrSymbol;

  return typetok;
  }






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

    printstlevel(1);    /* to see level 0 too, change to:   printst();  */

    if (DEBUG & DB_PARSERES){ 

      dbugprinttok(parseresult);
    }

    ppexpr(parseresult);           /* Pretty-print the result tree */

    /* uncomment following to call code generator. */
     
    // gencode(parseresult, blockoffs[blocknumber], labelnumber);
 
  }

