#include "item.h"



void func_ovl3_8017A3A0(GObj *item_gobj, GObj *fighter_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    f32 vel_x;
    f32 dist_x;
    s32 lr_vel;
    s32 lr_dist;

    if (ap->ground_or_air == ground)
    {
        dist_x = (DObjGetStruct(fighter_gobj)->translate.x - DObjGetStruct(item_gobj)->translate.x);

        lr_dist = (dist_x < 0.0F) ? LEFT : RIGHT;

        vel_x = lr_dist * ATRSHELL_MUL_VEL_X;

        ap->item_vars.shell.vel_x = vel_x;

        ap->phys_info.vel.x += vel_x;

        lr_vel = (ap->phys_info.vel.x < 0.0F) ? LEFT : RIGHT;

        lr_dist = (ap->item_vars.shell.vel_x < 0.0F) ? LEFT : RIGHT;

        if (lr_dist == lr_vel)
        {
            if (ABSF(ap->phys_info.vel.x) > ATRSHELL_CLAMP_VEL_X)
            {
                ap->phys_info.vel.x = ap->lr * ATRSHELL_CLAMP_VEL_X;
            }
        }
        if (ap->item_hit.update_state == gmHitCollision_UpdateState_Disable)
        {
            if (ABSF(ap->phys_info.vel.x) <= ATRSHELL_HIT_INIT_VEL_X)
            {
                ap->item_hit.update_state = gmHitCollision_UpdateState_New;

                itManager_UpdateHitPositions(item_gobj);
            }
        }
        ap->lr = (ap->phys_info.vel.x < 0.0F) ? LEFT : RIGHT;
    }
}

void func_ovl3_8017A534(GObj *item_gobj)
{
    s32 unused;
    GObj *fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];
    GObj *victim_gobj;
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f *translate = &joint->translate;
    s32 ft_count = 0;
    f32 square_xy;
    f32 dist_xy;
    Vec3f dist;

    if (fighter_gobj != NULL)
    {
        do
        {
            vec3f_sub(&dist, &DObjGetStruct(fighter_gobj)->translate, translate);

            if (ft_count == 0)
            {
                dist_xy = SQUARE(dist.x) + SQUARE(dist.y);
            }
            square_xy = (SQUARE(dist.x) + SQUARE(dist.y));

            if (square_xy <= dist_xy)
            {
                dist_xy = square_xy;

                victim_gobj = fighter_gobj;
            }
            fighter_gobj = fighter_gobj->group_gobj_next;

            ft_count++;
        }
        while (fighter_gobj != NULL);
    }
    func_ovl3_8017A3A0(item_gobj, victim_gobj); // victim_gobj is not always initialized??? Undefined behavior
}

void func_ovl3_8017A610(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    if (ap->item_vars.shell.dust_gfx_int == 0)
    {
        Vec3f pos = joint->translate;

        pos.y += ap->attributes->objectcoll_bottom;

        func_ovl2_800FF048(&pos, ap->lr, 1.0F);

        ap->item_vars.shell.dust_gfx_int = ATRSHELL_GFX_SPAWN_INT;
    }
    ap->item_vars.shell.dust_gfx_int--;
}

extern intptr_t D_NF_00005F88;
extern intptr_t D_NF_00006018;
extern intptr_t D_NF_00006048;

void func_ovl3_8017A6A0(GObj *item_gobj) // Identical to Green Shell function
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    s32 unused[2];

    func_8000BD1C(joint, itGetPData(ap, D_NF_00005F88, D_NF_00006018), 0.0F); // Linker thing
    func_8000BD54(joint->mobj, itGetPData(ap, D_NF_00005F88, D_NF_00006048), 0.0F); // Linker thing
    func_8000DF34(item_gobj);
}

void func_ovl3_8017A734(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->mobj->unk_mobj_0x94 = 0;
    DObjGetStruct(item_gobj)->unk_dobj_0x70 = 0;
}

