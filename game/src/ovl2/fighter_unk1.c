#include "fighter.h"
#include "article.h"
#include "gmmatch.h"
#include "ftdonkey.h"
#include "ftsamus.h"
#include "ftkirby.h"
#include "ftness.h"

extern s32 gmMusicIndexCurrent; // Static (.bss)
extern s32 gmMusicIndexDefault; // Static (.bss)

// 0x800E7AD0 - Get duration of special music in seconds
s32 ftSpecialItem_BGMGetDuration(s32 bgm_id)
{
    switch (bgm_id)
    {
    case ATSTAR_BGM_ID:
        return ATHAMMER_BGM_DURATION;

    case ATHAMMER_BGM_ID:
        return ATSTAR_BGM_DURATION;

    default:
        return 0;
    }
}

// 0x800E7AFC
void ftSpecialItem_BGMSetPlay(s32 bgm_id)
{
    if (ftSpecialItem_BGMGetDuration(bgm_id) >= ftSpecialItem_BGMGetDuration(gmMusicIndexCurrent))
    {
        func_80020AB4(0, bgm_id);

        gmMusicIndexCurrent = bgm_id;
    }
}

// 0x800E7B54
void ftSpecialItem_BGMCheckFighters(void)
{
    s32 bgm_play = gmMusicIndexDefault;
    s32 duration = ftSpecialItem_BGMGetDuration(bgm_play);
    GObj *fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

    while (fighter_gobj != NULL)
    {
        Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
        s32 bgm_id = gmMusicIndexDefault;
        s32 duration_new;

        if ((fp->item_hold != NULL) && (ArticleGetStruct(fp->item_hold)->at_kind == At_Kind_Hammer))
        {
            bgm_id = ATHAMMER_BGM_ID;
        }
        if (fp->star_invincible_timer > ATSTAR_WARN_BEGIN_FRAME)
        {
            bgm_id = ATSTAR_BGM_ID;
        }
        duration_new = ftSpecialItem_BGMGetDuration(bgm_id);

        if (duration < duration_new)
        {
            duration = duration_new;
            bgm_play = bgm_id;
        }
        fighter_gobj = fighter_gobj->group_gobj_next;
    }
    if (bgm_play != gmMusicIndexCurrent)
    {
        func_80020AB4(0, bgm_play);
        gmMusicIndexCurrent = bgm_play;
    }
}

// 0x800E7C4C
void ftCommon_ClearPlayerMatchStats(s32 player_id, GObj *fighter_gobj)
{
    s32 i;

    Match_Info->player_block[player_id].stock_count = 0;
    Match_Info->player_block[player_id].falls = Match_Info->player_block[player_id].score = 0;

    for (i = 0; i < GMMATCH_PLAYERS_MAX; i++)
    {
        Match_Info->player_block[player_id].total_ko_player[i] = 0;
        Match_Info->player_block[player_id].total_damage_player[i] = 0;
    }
    Match_Info->player_block[player_id].unk_pblock_0x28 = Match_Info->player_block[player_id].unk_pblock_0x2C = Match_Info->player_block[player_id].total_self_destruct = 0;
    Match_Info->player_block[player_id].total_damage_dealt = Match_Info->player_block[player_id].total_damage_all = 0;
    Match_Info->player_block[player_id].combo_damage_foe = Match_Info->player_block[player_id].combo_count_foe = 0;

    Match_Info->player_block[player_id].fighter_gobj = fighter_gobj;

    Match_Info->player_block[player_id].stale_index = 0;

    for (i = 0; i < ARRAY_COUNT(Match_Info->player_block[i].stale_flags); i++)
    {
        Match_Info->player_block[player_id].stale_flags[i][0] = 0;
        Match_Info->player_block[player_id].stale_flags[i][1] = 0;
    }
}

// 0x800E7ED4 - Get fighter GObj with player number
GObj* ftCommon_GetPlayerNumGObj(s32 player_number) 
{
    GObj *fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

    while (fighter_gobj != NULL)
    {
        Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

        if (player_number == fp->player_number)
        {
            return fighter_gobj;
        }
        else fighter_gobj = fighter_gobj->group_gobj_next;
    }
    return NULL;
}

// 0x800E7F14
void ftCommon_ResetControllerInputs(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->input.pl.button_hold = fp->input.pl.button_tap = fp->input.cp.button_inputs = 0;

    fp->input.pl.stick_range.x = fp->input.pl.stick_range.y = fp->input.pl.stick_prev.x = fp->input.pl.stick_prev.y = fp->input.cp.stick_range.x = fp->input.cp.stick_range.y = 0;

    fp->tap_stick_x = fp->tap_stick_y = fp->hold_stick_x = fp->hold_stick_y = U8_MAX - 1;

    fp->x18F_flag_b6 = TRUE;
}

void func_ovl2_800E7F68(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->x18F_flag_b6 = FALSE;
}

void func_ovl2_800E7F7C(GObj *fighter_gobj, s32 arg1)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->unk_0x174 = arg1;
}

extern u8 ftCommon_ShuffleFrameIndexMax[2] = { 4, 3 };

// 0x800E7F88
void ftCommon_SetShuffleInfo(Fighter_Struct *fp, bool32 is_electric, s32 damage, s32 status_id, f32 hitlag_mul)
{
    fp->shuffle_timer = func_ovl2_800EA1C0(damage, status_id, hitlag_mul) * FTCOMMON_DAMAGE_SHUFFLE_MUL;
    fp->shuffle_frame_index = 0;
    fp->is_shuffle_electric = is_electric;
    fp->shuffle_index_max = ftCommon_ShuffleFrameIndexMax[is_electric];
}

// 0x800E8000
f32 ftCommon_GetStickAngleRadians(Fighter_Struct *fp)
{
    return atan2f(fp->input.pl.stick_range.y, ABS(fp->input.pl.stick_range.x));
}

// 0x800E8044
void ftCommon_StickInputSetLR(Fighter_Struct *fp)
{
    fp->lr = (fp->input.pl.stick_range.x >= 0) ? RIGHT : LEFT;
}

