#ifndef _ARTICLEVARS_H_
#define _ARTICLEVARS_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define ATCAPSULE_GRAVITY 1.2F
#define ATCAPSULE_T_VEL 100.0F
#define ATCAPSULE_EXPLODE_SCALE 1.4F                    // Size of explosion graphics

#define ATTOMATO_DAMAGE_HEAL 100
#define ATTOMATO_GRAVITY 1.2F
#define ATTOMATO_T_VEL 100.0F

#define ATHEART_DAMAGE_HEAL 999
#define ATHEART_GRAVITY 0.25F
#define ATHEART_T_VEL 30.0F

#define ATSTAR_INVINCIBLE_TIME 600
#define ATSTAR_WARN_BEGIN_FRAME 480
#define ATSTAR_INTERACT_DELAY 16                        // Wait this many frames before becoming tangible
#define ATSTAR_GRAVITY 1.2F
#define ATSTAR_T_VEL 100.0F
#define ATSTAR_VEL_X 8.0F
#define ATSTAR_BOUNCE_Y 50.0F                           // Y-velocity added when Star Man touches the ground

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
    
#define ATHAMMER_COLANIM_ID 0x4E                        // Color animation applied to hammer when time is almost up
#define ATHAMMER_GRAVITY 1.5F
#define ATHAMMER_T_VEL 120.0F

#define ATMSBOMB_EXPLODE_LIFETIME 16
#define ATMSBOMB_DETECT_FIGHTER_DELAY 100
#define ATMSBOMB_DETECT_FIGHTER_RADIUS SQUARE(400.0F)   // Radius is actually 400 units, but it is not sqrt'd in the detection function, so it ends up checking 160000.0F
#define ATMSBOMB_GRAVITY 1.5F
#define ATMSBOMB_T_VEL 80.0F
#define ATMSBOMB_COLL_SIZE 30.0F                        // Size of Motion Sensor Bomb collision box
#define ATMSBOMB_EXPLODE_SCALE 1.2F                     // Size of explosion graphics

#define ATBOMBHEI_EXPLODE_COLANIM_ID 0x4D
#define ATBOMBHEI_EXPLODE_COLANIM_DURATION 90
#define ATBOMBHEI_EXPLODE_LIFETIME 6
#define ATBOMBHEI_WALK_WAIT 180                         // Number of frames required to pass for Bob-Omb to begin walking
#define ATBOMBHEI_FLASH_WAIT 480                        // Number of frames required to pass for Bob-Omb to begin flashing
#define ATBOMBHEI_SMOKE_WAIT 4                          // Delay between smoke GFX?
#define ATBOMBHEI_EXPLODE_WAIT 90.0F                    // Number of frames required to pass for Bob-Omb to explode after flashing? Also a float for some reason
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
#define ATGSHELL_HEALTH_MAX 4                           // Set every time shell hits a target
#define ATGSHELL_GFX_SPAWN_INT 8                        // Interval between dust GFX
#define ATGSHELL_DAMAGE_ALL_WAIT 32                     // Wait this many frames before shell can damage its owner and teammates
#define ATGSHELL_CLAMP_VEL_X 90.0F                      // Limit maximum X-velocity to this value
#define ATGSHELL_REBOUND_MUL_X 0.125F                   // Multiplies negated X-velocity; actually division, but optimized into multiplication if possible
#define ATGSHELL_REBOUND_VEL_Y 38.0F                    // Y-velocity gained when recoiling from hitting a target
#define ATGSHELL_STOP_VEL_X 12.0F                       // Halt all horizontal velocity if less than this value
#define ATGSHELL_DAMAGE_MUL_NORMAL 8.0F                 // Multiplies damage taken and turns it into horizontal velocity; run when Shell is hit out of its "wait" state
#define ATGSHELL_DAMAGE_MUL_ADD 3.0F                    // Multiplies damage taken and adds it to horizontal velocity; run whe Shell is hit out of its "slide" state
#define ATGSHELL_GRAVITY 1.2F
#define ATGSHELL_T_VEL 100.0F

#define ATCONTAINER_GFX_COUNT 7                         // Number of pieces Barrel and Crate containers burst into when smashed open
#define ATCONTAINER_GFX_LIFETIME 90                     // Smashed container pieces despawn once this runs out

#define ATBOX_HEALTH_MAX 15                             // Maximum damage box can resist before breaking
#define ATBOX_EXPLODE_SCALE 1.4F                        // Size of explosion graphics
#define ATBOX_GRAVITY 4.0F
#define ATBOX_T_VEL 120.0F

