#include "item.h"
#include <game/src/ft/fighter.h>
#include <game/src/gr/ground.h>
#include <game/src/gm/gmground.h>
#include <game/src/gm/gmmatch.h>
#include <game/src/it/article/article.h>

extern Weapon_Struct *D_ovl3_8018CFF0;
extern u32 D_ovl3_8018CFF8;
extern s32 dbObjDisplayStatus_Item;

void func_ovl3_801654B0(void)
{
    Weapon_Struct *wp;
    s32 i;

    D_ovl3_8018CFF0 = wp = hal_alloc(sizeof(Weapon_Struct) * WEAPON_ALLOC_MAX, 8U);

    for (i = 0; i < (WEAPON_ALLOC_MAX - 1); i++)
    {
        wp[i].wp_alloc_next = &wp[i + 1];
    }
    if (wp != NULL)
    {
        wp[i].wp_alloc_next = NULL;
    }
    D_ovl3_8018CFF8 = 1;
    dbObjDisplayStatus_Item = dbObjDisplayStatus_Master;
}

// Not the first function in this file

u32 func_ovl3_801655A0(void)
{
    u32 group_id = D_ovl3_8018CFF8++;

    if (D_ovl3_8018CFF8 == 0)
    {
        D_ovl3_8018CFF8++;
    }
    return group_id;
}

extern s32 D_ovl2_80131398;

