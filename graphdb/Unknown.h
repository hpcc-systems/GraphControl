/*******************************************************************************
 * Copyright (C) 2011 HPCC Systems.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/
#pragma once

#ifdef WIN32
#  ifdef STATIC_LIB
#    define GRAPHDB_API
#  elif defined GRAPHDB_EXPORTS
#    define GRAPHDB_API __declspec(dllexport)
#  else
#    define GRAPHDB_API __declspec(dllimport)
#  endif
#else
#	if __GNUC__ >= 4
#		define GRAPHDB_API __attribute__ ((visibility("default")))
#	else
#		define GRAPHDB_API
#	endif
#endif

#ifdef _MSC_VER
#ifndef interface
#define interface    struct __declspec(novtable)
#endif
#else
#ifndef interface
#define interface    struct
#endif
#endif

namespace ln
{
interface GRAPHDB_API IUnknown
{
	virtual unsigned long AddRef() = 0;
	virtual unsigned long Release() = 0;
};

class GRAPHDB_API CUnknown
{
private:
	boost::detail::atomic_count m_refCount;

public:
	CUnknown();
    CUnknown(const CUnknown & other);
    CUnknown & operator=(const CUnknown & other);
	virtual ~CUnknown();

	virtual unsigned long AddRef() throw();
	virtual unsigned long Release() throw();
};

#define BEGIN_CUNKNOWN 	virtual unsigned long AddRef() throw() { return CUnknown::AddRef(); } \
						virtual unsigned long Release() throw() { return CUnknown::Release(); } \
						template<typename T> T * QueryInterface() const { return const_cast<T *>(dynamic_cast<const T *>(this)); }
#define END_CUNKNOWN

inline void Link(IUnknown * ptr)		{ if (ptr) ptr->AddRef(); }
inline void Release(IUnknown * ptr)		{ if (ptr) ptr->Release(); }

template <typename T> inline void Link(T * ptr)	{ if (ptr) ptr->AddRef(); }
template <typename T> inline void Release(T * ptr) { if (ptr) ptr->Release(); }

template <typename T>
class CUnknownPtr
{
public:
	CUnknownPtr()
	{
		m_T = 0;
	}
	CUnknownPtr(T * c)
	{
		ln::Link(c);
		m_T = c;
	}
	CUnknownPtr(const CUnknownPtr<T>& c)
	{
		ln::Link(&*c);
		m_T = &*c;
	}
	~CUnknownPtr()
	{
		ln::Release(m_T);
	}
	inline CUnknownPtr<T>& operator = (const CUnknownPtr<T>& c)
	{
		ln::Link(&*c);
		ln::Release(m_T);
		m_T = &*c;
		return *this;
	}
	inline T *Detach()
	{
		T * temp = m_T;
		m_T = 0;
		return temp;

	}
	inline void Attach( const CUnknownPtr<T>& c)
	{
		if ( m_T != &*c )
		{
			ln::Release(m_T);
			m_T = &*c;
		}
	}
	inline bool operator ==(const CUnknownPtr<T>& c) const
	{
		return m_T == c.m_T;
	}
	inline T& operator *() const
	{
		return *m_T;
	}
	inline operator T*() const
	{
		return m_T;
	}
	inline T* operator ->() const
	{
		return m_T;
	}
	inline T* get() const
	{
		return m_T;
	}
	inline bool isLinked() const
	{
		return m_T != 0;
	}
	inline bool operator < (const CUnknownPtr<T>& other) const
	{
		return m_T < other.m_T;
	}

protected:
	T * m_T;
};
typedef CUnknownPtr<CUnknown> CUnknownPointer;

typedef CUnknownPtr<IUnknown> IUnknownPtr;
}


