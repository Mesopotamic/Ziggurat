/**
 * Internal ziggurat header, used to share stuff more easily between zig files that the user doesn't need
 * direct access too
 */
#ifndef __ZIGGURATE_INTERNAL_MAIN_HEADER_H__
#define __ZIGGURATE_INTERNAL_MAIN_HEADER_H__
#include <stdbool.h>
#include "Ziggurat/Ziggurat.h"

extern bool zigInit;

extern zigenum windowStatus;

extern uint32_t windowWidth;
extern uint32_t windowHeight;

#ifdef WIN32
extern HINSTANCE zigHInstance;
extern HWND zigHWindow;
#endif

/**
 * @brief Platform dependant window initialisation
 */
zigenum platformZigInit();

/**
 * @breif Platform dependant event handelling
 */
zigenum platformProcess();

#endif  //
