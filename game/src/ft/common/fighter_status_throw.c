#include "fighter.h"
#include "ftkirby.h"

void func_ovl3_8014A0C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 != 0U)
    {
        fp->command_vars.flags.flag1 = 0;

        fp->lr = -fp->lr;

        fp->phys_info.vel_ground.x = -fp->phys_info.vel_ground.x;
    }

    // flag2 = bool to invert facing direction

    if (fp->command_vars.flags.flag2 != 0U)
    {
        func_ovl3_8014AB64(fp->catch_gobj);

        func_ovl3_8014AFD0(fp->catch_gobj, (fp->command_vars.flags.flag2 == 1) ? -fp->lr : fp->lr, (fp->status_info.status_id == ftStatus_Common_ThrowB) ? 1 : 0, 1);

        fp->command_vars.flags.flag2 = 0;

        fp->catch_gobj = NULL;

        func_ovl2_800E8098(fp, 0U);
    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        if ((fp->ft_kind == Ft_Kind_Donkey) || (fp->ft_kind == Ft_Kind_PolyDonkey) || (fp->ft_kind == Ft_Kind_GiantDonkey))
        {
            if (fp->status_info.status_id == ftStatus_Common_ThrowF)
            {
                func_ovl3_8014E558(fp->catch_gobj);
                func_ovl3_8014D49C(fighter_gobj);

                return;
            }
        }
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_8014A1E8(GObj *fighter_gobj, bool32 is_throwf)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    s32 status_id;
    GObj *catch_gobj;
    Fighter_Struct *catch_fp;
    ftThrownStatus *thrown_status;

    catch_gobj = this_fp->catch_gobj;
    catch_fp = FighterGetStruct(catch_gobj);

    if ((is_throwf != FALSE) || ((this_fp->input.stick_range.x * this_fp->lr) >= 0))
    {
        if ((this_fp->ft_kind == Ft_Kind_Kirby) || (this_fp->ft_kind == Ft_Kind_PolyKirby))
        {
            status_id = ftStatus_Kirby_ThrowF;

            func_ovl2_800DEEC8(this_fp);
        }
        else status_id = ftStatus_Common_ThrowF;
        thrown_status = &this_fp->attributes->thrown_status[catch_fp->ft_kind].ft_thrown[0];
    }
    else
    {
        status_id = ftStatus_Common_ThrowB;
        thrown_status = &this_fp->attributes->thrown_status[catch_fp->ft_kind].ft_thrown[1];
    }
    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl2_800E8098(this_fp, 0x3FU);

    this_fp->command_vars.flags.flag2 = 0;
    this_fp->command_vars.flags.flag1 = 0;

    if ((this_fp->ft_kind == Ft_Kind_Samus) || (this_fp->ft_kind == Ft_Kind_PolySamus))
    {
        if (func_ovl2_80101E80(fighter_gobj) != NULL)
        {
            this_fp->gfx_stop_statupdate = TRUE;
        }
    }
    if (thrown_status->status1 != -1)
    {
        func_ovl3_8014AC0C(catch_gobj, thrown_status->status1, thrown_status->status2);
    }
    else func_ovl3_8014ACB4(catch_gobj, thrown_status->status2);

    if ((this_fp->ft_kind == Ft_Kind_Kirby) || (this_fp->ft_kind == Ft_Kind_PolyKirby))
    {
        if (status_id == ftStatus_Kirby_ThrowF)
        {
            this_fp->is_ignore_blastzone_top = TRUE;
            catch_fp->is_ignore_blastzone_top = TRUE;
        }
    }
}

bool32 func_ovl3_8014A394(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    bool32 is_throwf = FALSE;

    if ((fp->status_vars.common.catchwait.throw_wait == 0) || (fp->input.button_press & (fp->input.button_mask_a | fp->input.button_mask_b)))
    {
        is_throwf = TRUE;
    }
    else if ((fp->input.stick_prev.x >= FTCOMMON_CATCH_THROW_STICK_RANGE_MIN) || (fp->input.stick_range.x < FTCOMMON_CATCH_THROW_STICK_RANGE_MIN))
    {
        if ((fp->input.stick_prev.x <= -FTCOMMON_CATCH_THROW_STICK_RANGE_MIN) || (fp->input.stick_range.x > -FTCOMMON_CATCH_THROW_STICK_RANGE_MIN))
        {
            return FALSE;
        }
    }
    func_ovl3_8014A1E8(fighter_gobj, is_throwf);

    return TRUE;
}

// Might be an independent file here

void func_ovl3_8014A430(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8014A4A8);
}

void func_ovl3_8014A454(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((func_ovl2_800DE6B0(fighter_gobj) != FALSE) && (fp->phys_info.vel_air.y < 0.0F))
    {
        func_ovl3_8014A5AC(fighter_gobj);
    }
}

void func_ovl3_8014A4A8(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    GObj *catch_gobj = this_fp->catch_gobj;
    Fighter_Struct *catch_fp = FighterGetStruct(catch_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_ThrowFFall, 0.0F, 1.0F, 0x80U);

    catch_fp->is_ignore_blastzone_top = FALSE;
}

void func_ovl3_8014A4F8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        func_ovl2_800D8BB4(fighter_gobj);
    }
    else func_ovl2_800D93E4(fighter_gobj);
}

void func_ovl3_8014A538(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == ground)
    {
        func_ovl3_80149B78(fighter_gobj);
    }
    else if ((func_ovl2_800DE6B0(fighter_gobj) != FALSE) && (fp->phys_info.vel_air.y < 0.0F))
    {
        func_ovl2_800DE8E4(fighter_gobj);
    }
}

void func_ovl3_8014A5AC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftCollision_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_ThrowFLanding, 0.0F, 1.0F, 0x80U);
}
