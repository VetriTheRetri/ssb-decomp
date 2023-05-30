#include "fighter.h"

void func_ovl3_8014FBF0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (fp->status_vars.common.attacklw3.is_goto_attacklw3 != FALSE))
    {
        func_ovl3_8014FD14(fighter_gobj);
    }
    else ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8014329C);
}

void func_ovl3_8014FC40(GObj *fighter_gobj)
{
    func_ovl3_8014FC60(fighter_gobj);
}

bool32 func_ovl3_8014FC60(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((fp->input.pl.button_tap & fp->input.button_mask_a) && (attributes->is_have_attacklw3))
    {
        if (fp->command_vars.flags.flag1 != 0)
        {
            func_ovl3_8014FD14(fighter_gobj);

            return TRUE;
        }
        else fp->status_vars.common.attacklw3.is_goto_attacklw3 = TRUE;
    }
    return FALSE;
}

void func_ovl3_8014FCCC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag1 = 0;

    fp->status_vars.common.attacklw3.is_goto_attacklw3 = FALSE;

    ftCommon_MotionCountIncSetID(fp, 8);
    ftCommon_StatUpdateCountIncSetFlags(fp, fp->stat_flags.halfword);
    ftCommon_Update1PGameAttackStats(fp, 0);
}

void func_ovl3_8014FD14(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80146064(fighter_gobj) == FALSE)
    {
        fp->proc_status = func_ovl3_8014FCCC;

        ftStatus_Update(fighter_gobj, ftStatus_Common_AttackLw3, 0.0F, 1.0F, 0U);
        ftAnim_Update(fighter_gobj);
    }
}

bool32 func_ovl3_8014FD70(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((fp->input.pl.button_tap & fp->input.button_mask_a) && (fp->input.pl.stick_range.y <= FTCOMMON_ATTACKLW3_STICK_RANGE_MIN))
    {
        if (ftCommon_GetStickAngleRadians(fp) < -0.87266463F)
        {
            if (func_ovl3_80146A8C(fp) != FALSE)
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowLw);

                return TRUE;
            }
            if (attributes->is_have_attacklw3)
            {
                func_ovl3_8014FD14(fighter_gobj);

                return TRUE;
            }
        }
    }
    return FALSE;
}