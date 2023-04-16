#include "fighter.h"

void func_ovl3_801439D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.tornado.release_wait++;

    if (fp->status_vars.common.tornado.release_wait >= FTCOMMON_TORNADO_RELEASE_WAIT)
    {
        func_ovl3_80143CC4(fighter_gobj);
    }
}