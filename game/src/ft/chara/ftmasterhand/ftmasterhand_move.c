#include "ftmasterhand.h"



void func_ovl3_801591A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f vel;
    f32 magnitude;

    vec3f_sub(&vel, &fp->status_vars.masterhand.move.vel, &DObjGetStruct(fighter_gobj)->translate);

    magnitude = vec3f_mag(&vel);

    if (magnitude < 5.0F)
    {
        fp->status_vars.masterhand.move.magnitude = 0.0F;
        fp->phys_info.vel_air.x = vel.x;
        fp->phys_info.vel_air.y = vel.y;
    }
    else
    {
        fp->status_vars.masterhand.move.magnitude = magnitude;

        vec3f_normalize(&vel);

        vec3f_scale(&vel, magnitude * 0.1F);

        fp->phys_info.vel_air.x = vel.x;
        fp->phys_info.vel_air.y = vel.y;
    }
}

void func_ovl3_80159260(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    func_ovl2_800DE324(fighter_gobj);

    fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.masterhand.move.magnitude == 0.0F)
    {
        fp->phys_info.vel_air.z = 0.0F;
        fp->phys_info.vel_air.y = 0.0F;
        fp->phys_info.vel_air.x = 0.0F;

        fp->status_vars.masterhand.move.cb(fighter_gobj);
    }
}

void func_ovl3_801592B4(GObj *fighter_gobj, void (*cb)(GObj*), Vec3f *vel)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Move, fighter_gobj->anim_frame, 1.0F, 0U);

    fp->status_vars.masterhand.move.cb = cb;

    fp->status_vars.masterhand.move.vel = *vel;

    if (((vel->x - DObjGetStruct(fighter_gobj)->translate.x) * (f32)fp->lr) < 0.0F)
    {
        fp->lr = -fp->lr;
        fp->joint[0]->rotate.y = fp->lr * HALF_PI32;
    }
}
