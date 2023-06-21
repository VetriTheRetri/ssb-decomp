#include "article.h"

void func_ovl3_80177060(GObj *item_gobj, u8 arg1)
{
    s32 unused;
    DObj *joint = DObjGetStruct(item_gobj);
    Item_Struct *ap = itGetStruct(item_gobj);
    Effect_Unk *ep;

    func_ovl3_80177218(item_gobj);

    ep = func_ovl2_801005C8(&joint->translate); // WARNING: Actually some sprite struct

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ATBOMBHEI_EXPLODE_SCALE;
        ep->effect_info->scale.y = ATBOMBHEI_EXPLODE_SCALE;
        ep->effect_info->scale.z = ATBOMBHEI_EXPLODE_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(item_gobj)->unk_0x54 = 2;

    ap->item_hit.hit_sfx = 1;

    func_ovl3_8017275C(item_gobj);
    func_ovl3_8017279C(item_gobj);
    func_ovl3_80177C30(item_gobj);
}

extern u8 BombHei_Motion_WalkRight;
extern u8 BombHei_Motion_Data;
extern u8 BombHei_Motion_WalkLeft;

void func_ovl3_80177104(GObj *item_gobj, u8 lr)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    void *dll = (void*)((uintptr_t)((uintptr_t)ap->attributes->unk_0x0 - (uintptr_t)&BombHei_Motion_Data) + &BombHei_Motion_WalkLeft); // Linker thing
    void *dlr = (void*)((uintptr_t)((uintptr_t)ap->attributes->unk_0x0 - (uintptr_t)&BombHei_Motion_Data) + &BombHei_Motion_WalkRight); // Linker thing

    if (lr != CENTER)
    {
        ap->lr = RIGHT;
        ap->phys_info.vel.x = ATBOMBHEI_WALK_VEL_X;

        joint->display_list = dlr;
    }
    else
    {
        ap->lr = LEFT;
        ap->phys_info.vel.x = -ATBOMBHEI_WALK_VEL_X;

        joint->display_list = dll;
    }
}

void func_ovl3_80177180(GObj *item_gobj, u8 is_explode)
{
    s32 unused[4];
    Item_Struct *ap = itGetStruct(item_gobj);
    atCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(item_gobj);

    if ((ap->coll_data.coll_mask & MPCOLL_MASK_GROUND) || (is_explode != FALSE))
    {
        Vec3f pos = joint->translate;

        pos.y += attributes->objectcoll_bottom;

        func_ovl2_800FF3F4(&pos, ap->lr, 1.0F);
    }
}

void func_ovl3_80177208(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
}

void func_ovl3_80177218(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;
}

bool32 jtgt_ovl3_80177224(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATBOMBHEI_GRAVITY, ATBOMBHEI_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

s32 func_ovl3_80177260(GObj *item_gobj)
{
    GObj *fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];
    Vec3f *translate;
    s32 lr;
    s32 ret_lr = 0;
    Vec3f dist;
    DObj *aj = DObjGetStruct(item_gobj);

    if (fighter_gobj != NULL)
    {
        translate = &aj->translate;

        do
        {
            DObj *fj = DObjGetStruct(fighter_gobj);

            vec3f_sub(&dist, translate, &fj->translate);

            lr = (dist.x < 0.0F) ? LEFT : RIGHT;

            fighter_gobj = fighter_gobj->group_gobj_next;

            ret_lr += lr;
        }
        while (fighter_gobj != NULL);
    }
    return ret_lr; // I assume this is getting the number of players on either side of the Bob-Omb so it starts moving towards the most crowded area
}

bool32 jtgt_ovl3_80177304(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    void *dll = ((uintptr_t)ap->attributes->unk_0x0 - (uintptr_t)&BombHei_Motion_Data) + &BombHei_Motion_WalkLeft; // Linker thing
    s32 lr;

    if (ap->at_multi == ATBOMBHEI_WALK_WAIT)
    {
        lr = func_ovl3_80177260(item_gobj);

        if (lr == 0)
        {
            lr = rand_u16_range(2) - 1;
        }
        if (lr < 0)
        {
            ap->lr = RIGHT;
            ap->phys_info.vel.x = ATBOMBHEI_WALK_VEL_X;
        }
        else
        {
            ap->phys_info.vel.x = -ATBOMBHEI_WALK_VEL_X;

            joint->display_list = dll;

            ap->lr = LEFT;
        }
        func_ovl3_801779A8(item_gobj);
    }
    ap->at_multi++;

    return FALSE;
}

bool32 jtgt_ovl3_801773F4(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_801774B0);

    return FALSE;
}

