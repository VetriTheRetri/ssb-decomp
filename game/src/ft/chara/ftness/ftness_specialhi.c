#include <game/src/ft/chara/ftness/ftness.h>

#define FTNESS_SPECIALHISTART_STATUPDATE_FLAGS (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_HITSTATUS_PRESERVE | FTSTATUPDATE_COLANIM_PRESERVE)
#define FTNESS_SPECIALHIHOLD_STATUPDATE_FLAGS (FTSTATUPDATE_UNK5_PRESERVE | FTSTATUPDATE_UNK4_PRESERVE | FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_HITSTATUS_PRESERVE | FTSTATUPDATE_GFX_PRESERVE | FTSTATUPDATE_COLANIM_PRESERVE | FTSTATUPDATE_HIT_PRESERVE)
#define FTNESS_SPECIALHIEND_STATUPDATE_FLAGS (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_HITSTATUS_PRESERVE | FTSTATUPDATE_COLANIM_PRESERVE)
#define FTNESS_SPECIALHI_STATUPDATE_FLAGS (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_HITSTATUS_PRESERVE | FTSTATUPDATE_COLANIM_PRESERVE | FTSTATUPDATE_HIT_PRESERVE)

// PK Thunder (SpecialHi/SpecialAirHi)

// 0x80153C50
void ftNess_SpecialHi_DecThunderTimers(Fighter_Struct *fp)
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

// 0x80153C88
void ftNess_SpecialHi_SpawnPKThunder(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f vel;

    pos.x = 0.0F;
    pos.y = 0.0F;
    pos.z = 0.0F;

    func_ovl2_800EDF24(fp->joint[FTNESS_PK_THUNDER_SPAWN_JOINT], &pos);

    pos.z = 0.0F;

    vel.z = 0.0F;
    vel.y = 60.0F;
    vel.x = 0.0F;

    fp->status_vars.ness.specialhi.pk_thunder_gobj = func_ovl3_8016B2C4(fighter_gobj, &pos, &vel);
}

// 0x80153CFC
bool32 ftNess_SpecialHi_CheckCollidePKThunder(GObj *fighter_gobj)
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

    if (fp->status_vars.ness.specialhi.pk_jibaku_delay != 0) return FALSE;

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
            ip->item_vars.pk_thunder.pk_thunder_state = itNessThunderStatus_Collide;

            fp->status_vars.ness.specialhi.pk_thunder_pos = DObjGetStruct(pk_thunder_gobj)->translate;

            return TRUE;
        }
    }
    return FALSE;
}

// 0x80153E04
void ftNess_SpecialHiStart_ProcUpdate(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, ftNess_SpecialHiHold_SetStatus);
}

// 0x80153E28
void ftNess_SpecialAirHiStart_ProcUpdate(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, ftNess_SpecialAirHiHold_SetStatus);
}

// 0x80153E4C
void ftNess_SpecialHi_ProcPhysics(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.ness.specialhi.pk_thunder_gravity_delay != 0)
    {
        fp->status_vars.ness.specialhi.pk_thunder_gravity_delay--;
    }
    func_ovl2_800D8BB4(fighter_gobj);
}

// 0x80153E80
void ftNess_SpecialAirHi_ProcPhysics(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->status_vars.ness.specialhi.pk_thunder_gravity_delay != 0)
    {
        fp->status_vars.ness.specialhi.pk_thunder_gravity_delay--;
    }
    else func_ovl2_800D8D68(fp, 0.5F, attributes->fall_speed_max);

    if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
    {
        func_ovl2_800D9074(fp, attributes);
    }
}

// 0x80153EF8
void ftNess_SpecialHiStart_ProcMap(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, ftNess_SpecialHiStart_SwitchStatusAir);
}

// 0x80153F1C
void ftNess_SpecialAirHiStart_ProcMap(GObj *fighter_gobj)
{
    ftMapCollide_CheckGroundCliff(fighter_gobj, ftNess_SpecialAirHiStart_SwitchStatusGround);
}

