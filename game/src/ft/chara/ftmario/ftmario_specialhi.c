#include <game/src/ft/chara/ftmario/ftmario.h>

void func_ovl3_801560A0(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, FTMARIO_SUPERJUMP_AIR_DRIFT, TRUE, FALSE, TRUE, FTMARIO_SUPERJUMP_LANDING_LAG, FALSE);
    }
}

void func_ovl3_801560F4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 rot_z;
    f32 stick_rot;
    f32 joint_rot;
    s32 stick_x;

    if (fp->command_vars.flags.flag1 == FALSE)
    {
        stick_x = ABS(fp->input.stick_range.x);

        if (stick_x >= (FTMARIO_SUPERJUMP_TURN_STICK_THRESHOLD + 1))
        {
            stick_x = (fp->input.stick_range.x > 0) ? FTMARIO_SUPERJUMP_TURN_STICK_THRESHOLD : -FTMARIO_SUPERJUMP_TURN_STICK_THRESHOLD;

            rot_z = (f32)((fp->input.stick_range.x - stick_x) * FTMARIO_SUPERJUMP_AIR_DRIFT);

            rot_z = -(((f32)rot_z * PI32) / 180.0F);

            stick_rot = ABSF(rot_z);

            joint_rot = ABSF(fp->joint[1]->rotate.z);

            if (joint_rot < stick_rot)
            {
                fp->joint[1]->rotate.z = rot_z;
            }
        }
    }

    if (fp->command_vars.flags.flag2 != FALSE)
    {
        fp->command_vars.flags.flag2 = FALSE;

        stick_x = ABS(fp->input.stick_range.x);

        if (stick_x >= 21)
        {
            func_ovl2_800E8044(fp);

            fp->joint[0]->rotate.y = ((f32)fp->lr * HALF_PI32);
        }
    }
}

void func_ovl3_80156240(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->status_vars.mario.specialhi.is_air_bool == FALSE)
    {
        if (fp->ground_or_air == air)
        {
            func_ovl2_800D93E4(fighter_gobj);
            return;
        }

        func_ovl2_800D8C14(fighter_gobj);
        return;
    }

    if (fp->command_vars.flags.flag1 != FALSE)
    {
        func_ovl2_800D93E4(fighter_gobj);

        fp->phys_info.vel_air.x *= 0.95F;
        fp->phys_info.vel_air.y *= 0.95F;
        fp->phys_info.vel_air.z *= 0.95F;
        return;
    }

    func_ovl2_800D8D68(fp, 0.5F, attributes->fall_speed_max);

    if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
    {
        func_ovl2_800D9074(fp, attributes);
    }
}

bool32 func_ovl3_80156320(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    if (((fp->coll_data.clip_flag & 0x4000) == FALSE) || (fp->input.stick_range.y >= FTMARIO_SUPERJUMP_STICK_Y_UNK))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80156358(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        if ((fp->command_vars.flags.flag1 == FALSE) || ((fp->phys_info.vel_air.y >= 0.0F)))
        {
            func_ovl2_800DE724(fighter_gobj);
        }

        else if (func_ovl2_800DE798(fighter_gobj, func_ovl3_80156320) != FALSE)
        {
            if (fp->coll_data.coll_type & 0x3000)
            {
                func_ovl3_80144C24(fighter_gobj);
            }
            else func_ovl3_80142E3C(fighter_gobj, NULL, FTMARIO_SUPERJUMP_LANDING_LAG);
        }
    }
    else
    {
        func_ovl2_800DDF44(fighter_gobj);
    }
}

void func_ovl3_80156418(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag2 = FALSE;
    fp->command_vars.flags.flag1 = FALSE;
}

void jtgt_ovl3_80156428(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80156418(fighter_gobj);

    fp->status_vars.mario.specialhi.is_air_bool = FALSE;

    ftStatus_Update(fighter_gobj, ftStatus_Mario_SpecialHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

void jtgt_ovl3_80156478(GObj* fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80156418(fighter_gobj);

    fp->status_vars.mario.specialhi.is_air_bool = TRUE;

    fp->phys_info.vel_air.y = 0.0F;
    fp->phys_info.vel_air.x /= 1.5F;

    ftStatus_Update(fighter_gobj, ftStatus_Mario_SpecialAirHi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}