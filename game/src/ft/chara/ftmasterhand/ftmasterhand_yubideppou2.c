#include "ftmasterhand.h"

void func_ovl3_8015A600(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f vel;
    f32 magnitude;

    pos.x = DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.x + (-fp->lr * 3000.0F);
    pos.y = DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.y;
    pos.z = 0.0F;

    vec3f_sub(&vel, &pos, &DObjGetStruct(fighter_gobj)->translate);

    magnitude = vec3f_mag(&vel);

    if (magnitude < 5.0F)
    {
        fp->phys_info.vel_normal.x = vel.x;
        fp->phys_info.vel_normal.y = vel.y;
    }
    else
    {
        vec3f_normalize(&vel);
        vec3f_scale(&vel, magnitude * 0.1F);

        fp->phys_info.vel_normal.x = vel.x;
        fp->phys_info.vel_normal.y = vel.y;
    }
}

void func_ovl3_8015A6FC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.masterhand.yubideppou.wait_timer--;

    if (fp->status_vars.masterhand.yubideppou.wait_timer == 0)
    {
        func_ovl3_8015A538(fighter_gobj);
    }
    else func_ovl3_8015A600(fighter_gobj);
}

void func_ovl3_8015A748(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_Yubideppou2, 0.0F, 1.0F, 0U);

    fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.masterhand.yubideppou.wait_timer = rand_u16_range(120) + 60;
}
