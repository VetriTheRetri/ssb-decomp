#include <game/src/ft/chara/ftfox/ftfox.h>



void func_ovl3_8015BD00(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8015BFCC);
}

void func_ovl3_8015BD24(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8015C010);
}

void func_ovl3_8015BD48(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->status_vars.fox.specialhi.gravity_delay != 0)
    {
        fp->status_vars.fox.specialhi.gravity_delay--;
    }
    else
    {
        func_ovl2_800D8D68(fp, 0.5F, attributes->fall_speed_max);
    }

    if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
    {
        func_ovl2_800D9074(fp, attributes);
    }
}

void func_ovl3_8015BDC0(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015BE48);
}

void func_ovl3_8015BDE4(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, &func_ovl3_8015BE08);
}

void func_ovl3_8015BE08(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialHiStart, fighter_gobj->anim_frame, 1.0F, 2U);
}

void func_ovl3_8015BE48(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialAirHiStart, fighter_gobj->anim_frame, 1.0F, 2U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_8015BE94(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.fox.specialhi.launch_delay--;

    if (fp->status_vars.fox.specialhi.launch_delay == 0)
    {
        if (fp->ground_or_air == air)
        {
            func_ovl3_8015C60C(fighter_gobj);

        }
        else func_ovl3_8015C4DC(fighter_gobj);
    }
}

void func_ovl3_8015BEE8(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015BF70);
}

void func_ovl3_8015BF0C(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015BF30);
}

void func_ovl3_8015BF30(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialHiHold, fighter_gobj->anim_frame, 1.0F, 0x4002U);
}

void func_ovl3_8015BF70(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialAirHiHold, fighter_gobj->anim_frame, 1.0F, 0x4002U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_8015BFBC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    fp->status_vars.fox.specialhi.launch_delay = FTFOX_FIREFOX_LAUNCH_DELAY;
}

void func_ovl3_8015BFCC(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialHiHold, 0.0F, 1.0F, 2U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015BFBC(fighter_gobj);
}

void func_ovl3_8015C010(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialAirHiHold, 0.0F, 1.0F, 2U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015BFBC(fighter_gobj);
}

void func_ovl3_8015C054(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->joint[4]->rotate.x = (atan2f(fp->phys_info.vel_air.x, fp->phys_info.vel_air.y) * (f32)fp->lr) - HALF_PI32;
    func_ovl2_800EB528(fp->joint[4]);
}

void func_ovl3_8015C0B4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.fox.specialhi.travel_time--;

    if (fp->status_vars.fox.specialhi.travel_time == 0)
    {
        if (fp->ground_or_air == air)
        {
            func_ovl3_8015C88C(fighter_gobj);
        }
        else func_ovl3_8015C838(fighter_gobj);
    }
}

void func_ovl3_8015C108(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.fox.specialhi.decelerate_delay++;

    if (fp->status_vars.fox.specialhi.decelerate_delay >= FTFOX_FIREFOX_DECELERATE_DELAY)
    {
        func_ovl2_800D8978(fp, FTFOX_FIREFOX_DECELERATE_VEL);
    }

    func_ovl2_800D87D0(fighter_gobj);
}

void func_ovl3_8015C15C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.fox.specialhi.decelerate_delay++;

    if (fp->status_vars.fox.specialhi.decelerate_delay >= FTFOX_FIREFOX_DECELERATE_DELAY)
    {
        fp->phys_info.vel_air.x -= (f32)(FTFOX_FIREFOX_DECELERATE_VEL * cosf(fp->status_vars.fox.specialhi.angle) * (f32)fp->lr);
        fp->phys_info.vel_air.y -= (f32)(FTFOX_FIREFOX_DECELERATE_VEL * __sinf(fp->status_vars.fox.specialhi.angle));
    }
    func_ovl3_8015C054(fighter_gobj);
}

void func_ovl3_8015C1F4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.fox.specialhi.coll_timer_unk++;

    if (func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015C46C) != FALSE)
    {
        fp->status_vars.fox.specialhi.angle = atan2f(-fp->coll_data.ground_angle.x * (f32)fp->lr, fp->coll_data.ground_angle.y);
    }
}

