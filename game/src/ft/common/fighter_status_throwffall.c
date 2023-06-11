#include "ftdonkey.h"

void func_ovl3_8014DA00(GObj *fighter_gobj)
{
    if (ftCommon_LightThrow_CheckInterruptCommon(fighter_gobj) == FALSE)
    {
        func_ovl3_8014DFA8(fighter_gobj);
    }
}

void func_ovl3_8014DA30(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        if (fp->phys_info.vel_air.y > FTCOMMON_THROWFFALL_SKIP_LANDING_VEL_Y_MAX)
        {
            func_ovl3_8014D49C(fighter_gobj);
        }
        else func_ovl3_8014DCA4(fighter_gobj);
    }
}

void func_ovl3_8014DA98(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        ftMapCollide_SetAir(fp);
    }
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_ThrowFFall, 0.0F, 0.0F, 8U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_8014DAF8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    s32 vel_x;
    s32 vel_y;

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_ThrowFFall, 0.0F, 0.0F, 0U);

    switch (fp->status_vars.common.throwf.input_source)
    {
    case FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON:
        ftCommon_Jump_GetJumpForceButton(fp->input.pl.stick_range.x, &vel_x, &vel_y, fp->status_vars.common.throwf.is_short_hop);
        break;

    case FTCOMMON_KNEEBEND_INPUT_TYPE_STICK:
    default:
        vel_x = fp->input.pl.stick_range.x;
        vel_y = fp->status_vars.common.throwf.jump_force;

    }
    fp->phys_info.vel_air.y = (vel_y * attributes->jump_height_mul) + attributes->jump_height_base;
    fp->phys_info.vel_air.x = vel_x * attributes->jump_vel_x;

    fp->tap_stick_y = U8_MAX - 1;
}

void func_ovl3_8014DBE0(GObj *fighter_gobj)
{
    ftCommon_Pass_SetStatusParam(fighter_gobj, ftStatus_Donkey_ThrowFFall, 1.0F, 0);
}

bool32 func_ovl3_8014DC08(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (ftCommon_Pass_CheckInputSuccess(fp) != FALSE)
    {
        func_ovl3_8014DBE0(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}
