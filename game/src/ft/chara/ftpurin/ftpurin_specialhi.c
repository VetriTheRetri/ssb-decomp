#include "ftpurin.h"

#define FTPURIN_SPECIALHI_STATUPDATE_FLAGS (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_HITSTATUS_PRESERVE | FTSTATUPDATE_GFX_PRESERVE | FTSTATUPDATE_COLANIM_PRESERVE | FTSTATUPDATE_HIT_PRESERVE)

// 0x80151550
void ftPurin_SpecialHi_ProcUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

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
        ftCommon_IfAnimEnd_SetStatusWait(fighter_gobj);
    }
    else ftCommon_IfAnimEnd_SetStatusFall(fighter_gobj);
}

// 0x801515F0
void ftPurin_SpecialAirHi_ProcMap(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, ftPurin_SpecialAirHi_SwitchStatusGround);
}

// 0x801515CC
void ftPurin_SpecialHi_ProcMap(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, ftPurin_SpecialHi_SwitchStatusAir);
}

// 0x80151614
void ftPurin_SpecialAirHi_SwitchStatusGround(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(ftGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialHi, fighter_gobj->anim_frame, 1.0F, FTPURIN_SPECIALHI_STATUPDATE_FLAGS);
}

// 0x80151654
void ftPurin_SpecialHi_SwitchStatusAir(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialAirHi, fighter_gobj->anim_frame, 1.0F, FTPURIN_SPECIALHI_STATUPDATE_FLAGS);
    func_ovl2_800D8EB8(fp);
}

// 0x801516A0
void ftPurin_SpecialHi_SetStatus(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

// 0x801516D8
void ftPurin_SpecialAirHi_SetStatus(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Purin_SpecialAirHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}