bool32 jtgt_ovl3_8017A74C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATRSHELL_GRAVITY, ATRSHELL_T_VEL);

    if (!(ap->item_vars.shell.damage_all_delay))
    {
        func_ovl3_8017279C(item_gobj);

        ap->item_vars.shell.damage_all_delay = -1;
    }
    if (ap->item_vars.shell.damage_all_delay != -1)
    {
        ap->item_vars.shell.damage_all_delay--;
    }
    return FALSE;
}

bool32 func_ovl3_8017A7C4(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_8017A984);

    return FALSE;
}

bool32 jtgt_ovl3_8017A7EC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->item_vars.shell.health == 0)
    {
        return func_ovl3_80173DF4(item_gobj, 0.25F);
    }
    func_ovl3_80173B24(item_gobj, 0.25F, 0.5F, func_ovl3_8017A964);

    return FALSE;
}

extern itStatusDesc Article_R_Shell_Status[];

void func_ovl3_8017A83C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80173F54(ap);

    if (ABSF(ap->phys_info.vel.x) < 8.0F)
    {
        func_ovl3_80172E74(item_gobj);

        ap->item_vars.shell.is_damage = FALSE;
        ap->phys_info.vel.x = 0.0F;

        func_ovl3_8017279C(item_gobj);

        ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

        func_ovl3_8017A734(item_gobj);
        itMain_SetItemStatus(item_gobj, Article_R_Shell_Status, 0);
    }
    else if (ap->item_vars.shell.is_damage != FALSE)
    {
        ap->item_hit.update_state = gmHitCollision_UpdateState_New;

        itManager_UpdateHitPositions(item_gobj);
        func_ovl3_8017B0D4(item_gobj);
    }
    else
    {
        func_ovl3_80172E74(item_gobj);

        ap->phys_info.vel.x = 0.0F;

        func_ovl3_8017279C(item_gobj);

        ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

        func_ovl3_8017A734(item_gobj);
        itMain_SetItemStatus(item_gobj, Article_R_Shell_Status, 0);
    }
}

void func_ovl3_8017A964(GObj *item_gobj) // Unused
{
    func_ovl3_8017A83C(item_gobj);
}

void func_ovl3_8017A984(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_R_Shell_Status, 1);
}

bool32 jtgt_ovl3_8017A9D0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->phys_info.vel.x = ap->damage_taken_recent * ATRSHELL_DAMAGE_MUL_NORMAL * (-ap->lr_damage);

    if (ABSF(ap->phys_info.vel.x) > ATRSHELL_STOP_VEL_X)
    {
        ap->item_vars.shell.is_damage = TRUE;

        ap->item_hit.update_state = gmHitCollision_UpdateState_New;

        itManager_UpdateHitPositions(item_gobj);

        func_ovl3_801727BC(item_gobj);

        if (ap->ground_or_air != ground)
        {
            func_ovl3_8017B1A4(item_gobj);
        }
        else func_ovl3_8017B0D4(item_gobj);

    }
    else
    {
        ap->phys_info.vel.x = 0.0F;

        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;
    }
    return FALSE;
}

void jtgt_ovl3_8017AABC(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->rotate.y = 0.0F;

    itMain_SetItemStatus(item_gobj, Article_R_Shell_Status, 2);
}

void jtgt_ovl3_8017AAF0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_vars.shell.health = 1;
    ap->item_vars.shell.is_damage = TRUE;
    ap->item_vars.shell.damage_all_delay = ATRSHELL_DAMAGE_ALL_WAIT;

    ap->times_thrown = 0;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_R_Shell_Status, 3);
}

void jtgt_ovl3_8017AB48(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_vars.shell.health = 1;
    ap->item_vars.shell.is_damage = TRUE;
    ap->item_vars.shell.damage_all_delay = ATRSHELL_DAMAGE_ALL_WAIT;

    ap->times_thrown = 0;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_R_Shell_Status, 4);
}

