#include "ftmasterhand.h"



const u8 ftMasterHand_StatusRandomPool[12];
const u8 D_ovl3_80188DCC[16];
const u8 D_ovl3_80188DDC[8];
const u8 D_ovl3_80188DE4[8];
const u8 D_ovl3_80188DEC[20];

void func_ovl3_80158750(GObj *fighter_gobj)
{
    if (Match_Info->pause_status != gmPauseStatus_Disable)
    {
        func_ovl3_80159040(fighter_gobj);
    }
}

void func_ovl3_80158784(GObj *fighter_gobj) // Unused
{
    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Unk, 0.0F, 1.0F, 0U);
}

void func_ovl3_801587B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    s32 vel_x = (ABS(fp->input.pl.stick_range.x) >= 8) ? fp->input.pl.stick_range.x : 0;
    s32 vel_y = (ABS(fp->input.pl.stick_range.y) >= 8) ? fp->input.pl.stick_range.y : 0;

    fp->phys_info.vel_air.x = (f32)vel_x;
    fp->phys_info.vel_air.y = (f32)vel_y;
}

void func_ovl3_80158824(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    f32 angle;
    Fighter_Struct *fp_target;
    Vec3f sp30;

    if (ftCommon_Turn_CheckInputSuccess(fighter_gobj) != FALSE)
    {
        fp->lr = -fp->lr;
        fp->joint[0]->rotate.y = fp->lr * HALF_PI32;
    }

    angle = ftCommon_GetStickAngleRadians(fp);

    fp_target = ftGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj);

    if (fp->input.pl.button_tap & fp->input.button_mask_b)
    {
        if ((fp->input.pl.stick_range.x * fp->lr) >= 20)
        {
            if (ABSF(angle) <= F_DEG_TO_RAD(50.0F)) // 0.87266463F
            {
                func_ovl3_801580E0(fighter_gobj, &sp30);
                func_ovl3_801592B4(fighter_gobj, func_ovl3_801593A4, &sp30);
                return;
            }
        }
        if ((fp->input.pl.stick_range.y >= 20) && (F_DEG_TO_RAD(50.0F) < angle)) // 0.87266463F
        {
            func_ovl3_80159524(fighter_gobj);
            return;
        }
        else if ((fp->input.pl.stick_range.y <= -20) && (angle < F_DEG_TO_RAD(-50.0F))) // -0.87266463F
        {
            if ((fp_target->coll_data.ground_line_id != -1) && (fp_target->coll_data.ground_line_id != -2))
            {
                func_ovl3_8015817C(fighter_gobj, &sp30, 800.0F);
                func_ovl3_801592B4(fighter_gobj, func_ovl3_80159B9C, &sp30);
                return;
            }
        }
        func_ovl3_801580E0(fighter_gobj, &sp30);
        func_ovl3_801592B4(fighter_gobj, func_ovl3_80159854, &sp30);

    }
    else if (fp->input.pl.button_tap & fp->input.button_mask_a)
    {
        if ((ABS(fp->input.pl.stick_range.x) >= 56) && ((s32)fp->tap_stick_x < 3))
        {
            func_ovl3_80158310(fighter_gobj, &sp30, 3000.0F, 0);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_8015A374, &sp30);
            return;
        }

        else if ((fp->input.pl.stick_range.y >= 53) && ((s32)fp->tap_stick_y < 4))
        {
            func_ovl3_80158310(fighter_gobj, &sp30, 600.0F, 0);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_8015A7C4, &sp30);
            return;
        }
        else if ((fp->input.pl.stick_range.y <= -53) && ((s32)fp->tap_stick_y < 4))
        {
            func_ovl3_80158310(fighter_gobj, &sp30, 600.0F, 0);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_8015ACD4, &sp30);
            return;
        }
        else if (((fp->input.pl.stick_range.x * fp->lr) >= 20) && (angle <= F_DEG_TO_RAD(50.0F))) // 0.87266463F
        {
            func_ovl3_80158310(fighter_gobj, &sp30, 3000.0F, 100.0F);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_8015A314, &sp30);
            return;
        }
        else if ((fp->input.pl.stick_range.y >= 20) && (F_DEG_TO_RAD(50.0F) < angle)) // 0.87266463F
        {
            if ((fp_target->coll_data.ground_line_id != -1) && (fp_target->coll_data.ground_line_id != -2))
            {
                func_ovl3_801581BC(fighter_gobj, &sp30, 600.0F, 100.0F);
                func_ovl3_801592B4(fighter_gobj, func_ovl3_8015A268, &sp30);
                return;
            }
        }
        if ((fp->input.pl.stick_range.y <= -20) && (angle < F_DEG_TO_RAD(-50.0F)))
        {
            func_ovl3_801580E0(fighter_gobj, &sp30);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_801594BC, &sp30);
            return;
        }
        func_ovl3_8015817C(fighter_gobj, &sp30, 800.0F);
        func_ovl3_801592B4(fighter_gobj, func_ovl3_80159EC4, &sp30);
        return;
    }
    else func_ovl3_801587B0(fighter_gobj);
}

