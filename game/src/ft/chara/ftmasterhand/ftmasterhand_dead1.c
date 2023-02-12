#include "ftmasterhand.h"

void func_ovl3_8015AD50(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8015ADE8);
}

void func_ovl3_8015AD74(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_Dead1, 0.0F, 1.0F, 0U);

    fp = FighterGetStruct(fighter_gobj);

    fp->phys_info.vel_normal.z = 0.0F;
    fp->phys_info.vel_normal.y = 0.0F;
    fp->phys_info.vel_normal.x = 0.0F;
}