bool32 jtgt_ovl3_8017ABA0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_80173C68(item_gobj, 0.25F, 0.5F, func_ovl3_8017B0D4) != FALSE)
    {
        if (ap->phys_info.vel.x < 0.0F) ap->lr = LEFT;

        else ap->lr = RIGHT;

        ap->phys_info.vel.x = (((ap->lr * -8.0F) + -10.0F) * 0.7F);
    }
    return FALSE;
}

void func_ovl3_8017AC40(GObj *item_gobj, u8 lr)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->phys_info.vel.x = -ap->phys_info.vel.x;

    ap->item_vars.shell.vel_x = -ap->item_vars.shell.vel_x;

    if (lr != 0)
    {
        ap->lr = RIGHT;
    }
    else ap->lr = LEFT;
}

void func_ovl3_8017AC84(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    itCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f pos;

    if (func_ovl2_800FC67C(ap->coll_data.ground_line_id) != FALSE)
    {
        if (ap->lr == LEFT)
        {
            mpCollision_GetLREdgeLeft(ap->coll_data.ground_line_id, &pos);

            if ((joint->translate.x - attributes->objectcoll_width) <= pos.x)
            {
                func_ovl3_8017AC40(item_gobj, 1);
            }
        }
        else
        {
            mpCollision_GetLREdgeRight(ap->coll_data.ground_line_id, &pos);

            if (pos.x <= (joint->translate.x + attributes->objectcoll_width))
            {
                func_ovl3_8017AC40(item_gobj, 0);
            }
        }
    }
}

bool32 jtgt_ovl3_8017AD7C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_8017A610(item_gobj);
    func_ovl3_8017A534(item_gobj);
    func_ovl3_8017AC84(item_gobj);

    if (ap->lifetime == 0)
    {
        return TRUE;
    }
    else ap->lifetime--;

    return FALSE;
}

