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
* We have to ensure that Ziggurat has been compiled with a windowing system in mind
* This is usually automatically decided based on the Operating system, asside from Linux
* We can check this via adding all of the VK_USE_PLATFORM_*_KHR variables
* since they are defined to one, so their sum must be exactly equal to one
/*************************************************************************************************************/
#if ((VK_USE_PLATFORM_WIN32_KHR + VK_USE_PLATFORM_ANDROID_KHR + VK_USE_PLATFORM_METAL_EXT + \
      VK_USE_PLATFORM_XCB_KHR + VK_USE_PLATFORM_WAYLAND_KHR) != 1)
#error Ziggurat has not been built with exactly one window system in mind
#endif

// Include the VkClay Vulkan wrapper
#include "VkClay/VkClay.h"
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

/**
 * @brief Processes all of the events that happend this frame, must be called once per frame
 */
zigenum zig_ProcessEvents();

/**
 * @brief Gets the current status of the window
 */
zigenum zig_WindowStatus();

/**
 * @brief Asks Zig if the windowing loop should continue
 * @returns true if the loop should continue
 */
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
