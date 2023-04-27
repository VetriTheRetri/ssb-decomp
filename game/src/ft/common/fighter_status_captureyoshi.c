#include "fighter.h"
#include "ftyoshi.h"
#include "article.h"

void func_ovl3_8014C770(void) // Unused
{
	return;
}

void func_ovl3_8014C778(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    func_ovl3_8014A5F0(fighter_gobj, &pos, &DObjGetStruct(fighter_gobj)->rotate);

    DObjGetStruct(fighter_gobj)->translate.x = pos.x;
    DObjGetStruct(fighter_gobj)->translate.z = pos.z;

    if (fp->status_info.status_id == ftStatus_Common_CaptureYoshi)
    {
        if (fp->status_vars.common.captureyoshi.stage == 3)
        {
            func_ovl3_8014CF20(fighter_gobj);
        }
        else if (fp->status_vars.common.captureyoshi.stage == 1)
        {
            fp->status_vars.common.captureyoshi.stage = 2;

            fp->is_invisible = fp->x18E_flag_b0 = TRUE;

            func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Intangible);
        }
    }
}

void func_ovl3_8014C83C(GObj *fighter_gobj, GObj *capture_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp;

    func_ovl2_800E823C(fighter_gobj);

    if ((this_fp->item_hold != NULL) && !(ArticleGetStruct(this_fp->item_hold)->is_light_throw))
    {
        Vec3f vel;

        vel.x = vel.y = vel.z = 0.0F;

        func_ovl3_80172AEC(this_fp->item_hold, &vel, 1.0F);
    }
    if (this_fp->catch_gobj != NULL)
    {
        func_ovl3_8014B330(this_fp->catch_gobj);

        this_fp->catch_gobj = NULL;
    }
    else if (this_fp->capture_gobj != NULL)
    {
        func_ovl3_8014AECC(this_fp->capture_gobj, fighter_gobj);
    }
    this_fp->x192_flag_b3 = FALSE;

    this_fp->capture_gobj = capture_gobj;

    capture_fp = FighterGetStruct(capture_gobj);

    this_fp->lr = -capture_fp->lr;

    func_ovl2_800DEEC8(this_fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_CaptureYoshi, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    this_fp->status_vars.common.captureyoshi.stage = 0;
    this_fp->status_vars.common.captureyoshi.breakout_wait = 0;

    func_ovl2_800E8098(this_fp, 0x3FU);
    func_ovl2_800D9444(fighter_gobj);
    func_ovl3_8014C778(fighter_gobj);
    func_ovl2_800DE348(fighter_gobj);
}

void func_ovl3_8014C958(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.captureyoshi.effect_gobj == NULL)
    {
        fp->status_vars.common.captureyoshi.effect_gobj = func_ovl2_80103060(fighter_gobj);

        if (fp->status_vars.common.captureyoshi.effect_gobj != NULL)
        {
            fp->is_statupdate_stop_gfx = TRUE;
        }
    }
}

void func_ovl3_8014C9A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    bool32 is_escape = FALSE;

    if (fp->status_vars.common.captureyoshi.unk_0x9 == TRUE)
    {
        is_escape = TRUE;

        if (fp->status_vars.common.captureyoshi.effect_gobj != NULL)
        {
            func_ovl2_800E9C3C(fighter_gobj);

            fp->status_vars.common.captureyoshi.effect_gobj = NULL;
        }
    }
    else
    {
        func_ovl3_8014C958(fighter_gobj);

        if (fp->status_vars.common.captureyoshi.effect_gobj != NULL)
        {
            Effect_Struct *ep = EffectGetStruct(fp->status_vars.common.captureyoshi.effect_gobj);

            if ((ep->lifetime == 1) && (fp->status_vars.common.captureyoshi.effect_gobj->anim_frame <= 0.0F))
            {
                is_escape = TRUE;
            }
        }
        else if (fp->command_vars.flags.flag0 == 1U)
        {
            if (fp->status_vars.common.captureyoshi.breakout_wait-- <= 0)
            {
                is_escape = TRUE;
            }
        }
    }
    if (is_escape == TRUE)
    {
        Vec3f pos = DObjGetStruct(fighter_gobj)->translate;

        pos.z = 0.0F;

        func_ovl2_80103A88(&pos);
        func_ovl2_801041A0(&pos);
        func_800269C0(0x101U);

        fp->phys_info.vel_air.y = FTCOMMON_YOSHIEGG_ESCAPE_VEL_Y;
        fp->phys_info.vel_air.z = 0.0F;
        fp->phys_info.vel_air.x = 0.0F;

        DObjGetStruct(fighter_gobj)->translate.y += FTCOMMON_YOSHIEGG_ESCAPE_OFF_Y;

        func_ovl2_800DEEC8(fp);
        ftStatus_Update(fighter_gobj, ftStatus_Common_Fall, 0.0F, 1.0F, 0x1000U);
        func_ovl2_800EA948(fp, 0xC);
    }
}

