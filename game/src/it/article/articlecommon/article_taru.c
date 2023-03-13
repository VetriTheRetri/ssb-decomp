#include "article.h"

bool32 jtgt_ovl3_80179BA0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATTARU_GRAVITY, ATTARU_T_VEL);

    JObjGetStruct(article_gobj)->rotate.z += ap->article_vars.taru.roll_rotate_speed;

    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80179BF8(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80179D1C);

    return FALSE;
}

bool32 func_ovl3_80179C20(GObj *article_gobj)
{
    func_800269C0(0x3BU);

    func_ovl3_801791F4(&JObjGetStruct(article_gobj)->translate);

    if (func_ovl3_801730D4(article_gobj) != FALSE)
    {
        return TRUE;
    }
    else func_ovl3_8017A30C(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80179C78(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->percent_damage >= ATTARU_HEALTH_MAX)
    {
        return func_ovl3_80179C20(article_gobj);
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80179CB8(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.5F, 0.2F, func_ovl3_80179CE8);
}

extern ArticleStatusDesc Article_Taru_Status[];

void func_ovl3_80179CE8(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Taru_Status, 0);
}

void func_ovl3_80179D1C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_Taru_Status, 1);
}

void jtgt_ovl3_80179D60(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Taru_Status, 2);
}

bool32 func_ovl3_80179D88(GObj *article_gobj, f32 vel_mod)
{
    s32 filler;
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    bool32 is_collide_ground = func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND);

    if (func_ovl3_801737EC(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), vel_mod, NULL) != FALSE)
    {
        func_ovl3_80172508(article_gobj);
    }
    if (is_collide_ground != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80179DEC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->lifetime = ATTARU_LIFETIME;

    ap->phys_info.vel.y = 0.0F;

    func_ovl3_80172EC8(article_gobj, Article_Taru_Status, 6);
}