// 0x801655C8
GObj* wpManager_CreateWeapon(GObj *spawn_gobj, ItemSpawnData *item_status_desc, Vec3f *spawn_pos, u32 flags)
{
    GObj *item_gobj;
    void (*cb)(GObj*);
    ItemHitDesc *it_hit_desc;
    Weapon_Struct *wp;
    Weapon_Struct *owner_wp;
    Article_Struct *ap;
    Fighter_Struct *fp;
    s32 unused[8];

    wp = func_ovl3_80165558(spawn_gobj);

    if (wp == NULL)
    {
        return NULL;
    }
    item_gobj = func_80009968(0x3F4U, NULL, 5U, 0x80000000U);

    if (item_gobj == NULL)
    {
        wpManager_EjectWeaponStruct(wp);
        return NULL;
    }
    it_hit_desc = *(uintptr_t*)item_status_desc->p_item + (intptr_t)item_status_desc->offset_it_hit; // I hope this is correct?
    item_gobj->user_data = wp;
    wp->item_gobj = item_gobj;
    wp->it_kind = item_status_desc->it_kind;

    switch (flags & WEAPON_MASK_SPAWN_ALL)
    {
    case WEAPON_MASK_SPAWN_FIGHTER: // Items spawned by fighters
        fp = ftGetStruct(spawn_gobj);
        wp->owner_gobj = spawn_gobj;
        wp->team = fp->team;
        wp->port_id = fp->port_id;
        wp->handicap = fp->handicap;
        wp->player_number = fp->player_number;
        wp->lr = fp->lr;

        wp->display_state = fp->display_state;

        wp->item_hit.stale = gmCommon_DamageGetStaleMul(fp->port_id, fp->attack_id, fp->motion_count);
        wp->item_hit.attack_id = fp->attack_id;
        wp->item_hit.motion_count = fp->motion_count;
        wp->item_hit.stat_flags = fp->stat_flags;
        wp->item_hit.stat_count = fp->stat_count;
        break;

    case WEAPON_MASK_SPAWN_WEAPON: // Items spawned by other items
        owner_wp = wpGetStruct(spawn_gobj);
        wp->owner_gobj = owner_wp->owner_gobj;
        wp->team = owner_wp->team;
        wp->port_id = owner_wp->port_id;
        wp->handicap = owner_wp->handicap;
        wp->player_number = owner_wp->player_number;
        wp->lr = owner_wp->lr;

        wp->display_state = owner_wp->display_state;

        wp->item_hit.stale = owner_wp->item_hit.stale;
        wp->item_hit.attack_id = owner_wp->item_hit.attack_id;
        wp->item_hit.motion_count = owner_wp->item_hit.motion_count;
        wp->item_hit.stat_flags = owner_wp->item_hit.stat_flags;
        wp->item_hit.stat_count = owner_wp->item_hit.stat_count;
        break;

    case WEAPON_MASK_SPAWN_ARTICLE: // Items spawned by Pokémon
        ap = atGetStruct(spawn_gobj);
        wp->owner_gobj = ap->owner_gobj;
        wp->team = ap->team;
        wp->port_id = ap->port_id;
        wp->handicap = ap->handicap;
        wp->player_number = ap->player_number;
        wp->lr = ap->lr;

        wp->display_state = ap->display_state;

        wp->item_hit.stale = ap->article_hit.stale;
        wp->item_hit.attack_id = ap->article_hit.attack_id;
        wp->item_hit.motion_count = ap->article_hit.stat_count;
        wp->item_hit.stat_flags = ap->article_hit.stat_flags;
        wp->item_hit.stat_count = ap->article_hit.stat_count;
        break;

    default: // Items spawned independently 
    case WEAPON_MASK_SPAWN_GROUND:
        wp->owner_gobj = NULL;
        wp->team = WEAPON_TEAM_DEFAULT;
        wp->port_id = WEAPON_PORT_DEFAULT;
        wp->handicap = WEAPON_HANDICAP_DEFAULT;
        wp->player_number = 0;
        wp->lr = RIGHT;

        wp->display_state = dbObjDisplayStatus_Item;

        wp->item_hit.attack_id = 0;
        wp->item_hit.stale = WEAPON_STALE_DEFAULT;
        wp->item_hit.motion_count = gmCommon_MotionCountInc();
        wp->item_hit.stat_flags.attack_group_id = 0;
        wp->item_hit.stat_flags.is_smash_attack = wp->item_hit.stat_flags.is_ground_or_air = wp->item_hit.stat_flags.is_special_attack = FALSE;
        wp->item_hit.stat_count = gmCommon_StatUpdateCountInc();
        break;
    }
    wp->item_hit.update_state = gmHitCollision_UpdateState_New;

    wp->phys_info.vel.z = 0.0F;
    wp->phys_info.vel.y = 0.0F;
    wp->phys_info.vel.x = 0.0F;

    wp->phys_info.vel_ground = 0.0F;

    wp->item_hit.damage = it_hit_desc->damage;

    wp->item_hit.element = it_hit_desc->element;

    wp->item_hit.offset[0].x = it_hit_desc->offset[0].x;
    wp->item_hit.offset[0].y = it_hit_desc->offset[0].y;
    wp->item_hit.offset[0].z = it_hit_desc->offset[0].z;
    wp->item_hit.offset[1].x = it_hit_desc->offset[1].x;
    wp->item_hit.offset[1].y = it_hit_desc->offset[1].y;
    wp->item_hit.offset[1].z = it_hit_desc->offset[1].z;

    wp->item_hit.size = it_hit_desc->size * 0.5F;

    wp->item_hit.angle = it_hit_desc->angle;

    wp->item_hit.knockback_scale = it_hit_desc->knockback_scale;
    wp->item_hit.knockback_weight = it_hit_desc->knockback_weight;
    wp->item_hit.knockback_base = it_hit_desc->knockback_base;

    wp->item_hit.clang = it_hit_desc->clang;
    wp->item_hit.shield_damage = it_hit_desc->shield_damage;

    wp->item_hit.hit_sfx = it_hit_desc->sfx;

    wp->item_hit.priority = it_hit_desc->priority;
    wp->item_hit.flags_0x48_b1 = it_hit_desc->flags_0x2F_b0;
    wp->item_hit.flags_0x48_b2 = it_hit_desc->flags_0x2F_b1;

    wp->item_hit.can_rehit = FALSE;

    wp->item_hit.can_hop = it_hit_desc->can_hop;
    wp->item_hit.can_reflect = it_hit_desc->can_reflect;
    wp->item_hit.can_absorb = it_hit_desc->can_absorb;

    wp->item_hit.noheal = FALSE;

    wp->item_hit.can_shield = it_hit_desc->can_shield;
    wp->item_hit.hitbox_count = it_hit_desc->hitbox_count;

    wp->item_hit.interact_mask = GMHITCOLLISION_MASK_ALL;

    func_ovl3_80168158(wp);

    wp->hit_victim_damage = 0;
    wp->hit_reflect_damage = 0;
    wp->hit_attack_damage = 0;
    wp->hit_shield_damage = 0;
    wp->reflect_gobj = NULL;
    wp->absorb_gobj = NULL;

    wp->is_hitlag_victim = FALSE;
    wp->is_hitlag_item = FALSE;
    wp->is_camera_follow = FALSE;

    wp->group_id = 0;

    wp->is_static_damage = FALSE;

    wp->p_sfx = NULL;
    wp->sfx_id = 0;

    wp->shield_collide_angle = 0.0F;
    wp->shield_collide_vec.z = 0.0F;
    wp->shield_collide_vec.y = 0.0F;
    wp->shield_collide_vec.x = 0.0F;

    if (item_status_desc->unk_0x0 & 1)
    {
        func_8000F590(item_gobj, it_hit_desc->unk_0x0, NULL, item_status_desc->unk_0x10, item_status_desc->unk_0x11, item_status_desc->unk_0x12);

        cb = (item_status_desc->unk_0x0 & 2) ? func_ovl3_8016763C : func_ovl3_80167618;
    }
    else
    {
        func_ovl0_800C89BC(func_800092D0(item_gobj, it_hit_desc->unk_0x0), item_status_desc->unk_0x10, item_status_desc->unk_0x11, item_status_desc->unk_0x12);

        cb = (item_status_desc->unk_0x0 & 2) ? func_ovl3_801675F4 : func_ovl3_801675D0;
    }
    func_80009DF4(item_gobj, cb, 0xE, 0x80000000, -1);

    if (it_hit_desc->unk_0x4 != NULL)
    {
        func_8000F8F4(item_gobj, it_hit_desc->unk_0x4);
    }

    if ((it_hit_desc->unk_0x8 != NULL) || (it_hit_desc->unk_0xC != NULL))
    {

        func_8000BED8(item_gobj, it_hit_desc->unk_0x8, it_hit_desc->unk_0xC, 0.0F);
    }
    wp->coll_data.p_translate = &DObjGetStruct(item_gobj)->translate;
    wp->coll_data.p_lr = &wp->lr;

    wp->coll_data.object_coll.top = (f32)it_hit_desc->objectcoll_top;
    wp->coll_data.object_coll.center = (f32)it_hit_desc->objectcoll_center;
    wp->coll_data.object_coll.bottom = (f32)it_hit_desc->objectcoll_bottom;
    wp->coll_data.object_coll.width = (f32)it_hit_desc->objectcoll_width;
    wp->coll_data.p_object_coll = &wp->coll_data.object_coll;

    wp->coll_data.ignore_line_id = -1;

    wp->coll_data.ground_line_id = -1;
    wp->coll_data.ceil_line_id = -1;
    wp->coll_data.rwall_line_id = -1;
    wp->coll_data.lwall_line_id = -1;

    wp->coll_data.wall_flag = D_ovl2_80131398;
    wp->coll_data.coll_mask = 0;

    wp->coll_data.vel_push.x = 0.0F;
    wp->coll_data.vel_push.y = 0.0F;
    wp->coll_data.vel_push.z = 0.0F;

    func_80008188(item_gobj, func_ovl3_801662BC, 1U, 3U);
    func_80008188(item_gobj, func_ovl3_80166954, 1U, 1U);
    func_80008188(item_gobj, func_ovl3_80166BE4, 1U, 0U);

    wp->proc_update = item_status_desc->proc_update;
    wp->proc_map = item_status_desc->proc_map;
    wp->proc_hit = item_status_desc->proc_hit;
    wp->proc_shield = item_status_desc->proc_shield;
    wp->proc_hop = item_status_desc->proc_hop;
    wp->proc_setoff = item_status_desc->proc_setoff;
    wp->proc_reflector = item_status_desc->proc_reflector;
    wp->proc_absorb = item_status_desc->proc_absorb;
    wp->proc_dead = NULL;

    wp->coll_data.pos_curr = DObjGetStruct(item_gobj)->translate = *spawn_pos;

    if (flags & WEAPON_FLAG_PROJECT)
    {
        switch (flags & WEAPON_MASK_SPAWN_ALL)
        {
        default:
        case WEAPON_MASK_SPAWN_GROUND:
            break;

        case WEAPON_MASK_SPAWN_FIGHTER:
            func_ovl2_800DF09C(item_gobj, ftGetStruct(spawn_gobj)->coll_data.p_translate, &ftGetStruct(spawn_gobj)->coll_data);
            break;

        case WEAPON_MASK_SPAWN_WEAPON:
            func_ovl2_800DF09C(item_gobj, wpGetStruct(spawn_gobj)->coll_data.p_translate, &wpGetStruct(spawn_gobj)->coll_data);
            break;

        case WEAPON_MASK_SPAWN_ARTICLE:
            func_ovl2_800DF09C(item_gobj, atGetStruct(spawn_gobj)->coll_data.p_translate, &atGetStruct(spawn_gobj)->coll_data);
            break;
        }
    }
    wp->ground_or_air = air;

    func_ovl3_80165F60(item_gobj);

    return item_gobj;
}