void func_ovl3_8014CB24(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.captureyoshi.effect_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(fp->status_vars.common.captureyoshi.effect_gobj)->next;

        if (fp->ground_or_air == ground)
        {
            if (ABS(fp->input.stick_range.y) >= FTCOMMON_YOSHIEGG_WIGGLE_STICK_RANGE_MIN)
            {
                joint->translate.y = ((fp->input.stick_range.y < 0) ? -1 : 1) * FTCOMMON_YOSHIEGG_WIGGLE_GFX_RANGE_XY;
            }
            else joint->translate.y = 0.0F;

            if (ABS(fp->input.stick_range.x) >= FTCOMMON_YOSHIEGG_WIGGLE_STICK_RANGE_MIN)
            {
                joint->translate.x = ((fp->input.stick_range.x < 0) ? -1 : 1) * FTCOMMON_YOSHIEGG_WIGGLE_GFX_RANGE_XY;
            }
            else joint->translate.x = 0.0F;
        }
        else
        {
            joint->translate.x = 0.0F;
            joint->translate.y = 0.0F;
        }
    }
}

void func_ovl3_8014CC0C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag0 == 0)
    {
        s32 breakout_wait = fp->breakout_wait;

        if (func_ovl3_8014E400(fp) == TRUE)
        {
            if (fp->status_vars.common.captureyoshi.effect_gobj != NULL)
            {
                GObjSetAnimSpeed(fp->status_vars.common.captureyoshi.effect_gobj, FTCOMMON_YOSHIEGG_WIGGLE_ANIM_SPEED);
            }
        }
        else if (fp->status_vars.common.captureyoshi.effect_gobj != NULL)
        {
            GObjSetAnimSpeed(fp->status_vars.common.captureyoshi.effect_gobj, 1.0F);
        }

        fp->status_vars.common.captureyoshi.breakout_wait -= ((breakout_wait - fp->breakout_wait) * 12);

        if (fp->status_vars.common.captureyoshi.breakout_wait-- <= 0)
        {
            fp->command_vars.flags.flag0 = 1;
            fp->status_vars.common.captureyoshi.breakout_wait = FTCOMMON_YOSHIEGG_ESCAPE_WAIT_DEFAULT;
        }
    }
    if (fp->command_vars.flags.flag0 == 1)
    {
        if (fp->status_vars.common.captureyoshi.effect_gobj != NULL)
        {
            Effect_Struct *ep = EffectGetStruct(fp->status_vars.common.captureyoshi.effect_gobj);

            ep->unk_ef_0x1C = 1;
        }
    }
    if (fp->ground_or_air == ground)
    {
        func_ovl2_800D8BB4(fighter_gobj);
    }
    else jtgt_ovl2_800D9160(fighter_gobj);
}

void func_ovl3_8014CD24(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
        {
            fp->ground_or_air = air;
        }
    }
    else if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        fp->ground_or_air = ground;
    }
}

