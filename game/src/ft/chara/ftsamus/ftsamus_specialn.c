#include <game/src/ft/chara/ftsamus/ftsamus.h>

void func_ovl3_8015D300(Fighter_Struct *fp)
{
    if (fp->status_vars.samus.specialn.charge_gobj != NULL)
    {
        func_ovl3_8016800C(fp->status_vars.samus.specialn.charge_gobj);

        fp->status_vars.samus.specialn.charge_gobj = NULL;
    }
}

void func_ovl3_8015D338(GObj *fighter_gobj) // Runs when Samus is hit out of Charge Shot
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->fighter_vars.samus.charge_level = 0;

    func_ovl3_8015D300(fp);
}

void func_ovl3_8015D35C(Fighter_Struct *fp, Vec3f *pos)
{
    pos->y = 0.0F;
    pos->z = 0.0F;
    pos->x = FTSAMUS_CHARGE_OFF_X;

    func_ovl2_800EDF24(fp->joint[FTSAMUS_CHARGE_JOINT], pos);
}

void func_ovl3_8015D394(Fighter_Struct *fp)
{
    Vec3f pos;

    if (fp->status_vars.samus.specialn.charge_gobj != NULL)
    {
        func_ovl3_8015D35C(fp, &pos);

        DObjGetStruct(fp->status_vars.samus.specialn.charge_gobj)->translate = pos;
    }
}

void func_ovl3_8015D3EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        if (fp->ground_or_air == air)
        {
            func_ovl3_8015DAA8(fighter_gobj);
        }
        else if (fp->status_vars.samus.specialn.is_release != FALSE)
        {
            func_ovl3_8015DA60(fighter_gobj);
        }
        else func_ovl3_8015D734(fighter_gobj);
    }
}

void func_ovl3_8015D464(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->input.pl.button_tap & fp->input.button_mask_b) || (fp->input.pl.button_tap & fp->input.button_mask_a))
    {
        fp->status_vars.samus.specialn.is_release = TRUE;
    }
}

void func_ovl3_8015D49C(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015D540);
}

void func_ovl3_8015D4C0(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015D4E4);
}

void func_ovl3_8015D4E4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);

    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialNStart, fighter_gobj->anim_frame, fp->joint[0]->unk_dobj_0x78, 2U);

    fp->proc_damage = func_ovl3_8015D338;
}

void func_ovl3_8015D540(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialAirNStart, fighter_gobj->anim_frame, fp->joint[0]->unk_dobj_0x78, 2U);
    func_ovl2_800D8EB8(fp);

    fp->proc_damage = func_ovl3_8015D338;

    fp->status_vars.samus.specialn.is_release = TRUE;
}

void func_ovl3_8015D5AC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.samus.specialn.charge_int--;

    if (fp->status_vars.samus.specialn.charge_int == 0)
    {
        fp->status_vars.samus.specialn.charge_int = FTSAMUS_CHARGE_INT;

        if (fp->fighter_vars.samus.charge_level <= (FTSAMUS_CHARGE_MAX - 1))
        {
            fp->fighter_vars.samus.charge_level++;

            if (fp->fighter_vars.samus.charge_level == FTSAMUS_CHARGE_MAX)
            {
                func_ovl2_800E9814(fighter_gobj, 6, 0);
                func_ovl3_8015D300(fp);
                func_ovl3_8013E1C8(fighter_gobj);
            }

            else if (fp->status_vars.samus.specialn.charge_gobj != NULL)
            {
                Item_Struct *ip = ItemGetStruct(fp->status_vars.samus.specialn.charge_gobj);

                ip->item_vars.charge_shot.charge_size = fp->fighter_vars.samus.charge_level;
            }
        }
    }
}

void func_ovl3_8015D640(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 ret;

    if ((fp->input.pl.button_tap & fp->input.button_mask_b) || (fp->input.pl.button_tap & fp->input.button_mask_a))
    {
        func_ovl3_8015DA60(fighter_gobj);
        return;
    }

    ret = func_ovl3_801492F8(fp);

    if (ret != -1)
    {
        func_ovl3_8015D300(fp);
        func_ovl3_80149294(fighter_gobj, ret);
    }

    else if (fp->input.pl.button_tap & fp->input.button_mask_z)
    {
        func_ovl3_8015D300(fp);
        func_ovl3_8013E1C8(fighter_gobj);
    }
}

void func_ovl3_8015D700(GObj *fighter_gobj)
{
    func_ovl3_8015D394(FighterGetStruct(fighter_gobj));
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015DAA8);
}

