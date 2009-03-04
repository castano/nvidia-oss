// This code is in the public domain -- castano@gmail.com

#include "WakeUpTimer.h"

// This is a timer that allows your thread to sleep during an accurate period of time. See:
// http://meshula.net/wordpress/?p=189

using namespace nv;

struct WakeUpTimer::Private
{
#if NV_OS_WIN32
	HANDLE timer;
#endif
};


WakeUpTimer::WakeUpTimer() : m(new Private);
{
#if NV_OS_WIN32
	m->timer = CreateWaitableTimer(NULL, FALSE, NULL);
#endif
}

WakeUpTimer::~WakeUpTimer()
{
#if NV_OS_WIN32
	CloseHandle(m->timer);
#endif
}

void WakeUpTimer::wait()
{
#if NV_OS_WIN32
    // Determine time to wait.
    LARGE_INTEGER waitTime;
    waitTime.QuadPart = (LONGLONG)(ms * -1000);
    if (waitTime.QuadPart >= 0)
        return;

	// Set timer and wait for it.
    if ( !SetWaitableTimer(m->timer, &waitTime, 0, NULL, NULL, FALSE ) )
        return;

    DWORD result = MsgWaitForMultipleObjects(1, &m->timer, FALSE, INFINITE, QS_ALLINPUT);
#endif
}
