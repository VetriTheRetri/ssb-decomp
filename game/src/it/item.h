#ifndef _ITEM_H_
#define _ITEM_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/it/itemvars.h>
#include <game/src/gm/gmmisc.h>
#include <game/src/gm/gmsound.h>
#include <game/src/ef/effect.h>
#include "gmmatch.h"

#define ITEM_ALLOC_MAX 16

#define ITEM_FLAG_PROJECT (1 << 31)              // Perform initial collision check when spawning item?

#define ITEM_MASK_SPAWN_FIGHTER 0                   // Item spawned by fighter
#define ITEM_MASK_SPAWN_GROUND 1                    // Item spawned by stage 
#define ITEM_MASK_SPAWN_ITEM 2                      // Item spawned by another item
#define ITEM_MASK_SPAWN_ARTICLE 3                   // Item spawned by Pokémon / misc entity class(es?)
#define ITEM_MASK_SPAWN_DEFAULT 4

#define ITEM_MASK_SPAWN_ALL 0xF                     // Mask all GObj classes that can spawn items?

#define ITEM_TEAM_DEFAULT 4                         // Item is teamless; deals damage to any eligible target
#define ITEM_PORT_DEFAULT GMMATCH_PLAYERS_MAX
#define ITEM_HANDICAP_DEFAULT 9 // Handicap?
#define ITEM_STALE_DEFAULT 1.0F

#define ITEM_PICKUP_WAIT_DEFAULT 1400               // "Lifetime" while item is not being carried

#define ITEM_REFLECT_MAX_DEFAULT 100                // Maximum damage cap for reflected articles
#define ITEM_REFLECT_MUL_DEFAULT 1.8F               // Universal reflect damage multiplier
#define ITEM_REFLECT_ADD_DEFAULT 0.99F              // Added after multiplying article's hitbox damage

#define ITEM_DESPAWN_FLASH_BEGIN_DEFAULT 180U       // Item starts flashing rapidly once its lifetime (?) drops below this value
#define ITEM_ARROW_FLASH_INT_DEFAULT 45             // Red arrow pointing downward at article "blinks" at this frequency (45 frames visible, 45 frames invisible)

#define ITEM_REHIT_TIME_DEFAULT 16

#define ITEM_HOP_ANGLE_DEFAULT F_DEG_TO_RAD(135.0F) // 2.3561945F

#define ITEM_SPIN_SPEED_MUL_DEFAULT 0.31415927F     // 0.31415927F
#define ITEM_SPIN_SPEED_MUL_NEW_SPAWN 0.17453294F   // 0.17453294F, might actually be incorrect
#define ITEM_SPIN_SPEED_MUL_PREV_SPAWN 0.27925268F

#define ITEM_SPIN_SPEED_SET_SMASH_THROW (-0.36651915F)
#define ITEM_SPIN_SPEED_SET_NORMAL_THROW (-0.17453294F)

#define ITEM_SPIN_SPEED_FRACTION_DEFAULT 0.01F // Also multiplies spin speed

