#include <xcb/xcb.h>
#include "ZigInternal.h"

// Connection to the XCB server
xcb_connection_t *connection = NULL;
// Pointer to the current screen (No idea, maybe?)
xcb_screen_t *screen = NULL;
// Current window handle
xcb_window_t window;
// Server cookie for the window?
xcb_void_cookie_t cookie;

zigenum platformZigInit()
{
    // Connect to the X Server
    // We set NULL as the display name, so the contents of the DISPLAY environment variable will be used
    // In this case we usually want $DISPLAY=:0
    // But we leave that to the user
    connection = xcb_connect(NULL, NULL);

    // The above won't return null on a failure, instead we have to use the following
    int err = xcb_connection_has_error(connection);
    if (err) {
        return zig_unknownfail;
    }

    // From the xserver connection we want to get the current screen.
    // The current screen is extracted from the "Root" window
    screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

    // From the connection, generate an ID used as a handle for the window
    // we're about to create
    window = xcb_generate_id(connection);

    // Since X uses a server moddle, individual windows can be registered to a cookie
    uint32_t values[2] = {screen->white_pixel, XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS};
    cookie = xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 0, 0, 640, 480, 0,
                               XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
                               XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK, values);

    // Now show the window
    xcb_map_window(connection, window);
    xcb_flush(connection);

    return zig_success;
}

zigenum platformProcess() { return zig_success; }

zigenum platformCreateSurface(VkSurfaceKHR *pSurface, VkInstance instance) { return zig_success; }
