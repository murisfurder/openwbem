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

//
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

/**
 * @author Peter Dimov
 * @author Dan Nuffer
 */


#ifndef OW_INTRUSIVE_REFERENCE_HPP_INCLUDE_GUARD_
#define OW_INTRUSIVE_REFERENCE_HPP_INCLUDE_GUARD_

#include "OW_config.h"

namespace OW_NAMESPACE
{

//
//  IntrusiveReference
//
//  A smart pointer that uses intrusive reference counting.
//
//  Relies on unqualified calls to
//  
//      void IntrusiveReferenceAddRef(T * p);
//      void IntrusiveReferenceRelease(T * p);
//
//          (p != 0)
//
//  The object is responsible for destroying itself.
//


template<class T> class IntrusiveReference
{
private:
	typedef IntrusiveReference this_type;
public:
	typedef T element_type;

	IntrusiveReference(): m_pObj(0)
	{
	}
	IntrusiveReference(T * p, bool add_ref = true): m_pObj(p)
	{
		if (m_pObj != 0 && add_ref) IntrusiveReferenceAddRef(m_pObj);
	}
	template<class U> IntrusiveReference(IntrusiveReference<U> const & rhs): m_pObj(rhs.getPtr())
	{
		if (m_pObj != 0) IntrusiveReferenceAddRef(m_pObj);
	}
	IntrusiveReference(IntrusiveReference const & rhs): m_pObj(rhs.m_pObj)
	{
		if (m_pObj != 0) IntrusiveReferenceAddRef(m_pObj);
	}
	~IntrusiveReference()
	{
		if (m_pObj != 0) IntrusiveReferenceRelease(m_pObj);
	}
	template<class U> IntrusiveReference & operator=(IntrusiveReference<U> const & rhs)
	{
		this_type(rhs).swap(*this);
		return *this;
	}
	IntrusiveReference & operator=(IntrusiveReference const & rhs)
	{
		this_type(rhs).swap(*this);
		return *this;
	}
	IntrusiveReference & operator=(T * rhs)
	{
		this_type(rhs).swap(*this);
		return *this;
	}
	T * getPtr() const
	{
		return m_pObj;
	}
	T & operator*() const
	{
		return *m_pObj;
	}
	T * operator->() const
	{
		return m_pObj;
	}
	typedef T * this_type::*safe_bool;
	operator safe_bool() const
	{
		return m_pObj == 0? 0: &this_type::m_pObj;
	}
	bool operator! () const
	{
		return m_pObj == 0;
	}
	OW_DEPRECATED bool isNull() const // in 3.1.0
	{
	    return m_pObj == 0;
	}

	void swap(IntrusiveReference & rhs)
	{
		T * tmp = m_pObj;
		m_pObj = rhs.m_pObj;
		rhs.m_pObj = tmp;
	}

	template <class U>
	IntrusiveReference<U> cast_to() const
	{
		return IntrusiveReference<U>(dynamic_cast<U*>(m_pObj));
	}

private:
	T * m_pObj;
};
template<class T, class U> inline bool operator==(IntrusiveReference<T> const & a, IntrusiveReference<U> const & b)
{
	return a.getPtr() == b.getPtr();
}
template<class T, class U> inline bool operator!=(IntrusiveReference<T> const & a, IntrusiveReference<U> const & b)
{
	return a.getPtr() != b.getPtr();
}
template<class T> inline bool operator==(IntrusiveReference<T> const & a, T * b)
{
	return a.getPtr() == b;
}
template<class T> inline bool operator!=(IntrusiveReference<T> const & a, T * b)
{
	return a.getPtr() != b;
}
template<class T> inline bool operator==(T * a, IntrusiveReference<T> const & b)
{
	return a == b.getPtr();
}
template<class T> inline bool operator!=(T * a, IntrusiveReference<T> const & b)
{
	return a != b.getPtr();
}
#if __GNUC__ == 2 && __GNUC_MINOR__ <= 96
// Resolve the ambiguity between our op!= and the one in rel_ops
template<class T> inline bool operator!=(IntrusiveReference<T> const & a, IntrusiveReference<T> const & b)
{
	return a.getPtr() != b.getPtr();
}
#endif
template<class T> inline bool operator<(IntrusiveReference<T> const & a, IntrusiveReference<T> const & b)
{
	return a.getPtr() < b.getPtr();
}
template<class T> void swap(IntrusiveReference<T> & lhs, IntrusiveReference<T> & rhs)
{
	lhs.swap(rhs);
}
template<class T, class U> IntrusiveReference<T> static_pointer_cast(IntrusiveReference<U> const & p)
{
	return static_cast<T *>(p.getPtr());
}
template<class T, class U> IntrusiveReference<T> const_pointer_cast(IntrusiveReference<U> const & p)
{
	return const_cast<T *>(p.getPtr());
}
template<class T, class U> IntrusiveReference<T> dynamic_pointer_cast(IntrusiveReference<U> const & p)
{
	return dynamic_cast<T *>(p.getPtr());
}

} // end namespace OW_NAMESPACE

#endif
