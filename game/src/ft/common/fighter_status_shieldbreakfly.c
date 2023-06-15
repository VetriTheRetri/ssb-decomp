#include "fighter.h"
#include "gmmatch.h"

// 0x80149440
void ftCommon_ShieldBreakFly_ProcUpdate(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, ftCommon_ShieldBreakFall_SetStatus);
}

// 0x80149464
void ftCommon_ShieldBreakFly_ProcMap(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, ftCommon_ShieldBreakDown_SetStatus);
}

// 0x80149488
void ftCommon_ShieldBreakFly_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_ShieldBreakFly, 0.0F, 1.0F, FTSTATUPDATE_DAMAGEPORT_PRESERVE);
    ftAnim_Update(fighter_gobj);

    fp->phys_info.vel_air.x = 0.0F;
    fp->phys_info.vel_air.y = attributes->shield_break_vel_y;

    ftCommon_CheckSetColAnimIndex(fighter_gobj, FTCOMMON_SHIELDBREAK_COLANIM_ID, FTCOMMON_SHIELDBREAK_COLANIM_LENGTH);
    func_800269C0(0xFU);
}

extern s8 gmBonusStat_ShieldBreaker; // Bonus for breaking an enemy's shield in 1P game

// 0x80149510
void ftCommon_ShieldBreakFly_UpdateVarsSetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f offset;

    offset.x = 0.0F;
    offset.y = 0.0F;
    offset.z = 0.0F;

    func_ovl2_800EDF24(fp->joint[ftParts_YRotN_Joint], &offset);

    if (fp->ft_kind == Ft_Kind_Yoshi)
    {
        func_ovl2_80103A88(&DObjGetStruct(fighter_gobj)->translate);
        func_ovl2_801041A0(&DObjGetStruct(fighter_gobj)->translate);
    }
    else func_ovl2_80101790(&offset);

    ftCommon_Update1PGameDamageStats(fp, fp->shield_port_id, 0, 0, 0, 0);

    if ((Match_Info->game_type == gmMatch_GameType_1PGame) && (fp->shield_damage != 0))
    {
        if ((fp->shield_port_id == Scene_Info.player_port) && (fp->shield_port_id != fp->port_id))
        {
            gmBonusStat_ShieldBreaker = TRUE;
        }
    }
    ftCommon_ShieldBreakFly_SetStatus(fighter_gobj);
}

// 0x80149608
void ftCommon_ShieldBreakFlyReflector_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    SpecialHit *special_hit = fp->special_hit;
    Vec3f offset = special_hit->offset;

    func_ovl2_800EDF24(fp->joint[special_hit->joint_index], &offset);
    func_ovl2_8010155C(&offset, fp->lr_reflect);
    ftCommon_ShieldBreakFly_SetStatus(fighter_gobj);
}
