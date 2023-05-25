#include "fighter.h"

// CliffCatch + CliffWait

void func_ovl3_80144B30(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_80144DF4);
}

void func_ovl3_80144B54(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    DObj *topn_joint = fp->joint[0], *transn_joint = fp->joint[1];
    Vec3f vel;

    if (fp->lr == RIGHT)
    {
        func_ovl2_800F4428(fp->coll_data.cliff_id, &vel);
    }
    else func_ovl2_800F4408(fp->coll_data.cliff_id, &vel);

    topn_joint->translate.x = ((transn_joint->translate.z * fp->lr * topn_joint->scale.x) + vel.x);
    topn_joint->translate.y = ((transn_joint->translate.y * topn_joint->scale.y) + vel.y);
}

void func_ovl3_80144C1C(GObj *fighter_gobj)
{
    return;
}

void func_ovl3_80144C24(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f vel;

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffCatch, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    ftMapCollide_SetAir(fp);
    func_ovl2_800D9444(fighter_gobj);

    fp->coll_data.ground_line_id = -1;

    func_ovl3_80144B54(fighter_gobj);

    fp->x190_flag_b7 = TRUE;

    if (fp->lr == RIGHT)
    {
        func_ovl2_800F4428(fp->coll_data.cliff_id, &vel);
    }
    else func_ovl2_800F4408(fp->coll_data.cliff_id, &vel);

    func_ovl2_801016E0(&vel);

    fp->proc_damage = func_ovl3_80144CF8;

    ftCommon_SetCaptureFlags(fp, 4U);
}

void func_ovl3_80144CF8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ObjectColl *object_coll = &fp->coll_data.object_coll;
    Vec3f vel;

    if (fp->lr == RIGHT)
    {
        func_ovl2_800F4428(fp->coll_data.cliff_id, &vel);
    }
    else func_ovl2_800F4408(fp->coll_data.cliff_id, &vel);

    vel.x -= ((object_coll->width + 30.0F) * fp->lr);
    vel.y -= object_coll->center;

    func_ovl2_800DF014(fighter_gobj, &vel, &fp->coll_data);
}

void func_ovl3_80144DA4(GObj *fighter_gobj)
{
    if ((func_ovl3_80145620(fighter_gobj) == FALSE) && (func_ovl3_801457E0(fighter_gobj) == FALSE) && (func_ovl3_80145084(fighter_gobj) == FALSE))
    {
        func_ovl3_80144E84(fighter_gobj);
    }
}

void func_ovl3_80144DF4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CliffWait, 0.0F, 1.0F, 0U);

    fp->status_vars.common.cliffwait.status_id = 0;

    if (fp->percent_damage < FTCOMMON_CLIFF_DAMAGE_HIGH)
    {
        fp->status_vars.common.cliffwait.fall_wait = FTCOMMON_CLIFF_FALL_WAIT_DAMAGE_LOW;
    }
    else fp->status_vars.common.cliffwait.fall_wait = FTCOMMON_CLIFF_FALL_WAIT_DAMAGE_HIGH;

    fp->x190_flag_b7 = TRUE;

    func_ovl2_800E7F7C(fighter_gobj, 120);

    fp->proc_damage = func_ovl3_80144CF8;

    ftCommon_SetCaptureFlags(fp, 4U);
}

bool32 func_ovl3_80144E84(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.cliffwait.fall_wait--;

    if (fp->status_vars.common.cliffwait.fall_wait == 0)
    {
        fp->cliffcatch_wait = FTCOMMON_CLIFF_CATCH_WAIT;

        func_ovl3_80144CF8(fighter_gobj);
        func_ovl3_801436A0(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}