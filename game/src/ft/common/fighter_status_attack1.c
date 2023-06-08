#include "fighter.h"
#include "ftmario.h"
#include "ftfox.h"
#include "ftdonkey.h"
#include "ftsamus.h"
#include "ftlink.h"
#include "ftyoshi.h"
#include "ftcaptain.h"
#include "ftkirby.h"
#include "ftpikachu.h"
#include "ftpurin.h"
#include "ftness.h"

#define ftStatus_CheckAttack13Kind(fp)        \
(                                             \
    ((fp)->ft_kind == Ft_Kind_Mario)      ||  \
    ((fp)->ft_kind == Ft_Kind_MetalMario) ||  \
    ((fp)->ft_kind == Ft_Kind_PolyMario)  ||  \
    ((fp)->ft_kind == Ft_Kind_Luigi)      ||  \
    ((fp)->ft_kind == Ft_Kind_PolyLuigi)  ||  \
    ((fp)->ft_kind == Ft_Kind_Captain)    ||  \
    ((fp)->ft_kind == Ft_Kind_PolyCaptain)||  \
    ((fp)->ft_kind == Ft_Kind_Link)       ||  \
    ((fp)->ft_kind == Ft_Kind_PolyLink)   ||  \
    ((fp)->ft_kind == Ft_Kind_Ness)       ||  \
    ((fp)->ft_kind == Ft_Kind_PolyNess)       \
)                                             \

// 0x8014E7B0
void ftCommon_Attack11_ProcUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (fp->status_vars.common.attack1.is_goto_followup != FALSE))
    {
        if ((fp->ft_kind == Ft_Kind_Pikachu) || (fp->ft_kind == Ft_Kind_PolyPikachu))
        {
            ftCommon_Attack11_SetStatus(fighter_gobj);
        }
        else ftCommon_Attack12_SetStatus(fighter_gobj);
    }
    else func_ovl2_800D94C4(fighter_gobj);
}

// 0x8014E824
void ftCommon_Attack12_ProcUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ft_kind != Ft_Kind_Captain) && (fp->ft_kind != Ft_Kind_PolyCaptain) && (fp->command_vars.flags.flag1 != 0) && (fp->is_goto_attack100))
    {
        ftCommon_Attack100Start_SetStatus(fighter_gobj);
    }
    else if ((fp->command_vars.flags.flag1 != 0) && (fp->status_vars.common.attack1.is_goto_followup != FALSE))
    {
        ftCommon_Attack13_SetStatus(fighter_gobj);
    }
    else func_ovl2_800D94C4(fighter_gobj);
}

// 0x8014E8B4
void ftCommon_Attack13_ProcUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->ft_kind == Ft_Kind_Captain) || (fp->ft_kind == Ft_Kind_PolyCaptain)) && (fp->command_vars.flags.flag1 != 0) && (fp->is_goto_attack100))
    {
        ftCommon_Attack100Start_SetStatus(fighter_gobj);
    }
    else func_ovl2_800D94C4(fighter_gobj);
}

// 0x8014E91C
void ftCommon_Attack11_ProcInterrupt(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.attack1.interrupt_catch_timer < 2)
    {
        fp->status_vars.common.attack1.interrupt_catch_timer++;

        if (ftCommon_Catch_CheckInterruptAttack11(fighter_gobj) != FALSE)
        {
            return;
        }
    }
    if (ftCommon_Attack100Start_CheckInterruptCommon(fighter_gobj) == FALSE)
    {
        if ((fp->ft_kind == Ft_Kind_Pikachu) || (fp->ft_kind == Ft_Kind_PolyPikachu))
        {
            if (ftCommon_Attack11_CheckGoto(fighter_gobj) != FALSE)
            {
                return;
            }
        }
        else ftCommon_Attack12_CheckGoto(fighter_gobj);
    }
}

// 0x8014E9B4
void ftCommon_Attack12_ProcInterrupt(GObj *fighter_gobj)
{
    if (ftCommon_Attack13_CheckGoto(fighter_gobj) == FALSE)
    {
        ftCommon_Attack100Start_CheckInterruptCommon(fighter_gobj);
    }
}

// 0x8014E9E4
void ftCommon_Attack13_ProcInterrupt(GObj *fighter_gobj)
{
    ftCommon_Attack100Start_CheckInterruptCommon(fighter_gobj);
}

// 0x8014EA04
void ftCommon_Attack11_ProcStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCommon_MotionCountIncSetID(fp, ftAttack_Index_Attack11);
    ftCommon_StatUpdateCountIncSetFlags(fp, fp->stat_flags.halfword);
    ftCommon_Update1PGameAttackStats(fp, 0);
}

// 0x8014EA44
void ftCommon_Attack11_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (func_ovl3_80146064(fighter_gobj) == FALSE)
    {
        fp->proc_status = ftCommon_Attack11_ProcStatus;

        ftStatus_Update(fighter_gobj, ftStatus_Common_Attack11, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
        ftAnim_Update(fighter_gobj);

        fp->command_vars.flags.flag1 = 0;

        fp->status_vars.common.attack1.is_goto_followup = FALSE;
        fp->status_vars.common.attack1.interrupt_catch_timer = 0;

        fp->attack1_followup_count = 0;
        fp->attack1_status_id = fp->status_info.status_id;
        fp->is_goto_attack100 = FALSE;
        fp->attack1_followup_frames = attributes->attack1_followup_frames;
    }
}

