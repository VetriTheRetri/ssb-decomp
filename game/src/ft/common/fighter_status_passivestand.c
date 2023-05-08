#include "fighter.h"

void func_ovl3_80144700(GObj *fighter_gobj, s32 status_id)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        ftMapCollide_SetGround(fp);
    }
    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    func_ovl2_800E9CE8(fp);
}

bool32 func_ovl3_80144760(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (fp->time_since_last_z < FTCOMMON_PASSIVE_BUFFER_FRAMES_MAX)
    {
        if (ABS(fp->input.stick_range.x) >= FTCOMMON_PASSIVE_F_OR_B_RANGE)
        {
            if ((fp->input.stick_range.x * fp->lr) >= 0)
            {
                status_id = ftStatus_Common_PassiveStandF;
            }
            else status_id = ftStatus_Common_PassiveStandB;

            func_ovl3_80144700(fighter_gobj, status_id);

            return TRUE;
        }
    }
    return FALSE;
}