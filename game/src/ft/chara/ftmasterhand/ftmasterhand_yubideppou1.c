#include "ftmasterhand.h"

void func_ovl3_8015A350(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8015A748);
}

void func_ovl3_8015A374(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Yubideppou1, 0.0F, 1.0F, 0U);
    func_ovl3_80158030(fighter_gobj);

    fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.masterhand.yubideppou.bullet_count = 0;
}