void func_ovl2_800E806C(Fighter_Struct *fp, s32 arg1, s32 arg2)
{
    if (fp->status_info.pl_kind == Pl_Kind_Human)
    {
        func_ovl2_80115530(fp->port_id, arg1, arg2);
    }
}

// 0x800E8098
void ftCommon_SetCaptureFlags(Fighter_Struct *fp, u8 capture_flags)
{
    fp->capture_flags = capture_flags;
}

// 0x800E80A4
void ftCommon_SetCatchVars(Fighter_Struct *fp, u8 catch_flags, void (*proc_catch)(GObj*), void (*proc_capture)(GObj*, GObj*))
{
    fp->x192_flag_b2 = TRUE;

    fp->catch_flags = catch_flags;
    fp->proc_catch = proc_catch;
    fp->proc_capture = proc_capture;
}

// 0x800E80C4 - Fetch data of throwing fighter: character ID, port ID, team, player number and GObj pointer
void ftCommon_ThrownUpdateEnemyInfo(Fighter_Struct *this_fp, GObj *throw_gobj)
{
    Fighter_Struct *throw_fp = FighterGetStruct(throw_gobj); // Fighter throwing this player

    this_fp->throw_gobj = throw_gobj;
    this_fp->throw_ft_kind = throw_fp->ft_kind;
    this_fp->throw_port_id = throw_fp->port_id;
    this_fp->throw_player_number = throw_fp->player_number;
    this_fp->throw_team = throw_fp->team;
}

// 0x800E80F0
void ftCommon_PlayVoiceStoreInfo(Fighter_Struct *fp, u16 voice_id)
{
    fp->p_voice = func_800269C0(voice_id);

    fp->voice_id = (fp->p_voice != NULL) ? fp->p_voice->sfx_id : 0;
}

// 0x800E8138
void ftCommon_StopVoice(Fighter_Struct *fp)
{
    if (fp->p_voice != NULL)
    {
        if ((fp->p_voice->sfx_id != 0) && (fp->p_voice->sfx_id == fp->voice_id))
        {
            func_80026738(fp->p_voice);
        }
    }
    fp->p_voice = NULL;
    fp->voice_id = 0;
}

// 0x800E8190
void ftCommon_PlayLoopSFXStoreInfo(Fighter_Struct *fp, u16 sfx_id)
{
    if (fp->p_loop_sfx == NULL)
    {
        fp->p_loop_sfx = func_800269C0(sfx_id);

        fp->loop_sfx_id = (fp->p_loop_sfx != NULL) ? fp->p_loop_sfx->sfx_id : 0;
    }
}

// 0x800E81E4
void ftCommon_StopLoopSFX(Fighter_Struct *fp)
{
    if (fp->p_loop_sfx != NULL)
    {
        if ((fp->p_loop_sfx->sfx_id != 0) && (fp->p_loop_sfx->sfx_id == fp->loop_sfx_id))
        {
            func_80026738(fp->p_loop_sfx);
        }
    }
    fp->p_loop_sfx = NULL;
    fp->loop_sfx_id = 0;
}

// 0x800E823C
void ftCommon_ProcDamageStopVoice(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCommon_StopVoice(fp);

    if (fp->proc_damage != NULL)
    {
        fp->proc_damage(fighter_gobj);
    }
}

// Update render priority? Runs when a fighter gets Screen KO'd
void func_ovl2_800E827C(GObj *fighter_gobj, u8 arg1)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    om_g_move_obj_dl(fighter_gobj, arg1, 0x80000000);

    fp->unk_0x16 = arg1;
}

void func_ovl2_800E82B8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    DObj **p_joint = &fp->joint[0];
    DObj *joint;
    MObj *mobj;
    UnkDObjData *temp_v0;
    Vec3f *p_0x324;
    Vec3f *p_0x324_2;
    f32 temp_f20;
    s32 i;

    if (fp->status_info.script_id != -2)
    {
        if (fp->x18F_flag_b5)
        {
            p_0x324 = fp->attributes->unk_0x324;

            for (i = 0; i < ARRAY_COUNT(fp->joint); i++, p_joint++, p_0x324++)
            {
                joint = *p_joint;

                if (joint != NULL)
                {
                    if (fp->anim_flags.flags.x19B_flag_b4)
                    {
                        func_8000BFE8(joint);
                    }
                    else
                    {
                        func_ovl2_800EC238(joint);
                    }
                    func_ovl0_800C9488(joint, p_0x324);

                    mobj = joint->mobj;

                    while (mobj != NULL)
                    {
                        func_8000CF6C(mobj);
                        func_8000DA40(mobj);

                        mobj = mobj->mobj_next;
                    }
                }
            }
        }
        else for (i = 0; i < ARRAY_COUNT(fp->joint); i++, p_joint++)
        {
            joint = *p_joint;

            if (joint != NULL)
            {
                if (fp->anim_flags.flags.x19B_flag_b4)
                {
                    func_8000BFE8(joint);
                }
                else
                {
                    func_ovl2_800EC238(joint);
                }
                func_8000CCBC(joint);

                mobj = joint->mobj;

                while (mobj != NULL)
                {
                    func_8000CF6C(mobj);
                    func_8000DA40(mobj);

                    mobj = mobj->mobj_next;
                }
            }
        }
    }
    else if (fp->x18F_flag_b5)
    {
        p_0x324_2 = fp->attributes->unk_0x324;

        for (i = 0; i < ARRAY_COUNT(fp->joint); i++, p_joint++, p_0x324_2++)
        {
            joint = *p_joint;

            if (joint != NULL)
            {
                temp_v0 = joint->unk_0x84;

                if ((temp_v0 != NULL) && (temp_v0->unk_dobjdata_0xE != 0))
                {
                    temp_f20 = joint->unk_dobj_0x74;

                    joint->unk_dobj_0x74 = -1.1342745e38F;

                    func_ovl0_800C9488(joint, p_0x324_2);

                    joint->unk_dobj_0x74 = temp_f20;
                }
            }
        }
    }
    else for (i = 0; i < ARRAY_COUNT(fp->joint); i++, p_joint++)
    {
        joint = *p_joint;

        if (joint != NULL)
        {
            temp_v0 = joint->unk_0x84;

            if ((temp_v0 != NULL) && (temp_v0->unk_dobjdata_0xE != 0))
            {
                temp_f20 = joint->unk_dobj_0x74;

                joint->unk_dobj_0x74 = -1.1342745e38F;

                func_8000CCBC(joint);

                joint->unk_dobj_0x74 = temp_f20;
            }
        }
    }
}

