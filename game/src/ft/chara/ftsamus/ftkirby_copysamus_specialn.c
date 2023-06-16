#include <game/src/ft/chara/ftkirby/ftkirby.h>

void func_ovl3_80156E60(Fighter_Struct *fp)
{
    if (fp->status_vars.kirby.copysamus_specialn.charge_gobj != NULL)
    {
        wpMain_DestroyWeapon(fp->status_vars.kirby.copysamus_specialn.charge_gobj);

        fp->status_vars.kirby.copysamus_specialn.charge_gobj = NULL;
    }
}

void func_ovl3_80156E98(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->fighter_vars.kirby.copysamus_charge_level = 0;

    func_ovl3_80156E60(fp);
}

void func_ovl3_80156EBC(Fighter_Struct *fp, Vec3f *pos)
{
    pos->x = 0.0F;
    pos->y = FTKIRBY_COPYSAMUS_CHARGE_OFF_Y;
    pos->z = FTKIRBY_COPYSAMUS_CHARGE_OFF_Z;

    func_ovl2_800EDF24(fp->joint[FTKIRBY_COPYSAMUS_CHARGE_JOINT], pos);
}

void func_ovl3_80156EFC(Fighter_Struct *fp)
{
    Vec3f pos;

    if (fp->status_vars.kirby.copysamus_specialn.charge_gobj != NULL)
    {
        func_ovl3_80156EBC(fp, &pos);

        DObjGetStruct(fp->status_vars.kirby.copysamus_specialn.charge_gobj)->translate = pos;
    }
}

void func_ovl3_80156F54(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        if (fp->ground_or_air == air)
        {
            func_ovl3_80157610(fighter_gobj);
        }
        else if (fp->status_vars.kirby.copysamus_specialn.is_release != FALSE)
        {
            func_ovl3_801575C8(fighter_gobj);
        }
        else func_ovl3_8015729C(fighter_gobj);
    }
}

void func_ovl3_80156FCC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if ((fp->input.pl.button_tap & fp->input.button_mask_b) || (fp->input.pl.button_tap & fp->input.button_mask_a))
    {
        fp->status_vars.kirby.copysamus_specialn.is_release = TRUE;
    }
}

void func_ovl3_80157004(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_801570A8);
}

void func_ovl3_80157028(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015704C);
}

void func_ovl3_8015704C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftMap_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopySamus_SpecialNStart, fighter_gobj->anim_frame, fp->joint[ftParts_TopN_Joint]->unk_dobj_0x78, 2U);

    fp->proc_damage = func_ovl3_80156E98;
}

void func_ovl3_801570A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftMap_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopySamus_SpecialAirNStart, fighter_gobj->anim_frame, fp->joint[ftParts_TopN_Joint]->unk_dobj_0x78, 2U);
    func_ovl2_800D8EB8(fp);

    fp->proc_damage = func_ovl3_80156E98;

    fp->status_vars.kirby.copysamus_specialn.is_release = TRUE;
}

void func_ovl3_80157114(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->status_vars.kirby.copysamus_specialn.charge_int--;

    if (fp->status_vars.kirby.copysamus_specialn.charge_int == 0)
    {
        fp->status_vars.kirby.copysamus_specialn.charge_int = FTKIRBY_COPYSAMUS_CHARGE_INT;

        if (fp->fighter_vars.kirby.copysamus_charge_level <= (FTKIRBY_COPYSAMUS_CHARGE_MAX - 1))
        {
            fp->fighter_vars.kirby.copysamus_charge_level++;

            if (fp->fighter_vars.kirby.copysamus_charge_level == FTKIRBY_COPYSAMUS_CHARGE_MAX)
            {
                ftColor_CheckSetColAnimIndex(fighter_gobj, 6, 0);
                func_ovl3_80156E60(fp);
                ftCommon_Wait_SetStatus(fighter_gobj);
            }

            else if (fp->status_vars.kirby.copysamus_specialn.charge_gobj != NULL)
            {
                Weapon_Struct *ip = wpGetStruct(fp->status_vars.kirby.copysamus_specialn.charge_gobj);

                ip->item_vars.charge_shot.charge_size = fp->fighter_vars.kirby.copysamus_charge_level;
            }
        }
    }
}

void func_ovl3_801571A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    s32 status_id;

    if ((fp->input.pl.button_tap & fp->input.button_mask_b) || (fp->input.pl.button_tap & fp->input.button_mask_a))
    {
        func_ovl3_801575C8(fighter_gobj);
        return;
    }

    status_id = ftCommon_Escape_GetStatus(fp);

    if (status_id != -1)
    {
        func_ovl3_80156E60(fp);
        ftCommon_Escape_SetStatus(fighter_gobj, status_id);
    }

    else if (fp->input.pl.button_tap & fp->input.button_mask_z)
    {
        func_ovl3_8015D300(fp);
        ftCommon_Wait_SetStatus(fighter_gobj);
    }
}

void func_ovl3_80157268(GObj *fighter_gobj)
{
    func_ovl3_80156EFC(ftGetStruct(fighter_gobj));
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80157610);
}

