#ifndef _GMSCRIPT_H_
#define _GMSCRIPT_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define gmScriptEventUpdatePtr(event, type)                                   \
(event->p_script = (void*) ((uintptr_t)event->p_script + (sizeof(type))))     \

#define gmScriptEventCast(event, type)                                        \
((type*) event->p_script)                                                     \

// WARNING: Only advances 4 bytes at a time
#define gmScriptEventCastUpdate(event, type)                                  \
((type*) event->p_script++)                                                   \

#define gmColorEventUpdatePtr(event, type)                                    \
(event = (void*) ((uintptr_t)event + sizeof(type)))                           \

#define gmColorEventCast(event, type)                                         \
((type*) event)                                                               \

// WARNING: Only advances 4 bytes at a time
#define gmColorEventCastUpdate(event, type)                                   \
((type*) event++)                                                             \

typedef enum gmScriptEventKind
{
    gmScriptEvent_Kind_End,
    gmScriptEvent_Kind_SyncWait,
    gmScriptEvent_Kind_AsyncWait,
    gmScriptEvent_Kind_FighterHit,
    gmScriptEvent_Kind_ItemSwingHit,
    gmScriptEvent_Kind_ClearHitIndex,
    gmScriptEvent_Kind_ClearHitAll,
    gmScriptEvent_Kind_SetHitOffset,
    gmScriptEvent_Kind_SetHitDamage,
    gmScriptEvent_Kind_SetHitSize,
    gmScriptEvent_Kind_SetHitSoundLevel,
    gmScriptEvent_Kind_ResetHit, // ???
    gmScriptEvent_Kind_SetFighterThrow,
    gmScriptEvent_Kind_SubroutineThrown, // ???
    gmScriptEvent_Kind_PlaySFX,
    gmScriptEvent_Kind_UnkPlaySFX1,
    gmScriptEvent_Kind_UnkPlaySFX2,
    gmScriptEvent_Kind_PlayVoice,
    gmScriptEvent_Kind_UnkPlayVoice,
    gmScriptEvent_Kind_StorePlaySFX,
    gmScriptEvent_Kind_PlaySmashVoice,
    gmScriptEvent_Kind_SetFlag0,
    gmScriptEvent_Kind_SetFlag1,
    gmScriptEvent_Kind_SetFlag2,
    gmScriptEvent_Kind_SetFlag3,
    gmScriptEvent_Kind_SetAirJumpAdd,
    gmScriptEvent_Kind_SetAirJumpMax,
    gmScriptEvent_Kind_ResetHitStatusAll,
    gmScriptEvent_Kind_SetHitStatusPart,
    gmScriptEvent_Kind_SetHitStatusAll,
    gmScriptEvent_Kind_ResetHurtAll,
    gmScriptEvent_Kind_SetHurtPart,
    gmScriptEvent_Kind_LoopBegin,
    gmScriptEvent_Kind_LoopEnd,
    gmScriptEvent_Kind_Subroutine,
    gmScriptEvent_Kind_Return,
    gmScriptEvent_Kind_Goto,
    gmScriptEvent_Kind_ScriptPause,
    gmScriptEvent_Kind_GFX,
    gmScriptEvent_Kind_GFXPersist, // ???
    gmScriptEvent_Kind_SetModelPart,
    gmScriptEvent_Kind_Unk10,
    gmScriptEvent_Kind_Unk11,
    gmScriptEvent_Kind_SetTexturePart,
    gmScriptEvent_Kind_SetColAnim,
    gmScriptEvent_Kind_ResetColAnim,
    gmScriptEvent_Kind_SetParallelScript, // What
    gmScriptEvent_Kind_SlopeContour,
    gmScriptEvent_Kind_Unk14,
    gmScriptEvent_Kind_Unk15,
    gmScriptEvent_Kind_Unk16,
    gmScriptEvent_Kind_AfterImage // Sword Trail

} gmScriptEventKind;

typedef enum gmColorEventKind
{
    gmColorEvent_Kind_End,
    gmColorEvent_Kind_Wait,
    gmColorEvent_Kind_Goto,
    gmColorEvent_Kind_LoopBegin,
    gmColorEvent_Kind_LoopEnd,
    gmColorEvent_Kind_Subroutine,
    gmColorEvent_Kind_Return,
    gmColorEvent_Kind_SetParallelScript,
    gmColorEvent_Kind_ToggleColorOff,
    gmColorEvent_Kind_SetColor1,
    gmColorEvent_Kind_BlendColor1,
    gmColorEvent_Kind_SetColor2,
    gmColorEvent_Kind_BlendColor2,
    gmColorEvent_Kind_GFX,
    gmColorEvent_Kind_GFXPersist, // ???
    gmColorEvent_Kind_SetLight,
    gmColorEvent_Kind_ToggleLightOff,
    gmColorEvent_Kind_PlaySFX,
    gmColorEvent_Kind_SetUnk

} gmColorEventKind;

