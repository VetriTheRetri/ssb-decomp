#include "ftcaptain.h"
#include "ftness.h"

void func_ovl3_8013DE60(GObj *fighter_gobj)
{
    func_ovl3_8013DA14(fighter_gobj);
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8013DEC0);
}

void func_ovl3_8013DE90(GObj *fighter_gobj)
{
    func_ovl3_8013DA14(fighter_gobj);
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8013DF14);
}

void func_ovl3_8013DEC0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Ness_AppearStart, 0.0F, 1.0F, 0x22U);
    func_ovl3_8013DBAC(fighter_gobj);

    fp->x18E_flag_b0 = FALSE;
}

void func_ovl3_8013DF14(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ((fp->status_vars.common.entry.lr_entry == RIGHT) ? ftStatus_Ness_AppearR : ftStatus_Ness_AppearL), 0.0F, 1.0F, 0x22U);
    func_ovl3_8013DBAC(fighter_gobj);

    fp->x18E_flag_b0 = FALSE;
}

void func_ovl3_8013DF7C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8013DA14(fighter_gobj);

    if ((fp->status_vars.common.entry.lr_entry == LEFT) && (fp->unk_0x16 != 9) && (DObjGetStruct(fighter_gobj)->translate.z > -1000.0F))
    {
        func_ovl2_800E827C(fighter_gobj, 9);
    }
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8013E008);
}

void func_ovl3_8013DF14(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ((fp->status_vars.common.entry.lr_entry == RIGHT) ? ftStatus_Captain_AppearR : ftStatus_Captain_AppearL), 0.0F, 1.0F, 0U);
    func_ovl3_8013DBAC(fighter_gobj);

    fp->x18E_flag_b0 = FALSE;
}
