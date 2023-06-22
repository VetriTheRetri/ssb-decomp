#include "item.h"
#include "fighter.h"

#include <game/src/sys/develop.h>
#include <game/src/sys/hal_gu.h>
#include <game/src/sys/obj_renderer.h>
#include <game/src/sys/obj.h>

#include <game/include/PR/gu.h>
#include <game/include/PR/mbi.h>
#include <game/include/PR/sp.h>
#include <game/include/PR/ultratypes.h>

void func_ovl3_80171410(GObj *item_gobj)
{
    Item_Struct *ap;
    s32 i;
    Item_Hit *it_hit;
    Item_Hurt *at_hurt;
    MtxStore mtx_store;
    Vec3f *translate;

    ap = itGetStruct(item_gobj);
    it_hit = &ap->item_hit;

    for (i = 0; i < it_hit->hitbox_count; i++)
    {
        if ((it_hit->update_state != gmHitCollision_UpdateState_Disable) && (it_hit->update_state != gmHitCollision_UpdateState_New))
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
            if (it_hit->update_state == gmHitCollision_UpdateState_Interpolate)
            {
                hal_matrix_store_gbi(mtx_store, gMatrixHeap);

                hal_translate(mtx_store.gbi, it_hit->item_hit_unk[i].pos_prev.x, it_hit->item_hit_unk[i].pos_prev.y, it_hit->item_hit_unk[i].pos_prev.z);

                gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

                hal_matrix_store_gbi(mtx_store, gMatrixHeap);

                hal_scale(mtx_store.gbi, it_hit->size / 15.0F, it_hit->size / 15.0F, it_hit->size / 15.0F);

                gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

                gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C128);

                gSPPopMatrix(D_800465B0[0]++, G_MTX_MODELVIEW);
            }
            hal_matrix_store_gbi(mtx_store, gMatrixHeap);

            hal_translate(mtx_store.gbi, it_hit->item_hit_unk[i].pos.x, it_hit->item_hit_unk[i].pos.y, it_hit->item_hit_unk[i].pos.z);

            gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

            hal_matrix_store_gbi(mtx_store, gMatrixHeap);

            hal_scale(mtx_store.gbi, it_hit->size / 15.0F, it_hit->size / 15.0F, it_hit->size / 15.0F);

            gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

            if (it_hit->update_state == gmHitCollision_UpdateState_Interpolate)
            {
                gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C160);
            }
            gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C310);

            gSPPopMatrix(D_800465B0[0]++, G_MTX_MODELVIEW);
        }
    }
    at_hurt = &ap->item_hurt;

    if (ap->item_hurt.hitstatus != gmHitCollision_HitStatus_None)
    {
        translate = &DObjGetStruct(item_gobj)->translate;

        hal_matrix_store_gbi(mtx_store, gMatrixHeap);

        hal_translate(mtx_store.gbi, at_hurt->offset.x + translate->x, at_hurt->offset.y + translate->y, at_hurt->offset.z + translate->z);

        gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

        hal_matrix_store_gbi(mtx_store, gMatrixHeap);

        hal_scale(mtx_store.gbi, at_hurt->size.x / 15.0F, at_hurt->size.y / 15.0F, at_hurt->size.z / 15.0F);

        gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

        gDPPipeSync(D_800465B0[0]++);

        switch (at_hurt->hitstatus)
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

void func_ovl3_801719AC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    Vec3f *translate = &DObjGetStruct(item_gobj)->translate;
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

bool32 func_ovl3_80171C10(Item_Struct *ap)
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
    fp = ftGetStruct(ap->owner_gobj);

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

void func_ovl3_80171C7C(GObj *item_gobj) // Unused
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_hold))
        {
            func_80014038(item_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            func_80014038(item_gobj);
            func_ovl3_801719AC(item_gobj);
        }
        else if ((ap->item_hurt.hitstatus == gmHitCollision_HitStatus_None) && (ap->item_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            func_80014038(item_gobj);
        }
        else func_ovl3_80171410(item_gobj);
    }
}

