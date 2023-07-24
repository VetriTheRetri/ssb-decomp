#include "mpcoll.h"
#include "gmmisc.h"

extern mpRoomInfoContainer *gpMapRooms;
extern mpGeometryInfo *gpMapGeometry;
extern mpVertexInfoContainer *gpMapVertexInfo;
extern mpVertexArray *gpMapVertexID;
extern mpVertexLinks *gpMapVertexLinks;   //
extern mpVertexPosContainer *gpMapVertexData; // Vertex positions
extern Vec3f *gpMapRoomVectors;
extern mpUnkVectorContainer *D_ovl2_80131380;

f32 func_ovl2_800F39F0(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    return (f32)arg2 + (((arg0 - (f32)arg1) / (f32)(arg3 - arg1)) * (f32)(arg4 - arg2));
}

f32 func_ovl2_800F3A34(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    return (f32)arg1 + (((arg0 - (f32)arg2) / (f32)(arg4 - arg2)) * (f32)(arg3 - arg1));
}

// 0x800F3A78
bool32 mpCollision_GetUUCommon(s32 line_id, Vec3f *object_pos, f32 *arg2, u32 *flags, Vec3f *angle, s32 lr)
{
    mpVertexLinks *vlinks;
    mpRoomInfo *room_info;
    f32 vnear;
    u16 *pv;
    s32 v1x;
    s32 v1y;
    s32 v2x;
    s32 v2y;
    f32 vfar;
    f32 object_pos_x;
    f32 object_pos_y;
    s32 vid;
    u16 vertex1;
    s32 i;

    if ((line_id == -1) || (line_id == -2)) // -1 = not above ground, -2 = ???
    {
        while (TRUE)
        {
            fatal_printf("mpGetUUCommon() id = %d\n", line_id); // Since we're exclusively checking ground collision and the line ID passed isn't ground-valid, report the error

            scnmgr_crash_print_gobj_state();
        }
    }
    room_info = gpMapRooms->room_info[gpMapVertexInfo->vertex_info[line_id].room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetUUCommon() no collsion\n");

            scnmgr_crash_print_gobj_state();
        }
    }
    vlinks = &gpMapVertexLinks[line_id];

    if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
    {
        object_pos_x = object_pos->x - room_info->dynacoll_pos.x;
        object_pos_y = object_pos->y - room_info->dynacoll_pos.y;
    }
    else
    {
        object_pos_x = object_pos->x;
        object_pos_y = object_pos->y;
    }
    vertex1 = vlinks->vertex1;
    pv = &gpMapVertexID->vertex_id[vertex1];
    v1x = gpMapVertexData->vpos[pv[0]].pos.x;
    vid = vlinks->vertex2 - 1;
    v2x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex1 + vid]].pos.x;

    if (v2x < v1x)
    {
        vfar = v1x;
        vnear = v2x;
    }
    else
    {
        vfar = v2x;
        vnear = v1x;
    }
    if ((object_pos_x <= (vnear - 0.001F)) || ((vfar + 0.001F) <= object_pos_x))
    {
        return FALSE;
    }
    if (object_pos_x <= vnear)
    {
        object_pos_x = vnear;
    }
    else if (vfar <= object_pos_x)
    {
        object_pos_x = vfar;
    }
    if (vid != 1)
    {
        for (i = 0; i < vid; i++, pv++)
        {
            v1x = gpMapVertexData->vpos[pv[0]].pos.x;
            v2x = gpMapVertexData->vpos[pv[1]].pos.x;

            if (v2x == v1x)
            {
                while (TRUE)
                {
                    fatal_printf("same vtx x error mpGetUUCommon\n");
                    scnmgr_crash_print_gobj_state();
                }
            }
            if (((v1x <= object_pos_x) && (object_pos_x <= v2x)) || ((v2x <= object_pos_x) && (object_pos_x <= v1x)))
            {
                break;
            }
        }
    }
    v1y = gpMapVertexData->vpos[pv[0]].pos.y;
    v2y = gpMapVertexData->vpos[pv[1]].pos.y;

    if (flags != NULL)
    {
        *flags = gpMapVertexData->vpos[pv[0]].vertex_flags;
    }
    if (arg2 != NULL)
    {
        *arg2 = func_ovl2_800F39F0(object_pos_x, vnear, v1y, v2x, v2y) - object_pos_y;
    }
    if (angle != NULL)
    {
        mpCollision_GetUDAngle(angle, v1x, v1y, v2x, v2y, lr);
    }
    return TRUE;
}

// 0x800F3DD8
bool32 mpCollision_GetUUCommonUp(s32 line_id, Vec3f *object_pos, f32 *arg2, u32 *flags, Vec3f *angle)
{
    return mpCollision_GetUUCommon(line_id, object_pos, arg2, flags, angle, 1);
}

bool32 func_ovl2_800F3E04(s32 line_id, Vec3f *object_pos, f32 *arg2, u32 *flags, Vec3f *angle)
{
    return mpCollision_GetUUCommon(line_id, object_pos, arg2, flags, angle, -1);
}

// 0x800F3E30
bool32 mpCollision_GetLRCommon(s32 line_id, Vec3f *object_pos, f32 *arg2, u32 *flags, Vec3f *angle, s32 lr)
{
    mpVertexLinks *vlinks;
    mpRoomInfo *room_info;
    f32 vnear;
    f32 vfar;
    s32 v1x;
    s32 v1y;
    s32 v2x;
    s32 v2y;
    f32 object_pos_y;
    f32 object_pos_x;
    s32 vid;
    u16 vertex1;
    u16 *pv;
    s32 i;

    if ((line_id == -1) || (line_id == -2)) // -1 = not above ground, -2 = ???
    {
        while (TRUE)
        {
            fatal_printf("mpGetLRCommon() id = %d\n", line_id);

            scnmgr_crash_print_gobj_state();
        }
    }
    room_info = gpMapRooms->room_info[gpMapVertexInfo->vertex_info[line_id].room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetLRCommon() no collision\n");

            scnmgr_crash_print_gobj_state();
        }
    }
    vlinks = &gpMapVertexLinks[line_id];

    if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
    {
        object_pos_x = object_pos->x - room_info->dynacoll_pos.x;
        object_pos_y = object_pos->y - room_info->dynacoll_pos.y;
    }
    else
    {
        object_pos_x = object_pos->x;
        object_pos_y = object_pos->y;
    }
    vertex1 = vlinks->vertex1;
    pv = &gpMapVertexID->vertex_id[vertex1];
    v1y = gpMapVertexData->vpos[pv[0]].pos.y;
    vid = vlinks->vertex2 - 1;
    v2y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex1 + vid]].pos.y;

    if (v2y < v1y)
    {
        vfar = v1y;
        vnear = v2y;
    }
    else
    {
        vfar = v2y;
        vnear = v1y;
    }
    if ((object_pos_y <= (vnear - 0.001F)) || ((vfar + 0.001F) <= object_pos_y))
    {
        return FALSE;
    }
    if (object_pos_y <= vnear)
    {
        object_pos_y = vnear;
    }
    else if (vfar <= object_pos_y)
    {
        object_pos_y = vfar;
    }
    if (vid != 1)
    {
        for (i = 0; i < vid; i++, pv++)
        {
            v1y = gpMapVertexData->vpos[pv[0]].pos.y;
            v2y = gpMapVertexData->vpos[pv[1]].pos.y;

            if (v2y == v1y)
            {
                while (TRUE)
                {
                    fatal_printf("same vtx y error mpGetLRCommon\n");
                    scnmgr_crash_print_gobj_state();
                }
            }
            if (((v1y <= object_pos_y) && (object_pos_y <= v2y)) || ((v2y <= object_pos_y) && (object_pos_y <= v1y)))
            {
                break;
            }
        }
    }
    v1x = gpMapVertexData->vpos[pv[0]].pos.x;
    v2x = gpMapVertexData->vpos[pv[1]].pos.x;

    if (flags != NULL)
    {
        *flags = gpMapVertexData->vpos[pv[0]].vertex_flags;
    }
    if (arg2 != NULL)
    {
        *arg2 = func_ovl2_800F3A34(object_pos_y, v1x, v1y, v2x, v2y) - object_pos_x;
    }
    if (angle != NULL)
    {
        mpCollision_GetLRAngle(angle, v1x, v1y, v2x, v2y, lr);
    }
    return TRUE;
}

bool32 func_ovl2_800F4194(s32 line_id, Vec3f *object_pos, f32 *arg2, u32 *flags, Vec3f *angle)
{
    return mpCollision_GetLRCommon(line_id, object_pos, arg2, flags, angle, -1);
}

bool32 func_ovl2_800F41C0(s32 line_id, Vec3f *object_pos, f32 *arg2, u32 *flags, Vec3f *angle)
{
    return mpCollision_GetLRCommon(line_id, object_pos, arg2, flags, angle, 1);
}

// 0x800F41EC
void mpCollision_GetLREdge(s32 line_id, Vec3f *object_pos, s32 lr)
{
    mpVertexLinks *vlinks;
    mpRoomInfo *room_info;
    s32 v1x;
    s32 v1y;
    s32 v2x;
    s32 v2y;
    s32 vid;
    u16 vertex1;
    bool32 cmp_lt;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetLREdge() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    room_info = gpMapRooms->room_info[gpMapVertexInfo->vertex_info[line_id].room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetLREdge() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    vlinks = &gpMapVertexLinks[line_id];
    vertex1 = vlinks->vertex1;
    vid = (vlinks->vertex2 + vertex1) - 1;
    v1x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex1]].pos.x;
    v2x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vid]].pos.x;

    cmp_lt = (lr < 0) ? (v1x < v2x) : (v2x < v1x);

    if (cmp_lt != FALSE)
    {
        object_pos->x = v1x;
        object_pos->y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex1]].pos.y;
    }
    else
    {
        object_pos->x = v2x;
        object_pos->y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vid]].pos.y;
    }
    object_pos->z = 0.0F;

    if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
    {
        object_pos->x += room_info->dynacoll_pos.x;
        object_pos->y += room_info->dynacoll_pos.y;
    }
}

// 0x800F4408
void mpCollision_GetLREdgeRight(s32 line_id, Vec3f *object_pos)
{
    mpCollision_GetLREdge(line_id, object_pos, 1);
}

