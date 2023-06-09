#include "article.h"

bool32 jtgt_ovl3_80174E30(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATSWORD_GRAVITY, ATSWORD_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80174E68(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80174EF8);

    return FALSE;
}

bool32 jtgt_ovl3_80174E90(GObj *article_gobj)
{
    func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80174EC4);

    return FALSE;
}

extern ArticleStatusDesc Article_Bat_Status[];

void func_ovl3_80174EC4(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_Bat_Status, 0);
}

void func_ovl3_80174EF8(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    atCommon_UpdateArticleStatus(article_gobj, Article_Bat_Status, 1);
}

void jtgt_ovl3_80174F3C(GObj *article_gobj)
{
    DObjGetStruct(article_gobj)->rotate.y = 0.0F;

    atCommon_UpdateArticleStatus(article_gobj, Article_Bat_Status, 2);
}

bool32 jtgt_ovl3_80174F70(GObj *article_gobj)
{
    func_ovl3_80172558(atGetStruct(article_gobj), ATBAT_GRAVITY, ATBAT_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80174FA8(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80174EC4);
}

void jtgt_ovl3_80175000(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Bat_Status, 3);

    DObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;
}

bool32 jtgt_ovl3_80175044(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80174EC4);
}

void jtgt_ovl3_80175074(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Bat_Status, 4);
    DObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;
}

extern ArticleSpawnData Article_Bat_Data;

GObj* jtgt_ovl3_801750B8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Bat_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = atGetStruct(article_gobj);

        DObjGetStruct(article_gobj)->rotate.y = HALF_PI32;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}
