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

#define ITPKTHUNDER_TRAIL_COUNT 4

typedef struct ItemFireballAttributes
{
    s32 lifetime;
    f32 fall_speed_max;
    f32 collide_damage; // Item loses this much health when colliding with an obstruction
    f32 gravity;
    f32 collide_vel;
    f32 rotate_speed;
    f32 vel_ground;
    f32 vel_air;
    f32 vel_mul;
    void *p_item;
    int offset_it_hit;
    f32 frame_begin;    // Starting frame of texture animation?

} ItemFireballAttributes;

typedef struct ItemChargeShotAttributes
{
    f32 gfx_size;
    f32 vel_x;
    s32 damage;
    s32 hit_size;
    s32 coll_size;
    u32 shoot_sfx_id;
    u32 charge_sfx_id;
    u32 hit_sfx_id;
    s32 shield_damage;

} ItemChargeShotAttributes;

typedef struct SamusBomb_ItemVars
{
    s32 bomb_blink_timer;

} SamusBomb_ItemVars;

typedef struct Fireball_ItemVars
{
    s32 index; // Index of Fireball description to use; 0 = Mario, 1 = Luigi

} Fireball_ItemVars;

typedef struct Thunder_ItemVars // Pikachu's Thunder
{
    s32 thunder_state;

} Thunder_ItemVars;

typedef struct _PK_Thunder_ItemVars
{
    s32 x0;
    f32 x4;
    GObj *x8; // Original owner?
    GObj *xC[5];

} PK_Thunder_ItemVars;

typedef struct _PK_Thunder_Trail_ItemVars
{
    s32 x0;
    s32 trail_index; // Also key of RGB struct to use to set color of PK Thunder trails?
    GObj *x8; // Original owner?
    GObj *xC[5];

} PK_Thunder_Trail_ItemVars;

typedef struct Charge_Shot_ItemVars
{
    bool32 is_release;
    bool32 is_full_charge;
    s32 charge_size;
    GObj *owner_gobj;

} Charge_Shot_ItemVars;

typedef struct Spin_Attack_ItemVars
{
    s16 pos_x[4];
    s16 pos_y[4];
    u8 filler_0x10[0x18 - 0x10];
    u8 unk_0x18;
    s8 pos_index;

} Spin_Attack_ItemVars;

typedef struct Egg_Throw_ItemVars
{
    u8 unk_0x0;
    u8 is_throw;
    Vec2b trajectory;
    s16 throw_force;

} Egg_Throw_ItemVars;

#endif