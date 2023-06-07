#include "ftkirby.h"

#define FTKIRBY_SPECIALNSTART_STATUPDATE_FLAGS (FTSTATUPDATE_UNK4_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE)
#define FTKIRBY_SPECIALNLOOP_STATUPDATE_FLAGS (FTSTATUPDATE_UNK5_PRESERVE | FTSTATUPDATE_UNK4_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE | FTSTATUPDATE_HIT_PRESERVE)

void func_ovl3_80161CA0(GObj *kirby_gobj, GObj *victim_gobj, s32 damage)
{
    Fighter_Struct *fp_kirby = FighterGetStruct(kirby_gobj);
    Fighter_Struct *fp_victim = FighterGetStruct(victim_gobj);
    s32 star_dmg_victim = gmCommon_DamageApplyStale(fp_kirby->port_id, damage, fp_kirby->attack_id, fp_kirby->motion_count);

    damage = star_dmg_victim;

    func_ovl3_801415F8(victim_gobj, gmCommonObject_DamageCalcKnockback(fp_victim->percent_damage, star_dmg_victim, star_dmg_victim, 0, 100, 0, fp_victim->attributes->weight, fp_kirby->handicap, fp_victim->handicap), 0);
    ftCommon_DamageUpdateCheckDropItem(fp_victim, damage);
    ftCommon_AttackUpdateMatchStats(fp_kirby->port_id, fp_victim->port_id, damage);
    ftCommon_AttackAddStaleQueue(fp_kirby->port_id, fp_victim->port_id, fp_kirby->attack_id, fp_kirby->motion_count);
}

f32 func_ovl3_80161D6C(Vec3f *kirby_pos, Vec3f *victim_pos) // Get distance between Kirby and inhale victim
{
    f32 dist_x = kirby_pos->x - victim_pos->x;
    f32 dist_y = kirby_pos->y - victim_pos->y;
    f32 dist_z = kirby_pos->z - victim_pos->z;

    return (dist_x * dist_x) + (dist_y * dist_y) + (dist_z * dist_z);
}

void func_ovl3_80161DA8(Fighter_Struct *fp, GObj *fighter_gobj, Vec3f *pos)
{
    *pos = DObjGetStruct(fighter_gobj)->translate;

    pos->x += (160.0F * fp->lr);
    pos->y += 100.0F;
}

void func_ovl3_80161E08(GObj *fighter_gobj, bool32 unused)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->command_vars.flags.flag0 = 0;
    fp->command_vars.flags.flag2 = 0;
    fp->command_vars.flags.flag1 = 0;

    fp->status_vars.kirby.specialn.copy_id = Ft_Kind_Kirby;
    fp->status_vars.kirby.specialn.release_lag = FTKIRBY_VACUUM_RELEASE_LAG;
    fp->status_vars.kirby.specialn.dist.x = 0.0F;
    fp->status_vars.kirby.specialn.dist.y = 0.0F;
}

void func_ovl3_80161E3C(Fighter_Struct *fp)
{
    if (fp->ground_or_air == ground)
    {
        ftCommon_SetCatchFlags(fp, FTGRABINTERACT_MASK_SPECIALNKIRBY, func_ovl3_801631E4, ftCommon_CaptureKirby_ProcCapture);
    }
    else ftCommon_SetCatchFlags(fp, FTGRABINTERACT_MASK_SPECIALNKIRBY, func_ovl3_80163430, ftCommon_CaptureKirby_ProcCapture);
}

void func_ovl3_80161E94(GObj *fighter_gobj)
{
    func_ovl3_80161E3C(FighterGetStruct(fighter_gobj));
}

void func_ovl3_80161EB4(Fighter_Struct *fp)
{
    switch (fp->fighter_vars.kirby.copy_id)
    {
    case Ft_Kind_Samus:
        fp->fighter_vars.kirby.copysamus_charge_level = 0;
        fp->fighter_vars.kirby.copysamus_charge_recoil = 0;
        break;

    case Ft_Kind_Donkey:
        fp->fighter_vars.kirby.copydonkey_charge_level = 0;
        break;

    case Ft_Kind_Captain:
        fp->fighter_vars.kirby.copycaptain_falcon_punch_unk = 0;
        break;

    case Ft_Kind_Purin:
        fp->fighter_vars.kirby.copypurin_unk = 0;
        break;
    }
}

extern intptr_t ftKirby_LoadedFiles_SpecialNData;
extern void *D_ovl2_80131074;