void func_ovl3_80165ED0(DObj *joint, Vec3f *vec)
{
    vec->x *= joint->scale.x;
    vec->y *= joint->scale.y;

    vec3_get_euler_rotation(vec, 4, joint->rotate.z);

    vec->x += joint->translate.x;
    vec->y += joint->translate.y;
    vec->z += joint->translate.z;
}

void func_ovl3_80165F60(GObj *item_gobj) // Update hitbox(es?)
{
    Weapon_Struct *wp = wpGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    s32 i;

    for (i = 0; i < wp->item_hit.hitbox_count; i++)
    {
        ItemHitUnk *it_hit_unk = &wp->item_hit.item_hit_unk[i];

        Vec3f *offset = &wp->item_hit.offset[i];

        Vec3f *translate = &joint->translate;

        switch (wp->item_hit.update_state)
        {
        default:
        case gmHitCollision_UpdateState_Disable:
            break;

        case gmHitCollision_UpdateState_New:

            it_hit_unk->pos = *offset;

            if ((offset->x == 0.0F) && (offset->y == 0.0F) && (offset->z == 0.0F))
            {
                it_hit_unk->pos.x += translate->x;
                it_hit_unk->pos.y += translate->y;
                it_hit_unk->pos.z += translate->z;
            }
            else
            {
                func_ovl3_80165ED0(joint, &it_hit_unk->pos);
            }
            wp->item_hit.update_state = gmHitCollision_UpdateState_Transfer;
            it_hit_unk->unk_0x18 = 0;
            it_hit_unk->unk_0x5C = 0;
            break;

        case gmHitCollision_UpdateState_Transfer:
            wp->item_hit.update_state = gmHitCollision_UpdateState_Interpolate;

        case gmHitCollision_UpdateState_Interpolate:

            it_hit_unk->pos_prev = it_hit_unk->pos;

            it_hit_unk->pos = *offset;

            if ((offset->x == 0.0F) && (offset->y == 0.0F) && (offset->z == 0.0F))
            {
                it_hit_unk->pos.x += translate->x;
                it_hit_unk->pos.y += translate->y;
                it_hit_unk->pos.z += translate->z;
            }
            else
            {
                func_ovl3_80165ED0(joint, &it_hit_unk->pos);
            }
            it_hit_unk->unk_0x18 = 0;
            it_hit_unk->unk_0x5C = 0;
            break;
        }
    }
}

