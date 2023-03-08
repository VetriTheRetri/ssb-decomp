#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef struct Effect_Info
{
    u8 filler_0x0[0x1C];
    Vec3f scale;

} Effect_Info;

typedef struct Effect_Struct
{
    u8 filler_0x0[0x5C];
    Effect_Info *effect_info;

} Effect_Struct;

#endif