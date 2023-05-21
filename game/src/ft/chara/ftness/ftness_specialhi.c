#include <game/src/ft/chara/ftness/ftness.h>

// PK Thunder (SpecialHi/SpecialAirHi)

void func_ovl3_80153C50(Fighter_Struct *fp)
{

    if (fp->status_vars.ness.specialhi.pk_jibaku_delay != 0) // PK Thunder timers
    {
        fp->status_vars.ness.specialhi.pk_jibaku_delay--;
    }

    if (fp->fighter_vars.ness.is_thunder_destroy & TRUE)
    {
        if (fp->status_vars.ness.specialhi.pk_thunder_end_delay != 0)
        {
            fp->status_vars.ness.specialhi.pk_thunder_end_delay--;
        }
    }
}

void func_ovl3_80153C88(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f sp1C;

    pos.x = 0.0F;
    pos.y = 0.0F;
    pos.z = 0.0F;

    func_ovl2_800EDF24(fp->joint[FTNESS_PK_THUNDER_SPAWN_JOINT], &pos);

    pos.z = 0.0F;

    sp1C.z = 0.0F;
    sp1C.y = 60.0F;
    sp1C.x = 0.0F;

    fp->status_vars.ness.specialhi.pk_thunder_gobj = func_ovl3_8016B2C4(fighter_gobj, &pos, &sp1C);
}

bool32 func_ovl3_80153CFC(GObj *fighter_gobj)
{
    f32 fighter_dobj_x;
    f32 fighter_dobj_y;
    f32 item_dobj_x;
    f32 item_dobj_y;
    f32 collide_x;
    f32 collide_y;
    GObj *pk_thunder_gobj;
    Item_Struct *ip;
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    pk_thunder_gobj = fp->status_vars.ness.specialhi.pk_thunder_gobj;

    if (fp->fighter_vars.ness.pk_thunder_timer1 != 0) return FALSE;

    if ((fp->fighter_vars.ness.is_thunder_destroy & TRUE) || (pk_thunder_gobj == NULL)) return FALSE;

    ip = ItemGetStruct(pk_thunder_gobj);

    fighter_dobj_x = DObjGetStruct(fighter_gobj)->translate.x;
    item_dobj_x = DObjGetStruct(pk_thunder_gobj)->translate.x;

    collide_x = (fighter_dobj_x < item_dobj_x) ? -(fighter_dobj_x - item_dobj_x) : (fighter_dobj_x - item_dobj_x);

    if (collide_x < FTNESS_PK_THUNDER_COLLIDE_X)
    {
        fighter_dobj_y = DObjGetStruct(fighter_gobj)->translate.y + 150.0F;
        item_dobj_y = DObjGetStruct(pk_thunder_gobj)->translate.y;

        collide_y = (fighter_dobj_y < item_dobj_y) ? -(fighter_dobj_y - item_dobj_y) : (fighter_dobj_y - item_dobj_y);

        if (collide_y < FTNESS_PK_THUNDER_COLLIDE_Y)
        {
            ip->item_vars.pk_thunder.pk_thunder_state = 2;

            fp->status_vars.ness.specialhi.pk_thunder_vel = DObjGetStruct(pk_thunder_gobj)->translate;

            return TRUE;
        }
    }
    return FALSE;
}

void func_ovl3_80153E04(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, &func_ovl3_8015435C);
}

void func_ovl3_80153E28(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, &func_ovl3_801543A0);
}

void func_ovl3_80153E4C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.ness.specialhi.pk_thunder_gravity_delay != 0) fp->status_vars.ness.specialhi.pk_thunder_gravity_delay--;

    func_ovl2_800D8BB4(fighter_gobj);
}

void func_ovl3_80153E80(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->status_vars.ness.specialhi.pk_thunder_gravity_delay != 0) fp->status_vars.ness.specialhi.pk_thunder_gravity_delay--;

    else func_ovl2_800D8D68(fp, 0.5F, attributes->fall_speed_max);

    if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
    {
        func_ovl2_800D9074(fp, attributes);
    }
}

void func_ovl3_80153EF8(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, &func_ovl3_80153F80);
}

void func_ovl3_80153F1C(GObj *fighter_gobj)
{
    func_ovl2_800DE80C(fighter_gobj, &func_ovl3_80153F40);
}

void func_ovl3_80153F40(GObj *fighter_gobj) // Ness' grounded PK Thunder Start Action State handler
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiStart, fighter_gobj->anim_frame, 1.0F, 0x92);
}

