#include "fighter.h"
#include "ftkirby.h"
#include "ftpurin.h"

// These arrays are strange, Kirby begins at .rodata padding 0x80188578, and index is never zero, but ends up using the correct values regardless???
// If Kirby DOES beging at 0x80188578, that means his array accesses overflow into Jigglypuff's starting at index 0x4

f32 Fighter_Kirby_JumpAerialVelY[ftStatus_Kirby_JumpAerialF5 - ftStatus_Kirby_JumpAerialF1] = { 60.0F, 52.0F, 47.0F, 40.0F };
f32 Fighter_Purin_JumpAerialVelY[ftStatus_Purin_JumpAerialF5 - ftStatus_Purin_JumpAerialF1] = { 60.0F, 40.0F, 20.0F,  0.0F };

void func_ovl3_8013FA90(Fighter_Struct *fp)
{
    if (fp->status_vars.common.jumpaerial.turn_frames != 0)
    {
        fp->status_vars.common.jumpaerial.turn_frames--;

        fp->joint[0]->rotate.y += FTCOMMON_JUMPAERIAL_TURN_ROTATE_STEP;

        func_ovl2_800EB528(fp->joint[0]);

        if (fp->status_vars.common.jumpaerial.turn_frames == (FTCOMMON_JUMPAERIAL_TURN_FRAMES / 2))
        {
            fp->lr = -fp->lr;
        }
    }
}

void func_ovl3_8013FB00(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8013FA90(fp);
    func_ovl2_800D94E8(fighter_gobj);
}

void func_ovl3_8013FB2C(GObj *fighter_gobj)
{
    if ((func_ovl3_80150F08(fighter_gobj) == FALSE) && (func_ovl3_80150B00(fighter_gobj) == FALSE))
    {
        func_ovl3_8014019C(fighter_gobj);
    }
}

void func_ovl3_8013FB6C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    jtgt_ovl2_800D9414(fighter_gobj);

    if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
    {
        func_ovl2_800D9044(fp, attributes);
        func_ovl2_800D9074(fp, attributes);
    }
}

void func_ovl3_8013FBC4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    f32 vel_x;

    func_ovl2_800D9260(fp, &fp->status_vars.common.jumpaerial.drift, &fp->phys_info.vel_air.y, &fp->phys_info.vel_air.z);

    fp->phys_info.vel_air.x = fp->status_vars.common.jumpaerial.vel_x;

    if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
    {
        func_ovl2_800D9044(fp, attributes);
        func_ovl2_800D9074(fp, attributes);
    }
    fp->status_vars.common.jumpaerial.vel_x = fp->phys_info.vel_air.x;

    fp->phys_info.vel_air.x += fp->status_vars.common.jumpaerial.drift;
}

void func_ovl3_8013FC4C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    func_ovl2_800D8DB0(fp);

    (fp->is_fast_fall) ? func_ovl2_800D8DA0(fp, attributes) : func_ovl2_800D8E50(fp, attributes);

    switch (fp->ft_kind)
    {
    case Ft_Kind_Kirby:
    case Ft_Kind_PolyKirby:
        if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
        {
            func_ovl2_800D8FC8(fp, 8, attributes->aerial_acceleration * FTKIRBY_JUMPAERIAL_VEL_MUL, attributes->aerial_speed_max_x * FTKIRBY_JUMPAERIAL_VEL_MUL);
        }
        break;

    case Ft_Kind_Purin:
    case Ft_Kind_PolyPurin:
        if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
        {
            func_ovl2_800D8FC8(fp, 8, attributes->aerial_acceleration * FTPURIN_JUMPAERIAL_VEL_MUL, attributes->aerial_speed_max_x * FTPURIN_JUMPAERIAL_VEL_MUL);
        }
        break;
    }
    func_ovl2_800D9074(fp, attributes);
}

