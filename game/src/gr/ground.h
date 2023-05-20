#ifndef _GROUND_H_
#define _GROUND_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/sys/obj_renderer.h>

typedef enum grKind
{
    Gr_Kind_Castle, // Peach's Castle
    Gr_Kind_Sector,
    Gr_Kind_Jungle,
    Gr_Kind_Zebes,
    Gr_Kind_Hyrule,
    Gr_Kind_Yoster, // Yoshi's Island
    Gr_Kind_Pupupu, // Dream Land
    Gr_Kind_Yamabuki, // Saffron City
    Gr_Kind_Inishie, // Mushroom Kingdom
    Gr_Kind_PPPTest1,
    Gr_Kind_PPPTest2,
    Gr_Kind_Demo, // How to Play
    Gr_Kind_Yoster1P, // Small Yoshi's Island 
    Gr_Kind_Crystal, // Meta Crystal
    Gr_Kind_Duel, // Duel Zone
    Gr_Kind_Pushon, // Race to the Finish
    Gr_Kind_Last, // Final Destination

    Gr_Kind_TargetStart, // Start of Target Test stages
    Gr_Kind_TMario = Gr_Kind_TargetStart,
    Gr_Kind_TFox,
    Gr_Kind_TDonkey,
    Gr_Kind_TSamus,
    Gr_Kind_TLuigi,
    Gr_Kind_TLink,
    Gr_Kind_TYoshi,
    Gr_Kind_TCaptain,
    Gr_Kind_TKirby,
    Gr_Kind_TPikachu,
    Gr_Kind_TPurin,
    Gr_Kind_TNess,

    Gr_Kind_PlatformStart, // Start of Board the Platforms stages
    Gr_Kind_PMario = Gr_Kind_PlatformStart,
    Gr_Kind_PFox,
    Gr_Kind_PDonkey,
    Gr_Kind_PSamus,
    Gr_Kind_PLuigi,
    Gr_Kind_PLink,
    Gr_Kind_PYoshi,
    Gr_Kind_PCaptain,
    Gr_kind_PKirby,
    Gr_Kind_PPikachu,
    Gr_Kind_PPurin,
    Gr_Kind_PNess, // Please don't laugh

    Gr_Kind_CustomStart // Start of custom stages

} grKind;

typedef struct grMapObject
{
    GObj *ogobj;
    bool32 (*proc_update)(GObj*, GObj*, s32*);

} grMapObject;

typedef struct _Ground_Hit
{
    s32 update_state; // Not actually UpdateState, no idea what this is; something to do with sound effects?
    s32 damage;
    s32 angle;
    s32 knockback_scale;
    s32 knockback_weight;
    s32 knockback_base;
    s32 element;

} Ground_Hit;

static grMapObject D_ovl2_80131180[2];
static grMapObject D_ovl2_80131190[1];
static s32 D_ovl2_80131198;
static s32 D_ovl2_8013119C;

/*

struct Ground_Info_80131300
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
};

static struct Ground_Info_80131300 *Ground_Info; // TO DO: move this to the correct file

*/

#endif
