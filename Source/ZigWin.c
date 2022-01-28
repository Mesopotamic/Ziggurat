/**
 * Ziggurat's window specific functions
 */
#include "ZigInternal.h"

HINSTANCE zigHInstance = NULL;
HWND zigHWindow = NULL;

// Forward declare the window call back function
LRESULT CALLBACK WindowProcCallback(HWND windowHandle, UINT uMsg, WPARAM wParam, LPARAM lParam);

zigenum platformZigInit()
{
    if (!zigInit) {
        // Somehow this has been called without the wrapper
        return zig_unknownfail;
    }

    // First get the instance handle of the application we're linked to
    zigHInstance = GetModuleHandle(NULL);
    if (zigHInstance == NULL) return zig_unknownfail;

    // We need a name to register the window class within the windows api
    const wchar_t ZIG_WINDOW_CLASS_NAME[] = L"Ziggurat Window Class";

    WNDCLASS wc;
    memset(&wc, 0, sizeof(WNDCLASS));
    wc.lpszClassName = ZIG_WINDOW_CLASS_NAME;
    wc.hInstance = zigHInstance;
    wc.lpfnWndProc = WindowProcCallback;

    // Register this window class inside the windows API
    RegisterClass(&wc);

    // Lets extract the class info from the registered class
    WNDCLASSEXA info = {0};
    GetClassInfoEx(zigHInstance, ZIG_WINDOW_CLASS_NAME, &info);

    // Create the window
    HWND zigHWindow = CreateWindowEx(0,                      // Optional window styles
                                     ZIG_WINDOW_CLASS_NAME,  // Window Class Name
                                     "Ziggurat Window",      // Window title
                                     WS_OVERLAPPEDWINDOW,    // Window Style
                                     CW_USEDEFAULT,          // Pos x
                                     CW_USEDEFAULT,          // Pos y,
                                     windowWidth,            // Window width
                                     windowHeight,           // Window height
                                     NULL,                   // Parent window
                                     NULL,                   // Wmenu
                                     zigHInstance,           // Instance handle
                                     NULL                    // Extra data
    );

    // Check if the window handle has been created correctly
    if (!zigHWindow) return zig_unknownfail;

    // Tell windows API we want to show the window
    ShowWindow(zigHWindow, 1);
    return zig_success;
}

zigenum platformProcess()
{
    MSG msg = {0};

    // Want to loop through all the messages until windows requests a close
    while (msg.message != WM_QUIT) {
        // Check the next message
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            // The message was a regular one, so dispatch it to the window proc callback
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // Peek message was false, so we have completed all the messages for this frame
            break;
        }
    }

    return zig_success;
}

LRESULT CALLBACK WindowProcCallback(HWND windowHandle, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // We need to process all the messages sent to us by the windows API
    switch (uMsg) {
        /*
         * Window destruction requested
         */
        case WM_DESTROY:
            // Tell zig that the window is closed
            windowStatus = zig_windowclosed;
            PostQuitMessage(0);
            return 0;
        /*
         * Request a frame for the window
         */
        case WM_PAINT: {
            // braces needed to make a local namespace so we can have variables
            PAINTSTRUCT ps;
            memset(&ps, 0, sizeof(PAINTSTRUCT));

            HDC hdc = BeginPaint(windowHandle, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(windowHandle, &ps);
            return 0;
        }
        /*
         * Default case use the regular windows one
         */
        default:
            return DefWindowProc(windowHandle, uMsg, wParam, lParam);
            break;
    }
}
