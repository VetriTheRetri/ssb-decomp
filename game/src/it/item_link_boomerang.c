#include "item.h"
#include "fighter.h"

#define DOUBLE_PI32 6.2831855F

void func_ovl3_8016CC50(f32 *angle)
{
    if (DOUBLE_PI32 < *angle)
    {
        *angle -= DOUBLE_PI32;
    }
    else if (*angle < -DOUBLE_PI32)
    {
        *angle += DOUBLE_PI32;
    }
}