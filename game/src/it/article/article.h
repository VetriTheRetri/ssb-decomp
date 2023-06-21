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

#define ARTICLE_ALLOC_MAX 16

#define ARTICLE_FLAG_PROJECT (1U << 31)            // Perform initial collision check when spawning item?

#define ARTICLE_MASK_SPAWN_FIGHTER 0               // Article spawned by fighter
#define ARTICLE_MASK_SPAWN_GROUND 1                // Article spawned by stage 
#define ARTICLE_MASK_SPAWN_ITEM 2                  // Article spawned by another item
#define ARTICLE_MASK_SPAWN_ARTICLE 3               // Article spawned by Pok�mon / misc entity class(es?)
#define ARTICLE_MASK_SPAWN_DEFAULT 4

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

#define ARTICLE_DEFLECT_ANGLE_DEFAULT F_DEG_TO_RAD(135.0F) // 2.3561945F

#define ARTICLE_SPIN_SPEED_MUL_DEFAULT 0.31415927F
#define ARTICLE_SPIN_SPEED_MUL_NEW_SPAWN 0.17453294F
#define ARTICLE_SPIN_SPEED_MUL_PREV_SPAWN 0.27925268F

#define ARTICLE_SPIN_SPEED_SET_SMASH_THROW -0.36651915F
#define ARTICLE_SPIN_SPEED_SET_NORMAL_THROW -0.17453294F

#define ARTICLE_SPIN_SPEED_FRACTION_DEFAULT 0.01F // Also multiplies spin speed

typedef enum atKind
{
    // Common articles

    It_Kind_CommonStart,                    // Start of common article IDs
    It_Kind_Box = It_Kind_CommonStart,      // Crate
    It_Kind_Taru,                           // Barrel
    It_Kind_Capsule,                        // Capsule
    It_Kind_Egg,                            // Egg
    It_Kind_Tomato,                         // Maxim Tomato
    It_Kind_Heart,                          // Heart
    It_Kind_Star,                           // Star Man
    It_Kind_Sword,                          // Beam Sword
    It_Kind_Bat,                            // Home-Run Bat
    It_Kind_Harisen,                        // Fan
    It_Kind_StarRod,                        // Star Rod
    It_Kind_L_Gun,                          // Ray Gun
    It_Kind_F_Flower,                       // Fire Flower
    It_Kind_Hammer,                         // Hammer
    It_Kind_MSBomb,                         // Motion-Sensor Bomb
    It_Kind_BombHei,                        // Bob-Omb
    It_Kind_It_Bumper,                      // Bumper (Item)
    It_Kind_G_Shell,                        // Green Shell
    It_Kind_R_Shell,                        // Red Shell
    It_Kind_M_Ball,                         // Pok� Ball
    It_Kind_CommonEnd = It_Kind_M_Ball,     // End of common article IDs

    // Character articles

    It_Kind_FighterStart,                   // Start of fighter article IDs
    It_Kind_PK_Fire = It_Kind_FighterStart, // PK Fire pillar
    It_Kind_Link_Bomb,                      // Link's Bomb
    It_Kind_FighterEnd = It_Kind_Link_Bomb, // End of fighter article IDs

    // Stage hazards

    It_Kind_GroundStart,                    // Start of stage hazard IDs
    It_Kind_POW = It_Kind_GroundStart,      // POW block
    It_Kind_Gr_Bumper,                      // Bumper (Peach's Castle)
    It_Kind_Pakkun,                         // Pirahna Plant
    It_Kind_Mato,                           // Target
    It_Kind_Gr_Bomb,                        // Race to the Finish bomb

    It_Kind_GrMonsterStart,                 // Start of stage Pok�mon
    It_Kind_Gr_Lucky=It_Kind_GrMonsterStart,// Chansey (Saffron City)
    It_Kind_Marumine,                       // Electrode
    It_Kind_Hitokage,                       // Charmander
    It_Kind_Fushigibana,                    // Venusaur
    It_Kind_Porygon,                        // Porygon
    It_Kind_GroundEnd = It_Kind_Porygon,    // End of stage hazard IDs
    It_Kind_GrMonsterEnd=It_Kind_GroundEnd, // End of stage Pok�mon

    // Pok�mon

    It_Kind_MonsterStart,                   // Start of Pok�mon article IDs
    It_Kind_Iwark = It_Kind_MonsterStart,   // Onix
    It_Kind_Kabigon,                        // Snorlax
    It_Kind_Tosakinto,                      // Goldeen
    It_Kind_Nyars,                          // Meowth
    It_Kind_Lizardon,                       // Charizard
    It_Kind_Spear,                          // Beedrill
    It_Kind_Kamex,                          // Blastoise
    It_Kind_Mb_Lucky,                       // Chansey (Pok� Ball)
    It_Kind_Starmie,                        // Starmie
    It_Kind_Sawamura,                       // Hitmonlee
    It_Kind_Dogas,                          // Koffing
    It_Kind_Pippi,                          // Clefairy
    It_Kind_Mew,                            // Mew
    It_Kind_MonsterEnd = It_Kind_Mew,       // End of Pok�mon article IDs

    It_Kind_CustomStart                     // Start of custom article IDs (future modding?)

} atKind;

