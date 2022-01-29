cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Ziggurat VERSION 0.1.0 LANGUAGES C)

# Prevent Ziggurat from being added multiple times
if(TARGET Ziggurat)
	return()
endif()

######################################################################################
# We need to define the windowing system ziggurat, and as a result
# which Vulkan surface instance extension is being used as well
# This is handled automatically for most systems asside from linux
function(Ziggurat_AddTargetDefinitions ARG_TARGET)
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows" OR ${CMAKE_SYSTEM_NAME} STREQUAL "CYGWIN"
        OR ${CMAKE_SYSTEM_NAME} STREQUAL "MSYS")
        target_compile_definitions(${ARG_TARGET} PRIVATE VK_USE_PLATFORM_WIN32_KHR=1)
        target_compile_definitions(${ARG_TARGET} PRIVATE ZIG_WINDOWING_SYSTEM=Win32)
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
        target_compile_definitions(${ARG_TARGET} PRIVATE VK_USE_PLATFORM_ANDROID_KHR=1)
        target_compile_definitions(${ARG_TARGET} PRIVATE ZIG_WINDOWING_SYSTEM=Android)
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "iOS" OR ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        target_compile_definitions(${ARG_TARGET} PRIVATE VK_USE_PLATFORM_METAL_EXT=1)
        target_compile_definitions(${ARG_TARGET} PRIVATE ZIG_WINDOWING_SYSTEM=Molten)
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        # Linux Requires you to specify the windowing system to X or Wayland
        # You do this with -DZIG_WINDOW_SYSTEM="X/Wayland"
        if(NOT DEFINED ZIG_WINDOW_SYSTEM)
            message(FATAL_ERROR "Linux platforms need window system specified by -DZIG_WINDOW_SYSTEM=\"X/Wayland\"")
        endif()

        # Make sure that the correct windowing system name is specified
        if(${ZIG_WINDOW_SYSTEM} STREQUAL "X")
            target_compile_definitions(${ARG_TARGET} PRIVATE VK_USE_PLATFORM_XCB_KHR=1)
            target_compile_definitions(${ARG_TARGET} PRIVATE ZIG_WINDOWING_SYSTEM=XCB)
        elseif(${ZIG_WINDOW_SYSTEM} STREQUAL "Wayland")
            target_compile_definitions(${ARG_TARGET} PRIVATE VK_USE_PLATFORM_WAYLAND_KHR=1)
            target_compile_definitions(${ARG_TARGET} PRIVATE ZIG_WINDOWING_SYSTEM=Wayland)
        else()
            message(FATAL_ERROR "-DZIG_WINDOW_SYSTEM must be only X or Wayland")
        endif()
    else()
        message(FATAL_ERROR "Ziggurat being build for unknown platform!")
    endif()
endfunction()
# End of windowing system selection
#######################################################################################

# Add Ziggurat to the include directories
include_directories(${CMAKE_CURRENT_LIST_DIR}/Include)
include_directories(${VkClay_INCLUDE_DIRS})
set(Ziggurat_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/Include ${VkClay_INCLUDE_DIRS}  CACHE PATH INTERNAL)

# Create the library target, we need to parse at least one C file so that
# CMake can determine linker language, as a result we'll use Zig's main function
add_library(Ziggurat Source/Main.c)

# Add the compile definitions for Ziggurat and VkClay
Ziggurat_AddTargetDefinitions(Ziggurat)
Ziggurat_AddTargetDefinitions(VkClay)

# Track the include directories for Ziggurat 
target_sources(Ziggurat PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Include/Ziggurat/Ziggurat.h
    ${CMAKE_CURRENT_LIST_DIR}/Include/Ziggurat/ZigguratEnums.h)

# Go into the source directory to add the rest of the sources
add_subdirectory(Source)

# Now we need to add VkClay as a subproject to Ziggurat
# We assume the user will be pulling Mesopatamic as a whole by default
# However if not, they can define the path to VkClay using -DVK_CLAY_ROOT=
if(NOT DEFINED VK_CLAY_ROOT)
    set(VK_CLAY_ROOT "../VkClay")
endif()
add_subdirectory(${VK_CLAY_ROOT} VkClay)

# Link to VkClay
target_link_libraries(Ziggurat PUBLIC VkClay)

######################################################################################

# Organise all source files, this is done last
# Get all of the source files added to the project
get_target_property(PROJ_SOURCES Ziggurat SOURCES)

# Add a little function that sorts all of the files to be
# Yoinked from https://stackoverflow.com/a/31423421
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

assign_source_group(${PROJ_SOURCES})