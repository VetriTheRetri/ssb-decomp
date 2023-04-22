#include "fighter.h"

void func_ovl3_80147A70(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->command_vars.flags.flag1--;

        if (fp->command_vars.flags.flag1 == (FTCOMMON_HAMMER_TURN_FRAMES / 2))
        {
            fp->lr = -fp->lr;
        }
        fp->joint[0]->rotate.y += FTCOMMON_HAMMER_TURN_ROTATE_STEP;

        func_ovl2_800EB528(fp->joint[0]);
    }
}

void func_ovl3_80147AD0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80147A70(fighter_gobj);

    if (fp->command_vars.flags.flag1 == 0)
    {
        func_ovl2_800F3938(fighter_gobj);
    }
}

void func_ovl3_80147B14(GObj *fighter_gobj)
{
    func_ovl3_8014800C(fighter_gobj);
}

void func_ovl3_80147B34(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag1 = FTCOMMON_HAMMER_TURN_FRAMES;

    ftStatus_Update(fighter_gobj, ftStatus_Common_HammerTurn, func_ovl2_800F3828(fighter_gobj), 1.0F, func_ovl2_800F385C(fighter_gobj));
    func_ovl2_800F388C(fighter_gobj);
    func_ovl3_80147A70(fighter_gobj);
}

bool32 func_ovl3_80147B9C(GObj *fighter_gobj)
{
    if (func_ovl3_8013E9D0(fighter_gobj) != FALSE)
    {
        func_ovl3_80147B34(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}