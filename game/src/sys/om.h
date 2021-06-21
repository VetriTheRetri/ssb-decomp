#ifndef SYS_OM_H
#define SYS_OM_H

#include <ssb_types.h>

#include <PR/mbi.h>
#include <PR/os.h>
#include <PR/ultratypes.h>

// Object Manager (OM) Objects

struct GObjThread {
    /* 0x000 */ struct GObjThread *next;
    /* 0x008 */ OSThread osThread;
    /* 0x1B8 */ u64 *osStack;
    /* 0x1BC */ u32 stackSize;
}; // size == 0x1C0

/// This is the node for the allocated stack for a `struct GObjThread`
struct ThreadStackNode {
    /* 0x00 */ struct ThreadStackNode *next;
    /* 0x04 */ u32 stackSize;
    /* 0x08 */ u64 stack[1];
}; // size == 0x08 + VLA

struct MaybeCommonLink {
    struct GObjCommon *unk00;
    s32 unk04;
}; // size == 8

struct GObjCommon {
    /* 0x00 */ u32 unk00; // id
    /* 0x04 */ struct GObjCommon *unk04;
    /* 0x08 */ struct GObjCommon *unk08;
    /* 0x0C */ u8 unk0C; // link
    /* 0x0D */ u8 unk0D; // dl link
    /* 0x0E */ u8 unk0E;
    /* 0x0F */ u8 unk0F; // ptr kind?
    /* 0x10 */ u32 unk10;
    /* 0x14 */ void (*unk14)(void);
    /* 0x18 */ struct GObjProcess *unk18;
    /* 0x1C */ struct GObjProcess *unk1C;
    /* 0x20 */ struct GObjCommon *unk20;
    /* 0x24 */ struct GObjCommon *unk24;
    /* 0x28 */ u32 unk28;
    /* 0x2C */ void (*unk2C)(struct GObjCommon *);
    /* 0x30 */ s64 unk30;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ s64 unk40;
    /* 0x48 */ struct MaybeCommonLink unk48[5];
    // active/len of unk48
    /* 0x70 */ s32 unk70;
    // typed based on unk0F?
    // 0 : NULL
    // 1 : DObj
    // 2 : SObj
    // 3 : OMCamera
    /* 0x74 */ void *unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ void *unk84;
}; // size >= 0x88

struct GObjProcess {
    /* 0x00 */ struct GObjProcess *unk00;
    /* 0x04 */ struct GObjProcess *unk04;
    /* 0x08 */ struct GObjProcess *unk08;
    /* 0x08 */ struct GObjProcess *unk0C;
    /* 0x10 */ s32 unk10; // priority
    /* 0x14 */ u8 unk14;  // kind
    /* 0x15 */ u8 unk15;
    /* 0x18 */ struct GObjCommon *unk18;
    // following two fields are typed via unk14 / kind
    /* 0x1C */ union {
        struct GObjThread *thread;
        void (*cb)(struct GObjCommon *);
    } unk1C;
    /* 0x20 */ void *unk20;
}; // size == 0x24

struct OMMtx {
    /* 0x00 */ struct OMMtx *next;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x08 */ u32 pad08;
    /* 0x0C */ u8 pad0C[0x48 - 0xc];
}; // size == 0x48

// this is a guess, it could be something else
struct Vec3i {
    s32 x, y, z;
};

struct Vec3f {
    f32 x, y, z;
};

struct Mtx3Float {
    /* 0x00 */ struct OMMtx *mtx;
    /* 0x04 */ struct Vec3f v;
}; // size == 0x10

struct Mtx3Int {
    /* 0x00 */ struct OMMtx *mtx;
    /* 0x04 */ struct Vec3i v;
}; // size == 0x10

// or are the 3-vecs a union?
union Mtx3fi {
    struct Mtx3Float f;
    struct Mtx3Int i;
}; // size == 0x10

struct Mtx4Float {
    /* 0x00 */ struct OMMtx *mtx;
    /* 0x04 */ f32 f[4];
}; // size == 0x14

struct Mtx6Float {
    /* 0x00 */ struct OMMtx *mtx;
    /* 0x04 */ f32 f[6];
}; // size == 0x1C

struct Mtx7Float {
    /* 0x00 */ struct OMMtx *mtx;
    /* 0x04 */ f32 f[7];
}; // size == 0x20

struct Mtx3x3Float {
    struct OMMtx *mtx;
    f32 array[3][3];
}; // size == 0x28;

/// This stores up to 3 `Mtx3Int`/`Mtx3Float`/`Mtx4Float` structures in the VLA data
/// based on the kind id in the `kinds` arrays:
/// Kind 1 - `struct Mtx3Int` or `union Mtx3fi`
/// Kind 2 - `struct Mtx4Float`
/// Kind 3 - `struct Mtx3Float`
struct DObjDynamicStore {
    /* 0x00 */ u8 kinds[3];
    /* 0x04 */ u8 data[1];
}; // size == 4 + VLA

