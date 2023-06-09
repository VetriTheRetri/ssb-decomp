#include "fighter.h"

void func_ovl3_801479A0(GObj *fighter_gobj)
{
    if ((func_ovl3_8014800C(fighter_gobj) == FALSE) && (func_ovl3_80147E7C(fighter_gobj) == FALSE))
    {
        ftCommon_HammerWaitCheckSetStatus(fighter_gobj);
    }
}

void func_ovl3_801479E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_HammerWalk, ftCommon_HammerGetAnimFrame(fighter_gobj), 1.0F, ftCommon_HammerGetStatUpdateFlags(fighter_gobj));
    ftCommon_HammerCheckSetColAnim(fighter_gobj);
}

bool32 func_ovl3_80147A2C(GObj *fighter_gobj)
{
    if (func_ovl3_8013E614(fighter_gobj) != FALSE)
    {
        func_ovl3_801479E0(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}