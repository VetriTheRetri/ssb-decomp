#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include <game/include/ssb_types.h>
#include <game/include/macros.h>
#include <game/include/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/ft/ftstatusvars.h>
#include <game/src/gm/gmmisc.h>

#define LEFT -1
#define CENTER 0
#define RIGHT 1

typedef struct SpecialHit
{

    s32 hit_type;
    s32 joint_index;
    Vec3f unk_0x8;
    Vec3f unk_0x14;

} SpecialHit;

typedef struct RenderStateDesc
{
    s32 x0;
    s32 x4;
    Vec3f translate;
    Vec3f rotate;
    Vec3f scale;

} RenderStateDesc;

typedef struct RenderStateContainer
{

    RenderStateDesc *renderstate[4];

} RenderStateContainer;

typedef struct ftCommonAttributes
{
    f32 size_mul;
    f32 walkslow_anim_speed;
    f32 walkmiddle_anim_speed;
    f32 walkfast_anim_speed;
    f32 throw_walkslow_anim_speed;
    f32 throw_walkmiddle_anim_speed;
    f32 throw_walkfast_anim_speed; // Cargo Throw
    f32 unk_0x1C;
    f32 walk_speed_mul;
    f32 traction;
    f32 dash_speed;
    f32 dash_decelerate;
    f32 run_speed;
    f32 kneebend_length; // Jump squat frames
    f32 jump_vel_x;
    f32 jump_height_mul;
    f32 jump_height_base;
    f32 aerial_jump_vel_x;
    f32 aerial_jump_height;
    f32 aerial_acceleration;
    f32 aerial_speed_max_x;
    f32 aerial_friction;
    f32 gravity;
    f32 fall_speed_max;
    f32 fast_fall_speed;
    u32 jumps_max; // Number of jumps
    f32 weight;
    f32 attack11_follow_window; // Jab combo connection frames
    f32 dash_to_run; // Frames before dash transitions to run?
    f32 shield_size;
    f32 shield_break_vel_y;
    f32 shadow_size;
    Vec2f jostle_box;
    f32 unk_0x88;
    f32 vs_pause_zoom;
    f32 cam_offset_y;
    f32 cam_zoom;
    f32 cam_zoom_default;
    ObjectColl coll_box;
    Vec2f cliff_catch; // Ledge grab box
    s16 dead_sfx[2]; // KO voices
    s16 star_sfx;  // Star-KO voice
    s16 damage_sfx;
    s16 smash_sfx[3]; // Random Smash SFX
    s16 unk_0xC2;
    f32 halo_size_mul; // Platform size?
    f32 unk_0xC8;
    f32 unk_0xCC;
    f32 unk_0xD0;
    f32 unk_0xD4;
    f32 unk_0xD8;
    f32 unk_0xDC;
    f32 unk_0xE0;
    s16 unk_0xE4;
    s16 unk_0xE6;
    s32 unk_0xE8;
    u8 filler_0xEC[0x2D4 - 0xEC];
    RenderStateContainer *renderstate;
    u8 filler_0x2D8[0x324 - 0x2D8];
    s32 unk_0x324;

} ftCommonAttributes;

typedef struct ftDataUnkContainer3
{
    s32 x0;

} ftDataUnkContainer3;

typedef struct ftDataUnkContainer2
{
    s32 unk_0x0;
    s32 unk_0x4;
    s32 unk_0x8;

} ftDataUnkContainer2;

typedef struct ftDataUnkContainer
{
    ftDataUnkContainer2 unk_0x0[1];

} ftDataUnkContainer;

typedef struct ftData
{
    u8 filler_0x0[0x2C];
    ftDataUnkContainer3 *unk_0x2C;
    ftDataUnkContainer3 *unk_0x30;
    s32 unk_0x34;
    s32 unk_0x38;
    u8 filler_0x3C[0x64 - 0x3C];
    ftDataUnkContainer *unk_0x64;
    ftDataUnkContainer *unk_0x68;

} ftData;

