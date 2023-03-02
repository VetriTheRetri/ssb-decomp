#ifndef _ARTICLE_H_
#define _ARTICLE_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/gm/gmmisc.h>
#include <game/src/gm/gmsound.h>

typedef struct ArticleHitVictimFlags
{
    u32 flags_b0 : 1;
    u32 flags_b1 : 1;
    u32 flags_b2 : 1;
    u32 flags_b3 : 1;
    u32 flags_b456 : 3;
    u32 timer_rehit : 6;

} ArticleHitVictimFlags;

typedef struct ArticleHitUnk
{
    Vec3f pos;
    Vec3f pos_prev;
    s32 unk_0x18;
    u8 filler_0x1C[0x5C - 0x1C];
    f32 unk_0x5C;

} ArticleHitUnk;

typedef struct _ArticleHitArray
{
    GObj *victim_gobj;
    ArticleHitVictimFlags victim_flags;

} ArticleHitArray;

typedef struct _Article_Hit
{
    s32 update_state; // 0x0
    s32 damage; // 0x4
    f32 stale; // Might be damage in float? At least based on Melee?
    s32 element; // 0xC // Placed AFTER offset?
    s32 unk;
    Vec3f offset[2]; // 0x10 - 0x18    
    f32 size;
    s32 angle;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    u16 hit_status; // "Tangibility flag? 0x07"
    u16 hit_sfx;
    s32 unk_0x3C; // Shield damage?
    s32 unk_0x40; // Priority?
    u16 flags_0x44 : 7; // Reflectability flag

    u16 flags_0x48_b123456 : 6;
    u16 flags_0x48_b7 : 1;

    u16 flags_0x4A;
    u16 flags_0x4C;
    u16 flags_0x4E;
    s32 hitbox_count;
    ArticleHitUnk article_hit_unk[2];
    ArticleHitArray hit_targets[4];

} Article_Hit;

typedef struct Article_Struct // Common Items / Pokémon 
{
    void *unk_0x0;
    GObj *article_gobj;
    GObj *owner_gobj;
    s32 article_kind;
    s32 unk_0x10;
    u8 team;
    u8 port_index;
    u8 unk_0x16;
    u8 unk_0x17;
    s32 player_number;
    u32 unk_0x1C;
    u32 unk_0x20;
    s32 lr;

    u8 filler_0x28[0x38 - 0x28];

    Coll_Data coll_data;

    Ground_Air ground_or_air;

    Article_Hit article_hit[1];

    u8 filler_0x244[0x374 - 0x244];

    s32 display_state;

} Article_Struct;

#define ArticleGetStruct(article_gobj) \
((Article_Struct*)article_gobj->user_data) \

#endif
