#include "fighter.h"

void func_ovl3_8014E6A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (func_ovl3_80149CE0(fighter_gobj) == FALSE))
    {
        func_ovl3_80148D0C(fighter_gobj);
    }
}

void func_ovl3_8014E6E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ft_kind == Ft_Kind_Kirby) || (fp->ft_kind == Ft_Kind_PolyKirby))
    {
        if ((fp->fighter_vars.kirby.copy_id != Ft_Kind_Kirby) && (fp->fighter_vars.kirby.copy_bool_unk == FALSE))
        {
            func_ovl3_801635EC(fighter_gobj);
        }
    }
    ftStatus_Update(fighter_gobj, ftStatus_Common_Appeal, 0.0F, 1.0F, 0U);

    fp->command_vars.flags.flag1 = 0;
}

bool32 func_ovl3_8014E764(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.pl.button_tap & fp->input.button_mask_l)
    {
        func_ovl3_8014E6E0(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}