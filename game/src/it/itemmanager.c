#include <it/item.h>
#include <ft/fighter.h>
#include <wp/weapon.h>
#include <gm/gmmatch.h>
#include <gm/gmground.h>

extern itStruct *itManager_Global_CurrentUserData;
extern void *gItemFileData;
extern intptr_t D_NF_000000FB;
extern intptr_t D_NF_00B1BCA0;
extern intptr_t D_NF_00B1BDE0;
extern intptr_t D_NF_00B1BDE0_other;
extern intptr_t D_NF_00B1E640;
extern void *D_ovl3_8018D044;

extern s32 dbObject_DisplayMode_Global_Article;

// 0x8016DEA0
void itManager_AllocUserData(void) // Many linker things here
{
    itStruct *ap;
    s32 i;

    itManager_Global_CurrentUserData = ap = hal_alloc(sizeof(itStruct) * ITEM_ALLOC_MAX, 8U);

    for (i = 0; i < (ITEM_ALLOC_MAX - 1); i++)
    {
        ap[i].ip_alloc_next = &ap[i + 1];

    }
    if (ap != NULL)
    {
        ap[i].ip_alloc_next = NULL;
    }
    gItemFileData = rldm_get_file_with_external_heap(&D_NF_000000FB, hal_alloc(rldm_bytes_needed_to_load(&D_NF_000000FB), 0x10U));

    D_ovl3_8018D044 = func_ovl2_801159F8(&D_NF_00B1BCA0, &D_NF_00B1BDE0, &D_NF_00B1BDE0_other, &D_NF_00B1E640);

    func_ovl3_8016EF40();
    itManager_InitMonsterVars();
    func_ovl2_80111F80();

    dbObject_DisplayMode_Global_Article = dbObject_DisplayMode_Master;
}

// 0x8016DFAC
itStruct* itManager_GetStructSetNextAlloc(void) // Set global Article user_data link pointer to next member
{
    itStruct *next_item = itManager_Global_CurrentUserData;
    itStruct *current_item;

    if (next_item == NULL)
    {
        return NULL;
    }
    current_item = next_item;

    itManager_Global_CurrentUserData = next_item->ip_alloc_next;

    return current_item;
}

// 0x8016DFDC
void itManager_SetPrevAlloc(itStruct *ip) // Set global Article user_data link pointer to previous member
{
    ip->ip_alloc_next = itManager_Global_CurrentUserData;

    itManager_Global_CurrentUserData = ip;
}

void func_ovl3_8016DFF4(GObj *gobj, DObjDesc *joint_desc, DObj **p_ptr_dobj, u8 arg3)
{
    s32 i, index;
    DObj *joint, *dobj_array[18];

    for (i = 0; i < ARRAY_COUNT(dobj_array); i++)
    {
        dobj_array[i] = NULL;
    }
    for (i = 0; joint_desc->index != ARRAY_COUNT(dobj_array); i++, joint_desc++)
    {
        index = joint_desc->index & 0xFFF;

        if (index != 0)
        {
            joint = dobj_array[index] = func_800093F4(dobj_array[index - 1], joint_desc->display_list);
        }
        else
        {
            joint = dobj_array[0] = func_800092D0(gobj, joint_desc->display_list);
        }
        if (i == 1)
        {
            func_8000F364(joint, arg3, NULL, NULL, NULL);
        }
        else if (arg3 != 0)
        {
            func_80008CC0(joint, arg3, NULL);
        }
        joint->translate = joint_desc->translate;
        joint->rotate = joint_desc->rotate;
        joint->scale = joint_desc->scale;

        if (p_ptr_dobj != NULL) // I have yet to find a case where this point is actually reached
        {
            p_ptr_dobj[i] = joint;
        }
    }
}

extern u16 D_ovl2_80131398;

