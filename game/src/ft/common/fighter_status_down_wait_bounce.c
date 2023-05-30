#include "fighter.h"

// Covers DownBounce, DownWait

#define FTCOMMON_DOWNBOUNCE_STATUPDATE_FLAGS (FTSTATUPDATE_UNK3_PRESERVE | FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_SLOPECONTOUR_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE)

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

// 0x80144294
void ftCommon_DownWait_ApplyStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (fp->status_info.status_id == ftStatus_Common_DownBounceD)
    {
        status_id = ftStatus_Common_DownWaitD;
    }
    else status_id = ftStatus_Common_DownWaitU;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, FTCOMMON_DOWNBOUNCE_STATUPDATE_FLAGS);

    fp->status_vars.common.downwait.stand_wait = FTCOMMON_DOWNWAIT_STAND_WAIT;

    ftCommon_SetCaptureFlags(fp, 0x33U);

    fp->damage_mul = 0.5F;
}

void func_ovl3_80144308(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.downbounce.attack_buffer != 0)
    {
        fp->status_vars.common.downbounce.attack_buffer--;
    }
    if (fp->input.pl.button_tap & (fp->input.button_mask_a | fp->input.button_mask_b))
    {
        fp->status_vars.common.downbounce.attack_buffer = FTCOMMON_DOWNBOUNCE_ATTACK_BUFFER;
    }
    if ((fighter_gobj->anim_frame <= 0.0F) && (func_ovl3_80144944(fighter_gobj) == FALSE) && (func_ovl3_8014482C(fighter_gobj) == FALSE))
    {
        ftCommon_DownWait_ApplyStatus(fighter_gobj);
    }
}

// 0x80144398
bool32 ftCommon_DownBounce_UpOrDown(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    f32 rot_x = fp->joint[4]->rotate.x;

    rot_x /= DOUBLE_PI32;

    rot_x -= (s32) rot_x;

    if ((rot_x < -0.5F) || ((rot_x > 0.0F) && (rot_x < 0.5F)))
    {
        return 1;
    }
    else return 0;
}

extern u16 Fighter_DownBounce_Sound[];

void func_ovl3_80144428(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCommon_GFXSpawn(fighter_gobj, 0x16, 0, 0, 0, fp->lr, 0, 0);
    func_800269C0(Fighter_DownBounce_Sound[fp->ft_kind]);
    func_ovl2_800E806C(fp, 4, 0);
}

// 0x80144498
void ftCommon_DownBounce_ApplyStatus(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    if (fp->ground_or_air == air)
    {
        ftMapCollide_SetGround(fp);
    }
    if (ftCommon_DownBounce_UpOrDown(fighter_gobj) != 0)
    {
        status_id = ftStatus_Common_DownBounceD;
    }
    else status_id = ftStatus_Common_DownBounceU;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, FTSTATUPDATE_UNK3_PRESERVE);
    func_ovl3_80144428(fighter_gobj);

    fp->status_vars.common.downbounce.attack_buffer = 0;
    fp->damage_mul = 0.5F;

    ftCommon_VelDamageTransferGround(fp);
}
