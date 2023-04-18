#include "fighter.h"

void func_ovl3_8013F170(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != 0)
    {
        fp->cmd_flags.flag1 = 0;

        fp->lr = -fp->lr;
        fp->phys_info.vel_ground.x = -fp->phys_info.vel_ground.x;
    }
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8013EEE8);
}

void func_ovl3_8013F1C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl3_8013F598(fighter_gobj) == FALSE) && (fp->cmd_flags.flag2 != 0))
    {
        func_ovl3_8013F0EC(fighter_gobj);
    }
}

void func_ovl3_8013F208(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_TurnRun, 0.0F, 1.0F, 0U);

    fp->cmd_flags.flag1 = 0;
    fp->cmd_flags.flag2 = 0;
}

bool32 func_ovl3_8013F248(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->input.stick_range.x * fp->lr) <= FTCOMMON_TURNRUN_STICK_RANGE_MIN)
    {
        func_ovl3_8013F208(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}