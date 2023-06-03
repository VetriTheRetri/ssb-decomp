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
    Gr_Kind_Explain, // How to Play
    Gr_Kind_Yoster1P, // Small Yoshi's Island 
    Gr_Kind_Crystal, // Meta Crystal
    Gr_Kind_Duel, // Duel Zone
    Gr_Kind_Bonus3, // Race to the Finish
    Gr_Kind_Last, // Final Destination

    Gr_Kind_TargetStart, // Start of Target Test stages
    Gr_Kind_Bonus1Mario = Gr_Kind_TargetStart,
    Gr_Kind_Bonus1Fox,
    Gr_Kind_Bonus1Donkey,
    Gr_Kind_Bonus1Samus,
    Gr_Kind_Bonus1Luigi,
    Gr_Kind_Bonus1Link,
    Gr_Kind_Bonus1Yoshi,
    Gr_Kind_Bonus1Captain,
    Gr_Kind_Bonus1Kirby,
    Gr_Kind_Bonus1Pikachu,
    Gr_Kind_Bonus1Purin,
    Gr_Kind_Bonus1Ness,

    Gr_Kind_PlatformStart, // Start of Board the Platforms stages
    Gr_Kind_Bonus2Mario = Gr_Kind_PlatformStart,
    Gr_Kind_Bonus2Fox,
    Gr_Kind_Bonus2Donkey,
    Gr_Kind_Bonus2Samus,
    Gr_Kind_Bonus2Luigi,
    Gr_Kind_Bonus2Link,
    Gr_Kind_Bonus2Yoshi,
    Gr_Kind_Bonus2Captain,
    Gr_kind_Bonus2Kirby,
    Gr_Kind_Bonus2Pikachu,
    Gr_Kind_Bonus2Purin,
    Gr_Kind_Bonus2Ness,

    Gr_Kind_CustomStart // Start of custom stages

} grKind;

typedef enum grMaterial
{
    Gr_Mat_0,
    Gr_Mat_1,
    Gr_Mat_2,
    Gr_Mat_3,
    Gr_Mat_4,
    Gr_Mat_5,
    Gr_Mat_6,
    Gr_Mat_FireWeakHz1,
    Gr_Mat_FireStrongVt1,
    Gr_Mat_FireWeakVt1,
    Gr_Mat_SpikeStrongHz1,
    Gr_Mat_FireWeakVt2,
    Gr_Mat_Dokan1,
    Gr_Mat_Dokan2,
    Gr_Mat_Detect, // Board the Platforms / Race to the Finish gate
    Gr_Mat_FireWeakVt3,
    Gr_Mat_Custom

} grMaterial;



typedef struct _Ground_Hit
{
    s32 env_kind; // Not actually UpdateState, no idea what this is; something to do with sound effects?
    s32 damage;
    s32 angle;
    s32 knockback_scale;
    s32 knockback_weight;
    s32 knockback_base;
    s32 element;

} Ground_Hit;

typedef struct grMapObject
{
    GObj *ogobj;
    bool32 (*proc_update)(GObj*, GObj*, s32*);

} grMapObject;

typedef struct grMapEnvironment
{
    GObj *egobj;
    bool32 (*proc_update)(GObj*, GObj*, Ground_Hit*, s32*);

} grMapEnvironment;

static grMapObject D_ovl2_80131180[2];
static grMapEnvironment D_ovl2_80131190[1];
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
