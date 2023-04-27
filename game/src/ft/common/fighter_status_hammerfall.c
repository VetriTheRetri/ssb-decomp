#include "fighter.h"

void func_ovl3_80147BE0(GObj *fighter_gobj)
{
	return;
}

void func_ovl3_80147BE8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        if (fp->phys_info.vel_air.y > FTCOMMON_HAMMER_SKIP_LANDING_VEL_Y_MAX)
        {
            func_ovl2_800F3938(fighter_gobj);
        }
        else func_ovl3_801480A4(fighter_gobj);
    }
}

void func_ovl3_80147C50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        func_ovl2_800DEEC8(fp);
    }
    ftStatus_Update(fighter_gobj, ftStatus_Common_HammerFall, func_ovl2_800F3828(fighter_gobj), 1.0F, func_ovl2_800F385C(fighter_gobj));
    func_ovl2_800F388C(fighter_gobj);
    func_ovl2_800D8EB8(fp);
}

bool32 func_ovl3_80147CCC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl2_800F3794(fighter_gobj) != FALSE) && (fp->input.button_press & (fp->input.button_mask_a | fp->input.button_mask_b)))
    {
        func_ovl3_80147C50(fighter_gobj); // Wiggle out of DamageFall if A or B is pressed

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80147D30(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    s32 vel_x, vel_y;

    func_ovl2_800DEEC8(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_HammerFall, func_ovl2_800F3828(fighter_gobj), 1.0F, func_ovl2_800F385C(fighter_gobj));
    func_ovl2_800F388C(fighter_gobj);

    switch (fp->status_vars.common.hammer.input_source)
    {
    case FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON:
        func_ovl3_8013F6A0(fp->input.stick_range.x, &vel_x, &vel_y, fp->status_vars.common.hammer.is_short_hop);
        break;

    case FTCOMMON_KNEEBEND_INPUT_TYPE_STICK:
    default:
        vel_x = fp->input.stick_range.x;
        vel_y = fp->status_vars.common.hammer.jump_force;
        break;
    }
    fp->phys_info.vel_air.y = (vel_y * attributes->jump_height_mul) + attributes->jump_height_base;
    fp->phys_info.vel_air.x = vel_x * attributes->jump_vel_x;

    fp->tap_stick_y = U8_MAX - 1;
}

void func_ovl3_80147E34(GObj *fighter_gobj)
{
    func_ovl3_80141DA0(fighter_gobj, ftStatus_Common_HammerFall, func_ovl2_800F3828(fighter_gobj), func_ovl2_800F385C(fighter_gobj));
    func_ovl2_800F388C(fighter_gobj);
}

bool32 func_ovl3_80147E7C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80141E60(fp) != FALSE)
    {
        func_ovl3_80147E34(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}