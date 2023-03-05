#ifndef _OBJ_H_
#define _OBJ_H_

#include <PR/ultratypes.h>
#include <ssb_types.h>
#include <macros.h>

typedef enum GObjLinkIndex
{
    GObjLinkIndex_Fighter = 0x3,
    GObjLinkIndex_Article,
    GObjLinkIndex_Item

} GObjLinkIndex;

typedef f32 mtx[3][4];

typedef struct GObj GObj;

struct GObj
{
    // Info here acquired from halofactory of the Smash Remix team
    s32 unk_info; // arbitrary ID signifying related objects? e.g. 0x000003F8
    GObj *group_gobj_next;
    GObj *group_gobj_prev;
    u8 group;
    u8 room;
    u8 asynchronous_timer; // For subaction events?
    u8 unk_0xF;
    s32 group_order; // Might be room?
    void *call_unk;
    s32 unk_0x18;
    s32 unk_0x1C;
    GObj *room_gobj_next;
    GObj *room_gobj_prev;
    s32 room_order; // Might be group? Assuming room based on order here
    void (*renderer)(GObj *gobj);
    s32 unk_0x30;
    s32 unk_0x34;
    s32 unk_0x38; // 0xFFFFFFFF, textures or series of flags?
    u8 filler_0x3C[0x74 - 0x3C];
    void *obj;
    f32 anim_frame; // Current frame of animation?
    bool32 is_render;
    u32 unk_0x80;
    void *user_data;

};

extern GObj *gOMObjCommonLinks[];

typedef struct _Image // Image footer struct
{
    u8 filler[0x80];
    s16 index;
    f32 unk_0x84;
    f32 anim_frame; // Current frame of texture animation

} Image;

typedef struct JObj JObj;

struct JObj
{
    u8 filler_0x0[0x8];
    JObj *unk_0x8;
    JObj *unk_0xC;
    JObj *next;
    JObj *prev;
    mtx *mtx_translate; // 0x18
    Vec3f translate; // 0x1C - 0x24
    mtx *mtx_rotate; // 0x28
    s32 unk_0x2C;
    Vec3f rotate; // 0x30 - 0x3C
    s32 unk_0x3C;
    Vec3f scale; // 0x40 - 0x48
    s32 unk_0x4C;
    void *display_list;
    u8 unk_0x54;
    void *mtx_position; // ???
    u8 filler_0x5C[0x78 - 0x5C];
    f32 anim_rate;
    f32 unk_0x7C;
    Image *image;

};

typedef struct JObjDesc
{
    s32 index;
    void *x4;
    Vec3f translate;
    Vec3f rotate;
    Vec3f scale;

} JObjDesc;

#define JObjGetStruct(gobj) \
((JObj*)gobj->obj) \

#endif