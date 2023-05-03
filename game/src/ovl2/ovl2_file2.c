#include "fighter.h"
#include "ftkirby.h"

void func_ovl2_800D78E8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 i;

    if (fp->is_statupdate_stop_gfx)
    {
        func_ovl2_800E9C3C(fighter_gobj);
    }

    for (i = 0; i < ARRAY_COUNT(fp->joint); i++)
    {
        if (fp->joint[i] != NULL)
        {
            UnkDObjData *temp_s0 = fp->joint[i]->unk_0x84;

            if (temp_s0->unk_gobj != NULL)
            {
                func_80009A84(temp_s0->unk_gobj);
            }
            func_ovl2_800D767C(temp_s0);
        }
    }
    func_ovl2_800D75EC(fp);
    func_80009A84(fighter_gobj);
}

void func_ovl2_800D7994(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    switch (fp->ft_kind)
    {
    case Ft_Kind_Kirby:
    case Ft_Kind_PolyKirby:
        func_ovl3_80164650(fighter_gobj);
        break;

    case Ft_Kind_Link:
    case Ft_Kind_PolyLink:
        func_ovl3_801636D0(fighter_gobj);
        break;
    }
}

extern intptr_t ftKirby_LoadedFiles_SpecialNData;
extern s32 gmMatchInfo_PlayerCount;
extern void *D_ovl2_80131074; // Pointer to fighter files?

