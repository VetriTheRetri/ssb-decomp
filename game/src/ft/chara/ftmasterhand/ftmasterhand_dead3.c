#include "ftmasterhand.h"

void func_ovl3_8015AE80(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->lr = LEFT;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_Dead3, 0.0F, 1.0F, 0U);

    fp->phys_info.vel_air.z = 0.0F;
    fp->phys_info.vel_air.y = 0.0F;
    fp->phys_info.vel_air.x = 0.0F;
}
