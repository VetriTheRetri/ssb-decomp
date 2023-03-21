#include "article.h"
#include "item.h"
#include "fighter.h"

bool32 jtgt_ovl3_80175B20(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

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
    func_ovl3_80172EC8(article_gobj, Article_F_Flower_Status, 0);
}

void func_ovl3_80175BE4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_F_Flower_Status, 1);
}

void jtgt_ovl3_80175C28(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_F_Flower_Status, 2);
}

bool32 jtgt_ovl3_80175C50(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return func_ovl3_80173DF4(article_gobj, 0.0F);
    }
    else return func_ovl3_80173B24(article_gobj, 0.0F, 0.5F, func_ovl3_80175BB0);
}

bool32 jtgt_ovl3_80175C9C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

void jtgt_ovl3_80175CC4(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_F_Flower_Status, 3);
}

bool32 jtgt_ovl3_80175CEC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return func_ovl3_80173DF4(article_gobj, 0.0F);
    }
    else return func_ovl3_80173B24(article_gobj, 0.0F, 0.5F, func_ovl3_80175BB0);
}

void jtgt_ovl3_80175D38(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_F_Flower_Status, 4);
}

extern ArticleSpawnData Article_F_Flower_Data;

GObj* jtgt_ovl3_80175D60(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_F_Flower_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        ap->at_multi = ATFFLOWER_AMMO_MAX;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}

bool32 jtgt_ovl3_80175DDC(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80175E08(GObj *item_gobj)
{
    if (func_ovl3_80167C04(item_gobj) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80175E4C(GObj *item_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(item_gobj)->translate);

    return FALSE;
}

extern s32 D_ovl3_8018D044; // Something to do with GFX IDs; static (.bss)

bool32 jtgt_ovl3_80175E84(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);
    Vec3f *translate;

    ip->lifetime = ATFFLOWER_AMMO_LIFETIME;

    func_ovl3_801680EC(ip, fp);

    translate = &DObjGetStruct(item_gobj)->translate;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, translate->x, translate->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, translate->x, translate->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);

    return FALSE;
}

extern ItemSpawnData Item_F_Flower_Ammo_Desc;

GObj* func_ovl3_80175F48(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_F_Flower_Ammo_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->phys_info.vel.x = vel->x * ip->lr;
    ip->phys_info.vel.y = vel->y;
    ip->phys_info.vel.z = vel->z;

    ip->lifetime = ATFFLOWER_AMMO_LIFETIME;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, pos->x, pos->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, pos->x, pos->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);

    return item_gobj;
}

extern u8 D_NF_00000360;
extern ArticleSpawnData D_ovl3_80189C60;

void func_ovl3_8017604C(GObj *fighter_gobj, Vec3f *pos, s32 index, s32 ammo_sub)
{
    Article_Struct *ap = ArticleGetStruct(FighterGetStruct(fighter_gobj)->article_hold);
    Vec3f vel;
    f32 *flame_vel = (f32*)((uintptr_t)*D_ovl3_80189C60.p_file + (uintptr_t)&D_NF_00000360); // Linker thing

    vel.x = cosf(flame_vel[index]) * ATFFLOWER_AMMO_VEL;
    vel.y = __sinf(flame_vel[index]) * ATFFLOWER_AMMO_VEL;
    vel.z = 0.0F;

    func_ovl3_80175F48(fighter_gobj, pos, &vel);

    ap->at_multi -= ammo_sub;
}