#define ATTARU_LIFETIME 360
#define ATTARU_EXPLODE_LIFETIME 8
#define ATTARU_DESPAWN_FLASH_START 60                   // Begin flashing when below this value
#define ATTARU_HEALTH_MAX 10
#define ATTARU_MUL_VEL_X 1.4F
#define ATTARU_MIN_VEL_XY 0.1F                          // Decrement lifetime if Barrel's XY velocity is less than this value
#define ATTARU_ROLL_ROTATE_MUL 0.0045F                  // Multiplies rotation of barrel
#define ATTARU_EXPLODE_SCALE 1.4F                       // Size of explosion graphics
#define ATTARU_GRAVITY 4.0F
#define ATTARU_T_VEL 90.0F

#define ATRSHELL_INTERACT_MAX 24
#define ATRSHELL_LIFETIME 480
#define ATRSHELL_HEALTH_MAX 4
#define ATRSHELL_GFX_SPAWN_INT 8
#define ATRSHELL_DAMAGE_ALL_WAIT 16
#define ATRSHELL_CLAMP_VEL_X 70.0F
#define ATRSHELL_CLAMP_AIR_X 90.0F                      // Leftover from Green Shell? This is checked only when the ground beneath the Red Shell collapses
#define ATRSHELL_HIT_INIT_VEL_X 8.0F                    // Initialize hitbox if it is currently inactive and velocity is less than this value
#define ATRSHELL_MUL_VEL_X 1.2F
#define ATRSHELL_STOP_VEL_X 8.0F                        // Halt all horizontal velocity if less than this value OR disable hitbox
#define ATRSHELL_ADD_VEL_X 60.0F                        // Added when Red Shell is reflected
#define ATRSHELL_RECOIL_VEL_X (-8.0F)                   // Applied when shell is attacked
#define ATRSHELL_RECOIL_MUL_X 0.7F                      // Multiplies recoil velocity
#define ATRSHELL_DAMAGE_MUL_NORMAL 10.0F                // Multiplies damage taken and turns it into horizontal velocity; run when Shell is hit out of its "wait" state
#define ATRSHELL_GRAVITY 1.2F
#define ATRSHELL_T_VEL 100.0F

#define ATBUMPER_CASTLE_KNOCKBACK 300                   // Weight-Dependent Set Knockback of Bumper on Peach's Castle
#define ATBUMPER_CASTLE_ANGLE 361                       // Knockback angle of Bumper on Peach's Castle
#define ATBUMPER_LIFETIME 360
#define ATBUMPER_DESPAWN_TIMER 60                       // Bumper's lifetime is reset to this value; there is no hitbox during this state, and it vanishes for good once it runs out
#define ATBUMPER_RESET_VEL_TIMER 4                      // Bumper's X-velocity is reset to 0.0 when at_multi is less than this value
#define ATBUMPER_DAMAGE_ALL_WAIT 16     
#define ATBUMPER_HIT_SCALE 10                           // Initial of bumper when hitting a target while airborne
#define ATBUMPER_HIT_ANIM_LENGTH 3                      // Number of frames bumper's airborne hit texture lasts 
#define ATBUMPER_COLL_SIZE 120.0F           
#define ATBUMPER_REBOUND_VEL_X (-100.0F)                // Applied when bumper hits a target while grounded 
#define ATBUMPER_REBOUND_AIR_X (-400.0F)                // Applied when bumper hits a target while airborne
#define ATBUMPER_REBOUND_AIR_Y 200.0F                   // Applied when bumper hits a target while airborne
#define ATBUMPER_GRAVITY_NORMAL 1.4F
#define ATBUMPER_GRAVITY_HIT 4.0F
#define ATBUMPER_T_VEL 80.0F

#define ATGRLUCKY_EGG_SPAWN_WAIT 1                      // Wait this many frames before spawning egg (read only when egg spawn function is called)
#define ATGRLUCKY_EGG_SPAWN_OFF_X 200.0F                // X-offset of egg spawn
#define ATGRLUCKY_EGG_SPAWN_OFF_Y 200.0F                // Y-offset of egg spawn
#define ATGRLUCKY_EGG_SPAWN_MUL 8.0F                    // Multiplies random velocity of egg
#define ATGRLUCKY_EGG_SPAWN_ADD_X 8.0F                  // Added to mutliplied random velocity of egg
#define ATGRLUCKY_EGG_SPAWN_ADD_Y 30.0F                 // Added to multiplide random velocity of egg
#define ATGRLUCKY_EGG_SPAWN_BEGIN 80.0F                 // First frame egg spawn function is called
#define ATGRLUCKY_EGG_SPAWN_END 85.0F                   // Last frame egg spawn function is called
#define ATGRLUCKY_HIT_ROTATE_Z 0.10471976F              // Rotation step when Chansey is knocked out of the Pok�mon hut? Not actually applied?
#define ATGRLUCKY_GRAVITY 1.2F
#define ATGRLUCKY_T_VEL 100.0F