void func_ovl3_8014CD7C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag0 == 0)
    {
        fp->status_vars.common.captureyoshi.breakout_wait -= ((2.0F * fp->damage_taken_recent) / 0.5F);
    }
    if ((fp->unk_ft_0x820 == 4) && (fp->unk_ft_0x824 == 0))
    {
        fp->status_vars.common.captureyoshi.breakout_wait = 0;
        fp->status_vars.common.captureyoshi.unk_0x9 = 1;
    }
    fp->unk_ft_0x814 = 4;
}

ftYoshiEggDesc Fighter_YoshiEgg_HurtDesc[Ft_Kind_EnumMax] =
{
    { 2.0F, { 0.0F, 157.0F, 0.0F }, { 180.0F, 180.0F, 180.0F } },   // Mario
    { 1.9F, { 0.0F, 155.0F, 0.0F }, { 171.0F, 171.0F, 171.0F } },   // Fox
    { 3.5F, { 0.0F, 230.0F, 0.0F }, { 245.0F, 245.0F, 245.0F } },   // Donkey Kong
    { 2.2F, { 0.0F, 163.0F, 0.0F }, { 198.0F, 198.0F, 198.0F } },   // Samus
    { 2.2F, { 0.0F, 160.0F, 0.0F }, { 188.0F, 188.0F, 188.0F } },   // Luigi
    { 2.0F, { 0.0F, 133.0F, 0.0F }, { 148.0F, 148.0F, 148.0F } },   // Link
    { 2.5F, { 0.0F, 175.0F, 0.0F }, { 210.0F, 210.0F, 210.0F } },   // Yoshi
    { 2.2F, { 0.0F, 156.0F, 0.0F }, { 198.0F, 198.0F, 198.0F } },   // Captain Falcon
    { 1.8F, { 0.0F, 132.0F, 0.0F }, { 164.0F, 164.0F, 164.0F } },   // Kirby
    { 1.8F, { 0.0F, 144.0F, 0.0F }, { 165.0F, 165.0F, 165.0F } },   // Pikachu
    { 2.0F, { 0.0F, 144.0F, 0.0F }, { 162.0F, 162.0F, 162.0F } },   // Jigglypuff
    { 1.8F, { 0.0F, 160.0F, 0.0F }, { 168.0F, 168.0F, 168.0F } },   // Ness
    { 2.0F, { 0.0F, 157.0F, 0.0F }, { 180.0F, 180.0F, 180.0F } },   // Master Hand
    { 2.0F, { 0.0F, 157.0F, 0.0F }, { 180.0F, 180.0F, 180.0F } },   // Metal Mario
    { 2.0F, { 0.0F, 157.0F, 0.0F }, { 180.0F, 180.0F, 180.0F } },   // Poly Mario
    { 1.9F, { 0.0F, 155.0F, 0.0F }, { 171.0F, 171.0F, 171.0F } },   // Poly Fox
    { 3.5F, { 0.0F, 230.0F, 0.0F }, { 245.0F, 245.0F, 245.0F } },   // Poly Donkey Kong
    { 2.2F, { 0.0F, 163.0F, 0.0F }, { 198.0F, 198.0F, 198.0F } },   // Poly Samus
    { 2.2F, { 0.0F, 160.0F, 0.0F }, { 188.0F, 188.0F, 188.0F } },   // Poly Luigi
    { 2.0F, { 0.0F, 133.0F, 0.0F }, { 148.0F, 148.0F, 148.0F } },   // Poly Link
    { 2.5F, { 0.0F, 175.0F, 0.0F }, { 210.0F, 210.0F, 210.0F } },   // Poly Yoshi
    { 2.2F, { 0.0F, 156.0F, 0.0F }, { 198.0F, 198.0F, 198.0F } },   // Poly Captain Falcon
    { 1.8F, { 0.0F, 132.0F, 0.0F }, { 164.0F, 164.0F, 164.0F } },   // Poly Kirby
    { 1.8F, { 0.0F, 144.0F, 0.0F }, { 165.0F, 165.0F, 165.0F } },   // Poly Pikachu
    { 2.0F, { 0.0F, 144.0F, 0.0F }, { 162.0F, 162.0F, 162.0F } },   // Poly Jigglypuff
    { 1.8F, { 0.0F, 160.0F, 0.0F }, { 168.0F, 168.0F, 168.0F } },   // Poly Ness
    { 5.7F, { 0.0F, 400.0F, 0.0F }, { 350.0F, 350.0F, 350.0F } }    // Giant Donkey Kong
};