void func_ovl3_8015D734(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialNLoop, 0.0F, 1.0F, 2U);

    fp->proc_damage = func_ovl3_8015D338;
    fp->status_vars.samus.specialn.charge_int = FTSAMUS_CHARGE_INT;

    func_ovl3_8015D35C(fp, &pos);
    fp->status_vars.samus.specialn.charge_gobj = func_ovl3_80168DDC(fighter_gobj, &pos, fp->fighter_vars.samus.charge_level, 0);
}

void func_ovl3_8015D7AC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Item_Struct *ip;
    f32 charge_recoil_x;
    f32 charge_recoil_y;

    if (fp->command_vars.flags.flag0 != FALSE)
    {
        fp->command_vars.flags.flag0 = FALSE;

        func_ovl3_8015D35C(fp, &pos);

        if (fp->status_vars.samus.specialn.charge_gobj != NULL)
        {
            ip = ItemGetStruct(fp->status_vars.samus.specialn.charge_gobj);
            ftCommon_StopLoopSFX(fp);

            DObjGetStruct(fp->status_vars.samus.specialn.charge_gobj)->translate = pos;

            ip->item_vars.charge_shot.is_full_charge = TRUE;
            ip->item_vars.charge_shot.charge_size = (s32)fp->fighter_vars.samus.charge_level;

            func_ovl2_800DF09C(fp->status_vars.samus.specialn.charge_gobj, fp->coll_data.p_translate, &fp->coll_data);

            ip->item_vars.charge_shot.owner_gobj = NULL;
            fp->status_vars.samus.specialn.charge_gobj = NULL;
        }
        else func_ovl3_80168DDC(fighter_gobj, &pos, fp->fighter_vars.samus.charge_level, 1);


        if (fp->ground_or_air == air)
        {
            charge_recoil_x = (f32)(fp->fighter_vars.samus.charge_level + 1);

            fp->phys_info.vel_air.x = (f32) (((FTSAMUS_CHARGE_RECOIL_MUL * charge_recoil_x) + FTSAMUS_CHARGE_RECOIL_BASE) * (f32)-fp->lr);

            charge_recoil_y = charge_recoil_x + FTSAMUS_CHARGE_RECOIL_ADD + ((f32)fp->fighter_vars.samus.charge_recoil * -FTSAMUS_CHARGE_RECOIL_BASE);

            if (fp->phys_info.vel_air.y < charge_recoil_y)
            {
                fp->phys_info.vel_air.y = charge_recoil_y;
            }
            fp->fighter_vars.samus.charge_recoil++;
        }
        else
        {
            fp->phys_info.vel_ground.x = (f32) -((FTSAMUS_CHARGE_RECOIL_MUL * (f32)(fp->fighter_vars.samus.charge_level + 1)) + FTSAMUS_CHARGE_RECOIL_BASE);
        }

        fp->fighter_vars.samus.charge_level = 0;
        fp->proc_damage = NULL;

    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_8015D968(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015DA04);
}

void func_ovl3_8015D98C(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015D9B0);
}

void func_ovl3_8015D9B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialNEnd, fighter_gobj->anim_frame, 1.0F, 2U);

    fp->proc_damage = func_ovl3_8015D338;
}

void func_ovl3_8015DA04(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialAirNEnd, fighter_gobj->anim_frame, 1.0F, 2U);
    func_ovl2_800D8EB8(fp);

    fp->proc_damage = func_ovl3_8015D338;
}

void func_ovl3_8015DA60(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialNEnd, 0.0F, 1.0F, 2U);

    fp->proc_damage = func_ovl3_8015D338;
}

void func_ovl3_8015DAA8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        ftMapCollide_SetAir(fp);
        func_ovl2_800D8EB8(fp);
    }
    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialAirNEnd, 0.0F, 1.0F, 2U);

    fp->proc_damage = func_ovl3_8015D338;
}

f32 func_ovl3_8015DB14(Fighter_Struct *fp)
{
    f32 ret = fp->fighter_vars.samus.charge_level / (f32) FTSAMUS_CHARGE_MAX;

    ret = (-0.16000003F) * ret + 1.0F;

    return ret;
}

void func_ovl3_8015DB4C(Fighter_Struct *fp)
{
    fp->proc_damage = func_ovl3_8015D338;
    fp->status_vars.samus.specialn.charge_gobj = NULL;
    fp->command_vars.flags.flag0 = FALSE;
}

void jtgt_ovl3_8015DB64(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialNStart, 0.0F, func_ovl3_8015DB14(fp), 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015DB4C(fp);

    fp->status_vars.samus.specialn.is_release = (fp->fighter_vars.samus.charge_level == FTSAMUS_CHARGE_MAX) ? TRUE : FALSE;
}

void jtgt_ovl3_8015DBDC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Samus_SpecialAirNStart, 0.0F, func_ovl3_8015DB14(fp), 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_8015DB4C(fp);

    fp->status_vars.samus.specialn.is_release = TRUE;
}
