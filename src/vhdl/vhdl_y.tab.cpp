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


/* Substitute the variable and function names.  */
#define yyparse         yyvhdlparse
#define yylex           yyvhdllex
#define yyerror         yyvhdlerror
#define yydebug         yyvhdldebug
#define yynerrs         yyvhdlnerrs
#define yylval          yyvhdllval
#define yychar          yyvhdlchar

/* First part of user prologue.  */
#line 1 "parser.y"


// Based on BNF Syntax at
// http://tams-www.informatik.uni-hamburg.de/vhdl/tools/grammar/vhdl93-bnf.html

#include <cstring>
#include <iostream>

#include <util/dstring.h>

#include "vhdl_parser.h"

#define PARSER vhdl_parser
#define YYSTYPE vhdl_parsert::yystypet

#undef stack
#undef stack_type
#define stack(x) (PARSER.stack[x.stack_index])
#define stack_type(x) (static_cast<typet &>(static_cast<irept &>(PARSER.stack[x.stack_index])))

#define mto(x, y) stack(x).move_to_operands(stack(y))
#define mts(x, y) stack(x).move_to_sub(stack(y))

int yyvhdllex();
extern char *yyvhdltext;

/*******************************************************************\

Function: yyvhdlerror

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

extern YYSTYPE yyvhdllval;

int yyvhdlerror(const char *error_str)
{
  std::string tmp=error_str;
  if(yyvhdltext[0]!=0)
  {
    tmp+=" before `";
    tmp+=yyvhdltext;
    tmp+='\'';
  }
    
  source_locationt source_location;
  source_location.set_column(yyvhdllval.column);
  source_location.set_line(yyvhdllval.line);
  source_location.set_file(yyvhdllval.file);

  PARSER.error().source_location=source_location;
  PARSER.error() << tmp << messaget::eom;
                  
  return strlen(error_str)+1;
}

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void init(YYSTYPE &expr)
{
  newstack(expr.stack_index);
}

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void init(YYSTYPE &expr, const irep_idt &id)
{
  init(expr);
  stack(expr).id(id);
}

#line 99 "parser.y"

// http://www.csee.umbc.edu/portal/help/VHDL/operator.html

#line 178 "vhdl_y.tab.cpp"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YYVHDL_VHDL_Y_TAB_HPP_INCLUDED
# define YY_YYVHDL_VHDL_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yyvhdldebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_OR = 258,
    TOK_NOR = 259,
    TOK_XOR = 260,
    TOK_XNOR = 261,
    TOK_AND = 262,
    TOK_NAND = 263,
    TOK_NE = 264,
    TOK_GE = 265,
    TOK_LE = 266,
    TOK_SLL = 267,
    TOK_SRL = 268,
    TOK_SLA = 269,
    TOK_SRA = 270,
    TOK_ROL = 271,
    TOK_ROR = 272,
    UMINUS = 273,
    UPLUS = 274,
    TOK_MOD = 275,
    TOK_DOUBLE_STAR = 276,
    TOK_ABS = 277,
    TOK_NOT = 278,
    TOK_ARROW = 279,
    TOK_ASSIGN = 280,
    TOK_LEFT_LABEL_BRACKET = 281,
    TOK_RIGHT_LABEL_BRACKET = 282,
    TOK_BOX = 283,
    TOK_ACCESS = 284,
    TOK_AFTER = 285,
    TOK_ALIAS = 286,
    TOK_ALL = 287,
    TOK_ARCHITECTURE = 288,
    TOK_ARRAY = 289,
    TOK_ASSERT = 290,
    TOK_ATTRIBUTE = 291,
    TOK_BEGIN = 292,
    TOK_BLOCK = 293,
    TOK_BODY = 294,
    TOK_BUFFER = 295,
    TOK_BUS = 296,
    TOK_CASE = 297,
    TOK_COMPONENT = 298,
    TOK_CONFIGURATION = 299,
    TOK_CONSTANT = 300,
    TOK_DISCONNENT = 301,
    TOK_DOWNTO = 302,
    TOK_ELSE = 303,
    TOK_ELSIF = 304,
    TOK_END = 305,
    TOK_ENTITY = 306,
    TOK_EXIT = 307,
    TOK_FILE = 308,
    TOK_FOR = 309,
    TOK_FUNCTION = 310,
    TOK_GENERATE = 311,
    TOK_GENERIC = 312,
    TOK_GROUP = 313,
    TOK_GUARDED = 314,
    TOK_IF = 315,
    TOK_IMPURE = 316,
    TOK_IN = 317,
    TOK_INERTIAL = 318,
    TOK_INOUT = 319,
    TOK_IS = 320,
    TOK_LABEL = 321,
    TOK_LIBRARY = 322,
    TOK_LINKAGE = 323,
    TOK_LITERAL = 324,
    TOK_LOOP = 325,
    TOK_MAP = 326,
    TOK_NEW = 327,
    TOK_NEXT = 328,
    TOK_NULL = 329,
    TOK_OF = 330,
    TOK_ON = 331,
    TOK_OPEN = 332,
    TOK_OTHERS = 333,
    TOK_OUT = 334,
    TOK_PACKAGE = 335,
    TOK_PORT = 336,
    TOK_POSTPONED = 337,
    TOK_PROCEDURE = 338,
    TOK_PROCESS = 339,
    TOK_PROTECTED = 340,
    TOK_PURE = 341,
    TOK_RANGE = 342,
    TOK_RECORD = 343,
    TOK_REGISTER = 344,
    TOK_REJECT = 345,
    TOK_REM = 346,
    TOK_REPORT = 347,
    TOK_RETURN = 348,
    TOK_SELECT = 349,
    TOK_SEVERITY = 350,
    TOK_SIGNAL = 351,
    TOK_SUBTYPE = 352,
    TOK_THEN = 353,
    TOK_TO = 354,
    TOK_TRANSPORT = 355,
    TOK_TYPE = 356,
    TOK_UNAFFECTED = 357,
    TOK_UNITS = 358,
    TOK_UNTIL = 359,
    TOK_USE = 360,
    TOK_VARIABLE = 361,
    TOK_WAIT = 362,
    TOK_WHEN = 363,
    TOK_WHILE = 364,
    TOK_WITH = 365,
    TOK_NATURAL = 366,
    TOK_BASED_INTEGER = 367,
    TOK_STRING = 368,
    TOK_BIT_STRING = 369,
    TOK_CHAR = 370,
    TOK_IDENTIFIER = 371
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yyvhdllval;

int yyvhdlparse (void);

#endif /* !YY_YYVHDL_VHDL_Y_TAB_HPP_INCLUDED  */



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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1517

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  133
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  198
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  554

