#include "article.h"
#include "fighter.h"
#include "gmmatch.h"

void func_ovl3_80172310(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->rotate_speed = (ap->attributes->spin_speed != 0) ? (ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ARTICLE_SPIN_SPEED_MUL_DEFAULT) : 0.0F;

    if (ap->lr == LEFT)
    {
        ap->rotate_speed = -ap->rotate_speed;
    }
}

void func_ovl3_80172394(GObj *article_gobj, bool32 is_prev_spawn)
{
    // is_prev_spawn = whether article is newly spawned or previously spawned; 0 = new, 1 = old

    Article_Struct *ap = atGetStruct(article_gobj); // Ternary doesn't match here smh

    if (is_prev_spawn == FALSE)
    {
        if (ap->attributes->spin_speed != 0)
        {
            ap->rotate_speed = ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ARTICLE_SPIN_SPEED_MUL_NEW_SPAWN;
        }
        else ap->rotate_speed = 0.0F;
    }
    else if (ap->attributes->spin_speed != 0)
    {
        ap->rotate_speed = ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ARTICLE_SPIN_SPEED_MUL_PREV_SPAWN;
    }
    else ap->rotate_speed = 0.0F;
}

void func_ovl3_8017245C(GObj *article_gobj, f32 *spin_speed, bool32 is_smash_throw)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->rotate_speed = (is_smash_throw != FALSE) ? ARTICLE_SPIN_SPEED_SET_SMASH_THROW : ARTICLE_SPIN_SPEED_SET_NORMAL_THROW;

    if (*spin_speed < 0) // Facing direction, sort of
    {
        ap->rotate_speed = -ap->rotate_speed;
    }

    ap->rotate_speed = (ap->attributes->spin_speed != 0) ? (ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ap->rotate_speed) : 0.0F;
}

void func_ovl3_80172508(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->lr = (ap->phys_info.vel.x >= 0.0F) ? RIGHT : LEFT;

    func_ovl3_80172310(article_gobj);
}

void func_ovl3_80172558(Article_Struct *ap, f32 gravity, f32 terminal_velocity)
{
    ap->phys_info.vel.y -= gravity;

    if (terminal_velocity < func_ovl0_800C7A84(&ap->phys_info.vel))
    {
        func_ovl0_800C7A00(&ap->phys_info.vel);
        func_ovl0_800C7AE0(&ap->phys_info.vel, terminal_velocity);
    }
}

extern s32 dbObjDisplayStatus_Global_Article; // Static (.bss)

void func_ovl3_801725BC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->owner_gobj = NULL;
    ap->team = ARTICLE_TEAM_DEFAULT;
    ap->port_id = ARTICLE_PORT_DEFAULT;
    ap->handicap = ARTICLE_UNK_DEFAULT;
    ap->player_number = 0;
    ap->article_hit.stale = ARTICLE_STALE_DEFAULT;

    ap->display_state = dbObjDisplayStatus_Global_Article;
}

void func_ovl3_801725F8(Article_Struct *ap)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(ap->article_hit.hit_targets); i++)
    {
        ArticleHitArray *targets = &ap->article_hit.hit_targets[i];

        targets->victim_gobj = NULL;

        targets->victim_flags.is_interact_hurt = targets->victim_flags.is_interact_shield = targets->victim_flags.is_interact_reflect = FALSE;

        targets->victim_flags.timer_rehit = 0;

        targets->victim_flags.interact_mask = GMHITCOLLISION_MASK_ALL;
    }
}

void func_ovl3_8017275C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_801725F8(ap);

    ap->article_hit.update_state = gmHitCollision_UpdateState_New;

    itManager_UpdateHitPositions(article_gobj);
}

void func_ovl3_8017279C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->is_damage_all = TRUE;

    ap->owner_gobj = NULL;

    ap->team = ARTICLE_TEAM_DEFAULT;
}

void func_ovl3_801727BC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->owner_gobj = ap->damage_gobj;
    ap->team = ap->damage_team;
    ap->port_id = ap->damage_port;
    ap->player_number = ap->player_number; // Could potentially cause a bug? Didn't they mean damage_player_number?
    ap->handicap = ap->damage_handicap;
    ap->display_state = ap->damage_display_state;
}

