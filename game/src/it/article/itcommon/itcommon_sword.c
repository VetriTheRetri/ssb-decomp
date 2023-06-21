#include "article.h"



bool32 jtgt_ovl3_80174B50(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATSWORD_GRAVITY, ATSWORD_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 func_ovl3_80174B8C(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80174C18);

    return FALSE;
}

bool32 jtgt_ovl3_80174BB4(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, func_ovl3_80174BE4);
}

extern itStatusDesc Article_Sword_Status[];

void func_ovl3_80174BE4(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_Sword_Status, 0);
}

void func_ovl3_80174C18(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    atCommon_UpdateArticleStatus(item_gobj, Article_Sword_Status, 1);
}

void jtgt_ovl3_80174C5C(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->rotate.y = 0.0F;

    atCommon_UpdateArticleStatus(item_gobj, Article_Sword_Status, 2);
}

bool32 jtgt_ovl3_80174C90(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, func_ovl3_80174BE4);
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
    atCommon_UpdateArticleStatus(item_gobj, Article_Sword_Status, 3);

    DObjGetStruct(item_gobj)->next->rotate.y = HALF_PI32;
}

void jtgt_ovl3_80174D2C(GObj *item_gobj)
{
    func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, func_ovl3_80174BE4);
}

void jtgt_ovl3_80174D5C(GObj *item_gobj)
{
    atCommon_UpdateArticleStatus(item_gobj, Article_Sword_Status, 4);

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

        ap->x2D3_flag_b5 = TRUE;

        ap->indicator_gobj = func_ovl2_80111EC0(ap);
    }
    return item_gobj;
}