#define YYUNDEFTOK  2
#define YYMAXUTOK   371


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    23,   127,
     130,   131,    27,    21,   126,    22,   128,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   129,   125,
      11,     9,    12,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   132,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,    10,    13,    14,    15,    16,    17,
      18,    19,    20,    24,    25,    26,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   231,   231,   233,   237,   238,   242,   243,   247,   248,
     252,   258,   263,   271,   277,   278,   282,   289,   298,   302,
     303,   307,   308,   312,   323,   326,   334,   342,   349,   356,
     363,   374,   377,   385,   388,   394,   395,   399,   404,   408,
     413,   418,   427,   432,   440,   443,   449,   454,   462,   469,
     473,   480,   483,   486,   487,   491,   495,   499,   503,   508,
     512,   516,   520,   525,   533,   537,   542,   550,   551,   555,
     556,   559,   563,   568,   576,   577,   587,   591,   598,   612,
     615,   623,   630,   638,   645,   650,   658,   663,   672,   675,
     683,   690,   694,   698,   703,   711,   719,   726,   735,   748,
     751,   756,   759,   766,   769,   772,   778,   783,   791,   798,
     801,   809,   812,   819,   822,   830,   838,   846,   853,   863,
     873,   879,   885,   888,   900,   903,   911,   914,   922,   925,
     931,   938,   942,   948,   953,   961,   962,   966,   971,   979,
     983,   988,   997,   999,  1005,  1010,  1018,  1019,  1025,  1030,
    1038,  1044,  1045,  1050,  1058,  1062,  1063,  1067,  1071,  1072,
    1077,  1078,  1085,  1092,  1099,  1106,  1114,  1121,  1124,  1130,
    1136,  1142,  1148,  1154,  1160,  1166,  1172,  1178,  1184,  1190,
    1196,  1202,  1208,  1214,  1220,  1226,  1232,  1238,  1244,  1250,
    1257,  1261,  1267,  1273,  1279,  1285,  1291,  1300,  1305
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"OR\"", "\"NOR\"", "\"XOR\"",
  "\"XNOR\"", "\"AND\"", "\"NAND\"", "'='", "\"/=\"", "'<'", "'>'",
  "\">=\"", "\"<=\"", "\"SLL\"", "\"SRL\"", "\"SLA\"", "\"SRA\"",
  "\"ROL\"", "\"ROR\"", "'+'", "'-'", "'&'", "UMINUS", "UPLUS", "\"MOD\"",
  "'*'", "'/'", "\"**\"", "\"ABS\"", "\"NOT\"", "\"=>\"", "\":=\"",
  "\"<<\"", "\">>\"", "\"<>\"", "\"ACCESS\"", "\"AFTER\"", "\"ALIAS\"",
  "\"ALL\"", "\"ARCHITECTURE\"", "\"ARRAY\"", "\"ASSERT\"",
  "\"ATTRIBUTE\"", "\"BEGIN\"", "\"BLOCK\"", "\"BODY\"", "\"BUFFER\"",
  "\"BUS\"", "\"CASE\"", "\"COMPONENT\"", "\"CONFIGURATION\"",
  "\"CONSTANT\"", "\"DISCONNENT\"", "\"DOWNTO\"", "\"ELSE\"", "\"ELSIF\"",
  "\"END\"", "\"ENTITY\"", "\"EXIT\"", "\"FILE\"", "\"FOR\"",
  "\"FUNCTION\"", "\"GENERATE\"", "\"GENERIC\"", "\"GROUP\"",
  "\"GUARDED\"", "\"IF\"", "\"IMPURE\"", "\"IN\"", "\"INERTIAL\"",
  "\"INOUT\"", "\"IS\"", "\"LABEL\"", "\"LIBRARY\"", "\"LINKAGE\"",
  "\"LITERAL\"", "\"LOOP\"", "\"MAP\"", "\"NEW\"", "\"NEXT\"", "\"NULL\"",
  "\"OF\"", "\"ON\"", "\"OPEN\"", "\"OTHERS\"", "\"OUT\"", "\"PACKAGE\"",
  "\"PORT\"", "\"POSTPONED\"", "\"PROCEDURE\"", "\"PROCESS\"",
  "\"PROTECTED\"", "\"PURE\"", "\"RANGE\"", "\"RECORD\"", "\"REGISTER\"",
  "\"REJECT\"", "\"REM\"", "\"REPORT\"", "\"RETURN\"", "\"SELECT\"",
  "\"SEVERITY\"", "\"SIGNAL\"", "\"SUBTYPE\"", "\"THEN\"", "\"TO\"",
  "\"TRANSPORT\"", "\"TYPE\"", "\"UNAFFECTED\"", "\"UNITS\"", "\"UNTIL\"",
  "\"USE\"", "\"VARIABLE\"", "\"WAIT\"", "\"WHEN\"", "\"WHILE\"",
  "\"WITH\"", "TOK_NATURAL", "TOK_BASED_INTEGER", "TOK_STRING",
  "TOK_BIT_STRING", "TOK_CHAR", "TOK_IDENTIFIER", "';'", "','", "'\\''",
  "'.'", "':'", "'('", "')'", "'|'", "$accept", "design_file",
  "design_unit", "context_clause", "context_item", "use_clause",
  "name_list", "name", "selected_name", "library_clause", "library_unit",
  "primary_unit", "package_declaration", "package_declarative_part",
  "package_declarative_item", "physical_units_opt",
  "secondary_physical_units", "secondary_unit", "package",
  "package_body_declarative_part", "entity_declaration", "generic_list",
  "generic", "port_list", "port", "dir", "type",
  "element_declaration_list", "element_declaration", "identifier_list",
  "index_constraint_list", "index_constraint", "enumeration_literal_list",
  "enumeration_literal", "updown", "architecture",
  "architecture_decl_list", "architecture_decl", "s_list",
  "architecture_body", "architecture_item", "name_opt", "label_opt",
  "with_list", "with_item_list", "with_item", "process_decl_list",
  "process_decl", "process_body", "process_item", "assert_report_opt",
  "assert_severity_opt", "elsepart", "cases", "with_value_list",
  "with_value", "signal_list", "sigvalue", "delay_opt", "map_list",
  "map_item", "generic_map_list", "generic_map_item", "signal", "choice",
  "choices", "element_association", "element_association_list", "expr",
  "expr_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,    61,
     264,    60,    62,   265,   266,   267,   268,   269,   270,   271,
     272,    43,    45,    38,   273,   274,   275,    42,    47,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,    59,    44,    39,    46,    58,
      40,    41,   124
};
# endif

