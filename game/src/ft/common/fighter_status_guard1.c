#include "fighter.h"

#define ftStatus_CheckInterruptGuard(fighter_gobj) \
(                                                  \
    (func_ovl3_80146AE8(fighter_gobj) != FALSE) || \
    (func_ovl3_801493EC(fighter_gobj) != FALSE) || \
    (func_ovl3_80149C60(fighter_gobj) != FALSE) || \
    (func_ovl3_8013F604(fighter_gobj) != FALSE) || \
    (func_ovl3_80141F8C(fighter_gobj) != FALSE)    \
)                                                  \

void func_ovl3_80148120(Fighter_Struct *fp)
{
    if (!(fp->input.pl.button_hold & fp->input.button_mask_z))
    {
        fp->status_vars.common.guard.is_release = TRUE;
    }
}

void func_ovl3_80148144(GObj *fighter_gobj) // Set all of Yoshi's hurtbox collision states to invincible (GuardOn)
{
    ftCommon_SetHitStatusPart(fighter_gobj, 5,  gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 6,  gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 7,  gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 15, gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 11, gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 16, gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 12, gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 27, gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 22, gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 28, gmHitCollision_HitStatus_Invincible);
    ftCommon_SetHitStatusPart(fighter_gobj, 23, gmHitCollision_HitStatus_Invincible);
}

void func_ovl3_80148214(GObj *fighter_gobj) // Set all of Yoshi's hurtbox collision states to intangible (Guard)
{
    ftCommon_SetHitStatusPart(fighter_gobj, 5,  gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 6,  gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 7,  gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 15, gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 11, gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 16, gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 12, gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 27, gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 22, gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 28, gmHitCollision_HitStatus_Intangible);
    ftCommon_SetHitStatusPart(fighter_gobj, 23, gmHitCollision_HitStatus_Intangible);
}

void func_ovl3_801482E4(GObj *fighter_gobj)
{
    ftCommon_SetHitStatusPartAll(fighter_gobj, gmHitCollision_HitStatus_Normal);
}

Vec3f Fighter_Yoshi_GuardOffGfxOffset = { 0.0F, 0.0F, 0.0F };

void func_ovl3_80148304(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->is_shield)
    {
        if (fp->status_vars.common.guard.shield_decay_wait != 0)
        {
            fp->status_vars.common.guard.shield_decay_wait--;

            if (fp->status_vars.common.guard.shield_decay_wait == 0)
            {
                fp->shield_health--;

                if (fp->shield_health != 0)
                {
                    fp->status_vars.common.guard.shield_decay_wait = FTCOMMON_GUARD_DECAY_INT;

                    goto lag_decrement;
                }
                else goto lag_end;
            }
        }
    lag_decrement:
        if (fp->status_vars.common.guard.release_lag != 0)
        {
            fp->status_vars.common.guard.release_lag--;
        }
        if ((fp->status_vars.common.guard.release_lag == 0) && (fp->status_vars.common.guard.is_release != FALSE))
        {
        lag_end:
            if (fp->ft_kind == Ft_Kind_Yoshi)
            {
                ftCommon_ResetModelPartRenderAll(fighter_gobj);
                func_ovl3_801482E4(fighter_gobj);

                if (fp->is_statupdate_stop_gfx)
                {
                    Vec3f egg_gfx_offset = Fighter_Yoshi_GuardOffGfxOffset;

                    func_ovl2_800EDF24(fp->joint[3], &egg_gfx_offset);
                    func_ovl2_801041A0(&egg_gfx_offset);
                }
            }
            ftCommon_ProcDestroyGFX(fighter_gobj);

            fp->is_shield = FALSE;
        }
    }
}

