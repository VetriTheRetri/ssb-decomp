#include "fighter.h"
#include "gmmatch.h"
#include "gmground.h"

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
        if ((i != this_fp->port_id) && (Match_Info->player_block[i].player_kind == Ft_Kind_Mario))
        {
            GObj *fighter_gobj = Match_Info->player_block[i].fighter_gobj;

            if (fighter_gobj != NULL)
            {
                Fighter_Struct *other_fp = FighterGetStruct(fighter_gobj);

                if ((!(Match_Info->match_type & 2)) || (other_fp->stock_count != -1))
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

    Match_Info->player_block[this_fp->port_id].falls++;

    if (Match_Info->unk_minfo_0x1D_b0)
    {
        func_ovl2_801149CC(this_fp, -1);
    }

    if ((this_fp->damage_port_id != -1) && (this_fp->damage_port_id != GMMATCH_PLAYERS_MAX))
    {
        Match_Info->player_block[this_fp->damage_port_id].score++;

        Match_Info->player_block[this_fp->damage_port_id].total_ko_player[this_fp->port_id]++;

        if (Match_Info->unk_minfo_0x1D_b0)
        {
            func_ovl2_801149CC(FighterGetStruct(Match_Info->player_block[this_fp->damage_port_id].fighter_gobj), 1);
        }
    }
    else Match_Info->player_block[this_fp->port_id].total_self_destruct++;
    
    if (Match_Info->match_type & 2)
    {
        this_fp->stock_count--;

        Match_Info->player_block[this_fp->port_id].stock_count--;

        func_ovl2_8011388C(this_fp);
    }
    if (Match_Info->match_type & 8)
    {
        this_fp->stock_count--;

        Match_Info->player_block[this_fp->port_id].stock_count--;

        func_unkmulti_8018EFFC(this_fp->port_id, this_fp->unk_0x15);
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
        if (fp->stock_count == -1)
        {
            func_ovl3_8013D8B0(fighter_gobj);

            return;
        }
    }
    else if (Match_Info->match_type & 8)
    {
        if (Match_Info->player_block[fp->port_id].is_rebirth_multi != FALSE)
        {
            func_unkmulti_8018E18C(fighter_gobj);

            return;
        }
        else if (fp->stock_count == -1)
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

    if (fp->item_hold != NULL)
    {
        func_ovl3_801728D4(fp->item_hold);
    }
}

void func_ovl3_8013C0B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->star_invincible_time = 0;
    fp->is_ignore_blastzone_top = TRUE;
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

void func_ovl3_8013C1C4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    u32 sfx_id;

    func_ovl3_8013C050(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadDown, 0.0F, 1.0F, 0U);
    func_ovl3_8013C0B0(fighter_gobj);
    func_ovl3_8013C120(fighter_gobj);

    pos = DObjGetStruct(fighter_gobj)->translate;

    if (Match_Info->game_type != 2)
    {
        if (Ground_Info->cam_bound_right < pos.x)
        {
            pos.x = Ground_Info->cam_bound_right;
        }

        if (pos.x < Ground_Info->cam_bound_left)
        {
            pos.x = Ground_Info->cam_bound_left;
        }
    }
    func_ovl2_801021C0(&pos, fp->port_id, 0);
    func_ovl2_80115BF0(0x51, 0);

    if (((Match_Info->gr_kind >= Gr_Kind_TargetStart) && (Match_Info->gr_kind < Gr_Kind_PlatformStart)) || ((Match_Info->gr_kind >= Gr_Kind_PlatformStart) && (Match_Info->gr_kind < Gr_Kind_CustomStart)))
    {
        sfx_id = 0x9B;
    }
    else sfx_id = 0x9A;

    func_ovl3_8013BC60(sfx_id);
}

void func_ovl3_8013C30C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    u32 sfx_id;

    func_ovl3_8013C050(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadLeftRight, 0.0F, 1.0F, 0U);
    func_ovl3_8013C0B0(fighter_gobj);
    func_ovl3_8013C120(fighter_gobj);

    pos = DObjGetStruct(fighter_gobj)->translate;

    if (Match_Info->game_type != 2)
    {
        if (Ground_Info->cam_bound_top < pos.y)
        {
            pos.y = Ground_Info->cam_bound_top;
        }

        if (pos.y < Ground_Info->cam_bound_bottom)
        {
            pos.y = Ground_Info->cam_bound_bottom;
        }
    }
    func_ovl2_801021C0(&pos, fp->port_id, 1);
    func_ovl2_80115BF0(0x51, 0);

    if (((Match_Info->gr_kind >= Gr_Kind_TargetStart) && (Match_Info->gr_kind < Gr_Kind_PlatformStart)) || ((Match_Info->gr_kind >= Gr_Kind_PlatformStart) && (Match_Info->gr_kind < Gr_Kind_CustomStart)))
    {
        sfx_id = 0x9B;
    }
    else sfx_id = 0x9A;

    func_ovl3_8013BC60(sfx_id);
}

