#include "article.h"
#include "fighter.h"
#include "ground.h"

bool32 jtgt_ovl3_80182630(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATSAWAMURA_GRAVITY, ATSAWAMURA_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_80182660(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_8018273C(article_gobj);
    }
    return FALSE;
}

extern ArticleStatusDesc Article_Sawamura_Status[];

void func_ovl3_801826A8(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Sawamura_Status, 0);
}

bool32 jtgt_ovl3_801826D0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        func_ovl3_80182AAC(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80182714(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_801826A8);

    return FALSE;
}

void func_ovl3_8018273C(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Sawamura_Status, 1);
}

bool32 func_ovl3_80182764(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATSAWAMURA_GRAVITY, ATSAWAMURA_T_VEL);

    if ((ap->lr == RIGHT) && ((Ground_Info->blastzone_right - ATSAWAMURA_DESPAWN_OFF_X) <= joint->translate.x))
    {
        return TRUE;
    }
    else if ((ap->lr == LEFT) && (joint->translate.x <= (Ground_Info->blastzone_left + ATSAWAMURA_DESPAWN_OFF_X)))
    {
        return TRUE;
    }
    else if (ap->at_multi == 0)
    {
        return TRUE;
    }
    ap->at_multi--;

    return FALSE;
}

void func_ovl3_8018285C(GObj *article_gobj, GObj *fighter_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    DObj *aj = DObjGetStruct(article_gobj);
    DObj *fj = DObjGetStruct(fighter_gobj);
    s32 unused;
    Vec3f dist;
    Vec3f target_pos;

    target_pos = fj->translate;

    target_pos.y += ATSAWAMURA_TARGET_POS_OFF_Y - fp->coll_data.object_coll.bottom;

    vec3f_sub(&dist, &target_pos, &aj->translate);

    ap->phys_info.vel.z = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.x = ATSAWAMURA_KICK_VEL_X;

    vec3_get_euler_rotation(&ap->phys_info.vel, 4, atan2f(dist.y, dist.x));

    ap->lr = (dist.x < 0.0F) ? LEFT : RIGHT;

    if (ap->lr == RIGHT)
    {
        aj->rotate.y = PI32;
    }
}

extern intptr_t D_NF_00011F40;
extern intptr_t D_NF_00012340;

void func_ovl3_80182958(GObj *article_gobj)
{
    GObj *fighter_gobj = gOMObjCommonLinks[GObjLinkIndex_Fighter];
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    GObj *victim_gobj;
    s32 unused2[3];
    DObj *joint = DObjGetStruct(article_gobj);
    f32 square_xy;
    f32 dist_x;
    f32 dist_xy;
    Vec3f dist;
    s32 ft_count = 0;

    if (fighter_gobj != NULL)
    {
        do
        {
            Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

            if ((fighter_gobj != ap->owner_gobj) && (fp->team != ap->team))
            {
                vec3f_sub(&dist, &DObjGetStruct(fighter_gobj)->translate, &joint->translate);

                if (ft_count == 0)
                {
                    dist_xy = SQUARE(dist.x) + SQUARE(dist.y);
                }
                ft_count++;

                square_xy = SQUARE(dist.x) + SQUARE(dist.y);

                if (square_xy <= dist_xy)
                {
                    dist_xy = square_xy;

                    victim_gobj = fighter_gobj;
                }
            }
            fighter_gobj = fighter_gobj->group_gobj_next;
        } 
        while (fighter_gobj != NULL);
    }
    func_ovl3_8018285C(article_gobj, victim_gobj);

    if (ap->at_kind == At_Kind_Sawamura)
    {
        void *s = ArticleGetPData(ap, D_NF_00011F40, D_NF_00012340); // Linker thing

        joint->display_list = s;

        func_800269C0(0x13FU);
    }
    ap->at_multi = ATSAWAMURA_LIFETIME;

    ap->article_hit.size = ATSAWAMURA_KICK_SIZE;
}

void func_ovl3_80182AAC(GObj *article_gobj)
{
    func_ovl3_80182958(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Sawamura_Status, 2);
}

bool32 jtgt_ovl3_80182AE0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        ap->at_multi = ATSAWAMURA_KICK_WAIT;

        ap->phys_info.vel.y = 0.0F;

        func_ovl3_801826A8(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80182B34(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Sawamura_Data;

GObj* jtgt_ovl3_80182B74(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Sawamura_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(article_gobj);
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = *pos;

        joint->translate.y -= ap->attributes->gfx_offset.y;

        func_8000BD1C(joint, ArticleGetPData(ap, D_NF_00011F40, D_NF_00013624), 0.0F); // Linker thing

        func_800269C0(0x13EU);

        om_g_move_obj_dl_head(article_gobj, 0x12U, article_gobj->room_order);
    }
    return article_gobj;
}