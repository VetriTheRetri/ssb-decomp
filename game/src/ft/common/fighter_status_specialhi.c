#include "fighter.h"

void (*ftCommon_SpecialHi_StatusList[Ft_Kind_EnumMax])(GObj*) =
{
    ftMario_SpecialHi_SetStatus,
    ftFox_SpecialHiStart_SetStatus,
    ftDonkey_SpecialHi_SetStatus,
    jtgt_ovl3_8015DE0C,
    ftMario_SpecialHi_SetStatus,
    jtgt_ovl3_80164284,
    jtgt_ovl3_8015ED3C,
    jtgt_ovl3_80160630,
    jtgt_ovl3_801611A8,
    jtgt_ovl3_801529A0,
    ftPurin_SpecialHi_SetStatus,
    ftNess_SpecialHiStart_SetStatus,
    ftMario_SpecialHi_SetStatus,
    ftMario_SpecialHi_SetStatus,
    ftMario_SpecialHi_SetStatus,
    ftFox_SpecialHiStart_SetStatus,
    ftDonkey_SpecialHi_SetStatus,
    jtgt_ovl3_8015DE0C,
    ftMario_SpecialHi_SetStatus,
    jtgt_ovl3_80164284,
    jtgt_ovl3_8015ED3C,
    jtgt_ovl3_80160630,
    jtgt_ovl3_801611A8,
    jtgt_ovl3_801529A0,
    ftPurin_SpecialHi_SetStatus,
    ftNess_SpecialHiStart_SetStatus,
    ftDonkey_SpecialHi_SetStatus
};

// 0x80151160
bool32 ftCommon_SpecialHi_CheckInterruptCommon(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((fp->input.pl.button_tap & fp->input.button_mask_b) && (attributes->is_have_specialhi) && (fp->input.pl.stick_range.y >= FTCOMMON_SPECIALHI_STICK_RANGE_MIN))
    {
        ftCommon_SpecialHi_StatusList[fp->ft_kind](fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}