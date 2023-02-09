#include "ftkirby.h"

void func_ovl3_80161360(GObj *fighter_gobj)
{
    return;
}

void func_ovl3_80161368(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->armor < FTKIRBY_STONE_HEALTH_MID) // Apply color overlay based on remaining Stone HP
    {
        if (fp->armor < FTKIRBY_STONE_HEALTH_LOW)
        {
            if (fp->status_vars.kirby.speciallw.colanim_id != FTKIRBY_STONE_COLANIM_ID_LOW)
            {
                func_ovl2_800E9814(fighter_gobj, FTKIRBY_STONE_COLANIM_ID_LOW, 0);
                fp->status_vars.kirby.speciallw.colanim_id = FTKIRBY_STONE_COLANIM_ID_LOW;
            }
        }
        else if (fp->status_vars.kirby.speciallw.colanim_id != FTKIRBY_STONE_COLANIM_ID_MID)
        {
            func_ovl2_800E9814(fighter_gobj, FTKIRBY_STONE_COLANIM_ID_MID, 0);
            fp->status_vars.kirby.speciallw.colanim_id = FTKIRBY_STONE_COLANIM_ID_MID;
        }
    }
    else if (fp->status_vars.kirby.speciallw.colanim_id != FTKIRBY_STONE_COLANIM_ID_HIGH)
    {
        func_ovl2_800E9814(fighter_gobj, FTKIRBY_STONE_COLANIM_ID_HIGH, 0);
        fp->status_vars.kirby.speciallw.colanim_id = FTKIRBY_STONE_COLANIM_ID_HIGH;
    }
}

void func_ovl3_8016141C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->x191_flag_b2 = TRUE;

    fp->armor = FTKIRBY_STONE_HEALTH_MAX;
    fp->status_vars.kirby.speciallw.duration = FTKIRBY_STONE_DURATION_MAX;
    fp->status_vars.kirby.speciallw.colanim_id = FTKIRBY_STONE_COLANIM_ID_HIGH;

    func_ovl2_800E9814(fighter_gobj, FTKIRBY_STONE_COLANIM_ID_HIGH, 0);
}

void func_ovl3_80161468(Fighter_Struct *fp)
{
    fp->phys_info.vel_normal.y = FTKIRBY_STONE_FALL_VEL;
}

f32 func_ovl3_80161478(Fighter_Struct *fp)
{
    f32 rot_z = -atan2f(fp->coll_data.ground_angle.x, fp->coll_data.ground_angle.y);

    fp->joint[0]->rotate.z = rot_z;

    return rot_z;
}

bool32 func_ovl3_801614B4(GObj *fighter_gobj, bool32 is_allow_release)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (is_allow_release == TRUE)
    {
        if (fp->input.button_press & fp->input.button_mask_b)
        {
            return TRUE;
        }
    }
    else if ((fp->status_vars.kirby.speciallw.duration < (FTKIRBY_STONE_DURATION_MAX - FTKIRBY_STONE_DURATION_MIN)) && (fp->input.button_press & fp->input.button_mask_b))
    {
        return TRUE;
    }

    if (fp->status_vars.kirby.speciallw.duration > 0)
    {
        fp->status_vars.kirby.speciallw.duration--;

        return FALSE;
    }
    else return TRUE;
}

void func_ovl3_80161530(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != 0)
    {
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialLwHold, 0.0F, 1.0F, 0x32U);
        func_ovl3_8016141C(fighter_gobj);

        fp->cmd_flags.flag1 = 0;
    }
    else func_ovl2_800D9480(fighter_gobj, func_ovl3_80161AEC);
}

void func_ovl3_80161598(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != 0)
    {
        func_ovl3_8016141C(fighter_gobj);

        fp->cmd_flags.flag1 = 0;
    }
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80161C0C);
}

void func_ovl3_801615E4(GObj *fighter_gobj, bool32 is_release)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fp->x191_flag_b2) && (fp->cmd_flags.flag1 != 0))
    {
        if (is_release == FALSE)
        {
            func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialLwHold, 0.0F, 1.0F, 0x32U);
        }
        func_ovl3_8016141C(fighter_gobj);

        fp->cmd_flags.flag1 = 0;
        fp->cmd_flags.flag2 = 1;
    }
    if (fp->cmd_flags.flag2 != 0)
    {
        if (func_ovl3_801614B4(fighter_gobj, FALSE) == TRUE)
        {
            (is_release == FALSE) ? func_ovl3_80161B2C(fighter_gobj) : func_ovl3_80161C5C(fighter_gobj);

            fp->cmd_flags.flag2 = 0;
        }
        func_ovl3_80161368(fighter_gobj);
    }
}

void func_ovl3_801616B0(GObj *fighter_gobj)
{
    func_ovl3_801615E4(fighter_gobj, FALSE);
}

void func_ovl3_801616D0(GObj *fighter_gobj)
{
    func_ovl3_801615E4(fighter_gobj, TRUE);
}

