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
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse owmofparse
#define yylex   owmoflex
#define yyerror owmoferror
#define yylval  owmoflval
#define yychar  owmofchar
#define yydebug owmofdebug
#define yynerrs owmofnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ANY_TOK = 258,
     AS_TOK = 259,
     ASSOCIATION_TOK = 260,
     CLASS_TOK = 261,
     DISABLEOVERRIDE_TOK = 262,
     DT_BOOL_TOK = 263,
     DT_CHAR16_TOK = 264,
     DT_DATETIME_TOK = 265,
     DT_REAL32_TOK = 266,
     DT_REAL64_TOK = 267,
     DT_SINT16_TOK = 268,
     DT_SINT32_TOK = 269,
     DT_SINT64_TOK = 270,
     DT_SINT8_TOK = 271,
     DT_STR_TOK = 272,
     DT_UINT16_TOK = 273,
     DT_UINT32_TOK = 274,
     DT_UINT64_TOK = 275,
     DT_UINT8_TOK = 276,
     ENABLEOVERRIDE_TOK = 277,
     FALSE_TOK = 278,
     FLAVOR_TOK = 279,
     INDICATION_TOK = 280,
     INSTANCE_TOK = 281,
     METHOD_TOK = 282,
     NULL_TOK = 283,
     OF_TOK = 284,
     PARAMETER_TOK = 285,
     PRAGMA_TOK = 286,
     PROPERTY_TOK = 287,
     QUALIFIER_TOK = 288,
     REF_TOK = 289,
     REFERENCE_TOK = 290,
     RESTRICTED_TOK = 291,
     SCHEMA_TOK = 292,
     SCOPE_TOK = 293,
     TOSUBCLASS_TOK = 294,
     TRANSLATABLE_TOK = 295,
     TRUE_TOK = 296,
     LPAREN_TOK = 297,
     RPAREN_TOK = 298,
     LBRACE_TOK = 299,
     RBRACE_TOK = 300,
     SEMICOLON_TOK = 301,
     LBRACK_TOK = 302,
     RBRACK_TOK = 303,
     COMMA_TOK = 304,
     DOLLAR_TOK = 305,
     COLON_TOK = 306,
     EQUALS_TOK = 307,
     IDENTIFIER_TOK = 308,
     stringValue = 309,
     floatValue = 310,
     charValue = 311,
     binaryValue = 312,
     octalValue = 313,
     decimalValue = 314,
     hexValue = 315
   };
#endif
/* Tokens.  */
#define ANY_TOK 258
#define AS_TOK 259
#define ASSOCIATION_TOK 260
#define CLASS_TOK 261
#define DISABLEOVERRIDE_TOK 262
#define DT_BOOL_TOK 263
#define DT_CHAR16_TOK 264
#define DT_DATETIME_TOK 265
#define DT_REAL32_TOK 266
#define DT_REAL64_TOK 267
#define DT_SINT16_TOK 268
#define DT_SINT32_TOK 269
#define DT_SINT64_TOK 270
#define DT_SINT8_TOK 271
#define DT_STR_TOK 272
#define DT_UINT16_TOK 273
#define DT_UINT32_TOK 274
#define DT_UINT64_TOK 275
#define DT_UINT8_TOK 276
#define ENABLEOVERRIDE_TOK 277
#define FALSE_TOK 278
#define FLAVOR_TOK 279
#define INDICATION_TOK 280
#define INSTANCE_TOK 281
#define METHOD_TOK 282
#define NULL_TOK 283
#define OF_TOK 284
#define PARAMETER_TOK 285
#define PRAGMA_TOK 286
#define PROPERTY_TOK 287
#define QUALIFIER_TOK 288
#define REF_TOK 289
#define REFERENCE_TOK 290
#define RESTRICTED_TOK 291
#define SCHEMA_TOK 292
#define SCOPE_TOK 293
#define TOSUBCLASS_TOK 294
#define TRANSLATABLE_TOK 295
#define TRUE_TOK 296
#define LPAREN_TOK 297
#define RPAREN_TOK 298
#define LBRACE_TOK 299
#define RBRACE_TOK 300
#define SEMICOLON_TOK 301
#define LBRACK_TOK 302
#define RBRACK_TOK 303
#define COMMA_TOK 304
#define DOLLAR_TOK 305
#define COLON_TOK 306
#define EQUALS_TOK 307
#define IDENTIFIER_TOK 308
#define stringValue 309
#define floatValue 310
#define charValue 311
#define binaryValue 312
#define octalValue 313
#define decimalValue 314
#define hexValue 315




/* Copy the first part of user declarations.  */
#line 36 "OW_MOFParser.yy"

/*************** Includes and Defines *****************************/
#include <stdio.h> /* for debugging */
#include <assert.h>
#include "OW_MOFGrammar.hpp"
#include "OW_String.hpp"
#include "OW_Array.hpp"
#include "OW_MOFCompiler.hpp"
#include "OW_MOFParserDecls.hpp"

using namespace OpenWBEM;
using namespace OpenWBEM::MOF;

namespace OW_NAMESPACE
{
OW_DEFINE_EXCEPTION(MOFParser)
}

//#define YYDEBUG 1

// Lexer functions
void lexIncludeFile( void* context, const String& filename );
void yyerror( const char* );

