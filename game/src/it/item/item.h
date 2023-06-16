#ifndef _ITEM_H_
#define _ITEM_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/it/item/itemvars.h>
#include <game/src/gm/gmmisc.h>
#include <game/src/gm/gmsound.h>
#include <game/src/sys/develop.h>
#include <game/src/gm/gmmatch.h>

#define WEAPON_ALLOC_MAX 32                     // Allocate this many item user_data structs at once

#define WEAPON_STALE_DEFAULT 1.0F

#define WEAPON_TEAM_DEFAULT 4
#define WEAPON_PORT_DEFAULT GMMATCH_PLAYERS_MAX
#define WEAPON_HANDICAP_DEFAULT 9               // CPU level?

#define WEAPON_FLAG_PROJECT (1 << 31)           // Perform initial collision check when spawning item?

#define WEAPON_MASK_SPAWN_FIGHTER 0               // Item spawned by fighter
#define WEAPON_MASK_SPAWN_GROUND 1                // Item spawned by stage
#define WEAPON_MASK_SPAWN_WEAPON 2                // Item spawned by another item
#define WEAPON_MASK_SPAWN_ARTICLE 3               // Item spawned by Pokémon / misc entity class(es?)

#define WEAPON_MASK_SPAWN_ALL 0xF                 // Mask all GObj classes that can spawn items?

// Universal item hitbox attributes

#define WEAPON_REHIT_TIME_DEFAULT 16            // If the item is multihit, its hitbox will refresh per victim after this many frames have passed

#define WEAPON_REFLECT_TIME_DEFAULT 100         // Maximum damage cap for reflected items
#define WEAPON_REFLECT_MUL_DEFAULT 1.8F         // Universal reflect damage multiplier
#define WEAPON_REFLECT_ADD_DEFAULT 0.99F        // Added after multiplying item's hitbox damage

#define WEAPON_STALE_ADD_DEFAULT 0.999F         // Bonus 1% added after multiplying hitbox damage with staling modifier

#define WEAPON_DEFLECT_ANGLE_DEFAULT F_DEG_TO_RAD(135.0F) // 2.3561945F - Determines whether item bounces off a shield

typedef enum It_Kind
{
    It_Kind_PKThunder_Head = 0xE,
    It_Kind_PKThunder_Trail = 0xF,

} It_Kind;

typedef struct WeaponSpawnData
{
    u8 unk_0x0;
    s32 wp_kind;
    void **p_item; // Pointer to various item data
    intptr_t offset_wp_hit; // Offset of item hitbox info
    u8 unk_0x10;
    u8 unk_0x11;
    u8 unk_0x12;
    u8 unk_0x13;
    bool32 (*proc_update)(GObj*);
    bool32 (*proc_map)(GObj*);
    bool32 (*proc_hit)(GObj*);
    bool32 (*proc_shield)(GObj*);
    bool32 (*proc_hop)(GObj*);
    bool32 (*proc_setoff)(GObj*);
    bool32 (*proc_reflector)(GObj*);
    bool32 (*proc_absorb)(GObj*);

} WeaponSpawnData;

typedef struct wpCommonAttributes // Moreso hitbox stuff
{
    void *unk_0x0;
    void *unk_0x4;
    void *unk_0x8;
    void *unk_0xC;
    Vec3h offset[2];
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
    u32 sfx : 10;
    u32 priority : 3;
    u32 flags_0x2F_b0 : 1;
    u32 flags_0x2F_b1 : 1;
    u32 can_hop : 1;
    u32 can_reflect : 1;
    u32 can_absorb : 1;
    u32 can_shield : 1;
    u32 flags_0x2F_b6 : 1;
    u32 flags_0x2F_b7 : 1;
    u32 knockback_base : 10;

} wpCommonAttributes;

typedef struct ItemHitUnk
{
    Vec3f pos;
    Vec3f pos_prev;
    s32 unk_0x18;
    u8 filler_0x1C[0x54 - 0x1C];
    f32 unk_0x54;
    f32 unk_0x58;
    f32 unk_0x5C;

} ItemHitUnk;

typedef struct _ItemHitArray
{
    GObj *victim_gobj;
    gmHitCollisionFlags victim_flags;

} ItemHitArray;

