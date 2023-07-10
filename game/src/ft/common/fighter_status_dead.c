#include "fighter.h"
#include "gmmatch.h"
#include "gmground.h"
#include "ground.h"

// 0x8013BC60
void func_ovl3_8013BC60(u16 sfx_id)
{
    func_800269C0(sfx_id);
    func_ovl2_80113804(sfx_id);
}

// 0x8013BC8C
void func_ovl3_8013BC8C(ftStruct *this_fp)
{
    s32 i;

    func_ovl2_800E806C(this_fp, 0, 30);

    for (i = 0; i < ARRAY_COUNT(gpBattleState->player_block); i++)
    {
        if ((i != this_fp->player) && (gpBattleState->player_block[i].player_kind == Ft_Kind_Mario))
        {
            GObj *fighter_gobj = gpBattleState->player_block[i].fighter_gobj;

            if (fighter_gobj != NULL)
            {
                ftStruct *other_fp = ftGetStruct(fighter_gobj);

                if ((!(gpBattleState->match_rules & GMMATCH_GAMERULE_STOCK)) || (other_fp->stock_count != -1))
                {
                    func_ovl2_800E806C(other_fp, 1, 15);
                }
                else continue;
            }
        }
    }
}

// 0x8013BD64
void ftCommon_Dead_UpdateScore(ftStruct *this_fp)
{
    func_ovl2_8010F76C(this_fp);
    func_ovl2_80114968(this_fp);

    gpBattleState->player_block[this_fp->player].falls++;

    if (gpBattleState->is_display_score)
    {
        ifDisplayScoreFighter(this_fp, -1);
    }
    if ((this_fp->damage_player != -1) && (this_fp->damage_player != GMMATCH_PLAYERS_MAX))
    {
        gpBattleState->player_block[this_fp->damage_player].score++;

        gpBattleState->player_block[this_fp->damage_player].total_ko_player[this_fp->player]++;

        if (gpBattleState->is_display_score)
        {
            ifDisplayScoreFighter(ftGetStruct(gpBattleState->player_block[this_fp->damage_player].fighter_gobj), 1);
        }
    }
    else gpBattleState->player_block[this_fp->player].total_self_destruct++;
    
    if (gpBattleState->match_rules & GMMATCH_GAMERULE_STOCK)
    {
        this_fp->stock_count--;

        gpBattleState->player_block[this_fp->player].stock_count--;

        ifDisplayStockIconFall(this_fp);
    }
    if (gpBattleState->match_rules & GMMATCH_GAMERULE_1PGAME)
    {
        this_fp->stock_count--;

        gpBattleState->player_block[this_fp->player].stock_count--;

        func_unkmulti_8018EFFC(this_fp->player, this_fp->unk_0x15);
    }
    if (gpBattleState->match_rules & GMMATCH_GAMERULE_BONUS)
    {
        ifDisplayBonusFailure();
    }
}

// 0x8013BF94
void ftCommon_Dead_CheckRebirth(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    if (gpBattleState->match_rules & GMMATCH_GAMERULE_STOCK)
    {
        if (fp->stock_count == -1)
        {
            ftCommon_Sleep_SetStatus(fighter_gobj);

            return;
        }
    }
    else if (gpBattleState->match_rules & GMMATCH_GAMERULE_1PGAME)
    {
        if (gpBattleState->player_block[fp->player].is_rebirth_multi != FALSE)
        {
            func_unkmulti_8018E18C(fighter_gobj);

            return;
        }
        else if (fp->stock_count == -1)
        {
            ftCommon_Sleep_SetStatus(fighter_gobj);

            return;
        }
    }
    ftCommon_RebirthDown_SetStatus(fighter_gobj);
}

// 0x8013C050
void ftCommon_Dead_ResetCommonVars(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftCommon_ProcDamageStopVoice(fighter_gobj);
    func_ovl2_800D7994(fighter_gobj);
    func_ovl3_8014AF2C(fighter_gobj);

    fp->ground_or_air = GA_Air;
    fp->coll_data.ground_line_id = -1;

    if (fp->item_hold != NULL)
    {
        itMain_DestroyItem(fp->item_hold);
    }
}