void func_ovl3_80153F80(GObj *fighter_gobj) // Ness' aerial PK Thunder Start Action State handler
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiStart, fighter_gobj->anim_frame, 1.0F, 0x92);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80153FCC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.ness.specialhi.pk_jibaku_delay = FTNESS_PK_JIBAKU_DELAY;
    fp->status_vars.ness.specialhi.pk_thunder_end_delay = FTNESS_PK_THUNDER_END_DELAY;
    fp->status_vars.ness.specialhi.pk_thunder_gravity_delay = FTNESS_PK_THUNDER_GRAVITY_DELAY;
    fp->fighter_vars.ness.is_thunder_destroy = FALSE;
    fp->fighter_vars.ness.pk_thunder_trail_id = 0;
}

void jtgt_ovl3_80153FF0(GObj *fighter_gobj)
{
    func_ovl3_80153FCC(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiStart, 0.0F, 1.0F, 0);
    ftAnim_Update(fighter_gobj);
}

void jtgt_ovl3_80154030(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80153FCC(fighter_gobj);

    fp->phys_info.vel_air.y = 0.0F;
    fp->phys_info.vel_air.x /= 2;

    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiStart, 0.0F, 1.0F, 0);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80154098(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *gobj = fp->status_vars.ness.specialhi.pk_thunder_gobj;

    if (gobj == NULL)
    {
        fp->fighter_vars.ness.is_thunder_destroy |= TRUE;
    }

    fp->fighter_vars.ness.pk_thunder_trail_id++;

    if (fp->fighter_vars.ness.pk_thunder_trail_id >= (ARRAY_COUNT(fp->fighter_vars.ness.pk_thunder_trail_x) | ARRAY_COUNT(fp->fighter_vars.ness.pk_thunder_trail_y))
    {
        fp->fighter_vars.ness.pk_thunder_trail_id = 0;
    }

    func_ovl3_80153C50(fp);
}

void func_ovl3_801540EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80154098(fighter_gobj);

    if ((fp->fighter_vars.ness.pk_jibaku_delay <= 0) &&
    (fp->fighter_vars.ness.pk_thunder_end_delay <= 0) &&
    (fp->fighter_vars.ness.is_thunder_destroy & TRUE))
    {
        func_ovl3_80154518(fighter_gobj);
    }

    else if (func_ovl3_80153CFC(fighter_gobj) != FALSE)
    {
        func_ovl3_80154DFC(fighter_gobj);
    }
}

void func_ovl3_8015416C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80154098(fighter_gobj);

    if ((fp->fighter_vars.ness.pk_jibaku_delay <= 0) &&
    (fp->fighter_vars.ness.pk_thunder_end_delay <= 0) &&
    (fp->fighter_vars.ness.is_thunder_destroy & TRUE))
    {
        func_ovl3_80154558(fighter_gobj);
    }

    else if (func_ovl3_80153CFC(fighter_gobj) != FALSE)
    {
        func_ovl3_80154F54(fighter_gobj);
    }
}

void func_ovl3_801541EC(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, &func_ovl3_801542A8);
}

void func_ovl3_80154210(GObj *fighter_gobj)
{
    func_ovl2_800DE80C(fighter_gobj, &func_ovl3_80154268);
}

void func_ovl3_80154234(GObj *fighter_gobj) // Unused
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *gobj = fp->status_vars.ness.specialhi.pk_thunder_gobj;

    if ((!(fp->fighter_vars.ness.is_thunder_destroy & TRUE)) && (gobj != NULL))
    {
        Item_Struct *ip = ItemGetStruct(gobj);

        ip->item_vars.pk_thunder.pk_thunder_state = itNessThunderStatus_Destroy;
    }
}

void func_ovl3_80154268(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiHold, fighter_gobj->anim_frame, 1.0F, 0x4897);
}

void func_ovl3_801542A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = fighter_gobj->user_data;;

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiHold, fighter_gobj->anim_frame, 1.0F, 0x4897U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_801542F4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80153C88(fighter_gobj);

    if ((fp->is_statupdate_stop_gfx == FALSE) && (func_ovl2_801029F8(fighter_gobj) != NULL))
    {
        fp->is_statupdate_stop_gfx = TRUE;
    }

    fp->jumps_used = fp->attributes->jumps_max;
}

