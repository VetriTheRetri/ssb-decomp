#include "ftmasterhand.h"

void func_ovl3_80159DB0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80159040);
}

void func_ovl3_80159DD4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_GootsubuDown, 0.0F, 1.0F, 0U);

    fp->phys_info.vel_air.y = 0.0F;
}
