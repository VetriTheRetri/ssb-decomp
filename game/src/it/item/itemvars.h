#ifndef _ITEMVARS_H_
#define _ITEMVARS_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define ITBLASTER_VEL_X 160.0F

#define ITCHARGESHOT_GFX_SIZE_DIV 30.0F
#define ITCHARGESHOT_ROTATE_SPEED 0.31415927F

#define ITSAMUSBOMB_EXPLODE_LIFETIME 6
#define ITSAMUSBOMB_EXPLODE_RADIUS 180.0F

#define ITSAMUSBOMB_WAIT_LIFETIME 100                           // Countdown of Bomb until it explodes
#define ITSAMUSBOMB_WAIT_VEL_Y 10.0F                            // Initial velocity of Bomb
#define ITSAMUSBOMB_WAIT_ROTATE_SPEED_AIR 0.34906587F           // Bomb spins at this rate while airborne
#define ITSAMUSBOMB_WAIT_ROTATE_SPEED_GROUND 0.17453294F        // Bomb spins at this rate while grounded
#define ITSAMUSBOMB_WAIT_COLLIDE_MOD_VEL 0.9F                   // Modify velocity when colliding with an obstruction?
#define ITSAMUSBOMB_WAIT_GRAVITY 1.0F                           // Bomb's gravity
#define ITSAMUSBOMB_WAIT_T_VEL 50.0F                            // Bomb's terminal velocity
#define ITSAMUSBOMB_WAIT_BLINK_SLOW 40                          // The light in the center of the bomb blinks at its "slow" rate while lifetime is greater than this value
#define ITSAMUSBOMB_WAIT_BLINK_MID 20                           // The light in the center of the bomb blinks at its "mid" rate while lifetime is greater than this value
#define ITSAMUSBOMB_WAIT_BLINK_TIMER_SLOW 8                     // Switch out Bomb's texture animation frame when this timer reaches 0
#define ITSAMUSBOMB_WAIT_BLINK_TIMER_MID 5                      // Switch out Bomb's texture animation frame when this timer reaches 0
#define ITSAMUSBOMB_WAIT_BLINK_TIMER_FAST 3                     // Switch out Bomb's texture animation frame when this timer reaches 0

#define ITPIKACHUJOLT_LIFETIME 100
#define ITPIKACHUJOLT_VEL 55.0F
#define ITPIKACHUJOLT_GRAVITY 0.0F
#define ITPIKACHUJOLT_T_VEL 50.0F
#define ITPIKACHUJOLT_ROTATE_ANGLE_MAX 1.7453293F               
#define ITPIKACHUJOLT_ANIM_PUSH_FRAME 7.5F                      // Frame on which Thunder Jolt gets pushed ahead to simulate movement?
#define ITPIKACHUJOLT_COLL_GROUND 0                             // ID of Thunder Jolt collision type
#define ITPIKACHUJOLT_COLL_LWALL 1                              // ID of Thunder Jolt collision type
#define ITPIKACHUJOLT_COLL_CEIL 2                               // ID of Thunder Jolt collision type
#define ITPIKACHUJOLT_COLL_RWALL 3                              // ID of Thunder Jolt collision type

#define ITPIKACHUTHUNDER_TEXTURE_COUNT 4                        // Number of textures Thunder contains
#define ITPIKACHUTHUNDER_SPAWN_LIFETIME 40                      // Duration of inital Thunder projectile?
#define ITPIKACHUTHUNDER_CHAIN_LIFETIME 10                      // Duration of subsequent Thunder segments?
#define ITPIKACHUTHUNDER_EXPIRE 6                               // Thunder can no longer damage opponents once its lifetime has dipped below this number

#define ITPKFIRE_LIFETIME 20
#define ITPKFIRE_VEL_MUL 160.0F

#define ITPKTHUNDER_LIFETIME 160
#define ITPKTHUNDER_SPAWN_TRAIL_FRAME (ITPKTHUNDER_LIFETIME - 2)// Subtracted from PK Thunder's maximum lifetime to determine when to begin spawning trails
#define ITPKTHUNDER_TURN_STICK_THRESHOLD 45                     // Minimum stick range required to steer PK Thunder
#define ITPKTHUNDER_ANGLE_STEP 0.10471976F                      // If there is a difference between PK Thunder and the control stick's current angle, step this amount
#define ITPKTHUNDER_ANGLE_DIV 7.5F                              // Divide angle difference then add to current PK Thunder angle if less than quarter pi
#define ITPKTHUNDER_VEL 60.0F
#define ITPKTHUNDER_REFLECT_POS_Y_ADD 250.0F                    // Added to Y position when PK Thunder is reflected
#define ITPKTHUNDER_TRAIL_COUNT 5
#define ITPKTHUNDER_TEXTURE_COUNT 4

