#include "ftmasterhand.h"

void func_ovl3_80159780(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_80159040);
}

void func_ovl3_801597A4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f *translate;

    fp->lr = LEFT;

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Okuhikouki3, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    translate = &DObjGetStruct(fighter_gobj)->translate;

    translate->x = fp->status_vars.masterhand.okuhikouki.pos.x + 9000.0F;
    translate->y = fp->status_vars.masterhand.okuhikouki.pos.y + 3000.0F;
    translate->z = 0.0F;
}