#define ATMBALL_SPAWN_WAIT 30                           // Wait this many frames before releasing Pok�mon once thrown and landed
#define ATMBALL_GRAVITY 1.5F 
#define ATMBALL_T_VEL 120.0F

#define ATMONSTER_RISE_STOP_WAIT 22                     // Universal attribute for Pok�mon to stop slowly levitating upward and to use designated physics this many frames after spawning
#define ATMONSTER_RISE_VEL_Y 16.0F                      // Y-velocity of "levitate" effect after exiting Pok� Ball

#define ATPAKKUN_APPEAR_WAIT 180                        // Duration Pirahna Plant waits before coming out of its pipe
#define ATPAKKUN_REBIRTH_WAIT 1200                      // Duration Pirahna Plant waits before respawning after being knocked out and hitting one of the blast zones
#define ATPAKKUN_APPEAR_OFF_Y 245.0F      
#define ATPAKKUN_CLAMP_OFF_Y 360.0F      
#define ATPAKKUN_HURT_SIZE_MUL_Y 0.5F   
#define ATPAKKUN_DETECT_SIZE_WIDTH 600.0F               // Width of Pirahna Plant fighter detection box when checking to stay inside the pipe
#define ATPAKKUN_DETECT_SIZE_BOTTOM (-300.0F)           // Bottom of Pirahna Plant fighter detection box when checking to stay inside the pipe
#define ATPAKKUN_DETECT_SIZE_TOP 700.0F                 // Top of Pirahna Plant fighter detection box when checking to stay inside the pipe

#define ATIWARK_FLY_WAIT 30                             // Unconfirmed?
#define ATIWARK_MODEL_ROTATE_WAIT 6                     // Onix's sprite is flipped every time this timer is up; counts up, reset to 0 when reaching destination value
#define ATIWARK_ROCK_RUMBLE_WAIT 18                     // Frames to wait between screen shake effects
#define ATIWARK_ROCK_SPAWN_COUNT_MAX 9                  // Maximum number of rocks that can be spawned
#define ATIWARK_ROCK_SPAWN_COUNT_MIN 8                  // Added to number of rocks that can be spawned
#define ATIWARK_ROCK_SPAWN_WAIT_MAX 30                  // Maximum random delay between spawned rocks
#define ATIWARK_ROCK_SPAWN_WAIT_MIN 15                  // Added to random delay between spawned rocks
#define ATIWARK_ROCK_SPAWN_OFF_X_MUL 2000.0F            // Multiplies random spawn position of rock projectile
#define ATIWARK_ROCK_SPAWN_OFF_X_ADD (-1000.0F)         // Added to random spawn position of rock projectile
#define ATIWARK_FLY_VEL_Y 80.0F                         // Y-velocity of Onix when flying up
#define ATIWARK_FLY_STOP_Y 200.0F                       // Stop this many units away from the upper blast zone
#define ATIWARK_IWARK_ADD_POS_Y (-660.0F)               // Add this to Y-position if user is Onix
#define ATIWARK_OTHER_ADD_POS_Y (-100.0F)               // Add this to Y-position if user is not Onix

#define ATIWARK_ROCK_RANDOM_VEL_MAX 3                   // Maximum number of random initial Y-velocities possible
#define ATIWARK_ROCK_GRAVITY 2.0F                       // Gravity of rock projectile
#define ATIWARK_ROCK_T_VEL 200.0F                       // Terminal velocity of rock projectile
#define ATIWARK_ROCK_ROTATE_STEP (-0.5F)                // Z-rotation step of rock projectile
#define ATIWARK_ROCK_VEL_Y_START_A (-100.0F)            // One of three random initial Y-velocities possible
#define ATIWARK_ROCK_VEL_Y_START_B (-50.0F)             // One of three random initial Y-velocities possible
#define ATIWARK_ROCK_VEL_Y_START_C 0.0F                 // One of three random initial Y-velocities possible
#define ATIWARK_ROCK_COLLIDE_MUL_VEL_Y 0.1F             // Assume this is what slows the rocks down so much when they hit the ground
#define ATIWARK_ROCK_COLLIDE_ADD_VEL_Y (-150.0F)        // Added when rock collides with ground

