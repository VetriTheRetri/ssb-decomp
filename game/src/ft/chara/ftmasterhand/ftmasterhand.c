#include "ftmasterhand.h"

// General Master Hand code?

#define HALF_PI32 1.5707964F

void func_ovl3_80157F60(GObj *fighter_gobj) // Turn Master Hand around?
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->lr = -fp->lr;

    fp->joint[0]->rotate.y = (f32)fp->lr * HALF_PI32;
}

void func_ovl3_80157F90(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos_b;
    Vec3f pos_a;

    func_ovl2_800F4428(fp->fighter_vars.masterhand.p_masterhand->unk_0x4, &pos_b);

    func_ovl2_800F4408(fp->fighter_vars.masterhand.p_masterhand->unk_0x4, &pos_a);

    if (((((pos_b.x + pos_a.x) * 0.5F) - DObjGetStruct(fighter_gobj)->translate.x) * (f32)fp->lr) < 0.0F)
    {
        func_ovl3_80157F60(fighter_gobj);
    }
}

void func_ovl3_80158030(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.x - DObjGetStruct(fighter_gobj)->translate.x) * (f32)fp->lr) < 0.0F)
    {
        func_ovl3_80157F60(fighter_gobj);
    }
}

void func_ovl3_80158094(s32 var, Vec3f *pos)
{
    if (rand_u16() & 1)
    {
        func_ovl2_800F4428(var, pos);
    }
    else func_ovl2_800F4408(var, pos);
}

void func_ovl3_801580E0(GObj *fighter_gobj, Vec3f *pos)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *unk_fp = FighterGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj);
    MasterHand_Struct *p_masterhand = fp->fighter_vars.masterhand.p_masterhand;

    if ((unk_fp->coll_data.ground_line_id != -1) && (unk_fp->coll_data.ground_line_id != -2))
    {
        fp->fighter_vars.masterhand.p_masterhand->unk_0x4 = unk_fp->coll_data.ground_line_id;
    }
    else
    {
        if ((fp->coll_data.ground_line_id != -1) && (unk_fp->coll_data.ground_line_id != -2))
        {
            fp->fighter_vars.masterhand.p_masterhand->unk_0x4 = fp->coll_data.ground_line_id;
        }
        else
        {
            fp->fighter_vars.masterhand.p_masterhand->unk_0x4 = (s32)fp->fighter_vars.masterhand.p_masterhand->unk_0x8;
        }
    }
    func_ovl3_80158094(fp->fighter_vars.masterhand.p_masterhand->unk_0x4, pos);

    pos->y += 100.0F;
}

void func_ovl3_8015817C(GObj *fighter_gobj, Vec3f *pos, f32 off_y)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    pos->x = DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.x;
    pos->y = DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.y + off_y;
    pos->z = 0.0F;
}

void func_ovl3_801581BC(GObj *fighter_gobj, Vec3f *pos, f32 pos_x, f32 pos_y)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *fp_unk = FighterGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj);
    Vec3f translate = DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate;
    f32 x;
    f32 y;

    x = translate.x;

    translate.x += (rand_u16() & 1) ? pos_x : -pos_x;

    if (func_ovl2_800F3DD8(fp_unk->coll_data.ground_line_id, &translate, &y, 0, 0) != FALSE)
    {
        pos->x = translate.x;
    }
    else
    {
        translate.x = (x < translate.x) ? x - pos_x : x + pos_x;

        pos->x = (func_ovl2_800F3DD8(fp_unk->coll_data.ground_line_id, &translate, &y, 0, 0) != FALSE) ? translate.x : x;
    }
    pos->y = (f32)(translate.y + y + pos_y);
    pos->z = 0.0F;
}

void func_ovl3_80158310(GObj *fighter_gobj, Vec3f *pos, f32 pos_x, f32 pos_y)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    pos->x = (f32)((rand_u16() & 1) ? pos_x : -pos_x) + DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.x;
    pos->y = (f32)DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.y + pos_y;
    pos->z = 0.0F;
}

// I have no idea what is going on here but at least it matches
// Maybe Master Hand movement values or player tracking???

void func_ovl3_8015839C(s32 var, Vec3f *pos_input)
{
    Vec3f pos_b;
    Vec3f pos_a;
    f32 y;

    func_ovl2_800F4428(var, &pos_b);
    func_ovl2_800F4408(var, &pos_a);

    pos_input->x = (pos_b.x + pos_a.x) * 0.5F;
    pos_input->z = 0.0F;
    pos_input->y = 0.0F;

    func_ovl2_800F3DD8(var, pos_input, &y, 0, 0);
    pos_input->y += y;
}

void func_ovl3_80158428(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->fighter_vars.masterhand.p_masterhand->wait_timer = ((rand_u16_range(FTMASTERHAND_ATTACK_WAIT_MAX) + (FTMASTERHAND_ATTACK_WAIT_LEVEL_DIV / fp->cp_level)) / fp->fighter_vars.masterhand.p_masterhand->unk_0xC);
}

void func_ovl3_80158528(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 var_at;
    f32 var_f2;
    s32 temp_f4;

    if (fp->joint[0]->translate.z > 0.0F)
    {
        var_at = 127.0F;
        var_f2 = 1.0F;
    }
    else
    {
        if (fp->joint[0]->translate.z < -15000.0F)
        {
            var_f2 = 0.0F;
        }
        else
        {
            var_f2 = (fp->joint[0]->translate.z - (-15000.0F)) / 15000.0F;
        }
        var_at = 127.0F;
    }

    temp_f4 = ((var_at * var_f2) + 128.0F);

    if (temp_f4 >= (U8_MAX + 1))
    {
        fp->unk_0xA8C = U8_MAX;
    }
    else
    {
        fp->unk_0xA8C = temp_f4;
    }
    if (temp_f4 >= (U8_MAX + 1))
    {
        fp->unk_0xA8D = U8_MAX;
    }
    else
    {
        fp->unk_0xA8D = temp_f4;
    }
    if (temp_f4 >= (U8_MAX + 1))
    {
        fp->unk_0xA8E = U8_MAX;
    }
    else fp->unk_0xA8E = temp_f4;
}

void func_ovl3_80158604(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->x192_flag_b4 = TRUE;
    fp->unk_0xA8F = U8_MAX;
}

void func_ovl3_80158620(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->x192_flag_b4 = FALSE;
}

void func_ovl3_80158634(GObj *fighter_gobj)
{
    Fighter_Struct *fp;

    if (func_ovl2_800FC8EC(0) == FALSE)
    {
        while (TRUE)
        {
            fatal_printf("nothing under cll id\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800FC900(0, 1, &fp->fighter_vars.masterhand.p_masterhand->unk_0x8);
}

void func_ovl3_801586A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id = fp->status_info.status_id;

    if ((status_id != ftStatus_MasterHand_Dead1) && (status_id != ftStatus_MasterHand_Dead2) && (status_id != ftStatus_MasterHand_Dead3))
    {
        if (fp->percent_dmg_total >= 300)
        {
            func_unkmulti_8018F75C(fighter_gobj);
            if (fp->lr == LEFT)
            {
                func_ovl3_8015AD74(fighter_gobj);
            }
            else func_ovl3_8015AE80(fighter_gobj);
        }
        else if (fp->percent_dmg_total >= 200)
        {
            fp->fighter_vars.masterhand.p_masterhand->unk_0xC = 1.5F;
        }
    }
}