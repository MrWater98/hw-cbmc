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
#define yyparse         yysmvparse
#define yylex           yysmvlex
#define yyerror         yysmverror
#define yydebug         yysmvdebug
#define yynerrs         yysmvnerrs
#define yylval          yysmvlval
#define yychar          yysmvchar

/* First part of user prologue.  */
#line 1 "parser.y"

#include "smv_parser.h"
#include "smv_typecheck.h"
#include "util/std_types.h"

#define YYSTYPE unsigned
#define PARSER smv_parser

#include "y.tab.h"

#define YYMAXDEPTH 200000
#define YYSTYPE_IS_TRIVIAL 1

/*------------------------------------------------------------------------*/

#define yylineno yysmvlineno
#define yytext yysmvtext

#define yyerror yysmverror
int yysmverror(const std::string &error);
int yylex();
extern char *yytext;

/*------------------------------------------------------------------------*/

#define mto(x, y) stack_expr(x).move_to_operands(stack_expr(y))

  /*******************************************************************\

  Function: init

    Inputs:

   Outputs:

   Purpose:

  \*******************************************************************/

  static void init(exprt & expr) {
    expr.clear();
    PARSER.set_source_location(expr);
}

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

static void init(YYSTYPE &expr)
{
  newstack(expr);
  init(stack_expr(expr));
}

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

 static void init(YYSTYPE &expr, const irep_idt &id)
{
  init(expr);
  stack_expr(expr).id(id);
}

 /// binary TODO[docu]
 static void binary(YYSTYPE & x_result, YYSTYPE & y_lhs, const irep_idt &id,
                    YYSTYPE &z_rhs, const typet &t)
 {
   init(x_result, id);
   stack_expr(x_result).type() = t;
   auto &lhs = stack_expr(y_lhs);
   auto &rhs = stack_expr(z_rhs);
   DATA_INVARIANT(lhs.type().id() != ID_nil || rhs.type().id() != ID_nil,
                  "binary expr without types");
   if (lhs.type().id() == ID_nil)
     lhs.type() = rhs.type();
   if (rhs.type().id() == ID_nil)
     rhs.type() = lhs.type();
   stack_expr(x_result).add_to_operands(std::move(lhs), std::move(rhs));
 }

 /// binary TODO[docu]
 static void binary_arith(YYSTYPE & x_result, YYSTYPE & y_lhs,
                          const irep_idt &id, YYSTYPE &z_rhs)
 {
   init(x_result, id);
   auto &lhs = stack_expr(y_lhs);
   DATA_INVARIANT(lhs.type().id() != ID_nil, "arith expr without lhs type");
   stack_expr(x_result).type() = lhs.type();
   auto &rhs = stack_expr(z_rhs);
   if (rhs.type().id() == ID_nil)
     rhs.type() = lhs.type();
   stack_expr(x_result).add_to_operands(std::move(lhs), std::move(rhs));
 }

 /*******************************************************************\

 Function: j_binary

   Inputs:

  Outputs:

  Purpose:

 \*******************************************************************/

 static void j_binary(YYSTYPE & dest, YYSTYPE & op1, const irep_idt &id,
                      YYSTYPE &op2, const typet &t) {
   if (stack_expr(op1).id() == id) {
     dest = op1;
     mto(dest, op2);
   } else if (stack_expr(op2).id() == id) {
     dest = op2;
     mto(dest, op1);
   } else
     binary(dest, op1, id, op2, t);
}

/*******************************************************************\

Function: new_module

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

static void new_module(YYSTYPE &module)
{
  const std::string name=smv_module_symbol(stack_expr(module).id_string());
  PARSER.module=&PARSER.parse_tree.modules[name];
  PARSER.module->name=name;
  PARSER.module->base_name=stack_expr(module).id_string();
  PARSER.module->used=true;
}

/*------------------------------------------------------------------------*/


#line 237 "y.tab.cpp"

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
#ifndef YY_YYSMV_Y_TAB_HPP_INCLUDED
# define YY_YYSMV_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yysmvdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    AG_Token = 258,
    AX_Token = 259,
    AF_Token = 260,
    EG_Token = 261,
    EX_Toekn = 262,
    EF_Token = 263,
    INIT_Token = 264,
    TRANS_Token = 265,
    SPEC_Token = 266,
    VAR_Token = 267,
    DEFINE_Token = 268,
    ASSIGN_Token = 269,
    INVAR_Token = 270,
    FAIRNESS_Token = 271,
    MODULE_Token = 272,
    ARRAY_Token = 273,
    OF_Token = 274,
    DOTDOT_Token = 275,
    BOOLEAN_Token = 276,
    EXTERN_Token = 277,
    NEXT_Token = 278,
    INC_Token = 279,
    DEC_Token = 280,
    CASE_Token = 281,
    ESAC_Token = 282,
    BECOMES_Token = 283,
    ADD_Token = 284,
    SUB_Token = 285,
    SWITCH_Token = 286,
    init_Token = 287,
    PLUS_Token = 288,
    STRING_Token = 289,
    QSTRING_Token = 290,
    QUOTE_Token = 291,
    NUMBER_Token = 292,
    FALSE_Token = 293,
    TRUE_Token = 294,
    IMPLIES_Token = 295,
    EQUIV_Token = 296,
    XOR_Token = 297,
    OR_Token = 298,
    AND_Token = 299,
    NOT_Token = 300,
    EX_Token = 301,
    E_Token = 302,
    A_Token = 303,
    U_Token = 304,
    F_Token = 305,
    G_Token = 306,
    X_Token = 307,
    EQUAL_Token = 308,
    NOTEQUAL_Token = 309,
    LT_Token = 310,
    GT_Token = 311,
    LE_Token = 312,
    GE_Token = 313,
    UNION_Token = 314,
    IN_Token = 315,
    NOTIN_Token = 316,
    MOD_Token = 317,
    MINUS_Token = 318,
    TIMES_Token = 319,
    DIVIDE_Token = 320,
    UMINUS = 321,
    DOT_Token = 322
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yysmvlval;