// 0x800F4428
void mpCollision_GetLREdgeLeft(s32 line_id, Vec3f *object_pos)
{
    mpCollision_GetLREdge(line_id, object_pos, -1);
}

void func_ovl2_800F4448(s32 line_id, Vec3f *object_pos)
{
    mpCollision_GetLREdge(line_id, object_pos, 1);
}

void func_ovl2_800F4468(s32 line_id, Vec3f *object_pos)
{
    mpCollision_GetLREdge(line_id, object_pos, -1);
}

// 0x800F4488
void mpCollision_GetUDEdge(s32 line_id, Vec3f *object_pos, s32 ud)
{
    mpVertexLinks *vlinks;
    mpRoomInfo *room_info;
    mpVertexData *vpos1;
    mpVertexData *vpos2;
    s32 v1x;
    s32 v1y;
    s32 v2x;
    s32 v2y;
    s32 vid;
    u16 vertex1;
    bool32 cmp_lt;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetUDEdge() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    room_info = gpMapRooms->room_info[gpMapVertexInfo->vertex_info[line_id].room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetUDEdge() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    vlinks = &gpMapVertexLinks[line_id];
    vertex1 = vlinks->vertex1;
    vid = (vlinks->vertex2 + vertex1) - 1;
    vpos1 = &gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex1]];
    vpos2 = &gpMapVertexData->vpos[gpMapVertexID->vertex_id[vid]];

    v1y = vpos1->pos.y;
    v2y = vpos2->pos.y;

    cmp_lt = (ud < 0) ? (v1y < v2y) : (v2y < v1y);

    if (cmp_lt != FALSE)
    {
        object_pos->x = vpos1->pos.x;
        object_pos->y = v1y;
    }
    else
    {
        object_pos->x = vpos2->pos.x;
        object_pos->y = v2y;
    }
    object_pos->z = 0.0F;

    if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
    {
        object_pos->x += room_info->dynacoll_pos.x;
        object_pos->y += room_info->dynacoll_pos.y;
    }
}

void func_ovl2_800F4650(s32 line_id, Vec3f *object_pos)
{
    mpCollision_GetUDEdge(line_id, object_pos, 1);
}

void func_ovl2_800F4670(s32 line_id, Vec3f *object_pos)
{
    mpCollision_GetUDEdge(line_id, object_pos, -1);
}

void func_ovl2_800F4690(s32 line_id, Vec3f *object_pos)
{
    mpCollision_GetUDEdge(line_id, object_pos, 1);
}

void func_ovl2_800F46B0(s32 line_id, Vec3f *object_pos)
{
    mpCollision_GetUDEdge(line_id, object_pos, -1);
}

// 0x800F46D0
void mpCollision_GetUDAngle(Vec3f *angle, s32 v1x, s32 v1y, s32 v2x, s32 v2y, s32 lr)
{
    f32 py, sqrt_py;
    f32 dist_y;

    angle->z = 0.0F;

    dist_y = (v2y - v1y);

    if (dist_y == 0.0F)
    {
        angle->x = 0.0F;
        angle->y = lr;

        return;
    }
    py = -(dist_y / (v2x - v1x));

    sqrt_py = 1.0F / sqrtf(SQUARE(py) + 1.0F);

    if (lr < 0)
    {
        angle->x = (-py * sqrt_py);
        angle->y = -sqrt_py;
    }
    else
    {
        angle->x = (py * sqrt_py);
        angle->y = sqrt_py;
    }
    vec3f_normalize(angle);
}

// 0x800F47AC Also calculates angle? Runs whenever character lands directly on a line surface that isn't 0 degrees
bool32 mpCollision_CheckGroundSurfaceTilt(s32 v1x, s32 v1y, s32 v2x, s32 v2y, f32 d1x, f32 d1y, f32 d2x, f32 d2y, f32 *dfx, f32 *dfy)
{
    s32 vfary;
    s32 vneary;
    f32 ddist_x;
    f32 ddist_y;
    s32 vfarx;
    s32 vnearx;
    s32 vdist_y;
    s32 vdist_x;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 vddiv;
    f32 vddist_x;
    f32 vddist_y;
    f32 vddistdiv;
    f32 vdscale;
    f32 scale;
    f32 var_f18;

    vdist_y = v2y - v1y;
    ddist_y = d1y - d2y;

    if (vdist_y < 0)
    {
        vneary = v2y;
        vfary = v1y;
    }
    else
    {
        vfary = v2y;
        vneary = v1y;
    }
    if (ddist_y > 0.0F)
    {
        if (((vfary + 0.001F) < d2y) || (d1y < (vneary - 0.001F)))
        {
            return FALSE;
        }
    }
    else if (((vfary + 0.001F) < d1y) || (d2y < (vneary - 0.001F)))
    {
        return FALSE;
    }
    ddist_x = d1x - d2x;
    vdist_x = v2x - v1x;

    if (vdist_x < 0)
    {
        vnearx = v2x;
        vfarx = v1x;
    }
    else
    {
        vfarx = v2x;
        vnearx = v1x;
    }
    if (ddist_x > 0.0F)
    {
        if ((vfarx < d2x) || (d1x < vnearx))
        {
            return FALSE;
        }
    }
    else if ((vfarx < d1x) || (d2x < vnearx))
    {
        return FALSE;
    }
    if ((d2y - (v1y + (((d2x - v1x) / vdist_x) * vdist_y))) <= (-0.001F))
    {
        temp_f12_2 = v1y + (((d1x - v1x) / vdist_x) * vdist_y);

        if ((d1y - temp_f12_2) < 0.001F)
        {
            if (((-0.001F) < (d1y - temp_f12_2)) && (d1x <= vfarx) && (vnearx <= d1x))
            {
                *dfx = d1x;
                *dfy = temp_f12_2;

                return TRUE;
            }
        }
        else
        {
            vddist_x = v1x - d1x;
            vddist_y = v1y - d1y;

            var_f18 = (ddist_y * vddist_x) - (ddist_x * vddist_y);
            scale = (vdist_y * ddist_x) - (vdist_x * ddist_y);

            vddiv = var_f18 / scale;

            if (vddiv < 0.0F)
            {
                if (vddiv < (-0.001F))
                {
                    return FALSE;
                }
                var_f18 = 0.0F;
            }
            else if (vddiv > 1.0F)
            {
                if (1.001F < vddiv)
                {
                    return FALSE;
                }
                var_f18 = scale;
            }
            vddistdiv = ((vdist_x * vddist_y) - (vdist_y * vddist_x)) / scale;

            if ((vddistdiv < (-0.001F)) || (1.001F < vddistdiv))
            {
                return FALSE;
            }
            vdscale = 1.0F / scale;

            *dfx = v1x + (var_f18 * vdist_x * vdscale);
            *dfy = v1y + (var_f18 * vdist_y * vdscale);

            return TRUE;
        }
    }
    return FALSE;
}

