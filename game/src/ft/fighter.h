#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include <game/include/ssb_types.h>
#include <game/include/macros.h>
#include <game/include/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/ft/ftstatusvars.h>
#include <game/src/gm/gmmisc.h>
#include <game/src/gm/gmsound.h>

typedef struct SpecialHit
{

    s32 hit_type;
    s32 joint_index;
    Vec3f unk_0x8;
    Vec3f unk_0x14;

} SpecialHit;

typedef struct JObjContainer
{

    JObjDesc *renderstate[4];

} JObjContainer;

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
    ObjectColl object_coll;
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
    u16 throw_heavy_sfx;
    u16 unk_0xEA;
    u8 filler_0xEC[0x2D4 - 0xEC];
    JObjContainer *renderstate;
    u8 filler_0x2D8[0x324 - 0x2D8];
    s32 unk_0x324;
    s32 filler_0x328[0x334 - 0x328];
    s32 joint_throw_heavy;
    s32 unk_0x338;
    s32 joint_throw_light;

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
    ftStatus_Common_DeadLeftRight,
    ftStatus_Common_DeadUpStar,
    ftStatus_Common_DeadUpFall,
    ftStatus_Common_DeadUpFallWait,
    ftStatus_Common_Entry,
    ftStatus_Common_Unk1,
    ftStatus_Common_RebirthStand1,
    ftStatus_Common_RebirthStand2,
    ftStatus_Common_RebirthWait,
    ftStatus_Common_Wait,
    ftStatus_Common_WalkSlow,
    ftStatus_Common_WalkMiddle,
    ftStatus_Common_WalkFast,
    ftStatus_Common_WalkEnd,
    ftStatus_Common_Dash,
    ftStatus_Common_Run,
    ftStatus_Common_RunBrake,
    ftStatus_Common_Turn,
    ftStatus_Common_TurnRun,
    ftStatus_Common_KneeBend,
    ftStatus_Common_GuardKneeBend,
    ftStatus_Common_JumpF,
    ftStatus_Common_JumpB,
    ftStatus_Common_JumpAerialF,
    ftStatus_Common_JumpAerialB,
    ftStatus_Common_Fall,
    ftStatus_Common_FallAerial,
    ftStatus_Common_Squat,
    ftStatus_Common_SquatWait,
    ftStatus_Common_SquatRv,
    ftStatus_Common_LandingLight,
    ftStatus_Common_LandingHeavy,
    ftStatus_Common_Pass,
    ftStatus_Common_GuardPass,
    ftStatus_Common_OttottoWait,
    ftStatus_Common_Ottotto,
    ftStatus_Common_DamageHi1,
    ftStatus_Common_DamageHi2,
    ftStatus_Common_DamageHi3,
    ftStatus_Common_DamageN1,
    ftStatus_Common_DamageN2,
    ftStatus_Common_DamageN3,
    ftStatus_Common_DamageLw1,
    ftStatus_Common_DamageLw2,
    ftStatus_Common_DamageLw3,
    ftStatus_Common_DamageAir1,
    ftStatus_Common_DamageAir2,
    ftStatus_Common_DamageAir3,
    ftStatus_Common_DamageElec1,
    ftStatus_Common_DamageElec2,
    ftStatus_Common_DamageFlyHi,
    ftStatus_Common_DamageFlyN,
    ftStatus_Common_DamageFlyLw,
    ftStatus_Common_DamageFlyTop,
    ftStatus_Common_DamageFlyRoll,
    ftStatus_Common_WallDamage,
    ftStatus_Common_DamageFall,
    ftStatus_Common_FallSpecial,
    ftStatus_Common_LandingFallSpecial,
    ftStatus_Common_Tornado,
    ftStatus_Common_TaruCann, // DK Barrel
    ftStatus_Common_DokanStart, // Enter pipe
    ftStatus_Common_DokanWait, // In pipe
    ftStatus_Common_DokanEnd, // Exit pipe
    ftStatus_Common_DokanWalk, // Exit horizontal pipe
    ftStatus_Common_StopCeil, // Bump head into ceiling
    ftStatus_Common_DownBounceD,
    ftStatus_Common_DownBounceU,
    ftStatus_Common_DownWaitD,
    ftStatus_Common_DownWaitU,
    ftStatus_Common_DownStandD,
    ftStatus_Common_DownStandU,
    ftStatus_Common_PassiveStandF,
    ftStatus_Common_PassiveStandB,
    ftStatus_Common_DownForwardD,
    ftStatus_Common_DownForwardU,
    ftStatus_Common_DownBackD,
    ftStatus_Common_DownBackU,
    ftStatus_Common_DownAttackD,
    ftStatus_Common_DownAttackU,
    ftStatus_Common_Passive,
    ftStatus_Common_ReboundWait,
    ftStatus_Common_Rebound,
    ftStatus_Common_CliffCatch,
    ftStatus_Common_CliffWait,
    ftStatus_Common_CliffQuick,
    ftStatus_Common_CliffClimbQuick1,
    ftStatus_Common_CliffClimbQuick2,
    ftStatus_Common_CliffSlow,
    ftStatus_Common_CliffClimbSlow1,
    ftStatus_Common_CliffClimbSlow2,
    ftStatus_Common_CliffAttackQuick1,
    ftStatus_Common_CliffAttackQuick2,
    ftStatus_Common_CliffAttackSlow1,
    ftStatus_Common_CliffAttackSlow2,
    ftStatus_Common_CliffEscapeQuick1,
    ftStatus_Common_CliffEscapeQuick2,
    ftStatus_Common_CliffEscapeSlow1,
    ftStatus_Common_CliffEscapeSlow2,
    ftStatus_Common_LightGet,
    ftStatus_Common_HeavyGet,
    ftStatus_Common_LiftWait,
    ftStatus_Common_LiftTurn,
    ftStatus_Common_LightThrowDrop,
    ftStatus_Common_LightThrowDash,
    ftStatus_Common_LightThrowF,
    ftStatus_Common_LightThrowB,
    ftStatus_Common_LightThrowHi,
    ftStatus_Common_LightThrowLw,
    ftStatus_Common_LightThrowF4,
    ftStatus_Common_LightThrowB4,
    ftStatus_Common_LightThrowHi4,
    ftStatus_Common_LightThrowLw4,
    ftStatus_Common_LightThrowAirF,
    ftStatus_Common_LightThrowAirB,
    ftStatus_Common_LightThrowAirHi,
    ftStatus_Common_LightThrowAirLw,
    ftStatus_Common_LightThrowAirF4,
    ftStatus_Common_LightThrowAirB4,
    ftStatus_Common_LightThrowAirHi4,
    ftStatus_Common_LightThrowAirLw4,
    ftStatus_Common_HeavyThrowF,
    ftStatus_Common_HeavyThrowB,
    ftStatus_Common_HeavyThrowF4,
    ftStatus_Common_HeavyThrowB4,
    ftStatus_Common_SwordSwing1,
    ftStatus_Common_SwordSwing3,
    ftStatus_Common_SwordSwing4,
    ftStatus_Common_SwordSwingDash,
    ftStatus_Common_BatSwing1,
    ftStatus_Common_BatSwing3,
    ftStatus_Common_BatSwing4,
    ftStatus_Common_BatSwingDash,
    ftStatus_Common_HarisenSwing1,
    ftStatus_Common_HarisenSwing3,
    ftStatus_Common_HarisenSwing4,
    ftStatus_Common_HarisenSwingDash,
    ftStatus_Common_StarRodSwing1,
    ftStatus_Common_StarRodSwing3,
    ftStatus_Common_StarRodSwing4,
    ftStatus_Common_StarRodSwingDash,
    ftStatus_Common_LGunShoot,
    ftStatus_Common_LGunShootAir,
    ftStatus_Common_FireFlowerShoot,
    ftStatus_Common_FireFlowerShootAir,
    ftStatus_Common_HammerWait,
    ftStatus_Common_HammerWalk,
    ftStatus_Common_HammerTurn,
    ftStatus_Common_HammerKneeBend,
    ftStatus_Common_HammerFall,
    ftStatus_Common_HammerLanding,
    ftStatus_Common_GuardOn,
    ftStatus_Common_Guard,
    ftStatus_Common_GuardOff,
    ftStatus_Common_GuardSetOff,
    ftStatus_Common_EscapeF,
    ftStatus_Common_EscapeB,
    ftStatus_Common_ShieldBreakFly,
    ftStatus_Common_ShieldBreakFall,
    ftStatus_Common_ShieldBreakDownD,
    ftStatus_Common_ShieldBreakDownU,
    ftStatus_Common_ShieldBreakStandD,
    ftStatus_Common_ShieldBreakStandU,
    ftStatus_Common_FuraFura,
    ftStatus_Common_FuraSleep,
    ftStatus_Common_Catch,
    ftStatus_Common_CatchPull,
    ftStatus_Common_CatchWait,
    ftStatus_Common_ThrowF,
    ftStatus_Common_ThrowB,
    ftStatus_Common_CapturePulled,
    ftStatus_Common_CaptureWait,
    ftStatus_Common_CaptureKirby,
    ftStatus_Common_CaptureWaitKirby,
    ftStatus_Common_ThrownKirbyStar,
    ftStatus_Common_ThrownCopyStar,
    ftStatus_Common_CaptureYoshi,
    ftStatus_Common_YoshiEgg,
    ftStatus_Common_CaptureCaptain,
    ftStatus_Common_Unk2,
    ftStatus_Common_ThrownDonkeyF,
    ftStatus_Common_ThrownMarioB,
    ftStatus_Common_ThrownFoxF,
    ftStatus_Common_Shouldered,
    ftStatus_Common_ThrownF,
    ftStatus_Common_ThrownB,
    ftStatus_Common_ThrownUnk,
    ftStatus_Common_ThrownFoxB,
    ftStatus_Common_Appeal,
    ftStatus_Common_Attack11,
    ftStatus_Common_Attack12,
    ftStatus_Common_AttackDash,
    ftStatus_Common_AttackS3Hi,
    ftStatus_Common_AttackS3HiS,
    ftStatus_Common_AttackS3,
    ftStatus_Common_AttackS3LwS,
    ftStatus_Common_AttackS3Lw,
    ftStatus_Common_AttackHi3HiS, // Forward-angled up tilt???
    ftStatus_Common_AttackHi3,
    ftStatus_Common_AttackHi3LwS, // Unknown
    ftStatus_Common_AttackLw3,
    ftStatus_Common_AttackS4Hi,
    ftStatus_Common_AttackS4HiS,
    ftStatus_Common_AttackS4,
    ftStatus_Common_AttackS4LwS,
    ftStatus_Common_AttackS4Lw,
    ftStatus_Common_AttackHi4,
    ftStatus_Common_AttackLw4,
    ftStatus_Common_AttackAirN,
    ftStatus_Common_AttackAirF,
    ftStatus_Common_AttackAirB,
    ftStatus_Common_AttackAirHi,
    ftStatus_Common_AttackAirLw,
    ftStatus_Common_LandingAirN,
    ftStatus_Common_LandingAirF,
    ftStatus_Common_LandingAirB,
    ftStatus_Common_LandingAirHi,
    ftStatus_Common_LandingAirLw,
    ftStatus_Common_LandingAirX,
    ftStatus_Common_SpecialStart // Start of special move table

} ftCommonAction;

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

