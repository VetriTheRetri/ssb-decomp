#include "ftdonkey.h"

void func_ovl3_8014D850(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    fp->status_vars.common.throwf.kneebend_anim_frame++;

    if ((fp->status_vars.common.throwf.input_source == FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON)                       &&
    (fp->status_vars.common.throwf.kneebend_anim_frame <= FTCOMMON_KNEEBEND_SHORT_HOP_FRAMES)                     &&
    (fp->input.button_tap_prev & (HAL_BUTTON_C_RIGHT | HAL_BUTTON_C_LEFT | HAL_BUTTON_C_DOWN | HAL_BUTTON_C_UP)))
    {
        fp->status_vars.common.throwf.is_short_hop = TRUE;
    }
    if (attributes->kneebend_frames <= fp->status_vars.common.throwf.kneebend_anim_frame)
    {
        func_ovl3_8014DAF8(fighter_gobj);
    }
}

void func_ovl3_8014D8E4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80146BE0(fighter_gobj) == FALSE)
    {
        if (func_ovl3_8014DFA8(fighter_gobj) == FALSE)
        {
            if (fp->status_vars.common.throwf.jump_force < fp->input.stick_range.y)
            {
                fp->status_vars.common.throwf.jump_force = fp->input.stick_range.y;
            }
        }
    }
}

void func_ovl3_8014D950(GObj *fighter_gobj, s32 input_source)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Donkey_ThrowFKneeBend, 0.0F, 0.0F, 0.0F);

    fp->status_vars.common.throwf.jump_force = fp->input.stick_range.y;
    fp->status_vars.common.throwf.kneebend_anim_frame = 0.0F;
    fp->status_vars.common.throwf.input_source = input_source;
    fp->status_vars.common.throwf.is_short_hop = FALSE;
}

bool32 func_ovl3_8014D9B8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 input_source = func_ovl3_8013F474(fp);

    if (input_source != FTCOMMON_KNEEBEND_INPUT_TYPE_NONE)
    {
        func_ovl3_8014D950(fighter_gobj, input_source);

        return TRUE;
    }
    else return FALSE;
}