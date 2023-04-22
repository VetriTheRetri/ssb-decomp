#ifndef _FIGHTERVARS_H_
#define _FIGHTERVARS_H_

#include <game/src/ft/chara/ftmario/ftmario_statusvars.h>
#include <game/src/ft/chara/ftfox/ftfox_statusvars.h>
#include <game/src/ft/chara/ftdonkey/ftdonkey_statusvars.h>
#include <game/src/ft/chara/ftsamus/ftsamus_statusvars.h>
#include <game/src/ft/chara/ftlink/ftlink_statusvars.h>
#include <game/src/ft/chara/ftyoshi/ftyoshi_statusvars.h>
#include <game/src/ft/chara/ftcaptain/ftcaptain_statusvars.h>
#include <game/src/ft/chara/ftkirby/ftkirby_statusvars.h>
#include <game/src/ft/chara/ftpikachu/ftpikachu_statusvars.h>
#include <game/src/ft/chara/ftpurin/ftpurin_statusvars.h>
#include <game/src/ft/chara/ftness/ftness_statusvars.h>
#include <game/src/ft/chara/ftmasterhand/ftmasterhand_statusvars.h>

#define FTCOMMON_DEAD_REBIRTH_WAIT 45
#define FTCOMMON_DEADUP_REBIRTH_WAIT 180
#define FTCOMMON_DEADUPFALL_VEL_Z -83.333336F

#define FTCOMMON_REBIRTH_INVINCIBLE_FRAMES 120                  // Invincibility frames; setting this to 0 makes invincibility last forever (?)
#define FTCOMMON_REBIRTH_HALO_LOWER_WAIT 90
#define FTCOMMON_REBIRTH_HALO_DESPAWN_WAIT 390
#define FTCOMMON_REBIRTH_HALO_UNK_WAIT 45
#define FTCOMMON_REBIRTH_HALO_STAND_WAIT 75

#define FTCOMMON_SLEEP_STOCK_STEAL_WAIT 30

#define FTCOMMON_ENTRY_WAIT 120

#define FTCOMMON_WALKFAST_STICK_RANGE_MIN 62                    // Minimum stick range required for fast walk speed
#define FTCOMMON_WALKMIDDLE_STICK_RANGE_MIN 26                  // Minimum stick range required for medium walk speed

#define FTCOMMON_TURN_STICK_RANGE_MIN (-20)

#define FTCOMMON_DASH_BUFFER_FRAMES_MAX 3                       // Dash will register if stick range is greater than or equal to FTCOMMON_DASH_STICK_RANGE_MIN within this window of time
#define FTCOMMON_DASH_STICK_RANGE_MIN 56
#define FTCOMMON_DASH_DECELERATE_BEGIN 7.0F

#define FTCOMMON_RUN_STICK_RANGE_MIN 50

#define FTCOMMON_TURNRUN_STICK_RANGE_MIN (-30)

#define FTCOMMON_KNEEBEND_INPUT_TYPE_NONE 0
#define FTCOMMON_KNEEBEND_INPUT_TYPE_STICK 1
#define FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON 2
#define FTCOMMON_KNEEBEND_BUFFER_FRAMES_MAX 3                   // Jumpsquat will register if stick range is greater than FTCOMMON_KNEEBEND_STICK_RANGE_MIN within this window of time
#define FTCOMMON_KNEEBEND_JUMP_F_OR_B_RANGE (-10)               // Stick X range to determine whether to usee JumpF or JumpB action state
#define FTCOMMON_KNEEBEND_RUN_STICK_RANGE_MIN 44                // Used for jumpsquat interrupt from run?
#define FTCOMMON_KNEEBEND_STICK_RANGE_MIN 53                    // Minimum stick Y range required for stick jump
#define FTCOMMON_KNEEBEND_BUTTON_SHORT_FORCE 9.0F               // Jump force of C-button short jump
#define FTCOMMON_KNEEBEND_BUTTON_LONG_FORCE 17.0F               // Jump force of C-button long jump
#define FTCOMMON_KNEEBEND_BUTTON_SHORT_MIN 36.0F                // Minimum short jump height possible with C-button input
#define FTCOMMON_KNEEBEND_BUTTON_LONG_MIN 63.0F                 // Minimum long jump height possible with C-button input
#define FTCOMMON_KNEEBEND_BUTTON_HEIGHT_CLAMP 77.0F             // Maximum jump height possible with C-button input
#define FTCOMMON_KNEEBEND_SHORT_HOP_FRAMES 3.0F                 // Universal short hop window, unlike Melee where the user must simply not be holding their jump input on the last frame of jumpsquat

