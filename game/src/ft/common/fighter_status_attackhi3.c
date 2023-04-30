#include "fighter.h"

void func_ovl3_8014FA50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 stick_angle;
    s32 status_id;

    if (fp->ft_data->script1->script_info[0xAD].anim_id != 0)
    {
        stick_angle = atan2f(fp->input.stick_range.y, fp->input.stick_range.x * fp->lr);

        status_id = (stick_angle < 1.3439035F) ? ftStatus_Common_AttackHi3F : // WHAT
                    (stick_angle > 1.7976892F) ? ftStatus_Common_AttackHi3B : // WHAT
                                                 ftStatus_Common_AttackHi3;
    }
    else status_id = ftStatus_Common_AttackHi3;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

bool32 func_ovl3_8014FB1C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((fp->input.button_tap & fp->input.button_mask_a) && (fp->input.stick_range.y >= FTCOMMON_ATTACKHI3_STICK_RANGE_MIN))
    {
        if (func_ovl2_800E8000(fp) > 0.87266463F)
        {
            if (func_ovl3_80146A8C(fp) != FALSE)
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowHi);

                return TRUE;
            }
            if (attributes->is_have_attackhi3)
            {
                func_ovl3_8014FA50(fighter_gobj);

                return TRUE;
            }
        }
    }
    return FALSE;
}