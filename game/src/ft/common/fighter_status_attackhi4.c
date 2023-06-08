#include "fighter.h"
#include "article.h"

// 0x801505F0
void ftCommon_AttackHi4_SetStatus(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Common_AttackHi4, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftAnim_Update(fighter_gobj);
}

// 0x80150628
bool32 ftCommon_AttackHi4_CheckInputSuccess(Fighter_Struct *fp)
{
    if ((fp->input.pl.stick_range.y >= FTCOMMON_ATTACKHI4_STICK_RANGE_MIN) && (fp->input.pl.button_tap & fp->input.button_mask_a))
    {
        return TRUE;
    }
    else return FALSE;
}

// 0x80150660
bool32 ftCommon_AttackHi4_CheckInterruptCommon(Fighter_Struct *fp)
{
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146A8C(fp) != FALSE)
    {
        func_ovl3_80146690(fp->fighter_gobj, ftStatus_Common_LightThrowHi4);

        return TRUE;
    }
    if (attributes->is_have_attackhi4)
    {
        ftCommon_AttackHi4_SetStatus(fp->fighter_gobj);

        return TRUE;
    }
    return FALSE;
}

// 0x801506CC
bool32 ftCommon_AttackHi4_CheckInterruptKneebend(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (ftCommon_AttackHi4_CheckInputSuccess(fp) != FALSE)
    {
        return ftCommon_AttackHi4_CheckInterruptCommon(fp);
    }
    else return FALSE;
}

// 0x8015070C
bool32 ftCommon_AttackHi4_CheckInterruptCommon(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((ftCommon_AttackHi4_CheckInputSuccess(fp) != FALSE) && (fp->tap_stick_y < FTCOMMON_ATTACKHI4_BUFFER_FRAMES_MAX))
    {
        return ftCommon_AttackHi4_CheckInterruptCommon(fp);
    }
    else return FALSE;
}