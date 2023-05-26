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

    if (fp->status_info.pl_kind != Pl_Kind_Result)
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
    fp->is_shield = FALSE;
    fp->is_statupdate_stop_gfx = FALSE;
    fp->x18F_flag_b4 = FALSE;

    fp->cliffcatch_wait = 0;
    fp->time_since_last_z = 0;
    fp->acid_wait = 0;

    fp->tornado_wait = fp->tarucann_wait = 0;

    fp->hotfloor_wait = 0;
    fp->unk_ft_0x7AC = 0;
    fp->attack_damage = 0;
    fp->attack_hit_count = 0;
    fp->shield_attack_damage = 0;
    fp->shield_damage = 0;
    fp->unk_ft_0x7DC = 0;
    fp->damage_taken_recent = 0;
    fp->damage_port_id = -1;
    fp->unk_ft_0x820 = 0;
    fp->unk_ft_0x824 = 0;
    fp->unk_0x810 = 0;
    fp->unk_ft_0x814 = 0;
    fp->damage_heal = 0;
    fp->damage_joint_index = 0;
    fp->invincible_timer = 0;
    fp->walldamage_nohit_timer = 0;
    fp->star_invincible_timer = 0;

    fp->hit_status = gmHitCollision_HitStatus_Normal;
    fp->special_status = ftSpecialStatus_Normal;
    fp->special_hit_status = gmHitCollision_HitStatus_Normal;

    fp->throw_gobj = NULL;
    fp->catch_gobj = NULL;
    fp->capture_gobj = NULL;
    fp->x192_flag_b3 = FALSE;

    fp->item_hold = NULL;

    fp->lr_reflect = CENTER;
    fp->lr_absorb = CENTER;

    fp->reflect_damage = 0;
    fp->special_hit = NULL;

    fp->attack1_followup_frames = 0.0F;
    fp->unk_ft_0x7A0 = 0.0F;
    fp->attack_knockback = 0.0F;
    fp->attack_rebound = 0.0F;
    fp->damage_knockback_again = 0.0F;
    fp->knockback_resist_status = 0.0F;
    fp->knockback_resist_passive = 0.0F;
    fp->damage_knockback = 0.0F;
    fp->hitlag_mul = 1.0F;
    fp->shield_lifeup_wait = 10.0F;

    fp->is_fast_fall = FALSE;

    fp->player_number = gmMatchInfo_PlayerCount++;

    fp->publicity_knockback = 0.0F;

    fp->is_hitstun = FALSE;
    fp->x190_flag_b3 = FALSE;

    fp->shuffle_frame_index = fp->shuffle_index_max = 0;

    fp->x192_flag_b4 = FALSE;

    fp->is_shuffle_electric = 0;
    fp->shuffle_timer = 0;

    fp->attack_id = 0;
    fp->flags_hi.halfword = 0;
    fp->flags_lw.flags_0x3FF = 0;
    fp->flags_lw.flags_0x1000 = fp->flags_lw.flags_0x800 = fp->flags_lw.flags_0x400 = FALSE;

    fp->unk_0x290.halfword = fp->unk_ft_0x82A.halfword = 0;
    fp->unk_ft_0x828 = fp->flags_lw;

    fp->afterimage.desc_index = 0;

    DObjGetStruct(fighter_gobj)->translate = spawn->pos;
    DObjGetStruct(fighter_gobj)->scale.x = DObjGetStruct(fighter_gobj)->scale.y = DObjGetStruct(fighter_gobj)->scale.z = attributes->size_mul;

    if (fp->status_info.pl_kind != Pl_Kind_Result)
    {
        bool32 is_collide_ground = func_ovl2_800F9348(&DObjGetStruct(fighter_gobj)->translate, &fp->coll_data.ground_line_id, &fp->coll_data.ground_dist, &fp->coll_data.ground_flags, &fp->coll_data.ground_angle.x);

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
        fp->fighter_vars.mario.is_expend_tornado = FALSE;
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
        fp->fighter_vars.mario.is_expend_tornado = FALSE;
        break;

    case Ft_Kind_Captain:
    case Ft_Kind_PolyCaptain:
        fp->fighter_vars.captain.falcon_punch_unk = 0;
        break;

    case Ft_Kind_Kirby:
    case Ft_Kind_PolyKirby:

        fp->fighter_vars.kirby.copy_id = spawn->copy_kind;
        fp->fighter_vars.kirby.copysamus_charge_level = 0;
        fp->fighter_vars.kirby.copysamus_charge_recoil = 0;
        fp->fighter_vars.kirby.copydonkey_charge_level = 0;
        fp->fighter_vars.kirby.copycaptain_falcon_punch_unk = 0;
        fp->fighter_vars.kirby.copypurin_unk = 0;
        fp->fighter_vars.kirby.copylink_boomerang_gobj = NULL;

        if (spawn->copy_kind == Ft_Kind_Kirby)
        {
            fp->fighter_vars.kirby.copy_bool_unk = FALSE;
        }
        else fp->fighter_vars.kirby.copy_bool_unk = TRUE;

        if (fp->ft_kind == Ft_Kind_Kirby)
        {
            ftKirbyCopyData *copy_data = (ftKirbyCopyData*) ((uintptr_t)D_ovl2_80131074 + (intptr_t)&ftKirby_LoadedFiles_SpecialNData);

            ftCommon_SetModelPartRenderState(fighter_gobj, 6, copy_data[fp->fighter_vars.kirby.copy_id].unk_0x2);
        }
        break;

    case Ft_Kind_Link:
    case Ft_Kind_PolyLink:
        fp->fighter_vars.link.boomerang_gobj = NULL;

        ftCommon_SetModelPartRenderState(fighter_gobj, 0x15, -1);
        ftCommon_SetModelPartRenderState(fighter_gobj, 0x13, 0);
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

        if (fp->status_info.pl_kind != Pl_Kind_Result)
        {
            func_ovl3_80158428(fighter_gobj);
            func_ovl3_80158634(fighter_gobj);
        }
        break;
    }
    ftCommon_ClearHitAll(fighter_gobj);
    ftCommon_SetHitStatusPartAll(fighter_gobj, 1);
    func_ovl2_800E98B0(fighter_gobj);
}

