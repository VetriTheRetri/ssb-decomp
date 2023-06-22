#include "item.h"
#include "fighter.h"
#include "gmmatch.h"

bool32 jtgt_ovl3_80176450(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATMSBOMB_GRAVITY, ATMSBOMB_T_VEL);
    func_ovl3_801713F4(item_gobj);

    joint->next->unk_0x8->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 func_ovl3_801764A8(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80176538);

    return FALSE;
}

bool32 jtgt_ovl3_801764D0(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.4F, 0.3F, func_ovl3_80176504);
}

extern itStatusDesc Article_MSBomb_Status[];

void func_ovl3_80176504(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_MSBomb_Status, 0);
}

void func_ovl3_80176538(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_MSBomb_Status, 1);
}

void jtgt_ovl3_8017657C(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_MSBomb_Status, 2);
}

bool32 jtgt_ovl3_801765A4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATMSBOMB_GRAVITY, ATMSBOMB_T_VEL);
    func_ovl3_801713F4(item_gobj);

    joint->next->unk_0x8->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 jtgt_ovl3_801765FC(GObj *item_gobj)
{
    return func_ovl3_80173E58(item_gobj, func_ovl3_80176B94);
}

bool32 jtgt_ovl3_80176620(GObj *item_gobj)
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

void jtgt_ovl3_80176644(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->coll_data.object_coll.top = ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.center = 0.0F;
    ap->coll_data.object_coll.bottom = -ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.width = ATMSBOMB_COLL_SIZE;

    itMain_SetItemStatus(item_gobj, Article_MSBomb_Status, 3);
}

bool32 jtgt_ovl3_80176694(GObj *item_gobj)
{
    return func_ovl3_80173E58(item_gobj, func_ovl3_80176B94);
}

void jtgt_ovl3_801766B8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->coll_data.object_coll.top = ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.center = 0.0F;
    ap->coll_data.object_coll.bottom = -ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.width = ATMSBOMB_COLL_SIZE;

    itMain_SetItemStatus(item_gobj, Article_MSBomb_Status, 4);
}

void func_ovl3_80176708(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    Coll_Data *coll_data = &ap->coll_data;
    Vec3f angle;
    DObj *joint = DObjGetStruct(item_gobj);


    if ((coll_data->coll_mask & MPCOLL_MASK_CEIL) || (coll_data->coll_mask & MPCOLL_MASK_GROUND))
    {

        if (coll_data->coll_mask & MPCOLL_MASK_CEIL)
        {
            angle = coll_data->ceil_angle;

            ap->attach_line_id = coll_data->ceil_line_id;
        }
        if (coll_data->coll_mask & MPCOLL_MASK_GROUND)
        {
            angle = coll_data->ground_angle;

            ap->attach_line_id = coll_data->ground_line_id;
        }
    }
    else
    {
        if (coll_data->coll_mask & MPCOLL_MASK_RWALL)
        {
            angle = coll_data->rwall_angle;

            ap->attach_line_id = coll_data->rwall_line_id;
        }
        if (coll_data->coll_mask & MPCOLL_MASK_LWALL)
        {
            angle = coll_data->lwall_angle;

            ap->attach_line_id = coll_data->lwall_line_id;
        }
    }
    joint->rotate.z = atan2f(angle.y, angle.x) - HALF_PI32;
}

void func_ovl3_80176840(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    ap->coll_data.object_coll.top = ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.center = 0.0F;
    ap->coll_data.object_coll.bottom = -ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.width = ATMSBOMB_COLL_SIZE;

    ap->phys_info.vel.z = 0;
    ap->phys_info.vel.y = 0;
    ap->phys_info.vel.x = 0;

    joint->next->unk_0x54 = 0;
    joint->next->unk_0x8->unk_0x54 = 2;

    func_ovl3_80176708(item_gobj);

    ap->is_attach_surface = TRUE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    if ((ap->port_id != -1U) && (ap->port_id != GMMATCH_PLAYERS_MAX)) // Macro might be off though
    {
        GObj *fighter_gobj = Match_Info->player_block[ap->port_id].fighter_gobj;

        if (fighter_gobj != NULL)
        {
            func_ovl2_800E806C(ftGetStruct(fighter_gobj), 6, 0);
        }
    }
    func_800269C0(0x2CU);

    func_ovl3_8017279C(item_gobj);
}

void func_ovl3_80176934(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    itCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(item_gobj);
    s32 unused[4];

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        Vec3f translate = joint->translate;

        translate.y += attributes->objectcoll_bottom;

        func_ovl2_800FF3F4(&translate, ap->lr, 1.0F);
    }
}

void func_ovl3_801769AC(GObj *item_gobj, bool32 is_fighter)
{
    Effect_Unk *ep;
    DObj *joint = DObjGetStruct(item_gobj);

    if (is_fighter != FALSE)
    {
        func_ovl3_80176934(item_gobj);
    }
    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ATMSBOMB_EXPLODE_SCALE;
        ep->effect_info->scale.y = ATMSBOMB_EXPLODE_SCALE;
        ep->effect_info->scale.z = ATMSBOMB_EXPLODE_SCALE;
    }
    func_ovl2_801008F4(1);
    func_ovl3_8017275C(item_gobj);
    func_ovl3_80176F2C(item_gobj);

    DObjGetStruct(item_gobj)->unk_0x54 = 2;
}

bool32 jtgt_ovl3_80176A34(GObj *item_gobj)
{
    func_800269C0(1U);
    func_ovl3_801769AC(item_gobj, FALSE);

    return FALSE;
}

