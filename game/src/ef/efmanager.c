#include "effect.h"
#include "gmmatch.h"

void *D_ovl2_801313B0;
void *D_ovl2_801313B4;
void *D_ovl2_801313B8;
efStruct *gpEffectStructCurrent;
s32 gEffectStructsFree;
s32 gEffectBankIndex;
extern u8 D_ovl2_8012DF20[GMMATCH_PLAYERS_MAX];

extern intptr_t D_NF_00000053;
extern intptr_t D_NF_00000054;
extern intptr_t D_NF_00000055;

// To match this, rldm_get_file_with_external_heap and rldm_bytes_needed_to_load must take intptr_t or other int type as first argument
void efManager_AllocUserData(void)
{
    efStruct *ep;
    s32 i;
    s32 unused;

    gpEffectStructCurrent = ep = hal_alloc(sizeof(efStruct) * EFFECT_ALLOC_NUM, EFFECT_ALLOC_ALIGN);
    gEffectStructsFree = EFFECT_ALLOC_NUM;

    for (i = 0; i < (EFFECT_ALLOC_NUM - 1); i++)
    {
        ep[i].ep_alloc_next = &ep[i + 1];
    }
    if (ep != NULL)
    {
        ep[i].ep_alloc_next = NULL;
    }
    func_ovl2_800FCDEC();
    func_ovl2_800FCE6C();

    D_ovl2_801313B0 = rldm_get_file_with_external_heap(&D_NF_00000053, hal_alloc(rldm_bytes_needed_to_load(&D_NF_00000053), 0x10));
    D_ovl2_801313B4 = rldm_get_file_with_external_heap(&D_NF_00000054, hal_alloc(rldm_bytes_needed_to_load(&D_NF_00000054), 0x10));
    D_ovl2_801313B8 = rldm_get_file_with_external_heap(&D_NF_00000055, hal_alloc(rldm_bytes_needed_to_load(&D_NF_00000055), 0x10));

    func_ovl2_800FD18C();
}

// 0x800FD43C
efStruct* efManager_GetEffectStruct(bool32 is_force_return)
{
    efStruct *ep;

    if ((is_force_return == 0) && (gEffectStructsFree < 5))
    {
        return NULL;
    }
    ep = gpEffectStructCurrent;

    if (ep == NULL)
    {
        return NULL;
    }
    gpEffectStructCurrent = ep->ep_alloc_next;

    ep->fighter_gobj = NULL;
    ep->einfo = NULL;
    ep->is_pause_effect = FALSE;

    gEffectStructsFree--;

    return ep;
}

// 0x800FD4B8
efStruct* efManager_GetStructNoForceReturn(void)
{
    return efManager_GetEffectStruct(FALSE);
}

// 0x800FD4D8
efStruct* efManager_GetStructForceReturn(void)
{
    return efManager_GetEffectStruct(TRUE);
}

// 0x800FD4F8
void efManager_SetPrevAlloc(efStruct *ep)
{
    ep->ep_alloc_next = gpEffectStructCurrent;

    gpEffectStructCurrent = ep;

    gEffectStructsFree++;
}

// 0x800FD524
void func_ovl2_800FD524(GObj *effect_gobj)
{
    func_8000DF34(effect_gobj);

    if (effect_gobj->anim_frame <= 0.0F)
    {
        omEjectGObjCommon(effect_gobj);
    }
}

void func_ovl2_800FD568(GObj *effect_gobj)
{
    efStruct *ep = efGetStruct(effect_gobj);

    if (!(ep->is_pause_effect))
    {
        func_8000DF34(effect_gobj);

        if (effect_gobj->anim_frame <= 0.0F)
        {
            efManager_SetPrevAlloc(efGetStruct(effect_gobj));

            omEjectGObjCommon(effect_gobj);
        }
    }
}

// New file? Unused
void func_ovl2_800FD5D0(void)
{
    return;
}

// 0x800FD5D8
void func_ovl2_800FD5D8(GObj *effect_gobj)
{
    efStruct *ep = efGetStruct(effect_gobj);

    if (!(ep->is_pause_effect))
    {
        func_8000DF34(effect_gobj);
    }
}