int yysmvparse (void);

#endif /* !YY_YYSMV_Y_TAB_HPP_INCLUDED  */



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
#define YYFINAL  64
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   718

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  237

#define YYUNDEFTOK  2
#define YYMAXUTOK   322


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
      68,    69,     2,     2,    71,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    74,    70,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    75,     2,    76,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,    73,     2,     2,     2,     2,
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
      65,    66,    67
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   191,   191,   192,   196,   197,   200,   203,   204,   207,
     208,   208,   211,   212,   215,   216,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   239,   254,   255,   258,   267,   268,
     271,   272,   275,   291,   292,   293,   298,   301,   307,   316,
     321,   328,   335,   368,   369,   370,   371,   374,   392,   395,
     396,   399,   400,   403,   438,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   489,   490,   493,   523,   533,   537,   538,   545,   552,
     560,   571,   572,   576,   581,   582,   586
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AG_Token", "AX_Token", "AF_Token",
  "EG_Token", "EX_Toekn", "EF_Token", "INIT_Token", "TRANS_Token",
  "SPEC_Token", "VAR_Token", "DEFINE_Token", "ASSIGN_Token", "INVAR_Token",
  "FAIRNESS_Token", "MODULE_Token", "ARRAY_Token", "OF_Token",
  "DOTDOT_Token", "BOOLEAN_Token", "EXTERN_Token", "NEXT_Token",
  "INC_Token", "DEC_Token", "CASE_Token", "ESAC_Token", "BECOMES_Token",
  "ADD_Token", "SUB_Token", "SWITCH_Token", "init_Token", "PLUS_Token",
  "STRING_Token", "QSTRING_Token", "QUOTE_Token", "NUMBER_Token",
  "FALSE_Token", "TRUE_Token", "IMPLIES_Token", "EQUIV_Token", "XOR_Token",
  "OR_Token", "AND_Token", "NOT_Token", "EX_Token", "E_Token", "A_Token",
  "U_Token", "F_Token", "G_Token", "X_Token", "EQUAL_Token",
  "NOTEQUAL_Token", "LT_Token", "GT_Token", "LE_Token", "GE_Token",
  "UNION_Token", "IN_Token", "NOTIN_Token", "MOD_Token", "MINUS_Token",
  "TIMES_Token", "DIVIDE_Token", "UMINUS", "DOT_Token", "'('", "')'",
  "';'", "','", "'{'", "'}'", "':'", "'['", "']'", "$accept", "start",
  "modules", "module", "module_name", "module_head", "$@1", "sections",
  "semi_opt", "section", "extern_var", "vardecls", "module_argument",
  "module_argument_list", "module_argument_list_opt", "type", "usertype",
  "enum_list", "enum_element", "vardecl", "assignments", "assignment",
  "assignment_var", "assignment_head", "defines", "define", "formula",
  "term", "formula_list", "variable_name", "qstring_list", "cases", "case",
  "switches", "switch", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,    40,    41,
      59,    44,   123,   125,    58,    91,    93
};
# endif

