/**
 * Ziggurat's common main source, since ziggurat is very platform dependant we'll mainly just be providing
 * definitions to extern declarations
 */
#include "ZigInternal.h"

bool zigInit = false;

zigenum windowStatus = zig_windownotinit;

uint32_t windowWidth = 0;
uint32_t windowHeight = 0;

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
}

zigenum zig_WindowStatus() { return windowStatus; }

bool zig_WindowLoopContinues()
{
    return !((windowStatus == zig_windowclosed) || (windowStatus == zig_windowclosing));
}