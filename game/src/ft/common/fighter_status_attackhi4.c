#include "fighter.h"
#include "article.h"

void func_ovl3_801505F0(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Common_AttackHi4, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

bool32 func_ovl3_80150628(Fighter_Struct *fp)
{
    if ((fp->input.stick_range.y >= FTCOMMON_ATTACKHI4_STICK_RANGE_MIN) && (fp->input.button_tap & fp->input.button_mask_a))
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80150660(Fighter_Struct *fp)
{
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146A8C(fp) != FALSE)
    {
        func_ovl3_80146690(fp->this_fighter, ftStatus_Common_LightThrowHi4);

        return TRUE;
    }
    if (attributes->is_have_attackhi4)
    {
        func_ovl3_801505F0(fp->this_fighter);

        return TRUE;
    }
    return FALSE;
}

bool32 func_ovl3_801506CC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80150628(fp) != FALSE)
    {
        return func_ovl3_80150660(fp);
    }
    else return FALSE;
}

bool32 func_ovl3_8015070C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl3_80150628(fp) != FALSE) && (fp->tap_stick_y < FTCOMMON_ATTACKHI4_BUFFER_FRAMES_MAX))
    {
        return func_ovl3_80150660(fp);
    }
    else return FALSE;
}