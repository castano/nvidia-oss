// This code is in the public domain -- castanyo@yahoo.es

#ifndef NV_THREADS_H
#define NV_THREADS_H

#include <nvcore/nvcore.h>
#include <nvcore/Debug.h>

// Function linkage
#if NVTHREADS_SHARED
#ifdef NVTHREADS_EXPORTS
#define NVTHREADS_API DLL_EXPORT
#define NVTHREADS_CLASS DLL_EXPORT_CLASS
#else
#define NVTHREADS_API DLL_IMPORT
#define NVTHREADS_CLASS DLL_IMPORT
#endif
#else // NVMATH_SHARED
#define NVTHREADS_API
#define NVTHREADS_CLASS
#endif // NVMATH_SHARED

namespace nv
{
	
	void initThreads();
	
} // nv namespace

#endif // NV_THREADS_H
