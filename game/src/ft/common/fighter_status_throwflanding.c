#include "ftdonkey.h"

void func_ovl3_8014DC50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->status_vars.common.throwf.landing_anim_frame++;

    if (fp->status_vars.common.throwf.landing_anim_frame <= 4.0F)
    {
        func_ovl3_8014D49C(fighter_gobj);
    }
}

void func_ovl3_8014DCA4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_ThrowFLanding, 0.0F, 0.0F, 0U);

    fp->status_vars.common.throwf.landing_anim_frame = 0.0F;
}
