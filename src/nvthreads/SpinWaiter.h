// This code is in the public domain -- castano@gmail.com

#ifndef NV_THREADS_SPINWAITER_H
#define NV_THREADS_SPINWAITER_H

#include <nvthreads/nvthreads.h>

namespace nv
{
	// Spin wait helper class.
	struct SpinWaiter
	{
		SpinWaiter() : m_count(0) {}
		
		void backoff();
		
	private:
		int m_count;
	};
	
} // nv namespace

#endif // NV_THREADS_THREADUTIL_H
