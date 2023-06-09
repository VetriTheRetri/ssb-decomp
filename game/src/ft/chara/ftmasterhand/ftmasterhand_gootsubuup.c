#include "ftmasterhand.h"

void func_ovl3_80159B00(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    jtgt_ovl2_800D9414(fighter_gobj);

    fp = ftGetStruct(fighter_gobj);

    fp->phys_info.vel_air.y += 50.0F;
}

void func_ovl3_80159B3C(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    func_ovl2_800DE324(fighter_gobj);

    fp = ftGetStruct(fighter_gobj);

    if (3000.0F <= -fp->coll_data.ground_dist)
    {
        DObj *joint = DObjGetStruct(fighter_gobj);

        joint->translate.y += (fp->coll_data.ground_dist + 3000.0F);

        func_ovl3_80159D34(fighter_gobj);
    }
}

void func_ovl3_80159B9C(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_GootsubuUp, 0.0F, 1.0F, 0U);
}
