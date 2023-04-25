#include "article.h"
#include "fighter.h"

#include <game/src/sys/develop.h>
#include <game/src/sys/hal_gu.h>
#include <game/src/sys/obj_renderer.h>
#include <game/src/sys/obj.h>

#include <game/include/PR/gu.h>
#include <game/include/PR/mbi.h>
#include <game/include/PR/sp.h>
#include <game/include/PR/ultratypes.h>

void func_ovl3_80171410(GObj *article_gobj)
{
    Article_Struct *ap;
    s32 i;
    Article_Hit *at_hit;
    Article_Hurt *at_hurt;
    MtxStore mtx_store;
    Vec3f *translate;

    ap = ArticleGetStruct(article_gobj);
    at_hit = &ap->article_hit;

    for (i = 0; i < at_hit->hitbox_count; i++)
    {
        if ((at_hit->update_state != gmHitCollision_UpdateState_Disable) && (at_hit->update_state != gmHitCollision_UpdateState_New))
        {
            gDPPipeSync(D_800465B0[0]++);

            if (ap->display_state == dbObjDisplayStatus_HitCollision_Outline)
            {
                gDPSetPrimColor(D_800465B0[0]++, 0, 0, 176, 0, 0, 255);

                gDPSetEnvColor(D_800465B0[0]++, 176, 0, 0, 255);

                gDPSetBlendColor(D_800465B0[0]++, 0, 0, 0, 224);
            }
            else
            {
                gDPSetPrimColor(D_800465B0[0]++, 0, 0, 255, 255, 255, 255);

                gDPSetEnvColor(D_800465B0[0]++, 176, 0, 0, 255);

                gDPSetBlendColor(D_800465B0[0]++, 0, 0, 0, 0);
            }
            if (at_hit->update_state == gmHitCollision_UpdateState_Interpolate)
            {
                hal_matrix_store_gbi(mtx_store, gMatrixHeap);

                hal_translate(mtx_store.gbi, at_hit->article_hit_unk[i].pos_prev.x, at_hit->article_hit_unk[i].pos_prev.y, at_hit->article_hit_unk[i].pos_prev.z);

                gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

                hal_matrix_store_gbi(mtx_store, gMatrixHeap);

                hal_scale(mtx_store.gbi, at_hit->size / 15.0F, at_hit->size / 15.0F, at_hit->size / 15.0F);

                gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

                gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C128);

                gSPPopMatrix(D_800465B0[0]++, G_MTX_MODELVIEW);
            }
            hal_matrix_store_gbi(mtx_store, gMatrixHeap);

            hal_translate(mtx_store.gbi, at_hit->article_hit_unk[i].pos.x, at_hit->article_hit_unk[i].pos.y, at_hit->article_hit_unk[i].pos.z);

            gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

            hal_matrix_store_gbi(mtx_store, gMatrixHeap);

            hal_scale(mtx_store.gbi, at_hit->size / 15.0F, at_hit->size / 15.0F, at_hit->size / 15.0F);

            gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

            if (at_hit->update_state == gmHitCollision_UpdateState_Interpolate)
            {
                gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C160);
            }
            gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C310);

            gSPPopMatrix(D_800465B0[0]++, G_MTX_MODELVIEW);
        }
    }
    at_hurt = &ap->article_hurt;

    if (ap->article_hurt.hit_status != gmHitCollision_HitStatus_None)
    {
        translate = &DObjGetStruct(article_gobj)->translate;

        hal_matrix_store_gbi(mtx_store, gMatrixHeap);

        hal_translate(mtx_store.gbi, at_hurt->offset.x + translate->x, at_hurt->offset.y + translate->y, at_hurt->offset.z + translate->z);

        gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

        hal_matrix_store_gbi(mtx_store, gMatrixHeap);

        hal_scale(mtx_store.gbi, at_hurt->size.x / 15.0F, at_hurt->size.y / 15.0F, at_hurt->size.z / 15.0F);

        gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

        gDPPipeSync(D_800465B0[0]++);

        switch (at_hurt->hit_status)
        {
        case 1:
            gDPSetPrimColor(D_800465B0[0]++, 0, 0, 255, 255, 255, 255);

            gDPSetEnvColor(D_800465B0[0]++, 208, 208, 0, 255);
            break;

        case 2:
            gDPSetPrimColor(D_800465B0[0]++, 0, 0, 255, 255, 255, 255);

            gDPSetEnvColor(D_800465B0[0]++, 0, 208, 0, 255);
            break;
        case 3:
            gDPSetPrimColor(D_800465B0[0]++, 0, 0, 255, 255, 255, 255);

            gDPSetEnvColor(D_800465B0[0]++, 0, 0, 208, 255);
            break;
        }
        gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C058);

        gSPPopMatrix(D_800465B0[0]++, G_MTX_MODELVIEW);
    }
}

