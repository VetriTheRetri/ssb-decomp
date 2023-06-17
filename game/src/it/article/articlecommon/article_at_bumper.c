#include "article.h"
#include "fighter.h"



bool32 jtgt_ovl3_8017B430(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATBUMPER_GRAVITY_NORMAL, ATBUMPER_T_VEL);

    if (ap->at_multi != 0)
    {
        joint->scale.x = joint->scale.y = joint->scale.z = (2.0F - (10 - ap->at_multi) * 0.1F);

        ap->at_multi--;
    }
    else
    {
        joint->scale.z = 1.0F;
        joint->scale.y = 1.0F;
        joint->scale.x = 1.0F;
    }
    if (!ap->article_vars.bumper.damage_all_delay)
    {
        func_ovl3_8017279C(article_gobj);

        ap->article_vars.bumper.damage_all_delay = -1;
    }
    if (ap->article_vars.bumper.damage_all_delay != -1)
    {
        ap->article_vars.bumper.damage_all_delay--;
    }
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_8017B520(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_8017B634);

    return FALSE;
}

bool32 jtgt_ovl3_8017B548(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.8F, 0.8F, func_ovl3_8017B600);
}

bool32 jtgt_ovl3_8017B57C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    joint->scale.x = 2.0F;
    joint->scale.y = 2.0F;
    joint->scale.z = 2.0F;

    ap->article_vars.bumper.hit_anim_length = ATBUMPER_HIT_ANIM_LENGTH;

    joint->mobj->anim_frame = 1.0F;

    ap->phys_info.vel.x = ATBUMPER_REBOUND_AIR_X * ap->lr_attack;

    ap->phys_info.vel.y = ATBUMPER_REBOUND_AIR_Y;

    ap->at_multi = ATBUMPER_HIT_SCALE;

    func_ovl3_8017BEA0(article_gobj);

    return FALSE;
}

extern ArticleStatusDesc Article_At_Bumper_Status[];

void func_ovl3_8017B600(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_At_Bumper_Status, 0);
}

void func_ovl3_8017B634(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    atCommon_UpdateArticleStatus(article_gobj, Article_At_Bumper_Status, 1);
}

void jtgt_ovl3_8017B678(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_At_Bumper_Status, 2);
}

bool32 jtgt_ovl3_8017B6A0(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATBUMPER_GRAVITY_NORMAL, ATBUMPER_T_VEL);

    if (!(ap->article_vars.bumper.damage_all_delay))
    {
        func_ovl3_8017279C(article_gobj);

        ap->article_vars.bumper.damage_all_delay = -1;
    }
    if (ap->article_vars.bumper.damage_all_delay != -1)
    {
        ap->article_vars.bumper.damage_all_delay--;
    }
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8017B720(GObj *article_gobj)
{
    return func_ovl3_80173EE8(article_gobj, 0.8F, func_ovl3_8017BD4C);
}

bool32 jtgt_ovl3_8017B74C(GObj *article_gobj)
{
    func_ovl3_80172FE0(article_gobj);
    func_ovl3_8017279C(article_gobj);

    return FALSE;
}

bool32 func_ovl3_8017B778(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    Fighter_Struct *fp = ftGetStruct(ap->owner_gobj);

    if ((ap->phys_info.vel.x * fp->lr) < 0.0F)
    {
        ap->phys_info.vel.x = -ap->phys_info.vel.x;
    }
    func_ovl3_8017279C(article_gobj);

    return FALSE;
}

void jtgt_ovl3_8017B7DC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->article_vars.bumper.damage_all_delay = ATBUMPER_DAMAGE_ALL_WAIT;

    ap->coll_data.object_coll.top = ATBUMPER_COLL_SIZE;
    ap->coll_data.object_coll.bottom = -ATBUMPER_COLL_SIZE;

    atCommon_UpdateArticleStatus(article_gobj, Article_At_Bumper_Status, 3);
}

void func_ovl3_8017B828(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->article_vars.bumper.damage_all_delay = ATBUMPER_DAMAGE_ALL_WAIT;

    ap->coll_data.object_coll.top = ATBUMPER_COLL_SIZE;
    ap->coll_data.object_coll.bottom = -ATBUMPER_COLL_SIZE;

    atCommon_UpdateArticleStatus(article_gobj, Article_At_Bumper_Status, 4);
}

