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
#define yyparse         yyverilogparse
#define yylex           yyveriloglex
#define yyerror         yyverilogerror
#define yydebug         yyverilogdebug
#define yynerrs         yyverilognerrs
#define yylval          yyveriloglval
#define yychar          yyverilogchar

/* First part of user prologue.  */
#line 1 "parser.y"

/*******************************************************************\

Module: Verilog Parser

Author: Daniel Kroening, kroening@cs.cmu.edu

\*******************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <util/ebmc_util.h>
#include <util/std_expr.h>
#include <util/c_types.h>

#include "verilog_parser.h"

#define PARSER verilog_parser
#define YYSTYPE unsigned
#define YYSTYPE_IS_TRIVIAL 1

//#define YYDEBUG 1

#define mto(x, y) stack_expr(x).move_to_operands(stack_expr(y))
#define mts(x, y) stack_expr(x).move_to_sub((irept &)stack_expr(y))
#define swapop(x, y) stack_expr(x).operands().swap(stack_expr(y).operands())
#define addswap(x, y, z) stack_expr(x).add(y).swap(stack_expr(z))

int yyveriloglex();
extern char *yyverilogtext;

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void init(exprt &expr)
{
  expr.clear();
  verilog_parser.set_source_location(expr);
}

/*******************************************************************\

Function: init

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void init(YYSTYPE &expr)
{
  newstack(expr);
  init(stack_expr(expr));
}

/*******************************************************************\

Function: make_nil

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

inline static void make_nil(YYSTYPE &expr)
{
  newstack(expr);
  stack_expr(expr).make_nil();
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
  stack_expr(expr).id(id);
}

/*******************************************************************\

Function: new_symbol

  Inputs:

 Outputs:

 Purpose:


\*******************************************************************/

inline static void new_symbol(YYSTYPE &dest, YYSTYPE &src)
{
  init(dest, ID_symbol);
  addswap(dest, ID_identifier, src);
}

/*******************************************************************\

Function: extractbit

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

static void extractbit(YYSTYPE &expr, YYSTYPE &identifier, YYSTYPE &part)
{
  init(expr, ID_extractbit);
  mto(expr, identifier);
  stack_expr(expr).move_to_operands(stack_expr(part).op0());
}

/*******************************************************************\

Function: extractbits

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

static void extractbits(YYSTYPE &expr, YYSTYPE &identifier, YYSTYPE &range)
{
  init(expr, ID_extractbits);
  mto(expr, identifier);
  
  if(stack_expr(range).id()==ID_part_select)
  {
    stack_expr(expr).move_to_operands(stack_expr(range).op0(),
                                 stack_expr(range).op1());
  }
  else if(stack_expr(range).id()==ID_indexed_part_select_plus)
  {
    exprt offset=minus_exprt(stack_expr(range).op1(), from_integer(1, integer_typet{}));
    stack_expr(expr).copy_to_operands(stack_expr(range).op0(),
                                 plus_exprt(stack_expr(range).op0(), offset));
  }
  else if(stack_expr(range).id()==ID_indexed_part_select_minus)
  {
    exprt offset=minus_exprt(from_integer(1, integer_typet{}), stack_expr(range).op1());
    stack_expr(expr).copy_to_operands(stack_expr(range).op0(),
                                 plus_exprt(stack_expr(range).op0(), offset));
  }
  else
    assert(false);
}

/*******************************************************************\

Function: add_as_subtype

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

static void add_as_subtype(typet &dest, typet &what)
{
  // this is recursive and quadratic-time, so not super.
  if(what.is_nil())
  {
    // do nothing
  }
  else if(dest.is_nil() || dest.id()==irep_idt())
    dest.swap(what);
  else
  {
    typet &subtype=dest.subtype();
    add_as_subtype(subtype, what);
  }
}

/*******************************************************************\

Function: yyverilogerror

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

int yyverilogerror(const char *error)
{
  verilog_parser.parse_error(error, yyverilogtext);
  return strlen(error)+1;
}


#line 306 "verilog_y.tab.cpp"

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
#ifndef YY_YYVERILOG_VERILOG_Y_TAB_HPP_INCLUDED
# define YY_YYVERILOG_VERILOG_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yyverilogdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_PARSE_LANGUAGE = 258,
    TOK_PARSE_EXPRESSION = 259,
    TOK_PARSE_TYPE = 260,
    TOK_PARENASTERIC = 261,
    TOK_ASTERICPAREN = 262,
    TOK_EXCLAM = 263,
    TOK_TILDE = 264,
    TOK_AMPER = 265,
    TOK_TILDEAMPER = 266,
    TOK_TILDEVERTBAR = 267,
    TOK_CARET = 268,
    TOK_TILDECARET = 269,
    TOK_CARETTILDE = 270,
    TOK_MINUSGREATER = 271,
    TOK_ASTERIC = 272,
    TOK_SLASH = 273,
    TOK_PERCENT = 274,
    TOK_EQUALEQUAL = 275,
    TOK_EXCLAMEQUAL = 276,
    TOK_EQUALEQUALEQUAL = 277,
    TOK_EXCLAMEQUALEQUAL = 278,
    TOK_AMPERAMPER = 279,
    TOK_ASTERICASTERIC = 280,
    TOK_VERTBARVERTBAR = 281,
    TOK_LESS = 282,
    TOK_LESSEQUAL = 283,
    TOK_GREATER = 284,
    TOK_GREATEREQUAL = 285,
    TOK_GREATERGREATER = 286,
    TOK_GREATERGREATERGREATER = 287,
    TOK_LESSLESS = 288,
    TOK_LESSLESSLESS = 289,
    TOK_PLUS = 290,
    TOK_MINUS = 291,
    TOK_VERTBAR = 292,
    TOK_QUESTION = 293,
    TOK_COLON = 294,
    TOK_ALWAYS = 295,
    TOK_AND = 296,
    TOK_ASSIGN = 297,
    TOK_AUTOMATIC = 298,
    TOK_BEGIN = 299,
    TOK_BUF = 300,
    TOK_BUFIF0 = 301,
    TOK_BUFIF1 = 302,
    TOK_CASE = 303,
    TOK_CASEX = 304,
    TOK_CASEZ = 305,
    TOK_CMOS = 306,
    TOK_DEASSIGN = 307,
    TOK_DEFAULT = 308,
    TOK_DEFPARAM = 309,
    TOK_DISABLE = 310,
    TOK_EDGE = 311,
    TOK_ELSE = 312,
    TOK_END = 313,
    TOK_ENDCASE = 314,
    TOK_ENDFUNCTION = 315,
    TOK_ENDGENERATE = 316,
    TOK_ENDMODULE = 317,
    TOK_ENDPRIMITIVE = 318,
    TOK_ENDSPECIFY = 319,
    TOK_ENDTABLE = 320,
    TOK_ENDTASK = 321,
    TOK_EVENT = 322,
    TOK_FOR = 323,
    TOK_FORCE = 324,
    TOK_FOREVER = 325,
    TOK_FORK = 326,
    TOK_FUNCTION = 327,
    TOK_GENERATE = 328,
    TOK_GENVAR = 329,
    TOK_HIGHZ0 = 330,
    TOK_HIGHZ1 = 331,
    TOK_IF = 332,
    TOK_IFNONE = 333,
    TOK_INITIAL = 334,
    TOK_INOUT = 335,
    TOK_INPUT = 336,
    TOK_INTEGER = 337,
    TOK_JOIN = 338,
    TOK_LARGE = 339,
    TOK_LOCALPARAM = 340,
    TOK_MACROMODULE = 341,
    TOK_MEDIUM = 342,
    TOK_MODULE = 343,
    TOK_NAND = 344,
    TOK_NEGEDGE = 345,
    TOK_NMOS = 346,
    TOK_NOR = 347,
    TOK_NOT = 348,
    TOK_NOTIF0 = 349,
    TOK_NOTIF1 = 350,
    TOK_OR = 351,
    TOK_OUTPUT = 352,
    TOK_PARAMETER = 353,
    TOK_PMOS = 354,
    TOK_POSEDGE = 355,
    TOK_PRIMITIVE = 356,
    TOK_PULL0 = 357,
    TOK_PULL1 = 358,
    TOK_PULLDOWN = 359,
    TOK_PULLUP = 360,
    TOK_RCMOS = 361,
    TOK_REAL = 362,
    TOK_REALTIME = 363,
    TOK_REG = 364,
    TOK_RELEASE = 365,
    TOK_REPEAT = 366,
    TOK_RNMOS = 367,
    TOK_RPMOS = 368,
    TOK_RTRAN = 369,
    TOK_RTRANIF0 = 370,
    TOK_RTRANIF1 = 371,
    TOK_SCALARED = 372,
    TOK_SIGNED = 373,
    TOK_SMALL = 374,
    TOK_SPECIFY = 375,
    TOK_SPECPARAM = 376,
    TOK_STRONG0 = 377,
    TOK_STRONG1 = 378,
    TOK_SUPPLY0 = 379,
    TOK_SUPPLY1 = 380,
    TOK_TABLE = 381,
    TOK_TASK = 382,
    TOK_TIME = 383,
    TOK_TRAN = 384,
    TOK_TRANIF0 = 385,
    TOK_TRANIF1 = 386,
    TOK_TRI = 387,
    TOK_TRI0 = 388,
    TOK_TRI1 = 389,
    TOK_TRIAND = 390,
    TOK_TRIOR = 391,
    TOK_TRIREG = 392,
    TOK_UNSIGNED = 393,
    TOK_VECTORED = 394,
    TOK_WAIT = 395,
    TOK_WAND = 396,
    TOK_WEAK0 = 397,
    TOK_WEAK1 = 398,
    TOK_WHILE = 399,
    TOK_WIRE = 400,
    TOK_WOR = 401,
    TOK_XNOR = 402,
    TOK_XOR = 403,
    TOK_SETUP = 404,
    TOK_HOLD = 405,
    TOK_RECOVERY = 406,
    TOK_REMOVAL = 407,
    TOK_WIDTH = 408,
    TOK_SKEW = 409,
    TOK_VERTBARMINUSGREATER = 410,
    TOK_VERTBAREQUALGREATER = 411,
    TOK_PLUSPLUS = 412,
    TOK_MINUSMINUS = 413,
    TOK_PLUSEQUAL = 414,
    TOK_PLUSCOLON = 415,
    TOK_MINUSEQUAL = 416,
    TOK_MINUSCOLON = 417,
    TOK_ASTERICEQUAL = 418,
    TOK_SLASHEQUAL = 419,
    TOK_PERCENTEQUAL = 420,
    TOK_AMPEREQUAL = 421,
    TOK_CARETEQUAL = 422,
    TOK_VERTBAREQUAL = 423,
    TOK_LESSLESSEQUAL = 424,
    TOK_GREATERGREATEREQUAL = 425,
    TOK_LESSLESSLESSEQUAL = 426,
    TOK_GREATERGREATERGREATEREQUAL = 427,
    TOK_HASHHASH = 428,
    TOK_ACCEPT_ON = 429,
    TOK_ALIAS = 430,
    TOK_ALWAYS_COMB = 431,
    TOK_ALWAYS_FF = 432,
    TOK_ALWAYS_LATCH = 433,
    TOK_ASSERT = 434,
    TOK_ASSUME = 435,
    TOK_BEFORE = 436,
    TOK_BIND = 437,
    TOK_BINS = 438,
    TOK_BINSOF = 439,
    TOK_BIT = 440,
    TOK_BREAK = 441,
    TOK_BYTE = 442,
    TOK_CHANDLE = 443,
    TOK_CHECKER = 444,
    TOK_CLASS = 445,
    TOK_CLOCKING = 446,
    TOK_CONFIG = 447,
    TOK_CONST = 448,
    TOK_CONSTRAINT = 449,
    TOK_CONTEXT = 450,
    TOK_CONTINUE = 451,
    TOK_COVER = 452,
    TOK_COVERGROUP = 453,
    TOK_COVERPOINT = 454,
    TOK_CROSS = 455,
    TOK_DIST = 456,
    TOK_DO = 457,
    TOK_ENDCLASS = 458,
    TOK_ENDCLOCKING = 459,
    TOK_ENDCONFIG = 460,
    TOK_ENDGROUP = 461,
    TOK_ENDINTERFACE = 462,
    TOK_ENDPACKAGE = 463,
    TOK_ENDPROGRAM = 464,
    TOK_ENDPROPERTY = 465,
    TOK_ENDSEQUENCE = 466,
    TOK_ENUM = 467,
    TOK_EVENTUALLY = 468,
    TOK_EXPECT = 469,
    TOK_EXPORT = 470,
    TOK_EXTENDS = 471,
    TOK_EXTERN = 472,
    TOK_FINAL = 473,
    TOK_FIRST_MATCH = 474,
    TOK_FOREACH = 475,
    TOK_IFF = 476,
    TOK_IGNORE_BINS = 477,
    TOK_ILLEGAL_BINS = 478,
    TOK_IMPORT = 479,
    TOK_INSIDE = 480,
    TOK_INT = 481,
    TOK_INTERFACE = 482,
    TOK_INTERSECT = 483,
    TOK_JOIN_ANY = 484,
    TOK_JOIN_NONE = 485,
    TOK_LOCAL = 486,
    TOK_LOGIC = 487,
    TOK_LONGINT = 488,
    TOK_MATCHES = 489,
    TOK_MODPORT = 490,
    TOK_NEW = 491,
    TOK_NEXTTIME = 492,
    TOK_NULL = 493,
    TOK_PACKAGE = 494,
    TOK_PACKED = 495,
    TOK_PRIORITY = 496,
    TOK_PROGRAM = 497,
    TOK_PROPERTY = 498,
    TOK_PROTECTED = 499,
    TOK_PURE = 500,
    TOK_RAND = 501,
    TOK_RANDC = 502,
    TOK_RANDCASE = 503,
    TOK_RANDSEQUENCE = 504,
    TOK_REF = 505,
    TOK_RETURN = 506,
    TOK_S_ALWAYS = 507,
    TOK_S_EVENTUALLY = 508,
    TOK_S_NEXTTIME = 509,
    TOK_S_UNTIL = 510,
    TOK_S_UNTIL_WITH = 511,
    TOK_SEQUENCE = 512,
    TOK_SHORTINT = 513,
    TOK_SHORTREAL = 514,
    TOK_SOLVE = 515,
    TOK_STATIC = 516,
    TOK_STRING = 517,
    TOK_STRUCT = 518,
    TOK_SUPER = 519,
    TOK_TAGGED = 520,
    TOK_THIS = 521,
    TOK_THROUGHOUT = 522,
    TOK_TIMEPRECISION = 523,
    TOK_TIMEUNIT = 524,
    TOK_TYPE = 525,
    TOK_TYPEDEF = 526,
    TOK_UNION = 527,
    TOK_UNIQUE = 528,
    TOK_UNTIL = 529,
    TOK_UNTIL_WITH = 530,
    TOK_VAR = 531,
    TOK_VIRTUAL = 532,
    TOK_VOID = 533,
    TOK_WAIT_ORDER = 534,
    TOK_WILDCARD = 535,
    TOK_WITH = 536,
    TOK_WITHIN = 537,
    TOK_ENDOFFILE = 538,
    TOK_CHARSTR = 539,
    TOK_NUMBER = 540,
    TOK_QSTRING = 541,
    TOK_SYSIDENT = 542,
    TOK_SCANNER_ERROR = 543,
    TOK_AMPERTILDE = 544,
    UNARY_MINUS = 545,
    UNARY_PLUS = 546,
    LT_TOK_ELSE = 547
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yyveriloglval;

int yyverilogparse (void);

#endif /* !YY_YYVERILOG_VERILOG_Y_TAB_HPP_INCLUDED  */



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
#define YYFINAL  48
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3385

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  306
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  268
/* YYNRULES -- Number of rules.  */
#define YYNRULES  601
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1093

