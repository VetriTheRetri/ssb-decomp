#include "article.h"
#include "gmground.h"

#include <game/src/sys/develop.h>
#include <game/src/sys/hal_gu.h>
#include <game/src/sys/obj_renderer.h>
#include <game/src/sys/obj.h>

#include <game/include/PR/gu.h>
#include <game/include/PR/mbi.h>
#include <game/include/PR/sp.h>
#include <game/include/PR/ultratypes.h>

bool32 func_ovl3_8017E070(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (ap->article_vars.kabigon.rumble_wait == 0)
    {
        func_ovl2_801008F4(0);

        ap->article_vars.kabigon.rumble_wait = ATKABIGON_RUMBLE_WAIT;
    }
    ap->article_vars.kabigon.rumble_wait--;

    if (joint->translate.y < (Ground_Info->blastzone_bottom + ATKABIGON_MAP_OFF_Y))
    {
        return TRUE;
    }
    else return FALSE;
}

extern Gfx *D_800465B0[4];

void func_ovl3_8017E100(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    gDPPipeSync(D_800465B0[0]++);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_pickup))
        {
            gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

            func_80014038(article_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

            func_80014038(article_gobj);
            func_ovl3_801719AC(article_gobj);
        }
        else if ((ap->article_hurt.hit_status == gmHitCollision_HitStatus_None) && (ap->article_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

            func_80014038(article_gobj);
        }
        else
        {
            func_ovl3_80171410(article_gobj);
        }
    }

    gDPPipeSync(D_800465B0[0]++);
}

void func_ovl3_8017E25C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    ap->phys_info.vel.y = ATKABIGON_DROP_VEL_Y;

    joint->translate.x += ((ATKABIGON_DROP_OFF_X_MUL * rand_f32()) + ATKABIGON_DROP_OFF_X_ADD);

    func_ovl3_8017275C(article_gobj);

    ap->article_vars.kabigon.rumble_wait = 0;

    func_800269C0(0x85U);

    if (ap->at_kind == At_Kind_Kabigon)
    {
        func_800269C0(0x137U);

        joint->scale.y = ATKABIGON_DROP_SIZE_KABIGON;
        joint->scale.x = ATKABIGON_DROP_SIZE_KABIGON;

        ap->article_hit.size *= ATKABIGON_DROP_SIZE_KABIGON;
    }
    else
    {
        joint->scale.y = ATKABIGON_DROP_SIZE_OTHER;
        joint->scale.x = ATKABIGON_DROP_SIZE_OTHER;

        ap->article_hit.size *= ATKABIGON_DROP_SIZE_OTHER;
    }
    article_gobj->renderer = func_ovl3_8017E100;

    om_g_move_obj_dl_head(article_gobj, 0x12, article_gobj->room_order);
}

extern ArticleStatusDesc Article_Kabigon_Status[];

void func_ovl3_8017E350(GObj *article_gobj)
{
    func_ovl3_8017E25C(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Kabigon_Status, 1);
}

bool32 func_ovl3_8017E384(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if ((Ground_Info->blastzone_top - ATKABIGON_MAP_OFF_Y) <= joint->translate.y)
    {
        ap->at_multi--;

        ap->phys_info.vel.y = 0.0F;

        if (ap->at_multi == 0)
        {
            func_ovl3_8017E350(article_gobj);
        }
    }

    if (ap->article_vars.kabigon.dust_gfx_int == 0)
    {
        Vec3f pos = joint->translate;

        pos.x += (rand_f32() * ATKABIGON_JUMP_GFX_MUL_OFF) - ATKABIGON_JUMP_GFX_SUB_OFF;
        pos.y += (rand_f32() * ATKABIGON_JUMP_GFX_MUL_OFF) - ATKABIGON_JUMP_GFX_SUB_OFF;

        func_ovl2_800FF590(&pos);

        ap->article_vars.kabigon.dust_gfx_int = ATKABIGON_GFX_SPAWN_INT;
    }
    ap->article_vars.kabigon.dust_gfx_int--;

    return FALSE;
}

void func_ovl3_8017E4A4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    gDPPipeSync(D_800465B0[0]++);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_pickup))
        {
            gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);

            func_80014038(article_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);

            func_80014038(article_gobj);
            func_ovl3_801719AC(article_gobj);
        }
        else if ((ap->article_hurt.hit_status == gmHitCollision_HitStatus_None) && (ap->article_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);

            func_80014038(article_gobj);
        }
        else
        {
            func_ovl3_80171410(article_gobj);
        }
    }
    gDPPipeSync(D_800465B0[0]++);
}

void func_ovl3_8017E600(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_800269C0(0x86U);

    ap->at_multi = ATKABIGON_DROP_WAIT;

    ap->article_vars.kabigon.dust_gfx_int = ATKABIGON_GFX_SPAWN_INT;

    ap->phys_info.vel.y = ATKABIGON_JUMP_VEL_Y;
}

void func_ovl3_8017E648(GObj *article_gobj)
{
    func_ovl3_8017E600(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Kabigon_Status, 0);
}

bool32 func_ovl3_8017E67C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        func_ovl3_8017E648(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

extern intptr_t D_NF_0000B158;
extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Kabigon_Data;

GObj* jtgt_ovl3_8017E6C0(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Kabigon_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(article_gobj);
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->article_hit.interact_mask = GMHITCOLLISION_MASK_FIGHTER;

        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        func_8000BD1C(joint, ArticleGetPData(ap, D_NF_0000B158, D_NF_00013624), 0.0F); // Linker thing

        if (ap->at_kind == At_Kind_Kabigon)
        {
            func_800269C0(0x138U);
        }
        article_gobj->renderer = func_ovl3_8017E4A4;
    }
    return article_gobj;
}