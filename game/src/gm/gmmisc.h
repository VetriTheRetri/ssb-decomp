#ifndef _GMMISC_H_
#define _GMMISC_H_

// Data that is shared between different headers but does not really belong anywhere... yet

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define PERCENT_DAMAGE_MAX 999

#define LEFT -1
#define CENTER 0
#define RIGHT 1
#define WALL_UP 2               // Apparently a valid facing direction value used by Pikachu's Thunder Jolt?
#define WALL_DOWN 3             // Apparently a valid facing direction value used by Pikachu's Thunder Jolt?


#define GMHITCOLLISION_MASK_FIGHTER 1 // Can interact with fighters
#define GMHITCOLLISION_MASK_ITEM 2 // Can interact with items
#define GMHITCOLLISION_MASK_ARTICLE 4 // Can interact with articles


typedef enum gmHitCollisionStatus
{
    gmHitCollision_HitStatus_None, // User's hurtboxes are disabled
    gmHitCollision_HitStatus_Normal, // User can be hit
    gmHitCollision_HitStatus_Invincible, // User can be hit, but is immune to damage
    gmHitCollision_HitStatus_Intangible // User cannot be hit

} gmHitCollisionStatus;

typedef enum gmHitCollisionElement
{
    gmHitCollision_Element_Normal,
    gmHitCollision_Element_Fire // This continues but the rest is unconfirmed

} gmHitCollisionElement;

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

typedef union CommonAttackFlags
{
    struct
    {
        u16 flags_0x8000 : 1;
        u16 flags_0x4000 : 1;
        u16 flags_0x2000 : 1;
        u16 flags_0x1000 : 1;
        u16 flags_0x800 : 1;
        u16 flags_0x400 : 1;
        u16 flags_0x3FF : 10;
    };
    u16 halfword;

} CommonAttackFlags;

typedef struct FighterAttackFlags
{
    CommonAttackFlags hi;
    CommonAttackFlags lw;

} FighterAttackFlags;

typedef struct Color_Overlay
{
    void *p_script; // Pointer to Color Animation script?
    u16 color_event_timer;
    u16 unk_0x6;
    void *unk_0x8;
    s32 count;
    void *unk_0x10;
    void *unk_0x14;
    s32 unk_0x18;
    s32 unk_0x1C;
    s32 unk_0x20;
    s32 unk_0x24;
    s32 unk_0x28;
    s32 unk_0x2C;
    s32 unk_0x30;
    s32 unk_0x34;
    s32 unk_0x38;
    s32 colanim_id;
    u8 r, g, b, a; // RGBA
    
} Color_Overlay;

#endif