#include "article.h"

bool32 func_ovl3_8017C090(GObj *article_gobj)
{
    if ((f32)FLOAT_NEG_MAX == DObjGetStruct(article_gobj)->dobj_f0)
    {
        func_ovl3_8017C0D4(article_gobj);
    }
    return FALSE;
}

extern ArticleStatusDesc Article_POW_Status[];

void func_ovl3_8017C0D4(GObj *article_gobj)
{
    Article_Struct *ap;

    atCommon_UpdateArticleStatus(article_gobj, Article_POW_Status, 0);

    ap = atGetStruct(article_gobj), ap->article_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
}

bool32 func_ovl3_8017C110(GObj *article_gobj)
{
    if ((f32)FLOAT_NEG_MAX == DObjGetStruct(article_gobj)->dobj_f0)
    {
        func_ovl2_8010986C();

        return TRUE;
    }
    else return FALSE;
}

extern intptr_t D_NF_000011F8;
extern intptr_t D_NF_00001288;

bool32 func_ovl3_8017C15C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->proc_update = func_ovl3_8017C110;
    ap->article_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_8000BD1C(DObjGetStruct(article_gobj), ArticleGetPData(ap, D_NF_000011F8, D_NF_00001288), 0.0F); // Linker thing
    func_8000DF34(article_gobj);
    func_800269C0(0x117U);
    func_ovl2_801008F4(3);
    func_ovl2_80109B4C();

    return FALSE;
}

extern ArticleSpawnData Article_POW_Data;

GObj* jtgt_ovl3_8017C1E0(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = itManager_CreateItem(spawn_gobj, &Article_POW_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = atGetStruct(article_gobj);

        ap->article_hurt.interact_mask = GMHITCOLLISION_MASK_FIGHTER;
    }
    return article_gobj;
}
