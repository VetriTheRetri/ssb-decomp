#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include <game/include/ssb_types.h>
#include <game/include/macros.h>
#include <game/include/ultratypes.h>
#include <game/src/sys/hal_input.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/ft/fightervars.h>
#include <game/src/gm/gmmisc.h>
#include <game/src/gm/gmsound.h>

typedef struct Fighter_Struct Fighter_Struct;

typedef struct SpecialHit
{

    s32 hit_type;
    s32 joint_index;
    Vec3f offset;
    Vec3f size;

} SpecialHit;

typedef struct DObjDescContainer
{
    DObjDesc *dobj_desc;
    void *something[3];

} DObjDescContainer;

typedef struct ftItemPickup
{
    Vec2f pickup_offset_light;
    Vec2f pickup_range_light;
    Vec2f pickup_offset_heavy;
    Vec2f pickup_range_heavy;

} ftItemPickup;

typedef struct ftThrownStatus
{
    s32 status1, status2;

} ftThrownStatus;

typedef struct ftThrownStatusArray
{
    ftThrownStatus ft_thrown[2];

} ftThrownStatusArray;

typedef struct ftCommonAttributes
{
    f32 size_mul;
    f32 walkslow_anim_speed;
    f32 walkmiddle_anim_speed;
    f32 walkfast_anim_speed;
    f32 throw_walkslow_anim_speed;
    f32 throw_walkmiddle_anim_speed;
    f32 throw_walkfast_anim_speed; // Cargo Throw
    f32 rebound_anim_length;
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
    s32 jumps_max; // Number of jumps
    f32 weight;
    f32 attack1_followup_frames; // Jab combo connection frames
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
    u16 dead_sfx[2]; // KO voices
    u16 deadup_sfx;  // Star-KO voice
    u16 damage_sfx;
    u16 smash_sfx[3]; // Random Smash SFX
    s16 unk_0xC2;
    ftItemPickup item_pickup;
    s16 unk_0xE4;
    s16 unk_0xE6;
    u16 throw_heavy_sfx;
    u16 unk_0xEA;
    s32 unk_0xEC;
    u8 filler_0xEC[0x100 - 0xF0];
    u32 is_have_attack11 : 1;
    u32 is_have_attack12 : 1;
    u32 catch_flags_b2 : 1;
    u32 catch_flags_b3 : 1;
    u32 catch_flags_b4 : 1;
    u32 catch_flags_b5 : 1;
    u32 catch_flags_b6 : 1;
    u32 catch_flags_b7 : 1;
    u32 catch_flags_b8 : 1;
    u32 catch_flags_b9 : 1;
    u32 is_have_attack120 : 1;
    u32 is_have_attack121 : 1;
    u32 is_have_attack122 : 1;
    u32 is_have_attack123 : 1;
    u32 is_have_attack124 : 1;
    u32 is_have_attack125 : 1;
    u32 is_have_attack126 : 1;
    u32 is_have_attack127 : 1;
    u32 is_have_attack128 : 1;
    u32 is_have_attack129 : 1;
    u32 is_have_catch : 1;   // Whether fighter has a grab
    u32 catch_flags_b21 : 1;
    u32 catch_flags_b22 : 1;
    u32 catch_flags_b23 : 1;
    u32 catch_flags_b24 : 1;
    u32 catch_flags_b25 : 1;
    u32 catch_flags_b26 : 1;
    u32 catch_flags_b27 : 1;
    u32 catch_flags_b28 : 1;
    u32 catch_flags_b29 : 1;
    u32 catch_flags_b30 : 1;
    u32 catch_flags_b31 : 1;
    u8 filler_0x104[0x2B8 - 0x104];
    bool32 cliff_status_ground_air_id[5];
    u8 filler_0x2CC[0x2D4 - 0x2CC];
    DObjDescContainer *dobj_desc_container;
    DObjDesc *dobj_lookup; // WARNING: Not actually DObjDesc* but I don't know what this struct is or what its bounds are; bunch of consecutive floats
    s32 *unk_joint[8];
    s32 joint_index1; // What does this do?
    f32 joint_float1;
    s32 joint_index2;
    f32 joint_float2;
    u8 filler_0x304[0x31C - 0x30C];
    f32 unk_0x31C;
    f32 unk_0x320;
    Vec3f *unk_0x324; // Pointer to some array of vectors, something to do with joints
    s32 unk_0x328;
    s32 unk_0x32C;
    s32 unk_0x330;
    s32 joint_itemhold_heavy;
    ftThrownStatusArray *thrown_status;
    s32 joint_itemhold_light;

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
    ftStatus_Common_Sleep,
    ftStatus_Common_Entry,
    ftStatus_Common_EntryNull,
    ftStatus_Common_RebirthDown,
    ftStatus_Common_RebirthStand,
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
    ftStatus_Common_HammerFall, // Pretty much any aerial Hammer state
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
    ftStatus_Common_ThrownDonkeyUnk, // Related to DK throws?
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
    Ft_Kind_GiantDonkey,
    Ft_Kind_EnumMax

} ftKind;