#define YYPACT_NINF (-98)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-11)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     120,   240,   240,   240,   240,   240,   -27,   -52,   -40,   -33,
     -98,   -24,   -20,   -11,   -98,   -98,   -98,   -98,   -98,   -98,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
      41,    83,   -98,   595,   -98,   537,   -98,    -8,   196,   196,
     196,   196,   196,   -98,   -98,    35,   240,   240,   240,   170,
     240,   240,    63,   653,   196,   196,   196,   196,   196,   196,
     -98,    40,   -98,   -61,   -98,   -98,   240,   240,   240,    63,
      63,    79,   240,   240,    63,   -98,   595,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,    17,    81,    82,
      48,   372,   405,   438,   -98,    46,   -98,   273,   306,    52,
     -98,   240,   -98,    57,    57,    57,   -98,    63,    55,    94,
     -98,    63,   -98,   -98,   -98,   -98,    79,    62,    79,    57,
      57,    57,    78,   -98,    43,   537,   570,   603,   636,   653,
     196,    10,    10,    10,    10,    10,    10,   235,   -25,   -25,
      -2,    43,   -98,   -98,   -98,   -98,    64,    56,    63,   -98,
     -98,   -98,   240,   240,   240,    66,   -98,   -98,   -98,   -98,
     -98,   -98,    -7,   240,   -98,   -98,    63,   -98,   -98,   -98,
     -98,   103,   -98,   -98,   -98,    76,    84,   -98,    91,   471,
     504,   -98,   111,   -98,   132,   130,   101,   107,   -98,   110,
     112,   -98,    63,   -98,   -98,   -98,   -98,   -31,   162,   147,
     -98,   -58,   -98,   240,   -98,   -98,   157,   -98,   113,   -98,
     -98,   152,   -98,   130,   -98,    -5,   240,   240,   171,   -98,
     -98,   121,   339,    -7,   -98,   -98,   -98
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,     0,     0,     0,   116,   115,   114,    73,    75,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     4,    12,     3,    64,    65,   113,    92,    90,
      91,    95,    94,     7,     8,     9,     0,     0,     0,     0,
       0,     0,     0,    89,    93,    97,    96,    98,    99,   100,
      78,     0,   111,     0,     1,     5,    19,    21,    23,    17,
      27,    25,    29,    31,    33,     6,    12,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,     0,   122,     0,     0,     0,
      67,     0,    68,    14,    14,    14,    16,    35,     0,     0,
      26,    61,    58,    60,    59,    24,    53,     0,    55,    14,
      14,    14,     0,    13,    82,    85,    84,    86,    87,    88,
     101,   102,   103,   104,   106,   105,   107,   108,   109,   110,
      79,    83,    80,    81,   118,   117,     0,     0,    40,    66,
      69,    70,     0,     0,     0,     0,   112,    15,    18,    20,
      22,    36,     0,     0,    62,    54,     0,    56,    28,    30,
      32,     0,   120,   119,    38,    41,     0,    37,     0,     0,
       0,   124,     0,    43,     0,     0,    47,     0,    46,     0,
       0,    34,     0,    11,   123,    71,    72,     0,     0,     0,
      51,     0,    49,     0,    52,    63,     0,    39,     0,    77,
     125,     0,    45,     0,    44,     0,     0,     0,     0,    50,
      48,     0,     0,     0,    57,   126,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -98,   -98,   -98,   167,   197,   -98,   -98,   126,   -97,   -98,
     -98,    93,     9,   -98,   -98,   -21,   -98,   -98,   -10,   -98,
     -22,   -98,    38,   -98,    98,   -65,    68,    -1,    11,   -16,
     -98,   -98,   -98,   -98,   -98
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    30,    31,    32,   196,    33,   100,    75,   168,    76,
     131,   116,   184,   185,   186,   197,   198,   211,   212,   117,
     125,   126,   119,   127,   120,   128,    62,    35,    63,    36,
      37,    49,   106,   207,   220
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      38,    39,    40,    41,    42,   121,   218,    43,    77,    44,
     111,   192,   112,   223,   193,   224,    46,   169,   170,    53,
      54,    55,    56,    57,    58,    59,    60,    43,    47,    44,
     194,    77,   178,   179,   180,    48,   109,    93,    94,    95,
      96,    64,   219,    77,    50,   101,   102,   103,    51,   107,
     108,   154,   155,   118,   122,   122,   121,    52,   132,    97,
      98,    94,    95,    96,   230,   195,   111,    99,    34,    90,
      91,    92,    93,    94,    95,    96,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,    61,    14,    15,    16,
       6,   118,   123,   -10,   175,   122,   177,    95,    96,   110,
     122,   124,   122,    14,    15,    16,   158,   105,   156,   157,
     162,   165,   173,     1,     2,     3,     4,   167,     5,   172,
     176,   181,   183,   182,   113,   114,   115,     6,   191,   201,
     129,   130,   187,     7,     8,     9,    10,   202,   208,    11,
      12,    13,   209,   203,    14,    15,    16,    17,    18,    19,
     122,   204,   189,   190,   210,    20,    21,    22,    23,   213,
      24,    25,    26,     1,     2,     3,     4,   214,     5,   166,
     215,   216,   221,    27,   222,   226,   187,   227,    28,   228,
     233,   234,    29,     7,     8,     9,    10,   104,    65,    11,
      12,    13,   133,    45,    14,    15,    16,    17,    18,    19,
     171,   217,   236,   229,   200,    20,    21,    22,    23,   174,
      24,    25,    26,     0,   225,     0,   232,     0,     0,    77,
     188,     0,     0,    27,     0,     0,     0,     0,    28,     0,
       0,   199,    29,     1,     2,     3,     4,     0,     5,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,     0,     7,     8,     9,    10,     0,    77,    11,
      12,    13,     0,     0,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,     0,
      24,    25,    26,     0,   231,    91,    92,    93,    94,    95,
      96,     0,     0,    27,     0,     0,    77,     0,    28,     0,
       0,     0,    29,    78,    79,    80,    81,    82,     0,     0,
       0,     0,    83,     0,     0,     0,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    77,
       0,     0,     0,     0,   163,     0,    78,    79,    80,    81,
      82,     0,     0,     0,     0,    83,     0,     0,     0,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    77,     0,     0,     0,     0,   164,     0,    78,
      79,    80,    81,    82,     0,     0,     0,     0,    83,     0,
       0,     0,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    77,     0,     0,     0,   235,
       0,     0,    78,    79,    80,    81,    82,     0,     0,     0,
       0,    83,     0,     0,     0,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    77,     0,
       0,   159,     0,     0,     0,    78,    79,    80,    81,    82,
       0,     0,     0,     0,    83,     0,     0,     0,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    77,     0,     0,   160,     0,     0,     0,    78,    79,
      80,    81,    82,     0,     0,     0,     0,    83,     0,     0,
       0,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    77,     0,     0,   161,     0,     0,
       0,    78,    79,    80,    81,    82,     0,     0,     0,     0,
      83,     0,     0,     0,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    77,     0,     0,
     205,     0,     0,     0,    78,    79,    80,    81,    82,     0,
       0,     0,     0,    83,     0,     0,     0,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      77,     0,     0,   206,     0,     0,     0,    78,    79,    80,
      81,    82,     0,     0,     0,     0,    83,     0,     0,     0,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    77,    66,    67,    68,    69,    70,    71,
      72,    73,    80,    81,    82,     0,     0,    74,     0,    83,
       0,     0,     0,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    77,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,    82,     0,     0,
       0,     0,    83,     0,     0,     0,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,     0,     0,     0,    83,    77,     0,     0,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    83,     0,     0,     0,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96
};

