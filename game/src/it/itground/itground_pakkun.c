#include "item.h"
#include "fighter.h"

extern itStatusDesc Article_Pakkun_Status[];

void func_ovl3_8017CF20(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Pakkun_Status, 0);

    itGetStruct(item_gobj)->proc_dead = NULL;
}

void func_ovl3_8017CF58(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Pakkun_Status, 1);
}

void func_ovl3_8017CF80(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Pakkun_Status, 2);

    itGetStruct(item_gobj)->proc_dead = func_ovl3_8017D460;
}

void func_ovl3_8017CFC0(GObj *item_gobj)
{
    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        ap->item_vars.pakkun.is_wait_fighter = TRUE;
    }
}

bool32 func_ovl3_8017CFDC(GObj *item_gobj)
{
    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        GObj *fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

        f32 pos_x = ap->item_vars.pakkun.pos.x, pos_y = ap->item_vars.pakkun.pos.y;

        while (fighter_gobj != NULL)
        {
            Fighter_Struct *fp = ftGetStruct(fighter_gobj);
            DObj *joint = fp->joint[ftParts_TopN_Joint];
            f32 dist_x, translate_y;

            if (joint->translate.x < pos_x)
            {
                dist_x = -(joint->translate.x - pos_x);
            }
            else
            {
                dist_x = joint->translate.x - pos_x;
            }
            translate_y = joint->translate.y;

            if ((dist_x < ITPAKKUN_DETECT_SIZE_WIDTH) && (pos_y + ITPAKKUN_DETECT_SIZE_BOTTOM < translate_y) && (translate_y < (pos_y + ITPAKKUN_DETECT_SIZE_TOP)))
            {
                return FALSE;
            }
            fighter_gobj = fighter_gobj->group_gobj_next;
        }
    }
    return TRUE;
}

extern intptr_t D_NF_00000CC8;
extern intptr_t D_NF_00000CF8;
extern void *D_ovl2_801313F0;

bool32 func_ovl3_8017D0A4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->item_vars.pakkun.is_wait_fighter != FALSE)
    {
        ap->it_multi = ITPAKKUN_APPEAR_WAIT;
        ap->item_vars.pakkun.is_wait_fighter = FALSE;
    }
    ap->it_multi--;

    if (ap->it_multi == 0)
    {
        if (func_ovl3_8017CFDC(item_gobj) != FALSE)
        {
            DObj *joint = DObjGetStruct(item_gobj);

            func_8000BD1C(joint, (uintptr_t)D_ovl2_801313F0 + (intptr_t)&D_NF_00000CC8, 0.0F);
            func_8000BD54(joint->mobj, (uintptr_t)D_ovl2_801313F0 + (intptr_t)&D_NF_00000CF8, 0.0F);
            func_8000DF34(item_gobj);

            joint->translate.y += ap->item_vars.pakkun.pos.y;

            func_ovl3_8017CF58(item_gobj);
        }
        else
        {
            ap->it_multi = ITPAKKUN_APPEAR_WAIT;
        }
    }
    return FALSE;
}

void func_ovl3_8017D190(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->it_multi = ITPAKKUN_APPEAR_WAIT;

    func_ovl3_8017CF20(item_gobj);

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;
    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    DObjGetStruct(item_gobj)->translate.y = ap->item_vars.pakkun.pos.y;
}

void func_ovl3_8017D1DC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    f32 pos_y = DObjGetStruct(item_gobj)->translate.y - ap->item_vars.pakkun.pos.y;
    f32 off_y = pos_y + ITPAKKUN_APPEAR_OFF_Y;

    if (off_y <= ITPAKKUN_CLAMP_OFF_Y)
    {
        ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;
        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    }
    else
    {
        if (ap->item_hurt.hitstatus == gmHitCollision_HitStatus_None)
        {
            ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

            itMain_RefreshHit(item_gobj);
        }
        ap->item_hurt.size.y = (off_y - ITPAKKUN_CLAMP_OFF_Y) * ITPAKKUN_HURT_SIZE_MUL_Y;
        ap->item_hurt.offset.y = (ap->item_hurt.size.y + ITPAKKUN_CLAMP_OFF_Y) - pos_y;
    }
}

bool32 func_ovl3_8017D298(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint;

    if (ap->item_vars.pakkun.is_wait_fighter != FALSE)
    {
        DObjGetStruct(item_gobj)->dobj_f0 = (f32)FLOAT_NEG_MAX;

        func_ovl3_8017D190(item_gobj);

        ap->item_vars.pakkun.is_wait_fighter = FALSE;
    }

    joint = DObjGetStruct(item_gobj);

    if ((f32)FLOAT_NEG_MAX == joint->dobj_f0)
    {
        func_ovl3_8017D190(item_gobj);
    }
    else
    {
        joint->translate.y += ap->item_vars.pakkun.pos.y;
    }

    func_ovl3_8017D1DC(item_gobj);

    return FALSE;
}

extern intptr_t D_NF_00000E04;

bool32 jtgt_ovl3_8017D334(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->damage_knockback >= 100.0F)
    {
        DObj *joint = DObjGetStruct(item_gobj);
        f32 angle;

        joint->om_mtx[0]->unk04 = 0x46;

        joint->rotate.z = PI32;

        angle = gmCommon_Damage_GetKnockbackAngle(ap->damage_angle, ap->ground_or_air, ap->damage_knockback);

        ap->phys_info.vel_air.x = (f32)(cosf(angle) * ap->damage_knockback * -ap->lr_damage);
        ap->phys_info.vel_air.y = __sinf(angle) * ap->damage_knockback;

        ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;
        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

        func_ovl3_8017CF80(item_gobj);

        joint->dobj_f0 = (f32)FLOAT_NEG_MAX;

        func_8000BD54(joint->mobj, (uintptr_t)D_ovl2_801313F0 + (intptr_t)&D_NF_00000E04, 0.0f);
        func_8000DF34(item_gobj);
    }
    return FALSE;
}

bool32 func_ovl3_8017D460(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->translate = ap->item_vars.pakkun.pos;

    ap->it_multi = ITPAKKUN_REBIRTH_WAIT;

    ap->phys_info.vel_air.x = 0.0F;
    ap->phys_info.vel_air.y = 0.0F;
    ap->phys_info.vel_air.z = 0.0F;

    joint->rotate.z = 0.0F;

    joint->mobj->unk_mobj_0x98 = (f32)FLOAT_NEG_MAX;

    func_ovl3_8017CF20(item_gobj);

    ap->item_vars.pakkun.is_wait_fighter = FALSE;

    return FALSE;
}

extern itCreateDesc Article_Pakkun_Data;

GObj* jtgt_ovl3_8017D4D8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Pakkun_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        ap->item_vars.pakkun.pos = *pos;

        DObjGetStruct(item_gobj)->translate = *pos;

        ap->it_multi = ITPAKKUN_APPEAR_WAIT;

        ap->is_allow_knockback = TRUE;

        ap->item_vars.pakkun.is_wait_fighter = FALSE;

        ap->item_hit.can_rehit_shield = TRUE;
    }
    return item_gobj;
}