typedef enum ftCommonAction
{
    ftStatus_Common_DeadDown,
    ftStatus_Common_DeadSide,
    ftStatus_Common_DeadUpStar,
    ftStatus_Common_DeadUpFall,
    ftStatus_Common_LightThrowF = 0x6E,
    ftStatus_Common_LightThrowAirF = 0x76,

} ftCommonAction;

typedef enum ftHitStatus
{
    ftHitStatus_Normal,
    ftHitStatus_Unk,
    ftHitStatus_Invincible,
    ftHitStatus_Intangible
        
} ftHitStatus;

typedef enum ftKind
{

    Ft_Kind_Mario,
    Ft_Kind_Fox,
    Ft_Kind_Donkey,
    Ft_Kind_Samus,
    Ft_Kind_Luigi,
    Ft_Kind_Link,
    Ft_Kind_Yoshi,
    Ft_Kind_Captain,
    Ft_Kind_Kirby,
    Ft_Kind_Pikachu,
    Ft_Kind_Purin,
    Ft_Kind_Ness,
    Ft_Kind_MasterHand,
    Ft_Kind_MetalMario,
    Ft_Kind_PolyMario,
    Ft_Kind_PolyFox,
    Ft_Kind_PolyDonkey,
    Ft_Kind_PolySamus,
    Ft_Kind_PolyLuigi,
    Ft_Kind_PolyLink,
    Ft_Kind_PolyYoshi,
    Ft_Kind_PolyCaptain,
    Ft_Kind_PolyKirby,
    Ft_Kind_PolyPikachu,
    Ft_Kind_PolyPurin,
    Ft_Kind_PolyNess,
    Ft_Kind_GiantDonkey

} ftKind;

typedef enum plKind
{
    Pl_Kind_Human,
    Pl_Kind_CPU

} plKind;

typedef enum ftHitUpdateState
{
    ftHit_UpdateState_Disable,
    ftHit_UpdateState_New,
    ftHit_UpdateState_2,
    ftHit_UpdateState_3

} ftHitUpdateState;

typedef struct _Fighter_Hit
{
    s32 update_state;
    u32 unk_0x4;
    u32 unk_0x8;
    s32 damage;
    u8 filler[0xC4 - 0x10];

} Fighter_Hit;

typedef struct ftUnkFrameStruct
{
    f32 unk_0x0;
    s32 unk_0x4;
    void *unk_0x8;
    void *unk_0xC;
    f32 unk_0x10;
    void *unk_0x14;
    void *unk_0x18;
    void *unk_0x1C;

} ftUnkFrameStruct;

