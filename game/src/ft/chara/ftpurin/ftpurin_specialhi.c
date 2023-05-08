#include "ftpurin.h"

void func_ovl3_80151550(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 == 1)
    {
        if (func_ovl2_801020F4(fighter_gobj) != NULL)
        {
            fp->is_statupdate_stop_gfx = TRUE;
        }
        fp->command_vars.flags.flag1 = 0;
    }
    if (fp->status_info.status_id == ftStatus_Purin_SpecialHi)
    {
        func_ovl2_800D94C4(fighter_gobj);
    }
    else func_ovl2_800D94E8(fighter_gobj);
}

void func_ovl3_801515F0(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80151614);
}

void func_ovl3_801515CC(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80151654);
}

void func_ovl3_80151614(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialHi, fighter_gobj->anim_frame, 1.0F, 0x97U);
}

void func_ovl3_80151654(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialAirHi, fighter_gobj->anim_frame, 1.0F, 0x97U);
    func_ovl2_800D8EB8(fp);
}

void jtgt_ovl3_801516A0(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

void jtgt_ovl3_801516D8(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialAirHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}