#define YYUNDEFTOK  2
#define YYMAXUTOK   547


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,   303,   305,     2,     2,     2,
     299,   300,     2,     2,   296,     2,   301,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   293,
       2,   302,     2,     2,   304,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   297,     2,   298,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   294,     2,   295,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   567,   567,   567,   568,   570,   574,   576,   578,   582,
     583,   584,   585,   586,   587,   588,   589,   597,   601,   608,
     612,   616,   620,   625,   630,   638,   641,   643,   645,   647,
     652,   653,   661,   665,   667,   672,   673,   674,   677,   681,
     685,   688,   697,   702,   703,   717,   718,   723,   724,   733,
     734,   742,   747,   751,   756,   762,   767,   768,   771,   775,
     778,   783,   785,   789,   790,   794,   795,   796,   800,   804,
     808,   811,   815,   816,   820,   821,   824,   827,   831,   832,
     835,   836,   839,   841,   843,   848,   857,   866,   868,   872,
     874,   878,   894,   909,   914,   915,   920,   924,   925,   928,
     930,   934,   936,   941,   954,   955,   956,   960,   968,   973,
     981,   989,   991,   995,  1000,  1007,  1008,  1012,  1013,  1014,
    1018,  1023,  1028,  1030,  1034,  1042,  1043,  1052,  1053,  1057,
    1058,  1059,  1071,  1077,  1078,  1083,  1084,  1085,  1086,  1087,
    1091,  1092,  1096,  1098,  1102,  1105,  1111,  1112,  1116,  1117,
    1118,  1122,  1135,  1138,  1143,  1145,  1150,  1151,  1152,  1156,
    1158,  1159,  1160,  1162,  1163,  1164,  1165,  1166,  1167,  1168,
    1172,  1173,  1174,  1175,  1177,  1178,  1179,  1183,  1184,  1185,
    1188,  1191,  1195,  1200,  1202,  1206,  1211,  1213,  1218,  1220,
    1224,  1232,  1235,  1236,  1240,  1248,  1256,  1261,  1269,  1276,
    1286,  1287,  1291,  1292,  1297,  1298,  1302,  1303,  1308,  1309,
    1314,  1316,  1321,  1329,  1331,  1335,  1337,  1342,  1349,  1358,
    1359,  1362,  1365,  1370,  1375,  1380,  1382,  1387,  1392,  1401,
    1402,  1403,  1406,  1407,  1408,  1409,  1410,  1411,  1412,  1413,
    1414,  1415,  1425,  1427,  1431,  1438,  1443,  1445,  1449,  1454,
    1455,  1458,  1459,  1460,  1461,  1465,  1469,  1485,  1486,  1491,
    1492,  1494,  1496,  1498,  1503,  1505,  1510,  1511,  1515,  1529,
    1530,  1535,  1536,  1537,  1538,  1542,  1543,  1544,  1546,  1548,
    1554,  1555,  1562,  1567,  1569,  1573,  1578,  1582,  1585,  1588,
    1592,  1594,  1603,  1605,  1607,  1609,  1611,  1613,  1615,  1617,
    1619,  1624,  1625,  1629,  1630,  1631,  1632,  1636,  1637,  1638,
    1639,  1643,  1644,  1645,  1646,  1647,  1648,  1652,  1653,  1657,
    1658,  1659,  1660,  1664,  1665,  1669,  1671,  1676,  1685,  1686,
    1689,  1696,  1705,  1706,  1711,  1712,  1716,  1718,  1723,  1725,
    1730,  1733,  1740,  1743,  1745,  1750,  1754,  1756,  1761,  1765,
    1766,  1770,  1772,  1777,  1781,  1783,  1788,  1799,  1804,  1806,
    1810,  1814,  1816,  1820,  1828,  1833,  1834,  1835,  1836,  1837,
    1838,  1839,  1840,  1841,  1842,  1843,  1844,  1845,  1846,  1847,
    1848,  1849,  1850,  1851,  1852,  1853,  1854,  1858,  1863,  1864,
    1868,  1875,  1879,  1887,  1888,  1891,  1894,  1897,  1899,  1907,
    1912,  1915,  1923,  1926,  1933,  1935,  1940,  1941,  1947,  1948,
    1956,  1957,  1964,  1965,  1972,  1976,  1978,  1980,  1985,  1987,
    1989,  1992,  1998,  2000,  2004,  2009,  2010,  2011,  2012,  2013,
    2014,  2015,  2016,  2017,  2018,  2019,  2020,  2021,  2025,  2027,
    2032,  2037,  2038,  2039,  2043,  2045,  2047,  2052,  2053,  2054,
    2059,  2063,  2068,  2070,  2072,  2076,  2080,  2087,  2092,  2094,
    2096,  2101,  2103,  2105,  2110,  2112,  2117,  2120,  2123,  2129,
    2131,  2136,  2138,  2143,  2151,  2153,  2155,  2157,  2161,  2164,
    2168,  2169,  2173,  2175,  2182,  2200,  2201,  2205,  2208,  2218,
    2221,  2222,  2224,  2226,  2242,  2243,  2247,  2249,  2253,  2256,
    2257,  2263,  2264,  2268,  2270,  2275,  2276,  2278,  2279,  2281,
    2283,  2285,  2287,  2289,  2291,  2293,  2295,  2297,  2299,  2301,
    2303,  2305,  2307,  2309,  2311,  2313,  2315,  2317,  2319,  2321,
    2323,  2325,  2327,  2329,  2334,  2336,  2342,  2343,  2344,  2345,
    2346,  2347,  2348,  2350,  2351,  2352,  2353,  2354,  2355,  2356,
    2357,  2358,  2359,  2363,  2364,  2366,  2368,  2370,  2375,  2377,
    2379,  2384,  2385,  2386,  2387,  2388,  2389,  2390,  2391,  2392,
    2396,  2398,  2400,  2402,  2406,  2407,  2408,  2410,  2412,  2413,
    2414,  2415,  2417,  2421,  2424,  2428,  2433,  2435,  2439,  2449,
    2456,  2460,  2461,  2469,  2474,  2487,  2500,  2602,  2603,  2607,
    2611,  2614
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_PARSE_LANGUAGE",
  "TOK_PARSE_EXPRESSION", "TOK_PARSE_TYPE", "\"(*\"", "\"*)\"", "\"!\"",
  "\"~\"", "\"&\"", "\"~&\"", "\"~|\"", "\"^\"", "\"~^\"", "\"^~\"",
  "\"->\"", "\"*\"", "\"/\"", "\"%\"", "\"==\"", "\"!=\"", "\"===\"",
  "\"!==\"", "\"&&\"", "\"**\"", "\"||\"", "\"<\"", "\"<=\"", "\">\"",
  "\">=\"", "\">>\"", "\">>>\"", "\"<<\"", "\"<<<\"", "\"+\"", "\"-\"",
  "\"|\"", "\"?\"", "\":\"", "\"always\"", "\"and\"", "\"assign\"",
  "\"automatic\"", "\"begin\"", "\"buf\"", "\"bufif0\"", "\"bufif1\"",
  "\"case\"", "\"casex\"", "\"casez\"", "\"cmos\"", "\"deassign\"",
  "\"default\"", "\"defparam\"", "\"disable\"", "\"edge\"", "\"else\"",
  "\"end\"", "\"endcase\"", "\"endfunction\"", "\"endgenerate\"",
  "\"endmodule\"", "\"endprimitive\"", "\"endspecify\"", "\"endtable\"",
  "\"endtask\"", "\"event\"", "\"for\"", "\"force\"", "\"forever\"",
  "\"fork\"", "\"function\"", "\"generate\"", "\"genvar\"", "\"highz0\"",
  "\"highz1\"", "\"if\"", "\"ifnone\"", "\"initial\"", "\"inout\"",
  "\"input\"", "\"integer\"", "\"join\"", "\"large\"", "\"localparam\"",
  "\"macromodule\"", "\"medium\"", "\"module\"", "\"nand\"", "\"negedge\"",
  "\"nmos\"", "\"nor\"", "\"not\"", "\"notif0\"", "\"notif1\"", "\"or\"",
  "\"output\"", "\"parameter\"", "\"pmos\"", "\"posedge\"",
  "\"primitive\"", "\"pull0\"", "\"pull1\"", "\"pulldown\"", "\"pullup\"",
  "\"rcmos\"", "\"real\"", "\"realtime\"", "\"reg\"", "\"release\"",
  "\"repeat\"", "\"rnmos\"", "\"rpmos\"", "\"rtran\"", "\"rtranif0\"",
  "\"rtranif1\"", "\"scalared\"", "\"signed\"", "\"small\"", "\"specify\"",
  "\"specparam\"", "\"strong0\"", "\"strong1\"", "\"supply0\"",
  "\"supply1\"", "\"table\"", "\"task\"", "\"time\"", "\"tran\"",
  "\"tranif0\"", "\"tranif1\"", "\"tri\"", "\"tri0\"", "\"tri1\"",
  "\"triand\"", "\"trior\"", "\"trireg\"", "\"unsigned\"", "\"vectored\"",
  "\"wait\"", "\"wand\"", "\"weak0\"", "\"weak1\"", "\"while\"",
  "\"wire\"", "\"wor\"", "\"xnor\"", "\"xor\"", "\"setup\"", "\"hold\"",
  "\"recovery\"", "\"removal\"", "\"width\"", "\"skew\"", "\"|->\"",
  "\"|=>\"", "\"++\"", "\"--\"", "\"+=\"", "\"+:\"", "\"-=\"", "\"-:\"",
  "\"*=\"", "\"/=\"", "\"%=\"", "\"&=\"", "\"^=\"", "\"|=\"", "\"<<=\"",
  "\">>=\"", "\"<<<=\"", "\">>>=\"", "\"##\"", "\"accept_on\"",
  "\"alias\"", "\"always_comb\"", "\"always_ff\"", "\"always_latch\"",
  "\"assert\"", "\"assume\"", "\"before\"", "\"bind\"", "\"bins\"",
  "\"binsof\"", "\"bit\"", "\"break\"", "\"byte\"", "\"chandle\"",
  "\"checker\"", "\"class\"", "\"clocking\"", "\"config\"", "\"const\"",
  "\"constraint\"", "\"context\"", "\"continue\"", "\"cover\"",
  "\"covergroup\"", "\"coverpoint\"", "\"cross\"", "\"dist\"", "\"do\"",
  "\"endclass\"", "\"endclocking\"", "\"endconfig\"", "\"endgroup\"",
  "\"endinterface\"", "\"endpackage\"", "\"endprogram\"",
  "\"endproperty\"", "\"endsequence\"", "\"enum\"", "\"eventually\"",
  "\"expect\"", "\"export\"", "\"extends\"", "\"extern\"", "\"final\"",
  "\"first_match\"", "\"foreach\"", "\"iff\"", "\"ignore_bins\"",
  "\"illegal_bins\"", "\"import\"", "\"inside\"", "\"int\"",
  "\"interface\"", "\"intersect\"", "\"join_any\"", "\"join_none\"",
  "\"local\"", "\"logic\"", "\"longint\"", "\"matches\"", "\"modport\"",
  "\"new\"", "\"nexttime\"", "\"null\"", "\"package\"", "\"packed\"",
  "\"priority\"", "\"program\"", "\"property\"", "\"protected\"",
  "\"pure\"", "\"rand\"", "\"randc\"", "\"randcase\"", "\"randsequence\"",
  "\"ref\"", "\"return\"", "\"s_always\"", "\"s_eventually\"",
  "\"s_nexttime\"", "\"s_until\"", "\"s_until_with\"", "\"sequence\"",
  "\"shortint\"", "\"shortreal\"", "\"solve\"", "\"static\"", "\"string\"",
  "\"struct\"", "\"super\"", "\"tagged\"", "\"this\"", "\"throughout\"",
  "\"timeprecision\"", "\"timeunit\"", "\"type\"", "\"typedef\"",
  "\"union\"", "\"unique\"", "\"until\"", "\"until_with\"", "\"var\"",
  "\"virtual\"", "\"void\"", "\"wait_order\"", "\"wildcard\"", "\"with\"",
  "\"within\"", "TOK_ENDOFFILE", "TOK_CHARSTR", "TOK_NUMBER",
  "TOK_QSTRING", "TOK_SYSIDENT", "TOK_SCANNER_ERROR", "TOK_AMPERTILDE",
  "UNARY_MINUS", "UNARY_PLUS", "LT_TOK_ELSE", "';'", "'{'", "'}'", "','",
  "'['", "']'", "'('", "')'", "'.'", "'='", "'#'", "'@'", "'$'", "$accept",
  "grammar", "$@1", "source_text", "description_brace", "description",
  "program_declaration", "package_declaration", "config_declaration",
  "interface_declaration", "bind_directive", "type_declaration",
  "data_type", "enum_name_declaration", "enum_name_declaration_list",
  "integer_vector_type", "integer_atom_type", "class_type",
  "struct_union_member_list", "enum_base_type_opt", "interface_identifier",
  "interface_opt", "packed_opt", "packed_dimension_brace",
  "unpacked_dimension_brace", "packed_dimension", "unpacked_dimension",
  "unsized_dimension", "struct_union", "type_identifier",
  "udp_declaration", "udp_identifier", "udp_port_list",
  "udp_port_declaration_brace", "udp_port_declaration",
  "udp_output_declaration", "udp_input_declaration", "udp_reg_declaration",
  "udp_declaration_port_list", "udp_input_declaration_brace",
  "port_identifier_brace", "udp_body", "udp_initial_statement_opt",
  "table_entry_brace", "table_entry", "input_list",
  "output_or_level_symbol", "next_state", "module_declaration",
  "module_identifier_opt", "module_nonansi_header", "module_ansi_header",
  "list_of_port_declarations", "list_of_ports_opt",
  "module_parameter_port_list_opt", "module_keyword", "module_identifier",
  "list_of_ports", "port_declaration_brace", "module_port_declaration",
  "module_port_input_declaration", "module_port_output_declaration",
  "module_port_inout_declaration", "port_brace", "port",
  "port_expression_opt", "port_reference", "bit_select", "part_select",
  "indexed_part_select", "port_identifier", "module_item_brace",
  "module_item", "non_port_module_item", "generated_instantiation",
  "generate_item_brace", "generate_item", "generate_item_or_null",
  "generate_conditional_statement", "constant_expression",
  "generate_case_statement", "genvar_case_item_brace", "genvar_case_item",
  "generate_loop_statement", "generate_block_identifier",
  "genvar_assignment", "generate_block", "port_declaration",
  "module_or_generate_item", "module_or_generate_item_declaration",
  "package_or_generate_item_declaration",
  "concurrent_assertion_item_declaration", "property_declaration",
  "genvar_declaration", "list_of_genvar_identifiers", "genvar_identifier",
  "parameter_declaration", "list_of_param_assign", "param_assign",
  "param_identifier", "data_type_or_implicit", "implicit_data_type",
  "input_declaration", "output_declaration", "inout_declaration",
  "port_type", "net_type_or_trireg_opt", "net_type_or_trireg",
  "signing_opt", "signing", "automatic_opt", "list_of_port_identifiers",
  "reg_declaration", "decl_register_identifier",
  "list_of_register_identifiers", "register_name", "register_identifier",
  "range_opt", "range", "integer_declaration", "realtime_declaration",
  "real_declaration", "list_of_real_identifiers", "net_declaration",
  "vectored_scalared_opt", "net_type", "list_of_net_names", "net_name",
  "net_identifier", "list_of_net_decl_assignments", "net_decl_assignment",
  "delay3_opt", "delay3", "delay_value", "function_declaration",
  "range_or_type_opt", "range_or_type", "function_item_declaration_brace",
  "function_item_declaration", "task_declaration",
  "task_item_declaration_brace", "task_item_declaration",
  "block_item_declaration", "attribute_instance_brace",
  "attribute_instance", "attr_spec_list", "attr_spec", "attr_name",
  "block_reg_declaration", "event_declaration",
  "list_of_event_identifiers", "gate_instantiation", "cmos_switchtype",
  "enable_gatetype", "mos_switchtype", "n_input_gatetype",
  "n_output_gatetype", "pass_en_switchtype", "pass_switchtype",
  "gate_instance_brace", "gate_instance", "name_of_gate_instance_opt",
  "name_of_gate_instance", "module_instantiation",
  "param_value_assign_opt", "list_of_parameter_assignments",
  "ordered_parameter_assignment_brace", "named_parameter_assignment_brace",
  "ordered_parameter_assignment", "named_parameter_assignment",
  "parameter_identifier", "module_instance_brace", "module_instance",
  "name_of_instance", "list_of_module_connections_opt",
  "list_of_module_connections", "ordered_port_connection_brace",
  "ordered_port_connection", "named_port_connection_brace",
  "named_port_connection", "continuous_assign", "list_of_net_assignments",
  "net_assignment", "variable_assignment", "initial_construct",
  "always_construct", "statement", "statement_item",
  "subroutine_call_statement", "subroutine_call", "tf_call",
  "system_tf_call", "statement_or_null", "event_trigger",
  "hierarchical_event_identifier", "par_block", "disable_statement",
  "assert_property_statement", "assume_property_statement",
  "property_identifier", "cover_property_statement", "action_block",
  "concurrent_assert_statement", "concurrent_assume_statement",
  "concurrent_cover_statement", "immediate_assert_statement",
  "hierarchical_task_or_block_identifier", "hierarchical_tf_identifier",
  "wait_statement", "procedural_continuous_assignments",
  "blocking_assignment", "operator_assignment", "assignment_operator",
  "nonblocking_assignment", "procedural_timing_control_statement",
  "procedural_timing_control", "cycle_delay", "delay_or_event_control",
  "delay_control", "event_control", "event_identifier",
  "ored_event_expression", "event_expression", "conditional_statement",
  "case_statement", "case_item_brace", "case_item", "loop_statement",
  "for_initialization", "for_step", "for_step_assignment", "seq_block",
  "block_identifier", "statement_or_null_brace", "task_identifier",
  "system_task_name", "net_lvalue", "variable_lvalue",
  "indexed_variable_lvalue", "hierarchical_variable_identifier",
  "variable_identifier", "const_expression", "mintypmax_expression",
  "expression_opt", "expression_brace", "expression", "property_expr",
  "sequence_expr", "cycle_delay_range", "unary_operator",
  "inc_or_dec_expression", "primary", "primary_literal", "number",
  "concatenation", "replication", "function_subroutine_call",
  "function_identifier", "unsigned_number", "hierarchical_identifier",
  "identifier", "pulldown_strength_opt", "pullup_strength_opt",
  "drive_strength_opt", "list_of_specparam_assignments",
  "specparam_declaration", "specparam_assignment", "specparam_identifier", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,    59,   123,   125,    44,    91,    93,    40,
      41,    46,    61,    35,    64,    36
};
# endif

