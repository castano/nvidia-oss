// This code is in the public domain -- castano@gmail.com

#ifndef NV_MUTEX_H
#define NV_MUTEX_H

#include <nvthreads/nvthreads.h>

#include <nvcore/Ptr.h>

namespace nv
{

	class NVTHREADS_CLASS Mutex
	{
		NV_FORBID_COPY(Mutex);
	public:
		Mutex ();
		~Mutex ();

		void lock();
		bool tryLock();
		void unlock();

	private:
		struct Private;
		AutoPtr<Private> m;
	};

	
	class Lock
	{
		NV_FORBID_COPY(Lock);
	public:
		Lock (Mutex & m) : m_mutex (m)
		{
			m_mutex.lock();
		}

		~Lock ()
		{
			m_mutex.unlock();
		}
		
	private:
		Mutex & m_mutex;
	};

} // nv namespace

#endif // NV_MUTEX_H
