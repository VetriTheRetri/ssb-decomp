#include "fighter.h"

void func_ovl3_80148050(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.hammer.landing_anim_frame++;

    if (fp->status_vars.common.hammer.landing_anim_frame <= 4.0F)
    {
        ftCommon_HammerWaitSetStatus(fighter_gobj);
    }
}

void func_ovl3_801480A4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_HammerLanding, ftCommon_HammerGetAnimFrame(fighter_gobj), 1.0F, ftCommon_HammerGetStatUpdateFlags(fighter_gobj));
    ftCommon_HammerCheckSetColAnim(fighter_gobj);

    fp->status_vars.common.hammer.landing_anim_frame = 0.0F;
}