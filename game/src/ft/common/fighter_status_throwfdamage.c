#include "ftdonkey.h"

// DK enters this state when hit out of Cargo Thorw but it does not persist?

void func_ovl3_8014E050(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.throwfdamage.hitstun_timer -= 1.0F;

    if (fp->status_vars.common.throwfdamage.hitstun_timer <= 0.0F)
    {
        if (fp->ground_or_air == air)
        {
            fp->publicity_knockback = fp->status_vars.common.throwfdamage.publicity_knockback;

            func_ovl3_8014DA98(fighter_gobj);
        }
        else func_ovl3_8014D49C(fighter_gobj);
    }
}

void func_ovl3_8014E0E0(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    f32 knockback_resist = (this_fp->knockback_resist_status < this_fp->knockback_resist_passive) ? this_fp->knockback_resist_passive : this_fp->knockback_resist_status;

    this_fp->damage_knockback -= knockback_resist;

    if (this_fp->damage_knockback <= 0.0F)
    {
        this_fp->damage_knockback = 0.0F;
    }
    ftCommon_Damage_InitDamageVars(fighter_gobj, ftStatus_Donkey_ThrowFDamage, this_fp->damage_taken_recent, this_fp->damage_knockback, this_fp->damage_angle, this_fp->lr_damage, this_fp->damage_index, this_fp->damage_element, this_fp->damage_player_number, FALSE, FALSE, TRUE);

    if (this_fp->catch_gobj != NULL)
    {
        GObj *catch_gobj = this_fp->catch_gobj;
        Fighter_Struct *capture_fp = FighterGetStruct(catch_gobj);

        func_ovl3_8014AB64(catch_gobj);
        func_ovl2_800EB528(capture_fp->joint[0]);
    }
}