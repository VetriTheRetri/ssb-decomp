#include "fighter.h"

void func_ovl3_801491D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->command_vars.flags.flag1 = 0;
        fp->lr = -fp->lr;
    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        fp->phys_info.vel_air.x = fp->phys_info.vel_air.y = fp->phys_info.vel_air.z = 0.0F;
        fp->phys_info.vel_ground.x = fp->phys_info.vel_ground.y = fp->phys_info.vel_ground.z = 0.0F;

        if ((fp->ft_kind != Ft_Kind_Yoshi) && (fp->ft_kind != Ft_Kind_PolyYoshi) || (func_ovl3_80148F24(fighter_gobj) == FALSE))
        {
            func_ovl3_8013E1C8(fighter_gobj);
        }
    }
}

void func_ovl3_80149268(GObj *fighter_gobj)
{
    func_ovl3_80146B64(fighter_gobj);
}

void func_ovl3_80149288(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag1 = 0;
}

void func_ovl3_80149294(GObj *fighter_gobj, s32 status_id, s32 arg2)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->proc_status = func_ovl3_80149288;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->x18F_flag_b4 = TRUE;

    fp->status_vars.common.escape.unk_0x0 = arg2;
}

s32 func_ovl3_801492F8(Fighter_Struct *fp)
{
    if ((ABS(fp->input.pl.stick_range.x) >= FTCOMMON_ESCAPE_STICK_RANGE_MIN) && (fp->tap_stick_x < FTCOMMON_ESCAPE_BUFFER_FRAMES_MAX))
    {
        return ((fp->input.pl.stick_range.x * fp->lr) >= 0) ? ftStatus_Common_EscapeF : ftStatus_Common_EscapeB;
    }
    else return -1;
}

bool32 func_ovl3_8014935C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id = func_ovl3_801492F8(fp);

    if (status_id != -1)
    {
        func_ovl3_80149294(fighter_gobj, status_id, 0);

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_801493A4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.button_press & fp->input.button_mask_z)
    {
        func_ovl3_80149294(fighter_gobj, ftStatus_Common_EscapeF, 0);

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_801493EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id = func_ovl3_801492F8(fp);

    if (status_id != -1)
    {
        func_ovl3_80149294(fighter_gobj, status_id, 5);

        return TRUE;
    }
    else return FALSE;
}