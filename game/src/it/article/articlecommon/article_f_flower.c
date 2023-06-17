#include "article.h"
#include "item.h"
#include "fighter.h"

bool32 jtgt_ovl3_80175B20(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATFFLOWER_GRAVITY, ATFFLOWER_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80175B5C(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80175BE4);

    return FALSE;
}

bool32 jtgt_ovl3_80175B84(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.0F, 0.5F, func_ovl3_80175BB0);
}

extern ArticleStatusDesc Article_F_Flower_Status[];

void func_ovl3_80175BB0(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_F_Flower_Status, 0);
}

void func_ovl3_80175BE4(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    atCommon_UpdateArticleStatus(article_gobj, Article_F_Flower_Status, 1);
}

void jtgt_ovl3_80175C28(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_F_Flower_Status, 2);
}

bool32 jtgt_ovl3_80175C50(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return func_ovl3_80173DF4(article_gobj, 0.0F);
    }
    else return func_ovl3_80173B24(article_gobj, 0.0F, 0.5F, func_ovl3_80175BB0);
}

bool32 jtgt_ovl3_80175C9C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

void jtgt_ovl3_80175CC4(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_F_Flower_Status, 3);
}

bool32 jtgt_ovl3_80175CEC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return func_ovl3_80173DF4(article_gobj, 0.0F);
    }
    else return func_ovl3_80173B24(article_gobj, 0.0F, 0.5F, func_ovl3_80175BB0);
}

void jtgt_ovl3_80175D38(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_F_Flower_Status, 4);
}

extern ArticleSpawnData Article_F_Flower_Data;

GObj* jtgt_ovl3_80175D60(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = itManager_CreateItem(spawn_gobj, &Article_F_Flower_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = atGetStruct(article_gobj);

        ap->at_multi = ATFFLOWER_AMMO_MAX;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}

bool32 jtgt_ovl3_80175DDC(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80175E08(GObj *weapon_gobj)
{
    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80175E4C(GObj *weapon_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

    return FALSE;
}

extern s32 D_ovl3_8018D044; // Something to do with GFX IDs; static (.bss)

bool32 jtgt_ovl3_80175E84(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);
    Vec3f *translate;

    ip->lifetime = ATFFLOWER_AMMO_LIFETIME;

    wpMain_ReflectorInvertLR(ip, fp);

    translate = &DObjGetStruct(weapon_gobj)->translate;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, translate->x, translate->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, translate->x, translate->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);

    return FALSE;
}

extern WeaponSpawnData Item_F_Flower_Ammo_Desc;

GObj* func_ovl3_80175F48(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_F_Flower_Ammo_Desc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->phys_info.vel.x = vel->x * ip->lr;
    ip->phys_info.vel.y = vel->y;
    ip->phys_info.vel.z = vel->z;

    ip->lifetime = ATFFLOWER_AMMO_LIFETIME;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, pos->x, pos->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, pos->x, pos->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);

    return weapon_gobj;
}

extern u8 D_NF_00000360;
extern ArticleSpawnData D_ovl3_80189C60;

void func_ovl3_8017604C(GObj *fighter_gobj, Vec3f *pos, s32 index, s32 ammo_sub)
{
    Article_Struct *ap = atGetStruct(ftGetStruct(fighter_gobj)->item_hold);
    Vec3f vel;
    f32 *flame_vel = (f32*)((uintptr_t)*D_ovl3_80189C60.p_file + (uintptr_t)&D_NF_00000360); // Linker thing

    vel.x = cosf(flame_vel[index]) * ATFFLOWER_AMMO_VEL;
    vel.y = __sinf(flame_vel[index]) * ATFFLOWER_AMMO_VEL;
    vel.z = 0.0F;

    func_ovl3_80175F48(fighter_gobj, pos, &vel);

    ap->at_multi -= ammo_sub;
}