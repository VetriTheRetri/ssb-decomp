#include "article.h"
#include "item.h"
#include "gmground.h"

#include <game/src/sys/develop.h>
#include <game/src/sys/hal_gu.h>
#include <game/src/sys/obj_renderer.h>
#include <game/src/sys/obj.h>

#include <game/include/PR/gu.h>
#include <game/include/PR/mbi.h>
#include <game/include/PR/sp.h>
#include <game/include/PR/ultratypes.h>

void func_ovl3_8017FDC0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (ap->article_vars.spear.spear_spawn_wait <= 0)
    {
        Vec3f pos = joint->translate;
        s32 unused;

        pos.y = ap->article_vars.spear.spear_spawn_pos_y;

        pos.y += (ATSPEAR_SPAWN_OFF_Y_MUL * rand_f32()) + ATSPEAR_SPAWN_OFF_Y_ADD;

        func_ovl3_80180608(article_gobj, &pos, ap->at_kind);

        ap->article_vars.spear.spear_spawn_count--;
        ap->article_vars.spear.spear_spawn_wait = rand_u16_range(ATSPEAR_SPAWN_WAIT_RANDOM) + ATSPEAR_SPAWN_WAIT_CONST;
    }
}

bool32 func_ovl3_8017FE70(GObj *article_gobj)
{
    DObj *joint = DObjGetStruct(article_gobj);

    if (article_gobj->anim_frame == ATSPEAR_SWARM_CALL_WAIT)
    {
        joint->next->unk_dobj_0x70 = 0;

        func_ovl3_80180160(article_gobj);
    }
    return FALSE;
}

extern intptr_t D_NF_0000DF38;
extern intptr_t D_NF_0000DFFC;
extern intptr_t D_NF_0000E12C;

void func_ovl3_8017FEB8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    ap->at_multi = 0;

    ap->phys_info.vel.y = 0;

    if (ap->at_kind == At_Kind_Spear)
    {
        void *s = ArticleGetPData(ap, D_NF_0000DF38, D_NF_0000DFFC); // Linker thing
        s32 unused;

        func_8000BD1C(joint->next, s, 0.0F);

        s = ArticleGetPData(ap, D_NF_0000DF38, D_NF_0000E12C); // Linker thing

        func_8000BD54(joint->next->mobj, s, 0.0F);
        func_8000DF34(article_gobj);
        func_800269C0(0x140U);
    }
}

extern ArticleStatusDesc Article_Spear_Status[];

void func_ovl3_8017FF74(GObj *article_gobj)
{
    func_ovl3_8017FEB8(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_Spear_Status, 0);
}

bool32 func_ovl3_8017FFA8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATSPEAR_GRAVITY, ATSPEAR_T_VEL);

    ap->phys_info.vel.x += ATSPEAR_SWARM_CALL_VEL_X * ap->lr;

    if (ap->lr == RIGHT)
    {
        if ((Ground_Info->blastzone_right - ATSPEAR_SWARM_CALL_OFF_X) <= joint->translate.x)
        {
            ap->phys_info.vel.x = 0.0F;
            ap->phys_info.vel.y = 0.0F;

            if (ap->article_vars.spear.spear_spawn_count != 0)
            {
                func_ovl3_8017FDC0(article_gobj);
            }
            else return TRUE;

            ap->article_vars.spear.spear_spawn_wait--;
        }
    }
    if (ap->lr == LEFT)
    {
        if (joint->translate.x <= (Ground_Info->blastzone_left + ATSPEAR_SWARM_CALL_OFF_X))
        {
            ap->phys_info.vel.x = 0.0F;
            ap->phys_info.vel.y = 0.0F;

            if (ap->article_vars.spear.spear_spawn_count != 0)
            {
                func_ovl3_8017FDC0(article_gobj);
            }
            else return TRUE;

            ap->article_vars.spear.spear_spawn_wait--;
        }
    }
    return FALSE;
}

