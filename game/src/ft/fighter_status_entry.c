#include "fighter.h"

void func_ovl3_8013D930(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Common_Entry, 0.0F, 1.0F, 0U);

    fp->x18D_flag_b7 = TRUE;
    fp->x18E_flag_b0 = TRUE;
    fp->x191_flag_b1 = TRUE;
    fp->x18E_flag_b3 = TRUE;
}

void func_ovl3_8013D994(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.entry.entry_timer != 0)
    {
        fp->status_vars.common.entry.entry_timer--;

        if (fp->status_vars.common.entry.entry_timer == 0)
        {
            if (fp->ft_kind == Ft_Kind_MasterHand)
            {
                func_ovl3_80159040(fighter_gobj);
            }
            else
            {
                fp->lr = fp->status_vars.common.entry.lr_entry;

                DObjGetStruct(fighter_gobj)->translate = fp->entry_pos;

                fp->coll_data.ground_line_id = fp->status_vars.common.entry.ground_line_id;

                func_ovl3_8013E1C8(fighter_gobj);
            }
        }
    }
}

void func_ovl3_8013DA14(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != 0)
    {
        if ((fp->ft_kind == Ft_Kind_Pikachu) || (fp->ft_kind == Ft_Kind_Purin) || (fp->ft_kind == Ft_Kind_PolyPikachu) || (fp->ft_kind == Ft_Kind_PolyPurin))
        {
            func_ovl2_80102C28(&fp->entry_pos);
        }
        fp->cmd_flags.flag1 = 0;
    }
    if (fp->cmd_flags.flag2 != 0)
    {
        fp->cmd_flags.flag2 = 0;

        fp->x18E_flag_b0 = FALSE;
    }
}

void func_ovl3_8013DA94(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8013DA14(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        fp->lr = fp->status_vars.common.entry.lr_entry;

        DObjGetStruct(fighter_gobj)->translate = fp->entry_pos;

        fp->coll_data.ground_line_id = fp->status_vars.common.entry.ground_line_id;

        if (fp->ft_kind == Ft_Kind_MasterHand)
        {
            func_ovl3_80159040(fighter_gobj);
        }
        else func_ovl3_8013E1C8(fighter_gobj);
    }
}

void func_ovl3_8013DB2C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    DObj *topn_joint = fp->joint[0];
    DObj *transn_joint = fp->joint[1];

    topn_joint->translate.y = fp->entry_pos.y + transn_joint->translate.y;

    if (fp->status_vars.common.entry.is_rotate != FALSE)
    {
        topn_joint->translate.x = fp->entry_pos.x - transn_joint->translate.x;
        topn_joint->translate.z = fp->entry_pos.z - transn_joint->translate.z;

        topn_joint->rotate.y = PI32;
    }
    else
    {
        topn_joint->translate.x = fp->entry_pos.x + transn_joint->translate.x;
        topn_joint->translate.z = fp->entry_pos.z + transn_joint->translate.z;
    }
}

void func_ovl3_8013DBAC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->x191_flag_b1 = TRUE;

    fp->x191_flag_b4567 = 3;

    fp->x18E_flag_b0 = TRUE;
    fp->x18E_flag_b3 = TRUE;
}