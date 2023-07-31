#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <ssb_types.h>
#include <macros.h>
#include <sys/obj_renderer.h> // Probably shouldn't be included
#include <PR/ultratypes.h>
#include <sys/obj.h>

#include "effectvars.h"
#include "efdef.h"

#define EFFECT_ALLOC_NUM 38
#define EFFECT_ALLOC_ALIGN 0x8

enum efKind
{
    Ef_Kind_DamageNormal,               // Texture displayed when hit by an attack of the normal element
    Ef_Kind_FlameLR = 6,                // Flame whose velocity depends on the user's facing direction
    Ef_Kind_FlameRandom,                // Small flame texture that scatters
    Ef_Kind_FlameStatic,                // Small flame texture that is stationary?
    Ef_Kind_ShockSmall = 10,            // Texture displayed when hit by an attack of the electric element; small shockwave texture
    Ef_Kind_DustLight,                  // e.g. Light landing (no fast fall)
    Ef_Kind_DustLightRapid,             // Faster version of DustLight?
    Ef_Kind_DustHeavyDouble,            // Two instances of heavy dust clouds
    Ef_Kind_DustHeavyDoubleRapid,       // Two instances of faster heavy dust clouds?
    Ef_Kind_DustHeavy,                  // Single instance of heavy dust cloud
    Ef_Kind_DustHeavyReverse,           // Single instance of direction-flipped heavy dust cloud
    Ef_Kind_DustExpandLarge,            // Large dust cloud that grows in size
    Ef_Kind_DustExpandSmall,            // Small dust cloud that grows in size
    Ef_Kind_DustDashSmall,              // Small (actually pretty large) dust kickup behind user
    Ef_Kind_DustDashLarge,              // Large dust kickup behind user
    Ef_Kind_DamageFlyOrbs,              // Cyan orbs that fly outward, used only on DamageFlyRoll?
    Ef_Kind_QuakeM0 = 32,               // Creates an earthquake of magnitude 0
    Ef_Kind_QuakeM1,                    // Creates an earthquake of magnitude 1
    Ef_Kind_QuakeM2                     // Creates an earthquake of magnitude 2
};

struct efImage
{
    u8 filler_0x0[0x4];
    Vec3f translate;
    Vec3f rotate;
    Vec3f scale;
    u16 unk_effect_0x28;
    u16 unk_effect_0x2A;
    u8 filler_0x2C[0xB4 - 0x2C];
    void (*proc_dead)(GObj*);
    u16 unk_effect_0xB8;
    GObj *effect_gobj;
};

struct efParticle
{
    u8 filler_0x0[0x48];
    GfxColorAlpha color1;
    s32 unk_efpart_0x4C;
    GfxColorAlpha color2;
    u8 filler_0x54[0x5C - 0x54];
    efImage *effect_info;
};

struct efStruct
{
    efStruct *ep_alloc_next;
    GObj *fighter_gobj;
    u16 unk_effectstruct_0x8;
    efImage *einfo;
    u32 is_pause_effect : 1;
    u32 effect_flags_b1 : 1;
    u32 effect_flags_b2 : 1;
    u32 effect_flags_b3 : 1;
    void (*proc_update)(GObj*);

    union effect_vars // Effect vars union?
    {
        efVars_Common common;
        efVars_BoxSmash basic1;
        efVars_Basic2 basic2;
        efVars_DamageNormalHeavy damage_normal_heavy;
        efVars_DustLight dust_light;
        efVars_DustHeavy dust_heavy;
        efVars_DamageFlyOrbs damage_fly_orbs;
        efVars_DamageSpawnOrbs damage_spawn_orbs;
    } 
    effect_vars;
};

#define efGetStruct(effect_gobj) \
((efStruct*)(effect_gobj)->user_data) \

#endif