void func_ovl3_8015435C(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiHold, 0.0F, 1.0F, 0x800U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801542F4(fighter_gobj);
}

void func_ovl3_801543A0(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiHold, 0.0F, 1.0F, 0x800U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801542F4(fighter_gobj);
}

void func_ovl3_801543E4(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, FTNESS_PK_THUNDER_FALLSPECIAL_DRIFT, FALSE, TRUE, TRUE, FTNESS_PK_THUNDER_LANDING_LAG, FALSE);
    }
}

void func_ovl3_80154438(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, &func_ovl3_801544C0);
}

void func_ovl3_8015445C(GObj *fighter_gobj)
{
    func_ovl2_800DE80C(fighter_gobj, &func_ovl3_80154480);
}

void func_ovl3_80154480(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiEnd, fighter_gobj->anim_frame, 1.0F, 0x92U);
}

void func_ovl3_801544C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiEnd, fighter_gobj->anim_frame, 1.0F, 0x92U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_8015450C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->proc_damage = NULL;
}

void func_ovl3_80154518(GObj *fighter_gobj)
{
    func_ovl3_8015450C(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiEnd, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80154558(GObj *fighter_gobj)
{
    func_ovl3_8015450C(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiEnd, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80154598(GObj *fighter_gobj, Coll_Data *coll_data)
{
    f32 tan_rwall_angle;
    f32 rotation;
    f32 tangent;
    f32 tan_lwall_angle;
    u32 coll_mask;
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    rotation = (fp->lr == RIGHT) ? fp->status_vars.ness.specialhi.pk_jibaku_vel : (PI32 - fp->status_vars.ness.specialhi.pk_jibaku_vel);

    if (DOUBLE_PI32 < rotation)
    {
        rotation -= DOUBLE_PI32;
    }

    if (coll_data->coll_mask & MPCOLL_MASK_RWALL)
    {
        tan_rwall_angle = atan2f(coll_data->rwall_angle.y, coll_data->rwall_angle.x);

        tangent = tan_rwall_angle;

        if (DOUBLE_PI32 < tan_rwall_angle)
        {
            tangent = tan_rwall_angle - DOUBLE_PI32;
        }

        if ((rotation + PI32) < tangent)
        {
            tangent += PI32;
        }
        else
        {
            tangent += HALF_PI32;
        }
    }
    if (coll_data->coll_mask & MPCOLL_MASK_LWALL)
    {
        tan_lwall_angle = atan2f(coll_data->lwall_angle.y, coll_data->lwall_angle.x);

        tangent = tan_lwall_angle;

        if (DOUBLE_PI32 < tangent)
        {
            tangent = tan_lwall_angle - DOUBLE_PI32;
        }

        tangent = ((tangent + PI32) < rotation) ? (tangent + (-PI32)) : (tangent + HALF_PI32);
    }

    vec3_get_euler_rotation(&fp->phys_info.vel_air, 4, tangent - (fp->status_vars.ness.specialhi.pk_jibaku_vel  * (f32)fp->lr));

    fp->status_vars.ness.specialhi.pk_jibaku_vel = atan2f(fp->phys_info.vel_air.y, fp->phys_info.vel_air.x * (f32)fp->lr);
}

void func_ovl3_80154758(GObj *fighter_gobj) // Joint use here, fix array later to include all joints w/ TopN 
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->joint[4]->rotate.x = (f32)((atan2f(fp->phys_info.vel_air.x, fp->phys_info.vel_air.y) * (f32)fp->lr) - HALF_PI32);

    func_ovl2_800EB528(fp->joint[4]);
}

void func_ovl3_801547B8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.ness.specialhi.pk_jibaku_anim_length--;

    if (fp->status_vars.ness.specialhi.pk_jibaku_anim_length == 0)
    {
        func_ovl3_80154518(fighter_gobj);
    }
}


void func_ovl3_801547EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.ness.specialhi.pk_jibaku_anim_length--;

    if (fp->status_vars.ness.specialhi.pk_jibaku_anim_length == 0)
    {
        func_ovl3_80154558(fighter_gobj);
    }
}

void func_ovl3_80154820(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->phys_info.vel_ground.x > 0.0F)
    {
        fp->phys_info.vel_ground.x -= 6.142857F;
    }

    jtgt_ovl2_800D8B94(fighter_gobj);
    func_ovl3_80154758(fighter_gobj);
}

