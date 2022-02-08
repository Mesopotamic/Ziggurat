cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(SOURCES 
	${CMAKE_CURRENT_LIST_DIR}/ZigInternal.h
)

if(WIN32)
	set(SOURCES ${SOURCES} 
		"${CMAKE_CURRENT_LIST_DIR}/ZigWin.c")

elseif(UNIX)
	# On unix in order for this to work, we know the user must have 
	# passed a zig windowing system variable at command line.
	# As such we know it is in the cmake cache
	if(${ZIG_WINDOW_SYSTEM} STREQUAL "X")
		# User is targetting X
		set(SOURCES ${SOURCES} 
			"${CMAKE_CURRENT_LIST_DIR}/ZigXCB.c")
			
	else()
		# Probably using wayland
	endif()
endif()

target_sources(Ziggurat PRIVATE ${SOURCES})