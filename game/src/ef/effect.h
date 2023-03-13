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

typedef struct Effect_Unk
{
    u8 filler_0x0[0x5C];
    Effect_Info *effect_info;

} Effect_Unk;

typedef struct Effect_Struct
{
    s32 unk_0x0;
    GObj *fgobj;
    u8 filler_0x8[0x18 - 0x8];
    s32 lifetime;

} Effect_Struct;

#define EffectGetStruct(effect_gobj) \
((Effect_Struct*)effect_gobj->user_data) \

#endif