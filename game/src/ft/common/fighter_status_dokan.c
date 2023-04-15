#include "fighter.h"

void func_ovl3_80141FF0(Fighter_Struct *fp)
{
    if (fp->status_vars.common.dokan.turn_stop_wait != 0)
    {
        fp->status_vars.common.dokan.turn_stop_wait--;

        fp->joint[0]->rotate.y += (-FTCOMMON_DOKAN_TURN_STEP * fp->lr);

        func_ovl2_800EB528(fp->joint[0]);
    }
}

void func_ovl3_8014204C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80141FF0(fp);
    func_ovl2_800D9480(fighter_gobj, func_ovl3_801424BC);
}

void func_ovl3_80142080(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 unused[2];
    f32 pos_x;
    Vec3f *translate = &DObjGetStruct(fighter_gobj)->translate;
    s32 ground_line_id;

    func_ovl2_800FC814((fp->status_vars.common.dokan.ground_line_id == 0xC) ? 0xA : 0xB, &ground_line_id);
    func_ovl2_800FC894(ground_line_id, &pos_x);

    if (pos_x < translate->x)
    {
        translate->x -= FTCOMMON_DOKAN_POS_ADJUST;

        if (translate->x <= pos_x)
        {
            translate->x = pos_x;
        }
    }
    else if (translate->x < pos_x)
    {
        translate->x += FTCOMMON_DOKAN_POS_ADJUST;

        if (translate->x >= pos_x)
        {
            translate->x = pos_x;
        }
    }
}

void func_ovl3_80142164(GObj *fighter_gobj, s32 ground_line_id)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 new_line_id;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Common_DokanStart, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    fp->buffer_stick_y = U8_MAX - 1;

    func_ovl2_800D9444(fighter_gobj);

    fp->x18F_flag_b4 = TRUE;

    fp->status_vars.common.dokan.ground_line_id = ground_line_id;

    func_ovl2_800FC814((fp->status_vars.common.dokan.ground_line_id == 0xC) ? 0xA : 0xB, &new_line_id);
    func_ovl2_800FC894(new_line_id, &fp->status_vars.common.dokan.pos_current);

    func_800269C0(0xD6U);
    func_ovl2_800E7F7C(fighter_gobj, 1);

    if
    (
        (fp->ft_kind == Ft_Kind_Mario) || (fp->ft_kind == Ft_Kind_MetalMario) || (fp->ft_kind == Ft_Kind_PolyMario) ||
        (fp->ft_kind == Ft_Kind_Luigi) || (fp->ft_kind == Ft_Kind_PolyLuigi)
    )
    {
        fp->status_vars.common.dokan.turn_stop_wait = 0;
    }
    else fp->status_vars.common.dokan.turn_stop_wait = FTCOMMON_DOKAN_TURN_STOP_WAIT_DEFAULT;

    func_ovl3_80141FF0(fp);
    func_ovl2_8010972C();
}

bool32 func_ovl3_80142258(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    s32 ground_line_id;
    f32 dist_x;

    if ((fp->input.stick_range.y <= FTCOMMON_DOKAN_STICK_RANGE_MIN) && (fp->buffer_stick_y < FTCOMMON_DOKAN_BUFFER_FRAMES_MAX))
    {
        if ((fp->coll_data.clip_flag & 0xFFFF00FF) == 0xC)
        {
            func_ovl2_800FC814(0xA, &ground_line_id);
            func_ovl2_800FC894(ground_line_id, &pos);

            if (pos.x < DObjGetStruct(fighter_gobj)->translate.x)
            {
                dist_x = -(pos.x - DObjGetStruct(fighter_gobj)->translate.x);
            }
            else dist_x = pos.x - DObjGetStruct(fighter_gobj)->translate.x;

            if (dist_x <= FTCOMMON_DOKAN_DETECT_WIDTH)
            {
                func_ovl3_80142164(fighter_gobj, 0xC);

                return TRUE;
            }
        }
        else if ((fp->coll_data.clip_flag & 0xFFFF00FF) == 0xD)
        {
            func_ovl2_800FC814(0xB, &ground_line_id);
            func_ovl2_800FC894(ground_line_id, &pos);

            if (pos.x < DObjGetStruct(fighter_gobj)->translate.x)
            {
                dist_x = -(pos.x - DObjGetStruct(fighter_gobj)->translate.x);
            }
            else dist_x = pos.x - DObjGetStruct(fighter_gobj)->translate.x;

            if (dist_x <= FTCOMMON_DOKAN_DETECT_WIDTH)
            {
                func_ovl3_80142164(fighter_gobj, 0xD);

                return TRUE;
            }
        }
    }
    return FALSE;
}

void func_ovl3_801423B4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.dokan.pos_adjust_wait++;

    if (fp->status_vars.common.dokan.pos_adjust_wait == FTCOMMON_DOKAN_POS_ADJUST_WAIT)
    {
        if (fp->status_vars.common.dokan.wall_line_id == 0x14)
        {
            func_ovl3_801427CC(fighter_gobj);
        }
        else func_ovl3_801426D0(fighter_gobj);
    }
}

