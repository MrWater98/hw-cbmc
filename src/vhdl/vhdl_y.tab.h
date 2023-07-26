/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
