#include "item.h"
#include "fighter.h"
#include "gmmatch.h"

void func_ovl3_80172310(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->rotate_speed = (ip->attributes->spin_speed != 0) ? (ip->attributes->spin_speed * ITEM_SPIN_SPEED_FRACTION_DEFAULT * ITEM_SPIN_SPEED_MUL_DEFAULT) : 0.0F;

    if (ip->lr == LEFT)
    {
        ip->rotate_speed = -ip->rotate_speed;
    }
}

void func_ovl3_80172394(GObj *item_gobj, bool32 is_prev_spawn)
{
    // is_prev_spawn = whether article is newly spawned or previously spawned; 0 = new, 1 = old

    Item_Struct *ip = itGetStruct(item_gobj); // Ternary doesn't match here smh

    if (is_prev_spawn == FALSE)
    {
        if (ip->attributes->spin_speed != 0)
        {
            ip->rotate_speed = ip->attributes->spin_speed * ITEM_SPIN_SPEED_FRACTION_DEFAULT * ITEM_SPIN_SPEED_MUL_NEW_SPAWN;
        }
        else ip->rotate_speed = 0.0F;
    }
    else if (ip->attributes->spin_speed != 0)
    {
        ip->rotate_speed = ip->attributes->spin_speed * ITEM_SPIN_SPEED_FRACTION_DEFAULT * ITEM_SPIN_SPEED_MUL_PREV_SPAWN;
    }
    else ip->rotate_speed = 0.0F;
}

void func_ovl3_8017245C(GObj *item_gobj, f32 *spin_speed, bool32 is_smash_throw)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->rotate_speed = (is_smash_throw != FALSE) ? ITEM_SPIN_SPEED_SET_SMASH_THROW : ITEM_SPIN_SPEED_SET_NORMAL_THROW;

    if (*spin_speed < 0) // Facing direction, sort of
    {
        ip->rotate_speed = -ip->rotate_speed;
    }

    ip->rotate_speed = (ip->attributes->spin_speed != 0) ? (ip->attributes->spin_speed * ITEM_SPIN_SPEED_FRACTION_DEFAULT * ip->rotate_speed) : 0.0F;
}

void func_ovl3_80172508(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->lr = (ip->phys_info.vel.x >= 0.0F) ? RIGHT : LEFT;

    func_ovl3_80172310(item_gobj);
}

void func_ovl3_80172558(Item_Struct *ip, f32 gravity, f32 terminal_velocity)
{
    ip->phys_info.vel.y -= gravity;

    if (terminal_velocity < func_ovl0_800C7A84(&ip->phys_info.vel))
    {
        func_ovl0_800C7A00(&ip->phys_info.vel);
        func_ovl0_800C7AE0(&ip->phys_info.vel, terminal_velocity);
    }
}

extern s32 dbObjDisplayStatus_Global_Article; // Static (.bss)

void func_ovl3_801725BC(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->owner_gobj = NULL;
    ip->team = ITEM_TEAM_DEFAULT;
    ip->port_id = ITEM_PORT_DEFAULT;
    ip->handicap = ITEM_HANDICAP_DEFAULT;
    ip->player_number = 0;
    ip->item_hit.stale = ITEM_STALE_DEFAULT;

    ip->display_state = dbObjDisplayStatus_Global_Article;
}

void func_ovl3_801725F8(Item_Struct *ip)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(ip->item_hit.hit_targets); i++)
    {
        gmHitCollisionRecord *targets = &ip->item_hit.hit_targets[i];

        targets->victim_gobj = NULL;

        targets->victim_flags.is_interact_hurt = targets->victim_flags.is_interact_shield = targets->victim_flags.is_interact_reflect = FALSE;

        targets->victim_flags.timer_rehit = 0;

        targets->victim_flags.interact_mask = GMHITCOLLISION_MASK_ALL;
    }
}

void func_ovl3_8017275C(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_801725F8(ip);

    ip->item_hit.update_state = gmHitCollision_UpdateState_New;

    itManager_UpdateHitPositions(item_gobj);
}

void func_ovl3_8017279C(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_damage_all = TRUE;

    ip->owner_gobj = NULL;

    ip->team = ITEM_TEAM_DEFAULT;
}

void func_ovl3_801727BC(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->owner_gobj = ip->damage_gobj;
    ip->team = ip->damage_team;
    ip->port_id = ip->damage_port;
    ip->player_number = ip->player_number; // Could potentially cause a bug? Didn't they mean damage_player_number?
    ip->handicap = ip->damage_handicap;
    ip->display_state = ip->damage_display_state;
}

s32 func_ovl3_801727F4(Item_Struct *ip)
{
    s32 damage;

    if (ip->is_apply_mag_stale)
    {
        f32 mag = vec3f_mag(&ip->phys_info.vel) * 0.1F;

        damage = (ip->item_hit.damage + mag) * ip->item_hit.stale;
    }
    else damage = ip->item_hit.damage;

    return (damage * ip->item_hit.throw_mul) + 0.999F;
}