typedef struct gmScriptPointer
{
    void *p_goto[1];
    s32 script_index[4];

} gmScriptPointer;

typedef struct gmScriptEvent
{
    f32 frame_timer;
    u32 *p_script;
    s32 script_index;
    void *p_goto[1];
    s32 loop_count[4];

} gmScriptEvent;

typedef struct gmScriptEventDefault // Event with no arguments
{
    u32 opcode : 6;

} gmScriptEventDefault;

typedef struct gmScriptEventDouble // Event with no arguments
{
    u32 opcode : 6;
    u32 filler1 : 26;
    u32 filler2 : 32;
    
} gmScriptEventDouble;

typedef struct gmScriptEventWait
{
    u32 opcode : 6;
    u32 frames : 26;

} gmScriptEventWait;

typedef struct gmScriptEventCreateHit1
{
    u32 opcode : 6;
    u32 hit_id : 3;
    u32 interact_mask : 3;
    s32 joint_index : 7;
    u32 damage : 8;
    u32 clang : 1;
    u32 element : 4;

} gmScriptEventCreateHit1;

typedef struct gmScriptEventCreateHit2
{
    u32 size : 16;
    s32 off_x : 16;

} gmScriptEventCreateHit2;

typedef struct gmScriptEventCreateHit3
{
    s32 off_y : 16;
    s32 off_z : 16;

} gmScriptEventCreateHit3;

typedef struct gmScriptEventCreateHit4
{
    s32 angle : 10;
    u32 knockback_scale : 10;
    u32 knockback_weight : 10;
    u32 is_hit_ground_air : 2;

} gmScriptEventCreateHit4;

typedef struct gmScriptEventCreateHit5
{
    s32 shield_damage : 8;
    u32 sfx_level : 3;
    u32 sfx_kind : 4;
    u32 knockback_base : 10;

} gmScriptEventCreateHit5;

typedef struct gmScriptEventCreateHit
{
    gmScriptEventCreateHit1 s1;
    gmScriptEventCreateHit2 s2;
    gmScriptEventCreateHit3 s3;
    gmScriptEventCreateHit4 s4;
    gmScriptEventCreateHit5 s5;

} gmScriptEventCreateHit;

typedef struct gmScriptEventSetHitOffset1
{
    u32 opcode : 6;
    u32 hit_id : 3;
    s32 off_x : 16;

} gmScriptEventSetHitOffset1;

typedef struct gmScriptEventSetHitOffset2
{
    s32 off_y : 16;
    s32 off_z : 16;

} gmScriptEventSetHitOffset2;

typedef struct gmScriptEventSetHitOffset
{
    gmScriptEventSetHitOffset1 s1;
    gmScriptEventSetHitOffset2 s2;

} gmScriptEventSetHitOffset;

typedef struct gmScriptEventSetHitDamage
{
    u32 opcode : 6;
    u32 hit_id : 3;
    u32 damage : 8;

} gmScriptEventSetHitDamage;

typedef struct gmScriptEventSetHitSize
{
    u32 opcode : 6;
    u32 hit_id : 3;
    u32 size : 16;

} gmScriptEventSetHitSize;

typedef struct gmScriptEventSetHitSound
{
    u32 opcode : 6;
    u32 hit_id : 3;
    u32 sfx_level : 3;

} gmScriptEventSetHitSound;

typedef struct gmScriptEventResetHit
{
    u32 opcode : 6;
    u32 hit_id : 26;

} gmScriptEventResetHit;

typedef struct gmScriptEventClearHitIndex
{
    u32 opcode : 6;
    u32 hit_id : 26;

} gmScriptEventClearHitIndex;

typedef struct gmScriptEventClearHitAll
{
    u32 opcode : 6;

} gmScriptEventClearHitAll;

typedef struct gmScriptEventSetFighterThrow1
{
    u32 opcode : 6;

} gmScriptEventSetFighterThrow1;

typedef struct gmScriptEventSetFighterThrow2
{
    ftThrowHitDesc *fighter_throw;

} gmScriptEventSetFighterThrow2;

typedef struct gmScriptEventSetFighterThrow
{
    gmScriptEventSetFighterThrow1 s1;
    gmScriptEventSetFighterThrow2 s2;

} gmScriptEventSetFighterThrow;

typedef struct gmScriptEventPlaySFX
{
    u32 opcode : 6;
    u32 sfx_id : 26;

} gmScriptEventPlaySFX;

