#include "fighter.h"

void func_ovl3_8014ADB0(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *interact_gobj;
    Fighter_Struct *interact_fp;
    Vec3f pos;

    if (this_fp->x192_flag_b3)
    {
        interact_gobj = this_fp->catch_gobj;
    }
    else interact_gobj = this_fp->capture_gobj;

    interact_fp = FighterGetStruct(interact_gobj);

    if ((this_fp->status_info.status_id >= ftStatus_Common_ThrownDonkeyF) && (this_fp->status_info.status_id <= ftStatus_Common_ThrownFoxB))
    {
        pos.x = pos.y = pos.z = 0.0F;

        func_ovl2_800EDF24(this_fp->joint[4], &pos);

        pos.y -= 300.0F;

        DObjGetStruct(fighter_gobj)->translate = pos;
    }
    func_ovl2_800DF014(fighter_gobj, &DObjGetStruct(interact_gobj)->translate, &interact_fp->coll_data);

    if ((this_fp->ground_or_air == ground) && ((this_fp->coll_data.ground_line_id == -1) || (this_fp->coll_data.unk_0x78 != 0.0F)))
    {
        func_ovl2_800DEEC8(this_fp);
    }
}

void func_ovl3_8014AECC(GObj *fighter_gobj, GObj *interact_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *interact_fp = FighterGetStruct(interact_gobj);

    if (this_fp->x192_flag_b3)
    {
        func_ovl3_8014ADB0(fighter_gobj);
    }
    else func_ovl3_8014ADB0(interact_gobj);

    interact_fp->capture_gobj = NULL;
    this_fp->catch_gobj = NULL;
}

void func_ovl3_8014AF2C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *interact_gobj = fp->catch_gobj;

    if (interact_gobj != NULL)
    {
        func_ovl3_8014AECC(fighter_gobj, interact_gobj);

        goto next;
    }
    else interact_gobj = fp->capture_gobj;

    if (interact_gobj != NULL)
    {
        func_ovl3_8014AECC(interact_gobj, fighter_gobj);

    next:
        func_ovl2_800DEE54(fighter_gobj);
        func_ovl2_800DEE54(interact_gobj);
    }
}

static s32 D_ovl3_8018CF80; // Static (.bss)

void func_ovl3_8014AF98(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E80C4(fp, fp->capture_gobj);

    fp->status_vars.common.damage.unk_index = D_ovl3_8018CF80;
}