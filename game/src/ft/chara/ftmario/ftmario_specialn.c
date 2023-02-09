#include <game/src/ft/chara/ftmario/ftmario.h>

void func_ovl3_80155E40(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl2_800DEE54);
}

void func_ovl3_80155E64(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    s32 var;

    if (fp->cmd_flags.flag0 != 0)
    {
        fp->cmd_flags.flag0 = 0;

        pos.x = 0.0F;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTMARIO_FIREBALL_SPAWN_JOINT], &pos);

        switch (fp->ft_kind) // jtbl at 0x8018C630
        {
        case Ft_Kind_Mario:
        case Ft_Kind_MetalMario:
        case Ft_Kind_PolyMario:
            var = 0;
            break;

        case Ft_Kind_Fox:
        case Ft_Kind_Donkey:
        case Ft_Kind_Link:
        case Ft_Kind_Yoshi:
        case Ft_Kind_Captain:
        case Ft_Kind_Kirby:
        case Ft_Kind_Pikachu:
        case Ft_Kind_Purin:
        case Ft_Kind_Ness: // Undefined behavior here, var is uninitialized, but projectile spawn function still runs
            break;

        case Ft_Kind_Luigi:
        case Ft_Kind_PolyLuigi:
            var = 1;
            break;
        }
        func_ovl3_801687A0(fighter_gobj, &pos, var);
    }
}

void func_ovl3_80155F04(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80155FA0);
}

void func_ovl3_80155F28(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80155F4C);
}

void func_ovl3_80155F4C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Mario_SpecialN, fighter_gobj->anim_frame, 1.0F, 2U);

    fp->cb_accessory = func_ovl3_80155E64;
}

void func_ovl3_80155FA0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Mario_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 2U);
    func_ovl2_800D8EB8(fp);

    fp->cb_accessory = func_ovl3_80155E64;
}

void func_ovl3_80155FFC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag0 = FALSE;
    fp->cb_accessory = func_ovl3_80155E64;
}

void jtgt_ovl3_80156014(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Mario_SpecialN, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80155FFC(fighter_gobj);
}

void jtgt_ovl3_80156054(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Mario_SpecialAirN, 0.0F, 1.0F, 8U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80155FFC(fighter_gobj);
}