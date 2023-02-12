#include "ftsamus.h"

void func_ovl3_8015DC40(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, FTSAMUS_SCREWATTACK_AIR_DRIFT, TRUE, TRUE, TRUE, FTSAMUS_SCREWATTACK_LANDING_LAG, FALSE);
    }
}

void func_ovl3_8015DC94(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != FALSE)
    {
        fp->cmd_flags.flag1 = FALSE;
        fp->phys_info.vel_normal.x = (f32)fp->lr * FTSAMUS_SCREWATTACK_VEL_X_BASE;
    }
    if (fp->ground_or_air == air)
    {
        jtgt_ovl2_800D9414(fighter_gobj);
        func_ovl2_800D8FC8(fp, 0, 0.5F, 20.0F);
    }
    else func_ovl2_800D8BB4(fighter_gobj);
}

bool32 func_ovl3_8015DD20(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->coll_data.clip_flag & 0x4000) == FALSE) || (fp->input.stick_range.y >= -44))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8015DD58(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        if (fp->phys_info.vel_normal.y >= 0.0F)
        {
            func_ovl2_800DE724(fighter_gobj);
        }
        else if (func_ovl2_800DE798(fighter_gobj, func_ovl3_8015DD20) != FALSE)
        {
            if (fp->coll_data.coll_type & 0x3000)
            {
                func_ovl3_80144C24(fighter_gobj);
            }
            else func_ovl3_80142E3C(fighter_gobj, 0, FTSAMUS_SCREWATTACK_LANDING_LAG);
        }
    }
    else func_ovl2_800DDF44(fighter_gobj);
}

void jtgt_ovl3_8015DE0C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Samus_SpecialHi, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    fp->cmd_flags.flag1 = FALSE;
}

void func_ovl3_8015DE54(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800D8E50(fp, fp->attributes);
    func_ovl2_800D8FC8(fp, 0, 0.5F, 20.0F);
}

void jtgt_ovl3_8015DE90(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Samus_SpecialAirHi, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    fp->jumps_used = fp->attributes->jumps_max;
    fp->phys_info.vel_normal.y = FTSAMUS_SCREWATTACK_VEL_Y_BASE;

    func_ovl2_800D8E78(fp, 20.0F);
}