typedef enum atType
{
    It_Type_Ground,     // Article is spawned by the stage (?)
    It_Type_Swing,      // Article can be thrown and swung
    It_Type_Shoot,      // Article can be fired
    It_Type_Throw,      // Article can only be thrown
    It_Type_Touch,      // Article has special properties on interaction
    It_Type_Special,    // Hammer, Heart and Maxim Tomato?
    It_Type_Fighter     // Article spawned by fighter's item (projectile) ?

} atType; 

typedef struct gmMonsterInfo
{
    u8 monster_curr;
    u8 monster_prev;
    u8 monster_index[44];
    u8 monster_count;

} gmMonsterInfo;

static gmMonsterInfo Monster_Info; // Static (.bss) (0x8018D060)

typedef struct ArticleFileData
{
    f32 spawn_vel_y[20];

} ArticleFileData;

typedef struct itCreateDesc
{
    s32 it_kind;
    void **p_file;
    intptr_t offset;
    u8 unk_aspd_0xC;
    u8 unk_aspd_0xD;
    u8 unk_aspd_0xE;
    s32 update_state;
    bool32 (*proc_update)(GObj*);
    bool32 (*proc_map)(GObj*);
    bool32 (*proc_hit)(GObj*);
    bool32 (*proc_shield)(GObj*);
    bool32 (*proc_hop)(GObj*);
    bool32 (*proc_setoff)(GObj*);
    bool32 (*proc_reflector)(GObj*);
    bool32 (*proc_damage)(GObj*);

} itCreateDesc;

extern void *gItemFileData; // WARNING: This pointer exists in multiple areas and appears not to be exclusive to the Article section of Overlay 3 (0x8018D040)

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
    gmHitCollisionFlags victim_flags;

} ArticleHitArray;

typedef struct itStatusDesc
{
    bool32 (*proc_update)(GObj*);
    bool32 (*proc_map)(GObj*);
    bool32 (*proc_hit)(GObj*);
    bool32 (*proc_shield)(GObj*);
    bool32 (*proc_hop)(GObj*);
    bool32 (*proc_setoff)(GObj*);
    bool32 (*proc_reflector)(GObj*);
    bool32 (*proc_damage)(GObj*);

} itStatusDesc;

typedef struct _Item_Hit
{
    s32 update_state; // 0x0
    s32 damage; // 0x4
    f32 stale; // Might be swapped with throw_mul
    f32 throw_mul; // Might be swapped with stale
    s32 element; // 0xC // Placed AFTER offset?
    Vec3f offset[2]; // 0x10 - 0x28    
    f32 size;
    s32 angle;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    s32 shield_damage; // Shield damage?
    s32 priority; // Priority?
    u8 interact_mask; // Mask of object classes hitbox can interact with; 0x1 = fighters, 0x2 = items, 0x4 = articles
    u16 hit_sfx;
    u32 clang : 1;
    u32 can_rehit_item : 1;
    u32 can_rehit_fighter : 1;
    u32 can_rehit_shield : 1; // Article can rehit targets after default rehit cooldown expires
    u32 can_hop : 1;
    u32 can_reflect : 1;
    u32 can_shield : 1; // Not actually absorb but not yet known either
    u32 attack_id : 6; // Unconfirmed
    u16 motion_count;
    gmAttackFlags stat_flags;
    u16 stat_count;
    s32 hitbox_count;
    ArticleHitUnk article_hit_unk[2];
    ArticleHitArray hit_targets[4];

} Item_Hit;