s32 func_ovl3_801727F4(Article_Struct *ap)
{
    s32 damage;

    if (ap->x2CF_flag_b2)
    {
        f32 mag = vec3f_mag(&ap->phys_info.vel) * 0.1F;

        damage = (ap->article_hit.damage + mag) * ap->article_hit.stale;
    }
    else damage = ap->article_hit.damage;

    return (damage * ap->article_hit.throw_mul) + 0.999F;
}

// 0x80172890
bool32 atCommon_CheckTypeShootEmpty(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (((ap->at_kind == At_Kind_StarRod) || (ap->at_kind == At_Kind_L_Gun) || (ap->at_kind == At_Kind_F_Flower)) && (ap->at_multi == 0))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_801728D4(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if ((ap->is_hold) && (ap->owner_gobj != NULL))
    {
        Fighter_Struct *fp = ftGetStruct(ap->owner_gobj);

        fp->item_hold = NULL;

        ftCommon_GetHammerSetBGM(ap->owner_gobj);
    }
    else if ((ap->at_kind < At_Kind_Gr_Lucky) || (ap->at_kind > At_Kind_GrMonsterEnd))
    {
        func_ovl2_800FF590(&DObjGetStruct(article_gobj)->translate);
    }
    if (ap->unk_0x348 != NULL)
    {
        gOMObj_EjectGObjCommon(ap->unk_0x348);
    }
    itManager_SetPrevAlloc(ap);
    gOMObj_EjectGObjCommon(article_gobj);
}

void func_ovl3_80172984(GObj *article_gobj, Vec3f *vel, f32 stale, u16 flag1, u16 flag2) // Very high probability that Link's Bomb erroneously declares this without flag1 and flag2
{
    Article_Struct *ap = atGetStruct(article_gobj);
    GObj *fighter_gobj = ap->owner_gobj;
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;
    s32 joint_index;

    func_ovl0_800C9424(DObjGetStruct(article_gobj));

    pos.z = 0.0F;
    pos.y = 0.0F;
    pos.x = 0.0F;

    joint_index = (!(ap->is_light_throw)) ? fp->attributes->joint_itemhold_heavy : fp->attributes->joint_itemhold_light;

    func_ovl2_800EDF24(fp->joint[joint_index], &pos);

    DObjGetStruct(article_gobj)->translate.x = pos.x;
    DObjGetStruct(article_gobj)->translate.y = pos.y;
    DObjGetStruct(article_gobj)->translate.z = 0.0F;

    func_ovl2_800DF058(article_gobj, fp->coll_data.p_translate, &fp->coll_data);

    fp->item_hold = NULL;

    ap->is_hold = FALSE;

    ap->phys_info.vel = *vel;

    vec3f_scale(&ap->phys_info.vel, ap->vel_scale);

    ap->times_thrown++;
    ap->x2CF_flag_b2 = TRUE;

    ap->article_hit.stale = stale;

    ap->article_hit.stat_flags = *(gmAttackFlags*)&flag1;
    ap->article_hit.stat_count = flag2;

    ftCommon_GetHammerSetBGM(fighter_gobj);
    func_ovl3_8017275C(article_gobj);
}

extern void (*Article_Callback_Drop[])(GObj*); // Assumed to contain 45 callbacks?

void func_ovl3_80172AEC(GObj *article_gobj, Vec3f *vel, f32 stale)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    GObj *owner_gobj = ap->owner_gobj;
    Fighter_Struct *fp = ftGetStruct(owner_gobj);
    void (*proc_drop)(GObj*) = Article_Callback_Drop[ap->at_kind];

    if (proc_drop != NULL)
    {
        proc_drop(article_gobj);
    }
    func_ovl3_80172984(article_gobj, vel, stale, ftStatus_AttackIndex_ItemThrow, fp->stat_count);

    func_800269C0(ap->drop_sfx);
}

extern void (*Article_Callback_Throw[])(GObj*); 

