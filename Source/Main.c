/**
 * Ziggurat's common main source, since ziggurat is very platform dependant we'll mainly just be providing
 * definitions to extern declarations
 */
#include "ZigInternal.h"

bool zigInit = false;

zigenum windowStatus = zig_windownotinit;

uint32_t windowWidth = 0;
uint32_t windowHeight = 0;

const char* zig_GetVulkanSurfaceEXTName()
{
#ifdef VK_USE_PLATFORM_WIN32_KHR
    return "VK_KHR_win32_surface";
#elif defined VK_USE_PLATFORM_ANDROID_KHR
    return "VK_KHR_android_surface";
#elif defined VK_USE_PLATFORM_METAL_EXT
    return "VK_EXT_metal_surface";
#elif defined VK_USE_PLATFORM_XCB_KHR
    return "VK_KHR_xcb_surface";
#elif defined VK_USE_PLATFORM_WAYLAND_KHR
    return "VK_KHR_wayland_surface"
#else
    return NULL;
#endif
}

zigenum zig_CreateVulkanSurface(VkSurfaceKHR* pSurface, VkInstance instance)
{
    // Null pointer check the surface
    if (pSurface == NULL) {
        return zig_nullpointer;
    }
    zigenum res = platformCreateSurface(pSurface, instance);
    return res;
}

zigenum zig_ShowWindow(uint32_t width, uint32_t height)
{
    // ensure we haven't already initialised
    if (zigInit) return zig_alreadyinit;
    zigInit = true;

    windowWidth = width;
    windowHeight = height;

    // Calls into the platform specific
    zigenum res = platformZigInit();

    // Fail out early if platform specific fails
    if (res != zig_success) return res;

    // Set that the window is open
    windowStatus = zig_windowopen;
    return zig_success;
}

zigenum zig_WindowStatus() { return windowStatus; }

bool zig_WindowLoopContinues()
{
    return !((windowStatus == zig_windowclosed) || (windowStatus == zig_windowclosing));
}

zigenum zig_ProcessEvents()
{
    // Do platform specific message handling
    zigenum res = platformProcess();
    return res;
}
