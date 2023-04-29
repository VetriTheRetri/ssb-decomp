#include "fighter.h"
#include "ftfox.h"
#include "ftlink.h"
#include "ftkirby.h"
#include "ftpurin.h"
#include "ftcaptain.h"

#define ftStatus_CheckAttack100Kind(fp)     \
(                                           \
    (fp->ft_kind == Ft_Kind_Fox)        ||  \
    (fp->ft_kind == Ft_Kind_PolyFox)    ||  \
    (fp->ft_kind == Ft_Kind_Link)       ||  \
    (fp->ft_kind == Ft_Kind_PolyLink)   ||  \
    (fp->ft_kind == Ft_Kind_Kirby)      ||  \
    (fp->ft_kind == Ft_Kind_PolyKirby)  ||  \
    (fp->ft_kind == Ft_Kind_Purin)      ||  \
    (fp->ft_kind == Ft_Kind_PolyPurin)  ||  \
    (fp->ft_kind == Ft_Kind_Captain)    ||  \
    (fp->ft_kind == Ft_Kind_PolyCaptain)    \
)                                           \

void func_ovl3_8014F0D0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8014F3C0);
}

void func_ovl3_8014F0F4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (func_ovl3_80146064(fighter_gobj) == FALSE)
    {
        switch (fp->ft_kind)
        {
        case Ft_Kind_Fox:
        case Ft_Kind_PolyFox:
            status_id = ftStatus_Fox_Attack100Start;
            break;

        case Ft_Kind_Link:
        case Ft_Kind_PolyLink:
            status_id = ftStatus_Link_Attack100Start;
            break;

        case Ft_Kind_Kirby:
        case Ft_Kind_PolyKirby:
            status_id = ftStatus_Kirby_Attack100Start;
            break;

        case Ft_Kind_Purin:
        case Ft_Kind_PolyPurin:
            status_id = ftStatus_Purin_Attack100Start;
            break;

        case Ft_Kind_Captain:
        case Ft_Kind_PolyCaptain:
            status_id = ftStatus_Captain_Attack100Start;
            break;
        }
        ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
        ftAnim_Update(fighter_gobj);

        fp->status_vars.common.attack100.is_anim_end = FALSE;
        fp->status_vars.common.attack100.is_goto_loop = FALSE;

        fp->command_vars.flags.flag1 = 0;
        fp->command_vars.flags.flag2 = 0;
    }
}

extern intptr_t D_NF_00001220;
extern void *D_ovl2_80131074;

void func_ovl3_8014F1BC(Fighter_Struct *fp)
{
    Vec3f offset;

    if (fp->ft_kind == Ft_Kind_Kirby)
    {
        if (fp->command_vars.flags.flag2 != 0)
        {
            ftKirbyAttack100Gfx *attack_gfx = ((uintptr_t)D_ovl2_80131074 + (intptr_t)&D_NF_00001220); // Linker thing

            offset.x = attack_gfx[fp->command_vars.flags.flag2 - 1].offset.x;
            offset.y = attack_gfx[fp->command_vars.flags.flag2 - 1].offset.y;
            offset.z = attack_gfx[fp->command_vars.flags.flag2 - 1].offset.z;

            func_ovl2_800EDF24(fp->joint[0], &offset);

            func_ovl2_80101D34(&offset, fp->lr, attack_gfx[fp->command_vars.flags.flag2 - 1].vel.x, attack_gfx[fp->command_vars.flags.flag2 - 1].vel.y, attack_gfx[fp->command_vars.flags.flag2 - 1].vel.z);

            fp->command_vars.flags.flag2 = 0;
        }
    }
}

