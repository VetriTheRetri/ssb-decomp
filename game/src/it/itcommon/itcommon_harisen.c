#include "item.h"



void func_ovl3_80175140(GObj *item_gobj, f32 scale)
{
    DObjGetStruct(item_gobj)->scale.x = scale;
    DObjGetStruct(item_gobj)->scale.y = scale;
    DObjGetStruct(item_gobj)->scale.z = scale;
}

bool32 jtgt_ovl3_80175160(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATHARISEN_GRAVITY, ATHARISEN_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 func_ovl3_80175198(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80175228);

    return FALSE;
}

bool32 jtgt_ovl3_801751C0(GObj *item_gobj)
{
    func_ovl3_80173B24(item_gobj, 0.0F, 0.3F, func_ovl3_801751F4);

    return FALSE;
}

extern itStatusDesc Article_Harisen_Status[];

void func_ovl3_801751F4(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Harisen_Status, 0);
}

void func_ovl3_80175228(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_Harisen_Status, 1);
}

void jtgt_ovl3_8017526C(GObj *item_gobj)
{
    DObj *joint = DObjGetStruct(item_gobj);

    func_80008CC0(joint, 0x20U, 0U);

    joint->rotate.y = 0.0F;

    itMain_SetItemStatus(item_gobj, Article_Harisen_Status, 2);
}

bool32 jtgt_ovl3_801752C0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATHARISEN_GRAVITY, ATHARISEN_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801752F8(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.0F, 0.3F, func_ovl3_801751F4);
}

bool32 jtgt_ovl3_80175328(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

void jtgt_ovl3_80175350(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Harisen_Status, 3);

    DObjGetStruct(item_gobj)->next->rotate.y = -HALF_PI32;
}

bool32 jtgt_ovl3_80175394(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.0F, 0.3F, func_ovl3_801751F4);
}

void jtgt_ovl3_801753C4(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Harisen_Status, 4);

    DObjGetStruct(item_gobj)->next->rotate.y = -HALF_PI32;
}

extern u8 D_NF_00002198;
extern s32 D_ovl3_80189A70[2];

void func_ovl3_80175408(GObj *item_gobj, s32 index) // Unused
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_8000BD8C(item_gobj, ((D_ovl3_80189A70[index] + (uintptr_t)ap->attributes->unk_0x0) - (uintptr_t)&D_NF_00002198), 0.0F); // Linker thing
    func_8000DF34(item_gobj);
}

extern itCreateDesc Article_Harisen_Data;

GObj* jtgt_ovl3_80175460(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Harisen_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        DObjGetStruct(item_gobj)->rotate.y = HALF_PI32;

        ap->is_unused_item_bool = TRUE;

        ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ap);
    }
    return item_gobj;
}