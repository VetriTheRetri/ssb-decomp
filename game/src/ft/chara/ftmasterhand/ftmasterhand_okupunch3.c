#include "ftmasterhand.h"

void func_ovl3_8015AA10(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80159040);
}

void func_ovl3_8015AA34(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f *translate;

    fp->lr = LEFT;

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_OkuPunch3, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    translate = &DObjGetStruct(fighter_gobj)->translate;

    translate->x = fp->status_vars.masterhand.okupunch.pos.x;
    translate->y = fp->status_vars.masterhand.okupunch.pos.y + 6000.0F;
    translate->z = 0.0F;
}