// 0x80153F40
void ftNess_SpecialAirHiStart_SwitchStatusGround(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiStart, fighter_gobj->anim_frame, 1.0F, FTNESS_SPECIALHISTART_STATUPDATE_FLAGS);
}

// 0x80153F80
void ftNess_SpecialHiStart_SwitchStatusAir(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiStart, fighter_gobj->anim_frame, 1.0F, FTNESS_SPECIALHISTART_STATUPDATE_FLAGS);
    func_ovl2_800D8EB8(fp);
}

// 0x80153FCC
void ftNess_SpecialHi_InitStatusVars(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.ness.specialhi.pk_jibaku_delay = FTNESS_PK_JIBAKU_DELAY;
    fp->status_vars.ness.specialhi.pk_thunder_end_delay = FTNESS_PK_THUNDER_END_DELAY;
    fp->status_vars.ness.specialhi.pk_thunder_gravity_delay = FTNESS_PK_THUNDER_GRAVITY_DELAY;
    fp->fighter_vars.ness.is_thunder_destroy = FALSE;
    fp->fighter_vars.ness.pk_thunder_trail_id = 0;
}

// 0x80153FF0
void ftNess_SpecialHiStart_SetStatus(GObj *fighter_gobj)
{
    ftNess_SpecialHi_InitStatusVars(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiStart, 0.0F, 1.0F, 0);
    ftAnim_Update(fighter_gobj);
}

// 0x80154030
void ftNess_SpecialAirHiStart_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftNess_SpecialHi_InitStatusVars(fighter_gobj);

    fp->phys_info.vel_air.y = 0.0F;
    fp->phys_info.vel_air.x /= 2;

    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiStart, 0.0F, 1.0F, 0);
    ftAnim_Update(fighter_gobj);
}

// 0x80154098
void ftNess_SpecialHi_UpdatePKThunder(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *item_gobj = fp->status_vars.ness.specialhi.pk_thunder_gobj;

    if (item_gobj == NULL)
    {
        fp->fighter_vars.ness.is_thunder_destroy |= TRUE;
    }
    fp->fighter_vars.ness.pk_thunder_trail_id++;

    if (fp->fighter_vars.ness.pk_thunder_trail_id >= FTNESS_PKTHUNDER_TRAIL_POS_COUNT)
    {
        fp->fighter_vars.ness.pk_thunder_trail_id = 0;
    }
    ftNess_SpecialHi_DecThunderTimers(fp);
}

// 0x801540EC
void ftNess_SpecialHiHold_ProcUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftNess_SpecialHi_UpdatePKThunder(fighter_gobj);

    if ((fp->fighter_vars.ness.pk_jibaku_delay <= 0) &&
    (fp->fighter_vars.ness.pk_thunder_end_delay <= 0) &&
    (fp->fighter_vars.ness.is_thunder_destroy & TRUE))
    {
        ftNess_SpecialHiEnd_SetStatus(fighter_gobj);
    }

    else if (ftNess_SpecialHi_CheckCollidePKThunder(fighter_gobj) != FALSE)
    {
        ftNess_Jibaku_SetStatus(fighter_gobj);
    }
}

// 0x8015416C
void ftNess_SpecialAirHiHold_ProcUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftNess_SpecialHi_UpdatePKThunder(fighter_gobj);

    if ((fp->fighter_vars.ness.pk_jibaku_delay <= 0) &&
    (fp->fighter_vars.ness.pk_thunder_end_delay <= 0) &&
    (fp->fighter_vars.ness.is_thunder_destroy & TRUE))
    {
        ftNess_SpecialAirHiEnd_SetStatus(fighter_gobj);
    }

    else if (ftNess_SpecialHi_CheckCollidePKThunder(fighter_gobj) != FALSE)
    {
        ftNess_JibakuAir_SetStatus(fighter_gobj);
    }
}

// 0x801541EC
void ftNess_SpecialHiHold_ProcMap(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, ftNess_SpecialHiHold_SwitchStatusAir);
}