void func_ovl3_80171D38(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_hold))
        {
            func_80014768(item_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            func_80014768(item_gobj);
            func_ovl3_801719AC(item_gobj);
        }
        else if ((ap->item_hurt.hitstatus == gmHitCollision_HitStatus_None) && (ap->item_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            func_80014768(item_gobj);
        }
        else func_ovl3_80171410(item_gobj);
    }
}

void func_ovl3_80171DF4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    gDPPipeSync(D_800465B0[0]++);

    gDPSetCycleType(D_800465B0[0]++, G_CYC_2CYCLE);

    gDPSetRenderMode(D_800465B0[0]++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);

    if (ap->x338_flag_b0)
    {
        gDPSetEnvColor(D_800465B0[0]++, ap->colanim.color1.r, ap->colanim.color1.g, ap->colanim.color1.b, ap->colanim.color1.a);
    }
    else
    {
        gDPSetEnvColor(D_800465B0[0]++, 0, 0, 0, 0);
    }
    func_80014038(item_gobj);

    gDPPipeSync(D_800465B0[0]++);

    gDPSetCycleType(D_800465B0[0]++, G_CYC_1CYCLE);

    gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

void func_ovl3_80171F4C(GObj *item_gobj) // Unused
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_hold))
        {
            func_ovl3_80171DF4(item_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            func_ovl3_80171DF4(item_gobj);
            func_ovl3_801719AC(item_gobj);
        }
        else if ((ap->item_hurt.hitstatus == gmHitCollision_HitStatus_None) && (ap->item_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            func_ovl3_80171DF4(item_gobj);
        }
        else func_ovl3_80171410(item_gobj);
    }
}

void func_ovl3_80172008(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    gDPPipeSync(D_800465B0[0]++);

    gDPSetCycleType(D_800465B0[0]++, G_CYC_2CYCLE);

    gDPSetRenderMode(D_800465B0[0]++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);

    gDPPipeSync(D_800465B0[1]++);

    gDPSetCycleType(D_800465B0[1]++, G_CYC_2CYCLE);

    gDPSetRenderMode(D_800465B0[1]++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);

    if (ap->x338_flag_b0)
    {
        gDPSetEnvColor(D_800465B0[0]++, ap->colanim.color1.r, ap->colanim.color1.g, ap->colanim.color1.b, ap->colanim.color1.a);

        gDPSetEnvColor(D_800465B0[1]++, ap->colanim.color1.r, ap->colanim.color1.g, ap->colanim.color1.b, ap->colanim.color1.a);
    }
    else
    {
        gDPSetEnvColor(D_800465B0[0]++, 0, 0, 0, 0);

        gDPSetEnvColor(D_800465B0[1]++, 0, 0, 0, 0);
    }
    func_80014768(item_gobj);

    gDPPipeSync(D_800465B0[0]++);

    gDPSetCycleType(D_800465B0[0]++, G_CYC_1CYCLE);

    gDPSetRenderMode(D_800465B0[0]++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    gDPPipeSync(D_800465B0[1]++);

    gDPSetCycleType(D_800465B0[1]++, G_CYC_1CYCLE);

    gDPSetRenderMode(D_800465B0[1]++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
}

void func_ovl3_8017224C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_80171C10(ap) != FALSE)
    {
        if ((ap->display_state == dbObjDisplayStatus_Master) || (ap->is_hold))
        {
            func_ovl3_80172008(item_gobj);
        }
        else if (ap->display_state == dbObjDisplayStatus_MapCollision)
        {
            func_ovl3_80172008(item_gobj);
            func_ovl3_801719AC(item_gobj);
        }
        else if ((ap->item_hurt.hitstatus == gmHitCollision_HitStatus_None) && (ap->item_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            func_ovl3_80172008(item_gobj);
        }
        else func_ovl3_80171410(item_gobj);
    }
}