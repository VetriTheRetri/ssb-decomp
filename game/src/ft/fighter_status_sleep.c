#include "fighter.h"
#include "gmmatch.h"

bool32 func_ovl3_8013D580(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 pause_port_index[4];
    s32 steal_player_index;
    s32 player_id;
    s32 stock_count;

    if ((Match_Info->match_type & 2) && (Match_Info->is_team_battle == TRUE) && (fp->status_info.status_id == ftStatus_Common_Sleep))
    {
        if (fp->status_vars.common.sleep.stock_steal_wait == 0)
        {
            for (steal_player_index = 0, stock_count = 0, player_id = 0; player_id < ARRAY_COUNT(Match_Info->player_block); player_id++)
            {
                if ((player_id != fp->player_id) && (Match_Info->player_block[player_id].player_kind != 2) && (fp->team == Match_Info->player_block[player_id].port_index))
                {
                    if (Match_Info->player_block[player_id].stock_count > 0)
                    {
                        if (stock_count < Match_Info->player_block[player_id].stock_count)
                        {
                            steal_player_index = 0;
                            stock_count = Match_Info->player_block[player_id].stock_count;
                        }
                        pause_port_index[steal_player_index] = player_id;

                        steal_player_index++;
                    }
                }
            }
            if (steal_player_index != 0)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}