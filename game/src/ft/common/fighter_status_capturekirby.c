#include "ftkirby.h"
#include "article.h"

void func_ovl3_8014B700(GObj *fighter_gobj, Vec3f *dist)
{
    f32 mag = vec3f_mag(dist);

    if (mag < FTCOMMON_CAPTUREKIRBY_MAGNITUDE_MAX)
    {
        DObj *joint = DObjGetStruct(fighter_gobj)->next;

        mag /= FTCOMMON_CAPTUREKIRBY_MAGNITUDE_MAX;
        mag *= FTCOMMON_CAPTUREKIRBY_MAGNITUDE_MUL;

        joint->scale.x = joint->scale.y = joint->scale.z = FTCOMMON_CAPTUREKIRBY_MAGNITUDE_ADD + mag;
    }
}

void func_ovl3_8014B774(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Vec3f dist;
    Fighter_Struct *capture_fp = FighterGetStruct(this_fp->capture_gobj);

    dist.x = capture_fp->status_vars.kirby.specialn.dist.x;
    dist.y = capture_fp->status_vars.kirby.specialn.dist.y;
    dist.z = 0;

    func_ovl3_8014B700(fighter_gobj, &dist);

    if (ABSF(dist.x) > FTCOMMON_CAPTUREKIRBY_DIST_X_MIN)
    {
        dist.x = ((dist.x < 0.0F) ? -1 : 1) * FTCOMMON_CAPTUREKIRBY_DIST_X_MIN;
    }
    if (ABSF(dist.y) > FTCOMMON_CAPTUREKIRBY_DIST_Y_MIN)
    {
        dist.y = ((dist.y < 0.0F) ? -1 : 1) * FTCOMMON_CAPTUREKIRBY_DIST_Y_MIN;
    }
    capture_fp->status_vars.kirby.specialn.dist.x -= dist.x;
    capture_fp->status_vars.kirby.specialn.dist.y -= dist.y;

    func_ovl3_80161DA8(capture_fp, this_fp->capture_gobj, &dist);

    DObjGetStruct(fighter_gobj)->translate.x = capture_fp->status_vars.kirby.specialn.dist.x + dist.x;
    DObjGetStruct(fighter_gobj)->translate.y = capture_fp->status_vars.kirby.specialn.dist.y + dist.y;
    DObjGetStruct(fighter_gobj)->translate.z = DObjGetStruct(this_fp->capture_gobj)->translate.z;
}

void func_ovl3_8014B914(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8014B774(fighter_gobj);

    if ((fp->status_info.status_id == ftStatus_Common_CaptureKirby) && (fp->status_vars.common.capturekirby.is_goto_capturewait != FALSE))
    {
        func_ovl3_8014BDB4(fighter_gobj);
    }
}

void func_ovl3_8014B914(GObj *);                        /* extern */

