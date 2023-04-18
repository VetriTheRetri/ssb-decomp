#include "fighter.h"

#define ftStatus_CheckInterruptSquat(fighter_gobj) \
(                                                  \
    (func_ovl3_80151098(fighter_gobj) != FALSE) || \
    (func_ovl3_80151160(fighter_gobj) != FALSE) || \
    (func_ovl3_801511E0(fighter_gobj) != FALSE) || \
    (func_ovl3_80149CE0(fighter_gobj) != FALSE) || \
    (func_ovl3_80150470(fighter_gobj) != FALSE) || \
    (func_ovl3_8015070C(fighter_gobj) != FALSE) || \
    (func_ovl3_80150838(fighter_gobj) != FALSE) || \
    (func_ovl3_8014F8C0(fighter_gobj) != FALSE) || \
    (func_ovl3_8014FB1C(fighter_gobj) != FALSE) || \
    (func_ovl3_8014FD70(fighter_gobj) != FALSE) || \
    (func_ovl3_8014EC78(fighter_gobj) != FALSE) || \
    (func_ovl3_80148D0C(fighter_gobj) != FALSE) || \
    (func_ovl3_8014E764(fighter_gobj) != FALSE) || \
    (func_ovl3_8013F4D0(fighter_gobj) != FALSE) || \
    (func_ovl3_80141F0C(fighter_gobj) != FALSE) || \
    (func_ovl3_80142258(fighter_gobj) != FALSE)    \
)                                                  \

#define ftStatus_CheckInterruptSquatWait(fighter_gobj) \
(                                                      \
    (func_ovl3_80151098(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80151160(fighter_gobj) != FALSE) ||     \
    (func_ovl3_801511E0(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80149CE0(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80150470(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8015070C(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80150884(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8014F8C0(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8014FB1C(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8014FD70(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8014EC78(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80148D0C(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8014E764(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8013F4D0(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8013ED64(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80141EA4(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80142258(fighter_gobj) != FALSE)        \
)                                                      \

bool32 func_ovl3_80142E70(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.squat.is_allow_pass != FALSE)
    {
        if (fp->status_vars.common.squat.pass_wait != 0)
        {
            fp->status_vars.common.squat.pass_wait--;

            if (fp->status_vars.common.squat.pass_wait == 0)
            {
                func_ovl3_80141DA0(fighter_gobj, ftStatus_Common_Pass, 1.0F, 0);

                return TRUE;
            }
        }
    }
    if (fp->status_vars.common.squat.unk_0x8 != 0)
    {
        fp->status_vars.common.squat.unk_0x8--;
    }

    return FALSE;
}

void func_ovl3_80142ED8(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8014329C);
}

void func_ovl3_80142EFC(GObj *fighter_gobj)
{
    if (!ftStatus_CheckInterruptSquat(fighter_gobj))
    {
        func_ovl3_80142E70(fighter_gobj);
    }
}

void func_ovl3_80143024(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Squat, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->x192_flag_b0 = TRUE;

    fp->status_vars.common.squat.is_allow_pass = FALSE;
    fp->status_vars.common.squat.pass_wait = 0;

    if ((fp->input.stick_range.y <= FTCOMMON_SQUAT_STICK_RANGE_MIN) && (fp->hold_stick_y < FTCOMMON_SQUAT_BUFFER_FRAMES_MAX))
    {
        fp->status_vars.common.squat.unk_0x8 = 3;
    }
    else fp->status_vars.common.squat.unk_0x8 = 0;
}

void func_ovl3_801430A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Squat, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->x192_flag_b0 = TRUE;

    fp->status_vars.common.squat.is_allow_pass = TRUE;
    fp->status_vars.common.squat.pass_wait = FTCOMMON_SQUAT_PASS_WAIT;
    fp->status_vars.common.squat.unk_0x8 = 3;
}

bool32 func_ovl3_8014310C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.stick_range.y <= (FTCOMMON_SQUAT_STICK_RANGE_MIN - 2))
    {
        func_ovl3_80143024(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8014314C(GObj *fighter_gobj)
{
    return;
}

void func_ovl3_8014329C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_SquatWait, 0.0F, 1.0F, 0U);

    fp->x192_flag_b0 = TRUE;

    func_ovl2_800E7F7C(fighter_gobj, 120);
}

void func_ovl3_801432F0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_SquatWait, 0.0F, 1.0F, 0U);

    fp->x192_flag_b0 = TRUE;

    func_ovl2_800E7F7C(fighter_gobj, 120);

    fp->status_vars.common.squat.is_allow_pass = FALSE;
    fp->status_vars.common.squat.unk_0x8 = 0;
    fp->status_vars.common.squat.pass_wait = 0;
}

bool32 func_ovl3_8014310C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.stick_range.y <= (FTCOMMON_SQUAT_STICK_RANGE_MIN - 2))
    {
        func_ovl3_801432F0(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80143394(GObj *fighter_gobj)
{
    if (!ftStatus_CheckInterruptSquatWait(fighter_gobj))
    {
        func_ovl3_8013E648(fighter_gobj);
    }
}

void func_ovl3_801434CC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_SquatRv, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->x192_flag_b0 = TRUE;
}

bool32 func_ovl3_8014351C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.stick_range.y >= (FTCOMMON_SQUAT_STICK_RANGE_MIN + 4))
    {
        func_ovl3_801434CC(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}