#include "article.h"
#include "item.h"
#include "fighter.h"



bool32 jtgt_ovl3_801754F0(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATLGUN_GRAVITY, ATLGUN_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80175528(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_801755B8);

    return FALSE;
}

bool32 jtgt_ovl3_80175550(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.1F, func_ovl3_80175584);
}

extern ArticleStatusDesc Article_L_Gun_Status[];

void func_ovl3_80175584(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_L_Gun_Status, 0);
}

void func_ovl3_801755B8(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    atCommon_UpdateArticleStatus(article_gobj, Article_L_Gun_Status, 1);
}

void jtgt_ovl3_801755FC(GObj *article_gobj)
{
    DObjGetStruct(article_gobj)->rotate.y = 0.0F;

    atCommon_UpdateArticleStatus(article_gobj, Article_L_Gun_Status, 2);
}

bool32 jtgt_ovl3_80175630(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return func_ovl3_80173DF4(article_gobj, 0.2F);
    }
    else return func_ovl3_80173B24(article_gobj, 0.2F, 0.1F, func_ovl3_80175584);
}

bool32 jtgt_ovl3_80175684(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

void jtgt_ovl3_801756AC(GObj *article_gobj)
{
    s32 lr = ftGetStruct(atGetStruct(article_gobj)->owner_gobj)->lr;

    atCommon_UpdateArticleStatus(article_gobj, Article_L_Gun_Status, 3);

    DObjGetStruct(article_gobj)->next->rotate.y = (lr == LEFT) ? -HALF_PI32 : HALF_PI32;
}

bool32 jtgt_ovl3_8017572C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return func_ovl3_80173DF4(article_gobj, 0.2F);
    }
    else return func_ovl3_80173B24(article_gobj, 0.2F, 0.1F, func_ovl3_80175584);
}

void jtgt_ovl3_80175780(GObj *article_gobj)
{
    s32 lr = ftGetStruct(atGetStruct(article_gobj)->owner_gobj)->lr;

    atCommon_UpdateArticleStatus(article_gobj, Article_L_Gun_Status, 4);

    DObjGetStruct(article_gobj)->next->rotate.y = (lr == LEFT) ? -HALF_PI32 : HALF_PI32;
}

extern ArticleSpawnData Article_L_Gun_Data;

GObj* jtgt_ovl3_80175800(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_L_Gun_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = atGetStruct(article_gobj);

        ap->at_multi = ATLGUN_AMMO_MAX;

        DObjGetStruct(article_gobj)->rotate.y = (rand_u16() & 1) ? HALF_PI32 : -HALF_PI32;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}

// Ray Gun ammo functions

bool32 jtgt_ovl3_801758BC(GObj *item_gobj)
{
    DObj *joint = DObjGetStruct(item_gobj);

    if (joint->scale.x < ATLGUN_AMMO_CLAMP_SCALE_X)
    {
        joint->scale.x += ATLGUN_AMMO_STEP_SCALE_X;

        joint = DObjGetStruct(item_gobj); // Y tho lol

        if (ATLGUN_AMMO_CLAMP_SCALE_X < joint->scale.x)
        {
            joint->scale.x = ATLGUN_AMMO_CLAMP_SCALE_X;
        }
    }
    return FALSE;
}

bool32 jtgt_ovl3_80175914(GObj *item_gobj)
{
    if (func_ovl3_80167C04(item_gobj) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80175958(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl2_800FE068(&DObjGetStruct(item_gobj)->translate, ip->item_hit.damage);

    return TRUE;
}

bool32 jtgt_ovl3_80175988(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    return FALSE;
}

bool32 jtgt_ovl3_80175A00(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    return FALSE;
}

extern ItemSpawnData Item_L_Gun_Ammo_Desc;

GObj* func_ovl3_80175A60(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_L_Gun_Ammo_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = itGetStruct(item_gobj);

    ip->phys_info.vel.x = ip->lr * ATLGUN_AMMO_VEL_X;

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);

    return item_gobj;
}

void func_ovl3_80175AD8(GObj *fighter_gobj, Vec3f *pos)
{
    Article_Struct *ap = atGetStruct(ftGetStruct(fighter_gobj)->item_hold);

    func_ovl3_80175A60(fighter_gobj, pos);

    ap->at_multi--;
}