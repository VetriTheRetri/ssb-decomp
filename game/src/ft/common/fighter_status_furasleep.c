#include "fighter.h"

void func_ovl3_80149940(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 breakout_wait;

    fp->breakout_wait--;

    breakout_wait = fp->breakout_wait;

    ftCommon_Trap_UpdateBreakoutVars(fp);

    fp->breakout_wait += (fp->breakout_wait - breakout_wait) * 3;

    if (fp->breakout_wait <= 0)
    {
        func_ovl3_8013E1C8(fighter_gobj);
    }
}

void func_ovl3_801499A4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 breakout_wait;

    ftStatus_Update(fighter_gobj, ftStatus_Common_FuraSleep, 0.0F, 1.0F, FTSTATUPDATE_NULL_PRESERVE);

    breakout_wait = FTCOMMON_FURASLEEP_BREAKOUT_WAIT_DEFAULT - fp->percent_damage;

    if (breakout_wait <= 0)
    {
        breakout_wait = 0;
    }
    breakout_wait += FTCOMMON_FURASLEEP_BREAKOUT_WAIT_MIN;

    ftCommon_Trap_InitBreakoutVars(fp, breakout_wait);
    ftCommon_CheckSetColAnimIndex(fighter_gobj, FTCOMMON_FURASLEEP_COLANIM_ID, 0);
}
