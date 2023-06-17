#include "article.h"
#include "fighter.h"
#include "gmmatch.h"



bool32 jtgt_ovl3_80176450(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATMSBOMB_GRAVITY, ATMSBOMB_T_VEL);
    func_ovl3_801713F4(article_gobj);

    joint->next->unk_0x8->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 func_ovl3_801764A8(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80176538);

    return FALSE;
}

bool32 jtgt_ovl3_801764D0(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.4F, 0.3F, func_ovl3_80176504);
}

extern ArticleStatusDesc Article_MSBomb_Status[];

void func_ovl3_80176504(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_MSBomb_Status, 0);
}

void func_ovl3_80176538(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    atCommon_UpdateArticleStatus(article_gobj, Article_MSBomb_Status, 1);
}

void jtgt_ovl3_8017657C(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_MSBomb_Status, 2);
}

bool32 jtgt_ovl3_801765A4(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATMSBOMB_GRAVITY, ATMSBOMB_T_VEL);
    func_ovl3_801713F4(article_gobj);

    joint->next->unk_0x8->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 jtgt_ovl3_801765FC(GObj *article_gobj)
{
    return func_ovl3_80173E58(article_gobj, func_ovl3_80176B94);
}

bool32 jtgt_ovl3_80176620(GObj *article_gobj)
{
    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

void jtgt_ovl3_80176644(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->coll_data.object_coll.top = ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.center = 0.0F;
    ap->coll_data.object_coll.bottom = -ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.width = ATMSBOMB_COLL_SIZE;

    atCommon_UpdateArticleStatus(article_gobj, Article_MSBomb_Status, 3);
}

bool32 jtgt_ovl3_80176694(GObj *article_gobj)
{
    return func_ovl3_80173E58(article_gobj, func_ovl3_80176B94);
}

void jtgt_ovl3_801766B8(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->coll_data.object_coll.top = ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.center = 0.0F;
    ap->coll_data.object_coll.bottom = -ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.width = ATMSBOMB_COLL_SIZE;

    atCommon_UpdateArticleStatus(article_gobj, Article_MSBomb_Status, 4);
}

void func_ovl3_80176708(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    Coll_Data *coll_data = &ap->coll_data;
    Vec3f angle;
    DObj *joint = DObjGetStruct(article_gobj);


    if ((coll_data->coll_mask & MPCOLL_MASK_CEIL) || (coll_data->coll_mask & MPCOLL_MASK_GROUND))
    {

        if (coll_data->coll_mask & MPCOLL_MASK_CEIL)
        {
            angle = coll_data->ceil_angle;

            ap->unk_0x2D0 = coll_data->ceil_line_id;
        }
        if (coll_data->coll_mask & MPCOLL_MASK_GROUND)
        {
            angle = coll_data->ground_angle;

            ap->unk_0x2D0 = coll_data->ground_line_id;
        }
    }
    else
    {
        if (coll_data->coll_mask & MPCOLL_MASK_RWALL)
        {
            angle = coll_data->rwall_angle;

            ap->unk_0x2D0 = coll_data->rwall_line_id;
        }
        if (coll_data->coll_mask & MPCOLL_MASK_LWALL)
        {
            angle = coll_data->lwall_angle;

            ap->unk_0x2D0 = coll_data->lwall_line_id;
        }
    }
    joint->rotate.z = atan2f(angle.y, angle.x) - HALF_PI32;
}

void func_ovl3_80176840(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    ap->coll_data.object_coll.top = ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.center = 0.0F;
    ap->coll_data.object_coll.bottom = -ATMSBOMB_COLL_SIZE;
    ap->coll_data.object_coll.width = ATMSBOMB_COLL_SIZE;

    ap->phys_info.vel.z = 0;
    ap->phys_info.vel.y = 0;
    ap->phys_info.vel.x = 0;

    joint->next->unk_0x54 = 0;
    joint->next->unk_0x8->unk_0x54 = 2;

    func_ovl3_80176708(article_gobj);

    ap->x2CF_flag_b1 = TRUE;

    ap->article_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    if ((ap->port_id != -1U) && (ap->port_id != GMMATCH_PLAYERS_MAX)) // Macro might be off though
    {
        GObj *fighter_gobj = Match_Info->player_block[ap->port_id].fighter_gobj;

        if (fighter_gobj != NULL)
        {
            func_ovl2_800E806C(ftGetStruct(fighter_gobj), 6, 0);
        }
    }
    func_800269C0(0x2CU);

    func_ovl3_8017279C(article_gobj);
}

void func_ovl3_80176934(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    atCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(article_gobj);
    s32 unused[4];

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        Vec3f translate = joint->translate;

        translate.y += attributes->objectcoll_bottom;

        func_ovl2_800FF3F4(&translate, ap->lr, 1.0F);
    }
}

void func_ovl3_801769AC(GObj *article_gobj, bool32 is_fighter)
{
    Effect_Unk *ep;
    DObj *joint = DObjGetStruct(article_gobj);

    if (is_fighter != FALSE)
    {
        func_ovl3_80176934(article_gobj);
    }
    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ATMSBOMB_EXPLODE_SCALE;
        ep->effect_info->scale.y = ATMSBOMB_EXPLODE_SCALE;
        ep->effect_info->scale.z = ATMSBOMB_EXPLODE_SCALE;
    }
    func_ovl2_801008F4(1);
    func_ovl3_8017275C(article_gobj);
    func_ovl3_80176F2C(article_gobj);

    DObjGetStruct(article_gobj)->unk_0x54 = 2;
}

bool32 jtgt_ovl3_80176A34(GObj *article_gobj)
{
    func_800269C0(1U);
    func_ovl3_801769AC(article_gobj, FALSE);

    return FALSE;
}

