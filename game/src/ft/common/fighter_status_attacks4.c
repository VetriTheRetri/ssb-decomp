#include "fighter.h"
#include "article.h"

void func_ovl3_8014FE40(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f offset;

    switch (fp->ft_kind)
    {
    case Ft_Kind_Pikachu:
    case Ft_Kind_PolyPikachu:
        if ((fp->command_vars.flags.flag1 != 0) || (fp->command_vars.flags.flag2 != 0))
        {
            fp->status_vars.common.attack4.gfx_id += rand_u16_range((FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_ID_MAX - 1)) + 1;

            if (fp->status_vars.common.attack4.gfx_id >= FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_ID_MAX)
            {
                fp->status_vars.common.attack4.gfx_id -= FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_ID_MAX;
            }
            if (fp->command_vars.flags.flag1 != 0)
            {
                fp->command_vars.flags.flag1 = 0;

                offset.x = -FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_X;
                offset.z = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_Z;
                offset.y = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_Y;
            }
            if (fp->command_vars.flags.flag2 != 0)
            {
                fp->command_vars.flags.flag2 = 0;

                offset.x = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_X;
                offset.z = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_Z;
                offset.y = FTCOMMON_ATTACKS4_THUNDERSHOCK_GFX_OFF_Y;

            }
            func_ovl2_800EDF24(fp->joint[11], &offset);
            func_ovl2_800EE018(fp->joint[0], &offset);

            if (func_ovl2_801018A8(fighter_gobj, &offset, fp->status_vars.common.attack4.gfx_id) != NULL)
            {
                fp->is_statupdate_stop_gfx = TRUE;
            }
        }
        // Fallthrough, should break here for efficiency
    case Ft_Kind_Ness:
    case Ft_Kind_PolyNess:
        if ((fp->command_vars.flags.flag1 != 0) && !(fp->is_reflect))
        {
            fp->is_reflect = TRUE;
        }
        if ((fp->command_vars.flags.flag1 == 0) && (fp->is_reflect))
        {
            fp->is_reflect = FALSE;
        }
        break;
    }
    func_ovl2_800D94C4(fighter_gobj);
}

extern intptr_t ftNess_AttackS4_SpecialHit; // 0x00001114
extern void *D_ovl2_80131134;               // Pointer to Ness' file?

void func_ovl3_8014FFE0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 stick_angle;
    s32 status_id;

    if (fp->ft_data->script1->script_info[0xB2].anim_id != 0)
    {
        stick_angle = func_ovl2_800E8000(fp);

        status_id = (stick_angle > FTCOMMON_ATTACKS4_5ANGLE_HI_MIN)  ? ftStatus_Common_AttackS4Hi  :
                    (stick_angle > FTCOMMON_ATTACKS4_5ANGLE_HIS_MIN) ? ftStatus_Common_AttackS4HiS :
                    (stick_angle < FTCOMMON_ATTACKS4_5ANGLE_LW_MIN)  ? ftStatus_Common_AttackS4Lw  :
                    (stick_angle < FTCOMMON_ATTACKS4_5ANGLE_LWS_MIN) ? ftStatus_Common_AttackS4LwS :
                                                                       ftStatus_Common_AttackS4;
    }
    else if (fp->ft_data->script1->script_info[0xB1].anim_id != 0)
    {
        stick_angle = func_ovl2_800E8000(fp);

        status_id = (stick_angle > FTCOMMON_ATTACKS4_3ANGLE_HI_MIN)  ? ftStatus_Common_AttackS4Hi  :
                    (stick_angle < FTCOMMON_ATTACKS4_3ANGLE_LW_MIN)  ? ftStatus_Common_AttackS4Lw  :
                                                                       ftStatus_Common_AttackS4;
    }
    else status_id = ftStatus_Common_AttackS4;

    switch (fp->ft_kind)
    {
    case Ft_Kind_Pikachu:
    case Ft_Kind_PolyPikachu:
        fp->command_vars.flags.flag2 = 0;
        fp->command_vars.flags.flag1 = 0;
        break;

    case Ft_Kind_Ness:
    case Ft_Kind_PolyNess:
        fp->command_vars.flags.flag1 = 0;
        break;
    }
    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    switch (fp->ft_kind)
    {
    case Ft_Kind_Pikachu:
    case Ft_Kind_PolyPikachu:
        fp->status_vars.common.attack4.gfx_id = 0;

        fp->cb_hitlag_start = func_ovl2_800E9C8C;
        fp->cb_hitlag_end = func_ovl2_800E9CC4;
        break;

    case Ft_Kind_Ness:
    case Ft_Kind_PolyNess:
        fp->special_hit = (SpecialHit*) ((uintptr_t)D_ovl2_80131134 + (intptr_t)&ftNess_AttackS4_SpecialHit);
        break;
    }
}