bool32 jtgt_ovl3_80176A68(GObj *item_gobj)
{
    s32 unused[2];
    GObj *fighter_gobj;
    Vec3f *translate;
    Vec3f dist;
    Vec3f f_pos;
    DObj *aj = DObjGetStruct(item_gobj);
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->it_multi < ATMSBOMB_DETECT_FIGHTER_DELAY)
    {
        ap->it_multi++;
    }
    else
    {
        fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

        translate = &aj->translate;

        if (fighter_gobj != NULL)
        {
            do
            {
                Fighter_Struct *fp = ftGetStruct(fighter_gobj);
                DObj *fj = DObjGetStruct(fighter_gobj);
                f32 var = fp->attributes->object_coll.top * 0.5F;

                f_pos = fj->translate;

                f_pos.y += var;

                vec3f_sub(&dist, &f_pos, translate);

                if ((SQUARE(dist.x) + SQUARE(dist.y) + SQUARE(dist.z)) < ATMSBOMB_DETECT_FIGHTER_RADIUS)
                {
                    func_ovl3_801769AC(item_gobj, TRUE);
                }
                fighter_gobj = fighter_gobj->group_gobj_next;
            } 
            while (fighter_gobj != NULL);
        }
    }
    return FALSE;
}

void func_ovl3_80176B94(GObj *item_gobj)
{
    func_ovl3_80176840(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_MSBomb_Status, 5);
}

bool32 jtgt_ovl3_80176BC8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl2_800FC67C(ap->attach_line_id) == FALSE)
    {
        ap->is_attach_surface = FALSE;

        func_ovl3_80176E68(item_gobj);
    }
    return FALSE;
}

extern u8 D_NF_00000404;
extern itCreateDesc Article_MSBomb_Data;

void func_ovl3_80176C14(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    itHitEvent *ev = (itHitEvent*) ((uintptr_t)*Article_MSBomb_Data.p_file + &D_NF_00000404);

    if (ap->it_multi == ev[ap->item_event_index].timer)
    {
        ap->item_hit.angle = ev[ap->item_event_index].angle;
        ap->item_hit.damage = ev[ap->item_event_index].damage;
        ap->item_hit.size = ev[ap->item_event_index].size;

        ap->item_hit.can_rehit_item = TRUE;
        ap->item_hit.can_hop = FALSE;
        ap->item_hit.can_reflect = FALSE;
        ap->item_hit.clang = FALSE;

        ap->item_hit.element = gmHitCollision_Element_Fire;

        ap->item_event_index++;

        if (ap->item_event_index == 4)
        {
            ap->item_event_index = 3;
        }
    }
}

void func_ovl3_80176D00(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_8017279C(item_gobj);
}

bool32 jtgt_ovl3_80176D2C(GObj *item_gobj)
{
    s32 unused[2];
    GObj *fighter_gobj;
    Vec3f *translate;
    Vec3f dist;
    Vec3f f_pos;
    DObj *aj = DObjGetStruct(item_gobj);
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATMSBOMB_GRAVITY, ATMSBOMB_T_VEL);

    if (ap->it_multi < ATMSBOMB_DETECT_FIGHTER_DELAY)
    {
        ap->it_multi++;
    }
    else
    {
        fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

        translate = &aj->translate;

        if (fighter_gobj != NULL)
        {
            do
            {
                Fighter_Struct *fp = ftGetStruct(fighter_gobj);
                DObj *fj = DObjGetStruct(fighter_gobj);
                f32 var = fp->attributes->object_coll.top * 0.5F;

                f_pos = fj->translate;

                f_pos.y += var;

                vec3f_sub(&dist, &f_pos, translate);

                if ((SQUARE(dist.x) + SQUARE(dist.y) + SQUARE(dist.z)) < ATMSBOMB_DETECT_FIGHTER_RADIUS)
                {
                    func_ovl3_801769AC(item_gobj, FALSE);
                }
                fighter_gobj = fighter_gobj->group_gobj_next;
            } 
            while (fighter_gobj != NULL);
        }
    }
    return FALSE;
}

void func_ovl3_80176E68(GObj *item_gobj)
{
    func_ovl3_80176D00(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_MSBomb_Status, 6);
}

void func_ovl3_80176E9C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->it_multi = 0;

    ap->item_event_index = 0;

    ap->item_hit.stale = ITEM_STALE_DEFAULT;
    ap->item_hit.hit_sfx = 1;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_ovl3_80176C14(item_gobj);
}

bool32 jtgt_ovl3_80176EE4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80176C14(item_gobj);

    ap->it_multi++;

    if (ap->it_multi == ATMSBOMB_EXPLODE_LIFETIME)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80176F2C(GObj *item_gobj)
{
    func_ovl3_80176E9C(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_MSBomb_Status, 7);
}

GObj* jtgt_ovl3_80176F60(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_MSBomb_Data, pos, vel, flags);
    DObj *joint;
    Item_Struct *ap;
    Vec3f translate;

    if (item_gobj != NULL)
    {
        joint = DObjGetStruct(item_gobj);

        joint->next->unk_0x54 = 2;
        joint->next->unk_0x8->unk_0x54 = 0;

        translate = joint->translate;

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint->next->unk_0x8, 0x46U, 0U);

        joint->translate = translate;

        ap = itGetStruct(item_gobj);

        ap->it_multi = 0;

        ap->x2D3_flag_b5 = TRUE;

        ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ap);

        joint->rotate.z = 0.0F;
    }
    return item_gobj;
}