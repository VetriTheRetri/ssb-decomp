#include "ftcaptain.h"



void func_ovl3_80160280(Fighter_Struct *fp)
{
    func_ovl2_800E80A4(fp, 32, func_ovl3_80160690, func_ovl3_8014D2A0);
}

void func_ovl3_801602B0(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, FTCAPTAIN_FALCONDIVE_FALLSPECIAL_DRIFT, FALSE, TRUE, TRUE, FTCAPTAIN_FALCONDIVE_LANDING_LAG, FALSE);
    }
}

void func_ovl3_80160304(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fighter_gobj->anim_frame <= 0.0F) || (fp->cmd_flags.flag0 != 0))
    {
        Fighter_Struct *fp_catch = FighterGetStruct(fp->catch_gobj);

        fp_catch->status_vars.common.capturecaptain.capture_flag |= 0x2;

        func_ovl2_801008F4(1); // Apply screen shake/rumble?
        func_ovl3_80160730(fighter_gobj);
    }
}

void func_ovl3_80160370(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 stick_x;

    if (fp->cmd_flags.flag1 != 0)
    {
        fp->cmd_flags.flag1 = 0;

        stick_x = ABS(fp->input.stick_range.x);

        if (stick_x >= 19)
        {
            func_ovl2_800E8044(fp);

            fp->joint[0]->rotate.y = (f32)fp->lr * HALF_PI32;
        }
    }
}

void func_ovl3_801603F0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = AttributesGetStruct(fp);

    fp->phys_info.vel_normal.x = fp->status_vars.captain.specialhi.vel.x;
    fp->phys_info.vel_normal.y = fp->status_vars.captain.specialhi.vel.y;
    fp->phys_info.vel_normal.z = 0.0F;

    if (func_ovl2_800D8EDC(fp, common_attrs->aerial_speed_max_x * FTCAPTAIN_FALCONDIVE_AIR_SPEED_MAX_MUL) == FALSE)
    {
        func_ovl2_800D8FC8(fp, 8, common_attrs->aerial_acceleration * FTCAPTAIN_FALCONDIVE_AIR_ACCEL_MUL, common_attrs->aerial_speed_max_x * FTCAPTAIN_FALCONDIVE_AIR_SPEED_MAX_MUL);
        func_ovl2_800D9074(fp, common_attrs);
    }
    fp->status_vars.captain.specialhi.vel.x = fp->phys_info.vel_normal.x;
    fp->status_vars.captain.specialhi.vel.y = fp->phys_info.vel_normal.y;

    func_ovl2_800D93E4(fighter_gobj);

    fp->phys_info.vel_normal.x += fp->status_vars.captain.specialhi.vel.x;
    fp->phys_info.vel_normal.y += fp->status_vars.captain.specialhi.vel.y;
}

void func_ovl3_801604D8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f vec;

    if (!(fp->status_vars.captain.specialhi.unk_0x0 & 4))
    {
        func_ovl3_8014D0F0(fighter_gobj, fp->catch_gobj, &vec);
        if (vec3f_mag(&vec) > 180.0F)
        {
            vec3f_normalize(&vec);
            vec3f_scale(&vec, 180.0F);
        }
        vec3f_sub_from(&DObjGetStruct(fighter_gobj)->translate, &vec);
    }
}

void func_ovl3_80160560(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->phys_info.vel_normal.y < 0.0F)
    {
        if (fp->cmd_flags.flag2 == 0)
        {
            func_ovl2_800DE978(fighter_gobj);
        }
        else
        {
            func_ovl2_800DE958(fighter_gobj);
            fp->cmd_flags.flag2--;
        }
    }
    else if ((func_ovl2_800DE87C(fighter_gobj) != FALSE) && (fp->coll_data.coll_type & 0x3000))
    {
        func_ovl3_80144C24(fighter_gobj);
    }
}

void func_ovl3_801605FC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->jumps_used = fp->attributes->jumps_max;

    fp->status_vars.captain.specialhi.unk_0x0 = 0;

    fp->cmd_flags.flag0 = 0;
    fp->cmd_flags.flag1 = 0;
    fp->cmd_flags.flag2 = FTCAPTAIN_FALCONDIVE_UNK_TIMER;

    fp->status_vars.captain.specialhi.vel.x = 0.0F;
    fp->status_vars.captain.specialhi.vel.y = 0.0F;
}

void jtgt_ovl3_80160630(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);

    fp->cb_status = func_ovl3_801605FC;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialHi, 0.0F, 1.0F, 0U);
    func_ovl3_80160280(fp);
    func_ovl2_800E0830(fighter_gobj);
}

void func_ovl3_80160690(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj), *fp_catch;
    GObj *unk_gobj;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialAirHi, 0.0F, 1.0F, 4U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl2_800E8098(fp, 0x3FU);
    func_ovl2_800D9444(fighter_gobj);

    unk_gobj = fp->unk_gobj;
    fp->catch_gobj = unk_gobj;

    fp_catch = FighterGetStruct(unk_gobj); // No NULL check, might be dangerous

    if (fp_catch->ground_or_air == air)
    {
        fp->status_vars.common.capturecaptain.capture_flag |= 4;
        fp->x192_flag_b3 = FALSE;
    }
    else fp->x192_flag_b3 = TRUE;
}

void func_ovl3_80160730(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialHiCatch, 0.0F, 1.0F, 4U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl2_800E8098(fp, 0U);

    if ((fp->x192_flag_b3 == TRUE) && (fp->catch_gobj != NULL))
    {
        func_ovl3_8014ADB0(fighter_gobj);
    }
    fp->catch_gobj = NULL;
}

void jtgt_ovl3_801607B4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = &func_ovl3_801605FC;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Captain_SpecialHiRelease, 0.0F, 1.0F, 0U);
    func_ovl3_80160280(fp);
    func_ovl2_800E0830(fighter_gobj);
}