#include "fighter.h"

void func_ovl3_8013EA40(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        fp->phys_info.vel_ground.x *= 0.75F;

        func_ovl3_8013E1C8(fighter_gobj);
    }
}

void func_ovl3_8013EA90(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (fighter_gobj->anim_frame <= 5.0F))
    {
        if ((func_ovl3_80151098(fighter_gobj) == FALSE) && (func_ovl3_80149CE0(fighter_gobj) == FALSE) && (func_ovl3_801501E0(fighter_gobj) == FALSE) && (!(fighter_gobj->anim_frame <= 3.0F) || (func_ovl3_801493A4(fighter_gobj) == FALSE)))
        {
            if (func_ovl3_80148D0C(fighter_gobj) != FALSE) // Jump interrupt?
            {
                return;
            }
            else goto next;
        }
    }
    else if (fighter_gobj->anim_frame <= 20.0F)
    {
        if (func_ovl3_80151098(fighter_gobj) == FALSE)
        {
            if (func_ovl3_80149D80(fighter_gobj) == FALSE)
            {
                if ((func_ovl3_8014F69C(fighter_gobj) == FALSE) && (((fp->input.stick_range.x * fp->lr) >= 0) || (func_ovl3_8013ED64(fighter_gobj) == FALSE)))
                {
                    if (func_ovl3_80148D2C(fighter_gobj, (s32) (20.0F - fighter_gobj->anim_frame)) != FALSE)
                    {
                        return;
                    }
                    else goto next;
                }
            }
        }
    }
    else if ((func_ovl3_80149CE0(fighter_gobj) == FALSE) && (func_ovl3_8013ED64(fighter_gobj) == FALSE) && (func_ovl3_80148D0C(fighter_gobj) == FALSE))
    {
    next:
        if ((func_ovl3_8014E764(fighter_gobj) == FALSE) && (func_ovl3_8013F598(fighter_gobj) == FALSE))
        {
            func_ovl3_8013EF2C(fighter_gobj);
        }
    }
}

void func_ovl3_8013EC58(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fighter_gobj->anim_frame >= FTCOMMON_DASH_DECELERATE_BEGIN)
    {
        func_ovl2_800D8978(fp, attributes->dash_decelerate);
    }
    func_ovl2_800D87D0(fighter_gobj);
}

void func_ovl3_8013ECB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (attributes->dash_to_run <= fighter_gobj->anim_frame)
    {
        jtgt_ovl2_800DDEE8(fighter_gobj);
    }
    else jtgt_ovl2_800DDEC4(fighter_gobj);
}

void func_ovl3_8013ED00(GObj *fighter_gobj, u32 flag)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Dash, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->phys_info.vel_ground.x = fp->attributes->dash_speed;
    fp->tap_stick_x = (U8_MAX - 1);
    fp->command_vars.flags.flag1 = flag;
}

bool32 func_ovl3_8013ED64(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((ABS(fp->input.stick_range.x) >= FTCOMMON_DASH_STICK_RANGE_MIN) && (fp->tap_stick_x < FTCOMMON_DASH_BUFFER_FRAMES_MAX))
    {
        if ((fp->input.stick_range.x * fp->lr) < 0)
        {
            func_ovl3_8013E9A8(fighter_gobj);

            return TRUE;
        }
        func_ovl2_800E8044(fp);
        func_ovl3_8013ED00(fighter_gobj, 1);

        return TRUE;
    }
    return FALSE;
}

bool32 func_ovl3_8013EDFC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->input.stick_range.x * fp->status_vars.common.turn.lr_turn) >= FTCOMMON_DASH_STICK_RANGE_MIN) && (fp->tap_stick_x < FTCOMMON_DASH_BUFFER_FRAMES_MAX))
    {
        fp->status_vars.common.turn.lr_dash = fp->status_vars.common.turn.lr_turn;
        fp->status_vars.common.turn.unk_0x14 = 0;

        return TRUE;
    }
    else return FALSE;
}