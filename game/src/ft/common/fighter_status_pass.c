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

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, status_id, frame_begin, 1.0F, flags);
    func_ovl2_800D8EB8(fp);

    fp->phys_info.vel_air.y = 0.0F;

    fp->coll_data.ignore_line_id = fp->coll_data.ground_line_id;

    fp->tap_stick_y = U8_MAX - 1;
}

void func_ovl3_80141E18(GObj *fighter_gobj)
{
    func_ovl3_801430A8(fighter_gobj);
}

void func_ovl3_80141E38(GObj *fighter_gobj)
{
    func_ovl3_80141DA0(fighter_gobj, ftStatus_Common_GuardPass, 1.0F, 0U);
}

bool32 func_ovl3_80141E60(Fighter_Struct *fp)
{
    if ((fp->input.stick_range.y <= FTCOMMON_PASS_STICK_RANGE_MIN) && (fp->tap_stick_y < FTCOMMON_PASS_BUFFER_FRAMES_MAX) && (fp->coll_data.ground_flags & 0x4000))
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80141EA4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800F3794(fighter_gobj) != FALSE)
    {
        return func_ovl3_80147E7C(fighter_gobj);
    }
    else if (func_ovl3_80141E60(fp) != FALSE)
    {
        func_ovl3_80141E18(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80141F0C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800F3794(fighter_gobj) != FALSE)
    {
        return func_ovl3_80147E7C(fighter_gobj);
    }
    if (fp->status_vars.common.squat.is_allow_pass == FALSE)
    {
        if (func_ovl3_80141E60(fp) != FALSE)
        {
            fp->status_vars.common.squat.is_allow_pass = TRUE;
            fp->status_vars.common.squat.pass_wait = FTCOMMON_SQUAT_PASS_WAIT;

            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl3_80141F8C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl3_80141E60(fp) != FALSE) && (fp->input.button_hold & fp->input.button_mask_z))
    {
        func_ovl3_80141E38(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}