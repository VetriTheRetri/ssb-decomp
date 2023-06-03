#include "mpcoll.h"
#include "gmmisc.h"

static CollisionGroupInfo **D_ovl2_80131304;
static CollisionVertexInfo *D_ovl2_8013136C;
static CollisionVertexArray *D_ovl2_80131374;
static CollisionVertexLinks *D_ovl2_80131378;   // 
static CollisionVtxPosContainer *D_ovl2_80131370; // Vertex positions

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
    CollisionVertexLinks *vlinks;
    CollisionGroupInfo *collgroup;
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
    collgroup = D_ovl2_80131304[D_ovl2_8013136C[line_id].coll_group_id];

    if (collgroup->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetUUCommon() no collsion\n");

            scnmgr_crash_print_gobj_state();
        }
    }
    vlinks = &D_ovl2_80131378[line_id];

    if ((collgroup->p_dynacoll != NULL) || (collgroup->collision_kind != 0))
    {
        object_pos_x = object_pos->x - collgroup->dynacoll_pos.x;
        object_pos_y = object_pos->y - collgroup->dynacoll_pos.y;
    }
    else
    {
        object_pos_x = object_pos->x;
        object_pos_y = object_pos->y;
    }
    vertex1 = vlinks->vertex1;
    pv = &D_ovl2_80131374->unk_vertex[vertex1];
    v1x = D_ovl2_80131370->vpos[pv[0]].pos.x;
    vid = vlinks->vertex2 - 1;
    v2x = D_ovl2_80131370->vpos[D_ovl2_80131374->unk_vertex[vertex1 + vid]].pos.x;

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
            v1x = D_ovl2_80131370->vpos[pv[0]].pos.x;
            v2x = D_ovl2_80131370->vpos[pv[1]].pos.x;

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
    v1y = D_ovl2_80131370->vpos[pv[0]].pos.y;
    v2y = D_ovl2_80131370->vpos[pv[1]].pos.y;

    if (flags != NULL)
    {
        *flags = D_ovl2_80131370->vpos[pv[0]].unk_0x4;
    }
    if (arg2 != NULL)
    {
        *arg2 = func_ovl2_800F39F0(object_pos_x, vnear, v1y, v2x, v2y) - object_pos_y;
    }
    if (angle != NULL)
    {
        mpCollision_VertexCalcAngle(angle, v1x, v1y, v2x, v2y, lr);
    }
    return TRUE;
}

bool32 func_ovl2_800F3DD8(s32 line_id, Vec3f *object_pos, f32 *arg2, u32 *flags, Vec3f *angle)
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
    CollisionVertexLinks *vlinks;
    CollisionGroupInfo *collgroup;
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
    collgroup = D_ovl2_80131304[D_ovl2_8013136C[line_id].coll_group_id];

    if (collgroup->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetLRCommon() no collision\n");

            scnmgr_crash_print_gobj_state();
        }
    }
    vlinks = &D_ovl2_80131378[line_id];

    if ((collgroup->p_dynacoll != NULL) || (collgroup->collision_kind != 0))
    {
        object_pos_x = object_pos->x - collgroup->dynacoll_pos.x;
        object_pos_y = object_pos->y - collgroup->dynacoll_pos.y;
    }
    else
    {
        object_pos_x = object_pos->x;
        object_pos_y = object_pos->y;
    }
    vertex1 = vlinks->vertex1;
    pv = &D_ovl2_80131374->unk_vertex[vertex1];
    v1y = D_ovl2_80131370->vpos[pv[0]].pos.y;
    vid = vlinks->vertex2 - 1;
    v2y = D_ovl2_80131370->vpos[D_ovl2_80131374->unk_vertex[vertex1 + vid]].pos.y;

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
            v1y = D_ovl2_80131370->vpos[pv[0]].pos.y;
            v2y = D_ovl2_80131370->vpos[pv[1]].pos.y;

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
    v1x = D_ovl2_80131370->vpos[pv[0]].pos.x;
    v2x = D_ovl2_80131370->vpos[pv[1]].pos.x;

    if (flags != NULL)
    {
        *flags = D_ovl2_80131370->vpos[pv[0]].unk_0x4;
    }
    if (arg2 != NULL)
    {
        *arg2 = func_ovl2_800F3A34(object_pos_y, v1x, v1y, v2x, v2y) - object_pos_x;
    }
    if (angle != NULL)
    {
        func_ovl2_800F71A0(angle, v1x, v1y, v2x, v2y, lr);
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
    CollisionVertexLinks *vlinks;
    CollisionGroupInfo *collgroup;
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
    collgroup = D_ovl2_80131304[D_ovl2_8013136C[line_id].coll_group_id];

    if (collgroup->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetLREdge() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    vlinks = &D_ovl2_80131378[line_id];
    vertex1 = vlinks->vertex1;
    vid = (vlinks->vertex2 + vertex1) - 1;
    v1x = D_ovl2_80131370->vpos[D_ovl2_80131374->unk_vertex[vertex1]].pos.x;
    v2x = D_ovl2_80131370->vpos[D_ovl2_80131374->unk_vertex[vid]].pos.x;

    cmp_lt = (lr < 0) ? (v1x < v2x) : (v2x < v1x);

    if (cmp_lt != FALSE)
    {
        object_pos->x = v1x;
        object_pos->y = D_ovl2_80131370->vpos[D_ovl2_80131374->unk_vertex[vertex1]].pos.y;
    }
    else
    {
        object_pos->x = v2x;
        object_pos->y = D_ovl2_80131370->vpos[D_ovl2_80131374->unk_vertex[vid]].pos.y;
    }
    object_pos->z = 0.0F;

    if ((collgroup->p_dynacoll != NULL) || (collgroup->collision_kind != 0))
    {
        object_pos->x += collgroup->dynacoll_pos.x;
        object_pos->y += collgroup->dynacoll_pos.y;
    }
}

void func_ovl2_800F4408(s32 line_id, Vec3f *object_pos)
{
    mpCollision_GetLREdge(line_id, object_pos, 1);
}

void func_ovl2_800F4428(s32 line_id, Vec3f *object_pos)
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
    CollisionVertexLinks *vlinks;
    CollisionGroupInfo *collgroup;
    CollisionVertexPosition *vpos1;
    CollisionVertexPosition *vpos2;
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
    collgroup = D_ovl2_80131304[D_ovl2_8013136C[line_id].coll_group_id];

    if (collgroup->collision_kind >= 3)
    {
        while (TRUE)
        {
            fatal_printf("mpGetUDEdge() no collision\n");
            scnmgr_crash_print_gobj_state();
        }
    }
    vlinks = &D_ovl2_80131378[line_id];
    vertex1 = vlinks->vertex1;
    vid = (vlinks->vertex2 + vertex1) - 1;
    vpos1 = &D_ovl2_80131370->vpos[D_ovl2_80131374->unk_vertex[vertex1]];
    vpos2 = &D_ovl2_80131370->vpos[D_ovl2_80131374->unk_vertex[vid]];

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

    if ((collgroup->p_dynacoll != NULL) || (collgroup->collision_kind != 0))
    {
        object_pos->x += collgroup->dynacoll_pos.x;
        object_pos->y += collgroup->dynacoll_pos.y;
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
void mpCollision_VertexCalcAngle(Vec3f *angle, s32 v1x, s32 v1y, s32 v2x, s32 v2y, s32 lr)
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