// 0x8016E174
GObj* itManager_CreateItem(GObj *spawn_gobj, itCreateDesc *spawn_data, Vec3f *pos, Vec3f *vel, u32 flags)
{
    itStruct *ap = itManager_GetStructSetNextAlloc();
    GObj *item_gobj;
    itCommonAttributes *attributes;
    void (*cb_render)(GObj*);
    s32 unused[4];

    if (ap == NULL)
    {
        return NULL;
    }
    else item_gobj = func_80009968(0x3F5U, NULL, 4U, 0x80000000U);

    if (item_gobj == NULL)
    {
        itManager_SetPrevAlloc(ap);

        return NULL;
    }
    attributes = (itCommonAttributes*) ((uintptr_t)*spawn_data->p_file + (intptr_t)spawn_data->offset);

    if (attributes->unk_0x10_b2)
    {
        cb_render = (attributes->unk_0x10_b0) ? func_ovl3_8017224C : func_ovl3_80171F4C;
    }
    else cb_render = (attributes->unk_0x10_b0) ? func_ovl3_80171D38 : func_ovl3_80171C7C;

    func_80009DF4(item_gobj, cb_render, 0xB, 0x80000000, -1);

    item_gobj->user_data = ap;
    ap->item_gobj = item_gobj;
    ap->owner_gobj = NULL;
    ap->it_kind = spawn_data->it_kind;
    ap->type = attributes->type;
    ap->phys_info.vel = *vel;
    ap->phys_info.vel_ground = 0.0F;
    ap->attributes = attributes;

    func_ovl3_80172508(item_gobj);
    itMain_ResetPlayerVars(item_gobj);

    ap->is_allow_pickup = FALSE;
    ap->is_hold = FALSE;
    ap->is_allow_knockback = FALSE;
    ap->is_unused_item_bool = FALSE;
    ap->is_static_damage = FALSE;

    ap->pickup_wait = ITEM_PICKUP_WAIT_DEFAULT;

    ap->percent_damage = 0;
    ap->hitlag_timer = 0;
    ap->damage_highest = 0;
    ap->damage_knockback = 0.0F;
    ap->damage_queue = 0;
    ap->damage_lag = 0;

    ap->times_landed = 0;
    ap->times_thrown = 0;

    ap->weight = attributes->weight;
    ap->is_hitlag_victim = attributes->is_give_hitlag;
    ap->unk_sfx = attributes->unk_atca_sfx;
    ap->drop_sfx = attributes->drop_sfx;
    ap->throw_sfx = attributes->throw_sfx;

    ap->vel_scale = attributes->vel_scale * 0.01F;

    ap->is_damage_all = FALSE;
    ap->is_thrown = FALSE; // Applies magnitude and stale multiplier if TRUE and hitbox is active?
    ap->is_attach_surface = FALSE;

    ap->rotate_step = 0.0F;
    ap->indicator_gobj = NULL;
    ap->arrow_flash_timer = 0;

    ap->item_hit.update_state = spawn_data->update_state;
    ap->item_hit.damage = attributes->damage;
    ap->item_hit.stale = 1.0F;
    ap->item_hit.throw_mul = 1.0F;
    ap->item_hit.element = attributes->element;
    ap->item_hit.offset[0].x = attributes->hit_offset1_x;
    ap->item_hit.offset[0].y = attributes->hit_offset1_y;
    ap->item_hit.offset[0].z = attributes->hit_offset1_z;
    ap->item_hit.offset[1].x = attributes->hit_offset2_x;
    ap->item_hit.offset[1].y = attributes->hit_offset2_y;
    ap->item_hit.offset[1].z = attributes->hit_offset2_z;
    ap->item_hit.size = attributes->size * 0.5F;
    ap->item_hit.angle = attributes->angle;
    ap->item_hit.knockback_scale = attributes->knockback_scale;
    ap->item_hit.knockback_weight = attributes->knockback_weight;
    ap->item_hit.knockback_base = attributes->knockback_base;
    ap->item_hit.rebound = attributes->rebound;
    ap->item_hit.shield_damage = attributes->shield_damage;
    ap->item_hit.hit_sfx = attributes->hit_sfx;
    ap->item_hit.priority = attributes->priority;
    ap->item_hit.can_rehit_item = attributes->can_rehit_item;
    ap->item_hit.can_rehit_fighter = attributes->can_rehit_fighter;
    ap->item_hit.can_rehit_shield = FALSE;
    ap->item_hit.can_hop = attributes->can_hop;
    ap->item_hit.can_reflect = attributes->can_reflect;
    ap->item_hit.can_shield = attributes->can_shield;
    ap->item_hit.hitbox_count = attributes->hitbox_count;
    ap->item_hit.interact_mask = GMHITCOLLISION_MASK_ALL;

    ap->item_hit.attack_id = ftMotion_AttackIndex_None;
    ap->item_hit.stat_count = gmCommon_GetMotionCountInc();
    ap->item_hit.stat_flags.attack_group_id = ftStatus_AttackIndex_Null;
    ap->item_hit.stat_flags.is_smash_attack = ap->item_hit.stat_flags.is_ground_or_air = ap->item_hit.stat_flags.is_special_attack = FALSE;
    ap->item_hit.stat_count = gmCommon_GetStatUpdateCountInc();

    itMain_ClearHitRecord(ap);

    ap->item_hurt.hitstatus = attributes->hitstatus;
    ap->item_hurt.offset.x = attributes->hurt_offset.x;
    ap->item_hurt.offset.y = attributes->hurt_offset.y;
    ap->item_hurt.offset.z = attributes->hurt_offset.z;
    ap->item_hurt.size.x = attributes->hurt_size.x * 0.5F;
    ap->item_hurt.size.y = attributes->hurt_size.y * 0.5F;
    ap->item_hurt.size.z = attributes->hurt_size.z * 0.5F;
    ap->item_hurt.interact_mask = GMHITCOLLISION_MASK_ALL;

    ap->shield_collide_angle = 0.0F;
    ap->shield_collide_vec.x = 0.0F;
    ap->shield_collide_vec.y = 0.0F;
    ap->shield_collide_vec.z = 0.0F;

    ap->hit_normal_damage = 0;
    ap->hit_refresh_damage = 0;
    ap->hit_attack_damage = 0;
    ap->hit_shield_damage = 0;
    ap->reflect_gobj = NULL;

    if (attributes->unk_0x0 != NULL)
    {
        if (!(attributes->unk_0x10_b1))
        {
            func_8000F720(item_gobj, attributes->unk_0x0, attributes->unk_0x4, 0, spawn_data->unk_aspd_0xC, (s32)spawn_data->unk_aspd_0xD, (s32)spawn_data->unk_aspd_0xE);
        }
        else
        {
            func_ovl3_8016DFF4(item_gobj, attributes->unk_0x0, 0, spawn_data->unk_aspd_0xC);

            if (attributes->unk_0x4 != NULL)
            {
                func_8000F8F4(item_gobj, attributes->unk_0x4);
            }
        }
        if ((attributes->unk_atca_0x8 != NULL) || (attributes->unk_atca_0xC != NULL))
        {
            func_8000BED8(item_gobj, attributes->unk_atca_0x8, attributes->unk_atca_0xC, 0.0F);
            func_8000DF34(item_gobj);
        }
        func_ovl0_800C9424(DObjGetStruct(item_gobj));
    }
    else
    {
        func_800092D0(item_gobj, NULL);
    }
    ap->coll_data.p_translate = &DObjGetStruct(item_gobj)->translate;
    ap->coll_data.p_lr = &ap->lr;
    ap->coll_data.object_coll.top = attributes->objectcoll_top;
    ap->coll_data.object_coll.center = attributes->objectcoll_center;
    ap->coll_data.object_coll.bottom = attributes->objectcoll_bottom;
    ap->coll_data.object_coll.width = attributes->objectcoll_width;
    ap->coll_data.p_object_coll = &ap->coll_data.object_coll;
    ap->coll_data.ignore_line_id = -1;
    ap->coll_data.wall_flag = D_ovl2_80131398;
    ap->coll_data.coll_mask = 0;
    ap->coll_data.vel_push.x = 0.0F;
    ap->coll_data.vel_push.y = 0.0F;
    ap->coll_data.vel_push.z = 0.0F;

    gOMObj_AddGObjCommonProc(item_gobj, itManager_ProcItemMain, 1, 3);
    gOMObj_AddGObjCommonProc(item_gobj, itManager_ProcSearchHitAll, 1, 1);
    gOMObj_AddGObjCommonProc(item_gobj, itManager_ProcUpdateHitCollisions, 1, 0);

    ap->proc_update = spawn_data->proc_update;
    ap->proc_map = spawn_data->proc_map;
    ap->proc_hit = spawn_data->proc_hit;
    ap->proc_shield = spawn_data->proc_shield;
    ap->proc_hop = spawn_data->proc_hop;
    ap->proc_setoff = spawn_data->proc_setoff;
    ap->proc_reflector = spawn_data->proc_reflector;
    ap->proc_damage = spawn_data->proc_damage;
    ap->proc_dead = NULL;

    ap->coll_data.pos_curr = DObjGetStruct(item_gobj)->translate = *pos;

    if (flags & ITEM_FLAG_PROJECT)
    {
        switch (flags & ITEM_MASK_SPAWN_ALL)
        {
        case ITEM_MASK_SPAWN_GROUND:
        case ITEM_MASK_SPAWN_DEFAULT: // Default?
            break;

        case ITEM_MASK_SPAWN_FIGHTER:
            func_ovl2_800DF058(item_gobj, ftGetStruct(spawn_gobj)->coll_data.p_translate, &ftGetStruct(spawn_gobj)->coll_data);
            break;

        case ITEM_MASK_SPAWN_ITEM:
            func_ovl2_800DF058(item_gobj, wpGetStruct(spawn_gobj)->coll_data.p_translate, &wpGetStruct(spawn_gobj)->coll_data);
            break;

        case ITEM_MASK_SPAWN_ITEM:
            func_ovl2_800DF058(item_gobj, itGetStruct(spawn_gobj)->coll_data.p_translate, &itGetStruct(spawn_gobj)->coll_data);
            break;
        }
    }
    ap->ground_or_air = GA_Air;

    itManager_UpdateHitPositions(item_gobj);
    func_ovl3_80172FBC(item_gobj);

    return item_gobj;
}

// Don't forget the following two functions here, stashed until I better understand articles (idk and func_ovl3_8016EA78)

extern GObj* (*Article_Callback_Spawn[It_Kind_EnumMax])(GObj*, Vec3f*, Vec3f*, u32); // Array count is likely 45

GObj* func_ovl3_8016EA78(GObj *item_gobj, s32 index, Vec3f *pos, Vec3f *vel, u32 spawn_flags) // UPDATE: WHAT IS THIS OPTIMIZATION BRUH T.T
{
    GObj *new_gobj = Article_Callback_Spawn[index](item_gobj, pos, vel, spawn_flags);

    if (new_gobj != NULL)
    {
        if (index <= It_Kind_CommonEnd)
        {
            func_ovl2_801044B4(pos);
            func_ovl3_80172394(new_gobj, FALSE);
        }
    }
    return new_gobj;
}

// 0x8016EA78
itStruct* itManager_GetCurrentStructAlloc(void)
{
    return itManager_Global_CurrentUserData;
}

extern u16 D_ovl3_80189454[6];
extern u16 D_ovl3_80189460[6];

extern gmItemSpawn item_settings; // Static (.bss)

void func_ovl3_8016EB0C(void)
{
    item_settings.item_spawn_timer = D_ovl3_80189454[gpBattleState->item_switch] + rand_u16_range(D_ovl3_80189460[gpBattleState->item_switch] - D_ovl3_80189454[gpBattleState->item_switch]);
}

