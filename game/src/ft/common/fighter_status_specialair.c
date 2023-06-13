#include "fighter.h"

void (*ftKirby_SpecialAirN_StatusList[Ft_Kind_EnumMax])(GObj*) = 
{ 
    ftKirby_CopyMario_SpecialAirN_SetStatus, // Mario
    jtgt_ovl3_80156E18, // Fox
    jtgt_ovl3_80157F04, // Donkey Kong
    jtgt_ovl3_80157744, // Samus
    ftKirby_CopyMario_SpecialAirN_SetStatus, // Luigi
    jtgt_ovl3_801649C0, // Link
    jtgt_ovl3_8015F60C, // Yoshi
    jtgt_ovl3_80160B70, // Captain Faclon
    jtgt_ovl3_801633A0, // Kirby
    jtgt_ovl3_80153908, // Pikachu
    ftKirby_CopyPurin_SpecialAirN_SetStatus, // Jigglypuff
    ftKirby_CopyNess_SpecialAirN_SetStatus, // Ness
    jtgt_ovl3_801633A0, // Master Hand
    ftKirby_CopyMario_SpecialAirN_SetStatus, // Metal Mario
    jtgt_ovl3_801633A0, // Poly Mario
    jtgt_ovl3_801633A0, // Poly Fox
    jtgt_ovl3_801633A0, // Poly Donkey Kong
    jtgt_ovl3_801633A0, // Poly Samus
    jtgt_ovl3_801633A0, // Poly Luigi
    jtgt_ovl3_801633A0, // Poly Link
    jtgt_ovl3_801633A0, // Poly Yoshi
    jtgt_ovl3_801633A0, // Poly Captain Falcon
    jtgt_ovl3_801633A0, // Poly Kirby
    jtgt_ovl3_801633A0, // Poly Pikachu
    jtgt_ovl3_801633A0, // Poly Jigglypuff
    jtgt_ovl3_801633A0, // Poly Ness
    jtgt_ovl3_801633A0, // Giant Donkey Kong (This is actually inaccessible, Kirby's copy ID for Giant DK is always 2)
};

void (*ftCommon_SpecialAirN_StatusList[Ft_Kind_EnumMax])(GObj*) =
{
    ftMario_SpecialAirN_SetStatus,
    ftFox_SpecialAirN_SetStatus,
    ftDonkey_SpecialAirNStart_SetStatus,
    jtgt_ovl3_8015DBDC,
    ftMario_SpecialAirN_SetStatus,
    jtgt_ovl3_80163A4C,
    jtgt_ovl3_8015E79C,
    ftCaptain_SpecialAirN_SetStatus,
    ftKirby_SpecialAirN_SetStatusIndex,
    jtgt_ovl3_80151D64,
    ftPurin_SpecialAirN_SetStatus,
    ftNess_SpecialAirN_SetStatus,
    ftMario_SpecialAirN_SetStatus,
    ftMario_SpecialAirN_SetStatus,
    ftMario_SpecialAirN_SetStatus,
    ftFox_SpecialAirN_SetStatus,
    ftDonkey_SpecialAirNStart_SetStatus,
    jtgt_ovl3_8015DBDC,
    ftMario_SpecialAirN_SetStatus,
    jtgt_ovl3_80163A4C,
    jtgt_ovl3_8015E79C,
    ftCaptain_SpecialAirN_SetStatus,
    ftKirby_SpecialAirN_SetStatusIndex,
    jtgt_ovl3_80151D64,
    ftPurin_SpecialAirN_SetStatus,
    ftNess_SpecialAirN_SetStatus,
    ftDonkey_SpecialAirNStart_SetStatus
};

