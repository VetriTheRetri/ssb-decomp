#include "fighter.h"

void func_ovl3_8014AAF0(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        Fighter_Struct *capture_fp = FighterGetStruct(this_fp->capture_gobj);

        if ((capture_fp->ft_kind != Ft_Kind_Donkey) &&
        (capture_fp->ft_kind != Ft_Kind_PolyDonkey) &&
        (capture_fp->ft_kind != Ft_Kind_GiantDonkey) ||
        (capture_fp->status_info.status_id != ftStatus_Common_ThrowF))
        {
            func_ovl3_8014ACB4(fighter_gobj, this_fp->status_vars.common.thrown.status_id);
        }
    }
}

void func_ovl3_8014AB64(GObj *fighter_gobj)
{
    DObj *joint = DObjGetStruct(fighter_gobj);
    ftCommon_CapturePulled_BitmapRotateScale(fighter_gobj, &joint->translate, &joint->rotate);
}

void func_ovl3_8014AB8C(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
    Vec3f *this_pos = &DObjGetStruct(fighter_gobj)->translate;
    s32 unused[3];
    f32 dist_y;

    if (capture_fp->coll_data.ground_line_id != -1)
    {
        if (func_ovl2_800F3DD8(capture_fp->coll_data.ground_line_id, this_pos, &dist_y, &this_fp->coll_data.ground_flags, &this_fp->coll_data.ground_angle.x) != FALSE)
        {
            this_fp->coll_data.ground_line_id = capture_fp->coll_data.ground_line_id;

            return;
        }
    }
    func_ovl2_800DE324(fighter_gobj);
}

void func_ovl3_8014AC0C(GObj *fighter_gobj, s32 status_id_new, s32 status_id_queue)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp = FighterGetStruct(this_fp->capture_gobj);

    this_fp->ground_or_air = air;
    this_fp->jumps_used = 1;

    ftStatus_Update(fighter_gobj, status_id_new, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    if ((capture_fp->ft_kind == Ft_Kind_Yoshi) || (capture_fp->ft_kind == Ft_Kind_PolyYoshi))
    {
        this_fp->is_invisible = TRUE;

        ftCommon_SetHitStatusAll(fighter_gobj, gmHitCollision_HitStatus_Intangible);
    }
    ftCommon_SetCaptureFlags(this_fp, 0x3FU);

    this_fp->status_vars.common.thrown.status_id = status_id_queue;
}

void func_ovl3_8014ACB4(GObj *fighter_gobj, s32 status_id)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp = FighterGetStruct(this_fp->capture_gobj);

    this_fp->ground_or_air = air;
    this_fp->jumps_used = 1;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    if ((capture_fp->ft_kind == Ft_Kind_Yoshi) || (capture_fp->ft_kind == Ft_Kind_PolyYoshi))
    {
        this_fp->is_invisible = TRUE;

        ftCommon_SetHitStatusAll(fighter_gobj, gmHitCollision_HitStatus_Intangible);
    }
    ftCommon_SetCaptureFlags(this_fp, 0x3FU);

    if ((capture_fp->ft_kind == Ft_Kind_Mario)  ||
    (capture_fp->ft_kind == Ft_Kind_MetalMario) ||
    (capture_fp->ft_kind == Ft_Kind_Luigi)      ||
    (capture_fp->ft_kind == Ft_Kind_PolyMario)  ||
    (capture_fp->ft_kind == Ft_Kind_PolyLuigi))
    {
        if (capture_fp->status_info.status_id == ftStatus_Common_ThrowB)
        {
            func_ovl2_800E806C(this_fp, 7, 0);
        }
    }
}