#include "fighter.h"

void (*ftCommon_SpecialLw_StatusList[Ft_Kind_EnumMax])(GObj*) = 
{
    ftMario_SpecialLw_SetStatus,
    jtgt_ovl3_8015D250,
    jtgt_ovl3_8015BAFC,
    jtgt_ovl3_8015E220,
    ftMario_SpecialLw_SetStatus,
    jtgt_ovl3_8016458C,
    jtgt_ovl3_8015EFE4,
    jtgt_ovl3_80160128,
    jtgt_ovl3_80161A94,
    jtgt_ovl3_80151FBC,
    ftPurin_SpecialLw_SetStatus,
    ftNess_SpeciaLwStart_SetStatus,
    ftMario_SpecialLw_SetStatus,
    ftMario_SpecialLw_SetStatus,
    ftMario_SpecialLw_SetStatus,
    jtgt_ovl3_8015D250,
    jtgt_ovl3_8015BAFC,
    jtgt_ovl3_8015E220,
    ftMario_SpecialLw_SetStatus,
    jtgt_ovl3_8016458C,
    jtgt_ovl3_8015EFE4,
    jtgt_ovl3_80160128,
    jtgt_ovl3_80161A94,
    jtgt_ovl3_80151FBC,
    ftPurin_SpecialLw_SetStatus,
    ftNess_SpeciaLwStart_SetStatus,
    jtgt_ovl3_8015BAFC
};

bool32 func_ovl3_801511E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((fp->input.pl.button_tap & fp->input.button_mask_b) && (attributes->is_have_speciallw) && (fp->input.pl.stick_range.y <= FTCOMMON_SPECIALLW_STICK_RANGE_MIN))
    {
        ftCommon_SpecialLw_StatusList[fp->ft_kind](fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}