void func_ovl3_8015729C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopySamus_SpecialNLoop, 0.0F, 1.0F, 2U);

    fp->proc_damage = func_ovl3_80156E98;
    fp->status_vars.samus.specialn.charge_int = FTKIRBY_COPYSAMUS_CHARGE_INT;

    func_ovl3_80156EBC(fp, &pos);
    fp->status_vars.kirby.copysamus_specialn.charge_gobj = func_ovl3_80168DDC(fighter_gobj, &pos, fp->fighter_vars.kirby.copysamus_charge_level, 0);
}

void func_ovl3_80157314(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    Vec3f pos;
    Weapon_Struct *ip;
    f32 charge_recoil_x;
    f32 charge_recoil_y;

    if (fp->command_vars.flags.flag0 != FALSE)
    {
        fp->command_vars.flags.flag0 = FALSE;

        func_ovl3_80156EBC(fp, &pos);

        if (fp->status_vars.kirby.copysamus_specialn.charge_gobj != NULL)
        {
            ip = wpGetStruct(fp->status_vars.kirby.copysamus_specialn.charge_gobj);
            ftCommon_StopLoopSFX(fp);

            DObjGetStruct(fp->status_vars.kirby.copysamus_specialn.charge_gobj)->translate = pos;

            ip->item_vars.charge_shot.is_full_charge = TRUE;
            ip->item_vars.charge_shot.charge_size = (s32)fp->fighter_vars.kirby.copysamus_charge_level;

            func_ovl2_800DF09C(fp->status_vars.kirby.copysamus_specialn.charge_gobj, fp->coll_data.p_translate, &fp->coll_data);

            ip->item_vars.charge_shot.owner_gobj = NULL;
            fp->status_vars.kirby.copysamus_specialn.charge_gobj = NULL;
        }
        else func_ovl3_80168DDC(fighter_gobj, &pos, fp->fighter_vars.kirby.copysamus_charge_level, 1);


        if (fp->ground_or_air == air)
        {
            charge_recoil_x = (f32)(fp->fighter_vars.kirby.copysamus_charge_level + 1);

            fp->phys_info.vel_air.x = (f32)(((FTKIRBY_COPYSAMUS_CHARGE_RECOIL_MUL * charge_recoil_x) + FTKIRBY_COPYSAMUS_CHARGE_RECOIL_BASE) * (f32)-fp->lr);

            charge_recoil_y = charge_recoil_x + FTKIRBY_COPYSAMUS_CHARGE_RECOIL_ADD + ((f32)fp->fighter_vars.kirby.copysamus_charge_recoil * -FTKIRBY_COPYSAMUS_CHARGE_RECOIL_BASE);

            if (fp->phys_info.vel_air.y < charge_recoil_y)
            {
                fp->phys_info.vel_air.y = charge_recoil_y;
            }
            fp->fighter_vars.kirby.copysamus_charge_recoil++;
        }
        else
        {
            fp->phys_info.vel_ground.x = (f32)-((FTKIRBY_COPYSAMUS_CHARGE_RECOIL_MUL * (f32)(fp->fighter_vars.kirby.copysamus_charge_level + 1)) + FTKIRBY_COPYSAMUS_CHARGE_RECOIL_BASE);
        }

        fp->fighter_vars.kirby.copysamus_charge_level = 0;
        fp->proc_damage = NULL;

    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_801574D0(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015756C);
}

void func_ovl3_801574F4(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80157518);
}

void func_ovl3_80157518(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftMap_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopySamus_SpecialNEnd, fighter_gobj->anim_frame, 1.0F, 2U);

    fp->proc_damage = func_ovl3_80156E98;
}

void func_ovl3_8015756C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftMap_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopySamus_SpecialAirNEnd, fighter_gobj->anim_frame, 1.0F, 2U);
    func_ovl2_800D8EB8(fp);

    fp->proc_damage = func_ovl3_80156E98;
}

void func_ovl3_801575C8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopySamus_SpecialNEnd, 0.0F, 1.0F, 2U);

    fp->proc_damage = func_ovl3_80156E98;
}

void func_ovl3_80157610(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        ftMap_SetAir(fp);
        func_ovl2_800D8EB8(fp);
    }
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopySamus_SpecialAirNEnd, 0.0F, 1.F, 2U);

    fp->proc_damage = func_ovl3_80156E98;
}

f32 func_ovl3_8015767C(Fighter_Struct *fp)
{
    f32 ret = fp->fighter_vars.kirby.copysamus_charge_level / (f32) FTKIRBY_COPYSAMUS_CHARGE_MAX;

    ret = (-0.16000003F) * ret + 1.0F;

    return ret;
}

void func_ovl3_801576B4(Fighter_Struct *fp)
{
    fp->proc_damage = func_ovl3_80156E98;
    fp->status_vars.kirby.copysamus_specialn.charge_gobj = NULL;
    fp->command_vars.flags.flag0 = 0;
}

void jtgt_ovl3_801576CC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopySamus_SpecialNStart, 0.0f, func_ovl3_8015767C(fp), 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801576B4(fp);

    fp->status_vars.kirby.copysamus_specialn.is_release = (fp->fighter_vars.kirby.copysamus_charge_level == FTKIRBY_COPYSAMUS_CHARGE_MAX) ? TRUE : FALSE;
}

void jtgt_ovl3_80157744(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_CopySamus_SpecialAirNStart, 0.0F, func_ovl3_8015767C(fp), 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801576B4(fp);

    fp->status_vars.kirby.copysamus_specialn.is_release = TRUE;
}
