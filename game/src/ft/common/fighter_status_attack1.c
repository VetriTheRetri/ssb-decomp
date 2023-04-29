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

#define ftStatus_CheckAttack13Kind(fp)      \
(                                           \
    (fp->ft_kind == Ft_Kind_Mario)      ||  \
    (fp->ft_kind == Ft_Kind_MetalMario) ||  \
    (fp->ft_kind == Ft_Kind_PolyMario)  ||  \
    (fp->ft_kind == Ft_Kind_Luigi)      ||  \
    (fp->ft_kind == Ft_Kind_PolyLuigi)  ||  \
    (fp->ft_kind == Ft_Kind_Captain)    ||  \
    (fp->ft_kind == Ft_Kind_PolyCaptain)||  \
    (fp->ft_kind == Ft_Kind_Link)       ||  \
    (fp->ft_kind == Ft_Kind_PolyLink)   ||  \
    (fp->ft_kind == Ft_Kind_Ness)       ||  \
    (fp->ft_kind == Ft_Kind_PolyNess)       \
)                                           \

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

        fp->attack1_followup_count = 0;
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

void func_ovl3_8014EBB4(GObj *fighter_gobj)
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
        ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
        ftAnim_Update(fighter_gobj);

        fp->command_vars.flags.flag1 = 0;

        fp->status_vars.common.attack1.is_goto_followup = FALSE;

        fp->attack1_status_id = fp->status_info.status_id;
    }
}

bool32 func_ovl3_8014EC78(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->input.button_tap & fp->input.button_mask_a)
    {
        if (fp->item_hold != NULL)
        {
            if (ArticleGetStruct(fp->item_hold)->type == At_Type_Throw)
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowF);

                return TRUE;
            }
            if (fp->input.button_hold & fp->input.button_mask_z)
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
                        func_ovl3_8014EA44(fighter_gobj);

                        fp->attack1_followup_count++;

                        return TRUE;
                    }
                    break;
                }
                if (attributes->is_have_attack12)
                {
                    func_ovl3_8014EAD8(fighter_gobj);

                    fp->attack1_followup_count++;

                    return TRUE;
                }
                break;

            case ftStatus_Common_Attack12:
                if(ftStatus_CheckAttack13Kind(fp))
                {
                    func_ovl3_8014EBB4(fighter_gobj);

                    return TRUE;
                }
                break;
            }
        }
        else if (attributes->is_have_attack11)
        {
            func_ovl3_8014EA44(fighter_gobj);

            return TRUE;
        }
    }
    if (fp->attack1_followup_frames != 0.0F)
    {
        fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;
    }
    return FALSE;
}

bool32 func_ovl3_8014EEC0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->attack1_followup_frames != 0.0F)
    {
        fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;

        if ((fp->input.button_tap & fp->input.button_mask_a) && (attributes->is_have_attack11))
        {
            if (fp->command_vars.flags.flag1 != 0)
            {
                func_ovl3_8014EA44(fighter_gobj);

                return TRUE;
            }
            fp->status_vars.common.attack1.is_goto_followup = TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl3_8014EF50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->attack1_followup_frames != 0.0F)
    {
        fp->attack1_followup_frames -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;

        if ((fp->input.button_tap & fp->input.button_mask_a) && (attributes->is_have_attack12))
        {
            if (fp->command_vars.flags.flag1 != 0)
            {
                func_ovl3_8014EAD8(fighter_gobj);

                return TRUE;
            }
            fp->status_vars.common.attack1.is_goto_followup = TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl3_8014EFE0(GObj *fighter_gobj)
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

            if (fp->input.button_tap & fp->input.button_mask_a)
            {
                if (fp->command_vars.flags.flag1 != 0)
                {
                    func_ovl3_8014EBB4(fighter_gobj);

                    return TRUE;
                }
                fp->status_vars.common.attack1.is_goto_followup = TRUE;
            }
        }
    }
    return FALSE;
}