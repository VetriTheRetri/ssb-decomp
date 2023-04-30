#include "fighter.h"

void func_ovl3_8014ADB0(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *interact_gobj;
    Fighter_Struct *interact_fp;
    Vec3f pos;

    if (this_fp->x192_flag_b3)
    {
        interact_gobj = this_fp->catch_gobj;
    }
    else interact_gobj = this_fp->capture_gobj;

    interact_fp = FighterGetStruct(interact_gobj);

    if ((this_fp->status_info.status_id >= ftStatus_Common_ThrownDonkeyF) && (this_fp->status_info.status_id <= ftStatus_Common_ThrownFoxB))
    {
        pos.x = pos.y = pos.z = 0.0F;

        func_ovl2_800EDF24(this_fp->joint[4], &pos);

        pos.y -= 300.0F;

        DObjGetStruct(fighter_gobj)->translate = pos;
    }
    func_ovl2_800DF014(fighter_gobj, &DObjGetStruct(interact_gobj)->translate, &interact_fp->coll_data);

    if ((this_fp->ground_or_air == ground) && ((this_fp->coll_data.ground_line_id == -1) || (this_fp->coll_data.unk_0x78 != 0.0F)))
    {
        func_ovl2_800DEEC8(this_fp);
    }
}

void func_ovl3_8014AECC(GObj *fighter_gobj, GObj *interact_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *interact_fp = FighterGetStruct(interact_gobj);

    if (this_fp->x192_flag_b3)
    {
        func_ovl3_8014ADB0(fighter_gobj);
    }
    else func_ovl3_8014ADB0(interact_gobj);

    interact_fp->capture_gobj = NULL;
    this_fp->catch_gobj = NULL;
}

void func_ovl3_8014AF2C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *interact_gobj = fp->catch_gobj;

    if (interact_gobj != NULL)
    {
        func_ovl3_8014AECC(fighter_gobj, interact_gobj);

        goto next;
    }
    else interact_gobj = fp->capture_gobj;

    if (interact_gobj != NULL)
    {
        func_ovl3_8014AECC(interact_gobj, fighter_gobj);

    next:
        func_ovl2_800DEE54(fighter_gobj);
        func_ovl2_800DEE54(interact_gobj);
    }
}

static s32 D_ovl3_8018CF80; // Static (.bss)

void func_ovl3_8014AF98(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E80C4(fp, fp->capture_gobj);

    fp->status_vars.common.damage.unk_index = D_ovl3_8018CF80;
}

void func_ovl3_8014AFD0(GObj *fighter_gobj, s32 lr, s32 unk_index, bool32 is_cb_status)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
    ftThrowHitDesc *ft_throw;
    f32 knockback_final;
    s32 damage;
    f32 knockback_resist;
    f32 knockback_calc;

    knockback_resist = (this_fp->knockback_resist_status < this_fp->knockback_resist_passive) ? this_fp->knockback_resist_passive : this_fp->knockback_resist_status;

    D_ovl3_8018CF80 = unk_index;

    if (this_fp->hit_status != gmHitCollision_HitStatus_Normal)
    {
        func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Normal);
    }
    if (!(this_fp->x192_flag_b3))
    {
        func_ovl3_8014ADB0(fighter_gobj);
    }
    func_ovl2_800DEEC8(this_fp);

    ft_throw = capture_fp->fighter_throw;

    knockback_calc = func_ovl2_800E9D78(this_fp->percent_damage, ft_throw->damage, ft_throw->damage, ft_throw->knockback_weight, ft_throw->knockback_scale, ft_throw->knockback_base, this_fp->attributes->weight, capture_fp->handicap, this_fp->handicap);

    knockback_final = knockback_calc - knockback_resist;

    if (knockback_calc <= knockback_resist)
    {
        knockback_final = 0.0F;
    }
    damage = func_ovl2_800EA54C(capture_fp->port_id, ft_throw->damage, capture_fp->attack_id, capture_fp->flags_hi.halfword);

    if (capture_fp->x192_flag_b5)
    {
        damage = ((damage * 0.5F) + 0.999F);
    }
    if (func_ovl2_800E8AAC(fighter_gobj) != 1)
    {
        damage = 0;
    }
    if (is_cb_status != FALSE)
    {
        this_fp->cb_status = func_ovl3_8014AF98;
    }
    func_ovl3_80140EE4(fighter_gobj, ft_throw->status_id, damage, knockback_final, ft_throw->angle, lr, 1, ft_throw->element, capture_fp->player_number, TRUE, TRUE, TRUE);
    func_ovl2_800EAA2C(this_fp, capture_fp->port_id, 1, capture_fp->ft_kind, capture_fp->flags_lw.halfword, capture_fp->unk_0x290.halfword);

    if (damage != 0)
    {
        func_ovl2_800EA248(this_fp, damage);
        func_ovl2_800EA98C(capture_fp->port_id, this_fp->port_id, damage);
        func_ovl2_800EA614(capture_fp->port_id, this_fp->port_id, capture_fp->attack_id, capture_fp->flags_hi.halfword);

        if ((s32) ((damage * 0.75F) + 4.0F) > 0)
        {
            func_ovl2_800E806C(this_fp, 0, (s32) ((damage * 0.75F) + 4.0F));
        }
        if ((s32) ((damage * 0.5F) + 2.0F) > 0)
        {
            func_ovl2_800E806C(capture_fp, 5, (s32) ((damage * 0.5F) + 2.0F));
        }
    }
    this_fp->capture_gobj = NULL;
}