#define YYPACT_NINF (-427)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-133)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -427,    38,  -427,  -100,  -100,  -100,   -17,  -100,  -427,   347,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,   -64,  -427,   -55,   -94,     4,  -100,    -5,   339,  -427,
    -427,  -100,   -85,   -26,   -23,  -427,  -100,    29,  -427,  -427,
      44,  -427,  -427,  -427,  -100,   -83,   -49,     4,  -427,   137,
    -427,     4,    95,  -100,  -100,    58,  -100,  -100,  -100,  -100,
    -100,  -427,   260,  -427,     4,    94,  -427,    51,   160,  -427,
     111,   105,   380,   444,   161,   153,   250,  -427,  -100,  -100,
    -100,  -100,  -427,  -100,   187,  -100,   194,  -100,   240,   -43,
    -427,   194,   194,  -427,  -100,   194,   -12,    25,   447,   199,
     341,  -427,   230,     4,   194,   255,   318,   328,   213,   271,
     279,    69,   121,   276,  -427,   349,  -427,  -427,   194,   284,
     282,   202,   306,  -100,   213,   394,  -427,    81,   405,   314,
     324,   194,   194,   329,   344,  -427,   213,   194,   334,   213,
     213,   213,   -50,  -427,  -427,  -427,    64,   211,  -427,  1018,
    -427,   -21,  -427,    67,  -427,  -427,     4,   107,  -427,   213,
     452,  -100,  -427,  -427,   466,   213,  -427,  -100,   356,   359,
    1182,  -100,   213,  -100,   213,   -34,   213,  -100,  -100,   357,
     368,    69,  -100,   352,   173,  -427,  1018,  -427,  -427,   581,
     581,  -427,  -427,     4,  -427,  -427,   -22,  -427,   289,   256,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   213,   213,   213,  -427,  -427,   213,   398,  -427,
    -427,   194,    69,  -427,   195,   213,   373,   213,  1018,   374,
    -427,  -427,  -100,   228,   420,  1018,   432,   434,  1361,  -427,
    -100,  -427,  1453,   176,   183,   504,  -427,   297,   191,   213,
     213,   443,   213,   213,   431,   431,  -427,  -427,  1018,   300,
     822,   822,   822,   822,   822,   822,   684,   684,   684,   684,
     684,   684,   469,   469,   469,   469,   469,   469,   581,   581,
     581,  -427,  -427,  -427,  1489,  -100,   407,  -427,  -427,   213,
    1489,  -427,   863,   213,  -427,   529,   470,   473,   -75,   213,
     213,  -427,   308,   303,  -427,   426,   116,   430,   436,   213,
     479,   485,   438,  -427,   194,  1489,  1489,  -427,  -427,   213,
    -427,  -427,  -427,   640,  -427,   891,   -13,   213,   427,   433,
     446,   734,  1044,     0,   213,   519,   487,  -100,   213,   493,
     412,   576,  -427,   126,  -100,  -427,  -100,   213,  -427,   532,
     564,   918,  -427,   566,    60,  -427,  1489,  -427,  -427,   514,
      17,   501,   502,  -427,  1453,  -100,  -100,  -427,  -427,   213,
     213,   563,  1313,  -100,  -427,   559,  1127,  -427,  -427,   213,
     213,   213,  -427,    -9,     4,   795,   500,   580,  -427,  -100,
     503,  -100,   513,  -427,   213,   517,    20,   505,   509,     8,
     533,   539,  -427,  1387,  1426,  -100,   524,   544,   213,  -427,
    1208,  -427,   944,  -427,  -100,  -427,   213,  -427,  -100,   545,
     546,   311,  -427,  -100,  -427,  1453,   103,   660,   584,  -100,
     662,   550,  -100,  -427,  -427,   551,   224,   619,  -427,  1074,
     238,   213,   577,  -427,   331,   312,  -427,   236,  -427,  -427,
     442,   565,  -427,  -427,     4,   552,  -427,   213,   604,  -427,
    -100,  -427,  -427,     1,    36,  -427,   676,    -2,   636,   213,
     213,  -427,   213,   629,  1489,   213,   567,   598,   194,   568,
    -427,   273,   325,  1489,   561,  -427,   630,   631,   685,   697,
     571,  1237,  1283,   342,  1156,   645,  1489,  -427,  -100,   246,
     656,  -427,  -427,  -100,  -100,  -100,  -427,  -427,  -427,  -427,
    -427,  -427,   590,   592,  -427,   709,   668,   589,   596,   597,
     390,   292,   496,   555,   238,  -427,  -427,   213,   599,   600,
    -427,  -427,  -427,   648,   650,  -427,   986,  -427,  -427,   605,
     606,  -427,  -427,  -427
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     3,     0,
       6,     9,     8,     5,    19,    22,    20,    36,    21,    35,
      13,     0,    14,     0,     0,    11,     0,     0,     0,     7,
       4,     0,     0,     0,     0,    18,     0,     0,    24,    10,
       0,    15,    17,    16,    99,     0,     0,    12,    38,     0,
      79,   100,     0,     0,     0,     0,     0,     0,    99,     0,
       0,    25,     0,    39,    86,     0,    42,     0,     0,    46,
       0,     0,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,    80,     0,     0,     0,     0,     0,     0,     0,
      37,     0,     0,    23,     0,     0,   101,     0,     0,     0,
       0,    43,     0,    87,     0,     0,     0,     0,     0,     0,
       0,     0,    53,    45,    47,     0,    49,    50,     0,     0,
       0,     0,    31,    99,     0,   151,    89,     0,     0,     0,
       0,     0,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     0,   164,   161,   162,   163,     0,   151,   160,     0,
      65,     0,    62,     0,    59,    75,    74,     0,    72,     0,
       0,    99,    48,    30,     0,     0,    28,     0,     0,     0,
       0,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   151,     0,    67,     0,    60,    61,   170,
     169,   182,   166,   165,   154,   155,     0,   158,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    76,    77,     0,     0,    63,
      66,     0,     0,    54,     0,     0,     0,     0,     0,     0,
      27,    78,     0,     0,   151,     0,   151,     0,     0,   113,
       0,    90,   142,     0,     0,     0,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   167,   190,   197,     0,
     185,   186,   187,   188,   183,   184,   191,   196,   194,   192,
     193,   195,   173,   174,   175,   176,   177,   178,   171,   172,
     168,   181,   179,   180,    55,    99,     0,    73,    52,     0,
      44,    40,     0,     0,    33,     0,     0,     0,     0,     0,
       0,    88,   101,     0,   137,     0,     0,     0,     0,     0,
       0,     0,   151,    68,     0,    71,   157,   156,   159,     0,
     189,    57,    64,     0,    26,     0,     0,     0,     0,     0,
       0,     0,     0,   101,     0,     0,     0,     0,     0,     0,
     151,     0,   114,     0,     0,   109,     0,     0,   139,     0,
       0,     0,    83,     0,     0,    56,   198,    51,    29,     0,
       0,     0,   103,   106,   142,     0,     0,   153,   152,     0,
       0,     0,     0,    99,   121,     0,     0,   122,   102,     0,
       0,     0,   138,     0,   143,     0,     0,     0,    82,    99,
       0,    99,     0,    91,     0,     0,     0,     0,   148,   151,
       0,   144,   146,     0,     0,    99,     0,     0,     0,   113,
     124,   116,     0,   113,     0,   110,     0,   140,     0,     0,
       0,   153,    32,     0,   107,   142,     0,     0,     0,     0,
       0,     0,     0,    88,    88,     0,     0,     0,    95,     0,
     101,     0,   126,   115,   101,     0,   141,     0,    84,    41,
       0,     0,   105,   135,   136,   108,   133,     0,     0,   149,
       0,    92,   145,   101,   101,    96,     0,     0,     0,     0,
       0,   113,     0,     0,   125,     0,     0,     0,     0,     0,
      34,     0,     0,   150,     0,   147,     0,     0,     0,     0,
       0,     0,     0,   101,     0,     0,   127,   123,    99,     0,
       0,   104,   134,     0,    99,    99,   113,   113,   120,   113,
     113,   113,     0,     0,   111,     0,     0,     0,     0,     0,
     101,   101,   101,   101,   101,   117,    94,     0,     0,     0,
      98,    97,   131,     0,     0,   129,     0,    85,    93,     0,
       0,   112,   119,   118
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -427,  -427,  -427,  -427,   720,  -427,   725,    -3,  -427,  -427,
     724,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,   557,   652,  -170,   677,  -427,   -70,  -427,   612,  -427,
    -427,   506,   586,   537,  -134,  -427,  -427,  -427,   -40,  -302,
    -427,   -52,   -91,  -427,  -427,   361,  -427,  -427,  -354,  -427,
    -427,  -427,   239,   241,   330,   283,  -427,  -244,  -314,  -426,
    -427,   335,  -427,     3,   515,  -427,   512,  -427,   379,  -427
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     8,     9,    10,    11,    24,   147,    22,    12,
      13,    14,    15,    49,    61,   168,   336,    16,    17,    55,
      18,    65,    66,    68,    69,   118,   113,   151,   152,   153,
     184,   185,   157,   158,   309,    19,    62,    82,    70,    96,
     126,    52,   351,   371,   372,   373,   393,   425,   312,   352,
     452,   486,   483,   447,   465,   466,   313,   251,   316,   410,
     411,   407,   408,   148,   195,   196,   197,   198,   252,   269
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      21,    23,    25,    27,    25,   127,    74,   499,   254,   343,
     263,   249,   258,    67,    42,   227,   472,   440,    34,    31,
     340,   119,   120,    37,    20,   122,   402,   116,    40,   437,
      26,    35,    36,    47,   135,    44,   423,   228,     2,    41,
      99,    51,    45,    67,   117,   369,   123,    53,   162,    41,
      64,    64,   262,    72,    73,    51,    75,    76,   381,   496,
     405,   179,   180,    32,    33,   450,    46,   187,    38,   454,
     192,   169,    32,    33,    20,    97,    98,    64,   100,     3,
      64,    54,   103,   112,    64,   139,   140,   527,   112,   112,
     129,   121,   112,   125,   497,   141,   250,     4,    43,   128,
     299,   112,    48,   150,   303,   424,   124,    20,   156,   236,
     264,    20,    20,     5,   130,   112,    71,    50,   124,   124,
      51,   461,    32,    33,    20,    20,     6,   503,   112,   112,
     492,    32,    33,   183,   112,    32,    33,    67,   172,   193,
     390,   473,   474,   173,    32,    33,   421,    32,    33,   174,
     194,     7,    32,    33,   124,   400,    32,    33,    51,   391,
      20,   296,   530,   531,   239,   532,   533,   534,   243,   244,
     246,    32,    33,   175,    64,    64,   247,    85,   156,    64,
      86,    56,   456,   142,    41,   143,   144,   145,    20,   462,
      57,   230,   155,    20,   146,    58,   231,   244,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,    83,
      63,   222,   223,   224,   463,    84,    94,    20,   112,   156,
      90,   104,   357,   232,   139,   140,   105,    85,   233,   246,
      89,   358,    59,   331,   141,   305,    60,   246,    32,    33,
     225,   159,   127,   314,   365,   106,   322,   183,   457,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
      32,    33,   222,   223,   224,    87,    93,   107,   344,   108,
     109,    88,    51,   306,   481,   482,  -128,   165,   346,   260,
     347,    83,   226,   110,   261,    77,   348,   317,    87,   350,
     476,    78,   102,    79,   318,   353,    87,   307,    20,   134,
     349,   112,   321,    95,   111,    85,   298,   166,   132,    32,
      33,   417,   142,   370,   143,   144,   145,    20,    32,    33,
     125,   200,   344,   146,   246,   463,   128,   430,    20,   432,
     385,   246,   346,   394,   347,    32,    33,   392,   344,   511,
     348,    87,    20,   445,    80,   115,   345,   489,   346,    81,
     347,   524,   406,   409,   349,   525,   348,    32,    33,   412,
      51,   344,   127,   127,   455,   136,   138,   267,     3,   487,
     349,   346,   344,   347,   463,   150,    51,    20,    51,   348,
    -130,   137,   346,   154,   347,   160,     4,   161,   446,   163,
     348,   164,    51,   349,   133,   265,    20,   167,   509,   176,
     266,    64,     5,   232,   349,    64,   329,   188,   320,   354,
     460,   330,    20,   464,   355,     6,   406,   -70,    85,   409,
     344,   488,   -70,   464,   177,   412,   463,   350,  -132,    20,
     346,   350,   347,   353,   178,    20,   523,   353,   348,   181,
       7,   235,   528,   529,    39,    36,    20,   246,    32,    33,
     125,   125,   349,   495,   182,   237,   128,   128,   -69,    32,
      33,   240,   259,   -69,   241,   112,   255,   149,   464,   464,
     219,   220,   221,   256,   295,   222,   223,   224,   301,   304,
     350,    32,    33,   170,   310,    51,   353,    32,    33,    91,
     409,    51,    51,   319,    20,   186,   412,   194,   189,   190,
     191,    32,    33,   171,   172,   199,   324,   350,   350,   350,
     350,   350,   332,   353,   353,   353,   353,   353,   234,    32,
      33,   388,   172,   337,   238,   356,   344,   308,    33,   338,
     200,   245,   339,   248,   543,   359,   346,   375,   347,    32,
      33,   360,   172,   376,   348,   364,    33,   490,   200,    32,
      33,    32,    33,    92,    32,    33,   131,   377,   349,   268,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   362,   344,   294,   222,   223,   224,
     363,   383,   384,   544,   300,   346,   302,   347,   387,   389,
      20,   396,   397,   348,   399,   401,   403,   415,   404,   418,
     428,   429,   433,   436,   431,   439,   438,   349,   268,   186,
     446,   325,   326,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   441,   442,   222,   223,   224,   448,
     458,   459,   467,   468,   470,   471,   475,   478,   333,    20,
     485,   491,   335,   494,   492,   498,   500,   505,   341,   342,
     508,   513,   507,   510,   514,   515,   518,   516,   361,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   366,   517,
     222,   223,   224,   522,   526,   535,   374,   536,   537,   538,
     539,   540,   541,   382,   547,   548,   549,   386,   550,    29,
     552,   553,    28,    30,   253,   101,   395,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   413,   414,
     222,   223,   224,   229,   114,   434,   323,   257,   420,   297,
     422,   367,   542,   545,   469,   512,   477,   328,     0,   327,
       0,     0,     0,   435,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   449,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,     0,
       0,   222,   223,   224,     0,     0,     0,     0,     0,     0,
     484,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   493,     0,   222,   223,
     224,   426,     0,     0,     0,     0,     0,     0,   501,   502,
       0,   504,     0,     0,   506,   378,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,     0,     0,   222,
     223,   224,     0,     0,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,     0,   546,   222,   223,   224,
     427,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,     0,     0,   222,   223,   224,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,     0,     0,
     222,   223,   224,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   334,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
       0,     0,   222,   223,   224,     0,   368,     0,     0,     0,
       0,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,     0,   398,   222,   223,   224,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,     0,   453,
     222,   223,   224,   225,     0,     0,     0,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,     0,   379,
     222,   223,   224,     0,     0,     0,     0,     0,     0,     0,
       0,   551,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   226,     0,     0,     0,   479,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   380,     0,   222,   223,   224,     0,     0,     0,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
       0,   480,   222,   223,   224,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,     0,     0,   222,   223,
     224,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,     0,   419,   222,   223,   224,     0,     0,     0,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,     0,   521,   222,   223,   224,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   242,     0,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,     0,   451,   222,
     223,   224,     0,     0,     0,   519,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,     0,     0,   222,
     223,   224,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   520,     0,     0,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,     0,   416,   222,   223,   224,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,     0,     0,   222,   223,   224,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   311,     0,     0,     0,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
       0,   443,   222,   223,   224,     0,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,     0,     0,   222,
     223,   224,     0,     0,     0,     0,     0,     0,     0,     0,
     444,   315,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,     0,     0,   222,   223,   224
};

