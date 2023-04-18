#include "fighter.h"

void func_ovl3_801441C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_StopCeil, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->phys_info.vel_air.z = 0.0F;
    fp->phys_info.vel_air.y = 0.0F;
}