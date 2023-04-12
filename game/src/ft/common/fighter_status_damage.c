#include "fighter.h"

void func_ovl3_80140340(Fighter_Struct *fp)
{
    f32 knockback = (fp->ground_or_air == air) ? vec3f_mag(&fp->phys_info.vel_damage_air) : ABSF(fp->phys_info.vel_damage_ground.x);
    s32 spawn_gfx_wait;

    if (knockback < FTCOMMON_DAMAGE_KNOCKBACK_LOW)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_LOW;
    }
    else if (knockback < FTCOMMON_DAMAGE_KNOCKBACK_MID_LOW)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_MID_LOW;
    }
    else if (knockback < FTCOMMON_DAMAGE_KNOCKBACK_MID)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_MID;
    }
    else if (knockback < FTCOMMON_DAMAGE_KNOCKBACK_MID_HIGH)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_MID_HIGH;
    }
    else if (knockback < FTCOMMON_DAMAGE_KNOCKBACK_HIGH)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_HIGH;
    }
    else spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_DEFAULT;
    
    fp->status_vars.common.damage.dust_gfx_int = spawn_gfx_wait;
}

void func_ovl3_80140454(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.damage.dust_gfx_int != 0)
    {
        fp->status_vars.common.damage.dust_gfx_int--;

        if (fp->status_vars.common.damage.dust_gfx_int == 0)
        {
            func_ovl2_800EABDC(fighter_gobj, 0x11, 4, 0, 0, fp->lr, 0, 0);
            func_ovl3_80140340(fp);
        }
    }
}

void func_ovl3_801404B8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.damage.hitstun_timer != 0)
    {
        fp->status_vars.common.damage.hitstun_timer--;

        if (fp->status_vars.common.damage.hitstun_timer <= 0)
        {
            fp->knockback_last = fp->status_vars.common.damage.knockback;
        }
    }
}

void func_ovl3_801404E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_801404B8(fighter_gobj);

    if ((fighter_gobj->anim_frame <= 0.0F) && (fp->status_vars.common.damage.hitstun_timer <= 0))
    {
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_8014053C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80140454(fighter_gobj);
    func_ovl3_801404B8(fighter_gobj);

    if ((fighter_gobj->anim_frame <= 0.0F) && (fp->status_vars.common.damage.hitstun_timer <= 0))
    {
        func_ovl3_80143664(fighter_gobj);
    }
}

void func_ovl3_801405A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->hitlag_timer <= 0) && (fp->status_vars.common.damage.unk_0x30 != 0))
    {
        fp->status_vars.common.damage.unk_0x30 = 0;

        func_ovl2_800EA8EC(fp, 1);
    }
}

void func_ovl3_801405E4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->hitlag_timer <= 0)
    {
        func_ovl2_800E6F24(fighter_gobj, fp->status_vars.common.damage.status_id, 0.0F, 1.0F, 0x1400U);
        func_ovl2_800E0830(fighter_gobj);

        if (fp->status_info.status_id == ftStatus_Common_DamageFlyRoll)
        {
            func_ovl3_80140744(fighter_gobj);
        }
        fp->is_hitstun = TRUE;

        if (fp->status_vars.common.damage.unk_0x30 != 0)
        {
            fp->status_vars.common.damage.unk_0x30 = 0;
            func_ovl2_800EA8EC(fp, 1);
        }
    }
}

void func_ovl3_80140674(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.damage.hitstun_timer <= 0)
    {
        fp->is_hitstun = FALSE;

        if (fp->ground_or_air == air)
        {
            if (func_ovl2_800F3794(fighter_gobj) != FALSE)
            {
                func_ovl3_80147BE0(fighter_gobj);
            }
            else func_ovl3_8013F9A0(fighter_gobj);
        }
        else if (func_ovl2_800F3794(fighter_gobj) != FALSE)
        {
            jtgt_ovl2_800F38C4(fighter_gobj);
        }
        else func_ovl3_8013E070(fighter_gobj);
    }
}

void func_ovl3_8014070C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.damage.hitstun_timer <= 0)
    {
        fp->is_hitstun = FALSE;

        func_ovl3_80143560(fighter_gobj);
    }
}

void func_ovl3_80140744(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->joint[4]->rotate.x = atan2f(fp->phys_info.vel_air.x + fp->phys_info.vel_damage_air.x, fp->phys_info.vel_air.y + fp->phys_info.vel_damage_air.y) * fp->lr;

    func_ovl2_800EB528(fp->joint[4]);
}

void func_ovl3_801407A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        if (fp->status_vars.common.damage.hitstun_timer <= 0)
        {
            jtgt_ovl2_800D9160(fighter_gobj);
        }
        else
        {
            func_ovl2_800D91EC(fighter_gobj);
        }
    }
    else
    {
        func_ovl2_800D8BB4(fighter_gobj);
    }
    if (fp->status_info.status_id == ftStatus_Common_DamageFlyRoll)
    {
        func_ovl3_80140744(fighter_gobj);
    }
    if ((fp->throw_gobj != NULL) && (vec3f_mag(&fp->phys_info.vel_damage_air) < 70.0F))
    {
        func_ovl2_800E8518(fighter_gobj);
    }
}

void func_ovl3_80140878(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->hitlag_timer != 0)
    {
        if ((SQUARE(fp->input.stick_range.x) + SQUARE(fp->input.stick_range.y)) >= SQUARE(FTCOMMON_DAMAGE_SMASH_DI_RANGE_MIN))
        {
            if ((fp->buffer_stick_x < FTCOMMON_DAMAGE_SMASH_DI_BUFFER_FRAMES_MAX) || (fp->buffer_stick_y < FTCOMMON_DAMAGE_SMASH_DI_BUFFER_FRAMES_MAX))
            {
                Vec3f *translate = &DObjGetStruct(fighter_gobj)->translate;

                translate->x += fp->input.stick_range.x * FTCOMMON_DAMAGE_SMASH_DI_RANGE_MUL;
                translate->y += fp->input.stick_range.y * FTCOMMON_DAMAGE_SMASH_DI_RANGE_MUL;

                fp->buffer_stick_x = fp->buffer_stick_y = U8_MAX - 1;
            }
        }
    }
}

void func_ovl3_80140934(void) // Unused
{
    return;
}

void func_ovl3_8014093C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl2_800DEDAC(fighter_gobj) != FALSE)                 &&
    (func_ovl3_80141C6C(fighter_gobj) == FALSE)                     &&
    (fp->status_vars.common.damage.coll_flags & MPCOLL_MASK_GROUND) &&
    (func_ovl3_80144760(fighter_gobj) == FALSE)                     &&
    (func_ovl3_801446BC(fighter_gobj) == FALSE))
    {
        func_ovl3_80144498(fighter_gobj);
    }
}