void func_ovl3_80161F0C(GObj *fighter_gobj)
{
    s16 index;
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftKirbyCopyData *copy_data = (ftKirbyCopyData*) ((uintptr_t)D_ovl2_80131074 + (intptr_t)&ftKirby_LoadedFiles_SpecialNData); // Linker thing

    if (fp->command_vars.flags.flag1 != 0)
    {
        if (fp->fighter_vars.kirby.copy_id == fp->status_vars.kirby.specialn.copy_id)
        {
            func_800269C0(0xC7); // SFX?
        }
        else
        {
            func_800269C0(0xC6); // SFX?

            index = fp->status_vars.kirby.specialn.copy_id;
            fp->fighter_vars.kirby.copy_id = index;

            ftCommon_SetModelPartRenderStateIndex(fighter_gobj, 6, copy_data[index].unk_0x2);
            ftCommon_ResetModelPartRenderAll(fighter_gobj);
            func_ovl3_80161EB4(fp);
        }
        fp->command_vars.flags.flag1 = 0;
    }
}

void func_ovl3_80161FBC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->is_statupdate_stop_gfx == TRUE)
    {
        ftCommon_ProcDestroyGFX(fighter_gobj);
    }
}

void func_ovl3_8016201C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fp->is_statupdate_stop_gfx) && (fp->command_vars.flags.flag0 == 1))
    {
        if (func_ovl2_801042B4(fighter_gobj) != FALSE)
        {
            fp->command_vars.flags.flag0 = 0;
            fp->is_statupdate_stop_gfx = TRUE;
        }
    }
}

void func_ovl3_80162078(GObj *fighter_gobj)
{
    Fighter_Struct *kirby_fp = FighterGetStruct(fighter_gobj);
    ftKirbyCopyData *copy_data = (ftKirbyCopyData*) ((uintptr_t)D_ovl2_80131074 + &ftKirby_LoadedFiles_SpecialNData); // Linker thing
    Fighter_Struct *victim_fp;
    Vec3f kirby_pos;
    f32 dist;

    func_ovl3_80161DA8(kirby_fp, fighter_gobj, &kirby_pos);

    dist = func_ovl3_80161D6C(&DObjGetStruct(kirby_fp->catch_gobj)->translate, &kirby_pos);

    if (dist < 1024.0F)
    {
        victim_fp = FighterGetStruct(kirby_fp->catch_gobj); // No NULL check?

        victim_fp->status_vars.common.capturekirby.is_goto_capturewait = TRUE;

        if ((victim_fp->ft_kind == Ft_Kind_Kirby) || (victim_fp->ft_kind == Ft_Kind_PolyKirby))
        {
            kirby_fp->status_vars.kirby.specialn.copy_id = victim_fp->fighter_vars.kirby.copy_id;
            victim_fp->status_vars.common.capturekirby.is_kirby = TRUE;
        }
        else
        {
            kirby_fp->status_vars.kirby.specialn.copy_id = copy_data[victim_fp->ft_kind].copy_id;
        }

        func_800269C0(0xC5);

        if (kirby_fp->ground_or_air == ground)
        {
            func_ovl3_80163204(fighter_gobj);
        }
        else func_ovl3_80163450(fighter_gobj);
    }
    else if (dist < 9216.0F)
    {
        func_ovl3_80161FBC(fighter_gobj);
    }
}

void func_ovl3_801621A8(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_801633EC);
}

void func_ovl3_801621CC(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_80162FA8);
}

void func_ovl3_801621F0(GObj *fighter_gobj)
{
    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, func_ovl3_80162FE0);
}

void func_ovl3_80162214(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    void (*proc_map)(GObj*) = (fp->ground_or_air == ground) ? func_ovl3_80163274 : func_ovl3_801634C0;

    ftAnim_IfAnimEnd_ProcStatus(fighter_gobj, proc_map);
}

void func_ovl3_80162258(GObj *fighter_gobj)
{
    Fighter_Struct *kirby_fp = FighterGetStruct(fighter_gobj);

    if (kirby_fp->command_vars.flags.flag2 != 0)
    {
        if (kirby_fp->catch_gobj != NULL)
        {
            Fighter_Struct *victim_fp = FighterGetStruct(kirby_fp->catch_gobj);

            ftCommon_ThrownKirbyStar_SetStatus(kirby_fp->catch_gobj);
            ftCommon_ThrownUpdateEnemyInfo(victim_fp, fighter_gobj);

            victim_fp->phys_info.vel_air.z = 0.0F;
            victim_fp->phys_info.vel_air.y = 0.0F;
            victim_fp->phys_info.vel_air.x = (f32) (-victim_fp->lr * 120.0F);
        }
    }
}

