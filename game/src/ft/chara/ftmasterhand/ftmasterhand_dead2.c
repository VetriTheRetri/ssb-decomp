#include "ftmasterhand.h"

#define QUART_PI32 0.7853982F

void func_ovl3_8015ADC0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.masterhand.dead.dead_timer--;

    if (fp->status_vars.masterhand.dead.dead_timer == 0)
    {
        fp->cb_physics = NULL;
    }
}

void func_ovl3_8015ADE8(GObj *fighter_gobj)
{
    Fighter_Struct *fp;
    f32 vel_z;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_Dead2, 0.0F, 1.0F, 0U);

    fp = FighterGetStruct(fighter_gobj);

    fp->phys_info.vel_normal.x = 0.0F;
    fp->phys_info.vel_normal.y = __sinf(QUART_PI32) * 100.0F;

    vel_z = cosf(QUART_PI32) * 100.0F;

    fp->status_vars.masterhand.dead.dead_timer = 200;

    fp->phys_info.vel_normal.z = -vel_z;
}
