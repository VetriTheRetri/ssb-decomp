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

#define ITEM_TEAM_DEFAULT 4U
#define ITEM_PORT_DEFAULT 4U
#define ITEM_UNK_DEFAULT 9U                     // CPU level?

#define ITEM_FLAG_PROJECT 0x80000000            // Perform initial collision check when spawning item?

#define ITEM_MASK_SPAWN_FIGHTER 0               // Item spawned by fighter
#define ITEM_MASK_SPAWN_NONE 1                  // Item spawned independently 
#define ITEM_MASK_SPAWN_ITEM 2                  // Item spawned by another item
#define ITEM_MASK_SPAWN_ARTICLE 3               // Item spawned by Pokémon / misc entity class(es?)

#define ITEM_MASK_SPAWN_ALL 0xF                 // Mask all GObj classes that can spawn items?

// Universal item hitbox attributes

#define ITEM_REHIT_TIME_DEFAULT 16              // If the item is multihit, its hitbox will refresh per victim after this many frames have passed

#define ITEM_REFLECT_MAX_DEFAULT 100            // Maximum damage cap for reflected items
#define ITEM_REFLECT_MUL_DEFAULT 1.8F           // Universal reflect damage multiplier
#define ITEM_REFLECT_ADD_DEFAULT 0.99F          // Added after multiplying item's hitbox damage

#define ITEM_STALE_ADD_DEFAULT 0.999F           // Bonus 1% added after multiplying hitbox damage with staling modifier

#define ITEM_DEFLECT_ANGLE_DEFAULT 2.3561945F   // Determines whether item bounces off a shield

typedef enum It_Spawn
{
    It_Spawn_Fighter,
    It_Spawn_Default,
    It_Spawn_Item,
    It_Spawn_Article                            // Spawned by Pokémon / miscellaneous entity class?

} It_Spawn;

typedef enum It_Kind
{
    It_Kind_Ness_PKThunder_Head = 0xE,
    It_Kind_Ness_PKThunder_Trail = 0xF,
    It_Kind_Link_Bomb = 0x15 // Is this an article?

} It_Kind;

typedef enum Item_Hit_Element
{
    It_Hit_Kind_Normal,
    It_Hit_Kind_Fire,

} Item_Hit_Element;

typedef struct ItemStatusDesc
{
    u8 unk_0x0;
    s32 it_kind;
    void *p_item; // Pointer to various item data
    int offset_it_hit; // Offset of item hitbox info
    u8 unk_0x10;
    u8 unk_0x11;
    u8 unk_0x12;
    u8 unk_0x13;
    bool32 (*cb_anim)(GObj*);
    bool32 (*cb_coll)(GObj*);
    bool32 (*cb_give_damage)(GObj*);
    bool32 (*cb_shield_block)(GObj*);
    bool32 (*cb_shield_deflect)(GObj*);
    bool32 (*cb_attack)(GObj*);
    bool32 (*cb_reflect)(GObj*);
    bool32 (*cb_absorb)(GObj*);

} ItemStatusDesc;

typedef struct ItemHitDesc // Moreso hitbox stuff
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
    u32 knockback_scale : 10U;
    u32 damage : 8U;
    u32 element : 4U;
    u32 knockback_weight : 10U;
    s32 shield_damage : 8U;
    u32 hitbox_count : 2U;
    u32 clang : 1U;
    u32 sfx : 10U;
    u32 priority : 3U;
    u32 flags_0x2F_b0 : 1U;
    u32 flags_0x2F_b1 : 1U;
    u32 can_deflect : 1U;
    u32 can_reflect : 1U;
    u32 can_absorb : 1U;
    u32 can_shield : 1U;
    u32 flags_0x2F_b6 : 1U;
    u32 flags_0x2F_b7 : 1U;
    u32 knockback_base : 10U;

} ItemHitDesc;

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

typedef struct ItemHitVictimFlags
{
    u32 flags_b0 : 1;
    u32 flags_b1 : 1;
    u32 flags_b2 : 1;
    u32 flags_b3 : 1;
    u32 flags_b456 : 3;
    u32 timer_rehit : 6;

} ItemHitVictimFlags;