void func_ovl3_80148408(Fighter_Struct *fp)
{
    Vec3f *scale = &fp->joint[3]->scale;
    f32 scale_final;
    f32 scale_mul;

    if (fp->ft_kind == Ft_Kind_Yoshi)
    {
        scale_mul = 1.0F;
    }
    else scale_mul = fp->shield_health / FTCOMMON_GUARD_SIZE_HEALTH_DIV;

    scale_final = (((FTCOMMON_GUARD_SIZE_SCALE_MUL_INIT * scale_mul) + FTCOMMON_GUARD_SIZE_SCALE_MUL_ADD) * fp->attributes->shield_size) / FTCOMMON_GUARD_SIZE_SCALE_MUL_DIV;

    scale->x = scale->y = scale->z = scale_final;
}

void func_ovl3_80148488(Fighter_Struct *fp)
{
    f32 angle_r = atan2f(fp->input.pl.stick_range.y, fp->input.pl.stick_range.x * fp->lr);
    f32 angle_d;
    f32 range;

    if (angle_r < 0.0F)
    {
        angle_r += DOUBLE_PI32;
    }
    angle_d = F_RAD_TO_DEG(angle_r);

    if (angle_d < 0.0F)
    {
        angle_d = 0.0F;
    }
    if (angle_d > FTCOMMON_GUARD_ANGLE_MAX)
    {
        angle_d = FTCOMMON_GUARD_ANGLE_MAX;
    }
    fp->status_vars.common.guard.angle_i = (angle_d / 45.0F);
    fp->status_vars.common.guard.angle_f = (angle_d - (fp->status_vars.common.guard.angle_i * 45.0F));

    range = sqrtf(SQUARE(fp->input.pl.stick_range.x) + SQUARE(fp->input.pl.stick_range.y)) / GCONTROLLER_RANGE_MAX_F;

    if (range > 1.0F)
    {
        range = 1.0F;
    }
    fp->status_vars.common.guard.shield_rotate_range = range;
}

// WARNING: Not actually DObjDesc*
void func_ovl3_801485CC(DObj *joint, DObjDesc *joint_desc, f32 range)
{
    joint->rotate.x = ((joint->rotate.x - joint_desc->rotate.x) * range) + joint_desc->rotate.x;
    joint->rotate.y = ((joint->rotate.y - joint_desc->rotate.y) * range) + joint_desc->rotate.y;
    joint->rotate.z = ((joint->rotate.z - joint_desc->rotate.z) * range) + joint_desc->rotate.z;

    joint->translate.x = ((joint->translate.x - joint_desc->translate.x) * range) + joint_desc->translate.x;
    joint->translate.y = ((joint->translate.y - joint_desc->translate.y) * range) + joint_desc->translate.y;
    joint->translate.z = ((joint->translate.z - joint_desc->translate.z) * range) + joint_desc->translate.z;
}

// WARNING: Not actually DObjDesc*
void func_ovl3_80148664(DObj *joint, DObjDesc *joint_desc, f32 range, Vec3f *scale)
{
    f32 scale_translate;

    joint->rotate.x = ((joint->rotate.x - joint_desc->rotate.x) * range) + joint_desc->rotate.x;
    joint->rotate.y = ((joint->rotate.y - joint_desc->rotate.y) * range) + joint_desc->rotate.y;
    joint->rotate.z = ((joint->rotate.z - joint_desc->rotate.z) * range) + joint_desc->rotate.z;

    // y tho

    scale_translate = joint_desc->translate.x * scale->x;
    joint->translate.x = ((joint->translate.x - scale_translate) * range) + scale_translate;

    scale_translate = joint_desc->translate.y * scale->y;
    joint->translate.y = ((joint->translate.y - scale_translate) * range) + scale_translate;

    scale_translate = joint_desc->translate.z * scale->z;
    joint->translate.z = ((joint->translate.z - scale_translate) * range) + scale_translate;
}

