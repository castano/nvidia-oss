PROJECT(nvcore)

SET(CORE_SRCS
	nvcore.h
	DefsGnucDarwin.h
	DefsGnucLinux.h
	DefsGnucWin32.h
	DefsVcWin32.h
	Ptr.h
	RefCounted.h
	RefCounted.cpp
	BitArray.h
	Memory.h
	Memory.cpp
	Debug.h
	Debug.cpp
	Containers.h
	StrLib.h
	StrLib.cpp
	Radix.h
	Radix.cpp
	CpuInfo.h
	CpuInfo.cpp
	Algorithms.h
	Timer.h
	Library.h
	Library.cpp
	Stream.h
	StdStream.h
	TextReader.h
	TextReader.cpp
	TextWriter.h
	TextWriter.cpp
	Tokenizer.h
	Tokenizer.cpp
	FileSystem.h
	FileSystem.cpp
	Array2D.h
	Array2D.cpp)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

IF(MSVC)
	SET(CORE_SRCS ${CORE_SRCS} scanf.c)
ENDIF(MSVC)

# targets
ADD_DEFINITIONS(-DNVCORE_EXPORTS)

IF(UNIX)
	SET(LIBS ${LIBS} ${CMAKE_DL_LIBS})
ENDIF(UNIX)

IF(NVCORE_SHARED)
	ADD_LIBRARY(nvcore SHARED ${CORE_SRCS})
ELSE(NVCORE_SHARED)
	ADD_LIBRARY(nvcore ${CORE_SRCS})
ENDIF(NVCORE_SHARED)

TARGET_LINK_LIBRARIES(nvcore ${LIBS})

INSTALL(TARGETS nvcore
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static)
