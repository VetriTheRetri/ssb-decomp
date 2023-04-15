#include "fighter.h"

void func_ovl3_80141D60(GObj *fighter_gobj)
{
    if ((func_ovl3_80150F08(fighter_gobj) == FALSE) && (func_ovl3_80150B00(fighter_gobj) == FALSE))
    {
        func_ovl3_8014019C(fighter_gobj);
    }
}

void func_ovl3_80141DA0(GObj *fighter_gobj, s32 status_id, f32 frame_begin, u32 flags)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, status_id, frame_begin, 1.0F, flags);
    func_ovl2_800D8EB8(fp);

    fp->phys_info.vel_air.y = 0.0F;

    fp->coll_data.ignore_line_id = fp->coll_data.ground_line_id;

    fp->buffer_stick_y = U8_MAX - 1;
}

void func_ovl3_80141E18(GObj *fighter_gobj)
{
    func_ovl3_801430A8(fighter_gobj);
}

void func_ovl3_80141E38(GObj *fighter_gobj)
{
    func_ovl3_80141DA0(fighter_gobj, ftStatus_Common_GuardPass, 1.0F, 0U);
}
