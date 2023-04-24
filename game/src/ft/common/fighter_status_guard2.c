#include "fighter.h"
#include "effect.h"

void func_ovl3_80148E30(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_GuardOn, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    if (fp->shield_health != 0)
    {
        if (fp->ft_kind == Ft_Kind_Yoshi)
        {
            fp->status_vars.common.guard.effect_gobj = func_ovl2_80101374(fighter_gobj);

            func_ovl2_800E90F8(fighter_gobj);
            func_ovl3_80148214(fighter_gobj);
        }
        else fp->status_vars.common.guard.effect_gobj = func_ovl2_80101108(fighter_gobj);

        fp->x18F_flag_b2 = TRUE;
    }
    func_ovl3_80148714(fighter_gobj);

    fp->status_vars.common.guard.release_lag = FTCOMMON_GUARD_RELEASE_LAG;
    fp->status_vars.common.guard.shield_decay_wait = FTCOMMON_GUARD_DECAY_INT;
    fp->status_vars.common.guard.is_release = FALSE;
    fp->status_vars.common.guard.slide_frames = 0;
    fp->status_vars.common.guard.is_setoff = FALSE;

    ftStatus_Update(fighter_gobj, ftStatus_Common_Guard, 0.0F, 1.0F, 0x34U);

    func_ovl3_8014889C(fighter_gobj);

    fp->x18F_flag_b2 = TRUE;
}

bool32 func_ovl3_80148F24(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->input.button_hold & fp->input.button_mask_z) && (fp->shield_health != 0))
    {
        func_ovl3_80148E30(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80148F74(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80148304(fighter_gobj);

    if (fp->shield_health == 0)
    {
        func_ovl3_80149510(fighter_gobj);
    }
    else if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_8013E1C8(fighter_gobj);
    }
    else func_ovl3_80148714(fighter_gobj);
}

void func_ovl3_80148FF0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    u32 flag = fp->x18F_flag_b2;

    ftStatus_Update(fighter_gobj, ftStatus_Common_GuardOff, 0.0F, 1.0F, 0x34U);
    ftAnim_Update(fighter_gobj);

    fp->x18F_flag_b2 = flag;

    func_ovl3_80148714(fighter_gobj);
    func_800269C0(0xEU);
}

void func_ovl3_80149074(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80148120(fp);

    fp->status_vars.common.guard.setoff_frames--;

    if (fp->status_vars.common.guard.setoff_frames <= 0.0F)
    {
        if (fp->status_vars.common.guard.is_release != FALSE)
        {
            func_ovl3_80148FF0(fighter_gobj);
        }
        else func_ovl3_80148DDC(fighter_gobj);
    }
    else func_ovl3_8014889C(fighter_gobj);
}

void func_ovl3_80149108(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_GuardSetOff, 0.0F, 1.0F, 0x34U);

    fp->status_vars.common.guard.setoff_frames = (fp->shield_damage * FTCOMMON_GUARD_SETOFF_MUL) + FTCOMMON_GUARD_SETOFF_ADD;

    fp->phys_info.vel_ground.x = ((fp->lr == fp->lr_shield) ? LEFT : RIGHT) * (fp->status_vars.common.guard.setoff_frames * FTCOMMON_GUARD_VEL_MUL);

    if (fp->status_vars.common.guard.effect_gobj != NULL)
    {
        Effect_Struct *ep = EffectGetStruct(fp->status_vars.common.guard.effect_gobj);

        ep->unk_ef_0x1C = 1;
    }
    fp->x18F_flag_b2 = TRUE;

    fp->status_vars.common.guard.is_setoff = TRUE;
}