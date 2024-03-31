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
#include "token.h"

#include "lexan.h"
#include "symtab.h"

#include "parse.h"


        /* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN

TOKEN parseresult;


#line 136 "y.tab.c"

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
#define YYLAST   223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

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
       0,    85,    85,    89,    91,    94,    95,    96,    99,   102,
     103,   106,   109,   110,   113,   114,   117,   118,   121,   122,
     125,   126,   137,   138,   141,   143,   146,   149,   150,   153,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   167,
     170,   171,   174,   175,   178,   181,   182,   185,   186,   187,
     188,   189,   190,   191,   192,   195,   196,   197,   198,   201,
     202,   203,   204,   205,   206,   209,   210,   213,   214,   217,
     218,   221,   222,   226,   227,   228,   229,   230,   231,   232,
     237,   238,   239,   240,   244,   248,   252,   256,   257,   261,
     262,   263,   267,   268,   269,   271
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
  "idlist", "constantVal", "constant", "statementList", "typeSet",
  "typeList", "tblock", "cblock", "constantList", "vblock", "varspecs",
  "label", "vargroup", "fields", "fieldsList", "block", "statement",
  "functionCall", "endpart", "endif", "assignment", "expressionList",
  "expr", "signedExpression", "term", "sign", "signedId", "signedNumber",
  "signedTerm", "factor", "type", "array_type", "record_type",
  "point_type", "basic_list", "basic_type", "variable", YY_NULLPTR
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

#define YYPACT_NINF (-145)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -30,    28,    42,    31,  -145,    58,    43,    54,    58,    62,
    -145,   -14,     9,   104,    92,  -145,    83,    85,   114,   121,
      88,     9,    88,  -145,  -145,   -11,  -145,  -145,   115,   116,
     102,    40,  -145,    88,     9,  -145,    73,  -145,  -145,  -145,
    -145,  -145,    77,    88,  -145,  -145,    21,     3,   163,    77,
    -145,  -145,   119,    72,   108,   107,     9,  -145,  -145,    88,
    -145,   143,    88,    97,   104,   144,    58,  -145,  -145,  -145,
     128,   176,  -145,    88,  -145,   154,    88,    88,    88,    88,
      88,    88,    88,     9,    77,    77,    77,    77,    77,    77,
      77,    77,   163,    88,     9,     9,   -11,   182,  -145,   127,
    -145,  -145,  -145,  -145,    36,  -145,  -145,  -145,   148,   134,
      13,   135,   129,   149,  -145,    88,   140,  -145,     3,     3,
       3,     3,     3,     3,     3,   137,   163,   163,   163,  -145,
    -145,  -145,  -145,  -145,   182,  -145,  -145,  -145,  -145,  -145,
    -145,    27,   144,  -145,    27,  -145,    58,  -145,     9,     9,
    -145,   116,   171,    58,   150,    58,   147,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,   152,    68,
     157,   173,   162,   104,  -145,   172,   179,    27,    58,  -145,
    -145,   166,    68,  -145,  -145,    27,  -145,  -145
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     4,     0,     0,     0,
       3,     0,     0,     0,     0,    17,    92,     0,     0,     0,
       0,     0,     0,    38,    30,     0,    33,    32,     0,     0,
       0,     0,     2,     0,     0,    92,     0,    37,    74,    75,
      65,    66,     0,     0,    76,    77,     0,    54,    72,     0,
      55,    64,    73,     0,    10,     0,     0,    41,    29,     0,
      95,     0,     0,     0,    19,     0,     0,    16,    15,    21,
       0,    46,    24,     0,    79,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,    44,    93,     0,
      68,     5,    70,     8,     0,     6,     7,    18,     0,     0,
       0,     0,     0,     0,    39,     0,     0,    78,    47,    50,
      48,    51,    52,    49,    53,    43,    56,    57,    58,    59,
      60,    63,    61,    62,    36,     9,    34,    40,    94,    67,
      69,     0,    13,    14,     0,    20,    23,    45,     0,     0,
      31,    89,     0,     0,     0,     0,     0,    11,    81,    82,
      83,    80,    12,    25,    22,    35,    42,    86,     0,     0,
       0,     0,     0,     0,    90,     0,    88,     0,    28,    85,
      91,     0,     0,    26,    27,     0,    87,    84
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,  -145,    -5,  -145,   -12,   111,  -145,    74,  -145,  -145,
     151,   109,    71,  -145,  -145,  -145,    44,    -4,    -6,    -8,
     122,  -145,   202,   -57,    -3,   131,    29,   158,  -145,  -145,
    -145,   -24,  -128,  -145,  -145,  -145,    41,  -144,   -10
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,   111,   103,   156,    53,   109,   110,    67,    14,
      31,    68,   112,    23,   113,   171,   172,    24,    54,    45,
      58,   150,    27,    70,    71,    47,    48,    49,   105,   106,
      50,    51,   157,   158,   159,   160,   175,   161,    52
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       7,    30,    28,    10,    26,    99,    25,    15,    28,    84,
      85,    28,    16,    26,    17,    56,   163,    46,    74,    55,
      12,     1,    13,    86,    28,   176,    26,    69,    72,    57,
     151,     3,    76,    77,    78,    79,    80,    81,   176,   139,
      75,   140,     4,    12,   152,    82,    28,    12,    26,   183,
      96,    18,    30,    19,    20,   153,    97,   187,   147,     5,
     154,     6,    21,   129,   130,   131,   132,   133,     8,    22,
     116,   151,    66,    28,    12,    26,    83,   125,    92,   155,
      16,    38,    39,     9,    28,    28,    26,    26,    11,   136,
     134,    16,    38,    39,    40,    41,   153,    65,    42,    66,
     100,   101,   102,    40,    41,    43,    69,    29,   145,    42,
      32,    33,    34,   126,   127,   128,    43,    35,    76,    77,
      78,    79,    80,    81,    44,    59,    37,    63,    64,    73,
      93,    82,    60,    61,    94,    44,    60,    61,    28,    28,
      26,    26,   165,   166,    95,    62,    98,   108,   168,    62,
     170,    76,    77,    78,    79,    80,    81,   114,   138,   141,
     142,   180,   144,    12,    82,    76,    77,    78,    79,    80,
      81,    87,    88,   170,   167,   146,   149,   148,    82,   173,
     169,   174,    89,   117,   177,    90,    91,    76,    77,    78,
      79,    80,    81,    76,    77,    78,    79,    80,    81,   178,
      82,   115,   179,   181,   182,   135,    82,   118,   119,   120,
     121,   122,   123,   124,   185,   107,   162,   164,   137,   143,
      36,   104,   184,   186
};

static const yytype_uint8 yycheck[] =
{
       5,    13,    12,     8,    12,    62,    12,    11,    18,     6,
       7,    21,     3,    21,     5,    26,   144,    20,    42,    22,
      34,    51,    36,    20,    34,   169,    34,    31,    34,    40,
       3,     3,    11,    12,    13,    14,    15,    16,   182,     3,
      43,     5,     0,    34,    17,    24,    56,    34,    56,   177,
      56,    42,    64,    44,    45,    28,    59,   185,   115,    28,
      33,     3,    53,    87,    88,    89,    90,    91,    25,    60,
      73,     3,    59,    83,    34,    83,    55,    83,    49,    52,
       3,     4,     5,    29,    94,    95,    94,    95,    26,    95,
      93,     3,     4,     5,     6,     7,    28,    57,    21,    59,
       3,     4,     5,     6,     7,    28,   110,     3,   112,    21,
      18,    28,    27,    84,    85,    86,    28,     3,    11,    12,
      13,    14,    15,    16,    47,    10,     5,    11,    26,    56,
      58,    24,    17,    18,    26,    47,    17,    18,   148,   149,
     148,   149,   148,   149,    37,    30,     3,     3,   153,    30,
     155,    11,    12,    13,    14,    15,    16,    29,    31,    11,
      26,   173,    27,    34,    24,    11,    12,    13,    14,    15,
      16,     8,     9,   178,     3,    26,    39,    37,    24,    32,
      30,    29,    19,    29,    27,    22,    23,    11,    12,    13,
      14,    15,    16,    11,    12,    13,    14,    15,    16,    26,
      24,    25,    40,    31,    25,    94,    24,    76,    77,    78,
      79,    80,    81,    82,    48,    64,   142,   146,    96,   110,
      18,    63,   178,   182
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    63,     3,     0,    28,     3,    64,    25,    29,
      64,    26,    34,    36,    71,    79,     3,     5,    42,    44,
      45,    53,    60,    75,    79,    80,    81,    84,   100,     3,
      66,    72,    18,    28,    27,     3,    84,     5,     4,     5,
       6,     7,    21,    28,    47,    81,    86,    87,    88,    89,
      92,    93,   100,    67,    80,    86,    26,    40,    82,    10,
      17,    18,    30,    11,    26,    57,    59,    70,    73,    79,
      85,    86,    80,    56,    93,    86,    11,    12,    13,    14,
      15,    16,    24,    55,     6,     7,    20,     8,     9,    19,
      22,    23,    88,    58,    26,    37,    80,    86,     3,    85,
       3,     4,     5,    65,    89,    90,    91,    72,     3,    68,
      69,    64,    74,    76,    29,    25,    86,    29,    87,    87,
      87,    87,    87,    87,    87,    80,    88,    88,    88,    93,
      93,    93,    93,    93,    86,    67,    80,    82,    31,     3,
       5,    11,    26,    73,    27,    79,    26,    85,    37,    39,
      83,     3,    17,    28,    33,    52,    66,    94,    95,    96,
      97,    99,    69,    94,    74,    80,    80,     3,    64,    30,
      64,    77,    78,    32,    29,    98,    99,    27,    26,    40,
      66,    31,    25,    94,    78,    48,    98,    94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    65,    66,    67,
      67,    68,    69,    69,    70,    70,    71,    71,    72,    72,
      73,    73,    74,    74,    75,    76,    77,    78,    78,    79,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      82,    82,    83,    83,    84,    85,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    87,    87,    87,    87,    88,
      88,    88,    88,    88,    88,    89,    89,    90,    90,    91,
      91,    92,    92,    93,    93,    93,    93,    93,    93,    93,
      94,    94,    94,    94,    95,    96,    97,    98,    98,    99,
      99,    99,   100,   100,   100,   100
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     3,     1,     1,     1,     1,     3,     3,
       1,     3,     3,     2,     3,     1,     3,     1,     3,     2,
       3,     1,     3,     2,     3,     3,     3,     3,     2,     3,
       1,     5,     1,     1,     4,     6,     4,     2,     1,     4,
       3,     1,     2,     0,     3,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     2,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     3,     2,
       1,     1,     1,     1,     6,     3,     2,     3,     1,     1,
       3,     3,     1,     3,     4,     2
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
#line 85 "parse.y"
                                                                            { parseresult = makeprogram(yyvsp[-6], yyvsp[-4], yyvsp[-1]); }
#line 1620 "y.tab.c"
    break;

  case 3:
#line 90 "parse.y"
                          { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1626 "y.tab.c"
    break;

  case 4:
#line 91 "parse.y"
                          { yyval = cons(yyvsp[0], NULL); }
#line 1632 "y.tab.c"
    break;

  case 8:
#line 99 "parse.y"
                                        { instconst(yyvsp[-2], yyvsp[0]); }
#line 1638 "y.tab.c"
    break;

  case 9:
#line 102 "parse.y"
                                                           { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1644 "y.tab.c"
    break;

  case 11:
#line 106 "parse.y"
                               { insttype(yyvsp[-2], yyvsp[0]); }
#line 1650 "y.tab.c"
    break;

  case 14:
#line 113 "parse.y"
                                           { yyval = yyvsp[0]; }
#line 1656 "y.tab.c"
    break;

  case 16:
#line 117 "parse.y"
                                                       { yyval = yyvsp[0]; }
#line 1662 "y.tab.c"
    break;

  case 20:
#line 125 "parse.y"
                                         { yyval = yyvsp[0]; }
#line 1668 "y.tab.c"
    break;

  case 24:
#line 141 "parse.y"
                                            { yyval = dolabel(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1674 "y.tab.c"
    break;

  case 25:
#line 143 "parse.y"
                                  { instvars(yyvsp[-2], yyvsp[0]); }
#line 1680 "y.tab.c"
    break;

  case 26:
#line 146 "parse.y"
                                    { yyval = instfields(yyvsp[-2], yyvsp[0]); }
#line 1686 "y.tab.c"
    break;

  case 27:
#line 149 "parse.y"
                                           { yyval = nconc(yyvsp[-2], yyvsp[0]); }
#line 1692 "y.tab.c"
    break;

  case 29:
#line 153 "parse.y"
                                               { yyval = makeprogn(yyvsp[-2],cons(yyvsp[-1], yyvsp[0])); }
#line 1698 "y.tab.c"
    break;

  case 31:
#line 157 "parse.y"
                                               { yyval = makeif(yyvsp[-4], yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 1704 "y.tab.c"
    break;

  case 34:
#line 160 "parse.y"
                                              { yyval = makewhile(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1710 "y.tab.c"
    break;

  case 35:
#line 161 "parse.y"
                                                      { yyval = makefor(1, yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1716 "y.tab.c"
    break;

  case 36:
#line 162 "parse.y"
                                                             { yyval = makerepeat(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1722 "y.tab.c"
    break;

  case 37:
#line 163 "parse.y"
                                             { yyval = dogoto(yyvsp[-1], yyvsp[0]); }
#line 1728 "y.tab.c"
    break;

  case 39:
#line 167 "parse.y"
                                                                { yyval = makefuncall(yyvsp[-2], yyvsp[-3], yyvsp[-1]); }
#line 1734 "y.tab.c"
    break;

  case 40:
#line 170 "parse.y"
                                               { yyval = cons(yyvsp[-1], yyvsp[0]); }
#line 1740 "y.tab.c"
    break;

  case 41:
#line 171 "parse.y"
                                               { yyval = NULL; }
#line 1746 "y.tab.c"
    break;

  case 42:
#line 174 "parse.y"
                                               { yyval = yyvsp[0]; }
#line 1752 "y.tab.c"
    break;

  case 43:
#line 175 "parse.y"
                                               { yyval = NULL; }
#line 1758 "y.tab.c"
    break;

  case 44:
#line 178 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1764 "y.tab.c"
    break;

  case 45:
#line 181 "parse.y"
                                                         { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1770 "y.tab.c"
    break;

  case 47:
#line 185 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1776 "y.tab.c"
    break;

  case 48:
#line 186 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1782 "y.tab.c"
    break;

  case 49:
#line 187 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1788 "y.tab.c"
    break;

  case 50:
#line 188 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1794 "y.tab.c"
    break;

  case 51:
#line 189 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1800 "y.tab.c"
    break;

  case 52:
#line 190 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1806 "y.tab.c"
    break;

  case 53:
#line 191 "parse.y"
                                                      { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1812 "y.tab.c"
    break;

  case 56:
#line 196 "parse.y"
                                                           { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1818 "y.tab.c"
    break;

  case 57:
#line 197 "parse.y"
                                                            { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1824 "y.tab.c"
    break;

  case 58:
#line 198 "parse.y"
                                                         { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1830 "y.tab.c"
    break;

  case 59:
#line 201 "parse.y"
                                               { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1836 "y.tab.c"
    break;

  case 60:
#line 202 "parse.y"
                                                { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1842 "y.tab.c"
    break;

  case 61:
#line 203 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1848 "y.tab.c"
    break;

  case 62:
#line 204 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1854 "y.tab.c"
    break;

  case 63:
#line 205 "parse.y"
                                             { yyval = binop(yyvsp[-1], yyvsp[-2], yyvsp[0]); }
#line 1860 "y.tab.c"
    break;

  case 67:
#line 213 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1866 "y.tab.c"
    break;

  case 69:
#line 217 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1872 "y.tab.c"
    break;

  case 71:
#line 221 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1878 "y.tab.c"
    break;

  case 78:
#line 231 "parse.y"
                                               { yyval = yyvsp[-1]; }
#line 1884 "y.tab.c"
    break;

  case 79:
#line 232 "parse.y"
                                    { yyval = unaryop(yyvsp[-1], yyvsp[0]); }
#line 1890 "y.tab.c"
    break;

  case 84:
#line 244 "parse.y"
                                                   { yyval = instarray(yyvsp[-3], yyvsp[0]); }
#line 1896 "y.tab.c"
    break;

  case 85:
#line 248 "parse.y"
                              { yyval = instrec(yyvsp[-2], yyvsp[-1]); }
#line 1902 "y.tab.c"
    break;

  case 86:
#line 252 "parse.y"
                         { yyval = instpoint(yyvsp[-1], yyvsp[0]); }
#line 1908 "y.tab.c"
    break;

  case 87:
#line 256 "parse.y"
                                     { yyval = cons(yyvsp[-2], yyvsp[0]); }
#line 1914 "y.tab.c"
    break;

  case 88:
#line 257 "parse.y"
                   { yyval = cons(yyvsp[0], NULL); }
#line 1920 "y.tab.c"
    break;

  case 89:
#line 261 "parse.y"
                    { yyval = findtype(yyvsp[0]); }
#line 1926 "y.tab.c"
    break;

  case 90:
#line 262 "parse.y"
                              { yyval = instenum(yyvsp[-1]); }
#line 1932 "y.tab.c"
    break;

  case 91:
#line 263 "parse.y"
                                 { yyval = instdotdot(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1938 "y.tab.c"
    break;

  case 92:
#line 267 "parse.y"
                                                      { yyval = findid(yyvsp[0]); }
#line 1944 "y.tab.c"
    break;

  case 93:
#line 268 "parse.y"
                                      { yyval = reducedot(yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1950 "y.tab.c"
    break;

  case 94:
#line 269 "parse.y"
                                                          { yyval = arrayref(yyvsp[-3],
            yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 1957 "y.tab.c"
    break;

  case 95:
#line 271 "parse.y"
                                                      { yyval = dopoint(yyvsp[-1], yyvsp[0]); }
#line 1963 "y.tab.c"
    break;


#line 1967 "y.tab.c"

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
#line 273 "parse.y"


/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.
  */

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


