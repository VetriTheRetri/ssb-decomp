#include "ftmasterhand.h"

void func_ovl3_80159AA0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80159040);
}

void func_ovl3_80159AC4(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_WalkShoot, 0.0F, 1.0F, 0U);
}