// 0x800F4BD8
bool32 func_ovl2_800F4BD8(Vec3f *position, Vec3f *translate, Vec3f *ga_last, s32 *stand_line_id, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i;
    f32 vdist1;
    f32 vdist2;
    f32 vpdist_x, vpdist_y;
    f32 vtdist_x, vtdist_y;
    f32 line_project_pos;
    f32 vedge_x;
    f32 vedge_y;
    s32 line_id, vertex_id;
    s32 temp_s0;
    s32 temp_s1;
    s32 vpos_x;
    s32 vpos_y;
    f32 spB0;
    f32 spAC;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_Ground];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vedge_x = room_info->dynacoll_pos.x;
                vedge_y = room_info->dynacoll_pos.y;

                vpdist_x = position->x - vedge_x;
                vpdist_y = position->y - vedge_y;

                vtdist_x = translate->x - vedge_x;
                vtdist_y = translate->y - vedge_y;
            }
            else
            {
                vedge_x = vedge_y = 0.0F;

                vpdist_x = position->x;
                vpdist_y = position->y;

                vtdist_x = translate->x;
                vtdist_y = translate->y;
            }
            if (vpdist_y < vtdist_y)
            {
                vdist1 = vpdist_y - 0.001F;
                vdist2 = vtdist_y + 0.001F;
            }
            else
            {
                vdist1 = vtdist_y - 0.001F;
                vdist2 = vpdist_y + 0.001F;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev > vdist2)
                {
                    continue;
                }
                else if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next < vdist1)
                {
                    goto lbl_break; // Bruhhhhhhhhhhhhhhh
                }
                else
                {
                    vertex_id = gpMapVertexLinks[line_id].vertex1;

                    vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.x;
                    vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.y;

                    for (vertex_id = gpMapVertexLinks[line_id].vertex1; vertex_id < (gpMapVertexLinks[line_id].vertex1 + gpMapVertexLinks[line_id].vertex2) - 1; vertex_id++)
                    {
                        temp_s1 = vpos_x;
                        temp_s0 = vpos_y;

                        vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.x;
                        vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.y;

                        if (temp_s0 == vpos_y)
                        {
                            if (vtdist_y < vpdist_y)
                            {
                                if (mpCollision_CheckUDSurfaceFlat(temp_s1, temp_s0, vpos_x, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                                {
                                    if (line_project_pos <= ((spAC < vpdist_y) ? -(spAC - vpdist_y) : (spAC - vpdist_y))) continue;

                                    if (ga_last != NULL)
                                    {
                                        ga_last->x = spB0 + vedge_x;
                                        ga_last->y = spAC + vedge_y;
                                        ga_last->z = 0.0F;
                                    }
                                    if (stand_line_id != NULL)
                                    {
                                        *stand_line_id = line_id;
                                    }
                                    if (angle != NULL)
                                    {
                                        angle->x = angle->z = 0.0F;
                                        angle->y = 1.0F;
                                    }
                                    if (stand_coll_flags != NULL)
                                    {
                                        *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                                    }
                                    line_project_pos = (spAC < vpdist_y) ? -(spAC - vpdist_y) : (spAC - vpdist_y);
                                }
                            }
                        }
                        else if (mpCollision_CheckGroundSurfaceTilt(temp_s1, temp_s0, vpos_x, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                        {
                            if (line_project_pos <= ((spAC < vpdist_y) ? -(spAC - vpdist_y) : (spAC - vpdist_y))) continue;

                            if (ga_last != NULL)
                            {
                                ga_last->x = spB0 + vedge_x;
                                ga_last->y = spAC + vedge_y;
                                ga_last->z = 0.0F;
                            }
                            if (stand_line_id != NULL)
                            {
                                *stand_line_id = line_id;
                            }
                            if (angle != NULL)
                            {
                                mpCollision_GetUDAngle(angle, temp_s1, temp_s0, vpos_x, vpos_y, 1);
                            }
                            if (stand_coll_flags != NULL)
                            {
                                *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                            }
                            line_project_pos = (spAC < vpdist_y) ? -(spAC - vpdist_y) : (spAC - vpdist_y);
                        }
                    }
                }
            }
        lbl_break: // BRUHHHHHHHHHHHHHHHHH
            continue;
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

bool32 func_ovl2_800F521C(Vec3f *position, Vec3f *translate, Vec3f *ga_last, s32 *stand_line_id, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i;
    f32 vdist1;
    f32 vdist2;
    f32 vpdist_x, vpdist_y;
    f32 vtdist_x, vtdist_y;
    f32 line_project_pos;
    f32 vedge_y;
    f32 unkpos_y;
    f32 vedge_x;
    s32 line_id, vertex_id;
    s32 temp_s0;
    s32 temp_s1;
    s32 vpos_x;
    s32 vpos_y;
    f32 spB0;
    f32 spAC;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_Ground];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vedge_x = room_info->dynacoll_pos.x;
                vedge_y = room_info->dynacoll_pos.y;

                unkpos_y = gpMapRoomVectors[line_info->room_id].y;

                vpdist_x = (position->x - vedge_x) + gpMapRoomVectors[line_info->room_id].x;
                vpdist_y = (position->y - vedge_y) + unkpos_y;

                vtdist_x = translate->x - vedge_x;
                vtdist_y = translate->y - vedge_y;
            }
            else
            {
                unkpos_y = 0.0F;
                vedge_x = vedge_y = 0.0F;

                vpdist_x = position->x;
                vpdist_y = position->y;

                vtdist_x = translate->x;
                vtdist_y = translate->y;
            }
            if (vpdist_y < vtdist_y)
            {
                vdist1 = vpdist_y - 0.001F;
                vdist2 = vtdist_y + 0.001F;
            }
            else
            {
                vdist1 = vtdist_y - 0.001F;
                vdist2 = vpdist_y + 0.001F;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev > vdist2)
                {
                    continue;
                }
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next < vdist1)
                {
                    goto lbl_break; // Bruhhhhhhhhhhhhhhh
                }
                else
                {
                    vertex_id = gpMapVertexLinks[line_id].vertex1;

                    vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.x;
                    vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.y;

                    for (vertex_id = gpMapVertexLinks[line_id].vertex1; vertex_id < (gpMapVertexLinks[line_id].vertex1 + gpMapVertexLinks[line_id].vertex2) - 1; vertex_id++)
                    {
                        temp_s1 = vpos_x;
                        temp_s0 = vpos_y;

                        vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.x;
                        vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.y;

                        if (temp_s0 == vpos_y)
                        {
                            if (vtdist_y < vpdist_y)
                            {
                                if (mpCollision_CheckUDSurfaceFlat(temp_s1, temp_s0, vpos_x, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                                {
                                    if (line_project_pos <= ((spAC < (vpdist_y - unkpos_y)) ? -(spAC - (vpdist_y - unkpos_y)) : (spAC - (vpdist_y - unkpos_y)))) continue;

                                    if (ga_last != NULL)
                                    {
                                        ga_last->x = spB0 + vedge_x;
                                        ga_last->y = spAC + vedge_y;
                                        ga_last->z = 0.0F;
                                    }
                                    if (stand_line_id != NULL)
                                    {
                                        *stand_line_id = line_id;
                                    }
                                    if (angle != NULL)
                                    {
                                        angle->x = angle->z = 0.0F;
                                        angle->y = 1.0F;
                                    }
                                    if (stand_coll_flags != NULL)
                                    {
                                        *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                                    }
                                    line_project_pos = (spAC < (vpdist_y - unkpos_y)) ? -(spAC - (vpdist_y - unkpos_y)) : (spAC - (vpdist_y - unkpos_y));
                                }
                            }
                        }
                        else if (mpCollision_CheckGroundSurfaceTilt(temp_s1, temp_s0, vpos_x, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                        {
                            if (line_project_pos <= ((spAC < (vpdist_y - unkpos_y)) ? -(spAC - (vpdist_y - unkpos_y)) : (spAC - (vpdist_y - unkpos_y)))) continue;

                            if (ga_last != NULL)
                            {
                                ga_last->x = spB0 + vedge_x;
                                ga_last->y = spAC + vedge_y;
                                ga_last->z = 0.0F;
                            }
                            if (stand_line_id != NULL)
                            {
                                *stand_line_id = line_id;
                            }
                            if (angle != NULL)
                            {
                                mpCollision_GetUDAngle(angle, temp_s1, temp_s0, vpos_x, vpos_y, 1);
                            }
                            if (stand_coll_flags != NULL)
                            {
                                *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                            }
                            line_project_pos = (spAC < (vpdist_y - unkpos_y)) ? -(spAC - (vpdist_y - unkpos_y)) : (spAC - (vpdist_y - unkpos_y));
                        }
                    }
                }
            }
        lbl_break: // BRUHHHHHHHHHHHHHHHHH
            continue;
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

// 0x800F5A64
bool32 mpCollision_CheckCeilSurfaceTilt(s32 v1x, s32 v1y, s32 v2x, s32 v2y, f32 d1x, f32 d1y, f32 d2x, f32 d2y, f32 *dfx, f32 *dfy)
{
    s32 vfary;
    s32 vneary;
    f32 ddist_x;
    f32 ddist_y;
    s32 vfarx;
    s32 vnearx;
    s32 vdist_y;
    s32 vdist_x;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 vddiv;
    f32 vddist_x;
    f32 vddist_y;
    f32 vddistdiv;
    f32 vdscale;
    f32 scale;
    f32 var_f18;

    vdist_y = v2y - v1y;
    ddist_y = d1y - d2y;

    if (vdist_y < 0)
    {
        vneary = v2y;
        vfary = v1y;
    }
    else
    {
        vfary = v2y;
        vneary = v1y;
    }
    if (ddist_y > 0.0F)
    {
        if (((vfary + 0.001F) < d2y) || (d1y < (vneary - 0.001F)))
        {
            return FALSE;
        }
    }
    else if (((vfary + 0.001F) < d1y) || (d2y < (vneary - 0.001F)))
    {
        return FALSE;
    }
    ddist_x = d1x - d2x;
    vdist_x = v2x - v1x;

    if (vdist_x < 0)
    {
        vnearx = v2x;
        vfarx = v1x;
    }
    else
    {
        vfarx = v2x;
        vnearx = v1x;
    }
    if (ddist_x > 0.0F)
    {
        if ((vfarx < d2x) || (d1x < vnearx))
        {
            return FALSE;
        }
    }
    else if ((vfarx < d1x) || (d2x < vnearx))
    {
        return FALSE;
    }
    if ((d2y - (v1y + (((d2x - v1x) / vdist_x) * vdist_y))) >= (-0.001F))
    {
        temp_f12_2 = v1y + (((d1x - v1x) / vdist_x) * vdist_y);

        if ((d1y - temp_f12_2) > 0.001F)
        {
            if (((-0.001F) > (d1y - temp_f12_2)) && (d1x <= vfarx) && (vnearx <= d1x))
            {
                *dfx = d1x;
                *dfy = temp_f12_2;

                return TRUE;
            }
        }
        else
        {
            vddist_x = v1x - d1x;
            vddist_y = v1y - d1y;

            var_f18 = (ddist_y * vddist_x) - (ddist_x * vddist_y);
            scale = (vdist_y * ddist_x) - (vdist_x * ddist_y);
            vddiv = var_f18 / scale;

            if (vddiv < 0.0F)
            {
                if (vddiv < (-0.001F))
                {
                    return FALSE;
                }
                var_f18 = 0.0F;
            }
            else if (vddiv > 1.0F)
            {
                if (1.001F < vddiv)
                {
                    return FALSE;
                }
                var_f18 = scale;
            }
            vddistdiv = ((vdist_x * vddist_y) - (vdist_y * vddist_x)) / scale;

            if ((vddistdiv < (-0.001F)) || (1.001F < vddistdiv))
            {
                return FALSE;
            }
            vdscale = 1.0F / scale;

            *dfx = v1x + (var_f18 * vdist_x * vdscale);
            *dfy = v1y + (var_f18 * vdist_y * vdscale);

            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl2_800F5E90(Vec3f *position, Vec3f *translate, Vec3f *ga_last, s32 *stand_line_id, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i;
    f32 vdist1;
    f32 vdist2;
    f32 vpdist_x, vpdist_y;
    f32 vtdist_x, vtdist_y;
    f32 line_project_pos;
    f32 vedge_x;
    f32 vedge_y;
    s32 line_id, vertex_id;
    s32 temp_s0;
    s32 temp_s1;
    s32 vpos_x;
    s32 vpos_y;
    f32 spB0;
    f32 spAC;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_Ceil];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vedge_x = room_info->dynacoll_pos.x;
                vedge_y = room_info->dynacoll_pos.y;

                vpdist_x = position->x - vedge_x;
                vpdist_y = position->y - vedge_y;

                vtdist_x = translate->x - vedge_x;
                vtdist_y = translate->y - vedge_y;
            }
            else
            {
                vedge_x = vedge_y = 0.0F;

                vpdist_x = position->x;
                vpdist_y = position->y;

                vtdist_x = translate->x;
                vtdist_y = translate->y;
            }
            if (vpdist_y < vtdist_y)
            {
                vdist1 = vpdist_y - 0.001F;
                vdist2 = vtdist_y + 0.001F;
            }
            else
            {
                vdist1 = vtdist_y - 0.001F;
                vdist2 = vpdist_y + 0.001F;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next < vdist1)
                {
                    continue;
                }
                else if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev > vdist2)
                {
                    goto lbl_break; // Bruhhhhhhhhhhhhhhh
                }
                else
                {
                    vertex_id = gpMapVertexLinks[line_id].vertex1;

                    vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.x;
                    vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.y;

                    for (vertex_id = gpMapVertexLinks[line_id].vertex1; vertex_id < (gpMapVertexLinks[line_id].vertex1 + gpMapVertexLinks[line_id].vertex2) - 1; vertex_id++)
                    {
                        temp_s1 = vpos_x;
                        temp_s0 = vpos_y;

                        vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.x;
                        vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.y;

                        if (temp_s0 == vpos_y)
                        {
                            if (vtdist_y > vpdist_y)
                            {
                                if (mpCollision_CheckUDSurfaceFlat(temp_s1, temp_s0, vpos_x, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                                {
                                    if (line_project_pos <= ((spAC < vpdist_y) ? -(spAC - vpdist_y) : (spAC - vpdist_y))) continue;

                                    if (ga_last != NULL)
                                    {
                                        ga_last->x = spB0 + vedge_x;
                                        ga_last->y = spAC + vedge_y;
                                        ga_last->z = 0.0F;
                                    }
                                    if (stand_line_id != NULL)
                                    {
                                        *stand_line_id = line_id;
                                    }
                                    if (angle != NULL)
                                    {
                                        angle->x = angle->z = 0.0F;
                                        angle->y = -1.0F;
                                    }
                                    if (stand_coll_flags != NULL)
                                    {
                                        *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                                    }
                                    line_project_pos = (spAC < vpdist_y) ? -(spAC - vpdist_y) : (spAC - vpdist_y);
                                }
                            }
                        }
                        else if (mpCollision_CheckCeilSurfaceTilt(temp_s1, temp_s0, vpos_x, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                        {
                            if (line_project_pos <= ((spAC < vpdist_y) ? -(spAC - vpdist_y) : (spAC - vpdist_y))) continue;

                            if (ga_last != NULL)
                            {
                                ga_last->x = spB0 + vedge_x;
                                ga_last->y = spAC + vedge_y;
                                ga_last->z = 0.0F;
                            }
                            if (stand_line_id != NULL)
                            {
                                *stand_line_id = line_id;
                            }
                            if (angle != NULL)
                            {
                                mpCollision_GetUDAngle(angle, temp_s1, temp_s0, vpos_x, vpos_y, -1);
                            }
                            if (stand_coll_flags != NULL)
                            {
                                *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                            }
                            line_project_pos = (spAC < vpdist_y) ? -(spAC - vpdist_y) : (spAC - vpdist_y);
                        }
                    }
                }
            }
        lbl_break: // BRUHHHHHHHHHHHHHHHHH
            continue;
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

bool32 func_ovl2_800F64D4(Vec3f *position, Vec3f *translate, Vec3f *ga_last, s32 *stand_line_id, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i;
    f32 vdist1;
    f32 vdist2;
    f32 vpdist_x, vpdist_y;
    f32 vtdist_x, vtdist_y;
    f32 line_project_pos;
    f32 vedge_y;
    f32 unkpos_y;
    f32 vedge_x;
    s32 line_id, vertex_id;
    s32 temp_s0;
    s32 temp_s1;
    s32 vpos_x;
    s32 vpos_y;
    f32 spB0;
    f32 spAC;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_Ceil];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vedge_x = room_info->dynacoll_pos.x;
                vedge_y = room_info->dynacoll_pos.y;

                unkpos_y = gpMapRoomVectors[line_info->room_id].y;

                vpdist_x = (position->x - vedge_x) + gpMapRoomVectors[line_info->room_id].x;
                vpdist_y = (position->y - vedge_y) + unkpos_y;

                vtdist_x = translate->x - vedge_x;
                vtdist_y = translate->y - vedge_y;
            }
            else
            {
                unkpos_y = 0.0F;
                vedge_x = vedge_y = 0.0F;

                vpdist_x = position->x;
                vpdist_y = position->y;

                vtdist_x = translate->x;
                vtdist_y = translate->y;
            }
            if (vpdist_y < vtdist_y)
            {
                vdist1 = vpdist_y - 0.001F;
                vdist2 = vtdist_y + 0.001F;
            }
            else
            {
                vdist1 = vtdist_y - 0.001F;
                vdist2 = vpdist_y + 0.001F;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next < vdist1)
                {
                    continue;
                }
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev > vdist2)
                {
                    goto lbl_break; // Bruhhhhhhhhhhhhhhh
                }
                else
                {
                    vertex_id = gpMapVertexLinks[line_id].vertex1;

                    vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.x;
                    vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.y;

                    for (vertex_id = gpMapVertexLinks[line_id].vertex1; vertex_id < (gpMapVertexLinks[line_id].vertex1 + gpMapVertexLinks[line_id].vertex2) - 1; vertex_id++)
                    {
                        temp_s1 = vpos_x;
                        temp_s0 = vpos_y;

                        vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.x;
                        vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.y;

                        if (temp_s0 == vpos_y)
                        {
                            if (vtdist_y > vpdist_y)
                            {
                                if (mpCollision_CheckUDSurfaceFlat(temp_s1, temp_s0, vpos_x, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                                {
                                    if (line_project_pos <= ((spAC < (vpdist_y - unkpos_y)) ? -(spAC - (vpdist_y - unkpos_y)) : (spAC - (vpdist_y - unkpos_y)))) continue;

                                    if (ga_last != NULL)
                                    {
                                        ga_last->x = spB0 + vedge_x;
                                        ga_last->y = spAC + vedge_y;
                                        ga_last->z = 0.0F;
                                    }
                                    if (stand_line_id != NULL)
                                    {
                                        *stand_line_id = line_id;
                                    }
                                    if (angle != NULL)
                                    {
                                        angle->x = angle->z = 0.0F;
                                        angle->y = -1.0F;
                                    }
                                    if (stand_coll_flags != NULL)
                                    {
                                        *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                                    }
                                    line_project_pos = (spAC < (vpdist_y - unkpos_y)) ? -(spAC - (vpdist_y - unkpos_y)) : (spAC - (vpdist_y - unkpos_y));
                                }
                            }
                        }
                        else if (mpCollision_CheckCeilSurfaceTilt(temp_s1, temp_s0, vpos_x, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                        {
                            if (line_project_pos <= ((spAC < (vpdist_y - unkpos_y)) ? -(spAC - (vpdist_y - unkpos_y)) : (spAC - (vpdist_y - unkpos_y)))) continue;

                            if (ga_last != NULL)
                            {
                                ga_last->x = spB0 + vedge_x;
                                ga_last->y = spAC + vedge_y;
                                ga_last->z = 0.0F;
                            }
                            if (stand_line_id != NULL)
                            {
                                *stand_line_id = line_id;
                            }
                            if (angle != NULL)
                            {
                                mpCollision_GetUDAngle(angle, temp_s1, temp_s0, vpos_x, vpos_y, -1);
                            }
                            if (stand_coll_flags != NULL)
                            {
                                *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                            }
                            line_project_pos = (spAC < (vpdist_y - unkpos_y)) ? -(spAC - (vpdist_y - unkpos_y)) : (spAC - (vpdist_y - unkpos_y));
                        }
                    }
                }
            }
        lbl_break: // BRUHHHHHHHHHHHHHHHHH
            continue;
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

bool32 func_ovl2_800F6B58(Vec3f *position, Vec3f *translate, Vec3f *ga_last, s32 *stand_line_id, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i;
    f32 vdist1;
    f32 vdist2;
    f32 vpdist_x, vpdist_y;
    f32 vtdist_x, vtdist_y;
    f32 line_project_pos;
    f32 vedge_x;
    f32 vedge_y;
    s32 line_id, vertex_id;
    s32 temp_s0;
    s32 temp_s1;
    s32 vpos_x;
    s32 vpos_y;
    f32 spB0;
    f32 spAC;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_RWall];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vedge_y = room_info->dynacoll_pos.x;
                vedge_x = room_info->dynacoll_pos.y;

                vpdist_x = position->x - vedge_y;
                vpdist_y = position->y - vedge_x;

                vtdist_x = translate->x - vedge_y;
                vtdist_y = translate->y - vedge_x;
            }
            else
            {
                vedge_y = vedge_x = 0.0F;

                vpdist_x = position->x;
                vpdist_y = position->y;

                vtdist_x = translate->x;
                vtdist_y = translate->y;
            }
            if (vpdist_x < vtdist_x)
            {
                vdist1 = vpdist_x - 0.001F;
                vdist2 = vtdist_x + 0.001F;
            }
            else
            {
                vdist1 = vtdist_x - 0.001F;
                vdist2 = vpdist_x + 0.001F;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev > vdist2)
                {
                    continue;
                }
                else if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next < vdist1)
                {
                    goto lbl_break; // Bruhhhhhhhhhhhhhhh
                }
                else
                {
                    vertex_id = gpMapVertexLinks[line_id].vertex1;

                    vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.x;
                    vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.y;

                    for (vertex_id = gpMapVertexLinks[line_id].vertex1; vertex_id < (gpMapVertexLinks[line_id].vertex1 + gpMapVertexLinks[line_id].vertex2) - 1; vertex_id++)
                    {
                        temp_s0 = vpos_x;
                        temp_s1 = vpos_y;

                        vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.x;
                        vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.y;

                        if (temp_s0 == vpos_x)
                        {
                            if (vtdist_x < vpdist_x)
                            {
                                if (mpCollision_CheckLRSurfaceFlat(temp_s0, temp_s1, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                                {
                                    if (line_project_pos <= ((spB0 < vpdist_x) ? -(spB0 - vpdist_x) : (spB0 - vpdist_x))) continue;

                                    if (ga_last != NULL)
                                    {
                                        ga_last->x = spB0 + vedge_y;
                                        ga_last->y = spAC + vedge_x;
                                        ga_last->z = 0.0F;
                                    }
                                    if (stand_line_id != NULL)
                                    {
                                        *stand_line_id = line_id;
                                    }
                                    if (angle != NULL)
                                    {
                                        angle->y = angle->z = 0.0F;
                                        angle->x = 1.0F;
                                    }
                                    if (stand_coll_flags != NULL)
                                    {
                                        *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                                    }
                                    line_project_pos = (spB0 < vpdist_x) ? -(spB0 - vpdist_x) : (spB0 - vpdist_x);
                                }
                            }
                        }
                        else if (mpCollision_CheckRWallSurfaceTilt(temp_s0, temp_s1, vpos_x, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                        {
                            if (line_project_pos <= ((spB0 < vpdist_x) ? -(spB0 - vpdist_x) : (spB0 - vpdist_x))) continue;

                            if (ga_last != NULL)
                            {
                                ga_last->x = spB0 + vedge_y;
                                ga_last->y = spAC + vedge_x;
                                ga_last->z = 0.0F;
                            }
                            if (stand_line_id != NULL)
                            {
                                *stand_line_id = line_id;
                            }
                            if (angle != NULL)
                            {
                                mpCollision_GetLRAngle(angle, temp_s0, temp_s1, vpos_x, vpos_y, 1);
                            }
                            if (stand_coll_flags != NULL)
                            {
                                *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                            }
                            line_project_pos = (spB0 < vpdist_x) ? -(spB0 - vpdist_x) : (spB0 - vpdist_x);
                        }
                    }
                }
            }
        lbl_break: // BRUHHHHHHHHHHHHHHHHH
            continue;
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

// 0x800F7270
bool32 mpCollision_CheckRWallSurfaceTilt(s32 v1x, s32 v1y, s32 v2x, s32 v2y, f32 d1x, f32 d1y, f32 d2x, f32 d2y, f32 *dfx, f32 *dfy)
{
    s32 vfarx;
    s32 vnearx;
    f32 ddist_x;
    f32 ddist_y;
    s32 vfary;
    s32 vneary;
    s32 vdist_x;
    s32 vdist_y;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 vddiv;
    f32 vddist_x;
    f32 vddist_y;
    f32 vddistdiv;
    f32 vdscale;
    f32 scale;
    f32 var_f18;

    vdist_x = v2x - v1x;
    ddist_x = d1x - d2x;

    if (vdist_x < 0)
    {
        vnearx = v2x;
        vfarx = v1x;
    }
    else
    {
        vfarx = v2x;
        vnearx = v1x;
    }
    if (ddist_x > 0.0F)
    {
        if (((vfarx + 0.001F) < d2x) || (d1x < (vnearx - 0.001F)))
        {
            return FALSE;
        }
    }
    else if (((vfarx + 0.001F) < d1x) || (d2x < (vnearx - 0.001F)))
    {
        return FALSE;
    }
    ddist_y = d1y - d2y;
    vdist_y = v2y - v1y;

    if (vdist_y < 0)
    {
        vneary = v2y;
        vfary = v1y;
    }
    else
    {
        vfary = v2y;
        vneary = v1y;
    }
    if (ddist_y > 0.0F)
    {
        if ((vfary < d2y) || (d1y < vneary))
        {
            return FALSE;
        }
    }
    else if ((vfary < d1y) || (d2y < vneary))
    {
        return FALSE;
    }
    if ((d2x - (v1x + (((d2y - v1y) / (v2y - v1y)) * vdist_x))) <= (-0.001F))
    {
        temp_f12_2 = v1x + (((d1y - v1y) / vdist_y) * vdist_x);

        if ((d1x - temp_f12_2) < 0.001F)
        {
            if ((((-0.001F) < (d1x - temp_f12_2)) && (d1y <= vfary)) && (vneary <= d1y))
            {
                *dfx = temp_f12_2;
                *dfy = d1y;

                return TRUE;
            }
        }
        else
        {
            vddist_x = v1x - d1x;
            vddist_y = v1y - d1y;

            var_f18 = (ddist_y * vddist_x) - (ddist_x * vddist_y);
            scale = (vdist_y * ddist_x) - (vdist_x * ddist_y);

            vddiv = var_f18 / scale;

            if (vddiv < 0.0F)
            {
                if (vddiv < (-0.001F))
                {
                    return FALSE;
                }
                var_f18 = 0.0F;
            }
            else if (vddiv > 1.0F)
            {
                if (1.001F < vddiv)
                {
                    return FALSE;
                }
                var_f18 = scale;
            }
            vddistdiv = ((vdist_x * vddist_y) - (vdist_y * vddist_x)) / scale;

            if ((vddistdiv < (-0.001F)) || (1.001F < vddistdiv))
            {
                return FALSE;
            }
            vdscale = 1.0F / scale;

            *dfx = v1x + ((var_f18 * vdist_x) * vdscale);
            *dfy = v1y + ((var_f18 * vdist_y) * vdscale);

            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl2_800F769C(Vec3f *position, Vec3f *translate, Vec3f *ga_last, s32 *stand_line_id, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i;
    f32 vdist1;
    f32 vdist2;
    f32 vpdist_x, vpdist_y;
    f32 vtdist_x, vtdist_y;
    f32 line_project_pos;
    f32 vedge_x;
    f32 unkpos_x;
    f32 vedge_y;
    s32 line_id, vertex_id;
    s32 temp_s0;
    s32 temp_s1;
    s32 vpos_x;
    s32 vpos_y;
    f32 spB0;
    f32 spAC;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_RWall];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vedge_y = room_info->dynacoll_pos.x;
                vedge_x = room_info->dynacoll_pos.y;

                unkpos_x = gpMapRoomVectors[line_info->room_id].x;

                vpdist_x = (position->x - vedge_y) + unkpos_x;
                vpdist_y = (position->y - vedge_x) + gpMapRoomVectors[line_info->room_id].y;

                vtdist_x = translate->x - vedge_y;
                vtdist_y = translate->y - vedge_x;
            }
            else
            {
                unkpos_x = 0.0F;
                vedge_y = vedge_x = 0.0F;

                vpdist_x = position->x;
                vpdist_y = position->y;

                vtdist_x = translate->x;
                vtdist_y = translate->y;
            }
            if (vpdist_x < vtdist_x)
            {
                vdist1 = vpdist_x - 0.001F;
                vdist2 = vtdist_x + 0.001F;
            }
            else
            {
                vdist1 = vtdist_x - 0.001F;
                vdist2 = vpdist_x + 0.001F;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev > vdist2)
                {
                    continue;
                }
                else if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next < vdist1)
                {
                    goto lbl_break; // Bruhhhhhhhhhhhhhhh
                }
                else
                {
                    vertex_id = gpMapVertexLinks[line_id].vertex1;

                    vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.x;
                    vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.y;

                    for (vertex_id = gpMapVertexLinks[line_id].vertex1; vertex_id < (gpMapVertexLinks[line_id].vertex1 + gpMapVertexLinks[line_id].vertex2) - 1; vertex_id++)
                    {
                        temp_s0 = vpos_x;
                        temp_s1 = vpos_y;

                        vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.x;
                        vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.y;

                        if (temp_s0 == vpos_x)
                        {
                            if (vtdist_x < vpdist_x)
                            {
                                if (mpCollision_CheckLRSurfaceFlat(temp_s0, temp_s1, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                                {
                                    if (line_project_pos <= ((spB0 < (vpdist_x - unkpos_x)) ? -(spB0 - (vpdist_x - unkpos_x)) : (spB0 - (vpdist_x - unkpos_x)))) continue;

                                    if (ga_last != NULL)
                                    {
                                        ga_last->x = spB0 + vedge_y;
                                        ga_last->y = spAC + vedge_x;
                                        ga_last->z = 0.0F;
                                    }
                                    if (stand_line_id != NULL)
                                    {
                                        *stand_line_id = line_id;
                                    }
                                    if (angle != NULL)
                                    {
                                        angle->y = angle->z = 0.0F;
                                        angle->x = 1.0F;
                                    }
                                    if (stand_coll_flags != NULL)
                                    {
                                        *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                                    }
                                    line_project_pos = (spB0 < (vpdist_x - unkpos_x)) ? -(spB0 - (vpdist_x - unkpos_x)) : (spB0 - (vpdist_x - unkpos_x));
                                }
                            }
                        }
                        else if (mpCollision_CheckRWallSurfaceTilt(temp_s0, temp_s1, vpos_x, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                        {
                            if (line_project_pos <= ((spB0 < (vpdist_x - unkpos_x)) ? -(spB0 - (vpdist_x - unkpos_x)) : (spB0 - (vpdist_x - unkpos_x)))) continue;

                            if (ga_last != NULL)
                            {
                                ga_last->x = spB0 + vedge_y;
                                ga_last->y = spAC + vedge_x;
                                ga_last->z = 0.0F;
                            }
                            if (stand_line_id != NULL)
                            {
                                *stand_line_id = line_id;
                            }
                            if (angle != NULL)
                            {
                                mpCollision_GetLRAngle(angle, temp_s0, temp_s1, vpos_x, vpos_y, 1);
                            }
                            if (stand_coll_flags != NULL)
                            {
                                *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                            }
                            line_project_pos = (spB0 < (vpdist_x - unkpos_x)) ? -(spB0 - (vpdist_x - unkpos_x)) : (spB0 - (vpdist_x - unkpos_x));
                        }
                    }
                }
            }
        lbl_break: // BRUHHHHHHHHHHHHHHHHH
            continue;
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

bool32 mpCollision_CheckLRSurfaceFlat(s32 v1x, s32 v1y, s32 vpos_x, f32 vpdist_x, f32 vpdist_y, f32 vtdist_x, f32 vtdist_y, f32 *arg7, f32 *arg8)
{
    s32 unused[2];
    f32 temp_f18;
    s32 vnear;
    s32 vfar;
    f32 ddist_y;
    s32 vdist_x = vpos_x - v1y;
    f32 ddist_x = vpdist_x - vtdist_x;
    f32 vddist_x = v1x - vpdist_x;

    if (ddist_x > 0.0F)
    {
        if (((v1x - 0.001F) > vpdist_x) || (vtdist_x >= v1x))
        {
            return FALSE;
        }
    }
    else if (((v1x + 0.001F) < vpdist_x) || (vtdist_x <= v1x))
    {
        return FALSE;
    }
    ddist_y = vpdist_y - vtdist_y;

    if (vdist_x < 0)
    {
        vnear = vpos_x;
        vfar = v1y;
    }
    else
    {
        vfar = vpos_x;
        vnear = v1y;
    }

    if (ddist_y > 0.0F)
    {
        if ((vfar < vtdist_y) || (vpdist_y < vnear))
        {
            return FALSE;
        }
    }
    else if ((vfar < vpdist_y) || (vtdist_y < vnear))
    {
        return FALSE;
    }
    temp_f18 = ((vddist_x / ddist_x) * ddist_y) + vpdist_y;

    if ((temp_f18 < vnear) || (temp_f18 > vfar))
    {
        return FALSE;
    }

    *arg7 = v1x;
    *arg8 = temp_f18;

    return TRUE;
}

bool32 func_ovl2_800F7F00(Vec3f *position, Vec3f *translate, Vec3f *ga_last, s32 *stand_line_id, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i;
    f32 vdist1;
    f32 vdist2;
    f32 vpdist_x, vpdist_y;
    f32 vtdist_x, vtdist_y;
    f32 line_project_pos;
    f32 vedge_x;
    f32 vedge_y;
    s32 line_id, vertex_id;
    s32 temp_s0;
    s32 temp_s1;
    s32 vpos_x;
    s32 vpos_y;
    f32 spB0;
    f32 spAC;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_LWall];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vedge_y = room_info->dynacoll_pos.x;
                vedge_x = room_info->dynacoll_pos.y;

                vpdist_x = position->x - vedge_y;
                vpdist_y = position->y - vedge_x;

                vtdist_x = translate->x - vedge_y;
                vtdist_y = translate->y - vedge_x;
            }
            else
            {
                vedge_y = vedge_x = 0.0F;

                vpdist_x = position->x;
                vpdist_y = position->y;

                vtdist_x = translate->x;
                vtdist_y = translate->y;
            }
            if (vpdist_x < vtdist_x)
            {
                vdist1 = vpdist_x - 0.001F;
                vdist2 = vtdist_x + 0.001F;
            }
            else
            {
                vdist1 = vtdist_x - 0.001F;
                vdist2 = vpdist_x + 0.001F;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next < vdist1)
                {
                    continue;
                }
                else if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev > vdist2)
                {
                    goto lbl_break; // Bruhhhhhhhhhhhhhhh
                }
                else
                {
                    vertex_id = gpMapVertexLinks[line_id].vertex1;

                    vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.x;
                    vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.y;

                    for (vertex_id = gpMapVertexLinks[line_id].vertex1; vertex_id < (gpMapVertexLinks[line_id].vertex1 + gpMapVertexLinks[line_id].vertex2) - 1; vertex_id++)
                    {
                        temp_s0 = vpos_x;
                        temp_s1 = vpos_y;

                        vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.x;
                        vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.y;

                        if (temp_s0 == vpos_x)
                        {
                            if (vtdist_x > vpdist_x)
                            {
                                if (mpCollision_CheckLRSurfaceFlat(temp_s0, temp_s1, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                                {
                                    if (line_project_pos <= ((spB0 < vpdist_x) ? -(spB0 - vpdist_x) : (spB0 - vpdist_x))) continue;

                                    if (ga_last != NULL)
                                    {
                                        ga_last->x = spB0 + vedge_y;
                                        ga_last->y = spAC + vedge_x;
                                        ga_last->z = 0.0F;
                                    }
                                    if (stand_line_id != NULL)
                                    {
                                        *stand_line_id = line_id;
                                    }
                                    if (angle != NULL)
                                    {
                                        angle->y = angle->z = 0.0F;
                                        angle->x = -1.0F;
                                    }
                                    if (stand_coll_flags != NULL)
                                    {
                                        *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                                    }
                                    line_project_pos = (spB0 < vpdist_x) ? -(spB0 - vpdist_x) : (spB0 - vpdist_x);
                                }
                            }
                        }
                        else if (mpCollision_CheckLWallSurfaceTilt(temp_s0, temp_s1, vpos_x, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                        {
                            if (line_project_pos <= ((spB0 < vpdist_x) ? -(spB0 - vpdist_x) : (spB0 - vpdist_x))) continue;

                            if (ga_last != NULL)
                            {
                                ga_last->x = spB0 + vedge_y;
                                ga_last->y = spAC + vedge_x;
                                ga_last->z = 0.0F;
                            }
                            if (stand_line_id != NULL)
                            {
                                *stand_line_id = line_id;
                            }
                            if (angle != NULL)
                            {
                                mpCollision_GetLRAngle(angle, temp_s0, temp_s1, vpos_x, vpos_y, -1);
                            }
                            if (stand_coll_flags != NULL)
                            {
                                *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                            }
                            line_project_pos = (spB0 < vpdist_x) ? -(spB0 - vpdist_x) : (spB0 - vpdist_x);
                        }
                    }
                }
            }
        lbl_break: // BRUHHHHHHHHHHHHHHHHH
            continue;
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

bool32 mpCollision_CheckLWallSurfaceTilt(s32 v1x, s32 v1y, s32 v2x, s32 v2y, f32 d1x, f32 d1y, f32 d2x, f32 d2y, f32 *dfx, f32 *dfy)
{
    s32 vfarx;
    s32 vnearx;
    f32 ddist_x;
    f32 ddist_y;
    s32 vfary;
    s32 vneary;
    s32 vdist_x;
    s32 vdist_y;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 vddiv;
    f32 vddist_x;
    f32 vddist_y;
    f32 vddistdiv;
    f32 vdscale;
    f32 scale;
    f32 var_f18;

    vdist_x = v2x - v1x;
    ddist_x = d1x - d2x;

    if (vdist_x < 0)
    {
        vnearx = v2x;
        vfarx = v1x;
    }
    else
    {
        vfarx = v2x;
        vnearx = v1x;
    }
    if (ddist_x > 0.0F)
    {
        if (((vfarx + 0.001F) < d2x) || (d1x < (vnearx - 0.001F)))
        {
            return FALSE;
        }
    }
    else if (((vfarx + 0.001F) < d1x) || (d2x < (vnearx - 0.001F)))
    {
        return FALSE;
    }
    ddist_y = d1y - d2y;
    vdist_y = v2y - v1y;

    if (vdist_y < 0)
    {
        vneary = v2y;
        vfary = v1y;
    }
    else
    {
        vfary = v2y;
        vneary = v1y;
    }
    if (ddist_y > 0.0F)
    {
        if ((vfary < d2y) || (d1y < vneary))
        {
            return FALSE;
        }
    }
    else if ((vfary < d1y) || (d2y < vneary))
    {
        return FALSE;
    }
    if ((d2x - (v1x + (((d2y - v1y) / (v2y - v1y)) * vdist_x))) >= (-0.001F))
    {
        temp_f12_2 = v1x + (((d1y - v1y) / vdist_y) * vdist_x);

        if ((d1x - temp_f12_2) > 0.001F)
        {
            if ((((-0.001F) > (d1x - temp_f12_2)) && (d1y <= vfary)) && (vneary <= d1y))
            {
                *dfx = temp_f12_2;
                *dfy = d1y;

                return TRUE;
            }
        }
        else
        {
            vddist_x = v1x - d1x;
            vddist_y = v1y - d1y;

            var_f18 = (ddist_y * vddist_x) - (ddist_x * vddist_y);
            scale = (vdist_y * ddist_x) - (vdist_x * ddist_y);

            vddiv = var_f18 / scale;

            if (vddiv < 0.0F)
            {
                if (vddiv < (-0.001F))
                {
                    return FALSE;
                }
                var_f18 = 0.0F;
            }
            else if (vddiv > 1.0F)
            {
                if (1.001F < vddiv)
                {
                    return FALSE;
                }
                var_f18 = scale;
            }
            vddistdiv = ((vdist_x * vddist_y) - (vdist_y * vddist_x)) / scale;

            if ((vddistdiv < (-0.001F)) || (1.001F < vddistdiv))
            {
                return FALSE;
            }
            vdscale = 1.0F / scale;

            *dfx = v1x + ((var_f18 * vdist_x) * vdscale);
            *dfy = v1y + ((var_f18 * vdist_y) * vdscale);

            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl2_800F8974(Vec3f *position, Vec3f *translate, Vec3f *ga_last, s32 *stand_line_id, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i;
    f32 vdist1;
    f32 vdist2;
    f32 vpdist_x, vpdist_y;
    f32 vtdist_x, vtdist_y;
    f32 line_project_pos;
    f32 vedge_x;
    f32 unkpos_x;
    f32 vedge_y;
    s32 line_id, vertex_id;
    s32 temp_s0;
    s32 temp_s1;
    s32 vpos_x;
    s32 vpos_y;
    f32 spB0;
    f32 spAC;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_LWall];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vedge_y = room_info->dynacoll_pos.x;
                vedge_x = room_info->dynacoll_pos.y;

                unkpos_x = gpMapRoomVectors[line_info->room_id].x;

                vpdist_x = (position->x - vedge_y) + unkpos_x;
                vpdist_y = (position->y - vedge_x) + gpMapRoomVectors[line_info->room_id].y;

                vtdist_x = translate->x - vedge_y;
                vtdist_y = translate->y - vedge_x;
            }
            else
            {
                unkpos_x = 0.0F;
                vedge_y = vedge_x = 0.0F;

                vpdist_x = position->x;
                vpdist_y = position->y;

                vtdist_x = translate->x;
                vtdist_y = translate->y;
            }
            if (vpdist_x < vtdist_x)
            {
                vdist1 = vpdist_x - 0.001F;
                vdist2 = vtdist_x + 0.001F;
            }
            else
            {
                vdist1 = vtdist_x - 0.001F;
                vdist2 = vpdist_x + 0.001F;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next < vdist1)
                {
                    continue;
                }
                else if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev > vdist2)
                {
                    goto lbl_break; // Bruhhhhhhhhhhhhhhh
                }
                else
                {
                    vertex_id = gpMapVertexLinks[line_id].vertex1;

                    vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.x;
                    vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].pos.y;

                    for (vertex_id = gpMapVertexLinks[line_id].vertex1; vertex_id < (gpMapVertexLinks[line_id].vertex1 + gpMapVertexLinks[line_id].vertex2) - 1; vertex_id++)
                    {
                        temp_s0 = vpos_x;
                        temp_s1 = vpos_y;

                        vpos_x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.x;
                        vpos_y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id + 1]].pos.y;

                        if (temp_s0 == vpos_x)
                        {
                            if (vtdist_x > vpdist_x)
                            {
                                if (mpCollision_CheckLRSurfaceFlat(temp_s0, temp_s1, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                                {
                                    if (line_project_pos <= ((spB0 < (vpdist_x - unkpos_x)) ? -(spB0 - (vpdist_x - unkpos_x)) : (spB0 - (vpdist_x - unkpos_x)))) continue;

                                    if (ga_last != NULL)
                                    {
                                        ga_last->x = spB0 + vedge_y;
                                        ga_last->y = spAC + vedge_x;
                                        ga_last->z = 0.0F;
                                    }
                                    if (stand_line_id != NULL)
                                    {
                                        *stand_line_id = line_id;
                                    }
                                    if (angle != NULL)
                                    {
                                        angle->y = angle->z = 0.0F;
                                        angle->x = -1.0F;
                                    }
                                    if (stand_coll_flags != NULL)
                                    {
                                        *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                                    }
                                    line_project_pos = (spB0 < (vpdist_x - unkpos_x)) ? -(spB0 - (vpdist_x - unkpos_x)) : (spB0 - (vpdist_x - unkpos_x));
                                }
                            }
                        }
                        else if (mpCollision_CheckLWallSurfaceTilt(temp_s0, temp_s1, vpos_x, vpos_y, vpdist_x, vpdist_y, vtdist_x, vtdist_y, &spB0, &spAC) == TRUE)
                        {
                            if (line_project_pos <= ((spB0 < (vpdist_x - unkpos_x)) ? -(spB0 - (vpdist_x - unkpos_x)) : (spB0 - (vpdist_x - unkpos_x)))) continue;

                            if (ga_last != NULL)
                            {
                                ga_last->x = spB0 + vedge_y;
                                ga_last->y = spAC + vedge_x;
                                ga_last->z = 0.0F;
                            }
                            if (stand_line_id != NULL)
                            {
                                *stand_line_id = line_id;
                            }
                            if (angle != NULL)
                            {
                                mpCollision_GetLRAngle(angle, temp_s0, temp_s1, vpos_x, vpos_y, -1);
                            }
                            if (stand_coll_flags != NULL)
                            {
                                *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id]].vertex_flags;
                            }
                            line_project_pos = (spB0 < (vpdist_x - unkpos_x)) ? -(spB0 - (vpdist_x - unkpos_x)) : (spB0 - (vpdist_x - unkpos_x));
                        }
                    }
                }
            }
        lbl_break: // BRUHHHHHHHHHHHHHHHHH
            continue;
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

bool32 func_ovl2_800F8FFC(Vec3f *position)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    s32 i, j;
    mpRoomInfo *room_info;
    f32 vpdist_x, vpdist_y;
    s32 line_id;

    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_Ground];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vpdist_x = (position->x - room_info->dynacoll_pos.x);
                vpdist_y = (position->y - room_info->dynacoll_pos.y) + 0.001F;
            }
            else
            {
                vpdist_x = position->x;
                vpdist_y = position->y + 0.001F;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev <= vpdist_y)
                {
                    s32 vertex_id1 = gpMapVertexLinks->vertex_links[line_id].vertex1;
                    s32 vertex_id2 = gpMapVertexLinks->vertex_links[line_id].vertex2 - 1;

                    s32 x1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.x;
                    s32 x2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + vertex_id2]].pos.x;

                    if ((x1 <= vpdist_x && x2 >= vpdist_x) || (x2 <= vpdist_x && x1 >= vpdist_x))
                    {
                        if (vertex_id2 != 1)
                        {
                            for (j = 0; j < vertex_id2; j++, vertex_id1++)
                            {
                                x1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.x;
                                x2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.x;

                                if (func_ovl2_800F39F0(vpdist_x, x1, gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.y, x2, gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.y) < vpdist_y)
                                {
                                    return TRUE;
                                }
                            }
                        }
                        else if (func_ovl2_800F39F0(vpdist_x, x1, gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.y, x2, gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.y) < vpdist_y)
                        {
                            return TRUE;
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}

bool32 func_ovl2_800F9348(Vec3f *position, s32 *project_line_id, f32 *ga_dist, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i, j;
    f32 vpdist_x, vpdist_y;
    s32 line_id;
    f32 line_project_pos;
    f32 fpos;
    f32 gdist;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_Ground];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vpdist_x = (position->x - room_info->dynacoll_pos.x);
                vpdist_y = (position->y - room_info->dynacoll_pos.y);
            }
            else
            {
                vpdist_x = position->x;
                vpdist_y = position->y;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev <= vpdist_y)
                {
                    s32 vertex_id1 = gpMapVertexLinks[line_id].vertex1;
                    s32 vertex_id2 = gpMapVertexLinks[line_id].vertex2 - 1;

                    s32 x1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.x;
                    s32 x2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + vertex_id2]].pos.x;
                    s32 y1;
                    s32 y2;

                    if ((x1 <= vpdist_x && x2 >= vpdist_x) || (x2 <= vpdist_x && x1 >= vpdist_x))
                    {
                        if (vertex_id2 != 1)
                        {
                            for (j = 0; j < vertex_id2; j++, vertex_id1++)
                            {
                                x1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.x;
                                x2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.x;

                                if ((x1 <= vpdist_x && x2 >= vpdist_x) || (x2 <= vpdist_x && x1 >= vpdist_x))
                                {
                                    break;
                                }
                            }
                        }
                        y1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.y;
                        y2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.y;

                        fpos = func_ovl2_800F39F0(vpdist_x, x1, y1, x2, y2);

                        gdist = fpos - vpdist_y;

                        if (fpos <= vpdist_y)
                        {
                            if (ABSF(gdist) < line_project_pos)
                            {
                                if (project_line_id != NULL)
                                {
                                    *project_line_id = line_id;
                                }
                                if (ga_dist != NULL)
                                {
                                    *ga_dist = gdist;
                                }
                                if (stand_coll_flags != NULL)
                                {
                                    *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].vertex_flags;
                                }
                                if (angle != NULL)
                                {
                                    mpCollision_GetUDAngle(angle, x1, y1, x2, y2, 1);
                                }
                                line_project_pos = ABSF(gdist);
                            }
                        }
                    }
                }
            }
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

// Unused?
bool32 func_ovl2_800F97BC(Vec3f *position, s32 *project_line_id, f32 *ga_dist, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i, j;
    f32 vpdist_x, vpdist_y;
    s32 line_id;
    f32 line_project_pos;
    f32 fpos;
    f32 gdist;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_Ceil];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vpdist_x = (position->x - room_info->dynacoll_pos.x);
                vpdist_y = (position->y - room_info->dynacoll_pos.y);
            }
            else
            {
                vpdist_x = position->x;
                vpdist_y = position->y;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next >= vpdist_y)
                {
                    s32 vertex_id1 = gpMapVertexLinks[line_id].vertex1;
                    s32 vertex_id2 = gpMapVertexLinks[line_id].vertex2 - 1;

                    s32 x1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.x;
                    s32 x2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + vertex_id2]].pos.x;
                    s32 y1;
                    s32 y2;

                    if ((x1 <= vpdist_x && x2 >= vpdist_x) || (x2 <= vpdist_x && x1 >= vpdist_x))
                    {
                        if (vertex_id2 != 1)
                        {
                            for (j = 0; j < vertex_id2; j++, vertex_id1++)
                            {
                                x1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.x;
                                x2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.x;

                                if ((x1 <= vpdist_x && x2 >= vpdist_x) || (x2 <= vpdist_x && x1 >= vpdist_x))
                                {
                                    break;
                                }
                            }
                        }
                        y1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.y;
                        y2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.y;

                        fpos = func_ovl2_800F39F0(vpdist_x, x1, y1, x2, y2);

                        gdist = fpos - vpdist_y;

                        if (fpos >= vpdist_y)
                        {
                            if (ABSF(gdist) < line_project_pos)
                            {
                                if (project_line_id != NULL)
                                {
                                    *project_line_id = line_id;
                                }
                                if (ga_dist != NULL)
                                {
                                    *ga_dist = gdist;
                                }
                                if (stand_coll_flags != NULL)
                                {
                                    *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].vertex_flags;
                                }
                                if (angle != NULL)
                                {
                                    mpCollision_GetUDAngle(angle, x1, y1, x2, y2, -1);
                                }
                                line_project_pos = ABSF(gdist);
                            }
                        }
                    }
                }
            }
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

