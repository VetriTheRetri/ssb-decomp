#include "fighter.h"

void func_ovl3_8014E1D0(GObj *fighter_gobj, ftThrowReleaseDesc *throw_release) 
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *catch_gobj = this_fp->catch_gobj;
    Fighter_Struct *catch_fp = FighterGetStruct(catch_gobj);
    f32 knockback = gmCommonObject_DamageCalcKnockback(this_fp->percent_damage, 0, 0, throw_release->knockback_weight, throw_release->knockback_scale, throw_release->knockback_base, this_fp->attributes->weight, catch_fp->handicap, this_fp->handicap);
    
    func_ovl3_80140EE4(fighter_gobj, -1, 0, knockback, throw_release->angle, this_fp->lr, 1, 0, 0, FALSE, FALSE, FALSE);
    
    ftCommon_Update1PGameDamageStats(this_fp, 4, 0, 0, 0, 0);
}

void func_ovl3_8014E2A8(GObj *fighter_gobj, ftThrowReleaseDesc *throw_release)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
    f32 knockback;
    s32 lr;

    func_ovl3_8014ADB0(fighter_gobj);

    if (this_fp->ground_or_air == air)
    {
        this_fp->jumps_used = 1;

        DObjGetStruct(fighter_gobj)->translate.z = 0.0F;

        this_fp->phys_info.vel_air.z = DObjGetStruct(fighter_gobj)->translate.z;
    }
    knockback = gmCommonObject_DamageCalcKnockback(this_fp->percent_damage, 0, 0, throw_release->knockback_weight, throw_release->knockback_scale, throw_release->knockback_base, this_fp->attributes->weight, capture_fp->handicap, this_fp->handicap);

    if (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(capture_gobj)->translate.x)
    {
        lr = RIGHT;
    }
    else lr = LEFT;

    func_ovl3_80140EE4(fighter_gobj, -1, 0, knockback, throw_release->angle, lr, 1, 0, 0, FALSE, FALSE, FALSE);
    ftCommon_Update1PGameDamageStats(this_fp, 4, 0, 0, 0, 0);
}

void func_ovl3_8014E3EC(Fighter_Struct *fp, s32 breakout_wait)
{
    fp->breakout_wait = breakout_wait;
    fp->breakout_lr = fp->breakout_ud = 0;
}

bool32 func_ovl3_8014E400(Fighter_Struct *fp)
{
    bool32 is_mash = FALSE;
    s32 breakout_lr_bak, breakout_ud_bak;

    if ((fp->input.pl.button_tap & fp->input.button_mask_a) || (fp->input.pl.button_tap & fp->input.button_mask_b) || (fp->input.pl.button_tap & fp->input.button_mask_z))
    {
        is_mash = TRUE;

        fp->breakout_wait--;
    }
    breakout_lr_bak = fp->breakout_lr, breakout_ud_bak = fp->breakout_ud;

    if (fp->input.pl.stick_range.x < -FTCOMMON_CAPTURE_MASH_STICK_RANGE_MIN)
    {
        fp->breakout_lr = -1;
    }
    if (fp->input.pl.stick_range.x > FTCOMMON_CAPTURE_MASH_STICK_RANGE_MIN)
    {
        fp->breakout_lr = 1;
    }
    if (fp->input.pl.stick_range.y < -FTCOMMON_CAPTURE_MASH_STICK_RANGE_MIN)
    {
        fp->breakout_ud = -1;
    }
    if (fp->input.pl.stick_range.y > FTCOMMON_CAPTURE_MASH_STICK_RANGE_MIN)
    {
        fp->breakout_ud = 1;
    }
    if ((fp->breakout_lr != breakout_lr_bak) || (fp->breakout_ud != breakout_ud_bak))
    {
        is_mash = TRUE;

        fp->breakout_wait--;
    }
    return is_mash;
}

ftThrowReleaseDesc Fighter_ThrowF_Catch_Release       = { 361, 100, 30, 0 };
ftThrowReleaseDesc Fighter_Shouldered_Capture_Release = { 361,  80,  0, 0 };

void func_ovl3_8014E4D4(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);

    func_ovl3_8014E400(this_fp);

    if (this_fp->breakout_wait <= 0)
    {
        func_ovl3_8014E1D0(capture_gobj, &Fighter_ThrowF_Catch_Release);
        func_ovl3_8014E2A8(fighter_gobj, &Fighter_Shouldered_Capture_Release);

        capture_fp->catch_gobj = NULL;

        this_fp->capture_gobj = NULL;
    }
}

void func_ovl3_8014E558(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
    s32 damage;

    func_ovl3_8014ACB4(fighter_gobj, ftStatus_Common_Shouldered);
    func_ovl3_8014E3EC(this_fp, ((this_fp->percent_damage * 0.08F) + 14.0F));

    damage = gmCommon_DamageApplyStale(capture_fp->port_id, 8, capture_fp->attack_id, capture_fp->motion_count);

    if (ftCommon_GetBestHitStatusAll(fighter_gobj) != gmHitCollision_HitStatus_Normal)
    {
        damage = 0;
    }
    if (damage != 0)
    {
        func_ovl3_801415F8(fighter_gobj, gmCommonObject_DamageCalcKnockback(this_fp->percent_damage, damage, damage, 0, 100, 0, this_fp->attributes->weight, capture_fp->handicap, this_fp->handicap), 0);
        ftCommon_DamageUpdateCheckDropItem(this_fp, damage);
        ftCommon_AttackUpdateMatchStats(capture_fp->port_id, this_fp->port_id, damage);
        ftCommon_AttackAddStaleQueue(capture_fp->port_id, this_fp->port_id, capture_fp->attack_id, capture_fp->motion_count);
    }
    func_ovl2_800E806C(this_fp, 7, 0);
}