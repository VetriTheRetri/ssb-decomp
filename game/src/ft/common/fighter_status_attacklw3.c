#include "fighter.h"

// 0x8014FBF0
void ftCommon_AttackLw3_ProcUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (fp->status_vars.common.attacklw3.is_goto_attacklw3 != FALSE))
    {
        ftCommon_AttackLw3_SetStatus(fighter_gobj);
    }
    else ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8014329C);
}

// 0x8014FC40
void ftCommon_AttackLw3_ProcInterrupt(GObj *fighter_gobj)
{
    ftCommon_AttackLw3_CheckInterruptSelf(fighter_gobj);
}

// 0x8014FC60
bool32 ftCommon_AttackLw3_CheckInterruptSelf(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((fp->input.pl.button_tap & fp->input.button_mask_a) && (attributes->is_have_attacklw3))
    {
        if (fp->command_vars.flags.flag1 != 0)
        {
            ftCommon_AttackLw3_SetStatus(fighter_gobj);

            return TRUE;
        }
        else fp->status_vars.common.attacklw3.is_goto_attacklw3 = TRUE;
    }
    return FALSE;
}

// 0x8014FCCC
void ftCommon_AttackLw3_InitStatusVars(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag1 = 0;

    fp->status_vars.common.attacklw3.is_goto_attacklw3 = FALSE;

    ftCommon_MotionCountIncSetID(fp, ftAttack_Index_AttackLw3);
    ftCommon_StatUpdateCountIncSetFlags(fp, fp->stat_flags.halfword);
    ftCommon_Update1PGameAttackStats(fp, 0);
}

// 0x8014FD14
void ftCommon_AttackLw3_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80146064(fighter_gobj) == FALSE)
    {
        fp->proc_status = ftCommon_AttackLw3_InitStatusVars;

        ftStatus_Update(fighter_gobj, ftStatus_Common_AttackLw3, 0.0F, 1.0F, FTSTATUPDATE_NULL_PRESERVE);
        ftAnim_Update(fighter_gobj);
    }
}

// 0x8014FD70
bool32 ftCommon_AttackLw3_CheckInterruptCommon(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((fp->input.pl.button_tap & fp->input.button_mask_a) && (fp->input.pl.stick_range.y <= FTCOMMON_ATTACKLW3_STICK_RANGE_MIN))
    {
        if (ftCommon_GetStickAngleRadians(fp) < F_DEG_TO_RAD(-50.0F)) // -0.87266463F
        {
            if (func_ovl3_80146A8C(fp) != FALSE)
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowLw);

                return TRUE;
            }
            else if (attributes->is_have_attacklw3)
            {
                ftCommon_AttackLw3_SetStatus(fighter_gobj);

                return TRUE;
            }
        }
    }
    return FALSE;
}