#define ITFINALCUTTER_LIFETIME 20
#define ITFINALCUTTER_VEL 100.0F

#define ITEGGTHROW_LIFETIME 50
#define ITEGGTHROW_EXPLODE_LIFETIME 10
#define ITEGGTHROW_EXPLODE_SIZE 340.0F
#define ITEGGTHROW_TRAJECTORY_DIV 65.0F
#define ITEGGTHROW_TRAJECTORY_SUB_RIGHT 1.8675023F              // Default: 107 degrees; subtract angle from this if egg's facing direction is RIGHT
#define ITEGGTHROW_TRAJECTORY_SUB_LEFT 1.27409040928F           // Default: 73 degrees; subtract angle from this if egg's facing direction is LEFT
#define ITEGGTHROW_ANGLE_MUL 0.34906587F                        // Default: 20 degrees
#define ITEGGTHROW_ANGLE_CLAMP 0.10471976F                      // Default: 6 degrees; if less than this value, angle becomes 0.0
#define ITEGGTHROW_VEL_ADD 50.0F
#define ITEGGTHROW_VEL_FORCE_MUL 2.3F                           // Multiplies number of frames the B button was held
#define ITEGGTHROW_ANGLE_FORCE_MUL (-2.1F)
#define ITEGGTHROW_ANGLE_ADD (-1.5F)
#define ITEGGTHROW_GRAVITY 2.7F
#define ITEGGTHROW_T_VEL 120.0F

#define ITYOSHISTAR_LIFETIME 16
#define ITYOSHISTAR_LIFETIME_SCALE_MUL 0.175F
#define ITYOSHISTAR_LIFETIME_SCALE_ADD 0.3F
#define ITYOSHISTAR_ROTATE_SPEED 0.24F
#define ITYOSHISTAR_VEL_CLAMP 1.8F
#define ITYOSHISTAR_ANGLE 0.5235988F
#define ITYOSHISTAR_VEL 30.0F
#define ITYOSHISTAR_OFF_X 300.0F
#define ITYOSHISTAR_OFF_Y 20.0F

#define ITSPINATTACK_LIFETIME 100
#define ITSPINATTACK_EXTEND_POS_COUNT 4
#define ITSPINATTACK_VEL 28.0F
#define ITSPINATTACK_VEL_CLAMP 0.4F
#define ITSPINATTACK_OFF_X 40.0F
#define ITSPINATTACK_OFF_Y 80.0F
#define ITSPINATTACK_ANGLE F_DEG_TO_RAD(10.0F)                  // 0.17453294F

#define ITBOOMERANG_OFF_X 150.0F
#define ITBOOMERANG_OFF_Y 290.0F
#define ITBOOMERANG_HOMING_ANGLE_MAX 0.02617994F
#define ITBOOMERANG_HOMING_ANGLE_MIN 0.01308997F
#define ITBOOMERANG_VEL_SMASH 114.0F
#define ITBOOMERANG_VEL_TILT 85.0F
#define ITBOOMERANG_ANGLE_STICK_THRESHOLD 10                    // Minimum stick Y range required to angle Boomerang up or down
#define ITBOOMERANG_LIFETIME_SMASH 190
#define ITBOOMERANG_LIFETIME_TILT 160
#define ITBOOMERANG_LIFETIME_REFLECT 100

#define ITYUBIBULLET_EXPLODE_LIFETIME 6
#define ITYUBIBULLET_EXPLODE_SIZE 180.0F
#define ITYUBIBULLET_VEL_X 160.0F
#define ITYUBIBULLET_VEL_Y -25.0F


typedef enum wpPikachuThunderCollide
{
    wpPikachuThunder_Status_Active,
    wpPikachuThunder_Status_Collide,
    wpPikachuThunder_Status_Destroy

} wpPikachuThunderCollide;

