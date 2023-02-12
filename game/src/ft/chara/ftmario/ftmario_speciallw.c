#include <game/src/ft/chara/ftmario/ftmario.h>

void func_ovl3_801564F0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag3 != FALSE)
    {
        fp->status_vars.mario.speciallw.dust_gfx_int--;

        if (fp->status_vars.mario.speciallw.dust_gfx_int == 4)
        {
            func_ovl2_800EABDC(fighter_gobj, 11, 0, 0, 0, -fp->lr, 0, 0); // Spawn GFX
        }
        else if (fp->status_vars.mario.speciallw.dust_gfx_int == 0)
        {
            func_ovl2_800EABDC(fighter_gobj, 11, 0, 0, 0, fp->lr, 0, 0); // Spawn GFX 

            fp->status_vars.mario.speciallw.dust_gfx_int = 8;
        }
    }
    func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_801565A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag2 != FALSE)
    {
        fp->cmd_flags.flag2 = FALSE;
        fp->fighter_vars.mario.is_tornado_charge = TRUE;
    }
    func_ovl2_800D94E8(fighter_gobj);
}

f32 func_ovl3_801565E4(Fighter_Struct *fp, f32 drift)
{
    if (fp->cmd_flags.flag1 != FALSE)
    {
        fp->status_vars.mario.speciallw.tornado_drift -= 2.0F;

        drift += fp->status_vars.mario.speciallw.tornado_drift;

        if (drift < 0.0F)
        {
            drift = 0.0F;
        }
    }
    return drift;
}

void func_ovl3_80156630(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800D89E0(fp, 0, 0.025F, func_ovl3_801565E4(fp, 17.0F));
    func_ovl2_800D87D0(fighter_gobj);

    if ((fp->cmd_flags.flag3 != FALSE) && (fp->input.button_press & fp->input.button_mask_b))
    {
        fp->phys_info.vel_normal.y += FTMARIO_TORNADO_TAP_VEL_ADD;

        func_ovl3_80156808(fighter_gobj);
    }
}

void func_ovl3_801566C4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = fp->attributes;

    if ((fp->fighter_vars.mario.is_tornado_charge == FALSE) && (fp->cmd_flags.flag3 != FALSE) && (fp->input.button_press & fp->input.button_mask_b))
    {
        func_ovl2_800D8D34(fp, FTMARIO_TORNADO_TAP_VEL_ADD, 40.0F);
    }

    func_ovl2_800D8E50(fp, common_attrs);
    func_ovl2_800D8FC8(fp, 0, 0.03F, func_ovl3_801565E4(fp, 17.0F));
}

void func_ovl3_8015675C(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80156808);
}

void func_ovl3_80156780(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_801567B0);
}

void func_ovl3_801567A4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag3 = FALSE;
}

void func_ovl3_801567B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_801567A4(fighter_gobj);
    func_ovl2_800DEE98(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Mario_SpecialLw, fighter_gobj->anim_frame, 1.0F, 0x4000U);
    func_ovl2_800D8938(fp, 17.0F);
}

void func_ovl3_801567B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_801567A4(fighter_gobj);
    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Mario_SpecialAirLw, fighter_gobj->anim_frame, 1.0F, 0x4000U);
    func_ovl2_800D8D10(fp, 40.0F);
    func_ovl2_800D8E78(fp, 17.0F);
}

void func_ovl3_8015686C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag1 = FALSE;
    fp->cmd_flags.flag2 = FALSE;

    fp->status_vars.mario.speciallw.dust_gfx_int = 5;
    fp->status_vars.mario.speciallw.tornado_drift = 0.0F;
}

void jtgt_ovl3_8015688C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_801567A4(fighter_gobj);
    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Mario_SpecialAirLw, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    fp->phys_info.vel_normal.y = -7.0F;

    func_ovl2_800D8E78(fp, 17.0F);
    func_ovl3_8015686C(fighter_gobj);

    fp->unk_0x28E_bit_0x8 = FALSE; // Related to staling?
}


void jtgt_ovl3_80156910(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 tornado_vel_y;

    func_ovl3_801567A4(fighter_gobj);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Mario_SpecialAirLw, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    tornado_vel_y = (fp->fighter_vars.mario.is_tornado_charge != FALSE) ? 0.0F : 22.0F;

    fp->phys_info.vel_normal.y = (f32)(15.0F - tornado_vel_y);

    func_ovl2_800D8E78(fp, 17.0F);
    func_ovl3_8015686C(fighter_gobj);
}
