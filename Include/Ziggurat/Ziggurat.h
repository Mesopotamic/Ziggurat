/**
 * Welcome to the header for Ziggurat
 * The (Hopefully) crossplatform windowing system for Vulkan
 *
 * The idea here is that Mesopatamian Ziggurats are multiple raised platforms, ie cross platform!
 */
#ifndef __ZIGGURAT_MAIN_HEADER_H__
#define __ZIGGURAT_MAIN_HEADER_H__
#include <stdbool.h>
#include <stdint.h>
#include "ZigguratEnums.h"

/*************************************************************************************************************
 * We have to ensure that the windowing system for Ziggurat was specified
 * This controls for which windowing system Ziggurat will be built for
 * But it also defines the required Vulkan surface extension define,
 * as such, you have to place this include above your Vulkan headers
 * This is kind of messy, sorry!*/
#ifdef WIN32
#define ZIG_WINDOWING_SYSTEM_WIN32 (1)
#define VK_USE_PLATFORM_WIN32_KHR (1)
#elif defined __ANDROID__
#define ZIG_WINDOWING_SYSTEM_ANDROID (1)
#define VK_USE_PLATFORM_ANDROID_KHR (1)
#elif defined __APPLE__
#define ZIG_WINDOWING_SYSTEM_MOLTEN (1)
#define VK_USE_PLATFORM_METAL_EXT(1)
#elif defined __linux__
// Linux is special as it can have multiple windowing systems
// mainly either X or Wayland
// In this sitation we can't make the devision automatically
// So we need the user to pass one of these when compiling :
// either ZIG_WINDOWING_SYSTEM_X or XIG_WINDOWING_SYSTEM_WAYLAND
#if defined ZIG_WINDOWING_SYSTEM_X && defined ZIG_WINDOWING_SYSTEM_WAYLAND
#error You must define only one of ZIG_WINDOWING_SYSTEM_X or ZIG_WINDOWING_SYSTEM_WAYLAND. Not both
#elif not defined ZIG_WINDOWING_SYSTEM_X && not defined ZIG_WINDOWING_SYSTEM_WAYLAND
#error You must define either ZIG_WINDOWING_SYSTEM_X or ZIG_WINDOWING_SYSTEM_WAYLAND.

// Now that we've ensured exactly one linux windowing system was selected
// we can define the corresponding Vulkan define
#ifdef ZIG_WINDOWING_SYSTEM_X
#define VK_USE_PLATFORM_XCB_KHR
#elif defined ZIG_WINDOWING_SYSTEM_WAYLAND
#define VK_USE_PLATFORM_WAYLAND_KHR
#endif

#endif  // ifdef__linux__

// We got to the end of windowing system selection, and failed. So you're compiling for a werid target
#else
#error Ziggurat windowing system has not been set. Look in Ziggurat.h to ensure one has been defined
#endif
/*************************************************************************************************************/

/**
 * Common Ziggurat functions used on every platform
 */

/**
* @brief Gets the name of the instance extension targetted by this build of zig
* @returns "VK_KHR_*surface name*_surface"
*/
const char* zig_GetVulkanSurfaceEXTName();

/**
 * @brief Creates and shows the Ziggurat window
 * @param width Width of the window
 * @param height Height of the window
 * @returns Ziggurat success code
 */
zigenum zig_ShowWindow(uint32_t width, uint32_t height);

zigenum zig_ProcessEvents();

zigenum zig_WindowStatus();

bool zig_WindowLoopContinues();

/**
 * Windows specific declarations
 */
#ifdef WIN32
#include <Windows.h>

// We need to supply the windows instance window handles so that the vkWin32SurfaceCreateInfoKHR structure can
// be filled by the user

/**
 * @brief When targetting windows this function fetches the instance handle
 * @returns Instance Handle of current application
 */
HINSTANCE zig_GetHInstance();

/**
 * @brief When targetting windows, this function fetches the window handle
 * @returns Handle for the currently open Zig window
 */
HWND zig_GetHWindow();

#endif  // WIN32

#endif  // !__ZIGGURAT_MAIN_HEADER_H__