void (*ftCommon_SpecialAirHi_StatusList[Ft_Kind_EnumMax])(GObj*) =
{
    ftMario_SpecialAirHi_SetStatus,
    ftFox_SpecialAirHiStart_SetStatus,
    ftDonkey_SpecialAirHi_SetStatus,
    jtgt_ovl3_8015DE90,
    ftMario_SpecialAirHi_SetStatus,
    jtgt_ovl3_80164348,
    jtgt_ovl3_8015ED7C,
    ftCaptain_SpecialAirHi_SetStatus,
    ftKirby_SpecialAirHi_SetStatus,
    jtgt_ovl3_801529EC,
    ftPurin_SpecialAirHi_SetStatus,
    ftNess_SpecialAirHiStart_SetStatus,
    ftMario_SpecialAirN_SetStatus,
    ftMario_SpecialAirHi_SetStatus,
    ftMario_SpecialAirHi_SetStatus,
    ftFox_SpecialAirHiStart_SetStatus,
    ftDonkey_SpecialAirHi_SetStatus,
    jtgt_ovl3_8015DE90,
    ftMario_SpecialAirHi_SetStatus,
    jtgt_ovl3_80164348,
    jtgt_ovl3_8015ED7C,
    ftCaptain_SpecialAirHi_SetStatus,
    ftKirby_SpecialAirHi_SetStatus,
    jtgt_ovl3_801529EC,
    ftPurin_SpecialAirHi_SetStatus,
    ftNess_SpecialAirHiStart_SetStatus,
    ftDonkey_SpecialAirHi_SetStatus
};

void (*ftCommon_SpecialAirLw_StatusList[Ft_Kind_EnumMax])(GObj*) =
{
    ftMario_SpecialAirLw_SetStatus,
    jtgt_ovl3_8015D290,
    NULL,
    jtgt_ovl3_8015E274,
    ftMario_SpecialAirLw_SetStatus,
    jtgt_ovl3_801645E8,
    jtgt_ovl3_8015F04C,
    ftCaptain_SpecialAirLw_SetStatus,
    jtgt_ovl3_80161B70,
    jtgt_ovl3_80151FFC,
    ftPurin_SpecialAirLw_SetStatus,
    ftNess_SpecialAirLwStart_SetStatus,
    ftMario_SpecialAirLw_SetStatus,
    ftMario_SpecialAirLw_SetStatus,
    ftMario_SpecialAirLw_SetStatus,
    jtgt_ovl3_8015D290,
    NULL,
    jtgt_ovl3_8015E274,
    ftMario_SpecialAirLw_SetStatus,
    jtgt_ovl3_801645E8,
    jtgt_ovl3_8015F04C,
    ftCaptain_SpecialAirLw_SetStatus,
    jtgt_ovl3_80161B70,
    jtgt_ovl3_80151FFC,
    ftPurin_SpecialAirLw_SetStatus,
    ftNess_SpecialAirLwStart_SetStatus,
    NULL
};

// 0x80150ED0
void ftKirby_SpecialAirN_SetStatusIndex(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftKirby_SpecialAirN_StatusList[fp->fighter_vars.kirby.copy_id](fighter_gobj);
}

// 0x80150F08
bool32 ftCommon_SpecialAir_CheckInterruptCommon(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->input.pl.button_tap & fp->input.button_mask_b)
    {
        if (ftCommon_HammerCheckHold(fighter_gobj) == FALSE)
        {
            if (fp->input.pl.stick_range.y >= FTCOMMON_SPECIALHI_STICK_RANGE_MIN)
            {
                if (attributes->is_have_specialairhi)
                {
                    ftCommon_SpecialAirHi_StatusList[fp->ft_kind](fighter_gobj);

                    return TRUE;
                }
            }
            else if (fp->input.pl.stick_range.y <= FTCOMMON_SPECIALLW_STICK_RANGE_MIN)
            {
                if (attributes->is_have_specialairlw)
                {
                    ftCommon_SpecialAirLw_StatusList[fp->ft_kind](fighter_gobj);

                    return TRUE;
                }
            }
            else if (attributes->is_have_specialairn)
            {
                if ((fp->input.pl.stick_range.x * fp->lr) < FTCOMMON_SPECIALN_TURN_STICK_RANGE_MIN)
                {
                    ftCommon_StickInputSetLR(fp);
                }
                ftCommon_SpecialAirN_StatusList[fp->ft_kind](fighter_gobj);

                return TRUE;
            }
        }
    }
    return FALSE;
}