typedef struct _ItemHitArray
{
    GObj *victim_gobj;
    ItemHitVictimFlags victim_flags;

} ItemHitArray;

typedef struct _Item_Hit
{
    s32 update_state; // 0 = disabled, 1 = new hitbox, 2 and 3 = interpolate/copy current position to previous
    s32 damage; // 0x4
    f32 stale; // Multiplies damage
    u32 element; // 0xC // Placed AFTER offset?
    Vec3f offset[2]; // 0x10 - 0x24   
    f32 size;
    s32 angle;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    s32 shield_damage;
    s32 priority; // Used to determine winner in item hitbox vs item hitbox interaction?
    u8 hit_status; // "Tangibility flag? 0x07"
    u8 unk_0x45;
    u16 hit_sfx;
    union
    {
        struct
        {
            u32 clang : 1;
            u32 flags_0x48_b1 : 1;
            u32 flags_0x48_b2 : 1;
            u32 flags_0x48_b3 : 1;
            u32 can_deflect : 1; // Actually determines whether item's shield deflect routine can run?
            u32 can_reflect : 1;
            u32 can_absorb : 1;
            u32 flags_0x48_b7 : 1;
            u32 can_shield : 1;
            u32 attack_id : 6;
            u32 flags_0x49_b7 : 1;
            union
            {
                CommonAttackFlags flags_0x4A;
                u16 flags_0x4A_halfword;
            };
        };
        u8 flags_0x48;
    };

    union
    {
        struct
        {
            u32 flags_0x4C_b012 : 3;
            u32 can_rehit : 1;
            u32 flags_0x4C_b4 : 1;
            u32 flags_0x4C_b5 : 1;
            u32 flags_0x4C_10bit : 10;
            u16 flags_0x4E;
        };
        CommonAttackFlags flags_0x4C;
        u16 flags_0x4C_halfword;
    };

    s32 hitbox_count;
    ItemHitUnk item_hit_unk[2];
    ItemHitArray hit_targets[4];

} Item_Hit;

