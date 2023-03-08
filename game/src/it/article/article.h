#ifndef _ARTICLE_H_
#define _ARTICLE_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/it/article/articlevars.h>
#include <game/src/gm/gmmisc.h>
#include <game/src/gm/gmsound.h>
#include <game/src/ef/effect.h>

#define ARTICLE_TEAM_DEFAULT 4U // Article is teamless; deals damage to any eligible target
#define ARTICLE_PORT_DEFAULT 4U
#define ARTICLE_UNK_DEFAULT 9U // Handicap?
#define ARTICLE_STALE_DEFAULT 1.0F

#define ARTICLE_REFLECT_MAX_DEFAULT 100            // Maximum damage cap for reflected articles
#define ARTICLE_REFLECT_MUL_DEFAULT 1.8F           // Universal reflect damage multiplier
#define ARTICLE_REFLECT_ADD_DEFAULT 0.99F          // Added after multiplying article's hitbox damage

#define ARTICLE_DESPAWN_FLASH_INT_DEFAULT 180U // Article starts flashing rapidly once its lifetime (?) drops below this value
#define ARTICLE_ARROW_BLINK_INT_DEFAULT 45 // Red arrow pointing downward at article "blinks" at this frequency (45 frames visible, 45 frames invisible)

#define ARTICLE_REHIT_TIME_DEFAULT 16

#define ARTICLE_SPIN_SPEED_MUL_DEFAULT 0.31415927F
#define ARTICLE_SPIN_SPEED_MUL_NEW_SPAWN 0.17453294F
#define ARTICLE_SPIN_SPEED_MUL_PREV_SPAWN 0.27925268F

#define ARTICLE_SPIN_SPEED_SET_SMASH_THROW -0.36651915F
#define ARTICLE_SPIN_SPEED_SET_NORMAL_THROW -0.17453294F

#define ARTICLE_SPIN_SPEED_FRACTION_DEFAULT 0.01F // Also multiplies spin speed

typedef enum atKind
{
    // Common articles

    At_Kind_Box,        // Crate
    At_Kind_Taru,       // Barrel
    At_Kind_Capsule,    // Capsule
    At_Kind_Egg,        // Egg
    At_Kind_Tomato,     // Maxim Tomato
    At_Kind_Heart,      // Heart
    At_Kind_Star,       // Star Man
    At_Kind_Sword,      // Beam Sword
    At_Kind_Bat,        // Home-Run Bat
    At_Kind_Harisen,    // Fan
    At_Kind_StarRod,    // Star Rod
    At_Kind_L_Gun,      // Ray Gun
    At_Kind_F_Flower,   // Fire Flower
    At_Kind_Hammer,     // Hammer
    At_Kind_MSBomb,     // Motion-Sensor Bomb
    At_Kind_BombHei,    // Bob-Omb
    At_Kind_It_Bumper,  // Bumper (Item)
    At_Kind_G_Shell,    // Green Shell
    At_Kind_R_Shell,    // Red Shell
    At_Kind_M_Ball,     // Poké Ball

    // Character articles

    At_Kind_PK_Fire,    // PK Fire pillar
    At_Kind_Link_Bomb,  // Link's Bomb
    
    // Stage hazards

    At_Kind_POW,        // POW block
    At_Kind_Gr_Bumper,  // Bumper (Peach's Castle)
    At_Kind_Pakkun,     // Pirahna Plant
    At_Kind_Mato,       // Target
    At_Kind_Gr_Bomb,    // Race to the Finish bomb
    At_Kind_Gr_Lucky,   // Chansey (Saffron City)
    At_Kind_Marumine,   // Electrode
    At_Kind_Hitokage,   // Charmander
    At_Kind_Fushigibana,// Venusaur
    At_Kind_Porygon,    // Porygon

    // Pokémon

    At_Kind_Iwark,      // Onix
    At_Kind_Kabigon,    // Snorlax
    At_Kind_Tosakinto,  // Goldeen
    At_Kind_Nyars,      // Meowth
    At_Kind_Lizardon,   // Charizard
    At_Kind_Spear,      // Beedrill
    At_Kind_Kamex,      // Blastoise
    At_Kind_At_Lucky,   // Chansey (Poké Ball)
    At_Kind_Starmie,    // Starmie
    At_Kind_Sawamura,   // Hitmonlee
    At_Kind_Dogas,      // Koffing
    At_Kind_Pippi,      // Clefairy
    At_Kind_Mew         // Mew

} atKind;

typedef struct gmMonsterInfo
{
    u8 monster_curr;
    u8 monster_prev;
    u8 monster_index[44];
    u8 unk_0x2E;

} gmMonsterInfo;

static gmMonsterInfo Monster_Info; // Static (.bss) (0x8018D060)