bool32 func_ovl2_800F9C30(Vec3f *position, s32 *project_line_id, f32 *ga_dist, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i, j;
    f32 vpdist_x, vpdist_y;
    s32 line_id;
    f32 line_project_pos;
    f32 fpos;
    f32 gdist;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_RWall];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vpdist_x = (position->x - room_info->dynacoll_pos.x);
                vpdist_y = (position->y - room_info->dynacoll_pos.y);
            }
            else
            {
                vpdist_x = position->x;
                vpdist_y = position->y;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_prev <= vpdist_x)
                {
                    s32 vertex_id1 = gpMapVertexLinks[line_id].vertex1;
                    s32 vertex_id2 = gpMapVertexLinks[line_id].vertex2 - 1;

                    s32 y1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.y;
                    s32 y2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + vertex_id2]].pos.y;
                    s32 x1;
                    s32 x2;

                    if ((y1 <= vpdist_y && y2 >= vpdist_y) || (y2 <= vpdist_y && y1 >= vpdist_y))
                    {
                        if (vertex_id2 != 1)
                        {
                            for (j = 0; j < vertex_id2; j++, vertex_id1++)
                            {
                                y1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.y;
                                y2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.y;

                                if ((y1 <= vpdist_y && y2 >= vpdist_y) || (y2 <= vpdist_y && y1 >= vpdist_y))
                                {
                                    break;
                                }
                            }
                        }
                        x1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.x;
                        x2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.x;

                        fpos = func_ovl2_800F3A34(vpdist_y, x1, y1, x2, y2);

                        gdist = fpos - vpdist_x;

                        if (fpos <= vpdist_x)
                        {
                            if (ABSF(gdist) < line_project_pos)
                            {
                                if (project_line_id != NULL)
                                {
                                    *project_line_id = line_id;
                                }
                                if (ga_dist != NULL)
                                {
                                    *ga_dist = gdist;
                                }
                                if (stand_coll_flags != NULL)
                                {
                                    *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].vertex_flags;
                                }
                                if (angle != NULL)
                                {
                                    mpCollision_GetUDAngle(angle, x1, y1, x2, y2, 1);
                                }
                                line_project_pos = ABSF(gdist);
                            }
                        }
                    }
                }
            }
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

