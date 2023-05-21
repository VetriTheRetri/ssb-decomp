#include "ftmasterhand.h"

void func_ovl3_8015A0C0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80159040);
}

void func_ovl3_8015A0E4(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    jtgt_ovl2_800D9414(fighter_gobj);

    fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.masterhand.drill.follow_timer--;

    if (fp->status_vars.masterhand.drill.follow_timer == 0) // Wait until timer reaches 0 to switch physics?
    {
        fp->proc_physics = func_ovl3_8015A138;
        fp->status_vars.masterhand.drill.follow_timer = 39;
    }
}

void func_ovl3_8015A138(GObj *fighter_gobj)
{
    Fighter_Struct *fp;
    f32 dist_x;

    jtgt_ovl2_800D9414(fighter_gobj);

    fp = FighterGetStruct(fighter_gobj);

    dist_x = DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.x - DObjGetStruct(fighter_gobj)->translate.x;

    if (ABSF(dist_x) > 30.0F)
    {
        fp->phys_info.vel_air.x = (dist_x > 0.0F) ? 30.0F : -30.0F;
    }
    else
    {
        fp->phys_info.vel_air.x = dist_x;
    }
    fp->status_vars.masterhand.drill.follow_timer--;

    if (fp->status_vars.masterhand.drill.follow_timer == 0)
    {
        fp->phys_info.vel_air.x = 0.0F;
        fp->proc_physics = jtgt_ovl2_800D9414;
    }
}

void func_ovl3_8015A204(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f *translate = &DObjGetStruct(fighter_gobj)->translate;

    if (fp->status_vars.masterhand.drill.pos_x2 < translate->x)
    {
        translate->x = fp->status_vars.masterhand.drill.pos_x2;
    }
    else if (translate->x < fp->status_vars.masterhand.drill.pos_x1)
    {
        translate->x = fp->status_vars.masterhand.drill.pos_x1;
    }
    func_ovl2_800DE348(fighter_gobj);
}

void func_ovl3_8015A268(GObj *fighter_gobj)
{
    Fighter_Struct *fp;
    Vec3f pos;

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Drill, 0.0F, 1.0F, 0U);
    func_ovl3_80157F90(fighter_gobj);

    fp = fighter_gobj->user_data;

    func_ovl2_800F4428(fp->coll_data.ground_line_id, &pos);

    fp->status_vars.masterhand.drill.pos_x1 = pos.x;

    func_ovl2_800F4408(fp->coll_data.ground_line_id, &pos);

    fp->status_vars.masterhand.drill.pos_x2 = pos.x;

    fp->status_vars.masterhand.drill.follow_timer = 61;
}
