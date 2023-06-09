#include "fighter.h"

void func_ovl3_801497A0(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, ftCommon_FuraFura_SetStatus);
}

void func_ovl3_801497C4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    s32 status_id = (fp->status_info.status_id == ftStatus_Common_ShieldBreakDownD) ? ftStatus_Common_ShieldBreakStandD : ftStatus_Common_ShieldBreakStandU;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0xB2U);
}