typedef enum plKind
{
    Pl_Kind_Human,
    Pl_Kind_CPU

} plKind;

typedef enum ftSpecialStatus
{
    ftSpecialStatus_Invincible, // Fighter cannot take damage?
    ftSpecialStatus_Normal, // Fighter can take damage
    ftSpecialStatus_Star, // CPUs run away from fighter; cannot take damage
    ftSpecialStatus_Intangible // Fighter cannot be hit at all

} ftSpecialStatus;

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

typedef struct ftThrowHitDesc
{
    s32 status_id;
    s32 damage;
    s32 angle;
    s32 knockback_scale;
    s32 knockback_weight;
    s32 knockback_base;
    s32 element;

} ftThrowHitDesc;

typedef struct ftThrowReleaseDesc
{
    s32 angle;
    s32 knockback_scale;
    s32 knockback_weight;
    s32 knockback_base;

} ftThrowReleaseDesc;

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

typedef struct Fighter_Hurt
{
    s32 hit_status;
    s32 unk_ftht_0x4;
    DObj *joint;
    s32 unk_ftht_0xC;
    s32 unk_ftht_0x10;
    Vec3f offset;
    Vec3f size;

} Fighter_Hurt;

typedef struct FighterItemThrow
{
    s32 is_smash_throw : 1;
    s32 velocity : 10;
    s32 angle : 11;
    u32 damage : 10;

} FighterItemThrow;

typedef struct FighterItemSwing
{
    u32 anim_speed : 10;

} FighterItemSwing;

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