typedef struct ArticleHitEvent // Hitbox subaction event?
{
    u8 timer;
    s32 angle : 10;
    u32 damage : 8;
    u16 size;

} ArticleHitEvent;

typedef struct ArticleHitDesc
{
    u8 timer;
    s32 angle : 10;
    u32 damage : 8;
    u16 size;
    u32 knockback_scale;
    u32 knockback_weight;
    u32 knockback_base;
    s32 element;
    u32 clang : 1;
    s32 shield_damage;
    u16 hit_sfx;

} ArticleHitDesc;

typedef struct Article_Hurt
{
    u8 interact_mask; // 0x1 = interact with fighters, 0x2 = interact with items, 0x4 = interact with other articles
    s32 hitstatus;
    Vec3f offset; // Added to TopN joint
    Vec3f size;

} Article_Hurt; // Article Hurtbox, might be larger

typedef struct atCommonAttributes
{
    void *unk_0x0;
    void *unk_0x4;
    void *unk_atca_0x8;
    void *unk_atca_0xC;
    u32 unk_0x10_b0 : 1;
    u32 unk_0x10_b1 : 1;
    u32 unk_0x10_b2 : 1;
    u32 is_give_hitlag : 1;
    u32 is_light : 1;
    s32 hit_offset1_x : 16;
    s16 hit_offset1_y;
    s16 hit_offset1_z;
    s16 hit_offset2_x;
    s16 hit_offset2_y;
    s16 hit_offset2_z;
    Vec3h hurt_offset;
    Vec3h hurt_size;
    s16 objectcoll_top;
    s16 objectcoll_center;
    s16 objectcoll_bottom;
    s16 objectcoll_width;
    u16 size;
    s32 angle : 10;
    u32 knockback_scale : 10;
    u32 damage : 8;
    u32 element : 4;
    u32 knockback_weight : 10;
    s32 shield_damage : 8;
    u32 hitbox_count : 2;
    u32 clang : 1;
    u32 hit_sfx : 10;
    u32 priority : 3;
    u32 can_rehit_item : 1;
    u32 can_rehit_fighter : 1;
    u32 can_hop : 1;
    u32 can_reflect : 1;
    u32 can_shield : 1;
    u32 knockback_base : 10;
    u32 type : 4;
    u32 hitstatus : 4;
    u32 unk_atca_0x3C_b6 : 1;
    u32 unk_atca_0x3C_b7 : 1;
    u32 unk_atca_sfx : 10;
    u32 drop_sfx : 10;
    u32 throw_sfx : 10;
    u32 vel_scale : 9;
    u16 spin_speed;

} atCommonAttributes;

