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

#define ARTICLE_FLAG_PROJECT 0x80000000            // Perform initial collision check when spawning item?

#define ARTICLE_MASK_SPAWN_FIGHTER 0               // Item spawned by fighter
#define ARTICLE_MASK_SPAWN_NONE 1                  // Item spawned independently 
#define ARTICLE_MASK_SPAWN_ITEM 2               // Item spawned by another item
#define ARTICLE_MASK_SPAWN_ARTICLE 3               // Item spawned by Pokémon / misc entity class(es?)

#define ARTICLE_MASK_SPAWN_ALL 0xF                 // Mask all GObj classes that can spawn items?

#define ARTICLE_TEAM_DEFAULT 4U // Article is teamless; deals damage to any eligible target
#define ARTICLE_PORT_DEFAULT 4U
#define ARTICLE_UNK_DEFAULT 9U // Handicap?
#define ARTICLE_STALE_DEFAULT 1.0F

#define ARTICLE_PICKUP_WAIT_DEFAULT 1400           // "Lifetime" while item is not being carried

#define ARTICLE_REFLECT_MAX_DEFAULT 100            // Maximum damage cap for reflected articles
#define ARTICLE_REFLECT_MUL_DEFAULT 1.8F           // Universal reflect damage multiplier
#define ARTICLE_REFLECT_ADD_DEFAULT 0.99F          // Added after multiplying article's hitbox damage

#define ARTICLE_DESPAWN_FLASH_START_DEFAULT 180U // Article starts flashing rapidly once its lifetime (?) drops below this value
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

    At_Kind_CommonStart,                    // Start of common article IDs
    At_Kind_Box = At_Kind_CommonStart,      // Crate
    At_Kind_Taru,                           // Barrel
    At_Kind_Capsule,                        // Capsule
    At_Kind_Egg,                            // Egg
    At_Kind_Tomato,                         // Maxim Tomato
    At_Kind_Heart,                          // Heart
    At_Kind_Star,                           // Star Man
    At_Kind_Sword,                          // Beam Sword
    At_Kind_Bat,                            // Home-Run Bat
    At_Kind_Harisen,                        // Fan
    At_Kind_StarRod,                        // Star Rod
    At_Kind_L_Gun,                          // Ray Gun
    At_Kind_F_Flower,                       // Fire Flower
    At_Kind_Hammer,                         // Hammer
    At_Kind_MSBomb,                         // Motion-Sensor Bomb
    At_Kind_BombHei,                        // Bob-Omb
    At_Kind_It_Bumper,                      // Bumper (Item)
    At_Kind_G_Shell,                        // Green Shell
    At_Kind_R_Shell,                        // Red Shell
    At_Kind_M_Ball,                         // Poké Ball

    // Character articles

    At_Kind_FighterStart,                   // Start of fighter article IDs
    At_Kind_PK_Fire = At_Kind_FighterStart, // PK Fire pillar
    At_Kind_Link_Bomb,                      // Link's Bomb
    
    // Stage hazards

    At_Kind_GroundStart,                    // Start of stage hazard IDs
    At_Kind_POW = At_Kind_GroundStart,      // POW block
    At_Kind_Gr_Bumper,                      // Bumper (Peach's Castle)
    At_Kind_Pakkun,                         // Pirahna Plant
    At_Kind_Mato,                           // Target
    At_Kind_Gr_Bomb,                        // Race to the Finish bomb
    At_Kind_Gr_Lucky,                       // Chansey (Saffron City)
    At_Kind_Marumine,                       // Electrode
    At_Kind_Hitokage,                       // Charmander
    At_Kind_Fushigibana,                    // Venusaur
    At_Kind_Porygon,                        // Porygon

    // Pokémon

    At_Kind_MonsterStart,                   // Start of Pokémon article IDs
    At_Kind_Iwark = At_Kind_MonsterStart,   // Onix
    At_Kind_Kabigon,                        // Snorlax
    At_Kind_Tosakinto,                      // Goldeen
    At_Kind_Nyars,                          // Meowth
    At_Kind_Lizardon,                       // Charizard
    At_Kind_Spear,                          // Beedrill
    At_Kind_Kamex,                          // Blastoise
    At_Kind_At_Lucky,                       // Chansey (Poké Ball)
    At_Kind_Starmie,                        // Starmie
    At_Kind_Sawamura,                       // Hitmonlee
    At_Kind_Dogas,                          // Koffing
    At_Kind_Pippi,                          // Clefairy
    At_Kind_Mew,                            // Mew

    At_Kind_CustomStart                     // Start of custom article IDs (future modding?)

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

