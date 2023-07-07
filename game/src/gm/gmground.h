#ifndef _GMGROUND_H_
#define _GMGROUND_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/sys/obj_renderer.h>

typedef  struct gmGroundUnkBytes
{
    u8 byte[1]; // Size currently unknown

} gmGroundUnkBytes;

typedef struct gmGroundInfo
{
    void *unk_0x0;
    void *unk_0x4;
    void *unk_0x8;
    void *unk_0xC;
    void *unk_0x10;
    void *unk_0x14;
    void *unk_0x18;
    void *unk_0x1C;
    void *unk_0x20;
    void *unk_0x24;
    void *unk_0x28;
    void *unk_0x2C;
    void *unk_0x30;
    void *unk_0x34;
    void *unk_0x38;
    void *unk_0x3C;
    void *unk_0x40;
    void *unk_0x44;
    void *unk_0x48;
    GfxColorAlpha fog_color;
    s32 unk_0x50;
    s32 unk_0x54;
    s32 unk_0x58;
    s32 unk_0x5C;
    f32 unk_0x60;
    f32 unk_0x64;
    f32 unk_0x68;
    s16 cam_bound_top;
    s16 cam_bound_bottom;
    s16 cam_bound_right;
    s16 cam_bound_left;
    s16 blastzone_top;
    s16 blastzone_bottom;
    s16 blastzone_right;
    s16 blastzone_left;
    u32 unk_0x7C;
    u32 unk_0x80;
    gmGroundUnkBytes *unk_0x84;
    s16 unk_groundinfo_0x88;
    s16 unk_groundinfo_0x8A;
    u8 filler_0x88[0x92 - 0x8C];
    s16 unk_bound_top;
    s16 unk_bound_bottom;
    s16 unk_bound_right;
    s16 unk_bound_left;

} gmGroundInfo;

static gmGroundInfo *gpMapData; // TO DO: move this to the correct file

#endif