bool32 func_ovl3_8015C264(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fp->coll_data.ground_flags & 0x4000) || (fp->status_vars.fox.specialhi.coll_timer_unk >= 0xF))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8015C29C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    u16 coll_mask;

    fp->status_vars.fox.specialhi.coll_timer_unk++;

    if (func_ovl2_800DE758(fighter_gobj, func_ovl3_8015C264) != FALSE)
    {
        coll_mask = (fp->coll_data.coll_mask_prev ^ fp->coll_data.coll_mask) & fp->coll_data.coll_mask & MPCOLL_MASK_GROUND;

        if (((coll_mask & MPCOLL_MASK_GROUND) == 0) || (func_ovl0_800C7C98(&fp->phys_info.vel_air, &fp->coll_data.ground_angle, FTFOX_FIREFOX_COLL_ANGLE_UNK) == FALSE))
        {
            if (D_ovl3_8018C88C < vec3f_angle_diff(&fp->coll_data.ground_angle, &fp->phys_info.vel_air))
            {
                func_ovl3_8015CA64(fighter_gobj);
                return;
            }
            func_ovl3_8015C838(fighter_gobj);
            return;
        }
        goto coll_end;
    }

    coll_mask = (fp->coll_data.coll_mask_prev ^ fp->coll_data.coll_mask) & fp->coll_data.coll_mask & (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL) & 0xFFFF;

    if (coll_mask & MPCOLL_MASK_CEIL)
    {
        if (func_ovl0_800C7C98(&fp->phys_info.vel_air, &fp->coll_data.ceil_angle, FTFOX_FIREFOX_COLL_ANGLE_UNK) != FALSE)
        {
            goto coll_end;
        }
    }
    else if (coll_mask & MPCOLL_MASK_RWALL)
    {
        if (func_ovl0_800C7C98(&fp->phys_info.vel_air, &fp->coll_data.rwall_angle, FTFOX_FIREFOX_COLL_ANGLE_UNK) != FALSE)
        {
            goto coll_end;
        }
    }
    else if ((coll_mask & MPCOLL_MASK_LWALL) && (func_ovl0_800C7C98(&fp->phys_info.vel_air, &fp->coll_data.lwall_angle, FTFOX_FIREFOX_COLL_ANGLE_UNK) != FALSE))
    {
    coll_end:

        fp->lr = (fp->phys_info.vel_air.x >= 0.0F) ? RIGHT : LEFT;

        fp->joint[0]->rotate.y = (f32)((f32)fp->lr * HALF_PI32);

        fp->status_vars.fox.specialhi.angle = atan2f(fp->phys_info.vel_air.y, fp->phys_info.vel_air.x * (f32)fp->lr);

        func_ovl3_8015C054(fighter_gobj);
    }
}

void func_ovl3_8015C46C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialAirHi, fighter_gobj->anim_frame, 1.0F, 2U);

    fp->jumps_used = attributes->jumps_max;
}

void func_ovl3_8015C4C8(Fighter_Struct *fp)
{
    fp->status_vars.fox.specialhi.travel_time = FTFOX_FIREFOX_TRAVEL_TIME;
    fp->status_vars.fox.specialhi.decelerate_delay = 0;
    fp->status_vars.fox.specialhi.coll_timer_unk = 0;
}

void func_ovl3_8015C4DC(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    s32 temp_stick_y;
    s32 temp_stick_x;

    Vec3f sp38;

    s32 stick_y;
    s32 stick_x;

    s32 unused;

    temp_stick_x = fp->input.pl.stick_range.x;

    stick_x = temp_stick_x;

    if (temp_stick_x < 0)
    {
        stick_x = -temp_stick_x;
    }
    else stick_x = temp_stick_x;

    temp_stick_y = fp->input.pl.stick_range.y;

    stick_y = temp_stick_y;

    if (temp_stick_y < 0)
    {
        stick_y = -temp_stick_y;
    }
    else stick_y = temp_stick_y;

    if (((stick_y + stick_x) >= FTFOX_FIREFOX_ANGLE_STICK_THRESHOLD) && !(fp->coll_data.ground_flags & 0x4000))
    {
        sp38.x = (f32)temp_stick_x;
        sp38.y = (f32)fp->input.pl.stick_range.y;
        sp38.z = 0.0F;

        if (!(vec3f_angle_diff(&fp->coll_data.ground_angle, &sp38) < HALF_PI32))
        {
            ftCommon_StickInputSetLR(fp);
            ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialHi, 0.0F, 1.0F, 2U);
            func_ovl3_8015C4C8(fp);

            fp->phys_info.vel_ground.x = 115.0F;
            fp->status_vars.fox.specialhi.angle = atan2f(-fp->coll_data.ground_angle.x * (f32)fp->lr, fp->coll_data.ground_angle.y);
            return;
        }
    }
    ftMapCollide_SetAir(fp);
    func_ovl3_8015C60C(fighter_gobj);
}

