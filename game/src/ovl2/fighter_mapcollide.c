#include "fighter.h"

bool32 func_ovl2_800D9480(GObj *fighter_gobj, void (*cb_coll)(GObj*))
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        cb_coll(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl2_800D94C4(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8013E1C8);
}

void func_ovl2_800D94E8(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8013F9E0);
}
