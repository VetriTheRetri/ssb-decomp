#include "fighter.h"
#include "article.h"

void func_ovl3_80146FB0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl2_800DEE54);
}

const Vec3f Fighter_LGunShoot_Ammo_Offset = { FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_X, FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_Y, FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_Z };
const Vec3f Fighter_LGunShoot_Dust_Offset = { FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_X, FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_Y, FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_Z };

void func_ovl3_80146FD4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Article_Struct *ap;
    f32 size_mul;
    Vec3f spawn_ammo_offset;
    Vec3f spawn_gfx_offset;
    Vec3f dust_gfx_offset;

    if ((fp->item_hold != NULL) && (fp->command_vars.flags.flag0 != 0))
    {
        ap = ArticleGetStruct(fp->item_hold);

        if (ap->at_multi != 0)
        {
            spawn_ammo_offset = Fighter_LGunShoot_Ammo_Offset;

            size_mul = 1.0F / fp->attributes->size_mul;

            spawn_ammo_offset.x *= size_mul;
            spawn_ammo_offset.y *= size_mul;
            spawn_ammo_offset.z *= size_mul;

            func_ovl2_800EDF24(fp->joint[fp->attributes->joint_itemhold_light], &spawn_ammo_offset);
            func_ovl3_80175AD8(fighter_gobj, &spawn_ammo_offset);

            spawn_gfx_offset.x = 0.0F;
            spawn_gfx_offset.y = FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_Y;
            spawn_gfx_offset.z = FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_Z;

            func_ovl2_800EABDC(fighter_gobj, 0x1F, fp->attributes->joint_itemhold_light, &spawn_gfx_offset, 0, fp->lr, 1, 0);

            spawn_gfx_offset.x = 0.0F;
            spawn_gfx_offset.y = 0.0F;
            spawn_gfx_offset.z = -FTCOMMON_LGUNSHOOT_AMMO_SPAWN_OFF_Z;

            func_ovl2_800EABDC(fighter_gobj, 0x13, 0, &spawn_gfx_offset, 0, fp->lr, 0, 0);

            func_800269C0(0x3DU);
            func_ovl2_800E806C(fp, 9, 0);
        }
        else
        {
            dust_gfx_offset = Fighter_LGunShoot_Dust_Offset;

            func_ovl2_800EABDC(fighter_gobj, 0xB, fp->attributes->joint_itemhold_light, &dust_gfx_offset, 0, -fp->lr, 1, 0);
            func_800269C0(0x3EU);
        }
        fp->command_vars.flags.flag0 = 0;
    }
}

void func_ovl3_801471C0(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80147258);
}

void func_ovl3_801471E4(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80147208);
}

void func_ovl3_80147208(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_LGunShoot, fighter_gobj->anim_frame, 1.0F, 0U);

    fp->cb_accessory = func_ovl3_80146FD4;
}

void func_ovl3_80147258(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_LGunShootAir, fighter_gobj->anim_frame, 1.0F, 0U);
    func_ovl2_800D8EB8(fp);

    fp->cb_accessory = func_ovl3_80146FD4;
}

void func_ovl3_801472B0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl2_800DEE54);
}

const Vec3f Fighter_FireFlowerShoot_Ammo_Offset = { FTCOMMON_FIREFLOWERSHOOT_AMMO_SPAWN_OFF_X, FTCOMMON_FIREFLOWERSHOOT_AMMO_SPAWN_OFF_Y, FTCOMMON_FIREFLOWERSHOOT_AMMO_SPAWN_OFF_Z };