void func_ovl3_801616F0(GObj *fighter_gobj, bool32 is_release)
{
    if (func_ovl3_801614B4(fighter_gobj, TRUE) == TRUE)
    {
        (is_release == FALSE) ? func_ovl3_80161B2C(fighter_gobj) : func_ovl3_80161C5C(fighter_gobj);
    }
    func_ovl3_80161368(fighter_gobj);
}

void func_ovl3_8016174C(GObj *fighter_gobj)
{
    func_ovl3_801616F0(fighter_gobj, FALSE);
}

void func_ovl3_8016176C(GObj *fighter_gobj)
{
    func_ovl3_801616F0(fighter_gobj, TRUE);
}

extern f32 D_ovl2_8012C4E0[6];

void func_ovl3_8016178C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = fp->attributes;
    f32 temp_slide_angle;
    f32 ground_vel_x;
    f32 slide_angle;

    temp_slide_angle = func_ovl3_80161478(fp);

    slide_angle = temp_slide_angle;

    if (FTKIRBY_STONE_SLIDE_ANGLE < temp_slide_angle)
    {
        slide_angle = FTKIRBY_STONE_SLIDE_ANGLE;
    }

    else if (temp_slide_angle < -FTKIRBY_STONE_SLIDE_ANGLE)
    {
        slide_angle = -FTKIRBY_STONE_SLIDE_ANGLE;
    }

    fp->phys_info.vel_ground.x -= (__sinf(slide_angle) * FTKIRBY_STONE_SLIDE_VEL_MUL * (f32)fp->lr);

    ground_vel_x = fp->phys_info.vel_ground.x;

    if (ground_vel_x > FTKIRBY_STONE_SLIDE_CLAMP_VEL_X)
    {
        fp->phys_info.vel_ground.x = FTKIRBY_STONE_SLIDE_CLAMP_VEL_X;
    }
    else if (ground_vel_x < -FTKIRBY_STONE_SLIDE_CLAMP_VEL_X)
    {
        fp->phys_info.vel_ground.x = -FTKIRBY_STONE_SLIDE_CLAMP_VEL_X;
    }

    func_ovl2_800D8978(fp, (D_ovl2_8012C4E0[fp->coll_data.clip_flag & 0xFFFF00FF] * common_attrs->traction * FTKIRBY_STONE_SLIDE_TRACTION_MUL));
    func_ovl2_800D87D0(fighter_gobj);
}

void func_ovl3_801618C4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        func_ovl2_800DEEC8(fp);
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialAirLwStart, fighter_gobj->anim_frame, 1.0F, 0x12U);
        func_ovl3_80161468(fp);
    }
}

void func_ovl3_80161920(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        func_ovl2_800DEEC8(fp);
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialAirLwHold, fighter_gobj->anim_frame, 1.0F, 0x12U);
    }
}

void func_ovl3_80161974(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        func_ovl2_800DEEC8(fp);
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialAirLwFall, 0.0F, 1.0F, 0x32U);

        fp->x191_flag_b2 = TRUE;

        func_ovl3_80161468(fp);
    }
}

void func_ovl3_801619E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        func_ovl2_800DEE98(fp);
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialLwStart, fighter_gobj->anim_frame, 1.0F, 0U);
    }
}

void func_ovl3_80161A30(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        func_ovl2_800DEE98(fp);
        func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialAirLwLand, 0.0F, 1.0F, 0x32U);

        fp->x191_flag_b2 = TRUE;
    }
}

void jtgt_ovl3_80161A94(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialLwStart, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    fp->cmd_flags.flag2 = 0;
    fp->cmd_flags.flag1 = 0;

    fp->phys_info.vel_normal.y = 0.0F;
    fp->phys_info.vel_normal.x = 0.0F;
}

void jtgt_ovl3_80161AEC(GObj *fighter_gobj) // Unused
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialLwUnk, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    func_ovl3_80161360(fighter_gobj);
}

void func_ovl3_80161B2C(GObj *fighter_gobj)
{
    func_ovl2_800DEEC8(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialLwEnd, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
}

void jtgt_ovl3_80161B70(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    u32 armor_flag = fp->x191_flag_b2;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialAirLwStart, 0.0F, 1.0F, 0x32U);
    func_ovl2_800E0830(fighter_gobj);

    if ((fp->x191_flag_b2 = armor_flag & TRUE) != FALSE) // WAT
    {
        fp->cmd_flags.flag2 = 1;
    }
    else
    {
        fp->cmd_flags.flag2 = 0;
        fp->cmd_flags.flag1 = 0;
    }

    fp->phys_info.vel_normal.y = 0.0F;
    fp->phys_info.vel_normal.x = 0.0F;
}

void func_ovl3_80161C0C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialAirLwHold, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80161360(fighter_gobj);
    func_ovl3_80161468(fp);
}

void func_ovl3_80161C5C(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialAirLwEnd, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
}