bool32 func_ovl3_801501E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (((fp->input.stick_range.x * fp->lr) >= FTCOMMON_ATTACKS4_STICK_RANGE_MIN) && (fp->input.button_tap & fp->input.button_mask_a))
    {
        GObj *article_gobj = fp->item_hold;

        if (article_gobj != NULL)
        {
            Article_Struct *ap = ArticleGetStruct(article_gobj);

            if ((fp->input.button_hold & fp->input.button_mask_z) || ((ap->type == At_Type_Throw) || (ap->type == At_Type_Shoot) && (func_ovl3_80172890(article_gobj) != FALSE)))
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowF4);

                return TRUE;
            }
            switch (ap->type)
            {
            case At_Type_Swing:
                func_ovl3_80146E94(fighter_gobj, 2);
                return TRUE;

            case At_Type_Shoot:
                func_ovl3_80147844(fighter_gobj);
                return TRUE;
            }
        }
        if (attributes->is_have_attacks4)
        {
            func_ovl3_8014FFE0(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl3_8015030C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (((fp->input.stick_range.x * fp->status_vars.common.attack4.lr) >= FTCOMMON_ATTACKS4_STICK_RANGE_MIN) && (fp->input.button_tap & fp->input.button_mask_a))
    {
        GObj *article_gobj = fp->item_hold;

        if (article_gobj != NULL)
        {
            Article_Struct *ap = ArticleGetStruct(article_gobj);

            if ((fp->input.button_hold & fp->input.button_mask_z) || ((ap->type == At_Type_Throw) || (ap->type == At_Type_Shoot) && (func_ovl3_80172890(article_gobj) != FALSE)))
            {
                func_ovl3_80146690(fighter_gobj, ((fp->input.stick_range.x * fp->lr) >= 0) ? ftStatus_Common_LightThrowF4 : ftStatus_Common_LightThrowB4);

                return TRUE;
            }
            switch (ap->type)
            {
            case At_Type_Swing:
                func_ovl2_800E8044(fp);
                func_ovl3_80146E94(fighter_gobj, 2);
                return TRUE;

            case At_Type_Shoot:
                func_ovl2_800E8044(fp);
                func_ovl3_80147844(fighter_gobj);
                return TRUE;
            }
        }
        if (attributes->is_have_attacks4)
        {
            func_ovl2_800E8044(fp);
            func_ovl3_8014FFE0(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl3_80150470(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if ((ABS(fp->input.stick_range.x) >= FTCOMMON_ATTACKS4_STICK_RANGE_MIN) && (fp->tap_stick_x < FTCOMMON_ATTACKS4_BUFFER_FRAMES_MAX) && (fp->input.button_tap & fp->input.button_mask_a))
    {
        GObj *article_gobj = fp->item_hold;

        if (article_gobj != NULL)
        {
            Article_Struct *ap = ArticleGetStruct(article_gobj);

            if ((fp->input.button_hold & fp->input.button_mask_z) || ((ap->type == At_Type_Throw) || (ap->type == At_Type_Shoot) && (func_ovl3_80172890(article_gobj) != FALSE)))
            {
                func_ovl3_80146690(fighter_gobj, ((fp->input.stick_range.x * fp->lr) >= 0) ? ftStatus_Common_LightThrowF4 : ftStatus_Common_LightThrowB4);

                return TRUE;
            }
            switch (ap->type)
            {
            case At_Type_Swing:
                func_ovl2_800E8044(fp);
                func_ovl3_80146E94(fighter_gobj, 2);
                return TRUE;

            case At_Type_Shoot:
                func_ovl2_800E8044(fp);
                func_ovl3_80147844(fighter_gobj);
                return TRUE;
            }
        }
        if (attributes->is_have_attacks4)
        {
            func_ovl2_800E8044(fp);
            func_ovl3_8014FFE0(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}