void func_ovl3_8014B968(GObj *fighter_gobj, GObj *capture_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp;

    func_ovl2_800E823C(fighter_gobj);

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
    else if (this_fp->capture_gobj != NULL)
    {
        func_ovl3_8014AECC(this_fp->capture_gobj, fighter_gobj);
    }
    this_fp->x192_flag_b3 = FALSE;

    this_fp->capture_gobj = capture_gobj;

    capture_fp = FighterGetStruct(capture_gobj);

    this_fp->lr = -capture_fp->lr;

    ftMapCollide_SetAir(this_fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CaptureKirby, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl2_800E806C(this_fp, 7, 0);

    this_fp->status_vars.common.capturekirby.is_goto_capturewait = FALSE;
    this_fp->status_vars.common.capturekirby.lr = CENTER;
    this_fp->status_vars.common.capturekirby.is_kirby = 0;

    func_ovl2_800E8098(this_fp, 0x3FU);
    func_ovl2_800D9444(fighter_gobj);
    func_ovl3_8014B914(fighter_gobj);
    func_ovl2_800DE348(fighter_gobj);
}

void func_ovl3_8014BA98(Fighter_Struct *this_fp, Fighter_Struct *capture_fp)
{
    bool32 is_wiggle = FALSE;

    if ((capture_fp->status_info.status_id == ftStatus_Kirby_SpecialAirNWait) || (capture_fp->status_info.status_id == ftStatus_Kirby_SpecialNWait))
    {
        if ((this_fp->input.pl.stick_range.y >= FTCOMMON_CAPTUREKIRBY_WIGGLE_STICK_RANGE_MIN) && (this_fp->tap_stick_y < FTCOMMON_CAPTUREKIRBY_WIGGLE_BUFFER_FRAMES_MAX))
        {
            this_fp->tap_stick_y = U8_MAX - 1;
            is_wiggle = TRUE;

            if (capture_fp->ground_or_air == ground)
            {
                func_ovl3_80162D80(capture_fp->fighter_gobj);

                is_wiggle = TRUE;

                capture_fp->phys_info.vel_air.y = FTCOMMON_CAPTUREKIRBY_WIGGLE_VEL_XY;
            }
        }
        else if ((this_fp->input.pl.stick_range.y <= -FTCOMMON_CAPTUREKIRBY_WIGGLE_STICK_RANGE_MIN) && (this_fp->tap_stick_y < FTCOMMON_CAPTUREKIRBY_WIGGLE_BUFFER_FRAMES_MAX) && (this_fp->coll_data.ground_flags & 0x4000))
        {
            this_fp->tap_stick_y = U8_MAX - 1;
            is_wiggle = TRUE;

            if (capture_fp->ground_or_air == ground)
            {
                func_ovl3_80162D80(capture_fp->fighter_gobj);

                is_wiggle = TRUE;

                capture_fp->coll_data.ignore_line_id = capture_fp->coll_data.ground_line_id;
                capture_fp->phys_info.vel_air.y = -FTCOMMON_CAPTUREKIRBY_WIGGLE_VEL_XY;
            }
        }
        if ((ABS(this_fp->input.pl.stick_range.x) >= (FTCOMMON_CAPTUREKIRBY_WIGGLE_STICK_RANGE_MIN + 3)) && (this_fp->tap_stick_x < (FTCOMMON_CAPTUREKIRBY_WIGGLE_BUFFER_FRAMES_MAX * 2)))
        {
            this_fp->tap_stick_x = U8_MAX - 1;
            is_wiggle = TRUE;

            if (capture_fp->ground_or_air == FALSE)
            {
                capture_fp->phys_info.vel_ground.x = (((this_fp->input.pl.stick_range.x < 0) ? -1 : 1) * capture_fp->lr) * FTCOMMON_CAPTUREKIRBY_WIGGLE_VEL_XY;
            }
            else capture_fp->phys_info.vel_air.x = ((this_fp->input.pl.stick_range.x < 0) ? -1 : 1) * FTCOMMON_CAPTUREKIRBY_WIGGLE_VEL_XY;
        }
        if (is_wiggle != FALSE)
        {
            if (capture_fp->x9CC != NULL)
            {
                func_ovl0_800C87F4(capture_fp->joint[0]->next, capture_fp->x9CC, 0.0F);
            }
        }
    }
}

ftThrowReleaseDesc Fighter_CaptureKirby_Catch_Release   = { 361, 100, 90, 0 };
ftThrowReleaseDesc Fighter_CaptureKirby_Capture_Release = {  80, 100, 60, 0 };

void func_ovl3_8014BD04(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;

    if (capture_gobj != NULL)
    {
        Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
        s32 breakout_wait;

        func_ovl3_8014BA98(this_fp, capture_fp);

        breakout_wait = this_fp->breakout_wait;

        func_ovl3_8014E400(this_fp);

        this_fp->breakout_wait -= ((breakout_wait - this_fp->breakout_wait) * 5);

        this_fp->breakout_wait--;

        if (this_fp->breakout_wait <= 0)
        {
            func_ovl3_8014E1D0(capture_gobj, &Fighter_CaptureKirby_Catch_Release);
            func_ovl3_8014E2A8(fighter_gobj, &Fighter_CaptureKirby_Capture_Release);

            capture_fp->catch_gobj = NULL;
            this_fp->capture_gobj = NULL;
        }
    }
}

void func_ovl3_8014BDB4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CaptureWaitKirby, 0.0F, 1.0F, 0xA0U);
    func_ovl2_800E8098(fp, 0x3FU);

    fp->is_invisible = TRUE;

    func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Intangible);
    func_ovl3_8014E3EC(fp, 0x1F4);
}

void func_ovl3_8014BE24(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Common_Fall, 0.0F, 1.0F, 0x1000U);
}

void func_ovl3_8014BE54(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Fall, 0.0F, 1.0F, 0U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_8014BE90(GObj *fighter_gobj, f32 arg1, f32 arg2)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fp->is_statupdate_stop_gfx))
    {
        if (func_ovl2_80103CF8(fighter_gobj) != NULL)
        {
            fp->is_statupdate_stop_gfx = TRUE;
        }
    }
}

void func_ovl3_8014BEE0(GObj *fighter_gobj)
{
    func_ovl3_8014BE90(fighter_gobj, 360.0F, 210.0F);
}

