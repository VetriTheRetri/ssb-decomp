#include "fighter.h"

bool32 ftAnim_IfAnimEnd_ProcStatus(GObj *fighter_gobj, void (*proc_status)(GObj*))
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        proc_status(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl2_800D94C4(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8013E1C8);
}

void func_ovl2_800D94E8(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8013F9E0);
}