typedef enum atKind
{
    // Common articles

    It_Kind_CommonStart,                        // Start of common item IDs
    It_Kind_Box = It_Kind_CommonStart,          // Crate
    It_Kind_Taru,                               // Barrel
    It_Kind_Capsule,                            // Capsule
    It_Kind_Egg,                                // Egg
    It_Kind_Tomato,                             // Maxim Tomato
    It_Kind_Heart,                              // Heart
    It_Kind_Star,                               // Star Man
    It_Kind_Sword,                              // Beam Sword
    It_Kind_Bat,                                // Home-Run Bat
    It_Kind_Harisen,                            // Fan
    It_Kind_StarRod,                            // Star Rod
    It_Kind_L_Gun,                              // Ray Gun
    It_Kind_F_Flower,                           // Fire Flower
    It_Kind_Hammer,                             // Hammer
    It_Kind_MSBomb,                             // Motion-Sensor Bomb
    It_Kind_BombHei,                            // Bob-Omb
    It_Kind_It_Bumper,                          // Bumper (Item)
    It_Kind_G_Shell,                            // Green Shell
    It_Kind_R_Shell,                            // Red Shell
    It_Kind_M_Ball,                             // Poké Ball
    It_Kind_CommonEnd = It_Kind_M_Ball,         // End of common item IDs

    // Character articles

    It_Kind_FighterStart,                       // Start of fighter item IDs
    It_Kind_PKFire = It_Kind_FighterStart,     // PK Fire pillar
    It_Kind_Link_Bomb,                          // Link's Bomb
    It_Kind_FighterEnd = It_Kind_Link_Bomb,     // End of fighter item IDs

    // Stage hazards

    It_Kind_GroundStart,                        // Start of stage hazard IDs
    It_Kind_PowerBlock = It_Kind_GroundStart,   // POW block
    It_Kind_Gr_Bumper,                          // Bumper (Peach's Castle)
    It_Kind_Pakkun,                             // Pirahna Plant
    It_Kind_Mato,                               // Target
    It_Kind_RaceBomb,                           // Race to the Finish bomb

    It_Kind_GrMonsterStart,                     // Start of stage Pokémon
    It_Kind_Gr_Lucky = It_Kind_GrMonsterStart,  // Chansey (Saffron City)
    It_Kind_Marumine,                           // Electrode
    It_Kind_Hitokage,                           // Charmander
    It_Kind_Fushigibana,                        // Venusaur
    It_Kind_Porygon,                            // Porygon
    It_Kind_GroundEnd = It_Kind_Porygon,        // End of stage hazard IDs
    It_Kind_GrMonsterEnd = It_Kind_GroundEnd,   // End of stage Pokémon

    // Pokémon

    It_Kind_MbMonsterStart,                     // Start of Pokémon item IDs
    It_Kind_Iwark = It_Kind_MbMonsterStart,     // Onix
    It_Kind_Kabigon,                            // Snorlax
    It_Kind_Tosakinto,                          // Goldeen
    It_Kind_Nyars,                              // Meowth
    It_Kind_Lizardon,                           // Charizard
    It_Kind_Spear,                              // Beedrill
    It_Kind_Kamex,                              // Blastoise
    It_Kind_Mb_Lucky,                           // Chansey (Poké Ball)
    It_Kind_Starmie,                            // Starmie
    It_Kind_Sawamura,                           // Hitmonlee
    It_Kind_Dogas,                              // Koffing
    It_Kind_Pippi,                              // Clefairy
    It_Kind_Mew,                                // Mew
    It_Kind_MbMonsterEnd = It_Kind_Mew,         // End of Pokémon item IDs

    It_Kind_CustomStart                         // Start of custom item IDs (future modding?)

} atKind;

typedef enum itWeight
{
    It_Weight_Heavy,
    It_Weight_Light

} itWeight;

typedef enum atType
{
    It_Type_Ground,     // Item is spawned by the stage (?)
    It_Type_Swing,      // Item can be thrown and swung
    It_Type_Shoot,      // Item can be fired
    It_Type_Throw,      // Item can only be thrown
    It_Type_Touch,      // Item has special properties on interaction
    It_Type_Special,    // Hammer, Heart and Maxim Tomato?
    It_Type_Fighter     // Item spawned by fighter's item (projectile) ?

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

typedef struct itHitPositions
{
    Vec3f pos;
    Vec3f pos_prev;
    s32 unused1;
    u8 filler[0x5C - 0x1C];
    f32 unused2;

} itHitPositions;

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
    s32 update_state;                   // Hitbox's position update mode (0 = disabled, 1 = fresh, 2 = transfer, 3 = interpolate)
    s32 damage;                         // Hitbox's base damage output
    f32 stale;                          // Might be swapped with throw_mul
    f32 throw_mul;                      // Might be swapped with stale
    s32 element;                        // Hitbox's element
    Vec3f offset[2];                    // Hitbox offset from TopN translation vector?
    f32 size;                           // Hitbox size
    s32 angle;                          // Launch angle
    u32 knockback_scale;                // Knockback growth
    u32 knockback_weight;               // Weight-Dependent Set Knockback
    u32 knockback_base;                 // Base knockback
    s32 shield_damage;                  // Shield damage
    s32 priority;                       // Priority?
    u8 interact_mask;                   // Mask of object classes hitbox can interact with; 0x1 = fighters, 0x2 = items, 0x4 = articles
    u16 hit_sfx;                        // Played when hitbox connects with a hurtbox
    u32 clang : 1;                      // Item's hitbox can collide with other hitboxes
    u32 can_rehit_item : 1;             // Item can rehit item after default rehit cooldown expires
    u32 can_rehit_fighter : 1;          // Item can rehit fighter after default rehit cooldown expires
    u32 can_rehit_shield : 1;           // Item can rehit shield after default rehit cooldown expires
    u32 can_hop : 1;                    // Item can bounce off shields
    u32 can_reflect : 1;                // Item can be reflected
    u32 can_shield : 1;                 // Item can be shielded
    u32 attack_id : 6;                  // Attack ID copied from object that spawned this item
    u16 motion_count;                   // Item's animation update number?
    gmAttackFlags stat_flags;           // Item's status flags 
    u16 stat_count;                     // Item's status update number
    s32 hitbox_count;                   // Item's hitbox count (Up to 2?)
    itHitPositions hit_positions[2];    // Item hitbox position?
    gmHitCollisionRecord hit_targets[4];// Item's record of attacked targets

} Item_Hit;