// 0x8013C0B0
void ftCommon_Dead_ClearSpecialStats(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    fp->star_invincible_timer = 0;
    fp->is_nullstatus = TRUE;
    fp->x18E_flag_b0 = TRUE;

    ftSpecialItem_BGMCheckFighters(fighter_gobj);
}

// 0x8013C0EC
void ftCommon_Dead_UpdateRebirthWait(GObj *fighter_gobj) // Unused
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    fp->status_vars.common.dead.rebirth_wait--;

    if (fp->status_vars.common.dead.rebirth_wait == 0)
    {
        ftCommon_Dead_CheckRebirth(fighter_gobj);
    }
}

// 0x8013C120
void ftCommon_Dead_InitStatusVars(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    fp->status_vars.common.dead.rebirth_wait = FTCOMMON_DEAD_REBIRTH_WAIT;

    func_ovl2_800D9444(fighter_gobj);

    fp->is_invisible = TRUE;
    fp->x191_flag_b3 = TRUE;
    fp->x18E_flag_b3 = TRUE;

    efMain_CreateEarthquake(2);
    func_ovl3_8013BC8C(fp);
    ftCommon_Dead_UpdateScore(fp);

    if (fp->attributes->dead_sfx[0] != 0x2B7)
    {
        func_ovl3_8013BC60(fp->attributes->dead_sfx[0]);
    }
    if (fp->attributes->dead_sfx[1] != 0x2B7)
    {
        func_ovl3_8013BC60(fp->attributes->dead_sfx[1]);
    }
}

// 0x8013C1C4
void ftCommon_DeadDown_SetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;
    u32 sfx_id;

    ftCommon_Dead_ResetCommonVars(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadDown, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftCommon_Dead_ClearSpecialStats(fighter_gobj);
    ftCommon_Dead_InitStatusVars(fighter_gobj);

    pos = DObjGetStruct(fighter_gobj)->translate;

    if (gpBattleState->game_type != 2)
    {
        if (gpMapData->cam_bound_right < pos.x)
        {
            pos.x = gpMapData->cam_bound_right;
        }

        if (pos.x < gpMapData->cam_bound_left)
        {
            pos.x = gpMapData->cam_bound_left;
        }
    }
    func_ovl2_801021C0(&pos, fp->player, 0);
    func_ovl2_80115BF0(0x51, 0);

    if (((gpBattleState->gr_kind >= Gr_Kind_Bonus1Start) && (gpBattleState->gr_kind < Gr_Kind_Bonus2Start)) || ((gpBattleState->gr_kind >= Gr_Kind_Bonus2Start) && (gpBattleState->gr_kind < Gr_Kind_CustomStart)))
    {
        sfx_id = 0x9B;
    }
    else sfx_id = 0x9A;

    func_ovl3_8013BC60(sfx_id);
}

// 0x8013C30C
void ftCommon_DeadRight_SetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;
    u32 sfx_id;

    ftCommon_Dead_ResetCommonVars(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadLeftRight, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftCommon_Dead_ClearSpecialStats(fighter_gobj);
    ftCommon_Dead_InitStatusVars(fighter_gobj);

    pos = DObjGetStruct(fighter_gobj)->translate;

    if (gpBattleState->game_type != gmMatch_GameType_Bonus)
    {
        if (pos.y > gpMapData->cam_bound_top)
        {
            pos.y = gpMapData->cam_bound_top;
        }

        if (pos.y < gpMapData->cam_bound_bottom)
        {
            pos.y = gpMapData->cam_bound_bottom;
        }
    }
    func_ovl2_801021C0(&pos, fp->player, 1);
    func_ovl2_80115BF0(0x51, 0);

    if (((gpBattleState->gr_kind >= Gr_Kind_Bonus1Start) && (gpBattleState->gr_kind < Gr_Kind_Bonus2Start)) || ((gpBattleState->gr_kind >= Gr_Kind_Bonus2Start) && (gpBattleState->gr_kind < Gr_Kind_CustomStart)))
    {
        sfx_id = 0x9B;
    }
    else sfx_id = 0x9A;

    func_ovl3_8013BC60(sfx_id);
}

