#include "ftmasterhand.h"

void func_ovl3_80159A30(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80159040);
}

void func_ovl3_80159A54(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_WalkWait, 0.0F, 1.0F, 0U);

    fp->phys_info.vel_normal.z = 0;
    fp->phys_info.vel_normal.y = 0;
    fp->phys_info.vel_normal.x = 0;
}