void func_ovl3_80172B78(GObj *article_gobj, Vec3f *vel, f32 stale, bool32 is_smash_throw)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    GObj *owner_gobj = ap->owner_gobj;
    Fighter_Struct *fp = ftGetStruct(owner_gobj);
    void (*cb_throw)(GObj*);

    if ((ap->is_light_throw) == TRUE)
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
    cb_throw = Article_Callback_Throw[ap->at_kind];

    if (cb_throw != NULL)
    {
        cb_throw(article_gobj);
    }
    func_ovl3_80172984(article_gobj, vel, stale, fp->stat_flags.halfword, fp->stat_count);

    func_ovl2_8010066C(&DObjGetStruct(article_gobj)->translate, 1.0F);

    func_800269C0(((is_smash_throw != FALSE) ? ap->throw_sfx : ap->drop_sfx));

    func_ovl3_8017245C(article_gobj, vel, is_smash_throw);
}

extern void (*Article_Callback_Pickup[])(GObj*);

// 0x80172CA4
void atCommon_PickupSetHoldFighter(GObj *article_gobj, GObj *fighter_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    DObj *joint;
    void (*cb_pickup)(GObj*);
    Vec3f pos;
    s32 joint_index;

    fp->item_hold = article_gobj;
    ap->owner_gobj = fighter_gobj;

    ap->is_allow_pickup = FALSE;
    ap->is_hold = TRUE;

    ap->team = fp->team;
    ap->port_id = fp->port_id;
    ap->handicap = fp->handicap;
    ap->player_number = fp->player_number;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    ap->display_state = fp->display_state;

    func_ovl3_80173F78(ap);

    joint = func_800092D0(article_gobj, NULL);

    joint->unk_0xC->unk_0x8 = NULL;
    joint->unk_0xC = NULL;
    joint->next = DObjGetStruct(article_gobj);

    DObjGetStruct(article_gobj)->prev = joint;

    article_gobj->obj = joint;

    func_80008CC0(joint, 0x52, 0);

    joint_index = (!(ap->is_light_throw)) ? fp->attributes->joint_itemhold_heavy : fp->attributes->joint_itemhold_light;

    joint->unk_0x84 = fp->joint[joint_index];

    pos.x = 0.0F;
    pos.y = 0.0F;
    pos.z = 0.0F;

    func_ovl2_800EDF24(fp->joint[joint_index], &pos);

    func_ovl2_80104458(&pos);

    func_8000F988(article_gobj, ap->attributes->unk_0x0);

    cb_pickup = Article_Callback_Pickup[ap->at_kind];

    if (cb_pickup != NULL)
    {
        cb_pickup(article_gobj);
    }
    ftLink_SetModelPartHideShield(fighter_gobj);

    if (ap->is_light_throw == TRUE)
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

    ap->pickup_wait = ARTICLE_PICKUP_WAIT_DEFAULT;
}

void func_ovl3_80172E74(GObj *article_gobj) // Airborne article becomes grounded?
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->phys_info.vel.z = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.x = 0.0F;

    ap->is_allow_pickup = TRUE;
    ap->times_landed = 0;

    func_ovl3_801725BC(article_gobj);
    func_ovl3_80173F54(ap);
}

// 0x80172EC8
void atCommon_UpdateArticleStatus(GObj *article_gobj, ArticleStatusDesc *p_desc, s32 status_id) // Change article state
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->proc_update = p_desc[status_id].proc_update;
    ap->proc_map = p_desc[status_id].proc_map;
    ap->proc_hit = p_desc[status_id].proc_hit;
    ap->proc_shield = p_desc[status_id].proc_shield;
    ap->proc_hop = p_desc[status_id].proc_hop;
    ap->proc_setoff = p_desc[status_id].proc_setoff;
    ap->proc_reflector = p_desc[status_id].proc_reflector;
    ap->proc_damage = p_desc[status_id].proc_damage;

    ap->x2CF_flag_b2 = FALSE;

    ap->article_hit.stat_flags.attack_group_id = ftStatus_AttackIndex_Null;
    ap->article_hit.stat_flags.is_smash_attack = ap->article_hit.stat_flags.is_ground_or_air = ap->article_hit.stat_flags.is_special_attack = FALSE;

    ap->article_hit.stat_count = gmCommon_GetStatUpdateCountInc();
}