typedef struct Fighter_Com
{
    u8 behave_current;
    u8 behave_default;
    u8 attack_id;
    u8 behavior_set;
    u8 unk_ftcom_0x4;
    u8 behavior_write; // Override behavior
    u8 unk_ftcom_0x6;
    u8 input_wait; // "Controller command wait timer"
    u8 *p_command;
    void (*cb_com)(GObj *); // "Main behavior routine"
    s32 unk_ftcom_0x10;
    s32 unk_ftcom_0x14;
    s16 unk_ftcom_0x18;
    s16 unk_timer_0x1A;
    s32 unk_timer_0x1C;
    s32 unk_ftcom_0x20;
    u16 target_find_wait;
    u16 target_damage_percent;
    s32 unk_ftcom_0x28;
    s32 unk_ftcom_0x2C;
    GObj *target_gobj;
    s32 unk_ftcom_0x34;
    u8 unk_ftcom_0x38;
    u8 attack11;
    u8 attacks3;
    u8 attacks4;
    u8 attackhi3;
    u8 attackhi4;
    u8 attacklw3;
    u8 attacklw4;
    u8 specialn;
    u8 specialhi;
    u8 speciallw;
    u8 unk_ftcom_0x43; // Also neutral special?
    u8 filler_0x44[0x48 - 0x44];
    u8 ftcom_flags_0x48_b0 : 1;
    u8 ftcom_flags_0x48_b1 : 1;
    u8 ftcom_flags_0x48_b2 : 1;
    u8 ftcom_flags_0x48_b3 : 1;
    u8 ftcom_flags_0x48_b4 : 1;
    u8 ftcom_flags_0x48_b5 : 1;
    u8 ftcom_flags_0x48_b6 : 1;
    u8 ftcom_flags_0x48_b7 : 1;
    u8 ftcom_flags_0x49_b0 : 1;
    u8 ftcom_flags_0x49_b1 : 1;
    u8 ftcom_flags_0x49_b2 : 1;
    u8 ftcom_flags_0x49_b3 : 1;
    u8 ftcom_flags_0x49_b4 : 1;
    u8 ftcom_flags_0x49_b5 : 1;
    u8 ftcom_flags_0x49_b6 : 1;
    u8 ftcom_flags_0x49_b7 : 1;
    u8 ftcom_flags_0x4A_b0 : 1;
    u8 ftcom_flags_0x4A_b1 : 1;
    u8 ftcom_flags_0x4A_b2 : 1;
    u8 ftcom_flags_0x4A_b3 : 1;
    u8 ftcom_flags_0x4A_b4 : 1;
    u8 ftcom_flags_0x4A_b5 : 1;
    u8 ftcom_flags_0x4A_b6 : 1;
    u8 ftcom_flags_0x4A_b7 : 1;
    u8 ftcom_flags_0x4B_b0 : 1;
    u8 ftcom_flags_0x4B_b1 : 1;
    u8 ftcom_flags_0x4B_b2 : 1;
    u8 ftcom_flags_0x4B_b3 : 1;
    u8 ftcom_flags_0x4B_b4 : 1;
    u8 ftcom_flags_0x4B_b5 : 1;
    u8 ftcom_flags_0x4B_b6 : 1;
    u8 ftcom_flags_0x4B_b7 : 1;
    Vec2f cliff_left_pos; // Ledge position
    Vec2f cliff_right_pos;
    s32 target_line_id; // Line ID target is standing on
    Vec2f target_pos;
    f32 target_dist; // FLOAT_MAX when offstage
    Fighter_Struct *target_fp; // I assume this is what the documentation means?
    u8 filler_0x70[0x8C - 0x70];
    f32 unk_ftcom_0x8C;

} Fighter_Com;

struct Fighter_Struct
{
    void *fp_alloc_next;
    GObj *this_fighter;
    ftKind ft_kind;
    u8 team;
    u8 port_id;
    u8 renderstate_curr;  // Hi-Poly = 1, Low-Poly = 2
    u8 renderstate_match; // Hi-Poly = 1, Low-Poly = 2
    u8 costume_id;
    u8 shade_id; // i.e. When multiple instances of the same character costume are in-game
    u8 handicap; // Original note: offset to attack hitbox type in 5x (???)
    u8 cp_level; // CPU level
    s8 stock_count;
    u8 unk_0x15;
    u8 unk_0x16;
    s32 player_number; // Player's number? (Note: NOT player port, e.g. if players 2 and 4 are in a match,
                       // player 2 will be number 1 and player 4 will be number 2; used to match fighters and items?)

    struct status_info // Status = Action State
    {
        s32 status_frame_curr; // 0x1C
        plKind pl_kind;
        s32 status_id;
        s32 anim_id;

    } status_info;

    s32 percent_damage;
    s32 damage_resist; // Resits a specific amount of % damage before breaking, effectively damage-based armor
    s32 shield_health;
    s32 x38_unk;
    s32 x3C_unk;
    u32 hitlag_timer; // Freeze if TRUE
    s32 lr; // Facing direction; -1 = LEFT, 1 = RIGHT

    struct phys_info
    {
        Vec3f vel_air; // Aerial self-induced velocity
        Vec3f vel_damage_air; // Aerial knockback velocity
        Vec3f vel_ground; // Grounded self-induced velocity
        Vec3f vel_damage_ground; // Grounded knockback velocity

    } phys_info;