// 0x80154210
void ftNess_SpecialAirHiHold_ProcMap(GObj *fighter_gobj)
{
    ftMapCollide_CheckGroundCliff(fighter_gobj, ftNess_SpecialAirHiHold_SwitchStatusGround);
}

// 0x80154234
void ftNess_SpecialHi_SetPKThunderDestroy(GObj *fighter_gobj) // Unused
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *item_gobj = fp->status_vars.ness.specialhi.pk_thunder_gobj;

    if ((!(fp->fighter_vars.ness.is_thunder_destroy & TRUE)) && (item_gobj != NULL))
    {
        Item_Struct *ip = ItemGetStruct(item_gobj);

        ip->item_vars.pk_thunder.pk_thunder_state = itNessThunderStatus_Destroy;
    }
}

// 0x80154268
void ftNess_SpecialAirHiHold_SwitchStatusGround(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiHold, fighter_gobj->anim_frame, 1.0F, FTNESS_SPECIALHIHOLD_STATUPDATE_FLAGS);
}

// 0x801542A8
void ftNess_SpecialHiHold_SwitchStatusAir(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiHold, fighter_gobj->anim_frame, 1.0F, FTNESS_SPECIALHIHOLD_STATUPDATE_FLAGS);
    func_ovl2_800D8EB8(fp);
}

// 0x801542F4
void func_ovl3_801542F4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftNess_SpecialHi_SpawnPKThunder(fighter_gobj);

    if (!(fp->is_statupdate_stop_gfx) && (func_ovl2_801029F8(fighter_gobj) != NULL))
    {
        fp->is_statupdate_stop_gfx = TRUE;
    }
    fp->jumps_used = fp->attributes->jumps_max;
}

// 0x8015435C
void ftNess_SpecialHiHold_SetStatus(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiHold, 0.0F, 1.0F, FTSTATUPDATE_UNK4_PRESERVE);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801542F4(fighter_gobj);
}

// 0x801543A0
void ftNess_SpecialAirHiHold_SetStatus(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiHold, 0.0F, 1.0F, FTSTATUPDATE_UNK4_PRESERVE);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801542F4(fighter_gobj);
}

// 0x801543E4
void ftNess_SpecialAirHiEnd_ProcUpdate(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, FTNESS_PK_THUNDER_FALLSPECIAL_DRIFT, FALSE, TRUE, TRUE, FTNESS_PK_THUNDER_LANDING_LAG, FALSE);
    }
}

// 0x80154438
void ftNess_SpecialHiEnd_ProcMap(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, ftNess_SpecialHiEnd_SwitchStatusAir);
}

// 0x8015445C
void ftNess_SpecialAirHiEnd_ProcMap(GObj *fighter_gobj)
{
    ftMapCollide_CheckGroundCliff(fighter_gobj, ftNess_SpecialAirHiEnd_SwitchStatusGround);
}

// 0x80154480
void ftNess_SpecialAirHiEnd_SwitchStatusGround(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiEnd, fighter_gobj->anim_frame, 1.0F, FTNESS_SPECIALHIEND_STATUPDATE_FLAGS);
}

// 0x801544C0
void ftNess_SpecialHiEnd_SwitchStatusAir(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiEnd, fighter_gobj->anim_frame, 1.0F, FTNESS_SPECIALHIEND_STATUPDATE_FLAGS);
    func_ovl2_800D8EB8(fp);
}

// 0x8015450C
void ftNess_SpecialHi_ClearProcDamage(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->proc_damage = NULL;
}