// 0x800E8518
void ftCommon_ClearHitAll(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
    {
        Fighter_Hit *ft_hit = &fp->fighter_hit[i];

        ft_hit->update_state = gmHitCollision_UpdateState_Disable;
    }
    fp->is_hit_enable = FALSE;
}

// 0x800E853C
void ftCommon_ClearHitTargetsIndex(Fighter_Struct *fp, s32 hit_id)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hit[hit_id].hit_targets); i++)
    {
        FighterHitArray *targets = &fp->fighter_hit[hit_id].hit_targets[i];

        targets->victim_gobj = NULL;

        targets->victim_flags.is_interact_hurt = targets->victim_flags.is_interact_shield = FALSE;

        targets->victim_flags.timer_rehit = 0;

        targets->victim_flags.interact_mask = GMHITCOLLISION_MASK_ALL;
    }
}

// 0x800E8668
void ftCommon_RefreshHitIndex(GObj *fighter_gobj, s32 hit_id)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->fighter_hit[hit_id].update_state = gmHitCollision_UpdateState_New;

    fp->is_hit_enable = TRUE;

    ftCommon_ClearHitTargetsIndex(fp, hit_id);
}

// 0x800E86B4
void ftCommon_CollDataSetVelPush(GObj *fighter_gobj, Vec3f *vel_push)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->coll_data.vel_push = *vel_push;
}

// 0x800E86D4
s32 ftCommon_GetLightHoldJointIndex(Fighter_Struct *fp, s32 joint_index)
{
    if (joint_index == -2)
    {
        joint_index = fp->attributes->joint_itemhold_light;
    }
    return joint_index;
}

// 0x800E86F0
void ftLink_SetModelPartHideShield(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ft_kind == Ft_Kind_Link) || (fp->ft_kind == Ft_Kind_PolyLink))
    {
        ftCommon_SetModelPartRenderStateIndex(fighter_gobj, 0x15, 0);
        ftCommon_SetModelPartRenderStateIndex(fighter_gobj, 0x13, -1);
    }
}

// 0x800E8744
void ftCommon_GetHammerSetBGM(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ft_kind == Ft_Kind_Link) || (fp->ft_kind == Ft_Kind_PolyLink))
    {
        ftCommon_SetModelPartRenderStateIndex(fighter_gobj, 0x15, -1);
        ftCommon_SetModelPartRenderStateIndex(fighter_gobj, 0x13, 0);
    }
    ftSpecialItem_BGMCheckFighters();
}

// 0x800E87A0
void ftCommon_HitStatusSetColAnim(GObj *fighter_gobj, s32 hitstatus)
{
    switch (hitstatus)
    {
    case gmHitCollision_HitStatus_Normal:
        ftCommon_CheckSetColAnimIndex(fighter_gobj, 2, 0);
        break;

    case gmHitCollision_HitStatus_Invincible:
        ftCommon_CheckSetColAnimIndex(fighter_gobj, 4, 0);
        break;

    case gmHitCollision_HitStatus_Intangible:
        ftCommon_CheckSetColAnimIndex(fighter_gobj, 3, 0);
        break;
    }
}

// 0x800E880C
void ftCommon_SetHitStatusPartAll(GObj *fighter_gobj, s32 hitstatus)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hurt); i++)
    {
        Fighter_Hurt *ft_hurt = &fp->fighter_hurt[i];

        if (ft_hurt->hitstatus != gmHitCollision_HitStatus_None)
        {
            ft_hurt->hitstatus = hitstatus;
        }
    }
    fp->is_hitstatus_nodamage = (hitstatus == gmHitCollision_HitStatus_Normal) ? FALSE : TRUE;

    ftCommon_HitStatusSetColAnim(fighter_gobj, hitstatus);
}

// 0x800E8884
void ftCommon_SetHitStatusPart(GObj *fighter_gobj, s32 joint_index, s32 hitstatus)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hurt); i++)
    {
        Fighter_Hurt *ft_hurt = &fp->fighter_hurt[i];

        if ((ft_hurt->hitstatus != gmHitCollision_HitStatus_None) && (joint_index == ft_hurt->joint_index))
        {
            ft_hurt->hitstatus = hitstatus;

            if (ft_hurt->hitstatus != gmHitCollision_HitStatus_Normal)
            {
                fp->is_hitstatus_nodamage = TRUE;
            }
            return; // This means if there are multiple hurtboxes on the same bone/joint ID, only the first one is checked; same as Melee with Mr. Game & Watch / Fox's nose hurtboxes 
        }
    }
}

// 0x800E8A24
void ftCommon_SetHitStatusAll(GObj *fighter_gobj, s32 hitstatus)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->hitstatus = hitstatus;

    ftCommon_HitStatusSetColAnim(fighter_gobj, hitstatus);
}

// 0x800E8A48 - Get most effective bone collision state
s32 ftCommon_GetBestHitStatusPart(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 hitstatus_default = fp->hitstatus;
    s32 hitstatus_best = fp->fighter_hurt[0].hitstatus;
    s32 i;

    if (hitstatus_best != gmHitCollision_HitStatus_Normal)
    {
        for (i = 1; i < ARRAY_COUNT(fp->fighter_hurt); i++)
        {
            Fighter_Hurt *ft_hurt = &fp->fighter_hurt[i];

            if (ft_hurt->hitstatus == gmHitCollision_HitStatus_None) break;

            else if (ft_hurt->hitstatus < hitstatus_best)
            {
                hitstatus_best = ft_hurt->hitstatus;
            }
        }
    }
    if (hitstatus_default < hitstatus_best)
    {
        hitstatus_default = hitstatus_best;
    }
    return hitstatus_default;
}

