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
    GObj *room_gobj_next; // Unconfirmed, might be int
    GObj *room_gobj_prev; // Unconfirmed, might be int
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

#ifndef Mtx_t

typedef long	Mtx_t[4][4];

#endif

#ifndef Mtx

typedef union {
    Mtx_t		m;
    long long int	force_structure_alignment;
} Mtx;

#endif 

typedef struct OMMtx OMMtx;

struct OMMtx {
    /* 0x00 */ struct OMMtx *next;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x08 */ Mtx unk08;
    ///* 0x08 */ f32 unk08[4][4];
    ///* 0x08 */ f32 (*unk08)[4][4];
    ///* 0x0C */ u8 pad0C[0x48 - 0xc];
}; // size == 0x48

typedef struct MObj // Image footer struct
{
    u8 filler[0x80];
    s16 index;
    f32 unk_0x84;
    f32 anim_frame; // Current frame of texture animation
    u8 filler_0x8C[0x94 - 0x8C];
    u32 unk_mobj_0x94;
    f32 unk_mobj_0x98;

} MObj;

typedef struct UnkDObjData
{
    u8 filler_0x0[0xc];
    u8 unk_0xC;
    u8 unk_0xD;
    u8 filler_0xE[0xDC - 0xE];
    GObj *unk_gobj;

} UnkDObjData;

typedef struct DObj DObj;

struct DObj
{
    u8 filler_0x0[0x8];
    DObj *unk_0x8;
    DObj *unk_0xC;
    DObj *next;
    DObj *prev;
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
    OMMtx *unk58[5];
    void *aobj;
    s32 unk_dobj_0x70;
    f32 unk_dobj_0x74; // Multi-purpose? Usually FLOAT32_MAX, used as rotation step in Crate/Barrel smash GFX?
    f32 unk_dobj_0x78; // Multi-purpose? Fighters use this as animation playback rate, but it is used as rotation step in Crate/Barrel smash GFX?
    f32 unk_dobj_0x7C; // Multi-purpose? Usually animation frame, but used as rotation step in Crate/Barrel smash GFX?
    MObj *mobj;
    void *unk_0x84;    // Multi-purpose? Articles store a fighter joint here, but func_ovl2_800D78E8 expects a different struct
};

typedef struct DObjDesc
{
    s32 index;
    void *x4;
    Vec3f translate;
    Vec3f rotate;
    Vec3f scale;

} DObjDesc;

#define DObjGetStruct(gobj) \
((DObj*)gobj->obj) \

#endif