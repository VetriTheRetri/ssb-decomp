#include "ftsamus.h"

void func_ovl3_8015DF00(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;
    DObj *joint;

    if (fp->command_vars.flags.flag0 != FALSE)
    {
        fp->command_vars.flags.flag0 = FALSE;

        pos.x = 0.0F;
        pos.z = 0.0F;
        pos.y = 60.0F;

        joint = fp->joint[ftParts_TopN_Joint]; // Not required but stack might suggest they wrote it like this

        func_ovl2_800EDF24(joint, &pos);
        func_ovl3_80169328(fighter_gobj, &pos);
    }
}

void func_ovl3_8015DF64(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    func_ovl3_8015DF00(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        func_ovl3_8015E170(fighter_gobj);
    }
    else ftCommon_IfAnimEnd_SetStatusWait(fighter_gobj);
}

void func_ovl3_8015DFBC(GObj *fighter_gobj)
{
    func_ovl3_8015DF00(fighter_gobj);
    ftCommon_IfAnimEnd_SetStatusFall(fighter_gobj);
}

void func_ovl3_8015DFE4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->command_vars.flags.flag3 != FALSE)
    {
        func_ovl2_800D8ADC(fp, attributes->walk_speed_mul * FTSAMUS_BOMB_DRIFT, attributes->traction);
        func_ovl2_800D87D0(fighter_gobj);
    }
    else func_ovl2_800D8BB4(fighter_gobj);
}

void func_ovl3_8015E050(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    func_ovl2_800D8E50(fp, attributes);

    if (func_ovl2_800D8EDC(fp, attributes->aerial_speed_max_x * FTSAMUS_BOMB_DRIFT) == FALSE)
    {
        ftPhysics_ClampDriftStickRange(fp, 8, attributes->aerial_acceleration * FTSAMUS_BOMB_DRIFT, attributes->aerial_speed_max_x * FTSAMUS_BOMB_DRIFT);
        func_ovl2_800D9074(fp, attributes);
    }
}

void func_ovl3_8015E0E8(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015E1DC);
}

void func_ovl3_8015E10C(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015E130);
}

void func_ovl3_8015E130(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->command_vars.flags.flag3 = FALSE;

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialLw, fighter_gobj->anim_frame, 1.0F, 0U);
}

void func_ovl3_8015E170(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialAirLw, fighter_gobj->anim_frame, 1.0F, 0U);

    fp->phys_info.vel_air.y = FTSAMUS_BOMB_VEL_Y_BASE;
    fp->jumps_used = attributes->jumps_max;
}

void func_ovl3_8015E1DC(GObj *fighter_gobj)
{
    ftMapCollide_SetAir(ftGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialAirLw, fighter_gobj->anim_frame, 1.0F, 0U);
}

void func_ovl3_8015E218(Fighter_Struct *fp)
{
    fp->command_vars.flags.flag0 = FALSE;
}

void jtgt_ovl3_8015E220(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->command_vars.flags.flag3 = FALSE;

    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialLw, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015E218(fp);

    fp->status_vars.samus.speciallw.unused = FALSE;
}

void jtgt_ovl3_8015E274(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialAirLw, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015E218(fp);

    fp->phys_info.vel_air.y = FTSAMUS_BOMB_VEL_Y_BASE - FTSAMUS_BOMB_VEL_Y_SUB;

    func_ovl2_800D8E78(fp, attributes->aerial_speed_max_x * FTSAMUS_BOMB_DRIFT);

    fp->jumps_used = attributes->jumps_max; // Why tho

    fp->status_vars.samus.speciallw.unused = TRUE;
}