// Return to this when the struct at 0x2D8 of ftCommonAttributes is mapped
void func_ovl3_80148714(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 unused2;
    DObj *yrotn_joint = fp->joint[3];
    DObj **fj = &fp->joint[2];
    s32 index;
    s32 i;
    Vec3f *scale = &fp->attributes->unk_0x324[3];

    if (fp->is_shield)
    {
        func_ovl3_80148488(fp);

        // TO DO: figure out what this loop bound means

        for (i = 2, index = 0; i < ARRAY_COUNT(fp->joint); i++, fj++)
        {
            if (*fj != NULL)
            {
                index++;
            }
        }
        index--;

        func_8000BD1C(yrotn_joint, fp->attributes->unk_joint[fp->status_vars.common.guard.angle_i][index], fp->status_vars.common.guard.angle_f);
        func_8000BFE8(yrotn_joint);

        if (fp->x18F_flag_b5)
        {
            func_ovl0_800C9488(yrotn_joint, scale);
        }
        else func_8000CCBC(yrotn_joint);

        if (fp->x18F_flag_b5)
        {
            func_ovl3_80148664(yrotn_joint, &fp->attributes->dobj_lookup[index], fp->status_vars.common.guard.shield_rotate_range, scale);
        }
        else func_ovl3_801485CC(yrotn_joint, &fp->attributes->dobj_lookup[index], fp->status_vars.common.guard.shield_rotate_range);

        yrotn_joint->unk_dobj_0x74 = (f32)FLOAT_NEG_MAX;

        func_ovl3_80148408(fp);
        func_ovl2_800EB528(fp->joint[3]);
    }
}

// Need to revisit this when once I have a better understanding of these structs...
void func_ovl3_8014889C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    DObj **p_joint = &fp->joint[4];
    DObjDesc *unk_vec = &attributes->dobj_lookup[1];
    DObj *joint;
    Vec3f *scale;
    s32 i;

    if (fp->status_info.status_id != ftStatus_Common_GuardSetOff)
    {
        func_ovl3_80148488(fp);
    }
    fp->anim_flags.flags.x19B_flag_b4 = TRUE;

    func_ovl0_800C8758(fp->joint[2], attributes->unk_joint[fp->status_vars.common.guard.angle_i], fp->status_vars.common.guard.angle_f);
    ftAnim_Update(fighter_gobj);

    if (fp->x18F_flag_b5)
    {
        scale = &fp->attributes->unk_0x324[4];

        for (i = 4; i < ARRAY_COUNT(fp->joint); i++, p_joint++, scale++)
        {
            joint = *p_joint;

            if (joint != NULL)
            {
                if ((f32)FLOAT_NEG_MAX != joint->unk_dobj_0x74)
                {
                    func_ovl3_80148664(joint, unk_vec, fp->status_vars.common.guard.shield_rotate_range, scale);
                    joint->unk_dobj_0x74 = (f32)FLOAT_NEG_MAX;
                }
                unk_vec++;
            }
        }
        joint = fp->joint[3];

        if ((f32)FLOAT_NEG_MAX != joint->unk_dobj_0x74)
        {
            func_ovl3_80148664(joint, unk_vec, fp->status_vars.common.guard.shield_rotate_range, &fp->attributes->unk_0x324[3]);

            joint->unk_dobj_0x74 = (f32)FLOAT_NEG_MAX;
        }
    }
    else
    {
        for (i = 4; i < ARRAY_COUNT(fp->joint); i++, p_joint++)
        {
            joint = *p_joint;

            if (joint != NULL)
            {
                if ((f32)FLOAT_NEG_MAX != joint->unk_dobj_0x74)
                {
                    func_ovl3_801485CC(joint, unk_vec, fp->status_vars.common.guard.shield_rotate_range);

                    joint->unk_dobj_0x74 = (f32)FLOAT_NEG_MAX;
                }
                unk_vec++;
            }
        }
        joint = fp->joint[3];

        if ((f32)FLOAT_NEG_MAX != joint->unk_dobj_0x74)
        {
            func_ovl3_801485CC(joint, unk_vec, fp->status_vars.common.guard.shield_rotate_range);

            joint->unk_dobj_0x74 = (f32)FLOAT_NEG_MAX;
        }
    }
    func_ovl3_80148408(fp);
    func_ovl2_800EB648(fp->joint[2]);
}

