#include "article.h"
#include "fighter.h"
#include "gmmatch.h"

void func_ovl3_80172310(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->rotate_speed = (ap->attributes->spin_speed != 0) ? (ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ARTICLE_SPIN_SPEED_MUL_DEFAULT) : 0.0F;

    if (ap->lr == LEFT)
    {
        ap->rotate_speed = -ap->rotate_speed;
    }
}

void func_ovl3_80172394(GObj *article_gobj, bool32 is_prev_spawn)
{
    // is_prev_spawn = whether article is newly spawned or previously spawned; 0 = new, 1 = old

    Article_Struct *ap = ArticleGetStruct(article_gobj); // Ternary doesn't match here smh

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
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->rotate_speed = (is_smash_throw != FALSE) ? ARTICLE_SPIN_SPEED_SET_SMASH_THROW : ARTICLE_SPIN_SPEED_SET_NORMAL_THROW;

    if (*spin_speed < 0) // Facing direction, sort of
    {
        ap->rotate_speed = -ap->rotate_speed;
    }

    ap->rotate_speed = (ap->attributes->spin_speed != 0) ? (ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ap->rotate_speed) : 0.0F;
}

void func_ovl3_80172508(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

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
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->owner_gobj = NULL;
    ap->team = ARTICLE_TEAM_DEFAULT;
    ap->port_index = ARTICLE_PORT_DEFAULT;
    ap->unk_0x16 = ARTICLE_UNK_DEFAULT;
    ap->player_number = 0;
    ap->article_hit[0].stale = ARTICLE_STALE_DEFAULT;

    ap->display_state = dbObjDisplayStatus_Global_Article;
}

void func_ovl3_801725F8(Article_Struct *ap)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(ap->article_hit[0].hit_targets); i++)
    {
        ArticleHitArray *targets = &ap->article_hit[0].hit_targets[i];

        targets->victim_gobj = NULL;

        targets->victim_flags.flags_b0 = targets->victim_flags.flags_b1 = targets->victim_flags.flags_b2 = FALSE;

        targets->victim_flags.timer_rehit = 0;

        targets->victim_flags.flags_b456 = 7;
    }
}

void func_ovl3_8017275C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_801725F8(ap);

    ap->article_hit[0].update_state = gmHitCollision_UpdateState_New;

    func_ovl3_8016F280(article_gobj);
}

void func_ovl3_8017279C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_damage_all = TRUE;

    ap->owner_gobj = NULL;

    ap->team = ARTICLE_TEAM_DEFAULT;
}

void func_ovl3_801727BC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->owner_gobj = ap->damage_gobj;
    ap->team = ap->damage_team;
    ap->port_index = ap->damage_port;
    ap->player_number = ap->player_number; // Could potentially cause a bug? Didn't they mean damage_player_number?
    ap->unk_0x16 = ap->unk_0x2B4;
    ap->display_state = ap->damage_display_state;
}

s32 func_ovl3_801727F4(Article_Struct *ap)
{
    s32 damage;
    f32 f;

    if (ap->x2CF_flag_b2)
    {
        f32 mag = (vec3f_mag(&ap->phys_info.vel) * 0.1F); // Wat

        damage = ap->article_hit[0].stale * (ap->article_hit[0].damage + mag); // Wat
    }
    else
    {
        damage = ap->article_hit[0].damage;
    }

    f = damage; // Wat!

    f *= ap->article_hit[0].throw_mul; // WAT!

    return (ap->article_hit[0].throw_mul * damage) + 0.999F; // WAT!!! (It doesn't match otherwise???)
}

bool32 func_ovl3_80172890(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (((ap->at_kind == At_Kind_StarRod) || (ap->at_kind == At_Kind_L_Gun) || (ap->at_kind == At_Kind_F_Flower)) && (ap->unk_0x33E == 0))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_801728D4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if ((ap->is_pause_article) && (ap->owner_gobj != NULL))
    {
        Fighter_Struct *fp = FighterGetStruct(ap->owner_gobj);

        fp->article_hold = NULL;

        func_ovl2_800E8744(ap->owner_gobj);
    }

    else if ((ap->at_kind < At_Kind_Gr_Lucky) || (ap->at_kind >= At_Kind_Iwark))
    {
        func_ovl2_800FF590(&JObjGetStruct(article_gobj)->translate);
    }
    if (ap->unk_0x348 != NULL)
    {
        func_80009A84(ap->unk_0x348);
    }
    func_ovl3_8016DFDC(ap);
    func_80009A84(article_gobj);
}

