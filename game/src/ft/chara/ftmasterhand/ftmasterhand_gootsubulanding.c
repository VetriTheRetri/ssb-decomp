#include "ftmasterhand.h"

void func_ovl3_80159E20(GObj *fighter_gobj)
{
    if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        func_ovl3_80159DD4(fighter_gobj);
    }
}

void func_ovl3_80159E50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_GootsubuLanding, 0.0F, 1.0F, 0U);

    fp->phys_info.vel_normal.x = 0.0F;
    fp->phys_info.vel_normal.y = -400.0F;
}