// 0x8013C454
void ftCommon_DeadLeft_SetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;
    u32 sfx_id;

    ftCommon_Dead_ResetCommonVars(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadLeftRight, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    ftCommon_Dead_ClearSpecialStats(fighter_gobj);
    ftCommon_Dead_InitStatusVars(fighter_gobj);

    pos = DObjGetStruct(fighter_gobj)->translate;

    if (gpBattleState->game_type != gmMatch_GameType_Bonus)
    {
        if (pos.y > gpMapData->cam_bound_top)
        {
            pos.y = gpMapData->cam_bound_top;
        }
        if (pos.y < gpMapData->cam_bound_bottom)
        {
            pos.y = gpMapData->cam_bound_bottom;
        }
    }
    func_ovl2_801021C0(&pos, fp->player, 3);
    func_ovl2_80115BF0(0x51, 0);

    if (((gpBattleState->gr_kind >= Gr_Kind_Bonus1Start) && (gpBattleState->gr_kind < Gr_Kind_Bonus2Start)) || ((gpBattleState->gr_kind >= Gr_Kind_Bonus2Start) && (gpBattleState->gr_kind < Gr_Kind_CustomStart)))
    {
        sfx_id = 0x9B;
    }
    else sfx_id = 0x9A;

    func_ovl3_8013BC60(sfx_id);
}

// 0x8013C59C
void ftCommon_DeadUpStar_ProcUpdate(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    switch (fp->command_vars.flags.flag1)
    {
    case 1:
        fp->colanim.color1.a = 128 - ((fp->status_vars.common.dead.rebirth_wait * 128) / FTCOMMON_DEADUP_REBIRTH_WAIT);
        break;

    default:
        break;
    }
    if (fp->status_vars.common.dead.rebirth_wait != 0)
    {
        fp->status_vars.common.dead.rebirth_wait--;
    }
    if (fp->status_vars.common.dead.rebirth_wait == 0)
    {
        switch (fp->command_vars.flags.flag1)
        {
        case 0:
            fp->phys_info.vel_air.y = ((gpMapData->cam_bound_top * 0.6F) - DObjGetStruct(fighter_gobj)->translate.y) / 180.0F;
            fp->phys_info.vel_air.z = FTCOMMON_DEADUPFALL_VEL_Z;

            fp->colanim.is_use_color1 = TRUE;

            fp->colanim.color1.r = gpMapData->fog_color.r;
            fp->colanim.color1.g = gpMapData->fog_color.g;
            fp->colanim.color1.b = gpMapData->fog_color.b;
            fp->colanim.color1.a = 0;

            fp->status_vars.common.dead.rebirth_wait = FTCOMMON_DEADUP_REBIRTH_WAIT;

            fp->command_vars.flags.flag1++;
            break;

        case 1:
            func_ovl2_800D9444(fighter_gobj);
            func_ovl2_80100720(&fp->joint[ftParts_TopN_Joint]->translate, 5.0F);

            fp->is_invisible = TRUE;
            fp->x191_flag_b3 = TRUE;

            ftCommon_Dead_UpdateScore(fp);
            func_ovl3_8013BC60(0xCU);

            fp->x18E_flag_b3 = TRUE;
            fp->colanim.is_use_color1 = FALSE;

            fp->status_vars.common.dead.rebirth_wait = FTCOMMON_DEAD_REBIRTH_WAIT;

            fp->command_vars.flags.flag1++;
            break;

        case 2:
            ftCommon_Dead_CheckRebirth(fighter_gobj);
            break;

        default:
            break;
        }
    }
}