bool32 jtgt_ovl3_8017ADD4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if ((func_ovl3_801735A0(item_gobj, func_ovl3_8017B1A4) != FALSE) && (ap->coll_data.coll_mask & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL)))
    {
        ap->phys_info.vel.x = -ap->phys_info.vel.x;

        func_ovl3_80172508(item_gobj);
        func_ovl3_8017279C(item_gobj);

        ap->item_vars.shell.vel_x = -ap->item_vars.shell.vel_x;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017AE48(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_vars.shell.interact--;

    if (ap->item_vars.shell.interact == 0)
    {
        return TRUE;
    }
    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    ap->item_vars.shell.health = rand_u16_range(ATRSHELL_HEALTH_MAX);

    ap->phys_info.vel.x = (((ap->phys_info.vel.x * -1.0F) + (ATRSHELL_RECOIL_VEL_X * ap->lr_attack)) * ATRSHELL_RECOIL_MUL_X);

    func_ovl3_8017A734(item_gobj);

    if (ap->ground_or_air != ground)
    {
        func_ovl3_8017B1A4(item_gobj);
    }
    else
    {
        func_ovl3_8017B0D4(item_gobj);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017AF18(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_vars.shell.interact--;

    if (ap->item_vars.shell.interact == 0)
    {
        return TRUE;
    }
    ap->phys_info.vel.x += (ap->damage_taken_recent * 2.0F) * -ap->lr_damage;

    if (ABSF(ap->phys_info.vel.x) > ATRSHELL_STOP_VEL_X)
    {
        ap->item_hit.update_state = gmHitCollision_UpdateState_New;

        itManager_UpdateHitPositions(item_gobj);
        func_ovl3_801727BC(item_gobj);
        func_ovl3_8017B0D4(item_gobj);
    }
    else
    {
        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;
    }
    return FALSE;
}

void func_ovl3_8017AFEC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;
    ap->pickup_wait = ITEM_PICKUP_WAIT_DEFAULT;

    if (ap->phys_info.vel.x > ATRSHELL_CLAMP_VEL_X)
    {
        ap->phys_info.vel.x = ATRSHELL_CLAMP_VEL_X;
    }
    if (ap->phys_info.vel.x < -ATRSHELL_CLAMP_VEL_X)
    {
        ap->phys_info.vel.x = -ATRSHELL_CLAMP_VEL_X;
    }
    ap->phys_info.vel.y = 0.0F;

    if (ap->phys_info.vel.x < 0.0F)
    {
        ap->lr = LEFT;
    }
    else ap->lr = RIGHT;

    if (ap->item_vars.shell.is_setup_vars == FALSE)
    {
        ap->lifetime = ATRSHELL_LIFETIME;

        ap->item_vars.shell.is_setup_vars = TRUE;

        ap->item_vars.shell.interact = ATRSHELL_INTERACT_MAX;
    }
    ap->item_vars.shell.dust_gfx_int = ATRSHELL_GFX_SPAWN_INT;

    func_ovl3_8017A6A0(item_gobj);
    func_800269C0(0x37U);
    func_ovl3_8017279C(item_gobj);
    func_ovl3_80173F54(ap);
}

void func_ovl3_8017B0D4(GObj *item_gobj)
{
    func_ovl3_8017AFEC(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_R_Shell_Status, 5);
}

void func_ovl3_8017B108(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    if (ap->phys_info.vel.x > ATRSHELL_CLAMP_AIR_X)
    {
        ap->phys_info.vel.x = ATRSHELL_CLAMP_AIR_X;
    }
    if (ap->phys_info.vel.x < -ATRSHELL_CLAMP_AIR_X)
    {
        ap->phys_info.vel.x = -ATRSHELL_CLAMP_AIR_X;
    }
    if (ap->phys_info.vel.x < 0.0F)
    {
        ap->lr = LEFT;
    }
    else ap->lr = RIGHT;

    func_ovl3_8017279C(item_gobj);
    func_ovl3_80173F78(ap);
}

void func_ovl3_8017B1A4(GObj *item_gobj)
{
    func_ovl3_8017B108(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_R_Shell_Status, 6);
}

extern itCreateDesc Article_R_Shell_Data;

GObj *jtgt_ovl3_8017B1D8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_R_Shell_Data, pos, vel, flags);


    if (item_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(item_gobj);
        Item_Struct *ap;
        Vec3f translate = joint->translate;

        joint->rotate.y = HALF_PI32;

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = translate;

        joint->mobj->anim_frame = 0.0F;

        ap = itGetStruct(item_gobj);

        ap->item_hit.can_rehit_shield = TRUE;

        ap->item_vars.shell.health = 1;
        ap->item_vars.shell.is_setup_vars = FALSE;
        ap->item_vars.shell.is_damage = FALSE;
        ap->item_vars.shell.damage_all_delay = -1;
        ap->item_vars.shell.vel_x = 0;

        ap->x2D3_flag_b5 = TRUE;

        ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ap);
    }
    return item_gobj;
}

bool32 jtgt_ovl3_8017B2F8(GObj *item_gobj)
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8017B31C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *aj = DObjGetStruct(item_gobj), *fj = DObjGetStruct(ap->owner_gobj);

    ap->item_vars.shell.interact--;

    if (ap->item_vars.shell.interact == 0)
    {
        return TRUE;
    }

    if (aj->translate.x < fj->translate.x)
    {
        ap->lr = LEFT;

        if (ap->phys_info.vel.x >= 0.0F)
        {
            ap->phys_info.vel.x = -ap->phys_info.vel.x;
            ap->item_vars.shell.vel_x = -ap->item_vars.shell.vel_x;
        }
    }
    else
    {
        ap->lr = RIGHT;

        if (ap->phys_info.vel.x < 0.0F)
        {
            ap->phys_info.vel.x = -ap->phys_info.vel.x;
            ap->item_vars.shell.vel_x = -ap->item_vars.shell.vel_x;
        }
    }
    ap->phys_info.vel.x += (ATRSHELL_ADD_VEL_X * ap->lr);

    func_ovl3_8017279C(item_gobj);

    return FALSE;
}