#include "item.h"

void func_ovl3_80176110(GObj *item_gobj)
{
    atCommon_CheckSetColAnimIndex(item_gobj, ATHAMMER_WEAR_COLANIM_ID, 0);
}

bool32 jtgt_ovl3_80176134(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATHAMMER_GRAVITY, ATHAMMER_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 func_ovl3_8017616C(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_801761F8);

    return FALSE;
}

bool32 jtgt_ovl3_80176194(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.5F, 0.2F, func_ovl3_801761C4);
}

extern itStatusDesc Article_Hammer_Status[];

void func_ovl3_801761C4(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Hammer_Status, 0);
}

extern itStatusDesc Article_Hammer_Status[];

void func_ovl3_801761F8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_Hammer_Status, 1);
}

void jtgt_ovl3_8017623C(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->rotate.y = 0.0F;

    itMain_SetItemStatus(item_gobj, Article_Hammer_Status, 2);
}

bool32 jtgt_ovl3_80176270(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATHAMMER_GRAVITY, ATHAMMER_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801762A8(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.5F, 0.2F, func_ovl3_801761C4);
}

bool32 jtgt_ovl3_801762D8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

void jtgt_ovl3_80176300(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Hammer_Status, 3);

    DObjGetStruct(item_gobj)->next->rotate.y = HALF_PI32;

    ftSpecialItem_BGMCheckFighters();
}

bool32 jtgt_ovl3_80176348(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.5F, 0.2F, func_ovl3_801761C4);
}

void jtgt_ovl3_80176378(GObj *item_gobj)
{
    func_ovl3_80172FBC(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Hammer_Status, 4);

    DObjGetStruct(item_gobj)->next->rotate.y = HALF_PI32;

    ftSpecialItem_BGMCheckFighters();
}

extern itCreateDesc Article_Hammer_Data;

GObj *jtgt_ovl3_801763C8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Hammer_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        DObjGetStruct(item_gobj)->rotate.y = HALF_PI32;

        ap->x2D3_flag_b5 = TRUE;

        ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ap);
    }
    return item_gobj;
}