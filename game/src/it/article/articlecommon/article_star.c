#include "article.h"
#include "gmmatch.h"

bool32 jtgt_ovl3_80174930(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATSTAR_GRAVITY, ATSTAR_T_VEL);

    ap->at_multi--;

    if (ap->at_multi == 0)
    {
        func_ovl3_8017275C(article_gobj);
    }
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80174990(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    s32 unused;
    bool32 is_collide_ground = func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND);

    if (func_ovl3_801737EC(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), 1.0F, NULL) != FALSE)
    {
        func_ovl3_80172508(article_gobj);
    }
    if (is_collide_ground != FALSE)
    {
        ap->phys_info.vel.y = ATSTAR_BOUNCE_Y;

        func_800269C0(0x35U);
    }
    return FALSE;
}

bool32 jtgt_ovl3_80174A0C(GObj *article_gobj)
{
    return TRUE;
}

extern ArticleSpawnData Article_Star_Data;

GObj *jtgt_ovl3_80174A18(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    Unk_80131460_Ptr74 *unk_ptr = D_ovl2_80131460->unk_0x74;
    GObj *article_gobj;
    DObj *joint;
    Article_Struct *ap;
    Vec3f vel_real;
    Vec3f translate;

    vel_real.x = (pos->x < unk_ptr->unk_0x48) ? ATSTAR_VEL_X : -ATSTAR_VEL_X;
    vel_real.y = ATSTAR_BOUNCE_Y;
    vel_real.z = 0.0F;

    article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Star_Data, pos, &vel_real, flags);

    if (article_gobj != NULL)
    {
        joint = DObjGetStruct(article_gobj);

        translate = joint->translate;

        ap = article_gobj->user_data;

        ap->article_hit[0].hit_status = GMHITCOLLISION_MASK_FIGHTER; // Star Man can only interact with fighters
        ap->at_multi = ATSTAR_INTERACT_DELAY;

        ap->x2D3_flag_b5 = TRUE;

        func_80008CC0(joint, 0x2EU, 0U);

        joint->rotate.z = 0.0F;

        joint->translate = translate;
    }
    return article_gobj;
}