// 0x80172890
bool32 atCommon_CheckTypeShootEmpty(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (((ip->it_kind == It_Kind_StarRod) || (ip->it_kind == It_Kind_L_Gun) || (ip->it_kind == It_Kind_F_Flower)) && (ip->it_multi == 0))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_801728D4(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if ((ip->is_hold) && (ip->owner_gobj != NULL))
    {
        Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

        fp->item_hold = NULL;

        ftCommon_GetHammerSetBGM(ip->owner_gobj);
    }
    else if ((ip->it_kind < It_Kind_GrMonsterStart) || (ip->it_kind > It_Kind_GrMonsterEnd))
    {
        func_ovl2_800FF590(&DObjGetStruct(item_gobj)->translate);
    }
    if (ip->indicator_gobj != NULL)
    {
        gOMObj_EjectGObjCommon(ip->indicator_gobj);
    }
    itManager_SetPrevAlloc(ip);
    gOMObj_EjectGObjCommon(item_gobj);
}

void func_ovl3_80172984(GObj *item_gobj, Vec3f *vel, f32 stale, u16 flag1, u16 flag2) // Very high probability that Link's Bomb erroneously declares this without flag1 and flag2
{
    Item_Struct *ip = itGetStruct(item_gobj);
    GObj *fighter_gobj = ip->owner_gobj;
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;
    s32 joint_index;

    func_ovl0_800C9424(DObjGetStruct(item_gobj));

    pos.z = 0.0F;
    pos.y = 0.0F;
    pos.x = 0.0F;

    joint_index = (ip->weight == It_Weight_Heavy) ? fp->attributes->joint_itemhold_heavy : fp->attributes->joint_itemhold_light;

    func_ovl2_800EDF24(fp->joint[joint_index], &pos);

    DObjGetStruct(item_gobj)->translate.x = pos.x;
    DObjGetStruct(item_gobj)->translate.y = pos.y;
    DObjGetStruct(item_gobj)->translate.z = 0.0F;

    func_ovl2_800DF058(item_gobj, fp->coll_data.p_translate, &fp->coll_data);

    fp->item_hold = NULL;

    ip->is_hold = FALSE;

    ip->phys_info.vel = *vel;

    vec3f_scale(&ip->phys_info.vel, ip->vel_scale);

    ip->times_thrown++;
    ip->is_apply_mag_stale = TRUE;

    ip->item_hit.stale = stale;

    ip->item_hit.stat_flags = *(gmAttackFlags*)&flag1;
    ip->item_hit.stat_count = flag2;

    ftCommon_GetHammerSetBGM(fighter_gobj);
    func_ovl3_8017275C(item_gobj);
}

extern void (*Article_Callback_Drop[])(GObj*); // Assumed to contain 45 callbacks?

void func_ovl3_80172AEC(GObj *item_gobj, Vec3f *vel, f32 stale)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    GObj *owner_gobj = ip->owner_gobj;
    Fighter_Struct *fp = ftGetStruct(owner_gobj);
    void (*proc_drop)(GObj*) = Article_Callback_Drop[ip->it_kind];

    if (proc_drop != NULL)
    {
        proc_drop(item_gobj);
    }
    func_ovl3_80172984(item_gobj, vel, stale, ftStatus_AttackIndex_ItemThrow, fp->stat_count);

    func_800269C0(ip->drop_sfx);
}

extern void (*Article_Callback_Throw[])(GObj*); 

void func_ovl3_80172B78(GObj *item_gobj, Vec3f *vel, f32 stale, bool32 is_smash_throw)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    GObj *owner_gobj = ip->owner_gobj;
    Fighter_Struct *fp = ftGetStruct(owner_gobj);
    void (*proc_throw)(GObj*);

    if (ip->weight == It_Weight_Light)
    {
        if (is_smash_throw != FALSE)
        {
            func_ovl2_800E806C(fp, 6, 0);
        }
    }
    else
    {
        func_ovl2_800E806C(fp, ((is_smash_throw != FALSE) ? 9 : 6), 0);
    }
    proc_throw = Article_Callback_Throw[ip->it_kind];

    if (proc_throw != NULL)
    {
        proc_throw(item_gobj);
    }
    func_ovl3_80172984(item_gobj, vel, stale, fp->stat_flags.halfword, fp->stat_count);

    func_ovl2_8010066C(&DObjGetStruct(item_gobj)->translate, 1.0F);

    func_800269C0(((is_smash_throw != FALSE) ? ip->throw_sfx : ip->drop_sfx));

    func_ovl3_8017245C(item_gobj, vel, is_smash_throw);
}

extern void (*Article_Callback_Pickup[])(GObj*);

