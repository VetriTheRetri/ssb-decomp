#include "fighter.h"

void func_ovl3_80147EC0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    fp->status_vars.common.hammer.kneebend_anim_frame++;

    if ((fp->status_vars.common.hammer.input_source == FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON) && 
    (fp->status_vars.common.hammer.kneebend_anim_frame <= FTCOMMON_KNEEBEND_SHORT_HOP_FRAMES) && 
    (fp->input.button_tap_prev & (HAL_BUTTON_C_RIGHT | HAL_BUTTON_C_LEFT | HAL_BUTTON_C_DOWN | HAL_BUTTON_C_UP)))
    {
        fp->status_vars.common.hammer.is_short_hop = TRUE;
    }
    if (attributes->kneebend_frames <= fp->status_vars.common.hammer.kneebend_anim_frame)
    {
        func_ovl3_80147D30(fighter_gobj);
    }
}

void func_ovl3_80147F54(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.hammer.jump_force < fp->input.stick_range.y)
    {
        fp->status_vars.common.hammer.jump_force = fp->input.stick_range.y;
    }
}

void func_ovl3_80147F88(GObj *fighter_gobj, s32 input_source)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_HammerKneeBend, func_ovl2_800F3828(fighter_gobj), 1.0F, func_ovl2_800F385C(fighter_gobj));
    func_ovl2_800F388C(fighter_gobj);

    fp->status_vars.common.hammer.jump_force = fp->input.stick_range.y;
    fp->status_vars.common.hammer.kneebend_anim_frame = 0.0F;
    fp->status_vars.common.hammer.input_source = input_source;
    fp->status_vars.common.hammer.is_short_hop = FALSE;
}

bool32 func_ovl3_8014800C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 input_source = func_ovl3_8013F474(fp);

    if (input_source != FTCOMMON_KNEEBEND_INPUT_TYPE_NONE)
    {
        func_ovl3_80147F88(fighter_gobj, input_source);

        return TRUE;
    }
    else return FALSE;
}
