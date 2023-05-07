#include "ftyoshi.h"

void func_ovl3_8015EDC0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8015F0A8);
}

void func_ovl3_8015EDE4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    if (fp->command_vars.flags.flag0 != 0)
    {
        fp->command_vars.flags.flag0 = 0;

        pos.x = 0.0F;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTYOSHI_YOSHIBOMB_STAR_SPAWN_JOINT], &pos);
        func_ovl3_8016C954(fighter_gobj, &pos);
    }
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8013E1C8);
}

void func_ovl3_8015EE4C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800D8FA8(fp, fp->attributes) == FALSE)
    {
        func_ovl2_800D9074(fp, fp->attributes);
    }
}

void func_ovl3_8015EE84(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->command_vars.flags.flag1 != 0U) && (fp->phys_info.vel_air.y <= 0.0F))
    {
        if (func_ovl2_800DE87C(fighter_gobj) != FALSE)
        {
            if (fp->coll_data.coll_type & MPCOLL_MASK_GROUND)
            {
                ftCollision_SetGround(fp);
                ftStatus_Update(fighter_gobj, ftStatus_Yoshi_SpecialLwLanding, 0.0F, 1.0F, 0U);
            }
            else if (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL)
            {
                func_ovl3_80144C24(fighter_gobj);
            }
        }
    }
    else if ((func_ovl2_800DE8B0(fighter_gobj) != FALSE) && (fp->coll_data.coll_mask & MPCOLL_MASK_CEILHEAVY))
    {
        func_ovl3_8015F0A8(fighter_gobj);
    }
}

void func_ovl3_8015EF5C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE87C(fighter_gobj) != FALSE)
    {
        if (fp->coll_data.coll_type & MPCOLL_MASK_GROUND)
        {
            ftCollision_SetGround(fp);
            ftStatus_Update(fighter_gobj, ftStatus_Yoshi_SpecialLwLanding, 0.0F, 1.0F, 0U);
        }

        else if (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL)
        {
            func_ovl3_80144C24(fighter_gobj);
        }
    }
}

void func_ovl3_8015EFD4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = 0;
    fp->command_vars.flags.flag1 = 0;
}

void jtgt_ovl3_8015EFE4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_8015EFD4;

    func_ovl2_800DEEC8(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Yoshi_SpecialLwStart, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->jumps_used = fp->attributes->jumps_max;
}

void jtgt_ovl3_8015F04C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_8015EFD4;

    ftStatus_Update(fighter_gobj, ftStatus_Yoshi_SpecialAirLwStart, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->jumps_used = fp->attributes->jumps_max;
}

void func_ovl3_8015F0A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 vel_y_bak;

    if (ABSF(fp->phys_info.vel_air.x) > FTYOSHI_YOSHIBOMB_VEL_X_CLAMP)
    {
        fp->phys_info.vel_air.x = (f32)(TERN_VEL_LR(fp->phys_info.vel_air.x) * FTYOSHI_YOSHIBOMB_VEL_X_CLAMP);
    }

    vel_y_bak = fp->phys_info.vel_air.y;

    ftStatus_Update(fighter_gobj, ftStatus_Yoshi_SpecialAirLwLoop, fighter_gobj->anim_frame, 0, 1U);
    ftAnim_Update(fighter_gobj);

    fp->phys_info.vel_air.y = vel_y_bak;

    if (vel_y_bak > FTYOSHI_YOSHIBOMB_VEL_Y_CLAMP)
    {
        fp->phys_info.vel_air.y = FTYOSHI_YOSHIBOMB_VEL_Y_CLAMP;
    }
}