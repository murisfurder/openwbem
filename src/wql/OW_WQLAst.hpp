/*******************************************************************************
* Copyright (C) 2003-2004 Vintela, Inc. All rights reserved.
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

#ifndef OW_WQLAST_HPP_HPP_GUARD_
#define OW_WQLAST_HPP_HPP_GUARD_
#include "OW_config.h"
#include "OW_String.hpp"
#include "OW_Format.hpp"
#include "OW_List.hpp"
#include "OW_WQLVisitor.hpp"

#include <typeinfo>

#define OW_WQL_LOG_DEBUG(message) //nothing - until we create a way to get a logger

// The classes and functions defined in this file are not meant for general
// use, they are internal implementation details.  They may change at any time.

namespace OW_NAMESPACE
{

class OW_WQL_API node
{
	public:
		virtual ~node() {}
		void acceptInterface( WQLVisitor * v)
		{
			OW_WQL_LOG_DEBUG(Format("About to accept node of type: %1 , using visitor : %2", typeid(*this).name(), typeid(*v).name()));
			accept(v);
			OW_WQL_LOG_DEBUG(Format("Finished accepting node of type: %1 , using visitor : %2", typeid(*this).name(), typeid(*v).name()));
		}
	private:
		virtual void accept( WQLVisitor * ) const = 0;
};
class OW_WQL_API stmt: public node
{
	public:
		stmt()
			{}
		virtual ~stmt() {}
};
class OW_WQL_API stmt_selectStmt_optSemicolon : public stmt
{
	public:
		stmt_selectStmt_optSemicolon(
			selectStmt* pNewselectStmt1,
			optSemicolon* pNewoptSemicolon2
		)
			: stmt()
			, m_pselectStmt1(pNewselectStmt1)
			, m_poptSemicolon2(pNewoptSemicolon2)
		{}
		virtual ~stmt_selectStmt_optSemicolon();
		void accept( WQLVisitor* v ) const
		{
			v->visit_stmt_selectStmt_optSemicolon( this );
		}
		selectStmt* m_pselectStmt1;
		optSemicolon* m_poptSemicolon2;
};
class OW_WQL_API stmt_updateStmt_optSemicolon : public stmt
{
	public:
		stmt_updateStmt_optSemicolon(
			updateStmt* pNewupdateStmt1,
			optSemicolon* pNewoptSemicolon2
		)
			: stmt()
			, m_pupdateStmt1(pNewupdateStmt1)
			, m_poptSemicolon2(pNewoptSemicolon2)
		{}
		virtual ~stmt_updateStmt_optSemicolon();
		void accept( WQLVisitor* v ) const
		{
			v->visit_stmt_updateStmt_optSemicolon( this );
		}
		updateStmt* m_pupdateStmt1;
		optSemicolon* m_poptSemicolon2;
};
class OW_WQL_API stmt_insertStmt_optSemicolon : public stmt
{
	public:
		stmt_insertStmt_optSemicolon(
			insertStmt* pNewinsertStmt1,
			optSemicolon* pNewoptSemicolon2
		)
			: stmt()
			, m_pinsertStmt1(pNewinsertStmt1)
			, m_poptSemicolon2(pNewoptSemicolon2)
		{}
		virtual ~stmt_insertStmt_optSemicolon();
		void accept( WQLVisitor* v ) const
		{
			v->visit_stmt_insertStmt_optSemicolon( this );
		}
		insertStmt* m_pinsertStmt1;
		optSemicolon* m_poptSemicolon2;
};
class OW_WQL_API stmt_deleteStmt_optSemicolon : public stmt
{
	public:
		stmt_deleteStmt_optSemicolon(
			deleteStmt* pNewdeleteStmt1,
			optSemicolon* pNewoptSemicolon2
		)
			: stmt()
			, m_pdeleteStmt1(pNewdeleteStmt1)
			, m_poptSemicolon2(pNewoptSemicolon2)
		{}
		virtual ~stmt_deleteStmt_optSemicolon();
		void accept( WQLVisitor* v ) const
		{
			v->visit_stmt_deleteStmt_optSemicolon( this );
		}
		deleteStmt* m_pdeleteStmt1;
		optSemicolon* m_poptSemicolon2;
};
class OW_WQL_API optSemicolon: public node
{
	public:
		optSemicolon()
			{}
		virtual ~optSemicolon() {}
};
class OW_WQL_API optSemicolon_empty : public optSemicolon
{
	public:
		optSemicolon_empty(
		)
			: optSemicolon()
		{}
		virtual ~optSemicolon_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSemicolon_empty( this );
		}
};
class OW_WQL_API optSemicolon_SEMICOLON : public optSemicolon
{
	public:
		optSemicolon_SEMICOLON(
			String* pNewSEMICOLON1
		)
			: optSemicolon()
			, m_pSEMICOLON1(pNewSEMICOLON1)
		{}
		virtual ~optSemicolon_SEMICOLON();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSemicolon_SEMICOLON( this );
		}
		String* m_pSEMICOLON1;
};
class OW_WQL_API insertStmt : public node
{
	public:
		insertStmt(
			String* pNewINSERT1,
			String* pNewINTO2,
			String* pNewstrRelationName3,
			insertRest* pNewinsertRest4
		)
			: m_pINSERT1(pNewINSERT1)
			, m_pINTO2(pNewINTO2)
			, m_pstrRelationName3(pNewstrRelationName3)
			, m_pinsertRest4(pNewinsertRest4)
		{}
		virtual ~insertStmt();
		void accept( WQLVisitor* v ) const
		{
			v->visit_insertStmt( this );
		}
		String* m_pINSERT1;
		String* m_pINTO2;
		String* m_pstrRelationName3;
		insertRest* m_pinsertRest4;
};
class OW_WQL_API insertRest: public node
{
	public:
		insertRest()
			{}
		virtual ~insertRest() {}
};
class OW_WQL_API insertRest_VALUES_LEFTPAREN_targetList_RIGHTPAREN : public insertRest
{
	public:
		insertRest_VALUES_LEFTPAREN_targetList_RIGHTPAREN(
			String* pNewVALUES1,
			String* pNewLEFTPAREN2,
			List< targetEl* >* pNewtargetList3,
			String* pNewRIGHTPAREN4
		)
			: insertRest()
			, m_pVALUES1(pNewVALUES1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_ptargetList3(pNewtargetList3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~insertRest_VALUES_LEFTPAREN_targetList_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_insertRest_VALUES_LEFTPAREN_targetList_RIGHTPAREN( this );
		}
		String* m_pVALUES1;
		String* m_pLEFTPAREN2;
		List< targetEl* >* m_ptargetList3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API insertRest_DEFAULT_VALUES : public insertRest
{
	public:
		insertRest_DEFAULT_VALUES(
			String* pNewDEFAULT1,
			String* pNewVALUES2
		)
			: insertRest()
			, m_pDEFAULT1(pNewDEFAULT1)
			, m_pVALUES2(pNewVALUES2)
		{}
		virtual ~insertRest_DEFAULT_VALUES();
		void accept( WQLVisitor* v ) const
		{
			v->visit_insertRest_DEFAULT_VALUES( this );
		}
		String* m_pDEFAULT1;
		String* m_pVALUES2;
};
class OW_WQL_API insertRest_LEFTPAREN_columnList_RIGHTPAREN_VALUES_LEFTPAREN_targetList_RIGHTPAREN : public insertRest
{
	public:
		insertRest_LEFTPAREN_columnList_RIGHTPAREN_VALUES_LEFTPAREN_targetList_RIGHTPAREN(
			String* pNewLEFTPAREN1,
			List< String* >* pNewcolumnList2,
			String* pNewRIGHTPAREN3,
			String* pNewVALUES4,
			String* pNewLEFTPAREN5,
			List< targetEl* >* pNewtargetList6,
			String* pNewRIGHTPAREN7
		)
			: insertRest()
			, m_pLEFTPAREN1(pNewLEFTPAREN1)
			, m_pcolumnList2(pNewcolumnList2)
			, m_pRIGHTPAREN3(pNewRIGHTPAREN3)
			, m_pVALUES4(pNewVALUES4)
			, m_pLEFTPAREN5(pNewLEFTPAREN5)
			, m_ptargetList6(pNewtargetList6)
			, m_pRIGHTPAREN7(pNewRIGHTPAREN7)
		{}
		virtual ~insertRest_LEFTPAREN_columnList_RIGHTPAREN_VALUES_LEFTPAREN_targetList_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_insertRest_LEFTPAREN_columnList_RIGHTPAREN_VALUES_LEFTPAREN_targetList_RIGHTPAREN( this );
		}
		String* m_pLEFTPAREN1;
		List< String* >* m_pcolumnList2;
		String* m_pRIGHTPAREN3;
		String* m_pVALUES4;
		String* m_pLEFTPAREN5;
		List< targetEl* >* m_ptargetList6;
		String* m_pRIGHTPAREN7;
};
class OW_WQL_API deleteStmt : public node
{
	public:
		deleteStmt(
			String* pNewDELETE1,
			String* pNewFROM2,
			String* pNewstrRelationName3,
			optWhereClause* pNewoptWhereClause4
		)
			: m_pDELETE1(pNewDELETE1)
			, m_pFROM2(pNewFROM2)
			, m_pstrRelationName3(pNewstrRelationName3)
			, m_poptWhereClause4(pNewoptWhereClause4)
		{}
		virtual ~deleteStmt();
		void accept( WQLVisitor* v ) const
		{
			v->visit_deleteStmt( this );
		}
		String* m_pDELETE1;
		String* m_pFROM2;
		String* m_pstrRelationName3;
		optWhereClause* m_poptWhereClause4;
};
class OW_WQL_API updateStmt : public node
{
	public:
		updateStmt(
			String* pNewUPDATE1,
			String* pNewstrRelationName2,
			String* pNewSET3,
			List< updateTargetEl* >* pNewupdateTargetList4,
			optWhereClause* pNewoptWhereClause5
		)
			: m_pUPDATE1(pNewUPDATE1)
			, m_pstrRelationName2(pNewstrRelationName2)
			, m_pSET3(pNewSET3)
			, m_pupdateTargetList4(pNewupdateTargetList4)
			, m_poptWhereClause5(pNewoptWhereClause5)
		{}
		virtual ~updateStmt();
		void accept( WQLVisitor* v ) const
		{
			v->visit_updateStmt( this );
		}
		String* m_pUPDATE1;
		String* m_pstrRelationName2;
		String* m_pSET3;
		List< updateTargetEl* >* m_pupdateTargetList4;
		optWhereClause* m_poptWhereClause5;
};
class OW_WQL_API selectStmt : public node
{
	public:
		selectStmt(
			String* pNewSELECT1,
			optDistinct* pNewoptDistinct2,
			List< targetEl* >* pNewtargetList3,
			optFromClause* pNewoptFromClause4,
			optWhereClause* pNewoptWhereClause5,
			optGroupClause* pNewoptGroupClause6,
			optHavingClause* pNewoptHavingClause7,
			optSortClause* pNewoptSortClause8
		)
			: m_pSELECT1(pNewSELECT1)
			, m_poptDistinct2(pNewoptDistinct2)
			, m_ptargetList3(pNewtargetList3)
			, m_poptFromClause4(pNewoptFromClause4)
			, m_poptWhereClause5(pNewoptWhereClause5)
			, m_poptGroupClause6(pNewoptGroupClause6)
			, m_poptHavingClause7(pNewoptHavingClause7)
			, m_poptSortClause8(pNewoptSortClause8)
		{}
		virtual ~selectStmt();
		void accept( WQLVisitor* v ) const
		{
			v->visit_selectStmt( this );
		}
		String* m_pSELECT1;
		optDistinct* m_poptDistinct2;
		List< targetEl* >* m_ptargetList3;
		optFromClause* m_poptFromClause4;
		optWhereClause* m_poptWhereClause5;
		optGroupClause* m_poptGroupClause6;
		optHavingClause* m_poptHavingClause7;
		optSortClause* m_poptSortClause8;
};
class OW_WQL_API exprSeq: public node
{
	public:
		exprSeq()
			{}
		virtual ~exprSeq() {}
};
class OW_WQL_API exprSeq_aExpr : public exprSeq
{
	public:
		exprSeq_aExpr(
			aExpr* pNewaExpr1
		)
			: exprSeq()
			, m_paExpr1(pNewaExpr1)
		{}
		virtual ~exprSeq_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_exprSeq_aExpr( this );
		}
		aExpr* m_paExpr1;
};
class OW_WQL_API exprSeq_exprSeq_COMMA_aExpr : public exprSeq
{
	public:
		exprSeq_exprSeq_COMMA_aExpr(
			exprSeq* pNewexprSeq1,
			String* pNewCOMMA2,
			aExpr* pNewaExpr3
		)
			: exprSeq()
			, m_pexprSeq1(pNewexprSeq1)
			, m_pCOMMA2(pNewCOMMA2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~exprSeq_exprSeq_COMMA_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_exprSeq_exprSeq_COMMA_aExpr( this );
		}
		exprSeq* m_pexprSeq1;
		String* m_pCOMMA2;
		aExpr* m_paExpr3;
};
class OW_WQL_API exprSeq_exprSeq_USING_aExpr : public exprSeq
{
	public:
		exprSeq_exprSeq_USING_aExpr(
			exprSeq* pNewexprSeq1,
			String* pNewUSING2,
			aExpr* pNewaExpr3
		)
			: exprSeq()
			, m_pexprSeq1(pNewexprSeq1)
			, m_pUSING2(pNewUSING2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~exprSeq_exprSeq_USING_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_exprSeq_exprSeq_USING_aExpr( this );
		}
		exprSeq* m_pexprSeq1;
		String* m_pUSING2;
		aExpr* m_paExpr3;
};
class OW_WQL_API optDistinct: public node
{
	public:
		optDistinct()
			{}
		virtual ~optDistinct() {}
};
class OW_WQL_API optDistinct_empty : public optDistinct
{
	public:
		optDistinct_empty(
		)
			: optDistinct()
		{}
		virtual ~optDistinct_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optDistinct_empty( this );
		}
};
class OW_WQL_API optDistinct_DISTINCT : public optDistinct
{
	public:
		optDistinct_DISTINCT(
			String* pNewDISTINCT1
		)
			: optDistinct()
			, m_pDISTINCT1(pNewDISTINCT1)
		{}
		virtual ~optDistinct_DISTINCT();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optDistinct_DISTINCT( this );
		}
		String* m_pDISTINCT1;
};
class OW_WQL_API optDistinct_DISTINCT_ON_LEFTPAREN_exprSeq_RIGHTPAREN : public optDistinct
{
	public:
		optDistinct_DISTINCT_ON_LEFTPAREN_exprSeq_RIGHTPAREN(
			String* pNewDISTINCT1,
			String* pNewON2,
			String* pNewLEFTPAREN3,
			exprSeq* pNewexprSeq4,
			String* pNewRIGHTPAREN5
		)
			: optDistinct()
			, m_pDISTINCT1(pNewDISTINCT1)
			, m_pON2(pNewON2)
			, m_pLEFTPAREN3(pNewLEFTPAREN3)
			, m_pexprSeq4(pNewexprSeq4)
			, m_pRIGHTPAREN5(pNewRIGHTPAREN5)
		{}
		virtual ~optDistinct_DISTINCT_ON_LEFTPAREN_exprSeq_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optDistinct_DISTINCT_ON_LEFTPAREN_exprSeq_RIGHTPAREN( this );
		}
		String* m_pDISTINCT1;
		String* m_pON2;
		String* m_pLEFTPAREN3;
		exprSeq* m_pexprSeq4;
		String* m_pRIGHTPAREN5;
};
class OW_WQL_API optDistinct_ALL : public optDistinct
{
	public:
		optDistinct_ALL(
			String* pNewALL1
		)
			: optDistinct()
			, m_pALL1(pNewALL1)
		{}
		virtual ~optDistinct_ALL();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optDistinct_ALL( this );
		}
		String* m_pALL1;
};
class OW_WQL_API sortClause : public node
{
	public:
		sortClause(
			String* pNewORDER1,
			String* pNewBY2,
			List< sortby* >* pNewsortbyList3
		)
			: m_pORDER1(pNewORDER1)
			, m_pBY2(pNewBY2)
			, m_psortbyList3(pNewsortbyList3)
		{}
		virtual ~sortClause();
		void accept( WQLVisitor* v ) const
		{
			v->visit_sortClause( this );
		}
		String* m_pORDER1;
		String* m_pBY2;
		List< sortby* >* m_psortbyList3;
};
class OW_WQL_API optSortClause: public node
{
	public:
		optSortClause()
			{}
		virtual ~optSortClause() {}
};
class OW_WQL_API optSortClause_empty : public optSortClause
{
	public:
		optSortClause_empty(
		)
			: optSortClause()
		{}
		virtual ~optSortClause_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSortClause_empty( this );
		}
};
class OW_WQL_API optSortClause_sortClause : public optSortClause
{
	public:
		optSortClause_sortClause(
			sortClause* pNewsortClause1
		)
			: optSortClause()
			, m_psortClause1(pNewsortClause1)
		{}
		virtual ~optSortClause_sortClause();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSortClause_sortClause( this );
		}
		sortClause* m_psortClause1;
};
class OW_WQL_API sortby : public node
{
	public:
		sortby(
			aExpr* pNewaExpr1,
			String* pNewstrOptOrderSpecification2
		)
			: m_paExpr1(pNewaExpr1)
			, m_pstrOptOrderSpecification2(pNewstrOptOrderSpecification2)
		{}
		virtual ~sortby();
		void accept( WQLVisitor* v ) const
		{
			v->visit_sortby( this );
		}
		aExpr* m_paExpr1;
		String* m_pstrOptOrderSpecification2;
};
class OW_WQL_API optGroupClause: public node
{
	public:
		optGroupClause()
			{}
		virtual ~optGroupClause() {}
};
class OW_WQL_API optGroupClause_empty : public optGroupClause
{
	public:
		optGroupClause_empty(
		)
			: optGroupClause()
		{}
		virtual ~optGroupClause_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optGroupClause_empty( this );
		}
};
class OW_WQL_API optGroupClause_GROUP_BY_exprSeq : public optGroupClause
{
	public:
		optGroupClause_GROUP_BY_exprSeq(
			String* pNewGROUP1,
			String* pNewBY2,
			exprSeq* pNewexprSeq3
		)
			: optGroupClause()
			, m_pGROUP1(pNewGROUP1)
			, m_pBY2(pNewBY2)
			, m_pexprSeq3(pNewexprSeq3)
		{}
		virtual ~optGroupClause_GROUP_BY_exprSeq();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optGroupClause_GROUP_BY_exprSeq( this );
		}
		String* m_pGROUP1;
		String* m_pBY2;
		exprSeq* m_pexprSeq3;
};
class OW_WQL_API optHavingClause: public node
{
	public:
		optHavingClause()
			{}
		virtual ~optHavingClause() {}
};
class OW_WQL_API optHavingClause_empty : public optHavingClause
{
	public:
		optHavingClause_empty(
		)
			: optHavingClause()
		{}
		virtual ~optHavingClause_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optHavingClause_empty( this );
		}
};
class OW_WQL_API optHavingClause_HAVING_aExpr : public optHavingClause
{
	public:
		optHavingClause_HAVING_aExpr(
			String* pNewHAVING1,
			aExpr* pNewaExpr2
		)
			: optHavingClause()
			, m_pHAVING1(pNewHAVING1)
			, m_paExpr2(pNewaExpr2)
		{}
		virtual ~optHavingClause_HAVING_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optHavingClause_HAVING_aExpr( this );
		}
		String* m_pHAVING1;
		aExpr* m_paExpr2;
};
class OW_WQL_API optFromClause: public node
{
	public:
		optFromClause()
			{}
		virtual ~optFromClause() {}
};
class OW_WQL_API optFromClause_empty : public optFromClause
{
	public:
		optFromClause_empty(
		)
			: optFromClause()
		{}
		virtual ~optFromClause_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optFromClause_empty( this );
		}
};
class OW_WQL_API optFromClause_FROM_fromList : public optFromClause
{
	public:
		optFromClause_FROM_fromList(
			String* pNewFROM1,
			List< tableRef* >* pNewfromList2
		)
			: optFromClause()
			, m_pFROM1(pNewFROM1)
			, m_pfromList2(pNewfromList2)
		{}
		virtual ~optFromClause_FROM_fromList();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optFromClause_FROM_fromList( this );
		}
		String* m_pFROM1;
		List< tableRef* >* m_pfromList2;
};
class OW_WQL_API tableRef: public node
{
	public:
		tableRef()
			{}
		virtual ~tableRef() {}
};
class OW_WQL_API tableRef_relationExpr : public tableRef
{
	public:
		tableRef_relationExpr(
			relationExpr* pNewrelationExpr1
		)
			: tableRef()
			, m_prelationExpr1(pNewrelationExpr1)
		{}
		virtual ~tableRef_relationExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_tableRef_relationExpr( this );
		}
		relationExpr* m_prelationExpr1;
};
class OW_WQL_API tableRef_relationExpr_aliasClause : public tableRef
{
	public:
		tableRef_relationExpr_aliasClause(
			relationExpr* pNewrelationExpr1,
			aliasClause* pNewaliasClause2
		)
			: tableRef()
			, m_prelationExpr1(pNewrelationExpr1)
			, m_paliasClause2(pNewaliasClause2)
		{}
		virtual ~tableRef_relationExpr_aliasClause();
		void accept( WQLVisitor* v ) const
		{
			v->visit_tableRef_relationExpr_aliasClause( this );
		}
		relationExpr* m_prelationExpr1;
		aliasClause* m_paliasClause2;
};
class OW_WQL_API tableRef_joinedTable : public tableRef
{
	public:
		tableRef_joinedTable(
			joinedTable* pNewjoinedTable1
		)
			: tableRef()
			, m_pjoinedTable1(pNewjoinedTable1)
		{}
		virtual ~tableRef_joinedTable();
		void accept( WQLVisitor* v ) const
		{
			v->visit_tableRef_joinedTable( this );
		}
		joinedTable* m_pjoinedTable1;
};
class OW_WQL_API tableRef_LEFTPAREN_joinedTable_RIGHTPAREN_aliasClause : public tableRef
{
	public:
		tableRef_LEFTPAREN_joinedTable_RIGHTPAREN_aliasClause(
			String* pNewLEFTPAREN1,
			joinedTable* pNewjoinedTable2,
			String* pNewRIGHTPAREN3,
			aliasClause* pNewaliasClause4
		)
			: tableRef()
			, m_pLEFTPAREN1(pNewLEFTPAREN1)
			, m_pjoinedTable2(pNewjoinedTable2)
			, m_pRIGHTPAREN3(pNewRIGHTPAREN3)
			, m_paliasClause4(pNewaliasClause4)
		{}
		virtual ~tableRef_LEFTPAREN_joinedTable_RIGHTPAREN_aliasClause();
		void accept( WQLVisitor* v ) const
		{
			v->visit_tableRef_LEFTPAREN_joinedTable_RIGHTPAREN_aliasClause( this );
		}
		String* m_pLEFTPAREN1;
		joinedTable* m_pjoinedTable2;
		String* m_pRIGHTPAREN3;
		aliasClause* m_paliasClause4;
};
class OW_WQL_API joinedTable: public node
{
	public:
		joinedTable()
			{}
		virtual ~joinedTable() {}
};
class OW_WQL_API joinedTable_LEFTPAREN_joinedTable_RIGHTPAREN : public joinedTable
{
	public:
		joinedTable_LEFTPAREN_joinedTable_RIGHTPAREN(
			String* pNewLEFTPAREN1,
			joinedTable* pNewjoinedTable2,
			String* pNewRIGHTPAREN3
		)
			: joinedTable()
			, m_pLEFTPAREN1(pNewLEFTPAREN1)
			, m_pjoinedTable2(pNewjoinedTable2)
			, m_pRIGHTPAREN3(pNewRIGHTPAREN3)
		{}
		virtual ~joinedTable_LEFTPAREN_joinedTable_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinedTable_LEFTPAREN_joinedTable_RIGHTPAREN( this );
		}
		String* m_pLEFTPAREN1;
		joinedTable* m_pjoinedTable2;
		String* m_pRIGHTPAREN3;
};
class OW_WQL_API joinedTable_tableRef_CROSS_JOIN_tableRef : public joinedTable
{
	public:
		joinedTable_tableRef_CROSS_JOIN_tableRef(
			tableRef* pNewtableRef1,
			String* pNewCROSS2,
			String* pNewJOIN3,
			tableRef* pNewtableRef4
		)
			: joinedTable()
			, m_ptableRef1(pNewtableRef1)
			, m_pCROSS2(pNewCROSS2)
			, m_pJOIN3(pNewJOIN3)
			, m_ptableRef4(pNewtableRef4)
		{}
		virtual ~joinedTable_tableRef_CROSS_JOIN_tableRef();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinedTable_tableRef_CROSS_JOIN_tableRef( this );
		}
		tableRef* m_ptableRef1;
		String* m_pCROSS2;
		String* m_pJOIN3;
		tableRef* m_ptableRef4;
};
class OW_WQL_API joinedTable_tableRef_UNIONJOIN_tableRef : public joinedTable
{
	public:
		joinedTable_tableRef_UNIONJOIN_tableRef(
			tableRef* pNewtableRef1,
			String* pNewUNIONJOIN2,
			tableRef* pNewtableRef3
		)
			: joinedTable()
			, m_ptableRef1(pNewtableRef1)
			, m_pUNIONJOIN2(pNewUNIONJOIN2)
			, m_ptableRef3(pNewtableRef3)
		{}
		virtual ~joinedTable_tableRef_UNIONJOIN_tableRef();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinedTable_tableRef_UNIONJOIN_tableRef( this );
		}
		tableRef* m_ptableRef1;
		String* m_pUNIONJOIN2;
		tableRef* m_ptableRef3;
};
class OW_WQL_API joinedTable_tableRef_joinType_JOIN_tableRef_joinQual : public joinedTable
{
	public:
		joinedTable_tableRef_joinType_JOIN_tableRef_joinQual(
			tableRef* pNewtableRef1,
			joinType* pNewjoinType2,
			String* pNewJOIN3,
			tableRef* pNewtableRef4,
			joinQual* pNewjoinQual5
		)
			: joinedTable()
			, m_ptableRef1(pNewtableRef1)
			, m_pjoinType2(pNewjoinType2)
			, m_pJOIN3(pNewJOIN3)
			, m_ptableRef4(pNewtableRef4)
			, m_pjoinQual5(pNewjoinQual5)
		{}
		virtual ~joinedTable_tableRef_joinType_JOIN_tableRef_joinQual();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinedTable_tableRef_joinType_JOIN_tableRef_joinQual( this );
		}
		tableRef* m_ptableRef1;
		joinType* m_pjoinType2;
		String* m_pJOIN3;
		tableRef* m_ptableRef4;
		joinQual* m_pjoinQual5;
};
class OW_WQL_API joinedTable_tableRef_JOIN_tableRef_joinQual : public joinedTable
{
	public:
		joinedTable_tableRef_JOIN_tableRef_joinQual(
			tableRef* pNewtableRef1,
			String* pNewJOIN2,
			tableRef* pNewtableRef3,
			joinQual* pNewjoinQual4
		)
			: joinedTable()
			, m_ptableRef1(pNewtableRef1)
			, m_pJOIN2(pNewJOIN2)
			, m_ptableRef3(pNewtableRef3)
			, m_pjoinQual4(pNewjoinQual4)
		{}
		virtual ~joinedTable_tableRef_JOIN_tableRef_joinQual();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinedTable_tableRef_JOIN_tableRef_joinQual( this );
		}
		tableRef* m_ptableRef1;
		String* m_pJOIN2;
		tableRef* m_ptableRef3;
		joinQual* m_pjoinQual4;
};
class OW_WQL_API joinedTable_tableRef_NATURAL_joinType_JOIN_tableRef : public joinedTable
{
	public:
		joinedTable_tableRef_NATURAL_joinType_JOIN_tableRef(
			tableRef* pNewtableRef1,
			String* pNewNATURAL2,
			joinType* pNewjoinType3,
			String* pNewJOIN4,
			tableRef* pNewtableRef5
		)
			: joinedTable()
			, m_ptableRef1(pNewtableRef1)
			, m_pNATURAL2(pNewNATURAL2)
			, m_pjoinType3(pNewjoinType3)
			, m_pJOIN4(pNewJOIN4)
			, m_ptableRef5(pNewtableRef5)
		{}
		virtual ~joinedTable_tableRef_NATURAL_joinType_JOIN_tableRef();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinedTable_tableRef_NATURAL_joinType_JOIN_tableRef( this );
		}
		tableRef* m_ptableRef1;
		String* m_pNATURAL2;
		joinType* m_pjoinType3;
		String* m_pJOIN4;
		tableRef* m_ptableRef5;
};
class OW_WQL_API joinedTable_tableRef_NATURAL_JOIN_tableRef : public joinedTable
{
	public:
		joinedTable_tableRef_NATURAL_JOIN_tableRef(
			tableRef* pNewtableRef1,
			String* pNewNATURAL2,
			String* pNewJOIN3,
			tableRef* pNewtableRef4
		)
			: joinedTable()
			, m_ptableRef1(pNewtableRef1)
			, m_pNATURAL2(pNewNATURAL2)
			, m_pJOIN3(pNewJOIN3)
			, m_ptableRef4(pNewtableRef4)
		{}
		virtual ~joinedTable_tableRef_NATURAL_JOIN_tableRef();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinedTable_tableRef_NATURAL_JOIN_tableRef( this );
		}
		tableRef* m_ptableRef1;
		String* m_pNATURAL2;
		String* m_pJOIN3;
		tableRef* m_ptableRef4;
};
class OW_WQL_API aliasClause: public node
{
	public:
		aliasClause()
			{}
		virtual ~aliasClause() {}
};
class OW_WQL_API aliasClause_AS_strColId_LEFTPAREN_nameList_RIGHTPAREN : public aliasClause
{
	public:
		aliasClause_AS_strColId_LEFTPAREN_nameList_RIGHTPAREN(
			String* pNewAS1,
			String* pNewstrColId2,
			String* pNewLEFTPAREN3,
			List< String* >* pNewnameList4,
			String* pNewRIGHTPAREN5
		)
			: aliasClause()
			, m_pAS1(pNewAS1)
			, m_pstrColId2(pNewstrColId2)
			, m_pLEFTPAREN3(pNewLEFTPAREN3)
			, m_pnameList4(pNewnameList4)
			, m_pRIGHTPAREN5(pNewRIGHTPAREN5)
		{}
		virtual ~aliasClause_AS_strColId_LEFTPAREN_nameList_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aliasClause_AS_strColId_LEFTPAREN_nameList_RIGHTPAREN( this );
		}
		String* m_pAS1;
		String* m_pstrColId2;
		String* m_pLEFTPAREN3;
		List< String* >* m_pnameList4;
		String* m_pRIGHTPAREN5;
};
class OW_WQL_API aliasClause_AS_strColId : public aliasClause
{
	public:
		aliasClause_AS_strColId(
			String* pNewAS1,
			String* pNewstrColId2
		)
			: aliasClause()
			, m_pAS1(pNewAS1)
			, m_pstrColId2(pNewstrColId2)
		{}
		virtual ~aliasClause_AS_strColId();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aliasClause_AS_strColId( this );
		}
		String* m_pAS1;
		String* m_pstrColId2;
};
class OW_WQL_API aliasClause_strColId_LEFTPAREN_nameList_RIGHTPAREN : public aliasClause
{
	public:
		aliasClause_strColId_LEFTPAREN_nameList_RIGHTPAREN(
			String* pNewstrColId1,
			String* pNewLEFTPAREN2,
			List< String* >* pNewnameList3,
			String* pNewRIGHTPAREN4
		)
			: aliasClause()
			, m_pstrColId1(pNewstrColId1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pnameList3(pNewnameList3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~aliasClause_strColId_LEFTPAREN_nameList_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aliasClause_strColId_LEFTPAREN_nameList_RIGHTPAREN( this );
		}
		String* m_pstrColId1;
		String* m_pLEFTPAREN2;
		List< String* >* m_pnameList3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API aliasClause_strColId : public aliasClause
{
	public:
		aliasClause_strColId(
			String* pNewstrColId1
		)
			: aliasClause()
			, m_pstrColId1(pNewstrColId1)
		{}
		virtual ~aliasClause_strColId();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aliasClause_strColId( this );
		}
		String* m_pstrColId1;
};
class OW_WQL_API joinType: public node
{
	public:
		joinType()
			{}
		virtual ~joinType() {}
};
class OW_WQL_API joinType_FULL_strOptJoinOuter : public joinType
{
	public:
		joinType_FULL_strOptJoinOuter(
			String* pNewFULL1,
			String* pNewstrOptJoinOuter2
		)
			: joinType()
			, m_pFULL1(pNewFULL1)
			, m_pstrOptJoinOuter2(pNewstrOptJoinOuter2)
		{}
		virtual ~joinType_FULL_strOptJoinOuter();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinType_FULL_strOptJoinOuter( this );
		}
		String* m_pFULL1;
		String* m_pstrOptJoinOuter2;
};
class OW_WQL_API joinType_LEFT_strOptJoinOuter : public joinType
{
	public:
		joinType_LEFT_strOptJoinOuter(
			String* pNewLEFT1,
			String* pNewstrOptJoinOuter2
		)
			: joinType()
			, m_pLEFT1(pNewLEFT1)
			, m_pstrOptJoinOuter2(pNewstrOptJoinOuter2)
		{}
		virtual ~joinType_LEFT_strOptJoinOuter();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinType_LEFT_strOptJoinOuter( this );
		}
		String* m_pLEFT1;
		String* m_pstrOptJoinOuter2;
};
class OW_WQL_API joinType_RIGHT_strOptJoinOuter : public joinType
{
	public:
		joinType_RIGHT_strOptJoinOuter(
			String* pNewRIGHT1,
			String* pNewstrOptJoinOuter2
		)
			: joinType()
			, m_pRIGHT1(pNewRIGHT1)
			, m_pstrOptJoinOuter2(pNewstrOptJoinOuter2)
		{}
		virtual ~joinType_RIGHT_strOptJoinOuter();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinType_RIGHT_strOptJoinOuter( this );
		}
		String* m_pRIGHT1;
		String* m_pstrOptJoinOuter2;
};
class OW_WQL_API joinType_INNERP : public joinType
{
	public:
		joinType_INNERP(
			String* pNewINNERP1
		)
			: joinType()
			, m_pINNERP1(pNewINNERP1)
		{}
		virtual ~joinType_INNERP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinType_INNERP( this );
		}
		String* m_pINNERP1;
};
class OW_WQL_API joinQual: public node
{
	public:
		joinQual()
			{}
		virtual ~joinQual() {}
};
class OW_WQL_API joinQual_USING_LEFTPAREN_nameList_RIGHTPAREN : public joinQual
{
	public:
		joinQual_USING_LEFTPAREN_nameList_RIGHTPAREN(
			String* pNewUSING1,
			String* pNewLEFTPAREN2,
			List< String* >* pNewnameList3,
			String* pNewRIGHTPAREN4
		)
			: joinQual()
			, m_pUSING1(pNewUSING1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pnameList3(pNewnameList3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~joinQual_USING_LEFTPAREN_nameList_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinQual_USING_LEFTPAREN_nameList_RIGHTPAREN( this );
		}
		String* m_pUSING1;
		String* m_pLEFTPAREN2;
		List< String* >* m_pnameList3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API joinQual_ON_aExpr : public joinQual
{
	public:
		joinQual_ON_aExpr(
			String* pNewON1,
			aExpr* pNewaExpr2
		)
			: joinQual()
			, m_pON1(pNewON1)
			, m_paExpr2(pNewaExpr2)
		{}
		virtual ~joinQual_ON_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_joinQual_ON_aExpr( this );
		}
		String* m_pON1;
		aExpr* m_paExpr2;
};
class OW_WQL_API relationExpr: public node
{
	public:
		relationExpr()
			{}
		virtual ~relationExpr() {}
};
class OW_WQL_API relationExpr_strRelationName : public relationExpr
{
	public:
		relationExpr_strRelationName(
			String* pNewstrRelationName1
		)
			: relationExpr()
			, m_pstrRelationName1(pNewstrRelationName1)
		{}
		virtual ~relationExpr_strRelationName();
		void accept( WQLVisitor* v ) const
		{
			v->visit_relationExpr_strRelationName( this );
		}
		String* m_pstrRelationName1;
};
class OW_WQL_API relationExpr_strRelationName_ASTERISK : public relationExpr
{
	public:
		relationExpr_strRelationName_ASTERISK(
			String* pNewstrRelationName1,
			String* pNewASTERISK2
		)
			: relationExpr()
			, m_pstrRelationName1(pNewstrRelationName1)
			, m_pASTERISK2(pNewASTERISK2)
		{}
		virtual ~relationExpr_strRelationName_ASTERISK();
		void accept( WQLVisitor* v ) const
		{
			v->visit_relationExpr_strRelationName_ASTERISK( this );
		}
		String* m_pstrRelationName1;
		String* m_pASTERISK2;
};
class OW_WQL_API relationExpr_ONLY_strRelationName : public relationExpr
{
	public:
		relationExpr_ONLY_strRelationName(
			String* pNewONLY1,
			String* pNewstrRelationName2
		)
			: relationExpr()
			, m_pONLY1(pNewONLY1)
			, m_pstrRelationName2(pNewstrRelationName2)
		{}
		virtual ~relationExpr_ONLY_strRelationName();
		void accept( WQLVisitor* v ) const
		{
			v->visit_relationExpr_ONLY_strRelationName( this );
		}
		String* m_pONLY1;
		String* m_pstrRelationName2;
};
class OW_WQL_API optWhereClause: public node
{
	public:
		optWhereClause()
			{}
		virtual ~optWhereClause() {}
};
class OW_WQL_API optWhereClause_empty : public optWhereClause
{
	public:
		optWhereClause_empty(
		)
			: optWhereClause()
		{}
		virtual ~optWhereClause_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optWhereClause_empty( this );
		}
};
class OW_WQL_API optWhereClause_WHERE_aExpr : public optWhereClause
{
	public:
		optWhereClause_WHERE_aExpr(
			String* pNewWHERE1,
			aExpr* pNewaExpr2
		)
			: optWhereClause()
			, m_pWHERE1(pNewWHERE1)
			, m_paExpr2(pNewaExpr2)
		{}
		virtual ~optWhereClause_WHERE_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optWhereClause_WHERE_aExpr( this );
		}
		String* m_pWHERE1;
		aExpr* m_paExpr2;
};
class OW_WQL_API rowExpr : public node
{
	public:
		rowExpr(
			String* pNewLEFTPAREN1,
			rowDescriptor* pNewrowDescriptor2,
			String* pNewRIGHTPAREN3,
			String* pNewstrAllOp4,
			String* pNewLEFTPAREN5,
			rowDescriptor* pNewrowDescriptor6,
			String* pNewRIGHTPAREN7
		)
			: m_pLEFTPAREN1(pNewLEFTPAREN1)
			, m_prowDescriptor2(pNewrowDescriptor2)
			, m_pRIGHTPAREN3(pNewRIGHTPAREN3)
			, m_pstrAllOp4(pNewstrAllOp4)
			, m_pLEFTPAREN5(pNewLEFTPAREN5)
			, m_prowDescriptor6(pNewrowDescriptor6)
			, m_pRIGHTPAREN7(pNewRIGHTPAREN7)
		{}
		virtual ~rowExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_rowExpr( this );
		}
		String* m_pLEFTPAREN1;
		rowDescriptor* m_prowDescriptor2;
		String* m_pRIGHTPAREN3;
		String* m_pstrAllOp4;
		String* m_pLEFTPAREN5;
		rowDescriptor* m_prowDescriptor6;
		String* m_pRIGHTPAREN7;
};
class OW_WQL_API rowDescriptor : public node
{
	public:
		rowDescriptor(
			List< aExpr* >* pNewrowList1,
			String* pNewCOMMA2,
			aExpr* pNewaExpr3
		)
			: m_prowList1(pNewrowList1)
			, m_pCOMMA2(pNewCOMMA2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~rowDescriptor();
		void accept( WQLVisitor* v ) const
		{
			v->visit_rowDescriptor( this );
		}
		List< aExpr* >* m_prowList1;
		String* m_pCOMMA2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr: public node
{
	public:
		aExpr()
			{}
		virtual ~aExpr() {}
};
class OW_WQL_API aExpr_cExpr : public aExpr
{
	public:
		aExpr_cExpr(
			cExpr* pNewcExpr1
		)
			: aExpr()
			, m_pcExpr1(pNewcExpr1)
		{}
		virtual ~aExpr_cExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_cExpr( this );
		}
		cExpr* m_pcExpr1;
};
class OW_WQL_API aExpr_aExpr_AT_TIME_ZONE_cExpr : public aExpr
{
	public:
		aExpr_aExpr_AT_TIME_ZONE_cExpr(
			aExpr* pNewaExpr1,
			String* pNewAT2,
			String* pNewTIME3,
			String* pNewZONE4,
			cExpr* pNewcExpr5
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pAT2(pNewAT2)
			, m_pTIME3(pNewTIME3)
			, m_pZONE4(pNewZONE4)
			, m_pcExpr5(pNewcExpr5)
		{}
		virtual ~aExpr_aExpr_AT_TIME_ZONE_cExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_AT_TIME_ZONE_cExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pAT2;
		String* m_pTIME3;
		String* m_pZONE4;
		cExpr* m_pcExpr5;
};
class OW_WQL_API aExpr_PLUS_aExpr : public aExpr
{
	public:
		aExpr_PLUS_aExpr(
			String* pNewPLUS1,
			aExpr* pNewaExpr2
		)
			: aExpr()
			, m_pPLUS1(pNewPLUS1)
			, m_paExpr2(pNewaExpr2)
		{}
		virtual ~aExpr_PLUS_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_PLUS_aExpr( this );
		}
		String* m_pPLUS1;
		aExpr* m_paExpr2;
};
class OW_WQL_API aExpr_MINUS_aExpr : public aExpr
{
	public:
		aExpr_MINUS_aExpr(
			String* pNewMINUS1,
			aExpr* pNewaExpr2
		)
			: aExpr()
			, m_pMINUS1(pNewMINUS1)
			, m_paExpr2(pNewaExpr2)
		{}
		virtual ~aExpr_MINUS_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_MINUS_aExpr( this );
		}
		String* m_pMINUS1;
		aExpr* m_paExpr2;
};
class OW_WQL_API aExpr_BITINVERT_aExpr : public aExpr
{
	public:
		aExpr_BITINVERT_aExpr(
			String* pNewBITINVERT1,
			aExpr* pNewaExpr2
		)
			: aExpr()
			, m_pBITINVERT1(pNewBITINVERT1)
			, m_paExpr2(pNewaExpr2)
		{}
		virtual ~aExpr_BITINVERT_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_BITINVERT_aExpr( this );
		}
		String* m_pBITINVERT1;
		aExpr* m_paExpr2;
};
class OW_WQL_API aExpr_aExpr_PLUS_aExpr : public aExpr
{
	public:
		aExpr_aExpr_PLUS_aExpr(
			aExpr* pNewaExpr1,
			String* pNewPLUS2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pPLUS2(pNewPLUS2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_PLUS_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_PLUS_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pPLUS2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_MINUS_aExpr : public aExpr
{
	public:
		aExpr_aExpr_MINUS_aExpr(
			aExpr* pNewaExpr1,
			String* pNewMINUS2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pMINUS2(pNewMINUS2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_MINUS_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_MINUS_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pMINUS2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_ASTERISK_aExpr : public aExpr
{
	public:
		aExpr_aExpr_ASTERISK_aExpr(
			aExpr* pNewaExpr1,
			String* pNewASTERISK2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pASTERISK2(pNewASTERISK2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_ASTERISK_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_ASTERISK_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pASTERISK2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_SOLIDUS_aExpr : public aExpr
{
	public:
		aExpr_aExpr_SOLIDUS_aExpr(
			aExpr* pNewaExpr1,
			String* pNewSOLIDUS2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pSOLIDUS2(pNewSOLIDUS2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_SOLIDUS_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_SOLIDUS_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pSOLIDUS2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_PERCENT_aExpr : public aExpr
{
	public:
		aExpr_aExpr_PERCENT_aExpr(
			aExpr* pNewaExpr1,
			String* pNewPERCENT2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pPERCENT2(pNewPERCENT2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_PERCENT_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_PERCENT_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pPERCENT2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_BITAND_aExpr : public aExpr
{
	public:
		aExpr_aExpr_BITAND_aExpr(
			aExpr* pNewaExpr1,
			String* pNewBITAND2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pBITAND2(pNewBITAND2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_BITAND_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_BITAND_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pBITAND2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_BITOR_aExpr : public aExpr
{
	public:
		aExpr_aExpr_BITOR_aExpr(
			aExpr* pNewaExpr1,
			String* pNewBITOR2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pBITOR2(pNewBITOR2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_BITOR_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_BITOR_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pBITOR2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_BITSHIFTLEFT_aExpr : public aExpr
{
	public:
		aExpr_aExpr_BITSHIFTLEFT_aExpr(
			aExpr* pNewaExpr1,
			String* pNewBITSHIFTLEFT2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pBITSHIFTLEFT2(pNewBITSHIFTLEFT2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_BITSHIFTLEFT_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_BITSHIFTLEFT_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pBITSHIFTLEFT2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_BITSHIFTRIGHT_aExpr : public aExpr
{
	public:
		aExpr_aExpr_BITSHIFTRIGHT_aExpr(
			aExpr* pNewaExpr1,
			String* pNewBITSHIFTRIGHT2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pBITSHIFTRIGHT2(pNewBITSHIFTRIGHT2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_BITSHIFTRIGHT_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_BITSHIFTRIGHT_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pBITSHIFTRIGHT2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_LESSTHAN_aExpr : public aExpr
{
	public:
		aExpr_aExpr_LESSTHAN_aExpr(
			aExpr* pNewaExpr1,
			String* pNewLESSTHAN2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pLESSTHAN2(pNewLESSTHAN2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_LESSTHAN_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_LESSTHAN_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pLESSTHAN2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_LESSTHANOREQUALS_aExpr : public aExpr
{
	public:
		aExpr_aExpr_LESSTHANOREQUALS_aExpr(
			aExpr* pNewaExpr1,
			String* pNewLESSTHANOREQUALS2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pLESSTHANOREQUALS2(pNewLESSTHANOREQUALS2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_LESSTHANOREQUALS_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_LESSTHANOREQUALS_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pLESSTHANOREQUALS2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_GREATERTHAN_aExpr : public aExpr
{
	public:
		aExpr_aExpr_GREATERTHAN_aExpr(
			aExpr* pNewaExpr1,
			String* pNewGREATERTHAN2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pGREATERTHAN2(pNewGREATERTHAN2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_GREATERTHAN_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_GREATERTHAN_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pGREATERTHAN2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_GREATERTHANOREQUALS_aExpr : public aExpr
{
	public:
		aExpr_aExpr_GREATERTHANOREQUALS_aExpr(
			aExpr* pNewaExpr1,
			String* pNewGREATERTHANOREQUALS2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pGREATERTHANOREQUALS2(pNewGREATERTHANOREQUALS2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_GREATERTHANOREQUALS_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_GREATERTHANOREQUALS_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pGREATERTHANOREQUALS2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_EQUALS_aExpr : public aExpr
{
	public:
		aExpr_aExpr_EQUALS_aExpr(
			aExpr* pNewaExpr1,
			String* pNewEQUALS2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pEQUALS2(pNewEQUALS2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_EQUALS_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_EQUALS_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pEQUALS2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_NOTEQUALS_aExpr : public aExpr
{
	public:
		aExpr_aExpr_NOTEQUALS_aExpr(
			aExpr* pNewaExpr1,
			String* pNewNOTEQUALS2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pNOTEQUALS2(pNewNOTEQUALS2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_NOTEQUALS_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_NOTEQUALS_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pNOTEQUALS2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_AND_aExpr : public aExpr
{
	public:
		aExpr_aExpr_AND_aExpr(
			aExpr* pNewaExpr1,
			String* pNewAND2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pAND2(pNewAND2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_AND_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_AND_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pAND2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_OR_aExpr : public aExpr
{
	public:
		aExpr_aExpr_OR_aExpr(
			aExpr* pNewaExpr1,
			String* pNewOR2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pOR2(pNewOR2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_OR_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_OR_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pOR2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_NOT_aExpr : public aExpr
{
	public:
		aExpr_NOT_aExpr(
			String* pNewNOT1,
			aExpr* pNewaExpr2
		)
			: aExpr()
			, m_pNOT1(pNewNOT1)
			, m_paExpr2(pNewaExpr2)
		{}
		virtual ~aExpr_NOT_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_NOT_aExpr( this );
		}
		String* m_pNOT1;
		aExpr* m_paExpr2;
};
class OW_WQL_API aExpr_aExpr_CONCATENATION_aExpr : public aExpr
{
	public:
		aExpr_aExpr_CONCATENATION_aExpr(
			aExpr* pNewaExpr1,
			String* pNewCONCATENATION2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pCONCATENATION2(pNewCONCATENATION2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_CONCATENATION_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_CONCATENATION_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pCONCATENATION2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_LIKE_aExpr : public aExpr
{
	public:
		aExpr_aExpr_LIKE_aExpr(
			aExpr* pNewaExpr1,
			String* pNewLIKE2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pLIKE2(pNewLIKE2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_LIKE_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_LIKE_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pLIKE2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_aExpr_LIKE_aExpr_ESCAPE_aExpr : public aExpr
{
	public:
		aExpr_aExpr_LIKE_aExpr_ESCAPE_aExpr(
			aExpr* pNewaExpr1,
			String* pNewLIKE2,
			aExpr* pNewaExpr3,
			String* pNewESCAPE4,
			aExpr* pNewaExpr5
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pLIKE2(pNewLIKE2)
			, m_paExpr3(pNewaExpr3)
			, m_pESCAPE4(pNewESCAPE4)
			, m_paExpr5(pNewaExpr5)
		{}
		virtual ~aExpr_aExpr_LIKE_aExpr_ESCAPE_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_LIKE_aExpr_ESCAPE_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pLIKE2;
		aExpr* m_paExpr3;
		String* m_pESCAPE4;
		aExpr* m_paExpr5;
};
class OW_WQL_API aExpr_aExpr_NOT_LIKE_aExpr : public aExpr
{
	public:
		aExpr_aExpr_NOT_LIKE_aExpr(
			aExpr* pNewaExpr1,
			String* pNewNOT2,
			String* pNewLIKE3,
			aExpr* pNewaExpr4
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pNOT2(pNewNOT2)
			, m_pLIKE3(pNewLIKE3)
			, m_paExpr4(pNewaExpr4)
		{}
		virtual ~aExpr_aExpr_NOT_LIKE_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_NOT_LIKE_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pNOT2;
		String* m_pLIKE3;
		aExpr* m_paExpr4;
};
class OW_WQL_API aExpr_aExpr_NOT_LIKE_aExpr_ESCAPE_aExpr : public aExpr
{
	public:
		aExpr_aExpr_NOT_LIKE_aExpr_ESCAPE_aExpr(
			aExpr* pNewaExpr1,
			String* pNewNOT2,
			String* pNewLIKE3,
			aExpr* pNewaExpr4,
			String* pNewESCAPE5,
			aExpr* pNewaExpr6
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pNOT2(pNewNOT2)
			, m_pLIKE3(pNewLIKE3)
			, m_paExpr4(pNewaExpr4)
			, m_pESCAPE5(pNewESCAPE5)
			, m_paExpr6(pNewaExpr6)
		{}
		virtual ~aExpr_aExpr_NOT_LIKE_aExpr_ESCAPE_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_NOT_LIKE_aExpr_ESCAPE_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pNOT2;
		String* m_pLIKE3;
		aExpr* m_paExpr4;
		String* m_pESCAPE5;
		aExpr* m_paExpr6;
};
class OW_WQL_API aExpr_aExpr_ISNULL : public aExpr
{
	public:
		aExpr_aExpr_ISNULL(
			aExpr* pNewaExpr1,
			String* pNewISNULL2
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pISNULL2(pNewISNULL2)
		{}
		virtual ~aExpr_aExpr_ISNULL();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_ISNULL( this );
		}
		aExpr* m_paExpr1;
		String* m_pISNULL2;
};
class OW_WQL_API aExpr_aExpr_IS_NULLP : public aExpr
{
	public:
		aExpr_aExpr_IS_NULLP(
			aExpr* pNewaExpr1,
			String* pNewIS2,
			String* pNewNULLP3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pIS2(pNewIS2)
			, m_pNULLP3(pNewNULLP3)
		{}
		virtual ~aExpr_aExpr_IS_NULLP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_IS_NULLP( this );
		}
		aExpr* m_paExpr1;
		String* m_pIS2;
		String* m_pNULLP3;
};
class OW_WQL_API aExpr_aExpr_NOTNULL : public aExpr
{
	public:
		aExpr_aExpr_NOTNULL(
			aExpr* pNewaExpr1,
			String* pNewNOTNULL2
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pNOTNULL2(pNewNOTNULL2)
		{}
		virtual ~aExpr_aExpr_NOTNULL();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_NOTNULL( this );
		}
		aExpr* m_paExpr1;
		String* m_pNOTNULL2;
};
class OW_WQL_API aExpr_aExpr_IS_NOT_NULLP : public aExpr
{
	public:
		aExpr_aExpr_IS_NOT_NULLP(
			aExpr* pNewaExpr1,
			String* pNewIS2,
			String* pNewNOT3,
			String* pNewNULLP4
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pIS2(pNewIS2)
			, m_pNOT3(pNewNOT3)
			, m_pNULLP4(pNewNULLP4)
		{}
		virtual ~aExpr_aExpr_IS_NOT_NULLP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_IS_NOT_NULLP( this );
		}
		aExpr* m_paExpr1;
		String* m_pIS2;
		String* m_pNOT3;
		String* m_pNULLP4;
};
class OW_WQL_API aExpr_aExpr_IS_TRUEP : public aExpr
{
	public:
		aExpr_aExpr_IS_TRUEP(
			aExpr* pNewaExpr1,
			String* pNewIS2,
			String* pNewTRUEP3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pIS2(pNewIS2)
			, m_pTRUEP3(pNewTRUEP3)
		{}
		virtual ~aExpr_aExpr_IS_TRUEP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_IS_TRUEP( this );
		}
		aExpr* m_paExpr1;
		String* m_pIS2;
		String* m_pTRUEP3;
};
class OW_WQL_API aExpr_aExpr_IS_NOT_FALSEP : public aExpr
{
	public:
		aExpr_aExpr_IS_NOT_FALSEP(
			aExpr* pNewaExpr1,
			String* pNewIS2,
			String* pNewNOT3,
			String* pNewFALSEP4
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pIS2(pNewIS2)
			, m_pNOT3(pNewNOT3)
			, m_pFALSEP4(pNewFALSEP4)
		{}
		virtual ~aExpr_aExpr_IS_NOT_FALSEP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_IS_NOT_FALSEP( this );
		}
		aExpr* m_paExpr1;
		String* m_pIS2;
		String* m_pNOT3;
		String* m_pFALSEP4;
};
class OW_WQL_API aExpr_aExpr_IS_FALSEP : public aExpr
{
	public:
		aExpr_aExpr_IS_FALSEP(
			aExpr* pNewaExpr1,
			String* pNewIS2,
			String* pNewFALSEP3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pIS2(pNewIS2)
			, m_pFALSEP3(pNewFALSEP3)
		{}
		virtual ~aExpr_aExpr_IS_FALSEP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_IS_FALSEP( this );
		}
		aExpr* m_paExpr1;
		String* m_pIS2;
		String* m_pFALSEP3;
};
class OW_WQL_API aExpr_aExpr_IS_NOT_TRUEP : public aExpr
{
	public:
		aExpr_aExpr_IS_NOT_TRUEP(
			aExpr* pNewaExpr1,
			String* pNewIS2,
			String* pNewNOT3,
			String* pNewTRUEP4
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pIS2(pNewIS2)
			, m_pNOT3(pNewNOT3)
			, m_pTRUEP4(pNewTRUEP4)
		{}
		virtual ~aExpr_aExpr_IS_NOT_TRUEP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_IS_NOT_TRUEP( this );
		}
		aExpr* m_paExpr1;
		String* m_pIS2;
		String* m_pNOT3;
		String* m_pTRUEP4;
};
class OW_WQL_API aExpr_aExpr_ISA_aExpr : public aExpr
{
	public:
		aExpr_aExpr_ISA_aExpr(
			aExpr* pNewaExpr1,
			String* pNewISA2,
			aExpr* pNewaExpr3
		)
			: aExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pISA2(pNewISA2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~aExpr_aExpr_ISA_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_aExpr_ISA_aExpr( this );
		}
		aExpr* m_paExpr1;
		String* m_pISA2;
		aExpr* m_paExpr3;
};
class OW_WQL_API aExpr_rowExpr : public aExpr
{
	public:
		aExpr_rowExpr(
			rowExpr* pNewrowExpr1
		)
			: aExpr()
			, m_prowExpr1(pNewrowExpr1)
		{}
		virtual ~aExpr_rowExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExpr_rowExpr( this );
		}
		rowExpr* m_prowExpr1;
};
class OW_WQL_API bExpr: public node
{
	public:
		bExpr()
			{}
		virtual ~bExpr() {}
};
class OW_WQL_API bExpr_cExpr : public bExpr
{
	public:
		bExpr_cExpr(
			cExpr* pNewcExpr1
		)
			: bExpr()
			, m_pcExpr1(pNewcExpr1)
		{}
		virtual ~bExpr_cExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_cExpr( this );
		}
		cExpr* m_pcExpr1;
};
class OW_WQL_API bExpr_PLUS_bExpr : public bExpr
{
	public:
		bExpr_PLUS_bExpr(
			String* pNewPLUS1,
			bExpr* pNewbExpr2
		)
			: bExpr()
			, m_pPLUS1(pNewPLUS1)
			, m_pbExpr2(pNewbExpr2)
		{}
		virtual ~bExpr_PLUS_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_PLUS_bExpr( this );
		}
		String* m_pPLUS1;
		bExpr* m_pbExpr2;
};
class OW_WQL_API bExpr_MINUS_bExpr : public bExpr
{
	public:
		bExpr_MINUS_bExpr(
			String* pNewMINUS1,
			bExpr* pNewbExpr2
		)
			: bExpr()
			, m_pMINUS1(pNewMINUS1)
			, m_pbExpr2(pNewbExpr2)
		{}
		virtual ~bExpr_MINUS_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_MINUS_bExpr( this );
		}
		String* m_pMINUS1;
		bExpr* m_pbExpr2;
};
class OW_WQL_API bExpr_BITINVERT_bExpr : public bExpr
{
	public:
		bExpr_BITINVERT_bExpr(
			String* pNewBITINVERT1,
			bExpr* pNewbExpr2
		)
			: bExpr()
			, m_pBITINVERT1(pNewBITINVERT1)
			, m_pbExpr2(pNewbExpr2)
		{}
		virtual ~bExpr_BITINVERT_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_BITINVERT_bExpr( this );
		}
		String* m_pBITINVERT1;
		bExpr* m_pbExpr2;
};
class OW_WQL_API bExpr_bExpr_PLUS_bExpr : public bExpr
{
	public:
		bExpr_bExpr_PLUS_bExpr(
			bExpr* pNewbExpr1,
			String* pNewPLUS2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pPLUS2(pNewPLUS2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_PLUS_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_PLUS_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pPLUS2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_MINUS_bExpr : public bExpr
{
	public:
		bExpr_bExpr_MINUS_bExpr(
			bExpr* pNewbExpr1,
			String* pNewMINUS2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pMINUS2(pNewMINUS2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_MINUS_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_MINUS_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pMINUS2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_ASTERISK_bExpr : public bExpr
{
	public:
		bExpr_bExpr_ASTERISK_bExpr(
			bExpr* pNewbExpr1,
			String* pNewASTERISK2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pASTERISK2(pNewASTERISK2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_ASTERISK_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_ASTERISK_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pASTERISK2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_SOLIDUS_bExpr : public bExpr
{
	public:
		bExpr_bExpr_SOLIDUS_bExpr(
			bExpr* pNewbExpr1,
			String* pNewSOLIDUS2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pSOLIDUS2(pNewSOLIDUS2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_SOLIDUS_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_SOLIDUS_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pSOLIDUS2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_PERCENT_bExpr : public bExpr
{
	public:
		bExpr_bExpr_PERCENT_bExpr(
			bExpr* pNewbExpr1,
			String* pNewPERCENT2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pPERCENT2(pNewPERCENT2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_PERCENT_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_PERCENT_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pPERCENT2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_BITAND_bExpr : public bExpr
{
	public:
		bExpr_bExpr_BITAND_bExpr(
			bExpr* pNewbExpr1,
			String* pNewBITAND2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pBITAND2(pNewBITAND2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_BITAND_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_BITAND_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pBITAND2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_BITOR_bExpr : public bExpr
{
	public:
		bExpr_bExpr_BITOR_bExpr(
			bExpr* pNewbExpr1,
			String* pNewBITOR2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pBITOR2(pNewBITOR2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_BITOR_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_BITOR_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pBITOR2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_BITSHIFTLEFT_bExpr : public bExpr
{
	public:
		bExpr_bExpr_BITSHIFTLEFT_bExpr(
			bExpr* pNewbExpr1,
			String* pNewBITSHIFTLEFT2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pBITSHIFTLEFT2(pNewBITSHIFTLEFT2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_BITSHIFTLEFT_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_BITSHIFTLEFT_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pBITSHIFTLEFT2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_BITSHIFTRIGHT_bExpr : public bExpr
{
	public:
		bExpr_bExpr_BITSHIFTRIGHT_bExpr(
			bExpr* pNewbExpr1,
			String* pNewBITSHIFTRIGHT2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pBITSHIFTRIGHT2(pNewBITSHIFTRIGHT2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_BITSHIFTRIGHT_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_BITSHIFTRIGHT_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pBITSHIFTRIGHT2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_LESSTHAN_bExpr : public bExpr
{
	public:
		bExpr_bExpr_LESSTHAN_bExpr(
			bExpr* pNewbExpr1,
			String* pNewLESSTHAN2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pLESSTHAN2(pNewLESSTHAN2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_LESSTHAN_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_LESSTHAN_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pLESSTHAN2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_LESSTHANOREQUALS_bExpr : public bExpr
{
	public:
		bExpr_bExpr_LESSTHANOREQUALS_bExpr(
			bExpr* pNewbExpr1,
			String* pNewLESSTHANOREQUALS2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pLESSTHANOREQUALS2(pNewLESSTHANOREQUALS2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_LESSTHANOREQUALS_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_LESSTHANOREQUALS_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pLESSTHANOREQUALS2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_GREATERTHAN_bExpr : public bExpr
{
	public:
		bExpr_bExpr_GREATERTHAN_bExpr(
			bExpr* pNewbExpr1,
			String* pNewGREATERTHAN2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pGREATERTHAN2(pNewGREATERTHAN2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_GREATERTHAN_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_GREATERTHAN_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pGREATERTHAN2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_GREATERTHANOREQUALS_bExpr : public bExpr
{
	public:
		bExpr_bExpr_GREATERTHANOREQUALS_bExpr(
			bExpr* pNewbExpr1,
			String* pNewGREATERTHANOREQUALS2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pGREATERTHANOREQUALS2(pNewGREATERTHANOREQUALS2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_GREATERTHANOREQUALS_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_GREATERTHANOREQUALS_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pGREATERTHANOREQUALS2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_EQUALS_bExpr : public bExpr
{
	public:
		bExpr_bExpr_EQUALS_bExpr(
			bExpr* pNewbExpr1,
			String* pNewEQUALS2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pEQUALS2(pNewEQUALS2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_EQUALS_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_EQUALS_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pEQUALS2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_NOTEQUALS_bExpr : public bExpr
{
	public:
		bExpr_bExpr_NOTEQUALS_bExpr(
			bExpr* pNewbExpr1,
			String* pNewNOTEQUALS2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pNOTEQUALS2(pNewNOTEQUALS2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_NOTEQUALS_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_NOTEQUALS_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pNOTEQUALS2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API bExpr_bExpr_CONCATENATION_bExpr : public bExpr
{
	public:
		bExpr_bExpr_CONCATENATION_bExpr(
			bExpr* pNewbExpr1,
			String* pNewCONCATENATION2,
			bExpr* pNewbExpr3
		)
			: bExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pCONCATENATION2(pNewCONCATENATION2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~bExpr_bExpr_CONCATENATION_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_bExpr_bExpr_CONCATENATION_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pCONCATENATION2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API cExpr: public node
{
	public:
		cExpr()
			{}
		virtual ~cExpr() {}
};
class OW_WQL_API cExpr_attr : public cExpr
{
	public:
		cExpr_attr(
			attr* pNewattr1
		)
			: cExpr()
			, m_pattr1(pNewattr1)
		{}
		virtual ~cExpr_attr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_attr( this );
		}
		attr* m_pattr1;
};
class OW_WQL_API cExpr_strColId_optIndirection : public cExpr
{
	public:
		cExpr_strColId_optIndirection(
			String* pNewstrColId1,
			optIndirection* pNewoptIndirection2
		)
			: cExpr()
			, m_pstrColId1(pNewstrColId1)
			, m_poptIndirection2(pNewoptIndirection2)
		{}
		virtual ~cExpr_strColId_optIndirection();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_strColId_optIndirection( this );
		}
		String* m_pstrColId1;
		optIndirection* m_poptIndirection2;
};
class OW_WQL_API cExpr_aExprConst : public cExpr
{
	public:
		cExpr_aExprConst(
			aExprConst* pNewaExprConst1
		)
			: cExpr()
			, m_paExprConst1(pNewaExprConst1)
		{}
		virtual ~cExpr_aExprConst();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_aExprConst( this );
		}
		aExprConst* m_paExprConst1;
};
class OW_WQL_API cExpr_LEFTPAREN_aExpr_RIGHTPAREN : public cExpr
{
	public:
		cExpr_LEFTPAREN_aExpr_RIGHTPAREN(
			String* pNewLEFTPAREN1,
			aExpr* pNewaExpr2,
			String* pNewRIGHTPAREN3
		)
			: cExpr()
			, m_pLEFTPAREN1(pNewLEFTPAREN1)
			, m_paExpr2(pNewaExpr2)
			, m_pRIGHTPAREN3(pNewRIGHTPAREN3)
		{}
		virtual ~cExpr_LEFTPAREN_aExpr_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_LEFTPAREN_aExpr_RIGHTPAREN( this );
		}
		String* m_pLEFTPAREN1;
		aExpr* m_paExpr2;
		String* m_pRIGHTPAREN3;
};
class OW_WQL_API cExpr_strFuncName_LEFTPAREN_RIGHTPAREN : public cExpr
{
	public:
		cExpr_strFuncName_LEFTPAREN_RIGHTPAREN(
			String* pNewstrFuncName1,
			String* pNewLEFTPAREN2,
			String* pNewRIGHTPAREN3
		)
			: cExpr()
			, m_pstrFuncName1(pNewstrFuncName1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pRIGHTPAREN3(pNewRIGHTPAREN3)
		{}
		virtual ~cExpr_strFuncName_LEFTPAREN_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_strFuncName_LEFTPAREN_RIGHTPAREN( this );
		}
		String* m_pstrFuncName1;
		String* m_pLEFTPAREN2;
		String* m_pRIGHTPAREN3;
};
class OW_WQL_API cExpr_strFuncName_LEFTPAREN_exprSeq_RIGHTPAREN : public cExpr
{
	public:
		cExpr_strFuncName_LEFTPAREN_exprSeq_RIGHTPAREN(
			String* pNewstrFuncName1,
			String* pNewLEFTPAREN2,
			exprSeq* pNewexprSeq3,
			String* pNewRIGHTPAREN4
		)
			: cExpr()
			, m_pstrFuncName1(pNewstrFuncName1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pexprSeq3(pNewexprSeq3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~cExpr_strFuncName_LEFTPAREN_exprSeq_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_strFuncName_LEFTPAREN_exprSeq_RIGHTPAREN( this );
		}
		String* m_pstrFuncName1;
		String* m_pLEFTPAREN2;
		exprSeq* m_pexprSeq3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API cExpr_strFuncName_LEFTPAREN_ALL_exprSeq_RIGHTPAREN : public cExpr
{
	public:
		cExpr_strFuncName_LEFTPAREN_ALL_exprSeq_RIGHTPAREN(
			String* pNewstrFuncName1,
			String* pNewLEFTPAREN2,
			String* pNewALL3,
			exprSeq* pNewexprSeq4,
			String* pNewRIGHTPAREN5
		)
			: cExpr()
			, m_pstrFuncName1(pNewstrFuncName1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pALL3(pNewALL3)
			, m_pexprSeq4(pNewexprSeq4)
			, m_pRIGHTPAREN5(pNewRIGHTPAREN5)
		{}
		virtual ~cExpr_strFuncName_LEFTPAREN_ALL_exprSeq_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_strFuncName_LEFTPAREN_ALL_exprSeq_RIGHTPAREN( this );
		}
		String* m_pstrFuncName1;
		String* m_pLEFTPAREN2;
		String* m_pALL3;
		exprSeq* m_pexprSeq4;
		String* m_pRIGHTPAREN5;
};
class OW_WQL_API cExpr_strFuncName_LEFTPAREN_DISTINCT_exprSeq_RIGHTPAREN : public cExpr
{
	public:
		cExpr_strFuncName_LEFTPAREN_DISTINCT_exprSeq_RIGHTPAREN(
			String* pNewstrFuncName1,
			String* pNewLEFTPAREN2,
			String* pNewDISTINCT3,
			exprSeq* pNewexprSeq4,
			String* pNewRIGHTPAREN5
		)
			: cExpr()
			, m_pstrFuncName1(pNewstrFuncName1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pDISTINCT3(pNewDISTINCT3)
			, m_pexprSeq4(pNewexprSeq4)
			, m_pRIGHTPAREN5(pNewRIGHTPAREN5)
		{}
		virtual ~cExpr_strFuncName_LEFTPAREN_DISTINCT_exprSeq_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_strFuncName_LEFTPAREN_DISTINCT_exprSeq_RIGHTPAREN( this );
		}
		String* m_pstrFuncName1;
		String* m_pLEFTPAREN2;
		String* m_pDISTINCT3;
		exprSeq* m_pexprSeq4;
		String* m_pRIGHTPAREN5;
};
class OW_WQL_API cExpr_strFuncName_LEFTPAREN_ASTERISK_RIGHTPAREN : public cExpr
{
	public:
		cExpr_strFuncName_LEFTPAREN_ASTERISK_RIGHTPAREN(
			String* pNewstrFuncName1,
			String* pNewLEFTPAREN2,
			String* pNewASTERISK3,
			String* pNewRIGHTPAREN4
		)
			: cExpr()
			, m_pstrFuncName1(pNewstrFuncName1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pASTERISK3(pNewASTERISK3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~cExpr_strFuncName_LEFTPAREN_ASTERISK_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_strFuncName_LEFTPAREN_ASTERISK_RIGHTPAREN( this );
		}
		String* m_pstrFuncName1;
		String* m_pLEFTPAREN2;
		String* m_pASTERISK3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API cExpr_CURRENTDATE : public cExpr
{
	public:
		cExpr_CURRENTDATE(
			String* pNewCURRENTDATE1
		)
			: cExpr()
			, m_pCURRENTDATE1(pNewCURRENTDATE1)
		{}
		virtual ~cExpr_CURRENTDATE();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_CURRENTDATE( this );
		}
		String* m_pCURRENTDATE1;
};
class OW_WQL_API cExpr_CURRENTTIME : public cExpr
{
	public:
		cExpr_CURRENTTIME(
			String* pNewCURRENTTIME1
		)
			: cExpr()
			, m_pCURRENTTIME1(pNewCURRENTTIME1)
		{}
		virtual ~cExpr_CURRENTTIME();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_CURRENTTIME( this );
		}
		String* m_pCURRENTTIME1;
};
class OW_WQL_API cExpr_CURRENTTIME_LEFTPAREN_ICONST_RIGHTPAREN : public cExpr
{
	public:
		cExpr_CURRENTTIME_LEFTPAREN_ICONST_RIGHTPAREN(
			String* pNewCURRENTTIME1,
			String* pNewLEFTPAREN2,
			String* pNewICONST3,
			String* pNewRIGHTPAREN4
		)
			: cExpr()
			, m_pCURRENTTIME1(pNewCURRENTTIME1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pICONST3(pNewICONST3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~cExpr_CURRENTTIME_LEFTPAREN_ICONST_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_CURRENTTIME_LEFTPAREN_ICONST_RIGHTPAREN( this );
		}
		String* m_pCURRENTTIME1;
		String* m_pLEFTPAREN2;
		String* m_pICONST3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API cExpr_CURRENTTIMESTAMP : public cExpr
{
	public:
		cExpr_CURRENTTIMESTAMP(
			String* pNewCURRENTTIMESTAMP1
		)
			: cExpr()
			, m_pCURRENTTIMESTAMP1(pNewCURRENTTIMESTAMP1)
		{}
		virtual ~cExpr_CURRENTTIMESTAMP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_CURRENTTIMESTAMP( this );
		}
		String* m_pCURRENTTIMESTAMP1;
};
class OW_WQL_API cExpr_CURRENTTIMESTAMP_LEFTPAREN_ICONST_RIGHTPAREN : public cExpr
{
	public:
		cExpr_CURRENTTIMESTAMP_LEFTPAREN_ICONST_RIGHTPAREN(
			String* pNewCURRENTTIMESTAMP1,
			String* pNewLEFTPAREN2,
			String* pNewICONST3,
			String* pNewRIGHTPAREN4
		)
			: cExpr()
			, m_pCURRENTTIMESTAMP1(pNewCURRENTTIMESTAMP1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pICONST3(pNewICONST3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~cExpr_CURRENTTIMESTAMP_LEFTPAREN_ICONST_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_CURRENTTIMESTAMP_LEFTPAREN_ICONST_RIGHTPAREN( this );
		}
		String* m_pCURRENTTIMESTAMP1;
		String* m_pLEFTPAREN2;
		String* m_pICONST3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API cExpr_CURRENTUSER : public cExpr
{
	public:
		cExpr_CURRENTUSER(
			String* pNewCURRENTUSER1
		)
			: cExpr()
			, m_pCURRENTUSER1(pNewCURRENTUSER1)
		{}
		virtual ~cExpr_CURRENTUSER();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_CURRENTUSER( this );
		}
		String* m_pCURRENTUSER1;
};
class OW_WQL_API cExpr_SESSIONUSER : public cExpr
{
	public:
		cExpr_SESSIONUSER(
			String* pNewSESSIONUSER1
		)
			: cExpr()
			, m_pSESSIONUSER1(pNewSESSIONUSER1)
		{}
		virtual ~cExpr_SESSIONUSER();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_SESSIONUSER( this );
		}
		String* m_pSESSIONUSER1;
};
class OW_WQL_API cExpr_USER : public cExpr
{
	public:
		cExpr_USER(
			String* pNewUSER1
		)
			: cExpr()
			, m_pUSER1(pNewUSER1)
		{}
		virtual ~cExpr_USER();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_USER( this );
		}
		String* m_pUSER1;
};
class OW_WQL_API cExpr_EXTRACT_LEFTPAREN_optExtract_RIGHTPAREN : public cExpr
{
	public:
		cExpr_EXTRACT_LEFTPAREN_optExtract_RIGHTPAREN(
			String* pNewEXTRACT1,
			String* pNewLEFTPAREN2,
			optExtract* pNewoptExtract3,
			String* pNewRIGHTPAREN4
		)
			: cExpr()
			, m_pEXTRACT1(pNewEXTRACT1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_poptExtract3(pNewoptExtract3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~cExpr_EXTRACT_LEFTPAREN_optExtract_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_EXTRACT_LEFTPAREN_optExtract_RIGHTPAREN( this );
		}
		String* m_pEXTRACT1;
		String* m_pLEFTPAREN2;
		optExtract* m_poptExtract3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API cExpr_POSITION_LEFTPAREN_positionExpr_RIGHTPAREN : public cExpr
{
	public:
		cExpr_POSITION_LEFTPAREN_positionExpr_RIGHTPAREN(
			String* pNewPOSITION1,
			String* pNewLEFTPAREN2,
			positionExpr* pNewpositionExpr3,
			String* pNewRIGHTPAREN4
		)
			: cExpr()
			, m_pPOSITION1(pNewPOSITION1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_ppositionExpr3(pNewpositionExpr3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~cExpr_POSITION_LEFTPAREN_positionExpr_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_POSITION_LEFTPAREN_positionExpr_RIGHTPAREN( this );
		}
		String* m_pPOSITION1;
		String* m_pLEFTPAREN2;
		positionExpr* m_ppositionExpr3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API cExpr_SUBSTRING_LEFTPAREN_optSubstrExpr_RIGHTPAREN : public cExpr
{
	public:
		cExpr_SUBSTRING_LEFTPAREN_optSubstrExpr_RIGHTPAREN(
			String* pNewSUBSTRING1,
			String* pNewLEFTPAREN2,
			optSubstrExpr* pNewoptSubstrExpr3,
			String* pNewRIGHTPAREN4
		)
			: cExpr()
			, m_pSUBSTRING1(pNewSUBSTRING1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_poptSubstrExpr3(pNewoptSubstrExpr3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~cExpr_SUBSTRING_LEFTPAREN_optSubstrExpr_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_SUBSTRING_LEFTPAREN_optSubstrExpr_RIGHTPAREN( this );
		}
		String* m_pSUBSTRING1;
		String* m_pLEFTPAREN2;
		optSubstrExpr* m_poptSubstrExpr3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API cExpr_TRIM_LEFTPAREN_LEADING_trimExpr_RIGHTPAREN : public cExpr
{
	public:
		cExpr_TRIM_LEFTPAREN_LEADING_trimExpr_RIGHTPAREN(
			String* pNewTRIM1,
			String* pNewLEFTPAREN2,
			String* pNewLEADING3,
			trimExpr* pNewtrimExpr4,
			String* pNewRIGHTPAREN5
		)
			: cExpr()
			, m_pTRIM1(pNewTRIM1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pLEADING3(pNewLEADING3)
			, m_ptrimExpr4(pNewtrimExpr4)
			, m_pRIGHTPAREN5(pNewRIGHTPAREN5)
		{}
		virtual ~cExpr_TRIM_LEFTPAREN_LEADING_trimExpr_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_TRIM_LEFTPAREN_LEADING_trimExpr_RIGHTPAREN( this );
		}
		String* m_pTRIM1;
		String* m_pLEFTPAREN2;
		String* m_pLEADING3;
		trimExpr* m_ptrimExpr4;
		String* m_pRIGHTPAREN5;
};
class OW_WQL_API cExpr_TRIM_LEFTPAREN_TRAILING_trimExpr_RIGHTPAREN : public cExpr
{
	public:
		cExpr_TRIM_LEFTPAREN_TRAILING_trimExpr_RIGHTPAREN(
			String* pNewTRIM1,
			String* pNewLEFTPAREN2,
			String* pNewTRAILING3,
			trimExpr* pNewtrimExpr4,
			String* pNewRIGHTPAREN5
		)
			: cExpr()
			, m_pTRIM1(pNewTRIM1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_pTRAILING3(pNewTRAILING3)
			, m_ptrimExpr4(pNewtrimExpr4)
			, m_pRIGHTPAREN5(pNewRIGHTPAREN5)
		{}
		virtual ~cExpr_TRIM_LEFTPAREN_TRAILING_trimExpr_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_TRIM_LEFTPAREN_TRAILING_trimExpr_RIGHTPAREN( this );
		}
		String* m_pTRIM1;
		String* m_pLEFTPAREN2;
		String* m_pTRAILING3;
		trimExpr* m_ptrimExpr4;
		String* m_pRIGHTPAREN5;
};
class OW_WQL_API cExpr_TRIM_LEFTPAREN_trimExpr_RIGHTPAREN : public cExpr
{
	public:
		cExpr_TRIM_LEFTPAREN_trimExpr_RIGHTPAREN(
			String* pNewTRIM1,
			String* pNewLEFTPAREN2,
			trimExpr* pNewtrimExpr3,
			String* pNewRIGHTPAREN4
		)
			: cExpr()
			, m_pTRIM1(pNewTRIM1)
			, m_pLEFTPAREN2(pNewLEFTPAREN2)
			, m_ptrimExpr3(pNewtrimExpr3)
			, m_pRIGHTPAREN4(pNewRIGHTPAREN4)
		{}
		virtual ~cExpr_TRIM_LEFTPAREN_trimExpr_RIGHTPAREN();
		void accept( WQLVisitor* v ) const
		{
			v->visit_cExpr_TRIM_LEFTPAREN_trimExpr_RIGHTPAREN( this );
		}
		String* m_pTRIM1;
		String* m_pLEFTPAREN2;
		trimExpr* m_ptrimExpr3;
		String* m_pRIGHTPAREN4;
};
class OW_WQL_API optIndirection: public node
{
	public:
		optIndirection()
			{}
		virtual ~optIndirection() {}
};
class OW_WQL_API optIndirection_empty : public optIndirection
{
	public:
		optIndirection_empty(
		)
			: optIndirection()
		{}
		virtual ~optIndirection_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optIndirection_empty( this );
		}
};
class OW_WQL_API optIndirection_optIndirection_LEFTBRACKET_aExpr_RIGHTBRACKET : public optIndirection
{
	public:
		optIndirection_optIndirection_LEFTBRACKET_aExpr_RIGHTBRACKET(
			optIndirection* pNewoptIndirection1,
			String* pNewLEFTBRACKET2,
			aExpr* pNewaExpr3,
			String* pNewRIGHTBRACKET4
		)
			: optIndirection()
			, m_poptIndirection1(pNewoptIndirection1)
			, m_pLEFTBRACKET2(pNewLEFTBRACKET2)
			, m_paExpr3(pNewaExpr3)
			, m_pRIGHTBRACKET4(pNewRIGHTBRACKET4)
		{}
		virtual ~optIndirection_optIndirection_LEFTBRACKET_aExpr_RIGHTBRACKET();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optIndirection_optIndirection_LEFTBRACKET_aExpr_RIGHTBRACKET( this );
		}
		optIndirection* m_poptIndirection1;
		String* m_pLEFTBRACKET2;
		aExpr* m_paExpr3;
		String* m_pRIGHTBRACKET4;
};
class OW_WQL_API optIndirection_optIndirection_LEFTBRACKET_aExpr_COLON_aExpr_RIGHTBRACKET : public optIndirection
{
	public:
		optIndirection_optIndirection_LEFTBRACKET_aExpr_COLON_aExpr_RIGHTBRACKET(
			optIndirection* pNewoptIndirection1,
			String* pNewLEFTBRACKET2,
			aExpr* pNewaExpr3,
			String* pNewCOLON4,
			aExpr* pNewaExpr5,
			String* pNewRIGHTBRACKET6
		)
			: optIndirection()
			, m_poptIndirection1(pNewoptIndirection1)
			, m_pLEFTBRACKET2(pNewLEFTBRACKET2)
			, m_paExpr3(pNewaExpr3)
			, m_pCOLON4(pNewCOLON4)
			, m_paExpr5(pNewaExpr5)
			, m_pRIGHTBRACKET6(pNewRIGHTBRACKET6)
		{}
		virtual ~optIndirection_optIndirection_LEFTBRACKET_aExpr_COLON_aExpr_RIGHTBRACKET();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optIndirection_optIndirection_LEFTBRACKET_aExpr_COLON_aExpr_RIGHTBRACKET( this );
		}
		optIndirection* m_poptIndirection1;
		String* m_pLEFTBRACKET2;
		aExpr* m_paExpr3;
		String* m_pCOLON4;
		aExpr* m_paExpr5;
		String* m_pRIGHTBRACKET6;
};
class OW_WQL_API optExtract: public node
{
	public:
		optExtract()
			{}
		virtual ~optExtract() {}
};
class OW_WQL_API optExtract_empty : public optExtract
{
	public:
		optExtract_empty(
		)
			: optExtract()
		{}
		virtual ~optExtract_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optExtract_empty( this );
		}
};
class OW_WQL_API optExtract_strExtractArg_FROM_aExpr : public optExtract
{
	public:
		optExtract_strExtractArg_FROM_aExpr(
			String* pNewstrExtractArg1,
			String* pNewFROM2,
			aExpr* pNewaExpr3
		)
			: optExtract()
			, m_pstrExtractArg1(pNewstrExtractArg1)
			, m_pFROM2(pNewFROM2)
			, m_paExpr3(pNewaExpr3)
		{}
		virtual ~optExtract_strExtractArg_FROM_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optExtract_strExtractArg_FROM_aExpr( this );
		}
		String* m_pstrExtractArg1;
		String* m_pFROM2;
		aExpr* m_paExpr3;
};
class OW_WQL_API positionExpr: public node
{
	public:
		positionExpr()
			{}
		virtual ~positionExpr() {}
};
class OW_WQL_API positionExpr_bExpr_IN_bExpr : public positionExpr
{
	public:
		positionExpr_bExpr_IN_bExpr(
			bExpr* pNewbExpr1,
			String* pNewIN2,
			bExpr* pNewbExpr3
		)
			: positionExpr()
			, m_pbExpr1(pNewbExpr1)
			, m_pIN2(pNewIN2)
			, m_pbExpr3(pNewbExpr3)
		{}
		virtual ~positionExpr_bExpr_IN_bExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_positionExpr_bExpr_IN_bExpr( this );
		}
		bExpr* m_pbExpr1;
		String* m_pIN2;
		bExpr* m_pbExpr3;
};
class OW_WQL_API positionExpr_empty : public positionExpr
{
	public:
		positionExpr_empty(
		)
			: positionExpr()
		{}
		virtual ~positionExpr_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_positionExpr_empty( this );
		}
};
class OW_WQL_API optSubstrExpr: public node
{
	public:
		optSubstrExpr()
			{}
		virtual ~optSubstrExpr() {}
};
class OW_WQL_API optSubstrExpr_empty : public optSubstrExpr
{
	public:
		optSubstrExpr_empty(
		)
			: optSubstrExpr()
		{}
		virtual ~optSubstrExpr_empty();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSubstrExpr_empty( this );
		}
};
class OW_WQL_API optSubstrExpr_aExpr_substrFrom_substrFor : public optSubstrExpr
{
	public:
		optSubstrExpr_aExpr_substrFrom_substrFor(
			aExpr* pNewaExpr1,
			substrFrom* pNewsubstrFrom2,
			substrFor* pNewsubstrFor3
		)
			: optSubstrExpr()
			, m_paExpr1(pNewaExpr1)
			, m_psubstrFrom2(pNewsubstrFrom2)
			, m_psubstrFor3(pNewsubstrFor3)
		{}
		virtual ~optSubstrExpr_aExpr_substrFrom_substrFor();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSubstrExpr_aExpr_substrFrom_substrFor( this );
		}
		aExpr* m_paExpr1;
		substrFrom* m_psubstrFrom2;
		substrFor* m_psubstrFor3;
};
class OW_WQL_API optSubstrExpr_aExpr_substrFor_substrFrom : public optSubstrExpr
{
	public:
		optSubstrExpr_aExpr_substrFor_substrFrom(
			aExpr* pNewaExpr1,
			substrFor* pNewsubstrFor2,
			substrFrom* pNewsubstrFrom3
		)
			: optSubstrExpr()
			, m_paExpr1(pNewaExpr1)
			, m_psubstrFor2(pNewsubstrFor2)
			, m_psubstrFrom3(pNewsubstrFrom3)
		{}
		virtual ~optSubstrExpr_aExpr_substrFor_substrFrom();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSubstrExpr_aExpr_substrFor_substrFrom( this );
		}
		aExpr* m_paExpr1;
		substrFor* m_psubstrFor2;
		substrFrom* m_psubstrFrom3;
};
class OW_WQL_API optSubstrExpr_aExpr_substrFrom : public optSubstrExpr
{
	public:
		optSubstrExpr_aExpr_substrFrom(
			aExpr* pNewaExpr1,
			substrFrom* pNewsubstrFrom2
		)
			: optSubstrExpr()
			, m_paExpr1(pNewaExpr1)
			, m_psubstrFrom2(pNewsubstrFrom2)
		{}
		virtual ~optSubstrExpr_aExpr_substrFrom();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSubstrExpr_aExpr_substrFrom( this );
		}
		aExpr* m_paExpr1;
		substrFrom* m_psubstrFrom2;
};
class OW_WQL_API optSubstrExpr_aExpr_substrFor : public optSubstrExpr
{
	public:
		optSubstrExpr_aExpr_substrFor(
			aExpr* pNewaExpr1,
			substrFor* pNewsubstrFor2
		)
			: optSubstrExpr()
			, m_paExpr1(pNewaExpr1)
			, m_psubstrFor2(pNewsubstrFor2)
		{}
		virtual ~optSubstrExpr_aExpr_substrFor();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSubstrExpr_aExpr_substrFor( this );
		}
		aExpr* m_paExpr1;
		substrFor* m_psubstrFor2;
};
class OW_WQL_API optSubstrExpr_exprSeq : public optSubstrExpr
{
	public:
		optSubstrExpr_exprSeq(
			exprSeq* pNewexprSeq1
		)
			: optSubstrExpr()
			, m_pexprSeq1(pNewexprSeq1)
		{}
		virtual ~optSubstrExpr_exprSeq();
		void accept( WQLVisitor* v ) const
		{
			v->visit_optSubstrExpr_exprSeq( this );
		}
		exprSeq* m_pexprSeq1;
};
class OW_WQL_API substrFrom : public node
{
	public:
		substrFrom(
			String* pNewFROM1,
			aExpr* pNewaExpr2
		)
			: m_pFROM1(pNewFROM1)
			, m_paExpr2(pNewaExpr2)
		{}
		virtual ~substrFrom();
		void accept( WQLVisitor* v ) const
		{
			v->visit_substrFrom( this );
		}
		String* m_pFROM1;
		aExpr* m_paExpr2;
};
class OW_WQL_API substrFor : public node
{
	public:
		substrFor(
			String* pNewFOR1,
			aExpr* pNewaExpr2
		)
			: m_pFOR1(pNewFOR1)
			, m_paExpr2(pNewaExpr2)
		{}
		virtual ~substrFor();
		void accept( WQLVisitor* v ) const
		{
			v->visit_substrFor( this );
		}
		String* m_pFOR1;
		aExpr* m_paExpr2;
};
class OW_WQL_API trimExpr: public node
{
	public:
		trimExpr()
			{}
		virtual ~trimExpr() {}
};
class OW_WQL_API trimExpr_aExpr_FROM_exprSeq : public trimExpr
{
	public:
		trimExpr_aExpr_FROM_exprSeq(
			aExpr* pNewaExpr1,
			String* pNewFROM2,
			exprSeq* pNewexprSeq3
		)
			: trimExpr()
			, m_paExpr1(pNewaExpr1)
			, m_pFROM2(pNewFROM2)
			, m_pexprSeq3(pNewexprSeq3)
		{}
		virtual ~trimExpr_aExpr_FROM_exprSeq();
		void accept( WQLVisitor* v ) const
		{
			v->visit_trimExpr_aExpr_FROM_exprSeq( this );
		}
		aExpr* m_paExpr1;
		String* m_pFROM2;
		exprSeq* m_pexprSeq3;
};
class OW_WQL_API trimExpr_FROM_exprSeq : public trimExpr
{
	public:
		trimExpr_FROM_exprSeq(
			String* pNewFROM1,
			exprSeq* pNewexprSeq2
		)
			: trimExpr()
			, m_pFROM1(pNewFROM1)
			, m_pexprSeq2(pNewexprSeq2)
		{}
		virtual ~trimExpr_FROM_exprSeq();
		void accept( WQLVisitor* v ) const
		{
			v->visit_trimExpr_FROM_exprSeq( this );
		}
		String* m_pFROM1;
		exprSeq* m_pexprSeq2;
};
class OW_WQL_API trimExpr_exprSeq : public trimExpr
{
	public:
		trimExpr_exprSeq(
			exprSeq* pNewexprSeq1
		)
			: trimExpr()
			, m_pexprSeq1(pNewexprSeq1)
		{}
		virtual ~trimExpr_exprSeq();
		void accept( WQLVisitor* v ) const
		{
			v->visit_trimExpr_exprSeq( this );
		}
		exprSeq* m_pexprSeq1;
};
class OW_WQL_API attr : public node
{
	public:
		attr(
			String* pNewstrRelationName1,
			String* pNewPERIOD2,
			attrs* pNewattrs3,
			optIndirection* pNewoptIndirection4
		)
			: m_pstrRelationName1(pNewstrRelationName1)
			, m_pPERIOD2(pNewPERIOD2)
			, m_pattrs3(pNewattrs3)
			, m_poptIndirection4(pNewoptIndirection4)
		{}
		virtual ~attr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_attr( this );
		}
		String* m_pstrRelationName1;
		String* m_pPERIOD2;
		attrs* m_pattrs3;
		optIndirection* m_poptIndirection4;
};
class OW_WQL_API attrs: public node
{
	public:
		attrs()
			{}
		virtual ~attrs() {}
};
class OW_WQL_API attrs_strAttrName : public attrs
{
	public:
		attrs_strAttrName(
			String* pNewstrAttrName1
		)
			: attrs()
			, m_pstrAttrName1(pNewstrAttrName1)
		{}
		virtual ~attrs_strAttrName();
		void accept( WQLVisitor* v ) const
		{
			v->visit_attrs_strAttrName( this );
		}
		String* m_pstrAttrName1;
};
class OW_WQL_API attrs_attrs_PERIOD_strAttrName : public attrs
{
	public:
		attrs_attrs_PERIOD_strAttrName(
			attrs* pNewattrs1,
			String* pNewPERIOD2,
			String* pNewstrAttrName3
		)
			: attrs()
			, m_pattrs1(pNewattrs1)
			, m_pPERIOD2(pNewPERIOD2)
			, m_pstrAttrName3(pNewstrAttrName3)
		{}
		virtual ~attrs_attrs_PERIOD_strAttrName();
		void accept( WQLVisitor* v ) const
		{
			v->visit_attrs_attrs_PERIOD_strAttrName( this );
		}
		attrs* m_pattrs1;
		String* m_pPERIOD2;
		String* m_pstrAttrName3;
};
class OW_WQL_API attrs_attrs_PERIOD_ASTERISK : public attrs
{
	public:
		attrs_attrs_PERIOD_ASTERISK(
			attrs* pNewattrs1,
			String* pNewPERIOD2,
			String* pNewASTERISK3
		)
			: attrs()
			, m_pattrs1(pNewattrs1)
			, m_pPERIOD2(pNewPERIOD2)
			, m_pASTERISK3(pNewASTERISK3)
		{}
		virtual ~attrs_attrs_PERIOD_ASTERISK();
		void accept( WQLVisitor* v ) const
		{
			v->visit_attrs_attrs_PERIOD_ASTERISK( this );
		}
		attrs* m_pattrs1;
		String* m_pPERIOD2;
		String* m_pASTERISK3;
};
class OW_WQL_API targetEl: public node
{
	public:
		targetEl()
			{}
		virtual ~targetEl() {}
};
class OW_WQL_API targetEl_aExpr_AS_strColLabel : public targetEl
{
	public:
		targetEl_aExpr_AS_strColLabel(
			aExpr* pNewaExpr1,
			String* pNewAS2,
			String* pNewstrColLabel3
		)
			: targetEl()
			, m_paExpr1(pNewaExpr1)
			, m_pAS2(pNewAS2)
			, m_pstrColLabel3(pNewstrColLabel3)
		{}
		virtual ~targetEl_aExpr_AS_strColLabel();
		void accept( WQLVisitor* v ) const
		{
			v->visit_targetEl_aExpr_AS_strColLabel( this );
		}
		aExpr* m_paExpr1;
		String* m_pAS2;
		String* m_pstrColLabel3;
};
class OW_WQL_API targetEl_aExpr : public targetEl
{
	public:
		targetEl_aExpr(
			aExpr* pNewaExpr1
		)
			: targetEl()
			, m_paExpr1(pNewaExpr1)
		{}
		virtual ~targetEl_aExpr();
		void accept( WQLVisitor* v ) const
		{
			v->visit_targetEl_aExpr( this );
		}
		aExpr* m_paExpr1;
};
class OW_WQL_API targetEl_strRelationName_PERIOD_ASTERISK : public targetEl
{
	public:
		targetEl_strRelationName_PERIOD_ASTERISK(
			String* pNewstrRelationName1,
			String* pNewPERIOD2,
			String* pNewASTERISK3
		)
			: targetEl()
			, m_pstrRelationName1(pNewstrRelationName1)
			, m_pPERIOD2(pNewPERIOD2)
			, m_pASTERISK3(pNewASTERISK3)
		{}
		virtual ~targetEl_strRelationName_PERIOD_ASTERISK();
		void accept( WQLVisitor* v ) const
		{
			v->visit_targetEl_strRelationName_PERIOD_ASTERISK( this );
		}
		String* m_pstrRelationName1;
		String* m_pPERIOD2;
		String* m_pASTERISK3;
};
class OW_WQL_API targetEl_ASTERISK : public targetEl
{
	public:
		targetEl_ASTERISK(
			String* pNewASTERISK1
		)
			: targetEl()
			, m_pASTERISK1(pNewASTERISK1)
		{}
		virtual ~targetEl_ASTERISK();
		void accept( WQLVisitor* v ) const
		{
			v->visit_targetEl_ASTERISK( this );
		}
		String* m_pASTERISK1;
};
class OW_WQL_API updateTargetEl : public node
{
	public:
		updateTargetEl(
			String* pNewstrColId1,
			optIndirection* pNewoptIndirection2,
			String* pNewEQUALS3,
			aExpr* pNewaExpr4
		)
			: m_pstrColId1(pNewstrColId1)
			, m_poptIndirection2(pNewoptIndirection2)
			, m_pEQUALS3(pNewEQUALS3)
			, m_paExpr4(pNewaExpr4)
		{}
		virtual ~updateTargetEl();
		void accept( WQLVisitor* v ) const
		{
			v->visit_updateTargetEl( this );
		}
		String* m_pstrColId1;
		optIndirection* m_poptIndirection2;
		String* m_pEQUALS3;
		aExpr* m_paExpr4;
};
class OW_WQL_API aExprConst: public node
{
	public:
		aExprConst()
			{}
		virtual ~aExprConst() {}
};
class OW_WQL_API aExprConst_ICONST : public aExprConst
{
	public:
		aExprConst_ICONST(
			String* pNewICONST1
		)
			: aExprConst()
			, m_pICONST1(pNewICONST1)
		{}
		virtual ~aExprConst_ICONST();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExprConst_ICONST( this );
		}
		String* m_pICONST1;
};
class OW_WQL_API aExprConst_FCONST : public aExprConst
{
	public:
		aExprConst_FCONST(
			String* pNewFCONST1
		)
			: aExprConst()
			, m_pFCONST1(pNewFCONST1)
		{}
		virtual ~aExprConst_FCONST();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExprConst_FCONST( this );
		}
		String* m_pFCONST1;
};
class OW_WQL_API aExprConst_SCONST : public aExprConst
{
	public:
		aExprConst_SCONST(
			String* pNewSCONST1
		)
			: aExprConst()
			, m_pSCONST1(pNewSCONST1)
		{}
		virtual ~aExprConst_SCONST();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExprConst_SCONST( this );
		}
		String* m_pSCONST1;
};
class OW_WQL_API aExprConst_BITCONST : public aExprConst
{
	public:
		aExprConst_BITCONST(
			String* pNewBITCONST1
		)
			: aExprConst()
			, m_pBITCONST1(pNewBITCONST1)
		{}
		virtual ~aExprConst_BITCONST();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExprConst_BITCONST( this );
		}
		String* m_pBITCONST1;
};
class OW_WQL_API aExprConst_HEXCONST : public aExprConst
{
	public:
		aExprConst_HEXCONST(
			String* pNewHEXCONST1
		)
			: aExprConst()
			, m_pHEXCONST1(pNewHEXCONST1)
		{}
		virtual ~aExprConst_HEXCONST();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExprConst_HEXCONST( this );
		}
		String* m_pHEXCONST1;
};
class OW_WQL_API aExprConst_TRUEP : public aExprConst
{
	public:
		aExprConst_TRUEP(
			String* pNewTRUEP1
		)
			: aExprConst()
			, m_pTRUEP1(pNewTRUEP1)
		{}
		virtual ~aExprConst_TRUEP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExprConst_TRUEP( this );
		}
		String* m_pTRUEP1;
};
class OW_WQL_API aExprConst_FALSEP : public aExprConst
{
	public:
		aExprConst_FALSEP(
			String* pNewFALSEP1
		)
			: aExprConst()
			, m_pFALSEP1(pNewFALSEP1)
		{}
		virtual ~aExprConst_FALSEP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExprConst_FALSEP( this );
		}
		String* m_pFALSEP1;
};
class OW_WQL_API aExprConst_NULLP : public aExprConst
{
	public:
		aExprConst_NULLP(
			String* pNewNULLP1
		)
			: aExprConst()
			, m_pNULLP1(pNewNULLP1)
		{}
		virtual ~aExprConst_NULLP();
		void accept( WQLVisitor* v ) const
		{
			v->visit_aExprConst_NULLP( this );
		}
		String* m_pNULLP1;
};

} // end namespace OW_NAMESPACE

#endif