typedef struct Item_Struct // Common items, stage hazards and Pok�mon
{
    void *ap_alloc_next; // Region allocated for next Item_Struct
    GObj *article_gobj;
    GObj *owner_gobj;
    atKind it_kind;
    s32 type;
    u8 team;
    u8 port_id;
    u8 handicap;
    s32 player_number;
    s32 percent_damage;
    u32 hitlag_timer;
    s32 lr;

    struct phys_info
    {
        f32 vel_ground;
        Vec3f vel;

    } phys_info;

    Coll_Data coll_data;

    Ground_Air ground_or_air;

    Item_Hit article_hit;
    Article_Hurt article_hurt;

    s32 hit_victim_damage;
    s32 lr_attack; // Direction of outgoing attack?
    s32 hit_reflect_damage;
    s32 hit_attack_damage;
    s32 hit_shield_damage;
    f32 shield_collide_angle;
    Vec3f shield_collide_vec;
    GObj *reflect_gobj;
    gmAttackFlags reflect_stat_flags;
    u16 reflect_stat_count;
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
    u8 damage_handicap;
    s32 damage_display_state;
    s32 damage_taken_last;
    s32 lifetime;
    f32 vel_scale;
    u16 unk_0x2C8;
    u16 drop_sfx;
    u16 throw_sfx;

    u32 is_allow_pickup : 1; // Bool to check whether item can be picked up or not
    u32 is_hold : 1; // I think this is used to tell if a fighter is holding this article?
    u32 times_landed : 2; // Number of times item has touched the ground while not grabbed; overflows after 3
    u32 times_thrown : 3; // Number of times item has been dropped or thrown; overflows after 7
    u32 is_light_throw : 1;
    u32 is_damage_all : 1; // Article ignores ownership and can damage anything?
    u32 x2CF_flag_b1 : 1;
    u32 x2CF_flag_b2 : 1;
    u32 x2CF_flag_b3 : 1;
    u32 x2CF_flag_b4 : 1;
    u32 x2CF_flag_b5 : 1;
    u32 x2CF_flag_b6 : 1;
    u32 x2CF_flag_b7 : 1;
    u16 unk_0x2D0; // Some line ID 
    u32 pickup_wait : 12; // Number of frames article can last without being picked up (if applicable)
    u32 x2D3_flag_b4 : 1;
    u32 x2D3_flag_b5 : 1;
    u32 is_static_damage : 1;
    u32 x2D3_flag_b7 : 1;

    atCommonAttributes *attributes;

    Color_Overlay colanim;

    u32 is_hitlag_victim : 1;
    u16 at_multi; // Some sort of universal multi-purpose variable, e.g. it is used as intangibility delay for Star Man and ammo count for Ray Gun

    u8 x340_flag_b0123 : 4; // Script timer?
    f32 rotate_speed;
    GObj *unk_0x348;
    u8 arrow_flash_timer; // Frequency of red arrow indicator flash

    union article_vars
    {
        BombHei_ArticleVars bombhei;
        Shell_ArticleVars shell;
        Taru_ArticleVars taru;
        Bumper_ArticleVars bumper;
        Gr_Lucky_ArticleVars gr_lucky;
        M_Ball_ArticleVars m_ball;
        Pakkun_ArticleVars pakkun;
        Iwark_ArticleVars iwark;
        Kabigon_ArticleVars kabigon;
        Tosakinto_ArticleVars tosakinto;
        Mew_ArticleVars mew;
        Nyars_ArticleVars nyars;
        Lizardon_ArticleVars lizardon;
        Spear_ArticleVars spear;
        Kamex_ArticleVars kamex;
        Mb_Lucky_ArticleVars mb_lucky;
        Starmie_ArticleVars starmie;
        Dogas_ArticleVars dogas;
        Marumine_ArticleVars marumine;
        Porygon_ArticleVars porygon;
        Hitokage_ArticleVars hitokage;
        Fushigibana_ArticleVars fushigibana;
        Gr_Bomb_ArticleVars gr_bomb;
        PK_Fire_ArticleVars pkfire;
        Link_Bomb_ArticleVars link_bomb;

    } article_vars;

    s32 display_state;

    bool32 (*proc_update)(GObj*);
    bool32 (*proc_map)(GObj*);
    bool32 (*proc_hit)(GObj*);
    bool32 (*proc_shield)(GObj*);
    bool32 (*proc_hop)(GObj*);
    bool32 (*proc_setoff)(GObj*);
    bool32 (*proc_reflector)(GObj*);
    bool32 (*proc_damage)(GObj*);
    bool32 (*proc_dead)(GObj*);

} Item_Struct;

#define itGetStruct(article_gobj) \
((Item_Struct*)article_gobj->user_data) \


// Points to all sorts of data

#define ArticleGetPData(ap, off1, off2) \
( (void*) ( ((uintptr_t)ap->attributes->unk_0x0 - (intptr_t)&off1 ) + (intptr_t)&off2) ) \

#endif