// 0x800E8AAC - Get overall best collision state
s32 ftCommon_GetBestHitStatusAll(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 hitstatus_best = ftCommon_GetBestHitStatusPart(fighter_gobj);

    if (hitstatus_best < fp->special_hitstatus)
    {
        hitstatus_best = fp->special_hitstatus;
    }
    if (hitstatus_best < fp->itemstat_hitstatus)
    {
        hitstatus_best = fp->itemstat_hitstatus;
    }
    return hitstatus_best;
}

// 0x800E8B00
void ftCommon_InitFighterHurtParts(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Fighter_Hurt *ft_hurt = &fp->fighter_hurt[0];
    FighterHurtDesc *ft_hurt_desc = &fp->attributes->fighter_hurt_desc[0];
    s32 i;

    for (i = 0; i < FTPARTS_HURT_NUM_MAX; i++, ft_hurt++, ft_hurt_desc++)
    {
        if (ft_hurt_desc->joint_index != -1)
        {
            ft_hurt->joint_index = ft_hurt_desc->joint_index;
            ft_hurt->joint = fp->joint[ft_hurt->joint_index];

            ft_hurt->unk_ftht_0xC = ft_hurt_desc->unk_fthdesc_0x4;
            ft_hurt->unk_ftht_0x10 = ft_hurt_desc->unk_fthdesc_0x8;

            ft_hurt->offset = ft_hurt_desc->offset;
            ft_hurt->size = ft_hurt_desc->size;

            ft_hurt->size.x *= 0.5F;
            ft_hurt->size.y *= 0.5F;
            ft_hurt->size.z *= 0.5F;
        }
    }
    fp->is_fthurt_modify = FALSE;
}

// 0x800E8BC8
void ftCommon_UpdateFighterHurtPartIndex(GObj *fighter_gobj, s32 joint_index, Vec3f *offset, Vec3f *size)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hurt); i++)
    {
        Fighter_Hurt *ft_hurt = &fp->fighter_hurt[i];

        if (joint_index == ft_hurt->joint_index)
        {
            ft_hurt->offset = *offset;
            ft_hurt->size = *size;

            fp->fighter_hurt[i].size.x *= 0.5F;
            fp->fighter_hurt[i].size.y *= 0.5F;
            fp->fighter_hurt[i].size.z *= 0.5F;

            fp->is_fthurt_modify = TRUE;

            return; // The same oversight as ftCommon_SetHitStatusPart except this time on hurtbox offset and size
        }
    }
}

// 0x800E8C70
void ftCommon_SetModelPartRenderIndex(GObj *fighter_gobj, s32 joint_index, s32 render_state)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    DObjDescContainer *dobj_desc_container;
    ftModelPart *model_part;
    ftModelPartRenderState *joint_render_state;
    UnkDObjData *unk_dobj;
    DObj *joint;
    void *var_a2;
    s32 lod_index;
    void *sp38;

    joint = fp->joint[joint_index];
    dobj_desc_container = attributes->dobj_desc_container;
    joint_render_state = &fp->joint_render_state[joint_index - 4];
    unk_dobj = joint->unk_0x84;

    if (joint != NULL)
    {
        if (render_state != joint_render_state->render_state_b1)
        {
            joint_render_state->render_state_b1 = render_state;

            func_800091F4(joint);

            if (render_state != -1)
            {
                if (fp->attributes->model_parts->model_part_desc[joint_index - 4] != NULL)
                {
                    model_part = &fp->attributes->model_parts->model_part_desc[joint_index - 4]->model_part[render_state][fp->lod_current - 1];

                    joint->display_list = model_part->display_list;

                    func_ovl0_800C8CB8(joint, model_part->unk_modelpart_0x4, model_part->unk_modelpart_0x8, model_part->unk_modelpart_0xC, fp->costume_id);

                    unk_dobj->unk_0xC = model_part->unk_modelpart_0x10;
                }
                else
                {
                    if ((fp->lod_current == 1) || (dobj_desc_container->dobj_desc_array[1].dobj_desc[joint_index - 4].display_list == NULL))
                    {
                        lod_index = 0;
                    }
                    else lod_index = 1;

                    joint->display_list = dobj_desc_container->dobj_desc_array[lod_index].dobj_desc[joint_index - 4].display_list;

                    if (dobj_desc_container->dobj_desc_array[lod_index].d2 != NULL)
                    {
                        sp38 = dobj_desc_container->dobj_desc_array[lod_index].d2[joint_index - 4];
                    }
                    else sp38 = NULL;

                    if (dobj_desc_container->dobj_desc_array[lod_index].d3 != NULL)
                    {
                        var_a2 = dobj_desc_container->dobj_desc_array[lod_index].d3[joint_index - 4];
                    }
                    else var_a2 = NULL;

                    func_ovl0_800C8CB8(joint, sp38, var_a2, NULL, fp->costume_id);

                    unk_dobj->unk_0xC = dobj_desc_container->dobj_desc_array[lod_index].unk_dobjcontain_0xC;
                }
            }
            else joint->display_list = NULL;

            fp->is_modelpart_modify = TRUE;
        }
    }
}

void ftCommon_SetModelPartRenderStateIndex(GObj *fighter_gobj, s32 joint_index, s32 render_state)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->joint_render_state[joint_index - 4].render_state_b0 = render_state;

    fp->is_modelpart_modify = TRUE;
}