void func_ovl3_801661E0(GObj *item_gobj) // Set hitbox victim array
{
    Weapon_Struct *wp = wpGetStruct(item_gobj);
    ItemHitArray *targets;
    Item_Hit *it_hit;
    s32 i;

    it_hit = &wp->item_hit;

    if (it_hit->update_state != gmHitCollision_UpdateState_Disable)
    {
        for (i = 0; i < ARRAY_COUNT(wp->item_hit.hit_targets); i++)
        {
            targets = &it_hit->hit_targets[i];

            if (targets->victim_gobj != NULL)
            {
                if (targets->victim_flags.timer_rehit > 0)
                {
                    targets->victim_flags.timer_rehit--;

                    if (targets->victim_flags.timer_rehit <= 0)
                    {
                        targets->victim_gobj = NULL;

                        targets->victim_flags.is_interact_hurt = targets->victim_flags.is_interact_shield = targets->victim_flags.is_interact_reflect = targets->victim_flags.is_interact_absorb = FALSE;

                        targets->victim_flags.interact_mask = GMHITCOLLISION_MASK_ALL;
                    }
                }
            }
        }
    }
}

void func_ovl3_801662BC(GObj *item_gobj) // Run item logic pass 1 (animation, physics, collision, despawn check)
{
    Weapon_Struct *wp = wpGetStruct(item_gobj);
    Vec3f *translate;
    DObj *joint;

    if (!(wp->is_hitlag_item))
    {
        func_8000DF34(item_gobj);

        if (wp->proc_update != NULL)
        {
            if (wp->proc_update(item_gobj) != FALSE)
            {
                wpMain_DestroyWeapon(item_gobj);
                return;
            }
        }
        joint = DObjGetStruct(item_gobj);

        translate = &DObjGetStruct(item_gobj)->translate;

        wp->coll_data.pos_curr = *translate;

        translate->x += wp->phys_info.vel.x;
        translate->y += wp->phys_info.vel.y;
        translate->z += wp->phys_info.vel.z;

        wp->coll_data.pos_prev.x = translate->x - wp->coll_data.pos_curr.x;
        wp->coll_data.pos_prev.y = translate->y - wp->coll_data.pos_curr.y;
        wp->coll_data.pos_prev.z = translate->z - wp->coll_data.pos_curr.z;

        if ((wp->ground_or_air == ground) && (wp->coll_data.ground_line_id != -1) && (wp->coll_data.ground_line_id != -2) && (func_ovl2_800FC67C(wp->coll_data.ground_line_id) != FALSE))
        {
            func_ovl2_800FA7B8(wp->coll_data.ground_line_id, &wp->coll_data.pos_correct);

            translate->x += wp->coll_data.pos_correct.x;
            translate->y += wp->coll_data.pos_correct.y;
            translate->z += wp->coll_data.pos_correct.z;
        }
        else
        {
            wp->coll_data.pos_correct.z = 0.0F;
            wp->coll_data.pos_correct.y = 0.0F;
            wp->coll_data.pos_correct.x = 0.0F;
        }

        if ((translate->y < Ground_Info->blastzone_bottom) || (Ground_Info->blastzone_right < translate->x) || (translate->x < Ground_Info->blastzone_left) || (Ground_Info->blastzone_top < translate->y) || (translate->z < -20000.0F) || (20000.0F < translate->z))
        {
            if ((wp->proc_dead == NULL) || (wp->proc_dead(item_gobj) != FALSE))
            {
                wpMain_DestroyWeapon(item_gobj);
                return;
            }
        }

        if (wp->proc_map != NULL)
        {
            wp->coll_data.coll_mask_prev = wp->coll_data.coll_mask;
            wp->coll_data.coll_mask = 0U;
            wp->coll_data.unk_0x64 = 0;
            wp->coll_data.coll_type = 0;
            wp->coll_data.unk_0x58 = 0;

            if (wp->proc_map(item_gobj) != FALSE)
            {
                wpMain_DestroyWeapon(item_gobj);
                return;
            }
        }
        func_ovl3_80165F60(item_gobj);
        func_ovl3_801661E0(item_gobj);
    }
}