// 0x80172F98
bool32 atCommon_CheckSetColAnimIndex(GObj *article_gobj, s32 colanim_id, s32 duration)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    return caCheckSetColAnimIndex(&ap->colanim, colanim_id, duration);
}

void func_ovl3_80172FBC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    caResetColAnim(&ap->colanim);
}

void func_ovl3_80172FE0(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->phys_info.vel.x *= -0.06F;

    ap->phys_info.vel.y = (ap->phys_info.vel.y * -0.3F) + 25.0F;
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

        if (index <= At_Kind_CommonEnd)
        {
            vel.x = 0.0F;
            vel.y = *(f32*)((intptr_t)&hal_ld_article_floats + ((uintptr_t)&Article_File_Data->spawn_vel_y[index])); // Linker thing
            vel.z = 0;

            if (func_ovl3_8016EA78(gobj, index, &DObjGetStruct(gobj)->translate, &vel, (ARTICLE_FLAG_PROJECT | ARTICLE_MASK_SPAWN_ARTICLE)) != NULL)
            {
                func_ovl3_80172394(gobj, TRUE);
            }
            return TRUE;
        }
    }
    return FALSE;
}

void func_ovl3_80173180(GObj *article_gobj, ArticleHitEvent *event)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (event[ap->x340_flag_b0123].timer == ap->at_multi)
    {
        ap->article_hit.angle = event[ap->x340_flag_b0123].angle;
        ap->article_hit.damage = event[ap->x340_flag_b0123].damage;
        ap->article_hit.size = event[ap->x340_flag_b0123].size;

        ap->x340_flag_b0123++;

        if (ap->x340_flag_b0123 == 4)
        {
            ap->x340_flag_b0123 = 3;
        }
    }
}

extern s8 gmBonusStat_MewCatcher;

GObj* func_ovl3_80173228(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    GObj *monster_gobj;
    Article_Struct *mp;
    s32 i, j;
    s32 index;
    s32 unused;
    Vec3f vel;

    vel.x = 0.0F;
    vel.y = 16.0F;
    vel.z = 0.0F;

    // Is this checking to spawn Mew?

    if ((Save_Info.unlock_mask & 0xF) && ((rand_u16_range(151) == 0)) && (Monster_Info.monster_curr != At_Kind_Mew) && (Monster_Info.monster_prev != At_Kind_Mew))
    {
        index = At_Kind_Mew;
    }
    else
    {
        for (i = j = At_Kind_MonsterStart; i < At_Kind_Mew; i++) // Pokémon IDs
        {
            if ((i != Monster_Info.monster_curr) && (i != Monster_Info.monster_prev))
            {
                Monster_Info.monster_index[j - At_Kind_MonsterStart] = i;
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

    monster_gobj = func_ovl3_8016F238(article_gobj, index, &DObjGetStruct(article_gobj)->translate, &vel, (ARTICLE_FLAG_PROJECT | ARTICLE_MASK_SPAWN_ARTICLE));

    if (monster_gobj != NULL)
    {
        mp = atGetStruct(monster_gobj);
        mp->owner_gobj = ap->owner_gobj;
        mp->team = ap->team;
        mp->port_id = ap->port_id;
        mp->unk_0x16 = ap->handicap;
        mp->player_number = ap->player_number;
        mp->display_state = ap->display_state;

        if (Match_Info->game_type == gmMatch_GameType_1PGame)
        {
            if ((mp->port_id == Scene_Info.player_port) && (mp->at_kind == At_Kind_Mew))
            {
                gmBonusStat_MewCatcher = TRUE;
            }
        }
    }
    return monster_gobj;
}

bool32 jtgt_ovl3_801733E4(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_80019438(&ap->phys_info.vel, &ap->shield_collide_vec, ap->shield_collide_angle * 2);
    func_ovl3_80172508(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80173434(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    Fighter_Struct *fp = ftGetStruct(ap->owner_gobj);

    if ((ap->phys_info.vel.x * fp->lr) < 0.0F)
    {
        ap->phys_info.vel.x = -ap->phys_info.vel.x;
    }
    return FALSE;
}