// 0x800E8ECC
void ftCommon_ResetModelPartRenderAll(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    DObjDescContainer *dobj_desc_container;
    ftModelPart *model_part;
    ftModelPartRenderState *joint_render_state;
    UnkDObjData *unk_dobj;
    DObj *joint;
    void *var_a2;
    s32 lod_index;
    void *sp38;
    s32 i;

    dobj_desc_container = attributes->dobj_desc_container;

    for (i = 0; i < ARRAY_COUNT(fp->joint) - 4; i++)
    {
        joint = fp->joint[i + 4];

        if (joint != NULL)
        {
            joint_render_state = &fp->joint_render_state[i];

            if (joint_render_state->render_state_b1 != joint_render_state->render_state_b0)
            {
                joint_render_state->render_state_b1 = joint_render_state->render_state_b0;

                func_800091F4(joint);

                if (joint_render_state->render_state_b1 == -1)
                {
                    joint->display_list = NULL;
                }
                else
                {
                    unk_dobj = joint->unk_0x84;

                    if (attributes->model_parts->model_part_desc[i] != NULL)
                    {
                        model_part = &attributes->model_parts->model_part_desc[i]->model_part[joint_render_state->render_state_b1][fp->lod_current - 1];

                        joint->display_list = model_part->display_list;

                        func_ovl0_800C8CB8(joint, model_part->unk_modelpart_0x4, model_part->unk_modelpart_0x8, model_part->unk_modelpart_0xC, fp->costume_id);

                        unk_dobj->unk_0xC = model_part->unk_modelpart_0x10;
                    }
                    else
                    {
                        if ((fp->lod_current == 1) || (dobj_desc_container->dobj_desc_array[1].dobj_desc[i].display_list == NULL))
                        {
                            lod_index = 0;
                        }
                        else lod_index = 1;

                        joint->display_list = dobj_desc_container->dobj_desc_array[lod_index].dobj_desc[i].display_list;

                        if (dobj_desc_container->dobj_desc_array[lod_index].d2 != NULL)
                        {
                            sp38 = dobj_desc_container->dobj_desc_array[lod_index].d2[i];
                        }
                        else sp38 = NULL;

                        if (dobj_desc_container->dobj_desc_array[lod_index].d3 != NULL)
                        {
                            var_a2 = dobj_desc_container->dobj_desc_array[lod_index].d3[i];
                        }
                        else var_a2 = NULL;

                        func_ovl0_800C8CB8(joint, sp38, var_a2, NULL, fp->costume_id);

                        unk_dobj->unk_0xC = dobj_desc_container->dobj_desc_array[lod_index].unk_dobjcontain_0xC;
                    }
                }
            }
        }
    }
    fp->is_modelpart_modify = FALSE;
}

// 0x800E90F8
void ftCommon_HideModelPartAll(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 i;

    for (i = 4; i < ARRAY_COUNT(fp->joint); i++)
    {
        DObj *joint = fp->joint[i];

        if (joint != NULL)
        {
            if (fp->joint_render_state[i - 4].render_state_b1 == -1) continue;

            else
            {
                fp->joint_render_state[i - 4].render_state_b1 = -1;

                func_800091F4(joint);

                joint->display_list = NULL;
            }
        }
    }
    fp->is_modelpart_modify = TRUE;
}

// 0x800E9198
void ftCommon_SetModelPartLoDAll(GObj *fighter_gobj, u8 lod)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 i;

    if (lod != fp->lod_current)
    {
        fp->lod_current = lod;

        for (i = 4; i < ARRAY_COUNT(fp->joint); i++)
        {
            DObj *joint = fp->joint[i];

            if (joint != NULL)
            {
                s32 render_state = fp->joint_render_state[i - 4].render_state_b1;

                if (render_state == -1) continue;

                else
                {
                    fp->joint_render_state[i - 4].render_state_b1 = -1;

                    ftCommon_SetModelPartRenderIndex(fighter_gobj, i, render_state);
                }
            }
        }
        func_ovl2_800E9598(fighter_gobj);
    }
}

void func_ovl2_800E9248(GObj *fighter_gobj, s32 costume_id, s32 shade_id)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;
    DObj *joint;
    GObj *unk_gobj;
    UnkDObjData *unk_dobj;
    DObjDescContainer *dobj_desc_container;
    UnkFighterDObjData *unk_ftdobj;
    ftModelPartRenderState *joint_render_state;
    s32 lod_index;
    ftModelPart *model_part;
    void *var_a1;
    void *var_a2;
    s32 i;

    dobj_desc_container = attributes->dobj_desc_container;
    unk_ftdobj = attributes->unk_0x32C;

    for (i = 0; i < ARRAY_COUNT(fp->joint) - 4; i++)
    {
        joint = fp->joint[i + 4];

        if (joint != NULL)
        {
            func_800091F4(joint);

            joint_render_state = &fp->joint_render_state[i];

            if (joint_render_state->render_state_b1 != -1)
            {
                if (attributes->model_parts->model_part_desc[i] != 0)
                {
                    model_part = &attributes->model_parts->model_part_desc[i]->model_part[joint_render_state->render_state_b1][fp->lod_current - 1];

                    func_ovl0_800C8CB8(joint, model_part->unk_modelpart_0x4, model_part->unk_modelpart_0x8, model_part->unk_modelpart_0xC, costume_id);
                }
                else
                {
                    if ((fp->lod_current == 1) || (dobj_desc_container->dobj_desc_array[1].dobj_desc[i].display_list == NULL))
                    {
                        lod_index = 0;
                    }
                    else lod_index = 1;

                    if (dobj_desc_container->dobj_desc_array[lod_index].d2 != NULL)
                    {
                        var_a1 = dobj_desc_container->dobj_desc_array[lod_index].d2[i];
                    }
                    else var_a1 = NULL;

                    if (dobj_desc_container->dobj_desc_array[lod_index].d3 != NULL)
                    {
                        var_a2 = dobj_desc_container->dobj_desc_array[lod_index].d3[i];
                    }
                    else var_a2 = NULL;

                    func_ovl0_800C8CB8(joint, var_a1, var_a2, NULL, costume_id);
                }
            }
            if ((unk_ftdobj != NULL) && ((i + 4) == unk_ftdobj->joint_index))
            {
                unk_dobj = joint->unk_0x84;

                if (unk_dobj->unk_gobj != NULL)
                {
                    func_80009A84(unk_dobj->unk_gobj);

                    unk_dobj->unk_gobj = NULL;
                }
                if (costume_id != 0)
                {
                    unk_gobj = func_80009968(0x3E9U, NULL, 0xDU, 0x80000000U);
                    unk_dobj->unk_gobj = unk_gobj;

                    func_800092D0(unk_gobj, unk_ftdobj->unk_ftdobj_0x4);

                    func_ovl0_800C8CB8(unk_dobj->unk_gobj->obj, unk_ftdobj->unk_ftdobj_0x8, unk_ftdobj->unk_ftdobj_0xC, NULL, costume_id);
                }
            }
        }
    }
    fp->costume_id = costume_id;
    fp->shade_id = shade_id;

    fp->shade.r = ((attributes->shade_color[fp->shade_id - 1].r * attributes->shade_color[fp->shade_id - 1].a) / 255);
    fp->shade.g = ((attributes->shade_color[fp->shade_id - 1].g * attributes->shade_color[fp->shade_id - 1].a) / 255);
    fp->shade.b = ((attributes->shade_color[fp->shade_id - 1].b * attributes->shade_color[fp->shade_id - 1].a) / 255);

    func_ovl2_800E9598(fighter_gobj);
}

