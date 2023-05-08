#include <game/src/ft/chara/ftness/ftness.h>
#include <game/src/it/item/item.h>





// PSI Magnet (SpecialLw/SpecialAirLw)

void func_ovl3_801551E0(Fighter_Struct *fp) // PSI Magnet interrupt?
{
    if ((fp->input.button_hold & fp->input.button_mask_b) == FALSE)
    {
        fp->status_vars.ness.speciallw.is_release = TRUE;
    }
}

void func_ovl3_80155204(Fighter_Struct *fp)
{
    if (fp->status_vars.ness.speciallw.release_lag != 0)
    {
        fp->status_vars.ness.speciallw.release_lag--;
    }
}

void func_ovl3_8015521C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    DObj *joint = fp->joint[0];

    fp->lr = fp->lr_absorb;
    joint->rotate.y += (-PI32);

    func_ovl2_800EB528(fp->joint[0]);

    if (fp->ground_or_air == ground)
    {
        func_ovl3_80155948(fighter_gobj);
    }
    else func_ovl3_8015598C(fighter_gobj);
}

void func_ovl3_801552A0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, &func_ovl3_80155750);
}

void func_ovl3_801552C4(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, &func_ovl3_80155794);
}

void func_ovl3_801552E8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.ness.speciallw.gravity_delay != 0)
    {
        fp->status_vars.ness.speciallw.gravity_delay--;
    }
}

void func_ovl3_80155304(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->status_vars.ness.speciallw.gravity_delay != 0)
    {
        fp->status_vars.ness.speciallw.gravity_delay--;
    }
    else
    {
        func_ovl2_800D8D68(fp, 0.8F, attributes->fall_speed_max);
    }

    if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
    {
        func_ovl2_800D9074(fp, attributes);
    }
}

void func_ovl3_80155380(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, &func_ovl3_80155408);
}

void func_ovl3_801553A4(GObj *fighter_gobj)
{
    func_ovl2_800DE80C(fighter_gobj, func_ovl3_801553C8);
}

void func_ovl3_801553C8(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialLwStart, fighter_gobj->anim_frame, 1.0F, 0x92U);
}

void func_ovl3_80155408(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirLwStart, fighter_gobj->anim_frame, 1.0F, 0x92U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80155454(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->status_vars.ness.speciallw.release_lag = 30;
    fp->status_vars.ness.speciallw.is_release = FALSE;
    fp->status_vars.ness.speciallw.gravity_delay = 4;
}

void jtgt_ovl3_80155470(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialLwStart, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80155454(fighter_gobj);
}

void jtgt_ovl3_801554B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirLwStart, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80155454(fighter_gobj);

    fp->phys_info.vel_air.x /= 2;
    fp->phys_info.vel_air.y = 0.0F;
}

void func_ovl3_80155518(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_801551E0(fp);
    func_ovl3_80155204(fp);
}

void func_ovl3_80155544(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80155518(fighter_gobj);

    if ((fp->status_vars.ness.speciallw.release_lag <= 0) && (fp->status_vars.ness.speciallw.is_release != FALSE))
    {
        func_ovl3_80155AC8(fighter_gobj);
    }
}

void func_ovl3_80155544(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80155518(fighter_gobj);

    if ((fp->status_vars.ness.speciallw.release_lag <= 0) && (fp->status_vars.ness.speciallw.is_release != FALSE))
    {
        func_ovl3_80155B00(fighter_gobj);
    }
}

void func_ovl3_801555E4(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80155680);
}

void func_ovl3_80155608(GObj *fighter_gobj)
{
    func_ovl2_800DE80C(fighter_gobj, func_ovl3_8015562C);
}

void func_ovl3_8015562C(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialLwHold, fighter_gobj->anim_frame, 1.0F, 0x97U);

    fp->is_absorb = TRUE;
}

void func_ovl3_8015562C(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirLwHold, fighter_gobj->anim_frame, 1.0F, 0x97U);
    func_ovl2_800D8EB8(fp);

    fp->is_absorb = TRUE;
}

extern u8 ftNess_LoadedFiles_SpecialLwData;
extern void *D_ovl2_80131134;

void func_ovl3_801556E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 D_NF_0000164 = 0x16D4;

    if (!(fp->is_statupdate_stop_gfx))
    {
        if (func_ovl2_801025D8(fighter_gobj) != NULL)
        {
            fp->is_statupdate_stop_gfx = TRUE;
        }
    }
    fp->x18D_flag_b0 = TRUE;

    fp->special_hit = (SpecialHit*) ((uintptr_t)D_ovl2_80131134 + &ftNess_LoadedFiles_SpecialLwData); // Linker thing (attempt uintptr_t for 64-bit compatibility?)

    fp->command_vars.flags.flag1 = 0;
}

void func_ovl3_80155750(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialLwHold, 0.0F, 1.0F, 0x804U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801556E0(fighter_gobj);
}

void func_ovl3_80155794(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirLwHold, 0.0F, 1.0F, 0x804U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_801556E0(fighter_gobj);
}

void func_ovl3_801557D8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 != 0)
    {
        func_ovl3_80155750(fighter_gobj);
    }
}

void func_ovl3_80155808(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->command_vars.flags.flag1 != 0)
    {
        func_ovl3_80155794(fighter_gobj);
    }
}

void func_ovl3_80155838(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_801558D4);
}

void func_ovl3_8015585C(GObj *fighter_gobj)
{
    func_ovl2_800DE80C(fighter_gobj, func_ovl3_80155880);
}

void func_ovl3_80155880(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialLwHit, fighter_gobj->anim_frame, 1.0F, 0x897U);
    fp->is_absorb = TRUE;
}

void func_ovl3_801558D4(GObj *fighter_gobj)
{
    Fighter_Struct* fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirLwHit, fighter_gobj->anim_frame, 1.0F, 0x897U);
    func_ovl2_800D8EB8(fp);

    fp->is_absorb = TRUE;
}

void func_ovl3_80155934(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->is_absorb = TRUE;
}

void func_ovl3_80155948(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialLwHit, 0.0F, 1.0F, 4U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80155934(fighter_gobj);
}

void func_ovl3_8015598C(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirLwHit, 0.0F, 1.0F, 4U);
    ftAnim_Update(fighter_gobj);
    func_ovl3_80155934(fighter_gobj);
}

void func_ovl3_801559D0(GObj *fighter_gobj)
{
    func_ovl2_800D9480(fighter_gobj, &func_ovl3_8013F9E0);
}

void func_ovl3_801559F4(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80155A7C);
}


void func_ovl3_80155A18(GObj *fighter_gobj)
{
    func_ovl2_800DE80C(fighter_gobj, func_ovl3_80155A3C);
}

void func_ovl3_80155A3C(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialLwEnd, fighter_gobj->anim_frame, 1.0F, 0x92U);
}

void func_ovl3_80155A7C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirLwEnd, fighter_gobj->anim_frame, 1.0F, 0x92U);
    func_ovl2_800D8EB8(fp);
}

void func_ovl3_80155AC8(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialLwEnd, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80155B00(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Ness_SpecialAirLwEnd, 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);
}
