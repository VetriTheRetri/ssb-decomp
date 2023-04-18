#include "ftcaptain.h"



void func_ovl3_8015F7F0(GObj *fighter_gobj) // Falcon Punch
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fp->x18F_flag_b3))
    {
        if (fp->cmd_flags.flag0 == 1)
        {
            if (func_ovl2_80101F84(fighter_gobj) != FALSE)
            {
                fp->x18F_flag_b3 = TRUE;
            }
            fp->cmd_flags.flag0 = 0;
        }
    }

    else if (fp->cmd_flags.flag0 == 1)
    {
        func_ovl2_800E9C3C(fighter_gobj);
        fp->cmd_flags.flag0 = 2;
    }
}

f32 func_ovl3_8015F874(s32 stick_y)
{
    s32 temp_stick_y = ABS(stick_y);

    if (temp_stick_y >= 51)
    {
        temp_stick_y = 50;
    }

    temp_stick_y -= 10;

    if (temp_stick_y < 0)
    {
        temp_stick_y = 0;
    }

    if (stick_y < 0)
    {
        temp_stick_y = -temp_stick_y;
    }

    return (f32) (((temp_stick_y * 30) / 40.0F) * PI32) / 180.0F;
}

void func_ovl3_8015F8EC(GObj *fighter_gobj)
{
    func_ovl3_8015F7F0(fighter_gobj);
    func_ovl2_800D8C14(fighter_gobj);
}

void func_ovl3_8015F914(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 unused;
    f32 boost;

    if (fp->cmd_flags.flag1 != 0)
    {
        fp->cmd_flags.flag1 = 0;
        fp->fighter_vars.captain.falcon_punch_unk++;

        boost = func_ovl3_8015F874(fp->input.stick_range.y);

        fp->phys_info.vel_air.y = (f32)(__sinf(boost) * FTCAPTAIN_FALCONPUNCH_VEL_BASE);
        fp->phys_info.vel_air.x = (f32)(cosf(boost) * (f32)fp->lr * FTCAPTAIN_FALCONPUNCH_VEL_BASE);
    }

    func_ovl3_8015F7F0(fighter_gobj);

    switch (fp->cmd_flags.flag2)
    {
    case 0:
        func_ovl2_800D91EC(fighter_gobj);
        break;

    case 1:
        fp->phys_info.vel_air.y *= FTCAPTAIN_FALCONPUNCH_VEL_MUL;
        fp->phys_info.vel_air.x *= FTCAPTAIN_FALCONPUNCH_VEL_MUL;
        break;

    case 2:
        jtgt_ovl2_800D9160(fighter_gobj);
        break;
    }
}

void func_ovl3_8015FA2C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCollision_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x4006U);

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}

void func_ovl3_8015FA8C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x4006U);
    func_ovl2_800D8EB8(fp);

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}

void func_ovl3_8015FAF8(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015FA8C);
}

void func_ovl3_8015FB1C(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015FA2C);
}

void func_ovl3_8015FB40(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag2 = 0;
    fp->cmd_flags.flag1 = 0;
    fp->cmd_flags.flag0 = 0;
}

void func_ovl3_8015FB54() // Unused???
{
    return;
}

void jtgt_ovl3_8015FB5C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015FB40(fighter_gobj);

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}

void func_ovl3_8015FA8C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Captain_SpecialAirN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015FB40(fighter_gobj);

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}