void func_ovl3_80158C34(GObj *fighter_gobj) // Decide Master Hand's next attack
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;
    u32 random;
    u32 var;
    s32 status_id;
    u32 unused[2];
    const u8 *index_ptr;

    fp->fighter_vars.masterhand.p_masterhand->wait_timer--;

    if (fp->fighter_vars.masterhand.p_masterhand->wait_timer == 0)
    {
        if (fp->fighter_vars.masterhand.p_masterhand->unk_0x16 == 3)
        {
            fp->fighter_vars.masterhand.p_masterhand->unk_0x16 = 0;

            var = 2;
        }
        else
        {
            random = rand_u16_range(3);

            var = D_ovl3_80188DEC[fp->fighter_vars.masterhand.p_masterhand->unk_0x14 * 3 + random];

            if (var == 2)
            {
                fp->fighter_vars.masterhand.p_masterhand->unk_0x16 = 0;
            }
            else fp->fighter_vars.masterhand.p_masterhand->unk_0x16++;
        }
        if (ftGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->coll_data.ground_line_id == -1 ||
            ftGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->coll_data.ground_line_id == -2)
            {
                index_ptr = &D_ovl3_80188DE4[var * 2];
            }
            else index_ptr = &D_ovl3_80188DDC[var * 2];

        random = D_ovl3_80188DCC[*index_ptr + rand_u16_range(*(index_ptr + 1))];

        fp->fighter_vars.masterhand.p_masterhand->unk_0x14 = var;

        status_id = ftMasterHand_StatusRandomPool[random];

        fp->fighter_vars.masterhand.p_masterhand->unk_0x15 = random;

        switch (status_id)
        {
        case ftStatus_MasterHand_Hippataku:
            func_ovl3_801580E0(fighter_gobj, &pos);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_801593A4, &pos);
            break;

        case ftStatus_MasterHand_Okuhikouki1:
            func_ovl3_80159524(fighter_gobj);
            break;

        case ftStatus_MasterHand_GootsubuUp:
            func_ovl3_8015817C(fighter_gobj, &pos, 800.0F);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_80159B9C, &pos);
            break;

        case ftStatus_MasterHand_Walk:
            func_ovl3_801580E0(fighter_gobj, &pos);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_80159854, &pos);
            break;

        case ftStatus_MasterHand_Yubideppou1:
            func_ovl3_80158310(fighter_gobj, &pos, 3000.0F, 0.0F);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_8015A374, &pos);
            break;

        case ftStatus_MasterHand_OkuPunch1:
            func_ovl3_80158310(fighter_gobj, &pos, 600.0F, 0.0F);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_8015A7C4, &pos);
            break;

        case ftStatus_MasterHand_OkutsubushiStart:
            func_ovl3_80158310(fighter_gobj, &pos, 600.0F, 0.0F);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_8015ACD4, &pos);
            break;

        case ftStatus_MasterHand_Okukouki:
            func_ovl3_80158310(fighter_gobj, &pos, 3000.0F, 100.0F);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_8015A314, &pos);
            break;

        case ftStatus_MasterHand_Drill:
            func_ovl3_801581BC(fighter_gobj, &pos, 600.0F, 100.0F);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_8015A268, &pos);
            break;

        case ftStatus_MasterHand_Harau:
            func_ovl3_801580E0(fighter_gobj, &pos);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_801594BC, &pos);
            break;

        case ftStatus_MasterHand_Tsutsuku1:
            func_ovl3_8015817C(fighter_gobj, &pos, 800.0F);
            func_ovl3_801592B4(fighter_gobj, func_ovl3_80159EC4, &pos);
            break;

        default:
            break;
        }
        func_ovl3_80158428(fighter_gobj);
    }
}

void func_ovl3_80158F74(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->status_info.pl_kind == Pl_Kind_Human)
    {
        func_ovl3_80158824(fighter_gobj);
    }
    else func_ovl3_80158C34(fighter_gobj);
}

void func_ovl3_80158FB4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f vel;
    f32 magnitude;

    if (fp->status_info.pl_kind != Pl_Kind_Human)
    {
        vec3f_sub(&vel, &fp->status_vars.masterhand.wait.pos, &DObjGetStruct(fighter_gobj)->translate);

        magnitude = vec3f_mag(&vel);

        vec3f_normalize(&vel);

        vec3f_scale(&vel, magnitude * 0.1F);

        fp->phys_info.vel_air.x = vel.x;
        fp->phys_info.vel_air.y = vel.y;
    }
}

static gmUnkInfo_80131308 D_ovl2_80131308;

void func_ovl3_80159040(GObj *fighter_gobj)
{
    Fighter_Struct *fp;
    Vec3f *translate;
    Vec3f pos;
    s32 ground_line_id;

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Wait, 0.0F, 1.0F, 0);

    fp = ftGetStruct(fighter_gobj);

    translate = &DObjGetStruct(fighter_gobj)->translate;

    if (fp->coll_data.ground_line_id != -1)
    {
        fp->status_vars.masterhand.wait.pos.x = (f32)translate->x;
        fp->status_vars.masterhand.wait.pos.y = (f32)(translate->y + fp->coll_data.ground_dist);
    }
    else
    {
        ground_line_id = ftGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->coll_data.ground_line_id;

        if ((ground_line_id == -1) || (ground_line_id == -2))
        {
            ground_line_id = fp->fighter_vars.masterhand.p_masterhand->unk_0x8;
        }

        if (D_ovl2_80131308.unk_80131308_0x28 < translate->x)
        {
            func_ovl2_800F4408(ground_line_id, &pos);
        }
        else if (translate->x < D_ovl2_80131308.unk_80131308_0x2C)
        {
            func_ovl2_800F4428(ground_line_id, &pos);
        }
        else
        {
            func_ovl3_8015839C(ground_line_id, &pos);
        }
        fp->status_vars.masterhand.wait.pos.x = pos.x;
        fp->status_vars.masterhand.wait.pos.y = pos.y;
    }

    fp->status_vars.masterhand.wait.pos.y += (fp->fighter_vars.masterhand.p_masterhand->unk_0xC == 1.5F) ? 600.0F : 400.0F;
    fp->status_vars.masterhand.wait.pos.z = 0.0F;
}