void func_ovl3_8018010C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->phys_info.vel.y = ATSPEAR_SWARM_CALL_VEL_Y;

    ap->article_vars.spear.spear_spawn_pos_y = DObjGetStruct(article_gobj)->translate.y;
    ap->article_vars.spear.spear_spawn_wait = 0;
    ap->article_vars.spear.spear_spawn_count = ATSPEAR_SPAWN_COUNT;

    if (ap->at_kind == At_Kind_Spear)
    {
        func_800269C0(0x141U);
    }
}

bool32 jtgt_ovl3_80180194(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        func_ovl3_8017FF74(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_801801D8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Spear_Data;

GObj *jtgt_ovl3_80180218(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Spear_Data, pos, vel, flags);
    DObj *joint;
    Article_Struct *ap;

    if (article_gobj != NULL)
    {
        ap = ArticleGetStruct(article_gobj);

        func_ovl3_8017279C(article_gobj);

        joint = DObjGetStruct(article_gobj);

        func_80008CC0(joint->next, 0x48U, 0U);

        joint->translate = *pos;

        if (rand_u16_range(2) == 0)
        {
            joint->next->rotate.y = PI32;

            ap->lr = LEFT;

        }
        else ap->lr = RIGHT;

        ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->article_hit.interact_mask = GMHITCOLLISION_MASK_FIGHTER;

        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        joint->translate.y -= ap->attributes->objectcoll_bottom;

        func_8000BD1C(joint->next, ArticleGetPData(ap, D_NF_0000DF38, D_NF_00013624), 0.0F);
    }
    return article_gobj;
}

bool32 func_ovl3_80180354(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    if ((ip->lr == RIGHT) && ((Ground_Info->blastzone_right - ATSPEAR_SWARM_CALL_OFF_X) <= joint->translate.x))
    {
        return TRUE;
    }
    else if ((ip->lr == LEFT) && (joint->translate.x <= (Ground_Info->blastzone_left + ATSPEAR_SWARM_CALL_OFF_X)))
    {
        return TRUE;
    }
    else return FALSE;
}

extern Gfx *D_800465B0[4];

void func_ovl3_80180400(GObj *article_gobj)
{
    gDPPipeSync(D_800465B0[0]++);

    gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

    func_80014038(article_gobj);

    gDPPipeSync(D_800465B0[0]++);
}

void func_ovl3_80180480(GObj *article_gobj)
{
    func_ovl3_80167520(article_gobj, func_ovl3_80180400);
}

extern ItemSpawnData Item_Spear_Swarm_Data;
extern ItemSpawnData Item_Pippi_Swarm_Data;

GObj *func_ovl3_801804A4(GObj *article_gobj, Vec3f *pos, s32 at_kind)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    GObj *item_gobj = func_ovl3_801655C8(article_gobj, ((at_kind == At_Kind_Spear) ? &Item_Spear_Swarm_Data : &Item_Pippi_Swarm_Data), pos, ITEM_MASK_SPAWN_ARTICLE);
    DObj *joint;
    s32 unused;
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->lr = -ap->lr;

    ip->phys_info.vel.x = ip->lr * ATSPEAR_SWARM_FLY_VEL_X;

    joint = DObjGetStruct(item_gobj);

    if (at_kind == At_Kind_Spear)
    {
        func_80008CC0(joint->next->next, 0x48U, 0U);

        if (ip->lr == LEFT)
        {
            joint->next->next->rotate.y = PI32;
        }
    }
    else
    {
        item_gobj->renderer = func_ovl3_80180480;

        func_80008CC0(joint->next, 0x48U, 0U);

        if (ip->lr == RIGHT)
        {
            joint->next->rotate.y = PI32;
        }
    }
    joint->translate = *pos;

    ip->is_hitlag_victim = TRUE;

    return item_gobj;
}

void func_ovl3_80180608(GObj *article_gobj, Vec3f *pos, s32 at_kind)
{
    func_ovl3_801804A4(article_gobj, pos, at_kind);
}