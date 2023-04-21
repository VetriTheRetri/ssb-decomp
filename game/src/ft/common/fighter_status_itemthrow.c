#include "fighter.h"
#include "ftdonkey.h"
#include "article.h"

void func_ovl3_801462A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag3 != 0)
    {
        fp->status_vars.common.itemthrow.turn_rotate_step =
        fp->status_vars.common.itemthrow.turn_frames = fp->command_vars.flags.flag3;

        fp->status_vars.common.itemthrow.turn_invert_lr_wait = fp->command_vars.flags.flag3 / 2;

        fp->command_vars.flags.flag3 = 0;
    }

    if (fp->status_vars.common.itemthrow.turn_frames != 0)
    {
        fp->status_vars.common.itemthrow.turn_frames--;

        if (fp->status_vars.common.itemthrow.turn_invert_lr_wait != 0)
        {
            fp->status_vars.common.itemthrow.turn_invert_lr_wait--;

            if (fp->status_vars.common.itemthrow.turn_invert_lr_wait == 0)
            {
                fp->lr = -fp->lr;
            }
        }
        fp->joint[0]->rotate.y -= F_DEG_TO_RAD(180.0F / fp->status_vars.common.itemthrow.turn_rotate_step);

        func_ovl2_800EB528(fp->joint[0]);
    }
}

extern FighterItemThrow Fighter_ItemThrow_Desc[ftStatus_Common_SpecialStart];

void func_ovl3_8014634C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 vel_base;
    FighterItemThrow *item_throw_desc;
    f32 stale;
    Vec3f vel;
    s32 status_id;
    s32 angle;

    func_ovl3_801462A0(fighter_gobj);

    if (fp->command_vars.flags.flag2 != 0)
    {
        fp->status_vars.common.itemthrow.throw_vel = fp->command_vars.item_throw.vel * 0.01F;
        fp->status_vars.common.itemthrow.throw_angle = fp->command_vars.item_throw.angle;

        fp->command_vars.flags.flag2 = 0;
    }
    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->status_vars.common.itemthrow.throw_damage = fp->command_vars.item_throw.damage * 0.01F;

        fp->command_vars.flags.flag1 = 0;
    }
    if ((fp->item_hold != NULL) && (fp->command_vars.item_throw.is_throw_item != FALSE))
    {
        if ((fp->ft_kind == Ft_Kind_Donkey || fp->ft_kind == Ft_Kind_PolyDonkey || fp->ft_kind == Ft_Kind_GiantDonkey) &&
        (fp->status_info.status_id >= ftStatus_Donkey_HeavyThrowF && fp->status_info.status_id <= ftStatus_Donkey_HeavyThrowB4))
        {
            status_id = fp->status_info.status_id - ftStatus_Common_HeavyThrowF4;
        }
        else status_id = fp->status_info.status_id;

        vel_base = Fighter_ItemThrow_Desc[status_id - ftStatus_Common_LightThrowDrop].velocity * fp->status_vars.common.itemthrow.throw_vel * fp->attributes->item_throw_vel * 0.01F;

        if (fp->status_vars.common.itemthrow.throw_angle == 361)
        {
            angle = Fighter_ItemThrow_Desc[status_id - ftStatus_Common_LightThrowDrop].angle;
        }
        else angle = fp->status_vars.common.itemthrow.throw_angle;

        stale = Fighter_ItemThrow_Desc[status_id - ftStatus_Common_LightThrowDrop].damage * 0.01F * fp->status_vars.common.itemthrow.throw_damage * fp->attributes->item_throw_mul * 0.01F;

        vel.x = cosf(F_DEG_TO_RAD(angle)) * vel_base * fp->lr;
        vel.y = __sinf(F_DEG_TO_RAD(angle)) * vel_base;
        vel.z = 0.0F;

        if (status_id == ftStatus_Common_LightThrowDrop)
        {
            func_ovl3_80172AEC(fp->item_hold, &vel, stale);
        }
        else func_ovl3_80172B78(fp->item_hold, &vel, stale, Fighter_ItemThrow_Desc[status_id - ftStatus_Common_LightThrowDrop].is_smash_throw);

        fp->command_vars.flags.flag0 = 0;
    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_80146618(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        jtgt_ovl2_800D90E0(fighter_gobj);
    }
    else func_ovl2_800D8BB4(fighter_gobj);
}

void func_ovl3_8014665C(Fighter_Struct *fp)
{
    fp->command_vars.flags.flag0 = 0;
    fp->command_vars.flags.flag1 = 0;
    fp->command_vars.flags.flag2 = 0;
    fp->command_vars.flags.flag3 = 0;
}

void func_ovl3_80146670(Fighter_Struct *fp)
{
    fp->status_vars.common.itemthrow.turn_frames = 0;
    fp->status_vars.common.itemthrow.throw_angle = 361;
    fp->status_vars.common.itemthrow.throw_vel = 1.0F;
    fp->status_vars.common.itemthrow.throw_damage = 1.0F;
}

void func_ovl3_80146690(GObj *fighter_gobj, s32 status_id)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8014665C(fp);

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    func_ovl3_80146670(fp);
    func_ovl3_801462A0(fighter_gobj);
}