void func_ovl3_801622DC(GObj *fighter_gobj)
{
    Fighter_Struct *kirby_fp = FighterGetStruct(fighter_gobj);

    if (kirby_fp->command_vars.flags.flag2 != 0)
    {
        if (kirby_fp->catch_gobj != NULL)
        {
            Fighter_Struct *victim_fp = FighterGetStruct(kirby_fp->catch_gobj);

            ftCommon_ThrownCopyStar_SetStatus(kirby_fp->catch_gobj);

            victim_fp->phys_info.vel_air.y = (f32) (__sinf(1.308997F) * 100.0F);

            victim_fp->phys_info.vel_air.x = (f32) (cosf(1.308997F) * victim_fp->lr * 100.0F);

            victim_fp->phys_info.vel_air.z = 0.0F;
        }
    }
}

void func_ovl3_80162374(GObj *fighter_gobj)
{
    func_ovl3_80162258(fighter_gobj);
    func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_8016239C(GObj *fighter_gobj)
{
    func_ovl3_80162258(fighter_gobj);
    func_ovl2_800D94E8(fighter_gobj);
}

void func_ovl3_801623C4(GObj *fighter_gobj)
{
    func_ovl3_80161F0C(fighter_gobj);
    func_ovl3_801622DC(fighter_gobj);
    func_ovl2_800D94C4(fighter_gobj);
}

void func_ovl3_801623F4(GObj *fighter_gobj)
{
    func_ovl3_80161F0C(fighter_gobj);
    func_ovl3_801622DC(fighter_gobj);
    func_ovl2_800D94E8(fighter_gobj);
}

bool32 func_ovl3_80162424(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->status_vars.kirby.specialn.release_lag != 0)
    {
        fp->status_vars.kirby.specialn.release_lag--;
        return TRUE;
    }
    else if (fp->input.pl.button_hold & fp->input.button_mask_b)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80162468(GObj *fighter_gobj)
{
    if (func_ovl3_80162424(fighter_gobj) == FALSE)
    {
        func_ovl3_80163364(fighter_gobj);
    }
}

void func_ovl3_80162468(GObj *fighter_gobj)
{
    if (func_ovl3_80162424(fighter_gobj) == FALSE)
    {
        func_ovl3_801635B0(fighter_gobj);
    }
}

bool32 func_ovl3_801624C8(GObj *fighter_gobj, void (*cb)(GObj*))
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->input.pl.button_tap & fp->input.button_mask_a)
    {
        if (fp->catch_gobj != NULL)
        {
            if (fp->catch_gobj != NULL) // Now you check twice? Bruh.
            {
                func_ovl3_80161CA0(fighter_gobj, fp->catch_gobj, FTKIRBY_VACUUM_RELEASE_DAMAGE);
            }
            cb(fighter_gobj);

            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl3_80162534(GObj *fighter_gobj, void (*cb)(GObj*))
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->input.pl.button_tap & fp->input.button_mask_b) || (fp->input.pl.stick_range.y < -40))
    {
        if (fp->catch_gobj != NULL)
        {
            if (fp->catch_gobj != NULL)
            {
                func_ovl3_80161CA0(fighter_gobj, fp->catch_gobj, FTKIRBY_VACUUM_COPY_DAMAGE);
            }
            cb(fighter_gobj);
            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl3_801625B0(GObj *fighter_gobj, void (*cb)(GObj*))
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    s32 stick_x = fp->input.pl.stick_range.x;

    if (ABS(stick_x) < 28) stick_x = 0; // HAL Meme Laboratory

    if (((stick_x < 0) && (fp->lr == RIGHT)) || ((stick_x > 0) && (fp->lr == LEFT)))
    {
        cb(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80162634(GObj *fighter_gobj)
{
    if ((func_ovl3_801624C8(fighter_gobj, func_ovl3_80163224) == FALSE) && (func_ovl3_80162534(fighter_gobj, func_ovl3_80163314) == FALSE))
    {
        func_ovl3_801625B0(fighter_gobj, func_ovl3_801632C4);
    }
}

void func_ovl3_80162684(GObj *fighter_gobj)
{
    if (func_ovl3_801624C8(fighter_gobj, func_ovl3_80163470) == FALSE)
    {
        func_ovl3_80162534(fighter_gobj, func_ovl3_80163560);
    }
}

void func_ovl3_801626C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *attributes = fp->attributes;

    if (fp->is_fast_fall)
    {
        func_ovl2_800D8DA0(fp, attributes);
    }
    else
    {
        func_ovl2_800D8D68(fp, FTKIRBY_VACUUM_GRAVITY_MUL * attributes->gravity, FTKIRBY_VACUUM_FALL_MAX_MUL * attributes->fall_speed_max);
    }
    if (func_ovl2_800D8FA8(fp, attributes) == FALSE)
    {
        func_ovl2_800D9074(fp, attributes);
    }
}

void func_ovl3_80162750(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80162ABC);
}

void func_ovl3_80162774(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80162B04);
}

void func_ovl3_80162798(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80162B50);
}

