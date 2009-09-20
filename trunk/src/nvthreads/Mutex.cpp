// This code is in the public domain -- castano@gmail.com

#include <nvthreads/Mutex.h>

#if NV_OS_WIN32
	#define WIN32_LEAN_AND_MEAN
	#define VC_EXTRALEAN
	#define _WIN32_WINNT 0x0400 // for TryEnterCriticalSection
	#include <windows.h>
#elif NV_OS_UNIX
	#include <pthread.h>
	#include <errno.h> // EBUSY
#endif

using namespace nv;

struct Mutex::Private
{
#if NV_OS_WIN32
	CRITICAL_SECTION mutex;
#elif NV_OS_UNIX
	pthread_mutex_t mutex;
#endif	
};


Mutex::Mutex () : m(new Private)
{
#if NV_OS_WIN32
	InitializeCriticalSection(&m->mutex);
#elif NV_OS_UNIX
	int result = pthread_mutex_init(&m->mutex , NULL);
	nvDebugCheck(result == 0);
#endif	
}

Mutex::~Mutex ()
{
#if NV_OS_WIN32
	DeleteCriticalSection(&m->mutex);
#elif NV_OS_UNIX
	int result = pthread_mutex_destroy(&m->mutex);
	nvDebugCheck(result == 0);
#endif	
}

void Mutex::lock()
{
#if NV_OS_WIN32
	EnterCriticalSection(&m->mutex);
#elif NV_OS_UNIX
	int result = pthread_mutex_lock(&m->mutex);
	nvDebugCheck(result == 0);
#endif
}

bool Mutex::tryLock()
{
#if NV_OS_WIN32
	return TryEnterCriticalSection(&m->mutex) != 0;
#elif NV_OS_UNIX
	int result = pthread_mutex_trylock(&m->mutex);
	nvDebugCheck(result == 0 || result == EBUSY);
	return result == 0;
#endif
}

void Mutex::unlock()
{
#if NV_OS_WIN32
	LeaveCriticalSection(&m->mutex);	
#elif NV_OS_UNIX
	int result = pthread_mutex_unlock(&m->mutex);
	nvDebugCheck(result == 0);
#endif
}
