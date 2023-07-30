#ifndef _EFFECT_VARS_H_
#define _EFFECT_VARS_H_

#include <ssb_types.h>
#include <macros.h>
#include <sys/obj_renderer.h> // Probably shouldn't be included
#include <PR/ultratypes.h>
#include <sys/obj.h>

#include "efdef.h"

typedef struct efVars_BoxSmash
{
	s32 lifetime;
	s32 unk_ef_0x1C;

} efVars_BoxSmash;

typedef struct efVars_Basic2 // Stuff like the effect that is created when hit by a normal element attack
{
    Vec3f vel;
    u8 player;
    s32 size;
    efImage *efimage;
    u8 filler_0x2C[0x3C - 0x2C];

} efVars_Basic2;

typedef struct efVars_DamageNormalHeavy
{
    Vec3f pos;
    u8 player;
    s32 size;

} efVars_DamageNormalHeavy;

typedef struct efVars_DamageEHit
{
    Vec3f vel;
    s32 size;
    efImage *efimage;

} efVars_DamageEHit;

typedef struct efVars_Common
{
    Vec3f vel;
    s32 size;
    efImage *efimage;

} efVars_Common;

#endif