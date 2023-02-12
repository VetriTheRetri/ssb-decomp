#include <game/src/ft/chara/ftkirby/ftkirby.h>

void func_ovl3_801577A0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->fighter_vars.kirby.copydonkey_charge_level = 0;
}

void func_ovl3_801577AC(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80157BB0);
}

void func_ovl3_801577D0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_80157BEC);
}

void func_ovl3_801577F4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.button_press & (fp->input.button_mask_b | fp->input.button_mask_a))
    {
        fp->status_vars.kirby.copydonkey_specialn.is_release = TRUE;
    }
}

void func_ovl3_80157824(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_801578C0);
}

void func_ovl3_80157848(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015786C);
}

void func_ovl3_8015786C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyDonkey_SpecialNStart, fighter_gobj->anim_frame, 1.0F, 2U);

    fp->cb_take_damage = func_ovl3_801577A0;
}

void func_ovl3_801578C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyDonkey_SpecialAirNStart, fighter_gobj->anim_frame, 1.0F, 2U);

    fp->cb_take_damage = func_ovl3_801577A0;

    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80157918(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fighter_gobj->anim_frame >= 0.0F) && (fighter_gobj->anim_frame < JObjGetStruct(fighter_gobj)->anim_rate))
    {
        if (fp->status_vars.kirby.copydonkey_specialn.is_charging != FALSE)
        {
            if (fp->fighter_vars.kirby.copydonkey_charge_level < FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_MAX)
            {
                fp->fighter_vars.kirby.copydonkey_charge_level++;

                if (fp->fighter_vars.kirby.copydonkey_charge_level == FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_MAX)
                {
                    func_8000BB04(fighter_gobj, FTKIRBY_COPYDONKEY_GIANTPUNCH_CHRAGE_ANIM_SPEED);

                    func_ovl2_800E9814(fighter_gobj, FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_COLANIM_ID, 0);

                    fp->status_vars.kirby.copydonkey_specialn.is_cancel = TRUE;
                }
            }
        }
        if (fp->status_vars.kirby.copydonkey_specialn.is_cancel != FALSE)
        {
            func_ovl2_800DEE54(fighter_gobj);
        }
        else if (fp->status_vars.kirby.copydonkey_specialn.is_release != FALSE)
        {
            if (fp->ground_or_air == air)
            {
                func_ovl3_80157E28(fighter_gobj);
            }
            else func_ovl3_80157DAC(fighter_gobj);
        }
        else fp->status_vars.kirby.copydonkey_specialn.is_charging = TRUE;
    }
}

void func_ovl3_80157A18(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ground_or_air != ground) || (func_ovl3_8014935C(fighter_gobj) == FALSE))
    {
        if (fp->input.button_press & (fp->input.button_mask_b | fp->input.button_mask_a))
        {
            fp->status_vars.kirby.copydonkey_specialn.is_release = TRUE;
        }
        if (fp->input.button_press & fp->input.button_mask_z)
        {
            fp->status_vars.kirby.copydonkey_specialn.is_cancel = TRUE;
        }
    }
}

void func_ovl3_80157A8C(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80157B5C);
}

void func_ovl3_80157AB0(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80157B14);
}

void func_ovl3_80157AD4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_take_damage = func_ovl3_801577A0;

    if (fp->fighter_vars.kirby.copydonkey_charge_level == FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_MAX)
    {
        func_8000BB04(fighter_gobj, FTKIRBY_COPYDONKEY_GIANTPUNCH_CHRAGE_ANIM_SPEED);
    }
}

void func_ovl3_80157B14(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyDonkey_SpecialNLoop, fighter_gobj->anim_frame, 1.0F, 0x4002U);
    func_ovl3_80157AD4(fighter_gobj);
}