void func_ovl3_8017B874(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    s32 filler;
    Vec3f ground_angle;
    DObj *joint = DObjGetStruct(article_gobj);

    ground_angle = ap->coll_data.ground_angle;

    ap->unk_0x2D0 = ap->coll_data.ground_line_id;

    joint->rotate.z = (atan2f(ground_angle.y, ground_angle.x) - HALF_PI32);
}

extern intptr_t D_NF_00007648;
extern intptr_t D_NF_00007A38;
extern intptr_t D_NF_00007AF8;

void func_ovl3_8017B8DC(GObj *article_gobj)
{
    void *sp2C;
    void *sp24;
    DObj *joint;
    Article_Struct *ap;
    void *dl2, *dl1;

    ap = article_gobj->user_data;
    joint = article_gobj->obj;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    dl1 = (uintptr_t)((uintptr_t)ap->attributes->unk_0x0 - (intptr_t)&D_NF_00007648) + (intptr_t)&D_NF_00007AF8; // Linker thing

    joint->display_list = dl1;

    dl2 = ((uintptr_t)((uintptr_t)ap->attributes->unk_0x0 - (intptr_t)&D_NF_00007648) + (intptr_t)&D_NF_00007A38); // Linker thing

    func_800091F4(joint);
    func_800090DC(joint, dl2);

    joint->scale.z = 1.0F;
    joint->scale.y = 1.0F;
    joint->scale.x = 1.0F;

    ap->coll_data.object_coll.top = ATBUMPER_COLL_SIZE;
    ap->coll_data.object_coll.bottom = -ATBUMPER_COLL_SIZE;

    func_ovl3_8017B874(article_gobj);

    ap->x2CF_flag_b1 = TRUE;

    ap->lifetime = ATBUMPER_LIFETIME;

    func_ovl3_8017279C(article_gobj);
}

bool32 jtgt_ovl3_8017B9C8(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    joint->scale.x = 2.0F;
    joint->scale.z = 2.0F;

    ap->article_vars.bumper.hit_anim_length = ATBUMPER_HIT_ANIM_LENGTH;

    joint->mobj->anim_frame = 1.0F;

    ap->lr = -ap->lr_attack;

    ap->phys_info.vel.x = ap->lr_attack * ATBUMPER_REBOUND_VEL_X;

    ap->at_multi = ATBUMPER_HIT_SCALE;

    return FALSE;
}

bool32 jtgt_ovl3_8017BA2C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    atCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(article_gobj);
    Vec3f sp30;

    if ((ap->article_vars.bumper.hit_anim_length == 0) && (joint->mobj->anim_frame == 1.0F))
    {
        joint->mobj->anim_frame = 0.0F;
    }
    else
    {
        ap->article_vars.bumper.hit_anim_length--;
    }

    if (func_ovl2_800FC67C(ap->coll_data.ground_line_id) != FALSE)
    {
        if (ap->lr == LEFT)
        {
            func_ovl2_800F4428(ap->coll_data.ground_line_id, &sp30);

            if ((joint->translate.x - attributes->objectcoll_width) <= sp30.x)
            {
                ap->phys_info.vel.x = 0.0F;
            }
        }
        else
        {
            func_ovl2_800F4408(ap->coll_data.ground_line_id, &sp30);

            if (sp30.x <= (joint->translate.x + attributes->objectcoll_width))
            {
                ap->phys_info.vel.x = 0.0F;
            }
        }
    }
    if (ap->at_multi < ATBUMPER_RESET_VEL_TIMER)
    {
        ap->phys_info.vel.x = 0.0F;
    }
    if (ap->at_multi != 0)
    {
        joint->scale.x = joint->scale.z = 2.0F - ((10 - ap->at_multi) * 0.1F);

        ap->at_multi--;
    }
    else
    {
        joint->scale.z = 1.0F;
        joint->scale.y = 1.0F;
        joint->scale.x = 1.0F;
    }
    if (ap->lifetime == 0)
    {
        func_ovl3_8017BF1C(article_gobj);
    }
    ap->lifetime--;

    return FALSE;
}

