#ifndef _ARTICLEVARS_H_
#define _ARTICLEVARS_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define ATCAPSULE_GRAVITY 1.2F
#define ATCAPSULE_T_VEL 100.0F
#define ATCAPSULE_EXPLODE_SCALE 1.4F // Size of explosion graphics

#define ATTOMATO_GRAVITY 1.2F
#define ATTOMATO_T_VEL 100.0F

#define ATHEART_GRAVITY 0.25F
#define ATHEART_T_VEL 30.0F

#define ATSTAR_INTERACT_DELAY 16 // Wait this many frames before becoming tangible
#define ATSTAR_GRAVITY 1.2F
#define ATSTAR_T_VEL 100.0F
#define ATSTAR_VEL_X 8.0F
#define ATSTAR_BOUNCE_Y 50.0F // Y-velocity added when Star Man touches the ground

#define ATSWORD_GRAVITY 1.2F
#define ATSWORD_T_VEL 100.0F

#define ATBAT_GRAVITY 1.5F
#define ATBAT_T_VEL 120.0F

#define ATHARISEN_GRAVITY 1.0F
#define ATHARISEN_T_VEL 80.0F

#define ATLGUN_AMMO_MAX 16
#define ATLGUN_GRAVITY 1.5F
#define ATLGUN_T_VEL 130.0F
#define ATLGUN_AMMO_VEL_X 300.0F
#define ATLGUN_AMMO_STEP_SCALE_X 10.0F
#define ATLGUN_AMMO_CLAMP_SCALE_X 53.333332F

#define ATFFLOWER_AMMO_MAX 60
#define ATFFLOWER_AMMO_LIFETIME 30
#define ATFFLOWER_AMMO_VEL 30.0F
#define ATFFLOWER_GRAVITY 1.2F
#define ATFFLOWER_T_VEL 100.0F

#define ATHAMMER_COLANIM_ID 0x4E // Color animation applied to hammer when time is almost up
#define ATHAMMER_GRAVITY 1.5F
#define ATHAMMER_T_VEL 120.0F

#define ATMSBOMB_EXPLODE_LIFETIME 16
#define ATMSBOMB_DETECT_FIGHTER_DELAY 100
#define ATMSBOMB_DETECT_FIGHTER_RADIUS SQUARE(400.0F) // Radius is actually 400 units, but it is not sqrt'd in the detection function, so it ends up checking 160000.0F
#define ATMSBOMB_GRAVITY 1.5F
#define ATMSBOMB_T_VEL 80.0F
#define ATMSBOMB_COLL_SIZE 30.0F // Size of Motion Sensor Bomb collision box
#define ATMSBOMB_EXPLODE_SCALE 1.2F // Size of explosion graphics

#define ATBOMBHEI_EXPLODE_COLANIM_ID 0x4D
#define ATBOMBHEI_EXPLODE_COLANIM_DURATION 90
#define ATBOMBHEI_EXPLODE_LIFETIME 6
#define ATBOMBHEI_WALK_WAIT 180 // Number of frames required to pass for Bob-Omb to begin walking
#define ATBOMBHEI_FLASH_WAIT 480 // Number of frames required to pass for Bob-Omb to begin flashing
#define ATBOMBHEI_SMOKE_WAIT 4 // Delay between smoke GFX?
#define ATBOMBHEI_EXPLODE_WAIT 90.0F // Number of frames required to pass for Bob-Omb to explode after flashing? Also a float for some reason
#define ATBOMBHEI_WALK_VEL_X 24.0F
#define ATBOMBHEI_GRAVITY 1.2F
#define ATBOMBHEI_T_VEL 100.0F
#define ATBOMBHEI_EXPLODE_SCALE 1.4F

#define ATSTARROD_AMMO_MAX 20
#define ATSTARROD_GRAVITY 1.2F
#define ATSTARROD_T_VEL 100.0F
#define ATSTARROD_AMMO_SMASH_VEL_X 120.0F
#define ATSTARROD_AMMO_TILT_VEL_X 80.0F
#define ATSTARROD_AMMO_SMASH_LIFETIME 30.0F
#define ATSTARROD_AMMO_TILT_LIFETIME 30.0F

