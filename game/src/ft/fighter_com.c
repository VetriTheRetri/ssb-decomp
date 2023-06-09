#include "fighter.h"
#include "item.h"
#include "article.h"
#include "ftfox.h"
#include "gmmatch.h"

Item_Struct* func_ovl3_80131B00(Fighter_Struct *fp)
{
    GObj *item_gobj = gOMObjCommonLinks[gOMObjLinkIndexItem];

    if (item_gobj != NULL)
    {
        do
        {
            Item_Struct *ip = itGetStruct(item_gobj);

            if (ip->owner_gobj == fp->fighter_gobj)
            {
                return ip;
            }
            item_gobj = item_gobj->group_gobj_next;
        } 
        while (item_gobj != NULL);
    }
    return NULL;
}

Vec3f* func_ovl3_80131B44(Fighter_Struct *fp, s32 it_kind)
{
    GObj *item_gobj = gOMObjCommonLinks[gOMObjLinkIndexItem];

    if (item_gobj != NULL)
    {
        do
        {
            Item_Struct *ip = itGetStruct(item_gobj);

            if ((ip->owner_gobj == fp->fighter_gobj) && (ip->it_kind == it_kind))
            {
                return &DObjGetStruct(ip->item_gobj)->translate;
            }
            item_gobj = item_gobj->group_gobj_next;
        } 
        while (item_gobj != NULL);
    }
    return NULL;
}

void func_ovl3_80131BA0(Fighter_Struct *fp)
{
    Vec3f *pos = func_ovl3_80131B44(fp, It_Kind_PKThunder_Trail);
    Fighter_Com *ft_com = &fp->fighter_com;

    if (pos != NULL)
    {
        f32 dist_x = ft_com->target_pos.x - pos->x;
        f32 dist_y = ft_com->target_pos.y - pos->y;

        f32 sqrt = 1.0F / sqrtf(SQUARE(dist_x) + SQUARE(dist_y));

        fp->input.cp.stick_range.x = (GCONTROLLER_RANGE_MAX_F * dist_x * sqrt);
        fp->input.cp.stick_range.y = (GCONTROLLER_RANGE_MAX_F * dist_y * sqrt);
    }
    else
    {
        fp->input.cp.stick_range.x = 0;
        fp->input.cp.stick_range.y = 0;
    }
}