typedef struct itHitEvent               // Hitbox subaction event?
{
    u8 timer;
    s32 angle : 10;
    u32 damage : 8;
    u16 size;

} itHitEvent;

typedef struct itHitDesc
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

} itHitDesc;

typedef struct Item_Hurt
{
    u8 interact_mask;                   // 0x1 = interact with fighters, 0x2 = interact with weapons, 0x4 = interact with other items
    s32 hitstatus;                      // 0 = none, 1 = normal, 2 = invincible, 3 = intangible
    Vec3f offset;                       // Offset added to TopN joint's translation vector
    Vec3f size;                         // Hurtbox size

} Item_Hurt;

typedef struct itCommonAttributes
{
    void *unk_0x0;
    void *unk_0x4;
    void *unk_atca_0x8;
    void *unk_atca_0xC;
    u32 unk_0x10_b0 : 1;
    u32 unk_0x10_b1 : 1;
    u32 unk_0x10_b2 : 1;
    u32 is_give_hitlag : 1;
    u32 weight : 1;                     // Heavy = 0, Light = 1
    s32 hit_offset1_x : 16;
    s32 hit_offset1_y : 16;             // When in doubt, make these raw s16
    s32 hit_offset1_z : 16;
    s32 hit_offset2_x : 16;
    s32 hit_offset2_y : 16;
    s32 hit_offset2_z : 16;
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

} itCommonAttributes;

