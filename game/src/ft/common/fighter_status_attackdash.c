#include "fighter.h"
#include "article.h"

void func_ovl3_8014F670(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Common_AttackDash, 0.0F, 1.0F, 0U);
}

bool32 func_ovl3_8014F69C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->input.pl.button_tap & fp->input.button_mask_a)
    {
        if (fp->item_hold != NULL)
        {
            if ((fp->input.pl.button_hold & fp->input.button_mask_z) || (ArticleGetStruct(fp->item_hold)->type == At_Type_Throw))
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowDash);

                return TRUE;
            }
            if (ArticleGetStruct(fp->item_hold)->type == At_Type_Swing)
            {
                func_ovl3_80146E94(fighter_gobj, 3);

                return TRUE;
            }
        }
        if (attributes->is_have_attackdash)
        {
            func_ovl3_8014F670(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}