void func_ovl3_801466EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if ((ABS(fp->input.stick_range.x) >= FTCOMMON_LIGHTTHROW4_STICK_RANGE_X_MIN) && (fp->tap_stick_x < FTCOMMON_LIGHTTHROW4_F_OR_B_BUFFER_FRAMES_MAX))
    {
        status_id = ((fp->input.stick_range.x * fp->lr) >= 0) ? ftStatus_Common_LightThrowF4 : ftStatus_Common_LightThrowB4;
    }
    else if ((fp->input.stick_range.y >= FTCOMMON_LIGHTTHROW4_STICK_RANGE_Y_MIN) && (fp->tap_stick_y < (FTCOMMON_LIGHTTHROW4_HI_OR_LW_BUFFER_FRAMES_MAX + fp->attributes->kneebend_frames)))
    {
        status_id = ftStatus_Common_LightThrowHi4;
    }
    else if ((fp->input.stick_range.y <= -FTCOMMON_LIGHTTHROW4_STICK_RANGE_Y_MIN) && (fp->tap_stick_y < FTCOMMON_LIGHTTHROW4_HI_OR_LW_BUFFER_FRAMES_MAX))
    {
        status_id = ftStatus_Common_LightThrowLw4;
    }
    else if ((ABS(fp->input.stick_range.x) >= FTCOMMON_LIGHTTHROW_STICK_RANGE_XY_MIN) && (((func_ovl2_800E8000(fp) < 0.0F) ? -func_ovl2_800E8000(fp) : func_ovl2_800E8000(fp)) <= FTCOMMON_LIGHTTHROW_HI_OR_LW_ANGLE))
    {
        status_id = ((fp->input.stick_range.x * fp->lr) >= 0) ? ftStatus_Common_LightThrowF : ftStatus_Common_LightThrowB;
    }
    else if ((fp->input.stick_range.y >= FTCOMMON_LIGHTTHROW_STICK_RANGE_XY_MIN) && (func_ovl2_800E8000(fp) > FTCOMMON_LIGHTTHROW_HI_OR_LW_ANGLE))
    {
        status_id = ftStatus_Common_LightThrowHi;
    }
    else if ((fp->input.stick_range.y <= -FTCOMMON_LIGHTTHROW_STICK_RANGE_XY_MIN) && (func_ovl2_800E8000(fp) < -FTCOMMON_LIGHTTHROW_HI_OR_LW_ANGLE))
    {
        status_id = ftStatus_Common_LightThrowLw; 
    }
    else status_id = (ArticleGetStruct(fp->item_hold)->unk_0x10 == 3) ? ftStatus_Common_LightThrowF : ftStatus_Common_LightThrowDrop; // No NULL check

    func_ovl3_80146690(fighter_gobj, status_id);
}

void func_ovl3_80146930(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if ((ABS(fp->input.stick_range.x) >= FTCOMMON_HEAVYTHROW4_STICK_RANGE_X_MIN) && (fp->tap_stick_x < FTCOMMON_HEAVYTHROW4_F_OR_B_BUFFER_FRAMES_MAX))
    {
        status_id = ((fp->input.stick_range.x * fp->lr) >= 0) ? ftStatus_Common_HeavyThrowF4 : ftStatus_Common_HeavyThrowB4;
    }
    else if (((ABS(fp->input.stick_range.x) >= 0x14) && ((func_ovl2_800E8000(fp) < 0.0F) ? -func_ovl2_800E8000(fp) : func_ovl2_800E8000(fp)) <= FTCOMMON_HEAVYTHROW_HI_OR_LW_ANGLE))
    {
        status_id = ((fp->input.stick_range.x * fp->lr) >= 0) ? ftStatus_Common_HeavyThrowF : ftStatus_Common_HeavyThrowB;
    }
    else status_id = ftStatus_Common_HeavyThrowF;

    if ((fp->ft_kind == Ft_Kind_Donkey) || (fp->ft_kind == Ft_Kind_PolyDonkey) || (fp->ft_kind == Ft_Kind_GiantDonkey))
    {
        status_id += ftStatus_Common_HeavyThrowF4;
    }
    func_ovl3_80146690(fighter_gobj, status_id);

    fp->cb_take_damage = func_ovl3_80145D28;
}

bool32 func_ovl3_80146A8C(Fighter_Struct *fp)
{
    if (fp->item_hold != NULL)
    {
        if (fp->input.button_press & fp->input.button_mask_a)
        {
            if ((fp->input.button_hold & fp->input.button_mask_z) || (ArticleGetStruct(fp->item_hold)->unk_0x10 == 3))
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

bool32 func_ovl3_80146AE8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->item_hold != NULL) && (fp->input.button_press & fp->input.button_mask_a))
    {
        if (fp->status_vars.common.itemthrow.get_heavy_wait != 0)
        {
            func_ovl3_80146690(fighter_gobj, ftStatus_Common_HeavyGet);

            return TRUE;
        }
        else func_ovl3_801466EC(fighter_gobj);

        return TRUE;
    }
    if (fp->status_vars.common.itemthrow.get_heavy_wait != 0)
    {
        fp->status_vars.common.itemthrow.get_heavy_wait--;
    }
    return FALSE;
}

bool32 func_ovl3_80146B64(GObj *fighter_gobj) // Interrupt item throw from roll
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if ((func_ovl3_80146A8C(fp) != FALSE) && (fp->status_vars.common.itemthrow.turn_rotate_step != 0)) // Might be a different var? Not sure, this is just LightThrow again
    {
        if (fp->status_info.status_id == ftStatus_Common_EscapeF)
        {
            status_id = ftStatus_Common_LightThrowF4;
        }
        else status_id = ftStatus_Common_LightThrowB4;

        func_ovl3_80146690(fighter_gobj, status_id);

        return TRUE;
    }
    if (fp->status_vars.common.itemthrow.turn_rotate_step != 0)
    {
        fp->status_vars.common.itemthrow.turn_rotate_step--;
    }
    return FALSE;
}

bool32 func_ovl3_80146BE0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->item_hold != NULL) && (fp->input.button_press & (fp->input.button_mask_a | fp->input.button_mask_b)))
    {
        func_ovl3_80146930(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}