// Unused?
bool32 func_ovl2_800FA0A4(Vec3f *position, s32 *project_line_id, f32 *ga_dist, u32 *stand_coll_flags, Vec3f *angle)
{
    mpLineInfo *line_info;
    mpLineData *line_data;
    mpRoomInfo *room_info;
    s32 i, j;
    f32 vpdist_x, vpdist_y;
    s32 line_id;
    f32 line_project_pos;
    f32 fpos;
    f32 gdist;

    line_project_pos = (f32)FLOAT_MAX;
    line_info = gpMapGeometry->line_info;

    for (i = 0; i < gpMapGeometry->room_count; i++, line_info++)
    {
        line_data = &line_info->line_data[mpCollision_LineType_LWall];
        room_info = gpMapRooms->room_info[line_info->room_id];

        if ((line_data->line_count != 0) && (room_info->collision_kind < 3))
        {
            if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
            {
                // This runs when the corner of the character's map collision diamond collides with a wall?
                vpdist_x = (position->x - room_info->dynacoll_pos.x);
                vpdist_y = (position->y - room_info->dynacoll_pos.y);
            }
            else
            {
                vpdist_x = position->x;
                vpdist_y = position->y;
            }
            for (line_id = line_data->group_id; line_id < (line_data->group_id + line_data->line_count); line_id++)
            {
                if (gpMapVertexInfo->vertex_info[line_id].coll_pos_next >= vpdist_x)
                {
                    s32 vertex_id1 = gpMapVertexLinks[line_id].vertex1;
                    s32 vertex_id2 = gpMapVertexLinks[line_id].vertex2 - 1;

                    s32 y1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.y;
                    s32 y2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + vertex_id2]].pos.y;
                    s32 x1;
                    s32 x2;

                    if ((y1 <= vpdist_y && y2 >= vpdist_y) || (y2 <= vpdist_y && y1 >= vpdist_y))
                    {
                        if (vertex_id2 != 1)
                        {
                            for (j = 0; j < vertex_id2; j++, vertex_id1++)
                            {
                                y1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.y;
                                y2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.y;

                                if ((y1 <= vpdist_y && y2 >= vpdist_y) || (y2 <= vpdist_y && y1 >= vpdist_y))
                                {
                                    break;
                                }
                            }
                        }
                        x1 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].pos.x;
                        x2 = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1 + 1]].pos.x;

                        fpos = func_ovl2_800F3A34(vpdist_y, x1, y1, x2, y2);

                        gdist = fpos - vpdist_x;

                        if (fpos >= vpdist_x)
                        {
                            if (ABSF(gdist) < line_project_pos)
                            {
                                if (project_line_id != NULL)
                                {
                                    *project_line_id = line_id;
                                }
                                if (ga_dist != NULL)
                                {
                                    *ga_dist = gdist;
                                }
                                if (stand_coll_flags != NULL)
                                {
                                    *stand_coll_flags = gpMapVertexData->vpos[gpMapVertexID->vertex_id[vertex_id1]].vertex_flags;
                                }
                                if (angle != NULL)
                                {
                                    mpCollision_GetUDAngle(angle, x1, y1, x2, y2, -1);
                                }
                                line_project_pos = ABSF(gdist);
                            }
                        }
                    }
                }
            }
        }
    }
    if (line_project_pos == (f32)FLOAT_MAX)
    {
        return FALSE;
    }
    else return TRUE;
}