// ...ewww...
// 0x800E9598
void func_ovl2_800E9598(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftTexturePartRenderState *texture_render_state;
    ftTexturePartContainer *texture_parts;
    ftTexturePartInfo *texture_info;
    DObj *joint;
    MObj *mobj;
    s32 lod;
    s32 i, j;

    for (i = 0, texture_render_state = &fp->texture_render_state[i], texture_info = &fp->attributes->texture_parts->texture_part_info[i]; i < ARRAY_COUNT(fp->texture_render_state); i++, texture_render_state++, texture_info++)
    {
        if (texture_render_state->frame_index_current != texture_render_state->frame_index_default)
        {
            joint = fp->joint[texture_info->joint_index];
            lod = texture_info->lod[fp->lod_current - 1];

            if (joint != NULL)
            {
                mobj = joint->mobj;

                j = 0;

            loop:
                if (mobj != NULL)
                {
                    if (j != lod)
                    {
                        mobj = mobj->mobj_next;

                        j++;

                        goto loop;
                    }
                    else mobj->index = texture_render_state->frame_index;
                }
            }
        }
    }
    fp->is_texturepart_modify = TRUE;
}

// 0x800E962C
void ftCommon_SetTexturePartIndex(GObj *fighter_gobj, s32 obj_index, s32 frame_index)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftTexturePartInfo *texture_part_info = &fp->attributes->texture_parts->texture_part_info[obj_index];
    s32 lod = texture_part_info->lod[fp->lod_current - 1];
    DObj *joint = fp->joint[texture_part_info->joint_index];

    if (joint != NULL)
    {
        MObj *mobj = joint->mobj;

        s32 i = 0;

    loop:
        if (mobj != NULL)
        {
            if (i != lod)
            {
                mobj = mobj->mobj_next;

                i++;

                goto loop;
            }
            mobj->index = frame_index;

            fp->texture_render_state[obj_index].frame_index_current = frame_index;

            fp->is_texturepart_modify = TRUE;
        }
    }
}

void func_ovl2_800E96B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftTexturePartRenderState *texture_render_state;
    ftTexturePartContainer *texture_parts;
    ftTexturePartInfo *texture_info;
    DObj *joint;
    MObj *mobj;
    s32 lod;
    s32 i, j;

    for (i = 0, texture_render_state = &fp->texture_render_state[i], texture_info = &fp->attributes->texture_parts->texture_part_info[i]; i < ARRAY_COUNT(fp->texture_render_state); i++, texture_render_state++, texture_info++)
    {
        if (texture_render_state->frame_index_current != texture_render_state->frame_index_default)
        {
            texture_render_state->frame_index_current = texture_render_state->frame_index_default;

            joint = fp->joint[texture_info->joint_index];
            lod = texture_info->lod[fp->lod_current - 1];

            if (joint != NULL)
            {
                mobj = joint->mobj;

                j = 0;

            loop:
                if (mobj != NULL)
                {
                    if (j != lod)
                    {
                        mobj = mobj->mobj_next;

                        j++;

                        goto loop;
                    }
                    else mobj->index = texture_render_state->frame_index_current;
                }
            }
        }
    }
    fp->is_texturepart_modify = FALSE;
}

extern ColAnimDesc ColAnimTable[]; // 0x8012DBD0

// 0x800E974C
bool32 caCheckSetColAnimIndex(Color_Overlay *colanim, s32 colanim_id, s32 duration)
{
    if (ColAnimTable[colanim_id].unk_colanimdesc_0x4 >= ColAnimTable[colanim->colanim_id].unk_colanimdesc_0x4)
    {
        s32 i;

        colanim->colanim_id = colanim_id;
        colanim->duration = duration;
        colanim->cs[0].p_script = ColAnimTable[colanim_id].p_script;
        colanim->cs[0].color_event_timer = 0;
        colanim->cs[0].script_index = 0;

        for (i = 1; i < ARRAY_COUNT(colanim->cs); i++)
        {
            colanim->cs[i].p_script = NULL;
        }
        colanim->is_use_color1 = colanim->is_use_light = colanim->is_use_color2 = colanim->unk_ca_0x60_b34 = 0;

        return TRUE;
    }
    return FALSE;
}

// 0x800E9814
bool32 ftCommon_CheckSetColAnimIndex(GObj *fighter_gobj, s32 colanim_id, s32 duration)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    return caCheckSetColAnimIndex(&fp->colanim, colanim_id, duration);
}

// 0x800E9838
void caResetColAnim(Color_Overlay *colanim)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(colanim->cs); i++)
    {
        colanim->cs[i].p_script = NULL;
    }
    colanim->duration = 0;
    colanim->colanim_id = 0;

    colanim->is_use_color1 = colanim->is_use_light = colanim->is_use_color2 = colanim->unk_ca_0x60_b34 = 0;
}

void ftCommon_ResetColAnim(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    caResetColAnim(&fp->colanim);
}