static const yytype_int16 yycheck[] =
{
       1,     2,     3,     4,     5,    70,    37,    34,    33,    36,
      71,    18,    73,    71,    21,    73,    68,   114,   115,    20,
      21,    22,    23,    24,    25,    26,    27,    34,    68,    36,
      37,    33,   129,   130,   131,    68,    52,    62,    63,    64,
      65,     0,    73,    33,    68,    46,    47,    48,    68,    50,
      51,    34,    35,    69,    70,    71,   121,    68,    74,    67,
      68,    63,    64,    65,    69,    72,    71,    75,     0,    59,
      60,    61,    62,    63,    64,    65,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    28,    34,    35,    36,
      17,   117,    23,    68,   126,   121,   128,    64,    65,    69,
     126,    32,   128,    34,    35,    36,    68,    49,    37,    37,
      74,    69,    28,     3,     4,     5,     6,    70,     8,    74,
      68,    53,    76,    69,    66,    67,    68,    17,    72,    36,
      72,    73,   158,    23,    24,    25,    26,    71,    37,    29,
      30,    31,    20,    69,    34,    35,    36,    37,    38,    39,
     176,    70,   163,   164,    34,    45,    46,    47,    48,    68,
      50,    51,    52,     3,     4,     5,     6,    70,     8,   111,
      70,    69,    20,    63,    37,    28,   202,    74,    68,    37,
      19,    70,    72,    23,    24,    25,    26,    27,    31,    29,
      30,    31,    76,     6,    34,    35,    36,    37,    38,    39,
     117,   202,   233,   223,   176,    45,    46,    47,    48,   121,
      50,    51,    52,    -1,   213,    -1,   227,    -1,    -1,    33,
     162,    -1,    -1,    63,    -1,    -1,    -1,    -1,    68,    -1,
      -1,   173,    72,     3,     4,     5,     6,    -1,     8,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    23,    24,    25,    26,    -1,    33,    29,
      30,    31,    -1,    -1,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    -1,
      50,    51,    52,    -1,   226,    60,    61,    62,    63,    64,
      65,    -1,    -1,    63,    -1,    -1,    33,    -1,    68,    -1,
      -1,    -1,    72,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    33,
      -1,    -1,    -1,    -1,    71,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    33,    -1,    -1,    -1,    -1,    71,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    33,    -1,    -1,    -1,    70,
      -1,    -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    33,    -1,
      -1,    69,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    33,    -1,    -1,    69,    -1,    -1,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    33,    -1,    -1,    69,    -1,    -1,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    33,    -1,    -1,
      69,    -1,    -1,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      33,    -1,    -1,    69,    -1,    -1,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    33,     9,    10,    11,    12,    13,    14,
      15,    16,    42,    43,    44,    -1,    -1,    22,    -1,    49,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    49,    33,    -1,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    49,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,    17,    23,    24,    25,
      26,    29,    30,    31,    34,    35,    36,    37,    38,    39,
      45,    46,    47,    48,    50,    51,    52,    63,    68,    72,
      78,    79,    80,    82,   103,   104,   106,   107,   104,   104,
     104,   104,   104,    34,    36,    81,    68,    68,    68,   108,
      68,    68,    68,   104,   104,   104,   104,   104,   104,   104,
     104,   103,   103,   105,     0,    80,     9,    10,    11,    12,
      13,    14,    15,    16,    22,    84,    86,    33,    40,    41,
      42,    43,    44,    49,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    67,    68,    75,
      83,   104,   104,   104,    27,   103,   109,   104,   104,   106,
      69,    71,    73,   103,   103,   103,    88,    96,   106,    99,
     101,   102,   106,    23,    32,    97,    98,   100,   102,   103,
     103,    87,   106,    84,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,    34,    35,    37,    37,    68,    69,
      69,    69,    74,    71,    71,    69,   103,    70,    85,    85,
      85,    88,    74,    28,   101,    97,    68,    97,    85,    85,
      85,    53,    69,    76,    89,    90,    91,   106,   103,   104,
     104,    72,    18,    21,    37,    72,    81,    92,    93,   103,
      99,    36,    71,    69,    70,    69,    69,   110,    37,    20,
      34,    94,    95,    68,    70,    70,    69,    89,    37,    73,
     111,    20,    37,    71,    73,   105,    28,    74,    37,    95,
      69,   103,   104,    19,    70,    70,    92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    77,    78,    78,    79,    79,    80,    81,    81,    82,
      83,    82,    84,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    87,    88,    88,    89,    90,    90,
      91,    91,    92,    92,    92,    92,    92,    93,    93,    94,
      94,    95,    96,    97,    97,    97,    97,    98,    99,   100,
     100,   101,   101,   102,   103,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   105,   105,   106,   106,   107,   107,   107,   107,   107,
     107,   108,   108,   109,   110,   110,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     1,     1,     2,
       0,     6,     0,     2,     0,     1,     2,     1,     3,     1,
       3,     1,     3,     1,     2,     1,     2,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     2,     1,     1,     3,
       0,     1,     6,     1,     3,     3,     1,     1,     4,     1,
       3,     1,     4,     1,     2,     1,     2,     7,     1,     1,
       1,     1,     2,     4,     1,     1,     4,     3,     3,     4,
       4,     6,     6,     1,     1,     1,     3,     7,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     1,     1,     1,     1,     3,     3,     4,
       4,     0,     2,     4,     0,     2,     4
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
  case 3:
#line 192 "parser.y"
                     { PARSER.module->add_spec(stack_expr(yyvsp[0]));
                       PARSER.module->used=true; }
#line 1802 "y.tab.cpp"
    break;

  case 9:
#line 207 "parser.y"
                                      { new_module(yyvsp[0]); }
#line 1808 "y.tab.cpp"
    break;

  case 10:
#line 208 "parser.y"
                                      { new_module(yyvsp[0]); }
#line 1814 "y.tab.cpp"
    break;

  case 18:
#line 221 "parser.y"
                                         { PARSER.module->add_init(stack_expr(yyvsp[-1]), stack_expr(yyvsp[-2]).source_location()); }
#line 1820 "y.tab.cpp"
    break;

  case 20:
#line 223 "parser.y"
                                          { PARSER.module->add_trans(stack_expr(yyvsp[-1]), stack_expr(yyvsp[-2]).source_location()); }
#line 1826 "y.tab.cpp"
    break;

  case 22:
#line 225 "parser.y"
                                         { PARSER.module->add_spec(stack_expr(yyvsp[-1]), stack_expr(yyvsp[-2]).source_location()); }
#line 1832 "y.tab.cpp"
    break;

  case 28:
#line 231 "parser.y"
                                          { PARSER.module->add_invar(stack_expr(yyvsp[-1]), stack_expr(yyvsp[-2]).source_location()); }
#line 1838 "y.tab.cpp"
    break;

  case 30:
#line 233 "parser.y"
                                             { PARSER.module->add_fairness(stack_expr(yyvsp[-1]), stack_expr(yyvsp[-2]).source_location()); }
#line 1844 "y.tab.cpp"
    break;

  case 34:
#line 240 "parser.y"
           {
             const irep_idt &identifier=stack_expr(yyvsp[-2]).get(ID_identifier);
             smv_parse_treet::mc_vart &var=PARSER.module->vars[identifier];

             if(var.identifier!=irep_idt())
             {
               yyerror("variable `"+id2string(identifier)+"' already declared extern");
               YYERROR;
             }
             else
               var.identifier=stack_expr(yyvsp[0]).id_string();
           }
#line 1861 "y.tab.cpp"
    break;

  case 37:
#line 259 "parser.y"
           {
             const irep_idt &identifier=stack_expr(yyvsp[0]).get(ID_identifier);
             smv_parse_treet::mc_vart &var=PARSER.module->vars[identifier];
             var.var_class=smv_parse_treet::mc_vart::ARGUMENT;
             PARSER.module->ports.push_back(identifier);
           }
#line 1872 "y.tab.cpp"
    break;

  case 42:
#line 276 "parser.y"
           {
             init(yyval, ID_array);
             int start=atoi(stack_expr(yyvsp[-4]).id().c_str());
             int end=atoi(stack_expr(yyvsp[-2]).id().c_str());

             if(end < start)
             {
               yyerror("array must end with number >= `"+std::to_string(start)+"'");
               YYERROR;
             }

             stack_type(yyval).set(ID_size, end-start+1);
             stack_type(yyval).set(ID_offset, start);
             stack_type(yyval).subtype()=stack_type(yyvsp[0]);
           }
#line 1892 "y.tab.cpp"
    break;

  case 43:
#line 291 "parser.y"
                           { init(yyval, ID_bool); }
#line 1898 "y.tab.cpp"
    break;

  case 44:
#line 292 "parser.y"
                               { yyval=yyvsp[-1]; }
#line 1904 "y.tab.cpp"
    break;

  case 45:
#line 294 "parser.y"
           {
             init(yyval, ID_signedbv);
             stack_type(yyval).set(ID_width, 32);
           }
#line 1913 "y.tab.cpp"
    break;

  case 47:
#line 302 "parser.y"
           {
             init(yyval, "submodule");
             stack_expr(yyval).set(ID_identifier,
                           smv_module_symbol(stack_expr(yyvsp[0]).id_string()));
           }
#line 1923 "y.tab.cpp"
    break;

  case 48:
#line 308 "parser.y"
           {
             init(yyval, "submodule");
             stack_expr(yyval).set(ID_identifier,
                           smv_module_symbol(stack_expr(yyvsp[-3]).id_string()));
             stack_expr(yyval).operands().swap(stack_expr(yyvsp[-1]).operands());
           }
#line 1934 "y.tab.cpp"
    break;

  case 49:
#line 317 "parser.y"
           {
             init(yyval, ID_enumeration);
             stack_expr(yyval).add(ID_elements).get_sub().push_back(irept(stack_expr(yyvsp[0]).id()));
           }
#line 1943 "y.tab.cpp"
    break;

  case 50:
#line 322 "parser.y"
           {
             yyval=yyvsp[-2];
             stack_expr(yyval).add(ID_elements).get_sub().push_back(irept(stack_expr(yyvsp[0]).id())); 
           }
#line 1952 "y.tab.cpp"
    break;

  case 51:
#line 329 "parser.y"
           {
             yyval=yyvsp[0];
             PARSER.module->enum_set.insert(stack_expr(yyvsp[0]).id_string());
           }
#line 1961 "y.tab.cpp"
    break;

  case 52:
#line 336 "parser.y"
{
  const irep_idt &identifier=stack_expr(yyvsp[-3]).get(ID_identifier);
  smv_parse_treet::mc_vart &var=PARSER.module->vars[identifier];

  switch(var.var_class)
  {
  case smv_parse_treet::mc_vart::UNKNOWN:
    var.type=(typet &)stack_expr(yyvsp[-1]);
    var.var_class=smv_parse_treet::mc_vart::DECLARED;
    break;

  case smv_parse_treet::mc_vart::DEFINED:
    yyerror("variable `"+id2string(identifier)+"' already defined");
    YYERROR;
    break;

  case smv_parse_treet::mc_vart::DECLARED:
    yyerror("variable `"+id2string(identifier)+"' already declared as variable");
    YYERROR;
    break;
  
  case smv_parse_treet::mc_vart::ARGUMENT:
    yyerror("variable `"+id2string(identifier)+"' already declared as argument");
    YYERROR;
    break;
  
  default:
    assert(false);
  }
}
#line 1996 "y.tab.cpp"
    break;

  case 57:
#line 375 "parser.y"
           {
             binary(yyval, yyvsp[-4], ID_equal, yyvsp[-1], bool_typet{});

             if(stack_expr(yyvsp[-6]).id()=="next")
             {
               exprt &op=stack_expr(yyval).op0();
               exprt tmp("smv_next");
               tmp.operands().resize(1);
               tmp.op0().swap(op);
               tmp.swap(op);
               PARSER.module->add_trans(stack_expr(yyval));
             }
             else
               PARSER.module->add_init(stack_expr(yyval));
           }
#line 2016 "y.tab.cpp"
    break;

  case 59:
#line 395 "parser.y"
                            { init(yyval, ID_init); }
#line 2022 "y.tab.cpp"
    break;

  case 60:
#line 396 "parser.y"
                            { init(yyval, "next"); }
#line 2028 "y.tab.cpp"
    break;

  case 63:
#line 404 "parser.y"
{
  const irep_idt &identifier=stack_expr(yyvsp[-3]).get(ID_identifier);
  smv_parse_treet::mc_vart &var=PARSER.module->vars[identifier];

  switch(var.var_class)
  {
  case smv_parse_treet::mc_vart::UNKNOWN:
    var.type.make_nil();
    var.var_class=smv_parse_treet::mc_vart::DEFINED;
    break;

  case smv_parse_treet::mc_vart::DECLARED:
    var.var_class=smv_parse_treet::mc_vart::DEFINED;
    break;

  case smv_parse_treet::mc_vart::DEFINED:
    yyerror("variable `"+id2string(identifier)+"' already defined");
    YYERROR;
    break;
  
  case smv_parse_treet::mc_vart::ARGUMENT:
    yyerror("variable `"+id2string(identifier)+"' already declared as argument");
    YYERROR;
    break;
  
  default:
    assert(false);
  }

  binary(yyval, yyvsp[-3], ID_equal, yyvsp[-1], bool_typet{});
  PARSER.module->add_define(stack_expr(yyval));
}
#line 2065 "y.tab.cpp"
    break;

  case 66:
#line 442 "parser.y"
                                      { init(yyval, "smv_next"); mto(yyval, yyvsp[-1]); }
#line 2071 "y.tab.cpp"
    break;

  case 67:
#line 443 "parser.y"
                                      { yyval=yyvsp[-1]; }
#line 2077 "y.tab.cpp"
    break;

  case 68:
#line 444 "parser.y"
                                      { yyval=yyvsp[-1]; stack_expr(yyval).id("smv_nondet_choice"); }
#line 2083 "y.tab.cpp"
    break;

  case 69:
#line 445 "parser.y"
                                      { init(yyval, "inc"); mto(yyval, yyvsp[-1]); }
#line 2089 "y.tab.cpp"
    break;

  case 70:
#line 446 "parser.y"
                                      { init(yyval, "dec"); mto(yyval, yyvsp[-1]); }
#line 2095 "y.tab.cpp"
    break;

  case 71:
#line 447 "parser.y"
                                             { j_binary(yyval, yyvsp[-3], ID_plus, yyvsp[-1], stack_expr(yyvsp[-1]).type()); }
#line 2101 "y.tab.cpp"
    break;

  case 72:
#line 448 "parser.y"
                                             { init(yyval, ID_minus); mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[-1]); }
