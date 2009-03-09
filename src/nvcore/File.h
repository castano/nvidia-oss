// This code is in the public domain -- castano@gmail.com

#ifndef NV_CORE_FILE_H
#define NV_CORE_FILE_H

#include <nvcore/Debug.h>

#if NV_OS_LINUX
#define _GNU_SOURCE // *_unlocked
#endif
#include <stdio.h>

namespace nv
{
	enum OpenMode
	{
		OpenMode_NotOpen = 0,
		OpenMode_Read,
		OpenMode_Write,
		OpenMode_Append,
	};
	
	/// File class.
	class NVIO_CLASS File
	{
	public:
		
		File();
		~File();
		
		bool open(OpenMode mode);
		void close();

		uint read(void * data, uint len);
		uint write(void * data, uint len);

		/// Move to the given position in the archive.
		void seek(uint pos);

		/// Return the current position in the archive.
		uint tell() const;

		/// Return the current size of the archive.
		uint size() const;

		/// Determine if there has been any error.
		bool isError() const;

		/// Clear errors.
		void clearError();

		/// Return true if the stream is at the end.
		bool isAtEnd() const;

		
	protected:

		FILE * m_fp;
	
	};

	
	File::File() : m_fp(NULL)
	{
	}

	File::~File()
	{
		close();
	}
	
	bool File::open(const char * filePath, OpenMode mode)
	{
		nvCheck(filePath != NULL);
		nvCheck(mode != OpenMode_NotOpen);

		close();
		
		const char * modeString = NULL;
		if (mode == OpenMode_Read) modeString = "rb";
		if (mode == OpenMode_Write) modeString = "wb";
		if (mode == OpenMode_Append) modeString = "ab";

		#if NV_CC_MSVC && _MSVC_VER >= 1400
		fopen_s(&m_fp, filePath, modeString);
		#else
		m_fp = fopen(filePath, modeString);
		#endif
		
		if (m_fp == NULL)
		{
			return false;
		}
		
		return true; 
	}

	void File::close()
	{
		if (m_fp != NULL)
		{
			fclose(fp);
		}
	}

	OpenMode File::openMode() const
	{
		return m_openMode;
	}

	void File::seek( uint pos )
	{
		nvDebugCheck(m_fp != NULL);
		nvDebugCheck(pos < size());
		
		fseek(m_fp, pos, SEEK_SET);
	}

	uint File::tell() const
	{
		nvDebugCheck(m_fp != NULL);
		
		return ftell(m_fp);
	}

	uint File::size() const
	{
		nvDebugCheck(m_fp != NULL);
		uint pos = ftell(m_fp);
		fseek(m_fp, 0, SEEK_END);
		uint end = ftell(m_fp);
		fseek(m_fp, pos, SEEK_SET);
		return end;
	}

	bool File::isError() const
	{
	#if NV_OS_LINUX
		return /*m_fp == NULL ||*/ ferror_unlocked(m_fp) != 0;
	#else
		return /*m_fp == NULL ||*/ ferror(m_fp) != 0;
	#endif
	}

	void File::clearError()
	{
		nvDebugCheck(m_fp != NULL);
		clearerr(m_fp);
	}

	bool File::isAtEnd() const
	{
		nvDebugCheck(m_fp != NULL);
		return feof(m_fp) != 0;
	}

	
	FileError File::error() const
	{
		return m_error;
	}
	
	void File::clearError()
	{
		m_error = FileError_NoError;
	}

	uint File::read(void * data, uint len)
	{
		nvDebugCheck(data != NULL);
		nvDebugCheck(m_fp != NULL);

	#if NV_OS_LINUX
		return (uint)fread_unlocked(data, 1, len, m_fp);
	#else
		return (uint)fread(data, 1, len, m_fp);
	#endif
	}
	
	uint File::write(void * data, uint len)
	{
		nvDebugCheck(data != NULL);
		nvDebugCheck(m_fp != NULL);

	#if NV_OS_LINUX
		return (uint)fwrite_unlocked(data, 1, len, m_fp);		
	#else
		return (uint)fwrite(data, 1, len, m_fp);		
	#endif
	}	
	
} // nv namespace

#endif // NV_IO_FILE_H
