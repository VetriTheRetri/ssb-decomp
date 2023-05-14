#include "fighter.h"

void (*ftCommon_SpecialHi_StatusList[Ft_Kind_EnumMax])(GObj*) =
{
    jtgt_ovl3_80156428,
    jtgt_ovl3_8015CAB0,
    jtgt_ovl3_8015B974,
    jtgt_ovl3_8015DE0C,
    jtgt_ovl3_80156428,
    jtgt_ovl3_80164284,
    jtgt_ovl3_8015ED3C,
    jtgt_ovl3_80160630,
    jtgt_ovl3_801611A8,
    jtgt_ovl3_801529A0,
    jtgt_ovl3_801516A0,
    jtgt_ovl3_80153FF0,
    jtgt_ovl3_80156428,
    jtgt_ovl3_80156428,
    jtgt_ovl3_80156428,
    jtgt_ovl3_8015CAB0,
    jtgt_ovl3_8015B974,
    jtgt_ovl3_8015DE0C,
    jtgt_ovl3_80156428,
    jtgt_ovl3_80164284,
    jtgt_ovl3_8015ED3C,
    jtgt_ovl3_80160630,
    jtgt_ovl3_801611A8,
    jtgt_ovl3_801529A0,
    jtgt_ovl3_801516A0,
    jtgt_ovl3_80153FF0,
    jtgt_ovl3_8015B974
};

bool32 func_ovl3_80151160(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((fp->input.pl.button_tap & fp->input.button_mask_b) && (attributes->is_have_specialhi) && (fp->input.pl.stick_range.y >= FTCOMMON_SPECIALHI_STICK_RANGE_MIN))
    {
        ftCommon_SpecialHi_StatusList[fp->ft_kind](fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}