struct DObj {
    /* 0x00 */ struct DObj *unk0;
    /* 0x04 */ struct GObjCommon *unk4;
    /* 0x08 */ struct DObj *unk8;
    /* 0x0C */ struct DObj *unkC;
    /* 0x10 */ struct DObj *unk10;
    /* 0x14 */ uintptr_t unk14; //< `1` or `struct DObj *`
    /* 0x18 */ union Mtx3fi unk18;
    /* 0x28 */ struct Mtx4Float unk28;
    /* 0x3C */ struct Mtx3Float unk3C;
    /* 0x4C */ struct DObjDynamicStore *unk4C;
    /* 0x50 */ s32 unk50;
    // is this a union? WeirdBytewise...?
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 unk55;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 unk57;
    /* 0x58 */ struct OMMtx *unk58[5];
    /* 0x6C */ struct AObj *unk6C;
    // some sort of union struct for the animation `union {u32 u; f32 f;}`?
    /* 0x70 */ u32 *unk70;
    // Vec3fi?
    /* 0x74 */ f32 unk74; // scale? only in OMAnimation
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ struct MObj *unk80;
    /* 0x84 */ u32 unk84;
}; // size == 0x88, but it's dynamic..?

struct AObj {
    /* 0x00 */ struct AObj *next;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
}; // size == 0x24

// how is this struct related to DObj? 
struct OMAnimation {
    /* 0x00 */ struct DObj dobj;
    // does this start with a DObj (to 0x88)?
    // /* 0x00 */ u8 pad00[0x6C - 0];
    // /* 0x6C */ struct AObj *unk6C;
    // /* 0x70 */ u8 pad70[0x74 - 0x70];
    // /* 0x74 */ f32 unk74; // scale?
    // /* 0x78 */ u8 pad78[0x90 - 0x78];
    /* 0x88 */ u8 pad88[8];
    /* 0x90 */ struct AObj *unk90;
    // is this another pointer to the animation union?
    /* 0x94 */ u32 *unk94;
    /* 0x98 */ f32 unk98;
    /* 0x9C */ f32 unk9C;
    /* 0xA0 */ f32 unkA0;
}; // size >= 0xA4

// texture scroll? (from K64)
struct MObjSub {
    /* 0x00 */ u8 pad00[0x14 - 0];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u32 pad18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u32 pad20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u8 pad2C[0x54 - 0x2C];
    /* 0x54 */ u8 unk54;
    /* 0x58 */ u8 pad58[0x78 - 0x58];
}; // size == 0x78

struct MObj {
    /* 0x00 */ struct MObj *next;
    /* 0x04 */ u32 pad04;
    /* 0x08 */ struct MObjSub unk08;
    /* 0x80 */ u16 unk80;
    /* 0x82 */ u16 unk82;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ u32 pad8C;
    /* 0x90 */ struct AObj *unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ f32 unk98;
    /* 0x9C */ f32 unk9C;
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ u32 padA4;
}; // size = 0xA8

struct SObjSub10 {
    /* 0x00 */ u32 pad00;
    /* 0x04 */ u8 pad04[0x44 - 0x04];
}; // size == 0x44

struct SObj {
    /* 0x00 */ struct SObj *next;
    /* 0x04 */ struct GObjCommon *unk04;
    /* 0x08 */ struct SObj *unk08;
    /* 0x0C */ struct SObj *unk0C;
    /* 0x10 */ struct SObjSub10 unk10;
    /* 0x54 */ s32 unk54;
}; // size >= 0x58

struct OMCamera {
    /* 0x00 */ struct OMCamera *next;
    /* 0x04 */ struct GObjCommon *unk04;
    /* 0x08 */ Vp unk08;
    /* 0x18 */ union {
        struct Mtx6Float f6;
        struct Mtx7Float f7;
    } unk18;
    /* 0x38 */ struct Mtx3x3Float unk38;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ struct OMMtx *unk64[2];
    /* 0x6C */ struct AObj *unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s32 unk8C;
}; // size >= 0x90

