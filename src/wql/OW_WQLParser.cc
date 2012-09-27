/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse owwqlparse
#define yylex   owwqllex
#define yyerror owwqlerror
#define yylval  owwqllval
#define yychar  owwqlchar
#define yydebug owwqldebug
#define yynerrs owwqlnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ALL = 258,
     AND = 259,
     AS = 260,
     ASC = 261,
     ASTERISK = 262,
     AT = 263,
     BITAND = 264,
     BITCONST = 265,
     BITINVERT = 266,
     BITOR = 267,
     BITSHIFTLEFT = 268,
     BITSHIFTRIGHT = 269,
     BY = 270,
     COLON = 271,
     COMMA = 272,
     CONCATENATION = 273,
     CROSS = 274,
     CURRENTDATE = 275,
     CURRENTTIME = 276,
     CURRENTTIMESTAMP = 277,
     CURRENTUSER = 278,
     DAYP = 279,
     DEFAULT = 280,
     DELETE = 281,
     DESC = 282,
     DISTINCT = 283,
     EQUALS = 284,
     ESCAPE = 285,
     EXTRACT = 286,
     FALSEP = 287,
     FCONST = 288,
     FOR = 289,
     FROM = 290,
     FULL = 291,
     GREATERTHAN = 292,
     GREATERTHANOREQUALS = 293,
     GROUP = 294,
     HAVING = 295,
     HEXCONST = 296,
     HOURP = 297,
     ICONST = 298,
     IDENT = 299,
     IN = 300,
     INNERP = 301,
     INSERT = 302,
     INTERVAL = 303,
     INTO = 304,
     IS = 305,
     ISA = 306,
     ISNULL = 307,
     JOIN = 308,
     LEADING = 309,
     LEFT = 310,
     LEFTBRACKET = 311,
     LEFTPAREN = 312,
     LESSTHAN = 313,
     LESSTHANOREQUALS = 314,
     LIKE = 315,
     MINUS = 316,
     MINUTEP = 317,
     MONTHP = 318,
     NATIONAL = 319,
     NATURAL = 320,
     NOT = 321,
     NOTEQUALS = 322,
     NOTNULL = 323,
     NULLP = 324,
     ON = 325,
     ONLY = 326,
     OR = 327,
     ORDER = 328,
     OUTERP = 329,
     PERCENT = 330,
     PERIOD = 331,
     PLUS = 332,
     POSITION = 333,
     RIGHT = 334,
     RIGHTBRACKET = 335,
     RIGHTPAREN = 336,
     SCONST = 337,
     SECONDP = 338,
     SELECT = 339,
     SEMICOLON = 340,
     SESSIONUSER = 341,
     SET = 342,
     SOLIDUS = 343,
     SUBSTRING = 344,
     TIME = 345,
     TIMESTAMP = 346,
     TIMEZONEHOUR = 347,
     TIMEZONEMINUTE = 348,
     TRAILING = 349,
     TRIM = 350,
     TRUEP = 351,
     UNION = 352,
     UNIONJOIN = 353,
     UPDATE = 354,
     USER = 355,
     USING = 356,
     VALUES = 357,
     WHERE = 358,
     YEARP = 359,
     ZONE = 360,
     UMINUS = 361
   };
#endif
/* Tokens.  */
#define ALL 258
#define AND 259
#define AS 260
#define ASC 261
#define ASTERISK 262
#define AT 263
#define BITAND 264
#define BITCONST 265
#define BITINVERT 266
#define BITOR 267
#define BITSHIFTLEFT 268
#define BITSHIFTRIGHT 269
#define BY 270
#define COLON 271
#define COMMA 272
#define CONCATENATION 273
#define CROSS 274
#define CURRENTDATE 275
#define CURRENTTIME 276
#define CURRENTTIMESTAMP 277
#define CURRENTUSER 278
#define DAYP 279
#define DEFAULT 280
#define DELETE 281
#define DESC 282
#define DISTINCT 283
#define EQUALS 284
#define ESCAPE 285
#define EXTRACT 286
#define FALSEP 287
#define FCONST 288
#define FOR 289
#define FROM 290
#define FULL 291
#define GREATERTHAN 292
#define GREATERTHANOREQUALS 293
#define GROUP 294
#define HAVING 295
#define HEXCONST 296
#define HOURP 297
#define ICONST 298
#define IDENT 299
#define IN 300
#define INNERP 301
#define INSERT 302
#define INTERVAL 303
#define INTO 304
#define IS 305
#define ISA 306
#define ISNULL 307
#define JOIN 308
#define LEADING 309
#define LEFT 310
#define LEFTBRACKET 311
#define LEFTPAREN 312
#define LESSTHAN 313
#define LESSTHANOREQUALS 314
#define LIKE 315
#define MINUS 316
#define MINUTEP 317
#define MONTHP 318
#define NATIONAL 319
#define NATURAL 320
#define NOT 321
#define NOTEQUALS 322
#define NOTNULL 323
#define NULLP 324
#define ON 325
#define ONLY 326
#define OR 327
#define ORDER 328
#define OUTERP 329
#define PERCENT 330
#define PERIOD 331
#define PLUS 332
#define POSITION 333
#define RIGHT 334
#define RIGHTBRACKET 335
#define RIGHTPAREN 336
#define SCONST 337
#define SECONDP 338
#define SELECT 339
#define SEMICOLON 340
#define SESSIONUSER 341
#define SET 342
#define SOLIDUS 343
#define SUBSTRING 344
#define TIME 345
#define TIMESTAMP 346
#define TIMEZONEHOUR 347
#define TIMEZONEMINUTE 348
#define TRAILING 349
#define TRIM 350
#define TRUEP 351
#define UNION 352
#define UNIONJOIN 353
#define UPDATE 354
#define USER 355
#define USING 356
#define VALUES 357
#define WHERE 358
#define YEARP 359
#define ZONE 360
#define UMINUS 361




/* Copy the first part of user declarations.  */
#line 1 "OW_WQLParser.yy"

#define YYDEBUG 1
/*-------------------------------------------------------------------------
 *
 * OW_WQLImpl.yy
 *	  OpenWBEM WQL YACC rules/actions
 *
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * NOTES
 *	  CAPITALS are used to represent terminal symbols.
 *	  non-capitals are used to represent non-terminals.
 *-------------------------------------------------------------------------*/
/*******************************************************************************
* Portions Copyright (C) 2001 Vintela, Inc. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
*  - Neither the name of Vintela, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL Vintela, Inc. OR THE CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/**
 * @author Dan Nuffer
 */


#include <stdlib.h>
#include "OW_WQLAst.hpp"
#include "OW_WQLImpl.hpp"

void owwqlerror( const char* s);
extern "C" int owwqllex();