#define FTCOMMON_JUMPAERIAL_INPUT_TYPE_NONE 0
#define FTCOMMON_JUMPAERIAL_INPUT_TYPE_STICK 1
#define FTCOMMON_JUMPAERIAL_INPUT_TYPE_BUTTON 2
#define FTCOMMON_JUMPAERIAL_F_OR_B_RANGE (-10)
#define FTCOMMON_JUMPAERIAL_STICK_RANGE_MIN 53
#define FTCOMMON_JUMPAERIAL_TURN_STICK_RANGE_MIN (-30)
#define FTCOMMON_JUMPAERIAL_TURN_FRAMES 12
#define FTCOMMON_JUMPAERIAL_TURN_INVERT_LR_WAIT 6               // Invert facing direction on this frame of the direction turn process          
#define FTCOMMON_JUMPAERIAL_TURN_ROTATE_STEP (-0.2617994F)      // Model Y-rotation step for characters who can turn around during their double jump

#define FTCOMMON_DAMAGE_SMASH_DI_BUFFER_FRAMES_MAX 4
#define FTCOMMON_DAMAGE_SMASH_DI_RANGE_MIN 53
#define FTCOMMON_DAMAGE_CATCH_RELEASE_THRESHOLD 6               // If a grabbed fighter takes more than this much damage in one hit, they're released
#define FTCOMMON_DAMAGE_FIGHTER_FLYROLL_DAMAGE_MIN 100
#define FTCOMMON_DAMAGE_GFX_WAIT_LOW 0
#define FTCOMMON_DAMAGE_GFX_WAIT_MID_LOW 8
#define FTCOMMON_DAMAGE_GFX_WAIT_MID 5
#define FTCOMMON_DAMAGE_GFX_WAIT_MID_HIGH 3
#define FTCOMMON_DAMAGE_GFX_WAIT_HIGH 2
#define FTCOMMON_DAMAGE_GFX_WAIT_DEFAULT 1
#define FTCOMMON_DAMAGE_GFX_KNOCKBACK_LOW 120.0F
#define FTCOMMON_DAMAGE_GFX_KNOCKBACK_MID_LOW 150.0F
#define FTCOMMON_DAMAGE_GFX_KNOCKBACK_MID 200.0F
#define FTCOMMON_DAMAGE_GFX_KNOCKBACK_MID_HIGH 300.0F
#define FTCOMMON_DAMAGE_GFX_KNOCKBACK_HIGH 600.0F
#define FTCOMMON_DAMAGE_SMASH_DI_RANGE_MUL 2.1F
#define FTCOMMON_DAMAGE_SAKURAI_KNOCKBACK_LOW 32.0F
#define FTCOMMON_DAMAGE_SAKURAI_ANGLE_LOW_GR 0.0F
#define FTCOMMON_DAMAGE_SAKURAI_ANGLE_HIGH_GR 0.741764903069F
#define FTCOMMON_DAMAGE_SAKURAI_ANGLE_HIGH_GD 42.5F
#define FTCOMMON_DAMAGE_SAKURAI_ANGLE_DEFAULT_AR 0.75049156F
#define FTCOMMON_DAMAGE_STATUS_KNOCKBACK_LOW 12.0F              // Knockback < this value                                                      -> DamageX1
#define FTCOMMON_DAMAGE_STATUS_KNOCKBACK_MID 24.0F              // Knockback < this value && knockback >= FTCOMMON_DAMAGE_STATUS_KNOCKBACK_LOW -> DamageX2
#define FTCOMMON_DAMAGE_STATUS_KNOCKBACK_HIGH 32.0F             // Knockback < this value && knockback >= FTCOMMON_DAMAGE_STATUS_KNOCKBACK_MID -> DamageX3
#define FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_ANGLE_LOW 1.308997F
#define FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_ANGLE_HIGH 2.0071287F
#define FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_KNOCKBACK_MUL 0.8F    // Multiply crowd reaction knockback by this value if angle > ANGLE_LOW && angle < ANGLE_HIGH
#define FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_KNOCKBACK_UNK 160.0F
#define FTCOMMON_DAMAGE_FIGHTER_FLYTOP_ANGLE_LOW 1.2217306F
#define FTCOMMON_DAMAGE_FIGHTER_FLYTOP_ANGLE_HIGH 1.9198622F
#define FTCOMMON_DAMAGE_FIGHTER_FLYROLL_RANDOM_CHANCE 0.5F
#define FTCOMMON_DAMAGE_FIGHTER_REACT_GASP_KNOCKBACK_MIN 80.0F  // Minimum knockback required for a fighter to play their damage voice effect when getting hit

