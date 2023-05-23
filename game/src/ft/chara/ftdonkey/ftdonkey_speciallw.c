#include "ftdonkey.h"

void func_ovl3_8015B9F0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8015BAA4);
}

void func_ovl3_8015BA14(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fighter_gobj->anim_frame >= 0.0F) && (fighter_gobj->anim_frame < DObjGetStruct(fighter_gobj)->unk_dobj_0x78))
    {
        if (fp->status_vars.donkey.speciallw.is_loop != FALSE)
        {
            fp->status_vars.donkey.speciallw.is_loop = FALSE;
        }
        else func_ovl3_8015BAD0(fighter_gobj);
    }
}

void func_ovl3_8015BA7C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.pl.button_tap & fp->input.button_mask_b)
    {
        fp->status_vars.donkey.speciallw.is_loop = TRUE;
    }
}

void func_ovl3_8015BAA4(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_SpecialLwLoop, 0.0F, 1.0F, 0U);
}

void func_ovl3_8015BAD0(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_SpecialLwEnd, 0.0F, 1.0F, 0U);
}

void jtgt_ovl3_8015BAFC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Donkey_SpecialLwStart, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->status_vars.donkey.speciallw.is_loop = FALSE;
}
