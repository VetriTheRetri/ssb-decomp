#ifndef _HAL_INPUT_H_
#define _HAL_INPUT_H_

#include <macros.h>
#include <ssb_types.h>

#include <PR/mbi.h>
#include <PR/ultratypes.h>

// Might be temporary, don't know where else to put these

#define GCONTROLLER_RANGE_MAX_I 80                                 // Maximum control stick range in integer
#define GCONTROLLER_RANGE_MAX_F ((float)GCONTROLLER_RANGE_MAX_I)  // Maximum control stick range in float

#define HAL_BUTTON_C_RIGHT (1 << 0)
#define HAL_BUTTON_C_LEFT (1 << 1)
#define HAL_BUTTON_C_DOWN (1 << 2)
#define HAL_BUTTON_C_UP (1 << 3)
#define HAL_BUTTON_R (1 << 4)
#define HAL_BUTTON_L (1 << 5)
#define HAL_BUTTON_D_RIGHT (1 << 8)
#define HAL_BUTTON_D_LEFT (1 << 9)
#define HAL_BUTTON_D_DOWN (1 << 10)
#define HAL_BUTTON_D_UP (1 << 11)
#define HAL_BUTTON_START (1 << 12)
#define HAL_BUTTON_Z (1 << 13)
#define HAL_BUTTON_B (1 << 14)
#define HAL_BUTTON_A (1 << 15)

#endif 