typedef struct _Item_Struct
{
    u32 unk_x0;
    GObj *item_gobj;            // Pointer to item's GObj
    GObj *owner_gobj;           // Current owner of this item; expected to be fighter?
    s32 it_kind;                // Item ID
    u8 team;
    u8 port_index;
    u8 unk_0x12;
    s32 player_number;          // Number of player that spawned this item? 0 = item spawned on its own
    s32 lr;                     // Facing direction of item; -1 = LEFT, 0 = CENTER, 1 = RIGHT, 2 = WALL_UP (Thunder Jolt only?), 3 = WALL_DOWN (Thunder Jolt only?)

    struct
    {
        f32 vel_ground;
        Vec3f vel;

    } phys_info;

    Coll_Data coll_data;
    Ground_Air ground_or_air;
    Item_Hit item_hit[1];       // Indexed into an array so it can (hopefully) easily be expanded later

    s32 hit_victim_damage;      // Set to item hitbox's final damage output when hitting a target
    s32 unk_0x238;              // Might be self-damage?
    s32 hit_attack_damage;      // Set to item hitbox's final damage output when hitting another attack
    s32 hit_shield_damage;      // Set to item hitbox's final damage output when hitting a shield
    f32 shield_collide_angle;   // If this is less than 135 degrees, the item gets deflected
    Vec3f shield_collide_vec;   //
    GObj *reflect_gobj;         // GObj that reflected this item
    u16 unk_0x258;              // Attack flags
    u16 unk_0x25A;              // Attack flags
    GObj *absorb_gobj;          // GObj that absorbed this item

    u8 is_hitlag_victim : 1;
    u8 is_hitlag_item : 1;
    u8 x260_flag_b2 : 1;
    u8 x260_flag_b3 : 1;
    u8 x260_flag_b4 : 1;
    u8 x260_flag_b5 : 1;
    u8 x260_flag_b6 : 1;
    u8 x260_flag_b7 : 1;
    u8 x261_flag_b0 : 1;
    u8 x261_flag_b1 : 1;
    u8 x261_flag_b2 : 1;
    u8 x261_flag_b3 : 1;
    u8 x261_flag_b4 : 1;
    u8 x261_flag_b5 : 1;
    u8 x261_flag_b6 : 1;
    u8 x261_flag_b7 : 1;
    u8 x262_flag_b0 : 1;
    u8 x262_flag_b1 : 1;
    u8 x262_flag_b2 : 1;
    u8 x262_flag_b3 : 1;
    u8 x262_flag_b4 : 1;
    u8 x262_flag_b5 : 1;
    u8 x262_flag_b6 : 1;
    u8 x262_flag_b7 : 1;
    u8 x263_flag_b0 : 1;
    u8 x263_flag_b1 : 1;
    u8 x263_flag_b2 : 1;
    u8 x263_flag_b3 : 1;
    u8 x263_flag_b4 : 1;
    u8 x263_flag_b5 : 1;
    u8 x263_flag_b6 : 1;
    u8 x263_flag_b7 : 1;

    u32 group_id;
    s32 lifetime; // Frames until item despawns

    u8 is_camera_follow : 1;
    u8 is_static_damage : 1; // If this is FALSE, item's damage can be modified (on reflection only?)
    u8 x26C_flag_b2 : 1;
    u8 x26C_flag_b3 : 1;
    u8 x26C_flag_b4 : 1;
    u8 x26C_flag_b5 : 1;
    u8 x26C_flag_b6 : 1;
    u8 x26C_flag_b7 : 1;
    u8 x26D_flag_b0 : 1;
    u8 x26D_flag_b1 : 1;
    u8 x26D_flag_b2 : 1;
    u8 x26D_flag_b3 : 1;
    u8 x26D_flag_b4 : 1;
    u8 x26D_flag_b5 : 1;
    u8 x26D_flag_b6 : 1;
    u8 x26D_flag_b7 : 1;
    u8 x26E_flag_b0 : 1;
    u8 x26E_flag_b1 : 1;
    u8 x26E_flag_b2 : 1;
    u8 x26E_flag_b3 : 1;
    u8 x26E_flag_b4 : 1;
    u8 x26E_flag_b5 : 1;
    u8 x26E_flag_b6 : 1;
    u8 x26E_flag_b7 : 1;
    u8 x26F_flag_b0 : 1;
    u8 x26F_flag_b1 : 1;
    u8 x26F_flag_b2 : 1;
    u8 x26F_flag_b3 : 1;
    u8 x26F_flag_b4 : 1;
    u8 x26F_flag_b5 : 1;
    u8 x26F_flag_b6 : 1;
    u8 x26F_flag_b7 : 1;

    gmSoundEffect *p_sfx;                   // Pointer to item's current ongoing sound effect
    u16 sfx_id;                             // ID of sound effect this item is supposed to play? (This gets checked against gmSoundEffect's ID when despawning)

    bool32 (*cb_anim)(GObj*);               // Main animation routine
    bool32 (*cb_coll)(GObj*);               // Main collision routine
    bool32 (*cb_give_damage)(GObj*);        // Item hits a hurtbox
    bool32 (*cb_shield_block)(GObj*);       // Item collides with shield head-on
    bool32 (*cb_shield_deflect)(GObj*);     // Item hits corner of shield and bounces off
    bool32 (*cb_attack)(GObj*);             // Item collides with another attack hitbox
    bool32 (*cb_reflect)(GObj*);            // Item gets reflected
    bool32 (*cb_absorb)(GObj*);             // Item gets absorbed
    bool32 (*cb_destroy)(GObj*);            // Item hits blastzones (only run on this condition?)
    union
    {
        Fireball_ItemVars fireball;
        Charge_Shot_ItemVars charge_shot;
        SamusBomb_ItemVars samus_bomb;
        ThunderJolt_ItemVars thunder_jolt;
        Thunder_ItemVars thunder;
        PK_Thunder_ItemVars pk_thunder;
        PK_Thunder_Trail_ItemVars pk_thunder_trail;
        Egg_Throw_ItemVars egg_throw;
        Spin_Attack_ItemVars spin_attack; // Link's Up Special
        Boomerang_ItemVars boomerang;
        Star_ItemVars star;

    } item_vars;

    s32 display_state;

} Item_Struct;

#define ItemGetStruct(item_gobj) \
((Item_Struct*)item_gobj->user_data) \

#endif