#include "fighter.h"

void func_ovl3_80149720(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_801496A4);
}


void func_ovl3_80149744(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_ShieldBreakFall, 0.0F, 1.0F, 0x10B2U);
    func_ovl2_800D8EB8(fp);
    func_ovl2_800E806C(fp, gmHitCollision_HitStatus_Intangible, 0);
}

