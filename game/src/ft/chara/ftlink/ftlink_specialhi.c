#include "ftlink.h"

void func_ovl3_80163B40(Fighter_Struct *fp, Item_Struct *ip)
{
    ip->is_hitlag_item = FALSE;

    ip->item_vars.spin_attack.unk_0x18 = 1;

    func_ovl3_8016800C(ip->item_gobj);

    fp->status_vars.link.specialhi.spin_attack_gobj = NULL;
}

void func_ovl3_80163B80(GObj *fighter_gobj, Item_Struct *ip)
{
    ip->item_vars.spin_attack.pos_index++;
    ip->item_vars.spin_attack.pos_index %= (ARRAY_COUNT(ip->item_vars.spin_attack.pos_x) | ARRAY_COUNT(ip->item_vars.spin_attack.pos_y));

    ip->item_vars.spin_attack.pos_x[ip->item_vars.spin_attack.pos_index] = (s16) DObjGetStruct(fighter_gobj)->translate.x;
    ip->item_vars.spin_attack.pos_y[ip->item_vars.spin_attack.pos_index] = (s16) DObjGetStruct(fighter_gobj)->translate.y;
}

void func_ovl3_80163BF0(GObj *fighter_gobj, Item_Struct *ip)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        func_ovl3_80163B40(fp, ip);
    }
}

void func_ovl3_80163C2C(GObj *fighter_gobj, Item_Struct *ip)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    switch (fp->command_vars.flags.flag2) // jtbl at 0x8018C9F0
    {
    case 0:
        break;

    case 1:
        ip->item_hit.update_state = gmHitCollision_UpdateState_New;
        ip->item_hit.size = FTLINK_SPIN_ATTACK_FLAG_SIZE_1;

        func_ovl3_80165F60(fighter_gobj);
        break;

    case 2:

        ip->item_hit.update_state = gmHitCollision_UpdateState_New;
        ip->item_hit.size = FTLINK_SPIN_ATTACK_FLAG_SIZE_2;

        func_ovl3_80165F60(fighter_gobj);
        break;

    case 3:
        ip->item_hit.update_state = gmHitCollision_UpdateState_New;
        ip->item_hit.size = FTLINK_SPIN_ATTACK_FLAG_SIZE_3;

        func_ovl3_80165F60(fighter_gobj);
        break;

    case 4:
        ip->item_hit.update_state = gmHitCollision_UpdateState_New;
        ip->item_hit.size = FTLINK_SPIN_ATTACK_FLAG_SIZE_4;

        func_ovl3_80165F60(fighter_gobj);
        break;

    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        ip->item_hit.update_state = 0;
        break;

    case 13:
    default:
        ip->item_hit.update_state = 0;
        break;
    }
    fp->command_vars.flags.flag2 = 0;
}

void func_ovl3_80163D00(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->status_vars.link.specialhi.spin_attack_gobj != NULL)
    {
        Item_Struct *ip = itGetStruct(fp->status_vars.link.specialhi.spin_attack_gobj);

        if (fp->hitlag_timer != 0)
        {
            ip->is_hitlag_item = TRUE;
        }
        else ip->is_hitlag_item = FALSE;
    }
}

void func_ovl3_80163D44(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->status_vars.link.specialhi.spin_attack_gobj != NULL)
    {
        Item_Struct *ip = itGetStruct(fp->status_vars.link.specialhi.spin_attack_gobj);

        func_ovl3_80163C2C(fighter_gobj, ip);
        func_ovl3_80163B80(fighter_gobj, ip);
        func_ovl3_80163BF0(fighter_gobj, ip);
    }
}

void func_ovl3_80163D94(GObj *fighter_gobj, bool32 is_skip_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *spin_attack_gobj;
    Vec3f pos;

    if ((fp->command_vars.flags.flag0 != 0) && (fp->status_vars.link.specialhi.spin_attack_gobj == NULL))
    {
        fp->command_vars.flags.flag0 = 0;

        if (func_ovl2_80103378(fighter_gobj) != FALSE)
        {
            fp->is_statupdate_stop_gfx = TRUE;
        }
        if (is_skip_gobj == FALSE)
        {
            pos.z = 0.0F;
            pos.y = 0.0F;
            pos.x = 0.0F;

            func_ovl2_800EDF24(fp->joint[FTLINK_SPIN_ATTACK_SPAWN_JOINT], &pos);

            fp->status_vars.link.specialhi.spin_attack_gobj = func_ovl3_8016CB1C(fighter_gobj, &pos);

            if (fp->status_vars.link.specialhi.spin_attack_gobj != NULL)
            {
                Item_Struct *ip = itGetStruct(spin_attack_gobj);
                s32 i;

                ip->item_hit.update_state = 0;

                for (i = 0; i < (ARRAY_COUNT(ip->item_vars.spin_attack.pos_x) | ARRAY_COUNT(ip->item_vars.spin_attack.pos_y)); i++)
                {
                    ip->item_vars.spin_attack.pos_x[i] = (s16) DObjGetStruct(fighter_gobj)->translate.x;
                    ip->item_vars.spin_attack.pos_y[i] = (s16) DObjGetStruct(fighter_gobj)->translate.y;
                }
            }
        }
    }
}

