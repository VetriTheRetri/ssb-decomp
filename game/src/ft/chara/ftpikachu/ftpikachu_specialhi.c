#include "ftpikachu.h"

#define HALF_PI32 1.5707964F

void func_ovl3_801527B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.pikachu.specialhi.anim_frames--;

    if (fp->status_vars.pikachu.specialhi.anim_frames == 0) // Travel time must be unsigned in order for this to match; comparing == 0 also matches on both unsigned and signed
    {
        func_ovl3_80152E48(fighter_gobj);
    }
}

void func_ovl3_801527E4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.pikachu.specialhi.anim_frames--;

    if (fp->status_vars.pikachu.specialhi.anim_frames == 0) // Travel time must be unsigned in order for this to match; comparing == 0 also matches on both unsigned and signed
    {
        func_ovl3_80152FEC(fighter_gobj);
    }
}

void func_ovl3_80152818(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = fp->attributes;

    func_ovl2_800D8D68(fp, 0.8F, common_attrs->fall_speed_max);

    if (func_ovl2_800D8FA8(fp, common_attrs) == FALSE)
    {
        func_ovl2_800D9074(fp, common_attrs);
    }
}

void func_ovl3_8015286C(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_801528F4);
}

void func_ovl3_80152890(GObj *fighter_gobj)
{
    func_ovl2_800DE80C(fighter_gobj, func_ovl3_801528B4);
}

void func_ovl3_801528B4(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialHiStart, fighter_gobj->anim_frame, 0.0F, 0x92U);
}

void func_ovl3_801528F4(GObj *fighter_gobj)
{
    func_ovl2_800DEEC8(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirHiStart, fighter_gobj->anim_frame, 0.0F, 0x92U);
}

void func_ovl3_80152934(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag1 = 0;

    fp->status_vars.pikachu.specialhi.anim_frames = FTPIKACHU_QUICKATTACK_START_TIME;
    fp->status_vars.pikachu.specialhi.is_subsequent_zip = FALSE;
    fp->status_vars.pikachu.specialhi.coll_timer_unk = 0;

    fp->phys_info.vel_ground.x = 0.0F;
    fp->phys_info.vel_normal.y = 0.0F;
    fp->phys_info.vel_normal.x = 0.0F;
}

void func_ovl3_80152960(GObj *fighter_gobj)
{
    func_ovl2_800E8A24(fighter_gobj, gmHitCollision_Status_Intangible); // Set hit status

    func_ovl2_800E9814(fighter_gobj, FTPIKACHU_QUICKATTACK_COLANIM_ID, 0); // Apply color animation

    func_8000BB04(fighter_gobj, 0.0F); // Set animation speed (0.0F = freeze)
}

void jtgt_ovl3_801529A0(GObj *fighter_gobj)
{
    func_ovl3_80152934(fighter_gobj);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialHiStart, 0.0F, 0.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80152960(fighter_gobj);
}

void jtgt_ovl3_801529EC(GObj *fighter_gobj)
{
    func_ovl3_80152934(fighter_gobj);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirHiStart, 0.0F, 0.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80152960(fighter_gobj);
}

void func_ovl3_80152A38(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.pikachu.specialhi.travel_time--;

    if (fp->status_vars.pikachu.specialhi.travel_time <= 0) // NOW you're checking if less than too?
    {
        func_ovl3_801535F4(fighter_gobj);
    }
}

void func_ovl3_80152A6C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.pikachu.specialhi.anim_frames--;

    if (fp->status_vars.pikachu.specialhi.anim_frames <= 0) // NOW you're checking if less than too?
    {
        func_ovl3_80153654(fighter_gobj);
    }
}

void func_ovl3_80152AA0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->joint[FTPIKACHU_QUICKATTACK_BASE_JOINT]->rotate.x = (atan2f(fp->phys_info.vel_normal.x, fp->phys_info.vel_normal.y) * (f32)fp->lr) - HALF_PI32;

    fp->joint[FTPIKACHU_QUICKATTACK_BASE_JOINT]->scale.x = FTPIKACHU_QUICKATTACK_SCALE_X;
    fp->joint[FTPIKACHU_QUICKATTACK_BASE_JOINT]->scale.y = FTPIKACHU_QUICKATTACK_SCALE_Y;
    fp->joint[FTPIKACHU_QUICKATTACK_BASE_JOINT]->scale.z = FTPIKACHU_QUICKATTACK_SCALE_Z;

    func_ovl2_800EB528(fp->joint[FTPIKACHU_QUICKATTACK_BASE_JOINT]);
}

