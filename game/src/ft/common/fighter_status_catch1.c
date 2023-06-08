#include "fighter.h"

// 0x80149A10
void ftCommon_Catch_ProcUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.catchmain.catch_pull_frame_begin > 0.0F)
    {
        fp->status_vars.common.catchmain.catch_pull_frame_begin -= fp->status_vars.common.catchmain.catch_pull_anim_frames;

        if (fp->status_vars.common.catchmain.catch_pull_frame_begin <= 0.0F)
        {
            fp->status_vars.common.catchmain.catch_pull_frame_begin = 0.0F;
        }
    }
    if (fp->command_vars.flags.flag2 != 0)
    {
        fp->status_vars.common.catchmain.catch_pull_frame_begin = fp->command_vars.flags.flag2;

        fp->status_vars.common.catchmain.catch_pull_anim_frames = fp->status_vars.common.catchmain.catch_pull_frame_begin / fp->command_vars.flags.flag1;

        fp->command_vars.flags.flag2 = 0;
    }
    func_ovl2_800D94C4(fighter_gobj);
}

// 0x80149AC8
void ftCommon_Catch_CaptureSetStatusRelease(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *catch_fp;
    GObj *catch_gobj;

    func_ovl3_8013F9E0(fighter_gobj);

    catch_gobj = this_fp->catch_gobj;

    if (catch_gobj != NULL)
    {
        catch_fp = FighterGetStruct(catch_gobj);

        func_ovl3_8014ADB0(catch_gobj);

        if (catch_fp->ground_or_air == ground)
        {
            func_ovl3_8013E1C8(catch_gobj);
        }
        else func_ovl3_8013F9E0(catch_gobj);

        catch_fp->capture_gobj = NULL;
        this_fp->catch_gobj = NULL;
    }
}

// 0x80149B48
void func_ovl3_80149B48(GObj *fighter_gobj) // Unused
{
    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        ftCommon_Catch_CaptureSetStatusRelease(fighter_gobj);
    }
}

// 0x80149B78
void ftCommon_Catch_ProcMap(GObj *fighter_gobj)
{
    if (func_ovl2_800DDE50(fighter_gobj) == FALSE)
    {
        ftCommon_Catch_CaptureSetStatusRelease(fighter_gobj);
    }
}

// 0x80149BA8
void ftCommon_Catch_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Catch, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftAnim_Update(fighter_gobj);

    fp->command_vars.flags.flag1 = 1;
    fp->command_vars.flags.flag2 = 0;

    fp->status_vars.common.catchmain.catch_pull_anim_frames = 0.0F;
    fp->status_vars.common.catchmain.catch_pull_frame_begin = 0.0F;

    ftCommon_SetCatchVars(fp, FTCATCHKIND_MASK_CATCHCOMMON, ftCommon_CatchPull_SetStatus, ftCommon_CapturePulled_ProcCapture);

    fp->x192_flag_b5 = FALSE;

    if (((fp->ft_kind == Ft_Kind_Samus) || (fp->ft_kind == Ft_Kind_PolySamus)) && (func_ovl2_80101E80(fighter_gobj) != NULL))
    {
        fp->is_statupdate_stop_gfx = TRUE;
    }
}

// 0x80149C60
bool32 ftCommon_Catch_CheckInterruptGuard(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    u32 flags = fp->status_vars.common.catchmain.unk_0x24;

    if ((fp->input.pl.button_tap & fp->input.button_mask_a) && (attributes->is_have_catch))
    {
        ftCommon_Catch_SetStatus(fighter_gobj);

        fp->x192_flag_b5 = flags;

        return TRUE;
    }
    else return FALSE;
}

// 0x80149CE0
bool32 ftCommon_Catch_CheckInterruptCommon(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146A8C(fp) != FALSE)
    {
        func_ovl3_801466EC(fighter_gobj);

        return TRUE;
    }
    else if ((fp->input.pl.button_hold & fp->input.button_mask_z) && (fp->input.pl.button_tap & fp->input.button_mask_a) && (attributes->is_have_catch))
    {
        ftCommon_Catch_SetStatus(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

// 0x80149D80
bool32 ftCommon_Catch_CheckInterruptRunDash(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146A8C(fp) != FALSE)
    {
        func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowDash);

        return TRUE;
    }
    else if ((fp->input.pl.button_hold & fp->input.button_mask_z) && (fp->input.pl.button_tap & fp->input.button_mask_a) && (attributes->is_have_catch))
    {
        ftCommon_Catch_SetStatus(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

// 0x80149E24
bool32 ftCommon_Catch_CheckInterruptAttack11(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146A8C(fp) != FALSE)
    {
        func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowDash);

        return TRUE;
    }
    else if ((fp->input.pl.button_tap & fp->input.button_mask_z) && (attributes->is_have_catch))
    {
        ftCommon_Catch_SetStatus(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}