bool32 jtgt_ovl3_8017741C(GObj *item_gobj)
{
    func_ovl3_801779E4(item_gobj, 1);

    return FALSE;
}

bool32 jtgt_ovl3_80177440(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.4F, 0.3F, func_ovl3_80177474);
}

extern itStatusDesc Article_BombHei_Status[];

void func_ovl3_80177474(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    func_ovl3_80177208(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_BombHei_Status, 0);
}

void func_ovl3_801774B0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80177208(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_BombHei_Status, 1);
}

void jtgt_ovl3_801774FC(GObj *item_gobj)
{
    func_ovl3_80177218(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_BombHei_Status, 2);
}

bool32 jtgt_ovl3_80177530(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATBOMBHEI_GRAVITY, ATBOMBHEI_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8017756C(GObj *item_gobj)
{
    return func_ovl3_80173E58(item_gobj, func_ovl3_80177B78);
}

void jtgt_ovl3_80177590(GObj *item_gobj)
{
    func_ovl3_80177208(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_BombHei_Status, 3);
}

bool32 jtgt_ovl3_801775C4(GObj *item_gobj)
{
    return func_ovl3_80173E58(item_gobj, func_ovl3_80177B78);
}

void func_ovl3_801775E8(GObj *item_gobj)
{
    func_ovl3_80177208(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_BombHei_Status, 4);
}

void func_ovl3_8017761C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    if (ap->article_vars.bombhei.smoke_delay == 0)
    {
        Vec3f translate = joint->translate;

        translate.y += 120.0F;

        func_ovl2_800FF048(&translate, ap->lr, 1.0F);

        ap->article_vars.bombhei.smoke_delay = ATBOMBHEI_SMOKE_WAIT;
    }
    ap->article_vars.bombhei.smoke_delay--;
}

bool32 jtgt_ovl3_801776A0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    atCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f pos;

    func_ovl3_8017761C(item_gobj);

    if (func_ovl2_800FC67C(ap->coll_data.ground_line_id) != FALSE)
    {
        if (ap->lr == LEFT)
        {
            mpCollision_GetLREdgeLeft(ap->coll_data.ground_line_id, &pos);

            if ((joint->translate.x - attributes->objectcoll_width) <= pos.x)
            {
                func_ovl3_80177104(item_gobj, 1);
            }
        }
        else
        {
            mpCollision_GetLREdgeRight(ap->coll_data.ground_line_id, &pos);

            if (pos.x <= (joint->translate.x + attributes->objectcoll_width))
            {
                func_ovl3_80177104(item_gobj, 0);
            }
        }
    }
    if (ap->at_multi == ATBOMBHEI_FLASH_WAIT)
    {
        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.y = 0.0F;
        ap->phys_info.vel.x = 0.0F;

        func_ovl3_80177D60(item_gobj);
    }
    ap->at_multi++;

    return FALSE;
}

bool32 jtgt_ovl3_801777D8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_801735A0(item_gobj, func_ovl3_801775E8);

    if (ap->coll_data.coll_mask & MPCOLL_MASK_RWALL)
    {
        func_ovl3_80177104(item_gobj, 0);
    }
    if (ap->coll_data.coll_mask & MPCOLL_MASK_LWALL)
    {
        func_ovl3_80177104(item_gobj, 1);
    }
    return FALSE;
}

extern u8 BombHei_Motion_Unk;

void func_ovl3_80177848(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    atCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(item_gobj);
    void *texture;
    s32 unused;
    Vec3f pos;

    ap->is_allow_pickup = FALSE;

    ap->at_multi = 0;

    ap->article_vars.bombhei.smoke_delay = ATBOMBHEI_SMOKE_WAIT;

    func_ovl3_8017275C(item_gobj);

    texture = ((uintptr_t)ap->attributes->unk_0x0 - (uintptr_t)&BombHei_Motion_Data) + &BombHei_Motion_Unk; // Linker thing

    func_8000BD54(joint->mobj, texture, 0.0F); // Set texture animation?

    func_8000DF34(item_gobj);

    if (func_ovl2_800FC67C(ap->coll_data.ground_line_id) != FALSE)
    {
        if (ap->lr == LEFT)
        {
            mpCollision_GetLREdgeLeft(ap->coll_data.ground_line_id, &pos);

            if ((joint->translate.x - attributes->objectcoll_width) <= pos.x)
            {
                func_ovl3_80177104(item_gobj, 1);
            }
        }
        else
        {
            mpCollision_GetLREdgeRight(ap->coll_data.ground_line_id, &pos);

            if (pos.x <= (joint->translate.x + attributes->objectcoll_width))
            {
                func_ovl3_80177104(item_gobj, 0);
            }
        }
    }
    func_ovl3_8017279C(item_gobj);

    func_800269C0(0x2DU);
}

