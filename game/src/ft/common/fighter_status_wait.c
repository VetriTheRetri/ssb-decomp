#include "fighter.h"

void func_ovl3_8013E070(GObj *fighter_gobj)
{
    !ftStatus_CheckInterruptAll(fighter_gobj);
}

void func_ovl3_8013E1C8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800F3794(fighter_gobj) != FALSE)
    {
        func_ovl2_800F3938(fighter_gobj);
    }
    else
    {
        if (fp->ground_or_air == air)
        {
            ftMapCollide_SetGround(fp);
        }
        ftStatus_Update(fighter_gobj, ftStatus_Common_Wait, 0.0F, 1.0F, 0U);

        fp->x192_flag_b0 = TRUE;

        func_ovl2_800E7F7C(fighter_gobj, 120);
    }
}

bool32 func_ovl3_8013E258(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->input.stick_range.x * fp->lr) < 0) || (ABS(fp->input.stick_range.x) < 8))
    {
        return TRUE;
    }
    else return FALSE;
}


bool32 func_ovl3_8013E2A0(GObj *fighter_gobj)
{
    if (func_ovl3_8013E258(fighter_gobj) != FALSE)
    {
        func_ovl3_8013E1C8(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}