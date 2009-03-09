// This code is in the public domain -- castano@gmail.com

#include "SpinWaiter.h"
#include "Thread.h"

using namespace nv;

void SpinWaiter::backoff()
{
	if (m_count++ > 32)
	{
		Thread::sleep(0);
	} 
	else if (m_count > 12) 
	{
		Thread::yield();
	} 
	else 
	{
		Thread::spinWait(2 << m_count);
	}
}