typedef struct ArticleFileData
{
    f32 spawn_vel_y[20];

} ArticleFileData;

typedef struct ArticleStatusData
{
    u32 w0;
    ArticleFileData **p_file;
    u32 w2;
    u32 w3;

} ArticleStatusData;

extern ArticleFileData *Article_File_Data; // WARNING: This pointer exists in multiple areas and appears not to be exclusive to the Article section of Overlay 3 (0x8018D040)

typedef struct ArticleHitVictimFlags
{
    u32 flags_b0 : 1;
    u32 flags_b1 : 1;
    u32 flags_b2 : 1;
    u32 flags_b3 : 1;
    u32 flags_b456 : 3;
    u32 timer_rehit : 6;

} ArticleHitVictimFlags;

typedef struct ArticleHitUnk
{
    Vec3f pos;
    Vec3f pos_prev;
    s32 unk_0x18;
    u8 filler_0x1C[0x5C - 0x1C];
    f32 unk_0x5C;

} ArticleHitUnk;

typedef struct _ArticleHitArray
{
    GObj *victim_gobj;
    ArticleHitVictimFlags victim_flags;

} ArticleHitArray;

typedef struct ArticleLogicDesc
{
    bool32 (*cb_anim)(GObj*);
    bool32 (*cb_coll)(GObj*);
    bool32 (*cb_give_damage)(GObj*);
    bool32 (*cb_shield_block)(GObj*);
    bool32 (*cb_shield_deflect)(GObj*);
    bool32 (*cb_attack)(GObj*);
    bool32 (*cb_reflect)(GObj*);
    bool32 (*cb_take_damage)(GObj*);

} ArticleLogicDesc;

typedef struct _Article_Hit
{
    s32 update_state; // 0x0
    s32 damage; // 0x4
    f32 stale; // Might be damage in float? At least based on Melee?
    f32 throw_mul; // Multiplies damage on throw?
    s32 element; // 0xC // Placed AFTER offset?
    Vec3f offset[2]; // 0x10 - 0x18    
    f32 size;
    s32 angle;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    s32 shield_damage; // Shield damage?
    s32 priority; // Priority?
    u8 hit_status;
    u16 hit_sfx;
    u16 clang : 1;
    u16 flags_0x4C_b1 : 1;
    u16 flags_0x4C_b23456 : 5;
    u16 attack_id : 6;
    u16 flags_0x4C_b7 : 1;
    u16 flags_0x4E;
    CommonAttackFlags flags_hi;
    CommonAttackFlags flags_lw;
    s32 hitbox_count; // 0 = disabled, 1 = enabled, 2 and 3 related to position update?
    ArticleHitUnk article_hit_unk[2];
    ArticleHitArray hit_targets[4];

} Article_Hit;

typedef struct ArticleHitEvent // Hitbox subaction event?
{
    u8 opcode;
    s32 angle : 10;
    u32 damage : 8;
    u16 size;

} ArticleHitEvent;

typedef struct Article_Hurt
{
    u8 flags_0x0;
    s32 hit_status;
    Vec3f offset; // Added to TopN joint
    Vec3f size;

} Article_Hurt; // Article Hurtbox, might be larger

typedef struct atCommonAttributes
{
    void *unk_0x0;
    u8 filler_0x4[0x46 - 0x4];
    u16 spin_speed;

} atCommonAttributes;