// 0x8014EAD8
void ftCommon_Attack12_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80146064(fighter_gobj) == FALSE)
    {
        ftStatus_Update(fighter_gobj, ftStatus_Common_Attack12, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
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

// 0x8014EBB4
void ftCommon_Attack13_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (func_ovl3_80146064(fighter_gobj) == FALSE)
    {
        switch (fp->ft_kind)
        {
        case Ft_Kind_Mario:
        case Ft_Kind_MetalMario:
        case Ft_Kind_PolyMario:
            status_id = ftStatus_Mario_Attack13;
            break;

        case Ft_Kind_Luigi:
        case Ft_Kind_PolyLuigi:
            status_id = ftStatus_Mario_Attack13;
            break;

        case Ft_Kind_Captain:
        case Ft_Kind_PolyCaptain:
            status_id = ftStatus_Captain_Attack13;
            break;

        case Ft_Kind_Link:
        case Ft_Kind_PolyLink:
            status_id = ftStatus_Link_Attack13;
            break;

        case Ft_Kind_Ness:
        case Ft_Kind_PolyNess:
            status_id = ftStatus_Ness_Attack13;
            break;
        }
        ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
        ftAnim_Update(fighter_gobj);

        fp->command_vars.flags.flag1 = 0;

        fp->status_vars.common.attack1.is_goto_followup = FALSE;

        fp->attack1_status_id = fp->status_info.status_id;
    }
}

// 0x8014EC78
bool32 ftCommon_Attack1_CheckInterruptCommon(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->input.pl.button_tap & fp->input.button_mask_a)
    {
        if (fp->item_hold != NULL)
        {
            if (ArticleGetStruct(fp->item_hold)->type == At_Type_Throw)
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowF);

                return TRUE;
            }
            if (fp->input.pl.button_hold & fp->input.button_mask_z)
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowDrop);

                return TRUE;
            }
            switch (ArticleGetStruct(fp->item_hold)->type)
            {
            case At_Type_Swing:
                func_ovl3_80146E94(fighter_gobj, 0);
                return TRUE;

            case At_Type_Shoot:
                func_ovl3_80147844(fighter_gobj);
                return TRUE;
            }
        }
        if (fp->attack1_followup_frames != 0.0F)
        {
            switch (fp->attack1_status_id)
            {
            case ftStatus_Common_Attack11:
                if ((fp->ft_kind == Ft_Kind_Pikachu) || (fp->ft_kind == Ft_Kind_PolyPikachu))
                {
                    if (attributes->is_have_attack11)
                    {
                        ftCommon_Attack11_SetStatus(fighter_gobj);

                        fp->attack1_followup_count++;

                        return TRUE;
                    }
                    break;
                }
                else if (attributes->is_have_attack12)
                {
                    ftCommon_Attack12_SetStatus(fighter_gobj);

                    fp->attack1_followup_count++;

                    return TRUE;
                }
                break;

            case ftStatus_Common_Attack12:
                if(ftStatus_CheckAttack13Kind(fp))
                {
                    ftCommon_Attack13_SetStatus(fighter_gobj);

                    return TRUE;
                }
                break;
            }
        }
        else if (attributes->is_have_attack11)
        {
            ftCommon_Attack11_SetStatus(fighter_gobj);

            return TRUE;
        }
    }
    if (fp->attack1_followup_frames != 0.0F)
    {
        fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;
    }
    return FALSE;
}

// 0x8014EEC0
bool32 ftCommon_Attack11_CheckGoto(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->attack1_followup_frames != 0.0F)
    {
        fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;

        if ((fp->input.pl.button_tap & fp->input.button_mask_a) && (attributes->is_have_attack11))
        {
            if (fp->command_vars.flags.flag1 != 0)
            {
                ftCommon_Attack11_SetStatus(fighter_gobj);

                return TRUE;
            }
            fp->status_vars.common.attack1.is_goto_followup = TRUE;
        }
    }
    return FALSE;
}

// 0x8014EF50
bool32 ftCommon_Attack12_CheckGoto(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->attack1_followup_frames != 0.0F)
    {
        fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;

        if ((fp->input.pl.button_tap & fp->input.button_mask_a) && (attributes->is_have_attack12))
        {
            if (fp->command_vars.flags.flag1 != 0)
            {
                ftCommon_Attack12_SetStatus(fighter_gobj);

                return TRUE;
            }
            fp->status_vars.common.attack1.is_goto_followup = TRUE;
        }
    }
    return FALSE;
}

// 0x8014EFE0
bool32 ftCommon_Attack13_CheckGoto(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if(!ftStatus_CheckAttack13Kind(fp))
    {
        return FALSE;
    }
    else
    {
        if (fp->attack1_followup_frames != 0.0F)
        {
            fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;

            if (fp->input.pl.button_tap & fp->input.button_mask_a)
            {
                if (fp->command_vars.flags.flag1 != 0)
                {
                    ftCommon_Attack13_SetStatus(fighter_gobj);

                    return TRUE;
                }
                fp->status_vars.common.attack1.is_goto_followup = TRUE;
            }
        }
    }
    return FALSE;
}