#define ATGSHELL_LIFETIME 240
#define ATGSHELL_HEALTH_MAX 4           // Set every time shell hits a target
#define ATGSHELL_GFX_SPAWN_INT 8        // Interval between dust GFX
#define ATGSHELL_DAMAGE_ALL_WAIT 32     // Wait this many frames before shell can damage its owner and teammates
#define ATGSHELL_CLAMP_VEL_X 90.0F      // Limit maximum X-velocity to this value
#define ATGSHELL_REBOUND_MUL_X 0.125F   // Multiplies negated X-velocity; actually division, but optimized into multiplication if possible
#define ATGSHELL_REBOUND_VEL_Y 38.0F    // Y-velocity gained when recoiling from hitting a target
#define ATGSHELL_STOP_VEL_X 12.0F       // Halt all horizontal velocity if less than this value
#define ATGSHELL_DAMAGE_MUL_NORMAL 8.0F // Multiplies damage taken and turns it into horizontal velocity; run when Shell is hit out of its "wait" state
#define ATGSHELL_DAMAGE_MUL_ADD 3.0F    // Multiplies damage taken and adds it to horizontal velocity; run whe Shell is hit out of its "slide" state
#define ATGSHELL_GRAVITY 1.2F
#define ATGSHELL_T_VEL 100.0F

#define ATCONTAINER_GFX_COUNT 7         // Number of pieces Barrel and Crate containers burst into when smashed open
#define ATCONTAINER_GFX_LIFETIME 90     // Smashed container pieces despawn once this runs out

#define ATBOX_HEALTH_MAX 15             // Maximum damage box can resist before breaking
#define ATBOX_EXPLODE_SCALE 1.4F        // Size of explosion graphics
#define ATBOX_GRAVITY 4.0F
#define ATBOX_T_VEL 120.0F

#define ATTARU_LIFETIME 360
#define ATTARU_DESPAWN_FLASH_START 60   // Begin flashing when below this value
#define ATTARU_HEALTH_MAX 10
#define ATTARU_MUL_VEL_X 1.4F
#define ATTARU_MIN_VEL_XY 0.1F          // Decrement lifetime if Barrel's XY velocity is less than this value
#define ATTARU_ROLL_ROTATE_MUL 0.0045F  // Multiplies rotation of barrel
#define ATTARU_EXPLODE_SCALE 1.4F       // Size of explosion graphics
#define ATTARU_GRAVITY 4.0F
#define ATTARU_T_VEL 90.0F

#define ATRSHELL_INTERACT_MAX 24
#define ATRSHELL_LIFETIME 480
#define ATRSHELL_HEALTH_MAX 4
#define ATRSHELL_GFX_SPAWN_INT 8
#define ATRSHELL_DAMAGE_ALL_WAIT 16
#define ATRSHELL_CLAMP_VEL_X 70.0F
#define ATRSHELL_CLAMP_AIR_X 90.0F      // Leftover from Green Shell? This is checked only when the ground beneath the Red Shell collapses
#define ATRSHELL_HIT_INIT_VEL_X 8.0F    // Initialize hitbox if it is currently inactive and velocity is less than this value
#define ATRSHELL_MUL_VEL_X 1.2F
#define ATRSHELL_STOP_VEL_X 8.0F        // Halt all horizontal velocity if less than this value OR disable hitbox
#define ATRSHELL_ADD_VEL_X 60.0F        // Added when Red Shell is reflected
#define ATRSHELL_RECOIL_VEL_X (-8.0F)   // Applied when shell is attacked
#define ATRSHELL_RECOIL_MUL_X 0.7F      // Multiplies recoil velocity
#define ATRSHELL_DAMAGE_MUL_NORMAL 10.0F// Multiplies damage taken and turns it into horizontal velocity; run when Shell is hit out of its "wait" state
#define ATRSHELL_GRAVITY 1.2F
#define ATRSHELL_T_VEL 100.0F

typedef struct Common_ArticleVars
{
    u8 filler[0x24]; // fill 0x24 bytes until all vars are mapped

} Common_ArticleVars;

typedef struct BombHei_ArticleVars
{
    u16 smoke_delay; // Frames before smoke effect is created when Bob-Omb begins walking?

} BombHei_ArticleVars;

typedef struct Shell_ArticleVars
{
    u8 damage_all_delay; // Shell can hit owner and teammates once this frame timer reaches -1
    u8 dust_gfx_int; // Delay between dust GFX
    u8 health; // Appears to deterime whether Shell will despawn after hittin a target, shell can have up to 4 HP
    u8 is_damage; // Shell can damage players
    u8 is_setup_vars;
    u8 interact; // Decremented each time the shell is attacked, reflected, or it hits something; despawns shell at 0
    f32 vel_x;

} Shell_ArticleVars;

typedef struct Taru_ArticleVars
{
    f32 roll_rotate_speed;

} Taru_ArticleVars;

#endif