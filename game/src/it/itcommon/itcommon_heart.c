#include "item.h"

itCreateDesc itCommon_Heart_ItemDesc =
{
    It_Kind_Heart,                          // Item Kind
    &gItemFileData,                         // Pointer to item file data?
    0x100,                                  // Offset of item attributes in file?
    0x1B,                                   // ???
    0,                                      // ???
    0,                                      // ???
    gmHitCollision_UpdateState_Disable,     // Hitbox Update State
    itHeart_AFall_ProcUpdate,               // Proc Update
    itHeart_AFall_ProcMap,                  // Proc Map
    NULL,                                   // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Damage
};

itStatusDesc itCommon_Harisen_StatusDesc[3] =
{
    // Status 0 (Ground Wait)
    {
        NULL,                               // Proc Update
        itHeart_GWait_ProcMap,              // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 1 (Air Wait Fall)
    {
        itHeart_AFall_ProcUpdate,           // Proc Update
        itHeart_AFall_ProcMap,              // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 2 (Fighter Drop)
    {
        itHeart_AFall_ProcUpdate,           // Proc Update
        itHeart_FDrop_ProcMap,              // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    }
};

typedef enum itHeartStatus
{
    itStatus_Heart_GWait,
    itStatus_Heart_AFall,
    itStatus_Heart_FDrop

} itHeartStatus; 

// 0x801746F0
bool32 itHeart_AFall_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_80172558(ip, ATHEART_GRAVITY, ATHEART_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

// 0x80174728
bool32 itHeart_GWait_ProcMap(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, itHeart_AFall_SetStatus);

    return FALSE;
}

// 0x80174750
bool32 itHeart_AFall_ProcMap(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.1F, 0.0F, itHeart_GWait_SetStatus);
}

extern itStatusDesc itCommon_Heart_StatusDesc[];

// 0x80174780
void itHeart_GWait_SetStatus(GObj *item_gobj)
{
    itMain_SetGroundPickup(item_gobj);
    itMain_SetItemStatus(item_gobj, itCommon_Heart_StatusDesc, itStatus_Heart_GWait);
}

// 0x801747B4
void itHeart_AFall_SetStatus(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    itMap_SetAir(ip);
    itMain_SetItemStatus(item_gobj, itCommon_Heart_StatusDesc, itStatus_Heart_AFall);
}

// 0x801747F8
bool32 itHeart_FDrop_ProcMap(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.1F, 0.0F, itHeart_GWait_SetStatus);
}

// 0x80174828
void itHeart_FDrop_SetStatus(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, itCommon_Heart_StatusDesc, itStatus_Heart_FDrop);
}

// 0x80174850
GObj* itCommon_Heart_CreateItem(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &itCommon_Heart_ItemDesc, pos, vel, flags);
    DObj *joint;
    Vec3f translate;
    Item_Struct *ip;

    if (item_gobj != NULL)
    {
        joint = DObjGetStruct(item_gobj);
        ip = itGetStruct(item_gobj);
        translate = joint->translate;

        func_80008CC0(joint, 0x2E, 0);

        joint->translate = translate;

        joint->rotate.z = 0.0F;

        ip->is_unused_item_bool = TRUE;

        ip->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ip);
    }
    return item_gobj;
}