void func_ovl3_80152B24(GObj *fighter_gobj)
{
    jtgt_ovl2_800D8B94(fighter_gobj);
    func_ovl3_80152AA0(fighter_gobj);
}

void func_ovl3_80152B4C(GObj *fighter_gobj)
{
    func_ovl3_80152AA0(fighter_gobj);
}

void func_ovl3_80152B6C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        if (fp->coll_data.unk_0x56 & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
        {
            func_ovl2_800DEEC8(fp);
            func_ovl3_80153654(fighter_gobj);
        }
        else func_ovl3_80152DD8(fighter_gobj);
    }
    else if (fp->coll_data.unk_0x56 & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
    {
        func_ovl3_801535F4(fighter_gobj);
    }
}

bool32 func_ovl3_80152BF4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fp->coll_data.clip_flag & 0x4000) || (fp->status_vars.pikachu.specialhi.coll_timer_unk >= 2))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80152C2C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.pikachu.specialhi.coll_timer_unk++;

    if (func_ovl2_800DE798(fighter_gobj, func_ovl3_80152BF4) != FALSE)
    {
        if (fp->coll_data.coll_type & 0x3000)
        {
            func_ovl3_80144C24(fighter_gobj);

        }
        else if (FTPIKACHU_QUICKATTACK_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.ground_angle, &fp->phys_info.vel_normal))
        {
            func_ovl2_800DEE98(fp);
            func_ovl3_801535F4(fighter_gobj);
        }
        else func_ovl3_80152D98(fighter_gobj);
    }
    else
    {
        if ((fp->coll_data.unk_0x56 & MPCOLL_MASK_CEIL) && (FTPIKACHU_QUICKATTACK_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.ceil_angle, &fp->phys_info.vel_normal)))
        {
            func_ovl3_80153654(fighter_gobj);
        }
        if ((fp->coll_data.unk_0x56 & MPCOLL_MASK_RWALL) && (FTPIKACHU_QUICKATTACK_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.rwall_angle, &fp->phys_info.vel_normal)))
        {
            func_ovl3_80153654(fighter_gobj);
        }
        if ((fp->coll_data.unk_0x56 & MPCOLL_MASK_LWALL) && (FTPIKACHU_QUICKATTACK_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.lwall_angle, &fp->phys_info.vel_normal)))
        {
            func_ovl3_80153654(fighter_gobj);
        }
    }
}

void func_ovl3_80152D98(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialHi, fighter_gobj->anim_frame, 0.0F, 0x92U);
}

void func_ovl3_80152DD8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirHi, fighter_gobj->anim_frame, 0.0F, 0x92U);

    fp->jumps_used = fp->attributes->jumps_max;
}

void func_ovl3_80152E2C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.pikachu.specialhi.anim_frames = FTPIKACHU_QUICKATTACK_ZIP_TIME;
    fp->jumps_used = fp->attributes->jumps_max;
}

void func_ovl3_80152E48(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 sqrt_stick_range;
    f32 temp_stick_x;
    Vec3f stick_angle;
    f32 temp_stick_y;

    temp_stick_x = fp->input.stick_range.x;
    temp_stick_y = fp->input.stick_range.y;

    sqrt_stick_range = sqrtf(SQUARE(temp_stick_x) + SQUARE(temp_stick_y));

    if (sqrt_stick_range > 80.0F)
    {
        sqrt_stick_range = 80.0F;
    }
    if (!(sqrt_stick_range < FTPIKACHU_QUICKATTACK_STICK_RANGE_MIN) && !(fp->coll_data.clip_flag & 0x4000))
    {
        stick_angle.x = fp->input.stick_range.x;
        stick_angle.y = fp->input.stick_range.y;
        stick_angle.z = 0.0F;

        if ((vec3f_angle_diff(&fp->coll_data.ground_angle, &stick_angle) < HALF_PI32)) goto block_end;
        {
            fp->status_vars.pikachu.specialhi.stick_range.x = stick_angle.x;
            fp->status_vars.pikachu.specialhi.stick_range.y = stick_angle.y;

            func_ovl2_800E8044(fp);
            func_ovl3_80152E2C(fighter_gobj);

            fp->phys_info.vel_ground.x = (FTPIKACHU_QUICKATTACK_VEL_BASE * sqrt_stick_range) + FTPIKACHU_QUICKATTACK_VEL_ADD;

            if (fp->status_vars.pikachu.specialhi.is_subsequent_zip != FALSE)
            {
                fp->phys_info.vel_ground.x *= FTPIKACHU_QUICKATTACK_VEL_MUL;
            }
            func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialHi, 0.0F, 0.0F, 0U);
            func_ovl2_800E0830(fighter_gobj);
            return;
        }
    }
