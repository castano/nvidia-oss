// This code is in the public domain -- castano@gmail.com

#include "ThreadLocalStorage.h"

// NV_TLS_DECLARE(Context, context);
//
// context = new Context();
// if (nv::tlsIsValid(context)) context->member();
//
// nv::tlsFree(context);

#if 0

NV_TLS_DECLARE(int, test);

void test()
{
	test = new int();
	if (nv::tlsIsValid(test)) *test = 0;
	nv::tlsFree(test);
}

#endif