typedef enum wpNessPKThunderCollide
{
    wpNessPKThunder_Status_Active,                                 // PK Thunder is active
    wpNessPKThunder_Status_Destroy,                                // PK Thunder despawns
    wpNessPKThunder_Status_Collide                                 // PK Thunder collides with Ness

} wpNessPKThunderCollide;

typedef struct wpMarioFireballAttributes
{
    s32 lifetime;
    f32 fall_speed_max;
    f32 collide_damage; // Item loses this much health when colliding with an obstruction
    f32 gravity;
    f32 collide_vel;
    f32 rotate_speed;
    f32 angle_ground;
    f32 angle_air;
    f32 vel_base;
    void *p_item;
    int offset_wp_hit;
    f32 anim_frame;    // Starting frame of texture animation?

} wpMarioFireballAttributes;

typedef struct wpSamusChargeShotAttributes
{
    f32 gfx_size;
    f32 vel_x;
    s32 damage;
    s32 hit_size;
    s32 coll_size;
    u32 shoot_sfx_id;
    u32 charge_sfx_id;
    u32 hit_sfx_id;
    s32 priority;

} wpSamusChargeShotAttributes;

typedef struct SamusBomb_WeaponVars
{
    s32 bomb_blink_timer;

} SamusBomb_WeaponVars;

typedef struct Fireball_WeaponVars
{
    s32 index; // Index of Fireball description to use; 0 = Mario, 1 = Luigi

} Fireball_WeaponVars;

typedef struct ThunderJolt_WeaponVars
{
    s32 coll_type;
    Vec3f rotate;

} ThunderJolt_WeaponVars;

typedef struct Thunder_WeaponVars // Pikachu's Thunder
{
    s32 thunder_state;

} Thunder_WeaponVars;

typedef struct _PKThunder_WeaponVars
{
    s32 pkthunder_state;
    f32 angle;
    GObj *spawn_gobj; // PK Thunder's original owner
    GObj *trail_gobj[ITPKTHUNDER_TRAIL_COUNT];

} PKThunder_WeaponVars;

typedef struct _PKThunder_Trail_WeaponVars
{
    s32 pkthunder_trail_state;
    s32 trail_index; // Also key of RGB struct to use to set color of PK Thunder trails?
    GObj *spawn_gobj; // Original owner?
    GObj *trail_gobj[ITPKTHUNDER_TRAIL_COUNT];

} PKThunder_Trail_WeaponVars;

typedef struct ChargeShot_WeaponVars
{
    bool32 is_release;
    bool32 is_full_charge;
    s32 charge_size;
    GObj *owner_gobj;

} ChargeShot_WeaponVars;

typedef struct SpinAttack_WeaponVars
{
    s16 pos_x[ITSPINATTACK_EXTEND_POS_COUNT];
    s16 pos_y[ITSPINATTACK_EXTEND_POS_COUNT];
    Vec2f vel;
    s8 is_destroy;
    s8 pos_index;

} SpinAttack_WeaponVars;

typedef struct Boomerang_WeaponVars
{
    GObj *spawn_gobj; // GObj that spawned Boomerang
    u8 flyforward_timer;
    u8 homing_delay;
    u8 flags;
    u8 adjust_angle_delay;
    f32 default_angle;
    f32 homing_angle;

} Boomerang_WeaponVars;

typedef struct EggThrow_WeaponVars
{
    s8 is_spin; // Also determines whether Egg Throw is affected by gravity, not sure what to name it
    s8 is_throw;
    s8 stick_range;
    s8 lr;
    s16 throw_force;
    f32 angle;

} EggThrow_WeaponVars;

typedef struct Star_WeaponVars // Star Rod projectile
{
    s32 lifetime;

} Star_WeaponVars;

typedef struct Rock_WeaponVars
{
    s32 unk_0x0; // Unused?
    s32 ground_line_id;
    s32 unk_0x8; // Unused?
    s32 unk_0xC; // Set but never used?
    GObj *owner_gobj;

} Rock_WeaponVars;

typedef struct Coin_WeaponVars
{
    s32 lifetime;

} Coin_WeaponVars;

typedef struct Hydro_WeaponVars
{
    s32 unk_0x0; // Set to 0 but never used
    s32 unk_0x4; // Set to 0 but never used

} Hydro_WeaponVars;

typedef struct Smog_WeaponVars
{
    wpCommonAttributes *hit_desc;

} Smog_WeaponVars;

#endif