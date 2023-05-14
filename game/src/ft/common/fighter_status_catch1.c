#include "fighter.h"

void func_ovl3_80149A10(GObj *fighter_gobj)
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

void func_ovl3_80149AC8(GObj *fighter_gobj)
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

void func_ovl3_80149B48(GObj *fighter_gobj) // Unused
{
    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        func_ovl3_80149AC8(fighter_gobj);
    }
}

void func_ovl3_80149B78(GObj *fighter_gobj)
{
    if (func_ovl2_800DDE50(fighter_gobj) == FALSE)
    {
        func_ovl3_80149AC8(fighter_gobj);
    }
}

void func_ovl3_80149BA8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Catch, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->command_vars.flags.flag1 = 1;
    fp->command_vars.flags.flag2 = 0;

    fp->status_vars.common.catchmain.catch_pull_anim_frames = 0.0F;
    fp->status_vars.common.catchmain.catch_pull_frame_begin = 0.0F;

    func_ovl2_800E80A4(fp, 0x10, func_ovl3_80149F04, func_ovl3_8014A860);

    fp->x192_flag_b5 = FALSE;

    if (((fp->ft_kind == Ft_Kind_Samus) || (fp->ft_kind == Ft_Kind_PolySamus)) && (func_ovl2_80101E80(fighter_gobj) != NULL))
    {
        fp->is_statupdate_stop_gfx = TRUE;
    }
}

bool32 func_ovl3_80149C60(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    u32 flags = fp->status_vars.common.catchmain.unk_0x24;

    if ((fp->input.button_press & fp->input.button_mask_a) && (attributes->is_have_catch))
    {
        func_ovl3_80149BA8(fighter_gobj);

        fp->x192_flag_b5 = flags;

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80149CE0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146A8C(fp) != FALSE)
    {
        func_ovl3_801466EC(fighter_gobj);

        return TRUE;
    }
    else if ((fp->input.pl.button_hold & fp->input.button_mask_z) && (fp->input.button_press & fp->input.button_mask_a) && (attributes->is_have_catch))
    {
        func_ovl3_80149BA8(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80149D80(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146A8C(fp) != FALSE)
    {
        func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowDash);

        return TRUE;
    }
    else if ((fp->input.pl.button_hold & fp->input.button_mask_z) && (fp->input.button_press & fp->input.button_mask_a) && (attributes->is_have_catch))
    {
        func_ovl3_80149BA8(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80149E24(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146A8C(fp) != FALSE)
    {
        func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowDash);

        return TRUE;
    }
    else if ((fp->input.button_press & fp->input.button_mask_z) && (attributes->is_have_catch))
    {
        func_ovl3_80149BA8(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8014E91C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.attack1.interrupt_catch_timer < FTCOMMON_ATTACK1_INTERRUPT_CATCH_FRAMES_MAX)
    {
        fp->status_vars.common.attack1.interrupt_catch_timer++;

        if (func_ovl3_80149E24(fighter_gobj) != FALSE)
        {
            return;
        }
    }
    if (func_ovl3_8014F4EC(fighter_gobj) == FALSE)
    {
        if ((fp->ft_kind == Ft_Kind_Pikachu) || (fp->ft_kind == Ft_Kind_PolyPikachu))
        {
            if (func_ovl3_8014EEC0(fighter_gobj) != FALSE)
            {
                return;
            }
        }
        else func_ovl3_8014EF50(fighter_gobj);
    }
}