void func_ovl3_80131C68(Fighter_Struct *this_fp)
{
    Fighter_Com *ft_com = &this_fp->fighter_com;
    u8 *p_command;
    u8 command;
    s8 var_t1;
    s16 stick_range_y;
    s16 stick_range_x;
    f32 dist_x;
    f32 dist_y;

    if (ft_com->input_wait != 0)
    {
        ft_com->input_wait--;

        if (ft_com->input_wait == 0)
        {
            p_command = ft_com->p_command;

            while (ft_com->input_wait == 0)
            {
                command = *p_command++;

                if (command < 0xF0)
                {
                    ft_com->input_wait = command & 0xF;

                    switch (command & 0xF0)
                    {
                    case 0x0:
                        this_fp->input.cp.button_inputs |= 0x8000;
                        break;
                    case 0x10:
                        this_fp->input.cp.button_inputs &= 0xFFFF7FFF;
                        break;
                    case 0x20:
                        this_fp->input.cp.button_inputs |= 0x4000;
                        break;
                    case 0x30:
                        this_fp->input.cp.button_inputs &= 0xBFFF;
                        break;
                    case 0x40:
                        this_fp->input.cp.button_inputs |= 0x2000;
                        break;
                    case 0x50:
                        this_fp->input.cp.button_inputs &= 0xDFFF;
                        break;
                    case 0x60:
                        this_fp->input.cp.button_inputs |= 0x20;
                        break;
                    case 0x70:
                        this_fp->input.cp.button_inputs &= 0xFFDF;
                        break;
                    case 0x80:
                        this_fp->input.cp.button_inputs |= 0x1000;
                        break;
                    case 0x90:
                        this_fp->input.cp.button_inputs &= 0xEFFF;
                        break;
                    case 0xA0:
                        switch (*p_command)
                        {
                        default:
                            this_fp->input.cp.stick_range.x = *p_command++;
                            break;

                        case 0x7FU:
                            this_fp->input.cp.stick_range.x = (this_fp->joint[0]->translate.x < ft_com->target_pos.x) ? (GCONTROLLER_RANGE_MAX_I) : -(GCONTROLLER_RANGE_MAX_I);
                            p_command++;
                            break;

                        case 0x80U:
                            this_fp->input.cp.stick_range.x = (this_fp->joint[0]->translate.x < ft_com->target_pos.x) ? (GCONTROLLER_RANGE_MAX_I / 2) : -(GCONTROLLER_RANGE_MAX_I / 2);
                            p_command++;
                            break;
                        }
                        break;

                    case 0xB0:
                        switch (*p_command)
                        {
                        default:

                            this_fp->input.cp.stick_range.y = *p_command++;
                            break;

                        case 0x7FU:
                            this_fp->input.cp.stick_range.y = (this_fp->joint[0]->translate.y < ft_com->target_pos.y) ? (GCONTROLLER_RANGE_MAX_I) : -(GCONTROLLER_RANGE_MAX_I);
                            p_command++;
                            break;

                        case 0x80U:
                            this_fp->input.cp.stick_range.y = (this_fp->joint[0]->translate.y < ft_com->target_pos.y) ? (GCONTROLLER_RANGE_MAX_I / 2) : -(GCONTROLLER_RANGE_MAX_I / 2);
                            p_command++;
                            break;
                        }
                        break;

                    case 0xC0:
                        dist_x = ft_com->target_pos.x - this_fp->joint[0]->translate.x;
                        dist_y = ft_com->target_pos.y - this_fp->joint[0]->translate.y;

                        if ((this_fp->ground_or_air == ground) && (this_fp->cp_level < 5))
                        {
                            stick_range_x = (ABSF(dist_x) > 100.0F) ? (GCONTROLLER_RANGE_MAX_I / 2) : 0;
                        }
                        else if (this_fp->ground_or_air == ground)
                        {
                            if ((ft_com->unk_ftcom_0x8C * 1.5F) < ABSF(dist_x))
                            {
                                stick_range_x = (GCONTROLLER_RANGE_MAX_I);
                            }
                            else
                            {
                                if (ft_com->unk_ftcom_0x8C < ABSF(dist_x))
                                {
                                    stick_range_x = ((2.0F * ((ABSF(dist_x) - ft_com->unk_ftcom_0x8C) / ft_com->unk_ftcom_0x8C) * (GCONTROLLER_RANGE_MAX_F / 2)) + (GCONTROLLER_RANGE_MAX_F / 2));
                                }
                                else
                                {
                                    stick_range_x = (ABSF(dist_x) > 100.0F) ? (GCONTROLLER_RANGE_MAX_I / 2) : 0;
                                }
                            }
                        }
                        else
                        {
                            stick_range_x = ((ABSF(dist_x) > 100.0F) || ((this_fp->lr * dist_x) < 0.0F)) ? (GCONTROLLER_RANGE_MAX_I) : (GCONTROLLER_RANGE_MAX_I / 4);
                        }
                        stick_range_y = GCONTROLLER_RANGE_MAX_I;

                        if (this_fp->ground_or_air == ground)
                        {
                            if (this_fp->status_info.status_id != ftStatus_Common_KneeBend)
                            {
                                if (ft_com->target_line_id == this_fp->coll_data.ground_line_id)
                                {
                                    stick_range_y = dist_y = 0.0F;
                                }
                                if ((ft_com->ftcom_flags_0x4A_b1) && 
                                ((ft_com->target_fp->status_info.status_id == ftStatus_Common_CliffCatch) || 
                                (ft_com->target_fp->status_info.status_id == ftStatus_Common_CliffWait)))
                                {
                                    stick_range_y = dist_y = 0.0F;
                                }
                            }
                        }
                        else
                        {
                            if (((this_fp->ft_kind != Ft_Kind_Fox) ||
                            (((this_fp->status_info.status_id != ftStatus_Fox_SpecialHiStart)) &&
                            (this_fp->status_info.status_id != ftStatus_Fox_SpecialAirHiStart) &&
                            (this_fp->status_info.status_id != ftStatus_Fox_SpecialHiHold) &&
                            (this_fp->status_info.status_id != ftStatus_Fox_SpecialAirHiHold))) &&
                            (dist_y < 0))
                            {
                                stick_range_y = dist_y = 0.0F;
                            }
                            switch (ft_com->behavior_set)
                            {
                            case 7:
                                if (this_fp->joint[0]->translate.y < 0)
                                {
                                    stick_range_y = dist_y = 0.0F;
                                }
                                break;
                            case 8:
                            case 9:
                                if (this_fp->joint[0]->translate.y < -300.0F)
                                {
                                    stick_range_y = dist_y = 0.0F;
                                }
                                break;
                            }
                        }
                        if ((dist_x != 0.0F) && (dist_y != 0.0F))
                        {
                            if (ABSF(dist_y) < ABSF(dist_x))
                            {
                                this_fp->input.cp.stick_range.x = (dist_x > 0.0F) ? stick_range_x : -stick_range_x;

                                this_fp->input.cp.stick_range.y = (ABSF((dist_y / dist_x)) * ((dist_y > 0.0F) ? stick_range_y : -stick_range_y));
                            }
                            else
                            {
                                this_fp->input.cp.stick_range.x = (ABSF((dist_x / dist_y)) * ((dist_x > 0.0F) ? stick_range_x : -stick_range_x));

                                this_fp->input.cp.stick_range.y = (dist_y > 0.0F) ? stick_range_y : -stick_range_y;
                            }
                        }
                        else if (dist_x != 0.0F)
                        {
                            this_fp->input.cp.stick_range.x = (dist_x > 0.0F) ? stick_range_x : -stick_range_x;

                            this_fp->input.cp.stick_range.y = (ABSF((dist_y / dist_x)) * ((dist_y > 0.0F) ? stick_range_y : -stick_range_y));
                        }
                        else if (dist_y != 0.0F)
                        {
                            this_fp->input.cp.stick_range.x = (ABSF((dist_x / dist_y)) * ((dist_x > 0.0F) ? stick_range_x : -stick_range_x));

                            this_fp->input.cp.stick_range.y = (dist_y > 0.0F) ? stick_range_y : -stick_range_y;
                        }
                        else
                        {
                            this_fp->input.cp.stick_range.x = this_fp->input.cp.stick_range.y = 0;
                        }
                        break;
                    case 0xD0:
                        this_fp->input.cp.stick_range.x = var_t1;
                        break;
                    case 0xE0:
                        this_fp->input.cp.stick_range.y = var_t1;
                        break;
                    }
                }
                else switch (command)
                {
                case 0xF0:
                    ft_com->input_wait = *p_command++;
                    break;
                case 0xF1:
                    var_t1 = 1;
                    break;
                case 0xF2:
                    ft_com->input_wait = var_t1;
                    break;
                case 0xF3:
                    func_ovl3_80131BA0(this_fp);
                    break;
                case 0xFF:
                    ft_com->input_wait = 0;
                    ft_com->p_command = NULL;
                    return;
                }
            }
            ft_com->p_command = p_command;
        }
    }
}