// 0x80154518
void ftNess_SpecialHiEnd_SetStatus(GObj *fighter_gobj)
{
    ftNess_SpecialHi_ClearProcDamage(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHiEnd, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

// 0x80154558
void ftNess_SpecialAirHiEnd_SetStatus(GObj *fighter_gobj)
{
    ftNess_SpecialHi_ClearProcDamage(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiEnd, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

// 0x80154598
void ftNess_SpecialHi_CollideWallPhysics(GObj *fighter_gobj, Coll_Data *coll_data)
{
    f32 tan_rwall_angle;
    f32 rotation;
    f32 tangent;
    f32 tan_lwall_angle;
    u32 coll_mask;
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    rotation = (fp->lr == RIGHT) ? fp->status_vars.ness.specialhi.pk_jibaku_angle : (PI32 - fp->status_vars.ness.specialhi.pk_jibaku_angle);

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

    vec3_get_euler_rotation(&fp->phys_info.vel_air, 4, tangent - (fp->status_vars.ness.specialhi.pk_jibaku_angle * (f32)fp->lr));

    fp->status_vars.ness.specialhi.pk_jibaku_angle = atan2f(fp->phys_info.vel_air.y, fp->phys_info.vel_air.x * (f32)fp->lr);
}

// 0x80154758
void ftNess_SpecialHi_UpdateModelRoll(GObj *fighter_gobj) // Update joint's X rotation axis
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->joint[4]->rotate.x = (f32)((atan2f(fp->phys_info.vel_air.x, fp->phys_info.vel_air.y) * (f32)fp->lr) - HALF_PI32);

    func_ovl2_800EB528(fp->joint[4]);
}

// 0x801547B8
void ftNess_Jibaku_ProcUpdate(GObj *fighter_gobj) // Grounded PK Thunder Blast
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.ness.specialhi.pk_jibaku_anim_length--;

    if (fp->status_vars.ness.specialhi.pk_jibaku_anim_length == 0)
    {
        ftNess_SpecialHiEnd_SetStatus(fighter_gobj);
    }
}

// 0x801547EC
void ftNess_JibakuAir_ProcUpdate(GObj *fighter_gobj) // Aerial PK Thunder Blast
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.ness.specialhi.pk_jibaku_anim_length--;

    if (fp->status_vars.ness.specialhi.pk_jibaku_anim_length == 0)
    {
        ftNess_SpecialAirHiEnd_SetStatus(fighter_gobj);
    }
}

// 0x80154820
void ftNess_Jibaku_ProcPhysics(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->phys_info.vel_ground.x > 0.0F)
    {
        fp->phys_info.vel_ground.x -= FTNESS_PK_JIBAKU_DECELERATE;
    }

    jtgt_ovl2_800D8B94(fighter_gobj);
    ftNess_SpecialHi_UpdateModelRoll(fighter_gobj);
}

// 0x80154874
void ftNess_JibakuAir_ProcPhysics(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 vel_x_bak = fp->phys_info.vel_air.x;
    f32 vel_y_bak = fp->phys_info.vel_air.y;
    f32 fabs_axis;
    f32 fabs_axis_bak;

    fp->phys_info.vel_air.x -= (FTNESS_PK_JIBAKU_DECELERATE * cosf(fp->status_vars.ness.specialhi.pk_jibaku_angle) * fp->lr);

    fp->phys_info.vel_air.y -= (FTNESS_PK_JIBAKU_DECELERATE * __sinf(fp->status_vars.ness.specialhi.pk_jibaku_angle));

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
    ftNess_SpecialHi_UpdateModelRoll(fighter_gobj);
}

// 0x801549B0
bool32 ftNess_SpecialHi_CheckIgnorePass(GObj *fighter_gobj) // Check if Ness can pass through platforms, TRUE actually denies?
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    if (!(fp->coll_data.ground_flags & MPCOLL_MASK_NONSOLID) || ((f32)fp->status_vars.ness.specialhi.pk_jibaku_anim_length <= FTNESS_PK_JIBAKU_PASS_FRAME_END))
    {
        return TRUE;
    }
    else return FALSE;
}