void func_ovl3_80154874(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 vel_x_bak = fp->phys_info.vel_air.x;
    f32 vel_y_bak = fp->phys_info.vel_air.y;
    f32 fabs_axis;
    f32 fabs_axis_bak;

    fp->phys_info.vel_air.x -= (6.142857F * cosf(fp->status_vars.ness.specialhi.pk_jibaku_vel) * (f32)fp->lr);

    fp->phys_info.vel_air.y -= (6.142857F * __sinf(fp->status_vars.ness.specialhi.pk_jibaku_vel));

    fabs_axis = ABSF(fp->phys_info.vel_air.x);

    fabs_axis_bak = ABSF(vel_x_bak);

    if (fabs_axis_bak < fabs_axis)
    {
        fp->phys_info.vel_air.x = vel_x_bak;
    }

    fabs_axis = ABSF(fp->phys_info.vel_air.y);

    fabs_axis_bak = ABSF(vel_y_bak);

    if (fabs_axis_bak < fabs_axis)
    {
        fp->phys_info.vel_air.y = vel_y_bak;
    }

    func_ovl3_80154758(fighter_gobj);
}

bool32 func_ovl3_801549B0(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    if (!(fp->coll_data.ground_flags & 0x4000) || ((f32)fp->status_vars.ness.specialhi.pk_jibaku_anim_length <= 25.0F))
    {
        return TRUE;
    }

    else return FALSE;
}

void func_ovl3_801549FC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        if (fp->coll_data.coll_mask & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
        {
            ftMapCollide_SetAir(fp);
            func_ovl3_80154558(fighter_gobj);
        }
        else func_ovl3_80154D1C(fighter_gobj);
    }

    else if (fp->coll_data.coll_mask & (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
    {
        fp->phys_info.vel_ground.x = 0.0F;
        ftCommon_DownBounce_ApplyStatus(fighter_gobj);
    }
}

void func_ovl3_80154A8C(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);
    f32 unused;
    Vec3f pos;


    if (func_ovl2_800DE798(fighter_gobj, &func_ovl3_801549B0) != FALSE)
    {
        if (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL)
        {
            func_ovl3_80144C24(fighter_gobj);
            return;
        }
        if (FTNESS_PK_JIBAKU_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.ground_angle, &fp->phys_info.vel_air))
        {
            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;

            ftMapCollide_SetGround(fp);
            ftCommon_DownBounce_ApplyStatus(fighter_gobj);
            return;
        }
        func_ovl3_80154CBC(fighter_gobj);
        return;
    }

    pos.x = DObjGetStruct(fighter_gobj)->translate.x;
    pos.y = DObjGetStruct(fighter_gobj)->translate.y;
    pos.z = 0.0F;

    if (fp->coll_data.coll_mask & MPCOLL_MASK_CEIL)
    {
        if (FTNESS_PK_JIBAKU_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.ceil_angle, &fp->phys_info.vel_air))
        {
            pos.y += fp->coll_data.object_coll.top;
            func_ovl3_80155114(fighter_gobj, &fp->coll_data.ceil_angle, &pos);
        }
    }

    if (fp->coll_data.coll_mask & MPCOLL_MASK_RWALL)
    {

        if (FTNESS_PK_JIBAKU_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.rwall_angle, &fp->phys_info.vel_air))
        {
            pos.x += fp->coll_data.object_coll.width;
            pos.y += fp->coll_data.object_coll.center;

            func_ovl3_80155114(fighter_gobj, &fp->coll_data.rwall_angle, &pos);
        }
        else func_ovl3_80154598(fighter_gobj, &fp->coll_data);
    }

    if (fp->coll_data.coll_mask & MPCOLL_MASK_LWALL)
    {

        if (FTNESS_PK_JIBAKU_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.lwall_angle, &fp->phys_info.vel_air))
        {
            pos.x -= fp->coll_data.object_coll.width;
            pos.y += fp->coll_data.object_coll.center;

            func_ovl3_80155114(fighter_gobj, &fp->coll_data.lwall_angle, &pos);
        }
        else func_ovl3_80154598(fighter_gobj, &fp->coll_data);
    }
}

void func_ovl3_80154CBC(GObj *fighter_gobj)
{
    f32 frame_begin;

    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));

    frame_begin = fighter_gobj->anim_frame;

    if (frame_begin == 0.0F)
    {
        frame_begin = 1.0F;
    }

    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHi, frame_begin, 1.0F, 0x93U); // Change Action State to PK Thunder Blast
}

