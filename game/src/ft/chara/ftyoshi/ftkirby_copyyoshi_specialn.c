#include <game/src/ft/chara/ftkirby/ftkirby.h>

void func_ovl3_8015F180(Fighter_Struct *fp, void (*cb)(GObj*)) // Kirby's Yoshi Copy
{
    func_ovl2_800E80A4(fp, 1, cb, func_ovl3_8014C83C);
}

void func_ovl3_8015F1AC(GObj *fighter_gobj, void (*cb_catch)(GObj*))
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->cmd_flags.flag1 != 0) && (fp->catch_gobj != NULL)) || (fighter_gobj->anim_frame <= 0.0F))
    {
        fp->cmd_flags.flag1 = 0;

        cb_catch(fighter_gobj);
    }
}

void func_ovl3_8015F200(GObj *fighter_gobj)
{
    func_ovl3_8015F1AC(fighter_gobj, func_ovl3_8015F768);
}

void func_ovl3_8015F224(GObj *fighter_gobj)
{
    func_ovl3_8015F1AC(fighter_gobj, func_ovl3_8015F7AC);
}

void func_ovl3_8015F248(Fighter_Struct *fp)
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

void func_ovl3_8015F2BC(GObj *fighter_gobj)
{
    func_ovl3_8015F248(FighterGetStruct(fighter_gobj));
    func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_8015F2E8(GObj *fighter_gobj)
{
    func_ovl3_8015F248(FighterGetStruct(fighter_gobj));
    func_ovl2_800D94E8(fighter_gobj);
}

void func_ovl3_8015F314(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015F45C);
}

void func_ovl3_8015F338(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015F408);
}

void func_ovl3_8015F35C(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015F4F0);
}

void func_ovl3_8015F380(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015F4B0);
}

void func_ovl3_8015F3A4(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015F570);
}

void func_ovl3_8015F3C8(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015F530);
}

void func_ovl3_8015F3EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag1 = 0;
}

void func_ovl3_8015F3EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag2 = 0;
    fp->cmd_flags.flag1 = 0;
}

void func_ovl3_8015F408(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x25U);
    func_ovl3_8015F180(fp, func_ovl3_8015F6AC);
}

void func_ovl3_8015F45C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x25U);
    func_ovl3_8015F180(fp, func_ovl3_8015F6F0);
}

void func_ovl3_8015F4B0(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialNCatch, fighter_gobj->anim_frame, 1.0F, 0x24U);
}

void func_ovl3_8015F4F0(GObj *fighter_gobj)
{
    func_ovl2_800DEEC8(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialAirNCatch, fighter_gobj->anim_frame, 1.0F, 0x24U);
}

void func_ovl3_8015F530(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialNRelease, fighter_gobj->anim_frame, 1.0F, 0x24U);
}

void func_ovl3_8015F570(GObj *fighter_gobj)
{
    func_ovl2_800DEEC8(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialAirNRelease, fighter_gobj->anim_frame, 1.0F, 0x24U);
}

void jtgt_ovl3_8015F5B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_8015F3EC;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialN, 0.0F, 1.0F, 0U);
    func_ovl3_8015F180(fp, func_ovl3_8015F6AC);
    func_ovl2_800E0830(fighter_gobj);
}

void jtgt_ovl3_8015F60C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = &func_ovl3_8015F3F8;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialAirN, 0.0F, 1.0F, 0U);
    func_ovl3_8015F180(fp, func_ovl3_8015F6F0);
    func_ovl2_800E0830(fighter_gobj);
}

void func_ovl3_8015F668(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E8098(fp, 0x3FU);
    func_ovl2_800D9444(fighter_gobj);

    fp->catch_gobj = fp->unk_gobj;
}

void func_ovl3_8015F6AC(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialNCatch, fighter_gobj->anim_frame, 1.0F, 0x24U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015F668(fighter_gobj);
}

void func_ovl3_8015F6F0(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialAirNCatch, fighter_gobj->anim_frame, 1.0F, 0x24U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015F668(fighter_gobj);
}

void func_ovl3_8015F734(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E8098(fp, 0x3FU);

    fp->cmd_flags.flag2 = 0;
    fp->cmd_flags.flag1 = 0;
}

void func_ovl3_8015F768(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialNRelease, 0.0F, 1.0F, 0x24U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015F734(fighter_gobj);
}

void func_ovl3_8015F7AC(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyYoshi_SpecialAirNRelease, 0.0F, 1.0F, 0x24U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015F734(fighter_gobj);
}