#define YYPACT_NINF (-819)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-494)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     695,  -819,  2007,     9,   194,  -819,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,  2007,  2007,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,  2007,  2007,  -819,  -819,  -819,  -163,
     -87,  -819,    49,  -819,  3293,  -819,  -819,  -819,  -819,  -819,
      86,  -819,  -819,  -819,   143,  -819,   546,  -819,  -819,  -819,
      48,  -819,  -819,    80,    80,  -221,  2603,   -58,  3192,  2007,
    2007,    89,  2007,  -819,   116,   128,  2007,  2007,  2007,  2007,
    2007,  2007,  2007,  2007,  2007,  2007,  2007,  2007,  2007,  2007,
    2007,  2007,  2007,  2007,  2007,  2007,  2007,  2007,  2007,  2007,
    2007,    56,   -39,  -819,  -819,  -819,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,  -819,  -819,    61,  -819,    -3,    -3,
    -819,    88,    54,  -819,  -819,  -819,   162,  -819,   179,   190,
     210,   717,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,
    -819,  -819,    95,   -39,  2007,  -819,  -819,   106,  -819,   134,
    -819,  -819,  2007,   159,   165,  -819,  2007,    81,  3293,   110,
    -819,  -819,    31,  2543,  2252,  3349,  3349,   474,   474,   474,
    1228,  1228,  1228,  1228,  3101,  -819,  2727,   855,   855,   855,
     855,   537,   537,   537,   537,   585,   585,  3322,  3232,   106,
    -819,  -819,  -819,   230,  -819,  -819,  -819,  -819,  -819,    -3,
    -819,  -819,     0,   202,  -819,   248,  -819,  -819,  -819,   115,
    -819,  -819,  -819,   303,   499,   503,  -819,  -819,   304,  -819,
    -819,   308,    51,  -819,   297,  -819,  -819,  -819,  3293,  -819,
    -819,  3262,  -819,  -819,  2007,  2007,  2007,  -819,  2007,  -819,
    -819,   324,  -819,   248,   313,  -819,    54,  2007,   248,  1192,
    -819,  -819,  -819,   325,   308,  -819,  -819,   360,  -819,  2730,
     308,  -819,   364,  -819,  -819,  -819,   -39,  2007,  2007,   362,
    3293,   368,   372,  3293,  -819,  -819,   -43,  -819,  -819,  3293,
    -819,   633,  -819,  -819,  -819,  -819,  -819,  -819,   385,  -819,
    -819,  -819,  -819,   409,   659,  -819,   423,  -819,   657,   657,
      54,    -3,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  2971,
      -3,  -819,  -819,  -819,  -819,    54,    54,  -819,  -819,  -819,
    -819,  -819,   411,  -819,  -819,   -39,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,
    -147,   -45,   475,   433,   680,   418,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,  -819,  -819,  -819,   385,  -819,   385,
    -819,  -819,   385,   438,  -819,  -819,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,   685,  -819,  -819,   442,   426,  -819,
    -819,  3293,  3293,  -819,  -819,  -819,  -819,   324,   432,  2007,
    1445,  -819,   -16,  -174,  -819,  -819,    37,  -819,  -819,    -3,
     332,  -819,   125,  -819,  -819,   442,    -3,  -819,   442,   201,
     281,  -819,  -819,   442,   442,   282,   438,   438,  -819,   287,
     288,  2007,  -819,   444,  -819,   430,   134,   431,  -819,   693,
     434,   696,   439,   529,   445,   456,   -12,   438,   385,   438,
     385,   385,   438,  -819,   293,  -819,   411,  -819,   277,  -819,
     443,   451,   449,   458,    82,   247,   459,   463,  -819,  -819,
    -819,   461,   409,  -174,   718,   462,   464,   465,  -174,   -39,
     466,  -174,  -819,   721,   467,  -174,   468,   472,   476,   180,
    -159,   109,    73,  -819,  -819,  -819,  -819,  -819,  -819,  -819,
     469,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,   480,
     481,  -819,   484,  -819,  -819,  -819,  -819,  -819,  -819,  -819,
    -819,  -819,    63,   486,   498,  -819,  -819,   305,  -819,   478,
    -819,  -819,   409,   108,   746,   487,  -819,   488,   496,  -819,
    -819,  -819,  -819,  -819,  -819,  2896,  -819,   423,  -819,   500,
    -819,   500,  -819,  -819,    -3,   -74,   500,   500,  -819,   319,
     321,  -819,    54,  -819,   760,  -819,   323,  -819,   502,  -158,
     507,  1522,  2007,  1522,  2007,  2007,  -819,   885,  -819,   327,
    -819,   506,  -819,  -819,   546,   329,   438,   331,   438,   438,
     336,  -819,   456,   508,  -819,  -819,  -819,   517,  -819,   518,
     442,   442,   442,   211,  -819,   226,  -819,  -819,  -819,   504,
     369,  -819,  -819,   248,  -819,   520,  -819,  -819,  -819,   530,
     757,  2007,  2007,  2007,  -819,   523,  -819,  -174,  -819,  -819,
     530,   734,  2007,  -819,  2007,  2007,  2007,  2007,  -819,  -819,
    2007,  2007,  -819,   519,  -819,  1636,  -819,  -819,  -819,  -819,
    -819,  1323,  -819,  -819,  1371,  -819,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,  -819,  -819,  -819,    -5,  2007,  -819,
     229,  -819,  -174,  2007,  -819,  -819,  -819,  -819,  -819,  -819,
     -39,  -819,   538,   393,  2007,   423,  2007,  -819,   524,   442,
     248,  -819,  -819,   522,  -819,  -819,  -819,  -819,   444,  2007,
    -819,  1522,  1522,   -80,  1522,   526,  1522,  1522,  1522,  1522,
     528,  3035,   158,  -819,  1585,  2632,   412,  2661,  2123,   544,
     531,   533,   536,  -819,  -819,  3293,  -819,   456,  1403,   385,
    -819,   338,  -819,   349,   361,  -819,  -819,  1403,  -819,  -819,
     534,    93,  -819,   539,  -819,  -819,   540,   442,  -819,  -158,
    -819,  2007,  -819,  -819,   657,   657,  2971,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,  -819,  2169,  2230,  2290,  -819,  -819,
     548,   510,  -819,  -819,  2319,  2348,  2377,  2407,  2453,  2482,
     554,  -819,   555,  2007,  2007,   -28,  -819,  3293,  -819,   558,
    2007,  -819,  -819,  3293,  2007,  3293,   498,  -819,  -819,  3293,
     430,   134,  -819,  -819,  -819,   560,   565,   535,   561,  2007,
    -819,  -819,  2007,  -819,  -819,  -819,   123,   216,   498,  -819,
     123,  1585,   123,  -819,  -819,  -819,  1522,  1585,  1585,  1522,
    1522,  1522,  1522,  1522,  1522,  1522,  1522,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,   566,  -819,  2007,   532,  -819,   442,
     567,  -819,   572,  -819,   573,  -819,  -819,  3293,   586,  -819,
    -819,  -819,   571,   750,  -819,   584,   591,   592,   111,  -819,
     442,   829,   775,   442,   442,  -819,  -819,  -819,   442,   442,
     442,   442,   845,  1840,  1840,  1840,  2007,   821,  -819,  -819,
    -819,  -819,  -819,  -819,  -819,  -819,  3293,  3293,  1625,  1625,
    -819,  2007,  3293,  3293,   234,   613,   415,  1947,  2007,  2007,
     132,   869,  2574,   524,  -819,  -819,  -819,  1019,   843,   871,
     611,   441,  -819,  -819,   216,   141,   495,   495,  -819,  -819,
     123,   123,   856,  -819,  -819,  -819,  2007,  -819,  -819,   615,
    -819,  2007,   616,  -819,   365,  -819,   610,   366,  -819,  -819,
    -819,   853,  -819,  -819,  -819,   634,   500,  -819,  -819,  -819,
     619,  -819,  -819,  -819,  -819,  -819,   884,  1709,  -819,    24,
    1742,  1776,  2691,  -819,   867,  -819,  -819,  -819,  -819,  -819,
    -819,  2514,   498,  -819,   844,  -819,    34,  1928,  -819,    25,
     635,  -819,  -819,  -819,   870,  2007,  -819,  -819,   637,   639,
     640,   235,  -819,   257,   363,  -819,   -67,  -819,  -819,  -819,
     626,  2007,  -819,  -819,  -819,   586,  2007,   248,  -819,   586,
    -819,  -819,  -819,   872,  -819,   895,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,   -34,  -819,   631,   636,   645,   844,
    -819,  -819,   497,   132,  -819,  -819,  -819,   132,   423,   132,
     641,  -819,  -819,  -819,   642,   643,  -819,  -819,   644,  -819,
    -819,  3293,   610,  -819,  -819,  -819,  -819,  -819,  -819,  -819,
     646,  -819,   679,  -819,  -819,  -819,  -819,  -819,  -819,  1141,
     882,  -819,  -819,  -819,  -819,  -819,   647,  -819,  -819,  -819,
    -819,  -819,    18,  -819,  -819,  -819,   901,  -819,  -819,  -819,
    -819,   655,  -819
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     2,     0,     0,     0,     7,   562,   561,   563,   564,
     566,   567,   569,   568,     0,     0,   565,   280,   280,   582,
     593,   590,   535,   488,     0,     0,   588,   388,   389,     0,
     391,   280,   575,   494,     4,   280,   507,   505,   574,   583,
     578,   579,   580,   584,   496,   591,   204,     5,     1,     3,
     280,   510,   511,     0,     0,     0,   503,     0,   499,     0,
       0,     0,     0,   495,   576,   577,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    37,   206,   207,    35,    28,    39,
      41,    38,    36,    27,    56,    57,    43,   192,   204,   204,
      30,    45,     0,   193,    47,   205,     0,   280,     0,     0,
       0,     0,     8,    12,    13,    15,    11,    16,    10,     9,
     125,   125,     0,     0,     0,   281,   570,   490,   493,   496,
     571,   585,     0,     0,     0,   581,     0,     0,   503,     0,
     572,   573,     0,   498,   526,   528,   529,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   532,   533,   530,   531,   508,   509,   527,     0,   575,
     506,   578,   592,     0,    44,    42,    47,    24,    46,   204,
     218,   215,     0,   214,    47,   194,    19,    87,    88,     0,
      20,    18,    17,     0,   280,   280,    98,    97,     0,    21,
      14,     0,     0,   283,   286,   287,   491,   492,   504,   586,
     587,     0,   390,   392,     0,     0,     0,   120,     0,   576,
     577,     0,    29,    23,     0,   212,     0,     0,   217,     0,
      48,    52,    58,     0,    89,   126,   128,     0,   129,     0,
      89,    61,     0,    99,    96,   282,     0,     0,     0,     0,
     498,     0,     0,   534,    32,    33,     0,    40,   216,   213,
      55,     0,    22,    85,    90,   127,   280,   311,   249,   317,
     303,   304,   301,     0,   208,   133,     0,   280,   200,   200,
       0,   204,   312,   307,   313,   318,   305,   306,   314,   200,
     204,   308,   594,   595,   302,     0,     0,   309,   310,   319,
     320,   321,   219,   235,   239,     0,   322,   323,   324,   233,
     238,   234,   237,   241,   203,   236,   232,   240,   315,   316,
       0,     0,     0,     0,    99,   332,   130,   159,   170,   169,
     180,   176,   160,   157,   158,   156,   596,   171,   172,   174,
     173,   177,   202,   179,   178,   175,   162,   249,   596,   249,
     596,   596,   249,   328,   163,   161,   164,   165,   408,   410,
     412,   166,   167,   168,     0,   131,    86,   280,    94,   284,
     285,   144,   500,   121,   122,   123,    26,     0,     0,     0,
       0,   363,     0,     0,   250,   457,     0,   290,   209,   204,
     280,   185,     0,   183,   362,     0,   204,   201,     0,     0,
       0,   188,    47,     0,     0,     0,   328,   328,   225,     0,
       0,     0,   221,     0,   220,    94,   487,     0,   404,     0,
       0,     0,     0,     0,     0,   346,   229,   328,   249,   328,
     249,   249,   328,   330,     0,   325,   219,   329,     0,   124,
       0,     0,     0,     0,     0,   280,     0,     0,    95,    34,
      47,     0,     0,     0,   485,     0,     0,     0,     0,     0,
       0,     0,   280,   485,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   288,   370,   368,   367,   369,   364,   377,
       0,   379,   381,   378,   365,   366,   374,   386,   385,     0,
       0,   423,     0,   382,   280,   443,   441,   442,   375,   373,
     380,   384,   280,     0,     0,   251,   255,     0,   358,     0,
     489,   289,     0,   257,   133,     0,   132,     0,     0,   134,
     135,   136,   137,   138,   139,     0,   182,     0,    49,   198,
      47,   195,   222,   187,   204,     0,   197,   196,   186,     0,
       0,   224,     0,   223,     0,   601,     0,   597,     0,   115,
       0,     0,     0,     0,     0,     0,   181,     0,   347,     0,
     343,     0,   231,   230,   204,     0,   328,     0,   328,   328,
       0,   298,   346,     0,   409,   411,   413,     0,   280,     0,
       0,     0,     0,     0,   101,     0,   111,   113,   116,   117,
       0,    92,    91,    25,    51,     0,   396,   361,   418,     0,
     280,     0,     0,     0,   419,     0,   415,     0,   420,   474,
       0,   280,     0,   421,     0,     0,     0,     0,   444,   445,
       0,     0,   450,     0,   454,     0,   452,   387,   383,   371,
     372,     0,   393,   440,     0,   426,   427,   428,   429,   430,
     431,   433,   432,   434,   435,   436,   437,   425,     0,   376,
       0,   357,     0,     0,   291,   260,   261,   262,   263,   259,
       0,   258,     0,   280,     0,     0,     0,   184,   210,     0,
     199,   189,   191,     0,   299,   300,   226,   599,     0,     0,
     269,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   553,     0,   536,     0,     0,     0,     0,     0,     0,
       0,   334,   335,   336,   338,   340,   331,   346,   501,   249,
     292,     0,   294,     0,     0,   297,   326,   501,   280,    72,
     280,     0,    77,    62,    74,    68,     0,   280,    93,   115,
     100,     0,   118,   119,   200,   200,   200,   105,   106,   104,
     395,   484,   485,   482,   486,     0,     0,     0,   399,   478,
       0,     0,   485,   397,     0,     0,     0,     0,     0,     0,
       0,   456,     0,     0,     0,     0,   458,   461,   394,     0,
       0,   447,   448,   438,     0,   424,     0,   252,   359,   360,
      94,   589,   152,   133,   154,     0,     0,     0,     0,     0,
      50,    49,     0,   598,   600,   280,   543,   537,     0,   558,
     544,     0,   545,   546,   547,   548,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   280,   554,   401,
     280,   403,   280,   342,     0,   333,     0,     0,   344,     0,
       0,   348,   349,   351,   350,   354,   353,   502,     0,   293,
     295,   296,     0,   280,    63,     0,     0,     0,     0,    73,
       0,     0,     0,     0,   115,   102,   103,   112,     0,     0,
       0,     0,   280,     0,     0,     0,     0,   280,   280,   280,
     280,   280,   446,   280,   451,   455,   463,   462,     0,     0,
     453,     0,   439,   422,     0,     0,   280,     0,     0,     0,
     280,     0,   498,   211,   190,   270,   271,     0,     0,     0,
       0,     0,   557,   555,   539,   538,   540,   541,   549,   550,
     551,   552,   406,   400,   402,   405,   501,   337,   339,     0,
     345,   501,     0,   245,     0,   242,    47,     0,   246,   327,
      64,     0,    65,    66,    67,     0,    69,    60,    82,    75,
       0,   110,   107,   109,   108,   483,   280,     0,   469,     0,
       0,     0,     0,   398,   464,   475,   417,   476,   414,   459,
     460,     0,     0,   253,   280,   155,   280,     0,   146,     0,
       0,   153,   141,   140,   142,     0,    54,   278,     0,     0,
       0,   277,   279,   275,   276,   268,     0,   556,   542,   280,
       0,   501,   352,   355,   227,     0,     0,   244,   228,     0,
      59,   497,    70,    82,    78,     0,   114,   280,   473,   466,
     470,   280,   467,   468,     0,   280,     0,     0,     0,   280,
     264,   266,     0,   280,   150,   145,   147,   280,     0,   280,
       0,   272,   273,   274,     0,     0,   407,   341,     0,   243,
      47,   248,     0,   247,    76,    79,    83,   472,   471,   480,
       0,   479,   280,   481,   465,   449,   254,   267,   265,     0,
       0,   277,   275,   276,   149,   148,     0,   143,    53,   560,
     559,   356,     0,   280,   425,   256,     0,    84,    80,   477,
     151,     0,    81
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,
    -819,  -819,  -110,   563,  -819,  -819,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,   -78,   150,   435,  -819,  -819,  -819,  -819,
    -819,  -819,  -819,  -819,   103,   583,  -519,  -819,  -819,  -819,
    -819,   112,  -819,  -819,   -52,  -819,  -819,  -819,  -819,   713,
     847,   849,  -819,  -388,  -819,  -819,  -173,  -819,  -819,   232,
    -819,  -819,  -819,  -819,   233,   107,  -819,   375,    -6,   -65,
    -311,   854,  -819,  -819,  -819,  -468,  -376,  -727,  -819,  -567,
    -819,  -819,    -2,  -819,  -819,   -50,  -102,  -819,   346,  -819,
    -819,  -819,  -819,  -819,  -819,  -215,  -190,   686,   446,  -819,
     413,  -819,  -242,    84,    90,  -257,  -819,  -260,   -11,  -819,
    -819,  -367,    14,  -193,   703,  -819,  -819,   549,  -819,  -384,
    -169,  -819,   690,  -162,  -819,  -819,  -819,    -7,  -470,  -819,
     -10,  -308,  -819,  -462,  -819,  -819,  -819,  -819,   -29,  -819,
    -819,  -819,   197,   -17,  -819,  -819,   747,  -819,  -818,  -380,
    -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,    59,
    -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,   168,   169,
    -819,  -819,  -515,  -819,   280,  -819,  -819,    77,  -819,    83,
    -819,  -819,  -333,   542,  -819,  -819,  -253,  -819,  -819,  -374,
    -819,  -819,  -479,  -819,  -819,  -819,  -819,  -172,  -166,   136,
    -164,  -568,  -819,  -819,  -819,  -819,  -819,  -819,  -819,  -819,
     392,   -13,  -819,  -819,  -819,  -819,  -819,   357,  -366,  -386,
    -285,  -819,  -348,  -819,  -819,  -305,  -455,  -819,  -819,  -819,
    -819,  -819,  -320,  -408,   550,  -819,  -819,   -32,   -41,  -819,
    -819,   -54,  -503,  -797,   -15,    79,  -307,  -509,   316,  -819,
    -375,   930,  -819,  -452,   -51,   967,  -819,  -819,  -339,   -23,
     -72,  -819,  -819,   120,  -819,  -819,   339,  -819
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    49,    50,   122,   123,   124,   125,   126,
     210,   127,   107,   265,   266,   108,   109,   110,   388,   183,
     232,   185,   189,  1007,   678,   240,   800,   241,   111,   243,
     128,   252,   450,   853,   854,   855,   856,   857,   452,   730,
     733,   861,   862,  1013,  1014,  1015,  1082,  1091,   129,   273,
     130,   131,   456,   457,   378,   211,   274,   458,   593,   594,
     747,   748,   749,   595,   596,   597,   598,    63,   422,    65,
     538,   204,   245,   246,   336,   400,   983,   984,   530,   380,
     531,   977,   978,   532,   793,   796,   533,   247,   534,   337,
     338,   339,   340,   341,   402,   797,   987,   410,   411,   683,
     112,   113,  1028,   344,   345,   405,   406,   346,   412,   115,
     399,   539,   483,   191,   192,   193,   194,   423,   424,   348,
     992,   350,   419,   485,   574,   352,   934,   935,   936,   937,
     938,   393,   394,   515,   353,   670,   671,  1029,  1030,   354,
     805,   905,  1031,   641,   135,   212,   213,   214,   486,   355,
     396,   356,   357,   358,   359,   360,   361,   362,   363,   444,
     445,   446,   447,   364,   435,   710,   711,   712,   713,   714,
     834,   569,   570,   571,   840,   841,   842,   843,   844,   845,
     365,   517,   607,   608,   366,   367,   642,   488,   489,    26,
      27,    28,   754,   491,   605,   492,   493,   494,   495,   429,
     496,   923,   371,   372,   373,   497,   615,    29,   498,   499,
     500,   501,   658,   502,   503,   504,   505,   780,   506,   700,
     397,   775,   776,   508,   509,   957,   958,   510,   760,  1060,
    1061,   511,   374,   610,   425,    30,   519,    31,    32,    33,
    1012,   554,    57,   846,   959,   701,   702,   703,   704,    35,
      36,    37,    38,    39,    40,    41,    42,   790,    43,    44,
      45,   416,   417,   436,   556,   375,   557,   558
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,    54,   138,   138,   507,   143,   484,   343,   152,    55,
     487,   203,   137,   137,    61,   513,   490,    47,    91,   632,
     182,   136,   140,   391,   529,   643,    64,   628,   407,   407,
     139,   139,   408,   132,   404,   114,   195,   560,   254,   407,
     181,   541,   414,   268,   147,   149,   546,   547,    -6,   437,
     179,   439,   660,   516,   442,  -490,   673,  1087,   255,   342,
     518,   215,   133,  1021,  1037,   621,   453,   726,   888,   729,
     224,   403,   217,  1033,   141,   142,   335,   368,   524,   633,
     349,    34,   525,   369,   427,   370,   133,   351,   133,   993,
     634,   644,  -493,    51,    52,   133,   427,   186,   187,   133,
     199,   133,   527,    56,    58,   572,   779,   795,   233,   798,
      20,   528,   418,   418,   230,    95,   238,   133,    46,    55,
     134,   133,  -491,    17,    18,   428,   449,   573,   770,  1000,
     576,   216,   578,   579,  -492,    96,    59,   428,   148,   148,
     630,   153,   516,   592,   599,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     259,   261,   262,   229,   860,   516,   524,   606,   234,   591,
     525,   206,   819,   207,   215,   271,   804,   249,   249,   413,
     665,   225,   860,   226,    48,   828,   208,   636,   430,   819,
     527,   206,   838,   207,  1048,    21,  -490,  -490,   591,   528,
     682,   859,    60,   148,  1072,   666,   667,   808,    21,   619,
     945,   218,   645,   239,   646,   221,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   668,   664,  1044,   428,
     116,   809,   145,  -493,  -493,    20,   150,   151,   599,  1034,
      20,   993,   386,   387,   820,   507,   706,   484,   782,   390,
     134,   487,   924,   347,   925,   117,   513,   490,   889,    21,
     390,   782,   890,  -491,  -491,   118,   584,   209,   781,   734,
     735,   736,   585,   514,   586,  -492,  -492,   119,   184,   752,
     120,   781,   426,   235,    19,  -370,   236,   529,   481,   482,
     762,  -370,   910,   260,   260,   260,  1074,   263,   912,   913,
    1075,  1088,  1077,   821,   822,   968,   269,  -367,   260,   121,
     142,   142,   677,  -367,   894,   896,   908,   982,   188,   788,
     521,   980,   981,   522,   545,   461,   381,   382,   190,   138,
      20,    21,   138,    23,   872,   342,    62,   256,   922,   137,
      24,   922,   137,   922,   877,    25,   909,   395,   512,   686,
     454,   520,   335,   368,    20,   657,   349,   196,   801,   369,
     139,   370,   635,   351,   134,   133,   524,   142,   823,   824,
     525,   222,   603,   535,   806,   807,   200,   810,   523,   812,
     813,   814,   815,   526,    21,   540,   823,   824,   201,   964,
     527,   966,   895,    62,   922,   239,   142,   629,   631,   528,
     223,   848,   138,   823,   824,   825,   826,   138,   536,   202,
     138,   537,   137,  -369,   138,   982,   866,   137,   599,  -369,
     137,   520,   825,   826,   137,    92,   614,   524,   600,   520,
     139,   525,  -416,   623,    92,   139,   426,   516,   139,   744,
     745,   794,   139,   819,   219,   390,   330,   331,   827,   524,
     220,   527,   680,   525,    20,    21,   746,   431,   260,   433,
     528,   823,   824,   975,   332,   549,   550,  1018,   438,   627,
     440,   441,   819,   527,   407,   407,   407,   868,   869,   871,
     825,   826,   528,   946,   542,    61,   575,   236,   577,    77,
     260,   580,  1020,   133,   237,  1020,  1020,   737,   820,   911,
    1027,   738,   914,   915,   916,   917,   918,   919,   920,   921,
     529,   507,   739,   991,   231,   786,   740,   994,   929,   787,
     972,   449,   513,   490,   973,  1050,   819,   820,  1057,  1052,
     969,   970,  1058,  -115,  1045,   239,  1064,  -115,   592,   347,
     248,   248,   949,   599,    69,    70,    71,   951,   952,   953,
     954,   244,    77,   114,   283,   250,   138,   821,   822,   960,
     961,   731,    87,    88,   543,   548,   137,   544,   544,   290,
     551,   553,   291,   552,   552,   761,   581,   242,   251,   582,
     138,   820,   253,   743,   139,   300,   821,   822,   661,   257,
     137,   662,    69,    70,    71,   306,    46,   267,   264,   512,
      77,   138,   684,    93,   685,   582,   687,   582,   272,   688,
     716,   137,   720,   717,   722,   582,   965,   582,   967,   725,
     520,   849,   582,   516,   582,   721,   870,   723,   724,   139,
    1065,   705,   850,   707,   708,   582,   715,   791,  1071,  1063,
     821,   822,  1073,   275,   851,    94,   535,   582,  1004,  1008,
     383,  1005,  1009,   377,    95,   988,   384,   823,   824,   645,
     385,   646,   389,   647,   648,   649,   650,   651,   652,   653,
     654,   655,   656,   507,    96,   991,   825,   826,   392,   994,
     755,   756,   757,   395,   513,   490,   823,   824,     1,     2,
       3,   764,   398,   765,   766,   767,   768,   401,   421,   769,
      58,   858,   830,   731,   777,   825,   826,   428,   432,  -484,
     600,   434,   443,   783,   448,   455,   449,   460,   555,   559,
     561,    97,   562,   563,    98,   564,    99,   785,   565,   566,
     568,   998,   789,   587,   567,   901,  1046,   588,   904,   589,
     823,   824,   601,   381,   590,   381,   602,   609,   100,   604,
     620,   611,   637,   612,   613,   617,   622,   624,    58,   825,
     826,   625,   101,   638,   639,   626,  1070,   640,   102,   659,
     663,   313,   314,    21,    93,   672,   674,   675,   907,   319,
     320,   321,   322,   323,   324,   676,   679,   847,   325,   224,
     690,   741,   326,   327,   689,   718,   847,   727,   103,   104,
     728,   732,   657,   750,   751,   753,   758,   763,   105,   771,
     153,   799,   792,   106,   802,   811,    94,   816,   833,   836,
    1089,   835,   837,   709,   -71,   863,   858,   899,   645,   864,
     646,   876,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   886,   887,   884,   885,   138,   891,   898,   892,
     897,   900,   390,   893,   390,   926,   137,   930,   931,   932,
     933,   939,    69,    70,    71,   512,   -77,   942,   902,   535,
      77,   260,   979,   535,   943,   944,    83,    84,    85,    86,
      87,    88,   947,     6,     7,     8,     9,    10,    11,    12,
      13,   948,    97,   955,   963,    98,   974,    99,   985,   995,
     996,   997,  1006,   999,  1001,   715,  1010,   839,  1011,  1016,
      14,    15,    16,  1017,  1025,   289,  1047,  1039,  1038,   100,
    1041,  1040,  1042,  1043,  1056,   482,  1066,  1054,  1067,  1078,
    1079,  1080,  1085,   101,  1081,   524,  1083,  1086,  1092,   102,
     459,   903,   148,   148,   148,   962,   940,  1032,   669,   535,
     451,  1055,   979,   376,   197,   941,   198,   777,   777,   865,
     971,   950,   867,   138,   742,  1036,   148,   381,   381,   103,
     104,  1084,   390,   137,  1090,   205,   415,   719,  1076,   105,
     681,   989,  1062,   409,   106,   583,   420,   990,  1049,  1053,
    1068,   139,   906,   379,   927,   847,   928,   852,  1002,   759,
     847,  1059,  1069,   618,   784,  1003,   535,   818,   138,   616,
     535,   180,   535,   144,     0,   133,     0,   803,   137,     0,
       0,     0,     0,     0,     0,   462,   148,   512,     0,   148,
     148,     0,    17,    18,     0,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   148,     0,     0,     0,
       0,   463,     0,   464,   260,     0,   390,   465,   466,   467,
       0,   468,     0,     0,   469,     0,     0,     0,     0,     0,
     847,     0,     0,     0,     0,  1051,   283,   470,   471,   472,
     473,     0,     0,     0,     0,     0,   474,     0,     0,   288,
     289,   290,     0,     0,   291,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   299,   300,     0,     0,
       0,     0,     0,    19,     0,     0,     0,   306,    46,   475,
     476,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   313,   314,     0,     0,   133,     0,     0,
       0,   319,   320,   321,   322,   323,   324,   462,     0,   477,
     325,     0,     0,   478,   326,   327,     0,     0,     0,    20,
      21,    22,    23,     0,     0,     0,    17,    18,     0,    24,
       0,     0,     0,   463,    25,   464,   709,     0,     0,   465,
     466,   467,   479,   468,     0,     0,   469,     0,   480,   331,
       6,     7,     8,     9,    10,    11,    12,    13,   283,   470,
     471,   472,   473,     0,     0,     0,   332,     0,   474,     0,
       0,     0,     0,   290,     0,     0,   291,    14,    15,    16,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   300,
       0,     0,     0,     0,     0,    69,    70,    71,     0,   306,
      46,   475,   476,    77,     0,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,   313,   314,     0,     0,     0,
       0,     0,     0,   319,   320,   321,   322,   323,   324,     0,
       0,   477,   325,     0,     0,   478,   326,   327,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    18,
       0,     0,     0,    20,     0,     0,    23,     0,     0,     0,
       0,     0,   778,   134,   479,     0,     0,     0,     0,     0,
     480,   331,   481,   482,     0,     0,     0,     0,     0,   133,
       0,     0,     0,     0,     0,     0,     0,     0,   332,   462,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   463,     0,   464,     0,     0,
       0,   465,   466,   467,     0,   468,     0,     0,   469,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
     283,   470,   471,   472,   473,     0,     0,     0,     0,     0,
     474,     0,     0,     0,     0,   290,    14,    15,    16,     0,
       0,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,     0,     0,    20,     0,     0,    23,     0,
      19,     0,    46,   475,   476,   134,     0,     0,    14,    15,
      16,     0,     0,     0,   481,   482,     0,   313,   314,     0,
       0,   133,     0,     0,     0,   319,   320,   321,   322,   323,
     324,   462,     0,   477,   325,     0,     0,   478,   326,   327,
       0,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      17,    18,   779,     0,     0,     0,    24,   463,     0,   464,
     270,    25,     0,   465,   466,   467,   479,   468,     0,     0,
     469,     0,   480,   331,     0,     0,     0,     0,     0,     0,
       0,     0,   283,   470,   471,   472,   473,     0,     0,     0,
     332,     0,   474,     0,     0,     0,     0,   290,    17,    18,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,   475,   476,    14,    15,    16,
      17,    18,   691,     0,     0,     0,     0,     0,     0,   313,
     314,     0,     0,     0,     0,     0,     0,   319,   320,   321,
     322,   323,   324,     0,     0,   477,   325,     0,     0,   478,
     326,   327,     0,     6,     7,     8,     9,    10,    11,    12,
      13,     0,    17,    18,     0,     0,     0,    20,     0,    19,
      23,     0,     0,     0,     0,   692,   778,   134,   479,     0,
      14,    15,    16,     0,   480,   331,   481,   482,     0,     0,
       0,     0,     0,     6,     7,     8,     9,    10,    11,    12,
      13,    19,   332,     0,     6,     7,     8,     9,    10,    11,
      12,    13,     0,   772,     0,    20,    21,    22,    23,     0,
      14,    15,    16,     0,     0,    24,     0,     0,     0,     0,
      25,    14,    15,    16,   481,   482,     0,     0,     0,    17,
      18,     0,     0,     0,     0,     0,     0,    20,    21,    22,
      23,     0,     0,     0,     0,   693,     0,    24,     0,     0,
       0,     0,    25,     0,   839,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   773,     0,     6,     7,     8,
       9,    10,    11,    12,    13,   774,   773,     0,     0,    20,
       0,     0,    23,     0,     0,   694,   774,     0,     0,   134,
       0,   695,    17,    18,    14,    15,    16,     0,   481,   482,
       6,     7,     8,     9,    10,    11,    12,    13,   693,   696,
      19,     0,   956,     0,     0,     0,     0,     0,  1019,     0,
       0,     0,     0,     0,   697,   698,   699,    14,    15,    16,
       0,     0,    17,    18,     6,     7,     8,     9,    10,    11,
      12,    13,     0,    17,    18,   956,     0,     0,     0,     0,
       0,  1022,     0,     0,   695,     0,    20,    21,    22,    23,
       0,    14,    15,    16,     0,     0,    24,     0,     0,     0,
       0,    25,     0,    19,     0,     0,   482,     0,     0,   956,
       0,     0,     0,     0,     0,  1023,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,    17,    18,     0,    20,
      21,    22,    23,     0,    19,    14,    15,    16,     0,    24,
       0,     0,     0,     0,    25,     0,     0,     0,     0,     0,
       0,     0,     0,   956,     0,     0,     0,     0,     0,    17,
      18,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,     0,     0,     0,     0,     0,     0,    24,
      20,    21,    22,    23,    25,     0,     0,     0,     0,     0,
      24,     0,     0,    17,    18,    25,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,   976,    14,    15,    16,     0,     0,  1035,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    17,    18,     0,
     976,     0,     0,    24,     0,     0,     0,     0,    25,     0,
       0,     0,     0,     0,    19,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,    20,    21,    22,    23,
       0,     0,     0,     0,     0,     0,    24,     0,     0,     0,
       0,    25,    14,    15,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,    21,    22,    23,     0,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,    25,     0,     0,    19,     0,
       0,     0,     0,     0,     0,    17,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    21,    22,    23,     0,     0,
       0,     0,     0,    66,    24,     0,    67,    68,     0,    25,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,     0,     0,    17,    18,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    66,
       0,     0,    67,    68,     0,    19,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,     0,     0,
       0,     0,    20,    21,    22,    23,     0,     0,     0,     0,
       0,     0,    24,     0,     0,     0,     0,    25,     0,     0,
       0,    20,    21,    22,    23,     0,     0,     0,     0,     0,
      66,    24,     0,    67,    68,    19,    25,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    69,
      70,    71,    72,    73,    74,    75,     0,    77,     0,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,     0,
       0,    20,    21,    22,    23,     0,     0,     0,     0,     0,
      66,    24,     0,    67,    68,     0,    25,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    66,
       0,     0,    67,    68,     0,     0,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    66,     0,
       0,    67,    68,     0,     0,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    66,     0,     0,
      67,    68,     0,     0,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,     0,    66,     0,     0,
      67,    68,     0,   832,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    66,     0,     0,    67,    68,     0,   873,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    66,     0,     0,    67,    68,     0,     0,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,     0,     0,    66,     0,     0,    67,    68,     0,
     874,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    66,     0,     0,    67,    68,     0,     0,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,     0,     0,    66,     0,     0,    67,    68,     0,
     875,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    66,     0,     0,    67,    68,     0,   878,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    66,     0,     0,    67,    68,     0,   879,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    66,     0,     0,    67,    68,     0,   880,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       0,    66,     0,     0,    67,    68,     0,   881,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       0,     0,     0,     0,     0,     0,   133,    66,     0,     0,
      67,    68,     0,     0,    69,    70,    71,    72,    73,    74,
      75,    76,    77,   882,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     0,     0,     0,     0,     0,
     276,   277,   278,     0,     0,   279,   280,   281,     0,     0,
       0,   282,   883,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   283,     0,     0,
       0,     0,   284,   285,   286,     0,     0,     0,     0,   287,
     288,   289,   290,     0,  1026,   291,     0,     0,     0,   292,
       0,   293,   294,   295,   296,   297,   298,   299,   300,   301,
       0,     0,     0,     0,   302,   303,   304,   305,   306,    46,
       0,   227,   307,   308,   309,   310,   311,     0,     0,     0,
       0,   312,     0,     0,   313,   314,     0,   315,     0,   316,
     317,   318,   319,   320,   321,   322,   323,   324,     0,     0,
       0,   325,   986,     0,     0,   326,   327,   328,   329,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,     0,   133,     0,     0,     0,     0,     0,     0,   330,
     331,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   829,     0,   332,     0,     0,
       0,     0,     0,     0,     0,     0,   276,   277,   278,     0,
       0,   279,   280,   281,     0,     0,     0,   282,     0,     0,
       0,     0,     0,     0,   831,     0,     0,     0,     0,     0,
       0,     0,     0,   283,     0,     0,     0,     0,   284,     0,
     286,     0,     0,   333,     0,   287,     0,     0,   290,     0,
       0,   291,     0,     0,  1024,   292,     0,   293,   294,   295,
     296,   297,   298,     0,   300,   301,     0,     0,     0,     0,
     302,   303,   304,   305,   306,    46,     0,     0,   307,   308,
     309,   310,   311,     0,   334,     0,     0,     0,     0,     0,
     313,   314,     0,   315,     0,   316,   317,   318,   319,   320,
     321,   322,   323,   324,     0,     0,     0,   325,    93,     0,
       0,   326,   327,   328,   329,    66,     0,     0,    67,    68,
       0,     0,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     0,   330,   331,     0,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   332,     0,   313,   314,     0,     0,     0,
       0,     0,     0,   319,   320,   321,   322,   323,   324,     0,
       0,    66,   325,     0,    67,    68,   326,   327,    69,    70,
      71,    72,    73,    74,    75,     0,    77,     0,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,   333,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,     0,     0,    98,
       0,    99,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     334,     0,     0,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
       0,     0,    66,   102,     0,    67,    68,     0,   693,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   146,     0,   103,   104,     0,     0,     0,     0,     0,
       0,     0,    66,   105,     0,    67,    68,     0,   106,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   228,    66,     0,     0,    67,    68,     0,     0,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   258,   817,    66,     0,     0,    67,    68,     0,     0,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    66,     0,     0,    67,    68,     0,     0,    69,
      70,    71,    72,    73,    74,    75,     0,    77,     0,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    66,
       0,     0,     0,     0,     0,     0,    69,    70,    71,    72,
      73,    74,    75,     0,    77,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88
};