void func_ovl3_801779A8(GObj *item_gobj)
{
    func_ovl3_80177208(item_gobj);
    func_ovl3_80177848(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_BombHei_Status, 5);
}

void func_ovl3_801779E4(GObj *item_gobj, u8 arg1)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->phys_info.vel.z = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.x = 0.0F;

    func_ovl3_80177060(item_gobj, arg1);

    func_800269C0(1U);
}

extern intptr_t BombHei_Event;
extern itCreateDesc Article_BombHei_Data;

void func_ovl3_80177A24(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    ArticleHitEvent *ev = (ArticleHitEvent*) ((uintptr_t)*Article_BombHei_Data.p_file + (intptr_t)&BombHei_Event); // Linker thing

    if (ap->at_multi == ev[ap->x340_flag_b0123].timer)
    {
        ap->item_hit.angle = ev[ap->x340_flag_b0123].angle;
        ap->item_hit.damage = ev[ap->x340_flag_b0123].damage;
        ap->item_hit.size = ev[ap->x340_flag_b0123].size;

        ap->item_hit.can_rehit_item = TRUE;
        ap->item_hit.can_hop = FALSE;
        ap->item_hit.can_reflect = FALSE;
        ap->item_hit.clang = FALSE;

        ap->item_hit.element = gmHitCollision_Element_Fire;

        ap->x340_flag_b0123++;

        if (ap->x340_flag_b0123 == 4)
        {
            ap->x340_flag_b0123 = 3;
        }
    }
}

bool32 jtgt_ovl3_80177B10(GObj *item_gobj)
{
    func_ovl3_80177180(item_gobj, 0);
    func_ovl3_801779E4(item_gobj, 1);

    return FALSE;
}

bool32 jtgt_ovl3_80177B44(GObj *item_gobj)
{
    func_ovl3_80177180(item_gobj, 1);
    func_ovl3_801779E4(item_gobj, 0);

    return FALSE;
}

void func_ovl3_80177B78(GObj *item_gobj)
{
    func_ovl3_80177208(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_BombHei_Status, 6);
}

void func_ovl3_80177BAC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->at_multi = 0;

    ap->item_hit.stale = ARTICLE_STALE_DEFAULT;

    ap->x340_flag_b0123 = 0;

    func_ovl3_80177A24(item_gobj);
}

bool32 jtgt_ovl3_80177BE8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80177A24(item_gobj);

    ap->at_multi++;

    if (ap->at_multi == ATBOMBHEI_EXPLODE_LIFETIME)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80177C30(GObj *item_gobj)
{
    func_ovl3_80177BAC(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_BombHei_Status, 7);
}

bool32 jtgt_ovl3_80177C64(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_8017761C(item_gobj);

    if (ap->at_multi == ATBOMBHEI_EXPLODE_WAIT)
    {
        func_ovl3_80177180(item_gobj, 1);
        func_ovl3_801779E4(item_gobj, 0);
        func_800269C0(1U);
    }
    ap->at_multi++;

    return FALSE;
}

bool32 jtgt_ovl3_80177D00(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_801775E8);

    return FALSE;
}

void func_ovl3_80177D28(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    ap->at_multi = 0;

    joint->mobj->unk_mobj_0x94 = 0;

    atCommon_CheckSetColAnimIndex(item_gobj, ATBOMBHEI_EXPLODE_COLANIM_ID, ATBOMBHEI_EXPLODE_COLANIM_DURATION);
}

void func_ovl3_80177D60(GObj *item_gobj)
{
    func_ovl3_80177208(item_gobj);
    func_ovl3_80177D28(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_BombHei_Status, 8);
}

GObj *jtgt_ovl3_80177D9C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_BombHei_Data, pos, vel, flags);
    DObj *joint;
    Item_Struct *ap;
    Vec3f translate;

    if (item_gobj != NULL)
    {
        joint = DObjGetStruct(item_gobj);

        translate = joint->translate;

        ap = itGetStruct(item_gobj);

        ap->at_multi = 0;

        func_ovl3_8017279C(item_gobj);

        func_80008CC0(joint, 0x2EU, 0U);

        joint->translate = translate;

        ap->x2D3_flag_b5 = TRUE;

        joint->rotate.z = 0.0F;

        ap->indicator_gobj = func_ovl2_80111EC0(ap);
    }
    return item_gobj;
}