block_end:
    func_ovl2_800DEEC8(fp);

    func_ovl3_80152FEC(fighter_gobj);
}

void func_ovl3_80152FEC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 tangent;
    f32 sqrt_stick_range = sqrtf(SQUARE((f32)fp->input.stick_range.x) + SQUARE((f32)fp->input.stick_range.y));

    if (sqrt_stick_range > 80.0F)
    {
        sqrt_stick_range = 80.0F;
    }

    func_ovl2_800E8044(fp);

    if (sqrt_stick_range > FTPIKACHU_QUICKATTACK_STICK_RANGE_MIN)
    {
        tangent = atan2f((f32)fp->input.stick_range.y, (f32)(fp->input.stick_range.x * fp->lr));

        fp->status_vars.pikachu.specialhi.stick_range.x = (s32)fp->input.stick_range.x;
        fp->status_vars.pikachu.specialhi.stick_range.y = (s32)fp->input.stick_range.y;
    }
    else
    {
        tangent = 0.9F;
        sqrt_stick_range = 80.0F;

        fp->status_vars.pikachu.specialhi.stick_range.x = 0;
        fp->status_vars.pikachu.specialhi.stick_range.y = 80;
    }

    func_ovl3_80152E2C(fighter_gobj);

    fp->phys_info.vel_normal.x = cosf(tangent) * ((FTPIKACHU_QUICKATTACK_VEL_BASE * sqrt_stick_range) + FTPIKACHU_QUICKATTACK_VEL_ADD) * (f32)fp->lr;

    fp->phys_info.vel_normal.y = __sinf(tangent) * ((FTPIKACHU_QUICKATTACK_VEL_BASE * sqrt_stick_range) + FTPIKACHU_QUICKATTACK_VEL_ADD);

    if (fp->status_vars.pikachu.specialhi.is_subsequent_zip != FALSE)
    {
        fp->phys_info.vel_normal.x *= FTPIKACHU_QUICKATTACK_VEL_MUL;
        fp->phys_info.vel_normal.y *= FTPIKACHU_QUICKATTACK_VEL_MUL;
    }

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirHi, 0.0F, 0.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
}

bool32 func_ovl3_801531AC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f current_angle;
    Vec3f previous_angle;
    f32 unused[2];
    f32 temp_stick_x;
    f32 temp_stick_y;

    temp_stick_x = (f32)fp->input.stick_range.x;
    temp_stick_y = (f32)fp->input.stick_range.y;

    if (sqrtf((temp_stick_x * temp_stick_x) + (temp_stick_y * temp_stick_y)) < FTPIKACHU_QUICKATTACK_STICK_RANGE_MIN)
    {
        return FALSE;
    }
    else if (fp->status_vars.pikachu.specialhi.is_subsequent_zip == FALSE)
    {
        current_angle.x = (f32)fp->input.stick_range.x;
        current_angle.y = (f32)fp->input.stick_range.y;
        current_angle.z = 0.0F;

        previous_angle.x = (f32)fp->status_vars.pikachu.specialhi.stick_range.x;
        previous_angle.y = (f32)fp->status_vars.pikachu.specialhi.stick_range.y;
        previous_angle.z = 0.0F;

        if (FTPIKACHU_QUICKATTACK_ANGLE_DIFF_MIN < vec3f_angle_diff(&previous_angle, &current_angle))
        {
            return TRUE;
        }
        else return FALSE;
    }
    else return FALSE;
}