// 0x800E98D4
void ftCommon_ResetColAnimStatUpdate(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCommon_ResetColAnim(fighter_gobj);

    switch (ftCommon_GetBestHitStatusPart(fighter_gobj))
    {
    case gmHitCollision_HitStatus_Invincible:
        ftCommon_CheckSetColAnimIndex(fighter_gobj, 4, 0);
        break;

    case gmHitCollision_HitStatus_Intangible:
        ftCommon_CheckSetColAnimIndex(fighter_gobj, 3, 0);
        break;
    }
    switch (fp->ft_kind)
    {
    case Ft_Kind_Donkey:
    case Ft_Kind_PolyDonkey:
    case Ft_Kind_GiantDonkey:
        if (fp->fighter_vars.donkey.charge_level == FTDONKEY_GIANTPUNCH_CHARGE_MAX)
        {
            ftCommon_CheckSetColAnimIndex(fighter_gobj, FTDONKEY_GIANTPUNCH_CHARGE_COLANIM_ID, 0);
        }
        break;

    case Ft_Kind_Samus:
    case Ft_Kind_PolySamus:
        if (fp->fighter_vars.samus.charge_level == FTSAMUS_CHARGE_MAX)
        {
            ftCommon_CheckSetColAnimIndex(fighter_gobj, FTSAMUS_CHARGE_COLANIM_ID, 0);
        }
        break;

    case Ft_Kind_Kirby:
        if ((fp->fighter_vars.kirby.copy_id == Ft_Kind_Samus) || (fp->fighter_vars.kirby.copy_id == Ft_Kind_PolySamus))
        {
            if (fp->fighter_vars.kirby.copysamus_charge_level == FTKIRBY_COPYSAMUS_CHARGE_MAX)
            {
                ftCommon_CheckSetColAnimIndex(fighter_gobj, FTKIRBY_COPYSAMUS_CHARGE_COLANIM_ID, 0);
            }
        }
        if ((fp->fighter_vars.kirby.copy_id == Ft_Kind_Donkey) || (fp->fighter_vars.kirby.copy_id == Ft_Kind_PolyDonkey) || (fp->fighter_vars.kirby.copy_id == Ft_Kind_GiantDonkey))
        {
            if (fp->fighter_vars.kirby.copydonkey_charge_level == FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_MAX)
            {
                ftCommon_CheckSetColAnimIndex(fighter_gobj, FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_COLANIM_ID, 0);
            }
        }
        break;

    case Ft_Kind_Ness:
    case Ft_Kind_PolyNess:
        if (fp->is_absorb)
        {
            ftCommon_CheckSetColAnimIndex(fighter_gobj, FTNESS_PSI_MAGNET_COLANIM_ID, 0);
        }
        break;
    }
    if (fp->damage_heal != 0)
    {
        ftCommon_CheckSetColAnimIndex(fighter_gobj, 9, 0);
    }
    if (fp->star_invincible_timer != 0)
    {
        ftCommon_CheckSetColAnimIndex(fighter_gobj, 0x4A, 0);
    }
    if ((fp->invincible_timer != 0) || (fp->walldamage_nohit_timer != 0))
    {
        ftCommon_CheckSetColAnimIndex(fighter_gobj, 0xA, 0);
    }
    if (func_ovl2_800F37CC(fighter_gobj) != 0)
    {
        ftCommon_CheckSetColAnimIndex(fighter_gobj, 0x49, 0);
    }
}

extern s32 Fighter_ColAnimIndex_Skeleton[Ft_Kind_EnumMax] = 
{
    0x14,
    0x14,
    0x14,
    0x1C,
    0x14,
    0x14,
    0x14,
    0x14,
    0x18,
    0x14,
    0x18,
    0x14,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10
};

bool32 func_ovl2_800E9AF4(GObj *fighter_gobj, s32 colanim_id)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    return ftCommon_CheckSetColAnimIndex(fighter_gobj, Fighter_ColAnimIndex_Skeleton[fp->ft_kind] + colanim_id, 0);
}

// 0x800E9B30 - Set How to Play input sequence
void ftCommon_SetHowToPlayInputSeq(GObj *fighter_gobj, void *p_inputseq)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->howtoplay_input_wait = 0;
    fp->p_howtoplay_input = p_inputseq;
}

// 0x800E9B40 - Check if How to Play input sequence exists
bool32 ftCommon_CheckHowToPlayInputSeq(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->p_howtoplay_input != NULL)
    {
        return TRUE;
    }
    else return FALSE;
}

// 0x800E9B64
void efRunProc(GObj *fighter_gobj, void (*proc)(GObj*, Effect_Struct*))
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->is_statupdate_stop_gfx)
    {
        GObj *effect_gobj = gOMObjCommonLinks[gOMObjLinkIndexEffect];

        while (effect_gobj != NULL)
        {
            Effect_Struct *ep = EffectGetStruct(effect_gobj);

            GObj *next_effect = effect_gobj->group_gobj_next;

            if ((ep != NULL) && (fighter_gobj == ep->fighter_gobj))
            {
                proc(effect_gobj, ep);
            }
            effect_gobj = next_effect;
        }
    }
}

// 0x800E9BE8
void efDestroyGFX(GObj *effect_gobj, Effect_Struct *ep)
{
    Effect_Info *einfo = ep->einfo;

    if (einfo != NULL)
    {
        func_ovl0_800D39D4(einfo->unk_effect_0xB8, ep->unk_effectstruct_0x8 >> 3);
    }
    func_ovl2_800FD4F8(ep);
    func_80009A84(effect_gobj);
}

// 0x800E9C3C
void ftCommon_ProcDestroyGFX(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    efRunProc(fighter_gobj, efDestroyGFX);

    fp->is_statupdate_stop_gfx = FALSE;
}

// 0x800E9C78
void efPauseGFX(GObj *effect_gobj, Effect_Struct *ep)
{
    ep->is_pause_effect = TRUE;
}

// 0x800E9C78
void ftCommon_ProcPauseGFX(GObj *effect_gobj)
{
    efRunProc(effect_gobj, efPauseGFX);
}

// 0x800E9CB0
void efResumeGFX(GObj *effect_gobj, Effect_Struct *ep)
{
    ep->is_pause_effect = FALSE;
}

// 0x800E9CC4
void ftCommon_ProcResumeGFX(GObj *fighter_gobj)
{
    efRunProc(fighter_gobj, efResumeGFX);
}