static const yytype_int16 yycheck[] =
{
       3,     4,     5,     6,     7,    96,    58,     9,   178,   311,
      32,    45,   182,    53,    40,   149,   442,     9,    73,    83,
      95,    91,    92,    26,   124,    95,     9,    70,    31,     9,
      47,   125,   126,    36,   104,    58,    45,    58,     0,   124,
      80,    44,    65,    83,    87,    58,    58,   130,   118,   124,
      53,    54,   186,    56,    57,    58,    59,    60,    58,    58,
     374,   131,   132,   127,   128,   419,    89,   137,    73,   423,
     120,   123,   127,   128,   124,    78,    79,    80,    81,    41,
      83,   130,    85,    86,    87,    21,    22,   513,    91,    92,
      65,    94,    95,    96,    58,    31,   130,    59,   124,    96,
     234,   104,    73,   124,   238,   114,   118,   124,   111,   161,
     132,   124,   124,    75,    89,   118,    58,    73,   118,   118,
     123,   435,   127,   128,   124,   124,    88,   481,   131,   132,
     132,   127,   128,   136,   137,   127,   128,   177,   130,   142,
      14,   443,   444,    62,   127,   128,   390,   127,   128,    68,
      86,   113,   127,   128,   118,    95,   127,   128,   161,    33,
     124,   231,   516,   517,   167,   519,   520,   521,   171,   172,
     173,   127,   128,    92,   177,   178,   173,   126,   181,   182,
     129,    44,   426,   119,   124,   121,   122,   123,   124,    86,
      53,   124,   123,   124,   130,    58,   129,   200,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,   125,
     125,    26,    27,    28,   121,   131,    73,   124,   231,   232,
     125,    37,   116,   126,    21,    22,    42,   126,   131,   242,
     129,   125,   105,   295,    31,   242,   109,   250,   127,   128,
      55,   130,   343,   250,   324,    61,   259,   260,   428,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     127,   128,    26,    27,    28,   125,   125,    93,    50,    95,
      96,   131,   295,    65,    56,    57,    58,    95,    60,   126,
      62,   125,   107,   109,   131,    45,    68,   131,   125,   312,
      86,    51,   125,    53,   131,   312,   125,    89,   124,    89,
      82,   324,   131,    73,   130,   126,   131,   125,   129,   127,
     128,   383,   119,   336,   121,   122,   123,   124,   127,   128,
     343,   130,    50,   130,   347,   121,   343,   399,   124,   401,
     347,   354,    60,   356,    62,   127,   128,   354,    50,    86,
      68,   125,   124,   415,   104,   125,    58,   131,    60,   109,
      62,   125,   375,   376,    82,   129,    68,   127,   128,   376,
     383,    50,   473,   474,   424,   130,    58,   131,    41,    58,
      82,    60,    50,    62,   121,   124,   399,   124,   401,    68,
      58,    83,    60,   124,    62,   129,    59,    58,   116,   125,
      68,   129,   415,    82,    73,   126,   124,   111,   488,    14,
     131,   424,    75,   126,    82,   428,   126,    93,   131,   126,
     433,   131,   124,   436,   131,    88,   439,   126,   126,   442,
      50,   129,   131,   446,   130,   442,   121,   450,    58,   124,
      60,   454,    62,   450,   130,   124,   508,   454,    68,   130,
     113,     9,   514,   515,   125,   126,   124,   470,   127,   128,
     473,   474,    82,   470,   130,     9,   473,   474,   126,   127,
     128,   125,   130,   131,   125,   488,   129,   108,   491,   492,
      21,    22,    23,   125,    96,    26,    27,    28,   125,   125,
     503,   127,   128,   124,    70,   508,   503,   127,   128,   129,
     513,   514,   515,     9,   124,   136,   513,    86,   139,   140,
     141,   127,   128,   129,   130,   146,    83,   530,   531,   532,
     533,   534,   125,   530,   531,   532,   533,   534,   159,   127,
     128,   129,   130,    14,   165,   119,    50,   127,   128,    79,
     130,   172,    79,   174,    58,   125,    60,   130,    62,   127,
     128,   125,   130,   130,    68,   127,   128,   125,   130,   127,
     128,   127,   128,   129,   127,   128,   129,   131,    82,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   125,    50,   227,    26,    27,    28,
     125,    92,   125,    58,   235,    60,   237,    62,   125,    43,
     124,    89,    58,    68,    58,   111,   125,    64,   126,    70,
     130,    51,   119,   116,   131,   126,   131,    82,   259,   260,
     116,   262,   263,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,   131,   126,    26,    27,    28,   125,
     125,   125,    12,    89,    12,   125,   125,    58,   299,   124,
     103,   116,   303,    79,   132,     9,    50,    58,   309,   310,
      92,   130,   125,   125,    64,    64,   125,    12,   319,    15,
      16,    17,    18,    19,    20,    21,    22,    23,   329,    12,
      26,    27,    28,    68,    58,   125,   337,   125,     9,    51,
     131,   125,   125,   344,   125,   125,    78,   348,    78,     9,
     125,   125,     7,     9,   177,    83,   357,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,   379,   380,
      26,    27,    28,   151,    87,   404,   260,   181,   389,   232,
     391,   131,   531,   534,   439,   492,   446,   265,    -1,   264,
      -1,    -1,    -1,   404,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   418,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
     451,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,   467,    -1,    26,    27,
      28,    56,    -1,    -1,    -1,    -1,    -1,    -1,   479,   480,
      -1,   482,    -1,    -1,   485,   131,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    26,
      27,    28,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,   537,    26,    27,    28,
     125,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    26,    27,    28,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    26,    27,    28,    -1,   125,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,   125,    26,    27,    28,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,   125,
      26,    27,    28,    55,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    55,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,    -1,    -1,    -1,    55,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,   107,    -1,    26,    27,    28,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,   107,    26,    27,    28,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      28,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,   106,    26,    27,    28,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,   106,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,   100,    26,
      27,    28,    -1,    -1,    -1,    78,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    73,    26,    27,    28,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    64,    26,    27,    28,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    38,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    26,    27,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   134,     0,    41,    59,    75,    88,   113,   135,   136,
     137,   138,   142,   143,   144,   145,   150,   151,   153,   168,
     124,   140,   141,   140,   139,   140,    47,   140,   139,   137,
     143,    83,   127,   128,    73,   125,   126,   140,    73,   125,
     140,   124,    40,   124,    58,    65,    89,   140,    73,   146,
      73,   140,   174,   130,   130,   152,    44,    53,    58,   105,
     109,   147,   169,   125,   140,   154,   155,   171,   156,   157,
     171,    58,   140,   140,   174,   140,   140,    45,    51,    53,
     104,   109,   170,   125,   131,   126,   129,   125,   131,   129,
     125,   129,   129,   125,    73,    73,   172,   140,   140,   171,
     140,   155,   125,   140,    37,    42,    61,    93,    95,    96,
     109,   130,   140,   159,   157,   125,    70,    87,   158,   159,
     159,   140,   159,    58,   118,   140,   173,   175,   196,    65,
      89,   129,   129,    73,    89,   159,   130,    83,    58,    21,
      22,    31,   119,   121,   122,   123,   130,   140,   196,   201,
     124,   160,   161,   162,   124,   123,   140,   165,   166,   130,
     129,    58,   159,   125,   129,    95,   125,   111,   148,   174,
     201,   129,   130,    62,    68,    92,    14,   130,   130,   159,
     159,   130,   130,   140,   163,   164,   201,   159,    93,   201,
     201,   201,   120,   140,    86,   197,   198,   199,   200,   201,
     130,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    26,    27,    28,    55,   107,   167,    58,   161,
     124,   129,   126,   131,   201,     9,   174,     9,   201,   140,
     125,   125,   102,   140,   140,   201,   140,   196,   201,    45,
     130,   190,   201,   154,   156,   129,   125,   165,   156,   130,
     126,   131,   167,    32,   132,   126,   131,   131,   201,   202,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,    96,   159,   166,   131,   167,
     201,   125,   201,   167,   125,   196,    65,    89,   127,   167,
      70,    64,   181,   189,   196,    38,   191,   131,   131,     9,
     131,   131,   140,   164,    83,   201,   201,   197,   199,   126,
     131,   174,   125,   201,   125,   201,   149,    14,    79,    79,
      95,   201,   201,   172,    50,    58,    60,    62,    68,    82,
     140,   175,   182,   196,   126,   131,   119,   116,   125,   125,
     125,   201,   125,   125,   127,   159,   201,   131,   125,    58,
     140,   176,   177,   178,   201,   130,   130,   131,   131,    55,
     107,    58,   201,    92,   125,   196,   201,   125,   129,    43,
      14,    33,   196,   179,   140,   201,    89,    58,   125,    58,
      95,   111,     9,   125,   126,   191,   140,   194,   195,   140,
     192,   193,   196,   201,   201,    64,    73,   174,    70,   106,
     201,   190,   201,    45,   114,   180,    56,   125,   130,    51,
     174,   131,   174,   119,   178,   201,   116,     9,   131,   126,
       9,   131,   126,    64,    64,   174,   116,   186,   125,   201,
     181,   100,   183,   125,   181,   171,   190,   156,   125,   125,
     140,   191,    86,   121,   140,   187,   188,    12,    89,   194,
      12,   125,   192,   172,   172,   125,    86,   187,    58,    55,
     107,    56,    57,   185,   201,   103,   184,    58,   129,   131,
     125,   116,   132,   201,    79,   196,    58,    58,     9,     9,
      50,   201,   201,   181,   201,    58,   201,   125,    92,   159,
     125,    86,   188,   130,    64,    64,    12,    12,   125,    78,
      78,   106,    68,   174,   125,   129,    58,   192,   174,   174,
     181,   181,   181,   181,   181,   125,   125,     9,    51,   131,
     125,   125,   186,    58,    58,   185,   201,   125,   125,    78,
      78,   125,   125,   125
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     138,   139,   139,   140,   140,   140,   141,   141,   142,   143,
     143,   144,   144,   145,   146,   146,   147,   147,   147,   147,
     147,   148,   148,   149,   149,   150,   150,   151,   152,   153,
     153,   153,   154,   154,   155,   155,   156,   156,   157,   158,
     158,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   160,   160,   161,   162,   162,   163,   163,   164,
     164,   164,   165,   165,   166,   166,   167,   167,   168,   169,
     169,   170,   170,   170,   170,   170,   171,   171,   172,   172,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   174,
     174,   175,   175,   176,   176,   176,   177,   177,   178,   179,
     179,   180,   180,   181,   181,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   183,   183,   184,   184,   185,   185,
     185,   186,   186,   187,   187,   188,   188,   189,   189,   190,
     190,   190,   191,   191,   192,   192,   193,   193,   194,   194,
     195,   196,   196,   196,   197,   198,   198,   199,   200,   200,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   202,   202
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     2,     1,     1,
       3,     1,     3,     1,     1,     3,     3,     3,     3,     1,
       1,     1,     1,     7,     0,     2,     8,     6,     5,     9,
       5,     0,     7,     0,     6,     1,     1,     7,     0,     6,
      11,    16,     1,     3,     6,     3,     1,     3,     4,     1,
       1,     6,     4,     1,     3,     4,     6,     5,     2,     2,
       3,     3,     1,     2,     4,     1,     2,     1,     3,     1,
       6,     3,     1,     3,     1,     1,     1,     1,    11,     0,
       2,     5,     8,     7,    10,    15,     1,     3,     0,     2,
       3,     7,     9,    14,    12,     8,     9,    13,    13,     0,
       1,     0,     2,     1,     6,     4,     1,     3,     4,     0,
       2,     5,     8,     0,     2,     4,     3,     8,    11,    11,
       7,     2,     2,     6,     0,     2,     0,     2,     0,     5,
       2,     6,     5,     1,     3,     1,     1,     1,     3,     3,
       5,     6,     0,     3,     1,     3,     1,     4,     1,     3,
       4,     1,     6,     6,     1,     1,     3,     3,     1,     3,
       1,     1,     1,     1,     1,     2,     2,     3,     3,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     4,
       3,     3,     3,     3,     3,     3,     3,     1,     3
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
  case 10:
#line 253 "parser.y"
       {
       }
#line 2108 "vhdl_y.tab.cpp"
    break;

  case 11:
#line 259 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 2117 "vhdl_y.tab.cpp"
    break;

  case 12:
#line 264 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 2126 "vhdl_y.tab.cpp"
    break;

  case 13:
#line 272 "parser.y"
       {
         init(yyval, ID_symbol);
         yyvsp[0].set_location(stack(yyval));
         stack(yyval).set(ID_identifier, yyvsp[0].text);
       }
#line 2136 "vhdl_y.tab.cpp"
    break;

  case 16:
#line 283 "parser.y"
       {
         init(yyval, ID_member);
         mto(yyval, yyvsp[-2]);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).set(ID_component_name, yyvsp[0].text);
       }
