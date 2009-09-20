// This code is in the public domain -- castano@gmail.com

#include "Thread.h"

#if NV_OS_WIN32
	#define WIN32_LEAN_AND_MEAN
	#define VC_EXTRALEAN
	#define _WIN32_WINNT 0x0400 // For SwitchToThread()
	#include <windows.h>
	#include <process.h> // _beginthreadex
#elif NV_OS_UNIX
	#include <pthread.h>
	#include <unistd.h> // usleep
#endif

using namespace nv;

struct Thread::Private
{
#if NV_OS_WIN32
	HANDLE thread;
#elif NV_OS_UNIX
	pthread_t thread;
#endif
};

#if NV_OS_WIN32
/*static void __cdecl runThread(void * arg)
{
	Thread * thread = ((Thread *)arg);
	thread->run();
	thread->m->thread = NULL;
}*/
typedef unsigned int (__stdcall * Start) (void *);
#elif NV_OS_UNIX
extern "C"
{
	typedef void * (* Start) (void *);
}
#endif


Thread::Thread()
{
#if NV_OS_WIN32
#elif NV_OS_UNIX
#endif
}

Thread::~Thread()
{
	wait();
	nvDebugCheck(m->thread == 0);
}

void Thread::start()
{
	if (m->thread == 0) // @@ Is this a race condition?
	{
	#if NV_OS_WIN32
		//m->thread = CreateThread(NULL, 0, 
		//m->thread = _beginthread(runThread, 0, NULL);
		
		uint id;
		m->thread = (HANDLE)_beginthreadex (0, 0, Start(threadLoop), this, 0, &id);
		nvDebugCheck(m->thread != NULL);
	#elif NV_OS_UNIX
		int result = pthread_create(&m->thread, NULL, Start(threadLoop), this);
		nvDebugCheck(result == 0);
	#endif
	}
}

void Thread::wait()
{
#if NV_OS_WIN32
    DWORD status = WaitForSingleObject (m->thread, INFINITE);
    nvCheck (status ==  WAIT_OBJECT_0);
    BOOL ok = CloseHandle (m->thread);
    nvCheck (ok);
#elif NV_OS_UNIX
	int result = pthread_join(m->thread, NULL); 
	nvDebugCheck(result == 0);
#endif
}

bool Thread::isRunning () const
{
#if NV_OS_WIN32
	return m->thread != NULL;
#elif NV_OS_UNIX
	return m->thread != 0;
#endif
}

/*static*/ void Thread::spinWait(uint count)
{
	for (uint i = 0; i < count; i++) {}
}

/*static*/ void Thread::yield()
{
#if NV_OS_WIN32
	SwitchToThread();
#elif NV_OS_UNIX
	int result = sched_yield();
	nvDebugCheck(result == 0);
#endif
}

/*static*/ void Thread::sleep(uint ms)
{
#if NV_OS_WIN32
	Sleep(ms);
#elif NV_OS_UNIX
	usleep(1000 * ms);
#endif
}

#if NV_OS_WIN32

/*static*/ unsigned int Thread::threadLoop(Thread * thread)
{
	thread->run();
	
	// Reset thread handle.
	thread->m->thread = NULL;

	return 0;
}

#elif NV_OS_UNIX

/*static*/ void Thread::threadLoop(Thread * thread)
{
	thread->run();
	
	// Reset thread handle.
	thread->m->thread = 0;
	pthread_exit(0);
}

#endif