void func_ovl3_8014BF04(GObj *fighter_gobj, f32 decelerate)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (fp->command_vars.flags.flag2 != 3))
    {
        f32 sqrt_vel = sqrtf(SQUARE(fp->phys_info.vel_air.x) + SQUARE(fp->phys_info.vel_air.y));

        if (decelerate < sqrt_vel)
        {
            fp->phys_info.vel_air.x = (fp->phys_info.vel_air.x * (sqrt_vel - decelerate)) / sqrt_vel;
            fp->phys_info.vel_air.y = (fp->phys_info.vel_air.y * (sqrt_vel - decelerate)) / sqrt_vel;

            if (fp->phys_info.vel_air.y < 0)
            {
                fp->lr = LEFT;
            }
            else fp->lr = RIGHT;
        }
        else fp->phys_info.vel_air.x = fp->phys_info.vel_air.y = 0;

        fp->command_vars.flags.flag1--;

        func_ovl3_8014E400(fp);

        if (fp->breakout_wait <= 0)
        {
            fp->command_vars.flags.flag1 = 0;
        }
    }
    else
    {
        if (fp->command_vars.flags.flag2 == 1)
        {
            if (((fp->ft_kind == Ft_Kind_Kirby) || (fp->ft_kind == Ft_Kind_PolyKirby)) && (fp->status_vars.common.capturekirby.is_kirby != FALSE))
            {
                func_ovl3_80161EB4(fp);

                fp->fighter_vars.kirby.copy_id = Ft_Kind_Kirby;

                func_ovl2_800E8EAC(fighter_gobj, 6, 0);
                func_ovl2_800E8ECC(fighter_gobj);
            }
            fp->is_invisible = FALSE;

            func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Normal);
            func_ovl2_800E9C3C(fighter_gobj);
            func_ovl3_8014BE24(fighter_gobj);

            if (func_ovl2_80102070(&DObjGetStruct(fighter_gobj)->translate, (-fp->phys_info.vel_air.x < 0.0F) ? LEFT : RIGHT) != NULL)
            {
                fp->is_statupdate_stop_gfx = TRUE;
            }
        }
        else
        {
            if (fp->command_vars.flags.flag2 == 2)
            {
                fp->command_vars.flags.flag1 = 4;
                fp->command_vars.flags.flag2 = 3;

                fp->phys_info.vel_air.y = FTCOMMON_THROWNKIRBYSTAR_RELEASE_VEL_Y;

                if (fp->status_vars.common.capturekirby.lr != CENTER)
                {
                    fp->phys_info.vel_air.x = fp->status_vars.common.capturekirby.lr * FTCOMMON_THROWNKIRBYSTAR_RELEASE_VEL_X;
                }
                else fp->phys_info.vel_air.x = ((fp->phys_info.vel_air.x < 0.0F) ? LEFT : RIGHT) * FTCOMMON_THROWNKIRBYSTAR_RELEASE_VEL_X;

                func_ovl2_800E9C3C(fighter_gobj);

                if (func_ovl2_80102070(&DObjGetStruct(fighter_gobj)->translate, (-fp->phys_info.vel_air.x < 0.0F) ? LEFT : RIGHT) != NULL)
                {
                    fp->is_statupdate_stop_gfx = TRUE;
                }
                fp->is_invisible = FALSE;

                func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Normal);
            }
            if (fp->command_vars.flags.flag2 == 3)
            {
                DObj *joint = DObjGetStruct(fighter_gobj)->next;
                f32 scale = (4.0F - fp->command_vars.flags.flag1) * 0.25F;

                scale *= FTCOMMON_CAPTUREKIRBY_MAGNITUDE_MUL;

                joint->scale.x = joint->scale.y = joint->scale.z = FTCOMMON_CAPTUREKIRBY_MAGNITUDE_ADD + scale;

                if (fp->command_vars.flags.flag1-- <= 0)
                {
                    func_ovl3_8014BE24(fighter_gobj);
                }
            }
        }
    }
}

void func_ovl3_8014C260(GObj *fighter_gobj)
{
    func_ovl3_8014BF04(fighter_gobj, FTCOMMON_THROWNKIRBYSTAR_DECELERATE);
}