// 0x80172CA4
void itMain_PickupSetHoldFighter(GObj *item_gobj, GObj *fighter_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    DObj *joint;
    void (*proc_get)(GObj*);
    Vec3f pos;
    s32 joint_index;

    fp->item_hold = item_gobj;
    ip->owner_gobj = fighter_gobj;

    ip->is_allow_pickup = FALSE;
    ip->is_hold = TRUE;

    ip->team = fp->team;
    ip->port_id = fp->port_id;
    ip->handicap = fp->handicap;
    ip->player_number = fp->player_number;

    ip->phys_info.vel.x = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.z = 0.0F;

    ip->display_state = fp->display_state;

    func_ovl3_80173F78(ip);

    joint = func_800092D0(item_gobj, NULL);

    joint->unk_0xC->unk_0x8 = NULL;
    joint->unk_0xC = NULL;
    joint->next = DObjGetStruct(item_gobj);

    DObjGetStruct(item_gobj)->prev = joint;

    item_gobj->obj = joint;

    func_80008CC0(joint, 0x52, 0);

    joint_index = (ip->weight == It_Weight_Heavy) ? fp->attributes->joint_itemhold_heavy : fp->attributes->joint_itemhold_light;

    joint->unk_0x84 = fp->joint[joint_index];

    pos.x = 0.0F;
    pos.y = 0.0F;
    pos.z = 0.0F;

    func_ovl2_800EDF24(fp->joint[joint_index], &pos);

    func_ovl2_80104458(&pos);

    func_8000F988(item_gobj, ip->attributes->unk_0x0);

    proc_get = Article_Callback_Pickup[ip->it_kind];

    if (proc_get != NULL)
    {
        proc_get(item_gobj);
    }
    ftLink_SetModelPartHideShield(fighter_gobj);

    if (ip->weight == It_Weight_Light)
    {
        func_800269C0(0x31U);
    }
    else
    {
        if (fp->attributes->heavyget_sfx != 0x2B7)
        {
            func_800269C0(fp->attributes->heavyget_sfx);
        }
    }
    func_ovl2_800E806C(fp, 6, 0);

    ip->pickup_wait = ITEM_PICKUP_WAIT_DEFAULT;
}

void func_ovl3_80172E74(GObj *item_gobj) // Airborne article becomes grounded?
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->is_allow_pickup = TRUE;
    ip->times_landed = 0;

    func_ovl3_801725BC(item_gobj);
    func_ovl3_80173F54(ip);
}

// 0x80172EC8
void itMain_SetItemStatus(GObj *item_gobj, itStatusDesc *status_desc, s32 status_id) // Change article state
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->proc_update = status_desc[status_id].proc_update;
    ip->proc_map = status_desc[status_id].proc_map;
    ip->proc_hit = status_desc[status_id].proc_hit;
    ip->proc_shield = status_desc[status_id].proc_shield;
    ip->proc_hop = status_desc[status_id].proc_hop;
    ip->proc_setoff = status_desc[status_id].proc_setoff;
    ip->proc_reflector = status_desc[status_id].proc_reflector;
    ip->proc_damage = status_desc[status_id].proc_damage;

    ip->is_apply_mag_stale = FALSE;

    ip->item_hit.stat_flags.attack_group_id = ftStatus_AttackIndex_Null;
    ip->item_hit.stat_flags.is_smash_attack = ip->item_hit.stat_flags.is_ground_or_air = ip->item_hit.stat_flags.is_special_attack = FALSE;

    ip->item_hit.stat_count = gmCommon_GetStatUpdateCountInc();
}

// 0x80172F98
bool32 atCommon_CheckSetColAnimIndex(GObj *item_gobj, s32 colanim_id, s32 duration)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    return caCheckSetColAnimIndex(&ip->colanim, colanim_id, duration);
}

void func_ovl3_80172FBC(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    caResetColAnim(&ip->colanim);
}

void func_ovl3_80172FE0(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->phys_info.vel.x *= -0.06F;

    ip->phys_info.vel.y = (ip->phys_info.vel.y * -0.3F) + 25.0F;
}

 // Oh my...

typedef struct Unk_8017301C_Halfword // CODE RED, return to this later (it matches but NEEDS cleanup)
{
    u16 unk_0x0[1];

} Unk_8017301C_Halfword;

typedef struct ItemSettingsUnk
{
    s32 unk_0x0;
    s32 unk_0x4;
    u8 unk_0x8;
    s32 unk_0xC;
    u16 unk_0x10;
    Unk_8017301C_Halfword *unk_0x14;

} ItemSettingsUnk;