void func_ovl3_8013FD74(GObj *fighter_gobj, s32 input_source)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    s32 status_id = ((fp->input.stick_range.x * fp->lr) >= FTCOMMON_JUMPAERIAL_F_OR_B_RANGE) ? ftStatus_Common_JumpAerialF : ftStatus_Common_JumpAerialB;
    s32 stick_range_y = GMCONTROLLER_RANGE_MAX_I;
    s32 stick_range_x;

    // It would seem that the stick range jump mechanic was initially considered for double jumps as well...

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0x100U);

    if ((fp->ft_kind == Ft_Kind_Yoshi) || (fp->ft_kind == Ft_Kind_PolyYoshi))
    {
        fp->cb_physics = func_ovl3_8013FB6C;
        fp->knockback_resist_status = FTYOSHI_JUMPAERIAL_KNOCKBACK_RESIST;
    }
    else if ((fp->ft_kind == Ft_Kind_Ness) || (fp->ft_kind == Ft_Kind_PolyNess))
    {
        fp->cb_physics = func_ovl3_8013FBC4;
        fp->status_vars.common.jumpaerial.drift = 0.0F;
    }
    if ((input_source != FTCOMMON_JUMPAERIAL_INPUT_TYPE_STICK) && (input_source == FTCOMMON_JUMPAERIAL_INPUT_TYPE_BUTTON))
    {
        stick_range_x = fp->input.stick_range.x;
    }
    else stick_range_x = fp->input.stick_range.x; // Last minute bruh moment from HAL

    fp->phys_info.vel_air.y = (((stick_range_y * attributes->jump_height_mul) + attributes->jump_height_base) * attributes->aerial_jump_height);

    if ((fp->ft_kind == Ft_Kind_Ness) || (fp->ft_kind == Ft_Kind_PolyNess))
    {
        fp->status_vars.common.jumpaerial.vel_x = stick_range_x * attributes->aerial_jump_vel_x;
    }
    else fp->phys_info.vel_air.x = stick_range_x * attributes->aerial_jump_vel_x;

    fp->jumps_used++;

    fp->buffer_stick_y = U8_MAX - 1;

    fp->x192_flag_b0 = TRUE;

    if (((fp->ft_kind == Ft_Kind_Yoshi) || (fp->ft_kind == Ft_Kind_PolyYoshi)) && ((fp->input.stick_range.x * fp->lr) < FTCOMMON_JUMPAERIAL_TURN_STICK_RANGE_MIN))
    {
        fp->status_vars.common.jumpaerial.turn_frames = FTCOMMON_JUMPAERIAL_TURN_FRAMES;
    }
    else fp->status_vars.common.jumpaerial.turn_frames = 0;

    func_ovl3_8013FA90(fp);
}

void func_ovl3_8013FF38(GObj *fighter_gobj, s32 input_source)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    s32 status_id;
    s32 stick_range_x;
    s32 stick_range_y = GMCONTROLLER_RANGE_MAX_I;

    switch (fp->ft_kind)
    {
    case Ft_Kind_Kirby:
    case Ft_Kind_PolyKirby:
        status_id = fp->jumps_used + ftStatus_Kirby_JumpAerialF1 - 1;
        break;

    case Ft_Kind_Purin:
    case Ft_Kind_PolyPurin:
        status_id = fp->jumps_used + ftStatus_Purin_JumpAerialF1 - 1;
        break;
    }
    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0x100U);

    if ((input_source != FTCOMMON_JUMPAERIAL_INPUT_TYPE_STICK) && (input_source == FTCOMMON_JUMPAERIAL_INPUT_TYPE_BUTTON))
    {
        stick_range_x = fp->input.stick_range.x;
    }
    else stick_range_x = fp->input.stick_range.x;

    fp->phys_info.vel_air.x = stick_range_x * attributes->aerial_jump_vel_x;

    if (fp->jumps_used == 1)
    {
        fp->phys_info.vel_air.y = (((stick_range_y * attributes->jump_height_mul) + attributes->jump_height_base) * attributes->aerial_jump_height);

        fp->buffer_stick_y = U8_MAX - 1;
    }
    else switch (fp->ft_kind)
    {
    case Ft_Kind_Kirby:
    case Ft_Kind_PolyKirby:
        fp->phys_info.vel_air.y = Fighter_Kirby_JumpAerialVelY[(s32)fp->jumps_used] * (stick_range_y / GMCONTROLLER_RANGE_MAX_F);
        break;

    case Ft_Kind_Purin:
    case Ft_Kind_PolyPurin:
        fp->phys_info.vel_air.y = Fighter_Purin_JumpAerialVelY[(s32)fp->jumps_used] * (stick_range_y / GMCONTROLLER_RANGE_MAX_F);
        break;
    }
    fp->jumps_used++;

    fp->cmd_flags.flag1 = 0;

    fp->x192_flag_b0 = TRUE;

    if ((fp->input.stick_range.x * fp->lr) < FTCOMMON_JUMPAERIAL_TURN_STICK_RANGE_MIN)
    {
        fp->status_vars.common.jumpaerial.turn_frames = FTCOMMON_JUMPAERIAL_TURN_FRAMES;
    }
    else fp->status_vars.common.jumpaerial.turn_frames = 0;

    func_ovl3_8013FA90(fp);
}

