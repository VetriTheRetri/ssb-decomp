#include "fighter.h"

void (*ftKirby_SpecialN_StatusList[Ft_Kind_EnumMax])(GObj*) = 
{
    jtgt_ovl3_80156BD0,
    jtgt_ovl3_80156DD8,
    jtgt_ovl3_80157EAC,
    jtgt_ovl3_801576CC,
    jtgt_ovl3_80156BD0,
    jtgt_ovl3_80164940,
    jtgt_ovl3_8015F5B0,
    jtgt_ovl3_80160B30,
    jtgt_ovl3_80163154,
    jtgt_ovl3_801538C8,
    jtgt_ovl3_80151AC4,
    jtgt_ovl3_80155DBC,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80156BD0,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154,
    jtgt_ovl3_80163154
};
void (*ftCommon_SpecialN_StatusList[Ft_Kind_EnumMax])(GObj*) = 
{
    jtgt_ovl3_80156014,
    jtgt_ovl3_8015BC78,
    jtgt_ovl3_8015B61C,
    jtgt_ovl3_8015DB64,
    jtgt_ovl3_80156014,
    jtgt_ovl3_801639CC,
    jtgt_ovl3_8015E740,
    jtgt_ovl3_8015FB5C,
    jtgt_ovl3_80151060,
    jtgt_ovl3_80151D24,
    jtgt_ovl3_801514C4,
    ftNess_SpecialN_ProcStatus,
    jtgt_ovl3_80156014,
    jtgt_ovl3_80156014,
    jtgt_ovl3_80156014,
    jtgt_ovl3_8015BC78,
    jtgt_ovl3_8015B61C,
    jtgt_ovl3_8015DB64,
    jtgt_ovl3_80156014,
    jtgt_ovl3_801639CC,
    jtgt_ovl3_8015E740,
    jtgt_ovl3_8015FB5C,
    jtgt_ovl3_80151060,
    jtgt_ovl3_80151D24,
    jtgt_ovl3_801514C4,
    ftNess_SpecialN_ProcStatus,
    jtgt_ovl3_8015B61C
};

void jtgt_ovl3_80151060(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftKirby_SpecialN_StatusList[fp->fighter_vars.kirby.copy_id](fighter_gobj);
}

bool32 func_ovl3_80151098(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((fp->input.button_tap & fp->input.button_mask_b) && (attributes->is_have_specialn))
    {
        if ((fp->input.stick_range.y < FTCOMMON_SPECIALHI_STICK_RANGE_MIN) && (fp->input.stick_range.y > FTCOMMON_SPECIALLW_STICK_RANGE_MIN))
        {
            if ((fp->input.stick_range.x * fp->lr) < FTCOMMON_SPECIALN_TURN_STICK_RANGE_MIN)
            {
                func_ovl2_800E8044(fp);
            }
            ftCommon_SpecialN_StatusList[fp->ft_kind](fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}