#ifndef _FTFOX_STATUSVARS_H_
#define _FTFOX_STATUSVARS_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef struct ftFox_SpecialHi_StatusVars
{
    s32 launch_delay;
    s32 gravity_delay;
    f32 angle;
    s32 travel_time;
    s32 decelerate_delay;
    s32 coll_timer_unk;

} ftFox_SpecialHi_StatusVars;

typedef struct ftFox_SpecialLw_StartusVars
{
    s32 release_lag;
    s32 turn_frames;
    bool32 is_release;
    GObj *effect_gobj;
    s32 gravity_delay;

} ftFox_SpecialLw_StatusVars;

typedef union ftFox_StatusVars
{
    ftFox_SpecialHi_StatusVars specialhi;
    ftFox_SpecialLw_StatusVars speciallw;

} ftFox_StatusVars;

#endif