extern u8 *Fighter_Com_Script[]; // CPU player commands

void func_ovl3_80132564(Fighter_Struct *fp, s32 index)
{
    Fighter_Com *ft_com = &fp->fighter_com;

    if (fp->ground_or_air == ground)
    {
        ft_com->input_wait = ((2 * (rand_f32() * (GMCOMPLAYER_LEVEL_MAX - fp->cp_level))) + ((GMCOMPLAYER_LEVEL_MAX - fp->cp_level) * 2) + 1.0F);
    }
    else
    {
        ft_com->input_wait = ((rand_f32() * (GMCOMPLAYER_LEVEL_MAX - fp->cp_level)) + ((GMCOMPLAYER_LEVEL_MAX - fp->cp_level) / 2) + 1.0F);
    }
    ft_com->p_command = Fighter_Com_Script[index];
}

void func_ovl3_80132758(Fighter_Struct *fp, s32 index)
{
    Fighter_Com *ft_com = &fp->fighter_com;

    ft_com->input_wait = 1;
    ft_com->p_command = Fighter_Com_Script[index];
}

void func_ovl3_80132778(Fighter_Struct *fp, s32 index)
{
    Fighter_Com *ft_com = &fp->fighter_com;

    if (fp->ground_or_air == ground)
    {
        ft_com->input_wait = ((4 * (rand_f32() * (GMCOMPLAYER_LEVEL_MAX - fp->cp_level))) + ((GMCOMPLAYER_LEVEL_MAX - fp->cp_level) * 4) + 1.0F);
    }
    else
    {
        ft_com->input_wait = ((rand_f32() * (GMCOMPLAYER_LEVEL_MAX - fp->cp_level)) + (GMCOMPLAYER_LEVEL_MAX - fp->cp_level) + 1.0F);
    }
    ft_com->p_command = Fighter_Com_Script[index];
}

static gmUnkInfo_80131308 D_ovl2_80131308; // Extern

