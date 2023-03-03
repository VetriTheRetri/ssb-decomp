#ifndef _GMMISC_H_
#define _GMMISC_H_

// Data that is shared between different headers but does not really belong anywhere... yet

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define LEFT -1
#define CENTER 0
#define RIGHT 1
#define WALL_UP 2               // Apparently a valid facing direction value used by Pikachu's Thunder Jolt?
#define WALL_DOWN 3             // Apparently a valid facing direction value used by Pikachu's Thunder Jolt?

typedef enum gmHitCollisionStatus
{
    gmHitCollision_Status_None, // User's hurtboxes are disabled
    gmHitCollision_Status_Normal, // User can be hit
    gmHitCollision_Status_Invincible, // User can be hit, but is immune to damage
    gmHitCollision_Status_Intangible // User cannot be hit

} gmHitCollisionStatus;

typedef enum gmHitCollisionType // Hitbox types, this is universal but I don't know where else to put it so both fighters and items can see it without redefining it for each
{
    gmHitCollision_Type_Hurt,
    gmHitCollision_Type_Shield,
    gmHitCollision_Type_Unk,
    gmHitCollision_Type_Hit,
    gmHitCollision_Type_ArticleHurt,             // Only used for specific articles? e.g. Pirahna Plants dealing damage
    gmHitCollision_Type_Absorb,
    gmHitCollision_Type_Reflect

} gmHitCollisionType;

typedef enum gmHitCollisionUpdateState
{
    gmHitCollision_UpdateState_Disable,          // No active hitbox or updates
    gmHitCollision_UpdateState_New,              // Initialize hitbox positions
    gmHitCollision_UpdateState_Transfer,         // Transitions to interpolation mode, that's it
    gmHitCollision_UpdateState_Interpolate       // Copies current position to previous

} gmHitCollisionUpdateState;

typedef struct CommonAttackFlagsHi
{
    u16 flags_hi_b0 : 1;
    u16 flags_hi_b1 : 1;
    u16 flags_hi_b2 : 1;
    u16 flags_hi_b3 : 1;
    u16 flags_hi_b4 : 1;
    u16 flags_hi_b5 : 1;
    u16 flags_hi_0x3FF : 10;

} CommonAttackFlagsHi;

typedef struct CommonAttackFlagsLw
{
    u16 flags_lw_0x8000 : 1;
    u16 flags_lw_0x4000 : 1;
    u16 flags_lw_0x2000 : 1;
    u16 flags_lw_0x1000 : 1;
    u16 flags_lw_0x800 : 1;
    u16 flags_lw_0x400 : 1;
    u16 flags_lw_0x3FF : 10;

} CommonAttackFlagsLw;

typedef struct FighterAttackFlags
{
    CommonAttackFlagsHi hi;
    CommonAttackFlagsLw lw;

} FighterAttackFlags;

#endif