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
	
	protected:
		
		static void threadLoop(Thread *);

		virtual void run() = 0;

		static void yield();
		static void sleep(uint ms);
	
	private:
		struct Private;
		AutoPtr<Private> m;
	};

} // nv namespace

#endif // NV_THREAD_H