void func_ovl3_80157B5C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyDonkey_SpecialAirNLoop, fighter_gobj->anim_frame, 1.0F, 0x4002U);
    func_ovl3_80157AD4(fighter_gobj);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80157BB0(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyDonkey_SpecialNLoop, 0.0F, 1.0F, 2U);
    func_ovl3_80157AD4(fighter_gobj);
}

void func_ovl3_80157BEC(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyDonkey_SpecialAirNLoop, 0.0F, 1.0F, 0xAU);
    func_ovl3_80157AD4(fighter_gobj);
}

void func_ovl3_80157C28(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800DEE54(fighter_gobj);
    }

    else if ((fp->status_info.status_id == ftStatus_Kirby_CopyDonkey_SpecialNEnd) || (fp->status_info.status_id == ftStatus_Kirby_CopyDonkey_SpecialAirNEnd))
    {
        s32 i;

        for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
        {
            Fighter_Hit *ft_hit = &fp->fighter_hit[i];

            if (ft_hit->update_state == ftHit_UpdateState_New)
            {
                ft_hit->damage += fp->status_vars.kirby.copydonkey_specialn.charge_level * FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_DAMAGE_MUL;
            }
        }
    }
}

void func_ovl3_80157D18(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80157D3C);
}

void func_ovl3_80157D3C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    func_ovl2_800DEE98(fp);

    status_id = (fp->status_info.status_id == ftStatus_Kirby_CopyDonkey_SpecialAirNEnd) ? ftStatus_Kirby_CopyDonkey_SpecialNEnd : ftStatus_Kirby_CopyDonkey_SpecialNFull;

    func_ovl2_800E6F24(fighter_gobj, status_id, fighter_gobj->anim_frame, 1.0F, 3U);
}

void func_ovl3_80157D98(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.kirby.copydonkey_specialn.charge_level = fp->fighter_vars.kirby.copydonkey_charge_level;

    fp->fighter_vars.kirby.copydonkey_charge_level = 0;
}

void func_ovl3_80157DAC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    s32 status_id = (fp->fighter_vars.kirby.copydonkey_charge_level == FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_MAX) ? ftStatus_Kirby_CopyDonkey_SpecialNFull : ftStatus_Kirby_CopyDonkey_SpecialNEnd;

    func_ovl2_800E6F24(fighter_gobj, status_id, 0.0F, 1.0F, 2U);

    fp->phys_info.vel_ground.x = fp->fighter_vars.kirby.copydonkey_charge_level * FTKIRBY_COPYDONKEY_GIANTPUNCH_VEL_MUL;

    func_ovl3_80157D98(fighter_gobj);
}

void func_ovl3_80157E28(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    s32 status_id = (fp->fighter_vars.kirby.copydonkey_charge_level == FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_MAX) ? ftStatus_Kirby_CopyDonkey_SpecialAirNFull : ftStatus_Kirby_CopyDonkey_SpecialAirNEnd;

    func_ovl2_800E6F24(fighter_gobj, status_id, 0.0F, 1.0F, 0xAU);

    func_ovl3_80157D98(fighter_gobj);
}

void func_ovl3_80157E7C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.kirby.copydonkey_specialn.is_release = (fp->fighter_vars.kirby.copydonkey_charge_level == FTKIRBY_COPYDONKEY_GIANTPUNCH_CHARGE_MAX) ? TRUE : FALSE;

    fp->status_vars.kirby.copydonkey_specialn.is_charging = FALSE;
    fp->status_vars.kirby.copydonkey_specialn.is_cancel = FALSE;
}

void jtgt_ovl3_80157EAC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyDonkey_SpecialNStart, 0.0F, 1.0F, 0U);

    fp->cb_take_damage = func_ovl3_801577A0;

    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80157E7C(fighter_gobj);
}

void jtgt_ovl3_80157F04(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyDonkey_SpecialAirNStart, 0.0F, 1.0F, 8U);

    fp->cb_take_damage = func_ovl3_801577A0;

    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80157E7C(fighter_gobj);
}
