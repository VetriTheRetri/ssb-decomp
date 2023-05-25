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