    Coll_Data coll_data;

    u8 jumps_used;
    Ground_Air ground_or_air;

    f32 attack1_followup_frames;
    s32 attack1_status_id;
    s32 attack1_followup_count;
    s32 cliffcatch_wait;
    s32 time_since_last_z; // Frames since last Z-press, resets to 65536 on action state change
    s32 timer_unk3;
    s32 tornado_wait; // Wait this many frames before fighter can be picked up by the Hyrule Tornado again
    s32 tarucann_wait;// Wait this many frames before fighter can enter Barrel Cannon again
    u8 filler_0x170[0x174 - 0x170];
    s32 unk_0x174;
    s32 unk_0x178;

    union command_vars
    {
        struct flags
        {
            u32 flag0;
            u32 flag1;
            u32 flag2;
            u32 flag3;

        } flags;

        struct item_throw
        {
            bool32 is_throw_item;
            u8 unk1;
            u32 damage : 24;
            u8 unk2;
            u32 vel : 12;
            s32 angle : 12;

        } item_throw;

        // Equivalent to ftcmd flags from Melee?

    } command_vars;

    u32 x18C_flag_b0 : 1;
    u32 x18C_flag_b1 : 1;
    u32 x18C_flag_b2 : 1;
    u32 x18C_flag_b3 : 1;
    u32 x18C_flag_b4 : 1;
    u32 is_reflect : 1;
    s32 lr_reflect : 2;
    u32 is_absorb : 1;
    s32 lr_absorb : 2;
    u32 is_goto_attack100 : 1;
    u32 is_fast_fall : 1;
    u32 x18D_flag_b5 : 1;
    u32 is_check_blastzone : 1;
    u32 is_invisible : 1;

    u32 x18E_flag_b0 : 1;
    u32 x18E_flag_b1 : 1;
    u32 x18E_flag_b2 : 1;
    u32 x18E_flag_b3 : 1;
    u32 x18E_flag_b4 : 1;
    u32 x18E_flag_b5 : 1;
    u32 x18E_flag_b6 : 1;
    u32 x18E_flag_b7 : 1;

    u32 x18F_flag_b0 : 1;
    u32 x18F_flag_b1 : 1;
    u32 x18F_flag_b2 : 1;
    u32 is_statupdate_stop_gfx : 1; // Destroy GFX on action state change if TRUE
    u32 x18F_flag_b4 : 1;
    u32 x18F_flag_b5 : 1;
    u32 x18F_flag_b6 : 1;
    u32 is_hitstun : 1;

