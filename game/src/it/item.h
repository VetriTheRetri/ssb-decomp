#ifndef _ITEM_H_
#define _ITEM_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/it/itemvars.h>

#define ITEM_TEAM_DEFAULT 4U
#define ITEM_PORT_DEFAULT 4U
#define ITEM_UNK_DEFAULT 9U // CPU level?

#define ITEM_FLAG_PROJECT 0x80000000 // Perform initial collision check when spawning item?

#define ITEM_MASK_SPAWN 0xF // Mask all GObj classes that can spawn items?

#define ITEM_REHIT_DEFAULT 16 // If the item is multihit, its hitbox will refresh per victim after this many frames have passed

typedef enum It_Spawn
{
    It_Spawn_Fighter,
    It_Spawn_Default,
    It_Spawn_Item,
    It_Spawn_Monster // Spawned by Pokémon / miscellaneous entity class?

} It_Spawn;

typedef enum It_Kind
{
    It_Kind_Link_Bomb = 0x15

} It_Kind;

typedef enum itHitUpdateState
{
    itHit_UpdateState_Disable,          // No hitbox or updates to it
    itHit_UpdateState_New,              // Initialize hitbox positions
    itHit_UpdateState_Transfer,         // Transitions to update state 3, that's it
    itHit_UpdateState_Interpolate       // Copies current position to previous

} itHitUpdateState;

typedef struct ItemStatusDesc
{
    u8 unk_0x0;
    s32 it_kind;
    void *unk_0x8;
    int unk_0xC;
    u8 unk_0x10;
    u8 unk_0x11;
    u8 unk_0x12;
    u8 unk_0x13;
    bool32 (*cb_anim)(GObj*);
    bool32 (*cb_coll)(GObj*);
    void (*cb_hurt)(GObj*);
    void (*unk_0x20)(GObj*);
    void (*unk_0x24)(GObj*);
    void (*unk_0x28)(GObj*);
    bool32 (*cb_reflect)(GObj*);
    bool32 (*cb_absorb)(GObj*);

} ItemStatusDesc;

typedef struct Item_Attributes
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
    s32 flags_0x2C : 8U;
    u32 hitbox_count : 2U;
    u32 clang : 1U;
    u32 sfx : 10U;
    u32 flags_0x2E_b567 : 3U;
    u32 flags_0x2F_b0 : 1U;
    u32 flags_0x2F_b1 : 1U;
    u32 flags_0x2F_b2 : 1U;
    u32 flags_0x2F_b3 : 1U;
    u32 flags_0x2F_b4 : 1U;
    u32 flags_0x2F_b5 : 1U;
    u32 flags_0x2F_b6 : 1U;
    u32 flags_0x2F_b7 : 1U;
    u32 knockback_base : 10U;

} Item_Attributes;

typedef struct ItemHitUnk
{
    Vec3f pos;
    Vec3f pos_prev;
    s32 unk_0x18;
    u8 filler_0x1C[0x5C - 0x1C];
    f32 unk_0x5C;

} ItemHitUnk;

typedef struct _ItemHitArray
{
    GObj *victim_gobj;
    u32 flags_b0 : 1;
    u32 flags_b1 : 1;
    u32 flags_b2 : 1;
    u32 flags_b3 : 1;
    u32 flags_b456 : 3;
    u32 timer_rehit : 6;

} ItemHitArray;

typedef struct _Item_Hit
{
    s32 update_state; // 0 = disabled, 1 = new hitbox, 2 and 3 = interpolate/copy current position to previous
    u32 damage; // 0x4
    f32 stale; // Might be damage in float? At least based on Melee?
    u32 element; // 0xC // Placed AFTER offset?
    Vec3f offset[2]; // 0x10 - 0x24   
    f32 size;
    s32 angle;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    u32 unk_0x3C;
    s32 unk_0x40;
    u8 hit_status; // "Tangibility flag? 0x07"
    u16 hit_sfx;
    union
    {
        struct
        {
            u32 flags_0x48_b0 : 1;
            u32 flags_0x48_b1 : 1;
            u32 flags_0x48_b2 : 1;
            u32 flags_0x48_b3 : 1;
            u32 flags_0x48_b4 : 1;
            u32 flags_0x48_b5 : 1;
            u32 flags_0x48_b6 : 1;
            u32 flags_0x48_b7 : 1;
            u32 flags_0x49_b0 : 1;
            u32 attack_id : 6;
            u32 flags_0x49_b7 : 1;
            u16 flags_0x4A;
        };
        u8 flags_0x48;
    };

    union
    {
        struct
        {
            u32 flags_0x4C_b012 : 3;
            u32 flags_0x4C_b3 : 1;
            u32 flags_0x4C_b4 : 1;
            u32 flags_0x4C_b5 : 1;
            u32 flags_0x4C_10bit : 10;
            u16 flags_0x4E;
        };
        u16 flags_0x4C;
    };

    s32 hitbox_count; 
    ItemHitUnk item_hit_unk[2];
    ItemHitArray hit_targets[4];

} Item_Hit;