void func_ovl3_8014CDFC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Fighter_Hurt *ft_hurt = &fp->fighter_hurt[0];
    ftYoshiEggDesc *egg = &Fighter_YoshiEgg_HurtDesc[fp->ft_kind];
    s32 i;

    ft_hurt->joint = fp->joint[0];
    ft_hurt->unk_ftht_0x4 = 0;
    ft_hurt->unk_ftht_0xC = 1;
    ft_hurt->unk_ftht_0x10 = 0;
    ft_hurt->offset = egg->offset;
    ft_hurt->size = egg->size;

    ft_hurt++;

    for (i = 1; i < ARRAY_COUNT(fp->fighter_hurt); i++, ft_hurt++)
    {
        if (ft_hurt->hit_status != gmHitCollision_HitStatus_None)
        {
            ft_hurt->hit_status = gmHitCollision_HitStatus_Intangible;
        }
    }
    fp->x18C_flag_b1 = TRUE;
    fp->x18C_flag_b2 = TRUE;
}

void func_ovl3_8014CF0C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.common.captureyoshi.breakout_wait = FTCOMMON_YOSHIEGG_ESCAPE_WAIT_MAX;

    fp->command_vars.flags.flag0 = 0;
}

void func_ovl3_8014CF20(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *capture_fp;

    if (this_fp->ground_or_air == ground)
    {
        func_ovl2_800DEEC8(this_fp);
    }
    this_fp->cb_status = func_ovl3_8014CF0C;

    func_ovl2_800DEEC8(this_fp);
    ftStatus_Update(fighter_gobj, ftStatus_Common_YoshiEgg, 0.0F, 0.0F, 0U);
    func_ovl2_800E8098(this_fp, 0x3FU);

    this_fp->is_invisible = TRUE;

    func_ovl3_8014CDFC(fighter_gobj);
    func_ovl3_8014E3EC(this_fp, 0x2EE);
    func_ovl3_80161CA0(this_fp->capture_gobj, fighter_gobj, 5);
    func_ovl2_800E7F7C(fighter_gobj, 1);

    capture_fp = FighterGetStruct(this_fp->capture_gobj);

    DObjGetStruct(fighter_gobj)->translate = DObjGetStruct(this_fp->capture_gobj)->translate;
    DObjGetStruct(fighter_gobj)->translate.x -= (capture_fp->lr * FTCOMMON_YOSHIEGG_LAY_OFF_X);
    DObjGetStruct(fighter_gobj)->translate.y += FTCOMMON_YOSHIEGG_LAY_OFF_Y;

    func_ovl2_800DF014(fighter_gobj, &DObjGetStruct(this_fp->capture_gobj)->translate, &FighterGetStruct(this_fp->capture_gobj)->coll_data);

    this_fp->phys_info.vel_air.x = -capture_fp->lr * FTCOMMON_YOSHIEGG_LAY_VEL_X;
    this_fp->phys_info.vel_air.y = FTCOMMON_YOSHIEGG_LAY_VEL_Y;
    this_fp->damage_mul = FTCOMMON_YOSHIEGG_DAMAGE_MUL;

    this_fp->capture_gobj = NULL;

    this_fp->unk_0x9F0 = func_ovl3_8014CD7C;

    this_fp->status_vars.common.captureyoshi.lr = capture_fp->lr;
    this_fp->status_vars.common.captureyoshi.effect_gobj = NULL;
    this_fp->status_vars.common.captureyoshi.unk_0x9 = 0;

    func_ovl2_800EAA2C(this_fp, capture_fp->port_id, 1, capture_fp->ft_kind, capture_fp->flags_lw.halfword, capture_fp->unk_0x290.halfword);
    func_ovl3_8014C958(fighter_gobj);
}