#define FTCOMMON_PASS_STICK_RANGE_MIN (-53)                     // Minimum stick Y range required for platform drop to register
#define FTCOMMON_PASS_BUFFER_FRAMES_MAX 4

#define FTCOMMON_SQUAT_STICK_RANGE_MIN (-53)
#define FTCOMMON_SQUAT_BUFFER_FRAMES_MAX 4
#define FTCOMMON_SQUAT_PASS_WAIT 3                              

#define FTCOMMON_DOKAN_STICK_RANGE_MIN (-53)                    // Minimum stick Y range required for pipe enter to register
#define FTCOMMON_DOKAN_BUFFER_FRAMES_MAX 4
#define FTCOMMON_DOKAN_UNK_WAIT 20
#define FTCOMMON_DOKAN_TURN_STOP_WAIT_DEFAULT 8
#define FTCOMMON_DOKAN_TURN_STEP 0.19634955F
#define FTCOMMON_DOKAN_POS_ADJUST 25.0F
#define FTCOMMON_DOKAN_DETECT_WIDTH 200.0F
#define FTCOMMON_DOKAN_POS_ADJUST_WAIT 30.0F
#define FTCOMMON_DOKAN_EXIT_WAIT 30.0F

#define FTCOMMON_OTTOTTO_WALK_DIST_X_MIN 60.0F                  // ???
#define FTCOMMON_OTTOTTO_WALK_STICK_RANGE_MIN 60                // Minimum stick range required for walk interrupt???

#define FTCOMMON_LANDING_INTERRUPT_BEGIN 4.0F                   // If is_allow_interrupt == TRUE then landing can be interrupted once this many frames of the animation have played
#define FTCOMMON_LANDING_HEAVY_ANIM_SPEED 0.5F                  // Animation playback rate of landing after fastfall
#define FTCOMMON_LANDING_LIGHT_ANIM_SPEED 1.0F                  // Animation playback rate of normal landing

#define FTCOMMON_FALLSPECIAL_PASS_STICK_RANGE_MIN (-44)         // Minimum stick Y range required to pass through drop-through platforms while in FallSpecial
#define FTCOMMON_FALLSPECIAL_SKIP_LANDING_VEL_Y_MAX (-20.0F)    // Maximum Y velocity allowed for no impact land

#define FTCOMMON_TORNADO_RELEASE_WAIT 60.0F                     
#define FTCOMMON_TORNADO_PICKUP_WAIT 60                         // Frames before tornado can pick up individual fighter again

#define FTCOMMON_TARUCANN_RELEASE_WAIT 180                      // Maximum number of frames fighter can spend inside the Barrel Cannon on Kongo Jungle before automatically firing
#define FTCOMMON_TARUCANN_SHOOT_WAIT 10                         // Frames before fighter is released once the Barrel Cannon is in its firing state?
#define FTCOMMON_TARUCANN_PICKUP_WAIT 16                        // Frames before Barrel Cannon can be used again

