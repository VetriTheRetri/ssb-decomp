#include <game/src/ft/chara/ftkirby/ftkirby.h>

void func_ovl3_80156CB0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    if (fp->cmd_flags.flag0 != FALSE)
    {
        fp->cmd_flags.flag0 = FALSE;

        pos.x = FTKIRBY_COPYFOX_BLASTER_SPAWN_OFF_X;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTKIRBY_COPYFOX_BLASTER_SPAWN_JOINT], &pos);
        func_ovl3_80168A74(fighter_gobj, &pos);
    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_80156D38(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->cmd_flags.flag1 != 0) && (fp->input.button_press & fp->input.button_mask_b))
    {
        if (fp->ground_or_air == air)
        {
            func_ovl3_80156E18(fighter_gobj);
        }
        else func_ovl3_80156DD8(fighter_gobj);

        func_ovl2_800EA5E8(fp, 0x15);
        func_ovl2_800EA778(fp, fp->unk_0x28E_halfword);
        func_ovl2_800EA7B0(fp, 0);
    }
}

void func_ovl3_80156DC8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag0 = 0;
    fp->cmd_flags.flag1 = 0;
}

void func_ovl3_80156DD8(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyFox_SpecialN, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80156DC8(fighter_gobj);
}

void func_ovl3_80156E18(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Kirby_CopyFox_SpecialAirN, 0.0F, 1.0F, 8U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_80156DC8(fighter_gobj);
}