#line 2147 "vhdl_y.tab.cpp"
    break;

  case 17:
#line 290 "parser.y"
       {
         init(yyval, ID_all);
         yyvsp[-1].set_location(stack(yyval));
         mto(yyval, yyvsp[-2]);
       }
#line 2157 "vhdl_y.tab.cpp"
    break;

  case 23:
#line 313 "parser.y"
       {
         vhdl_parse_treet::itemt &a=PARSER.new_package_item();
         yyvsp[-6].set_location(a);
         a.set_name(stack(yyvsp[-5]));
         a.set(ID_decl, stack(yyvsp[-3]));
       }
#line 2168 "vhdl_y.tab.cpp"
    break;

  case 24:
#line 323 "parser.y"
       {
         init(yyval);
       }
#line 2176 "vhdl_y.tab.cpp"
    break;

  case 25:
#line 327 "parser.y"
       {
         yyval=yyvsp[-1];
         mts(yyval, yyvsp[0]);
       }
#line 2185 "vhdl_y.tab.cpp"
    break;

  case 26:
#line 335 "parser.y"
       {
         init(yyval, ID_constant);
         yyvsp[-7].set_location(stack(yyval));
         mts(yyval, yyvsp[-6]);
         mts(yyval, yyvsp[-1]);
         stack(yyval).type()=stack_type(yyvsp[-4]);
       }
#line 2197 "vhdl_y.tab.cpp"
    break;

  case 27:
#line 343 "parser.y"
       {
         init(yyval, ID_enumeration);
         yyvsp[-5].set_location(stack(yyval));
         mts(yyval, yyvsp[-4]);
         mts(yyval, yyvsp[-1]);
       }
#line 2208 "vhdl_y.tab.cpp"
    break;

  case 28:
#line 350 "parser.y"
       {
         init(yyval, "subtype");
         yyvsp[-4].set_location(stack(yyval));
         mts(yyval, yyvsp[-3]);
         mts(yyval, yyvsp[-1]);
       }
#line 2219 "vhdl_y.tab.cpp"
    break;

  case 29:
#line 357 "parser.y"
       {
         init(yyval, "subtype");
         yyvsp[-8].set_location(stack(yyval));
         mts(yyval, yyvsp[-7]);
         mts(yyval, yyvsp[-5]);
       }
#line 2230 "vhdl_y.tab.cpp"
    break;

  case 30:
#line 364 "parser.y"
       {
         init(yyval, "attribute");
         yyvsp[-4].set_location(stack(yyval));
         mts(yyval, yyvsp[-3]);
         mts(yyval, yyvsp[-1]);
       }
#line 2241 "vhdl_y.tab.cpp"
    break;

  case 31:
#line 374 "parser.y"
       {
         init(yyval);
       }
#line 2249 "vhdl_y.tab.cpp"
    break;

  case 32:
#line 378 "parser.y"
       {
         init(yyval);
       }