static const yytype_int16 yycheck[] =
{
      17,    18,    53,    54,   390,    56,   390,   249,    62,    24,
     390,   121,    53,    54,    31,   390,   390,     3,    35,   481,
      92,    53,    54,   276,   400,   504,    32,   479,   288,   289,
      53,    54,   289,    50,   287,    46,   114,   425,   211,   299,
      91,   408,   299,   236,    59,    60,   413,   414,     0,   357,
      91,   359,   514,   392,   362,     6,   524,    39,     7,   249,
     393,   133,     6,    39,    39,   473,   377,   582,    96,   588,
      39,   286,   137,    39,   295,   296,   249,   249,    44,     6,
     249,     2,    48,   249,   243,   249,     6,   249,     6,   907,
      17,    28,     6,    14,    15,     6,   243,   108,   109,     6,
     117,     6,    68,    24,    25,   117,   111,   674,   186,   676,
     284,    77,   305,   306,   179,   118,   194,     6,   109,   134,
     294,     6,     6,   157,   158,   284,   284,   139,   631,   926,
     438,   137,   440,   441,     6,   138,   299,   284,    59,    60,
     299,    62,   481,   301,   455,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
     224,   225,   226,   179,    81,   514,    44,   462,   189,    97,
      48,    86,    41,    88,   256,   239,   689,   204,   205,   299,
      82,   160,    81,   162,     0,   704,   101,   482,   243,    41,
      68,    86,   717,    88,  1001,   285,   157,   158,    97,    77,
     284,   730,   299,   134,  1032,   107,   108,   297,   285,   472,
     109,   142,   159,   297,   161,   146,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   128,   522,   305,   284,
     192,   693,   300,   157,   158,   284,   157,   158,   559,   976,
     284,  1069,   295,   296,    96,   641,   563,   641,   644,   276,
     294,   641,   830,   249,   832,   217,   641,   641,   296,   285,
     287,   657,   300,   157,   158,   227,   448,   182,   644,   590,
     591,   592,   448,   299,   448,   157,   158,   239,   227,   609,
     242,   657,   315,   293,   238,    60,   296,   673,   303,   304,
     620,    66,   811,   224,   225,   226,  1033,   228,   817,   818,
    1037,   293,  1039,   155,   156,   883,   237,    60,   239,   271,
     296,   296,   537,    66,   786,   793,   805,   293,   240,   662,
     293,   898,   899,   296,   412,   389,   257,   258,   284,   390,
     284,   285,   393,   287,   752,   535,   297,   296,   827,   390,
     294,   830,   393,   832,   762,   299,   808,   284,   390,   552,
     377,   393,   535,   535,   284,   302,   535,   205,   679,   535,
     393,   535,   299,   535,   294,     6,    44,   296,   255,   256,
      48,   300,   460,   400,   691,   692,   207,   694,   399,   696,
     697,   698,   699,    61,   285,   406,   255,   256,   208,   878,
      68,   880,   790,   297,   883,   297,   296,   479,   299,    77,
     300,   719,   463,   255,   256,   274,   275,   468,   293,   209,
     471,   296,   463,    60,   475,   293,   737,   468,   739,    66,
     471,   463,   274,   275,   475,   301,   468,    44,   455,   471,
     463,    48,   299,   475,   301,   468,   469,   786,   471,    80,
      81,    58,   475,    41,   295,   472,   179,   180,   300,    44,
     295,    68,   540,    48,   284,   285,    97,   331,   389,   333,
      77,   255,   256,    58,   197,   416,   417,   956,   358,   299,
     360,   361,    41,    68,   744,   745,   746,   744,   745,   746,
     274,   275,    77,   860,   293,   512,   437,   296,   439,    25,
     421,   442,   957,     6,   302,   960,   961,   296,    96,   816,
     972,   300,   819,   820,   821,   822,   823,   824,   825,   826,
     896,   907,   296,   907,   294,   296,   300,   907,   839,   300,
     296,   284,   907,   907,   300,  1005,    41,    96,  1017,  1009,
     888,   889,  1021,   296,   996,   297,  1025,   300,   301,   535,
     204,   205,   863,   864,    17,    18,    19,   868,   869,   870,
     871,    62,    25,   574,    67,    62,   617,   155,   156,   874,
     875,   588,    35,    36,   293,   293,   617,   296,   296,    82,
     293,   293,    85,   296,   296,   617,   293,   284,   284,   296,
     641,    96,   284,   599,   617,    98,   155,   156,   293,   302,
     641,   296,    17,    18,    19,   108,   109,   294,   284,   641,
      25,   662,   293,    67,   293,   296,   293,   296,   293,   296,
     293,   662,   293,   296,   293,   296,   879,   296,   881,   293,
     662,   293,   296,   972,   296,   576,   746,   578,   579,   662,
    1026,   562,   293,   564,   565,   296,   567,   670,  1032,  1024,
     155,   156,  1032,   293,   293,   109,   673,   296,   293,   293,
     298,   296,   296,   299,   118,   907,   298,   255,   256,   159,
     298,   161,    39,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,  1069,   138,  1069,   274,   275,   303,  1069,
     611,   612,   613,   284,  1069,  1069,   255,   256,     3,     4,
       5,   622,    43,   624,   625,   626,   627,   284,   297,   630,
     631,   728,   300,   730,   635,   274,   275,   284,   243,    39,
     737,   303,   284,   644,    39,   299,   284,   295,   284,   299,
     299,   185,    39,   299,   188,    39,   190,   658,   299,   210,
     284,   300,   663,   300,   299,   799,   999,   296,   802,   300,
     255,   256,   293,   674,   296,   676,   293,    39,   212,   298,
      39,   299,   293,   299,   299,   299,   299,   299,   689,   274,
     275,   299,   226,   293,   293,   299,  1029,   293,   232,   293,
     302,   124,   125,   285,    67,    39,   299,   299,   805,   132,
     133,   134,   135,   136,   137,   299,   296,   718,   141,    39,
     293,   297,   145,   146,   302,   299,   727,   299,   262,   263,
     293,   293,   302,   293,   284,    58,   293,    83,   272,   300,
     741,   297,   284,   277,   302,   299,   109,   299,   284,   296,
    1083,   300,   296,   301,   300,   296,   853,   302,   159,   299,
     161,   293,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   773,   774,   300,   300,   907,   299,   293,   780,
     300,   300,   879,   784,   881,   299,   907,   300,   296,   296,
     284,   300,    17,    18,    19,   907,   126,   293,   799,   896,
      25,   802,   897,   900,   293,   293,    31,    32,    33,    34,
      35,    36,    63,     8,     9,    10,    11,    12,    13,    14,
      15,   126,   185,    58,    83,   188,   293,   190,    39,    66,
      39,   300,   302,    57,   299,   836,    63,   301,   284,   300,
      35,    36,    37,    39,    57,    81,   300,    57,   293,   212,
     293,   985,   293,   293,    39,   304,   300,    65,   293,   298,
     298,   298,    60,   226,   300,    44,   300,   300,   293,   232,
     387,   801,   873,   874,   875,   876,   853,   974,   523,   976,
     377,  1013,   977,   250,   117,   853,   117,   888,   889,   737,
     891,   864,   739,  1024,   599,   977,   897,   898,   899,   262,
     263,   302,   999,  1024,  1086,   131,   300,   574,  1038,   272,
     544,   907,  1024,   290,   277,   446,   306,   907,  1005,  1009,
    1029,  1024,   805,   256,   836,   926,   837,   727,   931,   617,
     931,  1024,  1029,   471,   657,   932,  1033,   701,  1069,   469,
    1037,    91,  1039,    56,    -1,     6,    -1,   688,  1069,    -1,
      -1,    -1,    -1,    -1,    -1,    16,   957,  1069,    -1,   960,
     961,    -1,   157,   158,    -1,  1062,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   977,    -1,    -1,    -1,
      -1,    42,    -1,    44,   985,    -1,  1083,    48,    49,    50,
      -1,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
    1001,    -1,    -1,    -1,    -1,  1006,    67,    68,    69,    70,
      71,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    80,
      81,    82,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    97,    98,    -1,    -1,
      -1,    -1,    -1,   238,    -1,    -1,    -1,   108,   109,   110,
     111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,   125,    -1,    -1,     6,    -1,    -1,
      -1,   132,   133,   134,   135,   136,   137,    16,    -1,   140,
     141,    -1,    -1,   144,   145,   146,    -1,    -1,    -1,   284,
     285,   286,   287,    -1,    -1,    -1,   157,   158,    -1,   294,
      -1,    -1,    -1,    42,   299,    44,   301,    -1,    -1,    48,
      49,    50,   173,    52,    -1,    -1,    55,    -1,   179,   180,
       8,     9,    10,    11,    12,    13,    14,    15,    67,    68,
      69,    70,    71,    -1,    -1,    -1,   197,    -1,    77,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    85,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    -1,   108,
     109,   110,   111,    25,    -1,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,   124,   125,    -1,    -1,    -1,
      -1,    -1,    -1,   132,   133,   134,   135,   136,   137,    -1,
      -1,   140,   141,    -1,    -1,   144,   145,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   157,   158,
      -1,    -1,    -1,   284,    -1,    -1,   287,    -1,    -1,    -1,
      -1,    -1,   293,   294,   173,    -1,    -1,    -1,    -1,    -1,
     179,   180,   303,   304,    -1,    -1,    -1,    -1,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   197,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   157,
     158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    -1,    -1,    55,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    82,    35,    36,    37,    -1,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,   284,    -1,    -1,   287,    -1,
     238,    -1,   109,   110,   111,   294,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,   303,   304,    -1,   124,   125,    -1,
      -1,     6,    -1,    -1,    -1,   132,   133,   134,   135,   136,
     137,    16,    -1,   140,   141,    -1,    -1,   144,   145,   146,
      -1,    -1,    -1,    -1,    -1,    -1,   284,   285,   286,   287,
     157,   158,   111,    -1,    -1,    -1,   294,    42,    -1,    44,
     298,   299,    -1,    48,    49,    50,   173,    52,    -1,    -1,
      55,    -1,   179,   180,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    -1,    -1,    -1,
     197,    -1,    77,    -1,    -1,    -1,    -1,    82,   157,   158,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   109,   110,   111,    35,    36,    37,
     157,   158,    40,    -1,    -1,    -1,    -1,    -1,    -1,   124,
     125,    -1,    -1,    -1,    -1,    -1,    -1,   132,   133,   134,
     135,   136,   137,    -1,    -1,   140,   141,    -1,    -1,   144,
     145,   146,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,   157,   158,    -1,    -1,    -1,   284,    -1,   238,
     287,    -1,    -1,    -1,    -1,    93,   293,   294,   173,    -1,
      35,    36,    37,    -1,   179,   180,   303,   304,    -1,    -1,
      -1,    -1,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,   238,   197,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    17,    -1,   284,   285,   286,   287,    -1,
      35,    36,    37,    -1,    -1,   294,    -1,    -1,    -1,    -1,
     299,    35,    36,    37,   303,   304,    -1,    -1,    -1,   157,
     158,    -1,    -1,    -1,    -1,    -1,    -1,   284,   285,   286,
     287,    -1,    -1,    -1,    -1,   173,    -1,   294,    -1,    -1,
      -1,    -1,   299,    -1,   301,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,   100,    90,    -1,    -1,   284,
      -1,    -1,   287,    -1,    -1,   213,   100,    -1,    -1,   294,
      -1,   219,   157,   158,    35,    36,    37,    -1,   303,   304,
       8,     9,    10,    11,    12,    13,    14,    15,   173,   237,
     238,    -1,    53,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    -1,   252,   253,   254,    35,    36,    37,
      -1,    -1,   157,   158,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,   157,   158,    53,    -1,    -1,    -1,    -1,
      -1,    59,    -1,    -1,   219,    -1,   284,   285,   286,   287,
      -1,    35,    36,    37,    -1,    -1,   294,    -1,    -1,    -1,
      -1,   299,    -1,   238,    -1,    -1,   304,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   238,    -1,    -1,   157,   158,    -1,   284,
     285,   286,   287,    -1,   238,    35,    36,    37,    -1,   294,
      -1,    -1,    -1,    -1,   299,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,   157,
     158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   284,
     285,   286,   287,    -1,    -1,    -1,    -1,    -1,    -1,   294,
     284,   285,   286,   287,   299,    -1,    -1,    -1,    -1,    -1,
     294,    -1,    -1,   157,   158,   299,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    -1,   238,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     238,    53,    35,    36,    37,    -1,    -1,    59,    -1,    -1,
      -1,    -1,    -1,   284,   285,   286,   287,   157,   158,    -1,
      53,    -1,    -1,   294,    -1,    -1,    -1,    -1,   299,    -1,
      -1,    -1,    -1,    -1,   238,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,   284,   285,   286,   287,
      -1,    -1,    -1,    -1,    -1,    -1,   294,    -1,    -1,    -1,
      -1,   299,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     284,   285,   286,   287,    -1,    -1,    -1,    -1,    -1,    -1,
     294,    -1,    -1,    -1,    -1,   299,    -1,    -1,   238,    -1,
      -1,    -1,    -1,    -1,    -1,   157,   158,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   157,   158,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   284,   285,   286,   287,    -1,    -1,
      -1,    -1,    -1,    10,   294,    -1,    13,    14,    -1,   299,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,   157,   158,   238,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    10,
      -1,    -1,    13,    14,    -1,   238,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,   284,   285,   286,   287,    -1,    -1,    -1,    -1,
      -1,    -1,   294,    -1,    -1,    -1,    -1,   299,    -1,    -1,
      -1,   284,   285,   286,   287,    -1,    -1,    -1,    -1,    -1,
      10,   294,    -1,    13,    14,   238,   299,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    17,
      18,    19,    20,    21,    22,    23,    -1,    25,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,   284,   285,   286,   287,    -1,    -1,    -1,    -1,    -1,
      10,   294,    -1,    13,    14,    -1,   299,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    10,
      -1,    -1,    13,    14,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    10,    -1,
      -1,    13,    14,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    10,    -1,    -1,
      13,    14,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    10,    -1,    -1,
      13,    14,    -1,   300,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    10,    -1,    -1,    13,    14,    -1,   300,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    10,    -1,    -1,    13,    14,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    10,    -1,    -1,    13,    14,    -1,
     300,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    10,    -1,    -1,    13,    14,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    10,    -1,    -1,    13,    14,    -1,
     300,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    10,    -1,    -1,    13,    14,    -1,   300,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    10,    -1,    -1,    13,    14,    -1,   300,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    10,    -1,    -1,    13,    14,    -1,   300,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    10,    -1,    -1,    13,    14,    -1,   300,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,     6,    10,    -1,    -1,
      13,    14,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,   300,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    -1,    45,    46,    47,    -1,    -1,
      -1,    51,   300,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    79,
      80,    81,    82,    -1,   300,    85,    -1,    -1,    -1,    89,
      -1,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,   108,   109,
      -1,   298,   112,   113,   114,   115,   116,    -1,    -1,    -1,
      -1,   121,    -1,    -1,   124,   125,    -1,   127,    -1,   129,
     130,   131,   132,   133,   134,   135,   136,   137,    -1,    -1,
      -1,   141,   298,    -1,    -1,   145,   146,   147,   148,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   294,    -1,    -1,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,   179,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   293,    -1,   197,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,
      -1,    45,    46,    47,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,   293,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    72,    -1,
      74,    -1,    -1,   243,    -1,    79,    -1,    -1,    82,    -1,
      -1,    85,    -1,    -1,   293,    89,    -1,    91,    92,    93,
      94,    95,    96,    -1,    98,    99,    -1,    -1,    -1,    -1,
     104,   105,   106,   107,   108,   109,    -1,    -1,   112,   113,
     114,   115,   116,    -1,   284,    -1,    -1,    -1,    -1,    -1,
     124,   125,    -1,   127,    -1,   129,   130,   131,   132,   133,
     134,   135,   136,   137,    -1,    -1,    -1,   141,    67,    -1,
      -1,   145,   146,   147,   148,    10,    -1,    -1,    13,    14,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,   179,   180,    -1,    -1,    -1,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   197,    -1,   124,   125,    -1,    -1,    -1,
      -1,    -1,    -1,   132,   133,   134,   135,   136,   137,    -1,
      -1,    10,   141,    -1,    13,    14,   145,   146,    17,    18,
      19,    20,    21,    22,    23,    -1,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,   243,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   185,    -1,    -1,   188,
      -1,   190,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     284,    -1,    -1,   212,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,    -1,    -1,
      -1,    -1,    10,   232,    -1,    13,    14,    -1,   173,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,   262,   263,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    10,   272,    -1,    13,    14,    -1,   277,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    10,    -1,    -1,    13,    14,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,   267,    10,    -1,    -1,    13,    14,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    10,    -1,    -1,    13,    14,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    -1,    25,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    -1,    25,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     3,     4,     5,   307,   308,     8,     9,    10,    11,
      12,    13,    14,    15,    35,    36,    37,   157,   158,   238,
     284,   285,   286,   287,   294,   299,   495,   496,   497,   513,
     541,   543,   544,   545,   551,   555,   556,   557,   558,   559,
     560,   561,   562,   564,   565,   566,   109,   418,     0,   309,
     310,   551,   551,   449,   449,   550,   551,   548,   551,   299,
     299,   449,   297,   373,   374,   375,    10,    13,    14,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,   449,   301,    67,   109,   118,   138,   185,   188,   190,
     212,   226,   232,   262,   263,   272,   277,   318,   321,   322,
     323,   334,   406,   407,   414,   415,   192,   217,   227,   239,
     242,   271,   311,   312,   313,   314,   315,   317,   336,   354,
     356,   357,   449,     6,   294,   450,   543,   544,   560,   565,
     543,   295,   296,   560,   561,   300,    39,   550,   551,   550,
     157,   158,   547,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   544,
     557,   560,   566,   325,   227,   327,   414,   414,   240,   328,
     284,   419,   420,   421,   422,   329,   205,   356,   357,   449,
     207,   208,   209,   318,   377,   377,    86,    88,   101,   182,
     316,   361,   451,   452,   453,   566,   374,   375,   551,   295,
     295,   551,   300,   300,    39,   160,   162,   298,    39,   374,
     375,   294,   326,   329,   414,   293,   296,   302,   329,   297,
     331,   333,   284,   335,    62,   378,   379,   393,   394,   449,
      62,   284,   337,   284,   362,     7,   296,   302,    39,   547,
     551,   547,   547,   551,   284,   319,   320,   294,   419,   551,
     298,   547,   293,   355,   362,   293,    40,    41,    42,    45,
      46,    47,    51,    67,    72,    73,    74,    79,    80,    81,
      82,    85,    89,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   104,   105,   106,   107,   108,   112,   113,   114,
     115,   116,   121,   124,   125,   127,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   141,   145,   146,   147,   148,
     179,   180,   197,   243,   284,   362,   380,   395,   396,   397,
     398,   399,   402,   408,   409,   410,   413,   418,   425,   426,
     427,   429,   431,   440,   445,   455,   457,   458,   459,   460,
     461,   462,   463,   464,   469,   486,   490,   491,   503,   504,
     506,   508,   509,   510,   538,   571,   355,   299,   360,   452,
     385,   551,   551,   298,   298,   298,   295,   296,   324,    39,
     449,   492,   303,   437,   438,   284,   456,   526,    43,   416,
     381,   284,   400,   401,   492,   411,   412,   413,   411,   420,
     403,   404,   414,   318,   411,   403,   567,   568,   419,   428,
     428,   297,   374,   423,   424,   540,   565,   243,   284,   505,
     243,   505,   243,   505,   303,   470,   569,   437,   569,   437,
     569,   569,   437,   284,   465,   466,   467,   468,    39,   284,
     338,   341,   344,   376,   449,   299,   358,   359,   363,   319,
     295,   547,    16,    42,    44,    48,    49,    50,    52,    55,
      68,    69,    70,    71,    77,   110,   111,   140,   144,   173,
     179,   303,   304,   418,   425,   429,   454,   455,   493,   494,
     495,   499,   501,   502,   503,   504,   506,   511,   514,   515,
     516,   517,   519,   520,   521,   522,   524,   525,   529,   530,
     533,   537,   543,   556,   299,   439,   564,   487,   488,   542,
     543,   293,   296,   414,    44,    48,    61,    68,    77,   382,
     384,   386,   389,   392,   394,   449,   293,   296,   376,   417,
     414,   417,   293,   293,   296,   329,   417,   417,   293,   465,
     465,   293,   296,   293,   547,   284,   570,   572,   573,   299,
     359,   299,    39,   299,    39,   299,   210,   299,   284,   477,
     478,   479,   117,   139,   430,   465,   437,   465,   437,   437,
     465,   293,   296,   423,   503,   504,   506,   300,   296,   300,
     296,    97,   301,   364,   365,   369,   370,   371,   372,   376,
     449,   293,   293,   329,   298,   500,   526,   488,   489,    39,
     539,   299,   299,   299,   543,   512,   540,   299,   489,   492,
      39,   539,   299,   543,   299,   299,   299,   299,   559,   566,
     299,   299,   439,     6,    17,   299,   526,   293,   293,   293,
     293,   449,   492,   498,    28,   159,   161,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   302,   518,   293,
     439,   293,   296,   302,   526,    82,   107,   108,   128,   331,
     441,   442,    39,   381,   299,   299,   299,   401,   330,   296,
     329,   404,   284,   405,   293,   293,   419,   293,   296,   302,
     293,    40,    93,   173,   213,   219,   237,   252,   253,   254,
     525,   551,   552,   553,   554,   551,   552,   551,   551,   301,
     471,   472,   473,   474,   475,   551,   293,   296,   299,   406,
     293,   465,   293,   465,   465,   293,   478,   299,   293,   342,
     345,   449,   293,   346,   376,   376,   376,   296,   300,   296,
     300,   297,   373,   374,    80,    81,    97,   366,   367,   368,
     293,   284,   538,    58,   498,   551,   551,   551,   293,   516,
     534,   543,   538,    83,   551,   551,   551,   551,   551,   551,
     548,   300,    17,    90,   100,   527,   528,   551,   293,   111,
     523,   524,   525,   551,   523,   551,   296,   300,   488,   551,
     563,   565,   284,   390,    58,   385,   391,   401,   385,   297,
     332,   376,   302,   572,   548,   446,   552,   552,   297,   559,
     552,   299,   552,   552,   552,   552,   299,   267,   554,    41,
      96,   155,   156,   255,   256,   274,   275,   300,   553,   293,
     300,   293,   300,   284,   476,   300,   296,   296,   478,   301,
     480,   481,   482,   483,   484,   485,   549,   551,   437,   293,
     293,   293,   480,   339,   340,   341,   342,   343,   449,   342,
      81,   347,   348,   296,   299,   365,   376,   370,   411,   411,
     318,   411,   539,   300,   300,   300,   293,   539,   300,   300,
     300,   300,   300,   300,   300,   300,   551,   551,    96,   296,
     300,   299,   551,   551,   439,   359,   381,   300,   293,   302,
     300,   547,   551,   330,   547,   447,   448,   449,   498,   559,
     553,   552,   553,   553,   552,   552,   552,   552,   552,   552,
     552,   552,   498,   507,   507,   507,   299,   474,   475,   376,
     300,   296,   296,   284,   432,   433,   434,   435,   436,   300,
     340,   347,   293,   293,   293,   109,   417,    63,   126,   376,
     371,   376,   376,   376,   376,    58,    53,   531,   532,   550,
     531,   531,   551,    83,   498,   492,   498,   492,   507,   528,
     528,   551,   296,   300,   293,    58,    53,   387,   388,   550,
     385,   385,   293,   382,   383,    39,   298,   402,   408,   409,
     410,   425,   426,   454,   455,    66,    39,   300,   300,    57,
     549,   299,   483,   485,   293,   296,   302,   329,   293,   296,
      63,   284,   546,   349,   350,   351,   300,    39,   498,    59,
     532,    39,    59,    59,   293,    57,   300,   439,   408,   443,
     444,   448,   449,    39,   383,    59,   388,    39,   293,    57,
     547,   293,   293,   293,   305,   559,   492,   300,   549,   433,
     434,   551,   434,   436,    65,   350,    39,   498,   498,   517,
     535,   536,   543,   556,   498,   525,   300,   293,   444,   449,
     492,   425,   454,   455,   383,   383,   391,   383,   298,   298,
     298,   300,   352,   300,   302,    60,   300,    39,   293,   492,
     392,   353,   293
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   306,   308,   307,   307,   307,   309,   310,   310,   311,
     311,   311,   311,   311,   311,   311,   311,   312,   313,   314,
     315,   316,   317,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   319,   320,   320,   321,   321,   321,   322,   323,
     324,   325,   326,   327,   327,   328,   328,   329,   329,   330,
     330,   331,   331,   332,   332,   333,   334,   334,   335,   336,
     336,   337,   338,   339,   339,   340,   340,   340,   341,   342,
     343,   344,   345,   345,   346,   346,   347,   348,   349,   349,
     350,   350,   351,   352,   353,   354,   354,   354,   354,   355,
     355,   356,   357,   358,   359,   359,   360,   361,   361,   362,
     363,   364,   364,   364,   365,   365,   365,   366,   367,   367,
     368,   369,   369,   370,   370,   371,   371,   372,   372,   372,
     373,   374,   375,   375,   376,   377,   377,   378,   378,   379,
     379,   379,   380,   381,   381,   382,   382,   382,   382,   382,
     383,   383,   384,   384,   385,   386,   387,   387,   388,   388,
     388,   389,   390,   391,   392,   392,   393,   393,   393,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     395,   395,   395,   395,   395,   395,   395,   396,   396,   396,
     397,   398,   399,   400,   400,   401,   402,   402,   403,   403,
     404,   405,   406,   406,   407,   408,   409,   409,   410,   411,
     412,   412,   413,   413,   414,   414,   415,   415,   416,   416,
     417,   417,   418,   419,   419,   420,   420,   421,   422,   423,
     423,   424,   425,   426,   427,   428,   428,   429,   429,   430,
     430,   430,   431,   431,   431,   431,   431,   431,   431,   431,
     431,   431,   432,   432,   433,   434,   435,   435,   436,   437,
     437,   438,   438,   438,   438,   439,   440,   441,   441,   442,
     442,   442,   442,   442,   443,   443,   444,   444,   445,   446,
     446,   447,   447,   447,   447,   448,   448,   448,   448,   448,
     449,   449,   450,   451,   451,   452,   452,   453,   454,   455,
     456,   456,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   458,   458,   459,   459,   459,   459,   460,   460,   460,
     460,   461,   461,   461,   461,   461,   461,   462,   462,   463,
     463,   463,   463,   464,   464,   465,   465,   466,   467,   467,
     468,   469,   470,   470,   471,   471,   472,   472,   473,   473,
     474,   475,   476,   477,   477,   478,   479,   479,   480,   481,
     481,   482,   482,   483,   484,   484,   485,   486,   487,   487,
     488,   489,   490,   491,   492,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   494,   495,   495,
     496,   497,   497,   498,   498,   499,   500,   501,   501,   502,
     503,   503,   504,   504,   505,   506,   507,   507,   508,   508,
     509,   509,   510,   510,   511,   512,   513,   514,   515,   515,
     515,   515,   516,   516,   517,   518,   518,   518,   518,   518,
     518,   518,   518,   518,   518,   518,   518,   518,   519,   519,
     520,   521,   521,   521,   522,   522,   522,   523,   523,   523,
     524,   524,   525,   525,   525,   525,   525,   526,   527,   527,
     527,   528,   528,   528,   529,   529,   530,   530,   530,   531,
     531,   532,   532,   532,   533,   533,   533,   533,   534,   535,
     536,   536,   537,   537,   538,   539,   539,   540,   541,   542,
     543,   543,   543,   543,   544,   544,   545,   546,   547,   548,
     548,   549,   549,   550,   550,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   552,   552,   552,   552,
     552,   552,   552,   552,   552,   552,   552,   552,   552,   552,
     552,   552,   552,   553,   553,   553,   553,   553,   554,   554,
     554,   555,   555,   555,   555,   555,   555,   555,   555,   555,
     556,   556,   556,   556,   557,   557,   557,   557,   557,   557,
     557,   557,   557,   558,   559,   560,   561,   561,   562,   563,
     564,   565,   565,   566,   567,   568,   569,   570,   570,   571,
     572,   573
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     2,     2,     1,     0,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     2,
       2,     1,     4,     3,     2,     7,     5,     1,     1,     3,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       0,     0,     0,     0,     1,     0,     1,     0,     2,     0,
       2,     5,     1,     5,     3,     2,     1,     1,     1,    10,
       9,     1,     3,     1,     2,     2,     2,     2,     3,     3,
       3,     3,     1,     2,     1,     3,     4,     0,     1,     2,
       4,     6,     0,     0,     0,     4,     4,     2,     2,     0,
       1,     6,     6,     3,     0,     1,     0,     1,     1,     1,
       3,     1,     3,     3,     2,     2,     2,     3,     3,     3,
       3,     1,     3,     1,     5,     0,     1,     1,     2,     2,
       3,     5,     5,     5,     1,     0,     2,     2,     1,     1,
       2,     2,     3,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     5,     7,     1,     6,     1,     2,     3,     3,
       2,     9,     1,     3,     3,     5,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     1,     3,     3,     1,     3,
       5,     1,     1,     1,     2,     3,     3,     3,     3,     3,
       0,     1,     1,     1,     0,     1,     1,     1,     0,     1,
       2,     4,     4,     3,     1,     1,     3,     2,     1,     0,
       1,     1,     3,     3,     3,     1,     3,     7,     7,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     1,     1,     3,     3,     0,
       1,     2,     4,     6,     8,     1,    10,     0,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     7,     0,
       2,     1,     3,     3,     3,     2,     2,     2,     2,     2,
       0,     2,     3,     1,     3,     3,     1,     1,     1,     3,
       1,     3,     4,     5,     4,     5,     5,     4,     3,     4,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     0,     1,
       1,     4,     0,     4,     1,     1,     1,     3,     1,     3,
       1,     5,     1,     1,     3,     4,     0,     1,     1,     1,
       1,     1,     3,     1,     1,     3,     5,     4,     1,     3,
       3,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     2,     1,     1,
       4,     1,     4,     1,     2,     3,     1,     3,     5,     3,
       6,     5,     6,     5,     1,     6,     1,     3,     1,     3,
       1,     3,     1,     3,     5,     1,     1,     5,     2,     2,
       2,     2,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       2,     1,     1,     1,     2,     2,     4,     1,     1,     5,
       2,     4,     2,     4,     2,     4,     3,     1,     1,     3,
       3,     1,     2,     2,     5,     7,     6,     6,     6,     1,
       2,     3,     3,     2,     2,     5,     5,     9,     1,     1,
       1,     1,     3,     5,     1,     0,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     2,     1,     1,     1,     1,
       5,     0,     1,     1,     3,     1,     3,     1,     3,     3,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     5,     1,     1,     2,     3,     3,
       3,     3,     4,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     1,     2,     3,     4,     3,     2,     6,
       6,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     1,     2,     2,     1,     1,
       1,     3,     1,     1,     1,     3,     4,     4,     1,     1,
       1,     1,     3,     1,     0,     0,     0,     1,     3,     4,
       3,     1
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
#line 567 "parser.y"
                             { /*yydebug=1;*/ }
#line 3256 "verilog_y.tab.cpp"
    break;

  case 4:
#line 569 "parser.y"
           { PARSER.parse_tree.expr.swap(stack_expr(yyvsp[0])); }
#line 3262 "verilog_y.tab.cpp"
    break;

  case 5:
#line 571 "parser.y"
           { PARSER.parse_tree.expr.swap(stack_expr(yyvsp[0])); }
#line 3268 "verilog_y.tab.cpp"
    break;

  case 22:
#line 621 "parser.y"
                { PARSER.parse_tree.create_typedef(stack_expr(yyvsp[-2]), stack_expr(yyvsp[-1])); }
#line 3274 "verilog_y.tab.cpp"
    break;

  case 23:
#line 626 "parser.y"
                {
                  yyval=yyvsp[0];
                  add_as_subtype(stack_type(yyval), stack_type(yyvsp[-1]));
                }
#line 3283 "verilog_y.tab.cpp"
    break;

  case 24:
#line 631 "parser.y"
                {
                  yyval=yyvsp[-1];
                  add_as_subtype(stack_type(yyval), stack_type(yyvsp[0]));
                }
#line 3292 "verilog_y.tab.cpp"
    break;

  case 25:
#line 640 "parser.y"
                { /* todo */ }
#line 3298 "verilog_y.tab.cpp"
    break;

  case 26:
#line 642 "parser.y"
                { init(yyval, ID_c_enum); }
#line 3304 "verilog_y.tab.cpp"
    break;

  case 27:
#line 644 "parser.y"
                { init(yyval, ID_string); }
#line 3310 "verilog_y.tab.cpp"
    break;

  case 28:
#line 646 "parser.y"
                { init(yyval, ID_chandle); }
#line 3316 "verilog_y.tab.cpp"
    break;

  case 29:
#line 648 "parser.y"
                { init(yyval, "virtual_interface"); }
#line 3322 "verilog_y.tab.cpp"
    break;

  case 31:
#line 654 "parser.y"
                { init(yyval, ID_event); }
#line 3328 "verilog_y.tab.cpp"
    break;

  case 33:
#line 666 "parser.y"
                { init(yyval); mts(yyval, yyvsp[0]); }
#line 3334 "verilog_y.tab.cpp"
    break;

  case 34:
#line 668 "parser.y"
                { yyval=yyvsp[-2]; mts(yyval, yyvsp[0]); }
#line 3340 "verilog_y.tab.cpp"
    break;

  case 35:
#line 672 "parser.y"
                  { init(yyval, ID_bit); }
#line 3346 "verilog_y.tab.cpp"
    break;

  case 36:
#line 673 "parser.y"
                    { init(yyval, ID_logic); }
#line 3352 "verilog_y.tab.cpp"
    break;

  case 37:
#line 674 "parser.y"
                  { init(yyval, ID_reg); }
#line 3358 "verilog_y.tab.cpp"
    break;

  case 38:
#line 678 "parser.y"
                { init(yyval, ID_int); }
#line 3364 "verilog_y.tab.cpp"
    break;

  case 39:
#line 682 "parser.y"
                { init(yyval, ID_class); }
#line 3370 "verilog_y.tab.cpp"
    break;

  case 43:
#line 702 "parser.y"
          { make_nil(yyval); }
#line 3376 "verilog_y.tab.cpp"
    break;

  case 44:
#line 703 "parser.y"
                        { init(yyval, ID_interface); }
#line 3382 "verilog_y.tab.cpp"
    break;

  case 45:
#line 717 "parser.y"
          { make_nil(yyval); }
#line 3388 "verilog_y.tab.cpp"
    break;

  case 46:
#line 718 "parser.y"
                     { init(yyval, ID_packed); }
#line 3394 "verilog_y.tab.cpp"
    break;

  case 47:
#line 723 "parser.y"
          { make_nil(yyval); }
#line 3400 "verilog_y.tab.cpp"
    break;

  case 48:
#line 725 "parser.y"
          {
	    yyval=yyvsp[-1];
	    add_as_subtype(stack_type(yyval), stack_type(yyvsp[0]));
	  }
#line 3409 "verilog_y.tab.cpp"
    break;

  case 49:
#line 733 "parser.y"
          { make_nil(yyval); }
#line 3415 "verilog_y.tab.cpp"
    break;

  case 50:
#line 735 "parser.y"
          {
	    yyval=yyvsp[-1];
	    add_as_subtype(stack_type(yyval), stack_type(yyvsp[0]));
	  }
#line 3424 "verilog_y.tab.cpp"
    break;

  case 51:
#line 743 "parser.y"
                { init(yyval, ID_array);
		  stack_type(yyval).subtype().make_nil();
		  exprt &range=static_cast<exprt &>(stack_type(yyval).add(ID_range));
		  range.copy_to_operands(stack_expr(yyvsp[-3]), stack_expr(yyvsp[-1])); }
#line 3433 "verilog_y.tab.cpp"
    break;

  case 53:
#line 752 "parser.y"
                { init(yyval, ID_array);
		  stack_type(yyval).subtype().make_nil();
		  exprt &range=static_cast<exprt &>(stack_type(yyval).add(ID_range));
		  range.copy_to_operands(stack_expr(yyvsp[-3]), stack_expr(yyvsp[-1])); }
#line 3442 "verilog_y.tab.cpp"
    break;

  case 54:
#line 757 "parser.y"
        {
	  yyval=yyvsp[-1];
	}
#line 3450 "verilog_y.tab.cpp"
    break;

  case 55:
#line 763 "parser.y"
                { init(yyval, "unsized"); }
#line 3456 "verilog_y.tab.cpp"
    break;

  case 56:
#line 767 "parser.y"
                     { init(yyval, ID_struct); }
#line 3462 "verilog_y.tab.cpp"
    break;

  case 57:
#line 768 "parser.y"
                    { init(yyval, ID_union); }
#line 3468 "verilog_y.tab.cpp"
    break;

  case 58:
#line 772 "parser.y"
                { new_symbol(yyval, yyvsp[0]); }
#line 3474 "verilog_y.tab.cpp"
    break;

  case 85:
#line 849 "parser.y"
          {
            PARSER.parse_tree.create_module(
              stack_expr(yyvsp[-3]).operands()[0],
              stack_expr(yyvsp[-3]).operands()[1],
              stack_expr(yyvsp[-3]).operands()[2],
              stack_expr(yyvsp[-3]).operands()[4],
              stack_expr(yyvsp[-2]));
          }
#line 3487 "verilog_y.tab.cpp"
    break;

  case 86:
#line 858 "parser.y"
          {
            PARSER.parse_tree.create_module(
              stack_expr(yyvsp[-3]).operands()[0],
              stack_expr(yyvsp[-3]).operands()[1],
              stack_expr(yyvsp[-3]).operands()[2],
              stack_expr(yyvsp[-3]).operands()[4],
              stack_expr(yyvsp[-2]));
          }
#line 3500 "verilog_y.tab.cpp"
    break;

  case 91:
#line 883 "parser.y"
          { 
            init(yyval); stack_expr(yyval).operands().resize(5);
            stack_expr(yyval).operands()[0].swap(stack_expr(yyvsp[-5]));
            stack_expr(yyval).operands()[1].swap(stack_expr(yyvsp[-4]));
            stack_expr(yyval).operands()[2].swap(stack_expr(yyvsp[-3]));
            stack_expr(yyval).operands()[3].swap(stack_expr(yyvsp[-2]));
            stack_expr(yyval).operands()[4].swap(stack_expr(yyvsp[-1]));
          }
#line 3513 "verilog_y.tab.cpp"
    break;

  case 92:
#line 899 "parser.y"
          { 
            init(yyval); stack_expr(yyval).operands().resize(5);
            stack_expr(yyval).operands()[0].swap(stack_expr(yyvsp[-5]));
            stack_expr(yyval).operands()[1].swap(stack_expr(yyvsp[-4]));
            stack_expr(yyval).operands()[2].swap(stack_expr(yyvsp[-3]));
            stack_expr(yyval).operands()[3].swap(stack_expr(yyvsp[-2]));
            stack_expr(yyval).operands()[4].swap(stack_expr(yyvsp[-1]));
          }
#line 3526 "verilog_y.tab.cpp"
    break;

  case 93:
#line 909 "parser.y"
                                                          { yyval=yyvsp[-1]; }
#line 3532 "verilog_y.tab.cpp"
    break;

  case 94:
#line 914 "parser.y"
              { make_nil(yyval); }
#line 3538 "verilog_y.tab.cpp"
    break;

  case 96:
#line 920 "parser.y"
              { init(yyval); }
#line 3544 "verilog_y.tab.cpp"
    break;

  case 97:
#line 924 "parser.y"
                     { init(yyval, ID_module); }
#line 3550 "verilog_y.tab.cpp"
    break;

  case 98:
#line 925 "parser.y"
                          { init(yyval, ID_macromodule); }
#line 3556 "verilog_y.tab.cpp"
    break;

  case 100:
#line 930 "parser.y"
                                  { yyval = yyvsp[-1]; }
#line 3562 "verilog_y.tab.cpp"
    break;

  case 101:
#line 935 "parser.y"
                { init(yyval); mts(yyval, yyvsp[0]); }
#line 3568 "verilog_y.tab.cpp"
    break;

  case 102:
#line 937 "parser.y"
                { yyval=yyvsp[-2]; mts(yyval, yyvsp[0]); }
#line 3574 "verilog_y.tab.cpp"
    break;

  case 103:
#line 942 "parser.y"
                { yyval=yyvsp[-2];
		  exprt decl(ID_decl);
		  decl.move_to_operands(stack_expr(yyvsp[0]));
		  // grab the type and class from previous!
		  const irept &prev=stack_expr(yyval).get_sub().back();
                  decl.set(ID_type, prev.find(ID_type));
                  decl.set(ID_class, prev.find(ID_class));
		  stack_expr(yyval).move_to_sub(decl);
		}
#line 3588 "verilog_y.tab.cpp"
    break;

  case 104:
#line 954 "parser.y"
                                                                 { yyval=yyvsp[0]; }
#line 3594 "verilog_y.tab.cpp"
    break;

  case 105:
#line 955 "parser.y"
                                                                 { yyval=yyvsp[0]; }
#line 3600 "verilog_y.tab.cpp"
    break;

  case 106:
#line 956 "parser.y"
                                                                  { yyval=yyvsp[0]; }
#line 3606 "verilog_y.tab.cpp"
    break;

  case 107:
#line 961 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_input);
                  addswap(yyval, ID_type, yyvsp[-1]);
                  mto(yyval, yyvsp[0]); }