// 0x800E9CE8
void ftCommon_VelDamageTransferGround(Fighter_Struct *fp)
{
    if (fp->ground_or_air == ground)
    {
        Vec3f *ground_angle = &fp->coll_data.ground_angle;

        if (fp->phys_info.vel_damage_ground == 0.0F)
        {
            fp->phys_info.vel_damage_ground = fp->phys_info.vel_damage_air.x;

            if (fp->phys_info.vel_damage_ground > 250.0F)
            {
                fp->phys_info.vel_damage_ground = 250.0F;
            }
            if (fp->phys_info.vel_damage_ground < -250.0F)
            {
                fp->phys_info.vel_damage_ground = -250.0F;
            }
            fp->phys_info.vel_damage_air.x = ground_angle->y * fp->phys_info.vel_damage_ground;
            fp->phys_info.vel_damage_air.y = -ground_angle->x * fp->phys_info.vel_damage_ground;
        }
    }
}

/*
3F0CCCCD 3FE8BA2E 3F19999A 3FD55555
3F333333 3FB6DB6E 3F400000 3FAAAAAB
3F4CCCCD 3FA00000 3F666666 3F8E38E4
3F733333 3F86BCA2 3F800000 3F800000
3F8B851F 3F6ADCC5 3F000000 40A00000
3F0CCCCD 40800000 3F19999A 40555555
3F266666 4036DB6E 3F333333 40200000
3F400000 3FE8BA2E 3F4CCCCD 3FD8F2FC
3F59999A 3FCB2CB3 3F666666 3FBF0B76
3F733333 3FB4481D 3F266666 40555555
3F333333 4036DB6E 3F3D70A4 40200000
3F451EB8 400E38E4 3F4CCCCD 40000000
3F800000 3F124925 3F866666 3F09A269
3F8CCCCD 3F034834 3F933333 3EF3CF3E
3F9D70A4 3EE6A171 3F866666 3EDE9BD4
3F8CCCCD 3ECCCCCD 3F933333 3EBDA12F
3F99999A 3EB6DB6E 3FA00000 3EAAAAAB
3F666666 3F800000 3F800000 3F800000
3F8CCCCD 3F800000 3F9C28F6 3F800000
3FC00000 3F800000 3F8A3D71 3F6D097B
*/

extern f32 Knockback_Handicap_MulTable[40][2] = 
{
    { 0.55F,  16.363636363636F / 9.0F },
    {  0.6F,             15.0F / 9.0F },
    {  0.7F,   12.85714316367F / 9.0F },
    { 0.75F,             12.0F / 9.0F },
    {  0.8F,            11.25F / 9.0F },
    {  0.9F,             10.0F / 9.0F },
    { 0.95F,    9.47368454931F / 9.0F },
    {  1.0F,              9.0F / 9.0F },
    { 1.09F,   8.256880581381F / 9.0F },
    {  0.5F,             45.0F / 9.0F },
    { 0.55F,             36.0F / 9.0F },
    {  0.6F,             30.0F / 9.0F },
    { 0.65F,    25.7142863268F / 9.0F },
    {  0.7F,             22.5F / 9.0F },
    { 0.75F,  16.363636363636F / 9.0F },
    {  0.8F,  15.254237651824F / 9.0F },
    { 0.85F,  14.285714507102F / 9.0F },
    {  0.9F,  13.432835340495F / 9.0F },
    { 0.95F,  12.676056504246F / 9.0F },
    { 0.65F,             30.0F / 9.0F },
    {  0.7F,  25.714286327358F / 9.0F },
    { 0.74F,             22.5F / 9.0F },
    { 0.77F,             20.0F / 9.0F },
    {  0.8F,             18.0F / 9.0F },
    {  1.0F,   5.142857372757F / 9.0F },
    { 1.05F,   4.838709890842F / 9.0F },
    {  1.1F,   4.615384340286F / 9.0F },
    { 1.15F,   4.285714566707F / 9.0F },
    { 1.23F,   4.054054054054F / 9.0F },
    { 1.05F,   3.913043618196F / 9.0F },
    {  1.1F,              3.6F / 9.0F },
    { 1.15F,   3.333333333333F / 9.0F },
    {  1.2F,   3.214285790920F / 9.0F },
    { 1.25F,              3.0F / 9.0F },
    {  0.9F,              9.0F / 9.0F },
    {  1.0F,              9.0F / 9.0F },
    {  1.1F,              9.0F / 9.0F },
    { 1.22F,              9.0F / 9.0F },
    {  1.5F,              9.0F / 9.0F },
    { 1.08F,   8.333333333333F / 9.0F }
};

f32 gmCommon_DamageCalcKnockback(s32 percent_damage, s32 recent_damage, s32 hit_damage, s32 knockback_weight, s32 knockback_scale, s32 knockback_base, f32 weight, s32 attack_handicap, s32 defend_handicap) 
{
    f32 knockback;

    if (knockback_weight != 0)
    {
        knockback = ( ( ( ( ( ( 1.0F + ( 10.0F * knockback_weight * 0.05F) ) * weight * 1.4F ) + 18.0F ) * ( knockback_scale * 0.01F ) ) + knockback_base ) * ( Match_Info->unk_0xB * 0.01F ) * Knockback_Handicap_MulTable[attack_handicap - 1][0] ) * Knockback_Handicap_MulTable[defend_handicap - 1][1];
    } 
    else 
    {
        f32 damage_add = percent_damage + recent_damage;

        knockback = ( ( ( ( ( ( ( damage_add * 0.1F ) + ( damage_add * hit_damage * 0.05F ) ) * weight * 1.4F ) + 18.0F ) * ( knockback_scale * 0.01F ) ) + knockback_base ) * ( Match_Info->unk_0xB * 0.01F ) * Knockback_Handicap_MulTable[attack_handicap - 1][0] ) * Knockback_Handicap_MulTable[defend_handicap - 1][1];
    }
    if (knockback >= 2500.0F)
    {
        knockback = 2500.0F;
    }
    if (Save_Info.unk5E2 & 1) 
    {
        knockback = rand_f32() * 200.0F;
    }
    return knockback;
}