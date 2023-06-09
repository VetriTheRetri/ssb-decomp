#include "ftcaptain.h"

void func_ovl3_80160280(Fighter_Struct *fp)
{
    ftCommon_SetCatchVars(fp, FTCATCHKIND_MASK_SPECIALHICAPTAIN, func_ovl3_80160690, ftCommon_CaptureCaptain_ProcCapture);
}

void func_ovl3_801602B0(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        ftCommon_FallSpecial_SetStatus(fighter_gobj, FTCAPTAIN_FALCONDIVE_FALLSPECIAL_DRIFT, FALSE, TRUE, TRUE, FTCAPTAIN_FALCONDIVE_LANDING_LAG, FALSE);
    }
}

void func_ovl3_80160304(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = ftGetStruct(fighter_gobj);

    if ((fighter_gobj->anim_frame <= 0.0F) || (this_fp->command_vars.flags.flag0 != 0))
    {
        Fighter_Struct *catch_fp = ftGetStruct(fp->catch_gobj);

        catch_fp->status_vars.common.capturecaptain.capture_flag |= FTCOMMON_CAPTURECAPTAIN_MASK_THROW;

        func_ovl2_801008F4(1); // Apply screen shake/rumble?
        func_ovl3_80160730(fighter_gobj);
    }
}

void func_ovl3_80160370(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    s32 stick_x;

    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->command_vars.flags.flag1 = 0;

        stick_x = ABS(fp->input.pl.stick_range.x);

        if (stick_x > 18)
        {
            ftCommon_StickInputSetLR(fp);

            fp->joint[0]->rotate.y = fp->lr * HALF_PI32;
        }
    }
}

void func_ovl3_801603F0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = AttributesGetStruct(fp);

    fp->phys_info.vel_air.x = fp->status_vars.captain.specialhi.vel.x;
    fp->phys_info.vel_air.y = fp->status_vars.captain.specialhi.vel.y;
    fp->phys_info.vel_air.z = 0.0F;

    if (func_ovl2_800D8EDC(fp, attributes->aerial_speed_max_x * FTCAPTAIN_FALCONDIVE_AIR_SPEED_MAX_MUL) == FALSE)
    {
        func_ovl2_800D8FC8(fp, 8, attributes->aerial_acceleration * FTCAPTAIN_FALCONDIVE_AIR_ACCEL_MUL, attributes->aerial_speed_max_x * FTCAPTAIN_FALCONDIVE_AIR_SPEED_MAX_MUL);
        func_ovl2_800D9074(fp, attributes);
    }
    fp->status_vars.captain.specialhi.vel.x = fp->phys_info.vel_air.x;
    fp->status_vars.captain.specialhi.vel.y = fp->phys_info.vel_air.y;

    func_ovl2_800D93E4(fighter_gobj);

    fp->phys_info.vel_air.x += fp->status_vars.captain.specialhi.vel.x;
    fp->phys_info.vel_air.y += fp->status_vars.captain.specialhi.vel.y;
}

void func_ovl3_801604D8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f vec;

    if (!(fp->status_vars.captain.specialhi.unk_0x0 & 4))
    {
        ftCommon_CaptureCaptain_UpdateCapturePos(fighter_gobj, fp->catch_gobj, &vec);

        if (vec3f_mag(&vec) > 180.0F)
        {
            vec3f_normalize(&vec);
            vec3f_scale(&vec, 180.0F);
        }
        vec3f_sub_from(&DObjGetStruct(fighter_gobj)->translate, &vec);
    }
}

void func_ovl3_80160560(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->phys_info.vel_air.y < 0.0F)
    {
        if (fp->command_vars.flags.flag2 == 0)
        {
            func_ovl2_800DE978(fighter_gobj);
        }
        else
        {
            func_ovl2_800DE958(fighter_gobj);
            fp->command_vars.flags.flag2--;
        }
    }
    else if ((func_ovl2_800DE87C(fighter_gobj) != FALSE) && (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL))
    {
        ftCommon_CliffCatch_SetStatus(fighter_gobj);
    }
}

void func_ovl3_801605FC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->jumps_used = fp->attributes->jumps_max;

    fp->status_vars.captain.specialhi.unk_0x0 = 0;

    fp->command_vars.flags.flag0 = 0;
    fp->command_vars.flags.flag1 = 0;
    fp->command_vars.flags.flag2 = FTCAPTAIN_FALCONDIVE_UNK_TIMER;

    fp->status_vars.captain.specialhi.vel.x = 0.0F;
    fp->status_vars.captain.specialhi.vel.y = 0.0F;
}

void jtgt_ovl3_80160630(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);

    fp->proc_status = func_ovl3_801605FC;

    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialHi, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    func_ovl3_80160280(fp);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80160690(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj), *catch_fp;
    GObj *search_gobj;

    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialAirHi, 0.0F, 1.0F, FTSTATUPDATE_GFX_PRESERVE);
    ftAnim_Update(fighter_gobj);
    ftCommon_SetCaptureIgnoreMask(fp, FTCATCHKIND_MASK_ALL);
    func_ovl2_800D9444(fighter_gobj);

    search_gobj = fp->search_gobj;
    fp->catch_gobj = search_gobj;

    catch_fp = ftGetStruct(search_gobj); // No NULL check, might be dangerous

    if (catch_fp->ground_or_air == air)
    {
        fp->status_vars.common.capturecaptain.capture_flag |= FTCOMMON_CAPTURECAPTAIN_MASK_NOUPDATE;
        fp->x192_flag_b3 = FALSE;
    }
    else fp->x192_flag_b3 = TRUE;
}

void func_ovl3_80160730(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialHiCatch, 0.0F, 1.0F, FTSTATUPDATE_GFX_PRESERVE);
    ftAnim_Update(fighter_gobj);
    ftCommon_SetCaptureIgnoreMask(fp, FTCATCHKIND_MASK_NONE);

    if ((fp->x192_flag_b3 == TRUE) && (fp->catch_gobj != NULL))
    {
        func_ovl3_8014ADB0(fighter_gobj);
    }
    fp->catch_gobj = NULL;
}

void jtgt_ovl3_801607B4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->proc_status = func_ovl3_801605FC;

    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialHiRelease, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    func_ovl3_80160280(fp);
    ftAnim_Update(fighter_gobj);
}