#include "ftpikachu.h"
#include "gmground.h"

void func_ovl3_80151DB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f vel;

    pos.x = 0.0F;
    pos.y = 0.0F;
    pos.z = 0.0F;

    func_ovl2_800EDF24(fp->joint[FTPIKACHU_THUNDER_SPAWN_JOINT], &pos);

    pos.y = (f32)Ground_Info->blastzone_top - FTPIKACHU_THUNDER_SPAWN_OFF_Y;

    vel.x = 0.0F;
    vel.z = 0.0F;
    vel.y = FTPIKACHU_THUNDER_VEL_Y;

    fp->status_vars.pikachu.speciallw.thunder_gobj = func_ovl3_8016A80C(fighter_gobj, &pos, &vel);
}

void func_ovl3_80151E44(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag0 != 0)
    {
        func_ovl3_80151DB0(fighter_gobj);
    }
}

void func_ovl3_80151E74(GObj *fighter_gobj)
{
    func_ovl3_80151E44(fighter_gobj);
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8015236C);
}

void func_ovl3_80151EA4(GObj *fighter_gobj)
{
    func_ovl3_80151E44(fighter_gobj);
    func_ovl2_800D9480(fighter_gobj, func_ovl3_801523B0);
}

void func_ovl3_80151ED4(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80151F5C);
}

void func_ovl3_80151EF8(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80151F1C);
}

void func_ovl3_80151F1C(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialLwStart, fighter_gobj->anim_frame, 1.0F, 0x96U);
}

void func_ovl3_80151F5C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirLwStart, fighter_gobj->anim_frame, 1.0F, 0x96U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80151FA8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag1 = 0;
    fp->cmd_flags.flag0 = 0;

    fp->fighter_vars.pikachu.is_thunder_destroy = FALSE;
}

void jtgt_ovl3_80151FBC(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialLwStart, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80151FA8(fighter_gobj);
}

void jtgt_ovl3_80151FFC(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirLwStart, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80151FA8(fighter_gobj);
}

bool32 func_ovl3_8015203C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Item_Struct *ip;
    DObj *fighter_joint;
    DObj *item_joint;
    GObj *thunder_gobj;
    f32 ft_temp_x;
    f32 ft_temp_y;
    f32 it_temp_x;
    f32 it_temp_y;
    f32 dist_x;
    f32 dist_y;

    thunder_gobj = fp->status_vars.pikachu.speciallw.thunder_gobj;

    if (thunder_gobj == NULL)
    {
        fp->fighter_vars.pikachu.is_thunder_destroy |= TRUE;
    }

    if (fp->fighter_vars.pikachu.is_thunder_destroy & TRUE)
    {
        return FALSE;
    }

    ip = ItemGetStruct(thunder_gobj);

    fighter_joint = DObjGetStruct(fighter_gobj);
    item_joint = DObjGetStruct(thunder_gobj);

    ft_temp_x = fighter_joint->translate.x;
    it_temp_x = item_joint->translate.x;

    dist_x = (ft_temp_x < it_temp_x) ? -(ft_temp_x - it_temp_x) : (ft_temp_x - it_temp_x);

    if (dist_x < FTPIKACHU_THUNDER_COLLIDE_X)
    {
        ft_temp_y = fighter_joint->translate.y;
        it_temp_y = item_joint->translate.y + FTPIKACHU_THUNDER_COLL_OFF_Y;

        dist_y = (ft_temp_y < it_temp_y) ? -(ft_temp_y - it_temp_y) : (ft_temp_y - it_temp_y);

        if (dist_y < FTPIKACHU_THUNDER_COLLIDE_Y)
        {
            ip->item_vars.thunder.thunder_state = 1;

            return TRUE;
        }
    }
    return FALSE;
}

void func_ovl3_80152124(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_8015203C(fighter_gobj) != FALSE)
    {
        func_ovl3_80152588(fighter_gobj);
    }
    else if (fp->fighter_vars.pikachu.is_thunder_destroy & TRUE)
    {
        func_ovl3_80152724(fighter_gobj);
    }
    else if (fp->cmd_flags.flag1 != 0)
    {
        func_ovl3_80152724(fighter_gobj);
    }
}