// 0x8013C740
void ftCommon_DeadUpStar_SetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftCommon_Dead_ResetCommonVars(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadUpStar, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    func_ovl2_800D9444(fighter_gobj);

    fp->status_vars.common.dead.pos = DObjGetStruct(fighter_gobj)->translate;

    fp->x191_flag_b4567 = 2;

    fp->status_vars.common.dead.rebirth_wait = 1;

    fp->command_vars.flags.flag1 = 0;

    ftCommon_Dead_ClearSpecialStats(fighter_gobj);
    func_ovl2_800E7F7C(fighter_gobj, 1);

    if (fp->attributes->deadup_sfx != 0x2B7)
    {
        func_800269C0(fp->attributes->deadup_sfx);
    }
    func_ovl2_800E827C(fighter_gobj, 1);
    ftCommon_ResetColAnim(fighter_gobj);
}

// 0x8013C80C
void ftCommon_DeadUpFall_ProcUpdate(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    s32 sfx_id;

    switch (fp->command_vars.flags.flag1)
    {
    case 1:
        if (DObjGetStruct(fighter_gobj)->translate.y < gpMapData->blastzone_bottom)
        {
            fp->phys_info.vel_air.y = 0.0F;
        }
        break;

    default:
        break;
    }
    if (fp->status_vars.common.dead.rebirth_wait != 0)
    {
        fp->status_vars.common.dead.rebirth_wait--;
    }
    if (fp->status_vars.common.dead.rebirth_wait == 0)
    {
        switch (fp->command_vars.flags.flag1)
        {
        case 0:
            fp->phys_info.vel_air.y = (gpMapData->cam_bound_bottom - DObjGetStruct(fighter_gobj)->translate.y) / 180.0F;
            DObjGetStruct(fighter_gobj)->translate.z = (D_ovl2_80131460->unk_0x74->unk_p_80131460_vec.z - 3000.0F);

            if (DObjGetStruct(fighter_gobj)->translate.z < 2000.0F)
            {
                DObjGetStruct(fighter_gobj)->translate.z = 2000.0F;
            }
            DObjGetStruct(fighter_gobj)->translate.x = (f32)D_ovl2_80131460->unk_0x74->unk_p_80131460_vec.x;
            DObjGetStruct(fighter_gobj)->translate.y = (f32)(D_ovl2_80131460->unk_0x74->unk_p_80131460_vec.y + 3000.0F);

            if (gpMapData->blastzone_top < DObjGetStruct(fighter_gobj)->translate.y)
            {
                DObjGetStruct(fighter_gobj)->translate.y = gpMapData->blastzone_top;
            }
            fp->status_vars.common.dead.rebirth_wait = FTCOMMON_DEADUP_REBIRTH_WAIT;

            fp->command_vars.flags.flag1++;

            break;

        case 1:
            func_ovl2_800D9444(fighter_gobj);
            func_ovl2_80115BF0(0x51, 0);
            efMain_CreateEarthquake(2);
            func_ovl3_8013BC8C(fp);

            fp->x18E_flag_b3 = TRUE;
            fp->is_invisible = TRUE;
            fp->x191_flag_b3 = TRUE;

            ftCommon_Dead_UpdateScore(fp);

            if (((gpBattleState->gr_kind >= Gr_Kind_Bonus1Start) && (gpBattleState->gr_kind < Gr_Kind_Bonus2Start)) || ((gpBattleState->gr_kind >= Gr_Kind_Bonus2Start) && (gpBattleState->gr_kind < Gr_Kind_CustomStart)))
            {
                sfx_id = 0x9B;
            }
            else sfx_id = 0x9A;

            func_ovl3_8013BC60(sfx_id);

            if (fp->attributes->dead_sfx[0] != 0x2B7)
            {
                func_ovl3_8013BC60(fp->attributes->dead_sfx[0]);
            }
            if (fp->attributes->dead_sfx[1] != 0x2B7)
            {
                func_ovl3_8013BC60(fp->attributes->dead_sfx[1]);
            }
            fp->status_vars.common.dead.rebirth_wait = FTCOMMON_DEAD_REBIRTH_WAIT;
            fp->command_vars.flags.flag1++;

            break;

        case 2:
            ftCommon_Dead_CheckRebirth(fighter_gobj);

            break;

        default:
            break;
        }
    }
}

