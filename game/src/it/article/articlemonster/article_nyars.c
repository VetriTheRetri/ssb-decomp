#include "article.h"
#include "item.h"




bool32 func_ovl3_8017EEB0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return TRUE;
    }
    if (ap->at_multi == ap->article_vars.nyars.coin_spawn_wait)
    {
        func_ovl3_8017F408(article_gobj, ap->article_vars.nyars.coin_rotate_step * ATNYARS_COIN_ANGLE_STEP);

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

void func_ovl3_8017EFA0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->at_multi = ATNYARS_LIFETIME;

    ap->article_vars.nyars.coin_spawn_wait = ap->at_multi - (ATNYARS_COIN_SPAWN_WAIT / 2);
    ap->article_vars.nyars.coin_rotate_step = 0;
    ap->article_vars.nyars.model_rotate_wait = ATNYARS_MODEL_ROTATE_WAIT;
}

extern ArticleStatusDesc Article_Nyars_Status[];

void func_ovl3_8017EFC4(GObj *article_gobj)
{
    func_ovl3_8017EFA0(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Nyars_Status, 0);
}

bool32 jtgt_ovl3_8017EFF8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        ap->phys_info.vel.y = 0.0F;
        ap->phys_info.vel.x = 0.0F;

        func_ovl3_8017EFC4(article_gobj);

    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_8017F04C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_0000C130;
extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Nyars_Data;

GObj *jtgt_ovl3_8017F08C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Nyars_Data, pos, vel, flags);
    DObj *joint;
    Article_Struct *ap;

    if (article_gobj != NULL)
    {
        joint = DObjGetStruct(article_gobj);

        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = *pos;

        ap = ArticleGetStruct(article_gobj);

        ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        joint->translate.y -= ap->attributes->gfx_offset.y;

        func_8000BD1C(joint, ArticleGetPData(ap, D_NF_0000C130, D_NF_00013624), 0.0F);
    }
    return article_gobj;
}

bool32 func_ovl3_8017F17C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (ip->item_vars.coin.lifetime == 0)
    {
        return TRUE;
    }
    ip->item_vars.coin.lifetime--;

    return FALSE;
}

bool32 jtgt_ovl3_8017F1A4(GObj *item_gobj)
{
    func_ovl2_80100ACC(&DObjGetStruct(item_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_8017F1CC(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    if (ip->phys_info.vel.x > 0.0F)
    {
        ip->lr = RIGHT;
    }
    else ip->lr = LEFT;

    return FALSE;
}

bool32 jtgt_ovl3_8017F274(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern ItemStatusDesc D_ovl3_8018ACF4;

GObj *func_ovl3_8017F2E4(GObj *article_gobj, u8 rotate_step, f32 rotate_angle)
{
    Item_Struct *ip;
    GObj *item_gobj = func_ovl3_801655C8(article_gobj, &D_ovl3_8018ACF4, &DObjGetStruct(article_gobj)->translate, ITEM_MASK_SPAWN_ARTICLE);
    DObj *joint;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->item_vars.coin.lifetime = ATNYARS_COIN_LIFETIME;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = ATNYARS_COIN_VEL_X;

    vec3_get_euler_rotation(&ip->phys_info.vel, 4, (((rotate_step * 90.0F) + rotate_angle) * PI32) / 180.0F);

    joint = DObjGetStruct(item_gobj);

    func_80008CC0(joint, 0x1CU, 0U);
    func_80008CC0(joint, 0x46U, 0U);

    joint->translate = DObjGetStruct(article_gobj)->translate;

    return item_gobj;
}

void func_ovl3_8017F408(GObj *article_gobj, f32 angle)
{
    s32 coin_count;

    for (coin_count = 0; coin_count < ATNYARS_COIN_SPAWN_MAX; coin_count++)
    {
        func_ovl3_8017F2E4(article_gobj, coin_count, angle);

    }
}