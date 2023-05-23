#include "fighter.h"

bool32 func_ovl3_801457E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.pl.button_tap & fp->input.button_mask_z)
    {
        func_ovl3_80144FE8(fighter_gobj, 2);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80145824(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8014590C);
}

void func_ovl3_80145848(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8014594C);
}

void func_ovl3_8014586C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffEscapeQuick1, 0.0F, 1.0F, 0U);

    fp->x190_flag_b7 = TRUE;

    fp->proc_damage = func_ovl3_80144CF8;
}

void func_ovl3_801458BC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffEscapeSlow1, 0.0F, 1.0F, 0U);

    fp->x190_flag_b7 = TRUE;

    fp->proc_damage = func_ovl3_80144CF8;
}

void func_ovl3_8014590C(GObj *fighter_gobj)
{
    func_ovl3_80145490(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffEscapeQuick2, 0.0F, 1.0F, 0U);
    func_ovl3_8014557C(fighter_gobj);
}

void func_ovl3_8014594C(GObj *fighter_gobj)
{
    func_ovl3_80145490(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffEscapeSlow2, 0.0F, 1.0F, 0U);
    func_ovl3_8014557C(fighter_gobj);
}