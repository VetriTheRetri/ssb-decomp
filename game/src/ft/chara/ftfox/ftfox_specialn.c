#include <game/src/ft/chara/ftfox/ftfox.h>

void func_ovl3_8015BB50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    if (fp->cmd_flags.flag0 != FALSE)
    {
        fp->cmd_flags.flag0 = FALSE;

        pos.x = FTFOX_BLASTER_SPAWN_OFF_X;
        pos.y = 0.0F;
        pos.z = 0.0F;

        func_ovl2_800EDF24(fp->joint[FTFOX_BLASTER_HOLD_JOINT], &pos);
        func_ovl3_80168A74(fighter_gobj, &pos);
    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_8015BBD8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->cmd_flags.flag1 != FALSE) && (fp->input.button_press & fp->input.button_mask_b))
    {
        if (fp->ground_or_air == air)
        {
            func_ovl3_8015BCB8(fighter_gobj);
        }
        else func_ovl3_8015BC78(fighter_gobj);

        func_ovl2_800EA5E8(fp, 0x12);
        func_ovl2_800EA778(fp, fp->unk_0x28E_halfword);
        func_ovl2_800EA7B0(fp, 0);
    }
}

void func_ovl3_8015BC68(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->cmd_flags.flag0 = FALSE;
    fp->cmd_flags.flag1 = FALSE;
}


void func_ovl3_8015BC78(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialN, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015BC68(fighter_gobj);
}

void func_ovl3_8015BCB8(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialAirN, 0.0F, 1.0F, 8U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015BC68(fighter_gobj);
}
