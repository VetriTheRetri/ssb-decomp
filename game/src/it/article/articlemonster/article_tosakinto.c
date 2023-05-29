#include "article.h"

bool32 jtgt_ovl3_8017E7A0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATTOSAKINTO_GRAVITY, ATTOSAKINTO_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_8017E7CC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80173680(article_gobj);

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        ap->phys_info.vel.y = ATTOSAKINTO_FLAP_VEL_Y;

        func_ovl3_8017EA14(article_gobj);

        func_800269C0(0x8DU);
    }
    return FALSE;
}

extern ArticleStatusDesc Article_Tosakinto_Status[];

void func_ovl3_8017E828(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->at_multi = ATTOSAKINTO_LIFETIME;

    if (ap->at_kind == At_Kind_Tosakinto)
    {
        func_800269C0(0x143U);
    }
    atCommon_UpdateArticleStatus(article_gobj, Article_Tosakinto_Status, 0);
}

bool32 jtgt_ovl3_8017E880(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATTOSAKINTO_GRAVITY, ATTOSAKINTO_T_VEL);

    if (ap->at_multi == 0)
    {
        return TRUE;
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_8017E8CC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80173680(article_gobj);

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        ap->phys_info.vel.y = ATTOSAKINTO_FLAP_VEL_Y;

        if (rand_u16_range(2) != 0)
        {
            ap->phys_info.vel.x = -ap->phys_info.vel.x;
        }
        func_800269C0(0x8DU);
    }
    return FALSE;
}

extern intptr_t D_NF_0000B708;
extern intptr_t D_NF_0000B7CC;
extern intptr_t D_NF_0000B90C;

void func_ovl3_8017E93C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    void *s;
    s32 unused[2];

    ap->article_vars.tosakinto.pos = joint->translate;

    ap->phys_info.vel.y = ATTOSAKINTO_FLAP_VEL_Y;
    ap->phys_info.vel.x = ATTOSAKINTO_FLAP_VEL_X;

    if (ap->at_kind == At_Kind_Tosakinto)
    {
        s = ArticleGetPData(ap, D_NF_0000B708, D_NF_0000B7CC); // Linker thing

        func_8000BD1C(joint->next, s, 0.0F);

        s = ArticleGetPData(ap, D_NF_0000B708, D_NF_0000B90C); // Linker thing

        func_8000BD54(joint->next->mobj, s, 0.0F);

        func_8000DF34(article_gobj);
    }
}

void func_ovl3_8017EA14(GObj *article_gobj)
{
    func_ovl3_8017E93C(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_Tosakinto_Status, 1);
}

bool32 jtgt_ovl3_8017EA48(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_8017E828(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_8017EA98(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Tosakinto_Data;

GObj* jtgt_ovl3_8017EAD8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Tosakinto_Data, pos, vel, flags);
    DObj *joint;
    Article_Struct *ap;

    if (article_gobj != NULL)
    {
        func_ovl3_8017279C(article_gobj);

        joint = DObjGetStruct(article_gobj);

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = *pos;

        ap = ArticleGetStruct(article_gobj);

        ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        joint->translate.y -= ap->attributes->objectcoll_bottom;

        func_8000BD1C(joint, ArticleGetPData(ap, D_NF_0000B708, D_NF_00013624), 0.0F); // Linker thing
    }
    return article_gobj;
}