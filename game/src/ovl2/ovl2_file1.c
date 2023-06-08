#include "gmmatch.h"
#include "fighter.h"

s32 func_ovl2_800D6490(u16 arg0)
{
    s32 var_v1;
    s32 i;

    for (i = 0, var_v1 = 0; i < 16; i++, arg0 = arg0 >> 1)
    {
        if (arg0 & 1)
        {
            var_v1++;
        }
    }
    return var_v1;
}

s32 func_ovl2_800D6508(u16 arg0, u16 arg1, s32 arg2)
{
    s32 var_v1 = -1;

    arg2++;

    do
    {
        var_v1++;

        if ((arg0 & (1 << var_v1)) && !(arg1 & (1 << var_v1)))
        {
            arg2--;
        }
    } 
    while (arg2 != 0);

    return var_v1;
}

s32 func_ovl2_800D6554(u16 arg0, s32 arg1)
{
    s32 var_v1 = -1;

    arg1++;

    do
    {
        var_v1++;

        if (arg0 & (1 << var_v1))
        {
            arg1--;
        }
    }
    while (arg1 != 0);

    return var_v1;
}

extern u32 gmMatchInfo_1PGameTimeTotal; // Static (.bss); Total time taken to complete 1P Game (in frames);

void func_ovl2_800D6590(void)
{
    if (!(Save_Info.unlock_mask & GMSAVE_UNLOCK_MASK_NESS) && (Save_Info.spgame_difficulty >= gmMatch_Difficulty_Normal) && (Scene_Info.continues_used == 0) && (Save_Info.spgame_stock_count < 3))
    {
        Scene_Info.scene_queue = gmSceneIndex_Challenger_Ness;
        return;
    }
    if (!(Save_Info.unlock_mask & GMSAVE_UNLOCK_MASK_CAPTAIN) && (gmMatchInfo_1PGameTimeTotal < 43200)) // Captain Falcon's unlock criteria is 12 minutes instead of 20???
    {
        Scene_Info.scene_queue = gmSceneIndex_Challenger_Captain;
        return;
    }
    if (!(Save_Info.unlock_mask & GMSAVE_UNLOCK_MASK_PURIN))
    {
        Scene_Info.scene_queue = gmSceneIndex_Challenger_Purin;
        return;
    }
}

