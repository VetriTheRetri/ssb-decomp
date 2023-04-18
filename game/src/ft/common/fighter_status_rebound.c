#include "fighter.h"

void func_ovl3_80144A10(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.rebound.rebound_timer--;

    if (fp->status_vars.common.rebound.rebound_timer <= 0.0F)
    {
        func_ovl3_8013E1C8(fighter_gobj);
    }
}

void func_ovl3_80144A60(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Rebound, 0.0F, fp->status_vars.common.rebound.anim_speed, 0U);
}

void func_ovl3_80144A90(GObj *fighter_gobj)
{
    func_ovl3_80144A60(fighter_gobj);
}

void func_ovl3_80144AB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 lr_rebound;

    ftStatus_Update(fighter_gobj, ftStatus_Common_ReboundWait, 0.0F, 1.0F, 0U);

    fp->status_vars.common.rebound.anim_speed = fp->attributes->rebound_anim_length / fp->attack_damage_stale;

    fp->status_vars.common.rebound.rebound_timer = fp->attack_damage_stale;

    if (fp->lr == fp->lr_attack)
    {
        lr_rebound = LEFT;
    }
    else lr_rebound = RIGHT;

    fp->phys_info.vel_ground.x = (lr_rebound * (2.0F * fp->status_vars.common.rebound.rebound_timer));
}