void func_ovl3_8016EB78(s32 unused)
{
    s32 padding;
    s32 sp40;
    Vec3f pos;
    Vec3f sp28;

    if (gpBattleState->pause_status != gmMatch_PauseStatus_Disable)
    {
        if (item_settings.item_spawn_timer > 0)
        {
            item_settings.item_spawn_timer--;

            return;
        }
        if (itManager_GetCurrentStructAlloc() != NULL)
        {
            sp40 = func_ovl3_80173090(&item_settings.unk_0xC);

            func_ovl2_800FC894(item_settings.item_toggles[rand_u16_range(item_settings.max_items)], &pos);

            sp28.z = 0.0F;
            sp28.y = 0.0F;
            sp28.x = 0.0F;

            func_800269C0(0x3AU);

            func_ovl3_8016EA78(0, sp40, &pos, &sp28, 4);
        }
        func_ovl3_8016EB0C();
    }
}

GObj* func_ovl3_8016EC40(void)
{
    GObj *gobj;
    s32 i;
    s32 item_count;
    gmGroundUnkBytes *unk_0x84_2;
    s32 item_count_2;
    s32 max_items;
    s32 item_toggles[30];
    u32 item_bits;
    s32 j;
    u32 item_bits_3;
    gmGroundUnkBytes *unk_0x84;
    u32 item_bits_2;

    // TO DO: Figure out where the iterator limit of 20 is coming from

    if (gpBattleState->item_switch != 0)
    {
        if (gpBattleState->item_toggles != 0)
        {
            if (gpMapData->unk_0x84 != NULL)
            {
                unk_0x84_2 = gpMapData->unk_0x84;

                item_bits_2 = gpBattleState->item_toggles;

                item_count = 0;

                for (i = 0; i < It_Kind_FighterStart; i++, item_bits_2 >>= 1)
                {
                    if (item_bits_2 & 1)
                    {
                        item_count += unk_0x84_2->byte[i];
                    }
                }
                if (item_count == 0)
                {
                    return NULL;
                }
                item_settings.unk_0x1C = item_count;

                max_items = func_ovl2_800FC7A4(4);

                if (max_items == 0)
                {
                    return NULL;
                }
                if (max_items > ARRAY_COUNT(item_toggles))
                {
                    while (TRUE)
                    {
                        fatal_printf("Item positions are over %d!\n", ARRAY_COUNT(item_toggles));
                        scnmgr_crash_print_gobj_state();
                    }
                }
                item_settings.max_items = max_items;
                item_settings.item_toggles = hal_alloc(max_items * sizeof(*item_settings.item_toggles), 0);

                func_ovl2_800FC814(4, &item_toggles[0]);

                for (i = 0; i < max_items; i++)
                {
                    item_settings.item_toggles[i] = item_toggles[i];
                }
                gobj = func_80009968(0x3F5U, NULL, 2U, 0x80000000U);

                gOMObj_AddGObjCommonProc(gobj, func_ovl3_8016EB78, 1, 3);

                item_bits = gpBattleState->item_toggles;

                unk_0x84 = gpMapData->unk_0x84;

                for (i = 0, j = 0; i < It_Kind_FighterStart; i++, item_bits >>= 1)
                {
                    if ((item_bits & 1) && (unk_0x84->byte[i] != 0))
                    {
                        j++;
                    }
                }
                item_settings.unk_0x14 = j;
                item_settings.unk_0x18 = hal_alloc(j * sizeof(*item_settings.unk_0x18), 0);
                item_settings.unk_0x20 = hal_alloc(j * sizeof(*item_settings.unk_0x20), 2);

                item_bits_3 = gpBattleState->item_toggles;

                item_count_2 = 0;

                for (i = 0, j = 0; i < It_Kind_FighterStart; i++, item_bits_3 >>= 1)
                {
                    if ((item_bits_3 & 1) && (unk_0x84->byte[i] != 0))
                    {
                        item_settings.unk_0x18[j] = i;
                        item_settings.unk_0x20[j] = item_count_2;
                        item_count_2 += unk_0x84->byte[i];

                        j++;
                    }
                }
                func_ovl3_8016EB0C();

                return gobj;
            }
        }
    }
    return NULL;
}

static Unk_8018D048 D_ovl3_8018D048;

void func_ovl3_8016EF40(void)
{
    s32 sp28;
    s32 sp1C;
    s32 item_count_2;
    gmGroundUnkBytes *temp_a3;
    s32 temp_f18;
    s32 j;
    s32 item_count_4;
    s32 k;
    gmGroundUnkBytes *temp_t1;
    s32 item_count_2_2;
    s32 temp_a0;
    s32 i;
    s32 item_count;
    u32 item_bits;
    u32 item_bits_2;
    u32 item_bits_3;

    if ((gpBattleState->item_switch != 0) && (gpBattleState->item_toggles != 0) && (gpMapData->unk_0x84 != NULL))
    {
        item_bits = gpBattleState->item_toggles >> 4;

        temp_a3 = gpMapData->unk_0x84;

        item_count = 0;

        for (i = 4; i < 20; i++, item_bits >>= 1)
        {
            if (item_bits & 1)
            {
                item_count += temp_a3->byte[i];
            }
        }
        D_ovl3_8018D048.unk_0x10 = item_count;

        if (item_count != 0)
        {
            item_bits_2 = (u32)gpBattleState->item_toggles >> 4;

            temp_t1 = gpMapData->unk_0x84;

            for (j = 0, i = 4; i < It_Kind_FighterStart; i++, item_bits_2 >>= 1)
            {
                if ((item_bits_2 & 1) && (temp_t1->byte[i] != 0))
                {
                    j++;
                }
            }
            j++;

            D_ovl3_8018D048.unk_0x8 = j;
            D_ovl3_8018D048.unk_0xC = hal_alloc(j * sizeof(*D_ovl3_8018D048.unk_0xC), 0U);
            D_ovl3_8018D048.unk_0x14 = hal_alloc(j * sizeof(*D_ovl3_8018D048.unk_0x14), 2U);

            item_bits_2 = gpBattleState->item_toggles >> 4;

            item_count_2 = 0;

            for (j = 0, i = 4; i < It_Kind_FighterStart; i += 4, item_bits_2 >>= 1)
            {
                if ((item_bits_2 & 1) && (temp_t1->byte[i] != 0))
                {
                    D_ovl3_8018D048.unk_0xC[j] = i;
                    D_ovl3_8018D048.unk_0x14[j] = item_count_2;
                    item_count_2 += temp_t1->byte[i];
                    j++;
                }
                item_bits_2 >>= 1;

                if ((item_bits_2 & 1) && (temp_t1->byte[i + 1] != 0))
                {
                    D_ovl3_8018D048.unk_0xC[j] = i + 1;
                    D_ovl3_8018D048.unk_0x14[j] = item_count_2;
                    item_count_2 += temp_t1->byte[i + 1];
                    j++;
                }
                item_bits_2 >>= 1;

                if ((item_bits_2 & 1) && (temp_t1->byte[i + 2] != 0))
                {

                    D_ovl3_8018D048.unk_0xC[j] = i + 2;
                    D_ovl3_8018D048.unk_0x14[j] = item_count_2;
                    item_count_2 += temp_t1->byte[i + 2];
                    j++;
                }
                item_bits_2 >>= 1;

                if ((item_bits_2 & 1) && (temp_t1->byte[i + 3] != 0))
                {
                    D_ovl3_8018D048.unk_0xC[j] = i + 3;
                    D_ovl3_8018D048.unk_0x14[j] = item_count_2;
                    item_count_2 += temp_t1->byte[i + 3];
                    j++;
                }
            }
            D_ovl3_8018D048.unk_0xC[j] = 32;
            D_ovl3_8018D048.unk_0x14[j] = item_count_2;

            temp_f18 = (s32)(D_ovl3_8018D048.unk_0x10 * 0.1F);

            if (temp_f18 != 0)
            {
                item_count_4 = temp_f18;
            }
            else item_count_4 = 1;

            D_ovl3_8018D048.unk_0x10 += item_count_4;
        }
    }
    else
    {
        D_ovl3_8018D048.unk_0x10 = 0U;
    }
}

