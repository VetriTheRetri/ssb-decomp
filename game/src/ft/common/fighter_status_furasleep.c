#include "fighter.h"

void func_ovl3_80149940(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 breakout_wait;

    fp->breakout_wait--;

    breakout_wait = fp->breakout_wait;

    func_ovl3_8014E400(fp);

    fp->breakout_wait += (fp->breakout_wait - breakout_wait) * 3;

    if (fp->breakout_wait <= 0)
    {
        func_ovl3_8013E1C8(fighter_gobj);
    }
}

void func_ovl3_801499A4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = fighter_gobj->user_data;
    s32 breakout_wait;

    ftStatus_Update(fighter_gobj, ftStatus_Common_FuraSleep, 0.0F, 1.0F, 0U);

    breakout_wait = FTCOMMON_FURASLEEP_BREAKOUT_WAIT_DEFAULT - fp->percent_damage;

    if (breakout_wait <= 0)
    {
        breakout_wait = 0;
    }
    breakout_wait += FTCOMMON_FURASLEEP_BREAKOUT_WAIT_MIN;

    func_ovl3_8014E3EC(fp, breakout_wait);
    func_ovl2_800E9814(fighter_gobj, FTCOMMON_FURASLEEP_COLANIM_ID, 0);
}
