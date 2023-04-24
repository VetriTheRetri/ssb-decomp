#include "fighter.h"

void func_ovl3_80149440(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80149744);
}

void func_ovl3_80149464(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_801496A4);
}

void func_ovl3_80149488(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    func_ovl2_800DEEC8(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_ShieldBreakFly, 0.0F, 1.0F, 0x1000U);
    ftAnim_Update(fighter_gobj);

    fp->phys_info.vel_air.x = 0.0F;
    fp->phys_info.vel_air.y = attributes->shield_break_vel_y;

    func_ovl2_800E9814(fighter_gobj, FTCOMMON_SHIELDBREAK_COLANIM_ID, FTCOMMON_SHIELDBREAK_COLANIM_LENGTH);
    func_800269C0(0xFU);
}

struct UnkA4AD0 {
    /* 0x00 */ u8 scene;
    /* 0x01 */ u8 previousScene;
    /* 0x02 */ u8 pad02[0x13 - 0x02];
    /* 0x13 */ u8 player_port; // Port index of player in 1P game?
    /* 0x14 */ u8 pad14[0x48 - 0x14];
}; // size == 0x48

extern struct UnkA4AD0 D_800A4AD0;
extern s8 gmBonusStat_ShieldBreaker; // Bonus for breaking an enemy's shield in 1P game

void func_ovl3_80149510(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f offset;

    offset.x = 0.0F;
    offset.y = 0.0F;
    offset.z = 0.0F;

    func_ovl2_800EDF24(fp->joint[3], &offset);

    if (fp->ft_kind == Ft_Kind_Yoshi)
    {
        func_ovl2_80103A88(&DObjGetStruct(fighter_gobj)->translate);
        func_ovl2_801041A0(&DObjGetStruct(fighter_gobj)->translate);
    }
    else func_ovl2_80101790(&offset);

    func_ovl2_800EAA2C(fp, fp->shield_port_id, 0, 0, 0, 0);

    if ((Match_Info->game_type == 5) && (fp->shield_damage != 0))
    {
        if ((fp->shield_port_id == D_800A4AD0.player_port) && (fp->shield_port_id != fp->port_id))
        {
            gmBonusStat_ShieldBreaker = TRUE;
        }
    }
    func_ovl3_80149488(fighter_gobj);
}

void func_ovl3_80149608(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    SpecialHit *special_hit = fp->special_hit;
    Vec3f offset = special_hit->offset;

    func_ovl2_800EDF24(fp->joint[special_hit->joint_index], &offset);
    func_ovl2_8010155C(&offset, fp->lr_reflect);
    func_ovl3_80149488(fighter_gobj);
}

void func_ovl3_80149680(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_801497C4);
}

void func_ovl3_801496A4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (fp->ground_or_air == air)
    {
        ftCollision_SetGround(fp);
    }
    status_id = (ftCommon_DownBounce_UpOrDown(fighter_gobj) != 0) ? ftStatus_Common_ShieldBreakDownD : ftStatus_Common_ShieldBreakDownU;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0xB2U);
    func_ovl3_80144428(fighter_gobj);
}