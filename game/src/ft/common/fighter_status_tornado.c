#include "fighter.h"
#include "article.h"
#include "gmground.h"

void func_ovl3_801439D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.tornado.release_wait++;

    if (fp->status_vars.common.tornado.release_wait >= FTCOMMON_TORNADO_RELEASE_WAIT)
    {
        func_ovl3_80143CC4(fighter_gobj);
    }
}

void func_ovl3_80143A20(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *tornado_gobj = fp->status_vars.common.tornado.tornado_gobj;
    Vec3f pos = DObjGetStruct(tornado_gobj)->translate;
    Vec3f vel;
    f32 mul;
    f32 angle_d;
    f32 mag;
    f32 unused[2];

    angle_d = (fp->status_vars.common.tornado.release_wait * 0.016666668F);
    mul = (((400.0F * angle_d) + 100.0F) * 0.5F);

    pos.x += (mul * func_ovl0_800C78B8(F_DEG_TO_RAD(1800.0F * angle_d)));
    pos.z += (mul * bitmap_sinf(F_DEG_TO_RAD(1800.0F * angle_d)));
    pos.y += 500.0F * angle_d;

    vec3f_sub(&vel, &pos, &DObjGetStruct(fighter_gobj)->translate);

    mag = vec3f_mag(&vel);

    if (mag > 50.0F)
    {
        vec3f_scale(&vel, 50.0F / mag);
    }
    fp->phys_info.vel_air = vel;

    DObjGetStruct(fighter_gobj)->rotate.y = (fp->lr * HALF_PI32) + F_DEG_TO_RAD(1800.0F * angle_d);
}

void func_ovl3_80143BC4(GObj *fighter_gobj, GObj *tornado_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f vel;

    func_ovl2_800E823C(fighter_gobj);

    if ((fp->item_hold != NULL) && !(ArticleGetStruct(fp->item_hold)->is_light_throw))
    {
        vel.x = vel.y = vel.z = 0.0F;

        func_ovl3_80172AEC(fp->item_hold, &vel, ARTICLE_STALE_DEFAULT);
    }
    if (fp->catch_gobj != NULL)
    {
        func_ovl3_8014B330(fp->catch_gobj);

        fp->catch_gobj = NULL;
    }
    else if (fp->capture_gobj != NULL)
    {
        func_ovl3_8014AECC(fp->capture_gobj, fighter_gobj);
    }
    if (fp->ground_or_air == ground)
    {
        func_ovl2_800DEEC8(fp);
    }
    ftStatus_Update(fighter_gobj, ftStatus_Common_Tornado, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl2_800D9444(fighter_gobj);

    fp->status_vars.common.tornado.release_wait = 0;
    fp->status_vars.common.tornado.tornado_gobj = tornado_gobj;

    func_ovl2_800E8098(fp, 0x3FU);
    func_800269C0(0x11CU);
}

extern intptr_t D_NF_00000014;
extern intptr_t D_NF_000000BC;

void func_ovl3_80143CC4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GroundHazardAttributes *tornado = (GroundHazardAttributes*) (((uintptr_t)Ground_Info - (intptr_t)&D_NF_00000014) + (intptr_t)&D_NF_000000BC); // Linker thing
    f32 knockback;
    s32 damage;

    DObjGetStruct(fighter_gobj)->translate.z = 0.0F;

    knockback = func_ovl2_800E9D78(fp->percent_damage, tornado->damage, tornado->damage, tornado->knockback_weight, tornado->knockback_scale, tornado->knockback_base, fp->attributes->weight, 9, fp->offset_hit_type);

    if (func_ovl2_800E8AAC(fighter_gobj) != gmHitCollision_HitStatus_Normal)
    {
        damage = 0;
    }
    else damage = tornado->damage;

    func_ovl3_80140EE4(fighter_gobj, -1, damage, knockback, tornado->angle, fp->lr, 0, tornado->element, 0, TRUE, TRUE, TRUE);
    func_ovl2_800EAA2C(fp, 4, 4, 2, 0, 0);

    if (damage != 0)
    {
        func_ovl2_800EA248(fp, damage);
    }
    fp->tornado_wait = FTCOMMON_TORNADO_PICKUP_WAIT;
}