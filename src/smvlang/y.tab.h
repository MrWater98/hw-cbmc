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
