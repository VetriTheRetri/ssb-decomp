#include "fighter.h"
#include "article.h"

void func_ovl3_80146C40(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->item_hold != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(fp->item_hold);

        if (ap->at_kind == At_Kind_Harisen)
        {
            func_ovl3_80175140(fp->item_hold, FTCOMMON_HARISENSWING_SCALE_HIT);

            fp->status_vars.common.itemswing.harisen_scale_reset_wait = FTCOMMON_HARISENSWING_SCALE_RESET_WAIT;
        }
    }
}

void func_ovl3_80146C98(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->item_hold != NULL)
    {
        if (fp->status_vars.common.itemswing.harisen_scale_reset_wait != 0)
        {
            fp->status_vars.common.itemswing.harisen_scale_reset_wait--;

            if (fp->status_vars.common.itemswing.harisen_scale_reset_wait == 0)
            {
                func_ovl3_80175140(fp->item_hold, 1.0F);
            }
        }
    }
    func_ovl2_800D94C4(fighter_gobj);
}

extern const Vec3f Fighter_StarRodSwing_Star_Offset = { 0.0F, 200.0F, 0.0F };
extern const Vec3f Fighter_StarRodSwing_Dust_Offset = { 0.0F, 200.0F, 0.0F };

void func_ovl3_80146CF4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Article_Struct *ap;
    f32 scale_mul;
    s32 unused;

    if (fp->item_hold != NULL)
    {
        if (fp->command_vars.flags.flag1 != 0)
        {
            ap = ArticleGetStruct(fp->item_hold);

            if (ap->at_multi != 0)
            {
                func_800269C0(fp->command_vars.flags.flag1);
            }
            else func_800269C0(0x42U);

            fp->command_vars.flags.flag1 = 0;
        }
    }
    if ((fp->item_hold != NULL) && (fp->command_vars.flags.flag0 != 0))
    {
        ap = ArticleGetStruct(fp->item_hold);

        if (ap->at_multi != 0)
        {
            Vec3f star_pos = Fighter_StarRodSwing_Star_Offset;

            scale_mul = 1.0F / fp->attributes->size_mul;

            star_pos.x *= scale_mul;
            star_pos.y *= scale_mul;
            star_pos.z *= scale_mul;

            func_ovl2_800EDF24(fp->joint[fp->attributes->joint_throw_light], &star_pos);

            func_ovl3_80178594(fighter_gobj, &star_pos, (fp->command_vars.flags.flag0 == 1) ? FALSE : TRUE);
        }
        else
        {
            Vec3f gfx_offset = Fighter_StarRodSwing_Dust_Offset;

            func_ovl2_800EABDC(fighter_gobj, 0xB, fp->attributes->joint_throw_light, &gfx_offset, 0, -fp->lr, 1, 0);
        }
        fp->command_vars.flags.flag0 = 0;
    }
    func_ovl2_800D94C4(fighter_gobj);
}

extern FighterItemSwing Fighter_ItemSwing_Desc[4];
extern s32 Fighter_ItemSwing_Status[4][4];

void func_ovl3_80146E94(GObj *fighter_gobj, s32 swing_type)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Article_Struct *ap = ArticleGetStruct(fp->item_hold);
    s32 swing_id;
    s32 status_id;
    f32 anim_speed;

    switch (ap->at_kind)
    {
    case At_Kind_Sword:
        swing_id = 0;
        break;

    case At_Kind_Bat:
        swing_id = 1;
        break;

    case At_Kind_Harisen:
        swing_id = 2;
        break;

    case At_Kind_StarRod:
        swing_id = 3;
        break;
    }
    status_id = Fighter_ItemSwing_Status[swing_id][swing_type];
    anim_speed = Fighter_ItemSwing_Desc[status_id].anim_speed * 0.01F;

    fp->command_vars.flags.flag0 = 0;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, anim_speed, 0U);
    ftAnim_Update(fighter_gobj);

    fp->cb_give_damage = func_ovl3_80146C40;

    fp->status_vars.common.itemswing.harisen_scale_reset_wait = 0;

    fp->command_vars.flags.flag1 = 0;
}