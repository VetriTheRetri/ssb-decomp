#include "fighter.h"

void func_ovl3_8013F2A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    fp->status_vars.common.kneebend.anim_frame += DObjGetStruct(fighter_gobj)->unk_dobj_0x78;

    if ((fp->status_vars.common.kneebend.input_source == FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON) &&
    (fp->status_vars.common.kneebend.anim_frame <= FTCOMMON_KNEEBEND_SHORT_HOP_FRAMES) &&
    (fp->input.button_mask_c & (HAL_BUTTON_C_RIGHT | HAL_BUTTON_C_LEFT | HAL_BUTTON_C_DOWN | HAL_BUTTON_C_UP)))
    {
        fp->status_vars.common.kneebend.is_short_hop = TRUE;
    }
    if (attributes->kneebend_frames <= fp->status_vars.common.kneebend.anim_frame) 
    {
        func_ovl3_8013F880(fighter_gobj);
    }
}

void func_ovl3_8013F334(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80151160(fighter_gobj) == FALSE)
    {
        if (func_ovl3_801506CC(fighter_gobj) == FALSE)
        {
            if (fp->status_vars.common.kneebend.jump_force < fp->input.stick_range.y)
            {
                fp->status_vars.common.kneebend.jump_force = fp->input.stick_range.y;
            }
        }
    }
}

void func_ovl3_8013F3A0(GObj *fighter_gobj, s32 status_id, u32 input_source)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, status_id, 0.0F, 1.0F, 0U);

    fp->status_vars.common.kneebend.jump_force = fp->input.stick_range.y;
    fp->status_vars.common.kneebend.anim_frame = 0.0F;
    fp->status_vars.common.kneebend.input_source = input_source;
    fp->status_vars.common.kneebend.is_short_hop = FALSE;

    fp->x192_flag_b0 = TRUE;
}

void func_ovl3_8013F408(GObj *fighter_gobj, u32 input_source)
{
    func_ovl3_8013F3A0(fighter_gobj, ftStatus_Common_KneeBend, input_source);
}

void func_ovl3_8013F42C(GObj *fighter_gobj, u32 input_source)
{
    func_ovl3_8013F3A0(fighter_gobj, ftStatus_Common_GuardKneeBend, input_source);
}

bool32 func_ovl3_8013F450(Fighter_Struct *fp)
{
    if (fp->input.button_press & (HAL_BUTTON_C_RIGHT | HAL_BUTTON_C_LEFT | HAL_BUTTON_C_DOWN | HAL_BUTTON_C_UP))
    {
        return TRUE;
    }
    else return FALSE;
}

s32 func_ovl3_8013F474(Fighter_Struct *fp)
{
    if ((fp->input.stick_range.y > FTCOMMON_KNEEBEND_STICK_RANGE_MIN) && (fp->buffer_stick_y <= FTCOMMON_KNEEBEND_BUFFER_FRAMES_MAX))
    {
        return FTCOMMON_KNEEBEND_INPUT_TYPE_STICK;
    }
    else if (func_ovl3_8013F450(fp) != FALSE)
    {
        return FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON;
    }
    else return FTCOMMON_KNEEBEND_INPUT_TYPE_NONE;
}

bool32 func_ovl3_8013F4D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 input_source;

    if (func_ovl2_800F3794(fighter_gobj) != FALSE)
    {
        return func_ovl3_8014800C(fighter_gobj);
    }
    input_source = func_ovl3_8013F474(fp);

    if (input_source != FTCOMMON_KNEEBEND_INPUT_TYPE_NONE)
    {
        func_ovl3_8013F408(fighter_gobj, input_source);

        return TRUE;
    }
    else return FALSE;
}

s32 func_ovl3_8013F53C(Fighter_Struct *fp)
{
    if ((fp->input.stick_range.y > FTCOMMON_KNEEBEND_RUN_STICK_RANGE_MIN) && (fp->buffer_stick_y <= FTCOMMON_KNEEBEND_BUFFER_FRAMES_MAX))
    {
        return FTCOMMON_KNEEBEND_INPUT_TYPE_STICK;
    }
    else if (func_ovl3_8013F450(fp) != FALSE)
    {
        return FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON;
    }
    else return FTCOMMON_KNEEBEND_INPUT_TYPE_NONE;
}