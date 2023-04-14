#include "fighter.h"
#include "ftdonkey.h"

void func_ovl3_80140340(Fighter_Struct *fp)
{
    f32 knockback = (fp->ground_or_air == air) ? vec3f_mag(&fp->phys_info.vel_damage_air) : ABSF(fp->phys_info.vel_damage_ground.x);
    s32 spawn_gfx_wait;

    if (knockback < FTCOMMON_DAMAGE_GFX_KNOCKBACK_LOW)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_LOW;
    }
    else if (knockback < FTCOMMON_DAMAGE_GFX_KNOCKBACK_MID_LOW)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_MID_LOW;
    }
    else if (knockback < FTCOMMON_DAMAGE_GFX_KNOCKBACK_MID)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_MID;
    }
    else if (knockback < FTCOMMON_DAMAGE_GFX_KNOCKBACK_MID_HIGH)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_MID_HIGH;
    }
    else if (knockback < FTCOMMON_DAMAGE_GFX_KNOCKBACK_HIGH)
    {
        spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_HIGH;
    }
    else spawn_gfx_wait = FTCOMMON_DAMAGE_GFX_WAIT_DEFAULT;
    
    fp->status_vars.common.damage.dust_gfx_int = spawn_gfx_wait;
}

void func_ovl3_80140454(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.damage.dust_gfx_int != 0)
    {
        fp->status_vars.common.damage.dust_gfx_int--;

        if (fp->status_vars.common.damage.dust_gfx_int == 0)
        {
            func_ovl2_800EABDC(fighter_gobj, 0x11, 4, 0, 0, fp->lr, 0, 0);
            func_ovl3_80140340(fp);
        }
    }
}

void func_ovl3_801404B8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.damage.hitstun_timer != 0)
    {
        fp->status_vars.common.damage.hitstun_timer--;

        if (fp->status_vars.common.damage.hitstun_timer == 0)
        {
            fp->publicity_knockback = fp->status_vars.common.damage.publicity_knockback;
        }
    }
}

void func_ovl3_801404E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_801404B8(fighter_gobj);

    if ((fighter_gobj->anim_frame <= 0.0F) && (fp->status_vars.common.damage.hitstun_timer == 0))
    {
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_8014053C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80140454(fighter_gobj);
    func_ovl3_801404B8(fighter_gobj);

    if ((fighter_gobj->anim_frame <= 0.0F) && (fp->status_vars.common.damage.hitstun_timer == 0))
    {
        func_ovl3_80143664(fighter_gobj);
    }
}

void func_ovl3_801405A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->hitlag_timer <= 0) && (fp->status_vars.common.damage.is_limit_knockback != 0))
    {
        fp->status_vars.common.damage.is_limit_knockback = 0;

        func_ovl2_800EA8EC(fp, 1);
    }
}

void func_ovl3_801405E4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->hitlag_timer <= 0)
    {
        func_ovl2_800E6F24(fighter_gobj, fp->status_vars.common.damage.status_id, 0.0F, 1.0F, 0x1400U);
        func_ovl2_800E0830(fighter_gobj);

        if (fp->status_info.status_id == ftStatus_Common_DamageFlyRoll)
        {
            func_ovl3_80140744(fighter_gobj);
        }
        fp->is_hitstun = TRUE;

        if (fp->status_vars.common.damage.is_limit_knockback != 0)
        {
            fp->status_vars.common.damage.is_limit_knockback = 0;
            func_ovl2_800EA8EC(fp, 1);
        }
    }
}

void func_ovl3_80140674(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.damage.hitstun_timer == 0)
    {
        fp->is_hitstun = FALSE;

        if (fp->ground_or_air == air)
        {
            if (func_ovl2_800F3794(fighter_gobj) != FALSE)
            {
                func_ovl3_80147BE0(fighter_gobj);
            }
            else func_ovl3_8013F9A0(fighter_gobj);
        }
        else if (func_ovl2_800F3794(fighter_gobj) != FALSE)
        {
            jtgt_ovl2_800F38C4(fighter_gobj);
        }
        else func_ovl3_8013E070(fighter_gobj);
    }
}

void func_ovl3_8014070C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.damage.hitstun_timer == 0)
    {
        fp->is_hitstun = FALSE;

        func_ovl3_80143560(fighter_gobj);
    }
}

void func_ovl3_80140744(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->joint[4]->rotate.x = atan2f(fp->phys_info.vel_air.x + fp->phys_info.vel_damage_air.x, fp->phys_info.vel_air.y + fp->phys_info.vel_damage_air.y) * fp->lr;

    func_ovl2_800EB528(fp->joint[4]);
}