#line 2107 "y.tab.cpp"
    break;

  case 73:
#line 449 "parser.y"
                           { init(yyval, ID_constant); stack_expr(yyval).set(ID_value, stack_expr(yyvsp[0]).id()); stack_expr(yyval).type()=signedbv_typet{32}; }
#line 2113 "y.tab.cpp"
    break;

  case 74:
#line 450 "parser.y"
                                      { init(yyval, ID_constant); stack_expr(yyval).set(ID_value, ID_true); stack_expr(yyval).type()=typet(ID_bool); }
#line 2119 "y.tab.cpp"
    break;

  case 75:
#line 451 "parser.y"
                                      { init(yyval, ID_constant); stack_expr(yyval).set(ID_value, ID_false); stack_expr(yyval).type()=typet(ID_bool); }
#line 2125 "y.tab.cpp"
    break;

  case 76:
#line 452 "parser.y"
                                         { yyval=yyvsp[-1]; }
#line 2131 "y.tab.cpp"
    break;

  case 77:
#line 453 "parser.y"
                                                                 { init(yyval, ID_switch); mto(yyval, yyvsp[-4]); mto(yyval, yyvsp[-1]); }
#line 2137 "y.tab.cpp"
    break;

  case 78:
#line 454 "parser.y"
                                           { init(yyval, ID_unary_minus); mto(yyval, yyvsp[0]); }