// 0x8016F218
void itManager_InitMonsterVars(void)
{
    gMonsterData.monster_curr = gMonsterData.monster_prev = U8_MAX;
    gMonsterData.monster_count = (It_Kind_MbMonsterEnd - It_Kind_MbMonsterStart);
}

GObj* func_ovl3_8016F238(GObj *spawn_gobj, s32 index, Vec3f *pos, Vec3f *vel, u32 flags)
{
    return Article_Callback_Spawn[index](spawn_gobj, pos, vel, flags);
}

// 0x8016F280
void itManager_UpdateHitPositions(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);
    s32 i;

    for (i = 0; i < ip->item_hit.hitbox_count; i++)
    {
        switch (ip->item_hit.update_state)
        {
        case gmHitCollision_UpdateState_Disable:
            break;

        case gmHitCollision_UpdateState_New:
            ip->item_hit.hit_positions[i].pos.x = ip->item_hit.offset[i].x + DObjGetStruct(item_gobj)->translate.x;
            ip->item_hit.hit_positions[i].pos.y = ip->item_hit.offset[i].y + DObjGetStruct(item_gobj)->translate.y;
            ip->item_hit.hit_positions[i].pos.z = ip->item_hit.offset[i].z + DObjGetStruct(item_gobj)->translate.z;

            ip->item_hit.update_state = gmHitCollision_UpdateState_Transfer;

            ip->item_hit.hit_positions[i].unused1 = 0;
            ip->item_hit.hit_positions[i].unused2 = 0;
            break;

        case gmHitCollision_UpdateState_Transfer:
            ip->item_hit.update_state = gmHitCollision_UpdateState_Interpolate;

        case gmHitCollision_UpdateState_Interpolate:
            ip->item_hit.hit_positions[i].pos_prev = ip->item_hit.hit_positions[i].pos;

            ip->item_hit.hit_positions[i].pos.x = ip->item_hit.offset[i].x + DObjGetStruct(item_gobj)->translate.x;
            ip->item_hit.hit_positions[i].pos.y = ip->item_hit.offset[i].y + DObjGetStruct(item_gobj)->translate.y;
            ip->item_hit.hit_positions[i].pos.z = ip->item_hit.offset[i].z + DObjGetStruct(item_gobj)->translate.z;

            ip->item_hit.hit_positions[i].unused1 = 0;
            ip->item_hit.hit_positions[i].unused2 = 0;
            break;
        }
    }
}

// 0x8016F3D4
void itManager_UpdateHitVictimRecord(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);
    gmHitCollisionRecord *targets;
    itHitbox *it_hit;
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

                        targets->victim_flags.is_interact_hurt = targets->victim_flags.is_interact_shield = targets->victim_flags.is_interact_reflect = FALSE;

                        targets->victim_flags.interact_mask = GMHITCOLLISION_MASK_ALL;
                    }
                }
            }
        }
    }
}

// 0x8016F534
void itManager_ProcItemMain(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);
    Vec3f *translate;
    DObj *joint;

    if (ap->hitlag_timer != 0)
    {
        ap->hitlag_timer--;
    }
    if (ap->hitlag_timer <= 0)
    {
        func_8000DF34(item_gobj);
    }
    if (ap->hitlag_timer <= 0)
    {
        if (ap->proc_update != NULL)
        {
            if (ap->proc_update(item_gobj) != FALSE)
            {
                itMain_DestroyItem(item_gobj);
                return;
            }
        }
    }
    if (ap->is_allow_pickup)
    {
        ap->pickup_wait--;

        if (ap->pickup_wait <= ITEM_DESPAWN_FLASH_BEGIN_DEFAULT)
        {
            if (ap->pickup_wait == 0)
            {
                func_ovl2_8010066C(&DObjGetStruct(item_gobj)->translate, 1.0F);

                itMain_DestroyItem(item_gobj);

                return;
            }
            if (ap->pickup_wait & 1) // Make article invisible on odd frames
            {
                item_gobj->is_render ^= TRUE;
            }
        }

        if (ap->arrow_flash_timer == 0)
        {
            ap->arrow_flash_timer = ITEM_ARROW_FLASH_INT_DEFAULT;
        }
        ap->arrow_flash_timer--;
    }
    else item_gobj->is_render = FALSE;

    if (!(ap->is_hold))
    {
        joint = DObjGetStruct(item_gobj);

        translate = &DObjGetStruct(item_gobj)->translate;

        ap->coll_data.pos_curr = *translate;

        if (ap->hitlag_timer == 0)
        {
            translate->x += ap->phys_info.vel_air.x;
            translate->y += ap->phys_info.vel_air.y;
            translate->z += ap->phys_info.vel_air.z;
        }
        ap->coll_data.pos_prev.x = translate->x - ap->coll_data.pos_curr.x;
        ap->coll_data.pos_prev.y = translate->y - ap->coll_data.pos_curr.y;
        ap->coll_data.pos_prev.z = translate->z - ap->coll_data.pos_curr.z;

        if ((ap->is_attach_surface) && (func_ovl2_800FC67C(ap->attach_line_id) != FALSE))
        {
            mpCollData *coll_data = &ap->coll_data;

            func_ovl2_800FA7B8(ap->attach_line_id, &ap->coll_data.pos_correct);

            translate->x += coll_data->pos_correct.x;
            translate->y += coll_data->pos_correct.y;
            translate->z += coll_data->pos_correct.z;
        }

        else if ((ap->ground_or_air == GA_Ground) && (ap->coll_data.ground_line_id != -1) && (ap->coll_data.ground_line_id != -2) && (func_ovl2_800FC67C(ap->coll_data.ground_line_id) != FALSE))
        {
            func_ovl2_800FA7B8(ap->coll_data.ground_line_id, &ap->coll_data.pos_correct);

            translate->x += ap->coll_data.pos_correct.x;
            translate->y += ap->coll_data.pos_correct.y;
            translate->z += ap->coll_data.pos_correct.z;
        }
        else
        {
            ap->coll_data.pos_correct.z = 0.0F;
            ap->coll_data.pos_correct.y = 0.0F;
            ap->coll_data.pos_correct.x = 0.0F;
        }

        if ((translate->y < gpMapData->blastzone_bottom) || (gpMapData->blastzone_right < translate->x) || (translate->x < gpMapData->blastzone_left) || (gpMapData->blastzone_top < translate->y))
        {
            if ((ap->proc_dead == NULL) || (ap->proc_dead(item_gobj) != FALSE))
            {
                itMain_DestroyItem(item_gobj);
                return;
            }
        }
        if (ap->proc_map != NULL)
        {
            ap->coll_data.coll_mask_prev = ap->coll_data.coll_mask;
            ap->coll_data.coll_mask = 0;
            ap->coll_data.unk_0x64 = 0;
            ap->coll_data.coll_type = 0;
            ap->coll_data.unk_0x58 = 0;

            if (ap->proc_map(item_gobj) != FALSE)
            {
                itMain_DestroyItem(item_gobj);
                return;
            }
        }
        itManager_UpdateHitPositions(item_gobj);
        itManager_UpdateHitVictimRecord(item_gobj);
    }
    func_ovl3_801713B0(item_gobj);
}

