#include "article.h"
#include "item.h"




bool32 func_ovl3_8017EEB0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    if (ap->at_multi == 0)
    {
        return TRUE;
    }
    if (ap->at_multi == ap->article_vars.nyars.coin_spawn_wait)
    {
        func_ovl3_8017F408(item_gobj, ap->article_vars.nyars.coin_rotate_step * ATNYARS_COIN_ANGLE_STEP);

        ap->article_vars.nyars.coin_rotate_step++;
        ap->article_vars.nyars.coin_spawn_wait = ap->at_multi - ATNYARS_COIN_SPAWN_WAIT;

        func_800269C0(0x8AU);
    }
    if (ap->article_vars.nyars.model_rotate_wait == 0)
    {
        joint->rotate.y += PI32;

        ap->article_vars.nyars.model_rotate_wait = ATNYARS_MODEL_ROTATE_WAIT;
    }
    ap->article_vars.nyars.model_rotate_wait--;

    ap->at_multi--;

    return FALSE;
}

void func_ovl3_8017EFA0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->at_multi = ATNYARS_LIFETIME;

    ap->article_vars.nyars.coin_spawn_wait = ap->at_multi - (ATNYARS_COIN_SPAWN_WAIT / 2);
    ap->article_vars.nyars.coin_rotate_step = 0;
    ap->article_vars.nyars.model_rotate_wait = ATNYARS_MODEL_ROTATE_WAIT;
}

extern itStatusDesc Article_Nyars_Status[];

void func_ovl3_8017EFC4(GObj *item_gobj)
{
    func_ovl3_8017EFA0(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_Nyars_Status, 0);
}

bool32 jtgt_ovl3_8017EFF8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->at_multi == 0)
    {
        ap->phys_info.vel.y = 0.0F;
        ap->phys_info.vel.x = 0.0F;

        func_ovl3_8017EFC4(item_gobj);

    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_8017F04C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_801737B8(item_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_0000C130;
extern intptr_t D_NF_00013624;
extern itCreateDesc Article_Nyars_Data;

GObj *jtgt_ovl3_8017F08C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Nyars_Data, pos, vel, flags);
    DObj *joint;
    Item_Struct *ap;

    if (item_gobj != NULL)
    {
        joint = DObjGetStruct(item_gobj);

        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = *pos;

        ap = itGetStruct(item_gobj);

        ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        joint->translate.y -= ap->attributes->objectcoll_bottom;

        func_8000BD1C(joint, ArticleGetPData(ap, D_NF_0000C130, D_NF_00013624), 0.0F);
    }
    return item_gobj;
}

bool32 func_ovl3_8017F17C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (ip->weapon_vars.coin.lifetime == 0)
    {
        return TRUE;
    }
    ip->weapon_vars.coin.lifetime--;

    return FALSE;
}

bool32 jtgt_ovl3_8017F1A4(GObj *weapon_gobj)
{
    func_ovl2_80100ACC(&DObjGetStruct(weapon_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_8017F1CC(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    if (ip->phys_info.vel.x > 0.0F)
    {
        ip->lr = RIGHT;
    }
    else ip->lr = LEFT;

    return FALSE;
}

bool32 jtgt_ovl3_8017F274(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    wpMain_ReflectorInvertLR(ip, fp);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern wpCreateDesc D_ovl3_8018ACF4;

GObj *func_ovl3_8017F2E4(GObj *item_gobj, u8 coin_number, f32 rotate_angle)
{
    Weapon_Struct *ip;
    GObj *weapon_gobj = wpManager_CreateWeapon(item_gobj, &D_ovl3_8018ACF4, &DObjGetStruct(item_gobj)->translate, WEAPON_MASK_SPAWN_ARTICLE);
    DObj *joint;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->weapon_vars.coin.lifetime = ATNYARS_COIN_LIFETIME;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = ATNYARS_COIN_VEL_X;

    vec3_get_euler_rotation(&ip->phys_info.vel, 4, (((coin_number * ATYNARS_COIN_ANGLE_DIFF) + rotate_angle) * PI32) / 180.0F);

    joint = DObjGetStruct(weapon_gobj);

    func_80008CC0(joint, 0x1CU, 0U);
    func_80008CC0(joint, 0x46U, 0U);

    joint->translate = DObjGetStruct(item_gobj)->translate;

    return weapon_gobj;
}

void func_ovl3_8017F408(GObj *item_gobj, f32 angle)
{
    s32 coin_count;

    for (coin_count = 0; coin_count < ATNYARS_COIN_SPAWN_MAX; coin_count++)
    {
        func_ovl3_8017F2E4(item_gobj, coin_count, angle);
    }
}