// 0x801549FC
void ftNess_Jibaku_ProcMap(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        if (fp->coll_data.coll_mask & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
        {
            ftMapCollide_SetAir(fp);
            ftNess_SpecialAirHiEnd_SetStatus(fighter_gobj);
        }
        else ftNess_Jibaku_SwitchStatusAir(fighter_gobj);
    }
    else if (fp->coll_data.coll_mask & (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
    {
        fp->phys_info.vel_ground.x = 0.0F;
        ftCommon_DownBounce_SetStatus(fighter_gobj);
    }
}

// 0x80154A8C
void ftNess_JibakuAir_ProcMap(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);
    f32 unused;
    Vec3f pos;

    if (func_ovl2_800DE798(fighter_gobj, ftNess_SpecialHi_CheckIgnorePass) != FALSE)
    {
        if (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL)
        {
            ftCommon_CliffCatch_SetStatus(fighter_gobj);
            return;
        }
        if (FTNESS_PK_JIBAKU_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.ground_angle, &fp->phys_info.vel_air))
        {
            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;

            ftMapCollide_SetGround(fp);
            ftCommon_DownBounce_SetStatus(fighter_gobj);
            return;
        }
        ftNess_JibakuAir_SwitchStatusGround(fighter_gobj);
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

            ftNess_SpecialAirHiBound_SetStatus(fighter_gobj, &fp->coll_data.ceil_angle, &pos);
        }
    }
    if (fp->coll_data.coll_mask & MPCOLL_MASK_RWALL)
    {

        if (FTNESS_PK_JIBAKU_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.rwall_angle, &fp->phys_info.vel_air))
        {
            pos.x += fp->coll_data.object_coll.width;
            pos.y += fp->coll_data.object_coll.center;

            ftNess_SpecialAirHiBound_SetStatus(fighter_gobj, &fp->coll_data.rwall_angle, &pos);
        }
        else ftNess_SpecialHi_CollideWallPhysics(fighter_gobj, &fp->coll_data);
    }
    if (fp->coll_data.coll_mask & MPCOLL_MASK_LWALL)
    {
        if (FTNESS_PK_JIBAKU_HALT_ANGLE < vec3f_angle_diff(&fp->coll_data.lwall_angle, &fp->phys_info.vel_air))
        {
            pos.x -= fp->coll_data.object_coll.width;
            pos.y += fp->coll_data.object_coll.center;

            ftNess_SpecialAirHiBound_SetStatus(fighter_gobj, &fp->coll_data.lwall_angle, &pos);
        }
        else ftNess_SpecialHi_CollideWallPhysics(fighter_gobj, &fp->coll_data);
    }
}

// 0x80154CBC
void ftNess_JibakuAir_SwitchStatusGround(GObj *fighter_gobj)
{
    f32 frame_begin;

    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));

    frame_begin = fighter_gobj->anim_frame;

    if (frame_begin == 0.0F)
    {
        frame_begin = 1.0F;
    }
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHi, frame_begin, 1.0F, FTNESS_SPECIALHI_STATUPDATE_FLAGS); // Change Action State to PK Thunder Blast
}

// 0x80154D1C
void ftNess_Jibaku_SwitchStatusAir(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 frame_begin;

    ftMapCollide_SetAir(fp);

    frame_begin = fighter_gobj->anim_frame;

    if (frame_begin == 0.0F)
    {
        frame_begin = 1.0F;
    }
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHi, frame_begin, 1.0F, FTNESS_SPECIALHI_STATUPDATE_FLAGS);

    fp->status_vars.ness.specialhi.pk_jibaku_angle = atan2f(fp->phys_info.vel_air.y, fp->phys_info.vel_air.x * (f32)fp->lr);

    fp->jumps_used = fp->attributes->jumps_max;
}

// 0x80154DBC
void ftNess_Jibaku_InitStatusVars(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.ness.specialhi.pk_jibaku_anim_length = FTNESS_PK_JIBAKU_ANIM_LENGTH;

    ftNess_SpecialHi_UpdateModelRoll(fighter_gobj);

    fp->proc_damage = NULL;

    fp->jumps_used = fp->attributes->jumps_max;
}

