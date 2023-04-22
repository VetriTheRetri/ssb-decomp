#include "fighter.h"

void func_ovl3_801479A0(GObj *fighter_gobj)
{
    if ((func_ovl3_8014800C(fighter_gobj) == FALSE) && (func_ovl3_80147E7C(fighter_gobj) == FALSE))
    {
        func_ovl2_800F39AC(fighter_gobj);
    }
}

void func_ovl3_801479E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_HammerWalk, func_ovl2_800F3828(fighter_gobj), 1.0F, func_ovl2_800F385C(fighter_gobj));
    func_ovl2_800F388C(fighter_gobj);
}

bool32 func_ovl3_80147A2C(GObj *fighter_gobj)
{
    if (func_ovl3_8013E614(fighter_gobj) != FALSE)
    {
        func_ovl3_801479E0(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}