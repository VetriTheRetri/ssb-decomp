#ifndef _GMMATCH_H_
#define _GMMATCH_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef enum gmPauseStatus
{
    gmPauseStatus_Disable,        // Pausing not allowed
    gmPauseStatus_Enable,         // Pausing allowed
    gmPauseStatus_Paused,         // Player paused
    gmPauseStatus_Unpause         // Player unpaused

} gmPauseStatus;

typedef struct gmMatchInfo
{
    u8 unk_0x0;
    u8 unk_0x1;
    u8 unk_0x2;
    u8 unk_0x3;
    u8 unk_0x4;
    u8 unk_0x5;
    u8 unk_0x6;
    u8 unk_0x7;
    u8 unk_0x8;
    u8 unk_0x9;
    u8 unk_0xA;
    u8 unk_0xB;
    u8 unk_0xC;
    u8 unk_0xD;
    u8 unk_0xE;
    u8 unk_0xF;
    u8 unk_0x10;
    u8 pause_status;

} gmMatchInfo;

extern gmMatchInfo *D_800A50E8;

#endif