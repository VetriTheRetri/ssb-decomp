#ifndef _GROUND_H_
#define _GROUND_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

struct gmGroundInfo_80131300
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
    s32 unk_0x4C;
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
};

static struct gmGroundInfo_80131300 *D_ovl2_80131300; // TO DO: move this to the correct file

#endif
