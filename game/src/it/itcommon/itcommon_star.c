#include <it/item.h>
#include <gm/gmmatch.h>

itCreateDesc itCommon_Star_ItemDesc =
{
    It_Kind_Star,                           // Item Kind
    &gItemFileData,                         // Pointer to item file data?
    0x148,                                  // Offset of item attributes in file?
    0x1B,                                   // ???
    0,                                      // ???
    0,                                      // ???
    gmHitCollision_UpdateState_Disable,     // Hitbox Update State
    itStar_SDefault_ProcUpdate,             // Proc Update
    itStar_SDefault_ProcMap,                // Proc Map
    itStar_SDefault_ProcHit,                // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Damage
};

// 0x80174930
bool32 itStar_SDefault_ProcUpdate(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);

    itMain_UpdateGravityClampTVel(ap, ITSTAR_GRAVITY, ITSTAR_T_VEL);

    ap->it_multi--;

    if (ap->it_multi == 0)
    {
        itMain_RefreshHit(item_gobj);
    }
    itManager_UpdateSpin(item_gobj);

    return FALSE;
}

// 0x80174990
bool32 itStar_SDefault_ProcMap(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);
    s32 unused;
    bool32 is_collide_ground = func_ovl3_801737B8(item_gobj, MPCOLL_MASK_GROUND);

    if (itMap_CheckCollideAllRebound(item_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_RWALL | MPCOLL_MASK_LWALL), 1.0F, NULL) != FALSE)
    {
        itMain_VelSetRotateStepLR(item_gobj);
    }
    if (is_collide_ground != FALSE)
    {
        ap->phys_info.vel_air.y = ITSTAR_BOUNCE_Y;

        func_800269C0(0x35);
    }
    return FALSE;
}

// 0x80174A0C
bool32 itStar_SDefault_ProcHit(GObj *item_gobj)
{
    return TRUE;
}

// 0x80174A18
GObj* itCommon_Star_CreateItem(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    Unk_80131460_Ptr74 *unk_ptr = D_ovl2_80131460->unk_0x74;
    GObj *item_gobj;
    DObj *joint;
    itStruct *ap;
    Vec3f vel_real;
    Vec3f translate;

    vel_real.x = (pos->x < unk_ptr->unk_0x48) ? ITSTAR_VEL_X : -ITSTAR_VEL_X;
    vel_real.y = ITSTAR_BOUNCE_Y;
    vel_real.z = 0.0F;

    item_gobj = itManager_CreateItem(spawn_gobj, &itCommon_Star_ItemDesc, pos, &vel_real, flags);

    if (item_gobj != NULL)
    {
        joint = DObjGetStruct(item_gobj);

        translate = joint->translate;

        ap = item_gobj->user_data;

        ap->item_hit.interact_mask = GMHITCOLLISION_MASK_FIGHTER; // Star Man can only interact with fighters
        ap->it_multi = ITSTAR_INTERACT_DELAY;

        ap->is_unused_item_bool = TRUE;

        func_80008CC0(joint, 0x2E, 0);

        joint->rotate.z = 0.0F;

        joint->translate = translate;
    }
    return item_gobj;
}