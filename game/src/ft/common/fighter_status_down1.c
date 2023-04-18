#include "fighter.h"

// Covers DownBounce, DownWait

void func_ovl3_80144220(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.downwait.stand_wait--;

    if (fp->status_vars.common.downwait.stand_wait == 0)
    {
        func_ovl3_80144580(fighter_gobj);
    }
}

void func_ovl3_80144254(GObj *fighter_gobj)
{
    if ((func_ovl3_8014499C(fighter_gobj) == FALSE) && (func_ovl3_8014482C(fighter_gobj) == FALSE))
    {
        func_ovl3_801445D8(fighter_gobj);
    }
}

void func_ovl3_80144294(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (fp->status_info.status_id == ftStatus_Common_DownBounceD)
    {
        status_id = ftStatus_Common_DownWaitD;
    }
    else status_id = ftStatus_Common_DownWaitU;

    func_ovl2_800E6F24(fighter_gobj, status_id, 0.0F, 1.0F, 0x1E0U);

    fp->status_vars.common.downwait.stand_wait = FTCOMMON_DOWNWAIT_STAND_WAIT;

    func_ovl2_800E8098(fp, 0x33U);

    fp->damage_mul = 0.5F;
}

void func_ovl3_80144308(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.downbounce.attack_buffer != 0)
    {
        fp->status_vars.common.downbounce.attack_buffer--;
    }
    if (fp->input.button_press & (fp->input.button_mask_a | fp->input.button_mask_b))
    {
        fp->status_vars.common.downbounce.attack_buffer = FTCOMMON_DOWNBOUNCE_ATTACK_BUFFER;
    }
    if ((fighter_gobj->anim_frame <= 0.0F) && (func_ovl3_80144944(fighter_gobj) == FALSE) && (func_ovl3_8014482C(fighter_gobj) == FALSE))
    {
        func_ovl3_80144294(fighter_gobj);
    }
}

bool32 func_ovl3_80144398(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 rot_x = fp->joint[4]->rotate.x;

    rot_x /= DOUBLE_PI32;

    rot_x -= (s32) rot_x;

    if ((rot_x < -0.5F) || ((rot_x > 0.0F) && (rot_x < 0.5F)))
    {
        return TRUE;
    }
    else return FALSE;
}

extern u16 Fighter_DownBounce_Sound[];

void func_ovl3_80144428(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800EABDC(fighter_gobj, 0x16, 0, 0, 0, fp->lr, 0, 0);
    func_800269C0(Fighter_DownBounce_Sound[fp->ft_kind]);
    func_ovl2_800E806C(fp, 4, 0);
}

void func_ovl3_80144498(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (fp->ground_or_air == air)
    {
        func_ovl2_800DEE98(fp);
    }
    if (func_ovl3_80144398(fighter_gobj) != FALSE)
    {
        status_id = ftStatus_Common_DownBounceD;
    }
    else status_id = ftStatus_Common_DownBounceU;

    func_ovl2_800E6F24(fighter_gobj, status_id, 0.0F, 1.0F, 0x100U);
    func_ovl3_80144428(fighter_gobj);

    fp->status_vars.common.downbounce.attack_buffer = 0;
    fp->damage_mul = 0.5F;

    func_ovl2_800E9CE8(fp);
}