extern ftData *Fighter_FileData_ContainerList[Ft_Kind_EnumMax] =
{
    D_ovl2_80117810,
    D_ovl2_801196F4,
    D_ovl2_8011AC8C,
    D_ovl2_8011CC78,
    D_ovl2_8011E0A0,
    D_ovl2_8011F520,
    D_ovl2_801209D0,
    D_ovl2_80121E98,
    D_ovl2_80123680,
    D_ovl2_80124CE4,
    D_ovl2_8012617C,
    D_ovl2_801276A0,
    D_ovl2_80128C7C,
    D_ovl2_80118220,
    D_ovl2_80118C30,
    D_ovl2_8011A1B4,
    D_ovl2_8011B76C,
    D_ovl2_8011D698,
    D_ovl2_8011EAB0,
    D_ovl2_8011FF90,
    D_ovl2_80121410,
    D_ovl2_80122918,
    D_ovl2_8012427C,
    D_ovl2_8012572C,
    D_ovl2_80126BCC,
    D_ovl2_80128170,
    D_ovl2_8011C24C
};
extern u16 D_ovl2_80131398;

GObj* func_ovl2_800D7F3C(ftSpawnInfo *spawn) // Create fighter
{
    Fighter_Struct *fp;
    GObj *fighter_gobj;
    s32 i;
    UnkDObjData *dobj_unk;
    ftCommonAttributes *attributes;
    GObj *unk_dobj_gobj;
    DObj *topn_joint;
    UnkFighterDObjData *unk_ft_dobj;

    fighter_gobj = func_80009968(0x3E8U, NULL, 3U, 0x80000000U);

    func_80009DF4(fighter_gobj, spawn->unk_rebirth_0x3C, 9, 0x80000000, -1);

    fp = func_ovl2_800D7594();

    fighter_gobj->user_data = fp;

    fp->status_info.pl_kind = spawn->pl_kind;
    fp->this_fighter = fighter_gobj;
    fp->ft_kind = spawn->ft_kind;
    fp->ft_data = Fighter_FileData_ContainerList[fp->ft_kind];
    attributes = fp->attributes = (ftCommonAttributes*) ((uintptr_t)*fp->ft_data->p_file + (intptr_t)fp->ft_data->o_attributes);
    fp->x9D0 = spawn->unk_rebirth_0x38;
    fp->team = spawn->team;
    fp->port_id = spawn->port_id;
    fp->stock_count = spawn->stock_count;

    if (fp->status_info.pl_kind != Pl_Kind_Result)
    {
        Match_Info->player_block[fp->port_id].stock_count = spawn->stock_count;
    }
    fp->lod_current = fp->lod_match = spawn->model_lod;

    fp->costume_id = spawn->costume_id;
    fp->shade_id = spawn->shade_id;

    fp->shade.r = (attributes->shade_color[fp->shade_id - 1].r * attributes->shade_color[fp->shade_id - 1].a) / 255;
    fp->shade.g = (attributes->shade_color[fp->shade_id - 1].g * attributes->shade_color[fp->shade_id - 1].a) / 255;
    fp->shade.b = (attributes->shade_color[fp->shade_id - 1].b * attributes->shade_color[fp->shade_id - 1].a) / 255;

    fp->handicap = spawn->handicap;
    fp->cp_level = spawn->cp_level;

    fp->unk_0x178 = 0;
    fp->x3C_unk = 0;
    fp->anim_flags.word = 0;

    fp->p_sfx = NULL;
    fp->sfx_id = 0;
    fp->p_voice = NULL;
    fp->voice_id = 0;
    fp->p_loop_sfx = NULL;
    fp->loop_sfx_id = 0;

    fp->x18E_flag_4bit = 0;

    fp->is_invisible = FALSE;
    fp->x18E_flag_b0 = FALSE;

    fp->display_state = 0;

    fp->is_playing_sfx = FALSE;
    fp->x191_flag_b0 = FALSE;

    fp->proc_status = NULL;

    fp->unk_ft_0x149 = spawn->unk_rebirth_0x1C;
    fp->unk_0x15 = spawn->unk_rebirth_0x1E;
    fp->unk_0x16 = 9;

    fp->x18E_flag_b2 = spawn->unk_rebirth_0x1F_b2;

    fp->status_info.status_time_spent = 0;

    fp->fighter_cam_zoom_frame = attributes->cam_zoom;
    fp->fighter_cam_zoom_range = 1.0F;

    fp->x18E_flag_b4 = FALSE;
    fp->is_check_blastzone = FALSE;

    fp->x18F_flag_b5 = (attributes->unk_0x324 != NULL) ? TRUE : FALSE;

    for (i = 0; i < ARRAY_COUNT(fp->joint); i++)
    {
        fp->joint[i] = NULL;
    }
    topn_joint = func_800092D0(fighter_gobj, NULL);
    fp->joint[0] = topn_joint;
    func_ovl0_800C89BC(topn_joint, 0x4BU, 0U, 0U);
    fp->joint[0]->om_mtx[0]->unk05 = spawn->unk_rebirth_0x1D;

    func_ovl0_800C8DB4(fighter_gobj->obj, attributes->dobj_desc_container, fp->lod_current, &fp->joint[4], attributes->unk_ftca_0x29C, 0x4B, 0, 0, fp->costume_id, fp->unk_ft_0x149);

    for (i = 0; i < ARRAY_COUNT(fp->joint); i++)
    {
        if (fp->joint[i] != NULL)
        {
            fp->joint[i]->unk_0x84 = func_ovl2_800D7604();

            dobj_unk = fp->joint[i]->unk_0x84;
            dobj_unk->unk_0xC = attributes->dobj_desc_container[fp->lod_current - 1].unk_dobjcontain_0xC;
            dobj_unk->unk_0xD = i;

            if (fp->costume_id != 0)
            {
                if ((attributes->unk_0x32C != NULL) && (i == attributes->unk_0x32C->joint_index))
                {
                    unk_ft_dobj = attributes->unk_0x32C;

                    dobj_unk->unk_gobj = func_80009968(0x3E9U, NULL, 0xDU, 0x80000000U);

                    func_800092D0(dobj_unk->unk_gobj, unk_ft_dobj->unk_ftdobj_0x4);
                    func_ovl0_800C8CB8(dobj_unk->unk_gobj->obj, unk_ft_dobj->unk_ftdobj_0x8, unk_ft_dobj->unk_ftdobj_0xC, 0, fp->costume_id);
                }
            }
        }
    }
    for (i = 4; i < ARRAY_COUNT(fp->joint); i++)
    {
        if (fp->joint[i] != NULL)
        {
            fp->joint_render_state[i - 4][0] = fp->joint_render_state[i - 4][1] = (fp->joint[i]->display_list != NULL) ? 0 : -1;
        }
    }
    for (i = 0; i < ARRAY_COUNT(fp->unk_render); i++)
    {
        fp->unk_render[i][0] = fp->unk_render[i][1] = 0;
    }

    func_ovl2_800EB6EC(fp);

    fp->input.pl.stick_range.x = fp->input.pl.stick_range.y = fp->input.pl.stick_prev.x = fp->input.pl.stick_prev.y = fp->input.cp.stick_range.x = fp->input.cp.stick_range.y = 0;
    fp->input.pl.button_hold = fp->input.pl.button_tap = fp->input.cp.button_inputs = 0;

    fp->input.p_controller = spawn->p_controller;

    fp->input.button_mask_a = spawn->button_mask_a;
    fp->input.button_mask_b = spawn->button_mask_b;
    fp->input.button_mask_z = spawn->button_mask_z;
    fp->input.button_mask_l = spawn->button_mask_l;

    fp->tap_stick_x = fp->tap_stick_y = fp->hold_stick_x = fp->hold_stick_y = U8_MAX - 1;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hurt); i++)
    {
        if (attributes->fighter_hurt_desc[i].joint_index != -1)
        {
            fp->fighter_hurt[i].hit_status = gmHitCollision_HitStatus_Normal;
            fp->fighter_hurt[i].joint_index = attributes->fighter_hurt_desc[i].joint_index;
            fp->fighter_hurt[i].joint = fp->joint[fp->fighter_hurt[i].joint_index];
            fp->fighter_hurt[i].unk_ftht_0xC = attributes->fighter_hurt_desc[i].unk_fthdesc_0x4;
            fp->fighter_hurt[i].unk_ftht_0x10 = attributes->fighter_hurt_desc[i].unk_fthdesc_0x8;
            fp->fighter_hurt[i].offset = attributes->fighter_hurt_desc[i].offset;
            fp->fighter_hurt[i].size = attributes->fighter_hurt_desc[i].size;

            fp->fighter_hurt[i].size.x *= 0.5F;
            fp->fighter_hurt[i].size.y *= 0.5F;
            fp->fighter_hurt[i].size.z *= 0.5F;
        }
        else fp->fighter_hurt[i].hit_status = gmHitCollision_HitStatus_None;
    }
    fp->coll_data.p_translate = &DObjGetStruct(fighter_gobj)->translate;
    fp->coll_data.p_lr = &fp->lr;
    fp->coll_data.object_coll = attributes->object_coll;
    fp->coll_data.p_object_coll = &fp->coll_data.object_coll;
    fp->coll_data.cliffcatch_coll = attributes->cliffcatch_coll;
    fp->coll_data.ignore_line_id = -1;
    fp->coll_data.wall_flag = D_ovl2_80131398;
    fp->coll_data.coll_mask = 0;

    if (fp->status_info.pl_kind != Pl_Kind_Result)
    {
        func_80008188(fighter_gobj, func_ovl2_800E1260, 1U, 5U);
        func_80008188(fighter_gobj, func_ovl2_800E2604, 1U, 4U);
        func_80008188(fighter_gobj, func_ovl2_800E2660, 1U, 3U);
        func_80008188(fighter_gobj, func_ovl2_800E6100, 1U, 2U);
        func_80008188(fighter_gobj, func_ovl2_800E6178, 1U, 1U);
        func_80008188(fighter_gobj, func_ovl2_800E61EC, 1U, 0U);
    }
    else func_80008188(fighter_gobj, func_ovl1_80390584, 1U, 5U);

    func_ovl2_800D79F0(fighter_gobj, spawn);

    if (fp->status_info.pl_kind == 1)
    {
        func_unkmulti_8013A8A8(fighter_gobj);
    }
    if ((fp->status_info.pl_kind == 4) || (fp->status_info.pl_kind == 5))
    {
        fp->unk_0xA98 = 0;
        fp->unk_0xA94 = 0;
    }
    switch (fp->status_info.pl_kind)
    {
    case 3:
        func_ovl1_803905CC(fighter_gobj, 0x10000);
        break;

    case 4:
        func_ovl2_800DEE54(fighter_gobj);
        break;

    default:
        if (spawn->unk_rebirth_0x1F_b0)
        {
            func_ovl2_800DEE54(fighter_gobj);
            ftCommon_ResetControllerInputs(fighter_gobj);
        }
        else
        {
            func_ovl3_8013D930(fighter_gobj);
            ftCommon_ResetControllerInputs(fighter_gobj);
        }
        break;
    }
    if ((fp->status_info.pl_kind == Pl_Kind_Human) || (fp->status_info.pl_kind == Pl_Kind_CPU))
    {
        func_unkmulti_8013AC00(fighter_gobj);
    }
    if ((fp->status_info.pl_kind != Pl_Kind_Result) && !(spawn->unk_rebirth_0x1F_b1))
    {
        func_unkmulti_8013BB88(fighter_gobj);
    }
    return fighter_gobj;
}
