#include "ftdonkey.h"

void func_ovl3_8015B6D0(GObj *fighter_gobj)
{
    func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_8015B6F0(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, FTDONKEY_SPINNINGKONG_FALLSPECIAL_DRIFT, FALSE, TRUE, FALSE, FTDONKEY_SPINNINGKONG_LANDING_LAG, TRUE);
    }
}

void func_ovl3_8015B744(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800D89E0(fp, 0, FTDONKEY_SPINNINGKONG_GROUND_ACCEL, FTDONKEY_SPINNINGKONG_GROUND_VEL_MAX);
    func_ovl2_800D87D0(fighter_gobj);
}

void func_ovl3_8015B780(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCommonAttributes *attributes = fp->attributes;

    f32 gravity_mul = (fp->command_vars.flags.flag1 != 0U) ? FTDONKEY_SPINNINGKONG_END_GRAVITY_MUL : FTDONKEY_SPINNINGKONG_START_GRAVITY_MUL;

    func_ovl2_800D8D68(fp, attributes->gravity * gravity_mul, attributes->fall_speed_max);

    func_ovl2_800D8FC8(fp, 0, FTDONKEY_SPINNINGKONG_AIR_ACCEL, FTDONKEY_SPINNINGKONG_AIR_VEL_MAX);
}

void func_ovl3_8015B800(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015B898);
}

void func_ovl3_8015B824(GObj *fighter_gobj)
{
    func_ovl2_800DE80C(fighter_gobj, func_ovl3_8015B848);
}

void func_ovl3_8015B848(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCollision_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_SpecialHi, fighter_gobj->anim_frame, 1.0F, 0x4000U);
    func_ovl2_800D8938(fp, FTDONKEY_SPINNINGKONG_GROUND_VEL_MAX);
}

void func_ovl3_8015B898(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_SpecialAirHi, fighter_gobj->anim_frame, 1.0F, 0x4000U);
    func_ovl2_800D8E78(fp, FTDONKEY_SPINNINGKONG_AIR_VEL_MAX);
}

void func_ovl3_8015B8E8(GObj *fighter_gobj, bool32 stale_unk)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    ftStatus_Update(fighter_gobj, ftStatus_Donkey_SpecialAirHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    func_ovl2_800D8E78(fp, FTDONKEY_SPINNINGKONG_AIR_VEL_MAX);

    fp->jumps_used = attributes->jumps_max;

    fp->command_vars.flags.flag1 = 0;

    fp->status_vars.donkey.specialhi.unk_0x0 = 9;

    if (stale_unk == FALSE)
    {
        fp->flags_lw.flags_0x800 = FALSE;
    }
}

void jtgt_ovl3_8015B974(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);

    fp->phys_info.vel_air.y = 0.0F;

    func_ovl3_8015B8E8(fighter_gobj, FALSE);
}

void jtgt_ovl3_8015B9B8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->phys_info.vel_air.y = FTDONKEY_SPINNINGKONG_AIR_VEL_Y;

    func_ovl3_8015B8E8(fighter_gobj, TRUE);
}