    u32 x190_flag_b012 : 3;
    u32 x190_flag_b3 : 1;
    u32 x190_flag_b4 : 1;
    u32 x190_flag_b5 : 1;
    u32 x190_flag_b6 : 1;
    u32 x190_flag_b7 : 1;
    u32 x191_flag_b0 : 1;
    u32 is_ignore_blastzone_top : 1;
    u32 is_damage_resist : 1;
    u32 x191_flag_b3 : 1;
    u32 x191_flag_b4567 : 4;
    u32 x192_flag_b0 : 1;
    u32 x192_flag_b1 : 1;
    u32 x192_flag_b2 : 1;
    u32 x192_flag_b3 : 1;
    u32 x192_flag_b4 : 1;
    u32 x192_flag_b5 : 1;
    u32 x192_flag_b6 : 1;
    u32 x192_flag_b7 : 1;
    u32 x193_flag_b0 : 1;
    u32 x193_flag_b1 : 1;
    u32 x193_flag_b2 : 1;
    u32 x193_flag_b3 : 1;
    u32 x193_flag_b4 : 1;
    u32 x193_flag_b5 : 1;
    u32 x193_flag_b6 : 1;
    u32 x193_flag_b7 : 1;

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
        void *p_controller; // Controller inputs?
        u16 button_mask_a;
        u16 button_mask_b;
        u16 button_mask_z;
        u16 button_mask_l;
        u16 button_hold;
        u16 button_tap;
        u16 button_tap_prev; // Previous button tap?
        Vec2b stick_range;
        Vec2b stick_prev;  // Previous stick range?
        u16 button_mask_com;
        Vec2b stick_com; // CPU stick input?

    } input;

    Fighter_Com fighter_com;

    u8 filler_0x258[0x268 - 0x258];

    u8 tap_stick_x; // Frames control stick has been tapped
    u8 tap_stick_y; // Frames control stick has been tapped
    u8 hold_stick_x; // Frames control stick has been tapped or held
    u8 hold_stick_y; // Frames control stick has been tapped or held

    s32 breakout_wait; // Frames until fighter breaks out of shield break / sleep / Cargo Throw
    s8 breakout_lr; // Whether victim is mashing left or right
    s8 breakout_ud; // Whether victim is mashing up or down

    u8 filler_0x272[0x276 - 0x272];

    s16 unk_0x276;
    GObj *throw_gobj; // GObj pointer of player throwing this fighter?
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
        struct
        {
            gmAttackFlags flags_hi;
            gmAttackFlags flags_lw;
        };

        u32 unk_0x28C_word;
    };
    gmAttackFlags unk_0x290;

    Fighter_Hit fighter_hit[4];

    u8 filler_0x290[0x5B0 - 0x5A4];

    s32 star_invincible_time;
    s32 special_status;
    s32 hit_status;

    Fighter_Hurt fighter_hurt[11];

    f32 unk_ft_0x7A4;
    s32 unk_ft_0x7A8;
    s32 unk_ft_0x7AC;

    s32 unk_0x7B0;
    f32 attack_knockback;
    u16 attack_hit_count; // Number of times this fighter successfully dealt damage 
    s32 attack_damage;
    f32 attack_damage_stale; // Actually 2x staled damage?
    s32 shield_damage;
    u8 filler_0x7B4[0x7D0 - 0x7CC];
    s32 lr_shield;
    s32 unk_ft_0x7D4;
    s32 unk_ft_0x7D8;
    s32 unk_ft_0x7DC;
    f32 damage_knockback;
    f32 knockback_resist_passive;// Passive armor, always active (?)
    f32 knockback_resist_status; // Resist this many units of knockback, effectively knockback-based armor
    f32 damage_knockback_again;
    s32 damage_taken_recent;
    s32 damage_angle;
    s32 damage_element;
    s32 lr_damage;
    s32 damage_index;
    s32 unk_0x804;
    s32 damage_player_number;
    s32 damage_port_id; // Port index of damaging fighter
    s32 unk_0x810;
    s32 unk_ft_0x814;
    s32 unk_0x818;
    f32 damage_mul;

    s32 unk_ft_0x820;
    s32 unk_ft_0x824;
    s32 unk_ft_0x828;

    f32 publicity_knockback; // Knockback value used for crowd reactions

    GObj *search_gobj;  // GObj this fighter found when searching for grabbable fighters?
    f32 search_gobj_dist;
    void (*cb_catch)(GObj*); // Run this callback on grabbing attacker
    void (*cb_capture)(GObj*); // Run this callback on grabbed victim
    GObj *catch_gobj;   // GObj this fighter has caught
    GObj *capture_gobj; // GObj this fighter is captured by
    ftThrowHitDesc *fighter_throw; // Pointer to throw description
    GObj *item_hold;
    SpecialHit *special_hit;
    Vec3f entry_pos;

    u8 filler_0x844[0x864 - 0x860];

    f32 fighter_cam_zoom_range;

    ftUnkFrameStruct unk_frame[4];

    DObj *joint[36];

    u8 filler_0x980[0x9C4 - 0x978];

    ftData *ft_data;
    ftCommonAttributes *attributes;

    s32 x9CC;
    s32 x9D0;

    void (*cb_anim)(GObj*);
    void (*cb_accessory)(GObj*);
    void (*cb_interrupt)(GObj*);
    void (*cb_physics)(GObj*);
    void (*cb_coll)(GObj*);
    void (*cb_update_ik)(GObj*);
    void (*cb_take_damage)(GObj*);
    void (*unk_0x9F0)(GObj*);
    void (*cb_hit_shield)(GObj*);
    void (*cb_give_damage)(GObj*);
    void (*cb_update_gfx)(GObj*);
    void (*unk_0xA00)(GObj*);
    void (*cb_hitlag_start)(GObj*);
    void (*cb_hitlag_end)(GObj*);
    void (*cb_status)(GObj*);

    u8 filler_0xA10[0xA28 - 0xA10];

    Color_Overlay color_anim;

    s32 unk_ft_0xA6C;
    s32 unk_ft_0xA70;
    f32 light_angle1;
    f32 light_angle2;
    s32 unk_ft_0xA7C;
    s32 unk_ft_0xA80;
    s32 unk_ft_0xA84;
    u32 unk_ft_0xA88_b0 : 1;

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

    union fighter_vars
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

    union status_vars
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

};