// 0x80154DFC
void ftNess_Jibaku_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 angle_diff;
    s32 unused;
    Vec3f pos;

    if ((fp->coll_data.ground_flags & MPCOLL_MASK_NONSOLID)) goto block_2func;
    {
        pos.x = DObjGetStruct(fighter_gobj)->translate.x - fp->status_vars.ness.specialhi.pk_thunder_pos.x;
        pos.y = (DObjGetStruct(fighter_gobj)->translate.y + 150.0F) - fp->status_vars.ness.specialhi.pk_thunder_pos.y;
        pos.z = 0.0F;

        angle_diff = vec3f_angle_diff(&fp->coll_data.ground_angle, &pos);

        if (!(angle_diff < HALF_PI32))
        {
            if (2.3561945F < angle_diff) goto block_end;
            {
                fp->lr = (pos.x >= 0) ? RIGHT : LEFT;

                if (pos.x < 0)
                {
                    pos.x = -pos.x;
                }
                fp->phys_info.vel_ground.x = FTNESS_PK_JIBAKU_VEL;

                ftNess_Jibaku_InitStatusVars(fighter_gobj);
                ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialHi, 0.0F, 1.0F, FTSTATUPDATE_COLANIM_PRESERVE);
                ftAnim_Update(fighter_gobj);
                return;
            }
        }
        block_2func:
        ftMapCollide_SetAir(fp);
        ftNess_JibakuAir_SetStatus(fighter_gobj);
        return;
    }
    block_end:
    ftCommon_DownBounce_SetStatus(fighter_gobj);
}

// 0x80154F54
void ftNess_JibakuAir_SetStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    DObj *dobj = DObjGetStruct(fighter_gobj);
    f32 vel_x = dobj->translate.x - fp->status_vars.ness.specialhi.pk_thunder_pos.x;
    f32 vel_y = (dobj->translate.y + 150.0F) - fp->status_vars.ness.specialhi.pk_thunder_pos.y;

    fp->lr = (vel_x >= 0.0F) ? RIGHT : LEFT;

    fp->status_vars.ness.specialhi.pk_jibaku_angle  = atan2f(vel_y, ((f32)fp->lr * vel_x));

    fp->phys_info.vel_air.x = (f32)(cosf(fp->status_vars.ness.specialhi.pk_jibaku_angle) * FTNESS_PK_JIBAKU_VEL * (f32)fp->lr);
    fp->phys_info.vel_air.y = (f32)(__sinf(fp->status_vars.ness.specialhi.pk_jibaku_angle) * FTNESS_PK_JIBAKU_VEL);

    ftNess_Jibaku_InitStatusVars(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHi, 0.0F, 1.0F, FTSTATUPDATE_COLANIM_PRESERVE);
    ftAnim_Update(fighter_gobj);
}

// 0x80155058
void ftNess_SpecialAirHiBound_ProcUpdate(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_801438F0(fighter_gobj, FTNESS_PK_THUNDER_FALLSPECIAL_DRIFT, FALSE, TRUE, TRUE, FTNESS_PK_THUNDER_LANDING_LAG, FALSE);
    }
}

// 0x801550AC
void ftNess_SpecialAirHiBound_ProcMap(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE7D8(fighter_gobj) != FALSE)
    {
        if (fp->coll_data.coll_type & MPCOLL_MASK_CLIFF_ALL)
        {
            ftCommon_CliffCatch_SetStatus(fighter_gobj);
        }
        else
        {
            ftMapCollide_SetGround(fp);
            ftCommon_DownBounce_SetStatus(fighter_gobj);
        }
    }
}

// 0x80155114
void ftNess_SpecialAirHiBound_SetStatus(GObj *fighter_gobj, Vec3f *angle, Vec3f *pos)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);
    Vec3f *vel = &fp->phys_info.vel_air;

    func_ovl0_800C7B08(vel);
    func_ovl0_800C7AE0(vel, FTNESS_PK_JIBAKU_REBOUND_VEL_MAG);
    func_ovl0_800C7A84(vel);
    func_ovl2_800D8EB8(fp);

    fp->lr = (fp->phys_info.vel_air.x < 0.0F) ? RIGHT : LEFT;

    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirHiBound, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl2_800FFD58(pos, 4, atan2f(-angle->x, angle->y));
    func_ovl2_801008F4(2);
}