void func_ovl3_801407A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        if (fp->status_vars.common.damage.hitstun_timer == 0)
        {
            jtgt_ovl2_800D9160(fighter_gobj);
        }
        else
        {
            func_ovl2_800D91EC(fighter_gobj);
        }
    }
    else
    {
        func_ovl2_800D8BB4(fighter_gobj);
    }
    if (fp->status_info.status_id == ftStatus_Common_DamageFlyRoll)
    {
        func_ovl3_80140744(fighter_gobj);
    }
    if ((fp->throw_gobj != NULL) && (vec3f_mag(&fp->phys_info.vel_damage_air) < 70.0F))
    {
        func_ovl2_800E8518(fighter_gobj);
    }
}

void func_ovl3_80140878(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->hitlag_timer != 0)
    {
        if ((SQUARE(fp->input.stick_range.x) + SQUARE(fp->input.stick_range.y)) >= SQUARE(FTCOMMON_DAMAGE_SMASH_DI_RANGE_MIN))
        {
            if ((fp->buffer_stick_x < FTCOMMON_DAMAGE_SMASH_DI_BUFFER_FRAMES_MAX) || (fp->buffer_stick_y < FTCOMMON_DAMAGE_SMASH_DI_BUFFER_FRAMES_MAX))
            {
                Vec3f *translate = &DObjGetStruct(fighter_gobj)->translate;

                translate->x += fp->input.stick_range.x * FTCOMMON_DAMAGE_SMASH_DI_RANGE_MUL;
                translate->y += fp->input.stick_range.y * FTCOMMON_DAMAGE_SMASH_DI_RANGE_MUL;

                fp->buffer_stick_x = fp->buffer_stick_y = U8_MAX - 1;
            }
        }
    }
}

void func_ovl3_80140934(void) // Unused
{
    return;
}

void func_ovl3_8014093C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl2_800DEDAC(fighter_gobj) != FALSE)                 &&
    (func_ovl3_80141C6C(fighter_gobj) == FALSE)                     &&
    (fp->status_vars.common.damage.coll_flags & MPCOLL_MASK_GROUND) &&
    (func_ovl3_80144760(fighter_gobj) == FALSE)                     &&
    (func_ovl3_801446BC(fighter_gobj) == FALSE))
    {
        func_ovl3_80144498(fighter_gobj);
    }
}

f32 func_ovl3_801409BC(s32 angle, s32 ground_or_air, f32 knockback)
{
    f32 sakurai_angle;

    if (angle != 361)
    {
        sakurai_angle = F_DEG_TO_RAD(angle);
    }
    else if (ground_or_air == air)
    {
        sakurai_angle = FTCOMMON_DAMAGE_SAKURAI_ANGLE_DEFAULT_AR;
    }
    else if (knockback < FTCOMMON_DAMAGE_SAKURAI_KNOCKBACK_LOW)
    {
        sakurai_angle = FTCOMMON_DAMAGE_SAKURAI_ANGLE_LOW_GR;
    }
    else
    {
        sakurai_angle = F_DEG_TO_RAD(((((knockback - FTCOMMON_DAMAGE_SAKURAI_KNOCKBACK_LOW) / 0.099998474F) * FTCOMMON_DAMAGE_SAKURAI_ANGLE_HIGH_GD) + 1.0F));

        if (sakurai_angle > FTCOMMON_DAMAGE_SAKURAI_ANGLE_HIGH_GR)
        {
            sakurai_angle = FTCOMMON_DAMAGE_SAKURAI_ANGLE_HIGH_GR;
        }
    }
    return sakurai_angle;
}

s32 func_ovl3_80140A94(f32 knockback)
{
    s32 damage_level;

    if (knockback < FTCOMMON_DAMAGE_STATUS_KNOCKBACK_LOW)
    {
        damage_level = 0; // DamageX1
    }
    else if (knockback < FTCOMMON_DAMAGE_STATUS_KNOCKBACK_MID)
    {
        damage_level = 1; // DamageX2
    }
    else if (knockback < FTCOMMON_DAMAGE_STATUS_KNOCKBACK_HIGH)
    {
        damage_level = 2; // DamageX3
    }
    else damage_level = 3; // Fighter becomes airborne

    return damage_level;
}