void func_ovl3_801532B8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 == 1)
    {
        if (func_ovl3_801531AC(fighter_gobj) != FALSE)
        {
            fp->cmd_flags.flag1 = 0;

            fp->status_vars.pikachu.specialhi.is_subsequent_zip = TRUE;

            func_ovl3_80152E48(fighter_gobj);
        }
        else fp->cmd_flags.flag1 = 2;
    }
    else if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_8013E1C8(fighter_gobj);
    }
}

void func_ovl3_80153340(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 == 1)
    {
        if (func_ovl3_801531AC(fighter_gobj) != FALSE)
        {
            fp->cmd_flags.flag1 = 0;
            fp->status_vars.pikachu.specialhi.is_subsequent_zip = TRUE;

            func_ovl3_80152FEC(fighter_gobj);
        }
        else fp->cmd_flags.flag1 = 2;
    }
    else if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, FTPIKACHU_QUICKATTACK_FALLSPECIAL_DRIFT, FALSE, TRUE, TRUE, FTPIKACHU_QUICKATTACK_LANDING_LAG, FALSE);
    }
}

void func_ovl3_801533E4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != 0)
    {
        func_ovl2_800D8BB4(fighter_gobj);
    }
}

void func_ovl3_80153414(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != 0U)
    {
        ftCommonAttributes *common_attrs;

        func_ovl2_800D8E50(fp, fp->attributes);

        common_attrs = fp->attributes;

        func_ovl2_800D8FC8(fp, 8, common_attrs->aerial_acceleration * FTPIKACHU_QUICKATTACK_AIR_ACCEL_MUL, common_attrs->aerial_speed_max_x * FTPIKACHU_QUICKATTACK_AIR_SPEED_MUL);
       
        func_ovl2_800D9074(fp, fp->attributes);
    }
    else
    {
        fp->phys_info.vel_normal.y -= (fp->phys_info.vel_normal.y / FTPIKACHU_QUICKATTACK_VEL_Y_DIV);

        func_ovl2_800D9074(fp, fp->attributes);
    }
}

void func_ovl3_801534BC(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80153584);
}

void func_ovl3_801534E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE7D8(fighter_gobj) != FALSE)
    {
        if (fp->coll_data.coll_type & 0x3000)
        {
            func_ovl3_80144C24(fighter_gobj);
        }
        else func_ovl3_80142E3C(fighter_gobj, 0, 0.4F);
    }
}

void func_ovl3_80153544(GObj *fighter_gobj) // Unused
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialHiEnd, fighter_gobj->anim_frame, 1.0F, 0x92U);
}

void func_ovl3_80153584(GObj *fighter_gobj)
{
    func_ovl2_800DEEC8(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirHiEnd, fighter_gobj->anim_frame, 1.0F, 0x92U);
}

void func_ovl3_801535C4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.pikachu.specialhi.vel_x_bak = fp->phys_info.vel_normal.x;
    fp->status_vars.pikachu.specialhi.vel_y_bak = fp->phys_info.vel_normal.y;
    fp->status_vars.pikachu.specialhi.vel_ground_bak = fp->phys_info.vel_ground.x;

    fp->phys_info.vel_normal.y = 0.0F;
    fp->phys_info.vel_normal.x = 0.0F;
    fp->phys_info.vel_ground.x = 0.0F;
}

void func_ovl3_801535F4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_801535C4(fighter_gobj);

    fp->phys_info.vel_ground.x = fp->status_vars.pikachu.specialhi.vel_ground_bak * FTPIKACHU_QUICKATTACK_VEL_BAK_MUL;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialHiEnd, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
}

void func_ovl3_80153654(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_801535C4(fighter_gobj);

    fp->phys_info.vel_normal.x = (f32)(fp->status_vars.pikachu.specialhi.vel_x_bak * FTPIKACHU_QUICKATTACK_VEL_BAK_MUL);
    fp->phys_info.vel_normal.y = (f32)(fp->status_vars.pikachu.specialhi.vel_y_bak * FTPIKACHU_QUICKATTACK_VEL_BAK_MUL);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirHiEnd, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
}