void func_ovl2_800FD60C(GObj *effect_gobj)
{
    GObj *next_gobj;

    if (effect_gobj->unk_gobj_0x24 < -1000.0F)
    {
        next_gobj = effect_gobj->group_gobj_next;

        if (next_gobj->room != 2)
        {
            om_g_move_obj_dl(next_gobj, 2, 2);
        }
    }
    else
    {
        next_gobj = effect_gobj->group_gobj_next;

        if (next_gobj->room != 0x14)
        {
            om_g_move_obj_dl(next_gobj, 0x14, 2);
        }
    }
}

void func_ovl2_800FD68C(GObj *effect_gobj)
{
    GObj *next_gobj;

    if (effect_gobj->unk_gobj_0x24 > 1000.0F)
    {
        next_gobj = effect_gobj->group_gobj_next;

        if (next_gobj->room != 2)
        {
            om_g_move_obj_dl(next_gobj, 2, 2);
        }
    }
    else
    {
        next_gobj = effect_gobj->group_gobj_next;

        if (next_gobj->room != 0x14)
        {
            om_g_move_obj_dl(next_gobj, 0x14, 2);
        }
    }
}

// Another unused var
void func_ovl2_800FD70C(void)
{
    return;
}

void func_ovl2_800FD714(GObj *effect_gobj)
{
    efStruct *ep = efGetStruct(effect_gobj);

    if (ep != NULL)
    {
        if (ep->proc_update != NULL)
        {
            omAddGObjCommonProc(effect_gobj, ep->proc_update, 1, 3);
        }
    }
    else omAddGObjCommonProc(effect_gobj, func_ovl2_800FD524, 1, 3);

    effect_gobj->call_unk = NULL;
}

// Return here, currently missing 0x800FD778
void func_ovl2_800FDAFC(void *arg0)
{
    func_ovl2_800FD778(arg0, 0);
}

// 0x800FDB1C
void func_ovl2_800FDB1C(void *arg0)
{
    func_ovl2_800FD778(arg0, 1);
}

// 0x800FDB3C - Destroy effect GObj and particle too if applicable
efParticle* efManager_DestroyParticleGObj(efParticle *efpart, GObj *effect_gobj)
{
    if (efpart != NULL)
    {
        func_ovl0_800CEA40(efpart);
    }
    if (efGetStruct(effect_gobj) != NULL)
    {
        efStruct *ep = efGetStruct(effect_gobj);

        efManager_SetPrevAlloc(ep);
    }
    omEjectGObjCommon(effect_gobj);

    return NULL;
}

// 0x800FDB88
void efImage_Default_ProcDead(efImage *efimage)
{
    if (efGetStruct(efimage->effect_gobj) != NULL)
    {
        efStruct *ep = efGetStruct(efimage->effect_gobj);

        efManager_SetPrevAlloc(ep);
    }
    omEjectGObjCommon(efimage->effect_gobj);
}

// 0x800FDBCC
void efParticle_Default_ProcUpdate(GObj *effect_gobj)
{
    efStruct *ep = efGetStruct(effect_gobj);

    ep->effect_vars.basic2.efimage->translate.x += ep->effect_vars.basic2.vel.x;
    ep->effect_vars.basic2.efimage->translate.y += ep->effect_vars.basic2.vel.y;
}

// 0x800FDC04
efParticle* efParticle_DamageNormalLight_MakeEffect(Vec3f *pos, s32 player, s32 size, bool32 is_static)
{
    GObj *effect_gobj;
    efParticle *efpart;
    efImage *efimage;
    efStruct *ep;
    f32 angle;
    f32 vel;
    f32 scale;

    ep = efManager_GetStructNoForceReturn();

    if (ep == NULL)
    {
        return NULL;
    }
    effect_gobj = omMakeGObjCommon(gOMObj_Kind_Effect, NULL, 6, 0x80000000);

    if (effect_gobj == NULL)
    {
        efManager_SetPrevAlloc(ep);

        return NULL;
    }
    effect_gobj->user_data = ep;

    efpart = func_ovl0_800CE9E8(gEffectBankIndex, D_ovl2_8012DF20[player]);

    if (efpart != NULL)
    {
        efimage = func_ovl0_800CE1DC(efpart, 0);

        if (efimage != NULL)
        {
            efimage->effect_gobj = effect_gobj;
            efimage->proc_dead = efImage_Default_ProcDead;

            func_ovl0_800CEA14(efpart);

            if (efimage->unk_effect_0x2A == 0)
            {
                return NULL;
            }
            omAddGObjCommonProc(effect_gobj, efParticle_Default_ProcUpdate, 1, 3);

            ep->effect_vars.basic2.efimage = efimage;

            efimage->translate = *pos;

            vel = (is_static != FALSE) ? 0.0F : ((rand_f32() * 38.0F) + 12.0F);

            angle = rand_f32() * DOUBLE_PI32;

            ep->effect_vars.basic2.vel.x = cosf(angle) * vel;
            ep->effect_vars.basic2.vel.y = __sinf(angle) * vel;

            scale = (size < 10) ? (((10 - size) * -0.05F) + 1.0F) : (((size - 10) * 0.13F) + 1.0F);

            efimage->scale.x = efimage->scale.y = efimage->scale.z = scale;
        }
        else efpart = efManager_DestroyParticleGObj(efpart, effect_gobj);
    }
    else efManager_DestroyParticleGObj(NULL, effect_gobj);

    return efpart;
}

