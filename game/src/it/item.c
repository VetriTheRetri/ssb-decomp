#include "item.h"
#include <game/src/ft/fighter.h>
#include <game/src/gr/ground.h>
#include <game/src/gm/gmmatch.h>

#define HALF_PI32 1.5707964F

// Not the first function in this file

GObj* func_ovl3_801655C8(GObj *spawn_gobj, ItemStatusDesc *item_desc, Vec3f *spawn_pos, u32 flags)
{
    // Non-matching, can't force Vec3f pos into proper stack position without compromises :(

    GObj *item_gobj;
    f32 unk_float;
    Item_Attributes *item_attrs;
    Item_Struct *ip;
    Item_Struct *owner_ip;
    Fighter_Struct *fp_coll;
    Fighter_Struct *fp;
    u32 unused[5];
    Monster_Struct *pm;
    Item_Struct *ip_coll;
    Monster_Struct *pm_coll;
    void (*cb)(GObj*);
    Vec3f pos;

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
    item_attrs = *(int*)item_desc->unk_0x8 + (int)item_desc->unk_0xC;
    item_gobj->user_data = ip;
    ip->item_gobj = item_gobj;
    ip->it_kind = item_desc->it_kind;

    switch (flags & ITEM_MASK_SPAWN)
    {
    case 0: // Items spawned by fighters
        fp = FighterGetStruct(spawn_gobj);
        ip->owner_gobj = spawn_gobj;
        ip->team = fp->team;
        ip->port_index = fp->player_id;
        ip->unk_0x12 = fp->offset_hit_type;
        ip->unk_0x14 = fp->unk_0x18;
        ip->lr = fp->lr;

        ip->display_state = fp->display_state;

        ip->item_hit[0].stale = func_ovl2_800EA470(fp->player_id, fp->attack_id, fp->unk_0x28C_halfword);
        ip->item_hit[0].attack_id = fp->attack_id;
        ip->item_hit[0].flags_0x4A_halfword = fp->unk_0x28C_halfword;
        ip->item_hit[0].flags_0x4C_halfword = fp->unk_0x28E_halfword & 0xFFFF;
        ip->item_hit[0].flags_0x4E = fp->unk_0x290;
        break;

    case 2: // Items spawned by other items
        owner_ip = ItemGetStruct(spawn_gobj);
        ip->owner_gobj = owner_ip->owner_gobj;
        ip->team = owner_ip->team;
        ip->port_index = owner_ip->port_index;
        ip->unk_0x12 = owner_ip->unk_0x12;
        ip->unk_0x14 = owner_ip->unk_0x14;
        ip->lr = owner_ip->lr;

        ip->display_state = owner_ip->display_state;

        ip->item_hit[0].stale = owner_ip->item_hit[0].stale;
        ip->item_hit[0].attack_id = owner_ip->item_hit[0].attack_id;
        ip->item_hit[0].flags_0x4A_halfword = owner_ip->item_hit[0].flags_0x4A_halfword;
        ip->item_hit[0].flags_0x4C_halfword = owner_ip->item_hit[0].flags_0x4C_halfword & 0xFFFF;
        ip->item_hit[0].flags_0x4E = owner_ip->item_hit[0].flags_0x4E;
        break;

    case 3: // Items spawned by Pok�mon
        pm = MonsterGetStruct(spawn_gobj);
        ip->owner_gobj = pm->owner_gobj;
        ip->team = pm->team;
        ip->port_index = pm->port_index;
        ip->unk_0x12 = pm->unk_0x16;
        ip->unk_0x14 = pm->unk_0x18;
        ip->lr = pm->lr;

        ip->display_state = pm->display_state;

        ip->item_hit[0].stale = pm->monster_hit[0].stale;
        ip->item_hit[0].attack_id = pm->monster_hit[0].flags_0x48_b123456;
        ip->item_hit[0].flags_0x4A_halfword = pm->monster_hit[0].flags_0x4A_halfword;
        ip->item_hit[0].flags_0x4C_halfword = pm->monster_hit[0].flags_0x4C_halfword & 0xFFFF;
        ip->item_hit[0].flags_0x4E = pm->monster_hit[0].flags_0x4E;
        break;

    default: // Items spawned independently 
    case 1:
        ip->owner_gobj = NULL;
        ip->team = ITEM_TEAM_DEFAULT;
        ip->port_index = ITEM_PORT_DEFAULT;
        ip->unk_0x12 = ITEM_UNK_DEFAULT;
        ip->unk_0x14 = 0;
        ip->lr = RIGHT;
        ip->display_state = D_ovl3_8018CFF4;
        ip->item_hit[0].attack_id = 0;
        ip->item_hit[0].stale = 1.0F;

        ip->item_hit[0].flags_0x4A_halfword = func_ovl2_800EA5BC();

        ip->item_hit[0].flags_0x4C.flags_lw_0x3FF = 0;
        ip->item_hit[0].flags_0x4C.flags_lw_0x1000 = ip->item_hit[0].flags_0x4C.flags_lw_0x800 = ip->item_hit[0].flags_0x4C.flags_lw_0x400 = FALSE;
        ip->item_hit[0].flags_0x4E = func_ovl2_800EA74C();
        break;
    }
    ip->item_hit[0].update_state = 1;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->percent_damage = 0.0F;

    ip->item_hit[0].damage = item_attrs->damage;

    ip->item_hit[0].element = item_attrs->element;

    ip->item_hit[0].offset[0].x = item_attrs->offset[0].x;
    ip->item_hit[0].offset[0].y = item_attrs->offset[0].y;
    ip->item_hit[0].offset[0].z = item_attrs->offset[0].z;
    ip->item_hit[0].offset[1].x = item_attrs->offset[1].x;
    ip->item_hit[0].offset[1].y = item_attrs->offset[1].y;
    ip->item_hit[0].offset[1].z = item_attrs->offset[1].z;

    ip->item_hit[0].size = item_attrs->size * 0.5F;

    ip->item_hit[0].angle = item_attrs->angle;

    ip->item_hit[0].knockback_scale = item_attrs->knockback_scale;
    ip->item_hit[0].knockback_weight = item_attrs->knockback_weight;
    ip->item_hit[0].knockback_base = item_attrs->knockback_base;

    ip->item_hit[0].flags_0x48_b0 = item_attrs->clang;
    ip->item_hit[0].unk_0x3C = item_attrs->flags_0x2C;

    ip->item_hit[0].hit_sfx = item_attrs->sfx;

    ip->item_hit[0].unk_0x40 = item_attrs->flags_0x2E_b567;
    ip->item_hit[0].flags_0x48_b1 = item_attrs->flags_0x2F_b0;
    ip->item_hit[0].flags_0x48_b2 = item_attrs->flags_0x2F_b1;

    ip->item_hit[0].flags_0x48_b3 = FALSE;

    ip->item_hit[0].is_hit_airborne = item_attrs->flags_0x2F_b2;
    ip->item_hit[0].flags_0x48_b5 = item_attrs->flags_0x2F_b3;
    ip->item_hit[0].flags_0x48_b6 = item_attrs->flags_0x2F_b4;

    ip->item_hit[0].flags_0x48_b7 = FALSE;

    ip->item_hit[0].flags_0x49_b0 = item_attrs->flags_0x2F_b5;
    ip->item_hit[0].hitbox_count = item_attrs-.hitbox_count;

    ip->item_hit[0].hit_status = 7;

    func_ovl3_80168158(ip);

    ip->hit_victim_damage = 0;
    ip->unk_0x238 = 0;
    ip->hit_attack_damage = 0;
    ip->hit_shield_damage = 0;
    ip->reflect_gobj = NULL;
    ip->absorb_gobj = NULL;

    ip->x260_flag_b0 = FALSE;
    ip->is_hitlag_item = FALSE;
    ip->x26C_flag_b0 = FALSE;

    ip->group_id = 0;

    ip->is_static_damage = FALSE;

    ip->unk_0x270 = 0;
    ip->unk_0x274 = 0;

    ip->shield_collide_angle = 0.0F;
    ip->unk_0x250 = 0.0F;
    ip->unk_0x24C = 0.0F;
    ip->unk_0x248 = 0.0F;

    if (item_desc->unk_0x0 & 1)
    {
        func_8000F590(item_gobj, item_attrs->unk_0x0, NULL, item_desc->unk_0x10, item_desc->unk_0x11, item_desc->unk_0x12);

        cb = (item_desc->unk_0x0 & 2) ? func_ovl3_8016763C : func_ovl3_80167618;
    }
    else
    {
        func_ovl0_800C89BC(func_800092D0(item_gobj, item_attrs->unk_0x0), item_desc->unk_0x10, item_desc->unk_0x11, item_desc->unk_0x12);

        cb = (item_desc->unk_0x0 & 2) ? func_ovl3_801675F4 : func_ovl3_801675D0;
    }
    func_80009DF4(item_gobj, cb, 0xE, 0x80000000, -1);

    if (item_attrs->unk_0x4 != NULL)
    {
        func_8000F8F4(item_gobj, item_attrs->unk_0x4);
    }

    if ((item_attrs->unk_0x8 != NULL) || (item_attrs->unk_0xC != NULL))
    {

        func_8000BED8(item_gobj, item_attrs->unk_0x8, item_attrs->unk_0xC, 0.0F);
    }
    ip->coll_data.p_pos = &JObjGetStruct(item_gobj)->translate;
    ip->coll_data.p_lr = &ip->lr;

    ip->coll_data.object_coll.top = (f32)item_attrs->objectcoll_top;
    ip->coll_data.object_coll.center = (f32)item_attrs->objectcoll_center;
    ip->coll_data.object_coll.bottom = (f32)item_attrs->objectcoll_bottom;
    ip->coll_data.object_coll.width = (f32)item_attrs->objectcoll_width;
    ip->coll_data.p_coll_box = &ip->coll_data.object_coll;

    ip->coll_data.object_var = -1;

    ip->coll_data.unk_0x74 = -1;
    ip->coll_data.ceil_line_id = -1;
    ip->coll_data.rwall_line_id = -1;
    ip->coll_data.lwall_line_id = -1;

    ip->coll_data.wall_flag = D_ovl2_80131398;
    ip->coll_data.unk_0x56 = 0;

    ip->coll_data.pos_project.x = 0.0F;
    ip->coll_data.pos_project.y = 0.0F;
    ip->coll_data.pos_project.z = 0.0F;

    func_80008188(item_gobj, func_ovl3_801662BC, 1U, 3U);
    func_80008188(item_gobj, func_ovl3_80166954, 1U, 1U);
    func_80008188(item_gobj, func_ovl3_80166BE4, 1U, 0U);

    ip->cb_anim = item_desc->cb_anim;
    ip->cb_coll = item_desc->cb_coll;
    ip->cb_give_damage = item_desc->cb_give_damage;
    ip->cb_shield_block = item_desc->cb_shield_block;
    ip->cb_shield_deflect = item_desc->cb_shield_deflect;
    ip->cb_attack = item_desc->cb_attack;
    ip->cb_reflect = item_desc->cb_reflect;
    ip->cb_absorb = item_desc->cb_absorb;
    ip->cb_destroy = NULL;

    pos = *spawn_pos;

    JObjGetStruct(item_gobj)->translate = pos;

    ip->coll_data.pos_curr = pos;

    if (flags & ITEM_FLAG_PROJECT)
    {
        switch (flags & ITEM_MASK_SPAWN)
        {
        default:
        case It_Spawn_Default:
            break;

        case It_Spawn_Fighter:
            fp_coll = FighterGetStruct(spawn_gobj);
            func_ovl2_800DF09C(item_gobj, fp_coll->coll_data.p_pos, &fp_coll->coll_data);
            break;

        case It_Spawn_Item:
            ip_coll = ItemGetStruct(spawn_gobj);
            func_ovl2_800DF09C(item_gobj, ip_coll->coll_data.p_pos, &ip_coll->coll_data);
            break;

        case It_Spawn_Monster:
            pm_coll = MonsterGetStruct(spawn_gobj);
            func_ovl2_800DF09C(item_gobj, pm_coll->coll_data.p_pos, &pm_coll->coll_data);
            break;
        }
    }
    ip->ground_or_air = air;

    func_ovl3_80165F60(item_gobj);

    return item_gobj;
}

