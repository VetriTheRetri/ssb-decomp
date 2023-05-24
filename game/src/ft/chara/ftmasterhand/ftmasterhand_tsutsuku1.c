#include "ftmasterhand.h"

void func_ovl3_80159EA0(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8015A070);
}

void func_ovl3_80159EC4(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Tsutsuku1, 0.0F, 1.0F, 0U);
}