void func_ovl3_801472D4(Fighter_Struct *fp, s32 ammo_sub)
{
    Article_Struct *ap = ArticleGetStruct(fp->item_hold);
    Vec3f flame_spawn_offset = Fighter_FireFlowerShoot_Ammo_Offset;
    f32 size_mul;
    s32 flame_vel_index;

    if (ap->at_multi >= ammo_sub)
    {
        size_mul = 1.0F / fp->attributes->size_mul;

        flame_spawn_offset.x *= size_mul;
        flame_spawn_offset.y *= size_mul;
        flame_spawn_offset.z *= size_mul;

        func_ovl2_800EDF24(fp->joint[fp->attributes->joint_itemhold_light], &flame_spawn_offset);

        if (fp->status_vars.common.fireflower.flame_vel_index >= FTCOMMON_FIREFLOWERSHOOT_AMMO_INDEX_LOOP)
        {
            flame_vel_index = FTCOMMON_FIREFLOWERSHOOT_AMMO_INDEX_MAX - fp->status_vars.common.fireflower.flame_vel_index;
        }
        else flame_vel_index = fp->status_vars.common.fireflower.flame_vel_index;

        func_ovl3_8017604C(fp->fighter_gobj, &flame_spawn_offset, flame_vel_index, ammo_sub);
        func_ovl2_800E806C(fp, 6, 0);
    }
    fp->status_vars.common.fireflower.ammo_fire_count++;

    if (fp->status_vars.common.fireflower.ammo_fire_count > (U16_MAX + 1))
    {
        fp->status_vars.common.fireflower.ammo_fire_count = (U16_MAX + 1);
    }
    fp->status_vars.common.fireflower.flame_vel_index++;

    if (fp->status_vars.common.fireflower.flame_vel_index >= FTCOMMON_FIREFLOWERSHOOT_AMMO_INDEX_MAX)
    {
        fp->status_vars.common.fireflower.flame_vel_index = 0;

        func_ovl2_800EA5E8(fp, 0x36);
        func_ovl2_800EA778(fp, fp->flags_lw.halfword);
        func_ovl2_800EA7B0(fp, 0);
    }
}

const Vec3f Fighter_FireFlowerShoot_HaveAmmo_Dust_Offset = { 60.0F, 100.0F, 0.0F };
const Vec3f Fighter_FireFlowerShoot_NoAmmo_Dust_Offset   = { 0.0F, 0.0F, -180.0F };
const Vec3f Fighter_FireFlowerShoot_Spark_Offset         = { 0.0F, 80.0F,   0.0F };
const Vec3f Fighter_FireFlowerShoot_Spark_Scatter        = { 90.0F, 90.0F, 90.0F };
const Vec3f Fighter_FireFlowerShoot_Kickup_Offset        = { 0.0F, 0.0F, -180.0F };

void func_ovl3_80147434(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Article_Struct *ap;
    s32 ammo_sub;
    Vec3f gfx_haveammo_offset;
    Vec3f gfx_noammo_offset;
    Vec3f gfx_spark_offset;
    Vec3f gfx_spark_scatter;
    Vec3f gfx_dust_offset;

    if (!(fp->input.pl.button_hold & fp->input.button_mask_a))
    {
        fp->status_vars.common.fireflower.is_release = TRUE;
    }
    if (fp->status_vars.common.fireflower.release_lag < FTCOMMON_FIREFLOWERSHOOT_RELEASE_LAG)
    {
        fp->status_vars.common.fireflower.release_lag++;
    }
    if ((fp->status_vars.common.fireflower.release_lag < FTCOMMON_FIREFLOWERSHOOT_RELEASE_LAG) && (fp->input.button_press & fp->input.button_mask_a))
    {
        fp->status_vars.common.fireflower.release_lag = 0;
    }
    if (fp->item_hold != NULL)
    {
        if (fp->command_vars.flags.flag0 != 0)
        {
            ap = ArticleGetStruct(fp->item_hold);

            ammo_sub = (fp->status_vars.common.fireflower.ammo_fire_count == 0) ? 2 : 1;

            fp->status_vars.common.fireflower.gfx_spawn_int--;

            if (fp->status_vars.common.fireflower.gfx_spawn_int == 0)
            {
                fp->status_vars.common.fireflower.gfx_spawn_int = FTCOMMON_FIREFLOWERSHOOT_GFX_SPAWN_INT;

                if (ap->at_multi < ammo_sub)
                {
                    gfx_haveammo_offset = Fighter_FireFlowerShoot_HaveAmmo_Dust_Offset;

                    func_ovl2_800EABDC(fighter_gobj, 0xB, fp->attributes->joint_itemhold_light, &gfx_haveammo_offset, 0, -fp->lr, 1, 0);
                    func_800269C0(0x30U);
                }
                else
                {
                    gfx_noammo_offset = Fighter_FireFlowerShoot_NoAmmo_Dust_Offset;

                    func_ovl2_800EABDC(fighter_gobj, 0xB, 0, &gfx_noammo_offset, 0, fp->lr, 0, 0);
                    func_800269C0(0x1AU);
                }
            }
            fp->status_vars.common.fireflower.ammo_sub--;

            if (fp->status_vars.common.fireflower.ammo_sub == 0)
            {
                fp->status_vars.common.fireflower.ammo_sub = FTCOMMON_FIREFLOWERSHOOT_AMMO_INDEX_MAX;

                func_ovl3_801472D4(fp, ammo_sub);
            }
            if (fp->command_vars.flags.flag0 == 1)
            {
                if (ap->at_multi >= ammo_sub)
                {
                    gfx_spark_offset = Fighter_FireFlowerShoot_Spark_Offset;
                    gfx_spark_scatter = Fighter_FireFlowerShoot_Spark_Scatter;
                    gfx_dust_offset = Fighter_FireFlowerShoot_Kickup_Offset;

                    func_ovl2_800EABDC(fighter_gobj, 0x1F, fp->attributes->joint_itemhold_light, &gfx_spark_offset, &gfx_spark_scatter, fp->lr, 1, 0);
                    func_ovl2_800EABDC(fighter_gobj, 0x13, 0, &gfx_dust_offset, 0, fp->lr, 0, 0);
                }
                fp->command_vars.flags.flag0 = 2;

                GObjSetAnimSpeed(fighter_gobj, 0.0F);
            }
        }
        if ((fp->status_vars.common.fireflower.ammo_fire_count >= 5) && (fp->status_vars.common.fireflower.is_release != FALSE) && (fp->status_vars.common.fireflower.release_lag >= 20))
        {
            fp->command_vars.flags.flag0 = 0;

            GObjSetAnimSpeed(fighter_gobj, 1.0F);
        }
    }
}

