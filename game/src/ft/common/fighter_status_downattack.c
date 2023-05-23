#include "fighter.h"

void func_ovl3_80144910(GObj *fighter_gobj, s32 status_id)
{
    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

bool32 func_ovl3_80144944(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (fp->status_vars.common.downbounce.attack_buffer != 0)
    {
        if (fp->status_info.status_id == ftStatus_Common_DownBounceD)
        {
            status_id = ftStatus_Common_DownAttackD;
        }
        else status_id = ftStatus_Common_DownAttackU;

        func_ovl3_80144910(fighter_gobj, status_id);

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_8014499C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (fp->input.pl.button_tap & (fp->input.button_mask_a | fp->input.button_mask_b))
    {
        if (fp->status_info.status_id == ftStatus_Common_DownWaitD)
        {
            status_id = ftStatus_Common_DownAttackD;
        }
        else status_id = ftStatus_Common_DownAttackU;

        func_ovl3_80144910(fighter_gobj, status_id);

        return TRUE;
    }
    else return FALSE;
}