void func_ovl3_80165ED0(JObj *joint, Vec3f *vec)
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
    JObj *joint = JObjGetStruct(item_gobj);
    s32 i;

    for (i = 0; i < ip->item_hit[0].hitbox_count; i++)
    {
        ItemHitUnk *it_hit_unk = &ip->item_hit[0].item_hit_unk[i];

        Vec3f *offset = &ip->item_hit[0].offset[i];

        Vec3f *translate = &joint->translate;

        switch (ip->item_hit[0].update_state)
        {
        default:
        case itHit_UpdateState_Disable:
            break;

        case itHit_UpdateState_New:

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
            ip->item_hit[0].update_state = itHit_UpdateState_Transfer;
            it_hit_unk->unk_0x18 = 0;
            it_hit_unk->unk_0x5C = 0;
            break;

        case itHit_UpdateState_Transfer:
            ip->item_hit[0].update_state = itHit_UpdateState_Interpolate;

        case itHit_UpdateState_Interpolate:

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

    it_hit = &ip->item_hit[0];

    if (it_hit->update_state != itHit_UpdateState_Disable)
    {
        for (i = 0; i < ARRAY_COUNT(ip->item_hit[0].hit_targets); i++)
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

                        targets->victim_flags.flags_b0 = targets->victim_flags.flags_b1 = targets->victim_flags.flags_b2 = targets->victim_flags.flags_b3 = FALSE;

                        targets->victim_flags.flags_b456 = 7;
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
    JObj *joint;

    if (!(ip->is_hitlag_item))
    {
        func_8000DF34(item_gobj);

        if (ip->cb_anim != NULL)
        {
            if (ip->cb_anim(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
        joint = JObjGetStruct(item_gobj);

        translate = &JObjGetStruct(item_gobj)->translate;

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

        if ((translate->y < D_ovl2_80131300->blastzone_bottom) || (D_ovl2_80131300->blastzone_right < translate->x) || (translate->x < D_ovl2_80131300->blastzone_left) || (D_ovl2_80131300->blastzone_top < translate->y) || (translate->z < -20000.0F) || (20000.0F < translate->z))
        {
            if ((ip->cb_destroy == NULL) || (ip->cb_destroy(item_gobj) != FALSE))
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }

        if (ip->cb_coll != NULL)
        {
            ip->coll_data.unk_0x54 = ip->coll_data.unk_0x56;
            ip->coll_data.unk_0x56 = 0U;
            ip->coll_data.unk_0x64 = 0;
            ip->coll_data.coll_type = 0;
            ip->coll_data.unk_0x58 = 0;

            if (ip->cb_coll(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
        func_ovl3_80165F60(item_gobj);
        func_ovl3_801661E0(item_gobj);
    }
}

void func_ovl3_80166594(Item_Hit *it_hit, GObj *victim_gobj, s32 hitbox_type, s32 arg3)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(it_hit->hit_targets); i++)
    {
        if (victim_gobj == it_hit->hit_targets[i].victim_gobj) // Run this if the victim we're checking has already been hit
        {
            switch (hitbox_type)
            {
            case gmHitCollision_Hurt:
                it_hit->hit_targets[i].victim_flags.flags_b0 = TRUE;
                break;

            case gmHitCollision_Shield:
                it_hit->hit_targets[i].victim_flags.flags_b1 = TRUE;
                break;

            case 2:
                it_hit->hit_targets[i].victim_flags.flags_b1 = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Reflect:
                it_hit->hit_targets[i].victim_flags.flags_b2 = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Absorb:
                it_hit->hit_targets[i].victim_flags.flags_b3 = TRUE;
                break;

            case gmHitCollision_Hit:
                it_hit->hit_targets[i].victim_flags.flags_b456 = arg3;
                break;

            case 4:
                it_hit->hit_targets[i].victim_flags.flags_b0 = TRUE;
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
        case gmHitCollision_Hurt:
            it_hit->hit_targets[i].victim_flags.flags_b0 = TRUE;
            break;

        case gmHitCollision_Shield:
            it_hit->hit_targets[i].victim_flags.flags_b1 = TRUE;
            break;

        case 2:
            it_hit->hit_targets[i].victim_flags.flags_b1 = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
            break;

        case gmHitCollision_Reflect:
            it_hit->hit_targets[i].victim_flags.flags_b2 = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
            break;

        case gmHitCollision_Absorb:
            it_hit->hit_targets[i].victim_flags.flags_b3 = TRUE;
            break;

        case gmHitCollision_Hit:
            it_hit->hit_targets[i].victim_flags.flags_b456 = arg3;
            break;

        case 4:
            it_hit->hit_targets[i].victim_flags.flags_b0 = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
            break;

        default: break;
        }
    }
}

void func_ovl3_8016679C(Item_Struct *this_ip, Item_Hit *it_hit, GObj *target_gobj, s32 hitbox_type, s32 arg4)
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
                    func_ovl3_80166594(&victim_ip->item_hit[0], target_gobj, hitbox_type, arg4);
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
    s32 var_a0;
    s32 var_v1;

    this_hit_damage = func_ovl3_80168128(this_ip);
    victim_hit_damage = func_ovl3_80168128(victim_ip);

    func_ovl2_800F0C94(&sp2C, victim_hit, victim_hit_id, this_hit, this_hit_id);

    var_a0 = victim_hit->unk_0x40;
    var_v1 = this_hit->unk_0x40;

    if (var_v1 >= victim_hit->unk_0x40)
    {
        func_ovl3_8016679C(victim_ip, victim_hit, this_gobj, 3, 0);
        if (victim_ip->hit_attack_damage < victim_hit_damage)
        {
            victim_ip->hit_attack_damage = victim_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, victim_hit_damage);
        var_v1 = this_hit->unk_0x40;
        var_a0 = victim_hit->unk_0x40;
    }
    if (var_a0 >= var_v1)
    {
        func_ovl3_8016679C(this_ip, this_hit, victim_gobj, 3, 0);
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
    ItemHitVictimFlags these_flags, those_flags;
    s32 m, n, i, j;
    bool32 is_self_gobj;

    this_ip = ItemGetStruct(this_gobj);
    this_hit = &this_ip->item_hit[0];

    if ((this_hit->flags_0x48_b0) && (this_hit->update_state != itHit_UpdateState_Disable) && (this_hit->hit_status & 2))
    {
        other_gobj = gOMObjCommonLinks[GObjLinkIndex_Item];

        is_self_gobj = FALSE;

        if (other_gobj != NULL)
        {
            do
            {
                other_ip = ItemGetStruct(other_gobj);
                other_hit = &other_ip->item_hit[0];

                if (other_gobj == this_gobj)
                {
                    is_self_gobj = TRUE; // Not really sure what to name this
                }
                else if ((is_self_gobj != FALSE) && (this_ip->owner_gobj != other_ip->owner_gobj))
                {
                    if ((D_800A50E8->is_team_battle != TRUE) || (D_800A50E8->is_team_attack != FALSE)) goto next_check;
                    {
                        if (this_ip->team == other_ip->team) goto next_gobj; // YUCKY match but you can't say it's only a half

                    next_check:
                        if ((other_hit->update_state != itHit_UpdateState_Disable) && (other_hit->flags_0x48_b0))
                        {
                            if (other_hit->hit_status & 2)
                            {
                                those_flags.flags_b456 = 7;

                                for (m = 0; m < ARRAY_COUNT(other_hit->hit_targets); m++)
                                {
                                    if (this_gobj == other_hit->hit_targets[m].victim_gobj)
                                    {
                                        those_flags = other_hit->hit_targets[m].victim_flags;
                                        break;
                                    }
                                }

                                if (those_flags.flags_b456 == 7)
                                {
                                    these_flags.flags_b456 = 7;

                                    for (n = 0; n < ARRAY_COUNT(this_hit->hit_targets); n++)
                                    {
                                        if (other_gobj == this_hit->hit_targets[n].victim_gobj)
                                        {
                                            these_flags = this_hit->hit_targets[n].victim_flags;
                                            break;
                                        }
                                    }

                                    if (these_flags.flags_b456 == 7)
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

    if ((ip->hit_victim_damage != 0) || (ip->unk_0x238 != 0))
    {
        if (ip->cb_give_damage != NULL)
        {
            if (ip->cb_give_damage(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
    }
    if (ip->hit_shield_damage != 0)
    {
        if ((ip->item_hit[0].is_hit_airborne) && (ip->ground_or_air == air))
        {
            if (ip->shield_collide_angle < ITEM_DEFLECT_ANGLE_DEFAULT)
            {
                ip->shield_collide_angle -= HALF_PI32;

                if (ip->shield_collide_angle < 0.0F)
                {
                    ip->shield_collide_angle = 0.0F;
                }
                if (ip->cb_shield_deflect != NULL)
                {
                    if (ip->cb_shield_deflect(item_gobj) != FALSE)
                    {
                        func_ovl3_8016800C(item_gobj);
                        return;
                    }
                }
                goto next_check;
            }
        }
        if (ip->cb_shield_block != NULL)
        {
            if (ip->cb_shield_block(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
    }
next_check:
    if (ip->hit_attack_damage != 0)
    {
        if (ip->cb_attack != NULL)
        {
            if (ip->cb_attack(item_gobj) != FALSE)
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
        ip->port_index = fp->player_id;
        ip->display_state = fp->display_state;
        ip->unk_0x14 = fp->unk_0x18;
        ip->unk_0x12 = fp->offset_hit_type;
        ip->item_hit[0].flags_0x4C_halfword = ip->unk_0x258 & 0xFFFF;
        ip->item_hit[0].flags_0x4E = ip->unk_0x25A;

        if (ip->cb_reflect != NULL)
        {

            if (ip->cb_reflect(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
        if (!(ip->is_static_damage))
        {
            ip->item_hit[0].damage = (ip->item_hit[0].damage * ITEM_REFLECT_MUL_DEFAULT) + ITEM_REFLECT_ADD_DEFAULT;

            if (ip->item_hit[0].damage > ITEM_REFLECT_MAX_DEFAULT)
            {
                ip->item_hit[0].damage = ITEM_REFLECT_MAX_DEFAULT;
            }
        }
    }

    if (ip->absorb_gobj != NULL)
    {
        if (ip->cb_absorb != NULL)
        {

            if (ip->cb_absorb(item_gobj) != FALSE)
            {
                func_ovl3_8016800C(item_gobj);
                return;
            }
        }
    }
    ip->hit_victim_damage = 0;
    ip->unk_0x238 = 0;
    ip->hit_attack_damage = 0;
    ip->hit_shield_damage = 0;
    ip->reflect_gobj = NULL;
}