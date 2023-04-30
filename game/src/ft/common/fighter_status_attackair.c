#include "fighter.h"

void func_ovl3_801508E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ft_kind == Ft_Kind_Link) || (fp->ft_kind == Ft_Kind_PolyLink))
    {
        func_ovl2_800E8518(fighter_gobj);

        fp->is_fast_fall = FALSE;

        fp->phys_info.vel_air.y = FTCOMMON_ATTACKAIRLW_LINK_REHIT_BOUNCE_VEL_Y;

        if (fighter_gobj->anim_frame > FTCOMMON_ATTACKAIRLW_LINK_REHIT_FRAME_BEGIN)
        {
            ftStatus_Update(fighter_gobj, ftStatus_Common_AttackAirLw, FTCOMMON_ATTACKAIRLW_LINK_REHIT_FRAME_BEGIN, 1.0F, 0U);
        }
        fp->status_vars.common.attackair.rehit_timer = FTCOMMON_ATTACKAIRLW_LINK_REHIT_TIMER;
    }
}

void func_ovl3_80150980(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ft_kind == Ft_Kind_Link) || (fp->ft_kind == Ft_Kind_PolyLink))
    {
        if (fp->status_vars.common.attackair.rehit_timer != 0)
        {
            fp->status_vars.common.attackair.rehit_timer--;

            if ((fp->status_vars.common.attackair.rehit_timer == 0) && (fighter_gobj->anim_frame < FTCOMMON_ATTACKAIRLW_LINK_REHIT_FRAME_END))
            {
                func_ovl2_800E8668(fighter_gobj, 0);
                func_ovl2_800E8668(fighter_gobj, 1);
            }
        }
    }
    func_ovl2_800D94E8(fighter_gobj);
}

void func_ovl3_80150A08(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        if ((fp->command_vars.flags.flag1 != 0) && (fp->time_since_last_z > FTCOMMON_ATTACKAIR_SMOOTH_LANDING_BUFFER_FRAMES_MAX))
        {
            if (fp->ft_data->script1->script_info[fp->status_info.script_id + (ftStatus_Common_LandingAirN - ftStatus_Common_AttackAirN)].anim_id != 0)
            {
                func_ovl3_80150E80(fighter_gobj);
            }
            else func_ovl3_80142E10(fighter_gobj, fp->command_vars.flags.flag1 * 0.01F);
        }
        else if (fp->phys_info.vel_air.y > FTCOMMON_ATTACKAIR_SKIP_LANDING_VEL_Y_MAX)
        {
            func_ovl3_8013E1C8(fighter_gobj);
        }
        else func_ovl3_80142D9C(fighter_gobj);
    }
}