#define FTCOMMON_DOWNWAIT_STAND_WAIT 180                        // Frames until fighter automatically stands up from knockdown
#define FTCOMMON_DOWNWAIT_STAND_STICK_RANGE_MIN 20              // Minimum stick Y range required to stand up

#define FTCOMMON_DOWNBOUNCE_ATTACK_BUFFER 60

#define FTCOMMON_DOWN_FORWARD_BACK_RANGE_MIN 20                 // Minimum stick X range required for missed tech roll

#define FTCOMMON_PASSIVE_BUFFER_FRAMES_MAX 20                   // Tech buffer frames
#define FTCOMMON_PASSIVE_F_OR_B_RANGE 20 

#define FTCOMMON_CLIFF_CATCH_WAIT 30                            // Frames to wait before fighter can grab ledge again
#define FTCOMMON_CLIFF_DAMAGE_HIGH 100                          // If fighter's damage is greater than or equal to this, use Slow action states and hang time
#define FTCOMMON_CLIFF_FALL_WAIT_DAMAGE_HIGH 480
#define FTCOMMON_CLIFF_FALL_WAIT_DAMAGE_LOW 1080
#define FTCOMMON_CLIFF_MOTION_STICK_RANGE_MIN 20                // Minimum stick range required to preform ledge actions (and drop from ledge)

#define FTCOMMON_GET_MASK_LIGHT (1 << 0)
#define FTCOMMON_GET_MASK_HEAVY (1 << 1)

#define FTCOMMON_LIFT_TURN_FRAMES 8
#define FTCOMMON_LIFT_TURN_STEP (-0.3926991F)

#define FTCOMMON_LIGHTTHROW_STICK_RANGE_XY_MIN 20
#define FTCOMMON_LIGHTTHROW4_STICK_RANGE_X_MIN 56
#define FTCOMMON_LIGHTTHROW4_STICK_RANGE_Y_MIN 53
#define FTCOMMON_LIGHTTHROW4_F_OR_B_BUFFER_FRAMES_MAX 8
#define FTCOMMON_LIGHTTHROW4_HI_OR_LW_BUFFER_FRAMES_MAX 4
#define FTCOMMON_LIGHTTHROW_HI_OR_LW_ANGLE 0.87266463F

#define FTCOMMON_HEAVYTHROW_STICK_RANGE_XY_MIN 20
#define FTCOMMON_HEAVYTHROW4_STICK_RANGE_X_MIN 56
#define FTCOMMON_HEAVYTHROW4_STICK_RANGE_Y_MIN 53
#define FTCOMMON_HEAVYTHROW4_F_OR_B_BUFFER_FRAMES_MAX 8
#define FTCOMMON_HEAVYTHROW4_HI_OR_LW_BUFFER_FRAMES_MAX 4
#define FTCOMMON_HEAVYTHROW_HI_OR_LW_ANGLE 0.87266463F

#define FTCOMMON_HARISENSWING_SCALE_RESET_WAIT 2
#define FTCOMMON_HARISENSWING_SCALE_HIT 1.5F

#define FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_X 0.0F
#define FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_Y 60.0F
#define FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_Z 180.0F

#define FTCOMMON_FIREFLOWERSHOOT_GFX_SPAWN_INT 12
#define FTCOMMON_FIREFLOWERSHOOT_RELEASE_LAG 20
#define FTCOMMON_FIREFLOWERSHOOT_AMMO_INDEX_MAX 8
#define FTCOMMON_FIREFLOWERSHOOT_AMMO_INDEX_LOOP 5
#define FTCOMMON_FIREFLOWERSHOOT_AMMO_SPAWN_OFF_X 60.0F
#define FTCOMMON_FIREFLOWERSHOOT_AMMO_SPAWN_OFF_Y 100.0F
#define FTCOMMON_FIREFLOWERSHOOT_AMMO_SPAWN_OFF_Z 0.0F

#define FTCOMMON_HAMMER_TIME_MAX 720

typedef struct ftCommon_Filler
{
    u8 filler[0xB4C - 0xB18];

} ftCommon_Filler;

