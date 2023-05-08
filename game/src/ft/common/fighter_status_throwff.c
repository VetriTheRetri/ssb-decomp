#include "ftdonkey.h"

void func_ovl3_8014DD00(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.throwff.is_turn != FALSE)
    {
        fp->status_vars.common.throwff.turn_frames--;

        if (fp->lr == RIGHT)
        {
            DObjGetStruct(fighter_gobj)->rotate.y = HALF_PI32 - (( (f32) fp->status_vars.common.throwff.turn_frames / FTCOMMON_THROWFF_TURN_FRAMES) * PI32);
        }
        else
        {
            DObjGetStruct(fighter_gobj)->rotate.y = (( (f32) fp->status_vars.common.throwff.turn_frames / FTCOMMON_THROWFF_TURN_FRAMES) * PI32) + (-HALF_PI32);
        }
        if (fp->status_vars.common.throwff.turn_frames == 0)
        {
            fp->status_vars.common.throwff.is_turn = FALSE;
        }
    }
    if (fp->command_vars.flags.flag2 != 0U)
    {
        func_ovl3_8014AB64(fp->catch_gobj);
        func_ovl3_8014AFD0(fp->catch_gobj, -fp->lr, 0, 1);

        fp->command_vars.flags.flag2 = 0;
        fp->catch_gobj = NULL;

        func_ovl2_800E8098(fp, 0U);
    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_8014DE30(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_ThrowFF, fighter_gobj->anim_frame, 1.0F, 0U);

    fp->status_vars.common.throwff.is_turn = FALSE;

    func_ovl2_800E8098(fp, 0x3FU);
}

void func_ovl3_8014DE80(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_ThrowAirFF, fighter_gobj->anim_frame, 1.0F, 0U);
    func_ovl2_800E8098(fp, 0x3FU);
}

void func_ovl3_8014DECC(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8014DE80);
}

void func_ovl3_8014DEF0(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8014DE30);
}

void func_ovl3_8014DF14(GObj *fighter_gobj, bool32 is_turn)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;
    u32 flags;

    if (fp->ground_or_air == ground)
    {
        status_id = ftStatus_Donkey_ThrowFF;
        flags = 0;
    }
    else
    {
        status_id = ftStatus_Donkey_ThrowAirFF;
        flags = 8;
    }
    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, flags);
    ftAnim_Update(fighter_gobj);
    func_ovl2_800E8098(fp, 0x3FU);

    fp->command_vars.flags.flag2 = 0;

    fp->status_vars.common.throwff.is_turn = is_turn;

    if (is_turn != FALSE)
    {
        fp->lr = -fp->lr;

        fp->status_vars.common.throwff.turn_frames = FTCOMMON_THROWFF_TURN_FRAMES;
    }
}

bool32 func_ovl3_8014DFA8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    bool32 is_turn = FALSE;

    if (fp->input.button_tap & (fp->input.button_mask_a | fp->input.button_mask_b))
    {
        if ((ABS(fp->input.stick_range.x) >= FTCOMMON_THROWFF_TURN_STICK_RANGE_MIN) && ((fp->input.stick_range.x * fp->lr) < 0) && (fp->ground_or_air == air))
        {
            is_turn = TRUE;
        }
        func_ovl3_8014DF14(fighter_gobj, is_turn);

        return TRUE;
    }
    else return FALSE;
}