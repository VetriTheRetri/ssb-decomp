#include "ftmasterhand.h"

bool32 func_ovl3_801598C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    Vec3f *translate_m = &DObjGetStruct(fighter_gobj)->translate;
    Vec3f *translate_t = &DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate;

    if (((translate_t->y - translate_m->y) > -300.0F) &&
    ((translate_t->y - translate_m->y) < 500.0F) &&
    ((translate_t->x - translate_m->x) * fp->lr < 1200.0F)) // Check if target is within range, return TRUE if Master Hand should flick his pointer finger
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80159964(GObj *fighter_gobj)
{
    if (func_ovl3_801598C0(fighter_gobj) != FALSE)
    {
        func_ovl3_80159AC4(fighter_gobj);
    }
}

void func_ovl3_80159994(GObj *fighter_gobj)
{
    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        func_ovl3_80159A54(fighter_gobj);
    }
}

void func_ovl3_801599C4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->phys_info.vel_normal.y = 0;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_WalkLoop, 0.0F, 1.0F, 0U);

    fp->phys_info.vel_normal.x = fp->lr * 35.0F;
}