#define ATKABIGON_GFX_SPAWN_INT 4
#define ATKABIGON_DROP_WAIT 60                          // Wait this many frames before dropping after reaching the top of the screen
#define ATKABIGON_RUMBLE_WAIT 18                        // Wait this many frames between screen shake effects
#define ATKABIGON_DROP_VEL_Y (-220.0F)                  // Velocity of downward drop
#define ATKABIGON_DROP_OFF_X_MUL 2000.0F                // Multiplies random drop X-position
#define ATKABIGON_DROP_OFF_X_ADD (-1000.0F)             // Added to multiplied random drop X-position
#define ATKABIGON_DROP_SIZE_KABIGON 4.0F                // Size of Snorlax's drop model and hitbox
#define ATKABIGON_DROP_SIZE_OTHER 5.2F                  // Size of non-Snorlax drop model and hitbox (Clefairy)
#define ATKABIGON_JUMP_VEL_Y 80.0F                      // Y-velocity of Snorlax's jump
#define ATKABIGON_JUMP_GFX_MUL_OFF 200.0F               // Multiplies random spawn position of dust GFX when Snorlax jumps
#define ATKABIGON_JUMP_GFX_SUB_OFF 100.0F               // Subtracted from random spawn position of dust GFX when Snorlax jumps
#define ATKABIGON_MAP_OFF_Y 200.0F                      // Halt jump this many units away from top blastonze / despawn if Y-position is less than bottom blastzone + this value

#define ATTOSAKINTO_LIFETIME 360
#define ATTOSAKINTO_FLAP_VEL_X 10.0F                    // Semi-constant horizontal velocity that may randomly be inverted
#define ATTOSAKINTO_FLAP_VEL_Y 60.0F                    // Vertical velocity gained from touching the ground
#define ATTOSAKINTO_GRAVITY 6.0F
#define ATTOSAKINTO_T_VEL 90.0F

#define ATMEW_LIFETIME 480
#define ATMEW_GFX_SPAWN_INT 3
#define ATMEW_START_VEL_X 8.0F                          // Mew's initial X-velocity
#define ATMEW_START_VEL_Y -20.0F                        // Mew's initial Y-velocity
#define ATMEW_FLY_ADD_VEL_Y 0.8F                        // Added to Mew's Y-velocity every frame

#define ATNYARS_LIFETIME 240
#define ATNYARS_MODEL_ROTATE_WAIT 30                    // Flip Meowth's model every time this timer runs out; reset at 0
#define ATNYARS_COIN_SPAWN_MAX 4                        // Spawn this many coins simultaneously
#define ATNYARS_COIN_LIFETIME 10
#define ATNYARS_COIN_SPAWN_WAIT 8                       // Spawn a new set of coins at this frequency (frames)
#define ATNYARS_COIN_ANGLE_STEP 13.0F                   // Multiplies coin rotation step, actually angle in degrees
#define ATYNARS_COIN_ANGLE_DIFF 90.0F                   // Angle difference between each simultaneously spawned coin (90 degrees by default, this is why it's cross-shaped)
#define ATNYARS_COIN_VEL_X 130.0F

#define ATLIZARDON_LIFETIME 480
#define ATLIZARDON_FLAME_LIFETIME 30
#define ATLIZARDON_FLAME_SPAWN_WAIT 8                   // Wait this many frames before spawning another flame projectile
#define ATLIZARDON_TURN_WAIT 26                         // Wait this many frames before flipping Charizard's sprite
#define ATLIZARDON_FLAME_SPAWN_ANGLE -0.2617994F        // Angle at which flame projectile spreads
#define ATLIZARDON_FLAME_VEL_XY 50.0F       
#define ATLIZARDON_LIZARDON_FLAME_OFF_X 180.0F          // X-offset of Charizard's flame spawn position
#define ATLIZARDON_LIZARDON_FLAME_OFF_Y 120.0F          // Y-offset of Charizard's flame spawn position
#define ATLIZARDON_OTHER_FLAME_OFF_X 100.0F             // X-offset of other flame spawn position (Clefairy)
#define ATLIZARDON_DUST_GFX_OFF_X (-400.0F)             // X-offset of dust GFX when turning around
#define ATLIZARDON_GRAVITY 1.0F 
#define ATLIZARDON_T_VEL 40.0F

