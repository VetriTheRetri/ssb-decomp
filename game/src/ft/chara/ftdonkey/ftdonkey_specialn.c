#include "ftdonkey.h"

void func_ovl3_8015AF10(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->fighter_vars.donkey.charge_level = 0;
}

void func_ovl3_8015AF1C(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8015B320);
}

void func_ovl3_8015AF40(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8015B35C);
}

void func_ovl3_8015AF64(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.button_press & (fp->input.button_mask_b | fp->input.button_mask_a))
    {
        fp->status_vars.donkey.specialn.is_release = TRUE;
    }
}

void func_ovl3_8015AF94(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015B030);
}

void func_ovl3_8015AFB8(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015AFDC);
}

void func_ovl3_8015AFDC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Donkey_SpecialNStart, fighter_gobj->anim_frame, 1.0F, 2U);

    fp->cb_take_damage = func_ovl3_8015AF10;
}

void func_ovl3_8015B030(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Donkey_SpecialAirNStart, fighter_gobj->anim_frame, 1.0F, 2U);

    fp->cb_take_damage = func_ovl3_8015AF10;

    func_ovl2_800D8EB8(fp);
}

void func_ovl3_8015B088(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fighter_gobj->anim_frame >= 0.0F) && (fighter_gobj->anim_frame < JObjGetStruct(fighter_gobj)->anim_rate))
    {
        if (fp->status_vars.donkey.specialn.is_charging != FALSE)
        {
            if (fp->fighter_vars.donkey.charge_level < FTDONKEY_GIANTPUNCH_CHARGE_MAX)
            {
                fp->fighter_vars.donkey.charge_level++;

                if (fp->fighter_vars.donkey.charge_level == FTDONKEY_GIANTPUNCH_CHARGE_MAX)
                {
                    func_8000BB04(fighter_gobj, FTDONKEY_GIANTPUNCH_CHRAGE_ANIM_SPEED);

                    func_ovl2_800E9814(fighter_gobj, FTDONKEY_GIANTPUNCH_CHARGE_COLANIM_ID, 0);

                    fp->status_vars.donkey.specialn.is_cancel = TRUE;
                }
            }
        }
        if (fp->status_vars.donkey.specialn.is_cancel != FALSE)
        {
            func_ovl2_800DEE54(fighter_gobj);
        }
        else if (fp->status_vars.donkey.specialn.is_release != FALSE)
        {
            if (fp->ground_or_air == air)
            {
                func_ovl3_8015B598(fighter_gobj);
            }
            else func_ovl3_8015B51C(fighter_gobj);
        }
        else fp->status_vars.donkey.specialn.is_charging = TRUE;
    }
}

void func_ovl3_8015B188(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->ground_or_air != ground) || (func_ovl3_8014935C(fighter_gobj) == FALSE))
    {
        if (fp->input.button_press & (fp->input.button_mask_b | fp->input.button_mask_a))
        {
            fp->status_vars.donkey.specialn.is_release = TRUE;
        }
        if (fp->input.button_press & fp->input.button_mask_z)
        {
            fp->status_vars.donkey.specialn.is_cancel = TRUE;
        }
    }
}

void func_ovl3_8015B1FC(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015B2CC);
}

void func_ovl3_8015B220(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015B284);
}

void func_ovl3_8015B244(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_take_damage = func_ovl3_8015AF10;

    if (fp->fighter_vars.donkey.charge_level == FTDONKEY_GIANTPUNCH_CHARGE_MAX)
    {
        func_8000BB04(fighter_gobj, FTDONKEY_GIANTPUNCH_CHRAGE_ANIM_SPEED);
    }
}

void func_ovl3_8015B284(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Donkey_SpecialNLoop, fighter_gobj->anim_frame, 1.0F, 0x4002U);
    func_ovl3_8015B244(fighter_gobj);
}

void func_ovl3_8015B2CC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Donkey_SpecialAirNLoop, fighter_gobj->anim_frame, 1.0F, 0x4002U);
    func_ovl3_8015B244(fighter_gobj);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_8015B320(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Donkey_SpecialNLoop, 0.0F, 1.0F, 2U);
    func_ovl3_8015B244(fighter_gobj);
}

void func_ovl3_8015B35C(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Donkey_SpecialAirNLoop, 0.0F, 1.0F, 0xAU);
    func_ovl3_8015B244(fighter_gobj);
}

void func_ovl3_8015B398(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800DEE54(fighter_gobj);
    }

    else if ((fp->status_info.status_id == ftStatus_Donkey_SpecialNEnd) || (fp->status_info.status_id == ftStatus_Donkey_SpecialAirNEnd))
    {
        s32 i;

        for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
        {
            Fighter_Hit *ft_hit = &fp->fighter_hit[i];

            if (ft_hit->update_state == ftHit_UpdateState_New)
            {
                ft_hit->damage += fp->status_vars.donkey.specialn.charge_level * FTDONKEY_GIANTPUNCH_CHARGE_DAMAGE_MUL;
            }
        }
    }
}

void func_ovl3_8015B488(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015B4AC);
}

void func_ovl3_8015B4AC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 status_id;

    func_ovl2_800DEE98(fp);

    status_id = (fp->status_info.status_id == ftStatus_Donkey_SpecialAirNEnd) ? ftStatus_Donkey_SpecialNEnd : ftStatus_Donkey_SpecialNFull;

    func_ovl2_800E6F24(fighter_gobj, status_id, fighter_gobj->anim_frame, 1.0F, 3U);
}

void func_ovl3_8015B508(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.donkey.specialn.charge_level = fp->fighter_vars.donkey.charge_level;

    fp->fighter_vars.donkey.charge_level = 0;
}

void func_ovl3_8015B51C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    s32 status_id = (fp->fighter_vars.donkey.charge_level == FTDONKEY_GIANTPUNCH_CHARGE_MAX) ? ftStatus_Donkey_SpecialNFull : ftStatus_Donkey_SpecialNEnd;

    func_ovl2_800E6F24(fighter_gobj, status_id, 0.0F, 1.0F, 2U);

    fp->phys_info.vel_ground.x = fp->fighter_vars.donkey.charge_level * FTDONKEY_GIANTPUNCH_VEL_MUL;

    func_ovl3_8015B508(fighter_gobj);
}

void func_ovl3_8015B598(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    s32 status_id = (fp->fighter_vars.donkey.charge_level == FTDONKEY_GIANTPUNCH_CHARGE_MAX) ? ftStatus_Donkey_SpecialAirNFull : ftStatus_Donkey_SpecialAirNEnd;

    func_ovl2_800E6F24(fighter_gobj, status_id, 0.0F, 1.0F, 0xAU);

    func_ovl3_8015B508(fighter_gobj);
}

void func_ovl3_8015B5EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.donkey.specialn.is_release = (fp->fighter_vars.donkey.charge_level == FTDONKEY_GIANTPUNCH_CHARGE_MAX) ? TRUE : FALSE;

    fp->status_vars.donkey.specialn.is_charging = FALSE;
    fp->status_vars.donkey.specialn.is_cancel = FALSE;
}

void jtgt_ovl3_8015B61C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Donkey_SpecialNStart, 0.0F, 1.0F, 0U);

    fp->cb_take_damage = func_ovl3_8015AF10;

    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015B5EC(fighter_gobj);
}

void jtgt_ovl3_8015B674(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Donkey_SpecialAirNStart, 0.0F, 1.0F, 8U);

    fp->cb_take_damage = func_ovl3_8015AF10;

    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015B5EC(fighter_gobj);
}