bool32 func_ovl2_800D6630(void)
{
    s32 ft_index;
    u16 bonus_record_count;

    if (!(Save_Info.unlock_mask & GMSAVE_UNLOCK_MASK_LUIGI))
    {
        for (ft_index = 0, bonus_record_count = 0; ft_index < ARRAY_COUNT(Save_Info.spgame_records); ft_index++)
        {
            if (Save_Info.spgame_records[ft_index].bonus1_task_count == 10) // Check if fighter has broken all targets
            {
                bonus_record_count |= (ft_index << ft_index);
            }
        }
        if ((bonus_record_count & GMSAVEINFO_CHARACTER_MASK_ALL) == GMSAVEINFO_CHARACTER_MASK_ALL)
        {
            for (ft_index = 0, bonus_record_count = 0; ft_index < ARRAY_COUNT(Save_Info.spgame_records); ft_index++)
            {
                if (Save_Info.spgame_records[ft_index].bonus2_task_count == 10) // Check if fighter has boarded all platforms
                {
                    bonus_record_count |= (ft_index << ft_index);
                }
            }

            if ((bonus_record_count & GMSAVEINFO_CHARACTER_MASK_ALL) == GMSAVEINFO_CHARACTER_MASK_ALL)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void func_ovl2_800D6738(s32 arg0)
{
    s32 var_a2 = 0;

    if (Save_Info.spgame_records[Scene_Info.ft_kind].spgame_hiscore < Scene_Info.spgame_score)
    {
        Save_Info.spgame_records[Scene_Info.ft_kind].spgame_hiscore = Scene_Info.spgame_score;
        Save_Info.spgame_records[Scene_Info.ft_kind].spgame_continues = Scene_Info.continues_used;
        Save_Info.spgame_records[Scene_Info.ft_kind].spgame_bonuses = Scene_Info.bonuses;

        if (arg0 != 0)
        {
            Save_Info.spgame_records[Scene_Info.ft_kind].spgame_best_difficulty = Save_Info.spgame_difficulty + 1;
        }
        else Save_Info.spgame_records[Scene_Info.ft_kind].spgame_best_difficulty = 0;

        var_a2 = 1;
    }
    if ((Save_Info.spgame_records[Scene_Info.ft_kind].unk_0x1D == 0) && (arg0 != 0))
    {
        Save_Info.spgame_records[Scene_Info.ft_kind].unk_0x1D = 1;

        var_a2 = 1;
    }
    if (var_a2 != 0)
    {
        func_ovl0_800D45F4();
    }
}

extern struct gmSceneInfo D_800A3F80;
extern gmMatchInfo D_800A4B18;
extern struct Overlay D_ovl2_80116BF0;
extern struct Overlay D_ovl2_80116C14;
extern struct Overlay D_ovl2_80116C38;
extern struct Overlay D_ovl2_80116C5C;
extern struct Overlay D_ovl2_80116C80;
extern struct Overlay D_ovl2_80116CA4;
extern struct Overlay D_ovl2_80116CC8;
extern struct Overlay D_ovl2_80116CEC;
extern struct Overlay D_ovl2_80116D10;
extern struct Overlay D_ovl2_80116D34;
extern struct Overlay D_ovl2_80116D58;
extern u32 D_ovl2_80116D74[2];
extern struct Overlay D_ovl2_80116D7C;
extern u32 D_ovl2_80116D84[7];
extern u8 D_ovl2_80116DA0[];
extern u8 D_ovl2_80130D60;
extern s32 D_ovl2_80130D68;
extern s32 D_ovl2_80130D6C;
extern s32 D_ovl2_80130D70;
extern u8 D_ovl2_80130D74;
extern u8 D_ovl2_80130D75;
extern u8 D_ovl2_80130D76;

void func_ovl2_800D67DC(void)
{
    s32 i, j;
    u16 temp_s1;
    s32 bonus_stat_count;
    bool32 is_player_lose;
    u16 unk_spgame_record;
    u32 bonus_stat_mask;
    s32 temp_v0;
    s32 player_port;
    s32 scene_queue;

    D_ovl2_80130D60 = Scene_Info.scene_previous;

    D_800A4B18.is_team_battle = TRUE;
    D_800A4B18.match_rules = (GMMATCH_GAMERULE_1PGAME | GMMATCH_GAMERULE_TIME);
    D_800A4B18.unk_0xB = 100;
    D_800A4B18.is_display_score = FALSE;
    D_800A4B18.unk_minfo_0x1D_b1 = TRUE;

    if (Save_Info.unk5E2 & 4)
    {
        Scene_Info.ft_kind = Ft_Kind_Mario;
        Scene_Info.unk15 = 0;
    }
    D_800A4B18.player_block[Scene_Info.player_port].handicap = 9;
    D_800A4B18.player_block[Scene_Info.player_port].player_kind = 0;
    D_800A4B18.player_block[Scene_Info.player_port].team_index = 0;
    D_800A4B18.player_block[Scene_Info.player_port].shade_index = 0;
    D_800A4B18.player_block[Scene_Info.player_port].unk_0x8 = Scene_Info.player_port;
    D_800A4B18.player_block[Scene_Info.player_port].unk_0xA = Scene_Info.player_port;
    D_800A4B18.player_block[Scene_Info.player_port].character_kind = Scene_Info.ft_kind;
    D_800A4B18.player_block[Scene_Info.player_port].costume_index = Scene_Info.unk15;
    D_800A4B18.player_block[Scene_Info.player_port].stock_count = Save_Info.spgame_stock_count;
    D_800A4B18.player_block[Scene_Info.player_port].is_rebirth_multi = FALSE;

    Scene_Info.spgame_score = 0;
    Scene_Info.continues_used = 0;
    Scene_Info.bonuses = 0;

    gmMatchInfo_1PGameTimeTotal = 0;

    D_ovl2_80130D68 = 0;
    D_ovl2_80130D6C = 0;
    D_ovl2_80130D70 = 0;
    D_ovl2_80130D74 = 2;

    player_port = Scene_Info.player_port;

    for (i = 0; i < ARRAY_COUNT(Scene_Info.cpu_port); i++)
    {
        if (player_port == 3)
        {
            player_port = 0;
        }
        else player_port++;

        Scene_Info.cpu_port[i] = player_port;
    }
    if (Scene_Info.scene_queue >= 0xE)
    {
        goto block_45;
    }
    else
    {
        while (Scene_Info.scene_queue < 0xE)
        {
            u32 ignore_mask = ~(gmSaveChrMask(Ft_Kind_Ness) | gmSaveChrMask(Ft_Kind_Purin) | gmSaveChrMask(Ft_Kind_Captain) | gmSaveChrMask(Ft_Kind_Luigi));

            temp_s1 = (Save_Info.unk458 | (GMSAVEINFO_CHARACTER_MASK_ALL & ignore_mask)) & ~(1 << Scene_Info.ft_kind);

            is_player_lose = FALSE;

            switch (Scene_Info.scene_queue)
            {
            case 4:
                temp_s1 &= ~1;

                D_800A4B18.player_block[Scene_Info.cpu_port[0]].character_kind = func_ovl2_800D6508(temp_s1, 0, rand_u16_range(func_ovl2_800D6490(temp_s1)));

                if (D_800A4B18.player_block[Scene_Info.cpu_port[0]].character_kind == Ft_Kind_Luigi)
                {
                    D_800A4B18.player_block[Scene_Info.cpu_port[0]].costume_index = func_ovl2_800EC0EC(Ft_Kind_Luigi, 1);
                }
                else D_800A4B18.player_block[Scene_Info.cpu_port[0]].costume_index = 0;

                D_800A4B18.player_block[Scene_Info.cpu_port[0]].shade_index = 0;
                break;

            case 6:
                temp_v0 = func_ovl2_800D6490(temp_s1);

                D_800A4B18.player_block[Scene_Info.cpu_port[0]].character_kind = func_ovl2_800D6508(temp_s1, 0, rand_u16_range(temp_v0));
                D_800A4B18.player_block[Scene_Info.cpu_port[0]].costume_index = 0;
                D_800A4B18.player_block[Scene_Info.cpu_port[0]].shade_index = 0;

                D_800A4B18.player_block[Scene_Info.cpu_port[1]].character_kind = func_ovl2_800D6508(temp_s1, (1 << D_800A4B18.player_block[Scene_Info.cpu_port[0]].character_kind), rand_u16_range(temp_v0 - 1));
                D_800A4B18.player_block[Scene_Info.cpu_port[1]].costume_index = 0;
                D_800A4B18.player_block[Scene_Info.cpu_port[1]].shade_index = 0;
                break;

            case 8:
                temp_s1 = (Save_Info.unk458 | gmSaveChrMask(Ft_Kind_Kirby));

                D_ovl2_80130D75 = func_ovl2_800D6554(temp_s1, rand_u16_range(func_ovl2_800D6490(temp_s1)));

                D_ovl2_80130D76 = D_ovl2_80116DA0[D_ovl2_80130D75];
                break;
            }
            load_overlay(&D_ovl2_80116BF0);
            load_overlay(&D_ovl2_80116C14);

            Scene_Info.scene_previous = 0x34;
            Scene_Info.scene_current = 0xE;

            classic_map_entry();

            switch (Scene_Info.scene_queue)
            {
            case 3:
            case 7:
                load_overlay(&D_ovl2_80116D34);
                load_overlay(&D_ovl2_80116D58);

                Scene_Info.scene_previous = 0x34;
                Scene_Info.scene_current = 0x35;

                bonus_game_play_entry();
                break;

            default:
                load_overlay(&D_ovl2_80116D34);
                load_overlay(&D_ovl2_80116D10);
                overlay_set62_entry();

                if ((Scene_Info.scene_queue != 0xB) && ((D_800A4B18.player_block[Scene_Info.player_port].stock_count == -1) || (D_800A4B18.match_time_remain <= 0)))
                {
                    is_player_lose = TRUE;
                }
                break;
            }
            if (Scene_Info.unk12 != FALSE)
            {
                Scene_Info.scene_previous = 0x34;
                Scene_Info.scene_current = 8;

                return;
            }
            if (is_player_lose != FALSE)
            {
                load_overlay(&D_ovl2_80116BF0);
                load_overlay(&D_ovl2_80116D7C);
                overlay_set49_entry();

                if (Scene_Info.is_select_continue != FALSE)
                {
                    Scene_Info.continues_used++;

                    D_800A4B18.player_block[Scene_Info.player_port].stock_count = Save_Info.spgame_stock_count;

                    Scene_Info.scene_queue--;
                    D_ovl2_80130D74--;


                    if (!(D_ovl2_80130D74))
                    {
                        D_ovl2_80130D74 = 2;

                        D_ovl2_80130D70++;

                        if (D_ovl2_80130D70 > 9)
                        {
                            D_ovl2_80130D70 = 9;
                        }
                    }
                }
                else
                {
                    func_ovl2_800D6738(0);

                    Scene_Info.scene_previous = 0x34;
                    Scene_Info.scene_current = 0x1B;

                    return;
                }
            }
            else
            {
                D_ovl2_80130D70 = 0;
                D_ovl2_80130D74 = 2;
                bonus_stat_count = 0;

                for (i = 0; i < ARRAY_COUNT(Scene_Info.bonus_get_mask); i++)
                {
                    bonus_stat_mask = Scene_Info.bonus_get_mask[i];

                    for (j = 0; j < 32; j++, bonus_stat_mask >>= 1)
                    {
                        if (bonus_stat_mask & 1)
                        {
                            bonus_stat_count++;
                        }
                    }
                }
                Scene_Info.bonuses += bonus_stat_count;

                load_overlay(&D_ovl2_80116BF0);
                load_overlay(&D_ovl2_80116C38);

                Scene_Info.scene_previous = 0x34;
                Scene_Info.scene_current = 0x33;

                overlay_set50_51_entry();
            }
            Scene_Info.scene_queue++;
        }
        func_ovl2_800D6738(1);
        load_overlay(&D_ovl2_80116BF0);
        load_overlay(&D_ovl2_80116C80);

        Scene_Info.scene_previous = 0x34;
        Scene_Info.scene_current = 0x30;

        overlay_set48_entry();
        load_overlay(&D_ovl2_80116CEC);

        Scene_Info.scene_previous = 0x34;
        Scene_Info.scene_current = 0x38;

        func_unkmulti_801351B8();
        load_overlay(&D_ovl2_80116CC8);

        Scene_Info.scene_previous = 0x34;
        Scene_Info.scene_current = 0x37;

        func_unkmulti_8013200C();

        Scene_Info.scene_queue--;

        func_ovl2_800D6590();
    }
block_45:
    if (Scene_Info.scene_queue >= 0xE)
    {
        Scene_Info.unk09 = D_ovl2_80116D74[(s32)Scene_Info.scene_queue];

        load_overlay(&D_ovl2_80116BF0);
        load_overlay(&D_ovl2_80116C5C);

        Scene_Info.scene_previous = 0x34;
        Scene_Info.scene_current = 0xD;

        overlay_set13_entry();

        D_800A4B18.player_block[Scene_Info.player_port].stock_count = 0;

        load_overlay(&D_ovl2_80116D34);
        load_overlay(&D_ovl2_80116D10);
        overlay_set62_entry();

        if (Scene_Info.unk12 != FALSE)
        {
            Scene_Info.scene_previous = 0x34;
            Scene_Info.scene_current = 8;

            return;
        }
        if ((D_800A4B18.player_block[Scene_Info.player_port].stock_count != -1) && (D_800A4B18.match_time_remain != 0))
        {
            Scene_Info.unk43 = D_800A3F80.unk43;
            Scene_Info.unk02 = D_ovl2_80116D84[Scene_Info.scene_queue];

            load_overlay(&D_ovl2_80116BF0);
            load_overlay(&D_ovl2_80116CA4);

            Scene_Info.scene_previous = 0x34;
            Scene_Info.scene_current = 0xC;

            func_multiple_801323F8();

        }
        else if (Scene_Info.unk43 < 9)
        {
            Scene_Info.unk43 += 2;
        }
        if (Scene_Info.scene_queue == 0xE)
        {
            Scene_Info.scene_previous = 0x35;
            Scene_Info.scene_current = 0x13;
            return;
        }
    }
    if (!(Save_Info.unlock_mask & 0x10))
    {
        if ((Save_Info.unk5DC & 0xFF) == 0xFF)
        {
            for (i = 0, unk_spgame_record = 0; i < ARRAY_COUNT(Save_Info.spgame_records); i++)
            {
                if (Save_Info.spgame_records[i].unk_0x1D != 0)
                {
                    unk_spgame_record |= (1 << i);
                }
            }

            if ((unk_spgame_record & 0x36F) == 0x36F)
            {
                Scene_Info.unk02 = 4;

                load_overlay(&D_ovl2_80116BF0);
                load_overlay(&D_ovl2_80116CA4);

                Scene_Info.scene_previous = 0x34;
                Scene_Info.scene_current = 0xC;

                func_multiple_801323F8();
            }
        }
    }
    Scene_Info.scene_previous = 0x34;
    Scene_Info.scene_current = 0x1B;
}
