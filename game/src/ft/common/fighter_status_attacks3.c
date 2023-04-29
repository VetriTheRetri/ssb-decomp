#include "fighter.h"

void func_ovl3_8014F760(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 stick_angle;
    s32 status_id;

    if (func_ovl3_80146064(fighter_gobj) == FALSE)
    {
        if (fp->ft_data->script1->script_info[0xA9].unk_script_index != 0)
        {
            stick_angle = func_ovl2_800E8000(fp);

            status_id = (stick_angle > FTCOMMON_ATTACKS3_5ANGLE_HI_MIN)  ? ftStatus_Common_AttackS3Hi  :
                        (stick_angle > FTCOMMON_ATTACKS3_5ANGLE_HIS_MIN) ? ftStatus_Common_AttackS3HiS :
                        (stick_angle < FTCOMMON_ATTACKS3_5ANGLE_LW_MIN)  ? ftStatus_Common_AttackS3Lw  :
                        (stick_angle < FTCOMMON_ATTACKS3_5ANGLE_LWS_MIN) ? ftStatus_Common_AttackS3LwS :
                                                                           ftStatus_Common_AttackS3;
        }
        else if (fp->ft_data->script1->script_info[0xA8].unk_script_index != 0)
        {
            stick_angle = func_ovl2_800E8000(fp);

            status_id = (stick_angle > FTCOMMON_ATTACKS3_3ANGLE_HI_MIN)  ? ftStatus_Common_AttackS3Hi  :
                        (stick_angle < FTCOMMON_ATTACKS3_3ANGLE_LW_MIN)  ? ftStatus_Common_AttackS3Lw  :
                                                                           ftStatus_Common_AttackS3;
        }
        else status_id = ftStatus_Common_AttackS3;

        ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
        ftAnim_Update(fighter_gobj);
    }
}