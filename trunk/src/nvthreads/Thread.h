// This code is in the public domain -- castano@gmail.com

#ifndef NV_THREAD_H
#define NV_THREAD_H

#include <nvthreads/nvthreads.h>

#include <nvcore/Ptr.h>

namespace nv
{

	class NVTHREADS_CLASS Thread
	{
		NV_FORBID_COPY(Thread);
	public:
		Thread();
		virtual ~Thread();

		void start();
		void wait();

		bool isRunning() const;

		//static int threadId();
	
		static void spinWait(uint count);
		static void yield();
		static void sleep(uint ms);
	
	protected:
		
#if NV_OS_WIN32
		static unsigned int __stdcall threadLoop(Thread *);
#else
		static void threadLoop(Thread *);
#endif

		virtual void run() = 0;
	
	private:
		struct Private;
		AutoPtr<Private> m;
	};

} // nv namespace

#endif // NV_THREAD_H
