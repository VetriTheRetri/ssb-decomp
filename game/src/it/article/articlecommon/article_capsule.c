#include "article.h"

bool32 jtgt_ovl3_80173F90(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATCAPSULE_GRAVITY, ATCAPSULE_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80173FCC(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80174098);

    return FALSE;
}

bool32 func_ovl3_80173FF4(GObj *article_gobj)
{
    if (func_ovl3_801730D4(article_gobj) != FALSE)
    {
        return TRUE;
    }
    else func_ovl3_80174428(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80174030(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.4F, func_ovl3_80174064);
}

extern ArticleStatusDesc Article_Capsule_Status[]; // Capsule states

void func_ovl3_80174064(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Capsule_Status, 0);
}

void func_ovl3_80174098(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    func_ovl3_80173F78(ap);

    ap->is_damage_all = TRUE;

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_Normal;

    func_ovl3_80172EC8(article_gobj, Article_Capsule_Status, 1);
}

void jtgt_ovl3_801740FC(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Capsule_Status, 2);
}

bool32 jtgt_ovl3_80174124(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATCAPSULE_GRAVITY, ATCAPSULE_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80174160(GObj *article_gobj)
{
    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_ALL) != FALSE)
    {
        if (func_ovl3_801730D4(article_gobj) != FALSE)
        {
            return TRUE;
        }
        else func_ovl3_80174428(article_gobj);
    }
    return FALSE;
}

void jtgt_ovl3_801741B0(GObj *article_gobj) // Capsule gets thrown
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_damage_all = TRUE;

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_Normal;

    func_ovl3_80172EC8(article_gobj, Article_Capsule_Status, 3);
}

bool32 func_ovl3_801741F0(GObj *article_gobj) // Unused
{
    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80174214(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.4F, func_ovl3_80174064);
}

void jtgt_ovl3_80174248(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Capsule_Status, 4);
}

extern u8 D_NF_00000098;

extern ArticleSpawnData Article_Capsule_Data;

bool32 jtgt_ovl3_80174270(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->at_multi++;

    if (ap->at_multi == 6)
    {
        return TRUE;
    }
    func_ovl3_80173180(article_gobj, (ArticleHitEvent*)((uintptr_t)*Article_Capsule_Data.p_file + &D_NF_00000098)); // Linker thing

    return FALSE;
}

GObj* jtgt_ovl3_801742CC(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *gobj = func_ovl3_8016E174(spawn_gobj, &Article_Capsule_Data, pos, vel, flags);

    if (gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(gobj);

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return gobj;
}

void func_ovl3_80174340(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->at_multi = 0;
    ap->x340_flag_b0123 = 0;
    ap->article_hit[0].hit_sfx = 1;
    ap->article_hit[0].stale = ARTICLE_STALE_DEFAULT;

    func_800269C0(1U);

    ap->article_hit[0].flags_0x4C_b1 = TRUE;
    ap->article_hit[0].can_deflect = FALSE;
    ap->article_hit[0].can_reflect = FALSE;

    ap->article_hit[0].element = gmHitCollision_Element_Fire;

    ap->article_hit[0].clang = FALSE;

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_None;

    func_ovl3_8017279C(article_gobj);
    func_ovl3_8017275C(article_gobj);
    func_ovl3_80173180(article_gobj, (ArticleHitEvent*)((uintptr_t)*Article_Capsule_Data.p_file + &D_NF_00000098));
}

void func_ovl3_801743F4(GObj *article_gobj)
{
    func_ovl3_80174340(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Capsule_Status, 5);
}

void func_ovl3_80174428(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    Effect_Unk *ep;

    ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ep->effect_info->scale.y = ep->effect_info->scale.z = ATCAPSULE_EXPLODE_SCALE;
    }
    func_ovl2_801008F4(1);
    DObjGetStruct(article_gobj)->unk_0x54 = 2;
    func_ovl3_801743F4(article_gobj);
}