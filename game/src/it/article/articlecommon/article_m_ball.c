#include "article.h"
#include "fighter.h"
#include "gmmatch.h"

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

    joint->next->unk_0x8->mobj->unk_mobj_0x94 = 0;
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

    ap->is_allow_pickup = FALSE;

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

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->article_vars.m_ball.is_rebound = TRUE;

    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8017C97C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Fighter_Struct *fp;
    GObj *fighter_gobj;

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->article_vars.m_ball.is_rebound = TRUE;

    func_ovl3_80172FE0(article_gobj);

    fighter_gobj = ap->article_vars.m_ball.owner_gobj;
    ap->owner_gobj = fighter_gobj;
    fp = FighterGetStruct(fighter_gobj);

    ap->team = fp->team;
    ap->port_id = fp->port_id;
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

extern s32 D_ovl3_80189450;

bool32 jtgt_ovl3_8017CA48(GObj *m_ball_gobj)
{
    Article_Struct *m_ball_ap = ArticleGetStruct(m_ball_gobj);
    Article_Struct *monster_ap;
    GObj *monster_gobj;
    Vec3f vel;
    s32 unused[2];

    if (m_ball_ap->at_multi == 0)
    {
        vel.z = 0.0F;
        vel.y = 0.0F;
        vel.x = 0.0F;

        if (D_ovl3_80189450 == 0)
        {
            func_ovl3_80173228(m_ball_gobj);

            return TRUE;
        }
        monster_gobj = func_ovl3_8016F238(m_ball_gobj, D_ovl3_80189450 + (At_Kind_MonsterStart - 1), &DObjGetStruct(m_ball_gobj)->translate, &vel, (ARTICLE_FLAG_PROJECT | ARTICLE_MASK_SPAWN_ARTICLE));

        if (monster_gobj != NULL)
        {
            monster_ap = ArticleGetStruct(monster_gobj);

            monster_ap->owner_gobj = m_ball_ap->owner_gobj;
            monster_ap->team = m_ball_ap->team;
            monster_ap->port_id = m_ball_ap->port_id;
            monster_ap->unk_0x16 = m_ball_ap->unk_0x16;
            monster_ap->player_number = m_ball_ap->player_number;
            monster_ap->display_state = m_ball_ap->display_state;
        }
        return TRUE;
    }
    m_ball_ap->at_multi--;

    if (m_ball_ap->article_vars.m_ball.effect_gobj != NULL)
    {
        DObjGetStruct(m_ball_ap->article_vars.m_ball.effect_gobj)->translate = DObjGetStruct(m_ball_gobj)->translate;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017CB38(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl2_800FC67C(ap->unk_0x2D0) == FALSE)
    {
        ap->x2CF_flag_b1 = FALSE;

        func_ovl3_8017CDE4(article_gobj);
    }
    return FALSE;
}

void func_ovl3_8017CB84(GObj *article_gobj)
{
    s32 unused[2];
    DObj *joint = DObjGetStruct(article_gobj);
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *next;
    DObj *child;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    next = joint->next;
    next->unk_0x54 ^= 2;

    child = joint->next->unk_0x8;
    child->unk_0x54 ^= 2;

    func_800269C0(0x8BU);

    ap->unk_0x2D0 = ap->coll_data.ground_line_id;

    ap->x2CF_flag_b1 = TRUE;

    if ((ap->port_id != -1) && (ap->port_id != GMMATCH_PLAYERS_MAX))
    {
        GObj *fighter_gobj = Match_Info->player_block[ap->port_id].fighter_gobj;

        if (fighter_gobj != NULL)
        {
            Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

            func_ovl2_800E806C(fp, 8, 20);
        }
    }
    ap->article_vars.m_ball.effect_gobj = func_ovl2_80102C28(&joint->translate);

    func_ovl3_8017C6F8(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;
    ap->article_hit.can_reflect = FALSE;
}

void func_ovl3_8017CC88(GObj *article_gobj)
{
    func_ovl3_8017CB84(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_M_Ball_Status, 5);
}

bool32 jtgt_ovl3_8017CCBC(GObj *m_ball_gobj)
{
    Article_Struct *m_ball_ap = ArticleGetStruct(m_ball_gobj);
    Article_Struct *monster_ap;
    GObj *monster_gobj;
    Vec3f vel;
    s32 unused[2];

    if (m_ball_ap->at_multi == 0)
    {
        vel.z = 0.0F;
        vel.y = 0.0F;
        vel.x = 0.0F;

        if (D_ovl3_80189450 == 0)
        {
            func_ovl3_80173228(m_ball_gobj);

            return TRUE;
        }
        monster_gobj = func_ovl3_8016F238(m_ball_gobj, D_ovl3_80189450 + (At_Kind_MonsterStart - 1), &DObjGetStruct(m_ball_gobj)->translate, &vel, (ARTICLE_FLAG_PROJECT | ARTICLE_MASK_SPAWN_ARTICLE));

        if (monster_gobj != NULL)
        {
            monster_ap = ArticleGetStruct(monster_gobj);

            monster_ap->owner_gobj = m_ball_ap->owner_gobj;
            monster_ap->team = m_ball_ap->team;
            monster_ap->port_id = m_ball_ap->port_id;
            monster_ap->unk_0x16 = m_ball_ap->unk_0x16;
            monster_ap->player_number = m_ball_ap->player_number;
            monster_ap->display_state = m_ball_ap->display_state;
        }
        return TRUE;
    }
    m_ball_ap->at_multi--;

    if (m_ball_ap->article_vars.m_ball.effect_gobj != NULL)
    {
        DObjGetStruct(m_ball_ap->article_vars.m_ball.effect_gobj)->translate = DObjGetStruct(m_ball_gobj)->translate;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017CDAC(GObj *article_gobj)
{
    func_ovl3_80173B24(article_gobj, 0.2F, 0.2F, func_ovl3_8017CC88);

    return FALSE;
}

void func_ovl3_8017CDE4(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_M_Ball_Status, 6);
}

extern ArticleSpawnData Article_M_Ball_Data;

GObj* jtgt_ovl3_8017CE0C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_M_Ball_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(article_gobj);
        Article_Struct *ap = ArticleGetStruct(article_gobj);
        Vec3f translate = joint->translate;

        joint->next->unk_0x54 = 2;
        joint->next->unk_0x8->unk_0x54 = 0;

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint->next->unk_0x8, 0x46U, 0U);

        joint->translate = translate;

        ap->at_multi = ATMBALL_SPAWN_WAIT;

        ap->article_vars.m_ball.is_rebound = FALSE;

        ap->x2D3_flag_b5 = TRUE;

        joint->rotate.z = 0.0F;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}