#include <game/src/ft/chara/ftfox/ftfox.h>

// 0x8015BB50
void ftFox_SpecialN_ProcUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;

    if (fp->command_vars.flags.flag0 != 0)
    {
        fp->command_vars.flags.flag0 = 0;

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

// 0x8015BBD8
void ftFox_SpecialN_ProcInterrupt(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (fp->input.pl.button_tap & fp->input.button_mask_b))
    {
        if (fp->ground_or_air == air)
        {
            ftFox_SpecialAirN_SetStatus(fighter_gobj);
        }
        else ftFox_SpecialN_SetStatus(fighter_gobj);

        ftCommon_MotionCountIncSetID(fp, 0x12);
        ftCommon_StatUpdateCountIncSetFlags(fp, fp->stat_flags.halfword);
        ftCommon_Update1PGameAttackStats(fp, 0);
    }
}

// 0x8015BC68
void ftFox_SpecialN_InitStatusVars(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = 0;
    fp->command_vars.flags.flag1 = 0;
}

// 0x8015BC78
void ftFox_SpecialN_SetStatus(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialN, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftAnim_Update(fighter_gobj);
    ftFox_SpecialN_InitStatusVars(fighter_gobj);
}

// 0x8015BCB8
void ftFox_SpecialAirN_SetStatus(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialAirN, 0.0F, 1.0F, FTSTATUPDATE_FASTFALL_PRESERVE);
    ftAnim_Update(fighter_gobj);
    ftFox_SpecialN_InitStatusVars(fighter_gobj);
}
