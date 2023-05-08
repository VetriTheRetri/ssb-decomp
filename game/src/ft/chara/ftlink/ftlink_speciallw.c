#include "ftlink.h"

void func_ovl3_801643D0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;
    Vec3f sp1C;

    if (fp->command_vars.flags.flag0 != 0)
    {
        fp->command_vars.flags.flag0 = 0;

        pos = DObjGetStruct(fighter_gobj)->translate;

        sp1C.x = 0.0F;
        sp1C.y = 0.0F;
        sp1C.z = 0.0F;

        func_ovl3_801865A0(fighter_gobj, &pos, &sp1C);
    }
}

void func_ovl3_80164434(GObj *fighter_gobj)
{
    func_ovl3_801643D0(fighter_gobj);
    func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_8016445C(GObj *fighter_gobj)
{
    func_ovl3_801643D0(fighter_gobj);
    func_ovl2_800D94E8(fighter_gobj);
}

void func_ovl3_80164484(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        ftMapCollide_SetAir(fp);
        ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirLw, fighter_gobj->anim_frame, 1.0F, 0U);
    }
}

void func_ovl3_801644D4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DE6B0(fighter_gobj) != FALSE)
    {
        ftMapCollide_SetGround(fp);
        ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialLw, fighter_gobj->anim_frame, 1.0F, 0U);
    }
}

bool32 func_ovl3_80164524(GObj *fighter_gobj, bool32 is_ground)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->item_hold != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(fp->item_hold);

        if (ap->at_kind == At_Kind_Link_Bomb)
        {
            if (is_ground == TRUE)
            {
                func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowF4);
                return TRUE;
            }
            else func_ovl3_80146690(fighter_gobj, ftStatus_Common_LightThrowAirF4);
        }
        return TRUE;
    }
    return FALSE;
}

void jtgt_ovl3_8016458C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80164524(fighter_gobj, TRUE) != TRUE)
    {
        fp->command_vars.flags.flag0 = 0;

        ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialLw, 0.0F, 1.0F, 0U);
        ftAnim_Update(fighter_gobj);
    }
}

void jtgt_ovl3_801645E8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_80164524(fighter_gobj, FALSE) != TRUE)
    {
        fp->command_vars.flags.flag0 = 0;

        ftStatus_Update(fighter_gobj, ftStatus_Link_SpecialAirLw, 0.0F, 1.0F, 0U);
        ftAnim_Update(fighter_gobj);
    }
}
