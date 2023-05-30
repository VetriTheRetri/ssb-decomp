#include <game/src/ft/chara/ftfox/ftfox.h>

void func_ovl3_8015BB50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    if (fp->command_vars.flags.flag0 != FALSE)
    {
        fp->command_vars.flags.flag0 = FALSE;

        pos.x = FTFOX_BLASTER_SPAWN_OFF_X;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTFOX_BLASTER_HOLD_JOINT], &pos);
        func_ovl3_80168A74(fighter_gobj, &pos);
    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_8015BBD8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != FALSE) && (fp->input.pl.button_tap & fp->input.button_mask_b))
    {
        if (fp->ground_or_air == air)
        {
            func_ovl3_8015BCB8(fighter_gobj);
        }
        else func_ovl3_8015BC78(fighter_gobj);

        ftCommon_MotionCountIncSetID(fp, 0x12);
        ftCommon_StatUpdateCountIncSetFlags(fp, fp->stat_flags.halfword);
        ftCommon_Update1PGameAttackStats(fp, 0);
    }
}

void func_ovl3_8015BC68(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = FALSE;
    fp->command_vars.flags.flag1 = FALSE;
}


void func_ovl3_8015BC78(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015BC68(fighter_gobj);
}

void func_ovl3_8015BCB8(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialAirN, 0.0F, 1.0F, 8U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015BC68(fighter_gobj);
}
