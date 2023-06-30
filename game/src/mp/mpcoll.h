#ifndef _MPCOLL_H_
#define _MPCOLL_H_

#include <PR/ultratypes.h>
#include <ssb_types.h>
#include <macros.h>

#define MPCOLL_MASK_LWALL       (1 << 0)    // 0x1
#define MPCOLL_MASK_RWALL       (1 << 5)    // 0x20
#define MPCOLL_MASK_CEIL        (1 << 10)   // 0x400 
#define MPCOLL_MASK_GROUND      (1 << 11)   // 0x800
#define MPCOLL_MASK_LCLIFF      (1 << 12)   // 0x1000
#define MPCOLL_MASK_RCLIFF      (1 << 13)   // 0x2000
#define MPCOLL_MASK_CEILHEAVY   (1 << 14)   // 0x4000 - head bonk?
#define MPCOLL_MASK_UNK1        (1 << 15)   // 0x8000

#define MPCOLL_MASK_MAIN_ALL    (MPCOLL_MASK_GROUND | MPCOLL_MASK_CEIL | MPCOLL_MASK_RWALL | MPCOLL_MASK_LWALL) // Mask every main collision flag
#define MPCOLL_MASK_CLIFF_ALL   (MPCOLL_MASK_LCLIFF | MPCOLL_MASK_RCLIFF) // Mask all ledge flags       

#define MPCOLL_MASK_NONSOLID    (1 << 14) // Line ID can be passed through

typedef enum mpGroundAir
{
    GA_Ground,
    GA_Air

} mpGroundAir;

typedef struct CollisionGroupInfo
{
    u8 filler_0x0[0x1C];
    Vec3f dynacoll_pos;
    u8 filler_0x28[0x70 - 0x28];
    void *p_dynacoll;
    u8 filler_0x74[0x84 - 0x74];
    s32 collision_kind;

} CollisionGroupInfo;

typedef struct CollisionVertexInfo
{
    u8 coll_group_id;
    u8 coll_vertex_id;
    s16 coll_pos_next;
    s16 coll_pos_prev;
    s16 coll_type_next;
    s16 coll_type_prev;

} CollisionVertexInfo;

typedef struct CollisionVertexLinks
{
    u16 vertex1, vertex2;

} CollisionVertexLinks;

typedef struct CollisionVertexArray
{
    u16 unk_vertex[1];

} CollisionVertexArray;

typedef struct CollisionVertexPosition
{
    Vec2h pos;
    u16 unk_0x4;

} CollisionVertexPosition;

typedef struct CollisionVtxPosContainer
{
    CollisionVertexPosition vpos[1];

} CollisionVtxPosContainer;

typedef struct _ObjectColl
{
    f32 top;
    f32 center;
    f32 bottom;
    f32 width;

} ObjectColl;

typedef struct _Coll_Data
{
    Vec3f *p_translate; // Points to TopN translation vector
    s32 *p_lr; // Points to facing direction?
    Vec3f pos_curr;
    Vec3f pos_correct; // Unconfirmed
    Vec3f pos_prev; // Unconfirmed
    Vec3f vel_push; // Applied from extern stage objects such as Whispy's Wind?
    ObjectColl object_coll;
    ObjectColl *p_object_coll; // Points back to collision box???
    Vec2f cliffcatch_coll;
    u16 coll_mask_prev;
    u16 coll_mask;
    u16 unk_0x58;
    u16 coll_type; // "Flag that relates to type of clipping?"
    u16 wall_flag; // "Flag is enabled if moving into a wall"
    s32 unk_0x60;
    bool32 unk_0x64;
    Vec3f ground_to_air_pos_last;

    s32 ground_line_id;
    f32 ground_dist; // Distance to nearest ground line? 
    u32 ground_flags; // Line collision behavior (e.g. drop-through)
    Vec3f ground_angle;

    s32 ceil_line_id; // Clipping ID of last ceiling interacted with
    u32 ceil_flags;
    Vec3f ceil_angle;

    s32 lwall_line_id; // Clipping ID of last left wall interacted with
    u32 lwall_flags;
    Vec3f lwall_angle;

    s32 rwall_line_id;
    u32 rwall_flags;
    Vec3f rwall_angle;

    s32 cliff_id; // Ledge ID
    s32 ignore_line_id; // Ignore this line when checking for collision

} Coll_Data;

#endif