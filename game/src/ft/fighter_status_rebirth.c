#include "fighter.h"
#include "gmmatch.h"
#include "gmground.h"

extern ftStatus_Rebirth_CustomVars D_ovl2_80116DD0;
extern f32 Rebirth_Halo_Offset_X[GMMATCH_PLAYERS_MAX];

void func_ovl3_8013CF60(GObj *this_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(this_gobj);
    ftStatus_Rebirth_CustomVars rebirth_vars = D_ovl2_80116DD0;
    GObj *other_gobj;
    Fighter_Struct *other_fp;
    s32 halo_number;
    s32 sp3C;
    Vec3f halo_spawn_pos;

    rebirth_vars.lr_rebirth = this_fp->lr;
    rebirth_vars.unk_rebirth_0x24 = 0;

    func_ovl2_800FC814(0x20, &sp3C);
    func_ovl2_800FC894(sp3C, &halo_spawn_pos);

    halo_number = 0;

loop: // This makes no sense
    other_gobj = gOMObjCommonLinks[GObjLinkIndex_Fighter];

    while (other_gobj != NULL)
    {
        do
        {
            if (other_gobj != this_gobj)
            {
                other_fp = FighterGetStruct(other_gobj);

                if ((other_fp->status_info.status_id >= ftStatus_Common_RebirthDown) && (other_fp->status_info.status_id <= ftStatus_Common_RebirthWait))
                {
                    if (halo_number == other_fp->status_vars.common.rebirth.halo_number)
                    {
                        halo_number++;

                        goto loop;
                    }
                }
            }
            other_gobj = other_gobj->group_gobj_next;

            continue;
        }
        while (FALSE);
    }
    rebirth_vars.halo_offset.x = Rebirth_Halo_Offset_X[halo_number] + halo_spawn_pos.x;
    rebirth_vars.halo_offset.y = Ground_Info->blastzone_top;
    rebirth_vars.halo_offset.z = 0.0F;

    func_ovl2_800D79F0(this_gobj, &rebirth_vars);
    func_ovl2_8010F840(this_fp);
    func_ovl2_800DEE98(this_fp);

    this_fp->coll_data.ground_line_id = -2;
    this_fp->coll_data.clip_flag = 0x4000;
    this_fp->coll_data.ground_angle.y = 1.0F;
    this_fp->coll_data.ground_angle.x = 0.0F;
    this_fp->coll_data.ground_angle.z = 0.0F;

    func_ovl2_800E6F24(this_gobj, ftStatus_Common_RebirthDown, 100.0F, 1.0F, 0U);
    func_ovl2_800E0830(this_gobj);
    func_ovl2_800D9444(this_gobj);

    this_fp->status_vars.common.rebirth.halo_lower_wait = FTCOMMON_REBIRTH_HALO_LOWER_WAIT;
    this_fp->status_vars.common.rebirth.halo_despawn_wait = FTCOMMON_REBIRTH_HALO_DESPAWN_WAIT;
    this_fp->status_vars.common.rebirth.pos = DObjGetStruct(this_gobj)->translate;
    this_fp->status_vars.common.rebirth.halo_offset.x = Rebirth_Halo_Offset_X[halo_number] + halo_spawn_pos.x;
    this_fp->status_vars.common.rebirth.halo_offset.y = halo_spawn_pos.y;
    this_fp->status_vars.common.rebirth.halo_offset.z = 0.0F;

    this_fp->x191_flag_b3 = TRUE;
    this_fp->x191_flag_b1 = TRUE;
    this_fp->x18E_flag_b0 = TRUE;
    this_fp->x18E_flag_b1 = TRUE;
    this_fp->x191_flag_b4567 = 1;

    this_fp->status_vars.common.rebirth.halo_number = halo_number;

    this_fp->fighter_cam_zoom_range = 0.6F;

    if (func_ovl2_80104068(this_gobj, this_fp->attributes->unk_0xEC) != 0)
    {
        this_fp->x18F_flag_b3 = TRUE;
    }
    func_ovl2_800E9814(this_gobj, 0xB, 0);
    func_ovl2_800E7F7C(this_gobj, 1);
}

void func_ovl3_8013D1D4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.common.rebirth.halo_despawn_wait != 0)
    {
        fp->status_vars.common.rebirth.halo_despawn_wait--;
    }
    if (fp->status_vars.common.rebirth.halo_lower_wait != 0)
    {
        fp->status_vars.common.rebirth.halo_lower_wait--;
    }
}

void func_ovl3_8013D200(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8013D1D4(fighter_gobj);

    if (fp->status_vars.common.rebirth.halo_despawn_wait == (FTCOMMON_REBIRTH_HALO_DESPAWN_WAIT - FTCOMMON_REBIRTH_HALO_UNK_WAIT))
    {
        fp->x191_flag_b4567 = 0;
    }
    if (fp->status_vars.common.rebirth.halo_despawn_wait == (FTCOMMON_REBIRTH_HALO_DESPAWN_WAIT - FTCOMMON_REBIRTH_HALO_STAND_WAIT))
    {
        func_ovl3_8013D2DC(fighter_gobj);
    }
}

void func_ovl3_8013D264(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    DObjGetStruct(fighter_gobj)->translate.y = (((fp->status_vars.common.rebirth.pos.y - fp->status_vars.common.rebirth.halo_offset.y) / 8100.0F) *
                                               SQUARE(fp->status_vars.common.rebirth.halo_lower_wait)) + fp->status_vars.common.rebirth.halo_offset.y;
}

void func_ovl3_8013D2AC(GObj *fighter_gobj)
{
    func_ovl3_8013D1D4(fighter_gobj);
    func_ovl2_800D9480(fighter_gobj, func_ovl3_8013D518);
}

void func_ovl3_8013D2DC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Common_RebirthStand, 0.0F, 1.0F, 0x106U);
    func_ovl2_800E0830(fighter_gobj);

    fp->x191_flag_b3 = TRUE;
    fp->x191_flag_b1 = TRUE;
    fp->x18E_flag_b0 = TRUE;
    fp->x18E_flag_b1 = TRUE;

    fp->fighter_cam_zoom_range = 0.6F;
}

void func_ovl3_8013D358(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8013D1D4(fighter_gobj);

    if (fp->status_vars.common.rebirth.halo_despawn_wait == 0)
    {
        func_ovl2_800EA8EC(fp, FTCOMMON_REBIRTH_INVINCIBLE_FRAMES);
        func_ovl3_8013F9E0(fighter_gobj);
    }
}

void func_ovl3_8013D3A4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (ftStatus_CheckInterruptAll(fighter_gobj))
    {
        func_ovl2_800EA8EC(fp, FTCOMMON_REBIRTH_INVINCIBLE_FRAMES);
    }
}

void func_ovl3_8013D518(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Common_RebirthWait, 0.0F, 1.0F, 0x106U);

    fp->x191_flag_b1 = TRUE;
    fp->x18E_flag_b0 = TRUE;
    fp->x18E_flag_b1 = TRUE;

    fp->fighter_cam_zoom_range = 0.6F;
}