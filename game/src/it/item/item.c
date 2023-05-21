#include "item.h"
#include <game/src/ft/fighter.h>
#include <game/src/gr/ground.h>
#include <game/src/gm/gmground.h>
#include <game/src/gm/gmmatch.h>
#include <game/src/it/article/article.h>

extern Item_Struct *D_ovl3_8018CFF0;
extern s32 D_ovl3_8018CFF8;
extern s32 dbObjDisplayStatus_Item;

void func_ovl3_801654B0(void)
{
    Item_Struct *ip;
    s32 i;

    D_ovl3_8018CFF0 = ip = hal_alloc(sizeof(Item_Struct) * ITEM_ALLOC_MAX, 8U);

    for (i = 0; i < (ITEM_ALLOC_MAX - 1); i++)
    {
        ip[i].ip_alloc_next = &ip[i + 1];
    }
    if (ip != NULL)
    {
        ip[i].ip_alloc_next = NULL;
    }
    D_ovl3_8018CFF8 = 1;
    dbObjDisplayStatus_Item = dbObjDisplayStatus_Master;
}


// Not the first function in this file

u32 func_ovl3_801655A0(void)
{
    u32 group_id = D_ovl3_8018CFF8;

    if ((D_ovl3_8018CFF8 += 1) == 0)
    {
        D_ovl3_8018CFF8++;
    }
    return group_id;
}

extern s32 D_ovl2_80131398;

