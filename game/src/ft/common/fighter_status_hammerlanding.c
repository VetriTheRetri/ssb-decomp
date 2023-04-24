#include "fighter.h"

void func_ovl3_80148050(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.hammer.landing_anim_frame++;

    if (fp->status_vars.common.hammer.landing_anim_frame <= 4.0F)
    {
        func_ovl2_800F3938(fighter_gobj);
    }
}

void func_ovl3_801480A4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCollision_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_HammerLanding, func_ovl2_800F3828(fighter_gobj), 1.0F, func_ovl2_800F385C(fighter_gobj));
    func_ovl2_800F388C(fighter_gobj);

    fp->status_vars.common.hammer.landing_anim_frame = 0.0F;
}