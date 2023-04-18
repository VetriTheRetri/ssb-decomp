#include "ftmasterhand.h"

void func_ovl3_8015A3C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->fighter_vars.masterhand.p_masterhand->unk_0xC == 1.5F) && (fighter_gobj->anim_frame >= 20.0F) && (fp->status_vars.masterhand.yubideppou.bullet_count != 3))
    {
        func_ovl3_8015A538(fighter_gobj);
    }
    else if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_80159040(fighter_gobj);
    }
}

void func_ovl3_8015A45C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    if (fp->status_vars.masterhand.yubideppou.shoot_timer != 0)
    {
        fp->status_vars.masterhand.yubideppou.shoot_timer--;

        if (fp->status_vars.masterhand.yubideppou.shoot_timer == 0)
        {
            pos.z = 0.0F;
            pos.y = 0.0F;
            pos.x = 0.0F;

            func_ovl2_800EDF24(fp->joint[19], &pos);

            if ((fp->fighter_vars.masterhand.p_masterhand->unk_0xC == 1.5F) && (fp->status_vars.masterhand.yubideppou.bullet_count != 3))
            {
                func_ovl3_8016DE28(fighter_gobj, &pos);
            }
            else
            {
                func_ovl3_8016DDB4(fighter_gobj, &pos);
            }
        }
    }
    if (fp->fighter_vars.masterhand.p_masterhand->unk_0xC == 1.5F)
    {
        func_ovl3_8015A600(fighter_gobj);
    }
}

void func_ovl3_8015A538(GObj *fighter_gobj)
{
    Fighter_Struct *fp;
    Vec3f pos;

    ftStatus_Update(fighter_gobj, ftStatus_MasterHand_Yubideppou3, 0.0F, 1.0F, 0U);

    fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.masterhand.yubideppou.bullet_count++;

    pos.x = 0.0F;
    pos.y = 0.0F;
    pos.z = 0.0F;

    func_ovl2_800EDF24(fp->joint[15], &pos);

    if ((fp->fighter_vars.masterhand.p_masterhand->unk_0xC == 1.5F) && (fp->status_vars.masterhand.yubideppou.bullet_count != 3))
    {
        func_ovl3_8016DE28(fighter_gobj, &pos);
    }
    else
    {
        func_ovl3_8016DDB4(fighter_gobj, &pos);
    }
    fp->status_vars.masterhand.yubideppou.shoot_timer = 4;
}
