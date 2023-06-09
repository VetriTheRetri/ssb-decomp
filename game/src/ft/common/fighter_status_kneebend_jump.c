#include "fighter.h"

void func_ovl3_8013F2A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    fp->status_vars.common.kneebend.anim_frame += DObjGetStruct(fighter_gobj)->unk_dobj_0x78;

    if ((fp->status_vars.common.kneebend.input_source == FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON) &&
    (fp->status_vars.common.kneebend.anim_frame <= FTCOMMON_KNEEBEND_SHORT_HOP_FRAMES) &&
    (fp->input.pl.button_tap_prev & (HAL_BUTTON_C_RIGHT | HAL_BUTTON_C_LEFT | HAL_BUTTON_C_DOWN | HAL_BUTTON_C_UP)))
    {
        fp->status_vars.common.kneebend.is_short_hop = TRUE;
    }
    if (attributes->kneebend_frames <= fp->status_vars.common.kneebend.anim_frame) 
    {
        func_ovl3_8013F880(fighter_gobj);
    }
}

void func_ovl3_8013F334(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (func_ovl3_80151160(fighter_gobj) == FALSE)
    {
        if (ftCommon_AttackHi4_CheckInterruptKneebend(fighter_gobj) == FALSE)
        {
            if (fp->status_vars.common.kneebend.jump_force < fp->input.pl.stick_range.y)
            {
                fp->status_vars.common.kneebend.jump_force = fp->input.pl.stick_range.y;
            }
        }
    }
}

void func_ovl3_8013F3A0(GObj *fighter_gobj, s32 status_id, u32 input_source)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);

    fp->status_vars.common.kneebend.jump_force = fp->input.pl.stick_range.y;
    fp->status_vars.common.kneebend.anim_frame = 0.0F;
    fp->status_vars.common.kneebend.input_source = input_source;
    fp->status_vars.common.kneebend.is_short_hop = FALSE;

    fp->x192_flag_b0 = TRUE;
}

void func_ovl3_8013F408(GObj *fighter_gobj, u32 input_source)
{
    func_ovl3_8013F3A0(fighter_gobj, ftStatus_Common_KneeBend, input_source);
}

void func_ovl3_8013F42C(GObj *fighter_gobj, u32 input_source)
{
    func_ovl3_8013F3A0(fighter_gobj, ftStatus_Common_GuardKneeBend, input_source);
}

bool32 func_ovl3_8013F450(Fighter_Struct *fp)
{
    if (fp->input.pl.button_tap & (HAL_BUTTON_C_RIGHT | HAL_BUTTON_C_LEFT | HAL_BUTTON_C_DOWN | HAL_BUTTON_C_UP))
    {
        return TRUE;
    }
    else return FALSE;
}

s32 func_ovl3_8013F474(Fighter_Struct *fp)
{
    if ((fp->input.pl.stick_range.y >= FTCOMMON_KNEEBEND_STICK_RANGE_MIN) && (fp->tap_stick_y <= FTCOMMON_KNEEBEND_BUFFER_FRAMES_MAX))
    {
        return FTCOMMON_KNEEBEND_INPUT_TYPE_STICK;
    }
    else if (func_ovl3_8013F450(fp) != FALSE)
    {
        return FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON;
    }
    else return FTCOMMON_KNEEBEND_INPUT_TYPE_NONE;
}

bool32 func_ovl3_8013F4D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    s32 input_source;

    if (ftCommon_HammerCheckHold(fighter_gobj) != FALSE)
    {
        return func_ovl3_8014800C(fighter_gobj);
    }
    input_source = func_ovl3_8013F474(fp);

    if (input_source != FTCOMMON_KNEEBEND_INPUT_TYPE_NONE)
    {
        func_ovl3_8013F408(fighter_gobj, input_source);

        return TRUE;
    }
    else return FALSE;
}

s32 func_ovl3_8013F53C(Fighter_Struct *fp)
{
    if ((fp->input.pl.stick_range.y > FTCOMMON_KNEEBEND_RUN_STICK_RANGE_MIN) && (fp->tap_stick_y <= FTCOMMON_KNEEBEND_BUFFER_FRAMES_MAX))
    {
        return FTCOMMON_KNEEBEND_INPUT_TYPE_STICK;
    }
    else if (func_ovl3_8013F450(fp) != FALSE)
    {
        return FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON;
    }
    else return FTCOMMON_KNEEBEND_INPUT_TYPE_NONE;
}