// 0x800FA518
s32 func_ovl2_800FA518(s32 line_id)
{
    mpRoomInfo *room_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetNbVertex() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    room_info = gpMapRooms->room_info[gpMapVertexInfo->vertex_info[line_id].room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetNbVertex() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return gpMapVertexLinks[line_id].vertex2;
}

// 0x800F15E8
void func_ovl2_800FA5E8(s32 line_id, s32 vertex_id, Vec3f *pos)
{
    mpRoomInfo *room_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetVertex() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    room_info = gpMapRooms->room_info[gpMapVertexInfo->vertex_info[line_id].room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetVertex() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    pos->x = gpMapVertexData->vpos[gpMapVertexID->vertex_id[gpMapVertexLinks[line_id].vertex1 + vertex_id]].pos.x;
    pos->y = gpMapVertexData->vpos[gpMapVertexID->vertex_id[gpMapVertexLinks[line_id].vertex1 + vertex_id]].pos.y;
    pos->z = 0.0F;

    room_info = gpMapRooms->room_info[gpMapVertexInfo->vertex_info[line_id].room_id];

    if ((room_info->p_dynacoll != NULL) || (room_info->collision_kind != 0))
    {
        pos->x += room_info->dynacoll_pos.x;
        pos->y += room_info->dynacoll_pos.y;
    }
}

// 0x800FA7B8
void func_ovl2_800FA7B8(s32 line_id, Vec3f *speed)
{
    mpRoomInfo *room_info;
    u8 room_id;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetSpeedId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    room_id = gpMapVertexInfo->vertex_info[line_id].room_id;

    room_info = gpMapRooms->room_info[room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetSpeedId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    *speed = gpMapRoomVectors[room_id];
}

// 0x800FA8A4
s32 func_ovl2_800FA8A4(s32 line_id)
{
    mpRoomInfo *room_info;
    mpVertexInfo *vertex_info;
    u8 room_id;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetKindId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    vertex_info = &gpMapVertexInfo->vertex_info[line_id];
    room_info = gpMapRooms->room_info[vertex_info->room_id];

    if (room_info->collision_kind == 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetKindId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return vertex_info->coll_vertex_id;
}

// 0x800FA964
s32 func_ovl2_800FA964(s32 line_id)
{
    mpRoomInfo *room_info;
    mpVertexInfo *vertex_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeUnderRId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    vertex_info = &gpMapVertexInfo->vertex_info[line_id];
    room_info = gpMapRooms->room_info[vertex_info->room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeUnderRId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return vertex_info->edge_psign_id;
}

// 0x800FAA24
s32 func_ovl2_800FAA24(s32 line_id)
{
    mpRoomInfo *room_info;
    mpVertexInfo *vertex_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeUnderLId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    vertex_info = &gpMapVertexInfo->vertex_info[line_id];
    room_info = gpMapRooms->room_info[vertex_info->room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeUnderLId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return vertex_info->edge_nsign_id;
}

// 0x800FAAE4
s32 func_ovl2_800FAAE4(s32 line_id)
{
    mpRoomInfo *room_info;
    mpVertexInfo *vertex_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeUpperRId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    vertex_info = &gpMapVertexInfo->vertex_info[line_id];
    room_info = gpMapRooms->room_info[vertex_info->room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeUpperRId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return vertex_info->edge_psign_id;
}

// 0x800FABA4
s32 func_ovl2_800FABA4(s32 line_id)
{
    mpRoomInfo *room_info;
    mpVertexInfo *vertex_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeUpperLId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    vertex_info = &gpMapVertexInfo->vertex_info[line_id];
    room_info = gpMapRooms->room_info[vertex_info->room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeUpperLId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return vertex_info->edge_nsign_id;
}

// 0x800FAC64
s32 func_ovl2_800FAC64(s32 line_id)
{
    mpRoomInfo *room_info;
    mpVertexInfo *vertex_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeRightUId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    vertex_info = &gpMapVertexInfo->vertex_info[line_id];
    room_info = gpMapRooms->room_info[vertex_info->room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeRightUId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return vertex_info->edge_psign_id;
}

// 0X800FAD24
s32 func_ovl2_800FAD24(s32 line_id)
{
    mpRoomInfo *room_info;
    mpVertexInfo *vertex_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeRightDId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    vertex_info = &gpMapVertexInfo->vertex_info[line_id];
    room_info = gpMapRooms->room_info[vertex_info->room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeRightDId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return vertex_info->edge_nsign_id;
}

// 0x800FADE4
s32 func_ovl2_800FADE4(s32 line_id)
{
    mpRoomInfo *room_info;
    mpVertexInfo *vertex_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeLeftUId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    vertex_info = &gpMapVertexInfo->vertex_info[line_id];
    room_info = gpMapRooms->room_info[vertex_info->room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeLeftUId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return vertex_info->edge_psign_id;
}

// 0x800FAEA4
s32 func_ovl2_800FAEA4(s32 line_id)
{
    mpRoomInfo *room_info;
    mpVertexInfo *vertex_info;

    if ((line_id == -1) || (line_id == -2))
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeLeftDId() id = %d\n", line_id);
            scnmgr_crash_print_gobj_state();
        }
    }
    vertex_info = &gpMapVertexInfo->vertex_info[line_id];
    room_info = gpMapRooms->room_info[vertex_info->room_id];

    if (room_info->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetEdgeLeftDId() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    return vertex_info->edge_nsign_id;
}

void func_ovl2_800FAF64(s32 arg0, Vec3f *vec)
{
    if (!gpMapGeometry->unk_mpgeo_count)
    {
        vec->x = vec->y = vec->z = 0.0F;
    }
    else
    {
        s32 i, index = arg0;

        for (i = 0; i < gpMapGeometry->unk_mpgeo_count; i++)
        {
            if (index == D_ovl2_80131380->vector_data[i].mpvector_id)
            {
                vec->x = D_ovl2_80131380->vector_data[i].pos.x;
                vec->y = D_ovl2_80131380->vector_data[i].pos.y;
                vec->z = 0;

                break;
            }
        }
    }
}

extern s32 gMapVertexGroupCount;

void func_ovl2_800FB010(void)
{
    gpMapVertexInfo = hal_alloc(gMapVertexGroupCount * sizeof(mpVertexInfo), 8);
}