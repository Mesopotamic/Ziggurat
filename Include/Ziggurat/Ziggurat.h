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
/**
 * Common Ziggurat functions used on every platform
 */

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
