#include <game/src/ft/chara/ftkirby/ftkirby.h>



void func_ovl3_80160810(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fp->is_statupdate_stop_gfx))
    {
        if (fp->command_vars.flags.flag0 == 1)
        {
            if (func_ovl2_80101F84(fighter_gobj) != FALSE)
            {
                fp->is_statupdate_stop_gfx = TRUE;
            }
            fp->command_vars.flags.flag0 = 0;
        }
    }
    else if (fp->command_vars.flags.flag0 == 1)
    {
        func_ovl2_800E9C3C(fighter_gobj);
        fp->command_vars.flags.flag0 = 2;
    }
}

f32 func_ovl3_80160894(s32 stick_y)
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

void func_ovl3_8016090C(GObj *fighter_gobj)
{
    func_ovl3_80160810(fighter_gobj);
    func_ovl2_800D8C14(fighter_gobj);
}

void func_ovl3_80160934(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 unused;
    f32 boost;

    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->command_vars.flags.flag1 = 0;
        fp->fighter_vars.kirby.copycaptain_falcon_punch_unk++;

        boost = func_ovl3_80160894(fp->input.stick_range.y);

        fp->phys_info.vel_air.y = (f32)(__sinf(boost) * FTKIRBY_COPYCAPTAIN_FALCONPUNCH_VEL_BASE);
        fp->phys_info.vel_air.x = (f32)(cosf(boost) * (f32)fp->lr * FTKIRBY_COPYCAPTAIN_FALCONPUNCH_VEL_BASE);
    }

    func_ovl3_80160810(fighter_gobj);

    switch (fp->command_vars.flags.flag2)
    {
    case 0:
        func_ovl2_800D91EC(fighter_gobj);
        break;

    case 1:
        fp->phys_info.vel_air.y *= FTKIRBY_COPYCAPTAIN_FALCONPUNCH_VEL_MUL; // Interestingly, Kirby's version multiplies by singles, 
        fp->phys_info.vel_air.x *= FTKIRBY_COPYCAPTAIN_FALCONPUNCH_VEL_MUL; // as opposed to Falcon's multiplying by doubles
        break;

    case 2:
        jtgt_ovl2_800D9160(fighter_gobj);
        break;
    }
}

void func_ovl3_80160A40(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyCaptain_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x4006U);
}

void func_ovl3_80160A80(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyCaptain_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x4006U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80160ACC(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80160A80);
}

void func_ovl3_80160AF0(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80160A40);
}

void func_ovl3_80160B14(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag2 = 0;
    fp->command_vars.flags.flag1 = 0;
    fp->command_vars.flags.flag0 = 0;
}

void func_ovl3_80160B28() // Unused
{
    return;
}

void jtgt_ovl3_80160B30(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyCaptain_SpecialN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80160B14(fighter_gobj);
}

void jtgt_ovl3_80160B70(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyCaptain_SpecialAirN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80160B14(fighter_gobj);
}