void func_ovl3_80154D1C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 frame_begin;

    ftMapCollide_SetAir(fp);

    frame_begin = fighter_gobj->anim_frame;

    if (frame_begin == 0.0F)
    {
        frame_begin = 1.0F;
    }

    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHi, frame_begin, 1.0F, 0x93U);

    fp->status_vars.ness.specialhi.pk_jibaku_vel = atan2f(fp->phys_info.vel_air.y, fp->phys_info.vel_air.x * (f32)fp->lr);

    fp->jumps_used = fp->attributes->jumps_max;
}

void func_ovl3_80154DBC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.ness.specialhi.pk_jibaku_anim_length = FTNESS_PK_JIBAKU_ANIM_LENGTH;

    func_ovl3_80154758(fighter_gobj);

    fp->proc_damage = NULL;

    fp->jumps_used = fp->attributes->jumps_max;
}

void func_ovl3_80154DFC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 angle_diff;
    s32 unused;
    Vec3f vel;

    if ((fp->coll_data.ground_flags & 0x4000)) goto block_2func;
    {
        vel.x = DObjGetStruct(fighter_gobj)->translate.x - fp->status_vars.ness.specialhi.pk_thunder_vel.x;
        vel.y = (DObjGetStruct(fighter_gobj)->translate.y + 150.0F) - fp->status_vars.ness.specialhi.pk_thunder_vel.y;
        vel.z = 0.0F;

        angle_diff = vec3f_angle_diff(&fp->coll_data.ground_angle, &vel);

        if (!(angle_diff < HALF_PI32))
        {
            if (2.3561945F < angle_diff) goto block_end;
            {
                fp->lr = (vel.x >= 0) ? RIGHT : LEFT;

                if (vel.x < 0)
                {
                    vel.x = -vel.x;
                }

                fp->phys_info.vel_ground.x = 200.0F;

                func_ovl3_80154DBC(fighter_gobj);
                ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHi, 0.0F, 1.0F, 2U);
                ftAnim_Update(fighter_gobj);
                return;
            }
        }

        ftMapCollide_SetAir(fp);
        func_ovl3_80154F54(fighter_gobj);
        return;
    }

    block_end:
    ftCommon_DownBounce_ApplyStatus(fighter_gobj);
}

void func_ovl3_80154F54(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    DObj *dobj = DObjGetStruct(fighter_gobj);
    f32 vel_x = dobj->translate.x - fp->status_vars.ness.specialhi.pk_thunder_vel.x;
    f32 vel_y = (dobj->translate.y + 150.0F) - fp->status_vars.ness.specialhi.pk_thunder_vel.y;

    fp->lr = (vel_x >= 0.0F) ? RIGHT : LEFT;

    fp->status_vars.ness.specialhi.pk_jibaku_vel  = atan2f(vel_y, ((f32)fp->lr * vel_x));

    fp->phys_info.vel_air.x = (f32)(cosf(fp->status_vars.ness.specialhi.pk_jibaku_vel ) * 200.0F * (f32)fp->lr);
    fp->phys_info.vel_air.y = (f32)(__sinf(fp->status_vars.ness.specialhi.pk_jibaku_vel ) * 200.0F);

    func_ovl3_80154DBC(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHi, 0.0F, 1.0F, 2U);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80155058(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, 0.6F, FALSE, TRUE, TRUE, 0.17F, FALSE);
    }
}

void func_ovl3_801550AC(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE7D8(fighter_gobj) != FALSE)
    {
        if (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL)
        {
            func_ovl3_80144C24(fighter_gobj);
        }
        else
        {
            ftMapCollide_SetGround(fp);
            ftCommon_DownBounce_ApplyStatus(fighter_gobj);
        }
    }
}

void func_ovl3_80155114(GObj *fighter_gobj, Vec3f *arg1, Vec3f *arg2)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);
    Vec3f *vel = &fp->phys_info.vel_air;

    func_ovl0_800C7B08(vel);
    func_ovl0_800C7AE0(vel, 0.5F);
    func_ovl0_800C7A84(vel);
    func_ovl2_800D8EB8(fp);

    fp->lr = (fp->phys_info.vel_air.x < 0.0F) ? RIGHT : LEFT;

    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiBound, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl2_800FFD58(arg2, 4, atan2f(-arg1->x, arg1->y));
    func_ovl2_801008F4(2);
}