typedef struct _Weapon_Hit
{
    s32 update_state; // 0 = disabled, 1 = new hitbox, 2 and 3 = interpolate/copy current position to previous
    s32 damage; // 0x4
    f32 stale; // Multiplies damage
    s32 element; // 0xC // Placed AFTER offset?
    Vec3f offset[2]; // 0x10 - 0x24   
    f32 size;
    s32 angle;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    s32 shield_damage;
    s32 priority; // Used to determine winner in item hitbox vs item hitbox interaction?
    u8 interact_mask; // Mask of object classes hitbox can interact with; 0x1 = fighters, 0x2 = items, 0x4 = articles
    u16 hit_sfx;
    u32 clang : 1;
    u32 flags_0x48_b1 : 1;
    u32 flags_0x48_b2 : 1;
    u32 can_rehit : 1;
    u32 can_hop : 1; // Actually determines whether item's shield deflect routine can run?
    u32 can_reflect : 1;
    u32 can_absorb : 1;
    u32 noheal : 1;
    u32 can_shield : 1;
    u32 attack_id : 6;
    u32 flags_0x49_b7 : 1;
    u16 motion_count;
    gmAttackFlags stat_flags;
    u16 stat_count;
    s32 hitbox_count;
    ItemHitUnk item_hit_unk[2];
    ItemHitArray hit_targets[4];

} Weapon_Hit;

typedef struct _Weapon_Struct
{
    void *wp_alloc_next;        // Pointer to next item struct
    GObj *weapon_gobj;          // Pointer to item's GObj
    GObj *owner_gobj;           // Current owner of this item; expected to be fighter?
    s32 wp_kind;                // Item ID
    u8 team;
    u8 port_id;
    u8 handicap;
    s32 player_number;          // Number of player that spawned this item? 0 = item spawned on its own
    s32 lr;                     // Facing direction of item; -1 = LEFT, 0 = CENTER, 1 = RIGHT, 2 = WALL_UP (Thunder Jolt only?), 3 = WALL_DOWN (Thunder Jolt only?)

    struct
    {
        f32 vel_ground;
        Vec3f vel;

    } phys_info;

    Coll_Data coll_data;
    Ground_Air ground_or_air;
    Weapon_Hit item_hit;          

    s32 hit_victim_damage;      // Set to item hitbox's final damage output when hitting a target
    s32 hit_reflect_damage;     // Might be self-damage?
    s32 hit_attack_damage;      // Set to item hitbox's final damage output when hitting another attack
    s32 hit_shield_damage;      // Set to item hitbox's final damage output when hitting a shield
    f32 shield_collide_angle;   // If this is less than 135 degrees, the item gets deflected
    Vec3f shield_collide_vec;   //
    GObj *reflect_gobj;         // GObj that reflected this item
    gmAttackFlags reflect_stat_flags;    // Attack flags
    u16 reflect_stat_count;     // Attack flags
    GObj *absorb_gobj;          // GObj that absorbed this item

    u32 is_hitlag_victim : 1;   // Item can deal hitlag to target
    u32 is_hitlag_item : 1;     // Item is in hitlag

    u32 group_id;

    s32 lifetime; // Frames until item despawns

    u32 is_camera_follow : 1;
    u32 is_static_damage : 1; // If this is FALSE, item's damage can be modified (on reflection only?)

    gmSoundEffect *p_sfx;                   // Pointer to item's current ongoing sound effect
    u16 sfx_id;                             // ID of sound effect this item is supposed to play? (This gets checked against gmSoundEffect's ID when despawning)

    bool32 (*proc_update)(GObj*);               // Main animation routine
    bool32 (*proc_map)(GObj*);               // Main collision routine
    bool32 (*proc_hit)(GObj*);        // Item hits a hurtbox
    bool32 (*proc_shield)(GObj*);       // Item collides with shield head-on
    bool32 (*proc_hop)(GObj*);     // Item hits corner of shield and bounces off
    bool32 (*proc_setoff)(GObj*);             // Item collides with another attack hitbox
    bool32 (*proc_reflector)(GObj*);            // Item gets reflected
    bool32 (*proc_absorb)(GObj*);             // Item gets absorbed
    bool32 (*proc_dead)(GObj*);            // Item hits blastzones (only run on this condition?)

    union item_vars
    {
        Fireball_WeaponVars fireball;
        ChargeShot_WeaponVars charge_shot;
        SamusBomb_WeaponVars samus_bomb;
        ThunderJolt_WeaponVars thunder_jolt;
        Thunder_WeaponVars thunder;
        PKThunder_WeaponVars pk_thunder;
        PKThunder_Trail_WeaponVars pk_thunder_trail;
        EggThrow_WeaponVars egg_throw;
        SpinAttack_WeaponVars spin_attack; // Link's Up Special
        Boomerang_WeaponVars boomerang;
        Star_WeaponVars star;
        Rock_WeaponVars rock; // Onix's Rock Slide
        Coin_WeaponVars coin;
        Hydro_WeaponVars hydro;
        Smog_WeaponVars smog;

    } item_vars;

    s32 display_state;

} Weapon_Struct;

#define wpGetStruct(weapon_gobj) \
((Weapon_Struct*)weapon_gobj->user_data) \

#endif