#line 2143 "y.tab.cpp"
    break;

  case 79:
#line 455 "parser.y"
                                      { binary_arith(yyval, yyvsp[-2], ID_mod, yyvsp[0]); }
#line 2149 "y.tab.cpp"
    break;

  case 80:
#line 456 "parser.y"
                                      { binary_arith(yyval, yyvsp[-2], ID_mult, yyvsp[0]); }
#line 2155 "y.tab.cpp"
    break;

  case 81:
#line 457 "parser.y"
                                      { binary_arith(yyval, yyvsp[-2], ID_div, yyvsp[0]); }
#line 2161 "y.tab.cpp"
    break;

  case 82:
#line 458 "parser.y"
                                      { binary_arith(yyval, yyvsp[-2], ID_plus, yyvsp[0]); }
#line 2167 "y.tab.cpp"
    break;

  case 83:
#line 459 "parser.y"
                                      { binary_arith(yyval, yyvsp[-2], ID_minus, yyvsp[0]); }
#line 2173 "y.tab.cpp"
    break;

  case 84:
#line 460 "parser.y"
                                      { binary(yyval, yyvsp[-2], ID_equal, yyvsp[0], bool_typet{}); }
#line 2179 "y.tab.cpp"
    break;

  case 85:
#line 461 "parser.y"
                                      { binary(yyval, yyvsp[-2], ID_implies, yyvsp[0], bool_typet{}); }