#line 3615 "verilog_y.tab.cpp"
    break;

  case 108:
#line 969 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_output);
                  addswap(yyval, ID_type, yyvsp[-1]);
                  mto(yyval, yyvsp[0]); }
#line 3624 "verilog_y.tab.cpp"
    break;

  case 109:
#line 974 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_output_register);
                  addswap(yyval, ID_type, yyvsp[-1]);
                  mto(yyval, yyvsp[0]); }
#line 3633 "verilog_y.tab.cpp"
    break;

  case 110:
#line 982 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_inout);
                  addswap(yyval, ID_type, yyvsp[-1]);
                  mto(yyval, yyvsp[0]); }
#line 3642 "verilog_y.tab.cpp"
    break;

  case 111:
#line 990 "parser.y"
                { init(yyval); mts(yyval, yyvsp[0]); }
#line 3648 "verilog_y.tab.cpp"
    break;

  case 112:
#line 992 "parser.y"
                { yyval=yyvsp[-2];    mts(yyval, yyvsp[0]); }
#line 3654 "verilog_y.tab.cpp"
    break;

  case 113:
#line 996 "parser.y"
                { if(stack_expr(yyvsp[0]).is_nil())
		    yyval=yyvsp[0];
		  else { init(yyval, ID_decl);  mto(yyval, yyvsp[0]); }
		}