typedef struct _Fighter_Struct
{
    GObj *next_fighter;
    GObj *this_fighter;
    ftKind ft_kind;
    u8 team;
    u8 player_id;
    u8 renderstate_curr;  // Hi-Poly = 1, Low-Poly = 2
    u8 renderstate_match; // Hi-Poly = 1, Low-Poly = 2
    u8 costume_id;
    u8 shade_id; // i.e. When multiple instances of the same character costume are in-game
    u8 offset_hit_type; // Original note: offset to attack hitbox type in 5x (???)
    u8 cp_level; // CPU level
    s8 unk_0x14;
    u8 unk_0x15;
    u8 unk_0x16;
    s32 unk_0x18; // Based on port

    struct // Status = Action State
    {
        s32 status_frame_curr; // 0x1C
        plKind pl_kind;
        s32 status_id;
        s32 anim_id;

    } status_info;

    s32 percent_dmg_total;
    s32 armor; // Used as HP in Kirby's Stone
    s32 x34_unk;
    s32 x38_unk;
    s32 x3C_unk;
    u32 hitlag_timer; // Freeze if TRUE
    s32 lr; // Facing direction; -1 = LEFT, 1 = RIGHT

    struct
    {
        Vec3f vel_normal; // Knockback / external velocity?
        Vec3f vel_air;
        Vec3f vel_ground; // Might be one float?
        Vec3f unk_vec_0x6C;

    } phys_info;

    Coll_Data coll_data;
    u8 jumps_used;

    Ground_Air ground_or_air;

    f32 unk_0x150;
    u8 filler_0x154[0x160 - 0x154];
    s32 timer_unk; // Unknown timer
    u8 filler_0x164[0x174 - 0x164];
    s32 unk_0x174;
    s32 unk_0x178;

    struct
    {

        u32 flag0;
        u32 flag1;
        u32 flag2;
        u32 flag3;

        // Equivalent to ftcmd flags from Melee?

    } cmd_flags;

    u8 x18C_flag_b0 : 1;
    u8 x18C_flag_b1 : 1;
    u8 x18C_flag_b2 : 1;
    u8 x18C_flag_b3 : 1;
    u8 x18C_flag_b4 : 1;
    u8 is_reflect : 1;
    s8 lr_reflect : 2;
    u8 is_absorb : 1;
    s8 lr_absorb : 2;
    u8 x18D_flag_b3 : 1;
    u8 x18D_flag_b4 : 1;
    u8 x18D_flag_b5 : 1;
    u8 x18D_flag_b6 : 1;
    u8 x18D_flag_b7 : 1;

    u8 x18E_flag_b0 : 1;
    u8 x18E_flag_b1 : 1;
    u8 x18E_flag_b2 : 1;
    u8 x18E_flag_b3 : 1;
    u8 x18E_flag_b4 : 1;
    u8 x18E_flag_b5 : 1;
    u8 x18E_flag_b6 : 1;
    u8 x18E_flag_b7 : 1;

    u8 x18F_flag_b0 : 1;
    u8 x18F_flag_b1 : 1;
    u8 x18F_flag_b2 : 1;
    u8 x18F_flag_b3 : 1;
    u8 x18F_flag_b4 : 1;
    u8 x18F_flag_b5 : 1;
    u8 x18F_flag_b6 : 1;
    u8 x18F_flag_b7 : 1;

    union
    {
        struct
        {
            u8 x190_flag_b012 : 3;
            u8 x190_flag_b3 : 1;
            u8 x190_flag_b4 : 1;
            u8 x190_flag_b5 : 1;
            u8 x190_flag_b6 : 1;
            u8 x190_flag_b7 : 1;
            u8 x191_flag_b0 : 1;
            u8 x191_flag_b1 : 1;
            u8 x191_flag_b2 : 1;
            u8 x191_flag_b3 : 1;
            u8 x191_flag_b4567 : 4;
        };
        struct
        {
            s8 x190_sbyte;
            s8 x191_sbyte;
        };
        struct
        {
            u16 x190_halfword;
        };
    };

    u8 x192_flag_b0 : 1;
    u8 x192_flag_b1 : 1;
    u8 x192_flag_b2 : 1;
    u8 x192_flag_b3 : 1;
    u8 x192_flag_b4 : 1;
    u8 x192_flag_b5 : 1;
    u8 x192_flag_b6 : 1;
    u8 x192_flag_b7 : 1;

    u8 x193_flag_b0 : 1;
    u8 x193_flag_b1 : 1;
    u8 x193_flag_b2 : 1;
    u8 x193_flag_b3 : 1;
    u8 x193_flag_b4 : 1;
    u8 x193_flag_b5 : 1;
    u8 x193_flag_b6 : 1;
    u8 x193_flag_b7 : 1;

    u32 unk_0x194;
    union
    {
        struct
        {
            u32 x198_flag_b0 : 1;
            u32 x198_flag_b1 : 1;
            u32 x198_flag_b2 : 1;
            u32 x198_flag_b3 : 1;
            u32 x198_flag_b4 : 1;
            u32 x198_flag_b5 : 1;
            u32 x198_flag_b6 : 1;
            u32 x198_flag_b7 : 1;
            u32 x199_flag_b0 : 1;
            u32 x199_flag_b1 : 1;
            u32 x199_flag_b2 : 1;
            u32 x199_flag_b3 : 1;
            u32 x199_flag_b4 : 1;
            u32 x199_flag_b5 : 1;
            u32 x199_flag_b6 : 1;
            u32 x199_flag_b7 : 1;
            u32 x19A_flag_b0 : 1;
            u32 x19A_flag_b1 : 1;
            u32 x19A_flag_b2 : 1;
            u32 x19A_flag_b3 : 1;
            u32 x19A_flag_b4 : 1;
            u32 x19A_flag_b5 : 1;
            u32 x19A_flag_b6 : 1;
            u32 x19A_flag_b7 : 1;
            u32 x19B_flag_b0 : 1;
            u32 x19B_flag_b1 : 1;
            u32 x19B_flag_b2 : 1;
            u32 x19B_flag_b3 : 1;
            u32 x19B_flag_b4 : 1;
            u32 x19B_flag_b5 : 1;
            u32 x19B_flag_b6 : 1;
            u32 x19B_flag_b7 : 1;
        };

        u32 unk_0x198;
    };

    u32 unk_0x19C;
    u32 unk_0x1A0;
    f32 float_unk;
    u32 unk_0x1A8;
    u32 unk_0x1AC;

    struct _input
    {
        void *ptr_inputs; // Controller inputs?
        u16 button_mask_a;
        u16 button_mask_b;
        u16 button_mask_z;
        u16 button_mask_l;
        u16 button_hold;
        u16 button_press;
        u16 button_unk;
        Vec2b stick_range; // Might be range?
        Vec2b padding;

    } input;

    struct _cpu
    {
        u16 cpu_button_press;
        Vec2h cpu_stick_range;

    } cpu;

    u8 filler_unk_0x1D0[0x268 - 0x1CE];

    u8 buffer_stick_x;
    u8 buffer_stick_y;
    u8 buffer_button_b;

    u8 filler_0x26B[0x276 - 0x26B];

    s16 unk_0x276;
    s32 unk_0x278;
    s32 unk_0x27C;
    s32 unk_0x280;
    s32 unk_0x284;
    s32 attack_id;

    union
    {
        struct
        {
            u8 unk_0x28C_byte;
            u8 unk_0x28E_byte_4bit : 4;
            u8 unk_0x28E_byte;
        };
        struct
        {
            u16 unk_0x28C_half_fill;
            u16 unk_0x28E_half_3bit : 3;
            u8 unk_0x28E_bit_0x10 : 1;
            u8 unk_0x28E_bit_0x8 : 1;
        };
        struct
        {
            u16 unk_0x28C_halfword;
            u16 unk_0x28E_halfword;
        };

        u32 unk_0x28C_word;
    };
    u16 unk_0x290;

    Fighter_Hit fighter_hit[4];

    u8 filler_0x290[0x5B8 - 0x5A4];

    s32 hitstatus;

    u8 filler_0x58C[0x7E8 - 0x5BC];

    f32 unk_0x7E8;
    f32 unk_0x7EC;
    s32 unk_0x7F0;
    s32 unk_0x7F4;
    s32 unk_0x7F8;
    s32 unk_0x7FC;
    s32 unk_0x800;
    s32 unk_0x804;
    s32 unk_0x808;
    s32 unk_0x80C;
    s32 unk_0x810;
    s32 unk_0x814;
    s32 unk_0x818;
    f32 unk_0x81C;

    u8 filler_0x820[0x830 - 0x820];

    GObj *unk_gobj;
    u8 filler_0x834[0xC];
    GObj *catch_gobj;

    u8 filler_0x844[0x864 - 0x844];

    f32 unk_0x864;

    ftUnkFrameStruct unk_frame[4];

    JObj *joint[36];

    u8 filler_0x980[0x9C4 - 0x978];

    ftData *ft_data;
    ftCommonAttributes *attributes;

    s32 x9CC;
    s32 x9D0;

    void (*cb_anim)(GObj *);
    void (*cb_accessory)(GObj *);
    void (*cb_interrupt)(GObj *);
    void (*cb_physics)(GObj *);
    void (*cb_coll)(GObj *);
    void (*cb_update_ik)(GObj *);
    void (*cb_take_damage)(GObj *);
    void (*unk_0x9F0)(GObj *);
    void (*cb_hit_shield)(GObj *);
    void (*cb_give_damage)(GObj *);
    void (*cb_update_gfx)(GObj *);
    void (*unk_0xA00)(GObj *);
    void (*cb_hitlag_start)(GObj *);
    void (*cb_hitlag_end)(GObj *);
    void (*cb_status)(GObj *);

    u8 filler_0xA10[0xA64 - 0xA10];

    s32 unk_0xA64;

    u8 filler_0xA68[0xA8C - 0xA68];

    u8 unk_0xA8C;
    u8 unk_0xA8D;
    u8 unk_0xA8E;
    u8 unk_0xA8F;
    u32 unk_0xA90;
    u32 unk_0xA94;
    u32 unk_0xA98;
    s8 unk_0xA9C;
    s8 unk_0xA9D;
    s8 unk_0xA9E;
    s8 unk_0xA9F;

    u8 filler_0xAA0[0xADC - 0xAA0];

    union
    {
        ftMario_FighterVars mario;
        ftDonkey_FighterVars donkey;
        ftSamus_FighterVars samus;
        ftLink_FighterVars link;
        ftCaptain_FighterVars captain;
        ftKirby_FighterVars kirby;
        ftPikachu_FighterVars pikachu;
        ftPurin_FighterVars purin;
        ftNess_FighterVars ness;
        ftMasterHand_FighterVars masterhand;

    } fighter_vars;

    s32 hammer_time;

    union
    {
        ftCommon_StatusVars common;
        ftMario_StatusVars mario;
        ftFox_StatusVars fox;
        ftDonkey_StatusVars donkey;
        ftSamus_StatusVars samus;
        ftLink_StatusVars link;
        ftYoshi_StatusVars yoshi;
        ftCaptain_StatusVars captain;
        ftKirby_StatusVars kirby;
        ftPikachu_StatusVars pikachu;
        ftNess_StatusVars ness;
        ftMasterHand_StatusVars masterhand;

    } status_vars;

    s32 display_state;

} Fighter_Struct;

