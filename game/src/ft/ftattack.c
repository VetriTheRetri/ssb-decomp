#include "fighter.h"
#include <game/src/gm/gmmatch.h>

extern const f32 D_ovl2_8012B820[4];

f32 func_ovl2_800EA470(u32 port_id, s32 attack_id, u16 flags)
{
    s32 stale_index = Match_Info->player_block[port_id].stale_index;
    s32 backup_stale_id;
    s32 stale_id;
    s32 flag_id;
    
    if (attack_id != 0)
    {
        flag_id = backup_stale_id = (stale_index != 0) ? stale_index - 1 : ARRAY_COUNT(Match_Info->player_block);

        for (stale_id = 0; stale_id < ARRAY_COUNT(D_ovl2_8012B820); stale_id++)
        {
            if (attack_id == Match_Info->player_block[port_id].stale_flags[flag_id][0])
            {
                if (flags != Match_Info->player_block[port_id].stale_flags[flag_id][1])
                {
                    return D_ovl2_8012B820[stale_id];
                }
                if (flag_id == backup_stale_id)
                {
                    stale_id--;
                }
            }
            flag_id = (flag_id != 0) ? flag_id-- : ARRAY_COUNT(D_ovl2_8012B820);
        }
    }
    return 1.0F;
}