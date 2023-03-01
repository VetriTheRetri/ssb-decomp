#ifndef _ARTICLE_H_
#define _ARTICLE_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/gm/gmmisc.h>
#include <game/src/gm/gmsound.h>

typedef struct _Article_Hit
{
    s32 update_state; // 0 = disabled, 1 = new hitbox, 2 and 3 = interpolate/copy current position to previous
    s32 damage; // 0x4
    f32 stale;  // Multiplies damage
    u32 element; // 0xC // Placed AFTER offset?
    Vec3f offset[2]; // 0x10 - 0x18    
    f32 size;
    s32 unk_0x2C;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    u16 hit_status; // "Tangibility flag? 0x07"
    u16 hit_sfx;
    u32 unk_0x3C;
    s32 unk_0x40;
    u16 flags_0x44 : 7; // Reflectability flag

    u16 flags_0x48_b123456 : 6;
    u16 flags_0x48_b7 : 1;

    union
    {
        struct
        {
            CommonAttackFlagsHi flags_0x4A;
            CommonAttackFlagsLw flags_0x4C;
        };
        struct
        {
            u16 flags_0x4A_halfword;
            u16 flags_0x4C_halfword;
        };
    };

    u16 flags_0x4E;
    s32 hitbox_count;
    Vec3f pos;
    Vec3f pos_prev;

} Article_Hit;

typedef struct Article_Struct // Pokémon?
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

    u8 filler_0x110[0x8];

    Article_Hit article_hit[1];

    u8 filler_0x160[0x374 - 0x17C];

    s32 display_state;

} Article_Struct;

#define ArticleGetStruct(article_gobj) \
((Article_Struct*)article_gobj->user_data) \

#endif
