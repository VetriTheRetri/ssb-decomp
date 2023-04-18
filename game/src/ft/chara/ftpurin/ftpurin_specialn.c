#include "ftpurin.h"



void func_ovl3_80151260(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag2 = 0;
    fp->cmd_flags.flag1 = 0;
    fp->cmd_flags.flag0 = 0;
}

f32 func_ovl3_80151274(s32 stick_y)
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

    return (f32)(((temp_stick_y * 20) / 40.0F) * PI32) / 180.0F;
}

void func_ovl3_801512EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 unused;
    f32 boost;

    if (fp->cmd_flags.flag1 != 0)
    {
        fp->cmd_flags.flag1 = 0;

        fp->fighter_vars.purin.unk_0x0++;

        boost = func_ovl3_80151274(fp->input.stick_range.y);

        fp->phys_info.vel_air.y = (f32)(__sinf(boost) * FTPURIN_POUND_VEL_BASE);
        fp->phys_info.vel_air.x = (f32)(cosf(boost) * (f32)fp->lr * FTPURIN_POUND_VEL_BASE);
    }

    switch (fp->cmd_flags.flag2)
    {
    case 0:
        func_ovl2_800D91EC(fighter_gobj);
        break;

    case 1:
        fp->phys_info.vel_air.y *= FTPURIN_POUND_VEL_MUL;
        fp->phys_info.vel_air.x *= FTPURIN_POUND_VEL_MUL;
        break;

    case 2:
        jtgt_ovl2_800D9160(fighter_gobj);
        break;
    }
}

void func_ovl3_801513F0(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80151478);
}

void func_ovl3_80151414(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80151438);
}

void func_ovl3_80151438(GObj *fighter_gobj)
{
    ftCollision_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x92U);
}

void func_ovl3_80151478(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x92U);
    func_ovl2_800D8EB8(fp);
}

void jtgt_ovl3_801514C4(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialN, 0.0F, 1.0F, 0U);
    func_ovl3_80151260(fighter_gobj);
    ftAnim_Update(fighter_gobj);
}

void jtgt_ovl3_80151504(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialAirN, 0.0F, 1.0F, 0U);
    func_ovl3_80151260(fighter_gobj);
    ftAnim_Update(fighter_gobj);
}
