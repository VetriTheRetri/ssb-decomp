#include "article.h"

void func_ovl3_80176110(GObj *article_gobj)
{
    atCommon_CheckSetColAnimIndex(article_gobj, ATHAMMER_WEAR_COLANIM_ID, 0);
}

bool32 jtgt_ovl3_80176134(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATHAMMER_GRAVITY, ATHAMMER_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_8017616C(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_801761F8);

    return FALSE;
}

bool32 jtgt_ovl3_80176194(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.5F, 0.2F, func_ovl3_801761C4);
}

extern ArticleStatusDesc Article_Hammer_Status[];

void func_ovl3_801761C4(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Hammer_Status, 0);
}

extern ArticleStatusDesc Article_Hammer_Status[];

void func_ovl3_801761F8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_Hammer_Status, 1);
}

void jtgt_ovl3_8017623C(GObj *article_gobj)
{
    DObjGetStruct(article_gobj)->rotate.y = 0.0F;

    func_ovl3_80172EC8(article_gobj, Article_Hammer_Status, 2);
}

bool32 jtgt_ovl3_80176270(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATHAMMER_GRAVITY, ATHAMMER_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801762A8(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.5F, 0.2F, func_ovl3_801761C4);
}

bool32 jtgt_ovl3_801762D8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

void jtgt_ovl3_80176300(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Hammer_Status, 3);

    DObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;

    ftSpecialItem_BGMCheckFighters();
}

bool32 jtgt_ovl3_80176348(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.5F, 0.2F, func_ovl3_801761C4);
}

void jtgt_ovl3_80176378(GObj *article_gobj)
{
    func_ovl3_80172FBC(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Hammer_Status, 4);

    DObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;

    ftSpecialItem_BGMCheckFighters();
}

extern ArticleSpawnData Article_Hammer_Data;

GObj *jtgt_ovl3_801763C8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Hammer_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        DObjGetStruct(article_gobj)->rotate.y = HALF_PI32;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}