GObj* func_ovl3_801655C8(GObj *spawn_gobj, ItemSpawnData *item_status_desc, Vec3f *spawn_pos, u32 flags)
{
    GObj *item_gobj;
    void (*cb)(GObj*);
    ItemHitDesc *it_hit_desc;
    Item_Struct *ip;
    Item_Struct *owner_ip;
    Article_Struct *ap;
    Fighter_Struct *fp;
    s32 unused[8];

    ip = func_ovl3_80165558(spawn_gobj);

    if (ip == NULL)
    {
        return NULL;
    }
    item_gobj = func_80009968(0x3F4U, NULL, 5U, 0x80000000U);

    if (item_gobj == NULL)
    {
        func_ovl3_80165588(ip);
        return NULL;
    }
    it_hit_desc = *(uintptr_t*)item_status_desc->p_item + (intptr_t)item_status_desc->offset_it_hit; // I hope this is correct?
    item_gobj->user_data = ip;
    ip->item_gobj = item_gobj;
    ip->it_kind = item_status_desc->it_kind;

    switch (flags & ITEM_MASK_SPAWN_ALL)
    {
    case ITEM_MASK_SPAWN_FIGHTER: // Items spawned by fighters
        fp = FighterGetStruct(spawn_gobj);
        ip->owner_gobj = spawn_gobj;
        ip->team = fp->team;
        ip->port_id = fp->port_id;
        ip->handicap = fp->handicap;
        ip->player_number = fp->player_number;
        ip->lr = fp->lr;

        ip->display_state = fp->display_state;

        ip->item_hit.stale = func_ovl2_800EA470(fp->port_id, fp->attack_id, fp->flags_hi.halfword);
        ip->item_hit.attack_id = fp->attack_id;
        ip->item_hit.flags_0x4A.halfword = fp->flags_hi.halfword;
        ip->item_hit.flags_0x4C = fp->flags_lw;
        ip->item_hit.flags_0x4E.halfword = fp->unk_0x290.halfword;
        break;

    case ITEM_MASK_SPAWN_ITEM: // Items spawned by other items
        owner_ip = ItemGetStruct(spawn_gobj);
        ip->owner_gobj = owner_ip->owner_gobj;
        ip->team = owner_ip->team;
        ip->port_id = owner_ip->port_id;
        ip->handicap = owner_ip->handicap;
        ip->player_number = owner_ip->player_number;
        ip->lr = owner_ip->lr;

        ip->display_state = owner_ip->display_state;

        ip->item_hit.stale = owner_ip->item_hit.stale;
        ip->item_hit.attack_id = owner_ip->item_hit.attack_id;
        ip->item_hit.flags_0x4A.halfword = owner_ip->item_hit.flags_0x4A.halfword;
        ip->item_hit.flags_0x4C = owner_ip->item_hit.flags_0x4C;
        ip->item_hit.flags_0x4E.halfword = owner_ip->item_hit.flags_0x4E.halfword;
        break;

    case ITEM_MASK_SPAWN_ARTICLE: // Items spawned by Pokémon
        ap = ArticleGetStruct(spawn_gobj);
        ip->owner_gobj = ap->owner_gobj;
        ip->team = ap->team;
        ip->port_id = ap->port_id;
        ip->handicap = ap->handicap;
        ip->player_number = ap->player_number;
        ip->lr = ap->lr;

        ip->display_state = ap->display_state;

        ip->item_hit.stale = ap->article_hit.stale;
        ip->item_hit.attack_id = ap->article_hit.attack_id;
        ip->item_hit.flags_0x4A.halfword = ap->article_hit.flags_0x4E.halfword;
        ip->item_hit.flags_0x4C = ap->article_hit.flags_lw;
        ip->item_hit.flags_0x4E.halfword = ap->article_hit.flags_hi.halfword;
        break;

    default: // Items spawned independently 
    case ITEM_MASK_SPAWN_GROUND:
        ip->owner_gobj = NULL;
        ip->team = ITEM_TEAM_DEFAULT;
        ip->port_id = ITEM_PORT_DEFAULT;
        ip->handicap = ITEM_UNK_DEFAULT;
        ip->player_number = 0;
        ip->lr = RIGHT;

        ip->display_state = dbObjDisplayStatus_Item;

        ip->item_hit.attack_id = 0;
        ip->item_hit.stale = ITEM_STALE_DEFAULT;
        ip->item_hit.flags_0x4A.halfword = func_ovl2_800EA5BC();
        ip->item_hit.flags_0x4C.flags_0x3FF = 0;
        ip->item_hit.flags_0x4C.flags_0x1000 = ip->item_hit.flags_0x4C.flags_0x800 = ip->item_hit.flags_0x4C.flags_0x400 = FALSE;
        ip->item_hit.flags_0x4E.halfword = func_ovl2_800EA74C();
        break;
    }
    ip->item_hit.update_state = gmHitCollision_UpdateState_New;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->phys_info.vel_ground = 0.0F;

    ip->item_hit.damage = it_hit_desc->damage;

    ip->item_hit.element = it_hit_desc->element;

    ip->item_hit.offset[0].x = it_hit_desc->offset[0].x;
    ip->item_hit.offset[0].y = it_hit_desc->offset[0].y;
    ip->item_hit.offset[0].z = it_hit_desc->offset[0].z;
    ip->item_hit.offset[1].x = it_hit_desc->offset[1].x;
    ip->item_hit.offset[1].y = it_hit_desc->offset[1].y;
    ip->item_hit.offset[1].z = it_hit_desc->offset[1].z;

    ip->item_hit.size = it_hit_desc->size * 0.5F;

    ip->item_hit.angle = it_hit_desc->angle;

    ip->item_hit.knockback_scale = it_hit_desc->knockback_scale;
    ip->item_hit.knockback_weight = it_hit_desc->knockback_weight;
    ip->item_hit.knockback_base = it_hit_desc->knockback_base;

    ip->item_hit.clang = it_hit_desc->clang;
    ip->item_hit.shield_damage = it_hit_desc->shield_damage;

    ip->item_hit.hit_sfx = it_hit_desc->sfx;

    ip->item_hit.priority = it_hit_desc->priority;
    ip->item_hit.flags_0x48_b1 = it_hit_desc->flags_0x2F_b0;
    ip->item_hit.flags_0x48_b2 = it_hit_desc->flags_0x2F_b1;

    ip->item_hit.can_rehit = FALSE;

    ip->item_hit.can_deflect = it_hit_desc->can_deflect;
    ip->item_hit.can_reflect = it_hit_desc->can_reflect;
    ip->item_hit.can_absorb = it_hit_desc->can_absorb;

    ip->item_hit.noheal = FALSE;

    ip->item_hit.can_shield = it_hit_desc->can_shield;
    ip->item_hit.hitbox_count = it_hit_desc->hitbox_count;

    ip->item_hit.interact_mask = GMHITCOLLISION_MASK_ALL;

    func_ovl3_80168158(ip);

    ip->hit_victim_damage = 0;
    ip->hit_reflect_damage = 0;
    ip->hit_attack_damage = 0;
    ip->hit_shield_damage = 0;
    ip->reflect_gobj = NULL;
    ip->absorb_gobj = NULL;

    ip->is_hitlag_victim = FALSE;
    ip->is_hitlag_item = FALSE;
    ip->is_camera_follow = FALSE;

    ip->group_id = 0;

    ip->is_static_damage = FALSE;

    ip->p_sfx = NULL;
    ip->sfx_id = 0;

    ip->shield_collide_angle = 0.0F;
    ip->shield_collide_vec.z = 0.0F;
    ip->shield_collide_vec.y = 0.0F;
    ip->shield_collide_vec.x = 0.0F;

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
    ip->coll_data.p_translate = &DObjGetStruct(item_gobj)->translate;
    ip->coll_data.p_lr = &ip->lr;

    ip->coll_data.object_coll.top = (f32)it_hit_desc->objectcoll_top;
    ip->coll_data.object_coll.center = (f32)it_hit_desc->objectcoll_center;
    ip->coll_data.object_coll.bottom = (f32)it_hit_desc->objectcoll_bottom;
    ip->coll_data.object_coll.width = (f32)it_hit_desc->objectcoll_width;
    ip->coll_data.p_object_coll = &ip->coll_data.object_coll;

    ip->coll_data.ignore_line_id = -1;

    ip->coll_data.ground_line_id = -1;
    ip->coll_data.ceil_line_id = -1;
    ip->coll_data.rwall_line_id = -1;
    ip->coll_data.lwall_line_id = -1;

    ip->coll_data.wall_flag = D_ovl2_80131398;
    ip->coll_data.coll_mask = 0;

    ip->coll_data.pos_push.x = 0.0F;
    ip->coll_data.pos_push.y = 0.0F;
    ip->coll_data.pos_push.z = 0.0F;

    func_80008188(item_gobj, func_ovl3_801662BC, 1U, 3U);
    func_80008188(item_gobj, func_ovl3_80166954, 1U, 1U);
    func_80008188(item_gobj, func_ovl3_80166BE4, 1U, 0U);

    ip->proc_update = item_status_desc->proc_update;
    ip->proc_map = item_status_desc->proc_map;
    ip->proc_hit = item_status_desc->proc_hit;
    ip->proc_shield = item_status_desc->proc_shield;
    ip->proc_hop = item_status_desc->proc_hop;
    ip->proc_setoff = item_status_desc->proc_setoff;
    ip->proc_reflector = item_status_desc->proc_reflector;
    ip->proc_absorb = item_status_desc->proc_absorb;
    ip->proc_dead = NULL;

    ip->coll_data.pos_curr = DObjGetStruct(item_gobj)->translate = *spawn_pos;

    if (flags & ITEM_FLAG_PROJECT)
    {
        switch (flags & ITEM_MASK_SPAWN_ALL)
        {
        default:
        case ITEM_MASK_SPAWN_GROUND:
            break;

        case ITEM_MASK_SPAWN_FIGHTER:
            func_ovl2_800DF09C(item_gobj, FighterGetStruct(spawn_gobj)->coll_data.p_translate, &FighterGetStruct(spawn_gobj)->coll_data);
            break;

        case ITEM_MASK_SPAWN_ITEM:
            func_ovl2_800DF09C(item_gobj, ItemGetStruct(spawn_gobj)->coll_data.p_translate, &ItemGetStruct(spawn_gobj)->coll_data);
            break;

        case ITEM_MASK_SPAWN_ARTICLE:
            func_ovl2_800DF09C(item_gobj, ArticleGetStruct(spawn_gobj)->coll_data.p_translate, &ArticleGetStruct(spawn_gobj)->coll_data);
            break;
        }
    }
    ip->ground_or_air = air;

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
    Item_Struct *ip = ItemGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    s32 i;

    for (i = 0; i < ip->item_hit.hitbox_count; i++)
    {
        ItemHitUnk *it_hit_unk = &ip->item_hit.item_hit_unk[i];

        Vec3f *offset = &ip->item_hit.offset[i];

        Vec3f *translate = &joint->translate;

        switch (ip->item_hit.update_state)
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
            ip->item_hit.update_state = gmHitCollision_UpdateState_Transfer;
            it_hit_unk->unk_0x18 = 0;
            it_hit_unk->unk_0x5C = 0;
            break;

        case gmHitCollision_UpdateState_Transfer:
            ip->item_hit.update_state = gmHitCollision_UpdateState_Interpolate;

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
    Item_Struct *ip = ItemGetStruct(item_gobj);
    ItemHitArray *targets;
    Item_Hit *it_hit;
    s32 i;

    it_hit = &ip->item_hit;

    if (it_hit->update_state != gmHitCollision_UpdateState_Disable)
    {
        for (i = 0; i < ARRAY_COUNT(ip->item_hit.hit_targets); i++)
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
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Vec3f *translate;
    DObj *joint;

    if (!(ip->is_hitlag_item))
    {
        func_8000DF34(item_gobj);

        if (ip->proc_update != NULL)
        {
            if (ip->proc_update(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
        joint = DObjGetStruct(item_gobj);

        translate = &DObjGetStruct(item_gobj)->translate;

        ip->coll_data.pos_curr = *translate;

        translate->x += ip->phys_info.vel.x;
        translate->y += ip->phys_info.vel.y;
        translate->z += ip->phys_info.vel.z;

        ip->coll_data.pos_prev.x = translate->x - ip->coll_data.pos_curr.x;
        ip->coll_data.pos_prev.y = translate->y - ip->coll_data.pos_curr.y;
        ip->coll_data.pos_prev.z = translate->z - ip->coll_data.pos_curr.z;

        if ((ip->ground_or_air == ground) && (ip->coll_data.ground_line_id != -1) && (ip->coll_data.ground_line_id != -2) && (func_ovl2_800FC67C(ip->coll_data.ground_line_id) != FALSE))
        {
            func_ovl2_800FA7B8(ip->coll_data.ground_line_id, &ip->coll_data.pos_correct);

            translate->x += ip->coll_data.pos_correct.x;
            translate->y += ip->coll_data.pos_correct.y;
            translate->z += ip->coll_data.pos_correct.z;
        }
        else
        {
            ip->coll_data.pos_correct.z = 0.0F;
            ip->coll_data.pos_correct.y = 0.0F;
            ip->coll_data.pos_correct.x = 0.0F;
        }

        if ((translate->y < Ground_Info->blastzone_bottom) || (Ground_Info->blastzone_right < translate->x) || (translate->x < Ground_Info->blastzone_left) || (Ground_Info->blastzone_top < translate->y) || (translate->z < -20000.0F) || (20000.0F < translate->z))
        {
            if ((ip->proc_dead == NULL) || (ip->proc_dead(item_gobj) != FALSE))
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }

        if (ip->proc_map != NULL)
        {
            ip->coll_data.coll_mask_prev = ip->coll_data.coll_mask;
            ip->coll_data.coll_mask = 0U;
            ip->coll_data.unk_0x64 = 0;
            ip->coll_data.coll_type = 0;
            ip->coll_data.unk_0x58 = 0;

            if (ip->proc_map(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
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

            case gmHitCollision_Type_Unk:
                it_hit->hit_targets[i].victim_flags.is_interact_shield = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Type_Reflect:
                it_hit->hit_targets[i].victim_flags.is_interact_reflect = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Type_Absorb:
                it_hit->hit_targets[i].victim_flags.is_interact_absorb = TRUE;
                break;

            case gmHitCollision_Type_Hit:
                it_hit->hit_targets[i].victim_flags.interact_mask = interact_mask;
                break;

            case gmHitCollision_Type_ArticleHurt:
                it_hit->hit_targets[i].victim_flags.is_interact_hurt = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
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

        case gmHitCollision_Type_Unk:
            it_hit->hit_targets[i].victim_flags.is_interact_shield = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
            break;

        case gmHitCollision_Type_Reflect:
            it_hit->hit_targets[i].victim_flags.is_interact_reflect = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
            break;

        case gmHitCollision_Type_Absorb:
            it_hit->hit_targets[i].victim_flags.is_interact_absorb = TRUE;
            break;

        case gmHitCollision_Type_Hit:
            it_hit->hit_targets[i].victim_flags.interact_mask = interact_mask;
            break;

        case gmHitCollision_Type_ArticleHurt:
            it_hit->hit_targets[i].victim_flags.is_interact_hurt = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
            break;

        default: break;
        }
    }
}

void func_ovl3_8016679C(Item_Struct *this_ip, Item_Hit *it_hit, GObj *target_gobj, s32 hitbox_type, u32 interact_mask)
{
    if (this_ip->group_id != 0)
    {
        GObj *victim_gobj = gOMObjCommonLinks[GObjLinkIndex_Item];

        if (victim_gobj != NULL)
        {
            do
            {
                Item_Struct *victim_ip = ItemGetStruct(victim_gobj);

                if (victim_ip->group_id == this_ip->group_id)
                {
                    func_ovl3_80166594(&victim_ip->item_hit, target_gobj, hitbox_type, interact_mask);
                }
                victim_gobj = victim_gobj->group_gobj_next;

            } 
            while (victim_gobj != NULL);
        }
    }
    else func_ovl3_80166594(it_hit, target_gobj, hitbox_type, arg4);
}

void func_ovl3_80166854(Item_Struct *this_ip, Item_Hit *this_hit, s32 this_hit_id, Item_Struct *victim_ip, Item_Hit *victim_hit, s32 victim_hit_id, GObj *this_gobj, GObj *victim_gobj)
{
    s32 this_hit_damage;
    s32 victim_hit_damage;
    Vec3f sp2C;
    s32 victim_hit_priority;
    s32 this_hit_priority;

    this_hit_damage = func_ovl3_80168128(this_ip);
    victim_hit_damage = func_ovl3_80168128(victim_ip);

    func_ovl2_800F0C94(&sp2C, victim_hit, victim_hit_id, this_hit, this_hit_id);

    victim_hit_priority = victim_hit->priority;
    this_hit_priority = this_hit->priority;

    if (this_hit_priority >= victim_hit->priority)
    {
        func_ovl3_8016679C(victim_ip, victim_hit, this_gobj, gmHitCollision_Type_Hit, 0);
        if (victim_ip->hit_attack_damage < victim_hit_damage)
        {
            victim_ip->hit_attack_damage = victim_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, victim_hit_damage);
        this_hit_priority = this_hit->priority;
        victim_hit_priority = victim_hit->priority;
    }
    if (victim_hit_priority >= this_hit_priority)
    {
        func_ovl3_8016679C(this_ip, this_hit, victim_gobj, gmHitCollision_Type_Hit, 0);
        if (this_ip->hit_attack_damage < this_hit_damage)
        {
            this_ip->hit_attack_damage = this_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, this_hit_damage);
    }
}

void func_ovl3_80166954(GObj *this_gobj) // Scan for hitbox collision with other items
{
    GObj *other_gobj;
    Item_Struct *this_ip, *other_ip;
    Item_Hit *other_hit, *this_hit;
    gmHitCollisionFlags these_flags, those_flags;
    s32 m, n, i, j;
    bool32 is_check_self;

    this_ip = ItemGetStruct(this_gobj);
    this_hit = &this_ip->item_hit;

    if ((this_hit->clang) && (this_hit->update_state != gmHitCollision_UpdateState_Disable) && (this_hit->interact_mask & GMHITCOLLISION_MASK_ITEM))
    {
        other_gobj = gOMObjCommonLinks[GObjLinkIndex_Item];

        is_check_self = FALSE;

        if (other_gobj != NULL)
        {
            do
            {
                other_ip = ItemGetStruct(other_gobj);
                other_hit = &other_ip->item_hit;

                if (other_gobj == this_gobj)
                {
                    is_check_self = TRUE; // Not really sure what to name this
                }
                else if ((is_check_self != FALSE) && (this_ip->owner_gobj != other_ip->owner_gobj))
                {
                    if ((Match_Info->is_team_battle != TRUE) || (Match_Info->is_team_attack != FALSE)) goto next_check;
                    {
                        if (this_ip->team == other_ip->team) goto next_gobj; // YUCKY match but you can't say it's only a half

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
                                                    func_ovl3_80166854(other_ip, other_hit, i, this_ip, this_hit, j, other_gobj, this_gobj);
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
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if ((ip->hit_victim_damage != 0) || (ip->hit_reflect_damage != 0)) // 0x238 = hit article damage?
    {
        if (ip->proc_hit != NULL)
        {
            if (ip->proc_hit(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
    }
    if (ip->hit_shield_damage != 0)
    {
        if ((ip->item_hit.can_deflect) && (ip->ground_or_air == air))
        {
            if (ip->shield_collide_angle < ITEM_DEFLECT_ANGLE_DEFAULT)
            {
                ip->shield_collide_angle -= HALF_PI32;

                if (ip->shield_collide_angle < 0.0F)
                {
                    ip->shield_collide_angle = 0.0F;
                }
                if (ip->proc_hop != NULL)
                {
                    if (ip->proc_hop(item_gobj) != FALSE)
                    {
                        func_ovl3_8016800C(item_gobj);
                        return;
                    }
                }
                goto next_check;
            }
        }
        if (ip->proc_shield != NULL)
        {
            if (ip->proc_shield(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
    }
next_check:
    if (ip->hit_attack_damage != 0)
    {
        if (ip->proc_setoff != NULL)
        {
            if (ip->proc_setoff(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
    }

    if (ip->reflect_gobj != NULL)
    {
        Fighter_Struct *fp;

        ip->owner_gobj = ip->reflect_gobj;

        fp = FighterGetStruct(ip->reflect_gobj);

        ip->team = fp->team;
        ip->port_id = fp->port_id;
        ip->display_state = fp->display_state;
        ip->player_number = fp->player_number;
        ip->handicap = fp->handicap;
        ip->item_hit.flags_0x4C = ip->unk_0x258;
        ip->item_hit.flags_0x4E.halfword = ip->unk_0x25A.halfword;

        if (ip->proc_reflector != NULL)
        {
            if (ip->proc_reflector(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
        if (!(ip->is_static_damage))
        {
            ip->item_hit.damage = (ip->item_hit.damage * ITEM_REFLECT_MUL_DEFAULT) + ITEM_REFLECT_ADD_DEFAULT;

            if (ip->item_hit.damage > ITEM_REFLECT_MAX_DEFAULT)
            {
                ip->item_hit.damage = ITEM_REFLECT_MAX_DEFAULT;
            }
        }
    }

    if (ip->absorb_gobj != NULL)
    {
        if (ip->proc_absorb != NULL)
        {

            if (ip->proc_absorb(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
    }
    ip->hit_victim_damage = 0;
    ip->hit_reflect_damage = 0;
    ip->hit_attack_damage = 0;
    ip->hit_shield_damage = 0;
    ip->reflect_gobj = NULL;
}