typedef struct ftCommon_Dead_StatusVars
{
    s32 rebirth_wait;
    Vec3f pos;

} ftCommon_Dead_StatusVars;

typedef struct ftCommon_Rebirth_StatusVars
{
    Vec3f halo_offset;
    Vec3f pos;
    s32 halo_despawn_wait;
    s32 halo_number;
    s32 halo_lower_wait;

} ftCommon_Rebirth_StatusVars;

typedef struct ftStatus_Rebirth_CustomVars
{
    s32 unk_rebirth_0x0;
    Vec3f halo_offset;
    s32 lr_rebirth;
    s32 unk_rebirth_0x14;
    s32 unk_rebirth_0x18;
    s32 unk_rebirth_0x1C;
    s32 unk_rebirth_0x20;
    s32 unk_rebirth_0x24;
    s32 unk_rebirth_0x28;
    s32 unk_rebirth_0x2C;
    s32 unk_rebirth_0x30;
    s32 unk_rebirth_0x34;
    s32 unk_rebirth_0x38;
    s32 unk_rebirth_0x3C;

} ftStatus_Rebirth_CustomVars;

typedef struct ftCommon_Sleep_StatusVars
{
    s32 stock_steal_wait;

} ftCommon_Sleep_StatusVars;

typedef struct ftCommon_Entry_StatusVars
{
    s32 entry_wait;
    s32 lr_entry;
    s32 ground_line_id;
    bool32 is_rotate;

} ftCommon_Entry_StatusVars;

typedef struct ftCommon_Turn_StatusVars
{
    bool32 is_allow_turn_direction; // Cannot turn around at all if disabled + horizontal controls are inverted?
    bool32 is_disable_interrupts; // Sort of weird, still allows three interrupts even if false, one being shield and the other being jumpsquat, I don't know the third one
    u16 button_mask;
    s32 lr_dash;
    s32 lr_turn;
    s32 unk_0x14;

} ftCommon_Turn_StatusVars;

typedef struct ftCommon_KneeBend_StatusVars
{
    f32 jump_force;
    f32 anim_frame;
    s32 input_source;
    bool32 is_short_hop;

} ftCommon_KneeBend_StatusVars;

typedef struct ftCommon_JumpAerial_StatusVars
{
    f32 drift;
    f32 vel_x;
    s32 turn_frames;

} ftCommon_JumpAerial_StatusVars;

typedef struct ftCommon_Damage_StatusVars
{
    s32 hitstun_timer;
    s32 dust_gfx_int;
    f32 publicity_knockback;
    u16 coll_mask;
    u8 filler_0xE[0x2C - 0xE];
    s32 status_id;
    bool32 is_limit_knockback;

} ftCommon_Damage_StatusVars;

typedef struct ftCommon_Squat_StatusVars
{
    bool32 is_allow_pass;
    s32 pass_wait;
    s32 unk_0x8;

} ftCommon_Squat_StatusVars;

typedef struct ftCommon_Dokan_StatusVars
{
    s32 ground_line_id;
    s32 wall_line_id;
    Vec3f pos_current;
    Vec3f pos_target;
    s32 pos_adjust_wait;
    s32 set_unk_wait;
    s32 turn_stop_wait;

} ftCommon_Dokan_StatusVars;

typedef struct ftCommon_Landing_StatusVars
{
    bool32 is_allow_interrupt;

} ftCommon_Landing_StatusVars;

typedef struct ftCommon_FallSpecial_StatusVars
{
    f32 drift;
    bool32 is_allow_pass;
    bool32 is_goto_landing;
    f32 landing_lag;
    bool32 is_allow_interrupt;
    bool32 is_fall_accelerate;

} ftCommon_FallSpecial_StatusVars;

typedef struct ftCommon_Tornado_StatusVars
{
    s32 release_wait;
    GObj *tornado_gobj;

} ftCommon_Tornado_StatusVars;

typedef struct ftCommon_TaruCann_StatusVars
{
    s32 release_wait;
    s32 shoot_wait;
    GObj *tarucann_gobj;

} ftCommon_TaruCann_StatusVars;

