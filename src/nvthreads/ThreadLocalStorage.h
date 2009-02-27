// This code is in the public domain -- castano@gmail.com

#ifndef NV_THREADLOCALSTORAGE_H
#define NV_THREADLOCALSTORAGE_H

#include <nvthreads/nvthreads.h>

// NV_TLS_DECLARE(Context, context);
//
// context = new Context();
// if (nv::tlsIsValid(context)) context->member();
//
// nv::tlsFree(context);

#if NV_CC_MSVC
// Declarations so that we don't have to include windows.h
extern "C" {
	__stdcall unsigned long TlsAlloc();
	__stdcall void TlsFree(unsigned long idx);
	__stdcall void TlsSetValue(unsigned long idx, void * ptr);
	__stdcall void * TlsGetValue(unsigned long idx);
}
#endif

namespace nv
{

#if NV_CC_GNUC

	#define NV_TLS_DECLARE(Class, Var) \
		__thread Class * Var = NULL

	template <typename T>
	bool tlsIsValid(T * var) 
	{
		return var != NULL;
	}
	
	template <typename T>
	void tlsFree(T * & var) 
	{
		delete var; 
		var = NULL;
	}
	
#elif NV_CC_MSVC 

	// The WinXP dynamic linker does not support implicit TLS declaration. It's
	// supported on Vista, though. See:
	// http://www.nynaeve.net/?p=186
	// http://www.nynaeve.net/?p=187
	// http://www.nynaeve.net/?p=188 

	#define NV_TLS_DECLARE(Class, Var) \
		nv::ThreadLocal<Class> Var

	template <class T>
	class ThreadLocal
	{
	public:
		ThreadLocal() : m_index(0) {}
		~ThreadLocal() { nvCheck(m_index == 0); }

		void allocate()
		{
			if (m_index == 0)
			{
				m_index = TlsAlloc();
			}
		}
		void free()
		{
			delete ptr();
			TlsFree(m_index);
			m_index = 0;
		}

		bool isValid() const
		{
			return m_index != 0;
		}

		void operator=( T * p )
		{
			allocate();

			T * current = ptr();
			if (p != current)
			{
				delete current;
				setPtr(p);
			}
		}

		T * operator -> () const
		{
			return ptr();
		}

		T & operator*() const
		{
			return *ptr();
		}

	private:

		T * ptr() const {
			return static_cast<T *>(TlsGetValue(m_index));
		}

		void setPtr(T * p)
		{
			TlsSetValue(m_index, p);
		}

		uint m_index;
	};

	template <typename T>
	bool tlsIsValid(const ThreadLocal<T> & var) 
	{
		return var.isValid();
	}
	
	template <typename T>
	void tlsFree(ThreadLocal<T> & var) 
	{
		var.free();
	}

#endif // NV_CC_MSVC

} // nv namespace

#endif // NV_THREADLOCALSTORAGE_H
