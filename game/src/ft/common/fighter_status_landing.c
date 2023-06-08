#include "fighter.h"

#define ftStatus_CheckInterruptLanding(fighter_gobj)   \
(                                                      \
    (func_ovl3_80151098(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80151160(fighter_gobj) != FALSE) ||     \
    (func_ovl3_801511E0(fighter_gobj) != FALSE) ||     \
    (ftCommon_Catch_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (ftCommon_AttackS4_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (ftCommon_AttackHi4_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (ftCommon_AttackLw4_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (ftCommon_AttackS3_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (ftCommon_AttackHi3_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (ftCommon_AttackLw3_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (ftCommon_Attack1_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80148D0C(fighter_gobj) != FALSE) ||     \
    (ftCommon_Appeal_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8013F4D0(fighter_gobj) != FALSE) ||     \
    (ftCommon_Dash_CheckInterruptCommon(fighter_gobj) != FALSE) ||     \
    (func_ovl3_80141EA4(fighter_gobj) != FALSE) ||     \
    (ftCommon_Dokan_CheckEnter(fighter_gobj) != FALSE)        \
)                                                      \

void func_ovl3_80142B70(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fighter_gobj->anim_frame < FTCOMMON_LANDING_INTERRUPT_BEGIN) && (fp->status_vars.common.landing.is_allow_interrupt != FALSE) && !ftStatus_CheckInterruptLanding(fighter_gobj))
    {
        if ((fighter_gobj->anim_frame >= FTCOMMON_LANDING_INTERRUPT_BEGIN) && (fighter_gobj->anim_frame < (FTCOMMON_LANDING_INTERRUPT_BEGIN + DObjGetStruct(fighter_gobj)->unk_dobj_0x78)))
        {
            if (func_ovl3_80143354(fighter_gobj) != FALSE) return;
        }
        else if (func_ovl3_8014310C(fighter_gobj) != FALSE) return;

        if (func_ovl3_8013EA04(fighter_gobj) == FALSE)
        {
            func_ovl3_8013E648(fighter_gobj);
        }
    }
}

void func_ovl3_80142D44(GObj *fighter_gobj, s32 status_id, bool32 is_allow_interrupt, f32 anim_speed)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, status_id, 0.0F, anim_speed, 0U);

    fp->status_vars.common.landing.is_allow_interrupt = is_allow_interrupt;
}

void func_ovl3_80142D9C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->is_fast_fall) && (fp->phys_info.vel_air.y <= -fp->attributes->fast_fall_speed))
    {
        func_ovl3_80142D44(fighter_gobj, ftStatus_Common_LandingHeavy, TRUE, FTCOMMON_LANDING_HEAVY_ANIM_SPEED);
    }
    else func_ovl3_80142D44(fighter_gobj, ftStatus_Common_LandingLight, TRUE, FTCOMMON_LANDING_LIGHT_ANIM_SPEED);
}

void func_ovl3_80142E10(GObj *fighter_gobj, f32 anim_speed)
{
    func_ovl3_80142D44(fighter_gobj, ftStatus_Common_LandingAirX, FALSE, anim_speed);
}

void func_ovl3_80142E3C(GObj *fighter_gobj, bool32 is_allow_interrupt, f32 anim_speed)
{
    func_ovl3_80142D44(fighter_gobj, ftStatus_Common_LandingFallSpecial, is_allow_interrupt, anim_speed);
}