void func_ovl3_801627BC(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80162BF0);
}

void func_ovl3_801627E0(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80162BA0);
}

void func_ovl3_80162804(GObj *fighter_gobj)
{
    func_ovl2_800DDE84(fighter_gobj, func_ovl3_80162CE0);
}

void func_ovl3_80162828(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80162D80);
}

void func_ovl3_8016284C(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80162E20);
}

void func_ovl3_80162870(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_80162EC0);
}

void func_ovl3_80162894(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_801629D8);
}

void func_ovl3_801628B8(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80162A20);
}

void func_ovl3_801628DC(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80162A6C);
}

void func_ovl3_80162900(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80162C40);
}

void func_ovl3_80162924(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80162C90);
}

void func_ovl3_80162948(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80162D30);
}

void func_ovl3_8016296C(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80162DD0);
}

void func_ovl3_80162990(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80162E70);
}

void func_ovl3_801629B4(GObj *fighter_gobj)
{
    func_ovl2_800DE6E4(fighter_gobj, func_ovl3_80162F10);
}

void func_ovl3_801629D8(GObj *fighter_gobj)
{
    ftMapCollide_SetGround(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNStart, fighter_gobj->anim_frame, 1.0F, FTKIRBY_SPECIALNSTART_STATUPDATE_FLAGS);
    func_ovl3_80161E94(fighter_gobj);
}

void func_ovl3_80162A20(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNLoop, fighter_gobj->anim_frame, 1.0F, FTKIRBY_SPECIALNLOOP_STATUPDATE_FLAGS);
    func_ovl3_80161E3C(fp);
}

void func_ovl3_80162A6C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNEnd, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162ABC(GObj *fighter_gobj)
{
    ftMapCollide_SetAir(FighterGetStruct(fighter_gobj));
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNStart, fighter_gobj->anim_frame, 1.0F, FTKIRBY_SPECIALNSTART_STATUPDATE_FLAGS);
    func_ovl3_80161E94(fighter_gobj);
}

void func_ovl3_80162B04(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNLoop, fighter_gobj->anim_frame, 1.0F, FTKIRBY_SPECIALNLOOP_STATUPDATE_FLAGS);
    func_ovl3_80161E3C(fp);
}