#define FighterGetStruct(fighter_gobj) \
((Fighter_Struct*)fighter_gobj->user_data) \

#define JObjGetStruct(gobj) \
((JObj*)gobj->obj) \

#define AttributesGetStruct(fp) \
((ftCommonAttributes*)fp->attributes) \

#define FighterGetJoint(fp, id) \
((JObj*)fp->joint[id]) \

#define FighterCalcLandingLag(anim_length, target_length) \
((f32)anim_length / target_length) \

// Fighter Functions

void func_ovl2_800E6F24(GObj *fighter_gobj, s32 status_id, f32 frame_begin, f32 anim_rate, u32 flags); // Action State Change
void func_ovl3_801438F0(GObj *fighter_gobj, f32 aerial_drift, bool32 unk1, bool32 is_custom_gravity, bool32 unk2, f32 landing_lag, bool32 can_interrupt); // FallSpecial Action State
void func_ovl2_800DDE84(GObj*, void(*cb_coll)(GObj*)); // Grounded Collision check (stop at ledge?)
void func_ovl2_800DE80C(GObj*, void(*cb_coll)(GObj*)); // Aerial Collision check (ledge grab?)
void func_ovl2_800DEE98(Fighter_Struct*); // ???
void func_ovl2_800D8EB8(Fighter_Struct*); // ???
void func_ovl2_800DEEC8(Fighter_Struct*); // ???
void func_ovl2_800E0830(GObj*); // ???

#endif