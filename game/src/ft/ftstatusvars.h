#ifndef _FTSTATUSVARS_H_
#define _FTSTATUSVARS_H_

#include <game/src/ft/chara/ftmario/ftmario_statusvars.h>
#include <game/src/ft/chara/ftfox/ftfox_statusvars.h>
#include <game/src/ft/chara/ftdonkey/ftdonkey_statusvars.h>
#include <game/src/ft/chara/ftsamus/ftsamus_statusvars.h>
#include <game/src/ft/chara/ftlink/ftlink_statusvars.h>
#include <game/src/ft/chara/ftyoshi/ftyoshi_statusvars.h>
#include <game/src/ft/chara/ftcaptain/ftcaptain_statusvars.h>
#include <game/src/ft/chara/ftkirby/ftkirby_statusvars.h>
#include <game/src/ft/chara/ftpikachu/ftpikachu_statusvars.h>
#include <game/src/ft/chara/ftpurin/ftpurin_statusvars.h>
#include <game/src/ft/chara/ftness/ftness_statusvars.h>
#include <game/src/ft/chara/ftmasterhand/ftmasterhand_statusvars.h>

typedef struct ftCommon_Filler
{
    u8 filler[0xB4C - 0xB18];

} ftCommon_Filler;

typedef struct ftCommon_YoshiEgg_StatusVars
{
    u32 unk_0x0;
    u16 unk_0x4;

} ftCommon_YoshiEgg_StatusVars;

typedef struct ftCommon_CaptureCaptain_StatusVars
{
    u16 capture_flag;   // Collection of bit flags, only seen 0x4 and 0x2 used

} ftCommon_CaptureCaptain_StatusVars;

typedef struct ftCommon_CaptureKirby_StatusVars
{
    u16 unk_0x0;
    u16 unk_0x2;
    u16 unk_0x4;

} ftCommon_CaptureKirby_StatusVars;

typedef union ftCommon_StatusVars
{
    ftCommon_YoshiEgg_StatusVars yoshiegg;
    ftCommon_CaptureCaptain_StatusVars capturecaptain;
    ftCommon_CaptureKirby_StatusVars capturekirby;
    ftCommon_Filler filler;

} ftCommon_StatusVars;

#endif