void func_ovl2_800D79F0(GObj *fighter_gobj, ftSpawnInfo *spawn)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    f32 scale;

    fp->lr = spawn->lr_spawn;
    fp->percent_damage = spawn->damage;

    if (fp->status_info.pl_kind != 3)
    {
        Match_Info->player_block[fp->port_id].stock_damage_all = fp->percent_damage;
    }
    fp->shield_health = (fp->ft_kind == Ft_Kind_Yoshi) ? 55 : 55;

    fp->unk_ft_0x38 = 0.0F;
    fp->hitlag_timer = 0;
    fp->x192_flag_b6 = FALSE;

    func_ovl2_800D9444(fighter_gobj);

    fp->jumps_used = 0;
    fp->is_reflect = FALSE;
    fp->is_absorb = FALSE;
    fp->x18F_flag_b2 = FALSE;
    fp->is_statupdate_stop_gfx = FALSE;
    fp->x18F_flag_b4 = FALSE;

    fp->cliffcatch_wait = 0;
    fp->time_since_last_z = 0;
    fp->timer_unk3 = 0;

    fp->tornado_wait = fp->tarucann_wait = 0;

    fp->unk_0x170 = 0;
    fp->unk_ft_0x7AC = 0;
    fp->unk_0x7B0 = 0;
    fp->attack_hit_count = 0;
    fp->attack_damage = 0;
    fp->shield_damage = 0;
    fp->unk_ft_0x7DC = 0;
    fp->damage_taken_recent = 0;
    fp->damage_port_id = -1;
    fp->unk_ft_0x820 = 0;
    fp->unk_ft_0x824 = 0;
    fp->unk_0x810 = 0;
    fp->unk_ft_0x814 = 0;
    fp->unk_0x818 = 0;
    fp->unk_0x804 = 0;
    fp->unk_ft_0x5A4 = 0;
    fp->unk_ft_0x5A8 = 0;
    fp->unk_ft_0x5B0 = 0;

    fp->hit_status = gmHitCollision_HitStatus_Normal;
    fp->special_status = 1;
    fp->unk_ft_0x5AC = 1;

    fp->throw_gobj = NULL;
    fp->catch_gobj = NULL;
    fp->capture_gobj = NULL;
    fp->x192_flag_b3 = FALSE;

    fp->item_hold = NULL;

    fp->lr_reflect = CENTER;
    fp->lr_absorb = CENTER;

    fp->unk_ft_0x7D8 = 0;
    fp->special_hit = NULL;

    fp->attack1_followup_frames = 0.0F;
    fp->unk_ft_0x7A0 = 0.0F;
    fp->attack_knockback = 0.0F;
    fp->attack_damage_stale = 0.0F;
    fp->damage_knockback_again = 0.0F;
    fp->knockback_resist_status = 0.0F;
    fp->knockback_resist_passive = 0.0F;
    fp->damage_knockback = 0.0F;
    fp->unk_ft_0x7A4 = 1.0F;
    fp->unk_ft_0x7A8 = 10.0F;

    fp->is_fast_fall = FALSE;

    fp->player_number = gmMatchInfo_PlayerCount++;

    fp->publicity_knockback = 0.0F;

    fp->is_hitstun = FALSE;
    fp->x190_flag_b3 = FALSE;

    fp->unk_ft_0x272 = fp->unk_ft_0x273 = 0;

    fp->x192_flag_b4 = FALSE;

    fp->unk_0x274 = 0;
    fp->unk_0x276 = 0;

    fp->attack_id = 0;
    fp->flags_hi.halfword = 0;
    fp->flags_lw.flags_0x3FF = 0;
    fp->flags_lw.flags_0x1000 = fp->flags_lw.flags_0x800 = fp->flags_lw.flags_0x400 = FALSE;

    fp->unk_0x290.halfword = fp->unk_ft_0x82A.halfword = 0;
    fp->unk_ft_0x828 = fp->flags_lw;

    fp->unk_0xA9E = 0;

    DObjGetStruct(fighter_gobj)->translate = spawn->pos;
    DObjGetStruct(fighter_gobj)->scale.x = DObjGetStruct(fighter_gobj)->scale.y = DObjGetStruct(fighter_gobj)->scale.z = attributes->size_mul;

    if (fp->status_info.pl_kind != 3)
    {
        bool32 is_collide_ground = func_ovl2_800F9348(&DObjGetStruct(fighter_gobj)->translate, &fp->coll_data.ground_line_id, &fp->coll_data.ground_dist, &fp->coll_data.clip_flag, &fp->coll_data.ground_angle.x);

        if (is_collide_ground == FALSE)
        {
            fp->coll_data.ground_line_id = -1;
        }
        if ((is_collide_ground != 0) && (fp->coll_data.ground_dist > -300.0F) && (fp->ft_kind != Ft_Kind_MasterHand))
        {
            fp->ground_or_air = ground;

            DObjGetStruct(fighter_gobj)->translate.y += fp->coll_data.ground_dist;

            fp->coll_data.ground_dist = 0;
        }
        else
        {
            fp->ground_or_air = air;
            fp->jumps_used = 1;
        }
    }
    else
    {
        fp->ground_or_air = air;
        fp->jumps_used = 1;
    }

    fp->coll_data.pos_curr = DObjGetStruct(fighter_gobj)->translate;

    switch (fp->ft_kind)
    {
    case Ft_Kind_MetalMario:
        fp->knockback_resist_passive = 30.0F;

    case Ft_Kind_Mario:
    case Ft_Kind_PolyMario:
        fp->fighter_vars.mario.is_tornado_charge = FALSE;
        break;

    case Ft_Kind_GiantDonkey:
        fp->knockback_resist_passive = 48.0F;

    case Ft_Kind_Donkey:
    case Ft_Kind_PolyDonkey:
        fp->fighter_vars.donkey.charge_level = 0;
        break;

    case Ft_Kind_Samus:
    case Ft_Kind_PolySamus:
        fp->fighter_vars.samus.charge_level = 0;
        fp->fighter_vars.samus.charge_recoil = 0;
        break;

    case Ft_Kind_Luigi:
    case Ft_Kind_PolyLuigi:
        fp->fighter_vars.mario.is_tornado_charge = FALSE;
        break;

    case Ft_Kind_Captain:
    case Ft_Kind_PolyCaptain:
        fp->fighter_vars.captain.falcon_punch_unk = 0;
        break;

    case Ft_Kind_Kirby:
    case Ft_Kind_PolyKirby:

        fp->fighter_vars.kirby.copy_id = spawn->ft_kind;
        fp->fighter_vars.kirby.copysamus_charge_level = 0;
        fp->fighter_vars.kirby.copysamus_charge_recoil = 0;
        fp->fighter_vars.kirby.copydonkey_charge_level = 0;
        fp->fighter_vars.kirby.copycaptain_falcon_punch_unk = 0;
        fp->fighter_vars.kirby.copypurin_unk = 0;
        fp->fighter_vars.kirby.copylink_boomerang_gobj = NULL;

        if (spawn->ft_kind == Ft_Kind_Kirby)
        {
            fp->fighter_vars.kirby.copy_bool_unk = FALSE;
        }
        else fp->fighter_vars.kirby.copy_bool_unk = TRUE;

        if (fp->ft_kind == Ft_Kind_Kirby)
        {
            ftKirbyCopyData *copy_data = (ftKirbyCopyData*) ((uintptr_t)D_ovl2_80131074 + (intptr_t)&ftKirby_LoadedFiles_SpecialNData);

            func_ovl2_800E8EAC(fighter_gobj, 6, copy_data[fp->fighter_vars.kirby.copy_id].unk_0x2);
        }
        break;

    case Ft_Kind_Link:
    case Ft_Kind_PolyLink:
        fp->fighter_vars.link.boomerang_gobj = NULL;

        func_ovl2_800E8EAC(fighter_gobj, 0x15, -1);
        func_ovl2_800E8EAC(fighter_gobj, 0x13, 0);
        break;

    case Ft_Kind_Purin:
    case Ft_Kind_PolyPurin:
        fp->fighter_vars.purin.unk_0x0 = 0U;
        break;

    case Ft_Kind_MasterHand:
        fp->fighter_vars.masterhand.p_masterhand = &fp->fighter_vars.masterhand.s;
        fp->fighter_vars.masterhand.p_masterhand->unk_0xC = 1.0F;
        fp->fighter_vars.masterhand.p_masterhand->unk_0x14 = -1;
        fp->fighter_vars.masterhand.p_masterhand->unk_0x15 = -1;
        fp->fighter_vars.masterhand.p_masterhand->unk_0x16 = 0;

        if (fp->status_info.pl_kind != 3)
        {
            func_ovl3_80158428(fighter_gobj);
            func_ovl3_80158634(fighter_gobj);
        }
        break;
    }
    func_ovl2_800E8518(fighter_gobj);
    func_ovl2_800E880C(fighter_gobj, 1);
    func_ovl2_800E98B0(fighter_gobj);
}