#define ATSPEAR_SPAWN_COUNT 16                          // Swarm will have this many member Beedrill
#define ATSPEAR_SPAWN_WAIT_CONST 12                     // Minimum number of frames between Beedrill swarm member spawns
#define ATSPEAR_SPAWN_WAIT_RANDOM 9                     // Added to minimum number of frames between Beedrill swarm member spawns
#define ATSPEAR_SPAWN_OFF_Y_MUL 1800.0F                 // Multiplies random vertical spawn position
#define ATSPEAR_SPAWN_OFF_Y_ADD (-800.0F)               // Added to random vertical spawn position
#define ATSPEAR_SWARM_FLY_VEL_X 130.0F                  // X-velocity of Beedrill swarm members
#define ATSPEAR_SWARM_CALL_VEL_X 6.0F                   // Leader Beedrill's X-velocity when flying off to call the swarm, added each frame until called
#define ATSPEAR_SWARM_CALL_VEL_Y 60.0F                  // ???
#define ATSPEAR_SWARM_CALL_OFF_X 500.0F                 // Begin swarm when leader is this many units away from the side blastzone
#define ATSPEAR_SWARM_CALL_WAIT 51.0F                   // Fly off into the distance and call Beedrill swarm on this frame of the leader's wait animation
#define ATSPEAR_GRAVITY 1.0F
#define ATSPEAR_T_VEL 90.0F 

#define ATKAMEX_LIFETIME 360
#define ATKAMEX_HYDRO_LIFETIME 20
#define ATKAMEX_HYDRO_SPAWN_WAIT_CONST 30               // Constant wait frames to spawn Hydro Pump
#define ATKAMEX_HYDRO_SPAWN_WAIT_RANDOM 1               // Maximum random wait frames to spawn Hydro Pump
#define ATKAMEX_KAMEX_HYDRO_SPAWN_OFF_X 360.0F          // X-offset of Blastoise Hydro Pump spawn position
#define ATKAMEX_KAMEX_HYDRO_SPAWN_OFF_Y 100.0F          // Y-offset of Blastoise Hydro Pump spawn position
#define ATKAMEX_OTHER_HYDRO_SPAWN_OFF_X 100.0F          // X-offset of other Hydro Pump spawn position (Clefairy)
#define ATKAMEX_DUST_SPAWN_OFF_X (-150.0F)              // X-offset of dust GFX
#define ATKAMEX_COLL_SIZE 341.0F
#define ATKAMEX_PUSH_VEL_X 2.3F
#define ATKAMEX_CONST_VEL_X 38.0F                       // Constant velocity after Blastoise lands
#define ATKAMEX_GRAVITY 1.0F
#define ATKAMEX_T_VEL 40.0F

#define ATMBLUCKY_LIFETIME 90                           // Used only after Chansey has spawned all of its eggs
#define ATMBLUCKY_EGG_SPAWN_WAIT_ADD 4                  // Added when Chansey gets hit
#define ATMBLUCKY_EGG_SPAWN_COUNT 3 
#define ATMBLUCKY_EGG_SPAWN_WAIT_CONST 30
#define ATMBLUCKY_EGG_SPAWN_BASE_VEL 8.0F               // Multiplies random velocity
#define ATMBLUCKY_EGG_SPAWN_ADD_VEL_X 7.0F              // Added to multiplied random X-velocity
#define ATMBLUCKY_EGG_SPAWN_ADD_VEL_Y 40.0F             // Added to multiplide random Y-velocity
#define ATMBLUCKY_GRAVITY 1.0F
#define ATMBLUCKY_T_VEL 40.0F

#define ATEGG_EXPLODE_GFX_WAIT 8                        // Wait this many frames before spawning eggshell break GFX on explosion
#define ATEGG_EXPLODE_GFX_SCALE 1.4F                    // Scale of explosion GFX
#define ATEGG_GRAVITY 1.2F
#define ATEGG_T_VEL 100.0F

