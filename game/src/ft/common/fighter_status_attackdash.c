#include "fighter.h"
#include "article.h"

// 0x8014F670
void ftCommon_AttackDash_SetStatus(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Common_AttackDash, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
}

// 0x8014F69C - Also checks LightThrowDash and ItemSwingDash
bool32 ftCommon_AttackDash_CheckInterruptCommon(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->input.pl.button_tap & fp->input.button_mask_a)
    {
        if (fp->item_hold != NULL)
        {
            if ((fp->input.pl.button_hold & fp->input.button_mask_z) || (atGetStruct(fp->item_hold)->type == At_Type_Throw))
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowDash);

                return TRUE;
            }
            if (atGetStruct(fp->item_hold)->type == At_Type_Swing)
            {
                func_ovl3_80146E94(fighter_gobj, 3);

                return TRUE;
            }
        }
        if (attributes->is_have_attackdash)
        {
            ftCommon_AttackDash_SetStatus(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}