void func_ovl3_8015C60C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    s32 stick_x;
    s32 stick_y;
    s32 stick_x_2;

    stick_x = fp->input.pl.stick_range.x;

    stick_x = ABS(fp->input.pl.stick_range.x);

    stick_y = fp->input.pl.stick_range.y;

    stick_y = ABS(fp->input.pl.stick_range.y);

    if ((stick_y + stick_x) >= FTFOX_FIREFOX_ANGLE_STICK_THRESHOLD)
    {
        stick_x_2 = fp->input.pl.stick_range.x;

        stick_x_2 = ABS(fp->input.pl.stick_range.x);

        if (stick_x_2 >= FTFOX_FIREFOX_MODEL_STICK_THRESHOLD)
        {
            ftCommon_StickInputSetLR(fp);
        }
        fp->status_vars.fox.specialhi.angle = atan2f((f32)fp->input.pl.stick_range.y, (f32)(fp->input.pl.stick_range.x * fp->lr));
    }
    else
    {
        fp->status_vars.fox.specialhi.angle = (f32)HALF_PI32;
    }
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialAirHi, 0.0F, 1.0F, 2U);
    func_ovl3_8015C4C8(fp);

    fp->phys_info.vel_air.x = (f32)(cosf(fp->status_vars.fox.specialhi.angle) * 115.0F * (f32)fp->lr);
    fp->phys_info.vel_air.y = (f32)(__sinf(fp->status_vars.fox.specialhi.angle) * 115.0F);

    func_ovl3_8015C054(fighter_gobj);

    fp->jumps_used = attributes->jumps_max;
}

void func_ovl3_8015C750(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, FTFOX_FIREFOX_AIR_DRIFT, FALSE, TRUE, FALSE, FTFOX_FIREFOX_LANDING_LAG, TRUE);
    }
}

void func_ovl3_8015C7A4(GObj *fighter_gobj)
{
    func_ovl2_800D8978(FighterGetStruct(fighter_gobj), FTFOX_FIREFOX_DECELERATE_END);
    func_ovl2_800D87D0(fighter_gobj);
}

void func_ovl3_8015C7D4(GObj *fighter_gobj)
{
    ftMapCollide_CheckGroundCliff(fighter_gobj, func_ovl3_8015C7F8);
}

void func_ovl3_8015C838(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        ftMapCollide_SetGround(fp);
    }
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialHiEnd, 0.0F, 1.0F, 2U);
}

void func_ovl3_8015C88C(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialAirHiEnd, 0.0F, 1.0F, 2U);
}

void func_ovl3_8015C8BC(GObj* fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0) && (fp->ground_or_air == air))
    {
        func_ovl3_801438F0(fighter_gobj, FTFOX_FIREFOX_AIR_DRIFT, FALSE, TRUE, FALSE, FTFOX_FIREFOX_LANDING_LAG, TRUE);
    }

    else if (fighter_gobj->anim_frame <= 0.0F)
    {
        if (fp->ground_or_air == air)
        {
            func_ovl3_801438F0(fighter_gobj, FTFOX_FIREFOX_AIR_DRIFT, FALSE, TRUE, FALSE, FTFOX_FIREFOX_LANDING_LAG, TRUE);
        }
        else func_ovl3_8013E1C8(fighter_gobj);
    }
}

void func_ovl3_8015C97C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->ground_or_air == air)
    {
        jtgt_ovl2_800D9414(fighter_gobj);

        if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
        {
            func_ovl2_800D9074(fp, attributes);
        }
    }
    else func_ovl2_800D8BB4(fighter_gobj);

}

void func_ovl3_8015C9E8(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        if (func_ovl2_800DE7D8(fighter_gobj) != FALSE)
        {
            if (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL)
            {
                func_ovl3_80144C24(fighter_gobj);
            }
            else ftMapCollide_SetGround(fp);
        }
    }
    else jtgt_ovl2_800DDEC4(fighter_gobj);
}

void func_ovl3_8015CA64(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialHiBound, 0.0F, 1.0F, 2U);

    fp->command_vars.flags.flag1 = FALSE;
}

void func_ovl3_8015CAA4(Fighter_Struct *fp)
{
    fp->status_vars.fox.specialhi.gravity_delay = FTFOX_FIREFOX_GRAVITY_DELAY;
}

void jtgt_ovl3_8015CAB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialHiStart, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015CAA4(fp);

    fp->phys_info.vel_ground.x /= 2;
}

void jtgt_ovl3_8015CB10(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Fox_SpecialAirHiStart, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015CAA4(fp);

    fp->phys_info.vel_air.y = 0.0F;
    fp->phys_info.vel_air.x /= 2;
}