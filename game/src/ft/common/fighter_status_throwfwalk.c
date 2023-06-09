#include "ftdonkey.h"

#define ftStatus_CheckInterruptThrowFWalk(fighter_gobj)    \
(                                                          \
    (func_ovl3_80146BE0(fighter_gobj) != FALSE) ||         \
    (func_ovl3_8014DFA8(fighter_gobj) != FALSE) ||         \
    (func_ovl3_8014D9B8(fighter_gobj) != FALSE) ||         \
    (func_ovl3_8014DC08(fighter_gobj) != FALSE) ||         \
    (func_ovl3_8014D4EC(fighter_gobj) != FALSE)            \
)                                                          \

f32 func_ovl3_8014D530(Fighter_Struct *fp, s32 status_id)
{
    f32 walk_anim_speed;

    switch (status_id)
    {
    case ftStatus_Donkey_ThrowFWalkSlow:
        walk_anim_speed = fp->attributes->throw_walkslow_anim_speed;
        break;

    case ftStatus_Donkey_ThrowFWalkMiddle:
        walk_anim_speed = fp->attributes->throw_walkmiddle_anim_speed;
        break;

    case ftStatus_Donkey_ThrowFWalkFast:
        walk_anim_speed = fp->attributes->throw_walkfast_anim_speed;
        break;
    }
    return walk_speed;
}

void func_ovl3_8014D590(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (!ftStatus_CheckInterruptThrowFWalk(fighter_gobj))
    {
        s32 status_id = func_ovl3_8013E340(ABS(fp->input.pl.stick_range.x)) + (ftStatus_Donkey_ThrowFWalkSlow - ftStatus_Common_WalkSlow);

        if (status_id != fp->status_info.status_id)
        {
            f32 div = func_ovl3_8014D530(fp, fp->status_info.status_id);
            f32 mul = func_ovl3_8014D530(fp, status_id);

            func_ovl3_8014D68C(fighter_gobj, (s32) (mul * (fighter_gobj->anim_frame / div)));
        }
    }
}

void func_ovl3_8014D68C(GObj *fighter_gobj, f32 frame_begin)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, func_ovl3_8013E340(fp->input.pl.stick_range.x) + (ftStatus_Donkey_ThrowFWalkSlow - ftStatus_Common_WalkSlow), frame_begin, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_8014D6D8(GObj *fighter_gobj)
{
    func_ovl3_8014D68C(fighter_gobj, 0.0F);
}

bool32 func_ovl3_8014D6F8(GObj *fighter_gobj)
{
    if (func_ovl3_8013E614(fighter_gobj) != FALSE)
    {
        func_ovl3_8014D6D8(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}