// 0x8016F930
void itManager_UpdateHitVictimInteractStats(itHitbox *it_hit, GObj *victim_gobj, s32 hitbox_type, u32 interact_mask)
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
                it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Type_Reflect:
                it_hit->hit_targets[i].victim_flags.is_interact_reflect = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Type_Hit:
                it_hit->hit_targets[i].victim_flags.interact_mask = interact_mask;
                break;

            case gmHitCollision_Type_HurtRehit:
                it_hit->hit_targets[i].victim_flags.is_interact_hurt = TRUE;
                it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
                break;

            default: 
                break;
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
            it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
            break;

        case gmHitCollision_Type_Reflect:
            it_hit->hit_targets[i].victim_flags.is_interact_reflect = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
            break;

        case gmHitCollision_Type_Hit:
            it_hit->hit_targets[i].victim_flags.interact_mask = interact_mask;
            break;

        case gmHitCollision_Type_HurtRehit:
            it_hit->hit_targets[i].victim_flags.is_interact_hurt = TRUE;
            it_hit->hit_targets[i].victim_flags.timer_rehit = ITEM_REHIT_TIME_DEFAULT;
            break;

        default: 
            break;
        }
    }
}

// 0x8016FB18 - Item's hurtbox gets hit by a fighter
void itManager_UpdateDamageStatFighter(ftStruct *fp, ftHitbox *ft_hit, itStruct *ap, itHurtbox *at_hurt, GObj *fighter_gobj, GObj *item_gobj)
{
    s32 damage;
    f32 damage_knockback;
    Vec3f sp4C;

    func_ovl2_800E26BC(fp, ft_hit->group_id, item_gobj, gmHitCollision_Type_Hurt, 0, FALSE);

    damage = ft_hit->damage;

    if (fp->attack_damage < damage)
    {
        fp->attack_damage = damage;
    }
    if (at_hurt->hitstatus == gmHitCollision_HitStatus_Normal)
    {
        ap->damage_queue += damage;

        if (ap->damage_highest < damage)
        {
            ap->damage_highest = damage;
            ap->damage_angle = ft_hit->angle;
            ap->damage_element = ft_hit->element;

            ap->lr_damage = (DObjGetStruct(item_gobj)->translate.x < DObjGetStruct(fighter_gobj)->translate.x) ? RIGHT : LEFT;

            ap->damage_gobj = fighter_gobj;
            ap->damage_team = fp->team;
            ap->damage_port = fp->player;
            ap->damage_player_number = fp->player_number;
            ap->damage_handicap = fp->handicap;
            ap->damage_display_mode = fp->display_mode;
        }
        if (ap->is_allow_knockback)
        {
            damage_knockback = gmCommonObject_DamageCalcKnockback(ap->percent_damage, ap->damage_queue, damage, ft_hit->knockback_weight, ft_hit->knockback_scale, ft_hit->knockback_base, 1.0F, fp->handicap, ap->handicap);

            if (ap->damage_knockback < damage_knockback)
            {
                ap->damage_knockback = damage_knockback;
            }
        }
        func_ovl2_800F0AF8(&sp4C, ft_hit, at_hurt, item_gobj);

        switch (ft_hit->element)
        {
        case gmHitCollision_Element_Fire:
            func_ovl2_800FE2F4(&sp4C, ft_hit->damage);
            break;
        case gmHitCollision_Element_Electric:
            func_ovl2_800FE4EC(&sp4C, ft_hit->damage);
            break;
        case gmHitCollision_Element_Coin:
            func_ovl2_80100ACC(&sp4C);
            break;
        case gmHitCollision_Element_Slash:
            func_ovl2_800FE6E4(&sp4C, ft_hit->damage, func_ovl2_800F0FC0(fp, ft_hit));
            break;
        default:
            func_ovl2_800FDC04(&sp4C, fp->player, ft_hit->damage, 0);
            break;
        }
    }
    func_ovl2_800E2C24(fp, ft_hit);
}

// 0x8016FD4C
void itManager_UpdateAttackStatItem(itStruct *this_ap, itHitbox *this_hit, s32 this_hit_id, itStruct *victim_ap, itHitbox *victim_hit, s32 victim_hit_id, GObj *this_gobj, GObj *victim_gobj)
{
    s32 victim_hit_damage;
    s32 this_hit_damage;
    Vec3f sp2C;
    s32 victim_hit_priority;
    s32 this_hit_priority;

    victim_hit_damage = itMain_ApplyHitDamage(victim_ap);
    this_hit_damage = itMain_ApplyHitDamage(this_ap);

    func_ovl2_800F0EFC(&sp2C, victim_hit, victim_hit_id, this_hit, this_hit_id);

    this_hit_priority = this_hit->priority;
    victim_hit_priority = victim_hit->priority;

    if (this_hit_priority >= victim_hit->priority)
    {
        itManager_UpdateHitVictimInteractStats(victim_hit, this_gobj, gmHitCollision_Type_Hit, 0);

        if (victim_ap->hit_attack_damage < victim_hit_damage)
        {
            victim_ap->hit_attack_damage = victim_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, victim_hit_damage);

        this_hit_priority = this_hit->priority;
        victim_hit_priority = victim_hit->priority;
    }
    if (victim_hit_priority >= this_hit_priority)
    {
        itManager_UpdateHitVictimInteractStats(this_hit, victim_gobj, gmHitCollision_Type_Hit, 0);

        if (this_ap->hit_attack_damage < this_hit_damage)
        {
            this_ap->hit_attack_damage = this_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, this_hit_damage);
    }
}

// 0x8016FE4C
void itManager_UpdateAttackStatWeapon(wpStruct *ip, wpHitbox *wp_hit, s32 wp_hit_id, itStruct *ap, itHitbox *it_hit, s32 it_hit_id, GObj *weapon_gobj, GObj *item_gobj)
{
    s32 wp_hit_damage = wpMain_DamageApplyStale(ip);
    s32 it_hit_damage = itMain_ApplyHitDamage(ap);
    Vec3f sp2C;
    s32 it_hit_priority;
    s32 wp_hit_priority;

    func_ovl2_800F0CDC(&sp2C, wp_hit, wp_hit_id, it_hit, it_hit_id);

    wp_hit_priority = wp_hit->priority;
    it_hit_priority = it_hit->priority;

    if (wp_hit_priority >= it_hit->priority)
    {
        itManager_UpdateHitVictimInteractStats(it_hit, weapon_gobj, gmHitCollision_Type_Hit, 0);

        if (ap->hit_attack_damage < it_hit_damage)
        {
            ap->hit_attack_damage = it_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, it_hit_damage);

        wp_hit_priority = wp_hit->priority;
        it_hit_priority = it_hit->priority;
    }
    if (it_hit_priority >= wp_hit_priority)
    {
        func_ovl3_8016679C(ip, wp_hit, item_gobj, gmHitCollision_Type_Hit, 0);

        if (ip->hit_attack_damage < wp_hit_damage)
        {
            ip->hit_attack_damage = wp_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, wp_hit_damage);
    }
}