void func_ovl3_80172984(GObj *article_gobj, Vec3f *vel, f32 stale, u16 flags_hi, u16 flags_lw)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    GObj *fighter_gobj = ap->owner_gobj;
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    s32 joint_index;

    func_ovl0_800C9424(JObjGetStruct(article_gobj));

    pos.z = 0.0F;
    pos.y = 0.0F;
    pos.x = 0.0F;

    joint_index = (!(ap->is_light_throw)) ? fp->attributes->joint_throw_heavy : fp->attributes->joint_throw_light;

    func_ovl2_800EDF24(fp->joint[joint_index], &pos);

    JObjGetStruct(article_gobj)->translate.x = pos.x;
    JObjGetStruct(article_gobj)->translate.y = pos.y;
    JObjGetStruct(article_gobj)->translate.z = 0.0F;

    func_ovl2_800DF058(article_gobj, fp->coll_data.p_translate, &fp->coll_data);

    fp->article_hold = NULL;

    ap->is_pause_article = FALSE;

    ap->phys_info.vel = *vel;

    vec3f_scale(&ap->phys_info.vel, ap->vel_scale);

    ap->times_thrown++;
    ap->x2CF_flag_b2 = TRUE;

    ap->article_hit[0].stale = stale;
    ap->article_hit[0].flags_hi.halfword = *(vu16*)&flags_hi & U16_MAX; // Uh...
    ap->article_hit[0].flags_lw.halfword = flags_lw;

    func_ovl2_800E8744(fighter_gobj);
    func_ovl3_8017275C(article_gobj);
}

extern void (*Article_Callback_Drop[])(GObj*); // Assumed to contain 45 callbacks?

void func_ovl3_80172AEC(GObj *article_gobj, Vec3f *vel, f32 stale)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    GObj *owner_gobj = ap->owner_gobj;
    Fighter_Struct *fp = FighterGetStruct(owner_gobj);
    void (*cb_drop)(GObj*) = Article_Callback_Drop[ap->at_kind];

    if (cb_drop != NULL)
    {
        cb_drop(article_gobj);
    }
    func_ovl3_80172984(article_gobj, vel, stale, 0x38U, fp->unk_0x290);

    func_800269C0(ap->drop_sfx);
}

extern void (*Article_Callback_Throw[])(GObj*); 

void func_ovl3_80172B78(GObj *article_gobj, Vec3f *vel, f32 stale, bool32 is_smash_throw)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    GObj *owner_gobj = ap->owner_gobj;
    Fighter_Struct *fp = FighterGetStruct(owner_gobj);
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
    func_ovl3_80172984(article_gobj, vel, stale, fp->unk_0x28E_halfword, fp->unk_0x290);

    func_ovl2_8010066C(&JObjGetStruct(article_gobj)->translate, 1.0F);

    func_800269C0(((is_smash_throw != FALSE) ? ap->throw_sfx : ap->drop_sfx));

    func_ovl3_8017245C(article_gobj, vel, is_smash_throw);
}

extern void (*Article_Callback_Pickup[])(GObj*);