typedef struct FighterHitVictimFlags
{
    u32 flags_b0 : 1;
    u32 flags_b1 : 1;
    u32 flags_b2 : 1;
    u32 flags_b3 : 1;
    u32 flags_b456 : 3;
    u32 timer_rehit : 6;

} FighterHitVictimFlags;

typedef struct FighterHitArray
{
    GObj *victim_gobj;
    FighterHitVictimFlags victim_flags;

} FighterHitArray;

typedef struct _Fighter_Hit
{
    s32 update_state;
    u32 unk_0x4;
    u32 unk_0x8;
    s32 damage;
    s32 element;
    s32 unk_0x14;
    s32 unk_0x18;
    s32 unk_0x1C;
    s32 unk_0x20;
    s32 unk_0x24;
    s32 angle;
    s32 knockback_scale;
    s32 knockback_weight;
    s32 knockback_base;
    s32 unk_0x38;
    u8 flags_0x3C_b0 : 1;
    u8 flags_0x3C_b1 : 1;
    u8 flags_0x3C_b2 : 1;
    u8 flags_0x3C_b3 : 1;
    u8 flags_0x3C_b4 : 1;
    u8 flags_0x3C_b5 : 1;
    u8 flags_0x3C_b6 : 1;
    u8 is_hit_air : 1;
    u8 is_hit_ground : 1;
    u8 flags_0x3D_b1 : 1;
    u8 flags_0x3D_b2 : 1;
    u8 flags_0x3D_b3 : 1;
    u8 flags_0x3D_b4 : 1;
    u8 flags_0x3D_b5 : 1;
    u8 flags_0x3D_b6 : 1;
    u8 flags_0x3D_b7 : 1;
    u8 flags_0x3E_b0 : 1;
    u8 flags_0x3E_b1 : 1;
    u8 flags_0x3E_b2 : 1;
    u8 flags_0x3E_b3 : 1;
    u8 flags_0x3E_b4 : 1;
    u8 flags_0x3E_b5 : 1;
    u8 flags_0x3E_b6 : 1;
    u8 flags_0x3E_b7 : 1;
    u8 flags_0x3F_b0 : 1;
    u8 flags_0x3F_b1 : 1;
    u8 flags_0x3F_b2 : 1;
    u8 flags_0x3F_b3 : 1;
    u8 flags_0x3F_b4 : 1;
    u8 flags_0x3F_b5 : 1;
    u8 flags_0x3F_b6 : 1;
    u8 flags_0x3F_b7 : 1;
    u8 filler_0x40[0x5C - 0x40];
    FighterHitArray hit_targets[4];
    u8 filler[0xC4 - 0x7C];

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
    s32 player_number; // Player's number? (Note: NOT player port, e.g. if players 2 and 4 are in a match,
                       // player 2 will be number 1 and player 4 will be number 2; used to match fighters and items?)

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
    GObj *unk_0x278;
    s32 unk_0x27C;
    u8 unk_0x280;
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

    s32 hit_status;
    
    u8 filler_0x58C[0x7B0 - 0x5BC];

    s32 unk_0x7B0;

    u8 filler_0x7B4[0x7E8 - 0x7B4];

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
    GObj *catch_gobj;   // GObj this fighter has caught
    GObj *capture_gobj; // GObj this fighter is captured by
    s32 unk_0x848;
    GObj *article_hold;
    SpecialHit *special_hit;

    u8 filler_0x844[0x864 - 0x854];

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