void func_ovl3_80166594(Item_Hit *it_hit, GObj *victim_gobj, s32 hitbox_type, u32 interact_mask)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(it_hit->hit_targets); i++)
    {
        if (victim_gobj == it_hit->hit_targets[i].victim_gobj) // Run this if the victim we're checking has already been hit
        {
            switch (hitbox_type)
            {
            case gmHitCollision_Type_Hurt:
                it_hit->hit_targets[i].victim_flags.is_interact_hurt = TRUE;
                break;

            case gmHitCollision_Type_Shield:
                it_hit->hit_targets[i].victim_flags.is_interact_shield = TRUE;
                break;

            case gmHitCollision_Type_ShieldRehit:
                it_hit->hit_targets[i].victim_flags.is_interact_shield = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = WEAPON_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Type_Reflect:
                it_hit->hit_targets[i].victim_flags.is_interact_reflect = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = WEAPON_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Type_Absorb:
                it_hit->hit_targets[i].victim_flags.is_interact_absorb = TRUE;
                break;

            case gmHitCollision_Type_Hit:
                it_hit->hit_targets[i].victim_flags.interact_mask = interact_mask;
                break;

            case gmHitCollision_Type_HurtRehit:
                it_hit->hit_targets[i].victim_flags.is_interact_hurt = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = WEAPON_REHIT_TIME_DEFAULT;
                break;

            default: break;
            }
            break;
        }
    }
    if (i == ARRAY_COUNT(it_hit->hit_targets)) // Check if all victim slots have been filled
    {
        for (i = 0; i < ARRAY_COUNT(it_hit->hit_targets); i++) // Reset hit count and increment until there is an empty slot
        {
            if (it_hit->hit_targets[i].victim_gobj == NULL) break;
        }

        if (i == ARRAY_COUNT(it_hit->hit_targets)) i = 0; // Reset hit count again if all victim slots are full

        it_hit->hit_targets[i].victim_gobj = victim_gobj; // Store victim's pointer to slot

        switch (hitbox_type)
        {
        case gmHitCollision_Type_Hurt:
            it_hit->hit_targets[i].victim_flags.is_interact_hurt = TRUE;
            break;

        case gmHitCollision_Type_Shield:
            it_hit->hit_targets[i].victim_flags.is_interact_shield = TRUE;
            break;

        case gmHitCollision_Type_ShieldRehit:
            it_hit->hit_targets[i].victim_flags.is_interact_shield = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = WEAPON_REHIT_TIME_DEFAULT;
            break;

        case gmHitCollision_Type_Reflect:
            it_hit->hit_targets[i].victim_flags.is_interact_reflect = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = WEAPON_REHIT_TIME_DEFAULT;
            break;

        case gmHitCollision_Type_Absorb:
            it_hit->hit_targets[i].victim_flags.is_interact_absorb = TRUE;
            break;

        case gmHitCollision_Type_Hit:
            it_hit->hit_targets[i].victim_flags.interact_mask = interact_mask;
            break;

        case gmHitCollision_Type_HurtRehit:
            it_hit->hit_targets[i].victim_flags.is_interact_hurt = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = WEAPON_REHIT_TIME_DEFAULT;
            break;

        default: break;
        }
    }
}

