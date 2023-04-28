#include "fighter.h"
#include "article.h"

void func_ovl3_8014A5F0(GObj *fighter_gobj, Vec3f *this_pos, Vec3f *rotate)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp = FighterGetStruct(this_fp->capture_gobj);
    DObj *joint = DObjGetStruct(fighter_gobj)->next;
    s32 unused[13]; // Why so much stack?
    Vec3f capture_pos;

    func_ovl0_800C9A38(&capture_pos, capture_fp->joint[capture_fp->attributes->joint_itemhold_heavy], rotate);
    func_ovl2_800EDA0C(&capture_pos, rotate);

    this_pos->x = (-joint->translate.x * DObjGetStruct(fighter_gobj)->scale.x);
    this_pos->y = (-joint->translate.y * DObjGetStruct(fighter_gobj)->scale.y);
    this_pos->z = (-joint->translate.z * DObjGetStruct(fighter_gobj)->scale.z);

    func_ovl2_800ED3C0(&capture_pos, this_pos);
}

void func_ovl3_8014A6B4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    func_ovl3_8014A5F0(fighter_gobj, &pos, &DObjGetStruct(fighter_gobj)->rotate);

    DObjGetStruct(fighter_gobj)->translate.x = pos.x;
    DObjGetStruct(fighter_gobj)->translate.z = pos.z;

    if ((fp->status_info.status_id == ftStatus_Common_CapturePulled) && (fp->status_vars.common.capture.is_goto_pulled_wait != FALSE))
    {
        func_ovl3_8014AA58(fighter_gobj);
    }
}

void func_ovl3_8014A72C(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
    Vec3f *this_pos = &DObjGetStruct(fighter_gobj)->translate;
    Vec3f capture_pos;
    f32 dist_y;

    if (func_ovl2_800F3DD8(capture_fp->coll_data.ground_line_id, this_pos, &dist_y, &this_fp->coll_data.clip_flag, &this_fp->coll_data.ground_angle.x) != FALSE)
    {
        this_fp->coll_data.ground_line_id = capture_fp->coll_data.ground_line_id;

        if (dist_y >= 0.0F)
        {
            this_pos->y += dist_y;

            this_fp->ground_or_air = ground;
            this_fp->jumps_used = 0;
        }
        else
        {
            this_pos->y += dist_y * 0.5F;

            this_fp->ground_or_air = air;
            this_fp->jumps_used = 1;
        }
    }
    else
    {
        if (capture_fp->lr == RIGHT)
        {
            func_ovl2_800F4408(capture_fp->coll_data.ground_line_id, &capture_pos);
        }
        else func_ovl2_800F4428(capture_fp->coll_data.ground_line_id, &capture_pos);

        this_pos->y = this_pos->y + ((capture_pos.y - this_pos->y) * 0.5F);

        func_ovl2_800DE324(fighter_gobj);

        this_fp->ground_or_air = air;
        this_fp->jumps_used = 1;
    }
}

void func_ovl3_8014A860(GObj *fighter_gobj, GObj *capture_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp;
    Vec3f vel;

    func_ovl2_800E823C(fighter_gobj);

    if ((this_fp->item_hold != NULL) && !(ArticleGetStruct(this_fp->item_hold)->is_light_throw))
    {
        vel.x = vel.y = vel.z = 0.0F;

        func_ovl3_80172AEC(this_fp->item_hold, &vel, ARTICLE_STALE_DEFAULT);
    }
    if (this_fp->catch_gobj != NULL)
    {
        func_ovl3_8014B330(this_fp->catch_gobj);

        this_fp->catch_gobj = NULL;
    }
    else if (this_fp->capture_gobj != NULL)
    {
        func_ovl3_8014AECC(this_fp->capture_gobj, fighter_gobj);
    }
    this_fp->x192_flag_b3 = FALSE;

    this_fp->capture_gobj = capture_gobj;

    capture_fp = FighterGetStruct(capture_gobj);

    this_fp->lr = -capture_fp->lr;

    ftStatus_Update(fighter_gobj, ftStatus_Common_CapturePulled, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    this_fp->status_vars.common.capture.is_goto_pulled_wait = FALSE;

    func_ovl2_800E8098(this_fp, 0x3FU);
    func_ovl2_800E806C(this_fp, 9, 0);
    func_ovl2_800D9444(fighter_gobj);
    func_ovl3_8014A6B4(fighter_gobj);
    func_ovl3_8014A72C(fighter_gobj);
}

void func_ovl3_8014A980(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
    Vec3f *this_pos = &DObjGetStruct(fighter_gobj)->translate;
    Vec3f capture_pos;
    f32 dist_y;

    if (func_ovl2_800F3DD8(capture_fp->coll_data.ground_line_id, this_pos, &dist_y, &this_fp->coll_data.clip_flag, &this_fp->coll_data.ground_angle.x) != FALSE)
    {
        this_fp->coll_data.ground_line_id = capture_fp->coll_data.ground_line_id;

        this_pos->y += dist_y;

        this_fp->ground_or_air = ground;
        this_fp->jumps_used = 0;
    }
    else
    {
        if (capture_fp->lr == RIGHT)
        {
            func_ovl2_800F4408(capture_fp->coll_data.ground_line_id, &capture_pos);
        }
        else func_ovl2_800F4428(capture_fp->coll_data.ground_line_id, &capture_pos);

        this_pos->y = capture_pos.y;

        func_ovl2_800DE324(fighter_gobj);

        this_fp->ground_or_air = air;
        this_fp->jumps_used = 1;
    }
}

void func_ovl3_8014AA58(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp = FighterGetStruct(this_fp->capture_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CaptureWait, 0.0F, 1.0F, 0xA0U);

    if ((capture_fp->ft_kind == Ft_Kind_Yoshi) || (capture_fp->ft_kind == Ft_Kind_PolyYoshi))
    {
        this_fp->is_invisible = TRUE;

        func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Intangible);
    }
    func_ovl2_800E8098(this_fp, 0x3FU);
}