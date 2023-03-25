#include "fighter.h"
#include "item.h"
#include "ftfox.h"

Item_Struct* func_ovl3_80131B00(Fighter_Struct *fp)
{
    GObj *item_gobj = gOMObjCommonLinks[GObjLinkIndex_Item];

    if (item_gobj != NULL)
    {
        do
        {
            Item_Struct *ip = ItemGetStruct(item_gobj);

            if (ip->owner_gobj == fp->this_fighter)
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
    GObj *item_gobj = gOMObjCommonLinks[GObjLinkIndex_Item];

    if (item_gobj != NULL)
    {
        do
        {
            Item_Struct *ip = ItemGetStruct(item_gobj);

            if ((ip->owner_gobj == fp->this_fighter) && (ip->it_kind == it_kind))
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

        fp->input.stick_com.x = (GMCONTROLLER_RANGE_MAX_F * dist_x * sqrt);
        fp->input.stick_com.y = (GMCONTROLLER_RANGE_MAX_F * dist_y * sqrt);
    }
    else
    {
        fp->input.stick_com.x = 0;
        fp->input.stick_com.y = 0;
    }
}

void func_ovl3_80131C68(Fighter_Struct *this_fp)
{
    Fighter_Com *ft_com = &this_fp->fighter_com;
    u8 *p_input = ft_com->p_input;
    u8 input_timer;
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
            p_input = ft_com->p_input;

            while (ft_com->input_wait == 0)
            {
                input_timer = *p_input++;

                if (input_timer < 0xF0)
                {
                    ft_com->input_wait = input_timer & 0xF;

                    switch (input_timer & 0xF0)
                    {
                    case 0x0:
                        this_fp->input.button_mask_com |= 0x8000;
                        break;
                    case 0x10:
                        this_fp->input.button_mask_com &= 0xFFFF7FFF;
                        break;
                    case 0x20:
                        this_fp->input.button_mask_com |= 0x4000;
                        break;
                    case 0x30:
                        this_fp->input.button_mask_com &= 0xBFFF;
                        break;
                    case 0x40:
                        this_fp->input.button_mask_com |= 0x2000;
                        break;
                    case 0x50:
                        this_fp->input.button_mask_com &= 0xDFFF;
                        break;
                    case 0x60:
                        this_fp->input.button_mask_com |= 0x20;
                        break;
                    case 0x70:
                        this_fp->input.button_mask_com &= 0xFFDF;
                        break;
                    case 0x80:
                        this_fp->input.button_mask_com |= 0x1000;
                        break;
                    case 0x90:
                        this_fp->input.button_mask_com &= 0xEFFF;
                        break;
                    case 0xA0:
                        switch (*p_input)
                        {
                        default:
                            this_fp->input.stick_com.x = *p_input++;
                            break;

                        case 0x7FU:
                            this_fp->input.stick_com.x = (this_fp->joint[0]->translate.x < ft_com->target_pos.x) ? (GMCONTROLLER_RANGE_MAX_I) : -(GMCONTROLLER_RANGE_MAX_I);
                            p_input++;
                            break;

                        case 0x80U:
                            this_fp->input.stick_com.x = (this_fp->joint[0]->translate.x < ft_com->target_pos.x) ? (GMCONTROLLER_RANGE_MAX_I / 2) : -(GMCONTROLLER_RANGE_MAX_I / 2);
                            p_input++;
                            break;
                        }
                        break;

                    case 0xB0:
                        switch (*p_input)
                        {
                        default:

                            this_fp->input.stick_com.y = *p_input++;
                            break;

                        case 0x7FU:
                            this_fp->input.stick_com.y = (this_fp->joint[0]->translate.y < ft_com->target_pos.y) ? (GMCONTROLLER_RANGE_MAX_I) : -(GMCONTROLLER_RANGE_MAX_I);
                            p_input++;
                            break;

                        case 0x80U:
                            this_fp->input.stick_com.y = (this_fp->joint[0]->translate.y < ft_com->target_pos.y) ? (GMCONTROLLER_RANGE_MAX_I / 2) : -(GMCONTROLLER_RANGE_MAX_I / 2);
                            p_input++;
                            break;
                        }
                        break;

                    case 0xC0:
                        dist_x = ft_com->target_pos.x - this_fp->joint[0]->translate.x;
                        dist_y = ft_com->target_pos.y - this_fp->joint[0]->translate.y;

                        if ((this_fp->ground_or_air == ground) && (this_fp->cp_level < 5))
                        {
                            stick_range_x = (ABSF(dist_x) > 100.0F) ? (GMCONTROLLER_RANGE_MAX_I / 2) : 0;
                        }
                        else if (this_fp->ground_or_air == ground)
                        {
                            if ((ft_com->unk_ftcom_0x8C * 1.5F) < ABSF(dist_x))
                            {
                                stick_range_x = (GMCONTROLLER_RANGE_MAX_I);
                            }
                            else
                            {
                                if (ft_com->unk_ftcom_0x8C < ABSF(dist_x))
                                {
                                    stick_range_x = ((2.0F * ((ABSF(dist_x) - ft_com->unk_ftcom_0x8C) / ft_com->unk_ftcom_0x8C) * (GMCONTROLLER_RANGE_MAX_F / 2)) + (GMCONTROLLER_RANGE_MAX_F / 2));
                                }
                                else
                                {
                                    stick_range_x = (ABSF(dist_x) > 100.0F) ? (GMCONTROLLER_RANGE_MAX_I / 2) : 0;
                                }
                            }
                        }
                        else
                        {
                            stick_range_x = ((ABSF(dist_x) > 100.0F) || ((this_fp->lr * dist_x) < 0.0F)) ? (GMCONTROLLER_RANGE_MAX_I) : (GMCONTROLLER_RANGE_MAX_I / 4);
                        }
                        stick_range_y = GMCONTROLLER_RANGE_MAX_I;

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
                                this_fp->input.stick_com.x = (dist_x > 0.0F) ? stick_range_x : -stick_range_x;

                                this_fp->input.stick_com.y = (ABSF((dist_y / dist_x)) * ((dist_y > 0.0F) ? stick_range_y : -stick_range_y));
                            }
                            else
                            {
                                this_fp->input.stick_com.x = (ABSF((dist_x / dist_y)) * ((dist_x > 0.0F) ? stick_range_x : -stick_range_x));

                                this_fp->input.stick_com.y = (dist_y > 0.0F) ? stick_range_y : -stick_range_y;
                            }
                        }
                        else if (dist_x != 0.0F)
                        {
                            this_fp->input.stick_com.x = (dist_x > 0.0F) ? stick_range_x : -stick_range_x;

                            this_fp->input.stick_com.y = (ABSF((dist_y / dist_x)) * ((dist_y > 0.0F) ? stick_range_y : -stick_range_y));
                        }
                        else if (dist_y != 0.0F)
                        {
                            this_fp->input.stick_com.x = (ABSF((dist_x / dist_y)) * ((dist_x > 0.0F) ? stick_range_x : -stick_range_x));

                            this_fp->input.stick_com.y = (dist_y > 0.0F) ? stick_range_y : -stick_range_y;
                        }
                        else
                        {
                            this_fp->input.stick_com.x = this_fp->input.stick_com.y = 0;
                        }
                        break;
                    case 0xD0:
                        this_fp->input.stick_com.x = var_t1;
                        break;
                    case 0xE0:
                        this_fp->input.stick_com.y = var_t1;
                        break;
                    }
                }
                else switch (input_timer)
                {
                case 0xF0:
                    ft_com->input_wait = *p_input++;
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
                    ft_com->p_input = NULL;
                    return;
                }
            }
            ft_com->p_input = p_input;
        }
    }
}