#include "fighter.h"

#define ftStatus_CheckInterruptOttotto(fighter_gobj)\
(                                                   \
    (func_ovl3_80151098(fighter_gobj) != FALSE) ||  \
    (func_ovl3_80151160(fighter_gobj) != FALSE) ||  \
    (func_ovl3_801511E0(fighter_gobj) != FALSE) ||  \
    (ftCommon_Catch_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (ftCommon_AttackS4_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (ftCommon_AttackHi4_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (ftCommon_AttackLw4_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (ftCommon_AttackS3_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (ftCommon_AttackHi3_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (ftCommon_AttackLw3_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (ftCommon_Attack1_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (func_ovl3_80148D0C(fighter_gobj) != FALSE) ||  \
    (ftCommon_Appeal_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (func_ovl3_8013F4D0(fighter_gobj) != FALSE) ||  \
    (ftCommon_Dash_CheckInterruptCommon(fighter_gobj) != FALSE) ||  \
    (func_ovl3_80141EA4(fighter_gobj) != FALSE) ||  \
    (ftCommon_Dokan_CheckEnter(fighter_gobj) != FALSE) ||  \
    (func_ovl3_8014310C(fighter_gobj) != FALSE) ||  \
    (func_ovl3_8013EA04(fighter_gobj) != FALSE)     \
)                                                   \

void func_ovl3_80142850(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_80142AC4);
}

void func_ovl3_80142874(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!ftStatus_CheckInterruptOttotto(fighter_gobj))
    {
        if ((fp->input.pl.stick_range.x * fp->lr) >= FTCOMMON_OTTOTTO_WALK_STICK_RANGE_MIN)
        {
            func_ovl3_8013E648(fighter_gobj);
        }
    }
}

void func_ovl3_801429F4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    f32 dist_x;

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        func_ovl3_8013F9E0(fighter_gobj);
    }
    else
    {
        if (fp->lr == RIGHT)
        {
            func_ovl2_800F4408(fp->coll_data.ground_line_id, &pos);
        }
        else func_ovl2_800F4428(fp->coll_data.ground_line_id, &pos);

        if (DObjGetStruct(fighter_gobj)->translate.x < pos.x)
        {
            dist_x = -(DObjGetStruct(fighter_gobj)->translate.x - pos.x);
        }
        else dist_x = DObjGetStruct(fighter_gobj)->translate.x - pos.x;

        if (dist_x > FTCOMMON_OTTOTTO_WALK_DIST_X_MIN)
        {
            func_ovl3_8013E1C8(fighter_gobj);
        }
    }
}

void func_ovl3_80142AC4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_OttottoWait, 0.0F, 1.0F, 0U);

    fp->x192_flag_b0 = TRUE;
}

void func_ovl3_80142B08(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Ottotto, 0.0F, 1.0F, 0U);

    fp->phys_info.vel_air.z = 0.0F;
    fp->phys_info.vel_air.y = 0.0F;
    fp->phys_info.vel_air.x = 0.0F;
    fp->phys_info.vel_ground.x = 0.0F;

    fp->x192_flag_b0 = TRUE;
}
