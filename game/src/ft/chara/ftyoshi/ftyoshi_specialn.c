#include "ftyoshi.h"

void func_ovl3_8015E310(Fighter_Struct *fp, void (*cb_unk)(GObj*))
{
    func_ovl2_800E80A4(fp, 1, cb_unk, func_ovl3_8014C83C);
}

void func_ovl3_8015E33C(GObj *fighter_gobj, void (*cb_catch)(GObj *))
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->cmd_flags.flag1 != 0) && (fp->catch_gobj != NULL)) || (fighter_gobj->anim_frame <= 0.0F))
    {
        fp->cmd_flags.flag1 = 0;

        cb_catch(fighter_gobj);
    }
}

void func_ovl3_8015E390(GObj *fighter_gobj)
{
    func_ovl3_8015E33C(fighter_gobj, func_ovl3_8015E8F8);
}

void func_ovl3_8015E3B4(GObj *fighter_gobj)
{
    func_ovl3_8015E33C(fighter_gobj, func_ovl3_8015E93C);
}

void func_ovl3_8015E3D8(Fighter_Struct *fp)
{
    if (fp->cmd_flags.flag2 != 0U)
    {
        if (fp->catch_gobj != NULL)
        {
            Fighter_Struct *fp_catch = FighterGetStruct(fp->catch_gobj);

            fp_catch->status_vars.common.yoshiegg.unk_0x4 = 1;

            fp->cmd_flags.flag2 = 0;
        }
    }
    if (fp->cmd_flags.flag1 != 0U)
    {
        if (fp->catch_gobj != NULL)
        {
            Fighter_Struct *fp_catch = FighterGetStruct(fp->catch_gobj);

            fp_catch->status_vars.common.yoshiegg.unk_0x4 = 3;

            fp->catch_gobj = NULL;

            fp->cmd_flags.flag1 = 0;

            func_ovl2_800E8098(fp, 0U);
        }
    }
}

void func_ovl3_8015E44C(GObj *fighter_gobj)
{
    func_ovl3_8015E3D8(FighterGetStruct(fighter_gobj));
    func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_8015E478(GObj *fighter_gobj)
{
    func_ovl3_8015E3D8(FighterGetStruct(fighter_gobj));
    func_ovl2_800D94E8(fighter_gobj);
}

void func_ovl3_8015E4A4(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015E5EC);
}

void func_ovl3_8015E4C8(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015E598);
}

void func_ovl3_8015E4EC(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015E680);
}

void func_ovl3_8015E510(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015E640);
}

void func_ovl3_8015E534(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015E700);
}

void func_ovl3_8015E558(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015E6C0);
}

void func_ovl3_8015E57C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag1 = 0;
}

void func_ovl3_8015E588(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag2 = 0;
    fp->cmd_flags.flag1 = 0;
}

void func_ovl3_8015E598(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x25U);
    func_ovl3_8015E310(fp, func_ovl3_8015E83C);
}

void func_ovl3_8015E5EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x25U);
    func_ovl3_8015E310(fp, func_ovl3_8015E880);
}

void func_ovl3_8015E640(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialNCatch, fighter_gobj->anim_frame, 1.0F, 0x24U);
}

void func_ovl3_8015E680(GObj *fighter_gobj)
{
    func_ovl2_800DEEC8(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialAirNCatch, fighter_gobj->anim_frame, 1.0F, 0x24U);
}

void func_ovl3_8015E6C0(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialNRelease, fighter_gobj->anim_frame, 1.0F, 0x24U);
}

void func_ovl3_8015E700(GObj *fighter_gobj)
{
    func_ovl2_800DEEC8(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialAirNRelease, fighter_gobj->anim_frame, 1.0F, 0x24U);
}

void jtgt_ovl3_8015E740(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_8015E57C;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialN, 0.0F, 1.0F, 0U);
    func_ovl3_8015E310(fp, func_ovl3_8015E83C);
    func_ovl2_800E0830(fighter_gobj);
}

void jtgt_ovl3_8015E740(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_8015E588;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialAirN, 0.0F, 1.0F, 0U);
    func_ovl3_8015E310(fp, func_ovl3_8015E880);
    func_ovl2_800E0830(fighter_gobj);
}

void func_ovl3_8015E7F8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E8098(fp, 0x3FU); // Store grab vulnerability flags?
    func_ovl2_800D9444(fighter_gobj);

    fp->catch_gobj = fp->unk_gobj;
}

void func_ovl3_8015E83C(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialNCatch, fighter_gobj->anim_frame, 1.0F, 0x24U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015E7F8(fighter_gobj);
}

void func_ovl3_8015E880(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialAirNCatch, fighter_gobj->anim_frame, 1.0F, 0x24U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015E7F8(fighter_gobj);
}

void func_ovl3_8015E8C4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E8098(fp, 0x3FU);
    fp->cmd_flags.flag2 = 0;
    fp->cmd_flags.flag1 = 0;
}

void func_ovl3_8015E8F8(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialNRelease, 0.0F, 1.0F, 0x24U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015E8C4(fighter_gobj);
}

void func_ovl3_8015E93C(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Yoshi_SpecialAirNRelease, 0.0F, 1.0F, 0x24U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015E8C4(fighter_gobj);
}

void func_ovl3_8015E980(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.yoshi.specialhi.egg_gobj != NULL)
    {
        func_ovl3_8016800C(fp->status_vars.yoshi.specialhi.egg_gobj);
    }
}
