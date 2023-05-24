#include "ftmasterhand.h"

void func_ovl3_80159830(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_801599C4);
}

void func_ovl3_80159854(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Walk, 0.0F, 1.0F, 0U);
    func_ovl3_80157F90(fighter_gobj);

    fp->phys_info.vel_air.x = 0.0F;
    fp->phys_info.vel_air.y = fp->coll_data.ground_dist / 60.0F;
}
