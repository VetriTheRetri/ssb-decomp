#include "fighter.h"
#include "gmmatch.h"

#define FTCOMMON_DEAD_REBIRTH_WAIT 45

void func_ovl3_8013BC60(u16 sfx_id)
{
    func_800269C0(sfx_id);
    func_ovl2_80113804(sfx_id);
}

void func_ovl3_8013BC8C(Fighter_Struct *this_fp)
{
    s32 i;

    func_ovl2_800E806C(this_fp, 0, 30);

    for (i = 0; i < ARRAY_COUNT(Match_Info->player_block); i++)
    {
        if ((i != this_fp->player_id) && (Match_Info->player_block[i].player_kind == Ft_Kind_Mario))
        {
            GObj *fighter_gobj = Match_Info->player_block[i].fighter_gobj;

            if (fighter_gobj != NULL)
            {
                Fighter_Struct *other_fp = FighterGetStruct(fighter_gobj);

                if ((!(Match_Info->match_type & 2)) || (other_fp->unk_0x14 != -1))
                {
                    func_ovl2_800E806C(other_fp, 1, 15);
                }
                else continue;
            }
        }
    }
}

void func_ovl3_8013BD64(Fighter_Struct *this_fp)
{
    func_ovl2_8010F76C(this_fp);
    func_ovl2_80114968(this_fp);

    Match_Info->player_block[this_fp->player_id].falls++;

    if (Match_Info->unk_minfo_0x1D_b0)
    {
        func_ovl2_801149CC(this_fp, -1);
    }

    if ((this_fp->damage_player_id != -1) && (this_fp->damage_player_id != GMMATCH_PLAYERS_MAX))
    {
        Match_Info->player_block[this_fp->damage_player_id].score++;

        Match_Info->player_block[this_fp->damage_player_id].total_ko_player[this_fp->player_id]++;

        if (Match_Info->unk_minfo_0x1D_b0)
        {
            func_ovl2_801149CC(FighterGetStruct(Match_Info->player_block[this_fp->damage_player_id].fighter_gobj), 1);
        }
    }
    else Match_Info->player_block[this_fp->player_id].total_self_destruct++;
    
    if (Match_Info->match_type & 2)
    {
        this_fp->unk_0x14--;

        Match_Info->player_block[this_fp->player_id].stock_count--;

        func_ovl2_8011388C(this_fp);
    }
    if (Match_Info->match_type & 8)
    {
        this_fp->unk_0x14--;

        Match_Info->player_block[this_fp->player_id].stock_count--;

        func_unkmulti_8018EFFC(this_fp->player_id, this_fp->unk_0x15);
    }
    if (Match_Info->match_type & 4)
    {
        func_ovl2_80114C80();
    }
}

void func_ovl3_8013BF94(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (Match_Info->match_type & 2)
    {
        if (fp->unk_0x14 == -1)
        {
            func_ovl3_8013D8B0(fighter_gobj);

            return;
        }
    }
    else if (Match_Info->match_type & 8)
    {
        if (Match_Info->player_block[fp->player_id].is_rebirth_multi != FALSE)
        {
            func_unkmulti_8018E18C(fighter_gobj);

            return;
        }
        else if (fp->unk_0x14 == -1)
        {
            func_ovl3_8013D8B0(fighter_gobj);

            return;
        }
    }
    func_ovl3_8013CF60(fighter_gobj);
}

void func_ovl3_8013C050(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E823C(fighter_gobj);
    func_ovl2_800D7994(fighter_gobj);
    func_ovl3_8014AF2C(fighter_gobj);

    fp->ground_or_air = air;
    fp->coll_data.ground_line_id = -1;

    if (fp->article_hold != NULL)
    {
        func_ovl3_801728D4(fp->article_hold);
    }
}

void func_ovl3_8013C0B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->unk_ft_0x5B0 = 0;
    fp->x191_flag_b1 = TRUE;
    fp->x18E_flag_b0 = TRUE;

    func_ovl2_800E7B54(fighter_gobj);
}

void func_ovl3_8013C0EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.dead.rebirth_wait--;

    if (fp->status_vars.common.dead.rebirth_wait == 0)
    {
        func_ovl3_8013BF94(fighter_gobj);
    }
}

void func_ovl3_8013C120(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.dead.rebirth_wait = FTCOMMON_DEAD_REBIRTH_WAIT;

    func_ovl2_800D9444(fighter_gobj);

    fp->x18D_flag_b7 = TRUE;
    fp->x191_flag_b3 = TRUE;
    fp->x18E_flag_b3 = TRUE;

    func_ovl2_801008F4(2);
    func_ovl3_8013BC8C(fp);
    func_ovl3_8013BD64(fp);

    if (fp->attributes->dead_sfx[0] != 0x2B7)
    {
        func_ovl3_8013BC60(fp->attributes->dead_sfx[0]);
    }
    if (fp->attributes->dead_sfx[1] != 0x2B7)
    {
        func_ovl3_8013BC60(fp->attributes->dead_sfx[1]);
    }
}