#line 2257 "vhdl_y.tab.cpp"
    break;

  case 33:
#line 385 "parser.y"
       {
         init(yyval);
       }
#line 2265 "vhdl_y.tab.cpp"
    break;

  case 34:
#line 389 "parser.y"
       {
       }
#line 2272 "vhdl_y.tab.cpp"
    break;

  case 37:
#line 400 "parser.y"
       {
       }
#line 2279 "vhdl_y.tab.cpp"
    break;

  case 39:
#line 409 "parser.y"
       {
         vhdl_parse_treet::itemt &e=PARSER.new_entity_item();
         e.set_name(stack(yyvsp[-4]));
       }
#line 2288 "vhdl_y.tab.cpp"
    break;

  case 40:
#line 414 "parser.y"
       {
         vhdl_parse_treet::itemt &e=PARSER.new_entity_item();
         e.set_name(stack(yyvsp[-9]));
       }
#line 2297 "vhdl_y.tab.cpp"
    break;

  case 41:
#line 420 "parser.y"
       {
         vhdl_parse_treet::itemt &e=PARSER.new_entity_item();
         e.set_name(stack(yyvsp[-14]));
       }
#line 2306 "vhdl_y.tab.cpp"
    break;

  case 42:
#line 428 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 2315 "vhdl_y.tab.cpp"
    break;

  case 43:
#line 433 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 2324 "vhdl_y.tab.cpp"
    break;

  case 44:
#line 441 "parser.y"
       {
       }
#line 2331 "vhdl_y.tab.cpp"
    break;

  case 45:
#line 444 "parser.y"
       {
       }
#line 2338 "vhdl_y.tab.cpp"
    break;

  case 46:
#line 450 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 2347 "vhdl_y.tab.cpp"
    break;

  case 47:
#line 455 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 2356 "vhdl_y.tab.cpp"
    break;

  case 48:
#line 463 "parser.y"
       {
         init(yyval, ID_port);
       }
#line 2364 "vhdl_y.tab.cpp"
    break;

  case 49:
#line 470 "parser.y"
       {
         init(yyval, ID_input);
       }
#line 2372 "vhdl_y.tab.cpp"
    break;

  case 50:
#line 474 "parser.y"
       {
         init(yyval, ID_output);
       }
#line 2380 "vhdl_y.tab.cpp"
    break;

  case 51:
#line 481 "parser.y"
       {
       }
#line 2387 "vhdl_y.tab.cpp"
    break;

  case 52:
#line 484 "parser.y"
       {
       }
#line 2394 "vhdl_y.tab.cpp"
    break;

  case 54:
#line 488 "parser.y"
       {
         init(yyval, ID_enumeration);
       }
#line 2402 "vhdl_y.tab.cpp"
    break;

  case 55:
#line 492 "parser.y"
       {
         init(yyval, ID_range);
       }
#line 2410 "vhdl_y.tab.cpp"
    break;

  case 56:
#line 496 "parser.y"
       {
         init(yyval, ID_array);
       }
#line 2418 "vhdl_y.tab.cpp"
    break;

  case 57:
#line 500 "parser.y"
       {
         init(yyval, ID_struct);
       }
#line 2426 "vhdl_y.tab.cpp"
    break;

  case 58:
#line 504 "parser.y"
       {
         init(yyval, ID_reference);
         stack_type(yyval).subtype()=stack_type(yyvsp[0]);
       }
#line 2435 "vhdl_y.tab.cpp"
    break;

  case 59:
#line 509 "parser.y"
       {
         init(yyval);
       }
#line 2443 "vhdl_y.tab.cpp"
    break;

  case 60:
#line 513 "parser.y"
       {
         init(yyval);
       }
#line 2451 "vhdl_y.tab.cpp"
    break;

  case 62:
#line 521 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 2460 "vhdl_y.tab.cpp"
    break;

  case 63:
#line 526 "parser.y"
       {
         yyval=yyvsp[-1];
         mts(yyval, yyvsp[0]);
       }
#line 2469 "vhdl_y.tab.cpp"
    break;

  case 65:
#line 538 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 2478 "vhdl_y.tab.cpp"
    break;

  case 66:
#line 543 "parser.y"
       {
         yyval=yyvsp[-1];
         mts(yyval, yyvsp[0]);
       }
#line 2487 "vhdl_y.tab.cpp"
    break;

  case 70:
#line 557 "parser.y"
       {
       }
#line 2494 "vhdl_y.tab.cpp"
    break;

  case 72:
#line 564 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 2503 "vhdl_y.tab.cpp"
    break;

  case 73:
#line 569 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 2512 "vhdl_y.tab.cpp"
    break;

  case 75:
#line 578 "parser.y"
       {
         init(yyval, ID_constant);
         yyvsp[0].set_location(stack(yyval));
         stack(yyval).set(ID_type, ID_char);
         stack(yyval).set(ID_value, yyvsp[0].text);
       }
#line 2523 "vhdl_y.tab.cpp"
    break;

  case 76:
#line 588 "parser.y"
       {
         init(yyval, "downto");
       }
#line 2531 "vhdl_y.tab.cpp"
    break;

  case 77:
#line 592 "parser.y"
       {
         init(yyval, "to");
       }
#line 2539 "vhdl_y.tab.cpp"
    break;

  case 78:
#line 600 "parser.y"
       {
         vhdl_parse_treet::itemt &a=PARSER.new_architecture_item();
         yyvsp[-10].set_location(a);
         a.set_name(stack(yyvsp[-9]));
         a.set(ID_entity, stack(yyvsp[-7]));
         a.set(ID_decl, stack(yyvsp[-5]));
         a.set(ID_body, stack(yyvsp[-3]));
       }
#line 2552 "vhdl_y.tab.cpp"
    break;

  case 79:
#line 612 "parser.y"
       {
         init(yyval);
       }
#line 2560 "vhdl_y.tab.cpp"
    break;

  case 80:
#line 616 "parser.y"
       {
         yyval=yyvsp[-1];
         mts(yyval, yyvsp[0]);
       }
#line 2569 "vhdl_y.tab.cpp"
    break;

  case 81:
#line 624 "parser.y"
       {
         init(yyval, ID_signal);
         yyvsp[-4].set_location(stack(yyval));
         stack(yyval).get_sub().swap(stack(yyvsp[-3]).get_sub());
         stack(yyval).type()=stack_type(yyvsp[-1]);
       }
#line 2580 "vhdl_y.tab.cpp"
    break;

  case 82:
#line 631 "parser.y"
       {
         init(yyval, ID_constant);
         yyvsp[-7].set_location(stack(yyval));
         mts(yyval, yyvsp[-6]);
         mts(yyval, yyvsp[-1]);
         stack(yyval).type()=stack_type(yyvsp[-4]);
       }
#line 2592 "vhdl_y.tab.cpp"
    break;

  case 83:
#line 639 "parser.y"
       {
         init(yyval, ID_enumeration);
         yyvsp[-6].set_location(stack(yyval));
         mts(yyval, yyvsp[-5]);
         mts(yyval, yyvsp[-2]);
       }
#line 2603 "vhdl_y.tab.cpp"
    break;

  case 84:
#line 647 "parser.y"
       {
         init(yyval, ID_component);
       }
#line 2611 "vhdl_y.tab.cpp"
    break;

  case 85:
#line 652 "parser.y"
       {
         init(yyval, ID_component);
       }
#line 2619 "vhdl_y.tab.cpp"
    break;

  case 86:
#line 659 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 2628 "vhdl_y.tab.cpp"
    break;

  case 87:
#line 664 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 2637 "vhdl_y.tab.cpp"
    break;

  case 88:
#line 672 "parser.y"
       {
         init(yyval, ID_body);
       }
#line 2645 "vhdl_y.tab.cpp"
    break;

  case 89:
#line 676 "parser.y"
       {
         yyval=yyvsp[-1];
         mto(yyval, yyvsp[0]);
       }
#line 2654 "vhdl_y.tab.cpp"
    break;

  case 90:
#line 684 "parser.y"
       {
         init(yyval, ID_continuous_assign);
         yyvsp[-1].set_location(stack(yyval));
         mto(yyval, yyvsp[-2]);
         mto(yyval, yyvsp[0]);
       }
#line 2665 "vhdl_y.tab.cpp"
    break;

  case 91:
#line 691 "parser.y"
       {
         yyval=yyvsp[-6];
       }
#line 2673 "vhdl_y.tab.cpp"
    break;

  case 92:
#line 695 "parser.y"
       {
         yyval=yyvsp[-4];
       }
#line 2681 "vhdl_y.tab.cpp"
    break;

  case 93:
#line 700 "parser.y"
       {
         yyval=yyvsp[-9];
       }
#line 2689 "vhdl_y.tab.cpp"
    break;

  case 94:
#line 706 "parser.y"
       {
         init(yyval, ID_process);
         yyvsp[-10].set_location(stack(yyval));
         stack(yyval).operands().swap(stack(yyvsp[-4]).operands());
       }
#line 2699 "vhdl_y.tab.cpp"
    break;

  case 95:
#line 714 "parser.y"
       {
         init(yyval, ID_process);
         yyvsp[-6].set_location(stack(yyval));
         stack(yyval).operands().swap(stack(yyvsp[-4]).operands());
       }
#line 2709 "vhdl_y.tab.cpp"
    break;

  case 96:
#line 720 "parser.y"
       {
         init(yyval, ID_generate_if);
         yyvsp[-7].set_location(stack(yyval));
         mto(yyval, yyvsp[-6]);
         mto(yyval, yyvsp[-4]);
       }
#line 2720 "vhdl_y.tab.cpp"
    break;

  case 97:
#line 727 "parser.y"
       {
         init(yyval, ID_generate_for);
         yyvsp[-11].set_location(stack(yyval));
         mto(yyval, yyvsp[-10]);
         mto(yyval, yyvsp[-8]);
         mto(yyval, yyvsp[-6]);
         mto(yyval, yyvsp[-4]);
       }
#line 2733 "vhdl_y.tab.cpp"
    break;

  case 98:
#line 736 "parser.y"
       {
         init(yyval, ID_generate_for);
         yyvsp[-11].set_location(stack(yyval));
         mto(yyval, yyvsp[-10]);
         mto(yyval, yyvsp[-8]);
         mto(yyval, yyvsp[-6]);
         mto(yyval, yyvsp[-4]);
       }
#line 2746 "vhdl_y.tab.cpp"
    break;

  case 99:
#line 748 "parser.y"
       {
         init(yyval, ID_nil);
       }
#line 2754 "vhdl_y.tab.cpp"
    break;

  case 101:
#line 756 "parser.y"
       {
         init(yyval, ID_nil);
       }
#line 2762 "vhdl_y.tab.cpp"
    break;

  case 102:
#line 760 "parser.y"
       {
         yyval=yyvsp[-1];
       }
#line 2770 "vhdl_y.tab.cpp"
    break;

  case 103:
#line 767 "parser.y"
       {
       }
#line 2777 "vhdl_y.tab.cpp"
    break;

  case 104:
#line 770 "parser.y"
       {
       }
#line 2784 "vhdl_y.tab.cpp"
    break;

  case 105:
#line 773 "parser.y"
       {
       }
#line 2791 "vhdl_y.tab.cpp"
    break;

  case 106:
#line 779 "parser.y"
       {
         init(yyval);
         mto(yyval, yyvsp[0]);
       }
#line 2800 "vhdl_y.tab.cpp"
    break;

  case 107:
#line 784 "parser.y"
       {
         init(yyval);
         mto(yyval, yyvsp[0]);
       }
#line 2809 "vhdl_y.tab.cpp"
    break;

  case 108:
#line 792 "parser.y"
       {
       }
#line 2816 "vhdl_y.tab.cpp"
    break;

  case 109:
#line 798 "parser.y"
       {
         init(yyval);
       }
#line 2824 "vhdl_y.tab.cpp"
    break;

  case 110:
#line 802 "parser.y"
       {
         yyval=yyvsp[-1];
         mts(yyval, yyvsp[0]);
       }
#line 2833 "vhdl_y.tab.cpp"
    break;

  case 111:
#line 810 "parser.y"
       {
       }
#line 2840 "vhdl_y.tab.cpp"
    break;

  case 112:
#line 813 "parser.y"
       {
       }
#line 2847 "vhdl_y.tab.cpp"
    break;

  case 113:
#line 819 "parser.y"
       {
         init(yyval);
       }
#line 2855 "vhdl_y.tab.cpp"
    break;

  case 114:
#line 823 "parser.y"
       {
         yyval=yyvsp[-1];
         mto(yyval, yyvsp[0]);
       }
#line 2864 "vhdl_y.tab.cpp"
    break;

  case 115:
#line 831 "parser.y"
       {
         init(yyval, ID_code);
         yyvsp[-2].set_location(stack(yyval));
         stack(yyval).set(ID_statement, ID_assign);
         mto(yyval, yyvsp[-3]);
         mto(yyval, yyvsp[-1]);
       }
#line 2876 "vhdl_y.tab.cpp"
    break;

  case 116:
#line 839 "parser.y"
       {
         init(yyval, ID_code);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).set(ID_statement, ID_continuous_assign);
         mto(yyval, yyvsp[-2]);
         mto(yyval, yyvsp[0]);
       }
#line 2888 "vhdl_y.tab.cpp"
    break;

  case 117:
#line 847 "parser.y"
       {
         init(yyval, ID_code);
         yyvsp[-7].set_location(stack(yyval));
         stack(yyval).set(ID_statement, ID_ifthenelse);
         stack(yyval).move_to_operands(stack(yyvsp[-6]), stack(yyvsp[-4]), stack(yyvsp[-3]));
       }
#line 2899 "vhdl_y.tab.cpp"
    break;

  case 118:
#line 854 "parser.y"
       {
         init(yyval, ID_code);
         yyvsp[-10].set_location(stack(yyval));
         stack(yyval).set(ID_statement, ID_for);
         mto(yyval, yyvsp[-9]);
         mto(yyval, yyvsp[-7]);
         mto(yyval, yyvsp[-5]);
         mto(yyval, yyvsp[-3]);
       }
#line 2913 "vhdl_y.tab.cpp"
    break;

  case 119:
#line 864 "parser.y"
       {
         init(yyval, ID_code);
         yyvsp[-10].set_location(stack(yyval));
         stack(yyval).set(ID_statement, ID_for);
         mto(yyval, yyvsp[-9]);
         mto(yyval, yyvsp[-7]);
         mto(yyval, yyvsp[-5]);
         mto(yyval, yyvsp[-3]);
       }
#line 2927 "vhdl_y.tab.cpp"
    break;

  case 120:
#line 874 "parser.y"
       {
         init(yyval, ID_code);
         yyvsp[-6].set_location(stack(yyval));
         stack(yyval).set(ID_statement, ID_switch_case);
       }
#line 2937 "vhdl_y.tab.cpp"
    break;

  case 121:
#line 880 "parser.y"
       {
         init(yyval, ID_code);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).set(ID_statement, "exit");
       }
#line 2947 "vhdl_y.tab.cpp"
    break;

  case 122:
#line 886 "parser.y"
       {
       }
#line 2954 "vhdl_y.tab.cpp"
    break;

  case 123:
#line 889 "parser.y"
       {
         init(yyval, ID_code); yyvsp[-4].set_location(stack(yyval));
         stack(yyval).set(ID_statement, ID_assert);
         mto(yyval, yyvsp[-3]);
         mto(yyval, yyvsp[-2]);
         mto(yyval, yyvsp[-1]);
       }
#line 2966 "vhdl_y.tab.cpp"
    break;

  case 124:
#line 900 "parser.y"
       {
         init(yyval, ID_nil);
       }
#line 2974 "vhdl_y.tab.cpp"
    break;

  case 125:
#line 904 "parser.y"
       {
         yyval=yyvsp[0];
       }
#line 2982 "vhdl_y.tab.cpp"
    break;

  case 126:
#line 911 "parser.y"
       {
         init(yyval, ID_nil);
       }
#line 2990 "vhdl_y.tab.cpp"
    break;

  case 127:
#line 915 "parser.y"
       {
         yyval=yyvsp[0];
       }
#line 2998 "vhdl_y.tab.cpp"
    break;

  case 128:
#line 922 "parser.y"
       {
         init(yyval, ID_nil);
       }
#line 3006 "vhdl_y.tab.cpp"
    break;

  case 129:
#line 926 "parser.y"
       {
         init(yyval, ID_code);
         stack(yyval).set(ID_statement, ID_ifthenelse);
         stack(yyval).move_to_operands(stack(yyvsp[-3]), stack(yyvsp[-1]), stack(yyvsp[0]));
       }
#line 3016 "vhdl_y.tab.cpp"
    break;

  case 130:
#line 932 "parser.y"
       {
         yyval=yyvsp[0];
       }
#line 3024 "vhdl_y.tab.cpp"
    break;

  case 131:
#line 939 "parser.y"
       {
         init(yyval, ID_when);
       }
#line 3032 "vhdl_y.tab.cpp"
    break;

  case 132:
#line 943 "parser.y"
       {
       }
#line 3039 "vhdl_y.tab.cpp"
    break;

  case 133:
#line 949 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 3048 "vhdl_y.tab.cpp"
    break;

  case 134:
#line 954 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 3057 "vhdl_y.tab.cpp"
    break;

  case 137:
#line 967 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 3066 "vhdl_y.tab.cpp"
    break;

  case 138:
#line 972 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 3075 "vhdl_y.tab.cpp"
    break;

  case 139:
#line 980 "parser.y"
       {
         yyval=yyvsp[-2];
       }
#line 3083 "vhdl_y.tab.cpp"
    break;

  case 140:
#line 984 "parser.y"
       {
         init(yyval, ID_when);
         stack(yyval).move_to_operands(stack(yyvsp[-4]), stack(yyvsp[-1]));
       }
#line 3092 "vhdl_y.tab.cpp"
    break;

  case 141:
