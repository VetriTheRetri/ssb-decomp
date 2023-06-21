#include "article.h"

bool32 jtgt_ovl3_80173F90(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATCAPSULE_GRAVITY, ATCAPSULE_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 func_ovl3_80173FCC(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80174098);

    return FALSE;
}

bool32 func_ovl3_80173FF4(GObj *item_gobj)
{
    if (func_ovl3_801730D4(item_gobj) != FALSE)
    {
        return TRUE;
    }
    else func_ovl3_80174428(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80174030(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.4F, func_ovl3_80174064);
}

extern itStatusDesc Article_Capsule_Status[]; // Capsule states

void func_ovl3_80174064(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_Capsule_Status, 0);
}

void func_ovl3_80174098(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);

    ap->is_damage_all = TRUE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    atCommon_UpdateArticleStatus(item_gobj, Article_Capsule_Status, 1);
}

void jtgt_ovl3_801740FC(GObj *item_gobj)
{
    atCommon_UpdateArticleStatus(item_gobj, Article_Capsule_Status, 2);
}

bool32 jtgt_ovl3_80174124(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATCAPSULE_GRAVITY, ATCAPSULE_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80174160(GObj *item_gobj)
{
    if (func_ovl3_801737B8(item_gobj, MPCOLL_MASK_MAIN_ALL) != FALSE)
    {
        if (func_ovl3_801730D4(item_gobj) != FALSE)
        {
            return TRUE;
        }
        else func_ovl3_80174428(item_gobj);
    }
    return FALSE;
}

void jtgt_ovl3_801741B0(GObj *item_gobj) // Capsule gets thrown
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_damage_all = TRUE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    atCommon_UpdateArticleStatus(item_gobj, Article_Capsule_Status, 3);
}

bool32 func_ovl3_801741F0(GObj *item_gobj) // Unused
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80174214(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.4F, func_ovl3_80174064);
}

void jtgt_ovl3_80174248(GObj *item_gobj)
{
    atCommon_UpdateArticleStatus(item_gobj, Article_Capsule_Status, 4);
}

extern u8 D_NF_00000098;

extern itCreateDesc Article_Capsule_Data;

bool32 jtgt_ovl3_80174270(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->at_multi++;

    if (ap->at_multi == 6)
    {
        return TRUE;
    }
    func_ovl3_80173180(item_gobj, (ArticleHitEvent*)((uintptr_t)*Article_Capsule_Data.p_file + &D_NF_00000098)); // Linker thing

    return FALSE;
}

GObj* jtgt_ovl3_801742CC(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *gobj = itManager_CreateItem(spawn_gobj, &Article_Capsule_Data, pos, vel, flags);

    if (gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(gobj);

        ap->x2D3_flag_b5 = TRUE;

        ap->indicator_gobj = func_ovl2_80111EC0(ap);
    }
    return gobj;
}

void func_ovl3_80174340(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->at_multi = 0;
    ap->x340_flag_b0123 = 0;
    ap->item_hit.hit_sfx = 1;
    ap->item_hit.stale = ARTICLE_STALE_DEFAULT;

    func_800269C0(1U);

    ap->item_hit.can_rehit_item = TRUE;
    ap->item_hit.can_hop = FALSE;
    ap->item_hit.can_reflect = FALSE;

    ap->item_hit.element = gmHitCollision_Element_Fire;

    ap->item_hit.clang = FALSE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_ovl3_8017279C(item_gobj);
    func_ovl3_8017275C(item_gobj);
    func_ovl3_80173180(item_gobj, (ArticleHitEvent*)((uintptr_t)*Article_Capsule_Data.p_file + &D_NF_00000098));
}

void func_ovl3_801743F4(GObj *item_gobj)
{
    func_ovl3_80174340(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_Capsule_Status, 5);
}

void func_ovl3_80174428(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    Effect_Unk *ep;

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ep->effect_info->scale.y = ep->effect_info->scale.z = ATCAPSULE_EXPLODE_SCALE;
    }
    func_ovl2_801008F4(1);
    DObjGetStruct(item_gobj)->unk_0x54 = 2;
    func_ovl3_801743F4(item_gobj);
}