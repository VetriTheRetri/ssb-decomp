#include "article.h"

void func_ovl3_80177060(GObj *article_gobj, s32 arg1)
{
    s32 unused;
    JObj *joint = JObjGetStruct(article_gobj);
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Effect_Struct *ep;

    func_ovl3_80177218(article_gobj);

    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = 1.4F;
        ep->effect_info->scale.y = 1.4F;
        ep->effect_info->scale.z = 1.4F;
    }
    func_ovl2_801008F4(1);

    JObjGetStruct(article_gobj)->unk_0x54 = 2;

    ap->article_hit[0].hit_sfx = 1;

    func_ovl3_8017275C(article_gobj);
    func_ovl3_8017279C(article_gobj);
    func_ovl3_80177C30(article_gobj);
}

extern u8 D_NF_00003310;
extern u8 D_NF_000033F8;
extern u8 D_NF_000034C0;

void func_ovl3_80177104(GObj *article_gobj, u8 lr)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    JObj *joint = JObjGetStruct(article_gobj);
    void *dll = (void*)((uintptr_t)((uintptr_t)ap->attributes->unk_0x0 - (uintptr_t)&D_NF_000033F8) + &D_NF_000034C0); // Linker thing
    void *dlr = (void*)((uintptr_t)((uintptr_t)ap->attributes->unk_0x0 - (uintptr_t)&D_NF_000033F8) + &D_NF_00003310); // Linker thing

    if (lr != 0)
    {
        ap->lr = RIGHT;
        ap->phys_info.vel.x = ATBOMBHEI_WALK_VEL_X;

        joint->display_list = dlr;
    }
    else
    {
        ap->lr = LEFT;
        ap->phys_info.vel.x = -ATBOMBHEI_WALK_VEL_X;

        joint->display_list = dll;
    }
}

void func_ovl3_80177180(GObj *article_gobj, u8 is_explode)
{
    s32 unused[4];
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    atCommonAttributes *attributes = ap->attributes;
    JObj *joint = JObjGetStruct(article_gobj);

    if ((ap->coll_data.unk_0x56 & MPCOLL_MASK_GROUND) || (is_explode != FALSE))
    {
        Vec3f pos = joint->translate;

        pos.y += attributes->unk_0x2E;

        func_ovl2_800FF3F4(&pos, ap->lr, 1.0F);
    }
}

void func_ovl3_80177208(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_Normal;
}

void func_ovl3_80177218(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_None;
}

bool32 jtgt_ovl3_80177224(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATBOMBHEI_GRAVITY, ATBOMBHEI_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}