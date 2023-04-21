#include <game/src/ft/chara/ftkirby/ftkirby.h>

void func_ovl3_801536C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f vel;

    if (fp->command_vars.flags.flag0 != 0)
    {
        fp->command_vars.flags.flag0 = 0;

        pos.x = 0.0F;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTKIRBY_COPYPIKACHU_THUNDERJOLT_SPAWN_JOINT], &pos);

        pos.x += FTKIRBY_COPYPIKACHU_THUNDERJOLT_SPAWN_OFF_X * (f32)fp->lr;
        pos.y += FTKIRBY_COPYPIKACHU_THUNDERJOLT_SPAWN_OFF_Y;

        vel.x = cosf(FTKIRBY_COPYPIKACHU_THUNDERJOLT_SPAWN_ANGLE) * FTKIRBY_COPYPIKACHU_THUNDERJOLT_VEL * (f32)fp->lr;
        vel.y = __sinf(FTKIRBY_COPYPIKACHU_THUNDERJOLT_SPAWN_ANGLE) * FTKIRBY_COPYPIKACHU_THUNDERJOLT_VEL;
        vel.z = 0.0F;

        func_ovl3_801695E4(fighter_gobj, &pos, &vel);
        func_ovl2_800E9814(fighter_gobj, FTKIRBY_COPYPIKACHU_THUNDERJOLT_COLANIM_ID, 0);
    }
}

void func_ovl3_801537B8(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80153854);
}

void func_ovl3_801537DC(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80153800);
}

void func_ovl3_80153800(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCollision_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyPikachu_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x96U);

    fp->cb_accessory = func_ovl3_801536C0;
}

void func_ovl3_80153854(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyPikachu_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x96U);
    func_ovl2_800D8EB8(fp);

    fp->cb_accessory = func_ovl3_801536C0;
}

void func_ovl3_801538B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = 0;

    fp->cb_accessory = func_ovl3_801536C0;
}

void jtgt_ovl3_801538C8(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyPikachu_SpecialN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801538B0(fighter_gobj);
}

void jtgt_ovl3_80153908(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyPikachu_SpecialAirN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801538B0(fighter_gobj);
}
