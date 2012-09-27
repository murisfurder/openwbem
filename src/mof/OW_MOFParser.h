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
/* Line 1447 of yacc.c.  */
#line 214 "OW_MOFParser.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