void func_ovl3_801719AC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Vec3f *translate = &DObjGetStruct(article_gobj)->translate;
    ObjectColl *object_coll = &ap->coll_data.object_coll;
    MtxStore mtx_store;

    gDPPipeSync(D_800465B0[1]++);

    hal_matrix_store_gbi(mtx_store, gMatrixHeap);

    hal_translate(mtx_store.gbi, translate->x, translate->y + object_coll->bottom, translate->z);

    gSPMatrix(D_800465B0[1]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    hal_matrix_store_gbi(mtx_store, gMatrixHeap);

    hal_scale(mtx_store.gbi, object_coll->width / 30.0F, (object_coll->center - object_coll->bottom) / 30.0F, 1.0F);

    gSPMatrix(D_800465B0[1]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    gSPDisplayList(D_800465B0[1]++, &D_ovl2_8012C3D8);

    gSPPopMatrix(D_800465B0[1]++, G_MTX_MODELVIEW);

    hal_matrix_store_gbi(mtx_store, gMatrixHeap);

    hal_translate(mtx_store.gbi, translate->x, translate->y + object_coll->center, translate->z);

    gSPMatrix(D_800465B0[1]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    hal_matrix_store_gbi(mtx_store, gMatrixHeap);

    hal_scale(mtx_store.gbi, object_coll->width / 30.0F, (object_coll->top - object_coll->center) / 30.0F, 1.0F);

    gSPMatrix(D_800465B0[1]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    gSPDisplayList(D_800465B0[1]++, &D_ovl2_8012C458);

    gSPPopMatrix(D_800465B0[1]++, G_MTX_MODELVIEW);
}

bool32 func_ovl3_80171C10(Article_Struct *ap)
{
    Fighter_Struct *fp;

    if (ap->owner_gobj == NULL)
    {
        return TRUE;
    }
    else if (!(ap->is_hold))
    {
        return TRUE;
    }
    fp = FighterGetStruct(ap->owner_gobj);

    if (!(fp->x190_flag_b6))
    {
        return FALSE;
    }
    else if (fp->is_invisible)
    {
        return FALSE;
    }
    else return TRUE;
}

void func_ovl3_80171C7C(GObj *article_gobj) // Unused
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_hold))
        {
            func_80014038(article_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            func_80014038(article_gobj);
            func_ovl3_801719AC(article_gobj);
        }
        else if ((ap->article_hurt.hit_status == gmHitCollision_HitStatus_None) && (ap->article_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            func_80014038(article_gobj);
        }
        else func_ovl3_80171410(article_gobj);
    }
}

void func_ovl3_80171D38(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_hold))
        {
            func_80014768(article_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            func_80014768(article_gobj);
            func_ovl3_801719AC(article_gobj);
        }
        else if ((ap->article_hurt.hit_status == gmHitCollision_HitStatus_None) && (ap->article_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            func_80014768(article_gobj);
        }
        else func_ovl3_80171410(article_gobj);
    }
}

void func_ovl3_80171DF4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    gDPPipeSync(D_800465B0[0]++);

    gDPSetCycleType(D_800465B0[0]++, G_CYC_2CYCLE);

    gDPSetRenderMode(D_800465B0[0]++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);

    if (ap->x338_flag_b0)
    {
        gDPSetEnvColor(D_800465B0[0]++, ap->color_anim.r, ap->color_anim.g, ap->color_anim.b, ap->color_anim.a);
    }
    else
    {
        gDPSetEnvColor(D_800465B0[0]++, 0, 0, 0, 0);
    }
    func_80014038(article_gobj);

    gDPPipeSync(D_800465B0[0]++);

    gDPSetCycleType(D_800465B0[0]++, G_CYC_1CYCLE);

    gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

void func_ovl3_80171F4C(GObj *article_gobj) // Unused
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_hold))
        {
            func_ovl3_80171DF4(article_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            func_ovl3_80171DF4(article_gobj);
            func_ovl3_801719AC(article_gobj);
        }
        else if ((ap->article_hurt.hit_status == gmHitCollision_HitStatus_None) && (ap->article_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            func_ovl3_80171DF4(article_gobj);
        }
        else func_ovl3_80171410(article_gobj);
    }
}

void func_ovl3_80172008(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    gDPPipeSync(D_800465B0[0]++);

    gDPSetCycleType(D_800465B0[0]++, G_CYC_2CYCLE);

    gDPSetRenderMode(D_800465B0[0]++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);

    gDPPipeSync(D_800465B0[1]++);

    gDPSetCycleType(D_800465B0[1]++, G_CYC_2CYCLE);

    gDPSetRenderMode(D_800465B0[1]++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);

    if (ap->x338_flag_b0)
    {
        gDPSetEnvColor(D_800465B0[0]++, ap->color_anim.r, ap->color_anim.g, ap->color_anim.b, ap->color_anim.a);

        gDPSetEnvColor(D_800465B0[1]++, ap->color_anim.r, ap->color_anim.g, ap->color_anim.b, ap->color_anim.a);
    }
    else
    {
        gDPSetEnvColor(D_800465B0[0]++, 0, 0, 0, 0);

        gDPSetEnvColor(D_800465B0[1]++, 0, 0, 0, 0);
    }
    func_80014768(article_gobj);

    gDPPipeSync(D_800465B0[0]++);

    gDPSetCycleType(D_800465B0[0]++, G_CYC_1CYCLE);

    gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    gDPPipeSync(D_800465B0[1]++);

    gDPSetCycleType(D_800465B0[1]++, G_CYC_1CYCLE);

    gDPSetRenderMode(D_800465B0[1]++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
}

void func_ovl3_8017224C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_hold))
        {
            func_ovl3_80172008(article_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            func_ovl3_80172008(article_gobj);
            func_ovl3_801719AC(article_gobj);
        }
        else if ((ap->article_hurt.hit_status == gmHitCollision_HitStatus_None) && (ap->article_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            func_ovl3_80172008(article_gobj);
        }
        else func_ovl3_80171410(article_gobj);
    }
}