#ifndef _MPCOLL_H_
#define _MPCOLL_H_

#include <PR/ultratypes.h>
#include <ssb_types.h>
#include <macros.h>

#define MPCOLL_MASK_RWALL   (1 << 0)
#define MPCOLL_MASK_LWALL   (1 << 5)
#define MPCOLL_MASK_CEIL    (1 << 10)
#define MPCOLL_MASK_GROUND  (1 << 11)
#define MPCOLL_MASK_LCLIFF  (1 << 12)
#define MPCOLL_MASK_RCLIFF  (1 << 13)

#define MPCOLL_MASK_ALL     (MPCOLL_MASK_GROUND | MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL) // Mask every main collision flag

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
    Vec3f *p_translate; // Points to TopN translation vector
    s32 *p_lr; // Points to facing direction?
    Vec3f pos_curr;
    Vec3f pos_correct; // Unconfirmed
    Vec3f pos_prev; // Unconfirmed
    Vec3f pos_project; // Unconfirmed
    ObjectColl object_coll;
    void *p_object_coll; // Points back to collision box???
    Vec2f cliffcatch_coll;
    u16 unk_0x54;
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

    s32 rwall_line_id; // Clipping ID of last right wall interacted with
    u32 rwall_flags;
    Vec3f rwall_angle;

    s32 lwall_line_id;
    u32 lwall_flags;
    Vec3f lwall_angle;

    s32 cliff_id; // Ledge ID
    s32 ignore_line_id; // Ignore this line when checking for collision

} Coll_Data;

#endif