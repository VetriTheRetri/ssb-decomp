#include "ftmasterhand.h"

void func_ovl3_8015A840(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_8010CF20();
        func_ovl3_8015AA34(fighter_gobj);
        func_ovl3_80158620(fighter_gobj);
    }
}

void func_ovl3_8015A890(GObj *fighter_gobj)
{
    Fighter_Struct *fp;
    f32 dist_x;

    func_ovl2_800D938C(fighter_gobj);

    fp = FighterGetStruct(fighter_gobj);

    dist_x = JObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.x - JObjGetStruct(fighter_gobj)->translate.x;

    if (ABSF(dist_x) > 40.0F)
    {
        f32 vel_x = (dist_x > 0.0F) ? 40.0F : -40.0F;

        fp->phys_info.vel_normal.x += vel_x;
    }
    else
    {
        fp->phys_info.vel_normal.x += dist_x;
    }
    func_ovl3_80158528(fighter_gobj);
}

void func_ovl3_8015A950(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f *translate;
    Vec3f sp34;
    Vec3f sp28;

    fp->lr = CENTER;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_OkuPunch2, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    translate = &JObjGetStruct(fighter_gobj)->translate;

    translate->x = fp->status_vars.masterhand.okupunch.pos.x;
    translate->y = fp->status_vars.masterhand.okupunch.pos.y;
    translate->z = -15000.0F;

    sp34.x = 0.0F;
    sp34.y = 0.0F;
    sp34.z = 0.0F;

    sp28.x = 0.0F;
    sp28.y = 1000.0F;
    sp28.z = 7000.0F;

    func_ovl2_8010D0A4(&sp34, &sp28);
    func_ovl3_80158604(fighter_gobj);
}