void func_ovl3_80163EFC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->status_vars.link.specialhi.spin_attack_gobj != NULL)
    {
        func_ovl3_80163B40(fp, itGetStruct(fp->status_vars.link.specialhi.spin_attack_gobj));
    }
}

void func_ovl3_80163F30(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_801642EC);
}

void func_ovl3_80163F54(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        Fighter_Struct *fp = ftGetStruct(fighter_gobj);

        if (fp->status_vars.link.specialhi.spin_attack_gobj != NULL)
        {
            func_ovl3_80163B40(fp, itGetStruct(fp->status_vars.link.specialhi.spin_attack_gobj));
        }
        ftCommon_Wait_SetStatus(fighter_gobj);
    }
}

void func_ovl3_80163FB0(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        Fighter_Struct *fp = ftGetStruct(fighter_gobj);

        if (fp->status_vars.link.specialhi.spin_attack_gobj != NULL)
        {
            func_ovl3_80163B40(fp, itGetStruct(fp->status_vars.link.specialhi.spin_attack_gobj));
        }
        ftCommon_FallSpecial_SetStatus(fighter_gobj, FTLINK_SPIN_ATTACK_FALLSPECIAL_DRIFT, FALSE, TRUE, TRUE, FTLINK_SPIN_ATTACK_LANDING_LAG, FALSE);
    }
}

void func_ovl3_80164030(GObj *fighter_gobj)
{
    func_ovl3_80163D44(fighter_gobj);
    func_ovl3_80163D94(fighter_gobj, FALSE);
    func_ovl2_800D8BB4(fighter_gobj);
}

void func_ovl3_80164064(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    f32 gravity;

    func_ovl3_80163D44(fighter_gobj);
    func_ovl3_80163D94(fighter_gobj, TRUE);

    gravity = (fp->command_vars.flags.flag1 != 0U) ? fp->attributes->gravity : fp->attributes->gravity * FTLINK_SPIN_ATTACK_GRAVITY_MUL;

    func_ovl2_800D8D68(fp, gravity, fp->attributes->fall_speed_max);

    if (func_ovl2_800D8FA8(fp, fp->attributes) == FALSE)
    {
        ftCommonAttributes *attributes = fp->attributes;

        ftPhysicsClampDriftStickRange(fp, 8, attributes->aerial_acceleration * FTLINK_SPIN_ATTACK_AIR_DRIFT_MUL, attributes->aerial_speed_max_x);
        func_ovl2_800D9074(fp, fp->attributes);
    }
}

void func_ovl3_80164128(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        ftMapCollide_SetAir(fp);
        ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirHi, fighter_gobj->anim_frame, 1.0F, 5U);

        fp->proc_damage = func_ovl3_80163EFC;

        fp->jumps_used = fp->attributes->jumps_max;
    }
}

void func_ovl3_80164198(GObj *fighter_gobj)
{
    if (func_ovl2_800DDDDC(fighter_gobj, ftCommon_Fall_SetStatus) == FALSE)
    {
        func_ovl3_80163EFC(fighter_gobj);
    }
}

void func_ovl3_801641D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (func_ovl2_800DE87C(fighter_gobj) != FALSE)
    {
        func_ovl3_80163EFC(fighter_gobj);

        if (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL)
        {
            ftCommon_CliffCatch_SetStatus(fighter_gobj);
        }
        else if (fp->coll_data.coll_type & MPCOLL_MASK_GROUND)
        {
            ftMapCollide_SetGround(fp);
            ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialHiEnd, 0.0F, 1.0F, 0U);

            fp->proc_damage = func_ovl3_80163EFC;
        }
    }
}

void func_ovl3_8016426C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = 0;
    fp->command_vars.flags.flag2 = 0;
    fp->command_vars.flags.flag1 = 0;

    fp->status_vars.link.specialhi.spin_attack_gobj = NULL;
}

void jtgt_ovl3_80164284(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->proc_status = func_ovl3_8016426C;

    ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->proc_damage = func_ovl3_80163EFC;
    fp->proc_gfx = func_ovl3_80163D00;
}

void func_ovl3_801642EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialHiEnd, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->proc_damage = func_ovl3_80163EFC;
    fp->proc_gfx = func_ovl3_80163D00;
}

void jtgt_ovl3_80164348(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->proc_status = func_ovl3_8016426C;

    ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->phys_info.vel_air.y = FTLINK_SPIN_ATTACK_AIR_VEL_Y;

    fp->jumps_used = fp->attributes->jumps_max;

    fp->proc_damage = func_ovl3_80163EFC;
    fp->proc_gfx = func_ovl3_80163D00;
}