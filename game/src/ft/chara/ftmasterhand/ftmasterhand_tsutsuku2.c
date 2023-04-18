#include "ftmasterhand.h"

void func_ovl3_80159F40(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f translate;
    Vec3f vel;
    f32 magnitude;

    fp->status_vars.masterhand.tsutsuku.wait_timer--;

    if (fp->status_vars.masterhand.tsutsuku.wait_timer == 0)
    {
        func_ovl3_80159F14(fighter_gobj);
    }
    else
    {
        translate.x = DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.x + (-fp->lr * 900.0F);
        translate.y = DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.y + 300.0F;
        translate.z = 0.0F;

        vec3f_sub(&vel, &translate, &DObjGetStruct(fighter_gobj)->translate);

        magnitude = vec3f_mag(&vel);

        if (magnitude < 5.0F)
        {
            fp->phys_info.vel_air.x = vel.x;
            fp->phys_info.vel_air.y = vel.y;
        }
        else
        {
            vec3f_normalize(&vel);
            vec3f_scale(&vel, magnitude * 0.1F);

            fp->phys_info.vel_air.x = vel.x;
            fp->phys_info.vel_air.y = vel.y;
        }
    }
}

void func_ovl3_8015A070(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Tsutsuku2, 0.0F, 1.0F, 0U);

    fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.masterhand.tsutsuku.wait_timer = rand_u16_range(80) + 60;
}
