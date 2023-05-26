#include "fighter.h"
#include "article.h"
#include "gmmatch.h"

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
    GObj *fighter_gobj = gOMObjCommonLinks[GObjLinkIndexFighter];

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

    Match_Info->player_block[player_id].unk_pblock_0xD = 0;
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
    GObj *fighter_gobj = gOMObjCommonLinks[GObjLinkIndexFighter];

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
        ftCommon_SetModelPartRenderState(fighter_gobj, 0x15, 0);
        ftCommon_SetModelPartRenderState(fighter_gobj, 0x13, -1);
    }
}

// 0x800E8744
void ftCommon_GetHammerSetBGM(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ft_kind == Ft_Kind_Link) || (fp->ft_kind == Ft_Kind_PolyLink))
    {
        ftCommon_SetModelPartRenderState(fighter_gobj, 0x15, -1);
        ftCommon_SetModelPartRenderState(fighter_gobj, 0x13, 0);
    }
    ftSpecialItem_BGMCheckFighters();
}

// 0x800E87A0
void ftCommon_HitStatusSetColAnim(GObj *fighter_gobj, s32 hit_status)
{
    switch (hit_status)
    {
    case gmHitCollision_HitStatus_Normal:
        func_ovl2_800E9814(fighter_gobj, 2, 0);
        break;

    case gmHitCollision_HitStatus_Invincible:
        func_ovl2_800E9814(fighter_gobj, 4, 0);
        break;

    case gmHitCollision_HitStatus_Intangible:
        func_ovl2_800E9814(fighter_gobj, 3, 0);
        break;
    }
}

// 0x800E880C
void ftCommon_SetHitStatusPartAll(GObj *fighter_gobj, s32 hit_status)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hurt); i++)
    {
        Fighter_Hurt *ft_hurt = &fp->fighter_hurt[i];

        if (ft_hurt->hit_status != gmHitCollision_HitStatus_None)
        {
            ft_hurt->hit_status = hit_status;
        }
    }
    fp->is_hitstatus_nodamage = (hit_status == gmHitCollision_HitStatus_Normal) ? FALSE : TRUE;

    ftCommon_HitStatusSetColAnim(fighter_gobj, hit_status);
}

// 0x800E8884
void ftCommon_SetHitStatusPart(GObj *fighter_gobj, s32 joint_index, s32 hit_status)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hurt); i++)
    {
        Fighter_Hurt *ft_hurt = &fp->fighter_hurt[i];

        if ((ft_hurt->hit_status != gmHitCollision_HitStatus_None) && (joint_index == ft_hurt->joint_index))
        {
            ft_hurt->hit_status = hit_status;

            if (ft_hurt->hit_status != gmHitCollision_HitStatus_Normal)
            {
                fp->is_hitstatus_nodamage = TRUE;
            }
            return; // This means if there are multiple hurtboxes on the same bone/joint ID, only the first one is checked; same as Melee with Mr. Game & Watch / Fox's nose hurtboxes 
        }
    }
}

// 0x800E8A24
void ftCommon_SetHitStatusAll(GObj *fighter_gobj, s32 hit_status)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->hit_status = hit_status;

    ftCommon_HitStatusSetColAnim(fighter_gobj, hit_status);
}

// 0x800E8A48 - Get most effective bone collision state
s32 ftCommon_GetBestHitStatusPart(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 hit_status_default = fp->hit_status;
    s32 hit_status_best = fp->fighter_hurt[0].hit_status;
    s32 i;

    if (hit_status_best != gmHitCollision_HitStatus_Normal)
    {
        for (i = 1; i < ARRAY_COUNT(fp->fighter_hurt); i++)
        {
            Fighter_Hurt *ft_hurt = &fp->fighter_hurt[i];

            if (ft_hurt->hit_status == gmHitCollision_HitStatus_None) break;

            else if (ft_hurt->hit_status < hit_status_best)
            {
                hit_status_best = ft_hurt->hit_status;
            }
        }
    }
    if (hit_status_default < hit_status_best)
    {
        hit_status_default = hit_status_best;
    }
    return hit_status_default;
}

// 0x800E8AAC - Get overall best collision state
s32 ftCommon_GetBestHitStatusAll(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 hit_status_best = ftCommon_GetBestHitStatusPart(fighter_gobj);

    if (hit_status_best < fp->special_status)
    {
        hit_status_best = fp->special_status;
    }
    if (hit_status_best < fp->special_hit_status)
    {
        hit_status_best = fp->special_hit_status;
    }
    return hit_status_best;
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

            break;
        }
    }
}