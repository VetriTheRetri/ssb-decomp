#include "fighter.h"
#include "article.h"
#include "gmground.h"

void func_ovl3_80143E10(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.tarucann.shoot_wait != 0)
    {
        fp->status_vars.common.tarucann.shoot_wait--;

        if (fp->status_vars.common.tarucann.shoot_wait == (FTCOMMON_TARUCANN_SHOOT_WAIT / 2))
        {
            func_800269C0(0x119U);
        }
        if (fp->status_vars.common.tarucann.shoot_wait == 0)
        {
            func_ovl3_80144038(fighter_gobj);

            return;
        }
    }
    fp->status_vars.common.tarucann.release_wait++;

    if ((fp->status_vars.common.tarucann.release_wait >= FTCOMMON_TARUCANN_RELEASE_WAIT) && (fp->status_vars.common.tarucann.shoot_wait == 0))
    {
        fp->status_vars.common.tarucann.shoot_wait = FTCOMMON_TARUCANN_SHOOT_WAIT;

        func_ovl2_80109D20(fp->status_vars.common.tarucann.tarucann_gobj);
    }
}

void func_ovl3_80143EB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->status_vars.common.tarucann.shoot_wait == 0) && (fp->input.pl.button_tap & (fp->input.button_mask_a | fp->input.button_mask_b)))
    {
        fp->status_vars.common.tarucann.shoot_wait = FTCOMMON_TARUCANN_SHOOT_WAIT;

        func_ovl2_80109D20(fp->status_vars.common.tarucann.tarucann_gobj);
    }
}

void func_ovl3_80143F04(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *tarucann_gobj = fp->status_vars.common.tarucann.tarucann_gobj;

    DObjGetStruct(fighter_gobj)->translate = DObjGetStruct(tarucann_gobj)->translate;
}

void func_ovl3_80143F30(GObj *fighter_gobj, GObj *tarucann_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f vel;

    ftCommon_ProcDamageStopVoice(fighter_gobj);

    if ((fp->item_hold != NULL) && !(ArticleGetStruct(fp->item_hold)->is_light_throw))
    {
        vel.x = vel.y = vel.z = 0.0F;

        func_ovl3_80172AEC(fp->item_hold, &vel, ARTICLE_STALE_DEFAULT);
    }
    if (fp->catch_gobj != NULL)
    {
        func_ovl3_8014B330(fp->catch_gobj);

        fp->catch_gobj = NULL;
    }
    else if (fp->capture_gobj != NULL)
    {
        func_ovl3_8014AECC(fp->capture_gobj, fighter_gobj);
    }
    
    ftStatus_Update(fighter_gobj, ftStatus_Common_TaruCann, 0.0F, 0.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl2_800D9444(fighter_gobj);

    fp->status_vars.common.tarucann.shoot_wait = 0;
    fp->status_vars.common.tarucann.release_wait = 0;
    fp->status_vars.common.tarucann.tarucann_gobj = tarucann_gobj;

    ftCommon_SetHitStatusAll(fighter_gobj, 3);

    fp->is_invisible = TRUE;

    ftCommon_SetCatchIgnoreMask(fp, FTCATCHKIND_MASK_ALL);
    func_800269C0(0x11AU);
}

extern intptr_t D_NF_00000014;
extern intptr_t D_NF_000000BC;

void func_ovl3_80144038(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftThrowHitDesc *tarucann = (ftThrowHitDesc *)(((uintptr_t)Ground_Info - (intptr_t)&D_NF_00000014) + (intptr_t)&D_NF_000000BC); // Linker thing
    f32 knockback;
    s32 angle;

    DObjGetStruct(fighter_gobj)->translate.z = 0.0F;

    knockback = grMapObject_DamageCalcKnockback(fp->percent_damage, tarucann->damage, tarucann->damage, tarucann->knockback_weight, tarucann->knockback_scale, tarucann->knockback_base, fp->attributes->weight, 9, 9);

    angle = ((I_RAD_TO_DEG(func_ovl2_8010A12C()) * -fp->lr) + 90);
    angle -= (angle / 360) * 360;

    ftCommon_Damage_InitDamageVars(fighter_gobj, ftStatus_Common_DamageFlyRoll, tarucann->damage, knockback, angle, fp->lr, 0, tarucann->element, 0, TRUE, TRUE, FALSE);
    ftCommon_Update1PGameDamageStats(fp, 4, 4, 3, 0, 0);

    fp->unk_0x174 = 0;
    fp->tarucann_wait = FTCOMMON_TARUCANN_PICKUP_WAIT;
}