// 0x8016FF4C - Article's hurtbox gets hit by another article
void itManager_UpdateDamageStatItem(itStruct *attack_ap, itHitbox *attack_it_hit, s32 arg2, itStruct *defend_ap, itHurtbox *at_hurt, GObj *attack_gobj, GObj *defend_gobj)
{
    s32 damage;
    f32 launch_angle;
    s32 unk_bool;
    f32 vel;
    Vec3f sp4C;
    s32 lr;
    s32 unused;

    damage = itMain_ApplyHitDamage(attack_ap);

    unk_bool = (((defend_ap->type == It_Type_Ground) && (attack_it_hit->can_rehit_item)) ? TRUE : FALSE);

    itManager_UpdateHitVictimInteractStats(attack_it_hit, defend_gobj, ((unk_bool != FALSE) ? gmHitCollision_Type_HurtRehit : gmHitCollision_Type_Hurt), 0);

    if (unk_bool != FALSE)
    {
        if (attack_ap->hit_refresh_damage < damage)
        {
            attack_ap->hit_refresh_damage = damage;
        }
    }
    else if (attack_ap->hit_normal_damage < damage)
    {
        attack_ap->hit_normal_damage = damage;
    }
    vel = (attack_ap->phys_info.vel_air.x < 0.0F) ? -attack_ap->phys_info.vel_air.x : attack_ap->phys_info.vel_air.x;

    if (vel < 5.0F)
    {
        attack_ap->lr_attack = lr = (DObjGetStruct(defend_gobj)->translate.x < DObjGetStruct(attack_gobj)->translate.x) ? LEFT : RIGHT;
    }
    else
    {
        lr = (attack_ap->phys_info.vel_air.x < 0) ? LEFT : RIGHT;

        attack_ap->lr_attack = lr;
    }
    if (at_hurt->hitstatus == gmHitCollision_HitStatus_Normal)
    {
        defend_ap->damage_queue += damage;

        if (defend_ap->damage_highest < damage)
        {
            defend_ap->damage_highest = damage; // Last source of damage?
            defend_ap->damage_angle = attack_it_hit->angle;
            defend_ap->damage_element = attack_it_hit->element;

            vel = (attack_ap->phys_info.vel_air.x < 0.0F) ? -attack_ap->phys_info.vel_air.x : attack_ap->phys_info.vel_air.x;

            if (vel < 5.0F)
            {
                defend_ap->lr_hit = lr = (DObjGetStruct(defend_gobj)->translate.x < DObjGetStruct(attack_gobj)->translate.x) ? RIGHT : LEFT;
            }
            else
            {
                lr = (attack_ap->phys_info.vel_air.x < 0) ? RIGHT : LEFT;

                defend_ap->lr_hit = lr;
            }
            defend_ap->damage_gobj = attack_ap->owner_gobj;
            defend_ap->damage_team = attack_ap->team;
            defend_ap->damage_port = attack_ap->player;
            defend_ap->damage_player_number = attack_ap->player_number;
            defend_ap->damage_handicap = attack_ap->handicap;
            defend_ap->damage_display_mode = attack_ap->display_mode;
        }
        if (defend_ap->is_allow_knockback)
        {
            launch_angle = gmCommonObject_DamageCalcKnockback(defend_ap->percent_damage, defend_ap->damage_queue, damage, attack_it_hit->knockback_weight, attack_it_hit->knockback_scale, attack_it_hit->knockback_base, 1.0f, attack_ap->handicap, )defend_ap->handicap);

            if (defend_ap->damage_knockback < launch_angle)
            {
                defend_ap->damage_knockback = launch_angle;
            }
        }
        if (attack_ap->is_hitlag_victim)
        {
            func_ovl2_800F0F44(&sp4C, attack_it_hit, arg2, at_hurt, defend_gobj);

            switch (attack_it_hit->element)
            {
            case gmHitCollision_Element_Fire:
                func_ovl2_800FE2F4(&sp4C, damage);
                break;
            case gmHitCollision_Element_Electric:
                func_ovl2_800FE4EC(&sp4C, damage);
                break;
            case gmHitCollision_Element_Coin:
                func_ovl2_80100ACC(&sp4C);
                break;

            default:
                func_ovl2_800FDC04(&sp4C, attack_ap->player, damage, 0);
                break;
            }
        }
    }
    func_800269C0(attack_it_hit->hit_sfx);
}

// 0x801702C8 - Article's hurtbox gets hit by an item
void itManager_UpdateDamageStatWeapon(wpStruct *ip, wpHitbox *wp_hit, s32 arg2, itStruct *ap, itHurtbox *at_hurt, GObj *weapon_gobj, GObj *item_gobj)
{
    s32 damage;
    s32 unused;
    s32 unk_bool;
    f32 angle;
    Vec3f sp4C;
    f32 vel;
    s32 lr;

    damage = wpMain_DamageApplyStale(ip);

    unk_bool = ((ap->type == It_Type_Ground) && (wp_hit->can_rehit_item)) ? TRUE : FALSE;

    func_ovl3_8016679C(ip, wp_hit, item_gobj, ((unk_bool != FALSE) ? gmHitCollision_Type_HurtRehit : gmHitCollision_Type_Hurt), 0);

    if (unk_bool != FALSE)
    {
        if (ip->hit_refresh_damage < damage)
        {
            ip->hit_refresh_damage = damage;
        }
    }
    else if (ip->hit_normal_damage < damage)
    {
        ip->hit_normal_damage = damage;
    }
    if (at_hurt->hitstatus == gmHitCollision_HitStatus_Normal)
    {
        ap->damage_queue += damage;

        if (ap->damage_highest < damage)
        {
            ap->damage_highest = damage;
            ap->damage_angle = wp_hit->angle;
            ap->damage_element = wp_hit->element;

            vel = (ip->phys_info.vel_air.x < 0.0F) ? -ip->phys_info.vel_air.x : ip->phys_info.vel_air.x;

            if (vel < 5.0F)
            {
                ap->lr_hit = lr = (DObjGetStruct(item_gobj)->translate.x < DObjGetStruct(weapon_gobj)->translate.x) ? RIGHT : LEFT;
            }
            else
            {
                lr = (ip->phys_info.vel_air.x < 0) ? RIGHT : LEFT;

                ap->lr_hit = lr;
            }
            ap->damage_gobj = ip->owner_gobj;
            ap->damage_team = ip->team;
            ap->damage_port = ip->player;
            ap->damage_player_number = ip->player_number;
            ap->damage_handicap = ip->handicap;
            ap->damage_display_mode = ip->display_mode;
        }
        if (ap->is_allow_knockback)
        {
            angle = gmCommonObject_DamageCalcKnockback(ap->percent_damage, ap->damage_queue, damage, wp_hit->knockback_weight, wp_hit->knockback_scale, wp_hit->knockback_base, 1.0F, ip->handicap, ap->handicap);

            if (ap->damage_knockback < angle)
            {
                ap->damage_knockback = angle;
            }
        }
        if (ip->is_hitlag_victim)
        {
            func_ovl2_800F0D8C(&sp4C, wp_hit, arg2, at_hurt, item_gobj);

            switch (wp_hit->element)
            {
            case gmHitCollision_Element_Fire:
                func_ovl2_800FE2F4(&sp4C, damage);
                break;

            case gmHitCollision_Element_Electric:
                func_ovl2_800FE4EC(&sp4C, damage);
                break;

            case gmHitCollision_Element_Coin:
                func_ovl2_80100ACC(&sp4C);
                break;

            default:
                func_ovl2_800FDC04(&sp4C, ip->player, damage, NULL);
                break;
            }
        }
    }
    func_800269C0(wp_hit->hit_sfx);
}

extern s32 D_ovl2_801311A0[4]; // Static, array count might depend on GMMATCH_PLAYERS_MAX?