void func_ovl3_8014F2A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fighter_gobj->anim_frame >= 0.0F) && (fighter_gobj->anim_frame < DObjGetStruct(fighter_gobj)->unk_dobj_0x78))
    {
        fp->status_vars.common.attack100.is_anim_end = TRUE;

        func_ovl2_800EA5E8(fp, 4);
        func_ovl2_800EA778(fp, fp->flags_lw.halfword);
        func_ovl2_800EA7B0(fp, 0);
    }
    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->command_vars.flags.flag1 = 0;

        if ((fp->status_vars.common.attack100.is_anim_end != FALSE) && (fp->status_vars.common.attack100.is_goto_loop == FALSE))
        {
            func_ovl3_8014F45C(fighter_gobj);

            return;
        }
        else if (func_ovl3_80146064(fighter_gobj) == FALSE)
        {
            fp->status_vars.common.attack100.is_goto_loop = FALSE;
        }
        else return;
    }
    func_ovl3_8014F1BC(fp);
}

void func_ovl3_8014F388(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->input.button_tap & fp->input.button_mask_a) || (fp->input.button_tap_prev & fp->input.button_mask_a))
    {
        fp->status_vars.common.attack100.is_goto_loop = TRUE;
    }
}

void func_ovl3_8014F3C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    switch (fp->ft_kind)
    {
    case Ft_Kind_Fox:
    case Ft_Kind_PolyFox:
        status_id = ftStatus_Fox_Attack100Loop;
        break;

    case Ft_Kind_Link:
    case Ft_Kind_PolyLink:
        status_id = ftStatus_Link_Attack100Loop;
        break;

    case Ft_Kind_Kirby:
    case Ft_Kind_PolyKirby:
        status_id = ftStatus_Kirby_Attack100Loop;
        break;

    case Ft_Kind_Purin:
    case Ft_Kind_PolyPurin:
        status_id = ftStatus_Purin_Attack100Loop;
        break;

    case Ft_Kind_Captain:
    case Ft_Kind_PolyCaptain:
        status_id = ftStatus_Captain_Attack100Loop;
        break;
    }
    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    func_ovl3_8014F1BC(fp);
}

void func_ovl3_8014F45C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    switch (fp->ft_kind)
    {
    case Ft_Kind_Fox:
    case Ft_Kind_PolyFox:
        status_id = ftStatus_Fox_Attack100End;
        break;

    case Ft_Kind_Link:
    case Ft_Kind_PolyLink:
        status_id = ftStatus_Link_Attack100End;
        break;

    case Ft_Kind_Kirby:
    case Ft_Kind_PolyKirby:
        status_id = ftStatus_Kirby_Attack100End;
        break;

    case Ft_Kind_Purin:
    case Ft_Kind_PolyPurin:
        status_id = ftStatus_Purin_Attack100End;
        break;

    case Ft_Kind_Captain:
    case Ft_Kind_PolyCaptain:
        status_id = ftStatus_Captain_Attack100End;
        break;
    }
    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
}

bool32 func_ovl3_8014F4EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;
    s32 followup_count;

    if(!ftStatus_CheckAttack100Kind(fp))
    {
        return FALSE;
    }
    if ((fp->input.button_tap & fp->input.button_mask_a) || (fp->input.button_tap_prev & fp->input.button_mask_a))
    {
        fp->attack1_followup_count++;

        switch (fp->ft_kind)
        {
        case Ft_Kind_Fox:
        case Ft_Kind_PolyFox:
            followup_count = 4;
            status_id = ftStatus_Common_Attack12;
            break;

        case Ft_Kind_Link:
        case Ft_Kind_PolyLink:
            followup_count = 5;
            status_id = ftStatus_Common_Attack12;
            break;

        case Ft_Kind_Kirby:
        case Ft_Kind_PolyKirby:
            followup_count = 4;
            status_id = ftStatus_Common_Attack12;
            break;

        case Ft_Kind_Purin:
        case Ft_Kind_PolyPurin:
            followup_count = 4;
            status_id = ftStatus_Common_Attack12;
            break;

        case Ft_Kind_Captain:
        case Ft_Kind_PolyCaptain:
            followup_count = 6;
            status_id = ftStatus_Captain_Attack13;
            break;
        }
        if (fp->attack1_followup_count >= followup_count)
        {
            if ((status_id == fp->status_info.status_id) && (fp->command_vars.flags.flag1 != 0))
            {
                func_ovl3_8014F0F4(fighter_gobj);

                return TRUE;
            }
            else fp->is_goto_attack100 = TRUE;
        }
    }
    return FALSE;
}