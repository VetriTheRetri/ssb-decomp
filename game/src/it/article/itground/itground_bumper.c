#include "article.h"
#include "ground.h"
#include "gmmatch.h"

bool32 func_ovl3_8017D590(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

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

bool32 func_ovl3_8017D63C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->scale.x = 2.0F;
    joint->scale.y = 2.0F;

    ap->article_vars.bumper.hit_anim_length = ATBUMPER_HIT_ANIM_LENGTH;

    joint->mobj->anim_frame = 1.0F;

    ap->at_multi = ATBUMPER_HIT_SCALE;

    return FALSE;
}

extern itCreateDesc Article_Gr_Bumper_Data;

GObj *jtgt_ovl3_8017D67C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Gr_Bumper_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap;
        DObj *joint;

        func_ovl3_8017279C(item_gobj);

        ap = itGetStruct(item_gobj);
        joint = DObjGetStruct(item_gobj);

        ap->at_multi = 0;

        ap->item_hit.interact_mask = GMHITCOLLISION_MASK_FIGHTER;
        ap->item_hit.can_rehit_shield = TRUE;

        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = 0.0F;
        ap->phys_info.vel.z = 0.0F;

        joint->mobj->anim_frame = 0;

        if (Match_Info->gr_kind == Gr_Kind_Castle)
        {
            ap->item_hit.knockback_weight = ATBUMPER_CASTLE_KNOCKBACK;
            ap->item_hit.angle = ATBUMPER_CASTLE_ANGLE;
        }
    }
    return item_gobj;
}