typedef struct gmScriptEventCreateGFX1
{
    u32 opcode : 6;
    s32 joint_index : 7;
    u32 gfx_id : 9;
    u32 flag : 10;

} gmScriptEventCreateGFX1;

typedef struct gmScriptEventCreateGFX2
{
    s32 off_x : 16;
    s32 off_y : 16;

} gmScriptEventCreateGFX2;

typedef struct gmScriptEventCreateGFX3
{
    s32 off_z : 16;
    s32 rng_x : 16;

} gmScriptEventCreateGFX3;

typedef struct gmScriptEventCreateGFX4
{
    s32 rng_y : 16;
    s32 rng_z : 16;

} gmScriptEventCreateGFX4;

typedef struct gmScriptEventCreateGFX
{
    gmScriptEventCreateGFX1 s1;
    gmScriptEventCreateGFX2 s2;
    gmScriptEventCreateGFX3 s3;
    gmScriptEventCreateGFX4 s4;

} gmScriptEventCreateGFX;

typedef struct gmScriptEventSetHitStatusAll
{
    u32 opcode : 6;
    u32 hit_status : 26;

} gmScriptEventSetHitStatusAll;

typedef struct gmScriptEventSetHitStatusPart
{
    u32 opcode : 6;
    s32 joint_index : 7;
    u32 hit_status : 19;

} gmScriptEventSetHitStatusPart;

typedef struct gmScriptEventSetHurtPart1
{
    u32 opcode : 6;
    s32 joint_index : 7;

} gmScriptEventSetHurtPart1;

typedef struct gmScriptEventSetHurtPart2
{
    s32 off_x : 16;
    s32 off_y : 16;

} gmScriptEventSetHurtPart2;

typedef struct gmScriptEventSetHurtPart3
{
    s32 off_z : 16;
    s32 size_x : 16;

} gmScriptEventSetHurtPart3;

typedef struct gmScriptEventSetHurtPart4
{
    s32 size_y : 16;
    s32 size_z : 16;

} gmScriptEventSetHurtPart4;

typedef struct gmScriptEventSetHurtPart
{
    gmScriptEventSetHurtPart1 s1;
    gmScriptEventSetHurtPart2 s2;
    gmScriptEventSetHurtPart3 s3;
    gmScriptEventSetHurtPart4 s4;

} gmScriptEventSetHurtPart;

typedef struct gmScriptEventLoopBegin
{
    u32 opcode : 6;
    u32 loop_count : 26;

} gmScriptEventLoopBegin;

typedef struct gmScriptEventSubroutine1
{
    u32 opcode : 6;

} gmScriptEventSubroutine1;

typedef struct gmScriptEventSubroutine2
{
    void *p_goto;

} gmScriptEventSubroutine2;

typedef struct gmScriptEventSubroutine
{
    gmScriptEventSubroutine1 s1;
    gmScriptEventSubroutine2 s2;

} gmScriptEventSubroutine;

typedef struct gmScriptEventDamageUnk1
{
    u32 opcode : 6;

} gmScriptEventDamageUnk1;

typedef struct gmScriptEventDamageUnk2
{
    void *p_subroutine;

} gmScriptEventDamageUnk2;

typedef struct gmScriptEventDamage
{
    void *p_script[2][27];

} gmScriptEventDamage;

typedef struct gmScriptEventDamageUnk
{
    gmScriptEventDamageUnk1 s1;
    gmScriptEventDamageUnk2 s2;

} gmScriptEventDamageUnk;

typedef struct gmScriptEventReturn
{
    u32 opcode : 6;

} gmScriptEventReturn;

typedef struct gmScriptEventGoto1
{
    u32 opcode : 6;

} gmScriptEventGoto1;

typedef struct gmScriptEventGoto2
{
    void *p_goto;

} gmScriptEventGoto2;

typedef struct gmScriptEventGoto
{
    gmScriptEventGoto1 s1;
    gmScriptEventGoto2 s2;

} gmScriptEventGoto;

typedef struct gmScriptEventParallel1
{
    u32 opcode : 6;

} gmScriptEventParallel1;

typedef struct gmScriptEventParallel2
{
    void *p_goto;

} gmScriptEventParallel2;

typedef struct gmScriptEventParallel
{
    gmScriptEventParallel1 s1;
    gmScriptEventParallel2 s2;

} gmScriptEventParallel;

typedef struct gmScriptEventSetModelPart
{
    u32 opcode : 6;
    s32 joint_index : 7;
    s32 mode : 19;

} gmScriptEventSetModelPart;

typedef struct gmScriptEventSetTexturePart
{
    u32 opcode : 6;
    u32 obj_index : 6;
    u32 frame : 20;

} gmScriptEventSetTexturePart;

