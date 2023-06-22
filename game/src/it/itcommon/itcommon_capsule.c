#include "item.h"

// 0x80173F90
bool32 itCapsule_AFall_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_80172558(ip, ATCAPSULE_GRAVITY, ATCAPSULE_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

// 0x80173FCC
bool32 itCapsule_GWait_ProcMap(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80174098);

    return FALSE;
}

// 0x80173FF4
bool32 itCapsule_Default_ProcDamage(GObj *item_gobj)
{
    if (func_ovl3_801730D4(item_gobj) != FALSE)
    {
        return TRUE;
    }
    else func_ovl3_80174428(item_gobj);

    return FALSE;
}

// 0x80174030
bool32 itCapsule_AFall_ProcMap(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.4F, func_ovl3_80174064);
}

extern itStatusDesc Article_Capsule_Status[]; // Capsule states

void func_ovl3_80174064(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Capsule_Status, 0);
}

void func_ovl3_80174098(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ip);

    ip->is_damage_all = TRUE;

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    itMain_SetItemStatus(item_gobj, Article_Capsule_Status, 1);
}

void jtgt_ovl3_801740FC(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Capsule_Status, 2);
}

bool32 jtgt_ovl3_80174124(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_80172558(ip, ATCAPSULE_GRAVITY, ATCAPSULE_T_VEL);
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
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_damage_all = TRUE;

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    itMain_SetItemStatus(item_gobj, Article_Capsule_Status, 3);
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
    itMain_SetItemStatus(item_gobj, Article_Capsule_Status, 4);
}

extern u8 D_NF_00000098;

extern itCreateDesc Article_Capsule_Data;

bool32 jtgt_ovl3_80174270(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->it_multi++;

    if (ip->it_multi == 6)
    {
        return TRUE;
    }
    itMain_UpdateHitEvent(item_gobj, (itHitEvent*)((uintptr_t)*Article_Capsule_Data.p_file + &D_NF_00000098)); // Linker thing

    return FALSE;
}

GObj* jtgt_ovl3_801742CC(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Capsule_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ip = itGetStruct(item_gobj);

        ip->x2D3_flag_b5 = TRUE;

        ip->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ip);
    }
    return item_gobj;
}

void func_ovl3_80174340(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->it_multi = 0;
    ip->item_event_index = 0;
    ip->item_hit.hit_sfx = 1;
    ip->item_hit.stale = ARTICLE_STALE_DEFAULT;

    func_800269C0(1);

    ip->item_hit.can_rehit_item = TRUE;
    ip->item_hit.can_hop = FALSE;
    ip->item_hit.can_reflect = FALSE;

    ip->item_hit.element = gmHitCollision_Element_Fire;

    ip->item_hit.clang = FALSE;

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_ovl3_8017279C(item_gobj);
    func_ovl3_8017275C(item_gobj);
    itMain_UpdateHitEvent(item_gobj, (itHitEvent*)((uintptr_t)*Article_Capsule_Data.p_file + &D_NF_00000098));
}

void func_ovl3_801743F4(GObj *item_gobj)
{
    func_ovl3_80174340(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Capsule_Status, 5);
}

void func_ovl3_80174428(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    Effect_Unk *ep;

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ip->phys_info.vel.x = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.z = 0.0F;

    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ep->effect_info->scale.y = ep->effect_info->scale.z = ATCAPSULE_EXPLODE_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(item_gobj)->unk_0x54 = 2;

    func_ovl3_801743F4(item_gobj);
}