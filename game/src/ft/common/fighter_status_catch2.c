#include "fighter.h"

void func_ovl3_80149EC0(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);

    if (ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_8014A000) != 0)
    {
        Fighter_Struct *catch_fp = FighterGetStruct(this_fp->catch_gobj);

        catch_fp->status_vars.common.capture.is_goto_pulled_wait = TRUE;
    }
}

Vec3f Fighter_CatchPull_Gfx_Offset = { 0.0F, 0.0F, 0.0F };

void func_ovl3_80149F04(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f offset;

    ftStatus_Update(fighter_gobj, ftStatus_Common_CatchPull, fp->status_vars.common.catchmain.catch_pull_frame_begin, 1.0F, 0x44U);

    fp->catch_gobj = fp->search_gobj;

    fp->x192_flag_b3 = FALSE;

    func_ovl2_800E8098(fp, 0x3FU);

    if (fp->proc_slope != NULL)
    {
        fp->proc_slope(fighter_gobj);
    }
    offset = Fighter_CatchPull_Gfx_Offset;

    func_ovl2_800EDF24(fp->joint[fp->attributes->joint_itemhold_heavy], &offset);
    func_ovl2_80101500(&offset);
    func_ovl2_800E806C(fp, 9, 0);
}

void func_ovl3_80149FCC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.catchwait.throw_wait != 0)
    {
        fp->status_vars.common.catchwait.throw_wait--;
    }
    func_ovl3_8014A394(fighter_gobj);
}

void func_ovl3_8014A000(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_CatchWait, 0.0F, 1.0F, 0x40U);

    fp->status_vars.common.catchwait.throw_wait = FTCOMMON_CATCH_THROW_WAIT;

    func_ovl2_800E8098(fp, 0x3FU);

    if ((fp->ft_kind == Ft_Kind_Link) || (fp->ft_kind == Ft_Kind_PolyLink))
    {
        func_ovl2_800E8C70(fighter_gobj, 0x15, 0);
        func_ovl2_800E8C70(fighter_gobj, 0x13, -1);
    }
    else if ((fp->ft_kind == Ft_Kind_Yoshi) || (fp->ft_kind == Ft_Kind_PolyYoshi))
    {
        func_ovl2_800E8C70(fighter_gobj, 7, 1);
    }
}