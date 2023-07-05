#include "item.h"

bool32 func_ovl3_8017C090(GObj *item_gobj)
{
    if ((f32)FLOAT_NEG_MAX == DObjGetStruct(item_gobj)->dobj_f0)
    {
        func_ovl3_8017C0D4(item_gobj);
    }
    return FALSE;
}

extern itStatusDesc Article_POW_Status[];

void func_ovl3_8017C0D4(GObj *item_gobj)
{
    itStruct *ap;

    itMain_SetItemStatus(item_gobj, Article_POW_Status, 0);

    ap = itGetStruct(item_gobj), ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
}

bool32 func_ovl3_8017C110(GObj *item_gobj)
{
    if ((f32)FLOAT_NEG_MAX == DObjGetStruct(item_gobj)->dobj_f0)
    {
        func_ovl2_8010986C();

        return TRUE;
    }
    else return FALSE;
}

extern intptr_t D_NF_000011F8;
extern intptr_t D_NF_00001288;

bool32 func_ovl3_8017C15C(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);

    ap->proc_update = func_ovl3_8017C110;
    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_8000BD1C(DObjGetStruct(item_gobj), itGetPData(ap, D_NF_000011F8, D_NF_00001288), 0.0F); // Linker thing
    func_8000DF34(item_gobj);
    func_800269C0(0x117U);
    func_ovl2_801008F4(3);
    func_ovl2_80109B4C();

    return FALSE;
}

extern itCreateDesc Article_POW_Data;

GObj* jtgt_ovl3_8017C1E0(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_POW_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        itStruct *ap = itGetStruct(item_gobj);

        ap->item_hurt.interact_mask = GMHITCOLLISION_MASK_FIGHTER;
    }
    return item_gobj;
}
