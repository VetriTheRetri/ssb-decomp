#include "ftlink.h"

void func_ovl3_801636D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->fighter_vars.link.boomerang_gobj != NULL)
    {
        func_ovl3_8016800C(fp->fighter_vars.link.boomerang_gobj);

        fp->fighter_vars.link.boomerang_gobj = NULL;
    }
}

void func_ovl3_80163708(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    if (fp->command_vars.flags.flag0 != 0)
    {
        fp->command_vars.flags.flag0 = 0;

        pos.x = 0.0F;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTLINK_BOOMERANG_SPAWN_JOINT], &pos);

        fp->fighter_vars.link.boomerang_gobj = func_ovl3_8016DA78(fighter_gobj, &pos);
    }
}

void func_ovl3_80163770(GObj *fighter_gobj)
{
    func_ovl3_80163708(fighter_gobj);
    func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_80163798(GObj *fighter_gobj)
{
    func_ovl3_80163708(fighter_gobj);
    func_ovl2_800D94E8(fighter_gobj);
}

void func_ovl3_801637C0(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_801638AC);
}

void func_ovl3_80163808(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_801638EC);
}

void func_ovl3_8016382C(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8016397C);
}

void func_ovl3_80163850(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = 0;

    if ((ABS(fp->input.pl.stick_range.x) >= FTLINK_BOOMERANG_SMASH_STICK_MIN) && (fp->hold_stick_x < FTLINK_BOOMERANG_SMASH_BUFFER))
    {
        fp->status_vars.link.specialn.is_smash = TRUE;

        fp->flags_lw.flags_0x1000 = TRUE;
    }
    else fp->status_vars.link.specialn.is_smash = FALSE;
}

void func_ovl3_801638AC(GObj *fighter_gobj)
{
    ftMapCollide_SetAir(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x20U);
}

void func_ovl3_801638EC(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x20U);
}

void func_ovl3_8016392C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirNEmpty, fighter_gobj->anim_frame, 1.0F, 0U);
    fp->x192_flag_b0 = TRUE;
}

void func_ovl3_8016397C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialNEmpty, fighter_gobj->anim_frame, 1.0F, 0U);
    fp->x192_flag_b0 = TRUE;
}

void jtgt_ovl3_801639CC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_80163850;

    if (fp->fighter_vars.link.boomerang_gobj != NULL)
    {
        ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialNEmpty, 0.0F, 1.0F, 0U);

        fp->x192_flag_b0 = TRUE;
    }
    else ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialN, 0.0F, 1.0F, 0U);

    ftAnim_Update(fighter_gobj);
}

void jtgt_ovl3_80163A4C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_80163850;

    if (fp->fighter_vars.link.boomerang_gobj != NULL)
    {
        ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirNEmpty, 0.0F, 1.0F, 0U);

        fp->x192_flag_b0 = TRUE;
    }
    else ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirN, 0.0F, 1.0F, 0U);

    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80163ACC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirNReturn, 0.0F, 1.0F, 0U);
    }
    else ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialNReturn, 0.0F, 1.0F, 0U);

    ftAnim_Update(fighter_gobj);
}

void jtgt_ovl3_80164348(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_8016426C;

    ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->phys_info.vel_air.y = 69.0F;

    fp->jumps_used = fp->attributes->jumps_max;

    fp->cb_take_damage = func_ovl3_80163EFC;
    fp->cb_update_gfx = func_ovl3_80163D00;
}