#include "ftmasterhand.h"

void func_ovl3_80159500(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_801596B0);
}

void func_ovl3_80159524(GObj *fighter_gobj)
{
    Fighter_Struct *target_fp;
    Fighter_Struct *masterhand_fp;
    s32 var_a3;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_Okuhikouki1, 0.0F, 1.0F, 0U);

    masterhand_fp = FighterGetStruct(fighter_gobj);

    target_fp = FighterGetStruct(masterhand_fp->fighter_vars.masterhand.p_masterhand->target_gobj);

    var_a3 = ((target_fp->coll_data.ground_line_id != -1) && (target_fp->coll_data.ground_line_id != -2)) ? target_fp->coll_data.ground_line_id : masterhand_fp->fighter_vars.masterhand.p_masterhand->unk_0x8;

    func_ovl3_8015839C(var_a3, &masterhand_fp->status_vars.masterhand.okuhikouki.pos);
}
