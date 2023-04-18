#include "fighter.h"

void func_ovl3_80143560(GObj *fighter_gobj)
{
    if ((func_ovl3_80150F08(fighter_gobj) == FALSE) && (func_ovl3_80150B00(fighter_gobj) == FALSE) && (func_ovl3_8014019C(fighter_gobj) == FALSE))
    {
        func_ovl3_80147CCC(fighter_gobj);
    }
}

void func_ovl3_801435B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE7D8(fighter_gobj) != FALSE)
    {
        if (fp->coll_data.coll_type & 0x3000)
        {
            func_ovl3_80144C24(fighter_gobj);
        }
        else if ((func_ovl3_80144760(fighter_gobj) == FALSE) && (func_ovl3_801446BC(fighter_gobj) == FALSE))
        {
            ftCommon_DownBounce_ApplyStatus(fighter_gobj);
        }
    }
}

void func_ovl3_80143630(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800D8EB8(fp);
    func_ovl2_800E806C(fp, 3, 0);
}

void func_ovl3_80143664(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Common_DamageFall, 0.0F, 1.0F, 0x108U);
    func_ovl3_80143630(fighter_gobj);
}

void func_ovl3_801436A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_DamageFall, 0.0F, 1.0F, 8U);
    func_ovl3_80143630(fighter_gobj);

    fp->timer_unk2 = 0x10000;
}

void func_ovl3_801436F0(GObj *fighter_gobj) // Unused
{
    ftStatus_Update(fighter_gobj, ftStatus_Common_DamageFall, fighter_gobj->anim_frame, 1.0F, 0x108U);
    func_ovl3_80143630(fighter_gobj);
}