typedef struct _Monster_Hit
{
    s32 update_state; // 0x0
    u32 damage; // 0x4
    f32 stale; // Might be damage in float? At least based on Melee?
    u32 element; // 0xC // Placed AFTER offset?
    Vec3f offset[2]; // 0x10 - 0x24    
    f32 size;
    s32 unk_0x2C;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    u16 hit_status; // "Tangibility flag? 0x07"
    u16 hit_sfx;
    u32 unk_0x3C;
    s32 unk_0x40;
    u16 flags_0x44 : 7; // Reflectability flag

    u16 flags_0x48_b123456 : 6;
    u16 flags_0x48_b7 : 1;

    u16 flags_0x4A;
    u16 flags_0x4C;
    u16 flags_0x4E;
    s32 hitbox_count; 
    Vec3f pos;
    Vec3f pos_prev;

} Monster_Hit;

typedef struct _Item_Struct
{
    u32 unk_x0;
    GObj *item_gobj;
    GObj *owner_gobj;
    s32 it_kind;
    u8 team;
    u8 port_index;
    u8 unk_0x12;
    s32 unk_0x14;
    s32 lr;
    f32 percent_damage;

    struct
    {
        Vec3f vel;

    } phys_info;

    Coll_Data coll_data;
    Ground_Air ground_or_air;
    Item_Hit item_hit[1];

    u32 unk_0x234;
    u32 unk_0x238;
    s32 unk_0x23C;
    u32 unk_0x240;
    f32 unk_0x244;
    f32 unk_0x248;
    f32 unk_0x24C;
    f32 unk_0x250;
    u32 unk_0x254;
    u32 unk_0x258;
    u32 unk_0x25C;

    u8 x260_flag_b0 : 1;
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
    s32 lifetime; // Frames

    u8 x26C_flag_b0 : 1;
    u8 x26C_flag_b1 : 1;
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
    s32 unk_0x270;
    s16 unk_0x274;
    bool32(*cb_anim)(GObj *);
    bool32(*cb_coll)(GObj *);
    bool32(*cb_give_damage)(GObj *);
    void (*cb_unk_0x284)(GObj *);
    void (*cb_unk_0x288)(GObj *);
    void (*cb_unk_0x28C)(GObj *);
    bool32(*cb_reflect)(GObj *);
    bool32(*cb_absorb)(GObj *);
    bool32(*cb_destroy)(GObj *);
    union
    {
        Charge_Shot_ItemVars charge_shot;
        Spin_Attack_ItemVars spin_attack; // Link's Up Special
        Egg_Throw_ItemVars egg_throw;
        Thunder_ItemVars thunder;
        PK_Thunder_ItemVars pk_thunder_vars;
        PK_Thunder_Trail_ItemVars pk_thunder_trail_vars;

    } item_vars;

    s32 display_state;

} Item_Struct;

#define ItemGetStruct(item_gobj) \
((Item_Struct*)item_gobj->user_data) \

typedef struct Monster_Struct // Pokémon?
{
    void *unk_0x0;
    GObj *monster_gobj;
    GObj *owner_gobj;
    s32 monster_kind;
    s32 unk_0x10;
    u8 team;
    u8 port_index;
    u8 unk_0x16;
    u8 unk_0x17;
    u32 unk_0x18;
    u32 unk_0x1C;
    u32 unk_0x20;
    s32 lr;

    u8 filler_0x28[0x38 - 0x28];

    Coll_Data coll_data;

    u8 filler_0x110[0x8];

    Monster_Hit monster_hit[1];

    u8 filler_0x160[0x374 - 0x17C];

    s32 display_state;

} Monster_Struct;

#define MonsterGetStruct(monster_gobj) \
((Monster_Struct*)monster_gobj->user_data) \

#endif