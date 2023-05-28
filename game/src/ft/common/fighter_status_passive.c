#include "fighter.h"

void func_ovl3_80144660(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        ftMapCollide_SetGround(fp);
    }
    ftStatus_Update(fighter_gobj, ftStatus_Common_Passive, 0.0F, 1.0F, 0U);
    ftCommon_VelDamageTransferGround(fp);
}

bool32 func_ovl3_801446BC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->time_since_last_z < 20)
    {
        func_ovl3_80144660(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}