typedef struct ArticleSpawnData
{
    u32 w0;
    ArticleFileData **p_file;
    s32 offset;
    u32 w3;

} ArticleSpawnData;

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

typedef struct ArticleStatusDesc
{
    bool32 (*cb_anim)(GObj*);
    bool32 (*cb_coll)(GObj*);
    bool32 (*cb_give_damage)(GObj*);
    bool32 (*cb_shield_block)(GObj*);
    bool32 (*cb_shield_deflect)(GObj*);
    bool32 (*cb_attack)(GObj*);
    bool32 (*cb_reflect)(GObj*);
    bool32 (*cb_take_damage)(GObj*);

} ArticleStatusDesc;

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
    u32 flags_0x4C_b1 : 1;
    u32 flags_0x4C_b2 : 1;
    u32 can_rehit : 1; // Article can rehit targets after default rehit cooldown expires
    u32 can_deflect : 1;
    u32 can_reflect : 1;
    u32 can_absorb : 1; // Not actually absorb but not yet known either
    u16 attack_id : 6;
    u16 flags_0x4C_b7 : 1;
    u16 flags_0x4E;
    CommonAttackFlags flags_hi;
    CommonAttackFlags flags_lw;
    s32 hitbox_count;
    ArticleHitUnk article_hit_unk[2];
    ArticleHitArray hit_targets[4];

} Article_Hit;

typedef struct ArticleHitEvent // Hitbox subaction event?
{
    u8 timer;
    s32 angle : 10;
    u32 damage : 8;
    u16 size;

} ArticleHitEvent;

typedef struct Article_Hurt
{
    u8 interact_mask; // 0x1 = interact with fighters, 0x2 = interact with items, 0x4 = interact with other articles
    s32 hit_status;
    Vec3f offset; // Added to TopN joint
    Vec3f size;

} Article_Hurt; // Article Hurtbox, might be larger

typedef struct atCommonAttributes
{
    void *unk_0x0;
    u8 filler_0x4[0x2C - 0x4];
    Vec2h gfx_offset; // Universal?
    s16 ledge_stop_width; // Used by Bob-Omb to determine when to turn around
    u8 filler_0x32[0x46 - 0x32];
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
    f32 damage_knockback; // Angle at which article will be launched when getting hit?
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
    s32 lifetime;
    f32 vel_scale;
    u16 unk_0x2C8;
    u16 drop_sfx;
    u16 throw_sfx;

    u8 is_show_indicator : 1; // Bool to check whether to display red arrow indicator above article or not
    u8 is_pause_article : 1; // Suspend article logic updates? Might be used to tell if a fighter is holding this article?
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
    u16 pickup_wait : 12; // Number of frames article can last without being picked up (if applicable)
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
    u16 at_multi; // Some sort of universal multi-purpose variable, e.g. it is used as intangibility delay for Star Man and ammo count for Ray Gun

    u8 x340_flag_b0123 : 4;
    f32 rotate_speed;
    GObj *unk_0x348;

    u8 arrow_flash_timer; // Frequency of red arrow indicator flash
    u8 unk_0x34D;
    u8 unk_0x34E;
    u8 unk_0x34F;

    union
    {
        Common_ArticleVars common;
        BombHei_ArticleVars bombhei;
        Shell_ArticleVars shell;
        Taru_ArticleVars taru;
        Bumper_ArticleVars bumper;
        Gr_Lucky_ArticleVars gr_lucky;
        M_Ball_ArticleVars m_ball;
        Pakkun_ArticleVars pakkun;
        Iwark_ArticleVars iwark;
        Kabigon_ArticleVars kabigon;

    } article_vars;

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
