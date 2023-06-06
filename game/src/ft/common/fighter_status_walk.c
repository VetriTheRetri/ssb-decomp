#include "fighter.h"

#define ftStatus_CheckInterruptWalk(fighter_gobj)  \
(                                                  \
    (func_ovl3_80151098(fighter_gobj) != FALSE) || \
    (func_ovl3_80151160(fighter_gobj) != FALSE) || \
    (func_ovl3_801511E0(fighter_gobj) != FALSE) || \
    (func_ovl3_80149CE0(fighter_gobj) != FALSE) || \
    (ftCommon_AttackS4_CheckInterruptCommon(fighter_gobj) != FALSE) || \
    (ftCommon_AttackHi4_CheckInterruptCommon(fighter_gobj) != FALSE) || \
    (ftCommon_AttackLw4_CheckInterruptCommon(fighter_gobj) != FALSE) || \
    (ftCommon_AttackS3_CheckInterruptCommon(fighter_gobj) != FALSE) || \
    (ftCommon_AttackHi3_CheckInterruptCommon(fighter_gobj) != FALSE) || \
    (ftCommon_AttackLw3_CheckInterruptCommon(fighter_gobj) != FALSE) || \
    (ftCommon_Attack1_CheckInterruptCommon(fighter_gobj) != FALSE) || \
    (func_ovl3_80148D0C(fighter_gobj) != FALSE) || \
    (ftCommon_Appeal_CheckInterruptCommon(fighter_gobj) != FALSE) || \
    (func_ovl3_8013F4D0(fighter_gobj) != FALSE) || \
    (func_ovl3_8013ED64(fighter_gobj) != FALSE) || \
    (func_ovl3_8014310C(fighter_gobj) != FALSE) || \
    (func_ovl3_8013E2A0(fighter_gobj) != FALSE)    \
)                                                  \

f32 func_ovl3_8013E2E0(Fighter_Struct *fp, s32 status_id)
{
    f32 walk_anim_speed;

    switch (status_id)
    {
    case ftStatus_Common_WalkSlow:
        walk_anim_speed = fp->attributes->walkslow_anim_speed;
        break;

    case ftStatus_Common_WalkMiddle:
        walk_anim_speed = fp->attributes->walkmiddle_anim_speed;
        break;

    case ftStatus_Common_WalkFast:
        walk_anim_speed = fp->attributes->walkfast_anim_speed;
        break;
    }
    return walk_anim_speed;
}

s32 func_ovl3_8013E340(s8 stick_range_x)
{
    s32 status_id;

    stick_range_x = ABS(stick_range_x);

    if (stick_range_x >= FTCOMMON_WALKFAST_STICK_RANGE_MIN) status_id = ftStatus_Common_WalkFast;

    else if (stick_range_x >= FTCOMMON_WALKMIDDLE_STICK_RANGE_MIN) status_id = ftStatus_Common_WalkMiddle;

    else status_id = ftStatus_Common_WalkSlow;

    return status_id;
}

void func_ovl3_8013E390(GObj *fighter_gobj)
{
    Fighter_Struct *fp = fighter_gobj->user_data;

    if (!ftStatus_CheckInterruptWalk(fighter_gobj))
    {
        s32 status_id = func_ovl3_8013E340(ABS(fp->input.pl.stick_range.x));

        if (status_id != fp->status_info.status_id)
        {
            f32 div = func_ovl3_8013E2E0(fp, fp->status_info.status_id);
            f32 mul = func_ovl3_8013E2E0(fp, status_id);

            func_ovl3_8013E580(fighter_gobj, (s32) ((fighter_gobj->anim_frame / div) * mul));
        }
    }
}

void func_ovl3_8013E548(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800D8A70(fp, fp->attributes->walk_speed_mul, fp->attributes->traction);
    func_ovl2_800D87D0(fighter_gobj);
}

void func_ovl3_8013E580(GObj *fighter_gobj, f32 anim_frame_begin)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id = func_ovl3_8013E340(fp->input.pl.stick_range.x);

    ftStatus_Update(fighter_gobj, status_id, anim_frame_begin, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    if (status_id != ftStatus_Common_WalkFast)
    {
        fp->x192_flag_b0 = TRUE;
    }
}

void func_ovl3_8013E5F4(GObj *fighter_gobj)
{
    func_ovl3_8013E580(fighter_gobj, 0.0F);
}

bool32 func_ovl3_8013E614(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->input.pl.stick_range.x * fp->lr) >= 8)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_8013E648(GObj *fighter_gobj)
{
    if (func_ovl3_8013E614(fighter_gobj) != FALSE)
    {
        func_ovl3_8013E5F4(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}