#define FighterGetStruct(fighter_gobj) \
((Fighter_Struct*)fighter_gobj->user_data) \

#define AttributesGetStruct(fp) \
((ftCommonAttributes*)fp->attributes) \

#define FighterGetJoint(fp, id) \
((DObj*)fp->joint[id]) \

#define FighterCalcLandingLag(anim_length, target_length) \
((f32)anim_length / target_length) \

// Fighter Functions

void ftStatus_Update(GObj *fighter_gobj, s32 status_id, f32 frame_begin, f32 anim_rate, u32 flags); // Action State Change
void func_ovl3_801438F0(GObj *fighter_gobj, f32 drift, bool32 unk1, bool32 is_fall_accelerate, bool32 is_goto_landing, f32 landing_lag, bool32 is_allow_interrupt); // FallSpecial Action State
void func_ovl2_800DDE84(GObj*, void(*cb_coll)(GObj*)); // Grounded Collision check (stop at ledge?)
void func_ovl2_800DE80C(GObj*, void(*cb_coll)(GObj*)); // Aerial Collision check (ledge grab?)
void ftCollision_SetGround(Fighter_Struct*); // ???
void func_ovl2_800D8EB8(Fighter_Struct*); // ???
void func_ovl2_800DEEC8(Fighter_Struct*); // ???
void ftAnim_Update(GObj*); // ???

// Macro to check if a move has been interrupted by any standard action
#define ftStatus_CheckInterruptAll(fighter_gobj)   \
(                                                  \
    (func_ovl3_80151098(fighter_gobj) != FALSE) || \
    (func_ovl3_80151160(fighter_gobj) != FALSE) || \
    (func_ovl3_801511E0(fighter_gobj) != FALSE) || \
    (func_ovl3_80149CE0(fighter_gobj) != FALSE) || \
    (func_ovl3_80150470(fighter_gobj) != FALSE) || \
    (func_ovl3_8015070C(fighter_gobj) != FALSE) || \
    (func_ovl3_80150884(fighter_gobj) != FALSE) || \
    (func_ovl3_8014F8C0(fighter_gobj) != FALSE) || \
    (func_ovl3_8014FB1C(fighter_gobj) != FALSE) || \
    (func_ovl3_8014FD70(fighter_gobj) != FALSE) || \
    (func_ovl3_8014EC78(fighter_gobj) != FALSE) || \
    (func_ovl3_80148D0C(fighter_gobj) != FALSE) || \
    (func_ovl3_8014E764(fighter_gobj) != FALSE) || \
    (func_ovl3_8013F4D0(fighter_gobj) != FALSE) || \
    (func_ovl3_8013ED64(fighter_gobj) != FALSE) || \
    (func_ovl3_80141EA4(fighter_gobj) != FALSE) || \
    (func_ovl3_80142258(fighter_gobj) != FALSE) || \
    (func_ovl3_8014310C(fighter_gobj) != FALSE) || \
    (func_ovl3_8013EA04(fighter_gobj) != FALSE) || \
    (func_ovl3_8013E648(fighter_gobj) != FALSE)    \
)                                                  \

#endif