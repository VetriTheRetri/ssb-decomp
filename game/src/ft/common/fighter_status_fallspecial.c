#include "fighter.h"

void func_ovl3_80143730(GObj *fighter_gobj)
{
    func_ovl3_8014019C(fighter_gobj);
}

void func_ovl3_80143750(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    func_ovl2_800D8DB0(fp);

    if (fp->is_fast_fall)
    {
        func_ovl2_800D8DA0(fp, attributes);
    }
    else if (fp->status_vars.common.fallspecial.is_fall_accelerate != FALSE) // Accelerate until fighter reaches terminal velocity?
    {
        func_ovl2_800D8E50(fp, attributes);
    }
    else func_ovl2_800D8D68(fp, attributes->gravity, attributes->fast_fall_speed);

    if (func_ovl2_800D8EDC(fp, fp->status_vars.common.fallspecial.drift) == FALSE)
    {
        func_ovl2_800D8FC8(fp, 8, attributes->aerial_acceleration, fp->status_vars.common.fallspecial.drift);
        func_ovl2_800D9074(fp, attributes);
    }
}

bool32 func_ovl3_80143808(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->status_vars.common.fallspecial.is_allow_pass == FALSE) || !(fp->coll_data.ground_flags & MPCOLL_MASK_NONSOLID) || (fp->input.pl.stick_range.y >= FTCOMMON_FALLSPECIAL_PASS_STICK_RANGE_MIN))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8014384C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE798(fighter_gobj, func_ovl3_80143808) != FALSE)
    {
        if (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL)
        {
            func_ovl3_80144C24(fighter_gobj);
        }
        else if ((fp->status_vars.common.fallspecial.is_goto_landing != FALSE) || (fp->phys_info.vel_air.y < FTCOMMON_FALLSPECIAL_SKIP_LANDING_VEL_Y_MAX))
        {
            func_ovl3_80142E3C(fighter_gobj, fp->status_vars.common.fallspecial.is_allow_interrupt, fp->status_vars.common.fallspecial.landing_lag);
        }
        else func_ovl3_8013E1C8(fighter_gobj);
    }
}

void func_ovl3_801438F0(GObj *fighter_gobj, f32 drift, bool32 unk1, bool32 is_fall_accelerate, bool32 is_goto_landing, f32 landing_lag, bool32 is_allow_interrupt)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    ftStatus_Update(fighter_gobj, ftStatus_Common_FallSpecial, 0.0F, 1.0F, 8U);

    fp->status_vars.common.fallspecial.drift = (attributes->aerial_speed_max_x * drift);

    func_ovl2_800D8E78(fp, fp->status_vars.common.fallspecial.drift);

    if (fp->ground_or_air == ground)
    {
        ftMapCollide_SetAir(fp);
    }
    fp->jumps_used = attributes->jumps_max;

    fp->status_vars.common.fallspecial.is_allow_pass = TRUE;
    fp->status_vars.common.fallspecial.is_goto_landing = is_goto_landing;
    fp->status_vars.common.fallspecial.landing_lag = landing_lag;
    fp->status_vars.common.fallspecial.is_allow_interrupt = is_allow_interrupt;
    fp->status_vars.common.fallspecial.is_fall_accelerate = is_fall_accelerate;

    ftCommon_CheckSetColAnimIndex(fighter_gobj, 7, 0);
    func_ovl3_80165024(fighter_gobj);

    fp->x192_flag_b0 = TRUE;
}