void func_ovl3_8014B2AC(Fighter_Struct *this_fp)
{
    GObj *capture_gobj = this_fp->capture_gobj;
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
    ftThrowHitDesc *ft_throw = &capture_fp->fighter_throw[1];
    s32 damage = func_ovl2_800EA54C(capture_fp->port_id, ft_throw->damage, capture_fp->attack_id, capture_fp->flags_hi.halfword);

    func_ovl2_800EA248(this_fp, damage);
    func_ovl2_800EA98C(capture_fp->port_id, this_fp->port_id, damage);
    func_ovl2_800EA614(capture_fp->port_id, this_fp->port_id, capture_fp->attack_id, capture_fp->flags_hi.halfword);
}

void func_ovl3_8014B330(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *capture_gobj = this_fp->capture_gobj;
    Fighter_Struct *capture_fp = FighterGetStruct(capture_gobj);
    ftThrowHitDesc *ft_throw;
    f32 knockback_final;
    s32 lr;
    s32 damage;
    f32 knockback_resist;
    f32 knockback_calc;

    knockback_resist = (this_fp->knockback_resist_status < this_fp->knockback_resist_passive) ? this_fp->knockback_resist_passive : this_fp->knockback_resist_status;

    if (this_fp->hit_status != gmHitCollision_HitStatus_Normal)
    {
        func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Normal);
    }
    if (!(this_fp->x192_flag_b3))
    {
        func_ovl3_8014ADB0(fighter_gobj);
    }
    if (this_fp->ground_or_air == air)
    {
        func_ovl2_800DEEC8(this_fp);
    }
    ft_throw = &capture_fp->fighter_throw[1];

    knockback_calc = func_ovl2_800E9D78(this_fp->percent_damage, ft_throw->damage, ft_throw->damage, ft_throw->knockback_weight, ft_throw->knockback_scale, ft_throw->knockback_base, this_fp->attributes->weight, capture_fp->handicap, this_fp->handicap);

    knockback_final = knockback_calc - knockback_resist;

    if (knockback_calc <= knockback_resist)
    {
        knockback_final = 0.0F;
    }
    lr = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(capture_gobj)->translate.x) ? RIGHT : LEFT;

    damage = func_ovl2_800EA54C(capture_fp->port_id, ft_throw->damage, capture_fp->attack_id, capture_fp->flags_hi.halfword);;

    if (capture_fp->x192_flag_b5)
    {
        damage = ((damage * 0.5F) + 0.999F);
    }

    if (func_ovl2_800E8AAC(fighter_gobj) != 1)
    {
        damage = 0;
    }
    func_ovl3_80140EE4(fighter_gobj, ft_throw->status_id, damage, knockback_final, ft_throw->angle, lr, 1, gmHitCollision_Element_Normal, capture_fp->player_number, FALSE, FALSE, TRUE);
    func_ovl2_800EAA2C(this_fp, capture_fp->port_id, 1, capture_fp->ft_kind, capture_fp->flags_lw.halfword, capture_fp->unk_0x290.halfword);

    if (damage != 0)
    {
        func_ovl2_800EA248(this_fp, damage);
        func_ovl2_800EA98C(capture_fp->port_id, this_fp->port_id, damage);
        func_ovl2_800EA614(capture_fp->port_id, this_fp->port_id, capture_fp->attack_id, capture_fp->flags_hi.halfword);
    }
    this_fp->capture_gobj = NULL;
}

ftThrowHitDesc Fighter_ThrowHitDesc_Default = { -1, 0, 361, 0, 0, 20, 0 };

void func_ovl3_8014B5B4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftThrowHitDesc *ft_throw = &Fighter_ThrowHitDesc_Default;
    f32 knockback_calc;
    f32 knockback_resist;
    f32 knockback_final;

    if (fp->knockback_resist_status < fp->knockback_resist_passive)
    {
        knockback_resist = fp->knockback_resist_passive;
    }
    else knockback_resist = fp->knockback_resist_status;

    DObjGetStruct(fighter_gobj)->translate.z = 0.0F;

    knockback_calc = func_ovl2_800E9D78(fp->percent_damage, ft_throw->damage, ft_throw->damage, ft_throw->knockback_weight, ft_throw->knockback_scale, ft_throw->knockback_base, fp->attributes->weight, 9, fp->handicap);

    knockback_final = knockback_calc - knockback_resist;

    if (knockback_calc <= knockback_resist)
    {
        knockback_final = 0.0F;
    }
    func_ovl3_80140EE4(fighter_gobj, ft_throw->status_id, 0, knockback_final, ft_throw->angle, fp->lr, 1, ft_throw->element, 0, TRUE, TRUE, FALSE);
    func_ovl2_800EAA2C(fp, 4, 0, 0, 0, 0);
}