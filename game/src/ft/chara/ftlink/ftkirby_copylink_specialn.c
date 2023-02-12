#include <game/src/ft/chara/ftkirby/ftkirby.h>

void func_ovl3_80164650(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->fighter_vars.kirby.copylink_boomerang_gobj != NULL)
    {
        func_ovl3_8016800C(fp->fighter_vars.kirby.copylink_boomerang_gobj);

        fp->fighter_vars.kirby.copylink_boomerang_gobj = NULL;
    }
}

void func_ovl3_80164688(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    if (fp->cmd_flags.flag0 != 0)
    {
        fp->cmd_flags.flag0 = 0;

        pos.x = 0.0F;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTKIRBY_COPYLINK_BOOMERANG_SPAWN_JOINT], &pos);

        fp->fighter_vars.kirby.copylink_boomerang_gobj = func_ovl3_8016DA78(fighter_gobj, &pos);
    }
}

void func_ovl3_801646F0(GObj *fighter_gobj)
{
    func_ovl3_80164688(fighter_gobj);
    func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_80164718(GObj *fighter_gobj)
{
    func_ovl3_80164688(fighter_gobj);
    func_ovl2_800D94E8(fighter_gobj);
}

void func_ovl3_80164740(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80164820);
}

void func_ovl3_80164764(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_801648A0);
}

void func_ovl3_80164788(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80164860);
}

void func_ovl3_801647AC(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_801648F0);
}

void func_ovl3_801647D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag0 = 0;

    if ((ABS(fp->input.stick_range.x) >= FTKIRBY_COPYLINK_BOOMERANG_SMASH_STICK_MIN) && (fp->buffer_button_b < FTKIRBY_COPYLINK_BOOMERANG_SMASH_BUFFER))
    {
        fp->status_vars.kirby.copylink_specialn.is_smash = TRUE;
    }
    else fp->status_vars.kirby.copylink_specialn.is_smash = FALSE;
}

void func_ovl3_80164820(GObj *fighter_gobj)
{
    func_ovl2_800DEEC8(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x20U);
}

void func_ovl3_80164860(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x20U);
}

void func_ovl3_801648A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialAirNEmpty, fighter_gobj->anim_frame, 1.0F, 0U);

    fp->x192_flag_b0 = TRUE;
}

void func_ovl3_801648F0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialNEmpty, fighter_gobj->anim_frame, 1.0F, 0U);

    fp->x192_flag_b0 = TRUE;
}

void jtgt_ovl3_80164940(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_801647D0;

    if (fp->fighter_vars.kirby.copylink_boomerang_gobj != NULL)
    {
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialNEmpty, 0.0F, 1.0F, 0U);
        fp->x192_flag_b0 = TRUE;
    }
    else func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialN, 0.0F, 1.0F, 0U);

    func_ovl2_800E0830(fighter_gobj);
}

void jtgt_ovl3_801649C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_801647D0;

    if (fp->fighter_vars.kirby.copylink_boomerang_gobj != NULL)
    {
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialAirNEmpty, 0.0F, 1.0F, 0U);
        fp->x192_flag_b0 = TRUE;
    }
    else func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialAirN, 0.0F, 1.0F, 0U);

    func_ovl2_800E0830(fighter_gobj);
}

void func_ovl3_80164A40(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialAirNReturn, 0.0F, 1.0F, 0U);
    }
    else func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyLink_SpecialNReturn, 0.0F, 1.0F, 0U);

    func_ovl2_800E0830(fighter_gobj);
}