typedef struct ftCommon_DownWait_StatusVars
{
    s32 stand_wait;

} ftCommon_DownWait_StatusVars;

typedef struct ftCommon_DownBounce_StatusVars
{
    s32 attack_buffer;

} ftCommon_DownBounce_StatusVars;

typedef struct ftCommon_Rebound_StatusVars
{
    f32 anim_speed;
    f32 rebound_timer;

} ftCommon_Rebound_StatusVars;

typedef struct ftCommon_CliffWait_StatusVars
{
    s32 status_id;
    s32 fall_wait;

} ftCommon_CliffWait_StatusVars;

typedef struct ftCommon_CliffMotion_StatusVars
{
    s32 status_id;
    s32 cliff_id;

} ftCommon_CliffMotion_StatusVars;

typedef struct ftCommon_Lift_StatusVars 
{
    s32 turn_frames;

} ftCommon_Lift_StatusVars;

typedef struct ftCommon_ItemThrow_StatusVars
{
    s32 turn_rotate_step;
    s32 turn_frames;
    s32 turn_invert_lr_wait;
    f32 throw_vel;
    s32 throw_angle;
    f32 throw_damage;
    Vec2f unk;
    s32 get_heavy_wait;

} ftCommon_ItemThrow_StatusVars;

typedef struct ftCommon_ItemSwing_StatusVars
{
    s32 harisen_scale_reset_wait;

} ftCommon_ItemSwing_StatusVars;

typedef struct ftCommon_FireFlower_StatusVars
{
    s32 flame_vel_index;
    s32 ammo_sub;
    s32 gfx_spawn_int;
    s32 ammo_fire_count;
    bool32 is_release;
    s32 release_lag;

} ftCommon_FireFlower_StatusVars;

typedef struct ftCommon_YoshiEgg_StatusVars
{
    u32 unk_0x0;
    u16 unk_0x4;

} ftCommon_YoshiEgg_StatusVars;

typedef struct ftCommon_CaptureCaptain_StatusVars
{
    u16 capture_flag;   // Collection of bit flags, only seen 0x4 and 0x2 used

} ftCommon_CaptureCaptain_StatusVars;

typedef struct ftCommon_CaptureKirby_StatusVars
{
    u16 unk_0x0;
    u16 unk_0x2;
    u16 unk_0x4;

} ftCommon_CaptureKirby_StatusVars;

typedef union ftCommon_StatusVars
{
    ftCommon_Dead_StatusVars dead;
    ftCommon_Rebirth_StatusVars rebirth;
    ftCommon_Sleep_StatusVars sleep;
    ftCommon_Entry_StatusVars entry;
    ftCommon_Turn_StatusVars turn;
    ftCommon_KneeBend_StatusVars kneebend;
    ftCommon_JumpAerial_StatusVars jumpaerial;
    ftCommon_Damage_StatusVars damage;
    ftCommon_Squat_StatusVars squat;
    ftCommon_Dokan_StatusVars dokan;
    ftCommon_Landing_StatusVars landing;
    ftCommon_FallSpecial_StatusVars fallspecial;
    ftCommon_Tornado_StatusVars tornado;
    ftCommon_TaruCann_StatusVars tarucann;
    ftCommon_DownWait_StatusVars downwait;
    ftCommon_DownBounce_StatusVars downbounce;
    ftCommon_Rebound_StatusVars rebound;
    ftCommon_CliffWait_StatusVars cliffwait;
    ftCommon_CliffMotion_StatusVars cliffmotion;
    ftCommon_Lift_StatusVars lift;
    ftCommon_ItemThrow_StatusVars itemthrow;
    ftCommon_ItemSwing_StatusVars itemswing;
    ftCommon_FireFlower_StatusVars fireflower;
    ftCommon_YoshiEgg_StatusVars yoshiegg;
    ftCommon_CaptureCaptain_StatusVars capturecaptain;
    ftCommon_CaptureKirby_StatusVars capturekirby;

} ftCommon_StatusVars;

#endif