typedef struct Article_Struct // Common items, stage hazards and Pokémon
{
    void *unk_0x0;
    GObj *article_gobj;
    GObj *owner_gobj;
    atKind at_kind;
    s32 unk_0x10;
    u8 team;
    u8 port_index;
    u8 unk_0x16;
    u8 unk_0x17;
    s32 player_number;
    s32 percent_damage;
    u32 hitlag_timer;
    s32 lr;

    struct
    {
        f32 vel_ground;
        Vec3f vel;

    } phys_info;

    Coll_Data coll_data;

    Ground_Air ground_or_air;

    Article_Hit article_hit[1];
    Article_Hurt article_hurt;

    s32 hit_victim_damage;
    s32 lr_attack; // Direction of outgoing attack?
    s32 unk_0x26C;
    s32 hit_attack_damage;
    s32 hit_shield_damage;
    f32 shield_collide_angle;
    Vec3f shield_collide_vec;
    GObj *reflect_gobj;
    u16 unk_0x28C;
    u16 unk_0x28E;
    s32 damage_last; // Last 
    f32 damage_launch_angle; // Angle at which article will be launched when getting hit?
    s32 damage_taken_recent;
    s32 damage_angle;
    s32 damage_element;
    s32 lr_damage; // Direction of incoming attack?
    GObj *damage_gobj; // GObj that last dealt damage to this article?
    u8 damage_team;
    u8 damage_port;
    s32 damage_player_number;
    u8 unk_0x2B4;
    s32 damage_display_state;
    s32 damage_taken_last;

    u8 filler_0x160[0x2C4 - 0x2C0];

    f32 vel_scale;
    u16 unk_0x2C8;
    u16 drop_sfx;
    u16 throw_sfx;

    u8 x2CE_flag_b0 : 1;
    u8 is_pause_article : 1; // Suspend Article logic updates? Might be used to tell if a fighter is holding this article?
    u8 times_landed : 2; // Number of times item has touched the ground while not grabbed; overflows after 3
    u8 times_thrown : 3; // Number of times item has been dropped or thrown; overflows after 7
    u8 is_light_throw : 1;
    u8 is_damage_all : 1; // Article ignores ownership and can damage anything?
    u8 x2CF_flag_b1 : 1;
    u8 x2CF_flag_b2 : 1;
    u8 x2CF_flag_b3 : 1;
    u8 x2CF_flag_b4 : 1;
    u8 x2CF_flag_b5 : 1;
    u8 x2CF_flag_b6 : 1;
    u8 x2CF_flag_b7 : 1;
    u16 unk_0x2D0;
    u16 x2D2_flag_12bit : 12; // Lifetime?
    u8 x2D3_flag_b4 : 1;
    u8 x2D3_flag_b5 : 1;
    u8 is_static_damage : 1;
    u8 x2D3_flag_b7 : 1;

    atCommonAttributes *attributes;

    Color_Overlay color_anim;

    u8 filler_0x2D4[0x338 - 0x31C];

    u8 x338_flag_b0 : 1;
    u8 x338_flag_b1 : 1;
    u8 x338_flag_b2 : 1;
    u8 x338_flag_b3 : 1;
    u8 x338_flag_b4 : 1;
    u8 x338_flag_b5 : 1;
    u8 x338_flag_b6 : 1;
    u8 x338_flag_b7 : 1;
    u8 x339_flag_b0 : 1;
    u8 x339_flag_b1 : 1;
    u8 x339_flag_b2 : 1;
    u8 x339_flag_b3 : 1;
    u8 x339_flag_b4 : 1;
    u8 x339_flag_b5 : 1;
    u8 x339_flag_b6 : 1;
    u8 x339_flag_b7 : 1;
    u8 x33A_flag_b0 : 1;
    u8 x33A_flag_b1 : 1;
    u8 x33A_flag_b2 : 1;
    u8 x33A_flag_b3 : 1;
    u8 x33A_flag_b4 : 1;
    u8 x33A_flag_b5 : 1;
    u8 x33A_flag_b6 : 1;
    u8 x33A_flag_b7 : 1;
    u8 x33B_flag_b0 : 1;
    u8 x33B_flag_b1 : 1;
    u8 x33B_flag_b2 : 1;
    u8 x33B_flag_b3 : 1;
    u8 x33B_flag_b4 : 1;
    u8 x33B_flag_b5 : 1;
    u8 x33B_flag_b6 : 1;
    u8 x33B_flag_b7 : 1;
    u8 is_hitlag_victim : 1;
    u8 x33C_flag_b1 : 1;
    u8 x33C_flag_b2 : 1;
    u8 x33C_flag_b3 : 1;
    u8 x33C_flag_b4 : 1;
    u8 x33C_flag_b5 : 1;
    u8 x33C_flag_b6 : 1;
    u8 x33C_flag_b7 : 1;
    u8 x33D_flag_b0 : 1;
    u8 x33D_flag_b1 : 1;
    u8 x33D_flag_b2 : 1;
    u8 x33D_flag_b3 : 1;
    u8 x33D_flag_b4 : 1;
    u8 x33D_flag_b5 : 1;
    u8 x33D_flag_b6 : 1;
    u8 x33D_flag_b7 : 1;
    u16 unk_0x33E;

    u8 x340_flag_b0123 : 4;
    f32 rotate_speed;
    GObj *unk_0x348;

    u8 arrow_flash_timer;
    u8 unk_0x34D;
    u8 unk_0x34E;
    u8 unk_0x34F;

    u8 filler_0x350[0x374 - 0x350];

    s32 display_state;

    bool32 (*cb_anim)(GObj*);
    bool32 (*cb_coll)(GObj*);
    bool32 (*cb_give_damage)(GObj*);
    bool32 (*cb_shield_block)(GObj*);
    bool32 (*cb_shield_deflect)(GObj*);
    bool32 (*cb_attack)(GObj*);
    bool32 (*cb_reflect)(GObj*);
    bool32 (*cb_take_damage)(GObj*);
    bool32 (*cb_destroy)(GObj*);

} Article_Struct;

#define ArticleGetStruct(article_gobj) \
((Article_Struct*)article_gobj->user_data) \

#endif