void func_ovl3_8016679C(Weapon_Struct *this_wp, Item_Hit *it_hit, GObj *target_gobj, s32 hitbox_type, u32 interact_mask)
{
    if (this_wp->group_id != 0)
    {
        GObj *victim_gobj = gOMObjCommonLinks[gOMObjLinkIndexItem];

        if (victim_gobj != NULL)
        {
            do
            {
                Weapon_Struct *victim_wp = wpGetStruct(victim_gobj);

                if (victim_wp->group_id == this_wp->group_id)
                {
                    func_ovl3_80166594(&victim_wp->item_hit, target_gobj, hitbox_type, interact_mask);
                }
                victim_gobj = victim_gobj->group_gobj_next;

            } 
            while (victim_gobj != NULL);
        }
    }
    else func_ovl3_80166594(it_hit, target_gobj, hitbox_type, arg4);
}

void func_ovl3_80166854(Weapon_Struct *this_wp, Item_Hit *this_hit, s32 this_hit_id, Weapon_Struct *victim_wp, Item_Hit *victim_hit, s32 victim_hit_id, GObj *this_gobj, GObj *victim_gobj)
{
    s32 this_hit_damage;
    s32 victim_hit_damage;
    Vec3f sp2C;
    s32 victim_hit_priority;
    s32 this_hit_priority;

    this_hit_damage = func_ovl3_80168128(this_wp);
    victim_hit_damage = func_ovl3_80168128(victim_wp);

    func_ovl2_800F0C94(&sp2C, victim_hit, victim_hit_id, this_hit, this_hit_id);

    victim_hit_priority = victim_hit->priority;
    this_hit_priority = this_hit->priority;

    if (this_hit_priority >= victim_hit->priority)
    {
        func_ovl3_8016679C(victim_wp, victim_hit, this_gobj, gmHitCollision_Type_Hit, 0);
        if (victim_wp->hit_attack_damage < victim_hit_damage)
        {
            victim_wp->hit_attack_damage = victim_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, victim_hit_damage);
        this_hit_priority = this_hit->priority;
        victim_hit_priority = victim_hit->priority;
    }
    if (victim_hit_priority >= this_hit_priority)
    {
        func_ovl3_8016679C(this_wp, this_hit, victim_gobj, gmHitCollision_Type_Hit, 0);
        if (this_wp->hit_attack_damage < this_hit_damage)
        {
            this_wp->hit_attack_damage = this_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, this_hit_damage);
    }
}