typedef struct Item_Struct              // Common items, stage hazards and Pokémon
{
    void *ip_alloc_next;                // Memory region allocated for next Item_Struct
    GObj *item_gobj;                    // Item's GObj pointer
    GObj *owner_gobj;                   // Item's owner
    atKind it_kind;                     // Item ID
    s32 type;                           // Item type
    u8 team;                            // Item's team
    u8 port_id;                         // Item's port index
    u8 handicap;                        // Item's handicap
    s32 player_number;                  // Item's player number
    s32 percent_damage;                 // Item's damage
    u32 hitlag_timer;                   // Item's hitlag
    s32 lr;                             // Item's facing direction

    struct phys_info
    {
        f32 vel_ground;                 // Item's ground velocity
        Vec3f vel;                      // Item's aerial velocity

    } phys_info;

    Coll_Data coll_data;                // Item's collision data

    Ground_Air ground_or_air;           // Ground or air bool

    Item_Hit item_hit;                  // Item's hitbox
    Item_Hurt item_hurt;                // Item's hurtbox

    s32 hit_victim_damage;              // Damage applied to entity this item has hit
    s32 lr_attack;                      // Direction of outgoing attack?
    s32 hit_reflect_damage;             // Damage on reflection?
    s32 hit_attack_damage;              // Damage item dealt to other attack
    s32 hit_shield_damage;              // Damage item dealt to shield
    f32 shield_collide_angle;           // Angle at which item collided with shield?
    Vec3f shield_collide_vec;           // Position of shield this item collided with?
    GObj *reflect_gobj;                 // GObj that reflected this item
    gmAttackFlags reflect_stat_flags;   // Status flags of GObj reflecting this item (e.g. is_smash_attack, is_ground_or_air, is_special_attack, etc.)
    u16 reflect_stat_count;             // Status update count at the time the item is reflected?
    s32 damage_last;                    // I don't know why there are at least two of these
    f32 damage_knockback;               // Angle at which article will be launched when getting hit?
    s32 damage_taken_recent;            // How does this work?
    s32 damage_angle;                   // Angle of attack that hit the item
    s32 damage_element;                 // Element of attack that hit the item
    s32 lr_damage;                      // Direction of incoming attack
    GObj *damage_gobj;                  // GObj that last dealt damage to this article?
    u8 damage_team;                     // Team of attacker
    u8 damage_port;                     // Controller port of attacker
    s32 damage_player_number;           // Player number of attacker
    u8 damage_handicap;                 // Handicap of attacker
    s32 damage_display_state;           // Display mode of attacker which the item takes on
    s32 damage_taken_last;              // Final damage intake?
    s32 lifetime;                       // Item's duration in frames
    f32 vel_scale;                      // Scale item's velocity
    u16 unk_sfx;                        // Unused?
    u16 drop_sfx;                       // SFX to play when item is dropped?
    u16 throw_sfx;                      // SFX to play when item is thrown?

    u32 is_allow_pickup : 1;            // Bool to check whether item can be picked up or not
    u32 is_hold : 1;                    // I think this is used to tell if a fighter is holding this article?
    u32 times_landed : 2;               // Number of times item has touched the ground while not grabbed; overflows after 3
    u32 times_thrown : 3;               // Number of times item has been dropped or thrown; overflows after 7
    u32 weight : 1;                     // 0 = item is heavy, 1 = item is light
    u32 is_damage_all : 1;              // Item ignores ownership and can damage anything?
    u32 is_attach_surface : 1;          // Item is "sticking" to a surface? Related to attach_line_id, but if it remains TRUE when there is no collision, it still falls?
    u32 is_apply_mag_stale : 1;         // Apply magnitude and stale multiplier to damage output
    u16 attach_line_id;                 // Line ID that item is attached to? I don't understand how this works
    u32 pickup_wait : 12;               // Number of frames item can last without being picked up (if applicable)
    u32 is_allow_knockback : 1;         // Item can receive knockback velocity?
    u32 is_unused_item_bool : 1;        // Unused? Set various times, but no item process makes use of it
    u32 is_static_damage : 1;           // Ignore reflect multiplier if TRUE

    itCommonAttributes *attributes;     // Pointer to attributes

    Color_Overlay colanim;              // Item's color animation struct

    u32 is_hitlag_victim : 1;           // Item can deal hitlag to target
    u16 it_multi;                       // Some sort of universal multi-purpose variable, e.g. it is used as intangibility delay for Star Man and ammo count for Ray Gun

    u32 item_event_index : 4;           // Item hitbox script index? When in doubt, make this u8 : 4

    f32 rotate_speed;                   // Item rotation step

    GObj *indicator_gobj;               // Red arrow pickup indicator GObj
    u8 arrow_flash_timer;               // Frequency of red arrow indicator flash

    union item_vars                     // Item-specific state variables
    {
        BombHei_ItemVars bombhei;
        Shell_ItemVars shell;
        Taru_ItemVars taru;
        Bumper_ItemVars bumper;
        Gr_Lucky_ItemVars gr_lucky;
        M_Ball_ItemVars m_ball;
        Pakkun_ItemVars pakkun;
        Iwark_ItemVars iwark;
        Kabigon_ItemVars kabigon;
        Tosakinto_ItemVars tosakinto;
        Mew_ItemVars mew;
        Nyars_ItemVars nyars;
        Lizardon_ItemVars lizardon;
        Spear_ItemVars spear;
        Kamex_ItemVars kamex;
        Mb_Lucky_ItemVars mb_lucky;
        Starmie_ItemVars starmie;
        Dogas_ItemVars dogas;
        Marumine_ItemVars marumine;
        Porygon_ItemVars porygon;
        Hitokage_ItemVars hitokage;
        Fushigibana_ItemVars fushigibana;
        RaceBomb_ItemVars gr_bomb;
        PKFire_ItemVars pkfire;
        Link_Bomb_ItemVars link_bomb;

    } item_vars;

    s32 display_state;                  // Item's display mode: 0 = normal, 1 = hit collisions, 2 = opaque hurtboxes + transparent attack hitboxes, 3 = map collisions

    bool32 (*proc_update)(GObj*);       // Update general item information
    bool32 (*proc_map)(GObj*);          // Update item's map collision
    bool32 (*proc_hit)(GObj*);          // Runs when item collides with a hurtbox
    bool32 (*proc_shield)(GObj*);       // Runs when item collides with a shield
    bool32 (*proc_hop)(GObj*);          // Runs when item bounces off a shield
    bool32 (*proc_setoff)(GObj*);       // Runs when item's hitbox collides with another hitbox
    bool32 (*proc_reflector)(GObj*);    // Runs when item is reflected
    bool32 (*proc_damage)(GObj*);       // Runs when iteme takes damage
    bool32 (*proc_dead)(GObj*);         // Runs when item is in a blast zone

} Item_Struct;

#define itGetStruct(item_gobj) \
((Item_Struct*)item_gobj->user_data) \

// Points to all sorts of data

#define itGetPData(ip, off1, off2) \
( (void*) ( ( (uintptr_t)(ip)->attributes->unk_0x0 - (intptr_t)&(off1) ) + (intptr_t)&(off2) ) ) \

#define itGetHitEvent(it_desc, off) \
( (itHitEvent*) ( (uintptr_t)*(it_desc).p_file + (intptr_t)&(off) ) )

#endif