bool32 jtgt_ovl3_80176A68(GObj *article_gobj)
{
    s32 unused[2];
    GObj *fighter_gobj;
    Vec3f *translate;
    Vec3f dist;
    Vec3f f_pos;
    DObj *aj = DObjGetStruct(article_gobj);
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->at_multi < ATMSBOMB_DETECT_FIGHTER_DELAY)
    {
        ap->at_multi++;
    }
    else
    {
        fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

        translate = &aj->translate;

        if (fighter_gobj != NULL)
        {
            do
            {
                Fighter_Struct *fp = ftGetStruct(fighter_gobj);
                DObj *fj = DObjGetStruct(fighter_gobj);
                f32 var = fp->attributes->object_coll.top * 0.5F;

                f_pos = fj->translate;

                f_pos.y += var;

                vec3f_sub(&dist, &f_pos, translate);

                if ((SQUARE(dist.x) + SQUARE(dist.y) + SQUARE(dist.z)) < ATMSBOMB_DETECT_FIGHTER_RADIUS)
                {
                    func_ovl3_801769AC(article_gobj, TRUE);
                }
                fighter_gobj = fighter_gobj->group_gobj_next;
            } 
            while (fighter_gobj != NULL);
        }
    }
    return FALSE;
}

void func_ovl3_80176B94(GObj *article_gobj)
{
    func_ovl3_80176840(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_MSBomb_Status, 5);
}

bool32 jtgt_ovl3_80176BC8(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (func_ovl2_800FC67C(ap->unk_0x2D0) == FALSE)
    {
        ap->x2CF_flag_b1 = FALSE;

        func_ovl3_80176E68(article_gobj);
    }
    return FALSE;
}

extern u8 D_NF_00000404;
extern ArticleSpawnData Article_MSBomb_Data;

void func_ovl3_80176C14(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    ArticleHitEvent *ev = (ArticleHitEvent*) ((uintptr_t)*Article_MSBomb_Data.p_file + &D_NF_00000404);

    if (ap->at_multi == ev[ap->x340_flag_b0123].timer)
    {
        ap->article_hit.angle = ev[ap->x340_flag_b0123].angle;
        ap->article_hit.damage = ev[ap->x340_flag_b0123].damage;
        ap->article_hit.size = ev[ap->x340_flag_b0123].size;

        ap->article_hit.can_rehit_hurt = TRUE;
        ap->article_hit.can_hop = FALSE;
        ap->article_hit.can_reflect = FALSE;
        ap->article_hit.clang = FALSE;

        ap->article_hit.element = gmHitCollision_Element_Fire;

        ap->x340_flag_b0123++;

        if (ap->x340_flag_b0123 == 4)
        {
            ap->x340_flag_b0123 = 3;
        }
    }
}

void func_ovl3_80176D00(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->article_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_8017279C(article_gobj);
}

bool32 jtgt_ovl3_80176D2C(GObj *article_gobj)
{
    s32 unused[2];
    GObj *fighter_gobj;
    Vec3f *translate;
    Vec3f dist;
    Vec3f f_pos;
    DObj *aj = DObjGetStruct(article_gobj);
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATMSBOMB_GRAVITY, ATMSBOMB_T_VEL);

    if (ap->at_multi < ATMSBOMB_DETECT_FIGHTER_DELAY)
    {
        ap->at_multi++;
    }
    else
    {
        fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

        translate = &aj->translate;

        if (fighter_gobj != NULL)
        {
            do
            {
                Fighter_Struct *fp = ftGetStruct(fighter_gobj);
                DObj *fj = DObjGetStruct(fighter_gobj);
                f32 var = fp->attributes->object_coll.top * 0.5F;

                f_pos = fj->translate;

                f_pos.y += var;

                vec3f_sub(&dist, &f_pos, translate);

                if ((SQUARE(dist.x) + SQUARE(dist.y) + SQUARE(dist.z)) < ATMSBOMB_DETECT_FIGHTER_RADIUS)
                {
                    func_ovl3_801769AC(article_gobj, FALSE);
                }
                fighter_gobj = fighter_gobj->group_gobj_next;
            } 
            while (fighter_gobj != NULL);
        }
    }
    return FALSE;
}

void func_ovl3_80176E68(GObj *article_gobj)
{
    func_ovl3_80176D00(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_MSBomb_Status, 6);
}

void func_ovl3_80176E9C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->at_multi = 0;

    ap->x340_flag_b0123 = 0;

    ap->article_hit.stale = ARTICLE_STALE_DEFAULT;
    ap->article_hit.hit_sfx = 1;

    ap->article_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_ovl3_80176C14(article_gobj);
}

bool32 jtgt_ovl3_80176EE4(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80176C14(article_gobj);

    ap->at_multi++;

    if (ap->at_multi == ATMSBOMB_EXPLODE_LIFETIME)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80176F2C(GObj *article_gobj)
{
    func_ovl3_80176E9C(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_MSBomb_Status, 7);
}

GObj* jtgt_ovl3_80176F60(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = itManager_CreateItem(spawn_gobj, &Article_MSBomb_Data, pos, vel, flags);
    DObj *joint;
    Article_Struct *ap;
    Vec3f translate;

    if (article_gobj != NULL)
    {
        joint = DObjGetStruct(article_gobj);

        joint->next->unk_0x54 = 2;
        joint->next->unk_0x8->unk_0x54 = 0;

        translate = joint->translate;

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint->next->unk_0x8, 0x46U, 0U);

        joint->translate = translate;

        ap = atGetStruct(article_gobj);

        ap->at_multi = 0;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);

        joint->rotate.z = 0.0F;
    }
    return article_gobj;
}