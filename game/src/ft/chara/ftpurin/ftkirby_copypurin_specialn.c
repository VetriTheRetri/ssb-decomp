#include <game/src/ft/chara/ftkirby/ftkirby.h>



void func_ovl3_80151860(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag2 = 0;
    fp->cmd_flags.flag1 = 0;
    fp->cmd_flags.flag0 = 0;
}

f32 func_ovl3_80151874(s32 stick_y)
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

void func_ovl3_801518EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 unused;
    f32 boost;

    if (fp->cmd_flags.flag1 != 0)
    {
        fp->cmd_flags.flag1 = 0;

        fp->fighter_vars.kirby.copypurin_unk++;

        boost = func_ovl3_80151874(fp->input.stick_range.y);

        fp->phys_info.vel_normal.y = (f32)(__sinf(boost) * FTKIRBY_COPYPURIN_POUND_VEL_BASE);
        fp->phys_info.vel_normal.x = (f32)(cosf(boost) * (f32)fp->lr * FTKIRBY_COPYPURIN_POUND_VEL_BASE);
    }

    switch (fp->cmd_flags.flag2)
    {
    case 0:
        func_ovl2_800D91EC(fighter_gobj);
        break;

    case 1:
        fp->phys_info.vel_normal.y *= FTKIRBY_COPYPURIN_POUND_VEL_MUL;
        fp->phys_info.vel_normal.x *= FTKIRBY_COPYPURIN_POUND_VEL_MUL;
        break;

    case 2:
        jtgt_ovl2_800D9160(fighter_gobj);
        break;
    }
}

void func_ovl3_801519F0(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80151A78);
}

void func_ovl3_80151A14(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80151A38);
}

void func_ovl3_80151A38(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyPurin_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x92U);
}

void func_ovl3_80151A78(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyPurin_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x92U);
    func_ovl2_800D8EB8(fp);
}

void jtgt_ovl3_80151AC4(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyPurin_SpecialN, 0.0F, 1.0F, 0U);
    func_ovl3_80151860(fighter_gobj);
    func_ovl2_800E0830(fighter_gobj);
}

void jtgt_ovl3_80151B04(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyPurin_SpecialAirN, 0.0F, 1.0F, 0U);
    func_ovl3_80151860(fighter_gobj);
    func_ovl2_800E0830(fighter_gobj);
}
