#include "ftmasterhand.h"

void func_ovl3_8015ACB0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8015ABEC);
}

void func_ovl3_8015ACD4(GObj *fighter_gobj)
{
    Fighter_Struct *masterhand_fp, *target_fp;
    s32 unk_coll;
    s32 var_a3;

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_OkutsubushiStart, 0.0F, 1.0F, 0U);

    masterhand_fp = FighterGetStruct(fighter_gobj);

    target_fp = FighterGetStruct(masterhand_fp->fighter_vars.masterhand.p_masterhand->target_gobj);

    unk_coll = target_fp->coll_data.ground_line_id;

    var_a3 = ((unk_coll != -1) && (unk_coll != -2)) ? unk_coll : masterhand_fp->fighter_vars.masterhand.p_masterhand->unk_0x8;

    func_ovl3_8015839C(var_a3, &masterhand_fp->status_vars.masterhand.okutsubushi.pos);
}
