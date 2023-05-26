#include "fighter.h"
#include "article.h"

extern intptr_t ftCaptain_CaptureCaptain_Offset_Add; // 0x00000000
extern void *D_ovl2_80131034;
Vec3f Fighter_CaptureCaptain_Offset = { 0.0F, 0.0F, 0.0F };

void func_ovl3_8014D0F0(GObj *fighter_gobj, GObj *capture_gobj, Vec3f *pos)
{
    Vec3f offset = Fighter_CaptureCaptain_Offset;
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
    Vec2h *offset_add = (Vec2h*) ((uintptr_t)D_ovl2_80131034 + (intptr_t)&ftCaptain_CaptureCaptain_Offset_Add);
    s32 unused;

    pos->x = 0.0F;
    pos->y = 0.0F;
    pos->z = 0.0F;

    func_ovl2_800EDF24(this_fp->joint[29], pos);
    func_ovl2_800EDF24(capture_fp->joint[0], &offset);

    offset.x += (offset_add[capture_fp->ft_kind].x * this_fp->lr);
    offset.y += offset_add[capture_fp->ft_kind].y;

    vec3f_sub_from(pos, &offset);
}

void func_ovl3_8014D200(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f offset;

    if (fp->status_vars.common.capturecaptain.capture_flag & FTCOMMON_CAPTURECAPTAIN_MASK_THROW)
    {
        func_ovl3_8014D3BC(fighter_gobj);
    }
    else if (!(fp->status_vars.common.capturecaptain.capture_flag & FTCOMMON_CAPTURECAPTAIN_MASK_NOUPDATE))
    {
        func_ovl3_8014D0F0(fp->capture_gobj, fighter_gobj, &offset);

        if (vec3f_mag(&offset) > 180.0F)
        {
            vec3f_normalize(&offset);
            vec3f_scale(&offset, 180.0F);
        }
        vec3f_add_to(&DObjGetStruct(fighter_gobj)->translate, &offset);
    }
}

void func_ovl3_8014D2A0(GObj *fighter_gobj, GObj *capture_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp;

    ftCommon_ProcDamageStopVoice(fighter_gobj);

    if ((this_fp->item_hold != NULL) && !(ArticleGetStruct(this_fp->item_hold)->is_light_throw))
    {
        Vec3f vel;

        vel.x = vel.y = vel.z = 0.0F;

        func_ovl3_80172AEC(this_fp->item_hold, &vel, ARTICLE_STALE_DEFAULT);
    }
    if (this_fp->catch_gobj != NULL)
    {
        func_ovl3_8014B330(this_fp->catch_gobj);

        this_fp->catch_gobj = NULL;
    }
    this_fp->capture_gobj = capture_gobj;

    capture_fp = FighterGetStruct(capture_gobj);

    this_fp->lr = -capture_fp->lr;

    this_fp->status_vars.common.capturecaptain.capture_flag = 0;

    if (this_fp->ground_or_air != air)
    {
        this_fp->status_vars.common.capturecaptain.capture_flag |= FTCOMMON_CAPTURECAPTAIN_MASK_NOUPDATE;

        this_fp->x192_flag_b3 = TRUE;
    }
    else this_fp->x192_flag_b3 = FALSE;

    ftMapCollide_SetAir(this_fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CaptureCaptain, FTCOMMON_CAPTURECAPTAIN_FRAME_BEGIN, FTCOMMON_CAPTURECAPTAIN_ANIM_SPEED, 0U);
    ftCommon_SetCaptureFlags(this_fp, 0x3FU);
    ftAnim_Update(fighter_gobj);
    func_ovl2_800D9444(fighter_gobj);
    func_ovl3_8014D200(fighter_gobj);
}

void func_ovl3_8014D3BC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8014AFD0(fighter_gobj, fp->lr, 0, 0);
    ftCommon_SetCaptureFlags(fp, 0U);
}