bool32 jtgt_ovl3_8017BBFC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (func_ovl3_801735A0(article_gobj, func_ovl3_8017B828) != FALSE)
    {
        if (func_ovl2_800FC67C(ap->unk_0x2D0) == FALSE)
        {
            ap->x2CF_flag_b1 = FALSE;

            func_ovl3_8017B828(article_gobj);

            joint->scale.z = 1.0F;
            joint->scale.y = 1.0F;
            joint->scale.x = 1.0F;

            joint->mobj->anim_frame = 0.0F;
        }
        else if (ap->at_multi == 0)
        {
            func_ovl3_8017B874(article_gobj);
        }
    }
    return FALSE;
}

bool32 func_ovl3_8017BCC0(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    Fighter_Struct *fp = ftGetStruct(ap->owner_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    joint->scale.x = 2.0F;
    joint->scale.z = 2.0F;

    ap->article_vars.bumper.hit_anim_length = 3;

    joint->mobj->anim_frame = 1.0F;

    ap->phys_info.vel.x = (-fp->lr * ATBUMPER_REBOUND_VEL_X);

    ap->lr = fp->lr;

    ap->at_multi = ATBUMPER_HIT_SCALE;

    func_ovl3_8017279C(article_gobj);

    return FALSE;
}

void func_ovl3_8017BD4C(GObj *article_gobj)
{
    func_ovl3_8017B8DC(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_At_Bumper_Status, 5);
}

bool32 jtgt_ovl3_8017BD80(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if ((ap->article_vars.bumper.hit_anim_length == 0) && (joint->mobj->anim_frame == 1.0F))
    {
        joint->mobj->anim_frame = 0.0F;
    }
    else ap->article_vars.bumper.hit_anim_length--;

    func_ovl3_80172558(ap, ATBUMPER_GRAVITY_HIT, ATBUMPER_T_VEL);

    if (ap->at_multi != 0)
    {
        joint->scale.x = joint->scale.y = joint->scale.z = (2.0F - (10 - ap->at_multi) * 0.1F);

        ap->at_multi--;
    }
    else
    {
        joint->scale.z = 1;
        joint->scale.y = 1;
        joint->scale.x = 1;
    }
    if (!ap->article_vars.bumper.damage_all_delay)
    {
        func_ovl3_8017279C(article_gobj);

        ap->article_vars.bumper.damage_all_delay = -1;
    }
    if (ap->article_vars.bumper.damage_all_delay != -1)
    {
        ap->article_vars.bumper.damage_all_delay--;
    }
    return FALSE;
}

void func_ovl3_8017BEA0(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->article_vars.bumper.damage_all_delay = ATBUMPER_DAMAGE_ALL_WAIT;

    atCommon_UpdateArticleStatus(article_gobj, Article_At_Bumper_Status, 6);
}

bool32 func_ovl3_8017BED4(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->lifetime == 0)
    {
        return TRUE;
    }
    else if (ap->lifetime & 1)
    {
        DObj *joint = DObjGetStruct(article_gobj);

        joint->unk_0x54 ^= 2;
    }
    ap->lifetime--;

    return FALSE;
}

void func_ovl3_8017BF1C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    joint->mobj->anim_frame = 0;

    joint->scale.x = 1.0F;
    joint->scale.y = 1.0F;
    joint->scale.z = 1.0F;

    ap->lifetime = ATBUMPER_DESPAWN_TIMER;

    joint->unk_0x54 = 0;

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    atCommon_UpdateArticleStatus(article_gobj, Article_At_Bumper_Status, 7);
}

extern ArticleSpawnData Article_At_Bumper_Data;

GObj* jtgt_ovl3_8017BF8C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = itManager_CreateItem(spawn_gobj, &Article_At_Bumper_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(article_gobj);
        Article_Struct *ap;
        Vec3f translate = joint->translate;

        ap = atGetStruct(article_gobj);

        ap->at_multi = 0;

        ap->article_hit.interact_mask = GMHITCOLLISION_MASK_FIGHTER;

        ap->article_hit.can_rehit_shield = TRUE;

        joint->mobj->anim_frame = 0.0F;

        func_80008CC0(joint, 0x2EU, 0U);

        joint->translate = translate;

        joint->rotate.z = 0.0F;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}