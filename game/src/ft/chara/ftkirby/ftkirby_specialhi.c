#include "ftkirby.h"

void func_ovl3_80160BB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != 0)
    {
        switch (fp->cmd_flags.flag1)
        {
        case 1:

            if (fp->x18F_flag_b3 != FALSE)
            {
                func_ovl2_800E9C3C(fighter_gobj);
                fp->cmd_flags.flag1 = 0;
            }
            break;

        default:

            while (TRUE)
            {
                fatal_printf("gcFighterSpecialHiEffectKirby : Error  Unknown value %d \n", fp->cmd_flags.flag1);
                scnmgr_crash_print_gobj_state();
            }
        }
    }
    switch (fp->cmd_flags.flag2)
    {
    case 0:

        if (fp->x18F_flag_b3 != FALSE)
        {
            func_ovl2_800E9C3C(fighter_gobj);
            fp->cmd_flags.flag2 = 0;
        }
        break;

    case 2:

        if (func_ovl2_80102508(fighter_gobj) != FALSE)
        {
            fp->x18F_flag_b3 = TRUE;
            fp->cmd_flags.flag2 = 0;
        }
        break;

    case 3:

        if (func_ovl2_80102418(fighter_gobj) != FALSE)
        {
            fp->x18F_flag_b3 = TRUE;
            fp->cmd_flags.flag2 = 0;
        }
        break;

    case 4:

        if (func_ovl2_80102490(fighter_gobj) != FALSE)
        {
            fp->x18F_flag_b3 = TRUE;
            fp->cmd_flags.flag2 = 0;
        }
        break;

    case 5:

        if (func_ovl2_80102560(fighter_gobj) != FALSE)
        {
            fp->x18F_flag_b3 = TRUE;
            fp->cmd_flags.flag2 = 0;
        }
        break;

    default:

        while (TRUE)
        {
            fatal_printf("gcFighterSpecialHiEffectKirby : Error  Unknown value %d \n", fp->cmd_flags.flag2);
            scnmgr_crash_print_gobj_state();
        }
    }
}

void func_ovl3_80160D1C(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_801612D8);
}

void func_ovl3_80160D40(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    if (fp->cmd_flags.flag0 != 0)
    {
        fp->cmd_flags.flag0 = 0;

        pos.x = 0.0F;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTKIRBY_FINALCUTTER_BEAM_SPAWN_JOINT], &pos);

#ifdef NON_MATCHING

        pos.x = (fp->lr == RIGHT) ? pos.x + FTKIRBY_FINALCUTTER_OFF_X : pos.x - FTKIRBY_FINALCUTTER_OFF_X;

#else

        if (fp->lr == RIGHT) pos.x += FTKIRBY_FINALCUTTER_OFF_X; // Ternary doesn't match here, only if/else :(

        else pos.x -= FTKIRBY_FINALCUTTER_OFF_X;

#endif

        func_ovl3_8016BE8C(fighter_gobj, &pos);
    }
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8013E1C8);
}

void func_ovl3_80160DF0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = fp->attributes;

    func_ovl3_80160BB0(fighter_gobj);
    jtgt_ovl2_800D9414(fighter_gobj);

    if (func_ovl2_800D8FA8(fp, common_attrs) == FALSE)
    {
        func_ovl2_800D8FC8(fp, 8, common_attrs->aerial_acceleration * FTKIRBY_FINALCUTTER_AIR_ACCEL_MUL, common_attrs->aerial_speed_max_x);
        func_ovl2_800D9074(fp, common_attrs);
    }
}

void func_ovl3_80160E70(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = fp->attributes;

    func_ovl3_80160BB0(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        func_ovl2_800D8C14(fighter_gobj);
    }

    else
    {
        jtgt_ovl2_800D9414(fighter_gobj);

        if (func_ovl2_800D8FA8(fp, common_attrs) == FALSE)
        {
            func_ovl2_800D8FC8(fp, 8, common_attrs->aerial_acceleration * FTKIRBY_FINALCUTTER_AIR_ACCEL_MUL, common_attrs->aerial_speed_max_x);
            func_ovl2_800D9074(fp, common_attrs);
        }
    }
}

void func_ovl3_80160F10(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = fp->attributes;
    f32 temp_scale;

    func_ovl3_80160BB0(fighter_gobj);

    fp->joint[0]->scale.z = 0.8F;

    temp_scale = fp->joint[0]->scale.z;

    fp->joint[0]->scale.y = temp_scale;

    fp->joint[0]->scale.x = temp_scale;

    jtgt_ovl2_800D9414(fighter_gobj);

    fp->joint[0]->scale.z = 1.0F;

    temp_scale = fp->joint[0]->scale.z;

    fp->joint[0]->scale.y = temp_scale;

    fp->joint[0]->scale.x = temp_scale;

    if (func_ovl2_800D8FA8(fp, common_attrs) == FALSE)
    {
        func_ovl2_800D8FC8(fp, 8, common_attrs->aerial_acceleration * FTKIRBY_FINALCUTTER_AIR_ACCEL_MUL, common_attrs->aerial_speed_max_x);
        func_ovl2_800D9074(fp, common_attrs);
    }
}

void func_ovl3_80160FD8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = fp->attributes;

    func_ovl3_80160BB0(fighter_gobj);

    if (func_ovl2_800D8FA8(fp, common_attrs) == FALSE)
    {
        func_ovl2_800D8FC8(fp, 8, common_attrs->aerial_acceleration * FTKIRBY_FINALCUTTER_AIR_ACCEL_MUL, common_attrs->aerial_speed_max_x);
        func_ovl2_800D9074(fp, common_attrs);
    }
}

void func_ovl3_8016104C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        if (func_ovl2_800DDE50(fighter_gobj) == FALSE)
        {
            fp->ground_or_air = air;
        }
    }
    else
    {
        if (func_ovl2_800DE87C(fighter_gobj) != 0)
        {
            if (fp->coll_data.coll_type & 0x3000)
            {
                func_ovl3_80144C24(fighter_gobj);

            }
            else if ((fp->coll_data.coll_type & MPCOLL_MASK_GROUND) && (fp->phys_info.vel_normal.y < 0.0F))
            {
                func_ovl2_800DEE98(fp);
                func_ovl3_80161210(fighter_gobj);
            }
        }
    }
}

void func_ovl3_80161194(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag2 = 0;
    fp->cmd_flags.flag1 = 0;
    fp->cmd_flags.flag0 = 0;
}

void jtgt_ovl3_801611A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_80161194;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialHi, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}

void func_ovl3_80161210(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialHiLanding, 0.0F, 1.0F, 4U);
    func_ovl2_800E0830(fighter_gobj);

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}

void jtgt_ovl3_801611A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_status = func_ovl3_80161194;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialAirHi, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;
}

void func_ovl3_801612D8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 vel_y_bak = fp->phys_info.vel_normal.y;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_SpecialHiFall, 0.0F, 1.0F, 4U);
    func_ovl2_800E0830(fighter_gobj);

    fp->cb_hitlag_start = func_ovl2_800E9C8C;
    fp->cb_hitlag_end = func_ovl2_800E9CC4;

    fp->jumps_used = fp->attributes->jumps_max;

    fp->phys_info.vel_normal.y = vel_y_bak;
}