void func_ovl3_8015219C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_8015203C(fighter_gobj) != FALSE)
    {
        func_ovl3_801525C8(fighter_gobj);
    }
    else if (fp->fighter_vars.pikachu.is_thunder_destroy & TRUE)
    {
        func_ovl3_80152764(fighter_gobj);
    }
    else if (fp->cmd_flags.flag1 != 0)
    {
        func_ovl3_80152764(fighter_gobj);
    }
}

void func_ovl3_80152214(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_801522DC);
}

void func_ovl3_80152238(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015229C);
}

void func_ovl3_8015225C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *thunder_gobj = fp->status_vars.pikachu.speciallw.thunder_gobj;

    if (thunder_gobj == NULL)
    {
        fp->fighter_vars.pikachu.is_thunder_destroy |= TRUE;
    }
    if (!(fp->fighter_vars.pikachu.is_thunder_destroy & TRUE))
    {
        Item_Struct *ip = ItemGetStruct(thunder_gobj);

        ip->item_vars.thunder.thunder_state = 2;
    }
}

void func_ovl3_8015229C(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialLwLoop, fighter_gobj->anim_frame, 1.0F, 0x4097U);
}

void func_ovl3_801522DC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirLwLoop, fighter_gobj->anim_frame, 1.0F, 0x4097U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80152328(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag0 == 0)
    {
        func_ovl3_80151DB0(fighter_gobj);
    }
    fp->cmd_flags.flag0 = 0;

    fp->cb_take_damage = func_ovl3_8015225C;
}

void func_ovl3_8015236C(GObj *fighter_gobj)
{
    func_ovl3_80152328(fighter_gobj);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialLwLoop, 0.0F, 1.0F, 0x4000U);
    func_ovl2_800E0830(fighter_gobj);
}

void func_ovl3_801523B0(GObj *fighter_gobj)
{
    func_ovl3_80152328(fighter_gobj);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirLwLoop, 0.0F, 1.0F, 0x4000U);
    func_ovl2_800E0830(fighter_gobj);
}

void func_ovl3_801523F4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != 0)
    {
        func_ovl3_80152724(fighter_gobj);
    }
}

void func_ovl3_80152424(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->cmd_flags.flag1 != 0)
    {
        func_ovl3_80152764(fighter_gobj);
    }
}

void func_ovl3_80152454(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = fp->attributes;

    func_ovl2_800D8D68(fp, 0.5F, common_attrs->fall_speed_max);

    if (func_ovl2_800D8FA8(fp, common_attrs) == FALSE)
    {
        func_ovl2_800D9074(fp, common_attrs);
    }
}

void func_ovl3_801524A4(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_8015252C);
}

void func_ovl3_801524C8(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_801524EC);
}

void func_ovl3_801524EC(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialLwHit, fighter_gobj->anim_frame, 1.0F, 0x97U);
}

void func_ovl3_8015252C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirLwHit, fighter_gobj->anim_frame, 1.0F, 0x97U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80152578(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag1 = 0;

    fp->cb_take_damage = NULL;
}

void func_ovl3_80152588(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialLwHit, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80152578(fighter_gobj);
}

void func_ovl3_801525C8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirLwHit, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80152578(fighter_gobj);

    fp->phys_info.vel_air.y = FTPIKACHU_THUNDER_HIT_VEL_Y;
}

void func_ovl3_80152620(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8013F9E0);
}

void func_ovl3_80152644(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_801526CC);
}

void func_ovl3_80152668(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_8015268C);
}

void func_ovl3_8015268C(GObj *fighter_gobj)
{
    func_ovl2_800DEE98(FighterGetStruct(fighter_gobj));
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialLwEnd, fighter_gobj->anim_frame, 1.0F, 0x96U);
}

void func_ovl3_801526CC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);


    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirLwEnd, fighter_gobj->anim_frame, 1.0F, 0x96U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80152718(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cb_take_damage = NULL;
}

void func_ovl3_80152724(GObj *fighter_gobj)
{
    func_ovl3_80152718(fighter_gobj);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialLwEnd, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
}

void func_ovl3_80152764(GObj *fighter_gobj)
{
    func_ovl3_80152718(fighter_gobj);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Pikachu_SpecialAirLwEnd, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
}
