#ifndef _MPCOLL_H_
#define _MPCOLL_H_

#include <PR/ultratypes.h>
#include <ssb_types.h>
#include <macros.h>

#define MPCOLL_MASK_RWALL 0x1
#define MPCOLL_MASK_LWALL 0x20
#define MPCOLL_MASK_CEIL 0x400
#define MPCOLL_MASK_GROUND 0x800

typedef enum Ground_Air
{
    ground,
    air

} Ground_Air;

typedef struct _ObjectColl
{
    f32 top_y;
    f32 center_y;
    f32 bottom_y;
    f32 width;

} ObjectColl;

typedef struct _Coll_Data
{
    void *unk_0x0;
    void *unk_0x4;
    void *unk_0x8;
    Vec3f unk_0xC;
    Vec3f pos; // 0x8C
    Vec3f unk_0x24; // 0x94 - 0xA0;
    Vec3f unk_0x30; // Wind speed
    ObjectColl coll_box;
    void *p_coll_box; // Points back to collision box???
    u16 unk_0x50;
    u16 unk_0x52;
    u16 unk_0x54;
    u16 unk_0x56;
    u16 unk_0x58;
    u16 coll_type; // "Flag that relates to type of clipping?"
    u16 wall_flag; // "Flag is enabled if moving into a wall"
    u16 unk_0x60;
    u16 unk_0x62;
    u32 unk_0x64;
    u32 unk_0x68;
    Vec2f ground_to_air_pos_last;

    s32 unk_0x74;
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