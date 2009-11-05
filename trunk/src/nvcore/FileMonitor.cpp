// This code is in the public domain -- castano@gmail.com

#include "FileMonitor.h"

#if NV_OS_WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
//#include <shlwapi.h> // PathFileExists
#include <windows.h> // GetFileAttributes
#include <direct.h> // _mkdir
#endif

using namespace nv;

#pragma message(NV_FILE_LINE "TODO: Implement file monitor"

// http://mtlung.blogspot.com/2009/01/blog-post.html

/*
mDirectory = CreateFile(path,  
	FILE_LIST_DIRECTORY,  
	FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,  
	0,  
	OPEN_EXISTING,  
	// ReadDirectoryChangesW() needs FILE_FLAG_BACKUP_SEMANTICS  
	FILE_FLAG_OVERLAPPED | FILE_FLAG_BACKUP_SEMANTICS,  
	0);
*/

// ReadDirectoryChanges
// GetOverlappedResult
