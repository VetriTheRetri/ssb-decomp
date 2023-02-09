#ifndef _FTPURIN_H_
#define _FTPURIN_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/ft/fighter.h>

#define FTPURIN_POUND_VEL_BASE 0.65F
#define FTPURIN_POUND_VEL_MUL 0.92F

typedef enum ftPurinAction
{
    ftStatus_Purin_Attack100Start = 0xDC,
    ftStatus_Purin_Attack100Loop,
    ftStatus_Purin_Attack100End,            // These are all unused
    ftStauts_Purin_JumpAerialF1,
    ftStatus_purin_JumpAerialF2,
    ftStatus_Purin_JumpAerialF3,
    ftStatus_Purin_JumpAerialF4,
    ftStatus_Purin_JumpAerialF5,
    ftStatus_Purin_AppearR,
    ftStatus_Purin_AppearL,
    ftStatus_Purin_SpecialN,
    ftStatus_Purin_SpecialAirN,
    ftStatus_Purin_SpecialHi,
    ftStatus_Purin_SpecialAirHi,
    ftStatus_Purin_SpecialLw,
    ftStatus_Purin_SpecialAirLw

} ftPurinAction;

#endif