void func_ovl3_8013C454(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    u32 sfx_id;

    func_ovl3_8013C050(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadLeftRight, 0.0F, 1.0F, 0U);
    func_ovl3_8013C0B0(fighter_gobj);
    func_ovl3_8013C120(fighter_gobj);

    pos = DObjGetStruct(fighter_gobj)->translate;

    if (Match_Info->game_type != 2)
    {
        if (Ground_Info->cam_bound_top < pos.y)
        {
            pos.y = Ground_Info->cam_bound_top;
        }

        if (pos.y < Ground_Info->cam_bound_bottom)
        {
            pos.y = Ground_Info->cam_bound_bottom;
        }
    }
    func_ovl2_801021C0(&pos, fp->port_id, 3);
    func_ovl2_80115BF0(0x51, 0);

    if (((Match_Info->gr_kind >= Gr_Kind_TargetStart) && (Match_Info->gr_kind < Gr_Kind_PlatformStart)) || ((Match_Info->gr_kind >= Gr_Kind_PlatformStart) && (Match_Info->gr_kind < Gr_Kind_CustomStart)))
    {
        sfx_id = 0x9B;
    }
    else sfx_id = 0x9A;

    func_ovl3_8013BC60(sfx_id);
}

void func_ovl3_8013C59C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    switch (fp->command_vars.flags.flag1)
    {
    case 1:
        fp->color_anim.a = 128 - ((fp->status_vars.common.dead.rebirth_wait * 128) / FTCOMMON_DEADUP_REBIRTH_WAIT);
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
            fp->phys_info.vel_air.y = ((Ground_Info->cam_bound_top * 0.6F) - DObjGetStruct(fighter_gobj)->translate.y) / 180.0F;
            fp->phys_info.vel_air.z = FTCOMMON_DEADUPFALL_VEL_Z;

            fp->unk_ft_0xA88_b0 = TRUE;

            fp->color_anim.r = Ground_Info->fog_color.r;
            fp->color_anim.g = Ground_Info->fog_color.g;
            fp->color_anim.b = Ground_Info->fog_color.b;
            fp->color_anim.a = 0;

            fp->status_vars.common.dead.rebirth_wait = FTCOMMON_DEADUP_REBIRTH_WAIT;

            fp->command_vars.flags.flag1++;
            break;

        case 1:
            func_ovl2_800D9444(fighter_gobj);
            func_ovl2_80100720(&fp->joint[0]->translate, 5.0F);

            fp->x18D_flag_b7 = TRUE;
            fp->x191_flag_b3 = TRUE;

            func_ovl3_8013BD64(fp);
            func_ovl3_8013BC60(0xCU);

            fp->x18E_flag_b3 = TRUE;
            fp->unk_ft_0xA88_b0 = FALSE;

            fp->status_vars.common.dead.rebirth_wait = FTCOMMON_DEAD_REBIRTH_WAIT;

            fp->command_vars.flags.flag1++;
            break;

        case 2:
            func_ovl3_8013BF94(fighter_gobj);
            break;

        default:
            break;
        }
    }
}

void func_ovl3_8013C740(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8013C050(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadUpStar, 0.0F, 1.0F, 0U);
    func_ovl2_800D9444(fighter_gobj);

    fp->status_vars.common.dead.pos = DObjGetStruct(fighter_gobj)->translate;

    fp->x191_flag_b4567 = 2;

    fp->status_vars.common.dead.rebirth_wait = 1;

    fp->command_vars.flags.flag1 = 0;

    func_ovl3_8013C0B0(fighter_gobj);
    func_ovl2_800E7F7C(fighter_gobj, 1);

    if (fp->attributes->deadup_sfx != 0x2B7)
    {
        func_800269C0(fp->attributes->deadup_sfx);
    }
    func_ovl2_800E827C(fighter_gobj, 1);
    func_ovl2_800E98B0(fighter_gobj);
}

