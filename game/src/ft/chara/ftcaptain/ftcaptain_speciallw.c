#include "ftcaptain.h"

// 0x8015FC30
void ftCaptain_SpecialLw_UpdateGFX(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (!(fp->is_statupdate_stop_gfx))
    {
        if (fp->command_vars.flags.flag2 == 1)
        {

            if (func_ovl2_80101ED8(fighter_gobj) != FALSE)
            {
                fp->is_statupdate_stop_gfx = TRUE;
            }

            fp->command_vars.flags.flag2 = 0;
        }
    }
    else if (fp->command_vars.flags.flag2 == 2)
    {
        ftCommon_ProcDestroyGFX(fighter_gobj);
        fp->command_vars.flags.flag2 = 0;
    }
}

// 0x8015FCB0
void ftCaptain_SpecialLw_SetAir(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->ground_or_air = air;
    fp->jumps_used = 1;
}

void func_ovl3_8015FCC8(GObj *fighter_gobj) // Unused?
{
    ftMapCollide_SetGround(ftGetStruct(fighter_gobj));
}

// 0x8015FCE8
void ftCaptain_SpecialLw_DecideMapCollide(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        if (fp->command_vars.flags.flag3 != 0)
        {
            func_ovl2_800DDE84(fighter_gobj, ftCaptain_SpecialLw_SetAir);
        }
        else func_ovl2_800DDDDC(fighter_gobj, ftCaptain_SpecialLw_SetAir);
    }
    else func_ovl2_800DE6E4(fighter_gobj, ftCaptain_SpecialLw_SetAir);
}

// 0x8015FD50
void ftCaptain_SpecialLw_DecideSetEndStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        ftCommon_Wait_SetStatus(fighter_gobj);
    }
    else ftCommon_Fall_SetStatus(fighter_gobj);
}

// 0x8015FD90
void ftCaptain_SpecialLw_ProcUpdate(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, ftCaptain_SpecialLw_DecideSetEndStatus);
}

// 0x8015FDB4
void ftCaptain_SpecialLw_ProcPhysics(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        fp->joint[0]->rotate.z = (f32)-atan2f(fp->coll_data.ground_angle.x, fp->coll_data.ground_angle.y);
        func_ovl2_800D8C14(fighter_gobj);
    }
    else if (fp->command_vars.flags.flag0 != 0)
    {
        func_ovl2_800D91EC(fighter_gobj);
    }
    else func_ovl2_800D93E4(fighter_gobj);

    vec3f_scale(&fp->phys_info.vel_air, fp->status_vars.captain.speciallw.vel_scale);

    ftCaptain_SpecialLw_UpdateGFX(fighter_gobj);
}

// 0x8015FE4C
void ftCaptain_SpecialLwLanding_ProcPhysics(GObj *fighter_gobj)
{
    func_ovl2_800D8C14(fighter_gobj);
}

// 0x8015FE6C
void ftCaptain_SpecialAirLw_ProcPhysics(GObj *fighter_gobj)
{
    ftCaptain_SpecialLw_UpdateGFX(fighter_gobj);
    func_ovl2_800D93E4(fighter_gobj);
}

// 0x8015FE94
void ftCaptain_SpecialLwBound_ProcPhysics(GObj *fighter_gobj)
{
    func_ovl2_800D93E4(fighter_gobj);
}

// 0x8015FEB4
bool32 ftCaptain_SpecialLwBound_CheckMapCollideGoto(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 == 1) && (fp->coll_data.coll_mask & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL)))
    {
        ftMapCollide_SetAir(fp);
        ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialLwBound, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);

        fp->command_vars.flags.flag1 = 0;

        return TRUE;
    }
    else return FALSE;
}