void func_ovl3_8014C280(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f *angle;
    Vec3f pos = DObjGetStruct(fighter_gobj)->translate;
    Vec3f vel_bak;

    angle = NULL;

    if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        angle = &fp->coll_data.ground_angle;
    }
    else if (fp->coll_data.coll_mask & MPCOLL_MASK_CEIL)
    {
        angle = &fp->coll_data.ceil_angle;

        pos.y += fp->coll_data.object_coll.top;
    }
    else if (fp->coll_data.coll_mask & MPCOLL_MASK_RWALL)
    {
        angle = &fp->coll_data.rwall_angle;

        pos.x += fp->coll_data.object_coll.width;
        pos.y += fp->coll_data.object_coll.center;
    }
    else if (fp->coll_data.coll_mask & MPCOLL_MASK_LWALL)
    {
        angle = &fp->coll_data.lwall_angle;

        pos.x -= fp->coll_data.object_coll.width;
        pos.y += fp->coll_data.object_coll.center;
    }
    if (angle != NULL)
    {
        vel_bak = fp->phys_info.vel_air;

        func_ovl0_800C7B08(&fp->phys_info.vel_air, angle);

        if (((fp->phys_info.vel_air.x * vel_bak.x) + (vel_bak.y * fp->phys_info.vel_air.y)) < 0.0F)
        {
            fp->status_vars.common.capturekirby.lr = (angle->x < 0) ? LEFT : RIGHT;

            fp->command_vars.flags.flag1 = 0;
        }
        func_ovl2_801008F4(2);
        func_ovl2_800FFD58(&pos, 4, atan2f(-angle->x, angle->y));
    }
}

void func_ovl3_8014C424(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;

    if (capture_gobj != NULL)
    {
        Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);

        func_ovl3_8014ADB0(fighter_gobj);
        func_ovl2_800E8098(this_fp, 0U);
        func_ovl2_800E8098(capture_fp, 0U);
        func_ovl2_800EAA2C(this_fp, capture_fp->port_id, 1, capture_fp->ft_kind, capture_fp->flags_lw.halfword, capture_fp->unk_0x290.halfword);

        this_fp->capture_gobj = NULL;
        this_fp->catch_gobj = NULL;
        capture_fp->catch_gobj = NULL;
        capture_fp->capture_gobj = NULL;

        this_fp->status_vars.common.capturekirby.lr = (this_fp->phys_info.vel_air.x < 0.0F) ? LEFT : RIGHT;
    }
}

void func_ovl3_8014C4D8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag1 = 30;
    fp->command_vars.flags.flag2 = 2;

    func_ovl3_8014C424(fighter_gobj);
}

extern intptr_t ftKirby_LoadedFiles_SpecialNData;
extern void *D_ovl2_80131074;

void func_ovl3_8014C508(GObj *fighter_gobj)
{
    s32 i;
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftKirbyCopyData *copy_data = (ftKirbyCopyData*) ((uintptr_t)D_ovl2_80131074 + (intptr_t)&ftKirby_LoadedFiles_SpecialNData);

    if (fp->ground_or_air == ground)
    {
        ftMapCollide_SetAir(fp);
    }
    fp->proc_status = func_ovl3_8014C4D8;

    ftStatus_Update(fighter_gobj, ftStatus_Common_ThrownKirbyStar, 0.0F, 1.0F, 0x200U);
    func_ovl2_800E8098(fp, 0x3FU);

    fp->proc_hit = func_ovl3_8014BE54;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
    {
        Fighter_Hit *ft_hit = &fp->fighter_hit[i];

        if (ft_hit->update_state == gmHitCollision_UpdateState_New)
        {
            ft_hit->damage = copy_data[fp->ft_kind].star_damage;
        }
    }
    fp->is_invisible = fp->x18E_flag_b0 = TRUE;

    func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Intangible);
    func_ovl2_800E7F7C(fighter_gobj, 1);
    func_ovl3_8014E3EC(fp, 3);
}

void func_ovl3_8014C634(GObj *fighter_gobj)
{
    func_ovl3_8014BE90(fighter_gobj, -400.0F, 280.0F);
}

void func_ovl3_8014C658(GObj *fighter_gobj)
{
    func_ovl3_8014BF04(fighter_gobj, FTCOMMON_THROWNCOPYSTAR_DECELERATE);
}

void func_ovl3_8014C67C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag1 = 10;
    fp->command_vars.flags.flag2 = 1;

    func_ovl3_8014C424(fighter_gobj);
}

void func_ovl3_8014C6AC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        ftMapCollide_SetAir(fp);
    }
    fp->proc_status = func_ovl3_8014C67C;

    ftStatus_Update(fighter_gobj, ftStatus_Common_ThrownCopyStar, 0.0F, 1.0F, 0x200U);
    func_ovl2_800E8098(fp, 0x3FU);

    fp->proc_hit = func_ovl3_8014BE54;
    fp->is_invisible = fp->x18E_flag_b0 = TRUE;

    func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Intangible);
    func_ovl2_800E7F7C(fighter_gobj, 1);
}