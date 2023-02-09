#include "ftpurin.h"

void func_ovl3_80151710(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80151798);
}

void func_ovl3_80151734(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80151758);
}

void func_ovl3_80151758(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Purin_SpecialLw, fighter_gobj->anim_frame, 1.0F, 0x92U);
}

void func_ovl3_80151798(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Purin_SpecialAirLw, fighter_gobj->anim_frame, 1.0F, 0x92U);
    func_ovl2_800D8EB8(fp);
}

void jtgt_ovl3_801517E4(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Purin_SpecialLw, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
}

void jtgt_ovl3_8015181C(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Purin_SpecialAirLw, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
}