// 0x800FDE3C
void efImage_DamageNormalHeavy_ProcDead(efImage *efimage)
{
    efStruct *ep = efGetStruct(efimage->effect_gobj);
    Vec3f pos = efimage->translate;

    efParticle_DamageNormalLight_MakeEffect(&pos, ep->effect_vars.damage_normal_heavy.player, ep->effect_vars.damage_normal_heavy.size, FALSE);
    efManager_SetPrevAlloc(efGetStruct(efimage->effect_gobj));
    omEjectGObjCommon(efimage->effect_gobj);
}

u8 efParticle_DamageNormalHeavy_Color1R[8] = { 255, 255, 255, 255, 255, 0, 0, 0 };
u8 efParticle_DamageNormalHeavy_Color1G[8] = { 255, 255, 255, 255, 255, 0, 0, 0 };
u8 efParticle_DamageNormalHeavy_Color1B[8] = { 255, 255, 255, 255, 255, 0, 0, 0 };
u8 efParticle_DamageNormalHeavy_Color2R[8] = { 255, 255, 255, 255, 255, 0, 0, 0 };
u8 efParticle_DamageNormalHeavy_Color2G[8] = { 255, 255, 255, 255, 255, 0, 0, 0 };
u8 efParticle_DamageNormalHeavy_Color2B[8] = { 255, 255, 255, 255, 255, 0, 0, 0 };

// 0x800FDEAC
efParticle* efParticle_DamageNormalHeavy_MakeEffect(Vec3f *pos, s32 player, s32 size)
{
    GObj *effect_gobj;
    efParticle *efpart;
    efImage *efimage;
    efStruct *ep;

    ep = efManager_GetStructNoForceReturn();

    if (ep == NULL)
    {
        return NULL;
    }
    effect_gobj = omMakeGObjCommon(gOMObj_Kind_Effect, NULL, 6, 0x80000000);

    if (effect_gobj == NULL)
    {
        efManager_SetPrevAlloc(ep);

        return NULL;
    }
    effect_gobj->user_data = ep;

    efpart = func_ovl0_800CE9E8(gEffectBankIndex, 0x64);

    if (efpart != NULL)
    {
        efimage = func_ovl0_800CE1DC(efpart, 0);

        if (efimage != NULL)
        {
            efimage->effect_gobj = effect_gobj;
            efimage->proc_dead = efImage_DamageNormalHeavy_ProcDead;

            func_ovl0_800CEA14(efpart);

            if (efimage->unk_effect_0x2A == 0)
            {
                return FALSE;
            }
            ep->effect_vars.damage_normal_heavy.size = (s32) efimage; // WHAT

            efimage->translate = *pos;

            ep->effect_vars.damage_normal_heavy.pos = *pos;
            ep->effect_vars.damage_normal_heavy.player = player;
            ep->effect_vars.damage_normal_heavy.size = size;

            efpart->color1.r = efParticle_DamageNormalHeavy_Color1R[player];
            efpart->color1.g = efParticle_DamageNormalHeavy_Color1G[player];
            efpart->color1.b = efParticle_DamageNormalHeavy_Color1B[player];
            efpart->color1.a = 255;

            efpart->color2.r = efParticle_DamageNormalHeavy_Color2R[player];
            efpart->color2.g = efParticle_DamageNormalHeavy_Color2G[player];
            efpart->color2.b = efParticle_DamageNormalHeavy_Color2B[player];
        }
        else efpart = efManager_DestroyParticleGObj(efpart, effect_gobj);
    }
    else efManager_DestroyParticleGObj(NULL, effect_gobj);

    return efpart;
}

