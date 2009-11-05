// This code is in the public domain -- castano@gmail.com

#ifndef NV_CORE_FILEMONITOR_H
#define NV_CORE_FILEMONITOR_H

#include <nvcore/nvcore.h>

namespace nv
{

	class FileMonitor
	{
		NV_FORBID_COPY(FileMonitor);
	public:
		
		FileMonitor(const char * path, bool recursive);
		~FileMonitor();
	
		typedef void (* Notifier)(const char * name);
		
		void setNotifier(Notifier notifer);
		
	private:
		struct Private;
		Private & m;
	};

} // nv namespace


#endif // NV_CORE_FILEMONITOR_H