#line 3663 "verilog_y.tab.cpp"
    break;

  case 114:
#line 1001 "parser.y"
                { init(yyval, ID_decl);
		  make_nil(yyval); /* Not supported */ }
#line 3670 "verilog_y.tab.cpp"
    break;

  case 115:
#line 1007 "parser.y"
          { make_nil(yyval); }
#line 3676 "verilog_y.tab.cpp"
    break;

  case 118:
#line 1013 "parser.y"
                                      { make_nil(yyval); /* Not supported */ }
#line 3682 "verilog_y.tab.cpp"
    break;

  case 119:
#line 1014 "parser.y"
                                      { make_nil(yyval); /* Not supported */ }
#line 3688 "verilog_y.tab.cpp"
    break;

  case 120:
#line 1019 "parser.y"
                { init(yyval, ID_bit_select); mto(yyval, yyvsp[-1]); }
#line 3694 "verilog_y.tab.cpp"
    break;

  case 121:
#line 1024 "parser.y"
                { init(yyval, ID_part_select); mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[-1]); }
#line 3700 "verilog_y.tab.cpp"
    break;

  case 122:
#line 1029 "parser.y"
                { init(yyval, ID_indexed_part_select_plus); mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[-1]); }
#line 3706 "verilog_y.tab.cpp"
    break;

  case 123:
#line 1031 "parser.y"
                { init(yyval, ID_indexed_part_select_minus); mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[-1]); }
#line 3712 "verilog_y.tab.cpp"
    break;

  case 124:
#line 1035 "parser.y"
                { new_symbol(yyval, yyvsp[0]); }
#line 3718 "verilog_y.tab.cpp"
    break;

  case 125:
#line 1042 "parser.y"
                { init(yyval); }
#line 3724 "verilog_y.tab.cpp"
    break;

  case 126:
#line 1044 "parser.y"
                { yyval=yyvsp[-1]; mts(yyval, yyvsp[0]); }
#line 3730 "verilog_y.tab.cpp"
    break;

  case 130:
#line 1058 "parser.y"
                                                           { yyval=yyvsp[0]; }
#line 3736 "verilog_y.tab.cpp"
    break;

  case 131:
#line 1059 "parser.y"
                                                         {yyval=yyvsp[0]; }
#line 3742 "verilog_y.tab.cpp"
    break;

  case 132:
#line 1072 "parser.y"
                { init(yyval, ID_generate_block); swapop(yyval, yyvsp[-1]); }
#line 3748 "verilog_y.tab.cpp"
    break;

  case 133:
#line 1077 "parser.y"
                { init(yyval); }
#line 3754 "verilog_y.tab.cpp"
    break;

  case 134:
#line 1079 "parser.y"
                { yyval=yyvsp[-1]; mto(yyval, yyvsp[0]); }
#line 3760 "verilog_y.tab.cpp"
    break;

  case 141:
#line 1092 "parser.y"
              { init(yyval, ID_generate_skip); }
#line 3766 "verilog_y.tab.cpp"
    break;

  case 142:
#line 1097 "parser.y"
                { init(yyval, ID_generate_if); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 3772 "verilog_y.tab.cpp"
    break;

  case 143:
#line 1099 "parser.y"
                { init(yyval, ID_generate_if); mto(yyval, yyvsp[-4]); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 3778 "verilog_y.tab.cpp"
    break;

  case 145:
#line 1107 "parser.y"
                { init(yyval, ID_generate_case); mto(yyval, yyvsp[-3]); }
#line 3784 "verilog_y.tab.cpp"
    break;

  case 151:
#line 1126 "parser.y"
                { init(yyval, ID_generate_for);
          	  stack_expr(yyval).reserve_operands(4);
          	  mto(yyval, yyvsp[-6]);
          	  mto(yyval, yyvsp[-4]);
          	  mto(yyval, yyvsp[-2]);
          	  mto(yyval, yyvsp[0]);
          	}
#line 3796 "verilog_y.tab.cpp"
    break;

  case 153:
#line 1139 "parser.y"
                { init(yyval, ID_generate_assign); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 3802 "verilog_y.tab.cpp"
    break;

  case 154:
#line 1144 "parser.y"
                { init(yyval, ID_generate_block); }
#line 3808 "verilog_y.tab.cpp"
    break;

  case 155:
#line 1146 "parser.y"
                { init(yyval, ID_generate_block); stack_expr(yyval).operands().swap(stack_expr(yyvsp[-1]).operands()); }
#line 3814 "verilog_y.tab.cpp"
    break;

  case 156:
#line 1150 "parser.y"
                                                     { yyval=yyvsp[0]; }
#line 3820 "verilog_y.tab.cpp"
    break;

  case 157:
#line 1151 "parser.y"
                                                     { yyval=yyvsp[0]; }
#line 3826 "verilog_y.tab.cpp"
    break;

  case 158:
#line 1152 "parser.y"
                                                      { yyval=yyvsp[0]; }
#line 3832 "verilog_y.tab.cpp"
    break;

  case 159:
#line 1156 "parser.y"
                                                                       { yyval=yyvsp[0]; }
#line 3838 "verilog_y.tab.cpp"
    break;

  case 160:
#line 1158 "parser.y"
                                                         { yyval=yyvsp[0]; }
#line 3844 "verilog_y.tab.cpp"
    break;

  case 161:
#line 1159 "parser.y"
                                                     { yyval=yyvsp[0]; }
#line 3850 "verilog_y.tab.cpp"
    break;

  case 162:
#line 1160 "parser.y"
                                                      { yyval=yyvsp[0]; }
#line 3856 "verilog_y.tab.cpp"
    break;

  case 163:
#line 1162 "parser.y"
                                                        { yyval=yyvsp[0]; }
#line 3862 "verilog_y.tab.cpp"
    break;

  case 164:
#line 1163 "parser.y"
                                                     { yyval=yyvsp[0]; }
#line 3868 "verilog_y.tab.cpp"
    break;

  case 165:
#line 1164 "parser.y"
                                                    { yyval=yyvsp[0]; }
#line 3874 "verilog_y.tab.cpp"
    break;

  case 166:
#line 1165 "parser.y"
                                                               { yyval=yyvsp[0]; }
#line 3880 "verilog_y.tab.cpp"
    break;

  case 167:
#line 1166 "parser.y"
                                                               { yyval=yyvsp[0]; }
#line 3886 "verilog_y.tab.cpp"
    break;

  case 168:
#line 1167 "parser.y"
                                                              { yyval=yyvsp[0]; }
#line 3892 "verilog_y.tab.cpp"
    break;

  case 169:
#line 1168 "parser.y"
                                                                         { yyval=yyvsp[0]; }
#line 3898 "verilog_y.tab.cpp"
    break;

  case 182:
#line 1196 "parser.y"
                { init(yyval, ID_decl); stack_expr(yyval).set(ID_class, ID_genvar); swapop(yyval, yyvsp[-1]); }
#line 3904 "verilog_y.tab.cpp"
    break;

  case 183:
#line 1201 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 3910 "verilog_y.tab.cpp"
    break;

  case 184:
#line 1203 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 3916 "verilog_y.tab.cpp"
    break;

  case 185:
#line 1207 "parser.y"
                { new_symbol(yyval, yyvsp[0]); }
#line 3922 "verilog_y.tab.cpp"
    break;

  case 186:
#line 1212 "parser.y"
                { init(yyval, ID_parameter_decl); swapop(yyval, yyvsp[-1]); }
#line 3928 "verilog_y.tab.cpp"
    break;

  case 187:
#line 1214 "parser.y"
                { init(yyval, ID_local_parameter_decl); swapop(yyval, yyvsp[-1]); }
#line 3934 "verilog_y.tab.cpp"
    break;

  case 188:
#line 1219 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 3940 "verilog_y.tab.cpp"
    break;

  case 189:
#line 1221 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 3946 "verilog_y.tab.cpp"
    break;

  case 190:
#line 1225 "parser.y"
                { // $1 and $2 implement Verilog 2000 sized parameters,
		  // which can be ignored
		  init(yyval, ID_parameter);
		  addswap(yyval, ID_identifier, yyvsp[-2]);
		  addswap(yyval, ID_value, yyvsp[0]); }
#line 3956 "verilog_y.tab.cpp"
    break;

  case 194:
#line 1241 "parser.y"
                {
                  yyval=yyvsp[0];
                  add_as_subtype(stack_type(yyval), stack_type(yyvsp[-1]));
                }
#line 3965 "verilog_y.tab.cpp"
    break;

  case 195:
#line 1249 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_input);
                  addswap(yyval, ID_type, yyvsp[-1]);
                  swapop(yyval, yyvsp[0]); }
#line 3974 "verilog_y.tab.cpp"
    break;

  case 196:
#line 1257 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_output);
                  addswap(yyval, ID_type, yyvsp[-1]);
                  swapop(yyval, yyvsp[0]); }
#line 3983 "verilog_y.tab.cpp"
    break;

  case 197:
#line 1262 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_output_register);
                  addswap(yyval, ID_type, yyvsp[-1]);
                  swapop(yyval, yyvsp[0]); }
#line 3992 "verilog_y.tab.cpp"
    break;

  case 198:
#line 1270 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_inout);
                  addswap(yyval, ID_type, yyvsp[-1]);
                  swapop(yyval, yyvsp[0]); }
#line 4001 "verilog_y.tab.cpp"
    break;

  case 199:
#line 1277 "parser.y"
                {
                  yyval=yyvsp[0];
                  add_as_subtype(stack_type(yyval), stack_type(yyvsp[-1]));
                  // the net type is ignored right now
                }
#line 4011 "verilog_y.tab.cpp"
    break;

  case 200:
#line 1286 "parser.y"
                { init(yyval, ID_nil); }
#line 4017 "verilog_y.tab.cpp"
    break;

  case 203:
#line 1293 "parser.y"
                { init(yyval, ID_trireg); }
#line 4023 "verilog_y.tab.cpp"
    break;

  case 204:
#line 1297 "parser.y"
                { make_nil(yyval); }
#line 4029 "verilog_y.tab.cpp"
    break;

  case 206:
#line 1302 "parser.y"
                     { init(yyval, ID_signed); }
#line 4035 "verilog_y.tab.cpp"
    break;

  case 207:
#line 1303 "parser.y"
                       { init(yyval, ID_unsigned); }
#line 4041 "verilog_y.tab.cpp"
    break;

  case 208:
#line 1308 "parser.y"
                { make_nil(yyval); }
#line 4047 "verilog_y.tab.cpp"
    break;

  case 209:
#line 1310 "parser.y"
                { init(yyval, ID_automatic); }
#line 4053 "verilog_y.tab.cpp"
    break;

  case 210:
#line 1315 "parser.y"
                { init(yyval); stack_expr(yyvsp[-1]).type().swap(stack_expr(yyvsp[0])); mto(yyval, yyvsp[-1]); }
#line 4059 "verilog_y.tab.cpp"
    break;

  case 211:
#line 1317 "parser.y"
                { yyval=yyvsp[-3];    stack_expr(yyvsp[-1]).type().swap(stack_expr(yyvsp[0])); mto(yyval, yyvsp[-1]); }
#line 4065 "verilog_y.tab.cpp"
    break;

  case 212:
#line 1322 "parser.y"
                { init(yyval, ID_decl);
		  stack_expr(yyval).set(ID_class, ID_reg);
                  addswap(yyval, ID_type, yyvsp[-2]);
		  swapop(yyval, yyvsp[-1]); }
#line 4074 "verilog_y.tab.cpp"
    break;

  case 213:
#line 1330 "parser.y"
                { init(yyval, ID_equal); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 4080 "verilog_y.tab.cpp"
    break;

  case 215:
#line 1336 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4086 "verilog_y.tab.cpp"
    break;

  case 216:
#line 1338 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4092 "verilog_y.tab.cpp"
    break;

  case 217:
#line 1343 "parser.y"
          { 
            yyval=yyvsp[-1];
            stack_expr(yyval).add(ID_type)=stack_expr(yyvsp[0]);
          }
#line 4101 "verilog_y.tab.cpp"
    break;

  case 218:
#line 1350 "parser.y"
                { new_symbol(yyval, yyvsp[0]); }
#line 4107 "verilog_y.tab.cpp"
    break;

  case 219:
#line 1358 "parser.y"
                { make_nil(yyval); }
#line 4113 "verilog_y.tab.cpp"
    break;

  case 222:
#line 1366 "parser.y"
                { init(yyval, ID_decl); stack_expr(yyval).set(ID_class, ID_integer); swapop(yyval, yyvsp[-1]); }
#line 4119 "verilog_y.tab.cpp"
    break;

  case 223:
#line 1371 "parser.y"
                { init(yyval, ID_decl); stack_expr(yyval).set(ID_class, ID_realtime); swapop(yyval, yyvsp[-1]); }
#line 4125 "verilog_y.tab.cpp"
    break;

  case 224:
#line 1376 "parser.y"
                { init(yyval, ID_decl); stack_expr(yyval).set(ID_class, ID_realtime); swapop(yyval, yyvsp[-1]); }
#line 4131 "verilog_y.tab.cpp"
    break;

  case 225:
#line 1381 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4137 "verilog_y.tab.cpp"
    break;

  case 226:
#line 1383 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4143 "verilog_y.tab.cpp"
    break;

  case 227:
#line 1388 "parser.y"
                { init(yyval, ID_decl);
                  addswap(yyval, ID_class, yyvsp[-6]);
                  addswap(yyval, ID_type, yyvsp[-3]);
                  swapop(yyval, yyvsp[-1]); }
#line 4152 "verilog_y.tab.cpp"
    break;

  case 228:
#line 1393 "parser.y"
                { init(yyval, ID_decl);
                  addswap(yyval, ID_class, yyvsp[-6]);
                  addswap(yyval, ID_type, yyvsp[-3]);
                  swapop(yyval, yyvsp[-1]); }
#line 4161 "verilog_y.tab.cpp"
    break;

  case 229:
#line 1401 "parser.y"
                { make_nil(yyval); }
#line 4167 "verilog_y.tab.cpp"
    break;

  case 230:
#line 1402 "parser.y"
                           { init(yyval, "vectored"); }
#line 4173 "verilog_y.tab.cpp"
    break;

  case 231:
#line 1403 "parser.y"
                           { init(yyval, "scalared"); }
#line 4179 "verilog_y.tab.cpp"
    break;

  case 232:
#line 1406 "parser.y"
                      { init(yyval, ID_wire); }
#line 4185 "verilog_y.tab.cpp"
    break;

  case 233:
#line 1407 "parser.y"
                      { init(yyval, ID_tri); }
#line 4191 "verilog_y.tab.cpp"
    break;

  case 234:
#line 1408 "parser.y"
                      { init(yyval, ID_tri1); }
#line 4197 "verilog_y.tab.cpp"
    break;

  case 235:
#line 1409 "parser.y"
                      { init(yyval, ID_supply0); }
#line 4203 "verilog_y.tab.cpp"
    break;

  case 236:
#line 1410 "parser.y"
                      { init(yyval, ID_wand); }
#line 4209 "verilog_y.tab.cpp"
    break;

  case 237:
#line 1411 "parser.y"
                      { init(yyval, ID_triand); }
#line 4215 "verilog_y.tab.cpp"
    break;

  case 238:
#line 1412 "parser.y"
                      { init(yyval, ID_tri0); }
#line 4221 "verilog_y.tab.cpp"
    break;

  case 239:
#line 1413 "parser.y"
                      { init(yyval, ID_supply1); }
#line 4227 "verilog_y.tab.cpp"
    break;

  case 240:
#line 1414 "parser.y"
                      { init(yyval, ID_wor); }
#line 4233 "verilog_y.tab.cpp"
    break;

  case 241:
#line 1415 "parser.y"
                      { init(yyval, ID_trior); }
#line 4239 "verilog_y.tab.cpp"
    break;

  case 242:
#line 1426 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4245 "verilog_y.tab.cpp"
    break;

  case 243:
#line 1428 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4251 "verilog_y.tab.cpp"
    break;

  case 244:
#line 1432 "parser.y"
          {
            yyval=yyvsp[-1];
            stack_expr(yyval).add(ID_type)=stack_expr(yyvsp[0]);
          }
#line 4260 "verilog_y.tab.cpp"
    break;

  case 245:
#line 1439 "parser.y"
                { new_symbol(yyval, yyvsp[0]); }
#line 4266 "verilog_y.tab.cpp"
    break;

  case 246:
#line 1444 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4272 "verilog_y.tab.cpp"
    break;

  case 247:
#line 1446 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4278 "verilog_y.tab.cpp"
    break;

  case 248:
#line 1450 "parser.y"
                { init(yyval, ID_equal); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 4284 "verilog_y.tab.cpp"
    break;

  case 249:
#line 1454 "parser.y"
                { make_nil(yyval); }
#line 4290 "verilog_y.tab.cpp"
    break;

  case 251:
#line 1458 "parser.y"
                          { yyval=yyvsp[0]; }
#line 4296 "verilog_y.tab.cpp"
    break;

  case 252:
#line 1459 "parser.y"
                                  { yyval=yyvsp[-1]; }
#line 4302 "verilog_y.tab.cpp"
    break;

  case 253:
#line 1460 "parser.y"
                                                  { yyval=yyvsp[-3]; }
#line 4308 "verilog_y.tab.cpp"
    break;

  case 254:
#line 1461 "parser.y"
                                                                  { yyval=yyvsp[-5]; }
#line 4314 "verilog_y.tab.cpp"
    break;

  case 256:
#line 1472 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_function); 
                  addswap(yyval, ID_type, yyvsp[-6]);
                  add_as_subtype(stack_type(yyvsp[-6]), stack_type(yyvsp[-7]));
                  addswap(yyval, ID_symbol, yyvsp[-5]);
		  addswap(yyval, ID_ports, yyvsp[-4]);
		  addswap(yyval, "declarations", yyvsp[-2]);
		  addswap(yyval, ID_body, yyvsp[-1]);
		}
#line 4328 "verilog_y.tab.cpp"
    break;

  case 257:
#line 1485 "parser.y"
                { make_nil(yyval); }
#line 4334 "verilog_y.tab.cpp"
    break;

  case 258:
#line 1487 "parser.y"
                { yyval = yyvsp[0]; }
#line 4340 "verilog_y.tab.cpp"
    break;

  case 260:
#line 1493 "parser.y"
                { init(yyval, ID_integer); }
#line 4346 "verilog_y.tab.cpp"
    break;

  case 261:
#line 1495 "parser.y"
                { init(yyval, ID_real); }
#line 4352 "verilog_y.tab.cpp"
    break;

  case 262:
#line 1497 "parser.y"
                { init(yyval, ID_realtime); }
#line 4358 "verilog_y.tab.cpp"
    break;

  case 263:
#line 1499 "parser.y"
                { init(yyval, ID_time); }
#line 4364 "verilog_y.tab.cpp"
    break;

  case 264:
#line 1504 "parser.y"
                { init(yyval); mts(yyval, yyvsp[0]); }
#line 4370 "verilog_y.tab.cpp"
    break;

  case 265:
#line 1506 "parser.y"
                { yyval=yyvsp[-1]; mts(yyval, yyvsp[0]); }
#line 4376 "verilog_y.tab.cpp"
    break;

  case 268:
#line 1518 "parser.y"
                { init(yyval, ID_decl);
                  stack_expr(yyval).set(ID_class, ID_task); 
		  addswap(yyval, ID_symbol, yyvsp[-5]);
		  addswap(yyval, ID_ports, yyvsp[-4]);
		  addswap(yyval, "declarations", yyvsp[-2]);
		  addswap(yyval, ID_body, yyvsp[-1]);
                }
#line 4388 "verilog_y.tab.cpp"
    break;

  case 269:
#line 1529 "parser.y"
                { init(yyval); }
#line 4394 "verilog_y.tab.cpp"
    break;

  case 270:
#line 1531 "parser.y"
                { yyval=yyvsp[-1]; mts(yyval, yyvsp[0]); }
#line 4400 "verilog_y.tab.cpp"
    break;

  case 272:
#line 1536 "parser.y"
                                                          { yyval=yyvsp[-1]; }
#line 4406 "verilog_y.tab.cpp"
    break;

  case 273:
#line 1537 "parser.y"
                                                          { yyval=yyvsp[-1]; }
#line 4412 "verilog_y.tab.cpp"
    break;

  case 274:
#line 1538 "parser.y"
                                                          { yyval=yyvsp[-1]; }
#line 4418 "verilog_y.tab.cpp"
    break;

  case 275:
#line 1542 "parser.y"
                                                         { yyval=yyvsp[0]; }
#line 4424 "verilog_y.tab.cpp"
    break;

  case 276:
#line 1543 "parser.y"
                                                         { yyval=yyvsp[0]; }
#line 4430 "verilog_y.tab.cpp"
    break;

  case 277:
#line 1544 "parser.y"
                                                         { yyval=yyvsp[0]; }
#line 4436 "verilog_y.tab.cpp"
    break;

  case 278:
#line 1546 "parser.y"
                                                         { yyval=yyvsp[0]; }
#line 4442 "verilog_y.tab.cpp"
    break;

  case 279:
#line 1548 "parser.y"
                                                         { yyval=yyvsp[0]; }
#line 4448 "verilog_y.tab.cpp"
    break;

  case 280:
#line 1554 "parser.y"
                { init(yyval, ID_verilog_attribute); }
#line 4454 "verilog_y.tab.cpp"
    break;

  case 281:
#line 1556 "parser.y"
                { yyval=yyvsp[-1];
		  Forall_irep(it, stack_expr(yyvsp[0]).get_sub())
		    stack_expr(yyval).move_to_sub(*it);
		}
#line 4463 "verilog_y.tab.cpp"
    break;

  case 282:
#line 1563 "parser.y"
                { yyval=yyvsp[-1]; }
#line 4469 "verilog_y.tab.cpp"
    break;

  case 283:
#line 1568 "parser.y"
                { init(yyval); }
#line 4475 "verilog_y.tab.cpp"
    break;

  case 284:
#line 1570 "parser.y"
                { yyval=yyvsp[-2]; mts(yyval, yyvsp[0]); }
#line 4481 "verilog_y.tab.cpp"
    break;

  case 285:
#line 1574 "parser.y"
                { init(yyval, "attribute");
		  stack_expr(yyval).add(ID_name).swap(stack_expr(yyvsp[-2]));
		  stack_expr(yyval).add(ID_value).swap(stack_expr(yyvsp[0]));
		}
#line 4490 "verilog_y.tab.cpp"
    break;

  case 286:
#line 1579 "parser.y"
                { init(yyval, "attribute"); stack_expr(yyval).add(ID_name).swap(stack_expr(yyvsp[0])); }
#line 4496 "verilog_y.tab.cpp"
    break;

  case 290:
#line 1593 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4502 "verilog_y.tab.cpp"
    break;

  case 291:
#line 1595 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4508 "verilog_y.tab.cpp"
    break;

  case 292:
#line 1604 "parser.y"
                { init(yyval, ID_inst_builtin); addswap(yyval, ID_module, yyvsp[-3]); swapop(yyval, yyvsp[-1]); }
#line 4514 "verilog_y.tab.cpp"
    break;

  case 293:
#line 1606 "parser.y"
                { init(yyval, ID_inst_builtin); addswap(yyval, ID_module, yyvsp[-4]); swapop(yyval, yyvsp[-1]); }
#line 4520 "verilog_y.tab.cpp"
    break;

  case 294:
#line 1608 "parser.y"
                { init(yyval, ID_inst_builtin); addswap(yyval, ID_module, yyvsp[-3]); swapop(yyval, yyvsp[-1]); }
#line 4526 "verilog_y.tab.cpp"
    break;

  case 295:
#line 1610 "parser.y"
                { init(yyval, ID_inst_builtin); addswap(yyval, ID_module, yyvsp[-4]); swapop(yyval, yyvsp[-1]); }
#line 4532 "verilog_y.tab.cpp"
    break;

  case 296:
#line 1612 "parser.y"
                { init(yyval, ID_inst_builtin); addswap(yyval, ID_module, yyvsp[-4]); swapop(yyval, yyvsp[-1]); }
#line 4538 "verilog_y.tab.cpp"
    break;

  case 297:
#line 1614 "parser.y"
                { init(yyval, ID_inst_builtin); addswap(yyval, ID_module, yyvsp[-3]); swapop(yyval, yyvsp[-1]); }
#line 4544 "verilog_y.tab.cpp"
    break;

  case 298:
#line 1616 "parser.y"
                { init(yyval, ID_inst_builtin); addswap(yyval, ID_module, yyvsp[-2]); swapop(yyval, yyvsp[-1]); }
#line 4550 "verilog_y.tab.cpp"
    break;

  case 299:
#line 1618 "parser.y"
                { init(yyval, ID_inst_builtin); stack_expr(yyval).set(ID_module, ID_pulldown); swapop(yyval, yyvsp[-1]); }
#line 4556 "verilog_y.tab.cpp"
    break;

  case 300:
#line 1620 "parser.y"
                { init(yyval, ID_inst_builtin); stack_expr(yyval).set(ID_module, ID_pullup);   swapop(yyval, yyvsp[-1]); }
#line 4562 "verilog_y.tab.cpp"
    break;

  case 301:
#line 1624 "parser.y"
                       { init(yyval, ID_cmos); }
#line 4568 "verilog_y.tab.cpp"
    break;

  case 302:
#line 1625 "parser.y"
                       { init(yyval, ID_rcmos); }
#line 4574 "verilog_y.tab.cpp"
    break;

  case 303:
#line 1629 "parser.y"
                       { init(yyval, ID_bufif0); }
#line 4580 "verilog_y.tab.cpp"
    break;

  case 304:
#line 1630 "parser.y"
                       { init(yyval, ID_bufif1); }
#line 4586 "verilog_y.tab.cpp"
    break;

  case 305:
#line 1631 "parser.y"
                       { init(yyval, ID_notif0); }
#line 4592 "verilog_y.tab.cpp"
    break;

  case 306:
#line 1632 "parser.y"
                       { init(yyval, ID_notif1); }
#line 4598 "verilog_y.tab.cpp"
    break;

  case 307:
#line 1636 "parser.y"
                       { init(yyval, ID_nmos); }
#line 4604 "verilog_y.tab.cpp"
    break;

  case 308:
#line 1637 "parser.y"
                       { init(yyval, ID_pmos); }
#line 4610 "verilog_y.tab.cpp"
    break;

  case 309:
#line 1638 "parser.y"
                       { init(yyval, ID_rnmos); }
#line 4616 "verilog_y.tab.cpp"
    break;

  case 310:
#line 1639 "parser.y"
                       { init(yyval, ID_rpmos); }
#line 4622 "verilog_y.tab.cpp"
    break;

  case 311:
#line 1643 "parser.y"
                       { init(yyval, ID_and); }
#line 4628 "verilog_y.tab.cpp"
    break;

  case 312:
#line 1644 "parser.y"
                       { init(yyval, ID_nand); }
#line 4634 "verilog_y.tab.cpp"
    break;

  case 313:
#line 1645 "parser.y"
                       { init(yyval, ID_nor); }
#line 4640 "verilog_y.tab.cpp"
    break;

  case 314:
#line 1646 "parser.y"
                       { init(yyval, ID_or); }
#line 4646 "verilog_y.tab.cpp"
    break;

  case 315:
#line 1647 "parser.y"
                       { init(yyval, ID_nor); }
#line 4652 "verilog_y.tab.cpp"
    break;

  case 316:
#line 1648 "parser.y"
                       { init(yyval, ID_xor); }
#line 4658 "verilog_y.tab.cpp"
    break;

  case 317:
#line 1652 "parser.y"
                       { init(yyval, ID_buf); }
#line 4664 "verilog_y.tab.cpp"
    break;

  case 318:
#line 1653 "parser.y"
                       { init(yyval, ID_not); }
#line 4670 "verilog_y.tab.cpp"
    break;

  case 319:
#line 1657 "parser.y"
                       { init(yyval, "rtran"); }
#line 4676 "verilog_y.tab.cpp"
    break;

  case 320:
#line 1658 "parser.y"
                       { init(yyval, "rtranif0"); }
#line 4682 "verilog_y.tab.cpp"
    break;

  case 321:
#line 1659 "parser.y"
                       { init(yyval, "rtranif0"); }
#line 4688 "verilog_y.tab.cpp"
    break;

  case 322:
#line 1660 "parser.y"
                       { init(yyval, "rtranif1"); }
#line 4694 "verilog_y.tab.cpp"
    break;

  case 323:
#line 1664 "parser.y"
                       { init(yyval, "tranif0"); }
#line 4700 "verilog_y.tab.cpp"
    break;

  case 324:
#line 1665 "parser.y"
                       { init(yyval, "tranif1"); }
#line 4706 "verilog_y.tab.cpp"
    break;

  case 325:
#line 1670 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4712 "verilog_y.tab.cpp"
    break;

  case 326:
#line 1672 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4718 "verilog_y.tab.cpp"
    break;

  case 327:
#line 1677 "parser.y"
                { init(yyval, ID_inst); addswap(yyval, ID_instance, yyvsp[-4]);
                  swapop(yyval, yyvsp[-1]);
                  addswap(yyval, ID_range, yyvsp[-3]);
                }
#line 4727 "verilog_y.tab.cpp"
    break;

  case 328:
#line 1685 "parser.y"
                { init(yyval, "$_&#ANON" + PARSER.get_dummy_id()); }
#line 4733 "verilog_y.tab.cpp"
    break;

  case 331:
#line 1697 "parser.y"
                { init(yyval, ID_inst);
                  addswap(yyval, ID_module, yyvsp[-3]);
		  addswap(yyval, ID_parameter_assignments, yyvsp[-2]);
                  swapop(yyval, yyvsp[-1]); }
#line 4742 "verilog_y.tab.cpp"
    break;

  case 332:
#line 1705 "parser.y"
                { make_nil(yyval); }
#line 4748 "verilog_y.tab.cpp"
    break;

  case 333:
#line 1707 "parser.y"
                { yyval = yyvsp[-1]; }
#line 4754 "verilog_y.tab.cpp"
    break;

  case 336:
#line 1717 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4760 "verilog_y.tab.cpp"
    break;

  case 337:
#line 1719 "parser.y"
                { yyval=yyvsp[-2]; mto(yyval, yyvsp[0]); }
#line 4766 "verilog_y.tab.cpp"
    break;

  case 338:
#line 1724 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4772 "verilog_y.tab.cpp"
    break;

  case 339:
#line 1726 "parser.y"
                { yyval=yyvsp[-2]; mto(yyval, yyvsp[0]); }
#line 4778 "verilog_y.tab.cpp"
    break;

  case 341:
#line 1734 "parser.y"
                { init(yyval, ID_named_parameter_assignment);
	  	  stack_expr(yyval).add(ID_parameter).swap(stack_expr(yyvsp[-3]));
	  	  stack_expr(yyval).add(ID_value).swap(stack_expr(yyvsp[-1]));
	  	}
#line 4787 "verilog_y.tab.cpp"
    break;

  case 343:
#line 1744 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4793 "verilog_y.tab.cpp"
    break;

  case 344:
#line 1746 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4799 "verilog_y.tab.cpp"
    break;

  case 345:
#line 1751 "parser.y"
                { init(yyval, ID_inst); addswap(yyval, ID_instance, yyvsp[-3]); swapop(yyval, yyvsp[-1]); }
#line 4805 "verilog_y.tab.cpp"
    break;

  case 346:
#line 1754 "parser.y"
                  { init(yyval, "$_&#ANON" + PARSER.get_dummy_id());}
#line 4811 "verilog_y.tab.cpp"
    break;

  case 351:
#line 1771 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4817 "verilog_y.tab.cpp"
    break;

  case 352:
#line 1773 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4823 "verilog_y.tab.cpp"
    break;

  case 354:
#line 1782 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4829 "verilog_y.tab.cpp"
    break;

  case 355:
#line 1784 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4835 "verilog_y.tab.cpp"
    break;

  case 356:
#line 1789 "parser.y"
                { init(yyval, ID_named_port_connection);
                  mto(yyval, yyvsp[-3]);
                  mto(yyval, yyvsp[-1]); }
#line 4843 "verilog_y.tab.cpp"
    break;

  case 357:
#line 1800 "parser.y"
                { init(yyval, ID_continuous_assign); swapop(yyval, yyvsp[-1]); }
#line 4849 "verilog_y.tab.cpp"
    break;

  case 358:
#line 1805 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 4855 "verilog_y.tab.cpp"
    break;

  case 359:
#line 1807 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 4861 "verilog_y.tab.cpp"
    break;

  case 360:
#line 1811 "parser.y"
                { init(yyval, ID_equal); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 4867 "verilog_y.tab.cpp"
    break;

  case 362:
#line 1817 "parser.y"
                { init(yyval, ID_initial); mto(yyval, yyvsp[0]); }
#line 4873 "verilog_y.tab.cpp"
    break;

  case 363:
#line 1821 "parser.y"
                { init(yyval, ID_always); mto(yyval, yyvsp[0]); }
#line 4879 "verilog_y.tab.cpp"
    break;

  case 364:
#line 1829 "parser.y"
                { yyval=yyvsp[0]; }
#line 4885 "verilog_y.tab.cpp"
    break;

  case 371:
#line 1839 "parser.y"
                                  { yyval = yyvsp[-1]; }
#line 4891 "verilog_y.tab.cpp"
    break;

  case 372:
#line 1840 "parser.y"
                                     { yyval = yyvsp[-1]; }
#line 4897 "verilog_y.tab.cpp"
    break;

  case 387:
#line 1859 "parser.y"
                { yyval=yyvsp[-1]; }
#line 4903 "verilog_y.tab.cpp"
    break;

  case 390:
#line 1869 "parser.y"
                { init(yyval, ID_function_call);
		  stack_expr(yyval).operands().reserve(2);
		  mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[-1]); }
#line 4911 "verilog_y.tab.cpp"
    break;

  case 391:
#line 1876 "parser.y"
                { init(yyval, ID_function_call);
		  stack_expr(yyval).operands().resize(2);
		  stack_expr(yyval).operands()[0].swap(stack_expr(yyvsp[0])); }
#line 4919 "verilog_y.tab.cpp"
    break;

  case 392:
#line 1880 "parser.y"
                { init(yyval, ID_function_call);
		  stack_expr(yyval).operands().reserve(2);
		  mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[-1]); }
#line 4927 "verilog_y.tab.cpp"
    break;

  case 394:
#line 1888 "parser.y"
                                       { init(yyval, ID_skip); }
#line 4933 "verilog_y.tab.cpp"
    break;

  case 397:
#line 1898 "parser.y"
                { init(yyval, ID_fork); swapop(yyval, yyvsp[-1]); }
#line 4939 "verilog_y.tab.cpp"
    break;

  case 398:
#line 1901 "parser.y"
                { init(yyval, ID_block);
                  swapop(yyval, yyvsp[-1]);
                  addswap(yyval, ID_identifier, yyvsp[-2]); }
#line 4947 "verilog_y.tab.cpp"
    break;

  case 399:
#line 1908 "parser.y"
                { init(yyval, ID_disable); mto(yyval, yyvsp[-1]); }
#line 4953 "verilog_y.tab.cpp"
    break;

  case 400:
#line 1913 "parser.y"
                { init(yyval, ID_assert); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 4959 "verilog_y.tab.cpp"
    break;

  case 401:
#line 1916 "parser.y"
                { init(yyval, ID_assert); stack_expr(yyval).operands().resize(2);
		  stack_expr(yyval).op0().swap(stack_expr(yyvsp[-1])); stack_expr(yyval).op1().make_nil();
		  stack_expr(yyval).set(ID_identifier, stack_expr(yyvsp[-3]).id());
		}
#line 4968 "verilog_y.tab.cpp"
    break;

  case 402:
#line 1924 "parser.y"
                { init(yyval, ID_assume); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 4974 "verilog_y.tab.cpp"
    break;

  case 403:
#line 1927 "parser.y"
                { init(yyval, ID_assume); stack_expr(yyval).operands().resize(2);
		  stack_expr(yyval).op0().swap(stack_expr(yyvsp[-1])); stack_expr(yyval).op1().make_nil();
		  stack_expr(yyval).set(ID_identifier, stack_expr(yyvsp[-3]).id());
		}
#line 4983 "verilog_y.tab.cpp"
    break;

  case 405:
#line 1936 "parser.y"
                { init(yyval, ID_cover); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 4989 "verilog_y.tab.cpp"
    break;

  case 407:
#line 1942 "parser.y"
                { init(yyval, "action-else"); stack_expr(yyval).operands().resize(2);
                  stack_expr(yyval).op0().swap(stack_expr(yyvsp[-3])); stack_expr(yyval).op1().swap(stack_expr(yyvsp[-1])); }
#line 4996 "verilog_y.tab.cpp"
    break;

  case 409:
#line 1949 "parser.y"
                { 
		  yyval=yyvsp[0];
		  stack_expr(yyval).set(ID_identifier, stack_expr(yyvsp[-2]).id());
		}
#line 5005 "verilog_y.tab.cpp"
    break;

  case 411:
#line 1958 "parser.y"
                { 
		  yyval=yyvsp[0];
		  stack_expr(yyval).set(ID_identifier, stack_expr(yyvsp[-2]).id());
		}
#line 5014 "verilog_y.tab.cpp"
    break;

  case 413:
#line 1966 "parser.y"
                { 
		  yyval=yyvsp[0];
		  stack_expr(yyval).set(ID_identifier, stack_expr(yyvsp[-2]).id());
		}
#line 5023 "verilog_y.tab.cpp"
    break;

  case 414:
#line 1973 "parser.y"
                { init(yyval, ID_assert); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5029 "verilog_y.tab.cpp"
    break;

  case 417:
#line 1981 "parser.y"
                { init(yyval, ID_wait); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5035 "verilog_y.tab.cpp"
    break;

  case 418:
#line 1986 "parser.y"
                { init(yyval, ID_continuous_assign); mto(yyval, yyvsp[0]); }
#line 5041 "verilog_y.tab.cpp"
    break;

  case 419:
#line 1988 "parser.y"
                { init(yyval, ID_deassign); mto(yyval, yyvsp[0]); }
#line 5047 "verilog_y.tab.cpp"
    break;

  case 420:
#line 1990 "parser.y"
                { init(yyval, ID_force); swapop(yyval, yyvsp[0]); }
#line 5053 "verilog_y.tab.cpp"
    break;

  case 421:
#line 1993 "parser.y"
                { init(yyval, ID_release); mto(yyval, yyvsp[0]); }
#line 5059 "verilog_y.tab.cpp"
    break;

  case 422:
#line 1999 "parser.y"
                { init(yyval, ID_blocking_assign); mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[0]); }
#line 5065 "verilog_y.tab.cpp"
    break;

  case 424:
#line 2005 "parser.y"
                { init(yyval, ID_blocking_assign); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5071 "verilog_y.tab.cpp"
    break;

  case 438:
#line 2026 "parser.y"
                { init(yyval, ID_non_blocking_assign); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5077 "verilog_y.tab.cpp"
    break;

  case 439:
#line 2028 "parser.y"
                { init(yyval, ID_non_blocking_assign); mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[0]); }
#line 5083 "verilog_y.tab.cpp"
    break;

  case 440:
#line 2033 "parser.y"
                { yyval=yyvsp[-1]; mto(yyval, yyvsp[0]); }
#line 5089 "verilog_y.tab.cpp"
    break;

  case 444:
#line 2044 "parser.y"
                { init(yyval, ID_verilog_cycle_delay); mto(yyval, yyvsp[0]); }
#line 5095 "verilog_y.tab.cpp"
    break;

  case 445:
#line 2046 "parser.y"
                { init(yyval, ID_verilog_cycle_delay); mto(yyval, yyvsp[0]); }
#line 5101 "verilog_y.tab.cpp"
    break;

  case 446:
#line 2048 "parser.y"
                { init(yyval, ID_verilog_cycle_delay); mto(yyval, yyvsp[-1]); }
#line 5107 "verilog_y.tab.cpp"
    break;

  case 449:
#line 2055 "parser.y"
                { init(yyval, ID_repeat); }
#line 5113 "verilog_y.tab.cpp"
    break;

  case 450:
#line 2060 "parser.y"
                { init(yyval, ID_delay); mto(yyval, yyvsp[0]); }
#line 5119 "verilog_y.tab.cpp"
    break;

  case 451:
#line 2064 "parser.y"
                { init(yyval, ID_delay); mto(yyval, yyvsp[-2]); }
#line 5125 "verilog_y.tab.cpp"
    break;

  case 452:
#line 2069 "parser.y"
                { init(yyval, ID_event_guard); mto(yyval, yyvsp[0]); }
#line 5131 "verilog_y.tab.cpp"
    break;

  case 453:
#line 2071 "parser.y"
                { init(yyval, ID_event_guard); mto(yyval, yyvsp[-1]); }
#line 5137 "verilog_y.tab.cpp"
    break;

  case 454:
#line 2073 "parser.y"
                { init(yyval, ID_event_guard);
		  stack_expr(yyval).operands().resize(1);
	          stack_expr(yyval).op0().id(ID_verilog_star_event); }
#line 5145 "verilog_y.tab.cpp"
    break;

  case 455:
#line 2077 "parser.y"
                { init(yyval, ID_event_guard);
		  stack_expr(yyval).operands().resize(1);
	          stack_expr(yyval).op0().id(ID_verilog_star_event); }
#line 5153 "verilog_y.tab.cpp"
    break;

  case 456:
#line 2081 "parser.y"
                { init(yyval, ID_event_guard);
		  stack_expr(yyval).operands().resize(1);
	          stack_expr(yyval).op0().id(ID_verilog_star_event); }
#line 5161 "verilog_y.tab.cpp"
    break;

  case 457:
#line 2088 "parser.y"
                { new_symbol(yyval, yyvsp[0]); }
#line 5167 "verilog_y.tab.cpp"
    break;

  case 458:
#line 2093 "parser.y"
                { init(yyval, ID_event); mto(yyval, yyvsp[0]); }
#line 5173 "verilog_y.tab.cpp"
    break;

  case 459:
#line 2095 "parser.y"
                { yyval=yyvsp[-2]; mto(yyval, yyvsp[0]); }
#line 5179 "verilog_y.tab.cpp"
    break;

  case 460:
#line 2097 "parser.y"
                { yyval=yyvsp[-2]; mto(yyval, yyvsp[0]); }
#line 5185 "verilog_y.tab.cpp"
    break;

  case 461:
#line 2102 "parser.y"
                { yyval=yyvsp[0]; }
#line 5191 "verilog_y.tab.cpp"
    break;

  case 462:
#line 2104 "parser.y"
                { init(yyval, ID_posedge); mto(yyval, yyvsp[0]); }
#line 5197 "verilog_y.tab.cpp"
    break;

  case 463:
#line 2106 "parser.y"
                { init(yyval, ID_negedge); mto(yyval, yyvsp[0]); }
#line 5203 "verilog_y.tab.cpp"
    break;

  case 464:
#line 2111 "parser.y"
                { init(yyval, ID_if); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5209 "verilog_y.tab.cpp"
    break;

  case 465:
#line 2113 "parser.y"
                { init(yyval, ID_if); mto(yyval, yyvsp[-4]); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5215 "verilog_y.tab.cpp"
    break;

  case 466:
#line 2118 "parser.y"
                { init(yyval, ID_case);  mto(yyval, yyvsp[-3]);
                  Forall_operands(it, stack_expr(yyvsp[-1])) stack_expr(yyval).move_to_operands(*it); }
#line 5222 "verilog_y.tab.cpp"
    break;

  case 467:
#line 2121 "parser.y"
                { init(yyval, ID_casex); mto(yyval, yyvsp[-3]);
                  Forall_operands(it, stack_expr(yyvsp[-1])) stack_expr(yyval).move_to_operands(*it); }
#line 5229 "verilog_y.tab.cpp"
    break;

  case 468:
#line 2124 "parser.y"
                { init(yyval, ID_casez); mto(yyval, yyvsp[-3]);
                  Forall_operands(it, stack_expr(yyvsp[-1])) stack_expr(yyval).move_to_operands(*it); }
#line 5236 "verilog_y.tab.cpp"
    break;

  case 469:
#line 2130 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 5242 "verilog_y.tab.cpp"
    break;

  case 470:
#line 2132 "parser.y"
                { yyval=yyvsp[-1]; mto(yyval, yyvsp[0]); }
#line 5248 "verilog_y.tab.cpp"
    break;

  case 471:
#line 2137 "parser.y"
                { init(yyval, ID_case_item); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5254 "verilog_y.tab.cpp"
    break;

  case 472:
#line 2139 "parser.y"
                { init(yyval, ID_case_item);
                  stack_expr(yyval).operands().resize(1);
                  stack_expr(yyval).op0().id(ID_default);
                  mto(yyval, yyvsp[0]); }
#line 5263 "verilog_y.tab.cpp"
    break;

  case 473:
#line 2144 "parser.y"
                { init(yyval, ID_case_item);
                  stack_expr(yyval).operands().resize(1);
                  stack_expr(yyval).op0().id(ID_default);
                  mto(yyval, yyvsp[0]); }
#line 5272 "verilog_y.tab.cpp"
    break;

  case 474:
#line 2152 "parser.y"
                { init(yyval, ID_forever); mto(yyval, yyvsp[0]); }
#line 5278 "verilog_y.tab.cpp"
    break;

  case 475:
#line 2154 "parser.y"
                { init(yyval, ID_repeat); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5284 "verilog_y.tab.cpp"
    break;

  case 476:
#line 2156 "parser.y"
                { init(yyval, ID_while); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5290 "verilog_y.tab.cpp"
    break;

  case 477:
#line 2158 "parser.y"
                { init(yyval, ID_for); mto(yyval, yyvsp[-6]); mto(yyval, yyvsp[-4]); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5296 "verilog_y.tab.cpp"
    break;

  case 482:
#line 2174 "parser.y"
                { init(yyval, ID_block); swapop(yyval, yyvsp[-1]); }
#line 5302 "verilog_y.tab.cpp"
    break;

  case 483:
#line 2177 "parser.y"
                { init(yyval, ID_block);
                  swapop(yyval, yyvsp[-1]);
                  addswap(yyval, ID_identifier, yyvsp[-2]); }
#line 5310 "verilog_y.tab.cpp"
    break;

  case 485:
#line 2200 "parser.y"
                { init(yyval); }
#line 5316 "verilog_y.tab.cpp"
    break;

  case 486:
#line 2202 "parser.y"
                { yyval=yyvsp[-1]; mto(yyval, yyvsp[0]); }
#line 5322 "verilog_y.tab.cpp"
    break;

  case 488:
#line 2209 "parser.y"
                { init(yyval, ID_symbol);
                  stack_expr(yyval).set(ID_identifier, stack_expr(yyvsp[0]).id());
                }
#line 5330 "verilog_y.tab.cpp"
    break;

  case 491:
#line 2223 "parser.y"
                { extractbits(yyval, yyvsp[-1], yyvsp[0]); }
#line 5336 "verilog_y.tab.cpp"
    break;

  case 492:
#line 2225 "parser.y"
                { extractbits(yyval, yyvsp[-1], yyvsp[0]); }
#line 5342 "verilog_y.tab.cpp"
    break;

  case 495:
#line 2244 "parser.y"
                { extractbit(yyval, yyvsp[-1], yyvsp[0]); }
#line 5348 "verilog_y.tab.cpp"
    break;

  case 497:
#line 2250 "parser.y"
                { new_symbol(yyval, yyvsp[0]); }
#line 5354 "verilog_y.tab.cpp"
    break;

  case 500:
#line 2258 "parser.y"
                { init(yyval, "mintypmax"); mto(yyval, yyvsp[-4]); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5360 "verilog_y.tab.cpp"
    break;

  case 501:
#line 2263 "parser.y"
          { make_nil(yyval); }
#line 5366 "verilog_y.tab.cpp"
    break;

  case 503:
#line 2269 "parser.y"
                { init(yyval); mto(yyval, yyvsp[0]); }
#line 5372 "verilog_y.tab.cpp"
    break;

  case 504:
#line 2271 "parser.y"
                { yyval=yyvsp[-2];    mto(yyval, yyvsp[0]); }
#line 5378 "verilog_y.tab.cpp"
    break;

  case 506:
#line 2277 "parser.y"
                { yyval=yyvsp[-2]; mto(yyval, yyvsp[0]); }
#line 5384 "verilog_y.tab.cpp"
    break;

  case 508:
#line 2280 "parser.y"
                { init(yyval, ID_plus); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5390 "verilog_y.tab.cpp"
    break;

  case 509:
#line 2282 "parser.y"
                { init(yyval, ID_minus); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5396 "verilog_y.tab.cpp"
    break;

  case 510:
#line 2284 "parser.y"
                { init(yyval, ID_unary_plus); mto(yyval, yyvsp[0]); }
#line 5402 "verilog_y.tab.cpp"
    break;

  case 511:
#line 2286 "parser.y"
                { init(yyval, ID_unary_minus); mto(yyval, yyvsp[0]); }
#line 5408 "verilog_y.tab.cpp"
    break;

  case 512:
#line 2288 "parser.y"
                { init(yyval, ID_mult); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5414 "verilog_y.tab.cpp"
    break;

  case 513:
#line 2290 "parser.y"
                { init(yyval, ID_div); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5420 "verilog_y.tab.cpp"
    break;

  case 514:
#line 2292 "parser.y"
                { init(yyval, ID_mod); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5426 "verilog_y.tab.cpp"
    break;

  case 515:
#line 2294 "parser.y"
                { init(yyval, ID_equal); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5432 "verilog_y.tab.cpp"
    break;

  case 516:
#line 2296 "parser.y"
                { init(yyval, ID_notequal); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5438 "verilog_y.tab.cpp"
    break;

  case 517:
#line 2298 "parser.y"
                { init(yyval, ID_verilog_case_equality); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5444 "verilog_y.tab.cpp"
    break;

  case 518:
#line 2300 "parser.y"
                { init(yyval, ID_verilog_case_inequality); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5450 "verilog_y.tab.cpp"
    break;

  case 519:
#line 2302 "parser.y"
                { init(yyval, ID_and); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5456 "verilog_y.tab.cpp"
    break;

  case 520:
#line 2304 "parser.y"
                { init(yyval, ID_power); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5462 "verilog_y.tab.cpp"
    break;

  case 521:
#line 2306 "parser.y"
                { init(yyval, ID_or); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5468 "verilog_y.tab.cpp"
    break;

  case 522:
#line 2308 "parser.y"
                { init(yyval, ID_lt); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5474 "verilog_y.tab.cpp"
    break;

  case 523:
#line 2310 "parser.y"
                { init(yyval, ID_le); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5480 "verilog_y.tab.cpp"
    break;

  case 524:
#line 2312 "parser.y"
                { init(yyval, ID_gt); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5486 "verilog_y.tab.cpp"
    break;

  case 525:
#line 2314 "parser.y"
                { init(yyval, ID_ge); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5492 "verilog_y.tab.cpp"
    break;

  case 526:
#line 2316 "parser.y"
                { init(yyval, ID_bitand); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5498 "verilog_y.tab.cpp"
    break;

  case 527:
#line 2318 "parser.y"
                { init(yyval, ID_bitor); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5504 "verilog_y.tab.cpp"
    break;

  case 528:
#line 2320 "parser.y"
                { init(yyval, ID_bitxor); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5510 "verilog_y.tab.cpp"
    break;

  case 529:
#line 2322 "parser.y"
                { init(yyval, ID_bitxnor); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5516 "verilog_y.tab.cpp"
    break;

  case 530:
#line 2324 "parser.y"
                { init(yyval, ID_shl); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5522 "verilog_y.tab.cpp"
    break;

  case 531:
#line 2326 "parser.y"
                { init(yyval, ID_shl); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5528 "verilog_y.tab.cpp"
    break;

  case 532:
#line 2328 "parser.y"
                { init(yyval, ID_lshr); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5534 "verilog_y.tab.cpp"
    break;

  case 533:
#line 2333 "parser.y"
                { init(yyval, ID_shr); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5540 "verilog_y.tab.cpp"
    break;

  case 534:
#line 2335 "parser.y"
                { init(yyval, ID_if); mto(yyval, yyvsp[-4]); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5546 "verilog_y.tab.cpp"
    break;

  case 535:
#line 2337 "parser.y"
                { init(yyval, ID_constant); stack_expr(yyval).type()=typet(ID_string); addswap(yyval, ID_value, yyvsp[0]); }
#line 5552 "verilog_y.tab.cpp"
    break;

  case 537:
#line 2343 "parser.y"
                              { init(yyval, ID_not); mto(yyval, yyvsp[0]); }
#line 5558 "verilog_y.tab.cpp"
    break;

  case 538:
#line 2344 "parser.y"
                                           { init(yyval, ID_or); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5564 "verilog_y.tab.cpp"
    break;

  case 539:
#line 2345 "parser.y"
                                            { init(yyval, ID_and); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5570 "verilog_y.tab.cpp"
    break;

  case 540:
#line 2346 "parser.y"
                                            { init(yyval, ID_sva_overlapped_implication); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5576 "verilog_y.tab.cpp"
    break;

  case 541:
#line 2347 "parser.y"
                                            { init(yyval, ID_sva_non_overlapped_implication); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5582 "verilog_y.tab.cpp"
    break;

  case 542:
#line 2349 "parser.y"
                { yyval=yyvsp[-1]; }
#line 5588 "verilog_y.tab.cpp"
    break;

  case 543:
#line 2350 "parser.y"
                                         { init(yyval, "sva_always"); mto(yyval, yyvsp[0]); }
#line 5594 "verilog_y.tab.cpp"
    break;

  case 544:
#line 2351 "parser.y"
                                         { init(yyval, "sva_eventually"); mto(yyval, yyvsp[0]); }
#line 5600 "verilog_y.tab.cpp"
    break;

  case 545:
#line 2352 "parser.y"
                                         { init(yyval, "sva_nexttime"); mto(yyval, yyvsp[0]); }
#line 5606 "verilog_y.tab.cpp"
    break;

  case 546:
#line 2353 "parser.y"
                                         { init(yyval, "sva_s_always"); mto(yyval, yyvsp[0]); }
#line 5612 "verilog_y.tab.cpp"
    break;

  case 547:
#line 2354 "parser.y"
                                         { init(yyval, "sva_s_eventually"); mto(yyval, yyvsp[0]); }
#line 5618 "verilog_y.tab.cpp"
    break;

  case 548:
#line 2355 "parser.y"
                                         { init(yyval, "sva_s_nexttime"); mto(yyval, yyvsp[0]); }
#line 5624 "verilog_y.tab.cpp"
    break;

  case 549:
#line 2356 "parser.y"
                                                       { init(yyval, "sva_s_until"); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5630 "verilog_y.tab.cpp"
    break;

  case 550:
#line 2357 "parser.y"
                                                       { init(yyval, "sva_s_until_with"); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5636 "verilog_y.tab.cpp"
    break;

  case 551:
#line 2358 "parser.y"
                                                       { init(yyval, "sva_until"); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5642 "verilog_y.tab.cpp"
    break;

  case 552:
#line 2359 "parser.y"
                                                       { init(yyval, "sva_until_with"); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5648 "verilog_y.tab.cpp"
    break;

  case 554:
#line 2365 "parser.y"
                { yyval=yyvsp[-1]; mto(yyval, yyvsp[0]); }
#line 5654 "verilog_y.tab.cpp"
    break;

  case 555:
#line 2367 "parser.y"
                { init(yyval, ID_sva_sequence_concatenation); mto(yyval, yyvsp[-2]); mto(yyvsp[-1], yyvsp[0]); mto(yyval, yyvsp[-1]); }
#line 5660 "verilog_y.tab.cpp"
    break;

  case 556:
#line 2369 "parser.y"
                { init(yyval, ID_sva_sequence_first_match); mto(yyval, yyvsp[-1]); }
#line 5666 "verilog_y.tab.cpp"
    break;

  case 557:
#line 2371 "parser.y"
                { init(yyval, ID_sva_sequence_throughout); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[0]); }
#line 5672 "verilog_y.tab.cpp"
    break;

  case 558:
#line 2376 "parser.y"
                { init(yyval, ID_sva_cycle_delay); mto(yyval, yyvsp[0]); stack_expr(yyval).operands().push_back(nil_exprt()); }
#line 5678 "verilog_y.tab.cpp"
    break;

  case 559:
#line 2378 "parser.y"
                { init(yyval, ID_sva_cycle_delay); mto(yyval, yyvsp[-3]); mto(yyval, yyvsp[-1]); }
#line 5684 "verilog_y.tab.cpp"
    break;

  case 560:
#line 2380 "parser.y"
                { init(yyval, ID_sva_cycle_delay); mto(yyval, yyvsp[-3]); stack_expr(yyval).copy_to_operands(exprt(ID_infinity)); }
#line 5690 "verilog_y.tab.cpp"
    break;

  case 561:
#line 2384 "parser.y"
                           { init(yyval, ID_bitnot); }
#line 5696 "verilog_y.tab.cpp"
    break;

  case 562:
#line 2385 "parser.y"
                           { init(yyval, ID_not); }
#line 5702 "verilog_y.tab.cpp"
    break;

  case 563:
#line 2386 "parser.y"
                           { init(yyval, ID_reduction_and); }
#line 5708 "verilog_y.tab.cpp"
    break;

  case 564:
#line 2387 "parser.y"
                           { init(yyval, ID_reduction_nand); }
#line 5714 "verilog_y.tab.cpp"
    break;

  case 565:
#line 2388 "parser.y"
                           { init(yyval, ID_reduction_or); }
#line 5720 "verilog_y.tab.cpp"
    break;

  case 566:
#line 2389 "parser.y"
                           { init(yyval, ID_reduction_nor); }
#line 5726 "verilog_y.tab.cpp"
    break;

  case 567:
#line 2390 "parser.y"
                           { init(yyval, ID_reduction_xor); }
#line 5732 "verilog_y.tab.cpp"
    break;

  case 568:
#line 2391 "parser.y"
                           { init(yyval, ID_reduction_xnor); }
#line 5738 "verilog_y.tab.cpp"
    break;

  case 569:
#line 2392 "parser.y"
                           { init(yyval, ID_reduction_xnor); }
#line 5744 "verilog_y.tab.cpp"
    break;

  case 570:
#line 2397 "parser.y"
                { init(yyval, ID_preincrement); mto(yyval, yyvsp[0]); }
#line 5750 "verilog_y.tab.cpp"
    break;

  case 571:
#line 2399 "parser.y"
                { init(yyval, ID_predecrement); mto(yyval, yyvsp[0]); }
#line 5756 "verilog_y.tab.cpp"
    break;

  case 572:
#line 2401 "parser.y"
                { init(yyval, ID_postincrement); mto(yyval, yyvsp[-2]); }
#line 5762 "verilog_y.tab.cpp"
    break;

  case 573:
#line 2403 "parser.y"
                { init(yyval, ID_postdecrement); mto(yyval, yyvsp[-2]); }
#line 5768 "verilog_y.tab.cpp"
    break;

  case 576:
#line 2409 "parser.y"
                { extractbits(yyval, yyvsp[-1], yyvsp[0]); }
#line 5774 "verilog_y.tab.cpp"
    break;

  case 577:
#line 2411 "parser.y"
                { extractbits(yyval, yyvsp[-1], yyvsp[0]); }
#line 5780 "verilog_y.tab.cpp"
    break;

  case 581:
#line 2416 "parser.y"
                { yyval = yyvsp[-1]; }
#line 5786 "verilog_y.tab.cpp"
    break;

  case 582:
#line 2417 "parser.y"
                   { init(yyval, ID_NULL); }
#line 5792 "verilog_y.tab.cpp"
    break;

  case 584:
#line 2425 "parser.y"
                { init(yyval, ID_constant); addswap(yyval, ID_value, yyvsp[0]); }
#line 5798 "verilog_y.tab.cpp"
    break;

  case 585:
#line 2429 "parser.y"
                { init(yyval, ID_concatenation); swapop(yyval, yyvsp[-1]); }
#line 5804 "verilog_y.tab.cpp"
    break;

  case 586:
#line 2434 "parser.y"
                { init(yyval, ID_replication); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[-1]); }
#line 5810 "verilog_y.tab.cpp"
    break;

  case 587:
#line 2436 "parser.y"
                { init(yyval, ID_replication); mto(yyval, yyvsp[-2]); mto(yyval, yyvsp[-1]); }
#line 5816 "verilog_y.tab.cpp"
    break;

  case 592:
#line 2462 "parser.y"
                { init(yyval, ID_hierarchical_identifier);
		  stack_expr(yyval).reserve_operands(2);
		  mto(yyval, yyvsp[-2]);
		  mto(yyval, yyvsp[0]);
		}
#line 5826 "verilog_y.tab.cpp"
    break;

  case 593:
#line 2470 "parser.y"
                { new_symbol(yyval, yyvsp[0]); }
#line 5832 "verilog_y.tab.cpp"
    break;

  case 594:
#line 2474 "parser.y"
                         { make_nil(yyval); }
#line 5838 "verilog_y.tab.cpp"
    break;

  case 595:
#line 2487 "parser.y"
                         { make_nil(yyval); }
#line 5844 "verilog_y.tab.cpp"
    break;

  case 596:
#line 2500 "parser.y"
                         { make_nil(yyval); }
#line 5850 "verilog_y.tab.cpp"
    break;


#line 5854 "verilog_y.tab.cpp"

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
#line 2632 "parser.y"

