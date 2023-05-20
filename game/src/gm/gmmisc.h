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

#define GMCOMPLAYER_LEVEL_MAX 9

#define GMHITCOLLISION_MASK_FIGHTER (1 << 0) // Can interact with fighters
#define GMHITCOLLISION_MASK_ITEM    (1 << 1) // Can interact with items
#define GMHITCOLLISION_MASK_ARTICLE (1 << 2) // Can interact with articles

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
    gmHitCollision_Element_Fire,
    gmHitCollision_Element_Electric,
    gmHitCollision_Element_Slash,
    gmHitCollision_Element_Coin,
    gmHitCollision_Element_Unk1,
    gmHitCollision_Element_Sleep,
    gmHitCollision_Element_Unk2

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

typedef enum gmHitCollisionSoundEffect
{
    gmHitCollision_SoundEffect_Punch,
    gmHitCollision_SoundEffect_Kick,
    gmHitCollision_SoundEffect_Coin,
    gmHitCollision_SoundEffect_Burn,
    gmHitCollision_SoundEffect_Zap,
    gmHitCollision_SoundEffect_Slash,
    gmHitCollision_SoundEffect_Fan,
    gmHitCollision_SoundEffect_Bat,
    gmHitCollision_SoundEffect_EnumMax

} gmHitCollisionSoundEffect;

typedef enum gmHitCollisionSoundLevel
{
    gmHitCollision_SoundLevel_Weak,
    gmHitCollision_SoundLevel_Mid,
    gmHitCollision_SoundLevel_Strong,
    gmHitCollision_SoundLevel_EnumMax

} gmHitCollisionSoundLevel;

typedef enum ftHitCollisionLogKind
{
    ftHitCollision_LogKind_Fighter = 1,
    ftHitCollision_LogKind_Item,
    ftHitCollision_LogKind_Article,
    ftHitCollision_LogKind_Special

} ftHitCollisionLogKind;

typedef struct gmHitCollisionFlags
{
    u32 is_interact_hurt : 1;
    u32 is_interact_shield : 1;
    u32 is_interact_reflect : 1;
    u32 is_interact_absorb : 1;
    u32 interact_mask : 3;
    u32 timer_rehit : 6;

} gmHitCollisionFlags;

typedef struct gmPlayerInput
{
    u16 button_hold;
    u16 button_tap;
    u16 button_tap_prev;
    Vec2b stick_range;
    Vec2b stick_prev; // Previous stick range?

} gmPlayerInput;

typedef struct gmComputerInput
{
    u16 button_inputs;
    Vec2b stick_range; // CPU stick input?

} gmComputerInput;

typedef union gmAttackFlags
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

} gmAttackFlags;

typedef struct FighterAttackFlags
{
    gmAttackFlags hi;
    gmAttackFlags lw;

} FighterAttackFlags;

typedef struct Color_Script
{
    u32 *p_script; // Pointer to Color Animation script?
    u16 color_event_timer;
    u16 script_index;
    void *p_subroutine[1];
    s32 loop_count[1];
    void *p_goto[2];
    s32 unk_ca_timer;

} Color_Script;

typedef struct Color_Info
{
    u8 r, g, b, a;
    s16 ir, ig, ib, ia; // Interpolation step

} Color_Info;

typedef struct Color_Overlay
{
    Color_Script cs[2];
    s32 duration;
    s32 colanim_id;
    Color_Info color1;
    f32 light_angle1;
    f32 light_angle2;
    Color_Info color2;
    u8 is_use_color1 : 1;
    u8 is_use_light : 1;
    u8 is_use_color2 : 1;
    u8 unk_ca_0x60_b34 : 2;

} Color_Overlay;

#endif