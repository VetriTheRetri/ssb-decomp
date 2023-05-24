#include "ftdonkey.h"

#define ftStatus_CheckInterruptThrowFTurn(fighter_gobj) \
(                                                       \
    (func_ovl3_80146BE0(fighter_gobj) != FALSE) ||      \
    (func_ovl3_8014DFA8(fighter_gobj) != FALSE)         \
)                                                       \

void func_ovl3_8014D740(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->command_vars.flags.flag1 = 0;

        fp->lr = -fp->lr;

        fp->phys_info.vel_ground.x = -fp->phys_info.vel_ground.x;
    }
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8014D49C);
}

void func_ovl3_8014D790(GObj *fighter_gobj)
{
    if (!ftStatus_CheckInterruptThrowFTurn(fighter_gobj))
    {
        func_ovl3_8014D9B8(fighter_gobj);
    }
}

void func_ovl3_8014D7D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag1 = 0;

    ftStatus_Update(fighter_gobj, ftStatus_Donkey_ThrowFTurn, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

bool32 func_ovl3_8014D810(GObj *fighter_gobj)
{
    if (func_ovl3_8013E9D0(fighter_gobj) != FALSE)
    {
        func_ovl3_8014D7D0(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}