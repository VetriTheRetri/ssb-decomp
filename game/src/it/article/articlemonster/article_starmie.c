#include "article.h"
#include "item.h"
#include "fighter.h"

void func_ovl3_80181C20(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (ap->article_vars.starmie.swift_spawn_wait <= 0)
    {
        Vec3f pos = joint->translate;

        if (ap->at_kind == At_Kind_Starmie)
        {
            pos.x += ATSTARMIE_STARMIE_SWIFT_SPAWN_OFF_X * ap->lr;
            pos.y += ATSTARMIE_STARMIE_SWIFT_SPAWN_OFF_Y;
        }
        else pos.x += ATSTARMIE_OTHER_SWIFT_SPAWN_OFF_X * ap->lr;

        func_ovl3_80182608(article_gobj, &pos);

        func_800269C0(0x8CU);

        ap->article_vars.starmie.swift_spawn_wait = (rand_u16_range(ATSTARMIE_SWIFT_SPAWN_WAIT_RANDOM) + ATSTARMIE_SWIFT_SPAWN_WAIT_CONST);

        ap->phys_info.vel.x = -ap->lr * ATSTARMIE_PUSH_VEL_X;
    }
}

bool32 func_ovl3_80181D24(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return TRUE;
    }
    func_ovl3_80181C20(article_gobj);

    ap->article_vars.starmie.swift_spawn_wait--;

    ap->phys_info.vel.x += ap->article_vars.starmie.add_vel_x;

    ap->at_multi--;

    return FALSE;
}

void func_ovl3_80181D8C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    s32 lr_bak = ap->lr;

    ap->lr = (ap->article_vars.starmie.victim_pos.x < joint->translate.x) ? LEFT : RIGHT;

    if (ap->lr != lr_bak)
    {
        joint->rotate.y += PI32;
    }
    ap->at_multi = ATSTARMIE_LIFETIME;

    ap->article_vars.starmie.swift_spawn_wait = 0;
    ap->article_vars.starmie.add_vel_x = ap->lr * ATSTARMIE_ADD_VEL_X;
}

extern ArticleStatusDesc Article_Starmie_Status[];

void func_ovl3_80181E0C(GObj *article_gobj)
{
    func_ovl3_80181D8C(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_Starmie_Status, 1);
}

bool32 func_ovl3_80181E40(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if ((ap->lr == RIGHT) && (ap->article_vars.starmie.target_pos.x <= joint->translate.x))
    {
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_80181E0C(article_gobj);
    }
    if ((ap->lr == LEFT) && (joint->translate.x <= ap->article_vars.starmie.target_pos.x))
    {
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_80181E0C(article_gobj);
    }
    return FALSE;
}

extern intptr_t D_NF_000112A0;
extern intptr_t D_NF_00011338;

void func_ovl3_80181EF4(GObj *article_gobj, GObj *fighter_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    DObj *aj = DObjGetStruct(article_gobj);
    DObj *fj = DObjGetStruct(fighter_gobj);
    Vec3f dist;
    Vec3f target_pos;
    Vec3f *victim_pos;

    target_pos = fj->translate;

    dist.x = fj->translate.x - aj->translate.x;

    target_pos.y += ATSTARMIE_TARGET_POS_OFF_Y - fp->coll_data.object_coll.bottom;

    target_pos.x -= (fp->coll_data.object_coll.width + ATSTARMIE_TARGET_POS_OFF_X) * ((dist.x < 0.0F) ? LEFT : RIGHT);

    victim_pos = &fj->translate;

    vec3f_sub(&dist, &target_pos, &aj->translate);

    ap->phys_info.vel.z = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.x = ATSTARMIE_FOLLOW_VEL_X;

    vec3_get_euler_rotation(&ap->phys_info.vel, 4, atan2f(dist.y, dist.x));

    ap->article_vars.starmie.target_pos = target_pos;

    ap->article_vars.starmie.victim_pos = *victim_pos;

    ap->lr = (dist.x < 0.0F) ? LEFT : RIGHT;

    if (ap->lr == RIGHT)
    {
        aj->rotate.y = PI32;
    }
    if (ap->at_kind == At_Kind_Starmie)
    {
        func_8000BD54(aj->mobj, ArticleGetPData(ap, D_NF_000112A0, D_NF_00011338), 0); // Linker thing

        func_8000DF34(article_gobj);
    }
}

void func_ovl3_801820CC(GObj *article_gobj)
{
    GObj *fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    GObj *victim_gobj;
    s32 unused2[2];
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
    func_ovl3_80181EF4(article_gobj, victim_gobj);

    if (ap->at_kind == At_Kind_Starmie)
    {
        func_800269C0(0x142U);
    }
}

void func_ovl3_801821E8(GObj *article_gobj)
{
    func_ovl3_801820CC(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_Starmie_Status, 0);
}

bool32 jtgt_ovl3_8018221C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        ap->phys_info.vel.y = 0.0F;
        ap->phys_info.vel.x = 0.0F;

        func_ovl3_801821E8(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80182270(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Starmie_Data;

GObj* jtgt_ovl3_801822B0(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Starmie_Data, pos, vel, flags);

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

        joint->translate.y -= ap->attributes->objectcoll_bottom;

        func_8000BD1C(joint, ArticleGetPData(ap, D_NF_000112A0, D_NF_00013624), 0.0F); // Linker thing

        om_g_move_obj_dl_head(article_gobj, 0x12, article_gobj->room_order);
    }
    return article_gobj;
}

bool32 func_ovl3_801823B4(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    ip->phys_info.vel.x = ip->phys_info.vel.x; // Bruh

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_801823E8(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl2_80102070(&DObjGetStruct(item_gobj)->translate, ip->lr);

    return TRUE;
}

bool32 jtgt_ovl3_80182418(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    if (ip->phys_info.vel.x > 0.0F)
    {
        ip->lr = RIGHT;
    }
    else ip->lr = LEFT;

    return FALSE;
}

bool32 jtgt_ovl3_801824C0(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern ItemSpawnData Item_Swift_Data;

GObj* func_ovl3_80182530(GObj *article_gobj, Vec3f *pos)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    GObj *item_gobj = func_ovl3_801655C8(article_gobj, &Item_Swift_Data, pos, ITEM_MASK_SPAWN_ARTICLE);
    DObj *joint;
    s32 unused;
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->lr = ap->lr;

    ip->phys_info.vel.x = ip->lr * ATSTARMIE_SWIFT_VEL_X;

    joint = DObjGetStruct(item_gobj);

    joint->translate = *pos;

    func_ovl2_8010066C(&joint->translate, 1.0F);

    ip->lifetime = ATSTARMIE_SWIFT_LIFETIME;

    if (ip->lr == RIGHT)
    {
        joint->rotate.y = PI32;
    }
    return item_gobj;
}

void func_ovl3_80182608(GObj *article_gobj, Vec3f *pos)
{
    func_ovl3_80182530(article_gobj, pos);
}
