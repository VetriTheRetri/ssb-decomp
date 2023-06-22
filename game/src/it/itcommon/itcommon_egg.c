#include "item.h"

bool32 jtgt_ovl3_801815C0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATEGG_GRAVITY, ATEGG_T_VEL);
    func_ovl3_801713F4(item_gobj);

    joint->next->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 func_ovl3_80181618(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_8018171C);

    return FALSE;
}

bool32 func_ovl3_80181640(GObj *item_gobj)
{
    if (func_ovl3_801730D4(item_gobj) != FALSE)
    {
        func_ovl2_801041A0(&DObjGetStruct(item_gobj)->translate);

        return TRUE;
    }
    else func_ovl3_80181B90(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80181688(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, func_ovl3_801816E0);
}

void func_ovl3_801816B8(GObj *item_gobj)
{
    DObj *joint = DObjGetStruct(item_gobj);

    joint->scale.z = 1.0F;
    joint->scale.y = 1.0F;
    joint->scale.x = 1.0F;

    joint->next->rotate.z = joint->rotate.z;
}

extern itStatusDesc Article_Egg_Status[];

void func_ovl3_801816E0(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    func_ovl3_801816B8(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Egg_Status, 0);
}

void func_ovl3_8018171C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->is_damage_all = TRUE;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_Egg_Status, 1);
}

void jtgt_ovl3_80181778(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Egg_Status, 2);
}

bool32 jtgt_ovl3_801817A0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATEGG_GRAVITY, ATEGG_T_VEL);
    func_ovl3_801713F4(item_gobj);

    joint->next->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 jtgt_ovl3_801817F8(GObj *item_gobj)
{
    if (func_ovl3_801737B8(item_gobj, MPCOLL_MASK_MAIN_ALL) != FALSE)
    {
        if (func_ovl3_801730D4(item_gobj) != FALSE)
        {
            func_ovl2_801041A0(&DObjGetStruct(item_gobj)->translate);

            return TRUE;
        }
        else func_ovl3_80181B90(item_gobj);
    }
    return FALSE;
}

void jtgt_ovl3_80181854(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_damage_all = TRUE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    itMain_SetItemStatus(item_gobj, Article_Egg_Status, 3);
}

bool32 func_ovl3_80181894(GObj *item_gobj) // Unused
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801818B8(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, func_ovl3_801816E0);
}

void jtgt_ovl3_801818E8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_damage_all = TRUE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    itMain_SetItemStatus(item_gobj, Article_Egg_Status, 4);
}

extern itCreateDesc Article_Egg_Data;
extern intptr_t D_NF_00000B14;

bool32 jtgt_ovl3_80181928(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->it_multi++;

    if (ap->it_multi == ATEGG_EXPLODE_GFX_WAIT)
    {
        func_ovl2_801041A0(&DObjGetStruct(item_gobj)->translate);

        return TRUE;
    }
    itMain_UpdateHitEvent(item_gobj, (itHitEvent*) ((uintptr_t)*Article_Egg_Data.p_file + (intptr_t)&D_NF_00000B14) ); // Linker thing

    return FALSE;
}

GObj* jtgt_ovl3_80181998(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Egg_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(item_gobj);
        Item_Struct *egg_ap = itGetStruct(item_gobj);

        egg_ap->x2D3_flag_b5 = TRUE;

        egg_ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(egg_ap);

        func_80008CC0(joint->next, 0x2EU, 0U);

        joint->translate = *pos;

        if (flags & ARTICLE_MASK_SPAWN_ARTICLE)
        {
            Item_Struct *spawn_ap = itGetStruct(spawn_gobj);

            if ((spawn_ap->it_kind == It_Kind_Mb_Lucky) && (rand_u16_range(2) == 0))
            {
                joint->next->rotate.y = PI32;

                egg_ap->phys_info.vel.x = -egg_ap->phys_info.vel.x;

                egg_ap->lr = -egg_ap->lr;
            }
        }
    }
    return item_gobj;
}

extern intptr_t D_NF_00000098;

void func_ovl3_80181AA8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->it_multi = 0;

    ap->item_event_index = 0;

    ap->item_hit.hit_sfx = 1;
    ap->item_hit.stale = ARTICLE_STALE_DEFAULT;

    func_800269C0(1U);

    ap->item_hit.can_rehit_item = TRUE;
    ap->item_hit.can_hop = FALSE;
    ap->item_hit.can_reflect = FALSE;
    ap->item_hit.clang = FALSE;
    ap->item_hit.element = gmHitCollision_Element_Fire;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_ovl3_8017279C(item_gobj);
    func_ovl3_8017275C(item_gobj);
    itMain_UpdateHitEvent(item_gobj, (itHitEvent*) ( (uintptr_t)*Article_Egg_Data.p_file + (intptr_t)&D_NF_00000098) ); // Linker thing
}

void func_ovl3_80181B5C(GObj *item_gobj)
{
    func_ovl3_80181AA8(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Egg_Status, 5);
}

void func_ovl3_80181B90(GObj *item_gobj)
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
        ep->effect_info->scale.x = ep->effect_info->scale.y = ep->effect_info->scale.z = ATEGG_EXPLODE_GFX_SCALE;
    }

    func_ovl2_801008F4(1);

    DObjGetStruct(item_gobj)->unk_0x54 = 2;

    func_ovl3_80181B5C(item_gobj);
}