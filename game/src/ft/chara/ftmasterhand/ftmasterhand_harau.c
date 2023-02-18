#include "ftmasterhand.h"

void func_ovl3_801593E0(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_Harau, 0.0F, 1.0F, 0U);
}

void func_ovl3_8015940C(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

        if (fp->coll_data.ground_line_id == -1)
        {
            func_ovl3_80159040(fighter_gobj);
        }
        else func_ovl3_801593E0(fighter_gobj);
    }
}

void func_ovl3_8015946C(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    func_ovl2_800D93E4(fighter_gobj);

    fp = FighterGetStruct(fighter_gobj);

    fp->phys_info.vel_normal.x += fp->lr * FTMASTERHAND_HARAU_VEL_X;
}

void func_ovl3_801594BC(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_Harau, 0.0F, 1.0F, 0U);
    func_ovl3_80157F90(fighter_gobj);
}
