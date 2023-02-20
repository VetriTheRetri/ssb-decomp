#ifndef _GMMISC_H_
#define _GMMISC_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef struct CommonAttackFlagsHi
{
    u16 flags_hi_b0 : 1;
    u16 flags_hi_b1 : 1;
    u16 flags_hi_b2 : 1;
    u16 flags_hi_b3 : 1;
    u16 flags_hi_b4 : 1;
    u16 flags_hi_b5 : 1;
    u16 flags_hi_0x3FF : 10;

} CommonAttackFlagsHi;

typedef struct CommonAttackFlagsLw
{
    u16 flags_lw_0x8000 : 1;
    u16 flags_lw_0x4000 : 1;
    u16 flags_lw_0x2000 : 1;
    u16 flags_lw_0x1000 : 1;
    u16 flags_lw_0x800 : 1;
    u16 flags_lw_0x400 : 1;
    u16 flags_lw_0x3FF : 10;

} CommonAttackFlagsLw;

typedef struct FighterAttackFlags
{
    CommonAttackFlagsHi hi;
    CommonAttackFlagsLw lw;

} FighterAttackFlags;

#endif