#line 989 "parser.y"
       {
         init(yyval, ID_when);
         stack(yyval).move_to_operands(stack(yyvsp[-5]), stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3101 "vhdl_y.tab.cpp"
    break;

  case 142:
#line 997 "parser.y"
       {
       }
#line 3108 "vhdl_y.tab.cpp"
    break;

  case 143:
#line 1000 "parser.y"
       {
       }
#line 3115 "vhdl_y.tab.cpp"
    break;

  case 144:
#line 1006 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 3124 "vhdl_y.tab.cpp"
    break;

  case 145:
#line 1011 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 3133 "vhdl_y.tab.cpp"
    break;

  case 147:
#line 1020 "parser.y"
       {
       }
#line 3140 "vhdl_y.tab.cpp"
    break;

  case 148:
#line 1026 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 3149 "vhdl_y.tab.cpp"
    break;

  case 149:
#line 1031 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 3158 "vhdl_y.tab.cpp"
    break;

  case 150:
#line 1039 "parser.y"
       {
       }
#line 3165 "vhdl_y.tab.cpp"
    break;

  case 152:
#line 1046 "parser.y"
       {
         init(yyval, ID_extractbits);
         stack(yyval).move_to_operands(stack(yyvsp[-5]), stack(yyvsp[-3]), stack(yyvsp[-1]));
       }
#line 3174 "vhdl_y.tab.cpp"
    break;

  case 153:
#line 1051 "parser.y"
       {
         init(yyval, ID_extractbits);
       }
#line 3182 "vhdl_y.tab.cpp"
    break;

  case 161:
#line 1079 "parser.y"
       {
         init(yyval, ID_constant);
         yyvsp[0].set_location(stack(yyval));
         stack(yyval).set(ID_type, ID_string);
         stack(yyval).set(ID_value, yyvsp[0].text);
       }
#line 3193 "vhdl_y.tab.cpp"
    break;

  case 162:
#line 1086 "parser.y"
       {
         init(yyval, ID_constant);
         yyvsp[0].set_location(stack(yyval));
         stack(yyval).set(ID_type, ID_string);
         stack(yyval).set(ID_value, yyvsp[0].text);
       }
#line 3204 "vhdl_y.tab.cpp"
    break;

  case 163:
#line 1093 "parser.y"
       {
         init(yyval, ID_constant);
         yyvsp[0].set_location(stack(yyval));
         stack(yyval).set(ID_type, ID_char);
         stack(yyval).set(ID_value, yyvsp[0].text);
       }
#line 3215 "vhdl_y.tab.cpp"
    break;

  case 164:
#line 1100 "parser.y"
       {
         init(yyval, ID_constant);
         yyvsp[0].set_location(stack(yyval));
         stack(yyval).set(ID_type, ID_natural);
         stack(yyval).set(ID_value, yyvsp[0].text);
       }
#line 3226 "vhdl_y.tab.cpp"
    break;

  case 165:
#line 1107 "parser.y"
       {
         init(yyval, ID_constant);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).set(ID_type, ID_natural);
         stack(yyval).set(ID_value, yyvsp[-1].text);
         // the name is a unit
       }
#line 3238 "vhdl_y.tab.cpp"
    break;

  case 166:
#line 1115 "parser.y"
       {
         init(yyval, ID_constant);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).set(ID_type, ID_natural);
         stack(yyval).set(ID_value, yyvsp[-1].text);
       }
#line 3249 "vhdl_y.tab.cpp"
    break;

  case 167:
#line 1122 "parser.y"
       {
       }
#line 3256 "vhdl_y.tab.cpp"
    break;

  case 168:
#line 1125 "parser.y"
       { // Vector chaining
         init(yyval, ID_concatenation);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3266 "vhdl_y.tab.cpp"
    break;

  case 169:
#line 1131 "parser.y"
       {
         init(yyval, ID_unary_minus);
         yyvsp[-1].set_location(stack(yyval));
         mto(yyval, yyvsp[0]);
       }
#line 3276 "vhdl_y.tab.cpp"
    break;

  case 170:
#line 1137 "parser.y"
       {
         init(yyval, ID_unary_plus);
         yyvsp[-1].set_location(stack(yyval));
         mto(yyval, yyvsp[0]);
       }
#line 3286 "vhdl_y.tab.cpp"
    break;

  case 171:
#line 1143 "parser.y"
       {
         init(yyval, ID_plus);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3296 "vhdl_y.tab.cpp"
    break;

  case 172:
#line 1149 "parser.y"
       {
         init(yyval, ID_minus);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3306 "vhdl_y.tab.cpp"
    break;

  case 173:
#line 1155 "parser.y"
       {
         init(yyval, ID_shl);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3316 "vhdl_y.tab.cpp"
    break;

  case 174:
#line 1161 "parser.y"
       {
         init(yyval, ID_lshr);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3326 "vhdl_y.tab.cpp"
    break;

  case 175:
#line 1167 "parser.y"
       {
         init(yyval, ID_shl);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3336 "vhdl_y.tab.cpp"
    break;

  case 176:
#line 1173 "parser.y"
       {
         init(yyval, ID_ashr);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3346 "vhdl_y.tab.cpp"
    break;

  case 177:
#line 1179 "parser.y"
       {
         init(yyval, ID_rol);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3356 "vhdl_y.tab.cpp"
    break;

  case 178:
#line 1185 "parser.y"
       {
         init(yyval, ID_ror);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3366 "vhdl_y.tab.cpp"
    break;

  case 179:
#line 1191 "parser.y"
       {
         init(yyval, ID_mult);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3376 "vhdl_y.tab.cpp"
    break;

  case 180:
#line 1197 "parser.y"
       {
         init(yyval, ID_div);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3386 "vhdl_y.tab.cpp"
    break;

  case 181:
#line 1203 "parser.y"
       {
         init(yyval, ID_mod);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3396 "vhdl_y.tab.cpp"
    break;

  case 182:
#line 1209 "parser.y"
       {
         init(yyval, ID_not);
         yyvsp[-1].set_location(stack(yyval));
         mto(yyval, yyvsp[0]);
       }
#line 3406 "vhdl_y.tab.cpp"
    break;

  case 183:
#line 1215 "parser.y"
       {
         init(yyval, ID_and);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3416 "vhdl_y.tab.cpp"
    break;

  case 184:
#line 1221 "parser.y"
       {
         init(yyval, ID_nand);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3426 "vhdl_y.tab.cpp"
    break;

  case 185:
#line 1227 "parser.y"
       {
         init(yyval, ID_or);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3436 "vhdl_y.tab.cpp"
    break;

  case 186:
#line 1233 "parser.y"
       {
         init(yyval, ID_nor);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3446 "vhdl_y.tab.cpp"
    break;

  case 187:
#line 1239 "parser.y"
       {
         init(yyval, ID_xor);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3456 "vhdl_y.tab.cpp"
    break;

  case 188:
#line 1245 "parser.y"
       {
         init(yyval, ID_xnor);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3466 "vhdl_y.tab.cpp"
    break;

  case 189:
#line 1251 "parser.y"
       {
         init(yyval, ID_side_effect);
         yyvsp[-2].set_location(stack(yyval));
         stack(yyval).set(ID_statement, ID_function_call);
         stack(yyval).add(ID_operands).get_sub().swap(stack(yyvsp[-1]).get_sub());
       }
#line 3477 "vhdl_y.tab.cpp"
    break;

  case 190:
#line 1258 "parser.y"
       {
         yyval=yyvsp[-1];
       }
#line 3485 "vhdl_y.tab.cpp"
    break;

  case 191:
#line 1262 "parser.y"
       {
         init(yyval, ID_equal);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3495 "vhdl_y.tab.cpp"
    break;

  case 192:
#line 1268 "parser.y"
       {
         init(yyval, ID_gt);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3505 "vhdl_y.tab.cpp"
    break;

  case 193:
#line 1274 "parser.y"
       {
         init(yyval, ID_ge);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3515 "vhdl_y.tab.cpp"
    break;

  case 194:
#line 1280 "parser.y"
       {
         init(yyval, ID_lt);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3525 "vhdl_y.tab.cpp"
    break;

  case 195:
#line 1286 "parser.y"
       {
         init(yyval, ID_le);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3535 "vhdl_y.tab.cpp"
    break;

  case 196:
#line 1292 "parser.y"
       {
         init(yyval, ID_notequal);
         yyvsp[-1].set_location(stack(yyval));
         stack(yyval).move_to_operands(stack(yyvsp[-2]), stack(yyvsp[0]));
       }
#line 3545 "vhdl_y.tab.cpp"
    break;

  case 197:
#line 1301 "parser.y"
       {
         init(yyval);
         mts(yyval, yyvsp[0]);
       }
#line 3554 "vhdl_y.tab.cpp"
    break;

  case 198:
#line 1306 "parser.y"
       {
         yyval=yyvsp[-2];
         mts(yyval, yyvsp[0]);
       }
#line 3563 "vhdl_y.tab.cpp"
    break;


#line 3567 "vhdl_y.tab.cpp"

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
