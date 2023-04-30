#include "fighter.h"

void (*ftKirby_SpecialAirN_StatusList[Ft_Kind_EnumMax])(GObj*) = 
{ 
    jtgt_ovl3_80156C38, // Mario
    jtgt_ovl3_80156E18, // Fox
    jtgt_ovl3_80157F04, // Donkey Kong
    jtgt_ovl3_80157744, // Samus
    jtgt_ovl3_80156C38, // Luigi
    jtgt_ovl3_801649C0, // Link
    jtgt_ovl3_8015F60C, // Yoshi
    jtgt_ovl3_80160B70, // Captain Faclon
    jtgt_ovl3_801633A0, // Kirby
    jtgt_ovl3_80153908, // Pikachu
    jtgt_ovl3_80151B04, // Jigglypuff
    jtgt_ovl3_80155DFC, // Ness
    jtgt_ovl3_801633A0, // Master Hand
    jtgt_ovl3_80156C38, // Metal Mario
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

void (*ftCommon_SpecialAirN_StatusList[Ft_Kind_EnumMax])(GObj *) =
{
    jtgt_ovl3_80156054,
    jtgt_ovl3_8015BCB8,
    jtgt_ovl3_8015B674,
    jtgt_ovl3_8015DBDC,
    jtgt_ovl3_80156054,
    jtgt_ovl3_80163A4C,
    jtgt_ovl3_8015E79C,
    jtgt_ovl3_8015FBC0,
    jtgt_ovl3_80150ED0,
    jtgt_ovl3_80151D64,
    jtgt_ovl3_80151504,
    ftNess_SpecialAirN_ProcStatus,
    jtgt_ovl3_80156054,
    jtgt_ovl3_80156054,
    jtgt_ovl3_80156054,
    jtgt_ovl3_8015BCB8,
    jtgt_ovl3_8015B674,
    jtgt_ovl3_8015DBDC,
    jtgt_ovl3_80156054,
    jtgt_ovl3_80163A4C,
    jtgt_ovl3_8015E79C,
    jtgt_ovl3_8015FBC0,
    jtgt_ovl3_80150ED0,
    jtgt_ovl3_80151D64,
    jtgt_ovl3_80151504,
    ftNess_SpecialAirN_ProcStatus,
    jtgt_ovl3_8015B674
};

void (*ftCommon_SpecialAirHi_StatusList[Ft_Kind_EnumMax])(GObj *) =
{
    jtgt_ovl3_80156478,
    jtgt_ovl3_8015CB10,
    jtgt_ovl3_8015B9B8,
    jtgt_ovl3_8015DE90,
    jtgt_ovl3_80156478,
    jtgt_ovl3_80164348,
    jtgt_ovl3_8015ED7C,
    jtgt_ovl3_801607B4,
    jtgt_ovl3_80161270,
    jtgt_ovl3_801529EC,
    jtgt_ovl3_801516D8,
    jtgt_ovl3_80154030,
    jtgt_ovl3_80156054,
    jtgt_ovl3_80156478,
    jtgt_ovl3_80156478,
    jtgt_ovl3_8015CB10,
    jtgt_ovl3_8015B9B8,
    jtgt_ovl3_8015DE90,
    jtgt_ovl3_80156478,
    jtgt_ovl3_80164348,
    jtgt_ovl3_8015ED7C,
    jtgt_ovl3_801607B4,
    jtgt_ovl3_80161270,
    jtgt_ovl3_801529EC,
    jtgt_ovl3_801516D8,
    jtgt_ovl3_80154030,
    jtgt_ovl3_8015B9B8
};

void (*ftCommon_SpecialAirLw_StatusList[Ft_Kind_EnumMax])(GObj *) =
{
    jtgt_ovl3_80156910,
    jtgt_ovl3_8015D290,
    NULL,
    jtgt_ovl3_8015E274,
    jtgt_ovl3_80156910,
    jtgt_ovl3_801645E8,
    jtgt_ovl3_8015F04C,
    jtgt_ovl3_8016020C,
    jtgt_ovl3_80161B70,
    jtgt_ovl3_80151FFC,
    jtgt_ovl3_8015181C,
    jtgt_ovl3_801554B0,
    jtgt_ovl3_80156910,
    jtgt_ovl3_80156910,
    jtgt_ovl3_80156910,
    jtgt_ovl3_8015D290,
    NULL,
    jtgt_ovl3_8015E274,
    jtgt_ovl3_80156910,
    jtgt_ovl3_801645E8,
    jtgt_ovl3_8015F04C,
    jtgt_ovl3_8016020C,
    jtgt_ovl3_80161B70,
    jtgt_ovl3_80151FFC,
    jtgt_ovl3_8015181C,
    jtgt_ovl3_801554B0,
    NULL
};

void jtgt_ovl3_80150ED0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftKirby_SpecialAirN_StatusList[fp->fighter_vars.kirby.copy_id](fighter_gobj);
}

bool32 func_ovl3_80150F08(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->input.button_tap & fp->input.button_mask_b)
    {
        if (func_ovl2_800F3794(fighter_gobj) == FALSE)
        {
            if (fp->input.stick_range.y >= FTCOMMON_SPECIALHI_STICK_RANGE_MIN)
            {
                if (attributes->is_have_specialairhi)
                {
                    ftCommon_SpecialAirHi_StatusList[fp->ft_kind](fighter_gobj);

                    return TRUE;
                }
            }
            else if (fp->input.stick_range.y <= FTCOMMON_SPECIALLW_STICK_RANGE_MIN)
            {
                if (attributes->is_have_specialairlw)
                {
                    ftCommon_SpecialAirLw_StatusList[fp->ft_kind](fighter_gobj);

                    return TRUE;
                }
            }
            else if (attributes->is_have_specialairn)
            {
                if ((fp->input.stick_range.x * fp->lr) < FTCOMMON_SPECIALN_TURN_STICK_RANGE_MIN)
                {
                    func_ovl2_800E8044(fp);
                }
                ftCommon_SpecialAirN_StatusList[fp->ft_kind](fighter_gobj);

                return TRUE;
            }
        }
    }
    return FALSE;
}