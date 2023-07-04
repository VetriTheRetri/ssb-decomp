#include "item.h"

bool32 jtgt_ovl3_80174B50(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    itMain_UpdatePhysicsAir(ap, ITSWORD_GRAVITY, ITSWORD_T_VEL);
    itManager_UpdateSpin(item_gobj);

    return FALSE;
}

bool32 func_ovl3_80174B8C(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80174C18);

    return FALSE;
}

bool32 jtgt_ovl3_80174BB4(GObj *item_gobj)
{
    return itMap_CheckMapCollideThrownLanding(item_gobj, 0.2F, 0.5F, func_ovl3_80174BE4);
}

extern itStatusDesc Article_Sword_Status[];

void func_ovl3_80174BE4(GObj *item_gobj)
{
    itMain_SetGroundPickup(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Sword_Status, 0);
}

void func_ovl3_80174C18(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    itMap_SetAir(ap);
    itMain_SetItemStatus(item_gobj, Article_Sword_Status, 1);
}

void jtgt_ovl3_80174C5C(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->rotate.y = 0.0F;

    itMain_SetItemStatus(item_gobj, Article_Sword_Status, 2);
}

bool32 jtgt_ovl3_80174C90(GObj *item_gobj)
{
    return itMap_CheckMapCollideThrownLanding(item_gobj, 0.2F, 0.5F, func_ovl3_80174BE4);
}

bool32 jtgt_ovl3_80174CC0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

void jtgt_ovl3_80174CE8(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Sword_Status, 3);

    DObjGetStruct(item_gobj)->next->rotate.y = HALF_PI32;
}

void jtgt_ovl3_80174D2C(GObj *item_gobj)
{
    itMap_CheckMapCollideThrownLanding(item_gobj, 0.2F, 0.5F, func_ovl3_80174BE4);
}

void jtgt_ovl3_80174D5C(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Sword_Status, 4);

    DObjGetStruct(item_gobj)->next->rotate.y = HALF_PI32;
}

extern itCreateDesc Article_Sword_Data;

GObj* jtgt_ovl3_80174DA0(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Sword_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        DObjGetStruct(item_gobj)->rotate.y = HALF_PI32;

        ap->is_unused_item_bool = TRUE;

        ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ap);
    }
    return item_gobj;
}