using namespace OpenWBEM;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 197 "OW_WQLParser.yy"
typedef union YYSTYPE {
	stmt* pstmt;
	optSemicolon* poptSemicolon;
	insertStmt* pinsertStmt;
	List<targetEl*>* ptargetList;
	List<String*>* pcolumnList;
	insertRest* pinsertRest;
	deleteStmt* pdeleteStmt;
	List<updateTargetEl*>* pupdateTargetList;
	updateStmt* pupdateStmt;
	selectStmt* pselectStmt;
	exprSeq* pexprSeq;
	optDistinct* poptDistinct;
	List<sortby*>* psortbyList;
	sortClause* psortClause;
	optSortClause* poptSortClause;
	sortby* psortby;
	List<String*>* pnameList;
	optGroupClause* poptGroupClause;
	optHavingClause* poptHavingClause;
	List<tableRef*>* pfromList;
	optFromClause* poptFromClause;
	tableRef* ptableRef;
	joinedTable* pjoinedTable;
	aliasClause* paliasClause;
	joinType* pjoinType;
	joinQual* pjoinQual;
	relationExpr* prelationExpr;
	optWhereClause* poptWhereClause;
	rowExpr* prowExpr;
	List<aExpr*>* prowList;
	rowDescriptor* prowDescriptor;
	aExpr* paExpr;
	bExpr* pbExpr;
	cExpr* pcExpr;
	optIndirection* poptIndirection;
	optExtract* poptExtract;
	positionExpr* ppositionExpr;
	optSubstrExpr* poptSubstrExpr;
	substrFrom* psubstrFrom;
	substrFor* psubstrFor;
	trimExpr* ptrimExpr;
	attr* pattr;
	attrs* pattrs;
	targetEl* ptargetEl;
	updateTargetEl* pupdateTargetEl;
	aExprConst* paExprConst;
	String* pstring;
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 416 "OW_WQLParser.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 428 "OW_WQLParser.cc"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2658

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  59
/* YYNRULES -- Number of rules. */
#define YYNRULES  298
/* YYNRULES -- Number of states. */
#define YYNSTATES  479

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    16,    18,    23,
      25,    29,    31,    35,    40,    43,    51,    53,    58,    60,
      64,    70,    79,    81,    85,    89,    90,    92,    98,   100,
     102,   106,   110,   111,   113,   116,   117,   119,   121,   123,
     127,   128,   132,   133,   136,   138,   142,   143,   146,   148,
     151,   153,   158,   162,   167,   171,   177,   182,   188,   193,
     199,   202,   207,   209,   212,   215,   218,   220,   221,   223,
     228,   231,   233,   236,   239,   240,   243,   245,   247,   249,
     251,   253,   255,   263,   265,   269,   273,   275,   277,   279,
     281,   283,   285,   287,   289,   291,   293,   295,   297,   299,
     301,   303,   305,   307,   313,   316,   319,   322,   326,   330,
     334,   338,   342,   346,   350,   354,   358,   362,   366,   370,
     374,   378,   382,   386,   390,   393,   397,   401,   407,   412,
     419,   422,   426,   429,   434,   438,   443,   447,   452,   456,
     458,   460,   463,   466,   469,   473,   477,   481,   485,   489,
     493,   497,   501,   505,   509,   513,   517,   521,   525,   529,
     533,   535,   538,   540,   544,   548,   553,   559,   565,   570,
     572,   574,   579,   581,   586,   588,   590,   592,   597,   602,
     607,   613,   619,   624,   625,   630,   637,   638,   642,   644,
     646,   648,   650,   652,   656,   657,   658,   662,   666,   669,
     672,   674,   677,   680,   684,   687,   689,   694,   696,   700,
     704,   708,   710,   714,   716,   721,   723,   725,   727,   729,
     731,   733,   735,   737,   739,   741,   743,   745,   747,   749,
     751,   753,   755,   757,   759,   761,   763,   765,   767,   769,
     771,   773,   775,   777,   779,   781,   783,   785,   787,   789,
     791,   793,   795,   797,   799,   801,   803,   805,   807,   809,
     811,   813,   815,   817,   819,   821,   823,   825,   827,   829,
     831,   833,   835,   837,   839,   841,   843,   845,   847,   849,
     851,   853,   855,   857,   859,   861,   863,   865,   867,   869,
     871,   873,   875,   877,   879,   881,   883,   885,   887
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     108,     0,    -1,   118,   109,    -1,   117,   109,    -1,   110,
     109,    -1,   115,   109,    -1,    -1,    85,    -1,    47,    49,
     159,   113,    -1,   157,    -1,   111,    17,   157,    -1,   114,
      -1,   112,    17,   114,    -1,   102,    57,   111,    81,    -1,
      25,   102,    -1,    57,   112,    81,   102,    57,   111,    81,
      -1,   164,    -1,    26,    35,   159,   138,    -1,   158,    -1,
     116,    17,   158,    -1,    99,   159,    87,   116,   138,    -1,
      84,   120,   111,   130,   138,   127,   128,   123,    -1,   144,
      -1,   119,    17,   144,    -1,   119,   101,   144,    -1,    -1,
      28,    -1,    28,    70,    57,   119,    81,    -1,     3,    -1,
     124,    -1,   121,    17,   124,    -1,    73,    15,   121,    -1,
      -1,   122,    -1,   144,   125,    -1,    -1,     6,    -1,    27,
      -1,   160,    -1,   126,    17,   160,    -1,    -1,    39,    15,
     119,    -1,    -1,    40,   144,    -1,   131,    -1,   129,    17,
     131,    -1,    -1,    35,   129,    -1,   137,    -1,   137,   133,
      -1,   132,    -1,    57,   132,    81,   133,    -1,    57,   132,
      81,    -1,   131,    19,    53,   131,    -1,   131,    98,   131,
      -1,   131,   134,    53,   131,   136,    -1,   131,    53,   131,
     136,    -1,   131,    65,   134,    53,   131,    -1,   131,    65,
      53,   131,    -1,     5,   164,    57,   126,    81,    -1,     5,
     164,    -1,   164,    57,   126,    81,    -1,   164,    -1,    36,
     135,    -1,    55,   135,    -1,    79,   135,    -1,    46,    -1,
      -1,    74,    -1,   101,    57,   126,    81,    -1,    70,   144,
      -1,   159,    -1,   159,     7,    -1,    71,   159,    -1,    -1,
     103,   144,    -1,   104,    -1,    63,    -1,    24,    -1,    42,
      -1,    62,    -1,    83,    -1,    57,   142,    81,   143,    57,
     142,    81,    -1,   144,    -1,   141,    17,   144,    -1,   141,
      17,   144,    -1,    77,    -1,    61,    -1,     7,    -1,    88,
      -1,    75,    -1,    58,    -1,    59,    -1,    37,    -1,    38,
      -1,    29,    -1,    67,    -1,    18,    -1,     9,    -1,    12,
      -1,    13,    -1,    14,    -1,   146,    -1,   144,     8,    90,
     105,   146,    -1,    77,   144,    -1,    61,   144,    -1,    11,
     144,    -1,   144,    77,   144,    -1,   144,    61,   144,    -1,
     144,     7,   144,    -1,   144,    88,   144,    -1,   144,    75,
     144,    -1,   144,     9,   144,    -1,   144,    12,   144,    -1,
     144,    13,   144,    -1,   144,    14,   144,    -1,   144,    58,
     144,    -1,   144,    59,   144,    -1,   144,    37,   144,    -1,
     144,    38,   144,    -1,   144,    29,   144,    -1,   144,    67,
     144,    -1,   144,     4,   144,    -1,   144,    72,   144,    -1,
      66,   144,    -1,   144,    18,   144,    -1,   144,    60,   144,
      -1,   144,    60,   144,    30,   144,    -1,   144,    66,    60,
     144,    -1,   144,    66,    60,   144,    30,   144,    -1,   144,
      52,    -1,   144,    50,    69,    -1,   144,    68,    -1,   144,
      50,    66,    69,    -1,   144,    50,    96,    -1,   144,    50,
      66,    32,    -1,   144,    50,    32,    -1,   144,    50,    66,
      96,    -1,   144,    51,   144,    -1,   140,    -1,   146,    -1,
      77,   145,    -1,    61,   145,    -1,    11,   145,    -1,   145,
      77,   145,    -1,   145,    61,   145,    -1,   145,     7,   145,
      -1,   145,    88,   145,    -1,   145,    75,   145,    -1,   145,
       9,   145,    -1,   145,    12,   145,    -1,   145,    13,   145,
      -1,   145,    14,   145,    -1,   145,    58,   145,    -1,   145,
      59,   145,    -1,   145,    37,   145,    -1,   145,    38,   145,
      -1,   145,    29,   145,    -1,   145,    67,   145,    -1,   145,
      18,   145,    -1,   155,    -1,   164,   147,    -1,   163,    -1,
      57,   144,    81,    -1,   162,    57,    81,    -1,   162,    57,
     119,    81,    -1,   162,    57,     3,   119,    81,    -1,   162,
      57,    28,   119,    81,    -1,   162,    57,     7,    81,    -1,
      20,    -1,    21,    -1,    21,    57,    43,    81,    -1,    22,
      -1,    22,    57,    43,    81,    -1,    23,    -1,    86,    -1,
     100,    -1,    31,    57,   148,    81,    -1,    78,    57,   150,
      81,    -1,    89,    57,   151,    81,    -1,    95,    57,    54,
     154,    81,    -1,    95,    57,    94,   154,    81,    -1,    95,
      57,   154,    81,    -1,    -1,   147,    56,   144,    80,    -1,
     147,    56,   144,    16,   144,    80,    -1,    -1,   149,    35,
     144,    -1,   139,    -1,    82,    -1,    44,    -1,    92,    -1,
      93,    -1,   145,    45,   145,    -1,    -1,    -1,   144,   152,
     153,    -1,   144,   153,   152,    -1,   144,   152,    -1,   144,
     153,    -1,   119,    -1,    35,   144,    -1,    34,   144,    -1,
     144,    35,   119,    -1,    35,   119,    -1,   119,    -1,   159,
      76,   156,   147,    -1,   161,    -1,   156,    76,   161,    -1,
     156,    76,     7,    -1,   144,     5,   165,    -1,   144,    -1,
     159,    76,     7,    -1,     7,    -1,   164,   147,    29,   144,
      -1,   164,    -1,   164,    -1,   164,    -1,   164,    -1,    45,
      -1,    50,    -1,    52,    -1,    60,    -1,    68,    -1,    43,
      -1,    33,    -1,    82,    -1,    10,    -1,    41,    -1,    96,
      -1,    32,    -1,    69,    -1,    44,    -1,   139,    -1,     8,
      -1,    15,    -1,    26,    -1,    30,    -1,    47,    -1,    87,
      -1,    92,    -1,    93,    -1,    99,    -1,   102,    -1,   105,
      -1,    48,    -1,    64,    -1,    90,    -1,    91,    -1,   164,
      -1,     3,    -1,     4,    -1,     6,    -1,    19,    -1,    20,
      -1,    21,    -1,    22,    -1,    23,    -1,    25,    -1,    27,
      -1,    28,    -1,    31,    -1,    32,    -1,    34,    -1,    35,
      -1,    36,    -1,    39,    -1,    40,    -1,    45,    -1,    46,
      -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,    53,
      -1,    54,    -1,    55,    -1,    60,    -1,    65,    -1,    66,
      -1,    68,    -1,    69,    -1,    70,    -1,    71,    -1,    72,
      -1,    73,    -1,    74,    -1,    78,    -1,    79,    -1,    84,
      -1,    86,    -1,    89,    -1,    94,    -1,    95,    -1,    96,
      -1,    97,    -1,   100,    -1,   101,    -1,   103,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   300,   300,   302,   304,   306,   313,   314,   320,   326,
     328,   334,   336,   342,   344,   346,   352,   358,   364,   366,
     372,   378,   384,   386,   388,   395,   396,   398,   400,   406,
     408,   414,   421,   422,   428,   435,   436,   438,   444,   446,
     453,   454,   461,   462,   468,   470,   477,   478,   484,   486,
     488,   490,   496,   498,   500,   502,   504,   506,   508,   514,
     516,   518,   520,   526,   528,   530,   532,   539,   540,   546,
     548,   554,   556,   558,   565,   566,   572,   574,   576,   578,
     580,   582,   588,   594,   596,   602,   608,   610,   612,   614,
     616,   618,   620,   622,   624,   626,   628,   630,   632,   634,
     636,   638,   644,   646,   648,   650,   652,   654,   656,   658,
     660,   662,   664,   666,   668,   670,   672,   674,   676,   678,
     680,   682,   684,   686,   688,   690,   692,   694,   696,   698,
     700,   702,   704,   706,   708,   710,   712,   714,   716,   718,
     724,   726,   728,   730,   732,   734,   736,   738,   740,   742,
     744,   746,   748,   750,   752,   754,   756,   758,   760,   762,
     768,   770,   772,   774,   776,   778,   780,   782,   784,   786,
     788,   790,   792,   794,   796,   798,   800,   802,   804,   806,
     808,   810,   812,   819,   820,   822,   829,   830,   836,   838,
     840,   842,   844,   850,   853,   859,   860,   862,   864,   866,
     868,   874,   880,   886,   888,   890,   896,   902,   904,   906,
     912,   914,   916,   918,   924,   930,   936,   942,   948,   950,
     952,   954,   956,   958,   964,   966,   968,   970,   972,   974,
     976,   978,   984,   986,   988,   990,   992,   994,   996,   998,
    1000,  1002,  1004,  1006,  1008,  1010,  1012,  1014,  1016,  1022,
    1024,  1026,  1028,  1030,  1032,  1034,  1036,  1038,  1040,  1042,
    1044,  1046,  1048,  1050,  1052,  1054,  1056,  1058,  1060,  1062,
    1064,  1066,  1068,  1070,  1072,  1074,  1076,  1078,  1080,  1082,
    1084,  1086,  1088,  1090,  1092,  1094,  1096,  1098,  1100,  1102,
    1104,  1106,  1108,  1110,  1112,  1114,  1116,  1118,  1120
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ALL", "AND", "AS", "ASC", "ASTERISK",
  "AT", "BITAND", "BITCONST", "BITINVERT", "BITOR", "BITSHIFTLEFT",
  "BITSHIFTRIGHT", "BY", "COLON", "COMMA", "CONCATENATION", "CROSS",
  "CURRENTDATE", "CURRENTTIME", "CURRENTTIMESTAMP", "CURRENTUSER", "DAYP",
  "DEFAULT", "DELETE", "DESC", "DISTINCT", "EQUALS", "ESCAPE", "EXTRACT",
  "FALSEP", "FCONST", "FOR", "FROM", "FULL", "GREATERTHAN",
  "GREATERTHANOREQUALS", "GROUP", "HAVING", "HEXCONST", "HOURP", "ICONST",
  "IDENT", "IN", "INNERP", "INSERT", "INTERVAL", "INTO", "IS", "ISA",
  "ISNULL", "JOIN", "LEADING", "LEFT", "LEFTBRACKET", "LEFTPAREN",
  "LESSTHAN", "LESSTHANOREQUALS", "LIKE", "MINUS", "MINUTEP", "MONTHP",
  "NATIONAL", "NATURAL", "NOT", "NOTEQUALS", "NOTNULL", "NULLP", "ON",
  "ONLY", "OR", "ORDER", "OUTERP", "PERCENT", "PERIOD", "PLUS", "POSITION",
  "RIGHT", "RIGHTBRACKET", "RIGHTPAREN", "SCONST", "SECONDP", "SELECT",
  "SEMICOLON", "SESSIONUSER", "SET", "SOLIDUS", "SUBSTRING", "TIME",
  "TIMESTAMP", "TIMEZONEHOUR", "TIMEZONEMINUTE", "TRAILING", "TRIM",
  "TRUEP", "UNION", "UNIONJOIN", "UPDATE", "USER", "USING", "VALUES",
  "WHERE", "YEARP", "ZONE", "UMINUS", "$accept", "stmt", "optSemicolon",
  "insertStmt", "targetList", "columnList", "insertRest", "strColumnElem",
  "deleteStmt", "updateTargetList", "updateStmt", "selectStmt", "exprSeq",
  "optDistinct", "sortbyList", "sortClause", "optSortClause", "sortby",
  "strOptOrderSpecification", "nameList", "optGroupClause",
  "optHavingClause", "fromList", "optFromClause", "tableRef",
  "joinedTable", "aliasClause", "joinType", "strOptJoinOuter", "joinQual",
  "relationExpr", "optWhereClause", "strDatetime", "rowExpr", "rowList",
  "rowDescriptor", "strAllOp", "aExpr", "bExpr", "cExpr", "optIndirection",
  "optExtract", "strExtractArg", "positionExpr", "optSubstrExpr",
  "substrFrom", "substrFor", "trimExpr", "attr", "attrs", "targetEl",
  "updateTargetEl", "strRelationName", "strName", "strAttrName",
  "strFuncName", "aExprConst", "strColId", "strColLabel", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
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
     355,   356,   357,   358,   359,   360,   361
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   107,   108,   108,   108,   108,   109,   109,   110,   111,
     111,   112,   112,   113,   113,   113,   114,   115,   116,   116,
     117,   118,   119,   119,   119,   120,   120,   120,   120,   121,
     121,   122,   123,   123,   124,   125,   125,   125,   126,   126,
     127,   127,   128,   128,   129,   129,   130,   130,   131,   131,
     131,   131,   132,   132,   132,   132,   132,   132,   132,   133,
     133,   133,   133,   134,   134,   134,   134,   135,   135,   136,
     136,   137,   137,   137,   138,   138,   139,   139,   139,   139,
     139,   139,   140,   141,   141,   142,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   147,   147,   147,   148,   148,   149,   149,
     149,   149,   149,   150,   150,   151,   151,   151,   151,   151,
     151,   152,   153,   154,   154,   154,   155,   156,   156,   156,
     157,   157,   157,   157,   158,   159,   160,   161,   162,   162,
     162,   162,   162,   162,   163,   163,   163,   163,   163,   163,
     163,   163,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     2,     2,     0,     1,     4,     1,
       3,     1,     3,     4,     2,     7,     1,     4,     1,     3,
       5,     8,     1,     3,     3,     0,     1,     5,     1,     1,
       3,     3,     0,     1,     2,     0,     1,     1,     1,     3,
       0,     3,     0,     2,     1,     3,     0,     2,     1,     2,
       1,     4,     3,     4,     3,     5,     4,     5,     4,     5,
       2,     4,     1,     2,     2,     2,     1,     0,     1,     4,
       2,     1,     2,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     7,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     5,     4,     6,
       2,     3,     2,     4,     3,     4,     3,     4,     3,     1,
       1,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     2,     1,     3,     3,     4,     5,     5,     4,     1,
       1,     4,     1,     4,     1,     1,     1,     4,     4,     4,
       5,     5,     4,     0,     4,     6,     0,     3,     1,     1,
       1,     1,     1,     3,     0,     0,     3,     3,     2,     2,
       1,     2,     2,     3,     2,     1,     4,     1,     3,     3,
       3,     1,     3,     1,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short int yydefact[] =
{
       0,     0,     0,    25,     0,     0,     6,     6,     6,     6,
       0,     0,    28,    26,     0,   234,   235,    78,   236,   237,
      79,   232,   238,   245,    80,    77,   246,    81,   239,   247,
     248,   240,   241,   242,   243,    76,   244,   233,     0,   215,
       1,     7,     4,     5,     3,     2,    74,     0,     0,   213,
     227,     0,   169,   170,   172,   174,     0,   230,   225,   228,
     224,   219,   220,   221,     0,   222,     0,     0,   223,   231,
       0,     0,   226,   175,     0,     0,   229,   176,    46,   139,
     211,   102,   160,     9,     0,     0,   162,   183,     0,     0,
      17,     0,     0,     0,     8,     0,   106,     0,     0,     0,
     186,     0,     0,    83,   105,   124,   104,   194,   195,     0,
       0,     0,    74,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,     0,     0,
       0,     0,     0,     0,   132,     0,     0,     0,     0,     0,
       0,   161,    74,    18,   183,    75,    14,     0,    11,    16,
       0,     0,    22,     0,     0,     0,   190,   189,   191,   192,
     188,     0,     0,     0,     0,   163,     0,     0,     0,     0,
       0,   140,     0,   200,    22,     0,     0,     0,     0,   205,
      22,     0,    10,     0,     0,    47,    44,    50,    48,    71,
      40,   122,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   249,   210,   109,     0,   112,   113,   114,   115,   125,
     120,   118,   119,   136,     0,   131,   134,   138,   116,   117,
     126,   108,     0,   121,   123,   111,   107,   110,   212,   183,
     207,   217,     0,     0,     0,   164,     0,     0,     0,    20,
       0,     0,     0,     0,     0,    27,     0,   171,   173,   177,
       0,    84,    88,    98,    99,   100,   101,    97,    95,    93,
      94,    91,    92,    87,    96,    90,    86,    89,     0,   143,
       0,   142,   141,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     178,     0,     0,   198,   199,   179,   204,     0,     0,     0,
     182,     0,    50,    73,     0,     0,    67,    66,     0,    67,
       0,    67,     0,     0,     0,    49,    62,    72,     0,    42,
       0,   135,   133,   137,     0,   128,     0,   206,     0,   168,
       0,   165,     0,    19,     0,    12,     0,    13,    23,    24,
     187,     0,   146,   149,   150,   151,   152,   159,   157,   155,
     156,   193,   153,   154,   145,   158,   148,   144,   147,   202,
     201,   196,   197,   180,   181,   203,    52,    45,     0,    68,
      63,     0,    64,     0,     0,    65,    54,     0,    60,     0,
       0,     0,    32,   103,   127,     0,   209,   208,   166,   167,
       0,   184,   214,     0,     0,    83,    51,    53,     0,     0,
      56,    58,     0,     0,     0,     0,    38,   216,    41,    43,
       0,    33,    21,   129,     0,     0,    82,    70,     0,    57,
      55,     0,     0,    61,     0,   185,    15,     0,    59,    39,
      31,    29,    35,    69,     0,    36,    37,    34,    30
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     5,    42,     6,    78,   147,    94,   148,     7,   142,
       8,     9,   179,    14,   470,   451,   452,   471,   477,   445,
     359,   422,   185,   112,   186,   187,   355,   353,   410,   440,
     188,    90,    37,    79,   101,   102,   308,   152,   170,    81,
     141,   161,   162,   172,   175,   333,   334,   181,    82,   269,
      83,   143,    97,   446,   270,    85,    86,    87,   242
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -431
static const short int yypact[] =
{
     182,    13,   -24,     8,  1588,    26,   -43,   -43,   -43,   -43,
    1588,  1588,  -431,    -3,   790,  -431,  -431,  -431,  -431,  -431,
    -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,
    -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,   -27,  -431,
    -431,  -431,  -431,  -431,  -431,  -431,   -37,    95,    11,  -431,
    -431,  1241,  -431,    41,    69,  -431,    74,  -431,  -431,  -431,
    -431,  -431,  -431,  -431,  1241,  -431,  1241,  1241,  -431,  -431,
    1241,    75,  -431,  -431,    76,    78,  -431,  -431,    10,  -431,
    1918,  -431,  -431,  -431,    54,    94,  -431,   -41,  1588,  1241,
    -431,   -23,  1588,    99,  -431,  1241,  -431,    61,   114,   117,
     175,   149,    89,  1990,  -431,  2402,  -431,  1339,  1241,  1045,
     790,  1518,   -37,  1241,   495,  1241,    82,  1241,  1241,  1241,
    1241,  1241,  1241,  1241,  1241,   -20,  1241,  -431,  1241,  1241,
    1241,  1241,   113,  1241,  -431,  1241,  1241,  1241,  1241,   889,
     598,   126,   -13,  -431,  -431,  2295,  -431,    -7,  -431,  -431,
     790,   -12,  2295,  1588,   102,   103,  -431,  -431,  -431,  -431,
    -431,   104,   151,  1241,  2503,  -431,  1339,  1241,  1339,  1339,
    2469,  -431,   108,    -4,  1687,   111,  1241,  1143,  1143,    -4,
    2068,   119,  -431,  1518,  1588,   178,   983,  -431,   691,   191,
     164,  2402,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,
    -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,
    -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,
    -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,
    -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,
    -431,  -431,  -431,   193,   110,    25,    50,    73,    73,   198,
     333,   711,   711,  -431,   122,  -431,  -431,   302,   711,   711,
     857,    70,  1241,   333,  2367,   193,    70,   193,  -431,   133,
    -431,  -431,  1241,   135,  1241,  -431,   -10,  1241,  1588,  -431,
      14,  1588,   120,     1,  1241,  -431,  1241,  -431,  -431,  -431,
    1241,  2140,  -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,
    -431,  -431,  -431,  -431,  -431,  -431,  -431,  -431,   166,  -431,
    1990,  -431,  -431,  1339,  1339,  1339,  1339,  1339,  1339,  1339,
    1339,  1339,  1339,  1339,  1339,  1339,  1339,  1339,  1339,  1339,
    -431,  1241,  1241,   192,   190,  -431,    -4,   146,   152,  1241,
    -431,   983,   160,  -431,  1518,   177,   158,  -431,  1518,   158,
     141,   158,  1518,   194,  1588,  -431,   186,  -431,   230,   209,
    1432,  -431,  -431,  -431,  1241,  1652,   959,   126,    -9,  -431,
      -8,  -431,  1764,  -431,  1241,  -431,   195,  -431,  2295,  2295,
    2295,  1241,  -431,   374,   247,   167,   167,   352,  2536,  2570,
    2570,  2536,  2570,  2570,    80,  2536,  -431,    80,  -431,  2295,
    2295,  -431,  -431,  -431,  -431,    -4,   691,   983,  1518,  -431,
    -431,   123,  -431,  1518,   197,  -431,  -431,  1518,   196,  1588,
    1241,  1241,   189,  -431,  1495,  1241,  -431,  -431,  -431,  -431,
    1241,  -431,  2295,   790,   170,  2295,  -431,  -431,  1241,   207,
    -431,  -431,  1518,   123,  1588,     3,  -431,  -431,    -4,  2295,
     254,  -431,  -431,  1495,  2218,     7,  -431,  2295,  1588,  -431,
    -431,    37,  1588,  -431,  1241,  -431,  -431,    48,  -431,  -431,
     257,  -431,  1841,  -431,  1241,  -431,  -431,  -431,  -431
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -431,  -431,    22,  -431,  -149,  -431,  -431,    -1,  -431,  -431,
    -431,  -431,   -93,  -431,  -431,  -431,  -431,  -203,  -431,  -430,
    -431,  -431,  -431,  -431,  -177,   100,  -129,   -72,  -332,  -161,
    -431,   -91,   185,  -431,  -431,   -94,  -431,   -14,   162,   -22,
    -141,  -431,  -431,  -431,  -431,   -46,   -44,  -155,  -431,  -431,
     180,    34,    30,  -143,   -53,  -431,  -431,    51,  -431
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -219
static const short int yytable[] =
{
      80,   283,   151,   280,   278,   284,   341,   284,   284,   284,
     281,    12,   253,   284,   461,   173,  -218,   412,   110,   415,
     462,   190,   337,   338,   110,    11,    40,   110,   467,    43,
      44,    45,   115,   116,    38,  -215,    13,    96,   119,   120,
      46,    47,    41,   374,    84,   111,   254,   276,    10,   255,
     103,   279,   104,   105,   462,    39,   106,   115,   116,   117,
      88,    39,    39,   119,   120,   462,    89,    48,    95,   285,
     277,   371,   428,   429,   282,   145,   256,   115,   116,   146,
     115,   116,   377,   336,   463,   171,   131,   313,   466,   286,
      89,   286,   286,   286,   174,   180,    80,   286,    98,   191,
     136,   243,   137,   245,   246,   247,   248,   249,   250,   251,
     252,   131,   257,   138,   258,   259,   260,   261,   468,   263,
      91,   264,   265,   266,   267,   136,    99,   137,   367,   473,
     139,   100,   107,   108,   131,   109,    80,   153,   138,   144,
      84,   189,   345,   149,   171,   136,   171,   171,   136,   291,
     137,   140,    92,   310,   361,   327,   150,   154,   138,   346,
     155,   138,    39,   180,   180,   241,   163,   407,   329,   347,
     164,   411,   244,   262,   313,   416,   348,   346,   349,   368,
      84,   370,   277,   287,   288,   289,   290,   347,   350,   330,
     271,   362,   335,   438,   413,   344,   349,    93,   357,    17,
     340,   116,   351,   358,   271,   115,   116,   117,     1,   366,
     118,   119,   120,   189,   343,   360,   369,    20,   363,   156,
     351,   352,   376,   381,   439,   332,   331,   403,   325,     2,
     408,   437,   409,   404,    39,    39,   441,    24,    25,   356,
     443,   406,   327,   419,   328,   420,   405,   417,   365,   421,
     442,   456,   433,   444,   313,   329,   314,   157,    27,   131,
     316,   317,   450,   372,   458,   459,     3,   158,   159,   464,
     378,   478,   379,   136,   474,   137,   380,   436,   414,    35,
     375,     4,   460,   342,   455,   160,   138,   434,   402,   401,
     182,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   325,   115,
     116,   117,   373,   427,   118,   119,   120,   399,   400,   469,
     121,     0,   327,     0,   328,     0,     0,   448,   309,   144,
     311,   312,   149,     0,     0,   329,     0,     0,   423,     0,
     115,   116,   117,     0,     0,   118,   119,   120,     0,     0,
     424,   121,  -219,  -219,     0,     0,     0,     0,     0,   313,
     432,   314,   122,   131,   315,   316,   317,   435,     0,     0,
     123,   124,     0,     0,   189,     0,     0,   136,   189,   137,
       0,   313,   189,   125,   126,   127,     0,   316,   317,     0,
     138,   128,   129,   130,   131,    39,     0,     0,     0,    39,
     133,   134,     0,    39,     0,   418,     0,   449,   136,     0,
     137,   453,     0,   325,     0,     0,   454,   271,     0,    80,
       0,   138,     0,     0,   457,     0,     0,   327,     0,   328,
       0,     0,     0,     0,     0,   325,     0,     0,   189,     0,
     329,     0,     0,   189,     0,     0,     0,   189,     0,   327,
     472,   328,     0,     0,     0,     0,     0,   356,     0,    39,
     472,     0,   329,    84,    39,     0,     0,     0,    39,     0,
     447,     0,   189,     0,     0,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,     0,    39,     0,   447,     0,     0,   192,   193,
       0,   194,     0,    15,     0,     0,     0,     0,     0,   447,
      16,     0,     0,   447,   195,   196,   197,   198,   199,    17,
     200,    18,   201,   202,     0,    19,   203,   204,     0,   205,
     206,   207,     0,     0,   208,   209,     0,    20,     0,    21,
     210,   211,    22,    23,   212,   213,   214,   215,   216,   217,
     218,     0,     0,     0,     0,   219,     0,    24,    25,    26,
     220,   221,     0,   222,   223,   224,   225,   226,   227,   228,
       0,     0,     0,   229,   230,     0,     0,     0,    27,   231,
       0,   232,    28,     0,   233,    29,    30,    31,    32,   234,
     235,   236,   237,     0,    33,   238,   239,    34,   240,    35,
      36,   272,     0,     0,     0,   273,    15,     0,    50,    51,
       0,     0,     0,    16,     0,     0,     0,     0,    52,    53,
      54,    55,    17,     0,    18,     0,   274,     0,    19,    56,
      57,    58,     0,     0,     0,     0,     0,     0,     0,    59,
      20,    60,    21,    61,     0,    22,    23,     0,    62,     0,
      63,     0,     0,     0,     0,    64,     0,     0,    65,    66,
      24,    25,    26,     0,    67,     0,    68,    69,     0,     0,
       0,     0,     0,     0,     0,    70,    71,     0,     0,   275,
      72,    27,     0,     0,    73,    28,     0,    74,    29,    30,
      31,    32,     0,    75,    76,     0,   354,    33,    77,    15,
      34,     0,    35,    36,     0,     0,    16,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,    18,   115,   116,
     117,    19,     0,   118,   119,   120,     0,     0,     0,   121,
       0,     0,     0,    20,     0,    21,     0,     0,    22,    23,
       0,     0,     0,     0,     0,     0,     0,     0,  -219,  -219,
       0,     0,     0,    24,    25,    26,     0,     0,     0,     0,
       0,   125,   126,   127,     0,     0,     0,     0,     0,  -219,
    -219,   130,   131,     0,    27,     0,     0,     0,    28,   134,
       0,    29,    30,    31,    32,     0,   136,     0,   137,     0,
      33,     0,     0,    34,     0,    35,    36,    49,    15,   138,
      50,    51,     0,     0,     0,    16,     0,     0,     0,     0,
      52,    53,    54,    55,    17,     0,    18,     0,     0,     0,
      19,    56,    57,    58,     0,     0,     0,     0,     0,     0,
       0,    59,    20,    60,    21,    61,     0,    22,    23,     0,
      62,     0,    63,     0,     0,     0,     0,    64,     0,     0,
      65,    66,    24,    25,    26,     0,    67,     0,    68,    69,
       0,     0,     0,     0,   115,   116,   117,    70,    71,   118,
     119,   120,    72,    27,     0,   121,    73,    28,     0,    74,
      29,    30,    31,    32,     0,    75,    76,   364,     0,    33,
      77,     0,    34,     0,    35,    36,   268,    15,     0,     0,
       0,     0,     0,     0,    16,     0,     0,   125,   126,   127,
       0,     0,     0,    17,     0,    18,     0,  -219,   131,    19,
       0,     0,     0,     0,     0,   134,     0,     0,     0,     0,
       0,    20,   136,    21,   137,     0,    22,    23,     0,     0,
       0,     0,     0,     0,     0,   138,     0,     0,     0,     0,
       0,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   426,    15,     0,     0,
       0,     0,    27,     0,    16,     0,    28,     0,     0,    29,
      30,    31,    32,    17,     0,    18,     0,     0,    33,    19,
       0,    34,     0,    35,    36,     0,     0,     0,     0,     0,
       0,    20,   345,    21,     0,     0,    22,    23,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   346,
       0,    24,    25,    26,     0,     0,     0,     0,     0,   347,
       0,     0,     0,     0,     0,     0,   348,     0,   349,     0,
       0,     0,    27,     0,     0,     0,    28,     0,   350,    29,
      30,    31,    32,    15,     0,    50,    51,     0,    33,     0,
      16,    34,   351,    35,    36,    52,    53,    54,    55,    17,
       0,    18,     0,     0,     0,    19,    56,    57,    58,     0,
     176,   352,     0,     0,     0,     0,    59,    20,    60,    21,
      61,     0,    22,    23,     0,    62,     0,    63,     0,   177,
       0,     0,    64,     0,     0,    65,    66,    24,    25,    26,
       0,    67,     0,    68,    69,     0,     0,     0,     0,     0,
       0,     0,    70,    71,     0,     0,     0,    72,    27,     0,
       0,    73,    28,     0,    74,    29,    30,    31,    32,   178,
      75,    76,     0,     0,    33,    77,     0,    34,     0,    35,
      36,    15,     0,    50,    51,     0,     0,     0,    16,     0,
       0,     0,     0,    52,    53,    54,    55,    17,     0,    18,
       0,     0,     0,    19,    56,    57,    58,     0,   176,     0,
       0,     0,     0,     0,    59,    20,    60,    21,    61,     0,
      22,    23,     0,    62,     0,    63,     0,     0,     0,     0,
      64,     0,     0,    65,    66,    24,    25,    26,     0,    67,
       0,    68,    69,     0,     0,     0,     0,     0,     0,     0,
      70,    71,     0,     0,     0,    72,    27,     0,     0,    73,
      28,     0,    74,    29,    30,    31,    32,     0,    75,    76,
       0,     0,    33,    77,     0,    34,     0,    35,    36,    15,
       0,    50,    51,     0,     0,     0,    16,     0,     0,     0,
       0,    52,    53,    54,    55,    17,     0,    18,     0,     0,
       0,    19,    56,    57,    58,     0,     0,     0,     0,     0,
       0,     0,    59,    20,    60,    21,    61,     0,    22,    23,
       0,    62,     0,    63,     0,     0,     0,     0,    64,     0,
       0,    65,    66,    24,    25,    26,     0,    67,     0,    68,
      69,     0,     0,     0,     0,     0,     0,     0,    70,    71,
       0,     0,     0,    72,    27,     0,     0,    73,    28,     0,
      74,    29,    30,    31,    32,     0,    75,    76,     0,     0,
      33,    77,     0,    34,     0,    35,    36,    15,     0,    50,
     166,     0,     0,     0,    16,     0,     0,     0,     0,    52,
      53,    54,    55,    17,     0,    18,     0,     0,     0,    19,
      56,    57,    58,     0,     0,     0,     0,     0,     0,     0,
      59,    20,    60,    21,    61,     0,    22,    23,     0,    62,
       0,    63,     0,     0,     0,     0,   167,     0,     0,    65,
     168,    24,    25,    26,     0,     0,     0,    68,    69,     0,
       0,     0,     0,     0,     0,     0,   169,    71,     0,     0,
       0,    72,    27,     0,     0,    73,    28,     0,    74,    29,
      30,    31,    32,     0,    75,    76,     0,     0,    33,    77,
      15,    34,    50,    35,    36,     0,     0,    16,     0,     0,
       0,     0,    52,    53,    54,    55,    17,     0,    18,     0,
       0,     0,    19,    56,    57,    58,     0,     0,     0,     0,
       0,     0,     0,    59,    20,    60,    21,    61,     0,    22,
      23,     0,    62,     0,    63,     0,     0,     0,     0,   167,
       0,     0,    65,     0,    24,    25,    26,     0,     0,     0,
      68,    69,   115,   116,   117,     0,     0,   118,   119,   120,
      71,     0,     0,   121,    72,    27,     0,     0,    73,    28,
       0,    74,    29,    30,    31,    32,    15,    75,    76,     0,
       0,    33,    77,    16,    34,     0,    35,    36,     0,     0,
       0,     0,    17,     0,    18,   125,   126,   127,    19,     0,
       0,     0,     0,     0,     0,     0,   131,     0,     0,     0,
      20,     0,    21,   134,     0,    22,    23,     0,     0,     0,
     136,     0,   137,     0,     0,   183,     0,     0,     0,     0,
      24,    25,    26,   138,     0,     0,     0,     0,     0,   184,
       0,     0,     0,     0,     0,     0,    15,     0,     0,     0,
       0,    27,     0,    16,     0,    28,     0,     0,    29,    30,
      31,    32,    17,     0,    18,     0,     0,    33,    19,     0,
      34,     0,    35,    36,     0,     0,     0,     0,     0,     0,
      20,     0,    21,     0,     0,    22,    23,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      24,    25,    26,     0,     0,     0,     0,     0,     0,   115,
     116,   117,     0,     0,   118,   119,   120,     0,     0,     0,
     121,    27,     0,     0,     0,    28,     0,     0,    29,    30,
      31,    32,   425,     0,     0,     0,     0,    33,     0,     0,
      34,   113,    35,    36,   115,   116,   117,     0,     0,   118,
     119,   120,   125,   126,   127,   121,     0,     0,     0,     0,
       0,     0,  -219,   131,     0,     0,   122,     0,     0,     0,
     134,   331,   332,     0,   123,   124,     0,   136,     0,   137,
       0,     0,     0,     0,     0,     0,     0,   125,   126,   127,
     138,     0,     0,     0,     0,   128,   129,   130,   131,     0,
       0,     0,     0,   132,   133,   134,     0,     0,     0,   135,
       0,     0,   136,     0,   137,     0,     0,     0,   113,     0,
       0,   115,   116,   117,     0,   138,   118,   119,   120,     0,
     430,     0,   121,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   122,     0,     0,     0,     0,     0,     0,
       0,   123,   124,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   125,   126,   127,     0,     0,     0,
       0,     0,   128,   129,   130,   131,     0,     0,     0,     0,
     132,   133,   134,     0,     0,     0,   135,     0,     0,   136,
       0,   137,     0,     0,   431,   113,     0,   475,   115,   116,
     117,     0,   138,   118,   119,   120,     0,     0,     0,   121,
       0,     0,     0,     0,     0,     0,     0,     0,   476,     0,
     122,     0,     0,     0,     0,     0,     0,     0,   123,   124,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   125,   126,   127,     0,     0,     0,     0,     0,   128,
     129,   130,   131,     0,     0,     0,     0,   132,   133,   134,
       0,     0,     0,   135,     0,     0,   136,     0,   137,     0,
       0,     0,   113,   114,     0,   115,   116,   117,     0,   138,
     118,   119,   120,     0,     0,     0,   121,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   122,     0,     0,
       0,     0,     0,     0,     0,   123,   124,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   125,   126,
     127,     0,     0,     0,     0,     0,   128,   129,   130,   131,
       0,     0,     0,     0,   132,   133,   134,     0,     0,     0,
     135,     0,     0,   136,   113,   137,     0,   115,   116,   117,
       0,     0,   118,   119,   120,     0,   138,     0,   121,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,     0,   123,   124,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     125,   126,   127,     0,     0,     0,     0,     0,   128,   129,
     130,   131,     0,     0,     0,     0,   132,   133,   134,     0,
       0,     0,   135,     0,     0,   136,     0,   137,     0,     0,
       0,   165,   113,     0,     0,   115,   116,   117,   138,     0,
     118,   119,   120,     0,     0,     0,   121,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   122,     0,     0,
       0,     0,     0,   339,     0,   123,   124,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   125,   126,
     127,     0,     0,     0,     0,     0,   128,   129,   130,   131,
       0,     0,     0,     0,   132,   133,   134,     0,     0,     0,
     135,     0,     0,   136,   113,   137,     0,   115,   116,   117,
       0,     0,   118,   119,   120,     0,   138,     0,   121,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,     0,   123,   124,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     125,   126,   127,     0,     0,     0,     0,     0,   128,   129,
     130,   131,     0,     0,     0,     0,   132,   133,   134,     0,
       0,     0,   135,     0,     0,   136,     0,   137,     0,     0,
       0,   -85,   113,     0,     0,   115,   116,   117,   138,     0,
     118,   119,   120,     0,     0,     0,   121,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   122,     0,     0,
       0,     0,     0,     0,     0,   123,   124,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   125,   126,
     127,     0,     0,     0,     0,     0,   128,   129,   130,   131,
       0,     0,     0,     0,   132,   133,   134,     0,     0,     0,
     135,     0,     0,   136,     0,   137,     0,     0,   465,   113,
       0,     0,   115,   116,   117,     0,   138,   118,   119,   120,
       0,     0,     0,   121,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   122,     0,     0,     0,     0,     0,
       0,     0,   123,   124,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   125,   126,   127,     0,     0,
       0,     0,     0,   128,   129,   130,   131,     0,     0,     0,
       0,   132,   133,   134,     0,     0,     0,   135,     0,     0,
     136,   113,   137,     0,   115,   116,   117,     0,     0,   118,
     119,   120,     0,   138,     0,   121,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   122,     0,     0,     0,
       0,     0,     0,     0,   123,   124,     0,     0,     0,   115,
     116,   117,     0,     0,   118,   119,   120,   125,   126,   127,
     121,     0,     0,     0,     0,   128,   129,   130,   131,     0,
       0,   122,     0,   132,   133,   134,     0,     0,     0,   123,
     124,     0,   136,     0,   137,     0,     0,     0,     0,     0,
       0,     0,   125,   126,   127,   138,     0,     0,     0,     0,
     128,   129,   130,   131,     0,     0,     0,     0,   132,   133,
     134,     0,     0,     0,     0,     0,   313,   136,   314,   137,
       0,   315,   316,   317,     0,     0,     0,   318,     0,     0,
     138,     0,     0,     0,     0,     0,     0,     0,   319,     0,
       0,     0,     0,     0,     0,     0,   320,   321,     0,     0,
     292,     0,   293,     0,   322,   294,   295,   296,     0,     0,
       0,   297,     0,     0,     0,     0,     0,   323,   324,     0,
     325,     0,   298,     0,     0,     0,   326,     0,     0,     0,
     299,   300,     0,   313,   327,   314,   328,     0,   315,   316,
     317,     0,     0,     0,   318,     0,     0,   329,     0,     0,
       0,   301,   302,     0,   303,   319,     0,     0,     0,     0,
     304,     0,     0,   320,   321,     0,     0,   313,   305,   314,
     306,     0,   315,   316,   317,     0,     0,     0,   318,     0,
       0,   307,     0,     0,   323,   324,     0,   325,     0,     0,
       0,     0,     0,   326,     0,     0,     0,  -219,  -219,     0,
       0,   327,     0,   328,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   329,     0,     0,     0,  -219,  -219,
       0,   325,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   327,     0,   328,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   329
};

static const short int yycheck[] =
{
      14,   150,    95,   144,    17,    17,   183,    17,    17,    17,
      17,     3,    32,    17,   444,   108,    57,   349,    17,   351,
      17,   112,   177,   178,    17,    49,     0,    17,   458,     7,
       8,     9,     7,     8,     4,    76,    28,    51,    13,    14,
      10,    11,    85,    29,    14,    35,    66,   140,    35,    69,
      64,   142,    66,    67,    17,     4,    70,     7,     8,     9,
      87,    10,    11,    13,    14,    17,   103,    70,    57,    81,
      56,    81,    81,    81,    81,    89,    96,     7,     8,   102,
       7,     8,    81,   176,    81,   107,    61,     7,    81,   101,
     103,   101,   101,   101,   108,   109,   110,   101,    57,   113,
      75,   115,    77,   117,   118,   119,   120,   121,   122,   123,
     124,    61,   126,    88,   128,   129,   130,   131,    81,   133,
      25,   135,   136,   137,   138,    75,    57,    77,   269,    81,
      76,    57,    57,    57,    61,    57,   150,    76,    88,    88,
     110,   111,    19,    92,   166,    75,   168,   169,    75,   163,
      77,    57,    57,   167,    32,    75,    57,    43,    88,    36,
      43,    88,   111,   177,   178,   114,    17,   344,    88,    46,
      81,   348,    90,    60,     7,   352,    53,    36,    55,   272,
     150,   274,    56,    81,    81,    81,    35,    46,    65,    81,
     139,    69,    81,    70,    53,    17,    55,   102,     7,    24,
      81,     8,    79,    39,   153,     7,     8,     9,    26,    76,
      12,    13,    14,   183,   184,   105,    81,    42,    96,    44,
      79,    98,   102,    57,   101,    35,    34,    81,    61,    47,
      53,   408,    74,    81,   183,   184,   413,    62,    63,   188,
     417,    81,    75,    57,    77,    15,   339,    53,   262,    40,
      53,    81,    57,    57,     7,    88,     9,    82,    83,    61,
      13,    14,    73,   277,    57,   442,    84,    92,    93,    15,
     284,   474,   286,    75,    17,    77,   290,   406,   350,   104,
     281,    99,   443,   183,   433,   100,    88,   381,   334,   333,
     110,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,    61,     7,
       8,     9,   278,   366,    12,    13,    14,   331,   332,   462,
      18,    -1,    75,    -1,    77,    -1,    -1,   420,   166,   278,
     168,   169,   281,    -1,    -1,    88,    -1,    -1,   360,    -1,
       7,     8,     9,    -1,    -1,    12,    13,    14,    -1,    -1,
     364,    18,    50,    51,    -1,    -1,    -1,    -1,    -1,     7,
     374,     9,    29,    61,    12,    13,    14,   381,    -1,    -1,
      37,    38,    -1,    -1,   344,    -1,    -1,    75,   348,    77,
      -1,     7,   352,    50,    51,    52,    -1,    13,    14,    -1,
      88,    58,    59,    60,    61,   344,    -1,    -1,    -1,   348,
      67,    68,    -1,   352,    -1,   354,    -1,   421,    75,    -1,
      77,   425,    -1,    61,    -1,    -1,   430,   366,    -1,   433,
      -1,    88,    -1,    -1,   438,    -1,    -1,    75,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,   408,    -1,
      88,    -1,    -1,   413,    -1,    -1,    -1,   417,    -1,    75,
     464,    77,    -1,    -1,    -1,    -1,    -1,   406,    -1,   408,
     474,    -1,    88,   433,   413,    -1,    -1,    -1,   417,    -1,
     419,    -1,   442,    -1,    -1,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,    -1,   442,    -1,   444,    -1,    -1,     3,     4,
      -1,     6,    -1,     8,    -1,    -1,    -1,    -1,    -1,   458,
      15,    -1,    -1,   462,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    30,    31,    32,    -1,    34,
      35,    36,    -1,    -1,    39,    40,    -1,    42,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    60,    -1,    62,    63,    64,
      65,    66,    -1,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    78,    79,    -1,    -1,    -1,    83,    84,
      -1,    86,    87,    -1,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    -1,    99,   100,   101,   102,   103,   104,
     105,     3,    -1,    -1,    -1,     7,     8,    -1,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    -1,    26,    -1,    28,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    -1,    47,    48,    -1,    50,    -1,
      52,    -1,    -1,    -1,    -1,    57,    -1,    -1,    60,    61,
      62,    63,    64,    -1,    66,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    78,    -1,    -1,    81,
      82,    83,    -1,    -1,    86,    87,    -1,    89,    90,    91,
      92,    93,    -1,    95,    96,    -1,     5,    99,   100,     8,
     102,    -1,   104,   105,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    26,     7,     8,
       9,    30,    -1,    12,    13,    14,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    42,    -1,    44,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    -1,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    -1,    83,    -1,    -1,    -1,    87,    68,
      -1,    90,    91,    92,    93,    -1,    75,    -1,    77,    -1,
      99,    -1,    -1,   102,    -1,   104,   105,     7,     8,    88,
      10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    -1,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    -1,    47,    48,    -1,
      50,    -1,    52,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      60,    61,    62,    63,    64,    -1,    66,    -1,    68,    69,
      -1,    -1,    -1,    -1,     7,     8,     9,    77,    78,    12,
      13,    14,    82,    83,    -1,    18,    86,    87,    -1,    89,
      90,    91,    92,    93,    -1,    95,    96,    30,    -1,    99,
     100,    -1,   102,    -1,   104,   105,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    -1,    -1,    50,    51,    52,
      -1,    -1,    -1,    24,    -1,    26,    -1,    60,    61,    30,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    42,    75,    44,    77,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     7,     8,    -1,    -1,
      -1,    -1,    83,    -1,    15,    -1,    87,    -1,    -1,    90,
      91,    92,    93,    24,    -1,    26,    -1,    -1,    99,    30,
      -1,   102,    -1,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    19,    44,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    55,    -1,
      -1,    -1,    83,    -1,    -1,    -1,    87,    -1,    65,    90,
      91,    92,    93,     8,    -1,    10,    11,    -1,    99,    -1,
      15,   102,    79,   104,   105,    20,    21,    22,    23,    24,
      -1,    26,    -1,    -1,    -1,    30,    31,    32,    33,    -1,
      35,    98,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    -1,    47,    48,    -1,    50,    -1,    52,    -1,    54,
      -1,    -1,    57,    -1,    -1,    60,    61,    62,    63,    64,
      -1,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    -1,    -1,    -1,    82,    83,    -1,
      -1,    86,    87,    -1,    89,    90,    91,    92,    93,    94,
      95,    96,    -1,    -1,    99,   100,    -1,   102,    -1,   104,
     105,     8,    -1,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    -1,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    -1,
      47,    48,    -1,    50,    -1,    52,    -1,    -1,    -1,    -1,
      57,    -1,    -1,    60,    61,    62,    63,    64,    -1,    66,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,    -1,    -1,    -1,    82,    83,    -1,    -1,    86,
      87,    -1,    89,    90,    91,    92,    93,    -1,    95,    96,
      -1,    -1,    99,   100,    -1,   102,    -1,   104,   105,     8,
      -1,    10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    -1,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    -1,    47,    48,
      -1,    50,    -1,    52,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    60,    61,    62,    63,    64,    -1,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,
      -1,    -1,    -1,    82,    83,    -1,    -1,    86,    87,    -1,
      89,    90,    91,    92,    93,    -1,    95,    96,    -1,    -1,
      99,   100,    -1,   102,    -1,   104,   105,     8,    -1,    10,
      11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    20,
      21,    22,    23,    24,    -1,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    -1,    47,    48,    -1,    50,
      -1,    52,    -1,    -1,    -1,    -1,    57,    -1,    -1,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    -1,    -1,
      -1,    82,    83,    -1,    -1,    86,    87,    -1,    89,    90,
      91,    92,    93,    -1,    95,    96,    -1,    -1,    99,   100,
       8,   102,    10,   104,   105,    -1,    -1,    15,    -1,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    -1,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    -1,    47,
      48,    -1,    50,    -1,    52,    -1,    -1,    -1,    -1,    57,
      -1,    -1,    60,    -1,    62,    63,    64,    -1,    -1,    -1,
      68,    69,     7,     8,     9,    -1,    -1,    12,    13,    14,
      78,    -1,    -1,    18,    82,    83,    -1,    -1,    86,    87,
      -1,    89,    90,    91,    92,    93,     8,    95,    96,    -1,
      -1,    99,   100,    15,   102,    -1,   104,   105,    -1,    -1,
      -1,    -1,    24,    -1,    26,    50,    51,    52,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,
      42,    -1,    44,    68,    -1,    47,    48,    -1,    -1,    -1,
      75,    -1,    77,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      62,    63,    64,    88,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    83,    -1,    15,    -1,    87,    -1,    -1,    90,    91,
      92,    93,    24,    -1,    26,    -1,    -1,    99,    30,    -1,
     102,    -1,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    44,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,     7,
       8,     9,    -1,    -1,    12,    13,    14,    -1,    -1,    -1,
      18,    83,    -1,    -1,    -1,    87,    -1,    -1,    90,    91,
      92,    93,    30,    -1,    -1,    -1,    -1,    99,    -1,    -1,
     102,     4,   104,   105,     7,     8,     9,    -1,    -1,    12,
      13,    14,    50,    51,    52,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    29,    -1,    -1,    -1,
      68,    34,    35,    -1,    37,    38,    -1,    75,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      88,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    67,    68,    -1,    -1,    -1,    72,
      -1,    -1,    75,    -1,    77,    -1,    -1,    -1,     4,    -1,
      -1,     7,     8,     9,    -1,    88,    12,    13,    14,    -1,
      16,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    51,    52,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    -1,    -1,    -1,    72,    -1,    -1,    75,
      -1,    77,    -1,    -1,    80,     4,    -1,     6,     7,     8,
       9,    -1,    88,    12,    13,    14,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,
      -1,    -1,    -1,    72,    -1,    -1,    75,    -1,    77,    -1,
      -1,    -1,     4,     5,    -1,     7,     8,     9,    -1,    88,
      12,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    -1,    -1,    -1,
      72,    -1,    -1,    75,     4,    77,    -1,     7,     8,     9,
      -1,    -1,    12,    13,    14,    -1,    88,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    -1,
      -1,    -1,    72,    -1,    -1,    75,    -1,    77,    -1,    -1,
      -1,    81,     4,    -1,    -1,     7,     8,     9,    88,    -1,
      12,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    -1,    -1,    -1,
      72,    -1,    -1,    75,     4,    77,    -1,     7,     8,     9,
      -1,    -1,    12,    13,    14,    -1,    88,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    -1,
      -1,    -1,    72,    -1,    -1,    75,    -1,    77,    -1,    -1,
      -1,    81,     4,    -1,    -1,     7,     8,     9,    88,    -1,
      12,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    -1,    -1,    -1,
      72,    -1,    -1,    75,    -1,    77,    -1,    -1,    80,     4,
      -1,    -1,     7,     8,     9,    -1,    88,    12,    13,    14,
      -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    52,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    -1,    -1,    -1,    72,    -1,    -1,
      75,     4,    77,    -1,     7,     8,     9,    -1,    -1,    12,
      13,    14,    -1,    88,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    -1,     7,
       8,     9,    -1,    -1,    12,    13,    14,    50,    51,    52,
      18,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    -1,
      -1,    29,    -1,    66,    67,    68,    -1,    -1,    -1,    37,
      38,    -1,    75,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    88,    -1,    -1,    -1,    -1,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,     7,    75,     9,    77,
      -1,    12,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    -1,
       7,    -1,     9,    -1,    45,    12,    13,    14,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    58,    59,    -1,
      61,    -1,    29,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      37,    38,    -1,     7,    75,     9,    77,    -1,    12,    13,
      14,    -1,    -1,    -1,    18,    -1,    -1,    88,    -1,    -1,
      -1,    58,    59,    -1,    61,    29,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    37,    38,    -1,    -1,     7,    75,     9,
      77,    -1,    12,    13,    14,    -1,    -1,    -1,    18,    -1,
      -1,    88,    -1,    -1,    58,    59,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    37,    38,    -1,
      -1,    75,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    58,    59,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    26,    47,    84,    99,   108,   110,   115,   117,   118,
      35,    49,     3,    28,   120,     8,    15,    24,    26,    30,
      42,    44,    47,    48,    62,    63,    64,    83,    87,    90,
      91,    92,    93,    99,   102,   104,   105,   139,   159,   164,
       0,    85,   109,   109,   109,   109,   159,   159,    70,     7,
      10,    11,    20,    21,    22,    23,    31,    32,    33,    41,
      43,    45,    50,    52,    57,    60,    61,    66,    68,    69,
      77,    78,    82,    86,    89,    95,    96,   100,   111,   140,
     144,   146,   155,   157,   159,   162,   163,   164,    87,   103,
     138,    25,    57,   102,   113,    57,   144,   159,    57,    57,
      57,   141,   142,   144,   144,   144,   144,    57,    57,    57,
      17,    35,   130,     4,     5,     7,     8,     9,    12,    13,
      14,    18,    29,    37,    38,    50,    51,    52,    58,    59,
      60,    61,    66,    67,    68,    72,    75,    77,    88,    76,
      57,   147,   116,   158,   164,   144,   102,   112,   114,   164,
      57,   119,   144,    76,    43,    43,    44,    82,    92,    93,
     139,   148,   149,    17,    81,    81,    11,    57,    61,    77,
     145,   146,   150,   119,   144,   151,    35,    54,    94,   119,
     144,   154,   157,    57,    71,   129,   131,   132,   137,   159,
     138,   144,     3,     4,     6,    19,    20,    21,    22,    23,
      25,    27,    28,    31,    32,    34,    35,    36,    39,    40,
      45,    46,    49,    50,    51,    52,    53,    54,    55,    60,
      65,    66,    68,    69,    70,    71,    72,    73,    74,    78,
      79,    84,    86,    89,    94,    95,    96,    97,   100,   101,
     103,   164,   165,   144,    90,   144,   144,   144,   144,   144,
     144,   144,   144,    32,    66,    69,    96,   144,   144,   144,
     144,   144,    60,   144,   144,   144,   144,   144,     7,   156,
     161,   164,     3,     7,    28,    81,   119,    56,    17,   138,
     147,    17,    81,   111,    17,    81,   101,    81,    81,    81,
      35,   144,     7,     9,    12,    13,    14,    18,    29,    37,
      38,    58,    59,    61,    67,    75,    77,    88,   143,   145,
     144,   145,   145,     7,     9,    12,    13,    14,    18,    29,
      37,    38,    45,    58,    59,    61,    67,    75,    77,    88,
      81,    34,    35,   152,   153,    81,   119,   154,   154,    35,
      81,   131,   132,   159,    17,    19,    36,    46,    53,    55,
      65,    79,    98,   134,     5,   133,   164,     7,    39,   127,
     105,    32,    69,    96,    30,   144,    76,   147,   119,    81,
     119,    81,   144,   158,    29,   114,   102,    81,   144,   144,
     144,    57,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   144,
     144,   153,   152,    81,    81,   119,    81,   131,    53,    74,
     135,   131,   135,    53,   134,   135,   131,    53,   164,    57,
      15,    40,   128,   146,   144,    30,     7,   161,    81,    81,
      16,    80,   144,    57,   142,   144,   133,   131,    70,   101,
     136,   131,    53,   131,    57,   126,   160,   164,   119,   144,
      73,   122,   123,   144,   144,   111,    81,   144,    57,   131,
     136,   126,    17,    81,    15,    80,    81,   126,    81,   160,
     121,   124,   144,    81,    17,     6,    27,   125,   124
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
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
#ifndef	YYINITDEPTH
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
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()
    ;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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
#line 301 "OW_WQLParser.yy"
    { (yyval.pstmt) = WQLImpl::setStatement(new stmt_selectStmt_optSemicolon((yyvsp[-1].pselectStmt), (yyvsp[0].poptSemicolon))); }
    break;

  case 3:
#line 303 "OW_WQLParser.yy"
    { (yyval.pstmt) = WQLImpl::setStatement(new stmt_updateStmt_optSemicolon((yyvsp[-1].pupdateStmt), (yyvsp[0].poptSemicolon))); }
    break;

  case 4:
#line 305 "OW_WQLParser.yy"
    { (yyval.pstmt) = WQLImpl::setStatement(new stmt_insertStmt_optSemicolon((yyvsp[-1].pinsertStmt), (yyvsp[0].poptSemicolon))); }
    break;

  case 5:
#line 307 "OW_WQLParser.yy"
    { (yyval.pstmt) = WQLImpl::setStatement(new stmt_deleteStmt_optSemicolon((yyvsp[-1].pdeleteStmt), (yyvsp[0].poptSemicolon))); }
    break;

  case 6:
#line 313 "OW_WQLParser.yy"
    { (yyval.poptSemicolon) = 0; }
    break;

  case 7:
#line 315 "OW_WQLParser.yy"
    { (yyval.poptSemicolon) = new optSemicolon_SEMICOLON((yyvsp[0].pstring)); }
    break;

  case 8:
#line 321 "OW_WQLParser.yy"
    { (yyval.pinsertStmt) = new insertStmt((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pinsertRest)); }
    break;

  case 9:
#line 327 "OW_WQLParser.yy"
    { (yyval.ptargetList) = new List<targetEl*>(1, (yyvsp[0].ptargetEl)); }
    break;

  case 10:
#line 329 "OW_WQLParser.yy"
    { (yyvsp[-2].ptargetList)->push_back((yyvsp[0].ptargetEl)); delete (yyvsp[-1].pstring); (yyval.ptargetList) = (yyvsp[-2].ptargetList); }
    break;

  case 11:
#line 335 "OW_WQLParser.yy"
    { (yyval.pcolumnList) = new List<String*>(1, (yyvsp[0].pstring)); }
    break;

  case 12:
#line 337 "OW_WQLParser.yy"
    { (yyvsp[-2].pcolumnList)->push_back((yyvsp[0].pstring)); delete (yyvsp[-1].pstring); (yyval.pcolumnList) = (yyvsp[-2].pcolumnList); }
    break;

  case 13:
#line 343 "OW_WQLParser.yy"
    { (yyval.pinsertRest) = new insertRest_VALUES_LEFTPAREN_targetList_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].ptargetList), (yyvsp[0].pstring)); }
    break;

  case 14:
#line 345 "OW_WQLParser.yy"
    { (yyval.pinsertRest) = new insertRest_DEFAULT_VALUES((yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 15:
#line 347 "OW_WQLParser.yy"
    { (yyval.pinsertRest) = new insertRest_LEFTPAREN_columnList_RIGHTPAREN_VALUES_LEFTPAREN_targetList_RIGHTPAREN((yyvsp[-6].pstring), (yyvsp[-5].pcolumnList), (yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].ptargetList), (yyvsp[0].pstring)); }
    break;

  case 16:
#line 353 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 17:
#line 359 "OW_WQLParser.yy"
    { (yyval.pdeleteStmt) = new deleteStmt((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].poptWhereClause)); }
    break;

  case 18:
#line 365 "OW_WQLParser.yy"
    { (yyval.pupdateTargetList) = new List<updateTargetEl*>(1, (yyvsp[0].pupdateTargetEl)); }
    break;

  case 19:
#line 367 "OW_WQLParser.yy"
    { (yyvsp[-2].pupdateTargetList)->push_back((yyvsp[0].pupdateTargetEl)); delete (yyvsp[-1].pstring); (yyval.pupdateTargetList) = (yyvsp[-2].pupdateTargetList); }
    break;

  case 20:
#line 373 "OW_WQLParser.yy"
    { (yyval.pupdateStmt) = new updateStmt((yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pupdateTargetList), (yyvsp[0].poptWhereClause)); }
    break;

  case 21:
#line 379 "OW_WQLParser.yy"
    { (yyval.pselectStmt) = new selectStmt((yyvsp[-7].pstring), (yyvsp[-6].poptDistinct), (yyvsp[-5].ptargetList), (yyvsp[-4].poptFromClause), (yyvsp[-3].poptWhereClause), (yyvsp[-2].poptGroupClause), (yyvsp[-1].poptHavingClause), (yyvsp[0].poptSortClause)); }
    break;

  case 22:
#line 385 "OW_WQLParser.yy"
    { (yyval.pexprSeq) = new exprSeq_aExpr((yyvsp[0].paExpr)); }
    break;

  case 23:
#line 387 "OW_WQLParser.yy"
    { (yyval.pexprSeq) = new exprSeq_exprSeq_COMMA_aExpr((yyvsp[-2].pexprSeq), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 24:
#line 389 "OW_WQLParser.yy"
    { (yyval.pexprSeq) = new exprSeq_exprSeq_USING_aExpr((yyvsp[-2].pexprSeq), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 25:
#line 395 "OW_WQLParser.yy"
    { (yyval.poptDistinct) = 0; }
    break;

  case 26:
#line 397 "OW_WQLParser.yy"
    { (yyval.poptDistinct) = new optDistinct_DISTINCT((yyvsp[0].pstring)); }
    break;

  case 27:
#line 399 "OW_WQLParser.yy"
    { (yyval.poptDistinct) = new optDistinct_DISTINCT_ON_LEFTPAREN_exprSeq_RIGHTPAREN((yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pexprSeq), (yyvsp[0].pstring)); }
    break;

  case 28:
#line 401 "OW_WQLParser.yy"
    { (yyval.poptDistinct) = new optDistinct_ALL((yyvsp[0].pstring)); }
    break;

  case 29:
#line 407 "OW_WQLParser.yy"
    { (yyval.psortbyList) = new List<sortby*>(1, (yyvsp[0].psortby)); }
    break;

  case 30:
#line 409 "OW_WQLParser.yy"
    { (yyvsp[-2].psortbyList)->push_back((yyvsp[0].psortby)); delete (yyvsp[-1].pstring); (yyval.psortbyList) = (yyvsp[-2].psortbyList); }
    break;

  case 31:
#line 415 "OW_WQLParser.yy"
    { (yyval.psortClause) = new sortClause((yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].psortbyList)); }
    break;

  case 32:
#line 421 "OW_WQLParser.yy"
    { (yyval.poptSortClause) = 0; }
    break;

  case 33:
#line 423 "OW_WQLParser.yy"
    { (yyval.poptSortClause) = new optSortClause_sortClause((yyvsp[0].psortClause)); }
    break;

  case 34:
#line 429 "OW_WQLParser.yy"
    { (yyval.psortby) = new sortby((yyvsp[-1].paExpr), (yyvsp[0].pstring)); }
    break;

  case 35:
#line 435 "OW_WQLParser.yy"
    { (yyval.pstring) = 0; }
    break;

  case 36:
#line 437 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 37:
#line 439 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 38:
#line 445 "OW_WQLParser.yy"
    { (yyval.pnameList) = new List<String*>(1, (yyvsp[0].pstring)); }
    break;

  case 39:
#line 447 "OW_WQLParser.yy"
    { (yyvsp[-2].pnameList)->push_back((yyvsp[0].pstring)); delete (yyvsp[-1].pstring); (yyval.pnameList) = (yyvsp[-2].pnameList); }
    break;

  case 40:
#line 453 "OW_WQLParser.yy"
    { (yyval.poptGroupClause) = 0; }
    break;

  case 41:
#line 455 "OW_WQLParser.yy"
    { (yyval.poptGroupClause) = new optGroupClause_GROUP_BY_exprSeq((yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pexprSeq)); }
    break;

  case 42:
#line 461 "OW_WQLParser.yy"
    { (yyval.poptHavingClause) = 0; }
    break;

  case 43:
#line 463 "OW_WQLParser.yy"
    { (yyval.poptHavingClause) = new optHavingClause_HAVING_aExpr((yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 44:
#line 469 "OW_WQLParser.yy"
    { (yyval.pfromList) = new List<tableRef*>(1, (yyvsp[0].ptableRef)); }
    break;

  case 45:
#line 471 "OW_WQLParser.yy"
    { (yyvsp[-2].pfromList)->push_back((yyvsp[0].ptableRef)); delete (yyvsp[-1].pstring); (yyval.pfromList) = (yyvsp[-2].pfromList); }
    break;

  case 46:
#line 477 "OW_WQLParser.yy"
    { (yyval.poptFromClause) = 0; }
    break;

  case 47:
#line 479 "OW_WQLParser.yy"
    { (yyval.poptFromClause) = new optFromClause_FROM_fromList((yyvsp[-1].pstring), (yyvsp[0].pfromList)); }
    break;

  case 48:
#line 485 "OW_WQLParser.yy"
    { (yyval.ptableRef) = new tableRef_relationExpr((yyvsp[0].prelationExpr)); }
    break;

  case 49:
#line 487 "OW_WQLParser.yy"
    { (yyval.ptableRef) = new tableRef_relationExpr_aliasClause((yyvsp[-1].prelationExpr), (yyvsp[0].paliasClause)); }
    break;

  case 50:
#line 489 "OW_WQLParser.yy"
    { (yyval.ptableRef) = new tableRef_joinedTable((yyvsp[0].pjoinedTable)); }
    break;

  case 51:
#line 491 "OW_WQLParser.yy"
    { (yyval.ptableRef) = new tableRef_LEFTPAREN_joinedTable_RIGHTPAREN_aliasClause((yyvsp[-3].pstring), (yyvsp[-2].pjoinedTable), (yyvsp[-1].pstring), (yyvsp[0].paliasClause)); }
    break;

  case 52:
#line 497 "OW_WQLParser.yy"
    { (yyval.pjoinedTable) = new joinedTable_LEFTPAREN_joinedTable_RIGHTPAREN((yyvsp[-2].pstring), (yyvsp[-1].pjoinedTable), (yyvsp[0].pstring)); }
    break;

  case 53:
#line 499 "OW_WQLParser.yy"
    { (yyval.pjoinedTable) = new joinedTable_tableRef_CROSS_JOIN_tableRef((yyvsp[-3].ptableRef), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].ptableRef)); }
    break;

  case 54:
#line 501 "OW_WQLParser.yy"
    { (yyval.pjoinedTable) = new joinedTable_tableRef_UNIONJOIN_tableRef((yyvsp[-2].ptableRef), (yyvsp[-1].pstring), (yyvsp[0].ptableRef)); }
    break;

  case 55:
#line 503 "OW_WQLParser.yy"
    { (yyval.pjoinedTable) = new joinedTable_tableRef_joinType_JOIN_tableRef_joinQual((yyvsp[-4].ptableRef), (yyvsp[-3].pjoinType), (yyvsp[-2].pstring), (yyvsp[-1].ptableRef), (yyvsp[0].pjoinQual)); }
    break;

  case 56:
#line 505 "OW_WQLParser.yy"
    { (yyval.pjoinedTable) = new joinedTable_tableRef_JOIN_tableRef_joinQual((yyvsp[-3].ptableRef), (yyvsp[-2].pstring), (yyvsp[-1].ptableRef), (yyvsp[0].pjoinQual)); }
    break;

  case 57:
#line 507 "OW_WQLParser.yy"
    { (yyval.pjoinedTable) = new joinedTable_tableRef_NATURAL_joinType_JOIN_tableRef((yyvsp[-4].ptableRef), (yyvsp[-3].pstring), (yyvsp[-2].pjoinType), (yyvsp[-1].pstring), (yyvsp[0].ptableRef)); }
    break;

  case 58:
#line 509 "OW_WQLParser.yy"
    { (yyval.pjoinedTable) = new joinedTable_tableRef_NATURAL_JOIN_tableRef((yyvsp[-3].ptableRef), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].ptableRef)); }
    break;

  case 59:
#line 515 "OW_WQLParser.yy"
    { (yyval.paliasClause) = new aliasClause_AS_strColId_LEFTPAREN_nameList_RIGHTPAREN((yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pnameList), (yyvsp[0].pstring)); }
    break;

  case 60:
#line 517 "OW_WQLParser.yy"
    { (yyval.paliasClause) = new aliasClause_AS_strColId((yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 61:
#line 519 "OW_WQLParser.yy"
    { (yyval.paliasClause) = new aliasClause_strColId_LEFTPAREN_nameList_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pnameList), (yyvsp[0].pstring)); }
    break;

  case 62:
#line 521 "OW_WQLParser.yy"
    { (yyval.paliasClause) = new aliasClause_strColId((yyvsp[0].pstring)); }
    break;

  case 63:
#line 527 "OW_WQLParser.yy"
    { (yyval.pjoinType) = new joinType_FULL_strOptJoinOuter((yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 64:
#line 529 "OW_WQLParser.yy"
    { (yyval.pjoinType) = new joinType_LEFT_strOptJoinOuter((yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 65:
#line 531 "OW_WQLParser.yy"
    { (yyval.pjoinType) = new joinType_RIGHT_strOptJoinOuter((yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 66:
#line 533 "OW_WQLParser.yy"
    { (yyval.pjoinType) = new joinType_INNERP((yyvsp[0].pstring)); }
    break;

  case 67:
#line 539 "OW_WQLParser.yy"
    { (yyval.pstring) = 0; }
    break;

  case 68:
#line 541 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 69:
#line 547 "OW_WQLParser.yy"
    { (yyval.pjoinQual) = new joinQual_USING_LEFTPAREN_nameList_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pnameList), (yyvsp[0].pstring)); }
    break;

  case 70:
#line 549 "OW_WQLParser.yy"
    { (yyval.pjoinQual) = new joinQual_ON_aExpr((yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 71:
#line 555 "OW_WQLParser.yy"
    { (yyval.prelationExpr) = new relationExpr_strRelationName((yyvsp[0].pstring)); }
    break;

  case 72:
#line 557 "OW_WQLParser.yy"
    { (yyval.prelationExpr) = new relationExpr_strRelationName_ASTERISK((yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 73:
#line 559 "OW_WQLParser.yy"
    { (yyval.prelationExpr) = new relationExpr_ONLY_strRelationName((yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 74:
#line 565 "OW_WQLParser.yy"
    { (yyval.poptWhereClause) = 0; }
    break;

  case 75:
#line 567 "OW_WQLParser.yy"
    { (yyval.poptWhereClause) = new optWhereClause_WHERE_aExpr((yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 76:
#line 573 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("YEAR"); }
    break;

  case 77:
#line 575 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("MONTH"); }
    break;

  case 78:
#line 577 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("DAY"); }
    break;

  case 79:
#line 579 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("HOUR"); }
    break;

  case 80:
#line 581 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("MINUTE"); }
    break;

  case 81:
#line 583 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("SECOND"); }
    break;

  case 82:
#line 589 "OW_WQLParser.yy"
    { (yyval.prowExpr) = new rowExpr((yyvsp[-6].pstring), (yyvsp[-5].prowDescriptor), (yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].prowDescriptor), (yyvsp[0].pstring)); }
    break;

  case 83:
#line 595 "OW_WQLParser.yy"
    { (yyval.prowList) = new List<aExpr*>(1, (yyvsp[0].paExpr)); }
    break;

  case 84:
#line 597 "OW_WQLParser.yy"
    { (yyvsp[-2].prowList)->push_back((yyvsp[0].paExpr)); delete (yyvsp[-1].pstring); (yyval.prowList) = (yyvsp[-2].prowList); }
    break;

  case 85:
#line 603 "OW_WQLParser.yy"
    { (yyval.prowDescriptor) = new rowDescriptor((yyvsp[-2].prowList), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 86:
#line 609 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 87:
#line 611 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 88:
#line 613 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 89:
#line 615 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 90:
#line 617 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 91:
#line 619 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 92:
#line 621 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 93:
#line 623 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 94:
#line 625 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 95:
#line 627 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 96:
#line 629 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 97:
#line 631 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 98:
#line 633 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 99:
#line 635 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 100:
#line 637 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 101:
#line 639 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 102:
#line 645 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_cExpr((yyvsp[0].pcExpr)); }
    break;

  case 103:
#line 647 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_AT_TIME_ZONE_cExpr((yyvsp[-4].paExpr), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pcExpr)); }
    break;

  case 104:
#line 649 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_PLUS_aExpr((yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 105:
#line 651 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_MINUS_aExpr((yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 106:
#line 653 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_BITINVERT_aExpr((yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 107:
#line 655 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_PLUS_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 108:
#line 657 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_MINUS_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 109:
#line 659 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_ASTERISK_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 110:
#line 661 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_SOLIDUS_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 111:
#line 663 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_PERCENT_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 112:
#line 665 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_BITAND_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 113:
#line 667 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_BITOR_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 114:
#line 669 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_BITSHIFTLEFT_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 115:
#line 671 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_BITSHIFTRIGHT_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 116:
#line 673 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_LESSTHAN_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 117:
#line 675 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_LESSTHANOREQUALS_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 118:
#line 677 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_GREATERTHAN_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 119:
#line 679 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_GREATERTHANOREQUALS_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 120:
#line 681 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_EQUALS_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 121:
#line 683 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_NOTEQUALS_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 122:
#line 685 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_AND_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 123:
#line 687 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_OR_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 124:
#line 689 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_NOT_aExpr((yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 125:
#line 691 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_CONCATENATION_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 126:
#line 693 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_LIKE_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 127:
#line 695 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_LIKE_aExpr_ESCAPE_aExpr((yyvsp[-4].paExpr), (yyvsp[-3].pstring), (yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 128:
#line 697 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_NOT_LIKE_aExpr((yyvsp[-3].paExpr), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 129:
#line 699 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_NOT_LIKE_aExpr_ESCAPE_aExpr((yyvsp[-5].paExpr), (yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 130:
#line 701 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_ISNULL((yyvsp[-1].paExpr), (yyvsp[0].pstring)); }
    break;

  case 131:
#line 703 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_IS_NULLP((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 132:
#line 705 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_NOTNULL((yyvsp[-1].paExpr), (yyvsp[0].pstring)); }
    break;

  case 133:
#line 707 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_IS_NOT_NULLP((yyvsp[-3].paExpr), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 134:
#line 709 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_IS_TRUEP((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 135:
#line 711 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_IS_NOT_FALSEP((yyvsp[-3].paExpr), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 136:
#line 713 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_IS_FALSEP((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 137:
#line 715 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_IS_NOT_TRUEP((yyvsp[-3].paExpr), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 138:
#line 717 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_aExpr_ISA_aExpr((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 139:
#line 719 "OW_WQLParser.yy"
    { (yyval.paExpr) = new aExpr_rowExpr((yyvsp[0].prowExpr)); }
    break;

  case 140:
#line 725 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_cExpr((yyvsp[0].pcExpr)); }
    break;

  case 141:
#line 727 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_PLUS_bExpr((yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 142:
#line 729 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_MINUS_bExpr((yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 143:
#line 731 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_BITINVERT_bExpr((yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 144:
#line 733 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_PLUS_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 145:
#line 735 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_MINUS_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 146:
#line 737 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_ASTERISK_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 147:
#line 739 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_SOLIDUS_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 148:
#line 741 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_PERCENT_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 149:
#line 743 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_BITAND_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 150:
#line 745 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_BITOR_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 151:
#line 747 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_BITSHIFTLEFT_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 152:
#line 749 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_BITSHIFTRIGHT_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 153:
#line 751 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_LESSTHAN_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 154:
#line 753 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_LESSTHANOREQUALS_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 155:
#line 755 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_GREATERTHAN_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 156:
#line 757 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_GREATERTHANOREQUALS_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 157:
#line 759 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_EQUALS_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 158:
#line 761 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_NOTEQUALS_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 159:
#line 763 "OW_WQLParser.yy"
    { (yyval.pbExpr) = new bExpr_bExpr_CONCATENATION_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 160:
#line 769 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_attr((yyvsp[0].pattr)); }
    break;

  case 161:
#line 771 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_strColId_optIndirection((yyvsp[-1].pstring), (yyvsp[0].poptIndirection)); }
    break;

  case 162:
#line 773 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_aExprConst((yyvsp[0].paExprConst)); }
    break;

  case 163:
#line 775 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_LEFTPAREN_aExpr_RIGHTPAREN((yyvsp[-2].pstring), (yyvsp[-1].paExpr), (yyvsp[0].pstring)); }
    break;

  case 164:
#line 777 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_strFuncName_LEFTPAREN_RIGHTPAREN((yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 165:
#line 779 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_strFuncName_LEFTPAREN_exprSeq_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pexprSeq), (yyvsp[0].pstring)); }
    break;

  case 166:
#line 781 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_strFuncName_LEFTPAREN_ALL_exprSeq_RIGHTPAREN((yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pexprSeq), (yyvsp[0].pstring)); }
    break;

  case 167:
#line 783 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_strFuncName_LEFTPAREN_DISTINCT_exprSeq_RIGHTPAREN((yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pexprSeq), (yyvsp[0].pstring)); }
    break;

  case 168:
#line 785 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_strFuncName_LEFTPAREN_ASTERISK_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 169:
#line 787 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_CURRENTDATE((yyvsp[0].pstring)); }
    break;

  case 170:
#line 789 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_CURRENTTIME((yyvsp[0].pstring)); }
    break;

  case 171:
#line 791 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_CURRENTTIME_LEFTPAREN_ICONST_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 172:
#line 793 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_CURRENTTIMESTAMP((yyvsp[0].pstring)); }
    break;

  case 173:
#line 795 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_CURRENTTIMESTAMP_LEFTPAREN_ICONST_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 174:
#line 797 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_CURRENTUSER((yyvsp[0].pstring)); }
    break;

  case 175:
#line 799 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_SESSIONUSER((yyvsp[0].pstring)); }
    break;

  case 176:
#line 801 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_USER((yyvsp[0].pstring)); }
    break;

  case 177:
#line 803 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_EXTRACT_LEFTPAREN_optExtract_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].poptExtract), (yyvsp[0].pstring)); }
    break;

  case 178:
#line 805 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_POSITION_LEFTPAREN_positionExpr_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].ppositionExpr), (yyvsp[0].pstring)); }
    break;

  case 179:
#line 807 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_SUBSTRING_LEFTPAREN_optSubstrExpr_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].poptSubstrExpr), (yyvsp[0].pstring)); }
    break;

  case 180:
#line 809 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_TRIM_LEFTPAREN_LEADING_trimExpr_RIGHTPAREN((yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].ptrimExpr), (yyvsp[0].pstring)); }
    break;

  case 181:
#line 811 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_TRIM_LEFTPAREN_TRAILING_trimExpr_RIGHTPAREN((yyvsp[-4].pstring), (yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].ptrimExpr), (yyvsp[0].pstring)); }
    break;

  case 182:
#line 813 "OW_WQLParser.yy"
    { (yyval.pcExpr) = new cExpr_TRIM_LEFTPAREN_trimExpr_RIGHTPAREN((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].ptrimExpr), (yyvsp[0].pstring)); }
    break;

  case 183:
#line 819 "OW_WQLParser.yy"
    { (yyval.poptIndirection) = 0; }
    break;

  case 184:
#line 821 "OW_WQLParser.yy"
    { (yyval.poptIndirection) = new optIndirection_optIndirection_LEFTBRACKET_aExpr_RIGHTBRACKET((yyvsp[-3].poptIndirection), (yyvsp[-2].pstring), (yyvsp[-1].paExpr), (yyvsp[0].pstring)); }
    break;

  case 185:
#line 823 "OW_WQLParser.yy"
    { (yyval.poptIndirection) = new optIndirection_optIndirection_LEFTBRACKET_aExpr_COLON_aExpr_RIGHTBRACKET((yyvsp[-5].poptIndirection), (yyvsp[-4].pstring), (yyvsp[-3].paExpr), (yyvsp[-2].pstring), (yyvsp[-1].paExpr), (yyvsp[0].pstring)); }
    break;

  case 186:
#line 829 "OW_WQLParser.yy"
    { (yyval.poptExtract) = 0; }
    break;

  case 187:
#line 831 "OW_WQLParser.yy"
    { (yyval.poptExtract) = new optExtract_strExtractArg_FROM_aExpr((yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 188:
#line 837 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 189:
#line 839 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 190:
#line 841 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 191:
#line 843 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("TIMEZONE_HOUR"); }
    break;

  case 192:
#line 845 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("TIMEZONE_MINUTE"); }
    break;

  case 193:
#line 851 "OW_WQLParser.yy"
    { (yyval.ppositionExpr) = new positionExpr_bExpr_IN_bExpr((yyvsp[-2].pbExpr), (yyvsp[-1].pstring), (yyvsp[0].pbExpr)); }
    break;

  case 194:
#line 853 "OW_WQLParser.yy"
    { (yyval.ppositionExpr) = 0; }
    break;

  case 195:
#line 859 "OW_WQLParser.yy"
    { (yyval.poptSubstrExpr) = 0; }
    break;

  case 196:
#line 861 "OW_WQLParser.yy"
    { (yyval.poptSubstrExpr) = new optSubstrExpr_aExpr_substrFrom_substrFor((yyvsp[-2].paExpr), (yyvsp[-1].psubstrFrom), (yyvsp[0].psubstrFor)); }
    break;

  case 197:
#line 863 "OW_WQLParser.yy"
    { (yyval.poptSubstrExpr) = new optSubstrExpr_aExpr_substrFor_substrFrom((yyvsp[-2].paExpr), (yyvsp[-1].psubstrFor), (yyvsp[0].psubstrFrom)); }
    break;

  case 198:
#line 865 "OW_WQLParser.yy"
    { (yyval.poptSubstrExpr) = new optSubstrExpr_aExpr_substrFrom((yyvsp[-1].paExpr), (yyvsp[0].psubstrFrom)); }
    break;

  case 199:
#line 867 "OW_WQLParser.yy"
    { (yyval.poptSubstrExpr) = new optSubstrExpr_aExpr_substrFor((yyvsp[-1].paExpr), (yyvsp[0].psubstrFor)); }
    break;

  case 200:
#line 869 "OW_WQLParser.yy"
    { (yyval.poptSubstrExpr) = new optSubstrExpr_exprSeq((yyvsp[0].pexprSeq)); }
    break;

  case 201:
#line 875 "OW_WQLParser.yy"
    { (yyval.psubstrFrom) = new substrFrom((yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 202:
#line 881 "OW_WQLParser.yy"
    { (yyval.psubstrFor) = new substrFor((yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 203:
#line 887 "OW_WQLParser.yy"
    { (yyval.ptrimExpr) = new trimExpr_aExpr_FROM_exprSeq((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].pexprSeq)); }
    break;

  case 204:
#line 889 "OW_WQLParser.yy"
    { (yyval.ptrimExpr) = new trimExpr_FROM_exprSeq((yyvsp[-1].pstring), (yyvsp[0].pexprSeq)); }
    break;

  case 205:
#line 891 "OW_WQLParser.yy"
    { (yyval.ptrimExpr) = new trimExpr_exprSeq((yyvsp[0].pexprSeq)); }
    break;

  case 206:
#line 897 "OW_WQLParser.yy"
    { (yyval.pattr) = new attr((yyvsp[-3].pstring), (yyvsp[-2].pstring), (yyvsp[-1].pattrs), (yyvsp[0].poptIndirection)); }
    break;

  case 207:
#line 903 "OW_WQLParser.yy"
    { (yyval.pattrs) = new attrs_strAttrName((yyvsp[0].pstring)); }
    break;

  case 208:
#line 905 "OW_WQLParser.yy"
    { (yyval.pattrs) = new attrs_attrs_PERIOD_strAttrName((yyvsp[-2].pattrs), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 209:
#line 907 "OW_WQLParser.yy"
    { (yyval.pattrs) = new attrs_attrs_PERIOD_ASTERISK((yyvsp[-2].pattrs), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 210:
#line 913 "OW_WQLParser.yy"
    { (yyval.ptargetEl) = new targetEl_aExpr_AS_strColLabel((yyvsp[-2].paExpr), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 211:
#line 915 "OW_WQLParser.yy"
    { (yyval.ptargetEl) = new targetEl_aExpr((yyvsp[0].paExpr)); }
    break;

  case 212:
#line 917 "OW_WQLParser.yy"
    { (yyval.ptargetEl) = new targetEl_strRelationName_PERIOD_ASTERISK((yyvsp[-2].pstring), (yyvsp[-1].pstring), (yyvsp[0].pstring)); }
    break;

  case 213:
#line 919 "OW_WQLParser.yy"
    { (yyval.ptargetEl) = new targetEl_ASTERISK((yyvsp[0].pstring)); }
    break;

  case 214:
#line 925 "OW_WQLParser.yy"
    { (yyval.pupdateTargetEl) = new updateTargetEl((yyvsp[-3].pstring), (yyvsp[-2].poptIndirection), (yyvsp[-1].pstring), (yyvsp[0].paExpr)); }
    break;

  case 215:
#line 931 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 216:
#line 937 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 217:
#line 943 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 218:
#line 949 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 219:
#line 951 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("IN"); }
    break;

  case 220:
#line 953 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("IS"); }
    break;

  case 221:
#line 955 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ISNULL"); }
    break;

  case 222:
#line 957 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("LIKE"); }
    break;

  case 223:
#line 959 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("NOTNULL"); }
    break;

  case 224:
#line 965 "OW_WQLParser.yy"
    { (yyval.paExprConst) = new aExprConst_ICONST((yyvsp[0].pstring)); }
    break;

  case 225:
#line 967 "OW_WQLParser.yy"
    { (yyval.paExprConst) = new aExprConst_FCONST((yyvsp[0].pstring)); }
    break;

  case 226:
#line 969 "OW_WQLParser.yy"
    { (yyval.paExprConst) = new aExprConst_SCONST((yyvsp[0].pstring)); }
    break;

  case 227:
#line 971 "OW_WQLParser.yy"
    { (yyval.paExprConst) = new aExprConst_BITCONST((yyvsp[0].pstring)); }
    break;

  case 228:
#line 973 "OW_WQLParser.yy"
    { (yyval.paExprConst) = new aExprConst_HEXCONST((yyvsp[0].pstring)); }
    break;

  case 229:
#line 975 "OW_WQLParser.yy"
    { (yyval.paExprConst) = new aExprConst_TRUEP(new String("TRUE")); }
    break;

  case 230:
#line 977 "OW_WQLParser.yy"
    { (yyval.paExprConst) = new aExprConst_FALSEP(new String("FALSE")); }
    break;

  case 231:
#line 979 "OW_WQLParser.yy"
    { (yyval.paExprConst) = new aExprConst_NULLP(new String("NULL")); }
    break;

  case 232:
#line 985 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 233:
#line 987 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 234:
#line 989 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("AT"); }
    break;

  case 235:
#line 991 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("BY"); }
    break;

  case 236:
#line 993 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("DELETE"); }
    break;

  case 237:
#line 995 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ESCAPE"); }
    break;

  case 238:
#line 997 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("INSERT"); }
    break;

  case 239:
#line 999 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("SET"); }
    break;

  case 240:
#line 1001 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("TIMEZONE_HOUR"); }
    break;

  case 241:
#line 1003 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("TIMEZONE_MINUTE"); }
    break;

  case 242:
#line 1005 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("UPDATE"); }
    break;

  case 243:
#line 1007 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("VALUES"); }
    break;

  case 244:
#line 1009 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ZONE"); }
    break;

  case 245:
#line 1011 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("INTERVAL"); }
    break;

  case 246:
#line 1013 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("NATIONAL"); }
    break;

  case 247:
#line 1015 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("TIME"); }
    break;

  case 248:
#line 1017 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("TIMESTAMP"); }
    break;

  case 249:
#line 1023 "OW_WQLParser.yy"
    { (yyval.pstring) = (yyvsp[0].pstring); }
    break;

  case 250:
#line 1025 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ALL"); }
    break;

  case 251:
#line 1027 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("AND"); }
    break;

  case 252:
#line 1029 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ASC"); }
    break;

  case 253:
#line 1031 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("CROSS"); }
    break;

  case 254:
#line 1033 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("CURRENT_DATE"); }
    break;

  case 255:
#line 1035 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("CURRENT_TIME"); }
    break;

  case 256:
#line 1037 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("CURRENT_TIMESTAMP"); }
    break;

  case 257:
#line 1039 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("CURRENT_USER"); }
    break;

  case 258:
#line 1041 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("DEFAULT"); }
    break;

  case 259:
#line 1043 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("DESC"); }
    break;

  case 260:
#line 1045 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("DISTINCT"); }
    break;

  case 261:
#line 1047 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("EXTRACT"); }
    break;

  case 262:
#line 1049 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("FALSE"); }
    break;

  case 263:
#line 1051 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("FOR"); }
    break;

  case 264:
#line 1053 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("FROM"); }
    break;

  case 265:
#line 1055 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("FULL"); }
    break;

  case 266:
#line 1057 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("GROUP"); }
    break;

  case 267:
#line 1059 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("HAVING"); }
    break;

  case 268:
#line 1061 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("IN"); }
    break;

  case 269:
#line 1063 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("INNER"); }
    break;

  case 270:
#line 1065 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("INTO"); }
    break;

  case 271:
#line 1067 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("IS"); }
    break;

  case 272:
#line 1069 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ISA"); }
    break;

  case 273:
#line 1071 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ISNULL"); }
    break;

  case 274:
#line 1073 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("JOIN"); }
    break;

  case 275:
#line 1075 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("LEADING"); }
    break;

  case 276:
#line 1077 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("LEFT"); }
    break;

  case 277:
#line 1079 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("LIKE"); }
    break;

  case 278:
#line 1081 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("NATURAL"); }
    break;

  case 279:
#line 1083 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("NOT"); }
    break;

  case 280:
#line 1085 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("NOTNULL"); }
    break;

  case 281:
#line 1087 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("NULL"); }
    break;

  case 282:
#line 1089 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ON"); }
    break;

  case 283:
#line 1091 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ONLY"); }
    break;

  case 284:
#line 1093 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("OR"); }
    break;

  case 285:
#line 1095 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("ORDER"); }
    break;

  case 286:
#line 1097 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("OUTER"); }
    break;

  case 287:
#line 1099 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("POSITION"); }
    break;

  case 288:
#line 1101 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("RIGHT"); }
    break;

  case 289:
#line 1103 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("SELECT"); }
    break;

  case 290:
#line 1105 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("SESSION_USER"); }
    break;

  case 291:
#line 1107 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("SUBSTRING"); }
    break;

  case 292:
#line 1109 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("TRAILING"); }
    break;

  case 293:
#line 1111 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("TRIM"); }
    break;

  case 294:
#line 1113 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("TRUE"); }
    break;

  case 295:
#line 1115 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("UNION"); }
    break;

  case 296:
#line 1117 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("USER"); }
    break;

  case 297:
#line 1119 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("USING"); }
    break;

  case 298:
#line 1121 "OW_WQLParser.yy"
    { (yyval.pstring) = new String("WHERE"); }
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3819 "OW_WQLParser.cc"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytname[yytype];
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytname[yyx];
		yysize1 = yysize + yytnamerr (0, yytname[yyx]);
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1124 "OW_WQLParser.yy"