// 0x801705C4
void itManager_SearchHitFighter(GObj *item_gobj) // Check fighters for hit detection
{
    GObj *fighter_gobj;
    GObj *owner_gobj;
    s32 i;
    s32 k;
    s32 unused;
    s32 j;
    GObj *other_gobj;
    u32 team;
    ftHitbox *ft_hit;
    gmHitCollisionFlags fighter_victim_flags;
    itHurtbox *at_hurt;
    itStruct *ap = itGetStruct(item_gobj);
    ftStruct *fp;

    if (ap->item_hurt.interact_mask & GMHITCOLLISION_MASK_FIGHTER)
    {
        fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

        if (fighter_gobj != NULL)
        {
            do
            {
                owner_gobj = other_gobj = ap->owner_gobj; // Mandatory IDO meme because otherwise it swaps a0 and v1

                if ((fighter_gobj != ap->owner_gobj) || (ap->is_damage_all))
                {
                    fp = ftGetStruct(fighter_gobj);

                    if ((gpBattleState->is_team_battle != TRUE) || (gpBattleState->is_team_attack != FALSE) || (((fp->throw_gobj != NULL) ? fp->throw_team : fp->team) != ap->team) || (ap->is_damage_all))
                    {
                        if (!(fp->is_catchstatus))
                        {
                            k = 0;

                            if ((ap->owner_gobj == NULL) || (fp->throw_gobj == NULL) || (fp->throw_gobj != ap->owner_gobj))
                            {
                                for (i = 0; i < ARRAY_COUNT(D_ovl2_801311A0); i++)
                                {
                                    ft_hit = &fp->fighter_hit[i];

                                    if ((ft_hit->update_state != gmHitCollision_UpdateState_Disable) && ((ap->ground_or_air == GA_Air) && (ft_hit->is_hit_air) || (ap->ground_or_air == GA_Ground) && (ft_hit->is_hit_ground)))
                                    {
                                        fighter_victim_flags.is_interact_hurt = fighter_victim_flags.is_interact_shield = FALSE;

                                        fighter_victim_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                                        for (j = 0; j < ARRAY_COUNT(ft_hit->hit_targets); j++)
                                        {
                                            if (item_gobj == ft_hit->hit_targets[j].victim_gobj)
                                            {
                                                fighter_victim_flags = ft_hit->hit_targets[j].victim_flags;
                                                break;
                                            }
                                        }
                                        if ((!(fighter_victim_flags.is_interact_hurt)) && (!(fighter_victim_flags.is_interact_shield)) && (fighter_victim_flags.interact_mask == GMHITCOLLISION_MASK_ALL))
                                        {
                                            D_ovl2_801311A0[i] = TRUE;
                                            k++;

                                            continue;
                                        }
                                    }
                                    D_ovl2_801311A0[i] = FALSE;
                                }
                                if (k != 0)
                                {
                                    for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
                                    {
                                        at_hurt = &ap->item_hurt;

                                        if (D_ovl2_801311A0[i] != 0)
                                        {
                                            if (ap->item_hurt.hitstatus == gmHitCollision_HitStatus_None) break;

                                            if (at_hurt->hitstatus != gmHitCollision_HitStatus_Intangible)
                                            {
                                                if (func_ovl2_800EFC20(&fp->fighter_hit[i], at_hurt, item_gobj) != FALSE)
                                                {
                                                    itManager_UpdateDamageStatFighter(fp, &fp->fighter_hit[i], ap, at_hurt, fighter_gobj, item_gobj);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                fighter_gobj = fighter_gobj->group_gobj_next;
            } 
            while (fighter_gobj != NULL);
        }
    }
}

// 0x8017088C
void itManager_SearchHitItem(GObj *this_gobj) // Check other articles for hit detection
{
    itHitbox *this_hit;
    itStruct *other_ap;
    itStruct *this_ap;
    GObj *other_gobj;
    itHitbox *other_hit;
    gmHitCollisionFlags these_flags, those_flags;
    s32 i, j, m, n;
    bool32 is_check_self;
    itHurtbox *at_hurt;

    this_ap = itGetStruct(this_gobj);
    this_hit = &this_ap->item_hit;

    if (this_ap->item_hurt.interact_mask & GMHITCOLLISION_MASK_ITEM)
    {
        other_gobj = gOMObjCommonLinks[gOMObjLinkIndexItem];

        is_check_self = FALSE;

        while (other_gobj != NULL)
        {
            if (other_gobj == this_gobj)
            {
                is_check_self = TRUE;
            }
            else
            {
                other_ap = itGetStruct(other_gobj);
                other_hit = &other_ap->item_hit;

                if ((this_ap->owner_gobj != other_ap->owner_gobj) || (this_ap->is_damage_all))
                {
                    if ((gpBattleState->is_team_battle != TRUE) || (gpBattleState->is_team_attack != FALSE) || (this_ap->team != other_ap->team) || (this_ap->is_damage_all))
                    {
                        if (other_hit->update_state != gmHitCollision_UpdateState_Disable)
                        {
                            if (other_hit->interact_mask & GMHITCOLLISION_MASK_ITEM)
                            {
                                those_flags.is_interact_hurt = those_flags.is_interact_shield = FALSE;

                                those_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                                for (m = 0; m < ARRAY_COUNT(other_hit->hit_targets); m++) // IDO will flip you off if you don't use a new iterator here...
                                {
                                    if (this_gobj == other_hit->hit_targets[m].victim_gobj)
                                    {
                                        those_flags = other_hit->hit_targets[m].victim_flags;

                                        break;
                                    }
                                }
                                if ((!(those_flags.is_interact_hurt)) && (!(those_flags.is_interact_shield)) && (those_flags.interact_mask == GMHITCOLLISION_MASK_ALL))
                                {
                                    if ((is_check_self != FALSE) && (this_hit->rebound) && (other_hit->rebound) && (this_ap->owner_gobj != other_ap->owner_gobj))
                                    {
                                        if ((gpBattleState->is_team_battle != TRUE) || (gpBattleState->is_team_attack != FALSE) || (this_ap->team != other_ap->team))
                                        {
                                            if ((this_hit->update_state != gmHitCollision_UpdateState_Disable) && (this_hit->interact_mask & GMHITCOLLISION_MASK_ITEM))
                                            {
                                                these_flags.is_interact_hurt = these_flags.is_interact_shield = FALSE;

                                                these_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                                                for (n = 0; n < ARRAY_COUNT(this_hit->hit_targets); n++)
                                                {
                                                    if (other_gobj == this_hit->hit_targets[n].victim_gobj)
                                                    {
                                                        these_flags = this_hit->hit_targets[n].victim_flags;
                                                        break;
                                                    }
                                                }

                                                if ((these_flags.is_interact_hurt) || (these_flags.is_interact_shield) || (these_flags.interact_mask != GMHITCOLLISION_MASK_ALL)) goto hurtbox_check;

                                                else for (i = 0; i < other_hit->hitbox_count; i++)
                                                {
                                                    for (j = 0; j < this_hit->hitbox_count; j++)
                                                    {
                                                        if (func_ovl2_800F05C8(other_hit, i, this_hit, j) != FALSE)
                                                        {
                                                            itManager_UpdateAttackStatItem(other_ap, other_hit, i, this_ap, this_hit, j, other_gobj, this_gobj);

                                                            if (other_ap->hit_attack_damage == 0)
                                                            {
                                                                if (this_ap->hit_attack_damage != 0) goto hurtbox_check;
                                                            }
                                                            else goto next_gobj;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                hurtbox_check:
                                    for (i = 0; i < other_hit->hitbox_count; i++) // ...it also flips you off if you DON'T reuse 'i' here
                                    {
                                        at_hurt = &this_ap->item_hurt;

                                        if (this_ap->item_hurt.hitstatus == gmHitCollision_HitStatus_None) break;

                                        else if (at_hurt->hitstatus == gmHitCollision_HitStatus_Intangible) continue;

                                        else if (func_ovl2_800F06E8(other_hit, i, at_hurt, this_gobj) != FALSE)
                                        {
                                            itManager_UpdateDamageStatItem(other_ap, other_hit, i, this_ap, at_hurt, other_gobj, this_gobj);

                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        next_gobj:
            other_gobj = other_gobj->group_gobj_next;
        }
    }
}

// 0x80170C84
void itManager_SearchHitWeapon(GObj *item_gobj) // Check items for hit detection
{
    itHitbox *it_hit;
    wpStruct *ip;
    itStruct *ap;
    GObj *weapon_gobj;
    wpHitbox *wp_hit;
    gmHitCollisionFlags these_flags;
    gmHitCollisionFlags those_flags;
    s32 i, j, m, n;
    bool32 is_check_self;
    itHurtbox *at_hurt;

    ap = itGetStruct(item_gobj);
    it_hit = &ap->item_hit;

    if (ap->item_hurt.interact_mask & GMHITCOLLISION_MASK_WEAPON)
    {
        weapon_gobj = gOMObjCommonLinks[gOMObjLinkIndexWeapon];

        while (weapon_gobj != NULL)
        {
            ip = wpGetStruct(weapon_gobj);
            wp_hit = &ip->weapon_hit;

            if ((ap->owner_gobj != ip->owner_gobj) || (ap->is_damage_all))
            {
                if ((gpBattleState->is_team_battle != TRUE) || (gpBattleState->is_team_attack != FALSE) || (ap->team != ip->team) || (ap->is_damage_all))
                {
                    if (wp_hit->update_state != 0)
                    {
                        if (wp_hit->interact_mask & GMHITCOLLISION_MASK_ITEM)
                        {
                            those_flags.is_interact_hurt = those_flags.is_interact_shield = FALSE;

                            those_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                            for (m = 0; m < ARRAY_COUNT(wp_hit->hit_targets); m++) // IDO will flip you off if you don't use a new iterator here...
                            {
                                if (item_gobj == wp_hit->hit_targets[m].victim_gobj)
                                {
                                    those_flags = wp_hit->hit_targets[m].victim_flags;
                                    break;
                                }
                            }
                            if ((!(those_flags.is_interact_hurt)) && (!(those_flags.is_interact_shield)) && (those_flags.interact_mask == GMHITCOLLISION_MASK_ALL))
                            {
                                if ((it_hit->rebound) && (wp_hit->rebound) && (ap->owner_gobj != ip->owner_gobj))
                                {
                                    if ((gpBattleState->is_team_battle != TRUE) || (gpBattleState->is_team_attack != FALSE) || (ap->team != ip->team))
                                    {
                                        if ((it_hit->update_state != gmHitCollision_UpdateState_Disable) && (it_hit->interact_mask & GMHITCOLLISION_MASK_WEAPON))
                                        {
                                            these_flags.is_interact_hurt = these_flags.is_interact_shield = FALSE;

                                            these_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                                            for (n = 0; n < ARRAY_COUNT(it_hit->hit_targets); n++)
                                            {
                                                if (weapon_gobj == it_hit->hit_targets[n].victim_gobj)
                                                {
                                                    these_flags = it_hit->hit_targets[n].victim_flags;

                                                    break;
                                                }
                                            }

                                            if ((these_flags.is_interact_hurt) || (these_flags.is_interact_shield) || (these_flags.interact_mask != GMHITCOLLISION_MASK_ALL)) goto hurtbox_check;

                                            else for (i = 0; i < wp_hit->hitbox_count; i++)
                                            {
                                                for (j = 0; j < it_hit->hitbox_count; j++)
                                                {
                                                    if (func_ovl2_800F019C(wp_hit, i, it_hit, j) != FALSE)
                                                    {
                                                        itManager_UpdateAttackStatWeapon(ip, wp_hit, i, ap, it_hit, j, weapon_gobj, item_gobj);

                                                        if (ip->hit_attack_damage != 0) goto next_gobj;

                                                        else if (ap->hit_attack_damage != 0) goto hurtbox_check;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            hurtbox_check:
                                for (i = 0; i < wp_hit->hitbox_count; i++) // ...it also flips you off if you DON'T reuse 'i' here
                                {
                                    at_hurt = &ap->item_hurt;

                                    if (ap->item_hurt.hitstatus == gmHitCollision_HitStatus_None) break;

                                    else if (at_hurt->hitstatus == gmHitCollision_HitStatus_Intangible) continue;

                                    else if (func_ovl2_800F079C(wp_hit, i, at_hurt, item_gobj) != FALSE)
                                    {
                                        itManager_UpdateDamageStatWeapon(ip, wp_hit, i, ap, at_hurt, weapon_gobj, item_gobj);

                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        next_gobj:
            weapon_gobj = weapon_gobj->group_gobj_next;
        }
    }
}

// Copy pasted everything from Article VS Article hit collision logic and it instantly matched 82% of Article VS Item, even the stack; apparently in a much similar fashion to HAL

// 0x80171080
void itManager_ProcSearchHitAll(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);

    if (!(ip->is_hold))
    {
        itManager_SearchHitFighter(item_gobj);
        itManager_SearchHitItem(item_gobj);
        itManager_SearchHitWeapon(item_gobj);
    }
}

// 0x801710C4
void itManager_ProcUpdateHitCollisions(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);

    if (ap->damage_queue != 0)
    {
        ap->percent_damage += ap->damage_queue;

        if (ap->percent_damage > PERCENT_DAMAGE_MAX)
        {
            ap->percent_damage = PERCENT_DAMAGE_MAX;
        }
        ap->damage_lag = ap->damage_queue;

        if (ap->proc_damage != NULL)
        {
            if (ap->proc_damage(item_gobj) != FALSE)
            {
                itMain_DestroyItem(item_gobj);
                return;
            }
        }
    }
    if ((ap->hit_normal_damage != 0) || (ap->hit_refresh_damage != 0))
    {
        if (ap->proc_hit != NULL)
        {
            if (ap->proc_hit(item_gobj) != FALSE)
            {
                itMain_DestroyItem(item_gobj);
                return;
            }
        }
    }
    if (ap->hit_shield_damage != 0)
    {
        if ((ap->item_hit.can_hop) && (ap->ground_or_air == GA_Air))
        {
            if (ap->shield_collide_angle < ITEM_HOP_ANGLE_DEFAULT)
            {
                ap->shield_collide_angle -= HALF_PI32;

                if (ap->shield_collide_angle < 0.0F)
                {
                    ap->shield_collide_angle = 0.0F;
                }
                if (ap->proc_hop != NULL)
                {
                    if (ap->proc_hop(item_gobj) != FALSE)
                    {
                        itMain_DestroyItem(item_gobj);
                        return;
                    }
                }
                goto next_check;
            }
        }
        if (ap->proc_shield != NULL)
        {
            if (ap->proc_shield(item_gobj) != FALSE)
            {
                itMain_DestroyItem(item_gobj);
                return;
            }
        }
    }
next_check:
    if (ap->hit_attack_damage != 0)
    {
        if (ap->proc_setoff != NULL)
        {
            if (ap->proc_setoff(item_gobj) != FALSE)
            {
                itMain_DestroyItem(item_gobj);
                return;
            }
        }
    }
    if (ap->reflect_gobj != NULL)
    {
        ftStruct *fp;

        ap->owner_gobj = ap->reflect_gobj;

        fp = ftGetStruct(ap->reflect_gobj);

        ap->team = fp->team;
        ap->player = fp->player;
        ap->player_number = fp->player_number;
        ap->handicap = fp->handicap;
        ap->item_hit.stat_flags = ap->reflect_stat_flags;
        ap->item_hit.stat_count = ap->reflect_stat_count;

        if (ap->proc_reflector != NULL)
        {
            if (ap->proc_reflector(item_gobj) != FALSE)
            {
                itMain_DestroyItem(item_gobj);
                return;
            }
        }
        if (!(ap->is_static_damage))
        {
            ap->item_hit.damage = (ap->item_hit.damage * ITEM_REFLECT_MUL_DEFAULT) + ITEM_REFLECT_ADD_DEFAULT;

            if (ap->item_hit.damage > ITEM_REFLECT_MAX_DEFAULT)
            {
                ap->item_hit.damage = ITEM_REFLECT_MAX_DEFAULT;
            }
        }
    }
    if (ap->damage_lag != 0)
    {
        ap->hitlag_timer = gmCommon_DamageCalcHitLag(ap->damage_lag, ftStatus_Common_Wait, 1.0F); // Maybe 10 is the "none" status ID?
    }

    ap->hit_normal_damage = 0;
    ap->hit_refresh_damage = 0;
    ap->hit_attack_damage = 0;
    ap->hit_shield_damage = 0;
    ap->reflect_gobj = NULL;
    ap->damage_highest = 0;
    ap->damage_queue = 0;
    ap->damage_lag = 0;
    ap->damage_knockback = 0.0F;
}

void func_ovl3_801713B0(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);

    if (caMain_UpdateColAnim(&ap->colanim, item_gobj, 0, 0) != FALSE)
    {
        func_ovl3_80172FBC(item_gobj);
    }
}

// 0x801713F4
void itManager_UpdateSpin(GObj *item_gobj)
{
    itStruct *ip = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->rotate.z += ip->rotate_step;
}