// 0x8013CAAC
void ftCommon_DeadUpFall_SetStatus(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);

    ftCommon_Dead_ResetCommonVars(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadUpFall, 0.0F, 1.0F, FTSTATUPDATE_NONE_PRESERVE);
    func_ovl2_800D9444(fighter_gobj);

    fp->status_vars.common.dead.pos = DObjGetStruct(fighter_gobj)->translate;

    fp->x191_flag_b4567 = 2;

    fp->status_vars.common.dead.rebirth_wait = 1;

    fp->command_vars.flags.flag1 = 0;

    ftCommon_Dead_ClearSpecialStats(fighter_gobj);
    func_ovl2_800E7F7C(fighter_gobj, 1);

    if (fp->attributes->deadup_sfx != 0x2B7)
    {
        func_800269C0(fp->attributes->deadup_sfx);
    }
    func_ovl2_800E827C(fighter_gobj, 0x13);
    ftCommon_SetModelPartLevelDetailAll(fighter_gobj, 1);
}

// 0x8013CB7C
bool32 ftCommon_Dead_CheckInterruptCommon(GObj *fighter_gobj)
{
    ftStruct *fp = ftGetStruct(fighter_gobj);
    Vec3f *pos = &fp->joint[ftParts_TopN_Joint]->translate;

    if (fp->ft_kind == Ft_Kind_MasterHand)
    {
        return FALSE;
    }
    if (fp->x192_flag_b1)
    {
        return FALSE;
    }
    if (fp->is_check_blastzone)
    {
        if (pos->y < gpMapData->blastzone_bottom)
        {
            pos->y = gpMapData->blastzone_bottom + 500.0F;

            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;
            fp->phys_info.vel_air.z = 0.0F;
        }
        else if (gpMapData->blastzone_top < pos->y)
        {
            pos->y = gpMapData->blastzone_top - 500.0F;

            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;
            fp->phys_info.vel_air.z = 0.0F;
        }
        if (gpMapData->blastzone_right < pos->x)
        {
            pos->x = gpMapData->blastzone_right - 500.0F;

            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;
            fp->phys_info.vel_air.z = 0.0F;
        }
        else if (pos->x < gpMapData->blastzone_left)
        {
            pos->x = gpMapData->blastzone_left + 500.0F;

            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;
            fp->phys_info.vel_air.z = 0.0F;
        }
        return FALSE;
    }
    else if (!(fp->is_nullstatus))
    {
        if ((gpBattleState->game_type == gmMatch_GameType_1PGame) && (gpBattleState->player_block[fp->player].is_rebirth_multi != FALSE))
        {
            if (pos->y < gpMapData->unk_bound_bottom)
            {
                ftCommon_DeadDown_SetStatus(fighter_gobj);

                return TRUE;
            }
            if (pos->x > gpMapData->unk_bound_right)
            {
                ftCommon_DeadRight_SetStatus(fighter_gobj);

                return TRUE;
            }
            if (pos->x < gpMapData->unk_bound_left)
            {
                ftCommon_DeadLeft_SetStatus(fighter_gobj);

                return TRUE;
            }
            if (pos->y > gpMapData->unk_bound_top)
            {
                if (rand_f32() < 0.16666667F)
                {
                    ftCommon_DeadUpFall_SetStatus(fighter_gobj);

                    return TRUE;
                }
                else ftCommon_DeadUpStar_SetStatus(fighter_gobj);

                return TRUE;
            }
        }
        else if (pos->y < gpMapData->blastzone_bottom)
        {
            ftCommon_DeadDown_SetStatus(fighter_gobj);

            return TRUE;
        }
        else if (gpMapData->blastzone_right < pos->x)
        {
            ftCommon_DeadRight_SetStatus(fighter_gobj);

            return TRUE;
        }
        else if (pos->x < gpMapData->blastzone_left)
        {
            ftCommon_DeadLeft_SetStatus(fighter_gobj);

            return TRUE;
        }
        else if (gpMapData->blastzone_top < pos->y)
        {
            if (rand_f32() < 0.16666667F)
            {
                ftCommon_DeadUpFall_SetStatus(fighter_gobj);
            }
            else ftCommon_DeadUpStar_SetStatus(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}