void func_ovl3_80172CA4(GObj *article_gobj, GObj *fighter_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    JObj *joint;
    void (*cb_pickup)(GObj*);
    Vec3f pos;
    s32 joint_index;

    fp->article_hold = article_gobj;
    ap->owner_gobj = fighter_gobj;

    ap->x2CE_flag_b0 = FALSE;
    ap->is_pause_article = TRUE;

    ap->team = fp->team;
    ap->port_index = fp->player_id;
    ap->unk_0x16 = fp->offset_hit_type;
    ap->player_number = fp->player_number;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    ap->display_state = fp->display_state;

    func_ovl3_80173F78(ap);

    joint = func_800092D0(article_gobj, NULL);

    joint->unk_0xC->unk_0x8 = NULL;
    joint->unk_0xC = NULL;
    joint->next = JObjGetStruct(article_gobj);

    JObjGetStruct(article_gobj)->prev = joint;

    article_gobj->obj = joint;

    func_80008CC0(joint, 0x52, 0);

    joint_index = (!(ap->is_light_throw)) ? fp->attributes->joint_throw_heavy : fp->attributes->joint_throw_light;

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
    func_ovl2_800E86F0(fighter_gobj);

    if (ap->is_light_throw == TRUE)
    {
        func_800269C0(0x31U);
    }
    else
    {
        if (fp->attributes->throw_heavy_sfx != 0x2B7)
        {
            func_800269C0(fp->attributes->throw_heavy_sfx);
        }
    }
    func_ovl2_800E806C(fp, 6, 0);

    ap->x2D2_flag_12bit = 1400;
}

void func_ovl3_80172E74(GObj *article_gobj) // Airborne article becomes grounded?
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

    ap->phys_info.vel.z = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.x = 0.0F;

    ap->x2CE_flag_b0 = TRUE;
    ap->times_landed = 0;

    func_ovl3_801725BC(article_gobj);
    func_ovl3_80173F54(ap);
}

void func_ovl3_80172EC8(GObj *article_gobj, ArticleLogicDesc p_desc[], s32 status_id) // Change article state
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->cb_anim = p_desc[status_id].cb_anim;
    ap->cb_coll = p_desc[status_id].cb_coll;
    ap->cb_give_damage = p_desc[status_id].cb_give_damage;
    ap->cb_shield_block = p_desc[status_id].cb_shield_block;
    ap->cb_shield_deflect = p_desc[status_id].cb_shield_deflect;
    ap->cb_attack = p_desc[status_id].cb_attack;
    ap->cb_reflect = p_desc[status_id].cb_reflect;
    ap->cb_take_damage = p_desc[status_id].cb_take_damage;

    ap->x2CF_flag_b2 = FALSE;

    ap->article_hit[0].flags_hi.flags_0x3FF = 0x39U;
    ap->article_hit[0].flags_hi.flags_0x1000 =
    ap->article_hit[0].flags_hi.flags_0x800 =
    ap->article_hit[0].flags_hi.flags_0x400 = FALSE;

    ap->article_hit[0].flags_lw.halfword = func_ovl2_800EA74C();
}

void func_ovl3_80172F98(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl2_800E974C(&ap->color_anim);
}

void func_ovl3_80172FBC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl2_800E9838(&ap->color_anim);
}

void func_ovl3_80172FE0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

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

u8* func_ovl3_80173090(Unk_8018D048 *arg0)
{
    return *(u8*)(func_ovl3_8017301C(rand_u16_range((s32)arg0->unk_0x10), arg0, 0, arg0->unk_0x8) + arg0->unk_0xC);
}

extern u8 hal_ld_article_floats;

static Unk_8018D048 D_ovl3_8018D048;

typedef struct ArticleSpawnVelY
{
    f32 f[20];

} ArticleSpawnVelY;

extern ArticleSpawnVelY *Article_Spawn_Vel_Y; // WARNING: This pointer exists in multiple areas and appears not to be exclusive to the Article section of Overlay 3

bool32 func_ovl3_801730D4(GObj *gobj)
{
    s32 unused;
    s32 index;
    Vec3f vel; // Article's spawn velocity when falling out of a container

    if (D_ovl3_8018D048.unk_0x10 != 0)
    {
        index = func_ovl3_80173090(&D_ovl3_8018D048);

        if (index < 20)
        {
            vel.x = 0.0F;
            vel.y = *(f32*)(&hal_ld_article_floats + ((uintptr_t)&Article_Spawn_Vel_Y->f[index])); // Linker thing
            vel.z = 0;

            if (func_ovl3_8016EA78(gobj, index, &JObjGetStruct(gobj)->translate, &vel, 0x80000003U) != NULL)
            {
                func_ovl3_80172394(gobj, TRUE);
            }
            return TRUE;
        }
    }
    return FALSE;
}