void func_ovl3_8014772C(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_801477C8);
}

void func_ovl3_80147750(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80147774);
}

void func_ovl3_80147774(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_FireFlowerShoot, fighter_gobj->anim_frame, DObjGetStruct(fighter_gobj)->unk_dobj_0x78, 0U);

    fp->cb_accessory = func_ovl3_80147434;
}

void func_ovl3_801477C8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_FireFlowerShootAir, fighter_gobj->anim_frame, DObjGetStruct(fighter_gobj)->unk_dobj_0x78, 0U);
    func_ovl2_800D8EB8(fp);

    fp->cb_accessory = func_ovl3_80147434;
}

void func_ovl3_80147824(Fighter_Struct *fp)
{
    fp->status_vars.common.fireflower.flame_vel_index = 0;
    fp->status_vars.common.fireflower.ammo_sub = 1;
    fp->status_vars.common.fireflower.gfx_spawn_int = 1;
    fp->status_vars.common.fireflower.ammo_fire_count = 0;
    fp->status_vars.common.fireflower.is_release = FALSE;
    fp->status_vars.common.fireflower.release_lag = 0;
}

void func_ovl3_80147844(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Article_Struct *ap = ArticleGetStruct(fp->item_hold);
    s32 status_id;
    void (*cb_accessory)(GObj*);

    switch (ap->at_kind)
    {
    case At_Kind_L_Gun:
        status_id = ftStatus_Common_LGunShoot;
        cb_accessory = func_ovl3_80146FD4;
        break;

    case At_Kind_F_Flower:
        status_id = ftStatus_Common_FireFlowerShoot;
        cb_accessory = func_ovl3_80147434;
        break;
    }
    fp->command_vars.flags.flag0 = 0;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->cb_accessory = cb_accessory;

    func_ovl3_80147824(fp);
}

void func_ovl3_801478EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Article_Struct *ap = ArticleGetStruct(fp->item_hold);
    s32 status_id;
    void (*cb_accessory)(GObj*);

    switch (ap->at_kind)
    {
    case At_Kind_L_Gun:
        status_id = ftStatus_Common_LGunShootAir;
        cb_accessory = func_ovl3_80146FD4;
        break;

    case At_Kind_F_Flower:
        status_id = ftStatus_Common_FireFlowerShootAir;
        cb_accessory = func_ovl3_80147434;
        break;
    }
    fp->command_vars.flags.flag0 = 0;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    fp->cb_accessory = cb_accessory;

    func_ovl2_800D8EB8(fp);
    func_ovl3_80147824(fp);
}
