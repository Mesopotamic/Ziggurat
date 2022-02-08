#include <xcb/xcb.h>
#include "ZigInternal.h"

zigenum platformZigInit()
{
    // We need to initialise a connection to XServer via xcb
    xcb_connection_t *connection = xcb_connect(NULL, NULL);
    if(connection == NULL)
    {
        return zig_unknownfail;
    }
    return zig_success;
}

zigenum platformProcess()
{
    return zig_success;
}

zigenum platformCreateSurface(VkSurfaceKHR* pSurface, VkInstance instance)
{
    return zig_success;
}
