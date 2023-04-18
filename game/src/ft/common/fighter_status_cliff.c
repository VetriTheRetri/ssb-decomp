#include "fighter.h"

void func_ovl3_80144EE0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        switch (fp->status_vars.common.cliff.status_id)
        {
        case 0:
            func_ovl3_801451F0(fighter_gobj);
            break;

        case 1:
            func_ovl3_801456B4(fighter_gobj);
            break;

        case 2:
            func_ovl3_8014586C(fighter_gobj);
            break;
        }
    }
}

void func_ovl3_80144F64(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        switch (fp->status_vars.common.cliff.status_id)
        {
        case 3:
            func_ovl3_80145240(fighter_gobj);
            break;

        case 4:
            func_ovl3_80145704(fighter_gobj);
            break;

        case 5:
            func_ovl3_801458BC(fighter_gobj);
            break;
        }
    }
}