void func_ovl3_80148A88(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80148120(fp);
    func_ovl3_80148304(fighter_gobj);

    if (fp->shield_health == 0)
    {
        func_ovl3_80149510(fighter_gobj);
    }
    else
    {
        if (fighter_gobj->anim_frame <= 0.0F)
        {
            if (fp->status_vars.common.guard.is_release != FALSE)
            {
                if (fp->ft_kind == Ft_Kind_Yoshi)
                {
                    func_ovl3_801482E4(fighter_gobj);
                }
                func_ovl3_80148FF0(fighter_gobj);
            }
            else
            {
                if (fp->ft_kind == Ft_Kind_Yoshi)
                {
                    fp->status_vars.common.guard.effect_gobj = func_ovl2_80101374(fighter_gobj);

                    ftCommon_HideModelPartAll(fighter_gobj);
                    func_ovl3_80148214(fighter_gobj);

                    fp->is_shield = TRUE;

                    func_ovl3_80148714(fighter_gobj);
                }
                func_ovl3_80148DDC(fighter_gobj);
            }
        }
        else func_ovl3_80148714(fighter_gobj);
    }
}

void func_ovl3_80148B84(GObj *fighter_gobj)
{
    if (!ftStatus_CheckInterruptGuard(fighter_gobj))
    {
        func_ovl3_80142258(fighter_gobj);
    }
}

void func_ovl3_80148BFC(GObj *fighter_gobj, s32 slide_frames)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_GuardOn, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    if (fp->shield_health != 0)
    {
        if (fp->ft_kind == Ft_Kind_Yoshi)
        {
            func_ovl3_80148144(fighter_gobj);
        }
        else
        {
            fp->status_vars.common.guard.effect_gobj = func_ovl2_80101108(fighter_gobj);
            fp->is_shield = TRUE;
        }
    }
    func_ovl3_80148714(fighter_gobj);
    fp->status_vars.common.guard.release_lag = FTCOMMON_GUARD_RELEASE_LAG;
    fp->status_vars.common.guard.shield_decay_wait = FTCOMMON_GUARD_DECAY_INT;
    fp->status_vars.common.guard.is_release = FALSE;
    fp->status_vars.common.guard.slide_frames = slide_frames;
    fp->status_vars.common.guard.is_setoff = FALSE;

    func_800269C0(0xDU);
}

bool32 func_ovl3_80148CBC(GObj *fighter_gobj, s32 slide_frames)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->input.pl.button_hold & fp->input.button_mask_z) && (fp->shield_health != 0))
    {
        func_ovl3_80148BFC(fighter_gobj, slide_frames);

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80148D0C(GObj *fighter_gobj)
{
    return func_ovl3_80148CBC(fighter_gobj, 0);
}

bool32 func_ovl3_80148D2C(GObj *fighter_gobj, s32 slide_frames)
{
    return func_ovl3_80148CBC(fighter_gobj, slide_frames);
}

void func_ovl3_80148D4C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80148120(fp);
    func_ovl3_80148304(fighter_gobj);

    if (fp->shield_health == 0)
    {
        func_ovl3_80149510(fighter_gobj);
    }
    else if ((fp->status_vars.common.guard.is_release != FALSE) || !(fp->is_shield))
    {
        func_ovl3_80148FF0(fighter_gobj);
    }
    else func_ovl3_8014889C(fighter_gobj);
}

void func_ovl3_80148DDC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_Guard, 0.0F, 1.0F, 0x34U);
    func_ovl3_8014889C(fighter_gobj);

    fp->is_shield = TRUE;
}
