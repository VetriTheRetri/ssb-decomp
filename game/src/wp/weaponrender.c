#include "weapon.h"

#include <game/src/sys/develop.h>
#include <game/src/sys/hal_gu.h>
#include <game/src/sys/obj_renderer.h>
#include <game/src/sys/obj.h>

#include <game/include/PR/gu.h>
#include <game/include/PR/mbi.h>
#include <game/include/PR/sp.h>
#include <game/include/PR/ultratypes.h>
#include "weaponvars.h"

extern Gfx *D_800465B0[4];

extern BumpAllocRegion gMatrixHeap;

extern Mtx D_ovl2_8012C128;
extern Mtx D_ovl2_8012C160;
extern Mtx D_ovl2_8012C310;

// 0x80166E80
void wpRender_DisplayHitCollisions(GObj *weapon_gobj) // Render item hitboxes
{
    wpStruct *ip = wpGetStruct(weapon_gobj);
    Weapon_Hit *weapon_hit = &ip->weapon_hit;
    MtxStore mtx_store;
    s32 i;

    for (i = 0; i < weapon_hit->hitbox_count; i++)
    {
        if ((weapon_hit->update_state != gmHitCollision_UpdateState_Disable) && (weapon_hit->update_state != gmHitCollision_UpdateState_New))
        {
            gDPPipeSync(D_800465B0[0]++);

            if (ip->display_mode == dbObject_DisplayMode_HitAttackOutline)
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
            if (weapon_hit->update_state == gmHitCollision_UpdateState_Interpolate)
            {
                hal_matrix_store_gbi(mtx_store, gMatrixHeap);

                hal_translate(mtx_store.gbi, weapon_hit->hit_positions[i].pos_prev.x, weapon_hit->hit_positions[i].pos_prev.y, weapon_hit->hit_positions[i].pos_prev.z);

                gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

                hal_matrix_store_gbi(mtx_store, gMatrixHeap);

                hal_scale(mtx_store.gbi, weapon_hit->size / 15.0F, weapon_hit->size / 15.0F, weapon_hit->size / 15.0F);

                gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

                gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C128);

                gSPPopMatrix(D_800465B0[0]++, G_MTX_MODELVIEW);
            }
            hal_matrix_store_gbi(mtx_store, gMatrixHeap);

            hal_translate(mtx_store.gbi, weapon_hit->hit_positions[i].pos.x, weapon_hit->hit_positions[i].pos.y, weapon_hit->hit_positions[i].pos.z);

            gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

            hal_matrix_store_gbi(mtx_store, gMatrixHeap);

            hal_scale(mtx_store.gbi, weapon_hit->size / 15.0F, weapon_hit->size / 15.0F, weapon_hit->size / 15.0F);

            gSPMatrix(D_800465B0[0]++, mtx_store.gbi, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

            if (weapon_hit->update_state == gmHitCollision_UpdateState_Interpolate)
            {
                gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C160);
            }

            gSPDisplayList(D_800465B0[0]++, &D_ovl2_8012C310);

            gSPPopMatrix(D_800465B0[0]++, G_MTX_MODELVIEW);
        }
    }
}

extern Mtx D_ovl2_8012C3D8;
extern Mtx D_ovl2_8012C458;

