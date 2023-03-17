#include "article.h"
#include "ground.h"
#include "gmmatch.h"

bool32 func_ovl3_8017D590(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if ((ap->article_vars.bumper.hit_anim_length == 0) && (joint->mobj->anim_frame == 1.0F))
    {
        joint->mobj->anim_frame = 0;
    }
    else
    {
        ap->article_vars.bumper.hit_anim_length--;
    }
    if (ap->at_multi != 0)
    {
        joint->scale.x = joint->scale.y = 2.0F - ((10 - ap->at_multi) * 0.1F);

        ap->at_multi--;
    }
    else
    {
        joint->scale.y = 1;
        joint->scale.x = 1;
    }
    return FALSE;
}

bool32 func_ovl3_8017D63C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    joint->scale.x = 2.0F;
    joint->scale.y = 2.0F;

    ap->article_vars.bumper.hit_anim_length = ATBUMPER_HIT_ANIM_LENGTH;

    joint->mobj->anim_frame = 1.0F;

    ap->at_multi = ATBUMPER_HIT_SCALE;

    return FALSE;
}

extern ArticleSpawnData Article_Gr_Bumper_Data;

GObj *jtgt_ovl3_8017D67C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Gr_Bumper_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap;
        DObj *joint;

        func_ovl3_8017279C(article_gobj);

        ap = ArticleGetStruct(article_gobj);
        joint = DObjGetStruct(article_gobj);

        ap->at_multi = 0;

        ap->article_hit.interact_mask = GMHITCOLLISION_MASK_FIGHTER;
        ap->article_hit.can_rehit = TRUE;

        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = 0.0F;
        ap->phys_info.vel.z = 0.0F;

        joint->mobj->anim_frame = 0;

        if (Match_Info->gr_kind == Gr_Kind_Castle)
        {
            ap->article_hit.knockback_weight = ATBUMPER_CASTLE_KNOCKBACK;
            ap->article_hit.angle = ATBUMPER_CASTLE_ANGLE;
        }
    }
    return article_gobj;
}
