#include "ftcaptain.h"

void func_ovl3_8015FC30(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fp->x18F_flag_b3))
    {
        if (fp->cmd_flags.flag2 == 1)
        {

            if (func_ovl2_80101ED8(fighter_gobj) != FALSE)
            {
                fp->x18F_flag_b3 = TRUE;
            }

            fp->cmd_flags.flag2 = 0;
        }
    }

    else if (fp->cmd_flags.flag2 == 2)
    {
        func_ovl2_800E9C3C(fighter_gobj);
        fp->cmd_flags.flag2 = 0;
    }
}

void func_ovl3_8015FCB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->ground_or_air = air;
    fp->jumps_used = 1;
}

void func_ovl3_8015FCC8(GObj *fighter_gobj) // Unused?
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
}

void func_ovl3_8015FCE8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        if (fp->cmd_flags.flag3 != 0)
        {
            func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015FCB0);
        }
        else func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015FCB0);
    }
    else func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015FCB0);
}

void func_ovl3_8015FD50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        func_ovl3_8013E1C8(fighter_gobj);
    }
    else func_ovl3_8013F9E0(fighter_gobj);
}

void func_ovl3_8015FD90(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8015FD50);
}

void func_ovl3_8015FDB4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        fp->joint[0]->rotate.z = (f32)-atan2f(fp->coll_data.ground_angle.x, fp->coll_data.ground_angle.y);
        func_ovl2_800D8C14(fighter_gobj);
    }
    else if (fp->cmd_flags.flag0 != 0)
    {
        func_ovl2_800D91EC(fighter_gobj);
    }
    else func_ovl2_800D93E4(fighter_gobj);

    vec3f_scale(&fp->phys_info.vel_normal, fp->status_vars.captain.speciallw.vel_scale);

    func_ovl3_8015FC30(fighter_gobj);
}

void func_ovl3_8015FE4C(GObj *fighter_gobj)
{
    func_ovl2_800D8C14(fighter_gobj);
}

void func_ovl3_8015FE6C(GObj *fighter_gobj)
{
    func_ovl3_8015FC30(fighter_gobj);
    func_ovl2_800D93E4(fighter_gobj);
}

void func_ovl3_8015FE94(GObj *fighter_gobj)
{
    func_ovl2_800D93E4(fighter_gobj);
}

bool32 func_ovl3_8015FEB4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->cmd_flags.flag1 == 1) && (fp->coll_data.coll_mask & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL)))
    {
        func_ovl2_800DEEC8(fp);
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialLwBound, 0.0F, 1.0F, 0U);

        fp->cmd_flags.flag1 = 0;

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_8015FF2C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 == 2)
    {
        if (fp->ground_or_air == air)
        {
            func_ovl3_80160060(fighter_gobj);

            fp->cmd_flags.flag1 = 0;

            return TRUE;
        }
        fp->cmd_flags.flag1 = 0;
    }
    return FALSE;
}

void func_ovl3_8015FF88(GObj *fighter_gobj)
{
    func_ovl3_8015FCE8(fighter_gobj);

    if (func_ovl3_8015FEB4(fighter_gobj) == FALSE)
    {
        func_ovl3_8015FF2C(fighter_gobj);
    }
}

void func_ovl3_8015FFC0(GObj *fighter_gobj)
{
    func_ovl3_8015FCE8(fighter_gobj);
}

void func_ovl3_8015FFE0(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_801600EC);
}

void func_ovl3_80160004(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.captain.speciallw.scale_apply_timer < FTCAPTAIN_FALCONKICK_VEL_SCALE_APPLY_TIME)
    {
        fp->status_vars.captain.speciallw.scale_apply_timer++;

        fp->status_vars.captain.speciallw.vel_scale /= FTCAPTAIN_FALCONKICK_VEL_SCALE_DIV;
    }
}

void func_ovl3_80160038(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.captain.speciallw.scale_apply_timer = 0;

    fp->cmd_flags.flag0 = 0;
    fp->cmd_flags.flag3 = 0;
    fp->cmd_flags.flag1 = 0;
    fp->cmd_flags.flag2 = 0;

    fp->status_vars.captain.speciallw.vel_scale = 1.0F;
}

void func_ovl3_80160060(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 rot_z = fp->joint[0]->rotate.z;

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialLwEnd, 0.0F, 1.0F, 4U);

    fp->joint[0]->rotate.z = rot_z;
    fp->joint[1]->rotate.z = fp->joint[0]->rotate.z;

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}

void func_ovl3_801600EC(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialLwLanding, 0.0F, 1.0F, 0U);
}

void jtgt_ovl3_80160128(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_80160038;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialLw, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    fp->cb_hit_shield = func_ovl3_80160004;
    fp->cb_give_damage = func_ovl3_80160004;

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}

void jtgt_ovl3_801601A0(GObj *fighter_gobj) // Unused
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialLwEnd, 0.0F, 1.0F, 4U);
    func_ovl2_800E0830(fighter_gobj);

    fp->cb_give_damage = func_ovl3_80160004;

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}

void jtgt_ovl3_8016020C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_80160038;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialAirLw, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}