// 0x800FE068
efParticle* func_ovl2_800FE068(Vec3f *pos, s32 size)
{
    GObj *effect_gobj;
    efParticle *efpart;
    efImage *efimage;
    efStruct *ep;
    f32 angle;
    f32 vel;
    f32 scale;

    ep = efManager_GetStructNoForceReturn();

    if (ep == NULL)
    {
        return NULL;
    }
    effect_gobj = omMakeGObjCommon(gOMObj_Kind_Effect, NULL, 6, 0x80000000);

    if (effect_gobj == NULL)
    {
        efManager_SetPrevAlloc(ep);

        return NULL;
    }
    effect_gobj->user_data = ep;

    efpart = func_ovl0_800CE9E8(gEffectBankIndex, 0x25);

    if (efpart != NULL)
    {
        efimage = func_ovl0_800CE1DC(efpart, 0);

        if (efimage != NULL)
        {
            efimage->effect_gobj = effect_gobj;
            efimage->proc_dead = efImage_Default_ProcDead;

            func_ovl0_800CEA14(efpart);

            if (efimage->unk_effect_0x2A == 0)
            {
                return NULL;
            }
            omAddGObjCommonProc(effect_gobj, efParticle_Default_ProcUpdate, 1, 3);

            ep->effect_vars.common.efimage = efimage;

            efimage->translate = *pos;

            vel = ((rand_f32() * 8.0F) + 2.0F);

            angle = rand_f32() * DOUBLE_PI32;

            ep->effect_vars.common.vel.x = cosf(angle) * vel;
            ep->effect_vars.common.vel.y = __sinf(angle) * vel;

            scale = (size < 10) ? (((10 - size) * -0.05F) + 1.0F) : (((size - 10) * 0.15F) + 1.0F);

            efimage->scale.x = efimage->scale.y = efimage->scale.z = scale;
        }
        else efpart = efManager_DestroyParticleGObj(efpart, effect_gobj);
    }
    else efManager_DestroyParticleGObj(NULL, effect_gobj);

    return efpart;
}

void func_ovl2_800FE260(GObj *effect_gobj)
{
    efStruct *ep = efGetStruct(effect_gobj);
    DObj *dobj = DObjGetStruct(effect_gobj);

    func_8000DF34(effect_gobj);

    if (dobj->mobj->unk_mobj_0xA0 <= 0.0F)
    {
        efManager_SetPrevAlloc(ep);
        omEjectGObjCommon(effect_gobj);
    }
    else
    {
        dobj->translate.x += ep->effect_vars.common.vel.x;
        dobj->translate.y += ep->effect_vars.common.vel.y;
    }
}

// 0x800FE2F4
efParticle* efParticle_DamageFire_MakeEffect(Vec3f *pos, s32 size)
{
    GObj *effect_gobj;
    efParticle *efpart;
    efImage *efimage;
    efStruct *ep;
    f32 angle;
    f32 vel;
    f32 scale;

    ep = efManager_GetStructNoForceReturn();

    if (ep == NULL)
    {
        return NULL;
    }
    effect_gobj = omMakeGObjCommon(gOMObj_Kind_Effect, NULL, 6, 0x80000000);

    if (effect_gobj == NULL)
    {
        efManager_SetPrevAlloc(ep);

        return NULL;
    }
    effect_gobj->user_data = ep;

    efpart = func_ovl0_800CE9E8(gEffectBankIndex, 0x4D);

    if (efpart != NULL)
    {
        efimage = func_ovl0_800CE1DC(efpart, 0);

        if (efimage != NULL)
        {
            efimage->effect_gobj = effect_gobj;
            efimage->proc_dead = efImage_Default_ProcDead;

            func_ovl0_800CEA14(efpart);

            if (efimage->unk_effect_0x2A == 0)
            {
                return NULL;
            }
            omAddGObjCommonProc(effect_gobj, efParticle_Default_ProcUpdate, 1, 3);

            ep->effect_vars.common.efimage = efimage;

            efimage->translate = *pos;

            vel = ((rand_f32() * 18.0F) + 12.0F);

            angle = rand_f32() * DOUBLE_PI32;

            ep->effect_vars.common.vel.x = cosf(angle) * vel;
            ep->effect_vars.common.vel.y = __sinf(angle) * vel;

            scale = (size < 10) ? (((10 - size) * -0.05F) + 1.0F) : (((size - 10) * 0.15F) + 1.0F);

            efimage->scale.x = efimage->scale.y = efimage->scale.z = scale;
        }
        else efpart = efManager_DestroyParticleGObj(efpart, effect_gobj);
    }
    else efManager_DestroyParticleGObj(NULL, effect_gobj);

    return efpart;
}