void func_ovl3_80140B00(Fighter_Struct *this_fp, f32 knockback, f32 angle)
{
    GObj *victim_gobj = func_ovl2_800E7ED4(this_fp->damage_player_number);
    bool32 unk_bool;

    this_fp->status_vars.common.damage.publicity_knockback = knockback;
    this_fp->publicity_knockback = 0.0F;

    // By default, if knockback angle is between 75 and 115 degrees, the crowd is 20% less likely to gasp
    if ((angle > FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_ANGLE_LOW) && (angle < FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_ANGLE_HIGH))
    {
        this_fp->status_vars.common.damage.publicity_knockback *= FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_KNOCKBACK_MUL;
    }
    if ((victim_gobj != NULL) && (FighterGetStruct(victim_gobj)->publicity_knockback >= FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_KNOCKBACK_UNK))
    {
        unk_bool = TRUE;
    }
    else unk_bool = FALSE;

    func_ovl3_80164F2C(this_fp->this_fighter, this_fp->status_vars.common.damage.publicity_knockback, unk_bool);
}

s32 func_ovl3_80140BCC(GObj *fighter_gobj, s32 element, s32 damage_level)
{
    s32 thing;

    switch (element)
    {
    case gmHitCollision_Element_Fire:
        thing = func_ovl2_800E9814(fighter_gobj, damage_level + 0xC, 0);
        break;
    case gmHitCollision_Element_Electric:
        thing = func_ovl2_800E9AF4(fighter_gobj, damage_level);
        break;
    case gmHitCollision_Element_Sleep:
        thing = func_ovl2_800E9814(fighter_gobj, damage_level + 0x20, 0);
        break;
    default:
        thing = func_ovl2_800E9814(fighter_gobj, 5, 0);
        break;
    }
    return thing;
}

void func_ovl3_80140C50(f32 knockback, s32 element)
{
    switch (element)
    {
    case gmHitCollision_Element_Fire:
        if (knockback > FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_KNOCKBACK_UNK)
        {
            func_ovl2_80115BF0(0x53, 0);
        }
        break;

    case gmHitCollision_Element_Electric:
        if (knockback > FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_KNOCKBACK_UNK)
        {
            func_ovl2_80115BF0(0x54, 0);
        }
        break;

    case gmHitCollision_Element_Sleep:
        if (knockback > FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_KNOCKBACK_UNK)
        {
            func_ovl2_80115BF0(0x55, 0);
        }
        break;

    default:
        if (knockback > FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_KNOCKBACK_UNK)
        {
            func_ovl2_80115BF0(0x52, 0);
        }
        break;
    }
}

bool32 func_ovl3_80140D30(Fighter_Struct *fp)
{
    // Something to do with a fighter in Catch(Wait) being hit?

    if (fp->unk_0x7F8 == 6)
    {
        return FALSE;
    }

    if (fp->damage_knockback == 0.0F)
    {
        return TRUE;
    }
    if ((fp->hitlag_timer > 0) && (fp->x192_flag_b6) && (fp->unk_0x7E0 < (fp->damage_knockback_again + 30.0F)))
    {
        return TRUE;
    }
    if ((fp->ft_kind == Ft_Kind_Donkey) || (fp->ft_kind == Ft_Kind_PolyDonkey) || (fp->ft_kind == Ft_Kind_GiantDonkey))
    {
        if ((fp->status_info.status_id >= ftStatus_Donkey_ThrowFWait) && (fp->status_info.status_id <= ftStatus_Donkey_ThrowFUnk) && (func_ovl3_80140A94(func_ovl2_800EA1B0(fp->unk_0x7E0)) < 3))
        {
            return TRUE;
        }
    }
    return FALSE;
}

void func_ovl3_80140E2C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->damage_knockback == 0.0F) || ((fp->hitlag_timer > 0) && (fp->x192_flag_b6) && (fp->damage_knockback < (fp->damage_knockback_again + 30.0F))))
    {
        func_ovl3_80141648(fighter_gobj);
    }
    else
    {
        func_ovl2_800E823C(fighter_gobj);
        func_ovl3_8014E0E0(fighter_gobj);
    }
}

bool32 func_ovl3_80140EC0(Fighter_Struct *fp)
{
    if (fp->damage_taken_recent < FTCOMMON_DAMAGE_CATCH_RELEASE_THRESHOLD)
    {
        return TRUE;
    }
    else return FALSE;
}

s32 Fighter_StatusList_DamageGround[3][3] = { ftStatus_Common_DamageLw1,   ftStatus_Common_DamageN1,    ftStatus_Common_DamageHi1,
                                              ftStatus_Common_DamageLw2,   ftStatus_Common_DamageN2,    ftStatus_Common_DamageHi2,
                                              ftStatus_Common_DamageLw3,   ftStatus_Common_DamageN3,    ftStatus_Common_DamageHi3, };