bool32 func_ovl3_8014012C(Fighter_Struct *fp)
{
    if (fp->input.button_hold & (HAL_BUTTON_C_RIGHT | HAL_BUTTON_C_LEFT | HAL_BUTTON_C_DOWN | HAL_BUTTON_C_UP))
    {
        return TRUE;
    }
    else return FALSE;
}

s32 func_ovl3_80140150(Fighter_Struct *fp)
{
    if (fp->input.stick_range.y >= FTCOMMON_JUMPAERIAL_STICK_RANGE_MIN)
    {
        return FTCOMMON_JUMPAERIAL_INPUT_TYPE_STICK;
    }
    else if (func_ovl3_8014012C(fp) != FALSE)
    {
        return FTCOMMON_JUMPAERIAL_INPUT_TYPE_BUTTON;
    }
    else return FTCOMMON_JUMPAERIAL_INPUT_TYPE_NONE;
}

bool32 func_ovl3_8014019C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 input_source;

    if (func_ovl2_800F3794(fighter_gobj) != FALSE)
    {
        return FALSE;
    }

    if ((fp->ft_kind == Ft_Kind_Kirby) || (fp->ft_kind == Ft_Kind_PolyKirby) || (fp->ft_kind == Ft_Kind_Purin) || (fp->ft_kind == Ft_Kind_PolyPurin))
    {
        if (fp->jumps_used < fp->attributes->jumps_max)
        {
            if (fp->jumps_used == 1)
            {
                input_source = func_ovl3_8013F474(fp);

                if (input_source != FTCOMMON_JUMPAERIAL_INPUT_TYPE_NONE)
                {
                    func_ovl3_8013FF38(fighter_gobj, input_source);

                    return TRUE;
                }
            }
            else switch (fp->ft_kind)
            {
            case Ft_Kind_Kirby:
            case Ft_Kind_PolyKirby:

                if ((fp->status_info.status_id < ftStatus_Kirby_JumpAerialF1) || (fp->status_info.status_id > ftStatus_Kirby_JumpAerialF5) || (fp->cmd_flags.flag1 != 0))
                {
                    input_source = func_ovl3_80140150(fp);

                    if (input_source != FTCOMMON_JUMPAERIAL_INPUT_TYPE_NONE)
                    {
                        func_ovl3_8013FF38(fighter_gobj, input_source);

                        return TRUE;
                    }
                }
                break;

            case Ft_Kind_Purin:
            case Ft_Kind_PolyPurin:

                if ((fp->status_info.status_id < ftStatus_Purin_JumpAerialF1) || (fp->status_info.status_id > ftStatus_Purin_JumpAerialF5) || (fp->cmd_flags.flag1 != 0))
                {
                    input_source = func_ovl3_80140150(fp);

                    if (input_source != FTCOMMON_JUMPAERIAL_INPUT_TYPE_NONE)
                    {
                        func_ovl3_8013FF38(fighter_gobj, input_source);

                        return TRUE;
                    }
                }
                break;
            }
        }
    }
    else
    {
        input_source = func_ovl3_8013F474(fp);

        if ((input_source != FTCOMMON_JUMPAERIAL_INPUT_TYPE_NONE) && (fp->jumps_used < fp->attributes->jumps_max))
        {
            func_ovl3_8013FD74(fighter_gobj, input_source);

            return TRUE;
        }
    }
    return FALSE;
}