s32 func_ovl3_8017301C(s32 arg0, Unk_8018D048 *arg1, s32 arg2, u32 arg3) // Recursive!
{
    u32 temp_v0; s32 temp_v1;
    Unk_8017301C_Halfword *temp_t0;

    if (arg3 == (arg2 + 1)) return arg2;

    temp_v1 = (arg2 + arg3) / 2;

    if (arg0 < arg1->unk_0x14[temp_v1])
    {
        func_ovl3_8017301C(arg0, arg1, arg2, temp_v1);
    }
    else if (arg0 < arg1->unk_0x14[temp_v1 + 1])
    {
        return temp_v1;
    }
    else func_ovl3_8017301C(arg0, arg1, temp_v1, arg3);
}

u8 func_ovl3_80173090(Unk_8018D048 *arg0) // Might actually be raw u8
{
    return *(u8*)(func_ovl3_8017301C(rand_u16_range((s32)arg0->unk_0x10), arg0, 0, arg0->unk_0x8) + arg0->unk_0xC);
}

extern intptr_t hal_ld_article_floats;

static Unk_8018D048 D_ovl3_8018D048;

bool32 func_ovl3_801730D4(GObj *gobj)
{
    s32 unused;
    s32 index;
    Vec3f vel; // Article's spawn velocity when falling out of a container

    if (D_ovl3_8018D048.unk_0x10 != 0)
    {
        index = func_ovl3_80173090(&D_ovl3_8018D048);

        if (index <= It_Kind_CommonEnd)
        {
            vel.x = 0.0F;
            vel.y = *(f32*)((intptr_t)&hal_ld_article_floats + ((uintptr_t)&gItemFileData->spawn_vel_y[index])); // Linker thing
            vel.z = 0;

            if (func_ovl3_8016EA78(gobj, index, &DObjGetStruct(gobj)->translate, &vel, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_ARTICLE)) != NULL)
            {
                func_ovl3_80172394(gobj, TRUE);
            }
            return TRUE;
        }
    }
    return FALSE;
}

// 0x80173180
void itMain_UpdateHitEvent(GObj *item_gobj, itHitEvent *ev)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->it_multi == ev[ip->item_event_index].timer)
    {
        ip->item_hit.angle = ev[ip->item_event_index].angle;
        ip->item_hit.damage = ev[ip->item_event_index].damage;
        ip->item_hit.size = ev[ip->item_event_index].size;

        ip->item_event_index++;

        if (ip->item_event_index == 4)
        {
            ip->item_event_index = 3;
        }
    }
}

extern s8 gmBonusStat_MewCatcher;

GObj* func_ovl3_80173228(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    GObj *monster_gobj;
    Item_Struct *mp;
    s32 i, j;
    s32 index;
    s32 unused;
    Vec3f vel;

    vel.x = 0.0F;
    vel.y = 16.0F;
    vel.z = 0.0F;

    // Is this checking to spawn Mew?

    if ((Save_Info.unlock_mask & 0xF) && ((rand_u16_range(151) == 0)) && (Monster_Info.monster_curr != It_Kind_Mew) && (Monster_Info.monster_prev != It_Kind_Mew))
    {
        index = It_Kind_Mew;
    }
    else
    {
        for (i = j = It_Kind_MbMonsterStart; i < It_Kind_Mew; i++) // Pokémon IDs
        {
            if ((i != Monster_Info.monster_curr) && (i != Monster_Info.monster_prev))
            {
                Monster_Info.monster_index[j - It_Kind_MbMonsterStart] = i;
                j++;
            }
        }
        index = Monster_Info.monster_index[rand_u16_range(Monster_Info.monster_count)];
    }
    if (Monster_Info.monster_count != 10)
    {
        Monster_Info.monster_count--;
    }
    Monster_Info.monster_prev = Monster_Info.monster_curr;
    Monster_Info.monster_curr = index;

    monster_gobj = func_ovl3_8016F238(item_gobj, index, &DObjGetStruct(item_gobj)->translate, &vel, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_ARTICLE));

    if (monster_gobj != NULL)
    {
        mp = itGetStruct(monster_gobj);
        mp->owner_gobj = ip->owner_gobj;
        mp->team = ip->team;
        mp->port_id = ip->port_id;
        mp->handicap = ip->handicap;
        mp->player_number = ip->player_number;
        mp->display_state = ip->display_state;

        if (Match_Info->game_type == gmMatch_GameType_1PGame)
        {
            if ((mp->port_id == Scene_Info.player_port) && (mp->it_kind == It_Kind_Mew))
            {
                gmBonusStat_MewCatcher = TRUE;
            }
        }
    }
    return monster_gobj;
}

// 0x801733E4
bool32 itCommon_Default_ProcHop(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    func_ovl3_80172508(item_gobj);

    return FALSE;
}

// 0x80173434
bool32 itCommon_Default_ProcReflector(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    if ((ip->phys_info.vel.x * fp->lr) < 0.0F)
    {
        ip->phys_info.vel.x = -ip->phys_info.vel.x;
    }
    return FALSE;
}