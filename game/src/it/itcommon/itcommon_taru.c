#include "item.h"



bool32 jtgt_ovl3_80179BA0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATTARU_GRAVITY, ATTARU_T_VEL);

    DObjGetStruct(item_gobj)->rotate.z += ap->item_vars.taru.roll_rotate_speed;

    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 func_ovl3_80179BF8(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80179D1C);

    return FALSE;
}

bool32 func_ovl3_80179C20(GObj *item_gobj)
{
    func_800269C0(0x3BU);

    itEffect_CreateBoxSmashGFX(&DObjGetStruct(item_gobj)->translate);

    if (func_ovl3_801730D4(item_gobj) != FALSE)
    {
        return TRUE;
    }
    else func_ovl3_8017A30C(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80179C78(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->percent_damage >= ATTARU_HEALTH_MAX)
    {
        return func_ovl3_80179C20(item_gobj);
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80179CB8(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.5F, 0.2F, func_ovl3_80179CE8);
}

extern itStatusDesc Article_Taru_Status[];

void func_ovl3_80179CE8(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Taru_Status, 0);
}

void func_ovl3_80179D1C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_Taru_Status, 1);
}

void jtgt_ovl3_80179D60(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Taru_Status, 2);
}

bool32 func_ovl3_80179D88(GObj *item_gobj, f32 vel_mod)
{
    s32 unused;
    Item_Struct *ap;
    bool32 is_collide_ground = func_ovl3_801737B8(item_gobj, MPCOLL_MASK_GROUND);

    if (itMap_CheckCollideAllModifiyVel(item_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), vel_mod, NULL) != FALSE)
    {
        func_ovl3_80172508(item_gobj);
    }
    if (is_collide_ground != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80179DEC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->lifetime = ATTARU_LIFETIME;

    ap->phys_info.vel.y = 0.0F;

    itMain_SetItemStatus(item_gobj, Article_Taru_Status, 6);
}

bool32 jtgt_ovl3_80179E28(GObj *item_gobj)
{
    if (func_ovl3_80179D88(item_gobj, 0.5F) != FALSE)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        if (ap->phys_info.vel.y >= 90.0F) // Is it even possible to meet this condition? Didn't they mean ABSF(ap->phys_info.vel.y)?
        {
            func_ovl3_80179C20(item_gobj); // This causes the barrel to smash on impact when landing from too high; doesn't seem possible to trigger

            return TRUE;
        }
        else if (ap->phys_info.vel.y < 30.0F)
        {
            func_ovl3_80179DEC(item_gobj);
        }
        else
        {
            func_ovl0_800C7B08(&ap->phys_info.vel, &ap->coll_data.ground_angle);

            ap->phys_info.vel.y *= 0.2F;

            func_ovl3_80172508(item_gobj);
        }
        func_ovl3_8017279C(item_gobj);
    }
    return FALSE;
}

void func_ovl3_80179EF0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    DObjGetStruct(item_gobj)->next->rotate.x = HALF_PI32;

    ap->coll_data.object_coll.top = ap->coll_data.object_coll.width;
    ap->coll_data.object_coll.bottom = -ap->coll_data.object_coll.width;
}

void jtgt_ovl3_80179F1C(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Taru_Status, 3);
    func_ovl3_80179EF0(item_gobj);
}

bool32 func_ovl3_80179F40(GObj *item_gobj)
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

void jtgt_ovl3_80179F74(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Taru_Status, 4);
    func_ovl3_80179EF0(item_gobj);
}

extern intptr_t Article_Taru_Hit;
extern itCreateDesc Article_Taru_Data;

bool32 jtgt_ovl3_80179FA8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->it_multi++;

    if (ap->it_multi == ATTARU_EXPLODE_LIFETIME)
    {
        return TRUE;
    }
    else itMain_UpdateHitEvent(item_gobj, (itHitEvent*)((uintptr_t)*Article_Taru_Data.p_file + (intptr_t)&Article_Taru_Hit)); // Linker thing

    return FALSE;
}

bool32 jtgt_ovl3_8017A004(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    f32 roll_rotate_speed;
    f32 sqrt_vel;

    ap->phys_info.vel.x += (-(atan2f(ap->coll_data.ground_angle.y, ap->coll_data.ground_angle.x) - HALF_PI32) * ATTARU_MUL_VEL_X);

    ap->lr = (ap->phys_info.vel.x >= 0.0F) ? RIGHT : LEFT;

    sqrt_vel = sqrtf(SQUARE(ap->phys_info.vel.x) + SQUARE(ap->phys_info.vel.y));

    if (sqrt_vel < ATTARU_MIN_VEL_XY)
    {
        ap->lifetime--;

        if (ap->lifetime < ATTARU_DESPAWN_FLASH_START)
        {
            if (ap->lifetime == 0)
            {
                return TRUE;
            }
            else if (ap->lifetime & 1)
            {
                DObjGetStruct(item_gobj)->unk_0x54 ^= 2;
            }
        }
    }
    roll_rotate_speed = ((ap->lr == LEFT) ? ATTARU_ROLL_ROTATE_MUL : -ATTARU_ROLL_ROTATE_MUL) * sqrt_vel;

    ap->item_vars.taru.roll_rotate_speed = roll_rotate_speed;

    DObjGetStruct(item_gobj)->rotate.z += roll_rotate_speed;

    return FALSE;
}

bool32 jtgt_ovl3_8017A148(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_8017356C(item_gobj) == FALSE)
    {
        itMain_SetItemStatus(item_gobj, Article_Taru_Status, 4);
    }
    else if (ap->coll_data.coll_mask & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
    {
        return func_ovl3_80179C20(item_gobj);
    }
    return FALSE;
}

GObj* jtgt_ovl3_8017A1B8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Taru_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        ap->item_vars.taru.roll_rotate_speed = 0.0F;

        ap->is_damage_all = TRUE;

        ap->x2D3_flag_b5 = TRUE;

        ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ap);
    }
    return item_gobj;
}

void func_ovl3_8017A240(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->it_multi = 0;
    ap->item_event_index = 0;

    ap->item_hit.hit_sfx = 1;

    ap->item_hit.can_rehit_item = TRUE;
    ap->item_hit.can_reflect = FALSE;

    ap->item_hit.stale = ARTICLE_STALE_DEFAULT;
    ap->item_hit.element = gmHitCollision_Element_Fire;

    ap->item_hit.clang = FALSE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_ovl3_8017279C(item_gobj);
    func_ovl3_8017275C(item_gobj);
    itMain_UpdateHitEvent(item_gobj, (itHitEvent*)((uintptr_t)*Article_Taru_Data.p_file + (intptr_t)&Article_Taru_Hit));
}

void func_ovl3_8017A2D8(GObj *item_gobj)
{
    func_ovl3_8017A240(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Taru_Status, 5);
}

void func_ovl3_8017A30C(GObj *item_gobj)
{
    Effect_Unk *effect_unk;
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    effect_unk = func_ovl2_801005C8(&joint->translate);

    if (effect_unk != NULL)
    {
        effect_unk->effect_info->scale.x =
        effect_unk->effect_info->scale.y =
        effect_unk->effect_info->scale.z = ATTARU_EXPLODE_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(item_gobj)->unk_0x54 = 2;

    func_ovl3_8017A2D8(item_gobj);
}