#define ATSTARMIE_LIFETIME 240
#define ATSTARMIE_SWIFT_LIFETIME 30
#define ATSTARMIE_SWIFT_SPAWN_WAIT_CONST 12             // Constant wait frames to spawn Hydro Pump
#define ATSTARMIE_SWIFT_SPAWN_WAIT_RANDOM 1             // Maximum random wait frames to spawn Swift
#define ATSTARMIE_SWIFT_VEL_X 150.0F
#define ATSTARMIE_STARMIE_SWIFT_SPAWN_OFF_X 200.0F      // X-offset of Starmie Swift spawn position
#define ATSTARMIE_STARMIE_SWIFT_SPAWN_OFF_Y 100.0F      // Y-offset of Starmie Swift spawn position
#define ATSTARMIE_OTHER_SWIFT_SPAWN_OFF_X 100.0F        // X-offset of other Swift spawn position (Clefairy)
#define ATSTARMIE_TARGET_POS_OFF_X 400.0F               // Added to Starmie's target travel position + fighter's collision box
#define ATSTARMIE_TARGET_POS_OFF_Y 250.0F               // Added to Starmie's target travel position + fighter's collision box
#define ATSTARMIE_FOLLOW_VEL_X 20.0F                    // X-velocity at which Starmie follows its victim
#define ATSTARMIE_ADD_VEL_X 10.0F
#define ATSTARMIE_PUSH_VEL_X 70.0F                      // Set every time Starmie fires Swift

#define ATSAWAMURA_LIFETIME 600
#define ATSAWAMURA_KICK_WAIT 40
#define ATSAWAMURA_TARGET_POS_OFF_Y 500.0F              // Added to Hitmonlee's target travel position + fighter's collision box
#define ATSAWAMURA_DESPAWN_OFF_X 500.0F                 // Despawn if Hitmonlee is within this many units of the side blastzones
#define ATSAWAMURA_KICK_SIZE 300.0F                     // Size of kick hitbox
#define ATSAWAMURA_KICK_VEL_X 400.0F
#define ATSAWAMURA_GRAVITY 2.4F
#define ATSAWAMURA_T_VEL 100.0F

#define ATDOGAS_DESPAWN_WAIT 90                         // Wait this many frames after running out of gas before despawning
#define ATDOGAS_SMOG_SPAWN_WAIT 8
#define ATDOGAS_SMOG_SPAWN_COUNT 32                     // Spawn this many Smog clouds
#define ATDOGAS_SMOG_LIFETIME 30
#define ATDOGAS_SMOG_VEL_XY 18.0F                  
#define ATDOGAS_SMOG_MUL_OFF_X 400.0F                   // Multiply random spawn position
#define ATDOGAS_SMOG_SUB_OFF_X 200.0F                   // Subtracted from multiplied random spawn position
#define ATDOGAS_SMOG_MUL_OFF_Y 800.0F                   // Multiply random spawn position
#define ATDGOAS_SMOG_SUB_OFF_Y 400.0F                   // Subtracted from multiplied random spawn position

#define ATMARUMINE_EXPLODE_LIFETIME 6
#define ATMARUMINE_EXPLODE_GFX_SCALE 1.4F

#define ATPORYGON_SHAKE_STOP_WAIT 32                    // Stop vertical shake after this many frames have passed?

#define ATHITOKAGE_FLAME_LIFETIME 20
#define ATHITOKAGE_FLAME_SPAWN_WAIT 8
#define ATHITOKAGE_FLAME_SPAWN_ANGLE -0.20943952F
#define ATHITOKAGE_FLAME_VEL_XY 45.0F
#define ATHITOKAGE_FLAME_SPAWN_BEGIN 40.0F              // Charmander can begin firing Flamethrower this frame onward
#define ATHITOKAGE_FLAME_SPAWN_END 120.0F               // Charmander can no longer fire Flamethrower this frame onward
#define ATHITOKAGE_FLAME_SPAWN_OFF_X (-250.0F)          // X-offset of flame spawn
#define ATHITOKAGE_HIT_ROTATE_Z 0.10471976F
#define ATHITOKAGE_GRAVITY 1.2F
#define ATHITOKAGE_T_VEL 100.0F

#define ATFUSHIGIBANA_RETURN_WAIT 128                   // Wait this many frames before deactivating hitbox?
#define ATFUSHIGIBANA_RAZOR_LIFETIME 24
#define ATFUSHIGIBANA_RAZOR_SPAWN_WAIT 16
#define ATFUSHIGIBANA_RAZOR_VEL_X (-100.0F)
#define ATFUSHIGIBANA_RAZOR_ADD_VEL_X 5.0F              
#define ATFUSHIGIBANA_RAZOR_SPAWN_BEGIN 40.0F           // Venusaur can begin shooting Razor Leaf this frame onward
#define ATFUSHIGIBANA_RAZOR_SPAWN_END 120.0F            // Venusaur can no longer shoot Razor Leaf this frame onward
#define ATFUSHIGIBANA_RAZOR_SPAWN_OFF_X (-540.0F)       // X-offset of leaf spawn