s32 func_ovl3_8013F598(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    s32 input_source;

    if (ftCommon_HammerCheckHold(fighter_gobj) != FALSE)
    {
        return func_ovl3_8014800C(fighter_gobj);
    }
    input_source = func_ovl3_8013F53C(fp);

    if (input_source != FTCOMMON_KNEEBEND_INPUT_TYPE_NONE)
    {
        func_ovl3_8013F408(fighter_gobj, input_source);

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_8013F604(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    s32 input_source = func_ovl3_8013F474(fp);

    if ((input_source != FTCOMMON_KNEEBEND_INPUT_TYPE_NONE) && (fp->input.pl.button_hold & fp->input.button_mask_z))
    {
        func_ovl3_8013F42C(fighter_gobj, input_source);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8013F6A0(s32 stick_range_x, s32 *jump_vel_x, s32 *jump_vel_y, bool32 is_short_hop)
{
    f32 sqrt_vel_x;
    f32 vel_y;
    f32 vel_x;

    vel_x = ABS(stick_range_x);

    sqrt_vel_x = sqrtf(1.0F - SQUARE(vel_x / GCONTROLLER_RANGE_MAX_F));

    if (is_short_hop == FALSE)
    {
        vel_y = (FTCOMMON_KNEEBEND_BUTTON_LONG_FORCE * sqrt_vel_x) + FTCOMMON_KNEEBEND_BUTTON_LONG_MIN;

        if ((SQUARE(vel_x) + SQUARE(vel_y)) > SQUARE(GCONTROLLER_RANGE_MAX_F))
        {
            vel_y = sqrtf(SQUARE(GCONTROLLER_RANGE_MAX_F) - SQUARE(vel_x));
        }
        if (vel_y < FTCOMMON_KNEEBEND_BUTTON_LONG_MIN)
        {
            vel_y = FTCOMMON_KNEEBEND_BUTTON_LONG_MIN;
        }
    }
    else
    {
        vel_y = (FTCOMMON_KNEEBEND_BUTTON_SHORT_FORCE * sqrt_vel_x) + FTCOMMON_KNEEBEND_BUTTON_SHORT_MIN;

        if ((SQUARE(vel_x) + SQUARE(vel_y)) > SQUARE(GCONTROLLER_RANGE_MAX_F))
        {
            vel_y = sqrtf(SQUARE(GCONTROLLER_RANGE_MAX_F) - SQUARE(vel_x));
        }
        if (vel_y < FTCOMMON_KNEEBEND_BUTTON_SHORT_MIN)
        {
            vel_y = FTCOMMON_KNEEBEND_BUTTON_SHORT_MIN;
        }
    }
    if (vel_y > FTCOMMON_KNEEBEND_BUTTON_HEIGHT_CLAMP)
    {
        vel_y = FTCOMMON_KNEEBEND_BUTTON_HEIGHT_CLAMP;
    }
    *jump_vel_x = (stick_range_x >= 0) ? vel_x : -vel_x;

    *jump_vel_y = vel_y;
}

void func_ovl3_8013F880(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    s32 status_id;
    s32 vel_x, vel_y;

    ftMapCollide_SetAir(fp);

    status_id = ((fp->input.pl.stick_range.x * fp->lr) > FTCOMMON_KNEEBEND_JUMP_F_OR_B_RANGE) ? ftStatus_Common_JumpF : ftStatus_Common_JumpB;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);

    switch (fp->status_vars.common.kneebend.input_source)
    {
    case FTCOMMON_KNEEBEND_INPUT_TYPE_BUTTON:
        func_ovl3_8013F6A0(fp->input.pl.stick_range.x, &vel_x, &vel_y, fp->status_vars.common.kneebend.is_short_hop);
        break;

    case FTCOMMON_KNEEBEND_INPUT_TYPE_STICK:
    default:
        vel_x = fp->input.pl.stick_range.x;
        vel_y = fp->status_vars.common.kneebend.jump_force;

        if (vel_y < FTCOMMON_KNEEBEND_STICK_RANGE_MIN)
        {
            vel_y = FTCOMMON_KNEEBEND_STICK_RANGE_MIN;
        }
        break;
    }
    fp->phys_info.vel_air.y = (vel_y * attributes->jump_height_mul) + attributes->jump_height_base;
    fp->phys_info.vel_air.x = vel_x * attributes->jump_vel_x;

    fp->tap_stick_y = U8_MAX - 1;

    fp->x192_flag_b0 = TRUE;
}