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

/**
 * @brief Platform dependant window initialisation
 */
zigenum platformZigInit();

/**
 * @brief Platform dependant event handelling
 */
zigenum platformProcess();

/**
 * @brief Produces the surface for the build windowing system
 * @param pSurface Pointer to the Vulkan surface being created
 * @param instance The instance being used to created the device
 * @returns The Ziggurat success code
 */
zigenum platformCreateSurface(VkSurfaceKHR* pSurface, VkInstance instance);

#endif  //