// 0x800FE4EC
efParticle* func_ovl2_800FE4EC(Vec3f *pos, s32 size)
{
    GObj *effect_gobj;
    efParticle *efpart;
    efImage *efimage;
    efStruct *ep;
    f32 angle;
    f32 vel;
    f32 scale;

    ep = efManager_GetStructNoForceReturn();

    if (ep == NULL)
    {
        return NULL;
    }
    effect_gobj = omMakeGObjCommon(gOMObj_Kind_Effect, NULL, 6, 0x80000000);

    if (effect_gobj == NULL)
    {
        efManager_SetPrevAlloc(ep);

        return NULL;
    }
    effect_gobj->user_data = ep;

    efpart = func_ovl0_800CE9E8(gEffectBankIndex, 0x53);

    if (efpart != NULL)
    {
        efimage = func_ovl0_800CE1DC(efpart, 0);

        if (efimage != NULL)
        {
            efimage->effect_gobj = effect_gobj;
            efimage->proc_dead = efImage_Default_ProcDead;

            func_ovl0_800CEA14(efpart);

            if (efimage->unk_effect_0x2A == 0)
            {
                return NULL;
            }
            omAddGObjCommonProc(effect_gobj, efParticle_Default_ProcUpdate, 1, 3);

            ep->effect_vars.common.efimage = efimage;

            efimage->translate = *pos;

            vel = ((rand_f32() * 7.0F) + 3.0F);

            angle = rand_f32() * DOUBLE_PI32;

            ep->effect_vars.common.vel.x = cosf(angle) * vel;
            ep->effect_vars.common.vel.y = __sinf(angle) * vel;

            scale = (size < 5) ? (((5 - size) * -0.08F) + 1.0F) : (((size - 5) * 0.15F) + 1.0F);

            efimage->scale.x = efimage->scale.y = efimage->scale.z = scale;
        }
        else efpart = efManager_DestroyParticleGObj(efpart, effect_gobj);
    }
    else efManager_DestroyParticleGObj(NULL, effect_gobj);

    return efpart;
}

extern void *D_ovl2_8012DF24[];

// 0x800FE6E4
GObj* efParticle_DamageSlash_MakeEffect(Vec3f *pos, s32 size, f32 rotate)
{
    GObj *effect_gobj;
    DObj *dobj;
    f32 scale;

    effect_gobj = func_ovl2_800FDAFC(&D_ovl2_8012DF24);

    if (effect_gobj == NULL)
    {
        return NULL;
    }
    dobj = DObjGetStruct(effect_gobj);

    dobj->translate = *pos;

    dobj->rotate.z = rotate;

    scale = (size < 5) ? (((5 - size) * -0.08F) + 1.0F) : (((size - 5) * 0.18F) + 1.0F);

    dobj->scale.x = dobj->scale.y = scale;

    return effect_gobj;
}

// 0x800FE9B4
efParticle* efParticle_FlameLR_MakeEffect(Vec3f *pos, s32 lr)
{
    GObj *effect_gobj;
    efParticle *efpart;
    efImage *efimage;
    efStruct *ep;
    f32 angle;
    f32 vel;
    f32 scale;

    ep = efManager_GetStructNoForceReturn();

    if (ep == NULL)
    {
        return NULL;
    }
    effect_gobj = omMakeGObjCommon(gOMObj_Kind_Effect, NULL, 6, 0x80000000);

    if (effect_gobj == NULL)
    {
        efManager_SetPrevAlloc(ep);

        return NULL;
    }
    effect_gobj->user_data = ep;

    efpart = func_ovl0_800CE9E8(gEffectBankIndex, 0x12);

    if (efpart != NULL)
    {
        efimage = func_ovl0_800CE1DC(efpart, 0);

        if (efimage != NULL)
        {
            efimage->effect_gobj = effect_gobj;
            efimage->proc_dead = efImage_Default_ProcDead;

            func_ovl0_800CEA14(efpart);

            if (efimage->unk_effect_0x2A == 0)
            {
                return NULL;
            }
            omAddGObjCommonProc(effect_gobj, efParticle_Default_ProcUpdate, 1, 3);

            ep->effect_vars.common.efimage = efimage;

            efimage->translate = *pos;

            efimage->translate.x += (rand_f32() * 300.0F) + (-150.0F);
            efimage->translate.y += (rand_f32() * 200.0F) + (-150.0F);

            angle = rand_f32() * HALF_PI32;

            ep->effect_vars.common.vel.x = cosf(angle) * 20.0F * -lr;
            ep->effect_vars.common.vel.y = __sinf(angle) * 20.0F;

            efimage->scale.x = efimage->scale.y = efimage->scale.z = (rand_f32() * 1) + 1.0F;
        }
        else efpart = efManager_DestroyParticleGObj(efpart, effect_gobj);
    }
    else efManager_DestroyParticleGObj(NULL, effect_gobj);

    return efpart;
}

