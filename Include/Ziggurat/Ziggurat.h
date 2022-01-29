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
#error Ziggurat or project using Ziggurat has not been built with exactly one window system specified
#endif

// Include the VkClay Vulkan wrapper
#include "VkClay/VkClay.h"

/**
 * @brief Gets the name of the instance extension targetted by this build of zig, useful for when creating
 * your Vulkan instance
 * @returns "VK_KHR_*surface name*_surface"
 */
const char* zig_GetVulkanSurfaceEXTName();

/**
 * @brief Creates the vulkan surface for the user
 * @param instance The Vulkan instance handle used to create the physical device
 * @param pSurface Pointer to the Vukan Surface to be created
 * @returns Ziggurat success code
 */
zigenum zig_CreateVulkanSurface(VkSurfaceKHR* pSurface, VkInstance instance);

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

#endif  // !__ZIGGURAT_MAIN_HEADER_H__