//helper methods to check if a token is real or integer
int isReal(TOKEN tok) {
  if(tok->basicdt == REAL)
    return 1;
  else 
    return 0;
}
int isInt(TOKEN tok) {
  if(tok->basicdt == INTEGER)
    return 1;
  else 
    return 0;
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

/* binop links a binary operator op to two operands, lhs and rhs. */
TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs){ 
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

/* copytok makes a new token that is a copy of origtok */
TOKEN copytok(TOKEN target) {
  TOKEN copy = talloc();
  copy->tokentype = target->tokentype;
  copy->basicdt = target->basicdt;
  copy->symtype = target->symtype;
  copy->symentry = target->symentry;
  copy->link = target->link;
  copy->whichval = target->whichval;
  copy->intval = target->intval;
  copy->realval = target->realval;
  if (DEBUG & DB_MAKECOPY) {
    printf("copytok\n");
    dbugprinttok(copy);
  }
  return copy;
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

/* makelabel makes a new label, using labelnumber++ */
TOKEN makelabel(){
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = LABELOP;
  tok->operands = makeintc(labelnumber++);
  return tok;

}

/* makegoto makes a GOTO operator to go to the specified label.
   The label number is put into a number token. */
TOKEN makegoto(int label){
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = GOTOOP;
  tok->operands = makeintc(label);
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


/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args)
  {  
     fn->link = args;
     tok->tokentype = OPERATOR;  
     tok->operands = fn;
     tok->whichval = FUNCALLOP;
    SYMBOL sym = searchst(fn->stringval);
    if (sym->datatype->datatype){
      tok->basicdt = sym->datatype->datatype->basicdt;
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

/* makewhile makes structures for a while statement.
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
  SYMBOL sym = searchst(tok->stringval);
  tok->symentry = sym;

  if (sym->kind == VARSYM){
    SYMBOL typ = sym->datatype;
    tok->symtype = typ;
    if ( typ->kind == BASICTYPE ||
        typ->kind == POINTERSYM)
        tok->basicdt = typ->basicdt;
  }
  //if symbol isn't var
  else{
    tok->tokentype = NUMBERTOK;
    if (sym->basicdt == INTEGER){
      tok->basicdt = INTEGER;
      tok->intval = sym->constval.intnum;
    }
    else if (sym->basicdt == REAL){
      tok->basicdt = REAL;
      tok->realval = sym->constval.realnum;
    }
  }
  return tok; 
}


/* findtype looks up a type name in the symbol table, puts the pointer
   to its type into tok->symtype, returns tok. */
TOKEN findtype(TOKEN tok){
  SYMBOL sym = searchst(tok->stringval);
  tok->symentry = sym;
  tok->symtype = sym;
  return tok;
}



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

/* dolabel is the action for a label of the form   <number>: <statement>
   tok is a (now) unused token that is recycled. */
TOKEN dolabel(TOKEN labeltok, TOKEN tok, TOKEN statement){
  tok = makeprogn(tok, labeltok);

  int labelValue = labeltok->intval;
  int labelIndex = -1;

  for(int i = 0; i < sizeof(labels) / sizeof(labels[0]); i++) {
    if (labels[i] == labelValue) {
      labelIndex = i;
      break;
    }
  }

  if (labelIndex == -1){
    fprintf(stderr, "Label not found\n");
    return NULL;
  }

  TOKEN indexToken = makeintc(labelIndex);
  labeltok->operands = indexToken;
  labeltok->link = statement;


  return tok;
  


}

/* instlabel installs a user label into the label table */
void  instlabel (TOKEN num){
  labels[labelnumber++] = num->intval;  

}

/* nconc concatenates two token lists, destructively, by making the last link
   of lista point to listb.
   (nconc '(a b) '(c d e))  =  (a b c d e)  */
/* nconc is useful for putting together two fieldlist groups to
   make them into a single list in a record declaration. */
/* nconc should return lista, or listb if lista is NULL. */
TOKEN nconc(TOKEN lista, TOKEN listb){

  if (lista == NULL){
    return listb;
  }

  TOKEN mover = lista;
  while(mover->link != NULL){
    mover = mover->link;
  }
  mover->link = listb;

  return lista;

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


/* instrec will install a record definition.  Each token in the linked list
   argstok has a pointer its type.  rectok is just a trash token to be
   used to return the result in its symtype */
TOKEN instrec(TOKEN rectok, TOKEN argstok){

  SYMBOL recordSymbol = symalloc();
  recordSymbol->kind = RECORDSYM;

  int offset = 0;
  int alignedSize = 0;

  TOKEN mover = argstok;

  SYMBOL prev = NULL;
  while (mover) {
    SYMBOL fieldSym = makesym(mover->stringval);
    fieldSym->datatype = mover->symtype;
    fieldSym->size = mover->symtype->size;
    fieldSym->link = NULL;

    alignedSize = alignsize(mover->symtype);
    fieldSym->offset = wordaddress(offset, alignedSize);
    offset = fieldSym->offset + fieldSym->size;

    if (prev == NULL){
      recordSymbol->datatype = fieldSym;
    } else {
      prev->link = fieldSym;
    }
    prev = fieldSym;

    mover = mover->link;
  }

  recordSymbol->size = wordaddress(offset, 16); //****
  rectok->symtype = recordSymbol;

  return rectok;
}

/* reducedot handles a record reference.
   dot is a (now) unused token that is recycled. */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field){

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


  return makearef(var, makeintc(fieldOffset), NULL);

}

/* makearef makes an array reference operation.
   off is be an integer constant token
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok){
  if (var->whichval == AREFOP && off->basicdt == INTEGER) {
    
    TOKEN off1 = var->operands->link;
    if (off1->whichval == PLUSOP) {
      int num = off1->operands->intval;  
      int num2 = off->intval;
      TOKEN newoff = makeintc(num + num2);
      newoff->link = off1->operands->link;
      off1->operands = newoff;
    }
  }

  TOKEN areftok = makeop(AREFOP);
  var->link = off;
  areftok->operands = var;
  areftok->symentry = var->symentry;   


  return areftok;
}
/* instarray installs an array declaration into the symbol table.
   bounds points to a SUBRANGE symbol table entry.
   The symbol table pointer is returned in token typetok. */
TOKEN instarray(TOKEN bounds, TOKEN typetok){
  if (bounds->link) {
    typetok = instarray(bounds->link, typetok);

    SYMBOL subrange = bounds->symtype;
    SYMBOL typesym = typetok->symtype;
    SYMBOL arraysym = symalloc();

    arraysym->kind = ARRAYSYM;
    arraysym->datatype = typesym;
    arraysym->lowbound = subrange->lowbound;
    arraysym->highbound = subrange->highbound;
    arraysym->size = (arraysym->lowbound + arraysym->highbound - 1) * (typesym->size);
    typetok->symtype = arraysym;


  return typetok;


  } else {

    SYMBOL subrange = bounds->symtype;
    SYMBOL typesym = typetok->symtype;
    SYMBOL arraysym = symalloc();
    arraysym->kind = ARRAYSYM;
    arraysym->datatype = typesym;
    arraysym->lowbound = subrange->lowbound;
    arraysym->highbound = subrange->highbound;
    arraysym->size = (arraysym->highbound - arraysym->lowbound +  1) * (typesym->size);
    typetok->symtype = arraysym;


    return typetok;
  }
}



/* arrayref processes an array reference a[i]
   subs is a list of subscript expressions.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN arrayref(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb) {
  if (subs->link) {
    TOKEN timesop = makeop(TIMESOP);
    int low = arr->symtype->lowbound;
    int high = arr->symtype->highbound;
    int size = (arr->symtype->size / (high + low - 1));

    TOKEN s = copytok(subs);
    s->link = NULL;
    TOKEN elesize = makeintc(size);
    elesize->link = s;
    timesop->operands = elesize;

    TOKEN nsize = makeintc(-1 * size);
    nsize->link = timesop;
    TOKEN plusop = makeop(PLUSOP);
    plusop->operands = nsize;

    TOKEN subarref = makearef(arr, plusop, tokb);
    
    subarref->symtype = arr->symtype->datatype;

    return arrayref(subarref, tok, subs->link, tokb);


  } else {
    TOKEN timesop = makeop(TIMESOP);
    int low = arr->symtype->lowbound;
    int high = arr->symtype->highbound;
    int size = (arr->symtype->size / (high + low - 1));

    TOKEN elesize = makeintc(size);
    elesize->link = subs;
    timesop->operands = elesize;

    TOKEN nsize = makeintc(-1 * size);
    nsize->link = timesop;
    TOKEN plusop = makeop(PLUSOP);
    plusop->operands = nsize;


    return makearef(arr, plusop, tokb);
  }

  
}

/* makesubrange makes a SUBRANGE symbol table entry, puts the pointer to it
   into tok, and returns tok. */
TOKEN makesubrange(TOKEN tok, int low, int high){

  SYMBOL subrange = symalloc();
  subrange->kind = SUBRANGE;
  subrange->basicdt = INTEGER;
  subrange->lowbound = low;
  subrange->highbound = high;
  subrange->size = basicsizes[INTEGER];
  tok->symtype = subrange;


  return tok;
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

  return tok;
}


/* instdotdot installs a .. subrange in the symbol table.
   dottok is a (now) unused token that is recycled. */
TOKEN instdotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok) {
  int low = lowtok->intval;
  int high = hightok->intval;


  return makesubrange(dottok, low, high);
}




/* wordaddress pads the offset n to be a multiple of wordsize.
   wordsize should be 4 for integer, 8 for real and pointers,
   16 for records and arrays */
int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
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


/* fillintc smashes tok, making it into an INTEGER constant with value num */
TOKEN fillintc(TOKEN tok, int num);


/* makepnb is like makeprogn, except that if statements is already a progn,
   it just returns statements.  This is optional. */
TOKEN makepnb(TOKEN tok, TOKEN statements);

/* appendst makes a progn containing statements followed by more */
TOKEN appendst(TOKEN statements, TOKEN more);

/* finds label number in label table for user defined labels */
int findlabelnumber(int label) {

  for(int i = 0; i < labelnumber; i ++) {
    if (labels[i] == label) {

      return i;
    }
  }
  return -1;
}

/* dogoto is the action for a goto statement.
   tok is a (now) unused token that is recycled. */
TOKEN dogoto(TOKEN tok, TOKEN labeltok){
    int real_label = findlabelnumber(labeltok->intval);
    if (real_label == -1) {
      printf("Error: user defined label not found");
    }  

    tok = makegoto(real_label);

    return tok;
}


/* settoktype sets up the type fields of token tok.
   typ = type pointer, ent = symbol table entry of the variable  */
void  settoktype(TOKEN tok, SYMBOL typ, SYMBOL ent);


/* makewhile makes structures for a while statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makewhile(TOKEN tok, TOKEN expr, TOKEN tokb, TOKEN statement) {
  
  TOKEN label = makelabel();
  int current = labelnumber - 1;
  tok = makeprogn(tok, label);

  TOKEN gototok = makegoto(current);
  statement->link = gototok;
  TOKEN body = makeprogn(tokb, statement);

  TOKEN ifs = talloc();
  ifs = makeif(ifs, expr, body, NULL);
  label->link = ifs;


  return tok;
  
}



/* searchins will search for symbol, inserting it if not present. */
SYMBOL searchins(char name[]);

/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void insttype(TOKEN typename, TOKEN typetok) {
  SYMBOL typesym = searchins(typename->stringval);
  typesym->kind = TYPESYM;
  typesym->datatype = typetok->symtype;
  typesym->size = typetok->symtype->size;


}

/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename) {

  SYMBOL typesym = searchins(typename->stringval);


  SYMBOL pointsym = symalloc();
  pointsym->datatype = typesym;
  pointsym->kind = POINTERSYM;
  pointsym->size = basicsizes[POINTER];
  pointsym->basicdt = POINTER;

  tok->symtype = pointsym;



  return tok;
}


/* makeplus makes a + operator.
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makeplus(TOKEN lhs, TOKEN rhs, TOKEN tok){
  tok = makeop(PLUSOP);
  return tok;
}

/* addint adds integer off to expression exp, possibly using tok */
TOKEN addint(TOKEN exp, TOKEN off, TOKEN tok);

/* addoffs adds offset, off, to an aref expression, exp */
TOKEN addoffs(TOKEN exp, TOKEN off);

/* mulint multiplies expression exp by integer n */
TOKEN mulint(TOKEN exp, int n);



/* dopoint handles a ^ operator.  john^ becomes (^ john) with type record
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok){
  tok->symentry = var->symentry->datatype->datatype;
  tok->operands = var;



  return tok;
}

