#include "item.h"

itCreateDesc itCommon_Capsule_ItemDesc = 
{
    It_Kind_Capsule,                        // Item Kind
    &gItemFileData,                         // Pointer to item file data?
    0x50,                                   // Offset of item attributes in file?
    0x1B,                                   // ???
    0,                                      // ???
    0,                                      // ???
    gmHitCollision_UpdateState_Disable,     // Hitbox Update State
    itCapsule_AFall_ProcUpdate,             // Proc Update
    itCapsule_AFall_ProcMap,                // Proc Map
    NULL,                                   // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    itCapsule_Default_ProcHit               // Proc Damage
};

itStatusDesc itCommon_Capsule_StatusDesc[6] =
{
    // Status 0 (Ground Wait)
    {
        NULL,                               // Proc Update
        itCapsule_GWait_ProcMap,            // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        itCapsule_Default_ProcHit        // Proc Damage
    },

    // Status 1 (Air Fall Wait)
    {
        itCapsule_AFall_ProcUpdate,         // Proc Update
        itCapsule_AFall_ProcMap,            // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        itCapsule_Default_ProcHit        // Proc Damage
    },

    // Status 2 (Fighter Hold)
    {
        NULL,                               // Proc Update
        NULL,                               // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 3 (Fighter Throw)
    {
        itCapsule_AThrow_ProcUpdate,        // Proc Update
        itCapsule_AThrow_ProcMap,           // Proc Map
        itCapsule_Default_ProcHit,          // Proc Hit
        itCapsule_Default_ProcHit,          // Proc Shield
        itCommon_Default_ProcHop,           // Proc Hop
        itCapsule_Default_ProcHit,          // Proc Set-Off
        itCapsule_Default_ProcHit,          // Proc Reflector
        itCapsule_Default_ProcHit           // Proc Damage
    },

    // Status 4 (Fighter Drop)
    {
        itCapsule_AFall_ProcUpdate,         // Proc Update
        itCapsule_ADrop_ProcMap,            // Proc Map
        itCapsule_Default_ProcHit,          // Proc Hit
        itCapsule_Default_ProcHit,          // Proc Shield
        itCommon_Default_ProcHop,           // Proc Hop
        itCapsule_Default_ProcHit,          // Proc Set-Off
        itCapsule_Default_ProcHit,          // Proc Reflector
        itCapsule_Default_ProcHit           // Proc Damage
    },

    // Status 5 (Fighter Hold)
    {
        itCapsule_NExplode_ProcUpdate,      // Proc Update
        NULL,                               // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    }
};

typedef enum itCapsuleStatus
{
    itStatus_Capsule_GWait,
    itStatus_Capsule_AFall,
    itStatus_Capsule_FHold,
    itStatus_Capsule_AThrow,
    itStatus_Capsule_ADrop,
    itStatus_Capsule_NExplode

} itCapsuleStatus;

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
    func_ovl3_801735A0(item_gobj, itCapsule_AFall_SetStatus);

    return FALSE;
}

// 0x80173FF4
bool32 itCapsule_Default_ProcHit(GObj *item_gobj)
{
    if (func_ovl3_801730D4(item_gobj) != FALSE)
    {
        return TRUE;
    }
    else itCapsule_NExplode_CreateGFXGotoSetStatus(item_gobj);

    return FALSE;
}

// 0x80174030
bool32 itCapsule_AFall_ProcMap(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.4F, itCapsule_GWait_SetStatus);
}

extern itStatusDesc itCommon_Capsule_StatusDesc[]; // Capsule states

// 0x80174064
void itCapsule_GWait_SetStatus(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, itCommon_Capsule_StatusDesc, itStatus_Capsule_GWait);
}

// 0x80174098
void itCapsule_AFall_SetStatus(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ip);

    ip->is_damage_all = TRUE;

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    itMain_SetItemStatus(item_gobj, itCommon_Capsule_StatusDesc, itStatus_Capsule_AFall);
}

// 0x801740FC
void itCapsule_FHold_SetStatus(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, itCommon_Capsule_StatusDesc, itStatus_Capsule_FHold);
}

// 0x80174124
bool32 itCapsule_AThrow_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_80172558(ip, ATCAPSULE_GRAVITY, ATCAPSULE_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

// 0x80174160
bool32 itCapsule_AThrow_ProcMap(GObj *item_gobj)
{
    if (func_ovl3_801737B8(item_gobj, MPCOLL_MASK_MAIN_ALL) != FALSE)
    {
        if (func_ovl3_801730D4(item_gobj) != FALSE)
        {
            return TRUE;
        }
        else itCapsule_NExplode_CreateGFXGotoSetStatus(item_gobj);
    }
    return FALSE;
}

// 0x801741B0
void itCapsule_AThrow_SetStatus(GObj *item_gobj) // Capsule gets thrown
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_damage_all = TRUE;

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    itMain_SetItemStatus(item_gobj, itCommon_Capsule_StatusDesc, itStatus_Capsule_AThrow);
}

// 0x801741F0
bool32 func_ovl3_801741F0(GObj *item_gobj) // Unused
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

// 0x80174214
bool32 itCapsule_ADrop_ProcMap(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.4F, itCapsule_GWait_SetStatus);
}

// 0x80174248
void itCapsule_ADrop_SetStatus(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, itCommon_Capsule_StatusDesc, itStatus_Capsule_ADrop);
}

extern intptr_t itCapsule_HitEvent_Offset; // D_NF_00000098

// 0x80174270
bool32 itCapsule_NExplode_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->it_multi++;

    if (ip->it_multi == ATCAPSULE_EXPLODE_FRAME_END)
    {
        return TRUE;
    }
    itMain_UpdateHitEvent(item_gobj, itGetHitEvent(itCommon_Capsule_ItemDesc, itCapsule_HitEvent_Offset)); // (itHitEvent*) ((uintptr_t)*itCommon_Capsule_ItemDesc.p_file + (intptr_t)&D_NF_00000098); Linker thing

    return FALSE;
}

GObj* itCommon_Capsule_CreateItem(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &itCommon_Capsule_ItemDesc, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ip = itGetStruct(item_gobj);

        ip->is_unused_item_bool = TRUE;

        ip->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ip);
    }
    return item_gobj;
}

// 0x80174340
void itCapsule_NExplode_InitItemVars(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->it_multi = 0;
    ip->item_event_index = 0;
    ip->item_hit.hit_sfx = 1;
    ip->item_hit.stale = ITEM_STALE_DEFAULT;

    func_800269C0(1);

    ip->item_hit.can_rehit_item = TRUE;
    ip->item_hit.can_hop = FALSE;
    ip->item_hit.can_reflect = FALSE;

    ip->item_hit.element = gmHitCollision_Element_Fire;

    ip->item_hit.clang = FALSE;

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_ovl3_8017279C(item_gobj);
    func_ovl3_8017275C(item_gobj);

    itMain_UpdateHitEvent(item_gobj, itGetHitEvent(itCommon_Capsule_ItemDesc, itCapsule_HitEvent_Offset)); // Linker thing
}

// 0x801743F4
void itCapsule_NExplode_SetStatus(GObj *item_gobj)
{
    itCapsule_NExplode_InitItemVars(item_gobj);
    itMain_SetItemStatus(item_gobj, itCommon_Capsule_StatusDesc, itStatus_Capsule_NExplode);
}

// 0x80174428
void itCapsule_NExplode_CreateGFXGotoSetStatus(GObj *item_gobj)
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

    itCapsule_NExplode_SetStatus(item_gobj);
}