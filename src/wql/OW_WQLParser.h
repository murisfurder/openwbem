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
/* Line 1447 of yacc.c.  */
#line 300 "OW_WQLParser.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE owwqllval;



