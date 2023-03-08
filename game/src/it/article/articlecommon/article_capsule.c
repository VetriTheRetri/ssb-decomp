#include "article.h"

bool32 jtgt_ovl3_80173F90(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ARTICLE_CAPSULE_GRAVITY, ARTICLE_CAPSULE_T_VEL);
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

extern ArticleLogicDesc Article_Capsule_Status[]; // Capsule states

void func_ovl3_80174064(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Capsule_Status, 0);
}