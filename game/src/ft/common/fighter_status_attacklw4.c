#include "fighter.h"
#include "article.h"

void func_ovl3_80150760(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Common_AttackLw4, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

bool32 func_ovl3_80150798(Fighter_Struct *fp)
{
    if ((fp->input.stick_range.y <= FTCOMMON_ATTACKLW4_STICK_RANGE_MIN) && (fp->input.button_tap & fp->input.button_mask_a))
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_801507D0(Fighter_Struct *fp)
{
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146A8C(fp) != FALSE)
    {
        func_ovl3_80146690(fp->fighter_gobj, ftStatus_Common_LightThrowLw4);

        return TRUE;
    }
    if (attributes->is_have_attacklw4)
    {
        func_ovl3_80150760(fp->fighter_gobj);

        return TRUE;
    }
    return FALSE;
}

bool32 func_ovl3_80150838(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl3_80150798(fp) != FALSE) && (fp->status_vars.common.attack4.is_goto_attacklw4 != FALSE))
    {
        return func_ovl3_801507D0(fp);
    }
    else return FALSE;
}

bool32 func_ovl3_80150884(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl3_80150798(fp) != FALSE) && (fp->tap_stick_y < FTCOMMON_ATTACKLW4_BUFFER_FRAMES_MAX))
    {
        return func_ovl3_801507D0(fp);
    }
    else return FALSE;
}