#include "fighter.h"

void func_ovl3_8013E690(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->command_vars.flags.flag1 = 0;

        fp->status_vars.common.turn.unk_0x0 = 1;
        fp->status_vars.common.turn.unk_0x4 = 1;

        fp->lr = -fp->lr;
        fp->phys_info.vel_ground.x = -fp->phys_info.vel_ground.x;
    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_8013E1C8(fighter_gobj);
    }
}

// Dawg what
void func_ovl3_8013E700(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    bool32 unk_bool;

    if (fp->status_vars.common.turn.is_allow_turn_direction != FALSE)
    {
        fp->input.button_press |= fp->status_vars.common.turn.button_mask;
    }

    if (fp->status_vars.common.turn.is_disable_interrupts == FALSE) goto interrupt1;

    if (func_ovl3_80151098(fighter_gobj) != FALSE) return;

    if (func_ovl3_80151160(fighter_gobj) != FALSE) return;

    if (func_ovl3_801511E0(fighter_gobj) != FALSE) return;

interrupt1:
    if (func_ovl3_80149CE0(fighter_gobj) == FALSE)
    {
        if (fp->status_vars.common.turn.unk_0x14 < 256) fp->status_vars.common.turn.unk_0x14++;

        unk_bool = (fp->status_vars.common.turn.unk_0x14 < 6) ? func_ovl3_8015030C(fighter_gobj) : func_ovl3_80150470(fighter_gobj);

        if (unk_bool == FALSE)
        {
            if (fp->status_vars.common.turn.is_disable_interrupts == FALSE) goto interrupt2;

            if (func_ovl3_8015070C(fighter_gobj) != FALSE) return;

            if (func_ovl3_80150884(fighter_gobj) != FALSE) return;

            if (func_ovl3_8014F8C0(fighter_gobj) != FALSE) return;

            if (func_ovl3_8014FB1C(fighter_gobj) != FALSE) return;

            if (func_ovl3_8014FD70(fighter_gobj) != FALSE) return;

            if (func_ovl3_8014EC78(fighter_gobj) != FALSE) return;

        interrupt2:
            if (func_ovl3_80148D0C(fighter_gobj) != FALSE) return;

            if (func_ovl3_8014E764(fighter_gobj) != FALSE) return;

            if (func_ovl3_8013F4D0(fighter_gobj) != FALSE) return;

            func_ovl3_8013EDFC(fighter_gobj);

            if (fp->status_vars.common.turn.is_allow_turn_direction != FALSE)
            {
                if (fp->status_vars.common.turn.lr_dash != CENTER)
                {
                    if ((fp->input.stick_range.x * fp->status_vars.common.turn.lr_turn) >= FTCOMMON_DASH_STICK_RANGE_MIN)
                    {
                        func_ovl3_8013ED00(fighter_gobj, 0);
                    }
                }
            }
            if (fp->input.button_press & fp->input.button_mask_a)
            {
                fp->status_vars.common.turn.button_mask |= fp->input.button_mask_a;
            }
            if (fp->input.button_press & fp->input.button_mask_b)
            {
                fp->status_vars.common.turn.button_mask |= fp->input.button_mask_b;
            }
            if (fp->status_vars.common.turn.is_allow_turn_direction != FALSE)
            {
                fp->status_vars.common.turn.is_allow_turn_direction = FALSE;
            }
        }
    }
}

void func_ovl3_8013E908(GObj *fighter_gobj, s32 lr_dash)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag1 = 0;

    ftStatus_Update(fighter_gobj, ftStatus_Common_Turn, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->status_vars.common.turn.is_allow_turn_direction = FALSE;
    fp->status_vars.common.turn.is_disable_interrupts = FALSE;
    fp->status_vars.common.turn.button_mask = 0U;
    fp->status_vars.common.turn.lr_dash = lr_dash;
    fp->status_vars.common.turn.unk_0x14 = (lr_dash != 0) ? 0 : 256;
    fp->status_vars.common.turn.lr_turn = -fp->lr;
}

void func_ovl3_8013E988(GObj *fighter_gobj)
{
    func_ovl3_8013E908(fighter_gobj, CENTER);
}

void func_ovl3_8013E9A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8013E908(fighter_gobj, -fp->lr);
}

bool32 func_ovl3_8013E9D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->input.stick_range.x * fp->lr) <= FTCOMMON_TURN_STICK_RANGE_MIN)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_8013EA04(GObj *fighter_gobj)
{
    if (func_ovl3_8013E9D0(fighter_gobj) != FALSE)
    {
        func_ovl3_8013E988(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}