// 0x8015FF2C
bool32 ftCaptain_SpecialLwAir_CheckAirGoto(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 == 2)
    {
        if (fp->ground_or_air == air)
        {
            ftCaptain_SpecialLwAir_SetStatus(fighter_gobj);

            fp->command_vars.flags.flag1 = 0;

            return TRUE;
        }
        fp->command_vars.flags.flag1 = 0;
    }
    return FALSE;
}

// 0x8015FF88
void ftCaptain_SpecialLw_ProcMap(GObj *fighter_gobj)
{
    ftCaptain_SpecialLw_DecideMapCollide(fighter_gobj);

    if (ftCaptain_SpecialLwBound_CheckMapCollideGoto(fighter_gobj) == FALSE)
    {
        ftCaptain_SpecialLwAir_CheckAirGoto(fighter_gobj);
    }
}

// 0x8015FFC0
void ftCaptain_SpecialLwAir_ProcMap(GObj *fighter_gobj)
{
    ftCaptain_SpecialLw_DecideMapCollide(fighter_gobj);
}

// 0x8015FFE0
void ftCaptain_SpecialLwLanding_ProcMap(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, ftCaptain_SpecialLwLanding_SetStatus);
}

// 0x80160004
void ftCaptain_SpecialLw_ProcHit(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->status_vars.captain.speciallw.scale_apply_timer < FTCAPTAIN_FALCONKICK_VEL_SCALE_APPLY_TIME)
    {
        fp->status_vars.captain.speciallw.scale_apply_timer++;

        fp->status_vars.captain.speciallw.vel_scale /= FTCAPTAIN_FALCONKICK_VEL_SCALE_DIV;
    }
}

// 0x80160038
void ftCaptain_SpecialLw_ProcStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->status_vars.captain.speciallw.scale_apply_timer = 0;

    fp->command_vars.flags.flag0 = 0;
    fp->command_vars.flags.flag3 = 0;
    fp->command_vars.flags.flag1 = 0;
    fp->command_vars.flags.flag2 = 0;

    fp->status_vars.captain.speciallw.vel_scale = 1.0F;
}

// 0x80160060
void ftCaptain_SpecialLwAir_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    f32 rot_z = fp->joint[0]->rotate.z;

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialLwAir, 0.0F, 1.0F, FTSTATUPDATE_GFX_PRESERVE);

    fp->joint[0]->rotate.z = rot_z;
    fp->joint[1]->rotate.z = fp->joint[0]->rotate.z;

    fp->proc_lagstart = ftCommon_ProcPauseGFX;
    fp->proc_lagend = ftCommon_ProcResumeGFX;
}

// 0x801600EC
void ftCaptain_SpecialLwLanding_SetStatus(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(ftGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialLwLanding, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
}

// 0x80160128
void ftCaptain_SpecialLw_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->proc_status = ftCaptain_SpecialLw_ProcStatus;

    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialLw, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftAnim_Update(fighter_gobj);

    fp->proc_shield = ftCaptain_SpecialLw_ProcHit;
    fp->proc_hit = ftCaptain_SpecialLw_ProcHit;

    fp->proc_lagstart = ftCommon_ProcPauseGFX;
    fp->proc_lagend = ftCommon_ProcResumeGFX;
}

void jtgt_ovl3_801601A0(GObj *fighter_gobj) // Unused
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialLwAir, 0.0F, 1.0F, FTSTATUPDATE_GFX_PRESERVE);
    ftAnim_Update(fighter_gobj);

    fp->proc_hit = ftCaptain_SpecialLw_ProcHit;

    fp->proc_lagstart = ftCommon_ProcPauseGFX;
    fp->proc_lagend = ftCommon_ProcResumeGFX;
}

// 0x8016020C
void ftCaptain_SpecialAirLw_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->proc_status = ftCaptain_SpecialLw_ProcStatus;

    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialAirLw, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftAnim_Update(fighter_gobj);

    fp->proc_lagstart = ftCommon_ProcPauseGFX;
    fp->proc_lagend = ftCommon_ProcResumeGFX;
}