/* This is so we can avoid static variables and pass a pointer into yyparse */
#define YYPARSE_PARAM context
#define MOF_COMPILER (reinterpret_cast<Compiler*>(context))


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
#line 87 "OW_MOFParser.yy"
typedef union YYSTYPE {
	MOFSpecification*				pMOFSpecification;
	List<MOFProduction*>*		pMOFProductionList;
	MOFProduction*					pMOFProduction;
	IndicDeclaration*				pIndicDeclaration;
	ClassDeclaration*				pClassDeclaration;
	PropertyDeclaration*			pPropertyDeclaration;
	ObjectRef*						pObjectRef;
	Parameter*						pParameter;
	::OpenWBEM::MOF::Array*							pArray;
	CompilerDirective*			pCompilerDirective;
	MetaElement*					pMetaElement;
	List<MetaElement*>*			pMetaElementList;
	Initializer*					pInitializer;
	SuperClass*						pSuperClass;
	AssociationFeature*			pAssociationFeature;
	List<AssociationFeature*>*	pAssociationFeatureList;
	QualifierParameter*			pQualifierParameter;
	QualifierDeclaration*		pQualifierDeclaration;
	PragmaParameter*				pPragmaParameter;
	AssocDeclaration*				pAssocDeclaration;
	DefaultValue*					pDefaultValue;
	ClassFeature*					pClassFeature;
	List<ClassFeature*>*			pClassFeatureList;
	ReferenceInitializer*		pReferenceInitializer;
	QualifierType*					pQualifierType;
	DefaultFlavor*					pDefaultFlavor;
	String*							pString;
	IntegerValue*              pIntegerValue;
	ConstantValue*             pConstantValue;
	ArrayInitializer*				pArrayInitializer;
	ValueInitializer*				pValueInitializer;
	List<ValueInitializer*>*	pValueInitializerList;
	Flavor*							pFlavor;
	List<Flavor*>*					pFlavorList;
	List<ConstantValue*>*				pConstantValueList;
	Alias*							pAlias;
	List<Qualifier*>*				pQualifierList;
	ReferenceDeclaration*		pReferenceDeclaration;
	MethodDeclaration*			pMethodDeclaration;
	Qualifier*						pQualifier;
	List<Parameter*>*				pParameterList;
	Scope*							pScope;
	InstanceDeclaration*			pInstanceDeclaration;
	PragmaName*						pPragmaName;
	ClassName*						pClassName;
	AliasIdentifier*				pAliasIdentifier;
	QualifierName*					pQualifierName;
	PropertyName*					pPropertyName;
	ReferenceName*					pReferenceName;
	MethodName*						pMethodName;
	ParameterName*					pParameterName;
	DataType*						pDataType;
	ObjectHandle*					pObjectHandle;
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 298 "OW_MOFParser.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 143 "OW_MOFParser.yy"

#define YYLEX_PARAM context
int yylex(YYSTYPE *yylval, void* YYLEX_PARAM);


/* Line 219 of yacc.c.  */
#line 314 "OW_MOFParser.cc"

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1576

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  59
/* YYNRULES -- Number of rules. */
#define YYNRULES  182
/* YYNRULES -- Number of states. */
#define YYNSTATES  351

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    13,    15,    17,
      19,    21,    27,    29,    31,    38,    46,    54,    63,    71,
      80,    89,    99,   100,   103,   114,   126,   138,   151,   152,
     156,   157,   160,   171,   183,   195,   208,   210,   213,   216,
     219,   221,   223,   225,   227,   232,   234,   238,   241,   246,
     248,   251,   255,   257,   259,   261,   263,   265,   267,   271,
     276,   281,   287,   292,   298,   304,   311,   315,   320,   325,
     331,   337,   344,   351,   359,   361,   363,   365,   367,   369,
     371,   373,   375,   377,   379,   381,   383,   385,   387,   389,
     391,   393,   396,   398,   402,   405,   409,   413,   418,   421,
     425,   429,   434,   436,   439,   443,   446,   448,   450,   452,
     456,   459,   461,   465,   467,   470,   472,   474,   476,   478,
     480,   482,   484,   486,   488,   490,   492,   494,   496,   502,
     509,   511,   514,   518,   522,   527,   533,   535,   539,   541,
     543,   545,   547,   549,   551,   553,   555,   557,   559,   565,
     567,   571,   579,   588,   597,   607,   609,   612,   616,   621,
     623,   625,   627,   629,   631,   633,   635,   637,   639,   641,
     643,   645,   647,   649,   651,   653,   655,   657,   659,   661,
     663,   665,   667
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      62,     0,    -1,    63,    -1,    -1,    63,    64,    -1,    65,
      -1,    68,    -1,    70,    -1,    73,    -1,   106,    -1,   114,
      -1,    31,    66,    42,    67,    43,    -1,   119,    -1,    54,
      -1,     6,    74,    44,    69,    45,    46,    -1,     6,    74,
      77,    44,    69,    45,    46,    -1,     6,    74,    75,    44,
      69,    45,    46,    -1,     6,    74,    75,    77,    44,    69,
      45,    46,    -1,    80,     6,    74,    44,    69,    45,    46,
      -1,    80,     6,    74,    77,    44,    69,    45,    46,    -1,
      80,     6,    74,    75,    44,    69,    45,    46,    -1,    80,
       6,    74,    75,    77,    44,    69,    45,    46,    -1,    -1,
      69,    78,    -1,    47,     5,    71,    48,     6,    74,    44,
      72,    45,    46,    -1,    47,     5,    71,    48,     6,    74,
      77,    44,    72,    45,    46,    -1,    47,     5,    71,    48,
       6,    74,    75,    44,    72,    45,    46,    -1,    47,     5,
      71,    48,     6,    74,    75,    77,    44,    72,    45,    46,
      -1,    -1,    71,    49,    81,    -1,    -1,    72,    79,    -1,
      47,    25,    71,    48,     6,    74,    44,    69,    45,    46,
      -1,    47,    25,    71,    48,     6,    74,    77,    44,    69,
      45,    46,    -1,    47,    25,    71,    48,     6,    74,    75,
      44,    69,    45,    46,    -1,    47,    25,    71,    48,     6,
      74,    75,    77,    44,    69,    45,    46,    -1,   119,    -1,
       4,    76,    -1,    50,   119,    -1,    51,    74,    -1,    85,
      -1,    87,    -1,    86,    -1,    78,    -1,    47,    81,    71,
      48,    -1,   107,    -1,   107,    51,    82,    -1,   107,    83,
      -1,   107,    83,    51,    82,    -1,    84,    -1,    82,    84,
      -1,    42,   102,    43,    -1,    99,    -1,    22,    -1,     7,
      -1,    36,    -1,    39,    -1,    40,    -1,    91,    88,    46,
      -1,    91,    88,    97,    46,    -1,    91,    88,    96,    46,
      -1,    91,    88,    96,    97,    46,    -1,    80,    91,    88,
      46,    -1,    80,    91,    88,    97,    46,    -1,    80,    91,
      88,    96,    46,    -1,    80,    91,    88,    96,    97,    46,
      -1,    92,    89,    46,    -1,    92,    89,    97,    46,    -1,
      80,    92,    89,    46,    -1,    80,    92,    89,    97,    46,
      -1,    91,    90,    42,    43,    46,    -1,    91,    90,    42,
      93,    43,    46,    -1,    80,    91,    90,    42,    43,    46,
      -1,    80,    91,    90,    42,    93,    43,    46,    -1,   119,
      -1,   119,    -1,   119,    -1,    21,    -1,    16,    -1,    18,
      -1,    13,    -1,    19,    -1,    14,    -1,    20,    -1,    15,
      -1,    11,    -1,    12,    -1,     9,    -1,    17,    -1,     8,
      -1,    10,    -1,    74,    34,    -1,    94,    -1,    93,    49,
      94,    -1,    91,    95,    -1,    91,    95,    96,    -1,    80,
      91,    95,    -1,    80,    91,    95,    96,    -1,    92,    95,
      -1,    92,    95,    96,    -1,    80,    92,    95,    -1,    80,
      92,    95,    96,    -1,   119,    -1,    47,    48,    -1,    47,
     103,    48,    -1,    52,    98,    -1,   102,    -1,    99,    -1,
     104,    -1,    44,   100,    45,    -1,    44,    45,    -1,   102,
      -1,   100,    49,   102,    -1,    54,    -1,   101,    54,    -1,
     103,    -1,    55,    -1,    56,    -1,   101,    -1,   117,    -1,
     118,    -1,    57,    -1,    58,    -1,    59,    -1,    60,    -1,
     105,    -1,    76,    -1,   119,    -1,    33,   107,   108,   109,
      46,    -1,    33,   107,   108,   109,   112,    46,    -1,   119,
      -1,    51,    91,    -1,    51,    91,    97,    -1,    51,    91,
      96,    -1,    51,    91,    96,    97,    -1,    49,    38,    42,
     110,    43,    -1,   111,    -1,   110,    49,   111,    -1,    37,
      -1,     6,    -1,     5,    -1,    25,    -1,    33,    -1,    32,
      -1,    35,    -1,    27,    -1,    30,    -1,     3,    -1,    49,
      24,    42,   113,    43,    -1,    84,    -1,   113,    49,    84,
      -1,    26,    29,    74,    44,   115,    45,    46,    -1,    26,
      29,    74,    75,    44,   115,    45,    46,    -1,    80,    26,
      29,    74,    44,   115,    45,    46,    -1,    80,    26,    29,
      74,    75,    44,   115,    45,    46,    -1,   116,    -1,   115,
     116,    -1,   119,    97,    46,    -1,    80,   119,    97,    46,
      -1,    23,    -1,    41,    -1,    28,    -1,    53,    -1,     3,
      -1,     4,    -1,     6,    -1,     7,    -1,    91,    -1,    22,
      -1,    24,    -1,    26,    -1,    27,    -1,    29,    -1,    30,
      -1,    31,    -1,    32,    -1,    33,    -1,    35,    -1,    36,
      -1,    37,    -1,    38,    -1,    39,    -1,    40,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   212,   212,   217,   218,   222,   223,   224,   225,   226,
     227,   231,   245,   249,   253,   261,   269,   277,   285,   293,
     301,   309,   319,   320,   324,   335,   346,   357,   370,   371,
     375,   376,   380,   391,   402,   413,   427,   431,   435,   443,
     447,   448,   449,   453,   458,   463,   464,   469,   470,   478,
     479,   483,   489,   493,   494,   495,   496,   497,   501,   506,
     511,   516,   521,   526,   531,   536,   544,   549,   554,   559,
     567,   574,   581,   588,   598,   602,   606,   610,   611,   612,
     613,   614,   615,   616,   617,   618,   619,   620,   621,   622,
     623,   627,   631,   632,   636,   638,   640,   642,   644,   646,
     648,   650,   655,   659,   660,   665,   669,   670,   671,   675,
     677,   682,   683,   689,   690,   695,   696,   697,   698,   699,
     700,   704,   705,   706,   707,   711,   712,   716,   749,   755,
     764,   768,   773,   778,   783,   791,   802,   803,   808,   809,
     810,   811,   812,   813,   814,   815,   816,   817,   821,   832,
     833,   841,   850,   859,   868,   880,   881,   886,   888,   893,
     894,   898,   902,   903,   904,   906,   907,   908,   909,   910,
     912,   913,   915,   916,   917,   918,   919,   921,   922,   923,
     924,   925,   926
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ANY_TOK", "AS_TOK", "ASSOCIATION_TOK",
  "CLASS_TOK", "DISABLEOVERRIDE_TOK", "DT_BOOL_TOK", "DT_CHAR16_TOK",
  "DT_DATETIME_TOK", "DT_REAL32_TOK", "DT_REAL64_TOK", "DT_SINT16_TOK",
  "DT_SINT32_TOK", "DT_SINT64_TOK", "DT_SINT8_TOK", "DT_STR_TOK",
  "DT_UINT16_TOK", "DT_UINT32_TOK", "DT_UINT64_TOK", "DT_UINT8_TOK",
  "ENABLEOVERRIDE_TOK", "FALSE_TOK", "FLAVOR_TOK", "INDICATION_TOK",
  "INSTANCE_TOK", "METHOD_TOK", "NULL_TOK", "OF_TOK", "PARAMETER_TOK",
  "PRAGMA_TOK", "PROPERTY_TOK", "QUALIFIER_TOK", "REF_TOK",
  "REFERENCE_TOK", "RESTRICTED_TOK", "SCHEMA_TOK", "SCOPE_TOK",
  "TOSUBCLASS_TOK", "TRANSLATABLE_TOK", "TRUE_TOK", "LPAREN_TOK",
  "RPAREN_TOK", "LBRACE_TOK", "RBRACE_TOK", "SEMICOLON_TOK", "LBRACK_TOK",
  "RBRACK_TOK", "COMMA_TOK", "DOLLAR_TOK", "COLON_TOK", "EQUALS_TOK",
  "IDENTIFIER_TOK", "stringValue", "floatValue", "charValue",
  "binaryValue", "octalValue", "decimalValue", "hexValue", "$accept",
  "mofSpecification", "mofProductionList", "mofProduction",
  "compilerDirective", "pragmaName", "pragmaParameter", "classDeclaration",
  "classFeatureList", "assocDeclaration", "qualifierListEmpty",
  "associationFeatureList", "indicDeclaration", "className", "alias",
  "aliasIdentifier", "superClass", "classFeature", "associationFeature",
  "qualifierList", "qualifier", "flavorList", "qualifierParameter",
  "flavor", "propertyDeclaration", "referenceDeclaration",
  "methodDeclaration", "propertyName", "referenceName", "methodName",
  "dataType", "objectRef", "parameterList", "parameter", "parameterName",
  "array", "defaultValue", "initializer", "arrayInitializer",
  "constantValueList", "stringValueList", "constantValue", "integerValue",
  "referenceInitializer", "objectHandle", "qualifierDeclaration",
  "qualifierName", "qualifierType", "scope", "metaElementList",
  "metaElement", "defaultFlavor", "flavorListWithComma",
  "instanceDeclaration", "valueInitializerList", "valueInitializer",
  "booleanValue", "nullValue", "IDENTIFIER", 0
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
     315
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    61,    62,    63,    63,    64,    64,    64,    64,    64,
      64,    65,    66,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    70,    70,    70,    70,    71,    71,
      72,    72,    73,    73,    73,    73,    74,    75,    76,    77,
      78,    78,    78,    79,    80,    81,    81,    81,    81,    82,
      82,    83,    83,    84,    84,    84,    84,    84,    85,    85,
      85,    85,    85,    85,    85,    85,    86,    86,    86,    86,
      87,    87,    87,    87,    88,    89,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    92,    93,    93,    94,    94,    94,    94,    94,    94,
      94,    94,    95,    96,    96,    97,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   102,   102,   102,
     102,   103,   103,   103,   103,   104,   104,   105,   106,   106,
     107,   108,   108,   108,   108,   109,   110,   110,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   112,   113,
     113,   114,   114,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     5,     1,     1,     6,     7,     7,     8,     7,     8,
       8,     9,     0,     2,    10,    11,    11,    12,     0,     3,
       0,     2,    10,    11,    11,    12,     1,     2,     2,     2,
       1,     1,     1,     1,     4,     1,     3,     2,     4,     1,
       2,     3,     1,     1,     1,     1,     1,     1,     3,     4,
       4,     5,     4,     5,     5,     6,     3,     4,     4,     5,
       5,     6,     6,     7,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     3,     2,     3,     3,     4,     2,     3,
       3,     4,     1,     2,     3,     2,     1,     1,     1,     3,
       2,     1,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     6,
       1,     2,     3,     3,     4,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     1,
       3,     7,     8,     8,     9,     1,     2,     3,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     8,     0,     9,    10,   163,   164,   165,
     166,    89,    87,    90,    85,    86,    80,    82,    84,    78,
      88,    79,    81,    83,    77,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     162,     0,   167,    36,     0,     0,    12,     0,   130,    28,
      28,    28,    45,     0,     0,     0,    22,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,    52,     0,     0,     0,    37,     0,    39,    22,     0,
      22,     0,     0,    13,     0,   131,     0,     0,     0,     0,
       0,    44,   159,   161,   160,   113,   116,   117,   121,   122,
     123,   124,   118,     0,   115,   119,   120,   110,     0,   111,
      54,    53,    55,    56,    57,    46,    49,     0,    22,     0,
       0,     0,    38,     0,     0,     0,    23,     0,    40,    42,
      41,   167,     0,     0,    22,     0,     0,     0,   155,     0,
       0,    11,     0,     0,   133,   132,     0,   128,     0,     0,
       0,    29,     0,   114,    51,   109,     0,    50,    48,     0,
      22,     0,    22,     0,     0,    14,    91,   167,     0,     0,
       0,    74,     0,    75,     0,     0,     0,     0,     0,   156,
       0,     0,   103,     0,   126,   105,   107,   106,   108,   125,
     127,   134,     0,     0,   129,     0,     0,   112,     0,     0,
      22,     0,     0,     0,     0,     0,     0,    58,     0,     0,
       0,    66,     0,    16,     0,    15,     0,   151,   157,     0,
     104,   147,   140,   139,   141,   145,   146,   143,   142,   144,
     138,     0,   136,     0,    30,     0,     0,    22,     0,     0,
      18,     0,     0,     0,     0,     0,    62,     0,     0,     0,
      68,     0,    60,     0,    59,     0,     0,   167,     0,     0,
      92,    67,    17,   158,   152,   135,     0,   149,     0,     0,
      30,     0,    30,     0,    22,     0,    22,    20,     0,    19,
     153,     0,    64,     0,    63,     0,     0,    69,    61,    70,
     167,     0,    94,   102,    98,     0,     0,   137,   148,     0,
       0,    43,    31,     0,    30,     0,     0,     0,    22,     0,
      21,   154,    65,    72,     0,    96,   100,    95,    99,    71,
      93,   150,    24,     0,     0,     0,    32,     0,     0,     0,
      73,    97,   101,    26,     0,    25,    34,     0,    33,    27,
      35
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,     2,     9,    10,    55,    94,    11,    86,    12,
      74,   279,    13,   135,    68,    85,    69,   136,   312,   137,
      61,   125,    80,   126,   138,   139,   140,   179,   182,   180,
      52,   142,   269,   270,   302,   154,   155,   195,    81,   118,
     112,   113,   114,   198,   199,    15,    62,    73,    97,   241,
     242,   159,   278,    16,   147,   148,   115,   116,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -260
static const short int yypact[] =
{
    -260,    15,    24,  -260,  1509,    36,  1509,  1509,   357,  -260,
    -260,  -260,  -260,  -260,    13,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,     7,  -260,  -260,  1509,    61,  -260,   -26,  -260,  -260,
    -260,  -260,    65,  1509,    83,    73,  -260,  1509,    -6,    70,
       3,    82,  1555,   117,   -15,     0,    76,   211,   171,    60,
     124,  -260,     8,  1509,  1509,  -260,   405,  -260,  -260,   132,
    -260,  1461,   144,  -260,   153,   -23,   163,    98,   197,  1509,
     199,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,   152,   170,  -260,  -260,  -260,  -260,   118,  -260,
    -260,  -260,  -260,  -260,  -260,    60,  -260,    60,  -260,    64,
     173,    19,  -260,   168,  1509,   181,  -260,  1509,  -260,  -260,
    -260,  1509,  1509,   453,  -260,   501,  1509,   549,  -260,   167,
    1461,  -260,   -17,   299,   167,  -260,   179,  -260,   198,   177,
    1509,  -260,  1509,  -260,  -260,  -260,   211,  -260,    60,   597,
    -260,   188,  -260,  1461,   189,  -260,  -260,  1509,  1509,    75,
     193,   195,    46,  -260,   192,   645,   194,   167,   196,  -260,
     200,   693,  -260,   201,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,   256,   202,  -260,    17,    32,  -260,   204,   741,
    -260,   789,   837,  1461,   107,   203,   105,  -260,   116,   209,
     885,  -260,   226,  -260,   227,  -260,   228,  -260,  -260,   230,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,   121,  -260,    60,  -260,    67,   233,  -260,    69,   234,
    -260,   236,   933,   238,   239,   981,  -260,   131,   241,  1029,
    -260,   244,  -260,   246,  -260,   248,  1509,  1509,  1509,   141,
    -260,  -260,  -260,  -260,  -260,  -260,   256,  -260,   143,  1077,
    -260,   251,  -260,  1125,  -260,   254,  -260,  -260,   253,  -260,
    -260,   255,  -260,   278,  -260,   287,   148,  -260,  -260,  -260,
    1509,  1509,   294,  -260,   294,   296,  1461,  -260,  -260,    60,
     298,  -260,  -260,  1173,  -260,  1221,   300,  1269,  -260,  1317,
    -260,  -260,  -260,  -260,   301,   294,   294,  -260,  -260,  -260,
    -260,  -260,  -260,   302,  1365,   304,  -260,   305,  1413,   334,
    -260,  -260,  -260,  -260,   339,  -260,  -260,   345,  -260,  -260,
    -260
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,   -82,  -260,
      74,  -254,  -260,    18,   -65,    88,   -50,  -259,  -260,    -2,
     149,   218,  -260,  -124,  -260,  -260,  -260,    66,   102,   123,
     -59,  -127,   139,    93,  -195,  -144,   -85,  -260,   247,  -260,
    -260,   -62,   249,  -260,  -260,  -260,   395,  -260,  -260,  -260,
     127,  -260,  -260,  -260,  -136,  -138,  -260,  -260,    -4
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -77
static const short int yytable[] =
{
      14,   167,    56,    58,    58,    92,   143,    65,   145,   189,
     178,    65,    65,    95,   191,     3,   119,   129,    89,    63,
     311,    65,    51,    65,   152,    72,   313,   141,   315,   153,
       4,   192,   130,    98,    99,   218,    65,   212,    88,    64,
     108,   109,   110,   111,   167,    67,   169,    91,   100,    99,
       5,    66,   128,   189,   311,     6,   311,     7,    67,    67,
     334,   244,   185,   173,   190,    54,   174,   120,    67,   201,
     257,     8,    70,   304,   189,   311,   247,   255,   177,   171,
     132,    82,   121,    67,   141,    87,   141,   149,   209,   146,
     211,   197,   221,   268,   219,    58,   122,   222,   153,   123,
     124,   131,   226,    71,   207,   325,   326,    77,   170,    78,
     141,   280,    83,   284,    90,    67,    79,   189,    67,   277,
      67,   217,   152,    84,   101,    99,   141,   153,   252,   258,
      58,   261,   268,   263,    75,    76,    93,   181,   183,   301,
     245,   248,   187,   149,   157,   146,   149,   158,   146,   200,
     141,   260,   141,   256,   152,   246,   249,   153,   327,   153,
     328,   267,   262,   165,   275,   283,    96,   166,   153,   149,
     276,   146,   293,   181,   183,   127,   144,   292,   205,   268,
     206,   341,   342,   153,   305,   331,   308,   149,   150,   146,
     306,   324,   309,   141,   102,   281,   151,   306,   285,   103,
     267,   156,   317,   160,   319,   162,   163,   300,   149,   149,
     146,   146,   104,   164,   175,   176,   117,   172,   266,   153,
     141,   202,   203,   204,   141,   105,   106,   107,   108,   109,
     110,   111,   210,   213,   102,   220,   338,   -76,   223,   103,
     225,   194,   227,   214,   243,   259,   228,   267,   161,   230,
     250,   149,   104,   146,   141,   264,   141,   266,   141,   231,
     141,   232,   233,   303,   303,   105,   106,   107,   108,   109,
     110,   111,   271,   272,   273,   141,   274,   282,   286,   141,
     216,   234,   287,   235,   289,   290,   236,   294,   237,   238,
     297,   239,   298,   240,   299,   314,   303,   303,   318,   320,
     215,   321,    17,    18,   266,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,   102,    36,   322,    37,    38,   103,    39,    40,
      41,    42,    43,   323,    44,    45,    46,    47,    48,    49,
     104,   152,   329,    78,   332,   168,   336,   340,   343,    84,
     345,   346,    50,   105,   106,   107,   108,   109,   110,   111,
      17,    18,    59,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     348,    36,    60,    37,    38,   349,    39,    40,    41,    42,
      43,   350,    44,    45,    46,    47,    48,    49,   296,   330,
     196,   193,    57,   307,     0,     0,     0,     0,    17,    18,
      50,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     0,    36,
       0,    37,    38,     0,    39,    40,    41,    42,    43,     0,
      44,    45,    46,    47,    48,    49,     0,     0,     0,     0,
     133,     0,   134,     0,     0,     0,    17,    18,    50,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,     0,    37,
      38,     0,    39,    40,    41,    42,    43,     0,    44,    45,
      46,    47,    48,    49,     0,     0,     0,     0,   184,     0,
     134,     0,     0,     0,    17,    18,    50,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,    36,     0,    37,    38,     0,
      39,    40,    41,    42,    43,     0,    44,    45,    46,    47,
      48,    49,     0,     0,     0,     0,   186,     0,   134,     0,
       0,     0,    17,    18,    50,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     0,    36,     0,    37,    38,     0,    39,    40,
      41,    42,    43,     0,    44,    45,    46,    47,    48,    49,
       0,     0,     0,     0,   188,     0,   134,     0,     0,     0,
      17,    18,    50,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,     0,    37,    38,     0,    39,    40,    41,    42,
      43,     0,    44,    45,    46,    47,    48,    49,     0,     0,
       0,     0,   208,     0,   134,     0,     0,     0,    17,    18,
      50,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     0,    36,
       0,    37,    38,     0,    39,    40,    41,    42,    43,     0,
      44,    45,    46,    47,    48,    49,     0,     0,     0,     0,
     224,     0,   134,     0,     0,     0,    17,    18,    50,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,     0,    37,
      38,     0,    39,    40,    41,    42,    43,     0,    44,    45,
      46,    47,    48,    49,     0,     0,     0,     0,   229,     0,
     134,     0,     0,     0,    17,    18,    50,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,    36,     0,    37,    38,     0,
      39,    40,    41,    42,    43,     0,    44,    45,    46,    47,
      48,    49,     0,     0,     0,     0,   251,     0,   134,     0,
       0,     0,    17,    18,    50,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     0,    36,     0,    37,    38,     0,    39,    40,
      41,    42,    43,     0,    44,    45,    46,    47,    48,    49,
       0,     0,     0,     0,   253,     0,   134,     0,     0,     0,
      17,    18,    50,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,     0,    37,    38,     0,    39,    40,    41,    42,
      43,     0,    44,    45,    46,    47,    48,    49,     0,     0,
       0,     0,   254,     0,   134,     0,     0,     0,    17,    18,
      50,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     0,    36,
       0,    37,    38,     0,    39,    40,    41,    42,    43,     0,
      44,    45,    46,    47,    48,    49,     0,     0,   265,     0,
       0,     0,   134,     0,     0,     0,    17,    18,    50,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,     0,    37,
      38,     0,    39,    40,    41,    42,    43,     0,    44,    45,
      46,    47,    48,    49,     0,     0,     0,     0,   288,     0,
     134,     0,     0,     0,    17,    18,    50,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,    36,     0,    37,    38,     0,
      39,    40,    41,    42,    43,     0,    44,    45,    46,    47,
      48,    49,     0,     0,     0,     0,   291,     0,   134,     0,
       0,     0,    17,    18,    50,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     0,    36,     0,    37,    38,     0,    39,    40,
      41,    42,    43,     0,    44,    45,    46,    47,    48,    49,
       0,     0,   295,     0,     0,     0,   134,     0,     0,     0,
      17,    18,    50,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,     0,    37,    38,     0,    39,    40,    41,    42,
      43,     0,    44,    45,    46,    47,    48,    49,     0,     0,
       0,     0,   310,     0,   134,     0,     0,     0,    17,    18,
      50,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     0,    36,
       0,    37,    38,     0,    39,    40,    41,    42,    43,     0,
      44,    45,    46,    47,    48,    49,     0,     0,     0,     0,
     316,     0,   134,     0,     0,     0,    17,    18,    50,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,     0,    37,
      38,     0,    39,    40,    41,    42,    43,     0,    44,    45,
      46,    47,    48,    49,     0,     0,     0,     0,   333,     0,
     134,     0,     0,     0,    17,    18,    50,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,    36,     0,    37,    38,     0,
      39,    40,    41,    42,    43,     0,    44,    45,    46,    47,
      48,    49,     0,     0,     0,     0,   335,     0,   134,     0,
       0,     0,    17,    18,    50,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     0,    36,     0,    37,    38,     0,    39,    40,
      41,    42,    43,     0,    44,    45,    46,    47,    48,    49,
       0,     0,     0,     0,   337,     0,   134,     0,     0,     0,
      17,    18,    50,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,     0,    37,    38,     0,    39,    40,    41,    42,
      43,     0,    44,    45,    46,    47,    48,    49,     0,     0,
       0,     0,   339,     0,   134,     0,     0,     0,    17,    18,
      50,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     0,    36,
       0,    37,    38,     0,    39,    40,    41,    42,    43,     0,
      44,    45,    46,    47,    48,    49,     0,     0,     0,     0,
     344,     0,   134,     0,     0,     0,    17,    18,    50,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,     0,    37,
      38,     0,    39,    40,    41,    42,    43,     0,    44,    45,
      46,    47,    48,    49,     0,     0,     0,     0,   347,     0,
     134,     0,     0,     0,    17,    18,    50,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,    36,     0,    37,    38,     0,
      39,    40,    41,    42,    43,     0,    44,    45,    46,    47,
      48,    49,     0,     0,     0,     0,     0,     0,   134,     0,
       0,     0,    17,    18,    50,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     0,    36,     0,    37,    38,     0,    39,    40,
      41,    42,    43,     0,    44,    45,    46,    47,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34
};

static const short int yycheck[] =
{
       2,   125,     6,     7,     8,    70,    88,     4,    90,   147,
     137,     4,     4,    72,   150,     0,    78,    82,    68,     6,
     279,     4,     4,     4,    47,    51,   280,    86,   282,    52,
       6,    48,    82,    48,    49,   179,     4,   173,    44,    26,
      57,    58,    59,    60,   168,    51,   128,    44,    48,    49,
      26,    44,    44,   191,   313,    31,   315,    33,    51,    51,
     314,    44,   144,    44,   149,    29,   131,     7,    51,   154,
     214,    47,    54,   268,   212,   334,    44,   213,   137,   129,
      84,    63,    22,    51,   143,    67,   145,    91,   170,    91,
     172,   153,    46,   220,   179,    99,    36,   182,    52,    39,
      40,    83,   187,    42,   166,   300,   301,    42,    44,    44,
     169,    44,    29,    44,    44,    51,    51,   255,    51,   243,
      51,    46,    47,    50,    48,    49,   185,    52,   210,   214,
     134,   216,   259,   218,    60,    61,    54,   141,   142,   266,
     205,   206,   146,   147,    46,   147,   150,    49,   150,   153,
     209,    46,   211,    46,    47,   205,   206,    52,   302,    52,
     304,   220,    46,    45,    43,   247,    49,    49,    52,   173,
      49,   173,   257,   177,   178,    51,    44,    46,   160,   306,
     162,   325,   326,    52,    43,   309,    43,   191,    44,   191,
      49,    43,    49,   252,    23,   245,    43,    49,   248,    28,
     259,    38,   284,     6,   286,     6,    54,   266,   212,   213,
     212,   213,    41,    43,    46,    34,    45,    44,   220,    52,
     279,    42,    24,    46,   283,    54,    55,    56,    57,    58,
      59,    60,    44,    44,    23,    42,   318,    42,    46,    28,
      46,   153,    46,   177,    42,    42,    46,   306,    99,    48,
      46,   255,    41,   255,   313,    46,   315,   259,   317,     3,
     319,     5,     6,   267,   268,    54,    55,    56,    57,    58,
      59,    60,    46,    46,    46,   334,    46,    44,    44,   338,
     178,    25,    46,    27,    46,    46,    30,    46,    32,    33,
      46,    35,    46,    37,    46,    44,   300,   301,    44,    46,
     177,    46,     3,     4,   306,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    46,    26,    27,    28,    29,    30,
      31,    32,    33,    46,    35,    36,    37,    38,    39,    40,
      41,    47,    46,    44,    46,   127,    46,    46,    46,    50,
      46,    46,    53,    54,    55,    56,    57,    58,    59,    60,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      46,    24,    25,    26,    27,    46,    29,    30,    31,    32,
      33,    46,    35,    36,    37,    38,    39,    40,   259,   306,
     153,   152,     7,   276,    -1,    -1,    -1,    -1,     3,     4,
      53,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      -1,    26,    27,    -1,    29,    30,    31,    32,    33,    -1,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      45,    -1,    47,    -1,    -1,    -1,     3,     4,    53,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    -1,    26,
      27,    -1,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    45,    -1,
      47,    -1,    -1,    -1,     3,     4,    53,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    26,    27,    -1,
      29,    30,    31,    32,    33,    -1,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,
      -1,    -1,     3,     4,    53,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    -1,    26,    27,    -1,    29,    30,
      31,    32,    33,    -1,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    -1,    -1,
       3,     4,    53,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    -1,    26,    27,    -1,    29,    30,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    45,    -1,    47,    -1,    -1,    -1,     3,     4,
      53,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      -1,    26,    27,    -1,    29,    30,    31,    32,    33,    -1,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      45,    -1,    47,    -1,    -1,    -1,     3,     4,    53,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    -1,    26,
      27,    -1,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    45,    -1,
      47,    -1,    -1,    -1,     3,     4,    53,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    26,    27,    -1,
      29,    30,    31,    32,    33,    -1,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,
      -1,    -1,     3,     4,    53,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    -1,    26,    27,    -1,    29,    30,
      31,    32,    33,    -1,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    -1,    -1,
       3,     4,    53,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    -1,    26,    27,    -1,    29,    30,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    45,    -1,    47,    -1,    -1,    -1,     3,     4,
      53,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      -1,    26,    27,    -1,    29,    30,    31,    32,    33,    -1,
      35,    36,    37,    38,    39,    40,    -1,    -1,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,     3,     4,    53,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    -1,    26,
      27,    -1,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    45,    -1,
      47,    -1,    -1,    -1,     3,     4,    53,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    26,    27,    -1,
      29,    30,    31,    32,    33,    -1,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,
      -1,    -1,     3,     4,    53,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    -1,    26,    27,    -1,    29,    30,
      31,    32,    33,    -1,    35,    36,    37,    38,    39,    40,
      -1,    -1,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
       3,     4,    53,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    -1,    26,    27,    -1,    29,    30,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    45,    -1,    47,    -1,    -1,    -1,     3,     4,
      53,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      -1,    26,    27,    -1,    29,    30,    31,    32,    33,    -1,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      45,    -1,    47,    -1,    -1,    -1,     3,     4,    53,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    -1,    26,
      27,    -1,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    45,    -1,
      47,    -1,    -1,    -1,     3,     4,    53,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    26,    27,    -1,
      29,    30,    31,    32,    33,    -1,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,
      -1,    -1,     3,     4,    53,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    -1,    26,    27,    -1,    29,    30,
      31,    32,    33,    -1,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    -1,    -1,
       3,     4,    53,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    -1,    26,    27,    -1,    29,    30,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    45,    -1,    47,    -1,    -1,    -1,     3,     4,
      53,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      -1,    26,    27,    -1,    29,    30,    31,    32,    33,    -1,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      45,    -1,    47,    -1,    -1,    -1,     3,     4,    53,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    -1,    26,
      27,    -1,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    45,    -1,
      47,    -1,    -1,    -1,     3,     4,    53,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    26,    27,    -1,
      29,    30,    31,    32,    33,    -1,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,     3,     4,    53,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    -1,    26,    27,    -1,    29,    30,
      31,    32,    33,    -1,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    62,    63,     0,     6,    26,    31,    33,    47,    64,
      65,    68,    70,    73,    80,   106,   114,     3,     4,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    24,    26,    27,    29,
      30,    31,    32,    33,    35,    36,    37,    38,    39,    40,
      53,    74,    91,   119,    29,    66,   119,   107,   119,     5,
      25,    81,   107,     6,    26,     4,    44,    51,    75,    77,
      74,    42,    51,   108,    71,    71,    71,    42,    44,    51,
      83,    99,    74,    29,    50,    76,    69,    74,    44,    77,
      44,    44,    75,    54,    67,    91,    49,   109,    48,    49,
      48,    48,    23,    28,    41,    54,    55,    56,    57,    58,
      59,    60,   101,   102,   103,   117,   118,    45,   100,   102,
       7,    22,    36,    39,    40,    82,    84,    51,    44,    75,
      77,    74,   119,    45,    47,    74,    78,    80,    85,    86,
      87,    91,    92,    69,    44,    69,    80,   115,   116,   119,
      44,    43,    47,    52,    96,    97,    38,    46,    49,   112,
       6,    81,     6,    54,    43,    45,    49,    84,    82,    69,
      44,    77,    44,    44,    75,    46,    34,    91,    92,    88,
      90,   119,    89,   119,    45,    69,    45,   119,    45,   116,
      97,   115,    48,   103,    76,    98,    99,   102,   104,   105,
     119,    97,    42,    24,    46,    74,    74,   102,    45,    69,
      44,    69,   115,    44,    88,    90,    89,    46,    96,    97,
      42,    46,    97,    46,    45,    46,    97,    46,    46,    45,
      48,     3,     5,     6,    25,    27,    30,    32,    33,    35,
      37,   110,   111,    42,    44,    75,    77,    44,    75,    77,
      46,    45,    69,    45,    45,   115,    46,    96,    97,    42,
      46,    97,    46,    97,    46,    43,    80,    91,    92,    93,
      94,    46,    46,    46,    46,    43,    49,    84,   113,    72,
      44,    77,    44,    69,    44,    77,    44,    46,    45,    46,
      46,    45,    46,    97,    46,    43,    93,    46,    46,    46,
      91,    92,    95,   119,    95,    43,    49,   111,    43,    49,
      45,    78,    79,    72,    44,    72,    45,    69,    44,    69,
      46,    46,    46,    46,    43,    95,    95,    96,    96,    46,
      94,    84,    46,    45,    72,    45,    46,    45,    69,    45,
      46,    96,    96,    46,    45,    46,    46,    45,    46,    46,
      46
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

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
#line 212 "OW_MOFParser.yy"
    {
		MOF_COMPILER->mofSpecification = new MOFSpecification((yyvsp[0].pMOFProductionList));
		}
    break;

  case 3:
#line 217 "OW_MOFParser.yy"
    {(yyval.pMOFProductionList) = new List<MOFProduction*>; }
    break;

  case 4:
#line 218 "OW_MOFParser.yy"
    {(yyvsp[-1].pMOFProductionList)->push_back((yyvsp[0].pMOFProduction)); (yyval.pMOFProductionList) = (yyvsp[-1].pMOFProductionList);}
    break;

  case 5:
#line 222 "OW_MOFParser.yy"
    {(yyval.pMOFProduction) = new MOFProductionCompilerDirective((yyvsp[0].pCompilerDirective)); }
    break;

  case 6:
#line 223 "OW_MOFParser.yy"
    {(yyval.pMOFProduction) = new MOFProductionClassDeclaration((yyvsp[0].pClassDeclaration)); }
    break;

  case 7:
#line 224 "OW_MOFParser.yy"
    {(yyval.pMOFProduction) = new MOFProductionAssocDeclaration((yyvsp[0].pAssocDeclaration)); }
    break;

  case 8:
#line 225 "OW_MOFParser.yy"
    {(yyval.pMOFProduction) = new MOFProductionIndicDeclaration((yyvsp[0].pIndicDeclaration)); }
    break;

  case 9:
#line 226 "OW_MOFParser.yy"
    {(yyval.pMOFProduction) = new MOFProductionQualifierDeclaration((yyvsp[0].pQualifierDeclaration)); }
    break;

  case 10:
#line 227 "OW_MOFParser.yy"
    {(yyval.pMOFProduction) = new MOFProductionInstanceDeclaration((yyvsp[0].pInstanceDeclaration)); }
    break;

  case 11:
#line 232 "OW_MOFParser.yy"
    {
			(yyval.pCompilerDirective) = new CompilerDirective((yyvsp[-3].pPragmaName), (yyvsp[-1].pPragmaParameter), MOF_COMPILER->theLineInfo);
			if ((yyvsp[-3].pPragmaName)->pPragmaName->equalsIgnoreCase("include"))
			{
				lexIncludeFile(MOF_COMPILER, MOF_COMPILER->fixParsedString(*((yyvsp[-1].pPragmaParameter)->pPragmaParameter)));
			}
                        delete (yyvsp[-4].pString);
                        delete (yyvsp[-2].pString);
                        delete (yyvsp[0].pString);
		}
    break;

  case 12:
#line 245 "OW_MOFParser.yy"
    {(yyval.pPragmaName) = new PragmaName((yyvsp[0].pString)); }
    break;

  case 13:
#line 249 "OW_MOFParser.yy"
    {(yyval.pPragmaParameter) = new PragmaParameter((yyvsp[0].pString)); }
    break;

  case 14:
#line 254 "OW_MOFParser.yy"
    {
                (yyval.pClassDeclaration) = new ClassDeclaration(0, (yyvsp[-4].pClassName), 0, 0, (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-5].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 15:
#line 262 "OW_MOFParser.yy"
    {
                (yyval.pClassDeclaration) = new ClassDeclaration(0, (yyvsp[-5].pClassName), 0, (yyvsp[-4].pSuperClass), (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 16:
#line 270 "OW_MOFParser.yy"
    {
                (yyval.pClassDeclaration) = new ClassDeclaration(0, (yyvsp[-5].pClassName), (yyvsp[-4].pAlias), 0, (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 17:
#line 278 "OW_MOFParser.yy"
    {
                (yyval.pClassDeclaration) = new ClassDeclaration(0, (yyvsp[-6].pClassName), (yyvsp[-5].pAlias), (yyvsp[-4].pSuperClass), (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-7].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 18:
#line 286 "OW_MOFParser.yy"
    {
                (yyval.pClassDeclaration) = new ClassDeclaration((yyvsp[-6].pQualifierList), (yyvsp[-4].pClassName), 0, 0, (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-5].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 19:
#line 294 "OW_MOFParser.yy"
    {
                (yyval.pClassDeclaration) = new ClassDeclaration((yyvsp[-7].pQualifierList), (yyvsp[-5].pClassName), 0, (yyvsp[-4].pSuperClass), (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 20:
#line 302 "OW_MOFParser.yy"
    {
                (yyval.pClassDeclaration) = new ClassDeclaration((yyvsp[-7].pQualifierList), (yyvsp[-5].pClassName), (yyvsp[-4].pAlias), 0, (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 21:
#line 310 "OW_MOFParser.yy"
    {
                (yyval.pClassDeclaration) = new ClassDeclaration((yyvsp[-8].pQualifierList), (yyvsp[-6].pClassName), (yyvsp[-5].pAlias), (yyvsp[-4].pSuperClass), (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-7].pString);
                delete (yyvsp[-4].pSuperClass);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 22:
#line 319 "OW_MOFParser.yy"
    {(yyval.pClassFeatureList) = new List<ClassFeature*>; }
    break;

  case 23:
#line 320 "OW_MOFParser.yy"
    {(yyvsp[-1].pClassFeatureList)->push_back((yyvsp[0].pClassFeature)); (yyval.pClassFeatureList) = (yyvsp[-1].pClassFeatureList);}
    break;

  case 24:
#line 325 "OW_MOFParser.yy"
    {
                (yyval.pAssocDeclaration) = new AssocDeclaration((yyvsp[-7].pQualifierList), (yyvsp[-4].pClassName), 0, 0, (yyvsp[-2].pAssociationFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-9].pString);
                delete (yyvsp[-8].pString);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-5].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 25:
#line 336 "OW_MOFParser.yy"
    {
                (yyval.pAssocDeclaration) = new AssocDeclaration((yyvsp[-8].pQualifierList), (yyvsp[-5].pClassName), 0, (yyvsp[-4].pSuperClass), (yyvsp[-2].pAssociationFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-10].pString);
                delete (yyvsp[-9].pString);
                delete (yyvsp[-7].pString);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 26:
#line 347 "OW_MOFParser.yy"
    {
                (yyval.pAssocDeclaration) = new AssocDeclaration((yyvsp[-8].pQualifierList), (yyvsp[-5].pClassName), (yyvsp[-4].pAlias), 0, (yyvsp[-2].pAssociationFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-10].pString);
                delete (yyvsp[-9].pString);
                delete (yyvsp[-7].pString);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 27:
#line 358 "OW_MOFParser.yy"
    {
                (yyval.pAssocDeclaration) = new AssocDeclaration((yyvsp[-9].pQualifierList), (yyvsp[-6].pClassName), (yyvsp[-5].pAlias), (yyvsp[-4].pSuperClass), (yyvsp[-2].pAssociationFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-11].pString);
                delete (yyvsp[-10].pString);
                delete (yyvsp[-8].pString);
                delete (yyvsp[-7].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 28:
#line 370 "OW_MOFParser.yy"
    {(yyval.pQualifierList) = new List<Qualifier*>; }
    break;

  case 29:
#line 372 "OW_MOFParser.yy"
    {(yyvsp[-2].pQualifierList)->push_back((yyvsp[0].pQualifier)); (yyval.pQualifierList) = (yyvsp[-2].pQualifierList); delete (yyvsp[-1].pString); }
    break;

  case 30:
#line 375 "OW_MOFParser.yy"
    {(yyval.pAssociationFeatureList) = new List<AssociationFeature*>; }
    break;

  case 31:
#line 376 "OW_MOFParser.yy"
    {(yyvsp[-1].pAssociationFeatureList)->push_back((yyvsp[0].pAssociationFeature)); (yyval.pAssociationFeatureList) = (yyvsp[-1].pAssociationFeatureList);}
    break;

  case 32:
#line 381 "OW_MOFParser.yy"
    {
                (yyval.pIndicDeclaration) = new IndicDeclaration((yyvsp[-7].pQualifierList), (yyvsp[-4].pClassName), 0, 0, (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-9].pString);
                delete (yyvsp[-8].pString);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-5].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 33:
#line 392 "OW_MOFParser.yy"
    {
                (yyval.pIndicDeclaration) = new IndicDeclaration((yyvsp[-8].pQualifierList), (yyvsp[-5].pClassName), 0, (yyvsp[-4].pSuperClass), (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-10].pString);
                delete (yyvsp[-9].pString);
                delete (yyvsp[-7].pString);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 34:
#line 403 "OW_MOFParser.yy"
    {
                (yyval.pIndicDeclaration) = new IndicDeclaration((yyvsp[-8].pQualifierList), (yyvsp[-5].pClassName), (yyvsp[-4].pAlias), 0, (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-10].pString);
                delete (yyvsp[-9].pString);
                delete (yyvsp[-7].pString);
                delete (yyvsp[-6].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 35:
#line 414 "OW_MOFParser.yy"
    {
                (yyval.pIndicDeclaration) = new IndicDeclaration((yyvsp[-9].pQualifierList), (yyvsp[-6].pClassName), (yyvsp[-5].pAlias), (yyvsp[-4].pSuperClass), (yyvsp[-2].pClassFeatureList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-11].pString);
                delete (yyvsp[-10].pString);
                delete (yyvsp[-8].pString);
                delete (yyvsp[-7].pString);
                delete (yyvsp[-3].pString);
                delete (yyvsp[-1].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 36:
#line 427 "OW_MOFParser.yy"
    {(yyval.pClassName) = new ClassName((yyvsp[0].pString)); }
    break;

  case 37:
#line 431 "OW_MOFParser.yy"
    {(yyval.pAlias) = new Alias((yyvsp[0].pAliasIdentifier)); delete (yyvsp[-1].pString);}
    break;

  case 38:
#line 436 "OW_MOFParser.yy"
    {
                (yyval.pAliasIdentifier) = new AliasIdentifier((yyvsp[0].pString), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-1].pString);
        }
    break;

  case 39:
#line 443 "OW_MOFParser.yy"
    {(yyval.pSuperClass) = new SuperClass((yyvsp[0].pClassName)); delete (yyvsp[-1].pString); }
    break;

  case 40:
#line 447 "OW_MOFParser.yy"
    {(yyval.pClassFeature) = new ClassFeaturePropertyDeclaration((yyvsp[0].pPropertyDeclaration)); }
    break;

  case 41:
#line 448 "OW_MOFParser.yy"
    {(yyval.pClassFeature) = new ClassFeatureMethodDeclaration((yyvsp[0].pMethodDeclaration)); }
    break;

  case 42:
#line 449 "OW_MOFParser.yy"
    {(yyval.pClassFeature) = new ClassFeatureReferenceDeclaration((yyvsp[0].pReferenceDeclaration)); }
    break;

  case 43:
#line 453 "OW_MOFParser.yy"
    {(yyval.pAssociationFeature) = new AssociationFeatureClassFeature((yyvsp[0].pClassFeature)); }
    break;

  case 44:
#line 459 "OW_MOFParser.yy"
    {(yyvsp[-1].pQualifierList)->push_front((yyvsp[-2].pQualifier)); (yyval.pQualifierList) = (yyvsp[-1].pQualifierList); delete (yyvsp[-3].pString); delete (yyvsp[0].pString); }
    break;

  case 45:
#line 463 "OW_MOFParser.yy"
    {(yyval.pQualifier) = new Qualifier((yyvsp[0].pQualifierName), 0, 0, MOF_COMPILER->theLineInfo); }
    break;

  case 46:
#line 465 "OW_MOFParser.yy"
    {
                (yyval.pQualifier) = new Qualifier((yyvsp[-2].pQualifierName), 0, (yyvsp[0].pFlavorList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-1].pString);
        }
    break;

  case 47:
#line 469 "OW_MOFParser.yy"
    {(yyval.pQualifier) = new Qualifier((yyvsp[-1].pQualifierName), (yyvsp[0].pQualifierParameter), 0, MOF_COMPILER->theLineInfo); }
    break;

  case 48:
#line 471 "OW_MOFParser.yy"
    {
                (yyval.pQualifier) = new Qualifier((yyvsp[-3].pQualifierName), (yyvsp[-2].pQualifierParameter), (yyvsp[0].pFlavorList), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-1].pString);
        }
    break;

  case 49:
#line 478 "OW_MOFParser.yy"
    {(yyval.pFlavorList) = new List<Flavor*>(1, (yyvsp[0].pFlavor)); }
    break;

  case 50:
#line 479 "OW_MOFParser.yy"
    {(yyvsp[-1].pFlavorList)->push_back((yyvsp[0].pFlavor)); (yyval.pFlavorList) = (yyvsp[-1].pFlavorList);}
    break;

  case 51:
#line 484 "OW_MOFParser.yy"
    {
                (yyval.pQualifierParameter) = new QualifierParameterConstantValue((yyvsp[-1].pConstantValue), MOF_COMPILER->theLineInfo);
                delete (yyvsp[-2].pString);
                delete (yyvsp[0].pString);
        }
    break;

  case 52:
#line 489 "OW_MOFParser.yy"
    {(yyval.pQualifierParameter) = new QualifierParameterArrayInitializer((yyvsp[0].pArrayInitializer), MOF_COMPILER->theLineInfo); }
    break;

  case 53:
#line 493 "OW_MOFParser.yy"
    {(yyval.pFlavor) = new Flavor((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 54:
#line 494 "OW_MOFParser.yy"
    {(yyval.pFlavor) = new Flavor((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 55:
#line 495 "OW_MOFParser.yy"
    {(yyval.pFlavor) = new Flavor((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 56:
#line 496 "OW_MOFParser.yy"
    {(yyval.pFlavor) = new Flavor((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 57:
#line 497 "OW_MOFParser.yy"
    {(yyval.pFlavor) = new Flavor((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 58:
#line 502 "OW_MOFParser.yy"
    {
		(yyval.pPropertyDeclaration) = new PropertyDeclaration(0, (yyvsp[-2].pDataType), (yyvsp[-1].pPropertyName), 0, 0, MOF_COMPILER->theLineInfo);
		delete (yyvsp[0].pString);
	}
    break;

  case 59:
#line 507 "OW_MOFParser.yy"
    {
		(yyval.pPropertyDeclaration) = new PropertyDeclaration(0, (yyvsp[-3].pDataType), (yyvsp[-2].pPropertyName), 0, (yyvsp[-1].pDefaultValue), MOF_COMPILER->theLineInfo);
		delete (yyvsp[0].pString);
	}
    break;

  case 60:
#line 512 "OW_MOFParser.yy"
    {
		(yyval.pPropertyDeclaration) = new PropertyDeclaration(0, (yyvsp[-3].pDataType), (yyvsp[-2].pPropertyName), (yyvsp[-1].pArray), 0, MOF_COMPILER->theLineInfo);
		delete (yyvsp[0].pString);
	}
    break;

  case 61:
#line 517 "OW_MOFParser.yy"
    {
		(yyval.pPropertyDeclaration) = new PropertyDeclaration(0, (yyvsp[-4].pDataType), (yyvsp[-3].pPropertyName), (yyvsp[-2].pArray), (yyvsp[-1].pDefaultValue), MOF_COMPILER->theLineInfo);
		delete (yyvsp[0].pString);
	}
    break;

  case 62:
#line 522 "OW_MOFParser.yy"
    {
		(yyval.pPropertyDeclaration) = new PropertyDeclaration((yyvsp[-3].pQualifierList), (yyvsp[-2].pDataType), (yyvsp[-1].pPropertyName), 0, 0, MOF_COMPILER->theLineInfo);
		delete (yyvsp[0].pString);
	}
    break;

  case 63:
#line 527 "OW_MOFParser.yy"
    {
		(yyval.pPropertyDeclaration) = new PropertyDeclaration((yyvsp[-4].pQualifierList), (yyvsp[-3].pDataType), (yyvsp[-2].pPropertyName), 0, (yyvsp[-1].pDefaultValue), MOF_COMPILER->theLineInfo);
		delete (yyvsp[0].pString);
	}
    break;

  case 64:
#line 532 "OW_MOFParser.yy"
    {
		(yyval.pPropertyDeclaration) = new PropertyDeclaration((yyvsp[-4].pQualifierList), (yyvsp[-3].pDataType), (yyvsp[-2].pPropertyName), (yyvsp[-1].pArray), 0, MOF_COMPILER->theLineInfo);
		delete (yyvsp[0].pString);
	}
    break;

  case 65:
#line 537 "OW_MOFParser.yy"
    {
		(yyval.pPropertyDeclaration) = new PropertyDeclaration((yyvsp[-5].pQualifierList), (yyvsp[-4].pDataType), (yyvsp[-3].pPropertyName), (yyvsp[-2].pArray), (yyvsp[-1].pDefaultValue), MOF_COMPILER->theLineInfo);
		delete (yyvsp[0].pString);
	}
    break;

  case 66:
#line 545 "OW_MOFParser.yy"
    {
			(yyval.pReferenceDeclaration) = new ReferenceDeclaration(0, (yyvsp[-2].pObjectRef), (yyvsp[-1].pReferenceName), 0);
			delete (yyvsp[0].pString);
	}
    break;

  case 67:
#line 550 "OW_MOFParser.yy"
    {
			(yyval.pReferenceDeclaration) = new ReferenceDeclaration(0, (yyvsp[-3].pObjectRef), (yyvsp[-2].pReferenceName), (yyvsp[-1].pDefaultValue));
			delete (yyvsp[0].pString);
	}
    break;

  case 68:
#line 555 "OW_MOFParser.yy"
    {
			(yyval.pReferenceDeclaration) = new ReferenceDeclaration((yyvsp[-3].pQualifierList), (yyvsp[-2].pObjectRef), (yyvsp[-1].pReferenceName), 0);
			delete (yyvsp[0].pString);
	}
    break;

  case 69:
#line 560 "OW_MOFParser.yy"
    {
			(yyval.pReferenceDeclaration) = new ReferenceDeclaration((yyvsp[-4].pQualifierList), (yyvsp[-3].pObjectRef), (yyvsp[-2].pReferenceName), (yyvsp[-1].pDefaultValue));
			delete (yyvsp[0].pString);
	}
    break;

  case 70:
#line 568 "OW_MOFParser.yy"
    {
			(yyval.pMethodDeclaration) = new MethodDeclaration(0, (yyvsp[-4].pDataType), (yyvsp[-3].pMethodName), 0);
			delete (yyvsp[-1].pString);
			delete (yyvsp[0].pString);
			delete (yyvsp[-2].pString);
	}
    break;

  case 71:
#line 575 "OW_MOFParser.yy"
    {
			(yyval.pMethodDeclaration) = new MethodDeclaration(0, (yyvsp[-5].pDataType), (yyvsp[-4].pMethodName), (yyvsp[-2].pParameterList));
			delete (yyvsp[-3].pString);
			delete (yyvsp[-1].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 72:
#line 582 "OW_MOFParser.yy"
    {
			(yyval.pMethodDeclaration) = new MethodDeclaration((yyvsp[-5].pQualifierList), (yyvsp[-4].pDataType), (yyvsp[-3].pMethodName), 0);
			delete (yyvsp[-2].pString);
			delete (yyvsp[-1].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 73:
#line 589 "OW_MOFParser.yy"
    {
			(yyval.pMethodDeclaration) = new MethodDeclaration((yyvsp[-6].pQualifierList), (yyvsp[-5].pDataType), (yyvsp[-4].pMethodName), (yyvsp[-2].pParameterList));
			delete (yyvsp[-3].pString);
			delete (yyvsp[-1].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 74:
#line 598 "OW_MOFParser.yy"
    {(yyval.pPropertyName) = new PropertyName((yyvsp[0].pString)); }
    break;

  case 75:
#line 602 "OW_MOFParser.yy"
    {(yyval.pReferenceName) = new ReferenceName((yyvsp[0].pString)); }
    break;

  case 76:
#line 606 "OW_MOFParser.yy"
    {(yyval.pMethodName) = new MethodName((yyvsp[0].pString)); }
    break;

  case 77:
#line 610 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 78:
#line 611 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 79:
#line 612 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 80:
#line 613 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 81:
#line 614 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 82:
#line 615 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 83:
#line 616 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 84:
#line 617 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 85:
#line 618 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 86:
#line 619 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 87:
#line 620 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 88:
#line 621 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 89:
#line 622 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 90:
#line 623 "OW_MOFParser.yy"
    {(yyval.pDataType) = new DataType((yyvsp[0].pString)); }
    break;

  case 91:
#line 627 "OW_MOFParser.yy"
    {(yyval.pObjectRef) = new ObjectRef((yyvsp[-1].pClassName)); delete (yyvsp[0].pString); }
    break;

  case 92:
#line 631 "OW_MOFParser.yy"
    {(yyval.pParameterList) = new List<Parameter*>(1, (yyvsp[0].pParameter)); }
    break;

  case 93:
#line 632 "OW_MOFParser.yy"
    {(yyvsp[-2].pParameterList)->push_back((yyvsp[0].pParameter)); (yyval.pParameterList)=(yyvsp[-2].pParameterList); delete (yyvsp[-1].pString);}
    break;

  case 94:
#line 637 "OW_MOFParser.yy"
    {(yyval.pParameter) = new ParameterDataType(0, (yyvsp[-1].pDataType), (yyvsp[0].pParameterName), 0); }
    break;

  case 95:
#line 639 "OW_MOFParser.yy"
    {(yyval.pParameter) = new ParameterDataType(0, (yyvsp[-2].pDataType), (yyvsp[-1].pParameterName), (yyvsp[0].pArray)); }
    break;

  case 96:
#line 641 "OW_MOFParser.yy"
    {(yyval.pParameter) = new ParameterDataType((yyvsp[-2].pQualifierList), (yyvsp[-1].pDataType), (yyvsp[0].pParameterName), 0); }
    break;

  case 97:
#line 643 "OW_MOFParser.yy"
    {(yyval.pParameter) = new ParameterDataType((yyvsp[-3].pQualifierList), (yyvsp[-2].pDataType), (yyvsp[-1].pParameterName), (yyvsp[0].pArray)); }
    break;

  case 98:
#line 645 "OW_MOFParser.yy"
    {(yyval.pParameter) = new ParameterObjectRef(0, (yyvsp[-1].pObjectRef), (yyvsp[0].pParameterName), 0); }
    break;

  case 99:
#line 647 "OW_MOFParser.yy"
    {(yyval.pParameter) = new ParameterObjectRef(0, (yyvsp[-2].pObjectRef), (yyvsp[-1].pParameterName), (yyvsp[0].pArray)); }
    break;

  case 100:
#line 649 "OW_MOFParser.yy"
    {(yyval.pParameter) = new ParameterObjectRef((yyvsp[-2].pQualifierList), (yyvsp[-1].pObjectRef), (yyvsp[0].pParameterName), 0); }
    break;

  case 101:
#line 651 "OW_MOFParser.yy"
    {(yyval.pParameter) = new ParameterObjectRef((yyvsp[-3].pQualifierList), (yyvsp[-2].pObjectRef), (yyvsp[-1].pParameterName), (yyvsp[0].pArray)); }
    break;

  case 102:
#line 655 "OW_MOFParser.yy"
    {(yyval.pParameterName) = new ParameterName((yyvsp[0].pString)); }
    break;

  case 103:
#line 659 "OW_MOFParser.yy"
    {(yyval.pArray) = new ::OpenWBEM::MOF::Array(0); delete (yyvsp[-1].pString); delete (yyvsp[0].pString);}
    break;

  case 104:
#line 661 "OW_MOFParser.yy"
    {(yyval.pArray) = new ::OpenWBEM::MOF::Array((yyvsp[-1].pIntegerValue)); delete (yyvsp[-2].pString); delete (yyvsp[0].pString);}
    break;

  case 105:
#line 665 "OW_MOFParser.yy"
    {(yyval.pDefaultValue) = new DefaultValue((yyvsp[0].pInitializer)); delete (yyvsp[-1].pString);}
    break;

  case 106:
#line 669 "OW_MOFParser.yy"
    {(yyval.pInitializer) = new InitializerConstantValue((yyvsp[0].pConstantValue)); }
    break;

  case 107:
#line 670 "OW_MOFParser.yy"
    {(yyval.pInitializer) = new InitializerArrayInitializer((yyvsp[0].pArrayInitializer)); }
    break;

  case 108:
#line 671 "OW_MOFParser.yy"
    {(yyval.pInitializer) = new InitializerReferenceInitializer((yyvsp[0].pReferenceInitializer)); }
    break;

  case 109:
#line 676 "OW_MOFParser.yy"
    {(yyval.pArrayInitializer) = new ArrayInitializer((yyvsp[-1].pConstantValueList)); delete (yyvsp[-2].pString); delete (yyvsp[0].pString);}
    break;

  case 110:
#line 678 "OW_MOFParser.yy"
    {(yyval.pArrayInitializer) = new ArrayInitializer(0); delete (yyvsp[-1].pString); delete (yyvsp[0].pString);}
    break;

  case 111:
#line 682 "OW_MOFParser.yy"
    {(yyval.pConstantValueList) = new List<ConstantValue*>(1, (yyvsp[0].pConstantValue)); }
    break;

  case 112:
#line 684 "OW_MOFParser.yy"
    {(yyvsp[-2].pConstantValueList)->push_back((yyvsp[0].pConstantValue)); (yyval.pConstantValueList) = (yyvsp[-2].pConstantValueList); delete (yyvsp[-1].pString);}
    break;

  case 113:
#line 689 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString); }
    break;

  case 114:
#line 691 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[-1].pString); (yyval.pString)->concat(*(yyvsp[0].pString)); delete (yyvsp[0].pString);}
    break;

  case 115:
#line 695 "OW_MOFParser.yy"
    {(yyval.pConstantValue) = new ConstantValueIntegerValue((yyvsp[0].pIntegerValue)); }
    break;

  case 116:
#line 696 "OW_MOFParser.yy"
    {(yyval.pConstantValue) = new ConstantValueFloatValue((yyvsp[0].pString)); }
    break;

  case 117:
#line 697 "OW_MOFParser.yy"
    {(yyval.pConstantValue) = new ConstantValueCharValue((yyvsp[0].pString)); }
    break;

  case 118:
#line 698 "OW_MOFParser.yy"
    {(yyval.pConstantValue) = new ConstantValueStringValue((yyvsp[0].pString)); }
    break;

  case 119:
#line 699 "OW_MOFParser.yy"
    {(yyval.pConstantValue) = new ConstantValueBooleanValue((yyvsp[0].pString)); }
    break;

  case 120:
#line 700 "OW_MOFParser.yy"
    {(yyval.pConstantValue) = new ConstantValueNullValue((yyvsp[0].pString)); }
    break;

  case 121:
#line 704 "OW_MOFParser.yy"
    {(yyval.pIntegerValue) = new IntegerValueBinaryValue((yyvsp[0].pString)); }
    break;

  case 122:
#line 705 "OW_MOFParser.yy"
    {(yyval.pIntegerValue) = new IntegerValueOctalValue((yyvsp[0].pString)); }
    break;

  case 123:
#line 706 "OW_MOFParser.yy"
    {(yyval.pIntegerValue) = new IntegerValueDecimalValue((yyvsp[0].pString)); }
    break;

  case 124:
#line 707 "OW_MOFParser.yy"
    {(yyval.pIntegerValue) = new IntegerValueHexValue((yyvsp[0].pString)); }
    break;

  case 125:
#line 711 "OW_MOFParser.yy"
    {(yyval.pReferenceInitializer) = new ReferenceInitializerObjectHandle((yyvsp[0].pObjectHandle)); }
    break;

  case 126:
#line 712 "OW_MOFParser.yy"
    {(yyval.pReferenceInitializer) = new ReferenceInitializerAliasIdentifier((yyvsp[0].pAliasIdentifier)); }
    break;

  case 127:
#line 716 "OW_MOFParser.yy"
    {(yyval.pObjectHandle) = new ObjectHandle((yyvsp[0].pString)); }
    break;

  case 128:
#line 750 "OW_MOFParser.yy"
    {
			(yyval.pQualifierDeclaration)= new QualifierDeclaration((yyvsp[-3].pQualifierName), (yyvsp[-2].pQualifierType), (yyvsp[-1].pScope), 0, MOF_COMPILER->theLineInfo);
			delete (yyvsp[-4].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 129:
#line 756 "OW_MOFParser.yy"
    {
			(yyval.pQualifierDeclaration)= new QualifierDeclaration((yyvsp[-4].pQualifierName), (yyvsp[-3].pQualifierType), (yyvsp[-2].pScope), (yyvsp[-1].pDefaultFlavor), MOF_COMPILER->theLineInfo);
			delete (yyvsp[-5].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 130:
#line 764 "OW_MOFParser.yy"
    {(yyval.pQualifierName) = new QualifierName((yyvsp[0].pString)); }
    break;

  case 131:
#line 769 "OW_MOFParser.yy"
    {
			(yyval.pQualifierType) = new QualifierType((yyvsp[0].pDataType), 0, 0);
			delete (yyvsp[-1].pString);
	}
    break;

  case 132:
#line 774 "OW_MOFParser.yy"
    {
			(yyval.pQualifierType) = new QualifierType((yyvsp[-1].pDataType), 0, (yyvsp[0].pDefaultValue));
			delete (yyvsp[-2].pString);
	}
    break;

  case 133:
#line 779 "OW_MOFParser.yy"
    {
			(yyval.pQualifierType) = new QualifierType((yyvsp[-1].pDataType), (yyvsp[0].pArray), 0);
			delete (yyvsp[-2].pString);
	}
    break;

  case 134:
#line 784 "OW_MOFParser.yy"
    {
			(yyval.pQualifierType) = new QualifierType((yyvsp[-2].pDataType), (yyvsp[-1].pArray), (yyvsp[0].pDefaultValue));
			delete (yyvsp[-3].pString);
	}
    break;

  case 135:
#line 792 "OW_MOFParser.yy"
    {
			(yyval.pScope) = new Scope((yyvsp[-1].pMetaElementList));
			delete (yyvsp[-4].pString);
			delete (yyvsp[-3].pString);
			delete (yyvsp[-2].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 136:
#line 802 "OW_MOFParser.yy"
    {(yyval.pMetaElementList) = new List<MetaElement*>(1, (yyvsp[0].pMetaElement)); }
    break;

  case 137:
#line 804 "OW_MOFParser.yy"
    {(yyvsp[-2].pMetaElementList)->push_back((yyvsp[0].pMetaElement)); (yyval.pMetaElementList) = (yyvsp[-2].pMetaElementList); delete (yyvsp[-1].pString); }
    break;

  case 138:
#line 808 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 139:
#line 809 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 140:
#line 810 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 141:
#line 811 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 142:
#line 812 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 143:
#line 813 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 144:
#line 814 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 145:
#line 815 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 146:
#line 816 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 147:
#line 817 "OW_MOFParser.yy"
    {(yyval.pMetaElement) = new MetaElement((yyvsp[0].pString), MOF_COMPILER->theLineInfo); }
    break;

  case 148:
#line 822 "OW_MOFParser.yy"
    {
			(yyval.pDefaultFlavor) = new DefaultFlavor((yyvsp[-1].pFlavorList));
			delete (yyvsp[-4].pString);
			delete (yyvsp[-3].pString);
			delete (yyvsp[-2].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 149:
#line 832 "OW_MOFParser.yy"
    {(yyval.pFlavorList) = new List<Flavor*>(1, (yyvsp[0].pFlavor)); }
    break;

  case 150:
#line 834 "OW_MOFParser.yy"
    {
		(yyvsp[-2].pFlavorList)->push_back((yyvsp[0].pFlavor)); (yyval.pFlavorList) = (yyvsp[-2].pFlavorList);
		delete (yyvsp[-1].pString);
	}
    break;

  case 151:
#line 842 "OW_MOFParser.yy"
    {
			(yyval.pInstanceDeclaration) = new InstanceDeclaration(0, (yyvsp[-4].pClassName), 0, (yyvsp[-2].pValueInitializerList), MOF_COMPILER->theLineInfo);
			delete (yyvsp[-6].pString);
			delete (yyvsp[-5].pString);
			delete (yyvsp[-3].pString);
			delete (yyvsp[-1].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 152:
#line 851 "OW_MOFParser.yy"
    {
			(yyval.pInstanceDeclaration) = new InstanceDeclaration(0, (yyvsp[-5].pClassName), (yyvsp[-4].pAlias), (yyvsp[-2].pValueInitializerList), MOF_COMPILER->theLineInfo);
			delete (yyvsp[-7].pString);
			delete (yyvsp[-6].pString);
			delete (yyvsp[-3].pString);
			delete (yyvsp[-1].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 153:
#line 860 "OW_MOFParser.yy"
    {
			(yyval.pInstanceDeclaration) = new InstanceDeclaration((yyvsp[-7].pQualifierList), (yyvsp[-4].pClassName), 0, (yyvsp[-2].pValueInitializerList), MOF_COMPILER->theLineInfo);
			delete (yyvsp[-6].pString);
			delete (yyvsp[-5].pString);
			delete (yyvsp[-3].pString);
			delete (yyvsp[-1].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 154:
#line 869 "OW_MOFParser.yy"
    {
			(yyval.pInstanceDeclaration) = new InstanceDeclaration((yyvsp[-8].pQualifierList), (yyvsp[-5].pClassName), (yyvsp[-4].pAlias), (yyvsp[-2].pValueInitializerList), MOF_COMPILER->theLineInfo);
			delete (yyvsp[-7].pString);
			delete (yyvsp[-6].pString);
			delete (yyvsp[-3].pString);
			delete (yyvsp[-1].pString);
			delete (yyvsp[0].pString);
	}
    break;

  case 155:
#line 880 "OW_MOFParser.yy"
    {(yyval.pValueInitializerList) = new List<ValueInitializer*>(1, (yyvsp[0].pValueInitializer)); }
    break;

  case 156:
#line 882 "OW_MOFParser.yy"
    {(yyvsp[-1].pValueInitializerList)->push_back((yyvsp[0].pValueInitializer)); (yyval.pValueInitializerList) = (yyvsp[-1].pValueInitializerList);}
    break;

  case 157:
#line 887 "OW_MOFParser.yy"
    {(yyval.pValueInitializer) = new ValueInitializer(0, (yyvsp[-2].pString), (yyvsp[-1].pDefaultValue)); delete (yyvsp[0].pString); }
    break;

  case 158:
#line 889 "OW_MOFParser.yy"
    {(yyval.pValueInitializer) = new ValueInitializer((yyvsp[-3].pQualifierList), (yyvsp[-2].pString), (yyvsp[-1].pDefaultValue)); delete (yyvsp[0].pString); }
    break;

  case 159:
#line 893 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 160:
#line 894 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 161:
#line 898 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 162:
#line 902 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 163:
#line 903 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 164:
#line 904 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 165:
#line 906 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 166:
#line 907 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 167:
#line 908 "OW_MOFParser.yy"
    {(yyval.pString) = const_cast<String*>((yyvsp[0].pDataType)->pDataType.release()); delete (yyvsp[0].pDataType);}
    break;

  case 168:
#line 909 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 169:
#line 910 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 170:
#line 912 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 171:
#line 913 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 172:
#line 915 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 173:
#line 916 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 174:
#line 917 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 175:
#line 918 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 176:
#line 919 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 177:
#line 921 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 178:
#line 922 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 179:
#line 923 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 180:
#line 924 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 181:
#line 925 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;

  case 182:
#line 926 "OW_MOFParser.yy"
    {(yyval.pString) = (yyvsp[0].pString);}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3062 "OW_MOFParser.cc"

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


#line 930 "OW_MOFParser.yy"

void yyerror(const char* string)
{
	OW_THROW(MOFParserException, string);
}



