#ifndef _ITEM_H_
#define _ITEM_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/it/itemvars.h>

typedef enum It_Kind
{
    It_Kind_Link_Bomb = 0x15

} It_Kind;

typedef struct _Item_Hit
{
    s32 timer_rehit; // 0x0
    u32 damage; // 0x4
    f32 stale; // Might be damage in float? At least based on Melee?
    u32 element; // 0xC // Placed AFTER offset?
    Vec3f offset; // 0x10 - 0x18    
    Vec3f unk_0x1C;
    f32 size;
    s32 unk_0x2C;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    u32 unk_0x3C;
    u32 unk_0x40;
    u16 hit_status; // "Tangibility flag? 0x07"
    u16 hit_fgm;
    u32 is_reflect; // Reflectability flag
    u32 update_status; // 0 = disabled, 1 = enabled, 2 and 3 related to position update?
    Vec3f pos;
    Vec3f pos_prev;

} Item_Hit;

typedef struct _Item_Struct
{
    u32 unk_x0;
    GObj *item_gobj;
    GObj *owner_gobj;
    s32 it_kind;
    s32 team;
    s32 unk_0x14;
    s32 lr; // lr is unconfirmed; thought to be port owner,
    // but I've seen this compared against "facing direction" at 0x18 which would be silly
    s32 unk_x1C;

    struct
    {
        Vec3f vel;

    } phys_info;

    Coll_Data coll_data;
    Ground_Air ground_or_air;
    Item_Hit item_hit[1];

    u8 filler_0x16C[0x260 - 0x168];

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
    s32 unk_0x274;
    bool32(*cb_anim)(GObj*);
    bool32(*cb_coll)(GObj*);
    void (*cb_hurt)(GObj*);
    void (*cb_unk_0x284)(GObj*);
    void (*cb_unk_0x288)(GObj*);
    void (*cb_unk_0x28C)(GObj*);
    bool32(*cb_reflect)(GObj*);
    bool32(*cb_absorb)(GObj*);
    bool32(*cb_destroy)(GObj*);

    union
    {
        Charge_Shot_ItemVars charge_shot;
        Spin_Attack_ItemVars spin_attack; // Spin Attack uses items!?
        Egg_Throw_ItemVars egg_throw;
        Thunder_ItemVars thunder;
        PK_Thunder_ItemVars pk_thunder_vars;
        PK_Thunder_Trail_ItemVars pk_thunder_trail_vars;

    } item_vars;

} Item_Struct;

#define ItemGetStruct(item_gobj) \
((Item_Struct*)item_gobj->user_data) \

#endif