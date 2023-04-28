#include "fighter.h"

void func_ovl3_8014E7B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (fp->status_vars.common.attack1.is_goto_followup != FALSE))
    {
        if ((fp->ft_kind == Ft_Kind_Pikachu) || (fp->ft_kind == Ft_Kind_PolyPikachu))
        {
            func_ovl3_8014EA44(fighter_gobj);
        }
        else func_ovl3_8014EAD8(fighter_gobj);
    }
    else func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_8014E824(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ft_kind != Ft_Kind_Captain) && (fp->ft_kind != Ft_Kind_PolyCaptain) && (fp->command_vars.flags.flag1 != 0) && (fp->is_goto_attack100))
    {
        func_ovl3_8014F0F4(fighter_gobj);
    }
    else if ((fp->command_vars.flags.flag1 != 0) && (fp->status_vars.common.attack1.is_goto_followup != FALSE))
    {
        func_ovl3_8014EBB4(fighter_gobj);
    }
    else func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_8014E8B4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->ft_kind == Ft_Kind_Captain) || (fp->ft_kind == Ft_Kind_PolyCaptain)) && (fp->command_vars.flags.flag1 != 0) && (fp->is_goto_attack100))
    {
        func_ovl3_8014F0F4(fighter_gobj);
    }
    else func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_8014E9B4(GObj *fighter_gobj)
{
    if (func_ovl3_8014EFE0(fighter_gobj) == FALSE)
    {
        func_ovl3_8014F4EC(fighter_gobj);
    }
}

void func_ovl3_8014E9E4(GObj *fighter_gobj)
{
    func_ovl3_8014F4EC(fighter_gobj);
}

void func_ovl3_8014EA04(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800EA5E8(fp, 1);
    func_ovl2_800EA778(fp, fp->flags_lw.halfword);
    func_ovl2_800EA7B0(fp, 0);
}

void func_ovl3_8014EA44(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146064(fighter_gobj) == FALSE)
    {
        fp->cb_status = func_ovl3_8014EA04;

        ftStatus_Update(fighter_gobj, ftStatus_Common_Attack11, 0.0F, 1.0F, 0U);
        ftAnim_Update(fighter_gobj);

        fp->command_vars.flags.flag1 = 0;

        fp->status_vars.common.attack1.is_goto_followup = FALSE;
        fp->status_vars.common.attack1.interrupt_catch_timer = 0;

        fp->unk_ft_0x158 = 0;
        fp->attack1_status_id = fp->status_info.status_id;
        fp->is_goto_attack100 = FALSE;
        fp->attack1_followup_frames = attributes->attack1_followup_frames;
    }
}

void func_ovl3_8014EAD8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80146064(fighter_gobj) == FALSE)
    {
        ftStatus_Update(fighter_gobj, ftStatus_Common_Attack12, 0.0F, 1.0F, 0U);
        ftAnim_Update(fighter_gobj);

        fp->command_vars.flags.flag1 = 0;

        fp->status_vars.common.attack1.is_goto_followup = FALSE;

        fp->attack1_status_id = fp->status_info.status_id;

        switch (fp->ft_kind)
        {
        case Ft_Kind_Mario:
        case Ft_Kind_MetalMario:
        case Ft_Kind_PolyMario:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;

        case Ft_Kind_Luigi:
        case Ft_Kind_PolyLuigi:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;

        case Ft_Kind_Captain:
        case Ft_Kind_PolyCaptain:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;

        case Ft_Kind_Link:
        case Ft_Kind_PolyLink:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;

        case Ft_Kind_Ness:
        case Ft_Kind_PolyNess:
            fp->attack1_followup_frames = FTCOMMON_ATTACK1_FOLLOWUP_FRAMES_DEFAULT;
            break;
        }
    }
}