void func_ovl3_80173180(GObj *article_gobj, ArticleHitEvent event[])
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (event[ap->x340_flag_b0123].opcode == ap->unk_0x33E)
    {
        ap->article_hit[0].angle = event[ap->x340_flag_b0123].angle;
        ap->article_hit[0].damage = event[ap->x340_flag_b0123].damage;
        ap->article_hit[0].size = event[ap->x340_flag_b0123].size;

        ap->x340_flag_b0123++;

        if (ap->x340_flag_b0123 == 4)
        {
            ap->x340_flag_b0123 = 3;
        }
    }
}

struct RecordCharCombo {
    /* 0x00 */ u16 gamesWith;
    /* 0x02 */ u16 playedAgainst;
}; // size == 4

struct VsRecordData {
    /* 0x00 */ u16 kos[12];
    /* 0x18 */ u32 timeUsed; //< in seconds
    /* 0x1C */ u32 damageDealt;
    /* 0x20 */ u32 damageReceived;
    /* 0x24 */ u16 totalSDs;
    /* 0x26 */ u16 gamesPlayed;
    /* 0x28 */ u16 gamesPlayedAgainst;
    /* 0x2C */ struct RecordCharCombo combinations[12];
}; // size == 0x5C

// is this the saved data structure?
struct BigA44E0 {
    /* 0x000 */ struct VsRecordData vsRecords[12];
    /* 0x450 */ u8 unk540[(0x5EC - 0x450)];
}; // size == 0x5EC

struct UnkA4AD0 {
    /* 0x00 */ u8 scene;
    /* 0x01 */ u8 pad01[0x13 - 0x01];
    u8 unk_0x13;
    u8 filler_0x14[0x48 - 0x14];
}; // size == 0x48


extern struct BigA44E0 D_800A44E0;
extern struct UnkA4AD0 D_800A4AD0;
extern s8 D_ovl65_801936AD;

GObj* func_ovl3_80173228(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
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

    if ((D_800A44E0.unk540[7] & 0xF) && ((rand_u16_range(151) == 0)) && (Monster_Info.monster_curr != At_Kind_Mew) && (Monster_Info.monster_prev != At_Kind_Mew))
    {
        index = At_Kind_Mew;
    }
    else
    {
        for (i = j = At_Kind_Iwark; i < At_Kind_Mew; i++) // Pokémon IDs
        {
            if ((i != Monster_Info.monster_curr) && (i != Monster_Info.monster_prev))
            {
                Monster_Info.monster_index[j - At_Kind_Iwark] = i;
                j++;
            }
        }
        index = Monster_Info.unk_0x2[rand_u16_range(Monster_Info.unk_0x2E)];
    }
    if (Monster_Info.unk_0x2E != 10)
    {
        Monster_Info.unk_0x2E--;
    }
    Monster_Info.monster_prev = Monster_Info.monster_curr;
    Monster_Info.monster_curr = index;

    monster_gobj = func_ovl3_8016F238(article_gobj, index, &JObjGetStruct(article_gobj)->translate, &vel, 0x80000003);

    if (monster_gobj != NULL)
    {
        mp = ArticleGetStruct(monster_gobj);
        mp->owner_gobj = ap->owner_gobj;
        mp->team = ap->team;
        mp->port_index = ap->port_index;
        mp->unk_0x16 = ap->unk_0x16;
        mp->player_number = ap->player_number;
        mp->display_state = ap->display_state;

        if (Match_Info->unk_0x0 == 5)
        {
            if ((mp->port_index == D_800A4AD0.unk_0x13) && (mp->at_kind == At_Kind_Mew))
            {
                D_ovl65_801936AD = 1;
            }
        }
    }
    return monster_gobj;
}

bool32 jtgt_ovl3_801733E4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_80019438(&ap->phys_info.vel, &ap->shield_collide_vec, ap->shield_collide_angle * 2);
    func_ovl3_80172508(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80173434(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Fighter_Struct *fp = FighterGetStruct(ap->owner_gobj);

    if ((ap->phys_info.vel.x * fp->lr) < 0.0F)
    {
        ap->phys_info.vel.x = -ap->phys_info.vel.x;
    }
    return FALSE;
}