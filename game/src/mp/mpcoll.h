#ifndef _MPCOLL_H_
#define _MPCOLL_H_

#include <PR/ultratypes.h>
#include <ssb_types.h>
#include <macros.h>

#define MPCOLL_MASK_RWALL 0x1
#define MPCOLL_MASK_LWALL 0x20
#define MPCOLL_MASK_CEIL 0x400
#define MPCOLL_MASK_GROUND 0x800

typedef enum gmHitCollision // Hitbox types, this is universal but I don't know where else to put it so both fighters and items can see it without redefining it for each
{
    gmHitCollision_Hurt,
    gmHitCollision_Shield,
    gmHitCollision_Hit = 0x3,
    gmHitCollision_Absorb = 0x5,
    gmHitCollision_Reflect

} gmHitCollision;

typedef enum Ground_Air
{
    ground,
    air

} Ground_Air;

typedef struct _ObjectColl
{
    f32 top;
    f32 center;
    f32 bottom;
    f32 width;

} ObjectColl;

typedef struct _Coll_Data
{
    Vec3f *p_pos; // Points to TopN translation vector
    s32 *p_lr; // Points to facing direction?
    Vec3f pos_curr;
    Vec3f pos_correct; // Unconfirmed
    Vec3f pos_prev; // Unconfirmed
    Vec3f pos_project; // Unconfirmed
    ObjectColl object_coll;
    void *p_object_coll; // Points back to collision box???
    Vec2f unk_0x4C;
    u16 unk_0x54;
    u16 unk_0x56;
    u16 unk_0x58;
    u16 coll_type; // "Flag that relates to type of clipping?"
    u16 wall_flag; // "Flag is enabled if moving into a wall"
    u16 unk_0x60;
    u16 unk_0x62;
    bool32 unk_0x64;
    Vec3f ground_to_air_pos_last;

    s32 ground_line_id;
    f32 unk_0x78; // "Clipping / Platform ID directly under character"
    u32 clip_flag; // "Distance of platform directly under character"        u32 ground_flag; // "Clipping flag of platform directly under character"
    Vec3f ground_angle;

    s32 ceil_line_id; // Clipping ID of last ceiling interacted with
    s32 ceil_material;
    Vec3f ceil_angle;

    s32 rwall_line_id; // Clipping ID of last right wall interacted with
    s32 rwall_material;
    Vec3f rwall_angle;

    s32 lwall_line_id;
    s32 lwall_material;
    Vec3f lwall_angle;

    // Most of this is unconfirmed

    s32 unk_var;
    s32 object_var; // Might be the same as 0x19C from Melee?

} Coll_Data;

#endif