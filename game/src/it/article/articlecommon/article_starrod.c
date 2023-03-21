#include "article.h"
#include "item.h"
#include "fighter.h"



bool32 jtgt_ovl3_80177E80(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATSTARROD_GRAVITY, ATSTARROD_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80177EBC(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80177F4C);

    return FALSE;
}

bool32 jtgt_ovl3_80177EE4(GObj *article_gobj)
{
    func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80177F18);

    return FALSE;
}

extern ArticleStatusDesc Article_StarRod_Status;

void func_ovl3_80177F18(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_StarRod_Status, 0);
}

void func_ovl3_80177F4C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_StarRod_Status, 1);
}

void jtgt_ovl3_80177F90(GObj *article_gobj)
{
    DObjGetStruct(article_gobj)->rotate.y = 0.0F;

    func_ovl3_80172EC8(article_gobj, Article_StarRod_Status, 2);
}

bool32 jtgt_ovl3_80177FC4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATSTARROD_GRAVITY, ATSTARROD_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80178000(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80177F18);
}

bool32 jtgt_ovl3_80178030(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

void jtgt_ovl3_80178058(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_StarRod_Status, 3);

    DObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;
}

bool32 jtgt_ovl3_8017809C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return func_ovl3_80173DF4(article_gobj, 0.2F);
    }
    else return func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80177F18);
}

void jtgt_ovl3_801780F0(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_StarRod_Status, 4);
    DObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;
}

extern ArticleSpawnData Article_StarRod_Data;

GObj* jtgt_ovl3_80178134(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_StarRod_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        ap->at_multi = ATSTARROD_AMMO_MAX;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}

bool32 jtgt_ovl3_801781B0(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Vec3f pos;
    DObj *joint;

    if (ip->item_vars.star.lifetime == 0)
    {
        DObjGetStruct(item_gobj)->unk_0x54 = 2;

        func_ovl2_8010066C(&DObjGetStruct(item_gobj)->translate, 1.0F);

        return TRUE;
    }

    ip->item_vars.star.lifetime--;

    joint = DObjGetStruct(item_gobj);

    joint->rotate.z += (-0.2F * ip->lr);

    if (ip->item_vars.star.lifetime % 2)
    {
        pos.x = DObjGetStruct(item_gobj)->translate.x;
        pos.y = (s32)rand_u16_range(250) + (DObjGetStruct(item_gobj)->translate.y - 125.0F);
        pos.z = 0.0F;

        func_ovl2_800FFEA4(&pos, ip->lr * -1.0F, item_gobj);
    }
    return FALSE;
}

bool32 jtgt_ovl3_801782D4(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (func_ovl3_80167C04(item_gobj) != FALSE)
    {
        func_ovl2_80102070(&DObjGetStruct(item_gobj)->translate, ip->lr);

        func_800269C0(0x35U);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8017832C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl2_80102070(&DObjGetStruct(item_gobj)->translate, ip->lr);

    return TRUE;
}

bool32 jtgt_ovl3_8017835C(GObj *item_gobj)
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

bool32 jtgt_ovl3_80178404(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern u8 StarRod_Linker_Unk;
extern ItemSpawnData Item_StarRod_Desc;
extern uintptr_t D_ovl3_8018A1D0;

GObj *func_ovl3_80178474(GObj *fighter_gobj, Vec3f *pos, u8 is_smash)
{
    GObj *item_gobj;
    DObj *joint;
    Item_Struct *ip;

    if (is_smash == TRUE)
    {
        D_ovl3_8018A1D0 = (uintptr_t)&StarRod_Linker_Unk;
    }
    item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_StarRod_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));

    if (item_gobj == NULL)
    {
        return NULL;
    }
    joint = DObjGetStruct(item_gobj);
    ip = ItemGetStruct(item_gobj);

    ip->phys_info.vel.x = ((!(is_smash)) ? ATSTARROD_AMMO_TILT_VEL_X : ATSTARROD_AMMO_SMASH_VEL_X) * ip->lr;

    ip->item_vars.star.lifetime = (!(is_smash)) ? ATSTARROD_AMMO_TILT_LIFETIME : ATSTARROD_AMMO_SMASH_LIFETIME; // Why float lol

    func_80008CC0(joint, 0x2EU, 0U);

    joint->translate = *pos;

    joint->translate.z = 0.0F;

    return item_gobj;
}

void func_ovl3_80178594(GObj *fighter_gobj, Vec3f *pos, u8 is_smash)
{
    Article_Struct *ap = ArticleGetStruct(FighterGetStruct(fighter_gobj)->article_hold);

    func_ovl3_80178474(fighter_gobj, pos, is_smash);

    ap->at_multi--;
}