void func_ovl3_8013C80C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 sfx_id;

    switch (fp->command_vars.flags.flag1)
    {
    case 1:
        if (DObjGetStruct(fighter_gobj)->translate.y < Ground_Info->blastzone_bottom)
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
            fp->phys_info.vel_air.y = (Ground_Info->cam_bound_bottom - DObjGetStruct(fighter_gobj)->translate.y) / 180.0F;
            DObjGetStruct(fighter_gobj)->translate.z = (D_ovl2_80131460->unk_0x74->unk_p_80131460_vec.z - 3000.0F);

            if (DObjGetStruct(fighter_gobj)->translate.z < 2000.0F)
            {
                DObjGetStruct(fighter_gobj)->translate.z = 2000.0F;
            }
            DObjGetStruct(fighter_gobj)->translate.x = (f32)D_ovl2_80131460->unk_0x74->unk_p_80131460_vec.x;
            DObjGetStruct(fighter_gobj)->translate.y = (f32)(D_ovl2_80131460->unk_0x74->unk_p_80131460_vec.y + 3000.0F);

            if (Ground_Info->blastzone_top < DObjGetStruct(fighter_gobj)->translate.y)
            {
                DObjGetStruct(fighter_gobj)->translate.y = Ground_Info->blastzone_top;
            }
            fp->status_vars.common.dead.rebirth_wait = FTCOMMON_DEADUP_REBIRTH_WAIT;

            fp->command_vars.flags.flag1++;

            break;

        case 1:
            func_ovl2_800D9444(fighter_gobj);
            func_ovl2_80115BF0(0x51, 0);
            func_ovl2_801008F4(2);
            func_ovl3_8013BC8C(fp);

            fp->x18E_flag_b3 = TRUE;
            fp->x18D_flag_b7 = TRUE;
            fp->x191_flag_b3 = TRUE;

            func_ovl3_8013BD64(fp);

            if (((Match_Info->gr_kind >= Gr_Kind_TargetStart) && (Match_Info->gr_kind < Gr_Kind_PlatformStart)) || ((Match_Info->gr_kind >= Gr_Kind_PlatformStart) && (Match_Info->gr_kind < Gr_Kind_CustomStart)))
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
            func_ovl3_8013BF94(fighter_gobj);

            break;

        default:
            break;
        }
    }
}

void func_ovl3_8013CAAC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8013C050(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Common_DeadUpFall, 0.0F, 1.0F, 0U);
    func_ovl2_800D9444(fighter_gobj);

    fp->status_vars.common.dead.pos = DObjGetStruct(fighter_gobj)->translate;

    fp->x191_flag_b4567 = 2;

    fp->status_vars.common.dead.rebirth_wait = 1;

    fp->command_vars.flags.flag1 = 0;

    func_ovl3_8013C0B0(fighter_gobj);
    func_ovl2_800E7F7C(fighter_gobj, 1);

    if (fp->attributes->deadup_sfx != 0x2B7)
    {
        func_800269C0(fp->attributes->deadup_sfx);
    }
    func_ovl2_800E827C(fighter_gobj, 0x13);
    func_ovl2_800E9198(fighter_gobj, 1);
}

bool32 func_ovl3_8013CB7C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f *pos = &fp->joint[0]->translate;

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
        if (pos->y < Ground_Info->blastzone_bottom)
        {
            pos->y = Ground_Info->blastzone_bottom + 500.0F;

            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;
            fp->phys_info.vel_air.z = 0.0F;
        }
        else if (Ground_Info->blastzone_top < pos->y)
        {
            pos->y = Ground_Info->blastzone_top - 500.0F;

            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;
            fp->phys_info.vel_air.z = 0.0F;
        }
        if (Ground_Info->blastzone_right < pos->x)
        {
            pos->x = Ground_Info->blastzone_right - 500.0F;

            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;
            fp->phys_info.vel_air.z = 0.0F;
        }
        else if (pos->x < Ground_Info->blastzone_left)
        {
            pos->x = Ground_Info->blastzone_left + 500.0F;

            fp->phys_info.vel_air.x = 0.0F;
            fp->phys_info.vel_air.y = 0.0F;
            fp->phys_info.vel_air.z = 0.0F;
        }
        return FALSE;
    }
    else if (!(fp->is_ignore_blastzone_top))
    {
        if ((Match_Info->game_type == 5) && (Match_Info->player_block[fp->port_id].is_rebirth_multi != FALSE))
        {
            if (pos->y < Ground_Info->unk_bound_bottom)
            {
                func_ovl3_8013C1C4(fighter_gobj);

                return TRUE;
            }
            if (Ground_Info->unk_bound_right < pos->x)
            {
                func_ovl3_8013C30C(fighter_gobj);

                return TRUE;
            }
            if (pos->x < Ground_Info->unk_bound_left)
            {
                func_ovl3_8013C454(fighter_gobj);

                return TRUE;
            }
            if (Ground_Info->unk_bound_top < pos->y)
            {
                if (rand_f32() < 0.16666667F)
                {
                    func_ovl3_8013CAAC(fighter_gobj);

                    return TRUE;
                }
                else func_ovl3_8013C740(fighter_gobj);

                return TRUE;
            }
        }
        else if (pos->y < Ground_Info->blastzone_bottom)
        {
            func_ovl3_8013C1C4(fighter_gobj);

            return TRUE;
        }
        else if (Ground_Info->blastzone_right < pos->x)
        {
            func_ovl3_8013C30C(fighter_gobj);

            return TRUE;
        }
        else if (pos->x < Ground_Info->blastzone_left)
        {
            func_ovl3_8013C454(fighter_gobj);

            return TRUE;
        }
        else if (Ground_Info->blastzone_top < pos->y)
        {
            if (rand_f32() < 0.16666667F)
            {
                func_ovl3_8013CAAC(fighter_gobj);
            }
            else func_ovl3_8013C740(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}
