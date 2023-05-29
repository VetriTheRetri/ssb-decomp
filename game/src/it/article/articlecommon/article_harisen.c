#include "article.h"



void func_ovl3_80175140(GObj *article_gobj, f32 scale)
{
    DObjGetStruct(article_gobj)->scale.x = scale;
    DObjGetStruct(article_gobj)->scale.y = scale;
    DObjGetStruct(article_gobj)->scale.z = scale;
}

bool32 jtgt_ovl3_80175160(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATHARISEN_GRAVITY, ATHARISEN_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80175198(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80175228);

    return FALSE;
}

bool32 jtgt_ovl3_801751C0(GObj *article_gobj)
{
    func_ovl3_80173B24(article_gobj, 0.0F, 0.3F, func_ovl3_801751F4);

    return FALSE;
}

extern ArticleStatusDesc Article_Harisen_Status[];

void func_ovl3_801751F4(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_Harisen_Status, 0);
}

void func_ovl3_80175228(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    atCommon_UpdateArticleStatus(article_gobj, Article_Harisen_Status, 1);
}

void jtgt_ovl3_8017526C(GObj *article_gobj)
{
    DObj *joint = DObjGetStruct(article_gobj);

    func_80008CC0(joint, 0x20U, 0U);

    joint->rotate.y = 0.0F;

    atCommon_UpdateArticleStatus(article_gobj, Article_Harisen_Status, 2);
}

bool32 jtgt_ovl3_801752C0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATHARISEN_GRAVITY, ATHARISEN_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801752F8(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.0F, 0.3F, func_ovl3_801751F4);
}

bool32 jtgt_ovl3_80175328(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

void jtgt_ovl3_80175350(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Harisen_Status, 3);

    DObjGetStruct(article_gobj)->next->rotate.y = -HALF_PI32;
}

bool32 jtgt_ovl3_80175394(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.0F, 0.3F, func_ovl3_801751F4);
}

void jtgt_ovl3_801753C4(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Harisen_Status, 4);

    DObjGetStruct(article_gobj)->next->rotate.y = -HALF_PI32;
}

extern u8 D_NF_00002198;
extern s32 D_ovl3_80189A70[2];

void func_ovl3_80175408(GObj *article_gobj, s32 index) // Unused
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_8000BD8C(article_gobj, ((D_ovl3_80189A70[index] + (uintptr_t)ap->attributes->unk_0x0) - (uintptr_t)&D_NF_00002198), 0.0F); // Linker thing
    func_8000DF34(article_gobj);
}

extern ArticleSpawnData Article_Harisen_Data;

GObj* jtgt_ovl3_80175460(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Harisen_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        DObjGetStruct(article_gobj)->rotate.y = HALF_PI32;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}