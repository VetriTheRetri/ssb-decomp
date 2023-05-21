#include <game/src/ft/chara/ftkirby/ftkirby.h>

void func_ovl3_80155B40(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f vel;
    f32 angle;

    if (fp->command_vars.flags.flag0 != FALSE) // Check if flag to summon PK Fire is true
    {
        fp->command_vars.flags.flag0 = FALSE; // Revert to 0 if PK Fire is summoned, so it doesn't repeat on every frame of the move

        pos.x = 0.0F;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTKIRBY_COPYNESS_PK_FIRE_SPAWN_JOINT], &pos);

        pos.x += FTKIRBY_COPYNESS_PK_FIRE_SPAWN_OFF_X * (f32)fp->lr;
        pos.y += FTKIRBY_COPYNESS_PK_FIRE_SPAWN_OFF_Y;

        if (fp->ground_or_air == air)
        {
            vel.z = 0.0F;
            angle = FTKIRBY_COPYNESS_PK_FIRE_SPARK_ANGLE_AIR;
            vel.x = cosf(FTKIRBY_COPYNESS_PK_FIRE_SPARK_ANGLE_AIR) * FTKIRBY_COPYNESS_PK_FIRE_SPARK_VEL_AIR * (f32)fp->lr;
            vel.y = __sinf(FTKIRBY_COPYNESS_PK_FIRE_SPARK_ANGLE_AIR) * FTKIRBY_COPYNESS_PK_FIRE_SPARK_VEL_AIR;
        }
        else
        {
            vel.z = 0.0F;
            angle = FTKIRBY_COPYNESS_PK_FIRE_SPARK_ANGLE_GROUND;
            vel.x = cosf(FTKIRBY_COPYNESS_PK_FIRE_SPARK_ANGLE_GROUND) * FTKIRBY_COPYNESS_PK_FIRE_SPARK_VEL_GROUND * (f32)fp->lr;
            vel.y = __sinf(FTKIRBY_COPYNESS_PK_FIRE_SPARK_ANGLE_GROUND) * FTKIRBY_COPYNESS_PK_FIRE_SPARK_VEL_GROUND;
        }

        func_ovl3_8016AC78(fighter_gobj, &pos, &vel, angle); // Spawn PK Fire
    }
}

void func_ovl3_80155CAC(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80155D48);
}

void func_ovl3_80155CD0(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80155CF4);
}

void func_ovl3_80155CF4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyNess_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x96U);

    fp->proc_accessory = func_ovl3_80155B40;
}

void func_ovl3_80155D48(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyNess_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x96U);
    func_ovl2_800D8EB8(fp);

    fp->proc_accessory = func_ovl3_80155B40;
}

void func_ovl3_80155DA4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = 0;

    fp->proc_accessory = func_ovl3_80155B40;
}

void jtgt_ovl3_80155DBC(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyNess_SpecialN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80155DA4(fighter_gobj);
}

void jtgt_ovl3_80155DFC(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopyNess_SpecialAirN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80155DA4(fighter_gobj);
}
