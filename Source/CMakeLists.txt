cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(SOURCES 
	${CMAKE_CURRENT_LIST_DIR}/ZigInternal.h
)

if(WIN32)
	set(SOURCES ${SOURCES} 
		"${CMAKE_CURRENT_LIST_DIR}/ZigWin.c"
	)
endif()

target_sources(Ziggurat PUBLIC ${SOURCES})