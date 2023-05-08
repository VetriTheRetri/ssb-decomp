#include "ftness.h"

// PK Fire (SpecialN/SpecialAirN)

// 0x80153950
void ftNess_ItemSpawn_PKFire(GObj *fighter_gobj) // PK Fire setup
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

        func_ovl2_800EDF24(fp->joint[FTNESS_PK_FIRE_SPAWN_JOINT], &pos);

        pos.x += FTNESS_PK_FIRE_SPAWN_OFF_X * (f32)fp->lr;
        pos.y += FTNESS_PK_FIRE_SPAWN_OFF_Y;
        pos.z = 0.0F;

        if (fp->ground_or_air == air)
        {
            vel.z = 0.0F;
            angle = FTNESS_PK_FIRE_SPARK_ANGLE_AIR;
            vel.x = cosf(FTNESS_PK_FIRE_SPARK_ANGLE_AIR) * FTNESS_PK_FIRE_SPARK_VEL_AIR * (f32)fp->lr;
            vel.y = __sinf(FTNESS_PK_FIRE_SPARK_ANGLE_AIR) * FTNESS_PK_FIRE_SPARK_VEL_AIR;
        }
        else
        {
            vel.z = 0.0F;
            angle = FTNESS_PK_FIRE_SPARK_ANGLE_GROUND;
            vel.x = cosf(FTNESS_PK_FIRE_SPARK_ANGLE_GROUND) * FTNESS_PK_FIRE_SPARK_VEL_GROUND * (f32)fp->lr;
            vel.y = __sinf(FTNESS_PK_FIRE_SPARK_ANGLE_GROUND) * FTNESS_PK_FIRE_SPARK_VEL_GROUND;
        }

        func_ovl3_8016AC78(fighter_gobj, &pos, &vel, angle); // Spawn PK Fire
    }
}

// 0x80153AC0
void ftNess_SpecialN_MapCollide(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, ftNess_SpecialAirN_SwitchStatusAir);
}

// 0x80153AE4
void ftNess_SpecialAirN_MapCollide(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, ftNess_SpecialN_SwitchStatusGround);
}

// 0x80153B08
void ftNess_SpecialN_SwitchStatusGround(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);

    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x96U); // Action State Change

    fp->cb_accessory = ftNess_ItemSpawn_PKFire;
}

// 0x80153B5C
void ftNess_SpecialAirN_SwitchStatusAir(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);

    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x96U); // Action State Change

    func_ovl2_800D8EB8(fp);

    fp->cb_accessory = ftNess_ItemSpawn_PKFire;
}

// 0x80153BB8
void ftNess_SpecialN_SetStatusFlags(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = FALSE;
    fp->cb_accessory = ftNess_ItemSpawn_PKFire;
}

// 0x80153BD0
void ftNess_SpecialN_ProcStatus(GObj *fighter_gobj) // Aerial PK Fire collision callback
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialN, 0.0F, 1.0F, 0);
    ftAnim_Update(fighter_gobj);
    ftNess_SpecialN_SetStatusFlags(fighter_gobj);
}

// 0x80153C10
void ftNess_SpecialAirN_ProcStatus(GObj *fighter_gobj) // Grounded PK Fire collision callback
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirN, 0.0F, 1.0F, 0);
    ftAnim_Update(fighter_gobj);
    ftNess_SpecialN_SetStatusFlags(fighter_gobj);
}