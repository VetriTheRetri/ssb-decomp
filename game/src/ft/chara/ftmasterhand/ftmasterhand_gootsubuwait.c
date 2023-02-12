#include "ftmasterhand.h"

void func_ovl3_80159BD0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    jtgt_ovl2_800D9414(fighter_gobj);

    fp->status_vars.masterhand.gootsubu.wait_timer--;

    if (fp->status_vars.masterhand.gootsubu.wait_timer == 0)
    {
        func_ovl3_80159E50(fighter_gobj);
    }
    else
    {
        f32 dist_x = JObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.x - JObjGetStruct(fighter_gobj)->translate.x;

        if (ABSF(dist_x) > 35.0F)
        {
            fp->phys_info.vel_normal.x = (dist_x > 0.0F) ? 35.0F : -35.0F;
        }
        else fp->phys_info.vel_normal.x = dist_x;
    }
}

void func_ovl3_80159CA4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f *translate = &JObjGetStruct(fighter_gobj)->translate;
    f32 var;

    if (fp->status_vars.masterhand.gootsubu.pos_x2 < translate->x)
    {
        translate->x = fp->status_vars.masterhand.gootsubu.pos_x2;
    }

    else if (translate->x < fp->status_vars.masterhand.gootsubu.pos_x1)
    {
        translate->x = fp->status_vars.masterhand.gootsubu.pos_x1;
    }

    func_ovl2_800DE348(fighter_gobj);

    var = fp->coll_data.unk_0x78 + 3000.0F;

    translate->y -= var;

    fp->coll_data.unk_0x78 = 3000.0F;
}

void func_ovl3_80159D34(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_GootsubuWait, 0.0F, 1.0F, 0U);

    fp->status_vars.masterhand.gootsubu.wait_timer = rand_u16_range(60) + 60;

    func_ovl2_800F4428(fp->coll_data.unk_0x74, &pos);

    fp->status_vars.masterhand.gootsubu.pos_x1 = pos.x;

    func_ovl2_800F4408(fp->coll_data.unk_0x74, &pos);

    fp->status_vars.masterhand.gootsubu.pos_x2 = pos.x;
}
