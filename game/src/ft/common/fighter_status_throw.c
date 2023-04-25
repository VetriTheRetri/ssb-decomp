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

void func_ovl3_8014A1E8(GObj *fighter_gobj, s32 arg1)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    s32 status_id;
    GObj *catch_gobj;
    Fighter_Struct *catch_fp;
    ftThrownStatus *thrown_status;

    catch_gobj = this_fp->catch_gobj;
    catch_fp = FighterGetStruct(catch_gobj);

    if ((arg1 != 0) || ((this_fp->input.stick_range.x * this_fp->lr) >= 0))
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
