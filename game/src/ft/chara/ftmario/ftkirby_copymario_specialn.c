#include <game/src/ft/chara/ftkirby/ftkirby.h>

void func_ovl3_801569B0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl2_800DEE54);
}

void func_ovl3_801569D4(GObj *fighter_gobj)
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

        func_ovl2_800EDF24(fp->joint[FTKIRBY_COPYMARIO_FIREBALL_SPAWN_JOINT], &pos);

        switch (fp->fighter_vars.kirby.copy_id) // jtbl at 0x8018C6A0
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
        case Ft_Kind_Ness: // Undefined behavior here, var is uninitialized
            break;

        case Ft_Kind_Luigi:
        case Ft_Kind_PolyLuigi:
            var = 1;
            break;
        }
        func_ovl3_801687A0(fighter_gobj, &pos, var);
    }
}

void func_ovl3_80156A74(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80156B38);
}

void func_ovl3_80156A98(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80156ABC);
}

#define FTKIRBY_COPYMARIO_FIREBALL_CHECK_FT_KIND(fp, id_true, id_false) \
(((fp->fighter_vars.kirby.copy_id == Ft_Kind_Mario) || \
(fp->fighter_vars.kirby.copy_id == Ft_Kind_PolyMario) || \
(fp->fighter_vars.kirby.copy_id == Ft_Kind_MetalMario)) \
? id_true : id_false) \

void func_ovl3_80156ABC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEE98(fp);

    func_ovl2_800E6F24(fighter_gobj, FTKIRBY_COPYMARIO_FIREBALL_CHECK_FT_KIND(fp, ftStatus_Kirby_CopyMario_SpecialN, ftStatus_Kirby_CopyLuigi_SpecialN), fighter_gobj->anim_frame, 1.0F, 2U);

    fp->cb_accessory = func_ovl3_801569D4;
}

void func_ovl3_80156B38(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800DEEC8(fp);

    func_ovl2_800E6F24(fighter_gobj, FTKIRBY_COPYMARIO_FIREBALL_CHECK_FT_KIND(fp, ftStatus_Kirby_CopyMario_SpecialAirN, ftStatus_Kirby_CopyLuigi_SpecialAirN), fighter_gobj->anim_frame, 1.0F, 2U);

    func_ovl2_800D8EB8(fp);

    fp->cb_accessory = func_ovl3_801569D4;
}

void func_ovl3_80156BB8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag0 = 0;
    fp->cb_accessory = func_ovl3_801569D4;
}

void jtgt_ovl3_80156BD0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, FTKIRBY_COPYMARIO_FIREBALL_CHECK_FT_KIND(fp, ftStatus_Kirby_CopyMario_SpecialN, ftStatus_Kirby_CopyLuigi_SpecialN), 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80156BB8(fighter_gobj);
}

void jtgt_ovl3_80156C38(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, FTKIRBY_COPYMARIO_FIREBALL_CHECK_FT_KIND(fp, ftStatus_Kirby_CopyMario_SpecialAirN, ftStatus_Kirby_CopyLuigi_SpecialAirN), 0.0F, 1.0F, 8U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80156BB8(fighter_gobj);
}