#define ATGRBOMB_GFX_COUNT 7                            // Number of pieces RTTF Bomb bursts into when smashed open
#define ATGRBOMB_GFX_LIFETIME 90                        // Smashed RTTF Bomb pieces despawn once this runs out

#define ATGRBOMB_HEALTH_MAX 10
#define ATGRBOMB_EXPLODE_LIFETIME 6
#define ATGRBOMB_EXPLODE_GFX_SCALE 1.4F
#define ATGRBOMB_MUL_VEL_X 1.4F
#define ATGRBOMB_MIN_VEL_XY 0.1F                        // Decrement lifetime if Barrel's XY velocity is less than this value
#define ATGRBOMB_ROLL_ROTATE_MUL 0.0045F                // Multiplies rotation of barrel
#define ATGRBOMB_GRAVITY 4.0F
#define ATGRBOMB_T_VEL 90.0F

#define ATPKFIRE_LIFETIME 100
#define ATPKFIRE_HURT_DAMAGE_MUL 3                      // Multiplies damage taken, result gets subtracted from lifetime
#define ATPKFIRE_GRAVITY 0.45F
#define ATPKFIRE_T_VEL 55.0F

#define ATLINKBOMB_HEALTH 7
#define ATLINKBOMB_LIFETIME 300
#define ATLINKBOMB_EXPLODE_LIFETIME 6
#define ATLINKBOMB_BLOAT_COLANIM_ID 0x4F                // Apply this color animation when Bomb begins to bloat
#define ATLINKBOMB_BLOAT_COLANIM_LENGTH 96              // Duration of bloat color animation
#define ATLINKBOMB_SCALE_INDEX_MAX 10                   // Maximum number of scale floats in array?
#define ATLINKBOMB_SCALE_INDEX_REWIND 6                 // When index reaches this value, rewind
#define ATLINKBOMB_SCALE_INT 4                          // Interval between Bomb inflate/deflate animation updates; effectively animation speed
#define ATLINKBOMB_DAMAGE_RECOIL_VEL_X 20.0F            // Horizontal knockback taken from hits dealing less than ATLINKBOMB_HEALTH can sustain
#define ATLINKBOMB_DAMAGE_RECOIL_VEL_Y 18.0F            // Vertical knockback taken from hits dealing less than ATLINKBOMB_HEALTH can sustain
#define ATLINKBOMB_EXPLODE_THRESHOLD_VEL_X 36.0F        // If X-velocity is greater than this value when hitting a target, explode
#define ATLINKBOMB_EXPLODE_THRESHOLD_VEL_Y 25.0F        // If Y-velocity is greater than this value when hitting a target, explode
#define ATLINKBOMB_BLOAT_BEGIN 96.0F                    // Bomb begins bloating when lifetime is equal or less than this value
#define ATLINKBOMB_HIT_RECOIL_VEL_X 8.0F                // X-velocity upon hitting a target without exploding
#define ATLINKBOMB_HIT_RECOIL_VEL_Y 20.0F               // Y-velocity upon hitting a target without exploding
#define ATLINKBOMB_EXPLODE_GFX_SCALE 1.3F
#define ATLINKBOMB_GRAVITY 1.2F
#define ATLINKBOMB_T_VEL 100.0F

typedef struct BombHei_ArticleVars
{
    u16 smoke_delay;     // Frames before smoke effect is created when Bob-Omb begins walking?

} BombHei_ArticleVars;

typedef struct Shell_ArticleVars
{
    u8 damage_all_delay;     // Shell can hit owner and teammates once this frame timer reaches -1
    u8 dust_gfx_int;     // Delay between dust GFX
    u8 health;     // Appears to deterime whether Shell will despawn after hittin a target, shell can have up to 4 HP
    u8 is_damage;     // Shell can damage players
    u8 is_setup_vars;
    u8 interact;     // Decremented each time the shell is attacked, reflected, or it hits something; despawns shell at 0
    f32 vel_x;

} Shell_ArticleVars;

typedef struct Taru_ArticleVars
{
    f32 roll_rotate_speed;

} Taru_ArticleVars;

typedef struct Bumper_ArticleVars
{
    u16 hit_anim_length;     // Number of frames "hit" animation lasts after bouncing off a target in midair
    u16 unk_0x2;
    u16 damage_all_delay;     // Bumper is able to hit its owner (and teammates?) once this timer runs out

} Bumper_ArticleVars;