void func_ovl3_80162B50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNEnd, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162BA0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNCatch, fighter_gobj->anim_frame, 1.0F, FTSTATUPDATE_GFX_PRESERVE);
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162BF0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNHit, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162C40(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNHit, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162C90(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNCatch, fighter_gobj->anim_frame, 1.0F, FTSTATUPDATE_GFX_PRESERVE);
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162CE0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNRelease, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162D30(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNRelease, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162D80(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNWait, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162DD0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNWait, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162E20(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNTurn, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162E70(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNTurn, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162EC0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetAir(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNCopy, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162F10(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftMapCollide_SetGround(fp);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNCopy, fighter_gobj->anim_frame, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
}

void func_ovl3_80162F60(GObj *fighter_gobj)
{
    Fighter_Struct *kirby_fp = FighterGetStruct(fighter_gobj);

    if (kirby_fp->catch_gobj != NULL)
    {
        Fighter_Struct *victim_fp = FighterGetStruct(kirby_fp->catch_gobj);

        victim_fp->lr = kirby_fp->lr;
    }
    kirby_fp->lr *= -1.0F; // Why is this a float operation? It gets converted back into signed long...
}

void func_ovl3_80162FA8(GObj *fighter_gobj)
{
    func_ovl3_80162F60(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNWait, 0.0F, 1.0F, FTSTATUPDATE_NULL_PRESERVE);
}

void func_ovl3_80162FE0(GObj *fighter_gobj)
{
    func_ovl3_80162F60(fighter_gobj);
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNWait, 0.0F, 1.0F, FTSTATUPDATE_NULL_PRESERVE);
}

extern const Vec3f D_ovl3_80188E00;

void func_ovl3_80163018(GObj *fighter_gobj, s32 status_id)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos = D_ovl3_80188E00; // Never used???

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, FTSTATUPDATE_SLOPECONTOUR_PRESERVE);
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);

    if (fp->proc_slope != NULL)
    {
        fp->proc_slope(fighter_gobj);
    }
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_801630A0(GObj *fighter_gobj, s32 status_id)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f pos;

    ftStatus_Update(fighter_gobj, status_id, 0.0F, 1.0F, (FTSTATUPDATE_UNK4_PRESERVE | FTSTATUPDATE_SLOPECONTOUR_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);

    fp->catch_gobj = fp->search_gobj;

    fp->x192_flag_b3 = FALSE;

    if (fp->proc_slope != NULL)
    {
        fp->proc_slope(fighter_gobj);
    }
    ftAnim_Update(fighter_gobj);
    func_ovl3_80161DA8(fp, fighter_gobj, &pos);

    fp->status_vars.kirby.specialn.dist.x = DObjGetStruct(fp->catch_gobj)->translate.x - pos.x;
    fp->status_vars.kirby.specialn.dist.y = DObjGetStruct(fp->catch_gobj)->translate.y - pos.y;
}

void jtgt_ovl3_80163154(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNStart, 0.0F, 1.0F, FTSTATUPDATE_NULL_PRESERVE);
    func_ovl3_80161E08(fighter_gobj, FALSE);
    func_ovl3_80161E94(fighter_gobj);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_801631A0(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNLoop, 0.0F, 1.0F, (FTSTATUPDATE_UNK4_PRESERVE | FTSTATUPDATE_SLOPECONTOUR_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    func_ovl3_80161E94(fighter_gobj);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_801631E4(GObj *fighter_gobj)
{
    func_ovl3_801630A0(fighter_gobj, ftStatus_Kirby_SpecialNHit);
}

void func_ovl3_80163204(GObj *fighter_gobj)
{
    func_ovl3_80163018(fighter_gobj, ftStatus_Kirby_SpecialNCatch);
}

void func_ovl3_80163224(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNRelease, 0.0F, 1.0F, (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80163274(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNWait, 0.0F, 1.0F, (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_801632C4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNTurn, 0.0F, 1.0F, (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80163314(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNCopy, 0.0F, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80163364(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialNEnd, 0.0F, 1.0F, FTSTATUPDATE_GFX_PRESERVE);
    ftAnim_Update(fighter_gobj);
}

void jtgt_ovl3_801633A0(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNStart, 0.0F, 1.0F, FTSTATUPDATE_NULL_PRESERVE);
    func_ovl3_80161E08(fighter_gobj, TRUE);
    func_ovl3_80161E94(fighter_gobj);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_801633EC(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNLoop, 0.0F, 1.0F, (FTSTATUPDATE_UNK4_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    func_ovl3_80161E94(fighter_gobj);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80163430(GObj *fighter_gobj)
{
    func_ovl3_801630A0(fighter_gobj, ftStatus_Kirby_SpecialAirNHit);
}

void func_ovl3_80163450(GObj *fighter_gobj)
{
    func_ovl3_801630A0(fighter_gobj, ftStatus_Kirby_SpecialAirNCatch);
}

void func_ovl3_80163470(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNRelease, 0.0F, 1.0F, (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_801634C0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNWait, 0.0F, 1.0F, (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80163510(GObj *fighter_gobj) // Unused
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNTurn, 0.0F, 1.0F, (FTSTATUPDATE_TEXTUREPART_PRESERVE | FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_80163560(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNCopy, 0.0F, 1.0F, (FTSTATUPDATE_MODELPART_PRESERVE | FTSTATUPDATE_GFX_PRESERVE));
    ftCommon_SetCaptureFlags(fp, FTGRABINTERACT_MASK_ALL);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_801635B0(GObj *fighter_gobj)
{
    ftStatus_Update(fighter_gobj, ftStatus_Kirby_SpecialAirNEnd, 0.0F, 1.0F, FTSTATUPDATE_GFX_PRESERVE);
    ftAnim_Update(fighter_gobj);
}

void func_ovl3_801635EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80161EB4(fp);
    func_ovl2_80103F78(fighter_gobj);
    func_800269C0(0xCC);

    fp->fighter_vars.kirby.copy_id = Ft_Kind_Kirby;

    ftCommon_SetModelPartRenderStateIndex(fighter_gobj, 6, 0);
    ftCommon_ResetColAnimStatUpdate(fighter_gobj);
}

void func_ovl3_80163648(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->ft_kind == Ft_Kind_Kirby) ||
    (fp->ft_kind == Ft_Kind_PolyKirby)) &&
    (fp->fighter_vars.kirby.copy_id != Ft_Kind_Kirby) &&
    (fp->fighter_vars.kirby.copy_bool_unk == FALSE) &&
    (rand_f32() < 0.083333336F))
    {
        func_ovl3_801635EC(fighter_gobj);
    }
}