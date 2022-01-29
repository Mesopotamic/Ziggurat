/**
 * Ziggurat enums, usually used for success codes from a Ziggurat
 */
#ifndef __ZIGGURAT_ENUMS_HEADER_H__
#define __ZIGGURAT_ENUMS_HEADER_H__

typedef enum zigenum {
    zig_success = 0,       // Successful event
    zig_unknownfail,       // The command failed, but I haven't made an enum yet
    zig_alreadyinit,       // User tried to initialise Ziggurat, but it was already active
    zig_nullpointer,       // User passed a null pointer in the wrong place
    zig_windownotinit,     // Window hasn't been opened for the first time yet
    zig_windowopen,        // Window is currently open
    zig_windowminimised,   // Window is currently minimised
    zig_windowminimising,  // Window on first frame of minimising
    zig_windowclosed,      // Window is exited, cycle completed
    zig_windowclosing,     // Window on first frame of closing
} zigenum;

#endif  // !__ZIGGURAT_ENUMS_HEADER_H__
