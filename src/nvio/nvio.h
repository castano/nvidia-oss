// This code is in the public domain -- castano@gmaill.com

#ifndef NV_THREADS_H
#define NV_THREADS_H

#include <nvcore/nvcore.h>
#include <nvcore/Debug.h>

// Function linkage
#if NVIO_SHARED
#ifdef NVIO_EXPORTS
#define NVIO_API DLL_EXPORT
#define NVIO_CLASS DLL_EXPORT_CLASS
#else
#define NVIO_API DLL_IMPORT
#define NVIO_CLASS DLL_IMPORT
#endif
#else // NVIO_SHARED
#define NVIO_API
#define NVIO_CLASS
#endif // NVIO_SHARED

#endif // NV_THREADS_H
