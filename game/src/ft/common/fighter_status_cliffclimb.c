#include "fighter.h"

// CliffClimb + CliffAttack

void func_ovl3_80144EE0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        switch (fp->status_vars.common.cliffmotion.status_id)
        {
        case 0:
            func_ovl3_801451F0(fighter_gobj);
            break;

        case 1:
            func_ovl3_801456B4(fighter_gobj);
            break;

        case 2:
            func_ovl3_8014586C(fighter_gobj);
            break;
        }
    }
}

void func_ovl3_80144F64(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        switch (fp->status_vars.common.cliffmotion.status_id)
        {
        case 3:
            func_ovl3_80145240(fighter_gobj);
            break;

        case 4:
            func_ovl3_80145704(fighter_gobj);
            break;

        case 5:
            func_ovl3_801458BC(fighter_gobj);
            break;
        }
    }
}

void func_ovl3_80144FE8(GObj *fighter_gobj, s32 status_input)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;
    s32 status_new;

    if (fp->percent_damage < FTCOMMON_CLIFF_DAMAGE_HIGH)
    {
        status_id = ftStatus_Common_CliffQuick, status_new = 0;
    }
    else status_id = ftStatus_Common_CliffSlow, status_new = 3;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->status_vars.common.cliffmotion.status_id = status_input + status_new;
    fp->status_vars.common.cliffmotion.cliff_id = fp->coll_data.cliff_id;

    fp->x190_flag_b7 = TRUE;

    fp->proc_damage = func_ovl3_80144CF8;
}

bool32 func_ovl3_80145084(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((ABS(fp->input.pl.stick_range.x) >= FTCOMMON_CLIFF_MOTION_STICK_RANGE_MIN) || (ABS(fp->input.pl.stick_range.y) >= FTCOMMON_CLIFF_MOTION_STICK_RANGE_MIN))
    {
        f32 angle = func_ovl2_800E8000(fp);

        if ((angle > 0.87266463F) || ((angle > -0.87266463F) && ((fp->input.pl.stick_range.x * fp->lr) >= 0)))
        {
            if (fp->status_vars.common.cliffmotion.status_id != 0)
            {
                func_ovl3_80144FE8(fighter_gobj, 0);

                return TRUE;
            }
            else return FALSE;
        }
        else if (fp->status_vars.common.cliffmotion.status_id != 0)
        {
            fp->cliffcatch_wait = FTCOMMON_CLIFF_CATCH_WAIT;

            func_ovl3_80144CF8(fighter_gobj);
            func_ovl3_8013F9E0(fighter_gobj);

            return TRUE;
        }
        else return FALSE;
    }
    else fp->status_vars.common.cliffmotion.status_id = 1;

    return FALSE;
}

void func_ovl3_801451A8(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_801455A0);
}

void func_ovl3_801451CC(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_801455E0);
}

void func_ovl3_801451F0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffClimbQuick1, 0.0F, 1.0F, 0U);

    fp->x190_flag_b7 = TRUE;

    fp->proc_damage = func_ovl3_80144CF8;
}

void func_ovl3_80145240(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffClimbSlow1, 0.0F, 1.0F, 0U);

    fp->x190_flag_b7 = TRUE;

    fp->proc_damage = func_ovl3_80144CF8;
}

void func_ovl3_80145290(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl2_800DEE54);
}

void func_ovl3_801452B4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f vel;
    Vec3f *translate;
    f32 y;

    if (fp->ground_or_air == ground)
    {
        func_ovl2_800D8C14(fighter_gobj);
    }
    else
    {
        translate = &DObjGetStruct(fighter_gobj)->translate;

        pos = *translate;

        func_ovl2_800D9260(fp, &vel.x, NULL, &vel.z);

        pos.x += vel.x;
        pos.z += vel.z;

        func_ovl2_800FA7B8(fp->status_vars.common.cliffmotion.cliff_id, &vel);

        pos.x += vel.x;

        if (func_ovl2_800F3DD8(fp->status_vars.common.cliffmotion.cliff_id, &pos, &y, NULL, NULL) != FALSE)
        {
            pos.y += y;

            pos.y += fp->joint[1]->translate.y;

            fp->phys_info.vel_air.x = pos.x - translate->x;
            fp->phys_info.vel_air.y = pos.y - translate->y;
            fp->phys_info.vel_air.z = pos.z - translate->z;
        }
        else func_ovl2_800D93E4(fighter_gobj);
    }
}

void func_ovl3_801453F0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        jtgt_ovl2_800DDEC4(fighter_gobj);
    }
    else if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        ftMapCollide_SetGround(fp);
    }
}

void func_ovl3_80145440(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        func_ovl2_800DDF44(fighter_gobj);
    }
    else if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        ftMapCollide_SetGround(fp);
    }
}

void func_ovl3_80145490(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Coll_Data *coll_data = &fp->coll_data;
    Vec3f *translate = &DObjGetStruct(fighter_gobj)->translate;

    if (fp->attributes->cliff_status_ground_air_id[fp->status_vars.common.cliffmotion.status_id] == ground)
    {
        ftMapCollide_SetGround(fp);
    }
    if (fp->lr == RIGHT)
    {
        func_ovl2_800F4428(coll_data->cliff_id, translate);

        translate->x += 5.0F;
    }
    else
    {
        func_ovl2_800F4408(coll_data->cliff_id, translate);

        translate->x -= 5.0F;
    }
    coll_data->ground_line_id = coll_data->cliff_id;

    func_ovl2_800F3DD8(coll_data->ground_line_id, translate, &coll_data->ground_dist, &coll_data->ground_flags, &coll_data->ground_angle);

    translate->y += coll_data->ground_dist;

    coll_data->ground_dist = 0.0F;
}

void func_ovl3_8014557C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        fp->x18F_flag_b4 = TRUE;
    }
}

void func_ovl3_801455A0(GObj *fighter_gobj)
{
    func_ovl3_80145490(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffClimbQuick2, 0.0F, 1.0F, 0U);
    func_ovl3_8014557C(fighter_gobj);
}

void func_ovl3_801455E0(GObj *fighter_gobj)
{
    func_ovl3_80145490(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffClimbSlow2, 0.0F, 1.0F, 0U);
    func_ovl3_8014557C(fighter_gobj);
}