typedef struct gmScriptEventSetColAnim
{
    u32 opcode : 6;
    u32 colanim_id : 8;
    u32 length : 18;

} gmScriptEventSetColAnim;

typedef struct gmScriptEventSetFlag
{
    u32 opcode : 6;
    u32 flag : 26;

} gmScriptEventSetFlag;

typedef struct gmScriptEventSlopeContour
{
    u32 opcode : 6;
    u32 filler : 23;
    u32 mode : 3;

} gmScriptEventSlopeContour;

typedef struct gmScriptEventUnkFlag
{
    u32 opcode : 6;
    u32 flag : 26;

} gmScriptEventUnkFlag;

typedef struct gmScriptEventAfterImage
{
    u32 opcode : 6;
    u32 is_itemswing : 8;
    s32 render_state : 18;

} gmScriptEventAfterImage;

typedef struct gmScriptEventUnk31
{
    u32 opcode : 6;
    u32 value1 : 13;
    u32 value2 : 13;

} gmScriptEventUnk31;

typedef struct gmScriptEventUnk32
{
    u32 opcode : 6;
    u32 value1 : 26;

} gmScriptEventUnk32;

typedef struct gmColorEventDefault
{
    u32 opcode : 6;
    u32 value1 : 26;

} gmColorEventDefault;

typedef struct gmColorEventGoto1
{
    u32 opocode : 6;

} gmColorEventGoto1;

typedef struct gmColorEventGoto2
{
    void *p_goto;

} gmColorEventGoto2;

typedef struct gmColorEventGoto
{
    gmColorEventGoto1 s1;
    gmColorEventGoto2 s2;

} gmColorEventGoto;

typedef struct gmColorEventLoopBegin
{
    u32 opcode : 6;
    u32 loop_count : 26;

} gmColorEventLoopBegin;

typedef struct gmColorEventSubroutine1
{
    u32 opcode : 6;

} gmColorEventSubroutine1;

typedef struct gmColorEventSubroutine2
{
    void *p_subroutine;

} gmColorEventSubroutine2;

typedef struct gmColorEventSubroutine
{
    gmColorEventSubroutine1 s1;
    gmColorEventSubroutine2 s2;

} gmColorEventSubroutine;

typedef struct gmColorEventParallel1
{
    u32 opcode : 6;

} gmColorEventParallel1;

typedef struct gmColorEventParallel2
{
    void *p_script;

} gmColorEventParallel2;

typedef struct gmColorEventParallel
{
    gmColorEventParallel1 s1;
    gmColorEventParallel2 s2;

} gmColorEventParallel;

typedef struct gmColorEventSetRGBA1
{
    u32 opcode : 6;

} gmColorEventSetRGBA1;

typedef struct gmColorEventSetRGBA2
{
    u32 r : 8;
    u32 g : 8;
    u32 b : 8;
    u32 a : 8;

} gmColorEventSetRGBA2;

typedef struct gmColorEventBlendRGBA1
{
    u32 opcode : 6;
    u32 blend_frames : 26;

} gmColorEventBlendRGBA1;

typedef struct gmColorEventBlendRGBA2
{
    u32 r : 8;
    u32 g : 8;
    u32 b : 8;
    u32 a : 8;

} gmColorEventBlendRGBA2;

typedef struct gmColorEventBlendRGBA
{
    gmColorEventBlendRGBA1 s1;
    gmColorEventBlendRGBA2 s2;

} gmColorEventBlendRGBA;

typedef struct gmColorEventCreateGFX1
{
    u32 opcode : 6;
    s32 joint_index : 7;
    u32 gfx_id : 9;
    u32 flag : 10;

} gmColorEventCreateGFX1;

typedef struct gmColorEventCreateGFX2
{
    s32 off_x : 16;
    s32 off_y : 16;

} gmColorEventCreateGFX2;

typedef struct gmColorEventCreateGFX3
{
    s32 off_z : 16;
    s32 rng_x : 16;

} gmColorEventCreateGFX3;

typedef struct gmColorEventCreateGFX4
{
    s32 rng_y : 16;
    s32 rng_z : 16;

} gmColorEventCreateGFX4;

typedef struct gmColorEventCreateGFX
{
    gmColorEventCreateGFX1 s1;
    gmColorEventCreateGFX2 s2;
    gmColorEventCreateGFX3 s3;
    gmColorEventCreateGFX4 s4;

} gmColorEventCreateGFX;

typedef struct gmColorEventSetLight
{
    u32 opcode : 6;
    s32 light1 : 13;
    s32 light2 : 13;

} gmColorEventSetLight;

typedef struct gmColorEventPlaySFX
{
    u32 opcode : 6;
    u32 sfx_id : 26;

} gmColorEventPlaySFX;

#endif