void func_ovl3_80142424(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    DObjGetStruct(fighter_gobj)->translate.x = func_8000CA28(0.033333335F, fp->status_vars.common.dokan.pos_adjust_wait, fp->status_vars.common.dokan.pos_current.x, fp->status_vars.common.dokan.pos_target.x, 0.0F, 0.0F);
    DObjGetStruct(fighter_gobj)->translate.y = func_8000CA28(0.033333335F, fp->status_vars.common.dokan.pos_adjust_wait, fp->status_vars.common.dokan.pos_current.y, fp->status_vars.common.dokan.pos_target.y, 0.0F, 0.0F);
}

void func_ovl3_801424BC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 pos_target_x;
    s32 wall_line_id;

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Common_DokanWait, 0.0F, 1.0F, 0x10U);

    fp->x18D_flag_b7 = TRUE;
    fp->x18E_flag_b3 = TRUE;
    fp->x18E_flag_b5 = TRUE;

    fp->status_vars.common.dokan.pos_adjust_wait = 0;

    fp->x191_flag_b3 = TRUE;

    if (fp->status_vars.common.dokan.ground_line_id == 0xC)
    {
        fp->status_vars.common.dokan.wall_line_id = 0xB;
    }
    else fp->status_vars.common.dokan.wall_line_id = 0xA;

    func_ovl2_800FC814(fp->status_vars.common.dokan.wall_line_id, &wall_line_id);

    func_ovl2_800FC894(wall_line_id, &fp->status_vars.common.dokan.pos_target);

    if (rand_f32() <= 0.25F)
    {
        fp->status_vars.common.dokan.wall_line_id = 0x14;

        func_ovl2_800FC814(0x14, &wall_line_id);
        func_ovl2_800FC894(wall_line_id, &fp->status_vars.common.dokan.pos_target);

        if (func_ovl2_800F9C30(&fp->status_vars.common.dokan.pos_target, 0, &pos_target_x, 0, 0) != FALSE)
        {
            fp->status_vars.common.dokan.pos_target.x += pos_target_x + fp->coll_data.object_coll.width;
        }
    }
}

void func_ovl3_801425E4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame >= FTCOMMON_DOKAN_EXIT_WAIT)
    {
        if (fp->status_vars.common.dokan.turn_stop_wait != 0)
        {
            fp->status_vars.common.dokan.turn_stop_wait--;

            fp->joint[0]->rotate.y += (FTCOMMON_DOKAN_TURN_STEP * fp->lr);

            func_ovl2_800EB528(fp->joint[0]);
        }
    }
}

void func_ovl3_80142660(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.dokan.set_unk_wait != 0)
    {
        fp->status_vars.common.dokan.set_unk_wait--;

        if (fp->status_vars.common.dokan.set_unk_wait == 0)
        {
            func_ovl2_800E7F7C(fighter_gobj, 1);
        }
    }
}

void func_ovl3_80142698(GObj *fighter_gobj)
{
    func_ovl3_80142660(fighter_gobj);
    func_ovl3_801425E4(fighter_gobj);
    func_ovl2_800D9480(fighter_gobj, func_ovl2_800DEE54);
}

void func_ovl3_801426D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Common_DokanEnd, 0.0F, 1.0F, 0x10U);

    DObjGetStruct(fighter_gobj)->translate = fp->status_vars.common.dokan.pos_target;

    func_ovl2_800F9348(&DObjGetStruct(fighter_gobj)->translate, &fp->coll_data.ground_line_id, &fp->coll_data.unk_0x78, &fp->coll_data.clip_flag, &fp->coll_data.ground_angle);

    fp->x18F_flag_b4 = TRUE;
    fp->status_vars.common.dokan.set_unk_wait = FTCOMMON_DOKAN_UNK_WAIT;

    if ((fp->ft_kind != Ft_Kind_Mario) && (fp->ft_kind != Ft_Kind_MetalMario) && (fp->ft_kind != Ft_Kind_PolyMario) && (fp->ft_kind != Ft_Kind_Luigi) && (fp->ft_kind != Ft_Kind_PolyLuigi))
    {
        fp->status_vars.common.dokan.turn_stop_wait = FTCOMMON_DOKAN_TURN_STOP_WAIT_DEFAULT;
        fp->joint[0]->rotate.y = 0.0F;

        func_ovl2_800EB528(fp->joint[0]);
    }
    else fp->status_vars.common.dokan.turn_stop_wait = 0;

    func_800269C0(0xD6U);
}

void func_ovl3_801427CC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);

    fp->lr = RIGHT;

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Common_DokanWalk, 0.0F, 1.0F, 0x10U);

    DObjGetStruct(fighter_gobj)->translate = fp->status_vars.common.dokan.pos_target;

    fp->status_vars.common.dokan.set_unk_wait = FTCOMMON_DOKAN_UNK_WAIT;

    func_800269C0(0xD6U);
}