void func_ovl3_80166954(GObj *this_gobj) // Scan for hitbox collision with other items
{
    GObj *other_gobj;
    Weapon_Struct *this_wp, *other_wp;
    Item_Hit *other_hit, *this_hit;
    gmHitCollisionFlags these_flags, those_flags;
    s32 m, n, i, j;
    bool32 is_check_self;

    this_wp = wpGetStruct(this_gobj);
    this_hit = &this_wp->item_hit;

    if ((this_hit->clang) && (this_hit->update_state != gmHitCollision_UpdateState_Disable) && (this_hit->interact_mask & GMHITCOLLISION_MASK_ITEM))
    {
        other_gobj = gOMObjCommonLinks[gOMObjLinkIndexItem];

        is_check_self = FALSE;

        if (other_gobj != NULL)
        {
            do
            {
                other_wp = wpGetStruct(other_gobj);
                other_hit = &other_wp->item_hit;

                if (other_gobj == this_gobj)
                {
                    is_check_self = TRUE; // Not really sure what to name this
                }
                else if ((is_check_self != FALSE) && (this_wp->owner_gobj != other_wp->owner_gobj))
                {
                    if ((Match_Info->is_team_battle != TRUE) || (Match_Info->is_team_attack != FALSE)) goto next_check;
                    {
                        if (this_wp->team == other_wp->team) goto next_gobj; // YUCKY match but you can't say it's only a half

                    next_check:
                        if ((other_hit->update_state != gmHitCollision_UpdateState_Disable) && (other_hit->clang))
                        {
                            if (other_hit->interact_mask & GMHITCOLLISION_MASK_ITEM)
                            {
                                those_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                                for (m = 0; m < ARRAY_COUNT(other_hit->hit_targets); m++)
                                {
                                    if (this_gobj == other_hit->hit_targets[m].victim_gobj)
                                    {
                                        those_flags = other_hit->hit_targets[m].victim_flags;
                                        break;
                                    }
                                }

                                if (those_flags.interact_mask == GMHITCOLLISION_MASK_ALL)
                                {
                                    these_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                                    for (n = 0; n < ARRAY_COUNT(this_hit->hit_targets); n++)
                                    {
                                        if (other_gobj == this_hit->hit_targets[n].victim_gobj)
                                        {
                                            these_flags = this_hit->hit_targets[n].victim_flags;
                                            break;
                                        }
                                    }

                                    if (these_flags.interact_mask == GMHITCOLLISION_MASK_ALL)
                                    {
                                        for (i = 0; i < other_hit->hitbox_count; i++)
                                        {
                                            for (j = 0; j < this_hit->hitbox_count; j++)
                                            {
                                                if (func_ovl2_800F007C(other_hit, i, this_hit, j) != FALSE)
                                                {
                                                    func_ovl3_80166854(other_wp, other_hit, i, this_wp, this_hit, j, other_gobj, this_gobj);
                                                    goto next_gobj;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                next_gobj: other_gobj = other_gobj->group_gobj_next;
            }
            while (other_gobj != NULL);
        }
    }
}

void func_ovl3_80166BE4(GObj *item_gobj)
{
    Weapon_Struct *wp = wpGetStruct(item_gobj);

    if ((wp->hit_victim_damage != 0) || (wp->hit_reflect_damage != 0)) // 0x238 = hit article damage?
    {
        if (wp->proc_hit != NULL)
        {
            if (wp->proc_hit(item_gobj) != FALSE)
            {
                wpMain_DestroyWeapon(item_gobj);
                return;
            }
        }
    }
    if (wp->hit_shield_damage != 0)
    {
        if ((wp->item_hit.can_hop) && (wp->ground_or_air == air))
        {
            if (wp->shield_collide_angle < WEAPON_DEFLECT_ANGLE_DEFAULT)
            {
                wp->shield_collide_angle -= HALF_PI32;

                if (wp->shield_collide_angle < 0.0F)
                {
                    wp->shield_collide_angle = 0.0F;
                }
                if (wp->proc_hop != NULL)
                {
                    if (wp->proc_hop(item_gobj) != FALSE)
                    {
                        wpMain_DestroyWeapon(item_gobj);
                        return;
                    }
                }
                goto next_check;
            }
        }
        if (wp->proc_shield != NULL)
        {
            if (wp->proc_shield(item_gobj) != FALSE)
            {
                wpMain_DestroyWeapon(item_gobj);
                return;
            }
        }
    }
next_check:
    if (wp->hit_attack_damage != 0)
    {
        if (wp->proc_setoff != NULL)
        {
            if (wp->proc_setoff(item_gobj) != FALSE)
            {
                wpMain_DestroyWeapon(item_gobj);
                return;
            }
        }
    }

    if (wp->reflect_gobj != NULL)
    {
        Fighter_Struct *fp;

        wp->owner_gobj = wp->reflect_gobj;

        fp = ftGetStruct(wp->reflect_gobj);

        wp->team = fp->team;
        wp->port_id = fp->port_id;
        wp->display_state = fp->display_state;
        wp->player_number = fp->player_number;
        wp->handicap = fp->handicap;
        wp->item_hit.stat_flags = wp->reflect_stat_flags;
        wp->item_hit.stat_count = wp->reflect_stat_count;

        if (wp->proc_reflector != NULL)
        {
            if (wp->proc_reflector(item_gobj) != FALSE)
            {
                wpMain_DestroyWeapon(item_gobj);
                return;
            }
        }
        if (!(wp->is_static_damage))
        {
            wp->item_hit.damage = (wp->item_hit.damage * WEAPON_REFLECT_MUL_DEFAULT) + WEAPON_REFLECT_ADD_DEFAULT;

            if (wp->item_hit.damage > WEAPON_REFLECT_TIME_DEFAULT)
            {
                wp->item_hit.damage = WEAPON_REFLECT_TIME_DEFAULT;
            }
        }
    }

    if (wp->absorb_gobj != NULL)
    {
        if (wp->proc_absorb != NULL)
        {

            if (wp->proc_absorb(item_gobj) != FALSE)
            {
                wpMain_DestroyWeapon(item_gobj);
                return;
            }
        }
    }
    wp->hit_victim_damage = 0;
    wp->hit_reflect_damage = 0;
    wp->hit_attack_damage = 0;
    wp->hit_shield_damage = 0;
    wp->reflect_gobj = NULL;
}
