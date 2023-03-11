#include "article.h"

#define HALF_PI32 1.5707964F

bool32 jtgt_ovl3_80174B50(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATSWORD_GRAVITY, ATSWORD_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80174B8C(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80174C18);

    return FALSE;
}

bool32 jtgt_ovl3_80174BB4(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80174BE4);
}

extern ArticleStatusDesc Article_Sword_Status[];

void func_ovl3_80174BE4(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Sword_Status, 0);
}

void func_ovl3_80174C18(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_Sword_Status, 1);
}

void jtgt_ovl3_80174C5C(GObj *article_gobj)
{
    JObjGetStruct(article_gobj)->rotate.y = 0.0F;

    func_ovl3_80172EC8(article_gobj, Article_Sword_Status, 2);
}

bool32 jtgt_ovl3_80174C90(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80174BE4);
}

bool32 jtgt_ovl3_80174CC0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

void jtgt_ovl3_80174CE8(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Sword_Status, 3);

    JObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;
}

void jtgt_ovl3_80174D2C(GObj *article_gobj)
{
    func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80174BE4);
}

void jtgt_ovl3_80174D5C(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Sword_Status, 4);

    JObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;
}

extern ArticleSpawnData Article_Sword_Data;

GObj* jtgt_ovl3_80174DA0(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Sword_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        JObjGetStruct(article_gobj)->rotate.y = HALF_PI32;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}