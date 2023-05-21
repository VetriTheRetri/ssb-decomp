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

    if (fp->command_vars.flags.flag0 != 0)
    {
        fp->command_vars.flags.flag0 = 0;

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

        default:
            break; // Undefined behavior here, var is uninitialized, but projectile spawn function still runs

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

    ftMapCollide_SetGround(fp);

    ftStatus_Update(fighter_gobj, ftStatus_Mario_SpecialN, fighter_gobj->anim_frame, 1.0F, 2U);

    fp->proc_accessory = func_ovl3_80155E64;
}

void func_ovl3_80155FA0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Mario_SpecialAirN, fighter_gobj->anim_frame, 1.0F, 2U);
    func_ovl2_800D8EB8(fp);

    fp->proc_accessory = func_ovl3_80155E64;
}

void func_ovl3_80155FFC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = FALSE;
    fp->proc_accessory = func_ovl3_80155E64;
}

void jtgt_ovl3_80156014(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Mario_SpecialN, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80155FFC(fighter_gobj);
}

void jtgt_ovl3_80156054(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Mario_SpecialAirN, 0.0F, 1.0F, 8U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80155FFC(fighter_gobj);
}