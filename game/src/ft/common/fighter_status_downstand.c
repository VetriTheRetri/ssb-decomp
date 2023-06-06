#include "fighter.h"

void func_ovl3_80144530(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (func_ovl3_8013F4D0(fighter_gobj) == FALSE) && (func_ovl3_80141EA4(fighter_gobj) == FALSE))
    {
        func_ovl3_80142258(fighter_gobj);
    }
}

void func_ovl3_80144580(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if ((fp->status_info.status_id == ftStatus_Common_DownBounceD) || (fp->status_info.status_id == ftStatus_Common_DownWaitD))
    {
        status_id = ftStatus_Common_DownStandD;
    }
    else status_id = ftStatus_Common_DownStandU;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0);

    fp->command_vars.flags.flag1 = 0;
}

bool32 func_ovl3_801445D8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->input.pl.stick_range.y >= FTCOMMON_DOWNWAIT_STAND_STICK_RANGE_MIN) && (F_DEG_TO_RAD(50.0F) /* 0.87266463F */ <= ftCommon_GetStickAngleRadians(fp)) || (fp->input.pl.button_tap & fp->input.button_mask_z)))
    {
        func_ovl3_80144580(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}