#include "ftyoshi.h"

void func_ovl3_8015E9B0(Fighter_Struct *fp, Vec3f *pos) // Start of Egg Throw code 
{
    pos->x = 0.0F;
    pos->y = 0.0F;
    pos->z = 0.0F;

    func_ovl2_800EDF24(fp->joint[FTYOSHI_EGG_THROW_JOINT], pos);
}

void func_ovl3_8015E9E0(Fighter_Struct *fp)
{
    Vec3f pos;

    if (fp->status_vars.yoshi.specialhi.egg_gobj != NULL)
    {
        func_ovl3_8015E9B0(fp, &pos);

        DObjGetStruct(fp->status_vars.yoshi.specialhi.egg_gobj)->translate = pos;

        DObjGetStruct(fp->status_vars.yoshi.specialhi.egg_gobj)->scale = fp->joint[FTYOSHI_EGG_THROW_JOINT]->scale;
    }
}

void func_ovl3_8015EA5C(GObj *fighter_gobj)
{
    Item_Struct *ip;
    Vec3f pos;
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag2 == 2)
    {
        fp->command_vars.flags.flag2 = 0;

        if (fp->status_vars.yoshi.specialhi.egg_gobj != NULL)
        {
            ip = itGetStruct(fp->status_vars.yoshi.specialhi.egg_gobj);

            ip->item_vars.egg_throw.is_throw = TRUE;
            ip->item_vars.egg_throw.throw_force = fp->status_vars.yoshi.specialhi.throw_force;
            ip->item_vars.egg_throw.stick_range = fp->input.pl.stick_range.x;

            func_ovl2_800DF09C(fp->status_vars.yoshi.specialhi.egg_gobj, fp->coll_data.p_translate, &fp->coll_data);

            fp->status_vars.yoshi.specialhi.egg_gobj = NULL;
        }
        fp->command_vars.flags.flag1 = 1;
    }

    else if (fp->command_vars.flags.flag2 == 1)
    {
        fp->command_vars.flags.flag2 = 0;

        func_ovl3_8015E9B0(fp, &pos);

        fp->status_vars.yoshi.specialhi.egg_gobj = func_ovl3_8016C498(fighter_gobj, &pos);
    }
}

void func_ovl3_8015EB0C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->input.pl.button_hold & fp->input.button_mask_b)
    {
        fp->status_vars.yoshi.specialhi.throw_force++;
    }
}

void func_ovl3_8015EB38(GObj *fighter_gobj)
{
    func_ovl3_8015EB0C(fighter_gobj);
    func_ovl3_8015EA5C(fighter_gobj);
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8013E1C8);
}

void func_ovl3_8015EB70(GObj *fighter_gobj)
{
    func_ovl3_8015EB0C(fighter_gobj);
    func_ovl3_8015EA5C(fighter_gobj);
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, ftCommon_Fall_SetStatus);
}

void func_ovl3_8015EBA8(GObj *fighter_gobj)
{
    func_ovl3_8015E9E0(ftGetStruct(fighter_gobj));
    func_ovl2_800D8BB4(fighter_gobj);
}

void func_ovl3_8015EBD4(GObj *fighter_gobj)
{
    func_ovl3_8015E9E0(ftGetStruct(fighter_gobj));
    func_ovl2_800D91EC(fighter_gobj);
}

void func_ovl3_8015EC00(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Yoshi_SpecialHi, fighter_gobj->anim_frame, 1.0F, 4U);

    fp->proc_damage = func_ovl3_8015E980;
}

void func_ovl3_8015EC00(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Yoshi_SpecialAirHi, fighter_gobj->anim_frame, 1.0F, 4U);

    fp->proc_damage = func_ovl3_8015E980;

    func_ovl2_800D8EB8(fp);
}

void func_ovl3_8015ECAC(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8015EC54);
}

void func_ovl3_8015ECD0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 != 0)
    {
        ftMapCollide_CheckGroundCliff(fighter_gobj, func_ovl3_8015EC00);
    }
    else func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015EC00);
}

void func_ovl3_8015ED18(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    fp->proc_damage = func_ovl3_8015E980;
    fp->command_vars.flags.flag2 = 0;
    fp->command_vars.flags.flag1 = 0;
    fp->status_vars.yoshi.specialhi.egg_gobj = NULL;
    fp->status_vars.yoshi.specialhi.throw_force = 0;
}

void jtgt_ovl3_8015ED3C(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Yoshi_SpecialHi, 0.0F, 1.0F, 0U);
    func_ovl3_8015ED18(fighter_gobj);
    ftAnim_Update(fighter_gobj);
}

void jtgt_ovl3_8015ED7C(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Yoshi_SpecialAirHi, 0.0F, 1.0F, 0U);
    func_ovl3_8015ED18(fighter_gobj);
    ftAnim_Update(fighter_gobj);
}