typedef struct Gr_Lucky_ArticleVars
{
    Vec3f pos;
    u16 egg_spawn_wait;

} Gr_Lucky_ArticleVars;

typedef struct M_Ball_ArticleVars
{
    u16 is_rebound;     // Set to TRUE when Pok� Ball bounces back off a target
    GObj *owner_gobj;     // While Pok� Balls can be reflected, ownership is not transfered to the reflecting player; its original thrower remains its owner
    GObj *effect_gobj;     // Pok� Ball ray scatter GFX

} M_Ball_ArticleVars;

typedef struct Pakkun_ArticleVars
{
    Vec3f pos;
    u8 is_wait_fighter;     // TRUE if a fighter is occupying the pipe

} Pakkun_ArticleVars;

typedef struct Iwark_ArticleVars
{
    u16 rock_timer1;
    s32 rock_spawn_wait;     // Delay between rock projectiles
    u16 rock_timer2;
    u16 is_rumble;     // Not really a bool?
    u16 rumble_wait;
    u16 rock_spawn_count;     // Number of rocks to spawn?

} Iwark_ArticleVars;

typedef struct Kabigon_ArticleVars
{
    s32 dust_gfx_int;
    s32 rumble_wait;

} Kabigon_ArticleVars;

typedef struct Tosakinto_ArticleVars
{
    Vec3f pos;

} Tosakinto_ArticleVars;

typedef struct Mew_ArticleVars
{
    s32 esper_gfx_int;

} Mew_ArticleVars;

typedef struct Nyars_ArticleVars
{
    u16 coin_spawn_wait;
    u16 coin_rotate_step;
    u16 model_rotate_wait;

} Nyars_ArticleVars;

typedef struct Lizardon_ArticleVars
{
    Vec3f pos;
    u16 turn_wait;
    u16 flame_spawn_wait;

} Lizardon_ArticleVars;

typedef struct Spear_ArticleVars
{
    u16 spear_spawn_count;
    s32 spear_spawn_wait;
    f32 spear_spawn_pos_y;

} Spear_ArticleVars;

typedef struct Kamex_ArticleVars
{
    s32 hydro_spawn_wait;
    f32 hydro_push_vel_x;     // Added to Blastoise's velocity if is_apply_push is TRUE
    bool32 is_apply_push;     // Blastoise will be pushed forward after each Hydro Pump stream if enabled

} Kamex_ArticleVars;

typedef struct Mb_Lucky_ArticleVars
{
    u16 egg_spawn_wait;
    u16 lifetime;

} Mb_Lucky_ArticleVars;

typedef struct Starmie_ArticleVars
{
    s32 unk_0x0;
    s32 swift_spawn_wait;
    Vec3f target_pos;     // Position Starmie is set to travel when released from its Pok� Ball
    Vec3f victim_pos;     // Position of Starmie's selected victim
    f32 add_vel_x;

} Starmie_ArticleVars;

typedef struct Dogas_ArticleVars
{
    Vec3f pos;
    s32 smog_spawn_wait;

} Dogas_ArticleVars;

typedef struct Marumine_ArticleVars
{
    Vec3f offset;

} Marumine_ArticleVars;

typedef struct Porygon_ArticleVars
{
    Vec3f offset;

} Porygon_ArticleVars;

typedef struct Hitokage_ArticleVars
{
    Vec3f offset;
    u16 flags;
    u16 flame_spawn_wait;

} Hitokage_ArticleVars;

typedef struct Fushigibana_ArticleVars
{
    Vec3f offset;
    u16 flags;
    u16 razor_spawn_wait;

} Fushigibana_ArticleVars;

typedef struct Gr_Bomb_ArticleVars
{
    f32 roll_rotate_speed;

} Gr_Bomb_ArticleVars;

typedef struct PK_Fire_ArticleVars
{
    Effect_Info *effect;

} PK_Fire_ArticleVars;

typedef struct Link_Bomb_ArticleVars
{
    u16 unk_0x0;
    u16 unk_0x2;
    u16 scale_index;
    u16 scale_int; // Interval between Bomb inflate/deflate animation updates; effectively animation speed

} Link_Bomb_ArticleVars;

// Thought this might be a macro but it's not consistent

#define ArticleSetMonster(ap) \
    ap->at_multi = 22; \
    ap->phys_info.vel.z = 0.0F; \
    ap->phys_info.vel.x = 0.0F; \
    ap->phys_info.vel.y = 16.0F; \

#endif