// 0x800FE9B4
efParticle* efParticle_FlameRandom_MakeEffect(Vec3f *pos)
{
    GObj *effect_gobj;
    efParticle *efpart;
    efImage *efimage;
    efStruct *ep;
    f32 angle;
    f32 vel;
    f32 scale;

    ep = efManager_GetStructNoForceReturn();

    if (ep == NULL)
    {
        return NULL;
    }
    effect_gobj = omMakeGObjCommon(gOMObj_Kind_Effect, NULL, 6, 0x80000000);

    if (effect_gobj == NULL)
    {
        efManager_SetPrevAlloc(ep);

        return NULL;
    }
    effect_gobj->user_data = ep;

    efpart = func_ovl0_800CE9E8(gEffectBankIndex, 0x55);

    if (efpart != NULL)
    {
        efimage = func_ovl0_800CE1DC(efpart, 0);

        if (efimage != NULL)
        {
            efimage->effect_gobj = effect_gobj;
            efimage->proc_dead = efImage_Default_ProcDead;

            func_ovl0_800CEA14(efpart);

            if (efimage->unk_effect_0x2A == 0)
            {
                return NULL;
            }
            omAddGObjCommonProc(effect_gobj, efParticle_Default_ProcUpdate, 1, 3);

            ep->effect_vars.common.efimage = efimage;

            efimage->translate = *pos;

            angle = (rand_f32() * HALF_PI32) + QUART_PI32;

            ep->effect_vars.common.vel.x = cosf(angle) * 15.0F;
            ep->effect_vars.common.vel.y = __sinf(angle) * 15.0F;

            efimage->scale.x = efimage->scale.y = efimage->scale.z = (rand_f32() * 1) + 1.0F;
        }
        else efpart = efManager_DestroyParticleGObj(efpart, effect_gobj);
    }
    else efManager_DestroyParticleGObj(NULL, effect_gobj);

    return efpart;
}

// 0x800FEB58
efParticle* efParticle_FlameStatic_MakeEffect(Vec3f *pos)
{
    GObj *effect_gobj;
    efParticle *efpart;
    efImage *efimage;
    efStruct *ep;
    f32 angle;
    f32 vel;
    f32 scale;

    ep = efManager_GetStructNoForceReturn();

    if (ep == NULL)
    {
        return NULL;
    }
    effect_gobj = omMakeGObjCommon(gOMObj_Kind_Effect, NULL, 6, 0x80000000);

    if (effect_gobj == NULL)
    {
        efManager_SetPrevAlloc(ep);

        return NULL;
    }
    effect_gobj->user_data = ep;

    efpart = func_ovl0_800CE9E8(gEffectBankIndex, 0x55);

    if (efpart != NULL)
    {
        efimage = func_ovl0_800CE1DC(efpart, 0);

        if (efimage != NULL)
        {
            efimage->effect_gobj = effect_gobj;
            efimage->proc_dead = efImage_Default_ProcDead;

            func_ovl0_800CEA14(efpart);

            if (efimage->unk_effect_0x2A == 0)
            {
                return NULL;
            }
            omAddGObjCommonProc(effect_gobj, efParticle_Default_ProcUpdate, 1, 3);

            ep->effect_vars.common.efimage = efimage;

            efimage->translate = *pos;

            ep->effect_vars.common.vel.x = 0.0F;
            ep->effect_vars.common.vel.y = 0.0F;

            efimage->scale.x = efimage->scale.y = efimage->scale.z = (rand_f32() * 1) + 1.0F;
        }
        else efpart = efManager_DestroyParticleGObj(efpart, effect_gobj);
    }
    else efManager_DestroyParticleGObj(NULL, effect_gobj);

    return efpart;
}