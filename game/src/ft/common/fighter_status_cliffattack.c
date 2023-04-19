#include "fighter.h"

bool32 func_ovl3_80145620(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.button_press & (fp->input.button_mask_a | fp->input.button_mask_b))
    {
        func_ovl3_80144FE8(fighter_gobj, 1);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8014566C(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80145754);
}

void func_ovl3_80145690(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80145794);
}

void func_ovl3_801456B4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffAttackQuick1, 0.0F, 1.0F, 0U);

    fp->x190_flag_b7 = TRUE;

    fp->cb_take_damage = func_ovl3_80144CF8;
}

void func_ovl3_80145704(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffAttackSlow1, 0.0F, 1.0F, 0U);

    fp->x190_flag_b7 = TRUE;

    fp->cb_take_damage = func_ovl3_80144CF8;
}

void func_ovl3_80145754(GObj *fighter_gobj)
{
    func_ovl3_80145490(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffAttackQuick2, 0.0F, 1.0F, 0U);
    func_ovl3_8014557C(fighter_gobj);
}

void func_ovl3_80145794(GObj *fighter_gobj)
{
    func_ovl3_80145490(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffAttackSlow2, 0.0F, 1.0F, 0U);
    func_ovl3_8014557C(fighter_gobj);
}