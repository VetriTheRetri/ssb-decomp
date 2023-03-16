#include "article.h"
#include "fighter.h"

extern intptr_t D_NF_00009430;
extern intptr_t D_NF_00009520;

void func_ovl3_8017C690(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    void *t = (void*) (((uintptr_t)ap->attributes->unk_0x0 - (intptr_t)&D_NF_00009430) + (intptr_t)&D_NF_00009520); // Linker thing

    func_8000BD54(joint->next->next->unk_0x8->mobj, t, 0.0F);
    func_8000DF34(article_gobj);
}

void func_ovl3_8017C6F8(GObj *article_gobj)
{
    DObj *joint = DObjGetStruct(article_gobj);

    joint->next->unk_0x8->mobj->unk_image_0x94 = 0;
}

bool32 jtgt_ovl3_8017C710(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATMBALL_GRAVITY, ATMBALL_T_VEL);
    func_ovl3_801713F4(article_gobj);

    joint->next->unk_0x8->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 func_ovl3_8017C768(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_8017C7FC);

    return FALSE;
}

bool32 jtgt_ovl3_8017C790(GObj *article_gobj)
{
    func_ovl3_80173B24(article_gobj, 0.2F, 0.2F, func_ovl3_8017C7C8);

    return FALSE;
}

extern ArticleStatusDesc Article_M_Ball_Status[];

void func_ovl3_8017C7C8(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_M_Ball_Status, 0);
}

void func_ovl3_8017C7FC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_M_Ball_Status, 1);
}

void jtgt_ovl3_8017C840(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    DObjGetStruct(article_gobj)->rotate.y = 0.0F;

    ap->article_vars.m_ball.owner_gobj = ap->owner_gobj;

    func_ovl3_80172EC8(article_gobj, Article_M_Ball_Status, 2);
}

bool32 jtgt_ovl3_8017C880(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATMBALL_GRAVITY, ATMBALL_T_VEL);
    func_ovl3_801713F4(article_gobj);

    joint->next->unk_0x8->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 jtgt_ovl3_8017C8D8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->article_vars.m_ball.is_rebound != FALSE)
    {
        func_ovl3_80173C68(article_gobj, 0.2F, 0.2F, func_ovl3_8017CC88);
    }
    else
    {
        func_ovl3_80173B24(article_gobj, 0.2F, 0.2F, func_ovl3_8017CC88);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017C94C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

    ap->article_vars.m_ball.is_rebound = TRUE;

    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8017C97C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Fighter_Struct *fp;
    GObj *fighter_gobj;

    ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

    ap->article_vars.m_ball.is_rebound = TRUE;

    func_ovl3_80172FE0(article_gobj);

    fighter_gobj = ap->article_vars.m_ball.owner_gobj;
    ap->owner_gobj = fighter_gobj;
    fp = FighterGetStruct(fighter_gobj);

    ap->team = fp->team;
    ap->port_index = fp->player_id;
    ap->player_number = fp->player_number;
    ap->unk_0x16 = fp->offset_hit_type;

    return FALSE;
}

void jtgt_ovl3_8017C9E0(GObj *article_gobj)
{
    func_ovl3_8017C690(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_M_Ball_Status, 3);
}

void jtgt_ovl3_8017CA14(GObj *article_gobj)
{
    func_ovl3_8017C690(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_M_Ball_Status, 4);
}
