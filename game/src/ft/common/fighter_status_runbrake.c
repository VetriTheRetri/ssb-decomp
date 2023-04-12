#include "fighter.h"

void func_ovl3_8013EFB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl3_8013F598(fighter_gobj) == FALSE) && (fp->cmd_flags.flag1 != 0) && (fighter_gobj->anim_frame <= 4.0F))
    {
        func_ovl3_8013F248(fighter_gobj);
    }
}

void func_ovl3_8013F014(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    func_ovl2_800D8978(fp, attributes->traction * 1.25F);
    func_ovl2_800D87D0(fighter_gobj);
}

void func_ovl3_8013F05C(GObj *fighter_gobj, u32 flag)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Common_RunBrake, 0.0F, 1.0F, 0U);

    fp->cmd_flags.flag1 = flag;
}

bool32 func_ovl3_8013F0A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->input.stick_range.x * fp->lr) < FTCOMMON_RUN_STICK_RANGE_MIN)
    {
        func_ovl3_8013F05C(fighter_gobj, 1);

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_8013F0EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (ABS(fp->input.stick_range.x) < FTCOMMON_RUN_STICK_RANGE_MIN)
    {
        func_ovl3_8013F05C(fighter_gobj, 0);

        if (fp->attributes->run_speed < fp->phys_info.vel_ground.x)
        {
            fp->phys_info.vel_ground.x = fp->attributes->run_speed;
        }
        return TRUE;
    }
    else return FALSE;
}