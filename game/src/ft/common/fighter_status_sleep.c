#include "fighter.h"
#include "gmmatch.h"

bool32 func_ovl3_8013D580(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 steal_from_port_index[4];
    s32 active_teammate_count;
    s32 player_id;
    s32 stock_count;

    if ((Match_Info->match_type & 2) && (Match_Info->is_team_battle == TRUE) && (fp->status_info.status_id == ftStatus_Common_Sleep))
    {
        if (fp->status_vars.common.sleep.stock_steal_wait == 0)
        {
            for (active_teammate_count = 0, stock_count = 0, player_id = 0; player_id < ARRAY_COUNT(Match_Info->player_block); player_id++)
            {
                if ((player_id != fp->player_id) && (Match_Info->player_block[player_id].player_kind != 2) && (fp->team == Match_Info->player_block[player_id].port_index))
                {
                    if (Match_Info->player_block[player_id].stock_count > 0)
                    {
                        if (stock_count < Match_Info->player_block[player_id].stock_count)
                        {
                            active_teammate_count = 0;
                            stock_count = Match_Info->player_block[player_id].stock_count;
                        }
                        steal_from_port_index[active_teammate_count] = player_id;

                        active_teammate_count++;
                    }
                }
            }
            if (active_teammate_count != 0)
            {
                return TRUE; // Do not bring up pause menu
            }
        }
    }
    return FALSE; // Bring up pause menu
}

void func_ovl3_8013D6D0(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *steal_gobj;
    s32 active_teammate_count;
    s32 steal_from_port_index[4];
    s32 player_id;
    s32 random_steal_target;
    s32 stock_count;

    if ((Match_Info->match_type & 2) && (Match_Info->is_team_battle == TRUE))
    {
        if (this_fp->status_vars.common.sleep.stock_steal_wait != 0)
        {
            this_fp->status_vars.common.sleep.stock_steal_wait--;

            if (this_fp->status_vars.common.sleep.stock_steal_wait == 0)
            {
                this_fp->stock_count = 0;
                Match_Info->player_block[this_fp->player_id].stock_count = 0;

                func_ovl3_8013CF60(fighter_gobj);
            }
        }
        else
        {
            if (this_fp->input.button_press & HAL_BUTTON_START)
            {
                for (active_teammate_count = 0, stock_count = 0, player_id = 0; player_id < ARRAY_COUNT(Match_Info->player_block); player_id++)
                {
                    if ((player_id != this_fp->player_id) && (Match_Info->player_block[player_id].player_kind != 2) && (this_fp->team == Match_Info->player_block[player_id].port_index)) {

                        if (Match_Info->player_block[player_id].stock_count > 0)
                        {
                            if (stock_count < Match_Info->player_block[player_id].stock_count)
                            {
                                active_teammate_count = 0;
                                stock_count = Match_Info->player_block[player_id].stock_count;
                            }
                            steal_from_port_index[active_teammate_count] = player_id;
                            active_teammate_count++;
                        }
                    }
                }
                if (active_teammate_count != 0)
                {
                    random_steal_target = rand_u16_range(active_teammate_count);

                    Match_Info->player_block[steal_from_port_index[random_steal_target]].stock_count--;

                    steal_gobj = Match_Info->player_block[steal_from_port_index[random_steal_target]].fighter_gobj;

                    FighterGetStruct(steal_gobj)->stock_count--;

                    this_fp->stock_count = -2;

                    Match_Info->player_block[this_fp->player_id].stock_count = -2;

                    this_fp->status_vars.common.sleep.stock_steal_wait = FTCOMMON_SLEEP_STOCK_STEAL_WAIT;

                    func_ovl2_801102B0(this_fp->player_id, steal_from_port_index[random_steal_target]);

                    func_800269C0(0x114U);
                }
            }
        }
    }
}

void func_ovl3_8013D8B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Common_Sleep, 0.0F, 1.0F, 0U);

    fp->x18D_flag_b7 = TRUE;
    fp->x18E_flag_b0 = TRUE;
    fp->x191_flag_b1 = TRUE;
    fp->x191_flag_b3 = TRUE;

    fp->status_vars.common.sleep.stock_steal_wait = 0;

    fp->x191_flag_b4567 = 1;

    fp->x18E_flag_b3 = TRUE;
}