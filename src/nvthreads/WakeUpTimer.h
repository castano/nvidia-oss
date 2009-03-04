// This code is in the public domain -- castano@gmail.com

#ifndef NV_THREADS_WAKEUPTIMER_H
#define NV_THREADS_WAKEUPTIMER_H

#include <nvthreads/nvthreads.h>

namespace nv
{

	class NVTHREADS_CLASS WakeUpTimer
	{
		NV_FORBID_COPY(WakeUpTimer);
	public:
		WakeUpTimer();
		~WakeUpTimer();

		void wait();

	private:
		struct Private;
		AutoPtr<Private> m;
	};

} // nv namespace

#endif // NV_THREADS_WAKEUPTIMER_H