s32 Fighter_StatusList_DamageAir[4][3] =    { ftStatus_Common_DamageFlyLw, ftStatus_Common_DamageFlyN,  ftStatus_Common_DamageFlyHi,
                                              ftStatus_Common_DamageAir1,  ftStatus_Common_DamageAir1,  ftStatus_Common_DamageAir1,
                                              ftStatus_Common_DamageAir2,  ftStatus_Common_DamageAir2,  ftStatus_Common_DamageAir2,
                                              ftStatus_Common_DamageAir3,  ftStatus_Common_DamageAir3,  ftStatus_Common_DamageAir3 };

void func_ovl3_80140EE4(GObj *this_gobj, s32 status_id_replace, s32 arg2, f32 knockback, s32 angle_start,
s32 lr_damage, s32 damage_index, s32 element, s32 damage_player_number, s32 arg9, s32 unk_bool, bool32 is_publicity)
{
    Fighter_Struct *this_fp = FighterGetStruct(this_gobj);
    GObj *attacker_gobj;
    f32 angle_end = func_ovl3_801409BC(angle_start, this_fp->ground_or_air, knockback);
    f32 vel_x = cosf(angle_end) * knockback;
    s32 unused2;
    f32 vel_y = __sinf(angle_end) * knockback;
    f32 hitstun_timer = func_ovl2_800EA1B0(knockback);
    s32 unused1;
    s32 damage_level;
    s32 status_id_set;
    s32 status_id_var;
    Vec3f vel_damage;
    f32 angle_diff;
    s32 unused3[3];

    this_fp->status_vars.common.damage.hitstun_timer = hitstun_timer;

    if (this_fp->status_vars.common.damage.hitstun_timer == 0)
    {
        this_fp->status_vars.common.damage.hitstun_timer = 1;
    }

    damage_level = func_ovl3_80140A94(hitstun_timer);

    if (status_id_replace != -1)
    {
        damage_level = 3;
    }

    this_fp->lr = lr_damage;

    if (this_fp->ground_or_air == air)
    {
        status_id_var = status_id_set = Fighter_StatusList_DamageAir[damage_level][damage_index];

        this_fp->phys_info.vel_damage_air.x = -vel_x * this_fp->lr;
        this_fp->phys_info.vel_damage_air.y = vel_y;
        this_fp->phys_info.vel_damage_ground.x = 0.0F;
    }
    else
    {
        vel_damage.x = -vel_x * this_fp->lr;
        vel_damage.y = vel_y;
        vel_damage.z = 0.0F;

        angle_diff = vec3f_angle_diff(&this_fp->coll_data.ground_angle, &vel_damage);

        if (angle_diff < HALF_PI32)
        {
            status_id_var = status_id_set = Fighter_StatusList_DamageGround[damage_level][damage_index];

            func_ovl2_800DEEC8(this_fp);

            this_fp->phys_info.vel_damage_air.x = vel_damage.x;
            this_fp->phys_info.vel_damage_air.y = vel_damage.y;
            this_fp->phys_info.vel_damage_ground.x = 0.0F;
        }
        else if (damage_level == 3)
        {
            func_ovl2_800DEEC8(this_fp);

            status_id_var = status_id_set = Fighter_StatusList_DamageGround[damage_level][damage_index];

            if (angle_diff > 1.7453293F)
            {
                this_fp->phys_info.vel_damage_air.x = vel_damage.x;
                this_fp->phys_info.vel_damage_air.y = -vel_damage.y * 0.8F;
                this_fp->phys_info.vel_damage_ground.x = 0.0F;

                func_ovl2_800EABDC(this_gobj, 0x16, 0, 0, 0, this_fp->lr, 0, 0);
                func_ovl2_800EABDC(this_gobj, 0x20, 0, 0, 0, this_fp->lr, 0, 0);
            }
            else
            {
                this_fp->phys_info.vel_damage_air.x = vel_damage.x;
                this_fp->phys_info.vel_damage_air.y = vel_damage.y;
                this_fp->phys_info.vel_damage_ground.x = 0.0F;
            }
        }
        else
        {
            status_id_var = status_id_set = Fighter_StatusList_DamageGround[damage_level][damage_index];

            this_fp->phys_info.vel_damage_ground.x = (-vel_x * this_fp->lr);
            this_fp->phys_info.vel_damage_air.x = this_fp->coll_data.ground_angle.y * (-vel_x * this_fp->lr);
            this_fp->phys_info.vel_damage_air.y = -this_fp->coll_data.ground_angle.x * (-vel_x * this_fp->lr);
        }
    }
    this_fp->phys_info.vel_ground.x = 0.0F;
    this_fp->phys_info.vel_air.z = 0.0F;
    this_fp->phys_info.vel_air.y = 0.0F;
    this_fp->phys_info.vel_air.x = 0.0F;

    if ((damage_level == 3) && (this_fp->ground_or_air == air))
    {
        if ((angle_end > FTCOMMON_DAMAGE_FIGHTER_FLYTOP_ANGLE_LOW) && (angle_end < FTCOMMON_DAMAGE_FIGHTER_FLYTOP_ANGLE_HIGH))
        {
            status_id_var = status_id_set = ftStatus_Common_DamageFlyTop;
            
        }
        else if ((this_fp->percent_damage >= FTCOMMON_DAMAGE_FIGHTER_FLYROLL_DAMAGE_MIN) && (rand_f32() < FTCOMMON_DAMAGE_FIGHTER_FLYROLL_RANDOM_CHANCE))
        {
            status_id_var = status_id_set = ftStatus_Common_DamageFlyRoll;
            
        }
    }
    if (status_id_replace != -1)
    {
        status_id_set = status_id_replace;
    }

    if (((element == gmHitCollision_Element_Electric) && (status_id_set >= ftStatus_Common_DamageHi1)) && (status_id_set <= ftStatus_Common_WallDamage))
    {
        status_id_var = status_id_set;

        if (damage_level == 3)
        {
            status_id_set = ftStatus_Common_DamageElec2;
        }
        else
        {
            status_id_set = ftStatus_Common_DamageElec1;
        }
    }
    this_fp->damage_player_number = damage_player_number;

    func_ovl3_80140B00(this_fp, knockback, angle_end);

    if (arg2 != 0)
    {
        func_ovl3_80140BCC(this_gobj, element, damage_level);
    }
    func_ovl3_80140C50(knockback, element);

    if ((damage_level == 3) && (is_publicity != FALSE))
    {
        func_ovl3_80163648(this_gobj);
    }

    func_ovl2_800E6F24(this_gobj, status_id_set, 0.0F, 1.0F, 0x1000U);
    func_ovl2_800E0830(this_gobj);

    if (knockback >= 65000.0F)
    {
        this_fp->status_vars.common.damage.is_limit_knockback = TRUE;
    }
    else this_fp->status_vars.common.damage.is_limit_knockback = FALSE;
    

    if ((this_fp->status_info.status_id == ftStatus_Common_DamageElec1) || (this_fp->status_info.status_id == ftStatus_Common_DamageElec2))
    {
        this_fp->cb_update_gfx = func_ovl3_801405E4;
        this_fp->status_vars.common.damage.status_id = status_id_var;
    }
    else this_fp->cb_update_gfx = func_ovl3_801405A0;
    
    this_fp->unk_0xA00 = func_ovl3_80140878;

    this_fp->buffer_stick_x = this_fp->buffer_stick_y = U8_MAX - 1;

    this_fp->damage_knockback_again = knockback;

    if ((damage_level == 3) || (arg9 != 0))
    {
        func_ovl2_800E806C(this_fp, 2, 0);
    }
    if (this_fp->status_info.status_id == ftStatus_Common_DamageFlyRoll)
    {
        func_ovl3_80140744(this_gobj);
    }
    func_ovl3_80140340(this_fp);

    if (this_fp->status_vars.common.damage.dust_gfx_int != 0)
    {
        this_fp->status_vars.common.damage.dust_gfx_int = 1;
    }
    if ((!(hitstun_timer >= FTCOMMON_DAMAGE_FIGHTER_REACT_GASP_KNOCKBACK_MIN)) || (this_fp->attributes->damage_sfx == 0x2B7))
    {
        // ???

        if (unk_bool == FALSE) goto next;
        {

        }
    }
    func_800269C0(this_fp->attributes->damage_sfx);
next:
    this_fp->is_hitstun = TRUE;
    this_fp->timer_unk = 0x10000;

    if ((damage_level == 3) && (knockback >= 130.0F))
    {
        func_ovl2_800E7F7C(this_gobj, 0xA);
    }
    this_fp->status_vars.common.damage.coll_flags = 0;

    attacker_gobj = func_ovl2_800E7ED4(damage_player_number);

    if (attacker_gobj != NULL)
    {
        Fighter_Struct *attacker_fp = FighterGetStruct(attacker_gobj);

        attacker_fp->attack_hit_count++;
        attacker_fp->attack_knockback = knockback;
    }
}