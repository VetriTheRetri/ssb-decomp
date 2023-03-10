#include "ftpikachu.h"

void func_ovl3_80151B50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f vel;

    if (fp->cmd_flags.flag0 != 0)
    {
        fp->cmd_flags.flag0 = 0;

        pos.x = 0.0F;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTPIKACHU_THUNDERJOLT_SPAWN_JOINT], &pos);

        vel.x = cosf(FTPIKACHU_THUNDERJOLT_SPAWN_ANGLE) * FTPIKACHU_THUNDERJOLT_VEL * (f32)fp->lr;
        vel.y = __sinf(FTPIKACHU_THUNDERJOLT_SPAWN_ANGLE) * FTPIKACHU_THUNDERJOLT_VEL;
        vel.z = 0.0F;

        func_ovl3_801695E4(fighter_gobj, &pos, &vel);
        func_ovl2_800E9814(fighter_gobj, FTPIKACHU_THUNDERJOLT_COLANIM_ID, 0);
    }
}

void func_ovl3_80151C14(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80151CB0);
}

void func_ovl3_80151C38(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80151C5C);
}

void func_ovl3_80151C5C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x96U);

    fp->cb_accessory = func_ovl3_80151B50;
}

void func_ovl3_80151CB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x96U);
    func_ovl2_800D8EB8(fp);

    fp->cb_accessory = func_ovl3_80151B50;
}

void func_ovl3_80151D0C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag0 = 0;
    fp->cb_accessory = func_ovl3_80151B50;
}

void jtgt_ovl3_80151D24(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialN, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80151D0C(fighter_gobj);
}

void jtgt_ovl3_80151D64(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirN, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80151D0C(fighter_gobj);
}