bool32 func_ovl3_8013295C(Fighter_Struct *this_fp)
{
    Fighter_Com *ft_com = &this_fp->fighter_com;
    Fighter_Struct *other_fp;
    f32 this_pos_x = this_fp->joint[0]->translate.x;
    f32 this_pos_y = this_fp->joint[0]->translate.y;
    GObj *other_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];
    f32 distance = (f32)FLOAT_MAX;
    f32 square_xy;
    f32 other_pos_x;
    f32 other_pos_y;

    while (other_gobj != NULL)
    {

        if (other_gobj != this_fp->fighter_gobj)
        {
            other_fp = ftGetStruct(other_gobj);

            if (this_fp->team != other_fp->team)
            {
                other_pos_x = other_fp->joint[0]->translate.x;
                other_pos_y = other_fp->joint[0]->translate.y;

                if ((other_fp->status_info.status_id >= ftStatus_Common_Wait) &&
                (((func_ovl2_800F8FFC(&other_fp->joint[0]->translate) != FALSE) &&
                (other_pos_x <= D_ovl2_80131308.unk_80131308_0x28) &&
                (D_ovl2_80131308.unk_80131308_0x2C <= other_pos_x) &&
                (D_ovl2_80131308.unk_80131308_0x24 <= other_pos_y) &&
                (other_pos_y < Ground_Info->cam_bound_top)) ||
                ((this_fp->ground_or_air == ground) &&
                ((other_fp->status_info.status_id == ftStatus_Common_CliffCatch) ||
                (other_fp->status_info.status_id == ftStatus_Common_CliffWait)))) &&
                ((this_fp->ft_kind != Ft_Kind_MetalMario) ||
                (other_fp->ground_or_air == ground)))
                {
                    square_xy = SQUARE(this_pos_x - other_pos_x) + SQUARE(this_pos_y - other_pos_y);

                    if (square_xy < distance)
                    {
                        ft_com->target_pos.x = other_pos_x;
                        ft_com->target_pos.y = other_pos_y;
                        ft_com->target_fp = other_fp;

                        distance = square_xy;
                    }
                }
            }
        }
        other_gobj = other_gobj->group_gobj_next;
    }

    if (distance == (f32)FLOAT_MAX)
    {
        ft_com->target_line_id = -1;
        ft_com->target_dist = (f32)FLOAT_MAX;
        ft_com->ftcom_flags_0x4A_b1 = FALSE;

        return FALSE;
    }
    ft_com->ftcom_flags_0x4A_b1 = TRUE;
    ft_com->target_dist = sqrtf(distance);

    if (ft_com->target_fp->ground_or_air == ground)
    {
        ft_com->target_line_id = ft_com->target_fp->coll_data.ground_line_id;
    }
    else ft_com->target_line_id = -1;

    return TRUE;
}

bool32 func_ovl3_80132BC8(Fighter_Struct *this_fp)
{
    GObj *other_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

    while (other_gobj != NULL)
    {
        if (other_gobj != this_fp->fighter_gobj)
        {
            Fighter_Struct *other_fp = ftGetStruct(other_gobj);

            if (this_fp->team != other_fp->team)
            {
                DObj *other_joint = other_fp->joint[0];
                DObj *this_joint = this_fp->joint[0];
                f32 other_x = (other_joint->translate.x + other_fp->phys_info.vel_air.x * 3.0F);
                f32 other_y = (other_joint->translate.y + other_fp->phys_info.vel_air.x * 3.0F);
                f32 sqrt_xy = sqrtf(SQUARE(this_joint->translate.y - other_y) + SQUARE(this_joint->translate.x - other_x));

                if ((other_fp->star_hitstatus == gmHitCollision_HitStatus_Invincible) && (sqrt_xy < 1500.0F))
                {
                    return TRUE;
                }
                else if ((other_fp->item_hold != NULL) && (atGetStruct(other_fp->item_hold)->at_kind == At_Kind_M_Ball) && (sqrt_xy < 2500.0F))
                {
                    return TRUE;
                }
            }
        }
        other_gobj = other_gobj->group_gobj_next;
    }
    return FALSE;
}

Fighter_Struct* func_ovl3_80132D18(Fighter_Struct *this_fp)
{
    Fighter_Com *ft_com = &this_fp->fighter_com;
    GObj *other_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];
    s32 target_damage = 9999;
    Fighter_Struct *target_fp = NULL;

    while (other_gobj != NULL)
    {
        if (other_gobj != this_fp->fighter_gobj)
        {
            Fighter_Struct *other_fp = ftGetStruct(other_gobj);

            if (this_fp->team != other_fp->team)
            {
                if (other_fp->status_info.status_id >= ftStatus_Common_Wait)
                {
                    if ((ft_com->target_gobj != NULL) && (other_fp->fighter_gobj == ft_com->target_gobj))
                    {
                        if (other_fp->percent_damage == ft_com->target_damage_percent)
                        {
                            if ((u32)ft_com->target_find_wait != 0)
                            {
                                ft_com->target_find_wait--;
                            }
                            if ((u32)ft_com->target_find_wait == 0)
                            {
                                return other_fp;
                            }
                            else return NULL;
                        }
                        ft_com->target_gobj = NULL;
                    }
                    if (other_fp->percent_damage < target_damage)
                    {
                        target_damage = other_fp->percent_damage;
                        target_fp = other_fp;
                    }
                }
            }
        }
        other_gobj = other_gobj->group_gobj_next;
    }
    if (target_fp != NULL)
    {
        ft_com->target_damage_percent = target_damage;
        ft_com->target_gobj = target_fp->fighter_gobj;
        ft_com->target_find_wait = (rand_f32() * 300.0F) + 600.0F;
    }
    return NULL;
}

void func_ovl3_80132EC0(void) // Unused
{
    return;
}
