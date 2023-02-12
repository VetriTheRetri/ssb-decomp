#include <game/src/ft/chara/ftness/ftness.h>

#define HALF_PI32 1.5707964F
#define PI32 3.1415927F
#define DOUBLE_PI32 6.2831855F

// PK Fire (SpecialN/SpecialAirN)

void func_ovl3_80153950(GObj *fighter_gobj) // PK Fire setup
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f vel;
    f32 angle;

    if (fp->cmd_flags.flag0 != FALSE) // Check if flag to summon PK Fire is true
    {
        fp->cmd_flags.flag0 = FALSE; // Revert to 0 if PK Fire is summoned, so it doesn't repeat on every frame of the move

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

void func_ovl3_80153AC0(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80153B08);
}

void func_ovl3_80153AE4(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80153B08);
}

void func_ovl3_80153B08(GObj *fighter_gobj) // Grounded PK Fire Action State callback
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Ness_SpecialN, fighter_gobj->anim_frame, 1.0F, 0x96U); // Action State Change

    fp->cb_accessory = func_ovl3_80153950;
}

void func_ovl3_80153B5C(GObj *fighter_gobj) // Aerial PK Fire Action State callback
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Ness_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 0x96U); // Action State Change

    func_ovl2_800D8EB8(fp);

    fp->cb_accessory = func_ovl3_80153950;
}

void func_ovl3_80153BB8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag0 = FALSE;
    fp->cb_accessory = func_ovl3_80153950;
}

void jtgt_ovl3_80153BD0(GObj *fighter_gobj) // Aerial PK Fire collision callback
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Ness_SpecialN, 0.0F, 1.0F, 0);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80153BB8(fighter_gobj);
}

void jtgt_ovl3_80153C10(GObj *fighter_gobj) // Grounded PK Fire collision callback
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Ness_SpecialAirN, 0.0F, 1.0F, 0);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80153BB8(fighter_gobj);
}