#include "fighter.h"

void func_ovl3_8013EE50(GObj *fighter_gobj)
{
    if ((func_ovl3_80151098(fighter_gobj) == FALSE) &&
    (func_ovl3_80149D80(fighter_gobj) == FALSE) &&
    (ftCommon_AttackDash_CheckInterruptCommon(fighter_gobj) == FALSE) &&
    (func_ovl3_80148D2C(fighter_gobj, 4) == FALSE) &&
    (ftCommon_Appeal_CheckInterruptCommon(fighter_gobj) == FALSE) &&
    (func_ovl3_8013F598(fighter_gobj) == FALSE) &&
    (func_ovl3_8013F248(fighter_gobj) == FALSE))
    {
        func_ovl3_8013F0A0(fighter_gobj);
    }
}

void func_ovl3_8013EEE8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Run, 0.0F, 1.0F, FTSTATUPDATE_NULL_PRESERVE);

    fp->phys_info.vel_ground.x = fp->attributes->run_speed;
}

bool32 func_ovl3_8013EF2C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (attributes->dash_to_run <= fighter_gobj->anim_frame)
    {
        if (fighter_gobj->anim_frame < (attributes->dash_to_run + DObjGetStruct(fighter_gobj)->unk_dobj_0x78))
        {
            if ((fp->input.pl.stick_range.x * fp->lr) >= FTCOMMON_RUN_STICK_RANGE_MIN)
            {
                func_ovl3_8013EEE8(fighter_gobj);

                return TRUE;
            }
        }
    }
    return FALSE;
}