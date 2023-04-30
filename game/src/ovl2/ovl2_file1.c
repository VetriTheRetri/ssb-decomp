#include "ssb_types.h"

s32 func_ovl2_800D6490(u16 arg0)
{
    s32 var_v1;
    s32 i;

    for (i = 0, var_v1 = 0; i < 16; i++, arg0 = arg0 >> 1)
    {
        if (arg0 & 1)
        {
            var_v1++;
        }
    }
    return var_v1;
}

s32 func_ovl2_800D6508(u16 arg0, u16 arg1, s32 arg2)
{
    s32 var_v1 = -1;

    arg2++;

    do
    {
        var_v1++;

        if ((arg0 & (1 << var_v1)) && !(arg1 & (1 << var_v1)))
        {
            arg2--;
        }
    } 
    while (arg2 != 0);

    return var_v1;
}

s32 func_ovl2_800D6554(u16 arg0, s32 arg1)
{
    s32 var_v1 = -1;

    arg1++;

    do
    {
        var_v1++;

        if (arg0 & (1 << var_v1))
        {
            arg1--;
        }
    }
    while (arg1 != 0);

    return var_v1;
}