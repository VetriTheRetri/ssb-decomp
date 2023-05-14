#include "fighter.h"

void func_ovl3_801447E0(GObj *fighter_gobj, s32 status_id)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->x18F_flag_b4 = TRUE;
}

bool32 func_ovl3_8014482C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (ABS(fp->input.pl.stick_range.x) >= FTCOMMON_DOWN_FORWARD_BACK_RANGE_MIN)
    {
        if (func_ovl2_800E8000(fp) < 0.87266463F)
        {
            if ((fp->input.pl.stick_range.x * fp->lr) >= 0)
            {
                if ((fp->status_info.status_id == ftStatus_Common_DownBounceD) || (fp->status_info.status_id == ftStatus_Common_DownWaitD))
                {
                    status_id = ftStatus_Common_DownForwardD;
                }
                else status_id = ftStatus_Common_DownForwardU;
            }
            else if ((fp->status_info.status_id == ftStatus_Common_DownBounceD) || (fp->status_info.status_id == ftStatus_Common_DownWaitD))
            {
                status_id = ftStatus_Common_DownBackD;
            }
            else status_id = ftStatus_Common_DownBackU;

            func_ovl3_801447E0(fighter_gobj, status_id);

            return TRUE;
        }
    }
    return FALSE;
}