// 0x801671F0
void wpRender_DisplayMapCollisions(GObj *weapon_gobj) // Render item ECB?
{
    wpStruct *ip = wpGetStruct(weapon_gobj);
    Vec3f *translate = &DObjGetStruct(weapon_gobj)->translate;
    ObjectColl *object_coll = &ip->coll_data.object_coll;
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

void func_ovl3_80167454(void)
{
    gDPPipeSync(D_800465B0[1]++);

    gSPClearGeometryMode(D_800465B0[1]++, G_ZBUFFER);

    gDPSetRenderMode(D_800465B0[1]++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
}

void func_ovl3_801674B8(void)
{
    gDPPipeSync(D_800465B0[1]++);

    gSPSetGeometryMode(D_800465B0[1]++, G_ZBUFFER);

    gDPSetRenderMode(D_800465B0[1]++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
}

void func_ovl3_80167520(GObj *weapon_gobj, void(*proc_render)(GObj*))
{
    wpStruct *ip = wpGetStruct(weapon_gobj);

    if (ip->display_mode == dbObject_DisplayMode_MapCollision)
    {
        func_ovl3_80167454(weapon_gobj);

        proc_render(weapon_gobj);

        func_ovl3_801674B8();

        wpRender_DisplayMapCollisions(weapon_gobj);
    }
    else
    {
        if ((ip->display_mode == dbObject_DisplayMode_Master) || (ip->weapon_hit.update_state == gmHitCollision_UpdateState_Disable))
        {
            func_ovl3_80167454();

            proc_render(weapon_gobj);

            func_ovl3_801674B8();
        }
        else wpRender_DisplayHitCollisions(weapon_gobj);
    }
}

void func_ovl3_801675D0(GObj *weapon_gobj)
{
    func_ovl3_80167520(weapon_gobj, func_80013E8C);
}

void func_ovl3_801675F4(GObj *weapon_gobj)
{
    func_ovl3_80167520(weapon_gobj, func_800143FC);
}

void func_ovl3_80167618(GObj *weapon_gobj)
{
    func_ovl3_80167520(weapon_gobj, func_ovl0_800CB4B0); // Unused
}

void func_ovl3_8016763C(GObj *weapon_gobj)
{
    func_ovl3_80167520(weapon_gobj, func_80014768);
}

GfxColor wpNess_PKThunder_PrimColor[WPPKTHUNDER_TRAIL_COUNT - 1]    = { { 94, 163, 255 }, { 152, 189, 255 }, { 194, 217, 255 }, { 179, 241, 255 } };
GfxColor wpNess_PKThunder_EnvColor[WPPKTHUNDER_TRAIL_COUNT - 1]     = { { 58,   0, 131 }, {  91,   0, 178 }, { 134,  51, 217 }, { 167, 116, 248 } };

// 0x80167660
void wpRender_DisplayPKThunder(GObj *weapon_gobj)
{
    wpStruct *ip = wpGetStruct(weapon_gobj);
    s32 index = ip->weapon_vars.pkthunder_trail.trail_index;

    if (ip->display_mode == dbObject_DisplayMode_MapCollision)
    {
        func_ovl3_80167454();

        gDPPipeSync(D_800465B0[1]++);

        gDPSetPrimColor(D_800465B0[1]++, 0, 0, wpNess_PKThunder_PrimColor[index].r, wpNess_PKThunder_PrimColor[index].g, wpNess_PKThunder_PrimColor[index].b, 255);

        gDPSetEnvColor(D_800465B0[1]++, wpNess_PKThunder_EnvColor[index].r, wpNess_PKThunder_EnvColor[index].g, wpNess_PKThunder_EnvColor[index].b, 255);

        func_800143FC(weapon_gobj);

        func_ovl3_801674B8();

        wpRender_DisplayMapCollisions(weapon_gobj);
    }
    else if ((ip->display_mode == dbObject_DisplayMode_Master) || (ip->weapon_hit.update_state == gmHitCollision_UpdateState_Disable))
    {
        func_ovl3_80167454();

        gDPPipeSync(D_800465B0[1]++);

        gDPSetPrimColor(D_800465B0[1]++, 0, 0, wpNess_PKThunder_PrimColor[index].r, wpNess_PKThunder_PrimColor[index].g, wpNess_PKThunder_PrimColor[index].b, 255);

        gDPSetEnvColor(D_800465B0[1]++, wpNess_PKThunder_EnvColor[index].r, wpNess_PKThunder_EnvColor[index].g, wpNess_PKThunder_EnvColor[index].b, 255);

        func_800143FC(weapon_gobj);

        func_ovl3_801674B8();
    }
    else wpRender_DisplayHitCollisions(weapon_gobj);
}