// replace `struct TempUnkA6E0` with this
// and replace raw struct sizes in `func_8000683C`
struct OMSetup {
    /* 0x00 */ struct GObjThread *threads;
    /* 0x04 */ s32 numThreads;
    /* 0x08 */ u32 threadStackSize;
    /* 0x0C */ struct ThreadStackNode *stacks;
    /* 0x10 */ u32 numStacks;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ struct GObjProcess *processes;
    /* 0x1C */ s32 numProcesses;
    /* 0x20 */ struct GObjCommon *commons;
    /* 0x24 */ s32 numCommons;
    /* 0x28 */ s32 commonSize;
    /* 0x2C */ struct OMMtx *matrices;
    /* 0x30 */ s32 numMatrices;
    /* 0x34 */ void *cleanupFn; // void(*)(struct DObjDynamicStore *)
    /* 0x38 */ struct AObj *aobjs;
    /* 0x3C */ s32 numAObjs;
    /* 0x40 */ struct MObj *mobjs;
    /* 0x44 */ s32 numMObjs;
    /* 0x48 */ struct DObj *dobjs;
    /* 0x4C */ s32 numDObjs;
    /* 0x50 */ s32 dobjSize;
    /* 0x54 */ struct SObj *sobjs;
    /* 0x58 */ s32 numSObjs;
    /* 0x5C */ s32 sobjSize;
    /* 0x60 */ struct OMCamera *cameras;
    /* 0x64 */ s32 numCameras;
    /* 0x68 */ s32 cameraSize;
}; // size == 0x6C

// globals

/// Something to do with GObjCommon handling
extern s32 D_8003B874;
extern struct Mtx6Float D_8003B878;
extern struct Mtx7Float D_8003B894;
extern struct Mtx3x3Float D_8003B8B4;
extern union Mtx3fi D_8003B8DC;
extern struct Mtx4Float D_8003B900;
extern struct Mtx3Float D_8003B914;

#define OM_COMMON_MAX_LINKS    33
#define OM_COMMON_MAX_DL_LINKS 65
extern struct GObjCommon *gOMObjCommonLinks[OM_COMMON_MAX_LINKS];
extern struct GObjCommon *gOMObjCommonDLLinks[OM_COMMON_MAX_DL_LINKS];
// Something to do with an initial object to be passed to a new GObjProcess
extern struct GObjCommon *D_80046A54;
extern struct GObjCommon *D_80046A58;
extern struct GObjCommon *D_80046A5C;
extern struct GObjProcess *D_80046A60;
extern OSMesgQueue gOMMq;
extern u8 D_80046A88[1280];

// functions

extern s32 func_800078C8(void);
extern struct GObjProcess *func_80008188(struct GObjCommon *com, void *ptr, u8 kind, u32 pri);
extern void func_8000848C(struct GObjProcess *);
extern void func_80008CC0(struct DObj *, u8, u8);
extern struct OMMtx *func_80008CF0(struct OMCamera *, u8, u8);
extern struct AObj *func_80008E78(struct OMAnimation *anim, u8 index);
extern void func_80008EE4(struct DObj *);
extern struct AObj *func_80008F44(struct OMAnimation *anim, u8 index);
extern void func_80008FB0(struct OMAnimation *);
extern struct AObj *func_80009010(struct OMAnimation *anim, u8 index);
extern struct MObj *func_800090DC(struct DObj *, struct MObjSub *);
extern void func_800091F4(struct DObj *obj);
extern struct DObj *func_800092D0(struct GObjCommon *, s32);
extern struct DObj *func_80009380(struct DObj *, s32);
extern struct DObj *func_800093F4(struct DObj *, s32);
extern void func_8000948C(struct DObj *);
extern struct SObj *func_80009614(struct GObjCommon *, struct SObjSub10 *);
extern void func_800096EC(struct SObj *);
extern struct OMCamera *func_80009760(struct GObjCommon *);
extern struct GObjCommon *func_80009968(u32 id, void (*arg1)(void), u8 link, u32 arg3);
extern struct GObjCommon *func_800099A8(u32 id, void (*arg1)(void), u8 link, u32 arg3);
extern void func_80009A84(struct GObjCommon *);
extern void func_80009C90(struct GObjCommon *arg0, u8 link, u32 arg2);
extern void func_80009CC8(struct GObjCommon *arg0, u8 link, u32 arg2);
extern void func_80009DF4(
    struct GObjCommon *arg0,
    void (*arg1)(struct GObjCommon *),
    u8 dlLink,
    s32 arg3,
    s32 arg4);
extern void func_80009F74(
    struct GObjCommon *arg0,
    void (*arg1)(struct GObjCommon *),
    u32 arg2,
    s64 arg3,
    s32 arg4);
extern void om_g_move_obj_dl(struct GObjCommon *arg0, u8 dlLink, u32 arg2);
extern void om_g_move_obj_dl_head(struct GObjCommon *arg0, u8 dlLink, u32 arg2);
extern void func_8000A24C(struct GObjCommon *, u32);
extern void func_8000A2B4(struct GObjCommon *, struct GObjCommon *);
extern void set_max_obj_commons(s32 n);
extern s16 get_max_obj_commons(void);
extern void func_8000A340(void);
extern void func_8000A5E4(void);
extern void set_up_object_manager(struct OMSetup *);

#endif /* SYS_OM_H */