#line 2185 "y.tab.cpp"
    break;

  case 86:
#line 462 "parser.y"
                                      { j_binary(yyval, yyvsp[-2], ID_xor, yyvsp[0], bool_typet{}); }
#line 2191 "y.tab.cpp"
    break;

  case 87:
#line 463 "parser.y"
                                      { j_binary(yyval, yyvsp[-2], ID_or, yyvsp[0], bool_typet{}); }
#line 2197 "y.tab.cpp"
    break;

  case 88:
#line 464 "parser.y"
                                      { j_binary(yyval, yyvsp[-2], ID_and, yyvsp[0], bool_typet{}); }
#line 2203 "y.tab.cpp"
    break;

  case 89:
#line 465 "parser.y"
                                      { init(yyval, ID_not); mto(yyval, yyvsp[0]); }
#line 2209 "y.tab.cpp"
    break;

  case 90:
#line 466 "parser.y"
                                      { init(yyval, ID_AX);  mto(yyval, yyvsp[0]); }
#line 2215 "y.tab.cpp"
    break;

  case 91:
#line 467 "parser.y"
                                      { init(yyval, ID_AF);  mto(yyval, yyvsp[0]); }
#line 2221 "y.tab.cpp"
    break;

  case 92:
#line 468 "parser.y"
                                      { init(yyval, ID_AG);  mto(yyval, yyvsp[0]); }
#line 2227 "y.tab.cpp"
    break;

  case 93:
#line 469 "parser.y"
                                      { init(yyval, ID_EX);  mto(yyval, yyvsp[0]); }
#line 2233 "y.tab.cpp"
    break;

  case 94:
#line 470 "parser.y"
                                      { init(yyval, ID_EF);  mto(yyval, yyvsp[0]); }
#line 2239 "y.tab.cpp"
    break;

  case 95:
#line 471 "parser.y"
                                      { init(yyval, ID_EG);  mto(yyval, yyvsp[0]); }
#line 2245 "y.tab.cpp"
    break;

  case 96:
#line 472 "parser.y"
                                      { init(yyval, ID_A);  mto(yyval, yyvsp[0]); }
#line 2251 "y.tab.cpp"
    break;

  case 97:
#line 473 "parser.y"
                                      { init(yyval, ID_E);  mto(yyval, yyvsp[0]); }
#line 2257 "y.tab.cpp"
    break;

  case 98:
#line 474 "parser.y"
                                      { init(yyval, ID_F);  mto(yyval, yyvsp[0]); }
#line 2263 "y.tab.cpp"
    break;

  case 99:
#line 475 "parser.y"
                                      { init(yyval, ID_G);  mto(yyval, yyvsp[0]); }
#line 2269 "y.tab.cpp"
    break;

  case 100:
#line 476 "parser.y"
                                      { init(yyval, ID_X);  mto(yyval, yyvsp[0]); }
#line 2275 "y.tab.cpp"
    break;

  case 101:
#line 477 "parser.y"
                                      { binary(yyval, yyvsp[-2], ID_U, yyvsp[0], stack_expr(yyvsp[-2]).type()); }
#line 2281 "y.tab.cpp"
    break;

  case 102:
#line 478 "parser.y"
                                      { binary(yyval, yyvsp[-2], ID_equal,  yyvsp[0], bool_typet{}); }
#line 2287 "y.tab.cpp"
    break;

  case 103:
#line 479 "parser.y"
                                      { binary(yyval, yyvsp[-2], ID_notequal, yyvsp[0], bool_typet{}); }
#line 2293 "y.tab.cpp"
    break;

  case 104:
#line 480 "parser.y"
                                      { binary(yyval, yyvsp[-2], ID_lt,  yyvsp[0], bool_typet{}); }
#line 2299 "y.tab.cpp"
    break;

  case 105:
#line 481 "parser.y"
                                      { binary(yyval, yyvsp[-2], ID_le, yyvsp[0], bool_typet{}); }
#line 2305 "y.tab.cpp"
    break;

  case 106:
#line 482 "parser.y"
                                      { binary(yyval, yyvsp[-2], ID_gt,  yyvsp[0], bool_typet{}); }
#line 2311 "y.tab.cpp"
    break;

  case 107:
#line 483 "parser.y"
                                      { binary(yyval, yyvsp[-2], ID_ge, yyvsp[0], bool_typet{}); }
#line 2317 "y.tab.cpp"
    break;

  case 108:
#line 484 "parser.y"
                                      { binary(yyval, yyvsp[-2], "smv_union", yyvsp[0], bool_typet{}); }
#line 2323 "y.tab.cpp"
    break;

  case 109:
#line 485 "parser.y"
                                      { binary(yyval, yyvsp[-2], "smv_setin", yyvsp[0], bool_typet{}); }
#line 2329 "y.tab.cpp"
    break;

  case 110:
#line 486 "parser.y"
                                      { binary(yyval, yyvsp[-2], "smv_setnotin", yyvsp[0], bool_typet{}); }
#line 2335 "y.tab.cpp"
    break;

  case 111:
#line 489 "parser.y"
                      { init(yyval); mto(yyval, yyvsp[0]); }
#line 2341 "y.tab.cpp"
    break;

  case 112:
#line 490 "parser.y"
                                       { yyval=yyvsp[-2]; mto(yyval, yyvsp[0]); }
#line 2347 "y.tab.cpp"
    break;

  case 113:
#line 494 "parser.y"
           {
             const irep_idt &id=stack_expr(yyvsp[0]).id();

             bool is_enum=(PARSER.module->enum_set.find(id)!=
                           PARSER.module->enum_set.end());
             bool is_var=(PARSER.module->vars.find(id)!=
                          PARSER.module->vars.end());

             if(is_var && is_enum)
             {
               yyerror("identifier `"+id2string(id)+"' is ambiguous");
               YYERROR;
             }
             else if(is_enum)
             {
               init(yyval, ID_constant);
               stack_expr(yyval).type()=typet(ID_enumeration);
               stack_expr(yyval).set(ID_value, id);
             }
             else // not an enum, probably a variable
             {
               init(yyval, ID_symbol);
               stack_expr(yyval).set(ID_identifier, id);
               auto var_it = PARSER.module->vars.find(id);
               if(var_it!= PARSER.module->vars.end())
                 stack_expr(yyval).type()=var_it->second.type;
               //PARSER.module->vars[stack_expr($1).id()];
             }
           }
#line 2381 "y.tab.cpp"
    break;

  case 114:
#line 524 "parser.y"
           {
             const irep_idt &id=stack_expr(yyvsp[0]).id();

             init(yyval, ID_symbol);
             stack_expr(yyval).set(ID_identifier, id);
             PARSER.module->vars[id];
           }
#line 2393 "y.tab.cpp"
    break;

  case 115:
#line 534 "parser.y"
           {
             init(yyval, std::string(stack_expr(yyvsp[0]).id_string(), 1)); // remove backslash
           }
#line 2401 "y.tab.cpp"
    break;

  case 117:
#line 539 "parser.y"
           {
             std::string id(stack_expr(yyvsp[-2]).id_string());
             id+=".";
             id+=std::string(stack_expr(yyvsp[0]).id_string(), 1); // remove backslash
             init(yyval, id);
           }
#line 2412 "y.tab.cpp"
    break;

  case 118:
#line 546 "parser.y"
           {
             std::string id(stack_expr(yyvsp[-2]).id_string());
             id+=".";
             id+=stack_expr(yyvsp[0]).id_string();
             init(yyval, id);
           }
#line 2423 "y.tab.cpp"
    break;

  case 119:
#line 553 "parser.y"
           {
             std::string id(stack_expr(yyvsp[-3]).id_string());
             id+="[";
             id+=stack_expr(yyvsp[-1]).id_string();
             id+="]";
             init(yyval, id);
           }
#line 2435 "y.tab.cpp"
    break;

  case 120:
#line 561 "parser.y"
           {
             std::string id(stack_expr(yyvsp[-3]).id_string());
             id+="(";
             id+=stack_expr(yyvsp[-1]).id_string();
             id+=")";
             init(yyval, id);
           }
#line 2447 "y.tab.cpp"
    break;

  case 121:
#line 571 "parser.y"
           { init(yyval, "smv_cases"); }
#line 2453 "y.tab.cpp"
    break;

  case 122:
#line 573 "parser.y"
           { yyval=yyvsp[-1]; mto(yyval, yyvsp[0]); }
#line 2459 "y.tab.cpp"
    break;

  case 123:
#line 577 "parser.y"
           { binary(yyval, yyvsp[-3], ID_case, yyvsp[-1], stack_expr(yyvsp[-1]).type()); }
#line 2465 "y.tab.cpp"
    break;

  case 124:
#line 581 "parser.y"
           { init(yyval, "switches"); }
#line 2471 "y.tab.cpp"
    break;

  case 125:
#line 583 "parser.y"
           { yyval=yyvsp[-1]; mto(yyval, yyvsp[0]); }
#line 2477 "y.tab.cpp"
    break;

  case 126:
#line 587 "parser.y"
           { init(yyval, ID_switch); mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[-1]); }
#line 2483 "y.tab.cpp"
    break;


#line 2487 "y.tab.cpp"

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
#line 590 "parser.y"


int yysmverror(const std::string &error)
{
  PARSER.parse_error(error, yytext);
  return 0;
}

#undef yyerror

