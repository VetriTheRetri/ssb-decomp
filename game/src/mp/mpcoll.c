#include "mpcoll.h"
#include "obj.h"

extern s32 D_ovl2_80130DE0;
extern s32 D_ovl2_80130DE8[5]; // Wall line ID?
extern f32 D_ovl2_80130DFC;
extern s32 D_ovl2_80130E00;
extern s32 D_ovl2_80130E04;
extern Vec3f D_ovl2_80130E08;
extern u16 D_ovl2_80131398;

void func_ovl2_800D9510(void)
{
    D_ovl2_80130DE0 = 0;
}

void func_ovl2_800D951C(s32 arg0)
{
    s32 i;

    for (i = 0; i < D_ovl2_80130DE0; i++)
    {
        if (arg0 == D_ovl2_80130DE8[i])
        {
            return;
        }
    }

    if (D_ovl2_80130DE0 != ARRAY_COUNT(D_ovl2_80130DE8))
    {
        D_ovl2_80130DE8[D_ovl2_80130DE0] = arg0;
        D_ovl2_80130DE0++;
    }
}

void func_ovl2_800D957C(void)
{
    D_ovl2_80130DFC = ((f32) -(U16_MAX + 1));
}

void func_ovl2_800D9590(void)
{
    D_ovl2_80130DFC = ((f32) (U16_MAX + 1));
}

void func_ovl2_800D95A4(f32 arg0, s32 arg1, s32 arg2, Vec3f *arg3)
{
    D_ovl2_80130DFC = arg0;
    D_ovl2_80130E00 = arg1;
    D_ovl2_80130E04 = arg2;
    D_ovl2_80130E08 = *arg3;
}

void func_ovl2_800D95E0(f32 *arg0, s32 *arg1, s32 *arg2, Vec3f *arg3)
{
    *arg0 = D_ovl2_80130DFC;
    *arg1 = D_ovl2_80130E00;
    *arg2 = D_ovl2_80130E04;
    *arg3 = D_ovl2_80130E08;
}

bool32 func_ovl2_800D9628(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f b;
    Vec3f a;
    s32 sp2C;
    s32 sp28;

    sp28 = func_ovl2_800FAAE4(coll_data->ceil_line_id);

    b.x = translate->x;
    b.y = translate->y + object_coll->top;
    a.x = translate->x + object_coll->width;
    a.y = translate->y + object_coll->center;

    if ((func_ovl2_800F7F00(&b, &a, 0, &sp2C, 0, 0) != FALSE) && (sp2C != sp28))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl2_800D96D8(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f sp3C;
    Vec3f sp30;
    f32 sp2C;

    sp30.x = translate->x + object_coll->width;
    sp3C.x = sp30.x;

    sp30.y = translate->y + object_coll->center;
    sp3C.y = sp30.y;

    sp3C.x += (2.0F * (coll_data->ceil_angle.y * object_coll->width));
    sp3C.y += (2.0F * (-coll_data->ceil_angle.x * object_coll->width));

    if (func_ovl2_800F7F00(&sp3C, &sp30, &coll_data->ground_to_air_pos_last, NULL, 0, 0) != 0)
    {
        sp30.x = coll_data->ground_to_air_pos_last.x - object_coll->width;
        sp30.y = translate->y + object_coll->top;

        if (func_ovl2_800F3E04(coll_data->ceil_line_id, &sp30, &sp2C, &coll_data->ceil_material, &coll_data->ceil_angle.x) != 0)
        {
            translate->y += sp2C;
            translate->x = sp30.x;
        }
    }
}

bool32 func_ovl2_800D97F0(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f b;
    Vec3f a;
    s32 sp2C;
    s32 sp28;

    sp28 = func_ovl2_800FABA4(coll_data->ceil_line_id);

    b.x = translate->x;
    b.y = translate->y + object_coll->top;
    a.x = translate->x - object_coll->width;
    a.y = translate->y + object_coll->center;

    if ((func_ovl2_800F6B58(&b, &a, 0, &sp2C, 0, 0) != FALSE) && (sp2C != sp28))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl2_800D98A0(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f sp3C;
    Vec3f sp30;
    f32 sp2C;

    sp30.x = translate->x - object_coll->width;
    sp3C.x = sp30.x;

    sp30.y = translate->y + object_coll->center;
    sp3C.y = sp30.y;

    sp3C.x += (2.0F * (-coll_data->ceil_angle.y * object_coll->width));
    sp3C.y += (2.0F * (coll_data->ceil_angle.x * object_coll->width));

    if (func_ovl2_800F6B58(&sp3C, &sp30, &coll_data->ground_to_air_pos_last, NULL, 0, 0) != 0)
    {
        sp30.x = coll_data->ground_to_air_pos_last.x + object_coll->width;
        sp30.y = translate->y + object_coll->top;

        if (func_ovl2_800F3E04(coll_data->ceil_line_id, &sp30, &sp2C, &coll_data->ceil_material, &coll_data->ceil_angle.x) != 0)
        {
            translate->y += sp2C;
            translate->x = sp30.x;
        }
    }
}

void func_ovl2_800D99B8(Coll_Data *coll_data)
{
    if (func_ovl2_800D9628(coll_data) != FALSE)
    {
        func_ovl2_800D96D8(coll_data);
    }
    if (func_ovl2_800D97F0(coll_data) != FALSE)
    {
        func_ovl2_800D98A0(coll_data);
    }
}

bool32 func_ovl2_800D9A00(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f b;
    Vec3f a;
    s32 sp2C = func_ovl2_800FAA24(coll_data->ground_line_id);

    b.x = translate->x;
    b.y = translate->y + object_coll->bottom;
    a.x = translate->x + object_coll->width;
    a.y = translate->y + object_coll->center;

    if ((func_ovl2_800F7F00(&b, &a, NULL, &coll_data->unk_0x60, 0, 0) != 0) && (sp2C != coll_data->unk_0x60))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl2_800D9AB0(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34;

    sp38.x = translate->x + object_coll->width;
    sp38.y = translate->y + object_coll->center;

    if (func_ovl2_800F4194(coll_data->unk_0x60, &sp38, NULL, NULL, NULL) != 0)
    {
        sp38.x = translate->x + object_coll->width;
        sp44.x = sp38.x;
        sp38.y = translate->y + object_coll->center;
        sp44.y = sp38.y;

        sp44.x += (2.0F * (-coll_data->ground_angle.y * object_coll->width));
        sp44.y += (2.0F * (coll_data->ground_angle.x * object_coll->width));

        if (func_ovl2_800F7F00(&sp44, &sp38, &coll_data->ground_to_air_pos_last, NULL, 0, 0) != 0)
        {
            sp38.x = coll_data->ground_to_air_pos_last.x - object_coll->width;
            sp38.y = translate->y + object_coll->bottom;

            if (func_ovl2_800F3DD8(coll_data->ground_line_id, &sp38, &sp34, &coll_data->clip_flag, &coll_data->ground_angle.x) != 0)
            {
                translate->y += sp34;
                translate->x = sp38.x;
            }
        }
    }
    else
    {
        func_ovl2_800F4650(coll_data->unk_0x60, &sp44);

        sp44.x -= 2.0F;
        sp38.x = sp44.x - (2.0F * object_coll->width);
        sp38.y = sp44.y - (2.0F * (object_coll->center - object_coll->bottom));

        if (func_ovl2_800F4BD8(&sp44, &sp38, &coll_data->ground_to_air_pos_last, NULL, NULL, NULL) != 0)
        {
            sp38.x = coll_data->ground_to_air_pos_last.x;
            sp38.y = translate->y;

            if (func_ovl2_800F3DD8(coll_data->ground_line_id, &sp38, &sp34, &coll_data->clip_flag, &coll_data->ground_angle.x) != 0)
            {
                translate->y += sp34;
                translate->x = sp38.x;
            }
        }
    }
}

bool32 func_ovl2_800D9CC0(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f b;
    Vec3f a;
    s32 sp2C = func_ovl2_800FA964(coll_data->ground_line_id);

    b.x = translate->x;
    b.y = translate->y + object_coll->bottom;
    a.x = translate->x - object_coll->width;
    a.y = translate->y + object_coll->center;

    if ((func_ovl2_800F6B58(&b, &a, NULL, &coll_data->unk_0x60, 0, 0) != 0) && (sp2C != coll_data->unk_0x60))
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl2_800D9D70(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34;

    sp38.x = translate->x - object_coll->width;
    sp38.y = translate->y + object_coll->center;

    if (func_ovl2_800F41C0(coll_data->unk_0x60, &sp38, NULL, NULL, NULL) != 0)
    {
        sp38.x = translate->x - object_coll->width;
        sp44.x = sp38.x;
        sp38.y = translate->y + object_coll->center;
        sp44.y = sp38.y;

        sp44.x += (2.0F * (coll_data->ground_angle.y * object_coll->width));
        sp44.y += (2.0F * (-coll_data->ground_angle.x * object_coll->width));

        if (func_ovl2_800F6B58(&sp44, &sp38, &coll_data->ground_to_air_pos_last, NULL, 0, 0) != 0)
        {
            sp38.x = coll_data->ground_to_air_pos_last.x + object_coll->width;
            sp38.y = translate->y + object_coll->bottom;

            if (func_ovl2_800F3DD8(coll_data->ground_line_id, &sp38, &sp34, &coll_data->clip_flag, &coll_data->ground_angle.x) != 0)
            {
                translate->y += sp34;
                translate->x = sp38.x;
            }
        }
    }
    else
    {
        func_ovl2_800F4690(coll_data->unk_0x60, &sp44);

        sp44.x += 2.0F;
        sp44.x = sp38.x + (2.0F * object_coll->width);
        sp44.y = sp38.y - (2.0F * (object_coll->center - object_coll->bottom));

        if (func_ovl2_800F4BD8(&sp44, &sp38, &coll_data->ground_to_air_pos_last, NULL, NULL, NULL) != 0)
        {
            sp38.x = coll_data->ground_to_air_pos_last.x;
            sp38.y = translate->y;

            if (func_ovl2_800F3DD8(coll_data->ground_line_id, &sp38, &sp34, &coll_data->clip_flag, &coll_data->ground_angle.x) != 0)
            {
                translate->y += sp34;
                translate->x = sp38.x;
            }
        }
    }
}

void func_ovl2_800D9F84(Coll_Data *coll_data)
{
    if (func_ovl2_800D9A00(coll_data) != FALSE)
    {
        func_ovl2_800D9AB0(coll_data);
    }
    if (func_ovl2_800D9CC0(coll_data) != FALSE)
    {
        func_ovl2_800D9D70(coll_data);
    }
}

void func_ovl2_800D9FCC(Coll_Data *coll_data) // Check if fighter is above ground while airborne
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f sp2C;

    sp2C.x = translate->x;
    sp2C.y = translate->y + object_coll->bottom;

    if (func_ovl2_800F9348(&sp2C, &coll_data->ground_line_id, &coll_data->ground_dist, &coll_data->clip_flag, &coll_data->ground_angle.x) == FALSE)
    {
        coll_data->ground_line_id = -1;
    }
}

bool32 func_ovl2_800DA034(Coll_Data *coll_data, bool32(*cb_coll)(Coll_Data *, GObj*, bool32), GObj *gobj, bool32 arg3)
{
    Vec3f *translate = coll_data->p_translate;
    Vec3f *pcurr = &coll_data->pos_curr;
    f32 project_y;
    f32 project_x;
    f32 var_f20;
    f32 var_f22;
    f32 var_f24;
    s32 var_s1;
    s32 var_s3;
    s32 sp50;

    if (translate->x < pcurr->x)
    {
        project_x = -(translate->x - pcurr->x);
    }
    else project_x = translate->x - pcurr->x;

    if (translate->y < pcurr->y)
    {
        project_y = -(translate->y - pcurr->y);
    }
    else project_y = translate->y - pcurr->y;

    if ((project_x > 250.0F) || (project_y > 250.0F))
    {
        var_s3 = (project_y < project_x) ? (s32)(project_x / 250.0F) : (s32)(project_y / 250.0F);

        var_s3++;

        var_f20 = coll_data->pos_prev.x / var_s3;
        var_f22 = coll_data->pos_prev.y / var_s3;
        var_f24 = coll_data->pos_prev.z / var_s3;
    }
    else
    {
        var_s3 = 1;

        var_f20 = coll_data->pos_prev.x;
        var_f22 = coll_data->pos_prev.y;
        var_f24 = coll_data->pos_prev.z;
    }
    *translate = *pcurr;

    for (var_s1 = 0; (var_s1 < var_s3) && (coll_data->unk_0x64 == 0); var_s1++)
    {
        *pcurr = *translate;

        if (var_s1 == 0)
        {
            translate->x += coll_data->pos_correct.x + coll_data->pos_project.x;
            translate->y += coll_data->pos_correct.y + coll_data->pos_project.y;
            translate->z += coll_data->pos_correct.z + coll_data->pos_project.z;
        }
        translate->x += var_f20;
        translate->y += var_f22;
        translate->z += var_f24;

        sp50 = cb_coll(coll_data, gobj, arg3);
    }
    coll_data->wall_flag = D_ovl2_80131398;

    return sp50;
}

bool32 func_ovl2_800DA294(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    ObjectColl *p_object_coll = coll_data->p_object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f *pcurr = &coll_data->pos_curr;
    Vec3f sp4C;
    Vec3f sp40;
    bool32 is_collide_rwall = FALSE;
    s32 test_line_id;
    s32 ground_line_id;
    bool32 wall_collide;

    func_ovl2_800D9510();

    ground_line_id = (func_ovl2_800FC67C(coll_data->ground_line_id) != FALSE) ? func_ovl2_800FAA24(coll_data->ground_line_id) : -1;

    sp4C.x = pcurr->x + p_object_coll->width;
    sp4C.y = pcurr->y + p_object_coll->center;
    sp40.x = translate->x + object_coll->width;
    sp40.y = translate->y + object_coll->center;

    wall_collide = (coll_data->wall_flag != D_ovl2_80131398) ? func_ovl2_800F8974(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) : func_ovl2_800F7F00(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL);

    if ((wall_collide != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_rwall = TRUE;
    }
    sp4C.x = pcurr->x;
    sp4C.y = pcurr->y + p_object_coll->bottom;
    sp40.x = translate->x;
    sp40.y = translate->y + object_coll->bottom;

    wall_collide = (coll_data->wall_flag != D_ovl2_80131398) ? func_ovl2_800F8974(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) : func_ovl2_800F7F00(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL);

    if ((wall_collide != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_rwall = TRUE;
    }
    sp4C.x = pcurr->x;
    sp4C.y = pcurr->y + p_object_coll->top;
    sp40.x = translate->x;
    sp40.y = translate->y + object_coll->top;

    wall_collide = (coll_data->wall_flag != D_ovl2_80131398) ? func_ovl2_800F8974(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) : func_ovl2_800F7F00(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL);

    if ((wall_collide != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_rwall = TRUE;
    }
    sp4C.x = translate->x;
    sp4C.y = translate->y + object_coll->bottom;
    sp40.x = translate->x + object_coll->width;
    sp40.y = translate->y + object_coll->center;

    if ((func_ovl2_800F7F00(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_rwall = TRUE;
    }
    sp4C.x = translate->x;
    sp4C.y = translate->y + object_coll->top;
    sp40.x = translate->x + object_coll->width;
    sp40.y = translate->y + object_coll->center;

    if ((func_ovl2_800F7F00(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_rwall = TRUE;
    }
    if (is_collide_rwall != FALSE)
    {
        coll_data->coll_mask |= MPCOLL_MASK_RWALL;
    }
    return is_collide_rwall;
}

void func_ovl2_800DA658(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C;
    s32 i;
    s32 temp_v0;
    s32 j;
    f32 sp6C;
    s32 wall_line_id;
    f32 sp64;

    func_ovl2_800D9590();

    for (i = 0; i < D_ovl2_80130DE0; i++)
    {
        wall_line_id = D_ovl2_80130DE8[i];

        func_ovl2_800F4650(wall_line_id, &sp94);

        if (sp94.y < (translate->y + object_coll->bottom))
        {
            if ((sp94.x < D_ovl2_80130DFC) && (func_ovl2_800F4194(wall_line_id, &sp94, NULL, &sp6C, &sp88) != 0))
            {
                func_ovl2_800D95A4(sp94.x, wall_line_id, sp6C, &sp88);
            }
        }
        else
        {
            func_ovl2_800F4670(wall_line_id, &sp94);

            if ((translate->y + object_coll->top) < sp94.y)
            {
                if ((sp94.x < D_ovl2_80130DFC) && (func_ovl2_800F4194(wall_line_id, &sp94, NULL, &sp6C, &sp88) != 0))
                {
                    func_ovl2_800D95A4(sp94.x, wall_line_id, sp6C, &sp88);
                }
            }
            else
            {
                sp94.x = translate->x;
                sp94.y = translate->y + object_coll->bottom;

                if (func_ovl2_800F4194(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) < D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                sp94.x = translate->x + object_coll->width;
                sp94.y = translate->y + object_coll->center;

                if (func_ovl2_800F4194(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) < D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                sp94.x = translate->x;
                sp94.y = translate->y + object_coll->top;

                if (func_ovl2_800F4194(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) < D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                temp_v0 = func_ovl2_800FA518(wall_line_id);

                for (j = 0; j < temp_v0; j++)
                {
                    func_ovl2_800FA5E8(wall_line_id, j, &sp7C);

                    if ((translate->y + object_coll->bottom) <= sp7C.y)
                    {
                        if (sp7C.y <= (translate->y + object_coll->center))
                        {
                            sp64 = sp7C.x - (((sp7C.y - (translate->y + object_coll->bottom)) * object_coll->width) / (object_coll->center - object_coll->bottom));

                            goto block_26;
                        }
                    }
                    if ((translate->y + object_coll->center) <= sp7C.y)
                    {
                        if (sp7C.y <= (translate->y + object_coll->top))
                        {
                            sp64 = sp7C.x - ((((translate->y + object_coll->top) - sp7C.y) * object_coll->width) / (object_coll->top - object_coll->center));

                        block_26:
                            if ((sp64 < D_ovl2_80130DFC) && (func_ovl2_800F4194(wall_line_id, &sp7C, NULL, &sp6C, &sp88) != 0))
                            {
                                func_ovl2_800D95A4(sp64, wall_line_id, sp6C, &sp88);
                            }
                        }
                    }
                }
            }
        }
        continue;
    }
    func_ovl2_800D95E0(&sp64, &coll_data->rwall_line_id, &coll_data->rwall_material, &coll_data->rwall_angle);

    if (sp64 < translate->x)
    {
        translate->x = sp64;
    }
}

bool32 func_ovl2_800DAAA8(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    ObjectColl *p_object_coll = coll_data->p_object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f *pcurr = &coll_data->pos_curr;
    Vec3f sp4C;
    Vec3f sp40;
    bool32 is_collide_lwall = FALSE;
    s32 test_line_id;
    s32 ground_line_id;
    bool32 wall_collide;

    func_ovl2_800D9510();

    ground_line_id = (func_ovl2_800FC67C(coll_data->ground_line_id) != FALSE) ? func_ovl2_800FA964(coll_data->ground_line_id) : -1;

    sp4C.x = pcurr->x - p_object_coll->width;
    sp4C.y = pcurr->y + p_object_coll->center;
    sp40.x = translate->x - object_coll->width;
    sp40.y = translate->y + object_coll->center;

    wall_collide = (coll_data->wall_flag != D_ovl2_80131398) ? func_ovl2_800F769C(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) : func_ovl2_800F6B58(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL);

    if ((wall_collide != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_lwall = TRUE;
    }
    sp4C.x = pcurr->x;
    sp4C.y = pcurr->y + p_object_coll->bottom;
    sp40.x = translate->x;
    sp40.y = translate->y + object_coll->bottom;

    wall_collide = (coll_data->wall_flag != D_ovl2_80131398) ? func_ovl2_800F769C(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) : func_ovl2_800F6B58(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL);

    if ((wall_collide != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_lwall = TRUE;
    }
    sp4C.x = pcurr->x;
    sp4C.y = pcurr->y + p_object_coll->top;
    sp40.x = translate->x;
    sp40.y = translate->y + object_coll->top;

    wall_collide = (coll_data->wall_flag != D_ovl2_80131398) ? func_ovl2_800F769C(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) : func_ovl2_800F6B58(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL);

    if ((wall_collide != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_lwall = TRUE;
    }
    sp4C.x = translate->x;
    sp4C.y = translate->y + object_coll->bottom;
    sp40.x = translate->x - object_coll->width;
    sp40.y = translate->y + object_coll->center;

    if ((func_ovl2_800F6B58(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_lwall = TRUE;
    }
    sp4C.x = translate->x;
    sp4C.y = translate->y + object_coll->top;
    sp40.x = translate->x - object_coll->width;
    sp40.y = translate->y + object_coll->center;

    if ((func_ovl2_800F6B58(&sp4C, &sp40, NULL, &test_line_id, NULL, NULL) != FALSE) && (test_line_id != ground_line_id))
    {
        func_ovl2_800D951C(test_line_id);

        is_collide_lwall = TRUE;
    }
    if (is_collide_lwall != FALSE)
    {
        coll_data->coll_mask |= MPCOLL_MASK_LWALL;
    }
    return is_collide_lwall;
}

void func_ovl2_800DAE6C(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C;
    s32 i;
    s32 temp_v0;
    s32 j;
    f32 sp6C;
    s32 wall_line_id;
    f32 sp64;

    func_ovl2_800D957C();

    for (i = 0; i < D_ovl2_80130DE0; i++)
    {
        wall_line_id = D_ovl2_80130DE8[i];

        func_ovl2_800F4690(wall_line_id, &sp94);

        if (sp94.y < (translate->y + object_coll->bottom))
        {
            if ((D_ovl2_80130DFC < sp94.x) && (func_ovl2_800F41C0(wall_line_id, &sp94, NULL, &sp6C, &sp88) != 0))
            {
                func_ovl2_800D95A4(sp94.x, wall_line_id, sp6C, &sp88);
            }
        }
        else
        {
            func_ovl2_800F46B0(wall_line_id, &sp94);

            if ((translate->y + object_coll->top) < sp94.y)
            {
                if ((D_ovl2_80130DFC < sp94.x) && (func_ovl2_800F41C0(wall_line_id, &sp94, NULL, &sp6C, &sp88) != 0))
                {
                    func_ovl2_800D95A4(sp94.x, wall_line_id, sp6C, &sp88);
                }
            }
            else
            {
                sp94.x = translate->x;
                sp94.y = translate->y + object_coll->bottom;

                if (func_ovl2_800F41C0(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) > D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                sp94.x = translate->x - object_coll->width;
                sp94.y = translate->y + object_coll->center;

                if (func_ovl2_800F41C0(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) > D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                sp94.x = translate->x;
                sp94.y = translate->y + object_coll->top;

                if (func_ovl2_800F41C0(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) > D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                temp_v0 = func_ovl2_800FA518(wall_line_id);

                for (j = 0; j < temp_v0; j++)
                {
                    func_ovl2_800FA5E8(wall_line_id, j, &sp7C);

                    if ((translate->y + object_coll->bottom) <= sp7C.y)
                    {
                        if (sp7C.y <= (translate->y + object_coll->center))
                        {
                            sp64 = sp7C.x + (((sp7C.y - (translate->y + object_coll->bottom)) * object_coll->width) / (object_coll->center - object_coll->bottom));

                            goto block_26;
                        }
                    }
                    if ((translate->y + object_coll->center) <= sp7C.y)
                    {
                        if (sp7C.y <= (translate->y + object_coll->top))
                        {
                            sp64 = sp7C.x + ((((translate->y + object_coll->top) - sp7C.y) * object_coll->width) / (object_coll->top - object_coll->center));

                        block_26:
                            if ((D_ovl2_80130DFC < sp64) && (func_ovl2_800F41C0(wall_line_id, &sp7C, NULL, &sp6C, &sp88) != 0))
                            {
                                func_ovl2_800D95A4(sp64, wall_line_id, sp6C, &sp88);
                            }
                        }
                    }
                }
            }
        }
        continue;
    }
    func_ovl2_800D95E0(&sp64, &coll_data->lwall_line_id, &coll_data->lwall_material, &coll_data->lwall_angle);

    if (translate->x < sp64)
    {
        translate->x = sp64;
    }
}

bool32 func_ovl2_800DB2BC(Coll_Data *coll_data)
{
    Vec3f *translate = coll_data->p_translate;
    s32 temp_v0;
    Vec3f sp3C;
    s32 unused;
    bool32 sp34;
    f32 sp30;

    coll_data->coll_type &= ~(MPCOLL_MASK_GROUND);

    sp3C.x = translate->x;
    sp3C.y = translate->y + coll_data->object_coll.bottom;

    if (func_ovl2_800FC67C(coll_data->ground_line_id) == FALSE)
    {
        func_ovl2_800D9FCC(coll_data);

        return FALSE;
    }
    if (func_ovl2_800F3DD8(coll_data->ground_line_id, &sp3C, &sp30, &coll_data->clip_flag, &coll_data->ground_angle) != FALSE)
    {
        translate->y += sp30;

        coll_data->ground_dist = 0.0F;
        coll_data->coll_type |= MPCOLL_MASK_GROUND;

        return TRUE;
    }
    sp34 = FALSE;

    func_ovl2_800F4428(coll_data->ground_line_id, &sp3C);

    if (translate->x <= sp3C.x)
    {
        temp_v0 = func_ovl2_800FAA24(coll_data->ground_line_id);

        if ((temp_v0 != -1) && (func_ovl2_800FA8A4(temp_v0) == 2))
        {
            sp34 = TRUE;
        }
    }
    else
    {
        func_ovl2_800F4408(coll_data->ground_line_id, &sp3C);

        temp_v0 = func_ovl2_800FA964(coll_data->ground_line_id);

        if ((temp_v0 != -1) && (func_ovl2_800FA8A4(temp_v0) == 3))
        {
            sp34 = TRUE;
        }
    }
    translate->y = sp3C.y - coll_data->object_coll.bottom;

    if (sp34 != 0)
    {
        translate->x = sp3C.x;

        func_ovl2_800F3DD8(coll_data->ground_line_id, &sp3C, NULL, &coll_data->clip_flag, &coll_data->ground_angle);

        coll_data->coll_type |= MPCOLL_MASK_GROUND;
        coll_data->ground_dist = 0.0F;

        return TRUE;
    }
    func_ovl2_800D9FCC(coll_data);

    return FALSE;
}

bool32 func_ovl2_800DB474(Coll_Data *coll_data, s32 arg1)
{
    ObjectColl *p_object_coll = coll_data->p_object_coll;
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    s32 var_v0;
    Vec3f sp4C;
    Vec3f sp40;
    s32 ground_line_id;
    u32 sp38;
    Vec3f sp2C;

    sp4C.x = coll_data->pos_curr.x;
    sp4C.y = coll_data->pos_curr.y + p_object_coll->bottom;
    sp40.x = translate->x;
    sp40.y = translate->y + object_coll->bottom;

                         var_v0
                              
                            =

        (coll_data->wall_flag != D_ovl2_80131398)

                            ?

    func_ovl2_800F521C(&sp4C, &sp40, &coll_data->ground_to_air_pos_last, &ground_line_id, &sp38, &sp2C)

                            :

    func_ovl2_800F4BD8(&sp4C, &sp40, &coll_data->ground_to_air_pos_last, &ground_line_id, &sp38, &sp2C);

    if ((var_v0 != 0) && (ground_line_id != arg1))
    {
        coll_data->coll_mask |= MPCOLL_MASK_GROUND;
        coll_data->ground_line_id = ground_line_id;
        coll_data->clip_flag = sp38;
        coll_data->ground_angle = sp2C;

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl2_800DB590(Coll_Data *coll_data)
{
    Vec3f *translate = coll_data->p_translate;
    Vec2f *cliffcatch_coll = &coll_data->cliffcatch_coll;
    Vec3f *pcurr = &coll_data->pos_curr;
    Vec3f sp48;
    Vec3f sp3C;
    u32 sp38;
    s32 var_v0;

    if (*coll_data->p_lr != RIGHT)
    {
        return FALSE;
    }

    sp48.x = pcurr->x + cliffcatch_coll->x;
    sp48.y = pcurr->y + cliffcatch_coll->y;
    sp3C.x = translate->x + cliffcatch_coll->x;
    sp3C.y = translate->y + cliffcatch_coll->y;

                    var_v0

                       =

    (coll_data->wall_flag != D_ovl2_80131398)

                       ?

    func_ovl2_800F521C(&sp48, &sp3C, &coll_data->ground_to_air_pos_last, &coll_data->cliff_id, &sp38, NULL)

                       :

    func_ovl2_800F4BD8(&sp48, &sp3C, &coll_data->ground_to_air_pos_last, &coll_data->cliff_id, &sp38, NULL);


    if ((var_v0 != 0) && (sp38 & 0x8000) && ((sp38 & 0xFFFF00FF) != 4))
    {
        func_ovl2_800F4428(coll_data->cliff_id, &sp3C);

        if ((coll_data->ground_to_air_pos_last.x - sp3C.x) < 800.0F)
        {
            coll_data->coll_mask |= MPCOLL_MASK_CLIFF;
            coll_data->coll_type |= MPCOLL_MASK_CLIFF;

            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl2_800DB6F0(Coll_Data *coll_data)
{
    Vec3f *translate = coll_data->p_translate;
    Vec2f *cliffcatch_coll = &coll_data->cliffcatch_coll;
    Vec3f *pcurr = &coll_data->pos_curr;
    Vec3f sp48;
    Vec3f sp3C;
    u32 sp38;
    s32 var_v0;

    if (*coll_data->p_lr != LEFT)
    {
        return FALSE;
    }

    sp48.x = pcurr->x - cliffcatch_coll->x;
    sp48.y = pcurr->y + cliffcatch_coll->y;
    sp3C.x = translate->x - cliffcatch_coll->x;
    sp3C.y = translate->y + cliffcatch_coll->y;

                    var_v0

                       =

    (coll_data->wall_flag != D_ovl2_80131398)

                       ?

    func_ovl2_800F521C(&sp48, &sp3C, &coll_data->ground_to_air_pos_last, &coll_data->cliff_id, &sp38, NULL)

                       :

    func_ovl2_800F4BD8(&sp48, &sp3C, &coll_data->ground_to_air_pos_last, &coll_data->cliff_id, &sp38, NULL);

    if ((var_v0 != 0) && (sp38 & 0x8000))
    {
        func_ovl2_800F4408(coll_data->cliff_id, &sp3C);

        if ((sp3C.x - coll_data->ground_to_air_pos_last.x) < 800.0F)
        {
            coll_data->coll_mask |= MPCOLL_MASK_RCLIFF;
            coll_data->coll_type |= MPCOLL_MASK_RCLIFF;

            return TRUE;
        }
    }
    return FALSE;
}

bool32 func_ovl2_800DB838(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    ObjectColl *p_object_coll = coll_data->p_object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f *pcurr = &coll_data->pos_curr;
    Vec3f sp54;
    Vec3f sp48;
    bool32 is_collide_rwall;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    u32 sp34;
    s32 var_v0;

    is_collide_rwall = FALSE;

    coll_data->unk_0x58 &= ~(MPCOLL_MASK_RWALL);
    coll_data->coll_type &= ~(MPCOLL_MASK_RWALL);

    func_ovl2_800D9510();

    sp54.x = pcurr->x + p_object_coll->width;
    sp54.y = pcurr->y + p_object_coll->center;
    sp48.x = translate->x + object_coll->width;
    sp48.y = translate->y + object_coll->center;

                             var_v0

                                =

            (coll_data->wall_flag != D_ovl2_80131398)

                                ?

    func_ovl2_800F8974(&sp54, &sp48, NULL, &sp40, NULL, NULL)

                                :

    func_ovl2_800F7F00(&sp54, &sp48, NULL, &sp40, NULL, NULL);

    if (var_v0 != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_rwall = TRUE;
    }
    sp54.x = pcurr->x;
    sp54.y = pcurr->y + p_object_coll->bottom;
    sp48.x = translate->x;
    sp48.y = translate->y + object_coll->bottom;

                         var_v0

                            =

            (coll_data->wall_flag != D_ovl2_80131398)

                            ?

    func_ovl2_800F8974(&sp54, &sp48, NULL, &sp40, NULL, NULL)

                            :

    func_ovl2_800F7F00(&sp54, &sp48, NULL, &sp40, NULL, NULL);

    if (var_v0 != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_rwall = TRUE;
    }
    sp54.x = pcurr->x;
    sp54.y = pcurr->y + p_object_coll->top;
    sp48.x = translate->x;
    sp48.y = translate->y + object_coll->top;

                     var_v0

                        =

    (coll_data->wall_flag != D_ovl2_80131398)

                        ?

    func_ovl2_800F8974(&sp54, &sp48, NULL, &sp40, NULL, NULL)

                        :

    func_ovl2_800F7F00(&sp54, &sp48, NULL, &sp40, NULL, NULL);

    if (var_v0 != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_rwall = TRUE;
    }
    sp54.x = translate->x;
    sp54.y = translate->y + object_coll->bottom;
    sp48.x = translate->x + object_coll->width;
    sp48.y = translate->y + object_coll->center;

    if (func_ovl2_800F7F00(&sp54, &sp48, NULL, &sp40, NULL, NULL) != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_rwall = TRUE;
    }
    sp54.x = translate->x;
    sp54.y = translate->y + object_coll->top;
    sp48.x = translate->x + object_coll->width;
    sp48.y = translate->y + object_coll->center;

    if (func_ovl2_800F7F00(&sp54, &sp48, NULL, &sp40, NULL, NULL) != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_rwall = TRUE;
    }
    sp54.x = pcurr->x + p_object_coll->width;
    sp54.y = pcurr->y + p_object_coll->center;
    sp48.x = translate->x + object_coll->width;
    sp48.y = translate->y + object_coll->center;

                     var_v0

                        =

    (coll_data->wall_flag != D_ovl2_80131398)

                        ?

    func_ovl2_800F64D4(&sp54, &sp48, NULL, &sp40, NULL, NULL)

                        :

    func_ovl2_800F5E90(&sp54, &sp48, NULL, &sp40, NULL, NULL);

    if (var_v0 != 0)
    {
        sp38 = func_ovl2_800FABA4(sp40);

        if (sp38 != -1)
        {
            if (func_ovl2_800FA8A4(sp38) == 3)
            {
                sp54.x = pcurr->x;
                sp54.y = pcurr->y + p_object_coll->top;
                sp48.x = translate->x;
                sp48.y = translate->y + object_coll->top;

                                     var_v0

                                        =

                    (coll_data->wall_flag != D_ovl2_80131398)

                                        ?

                func_ovl2_800F64D4(&sp54, &sp48, NULL, &sp3C, NULL, NULL)

                                        :

                func_ovl2_800F5E90(&sp54, &sp48, NULL, &sp3C, NULL, NULL);

                if ((var_v0 == 0) || (sp40 != sp3C))
                {
                    sp54.x = translate->x;
                    sp54.y = translate->y + object_coll->top;
                    sp48.x = translate->x + object_coll->width;
                    sp48.y = translate->y + object_coll->center;

                    if ((func_ovl2_800F5E90(&sp54, &sp48, 0, &sp3C, 0, 0) == 0) || (sp40 != sp3C))
                    {
                        func_ovl2_800D951C(sp38);

                        is_collide_rwall = TRUE;
                    }
                }
            }
        }
    }
    sp54.x = pcurr->x + p_object_coll->width;
    sp54.y = pcurr->y + p_object_coll->center;
    sp48.x = translate->x + object_coll->width;
    sp48.y = translate->y + object_coll->center;

                         var_v0

                            =

        (coll_data->wall_flag != D_ovl2_80131398)

                            ?

    func_ovl2_800F521C(&sp54, &sp48, NULL, &sp40, &sp34, NULL)

                            :

    func_ovl2_800F4BD8(&sp54, &sp48, NULL, &sp40, &sp34, NULL);

    if ((var_v0 != 0) && !(sp34 & 0x4000))
    {
        sp38 = func_ovl2_800FAA24(sp40);

        if (sp38 != -1)
        {
            if (func_ovl2_800FA8A4(sp38) == 3)
            {
                sp54.x = pcurr->x;
                sp54.y = pcurr->y + p_object_coll->bottom;
                sp48.x = translate->x;
                sp48.y = translate->y + object_coll->bottom;

                                 var_v0

                                    =

                (coll_data->wall_flag != D_ovl2_80131398)

                                    ?

                func_ovl2_800F521C(&sp54, &sp48, NULL, &sp3C, NULL, NULL)

                                    :

                func_ovl2_800F4BD8(&sp54, &sp48, NULL, &sp3C, NULL, NULL);

                if ((var_v0 == 0) || (sp40 != sp3C))
                {
                    sp54.x = translate->x;
                    sp54.y = translate->y + object_coll->bottom;
                    sp48.x = translate->x + object_coll->width;
                    sp48.y = translate->y + object_coll->center;

                    if ((func_ovl2_800F4BD8(&sp54, &sp48, NULL, &sp3C, NULL, NULL) == 0) || (sp40 != sp3C))
                    {
                        func_ovl2_800D951C(sp38);

                        is_collide_rwall = TRUE;
                    }
                }
            }
        }
    }
    if (is_collide_rwall != FALSE)
    {
        coll_data->coll_mask |= MPCOLL_MASK_RWALL;
    }
    return is_collide_rwall;
}

void func_ovl2_800DBF58(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C;
    s32 i;
    s32 temp_v0;
    s32 j;
    f32 sp6C;
    s32 wall_line_id;
    f32 sp64;

    func_ovl2_800D9590();

    for (i = 0; i < D_ovl2_80130DE0; i++)
    {
        wall_line_id = D_ovl2_80130DE8[i];

        func_ovl2_800F4650(wall_line_id, &sp94);

        if (sp94.y < (translate->y + object_coll->bottom))
        {
            if ((sp94.x < D_ovl2_80130DFC) && (func_ovl2_800F4194(wall_line_id, &sp94, NULL, &sp6C, &sp88) != 0))
            {
                func_ovl2_800D95A4(sp94.x, wall_line_id, sp6C, &sp88);
            }
        }
        else
        {
            func_ovl2_800F4670(wall_line_id, &sp94);

            if ((translate->y + object_coll->top) < sp94.y)
            {
                if ((sp94.x < D_ovl2_80130DFC) && (func_ovl2_800F4194(wall_line_id, &sp94, NULL, &sp6C, &sp88) != 0))
                {
                    func_ovl2_800D95A4(sp94.x, wall_line_id, sp6C, &sp88);
                }
            }
            else
            {
                sp94.x = translate->x;
                sp94.y = translate->y + object_coll->bottom;

                if (func_ovl2_800F4194(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) < D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                sp94.x = translate->x + object_coll->width;
                sp94.y = translate->y + object_coll->center;

                if (func_ovl2_800F4194(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) < D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                sp94.x = translate->x;
                sp94.y = translate->y + object_coll->top;

                if (func_ovl2_800F4194(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) < D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                temp_v0 = func_ovl2_800FA518(wall_line_id);

                for (j = 0; j < temp_v0; j++)
                {
                    func_ovl2_800FA5E8(wall_line_id, j, &sp7C);

                    if ((translate->y + object_coll->bottom) <= sp7C.y)
                    {
                        if (sp7C.y <= (translate->y + object_coll->center))
                        {
                            sp64 = sp7C.x - (((sp7C.y - (translate->y + object_coll->bottom)) * object_coll->width) / (object_coll->center - object_coll->bottom));

                            goto block_26;
                        }
                    }
                    if ((translate->y + object_coll->center) <= sp7C.y)
                    {
                        if (sp7C.y <= (translate->y + object_coll->top))
                        {
                            sp64 = sp7C.x - ((((translate->y + object_coll->top) - sp7C.y) * object_coll->width) / (object_coll->top - object_coll->center));

                        block_26:
                            if ((sp64 < D_ovl2_80130DFC) && (func_ovl2_800F4194(wall_line_id, &sp7C, NULL, &sp6C, &sp88) != 0))
                            {
                                func_ovl2_800D95A4(sp64, wall_line_id, sp6C, &sp88);
                            }
                        }
                    }
                }
            }
        }
        continue;
    }
    func_ovl2_800D95E0(&sp64, &coll_data->rwall_line_id, &coll_data->rwall_material, &coll_data->rwall_angle);

    if (sp64 < translate->x)
    {
        translate->x = sp64;

        coll_data->coll_type |= MPCOLL_MASK_RWALL;
    }
    coll_data->unk_0x58 |= MPCOLL_MASK_RWALL;
}

bool32 func_ovl2_800DC3C8(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    ObjectColl *p_object_coll = coll_data->p_object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f *pcurr = &coll_data->pos_curr;
    Vec3f sp54;
    Vec3f sp48;
    bool32 is_collide_lwall;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    u32 sp34;
    s32 var_v0;

    is_collide_lwall = FALSE;

    coll_data->unk_0x58 &= ~(MPCOLL_MASK_LWALL);
    coll_data->coll_type &= ~(MPCOLL_MASK_LWALL);

    func_ovl2_800D9510();

    sp54.x = pcurr->x - p_object_coll->width;
    sp54.y = pcurr->y + p_object_coll->center;
    sp48.x = translate->x - object_coll->width;
    sp48.y = translate->y + object_coll->center;

                             var_v0

                                =

            (coll_data->wall_flag != D_ovl2_80131398)

                                ?

    func_ovl2_800F769C(&sp54, &sp48, NULL, &sp40, NULL, NULL)

                                :

    func_ovl2_800F6B58(&sp54, &sp48, NULL, &sp40, NULL, NULL);

    if (var_v0 != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_lwall = TRUE;
    }
    sp54.x = pcurr->x;
    sp54.y = pcurr->y + p_object_coll->bottom;
    sp48.x = translate->x;
    sp48.y = translate->y + object_coll->bottom;

                         var_v0

                            =

            (coll_data->wall_flag != D_ovl2_80131398)

                            ?

    func_ovl2_800F769C(&sp54, &sp48, NULL, &sp40, NULL, NULL)

                            :

    func_ovl2_800F6B58(&sp54, &sp48, NULL, &sp40, NULL, NULL);

    if (var_v0 != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_lwall = TRUE;
    }
    sp54.x = pcurr->x;
    sp54.y = pcurr->y + p_object_coll->top;
    sp48.x = translate->x;
    sp48.y = translate->y + object_coll->top;

                     var_v0

                        =

    (coll_data->wall_flag != D_ovl2_80131398)

                        ?

    func_ovl2_800F769C(&sp54, &sp48, NULL, &sp40, NULL, NULL)

                        :

    func_ovl2_800F6B58(&sp54, &sp48, NULL, &sp40, NULL, NULL);

    if (var_v0 != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_lwall = TRUE;
    }
    sp54.x = translate->x;
    sp54.y = translate->y + object_coll->bottom;
    sp48.x = translate->x - object_coll->width;
    sp48.y = translate->y + object_coll->center;

    if (func_ovl2_800F6B58(&sp54, &sp48, NULL, &sp40, NULL, NULL) != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_lwall = TRUE;
    }
    sp54.x = translate->x;
    sp54.y = translate->y + object_coll->top;
    sp48.x = translate->x - object_coll->width;
    sp48.y = translate->y + object_coll->center;

    if (func_ovl2_800F6B58(&sp54, &sp48, NULL, &sp40, NULL, NULL) != 0)
    {
        func_ovl2_800D951C(sp40);

        is_collide_lwall = TRUE;
    }
    sp54.x = pcurr->x - p_object_coll->width;
    sp54.y = pcurr->y + p_object_coll->center;
    sp48.x = translate->x - object_coll->width;
    sp48.y = translate->y + object_coll->center;

                     var_v0

                        =

    (coll_data->wall_flag != D_ovl2_80131398)

                        ?

    func_ovl2_800F64D4(&sp54, &sp48, NULL, &sp40, NULL, NULL)

                        :

    func_ovl2_800F5E90(&sp54, &sp48, NULL, &sp40, NULL, NULL);

    if (var_v0 != 0)
    {
        sp38 = func_ovl2_800FAAE4(sp40);

        if (sp38 != -1)
        {
            if (func_ovl2_800FA8A4(sp38) == 2)
            {
                sp54.x = pcurr->x;
                sp54.y = pcurr->y + p_object_coll->top;
                sp48.x = translate->x;
                sp48.y = translate->y + object_coll->top;

                                     var_v0

                                        =

                    (coll_data->wall_flag != D_ovl2_80131398)

                                        ?

                func_ovl2_800F64D4(&sp54, &sp48, NULL, &sp3C, NULL, NULL)

                                        :

                func_ovl2_800F5E90(&sp54, &sp48, NULL, &sp3C, NULL, NULL);

                if ((var_v0 == 0) || (sp40 != sp3C))
                {
                    sp54.x = translate->x;
                    sp54.y = translate->y + object_coll->top;
                    sp48.x = translate->x - object_coll->width;
                    sp48.y = translate->y + object_coll->center;

                    if ((func_ovl2_800F5E90(&sp54, &sp48, 0, &sp3C, 0, 0) == 0) || (sp40 != sp3C))
                    {
                        func_ovl2_800D951C(sp38);

                        is_collide_lwall = TRUE;
                    }
                }
            }
        }
    }
    sp54.x = pcurr->x - p_object_coll->width;
    sp54.y = pcurr->y + p_object_coll->center;
    sp48.x = translate->x - object_coll->width;
    sp48.y = translate->y + object_coll->center;

                         var_v0

                            =

        (coll_data->wall_flag != D_ovl2_80131398)

                            ?

    func_ovl2_800F521C(&sp54, &sp48, NULL, &sp40, &sp34, NULL)

                            :

    func_ovl2_800F4BD8(&sp54, &sp48, NULL, &sp40, &sp34, NULL);

    if ((var_v0 != 0) && !(sp34 & 0x4000))
    {
        sp38 = func_ovl2_800FA964(sp40);

        if (sp38 != -1)
        {
            if (func_ovl2_800FA8A4(sp38) == 2)
            {
                sp54.x = pcurr->x;
                sp54.y = pcurr->y + p_object_coll->bottom;
                sp48.x = translate->x;
                sp48.y = translate->y + object_coll->bottom;

                                 var_v0

                                    =

                (coll_data->wall_flag != D_ovl2_80131398)

                                    ?

                func_ovl2_800F521C(&sp54, &sp48, NULL, &sp3C, NULL, NULL)

                                    :

                func_ovl2_800F4BD8(&sp54, &sp48, NULL, &sp3C, NULL, NULL);

                if ((var_v0 == 0) || (sp40 != sp3C))
                {
                    sp54.x = translate->x;
                    sp54.y = translate->y + object_coll->bottom;
                    sp48.x = translate->x - object_coll->width;
                    sp48.y = translate->y + object_coll->center;

                    if ((func_ovl2_800F4BD8(&sp54, &sp48, NULL, &sp3C, NULL, NULL) == 0) || (sp40 != sp3C))
                    {
                        func_ovl2_800D951C(sp38);

                        is_collide_lwall = TRUE;
                    }
                }
            }
        }
    }
    if (is_collide_lwall != FALSE)
    {
        coll_data->coll_mask |= MPCOLL_MASK_LWALL;
    }
    return is_collide_lwall;
}

void func_ovl2_800DCAE8(Coll_Data *coll_data)
{
    ObjectColl *object_coll = &coll_data->object_coll;
    Vec3f *translate = coll_data->p_translate;
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C;
    s32 i;
    s32 temp_v0;
    s32 j;
    f32 sp6C;
    s32 wall_line_id;
    f32 sp64;

    func_ovl2_800D957C();

    for (i = 0; i < D_ovl2_80130DE0; i++)
    {
        wall_line_id = D_ovl2_80130DE8[i];

        func_ovl2_800F4690(wall_line_id, &sp94);

        if (sp94.y < (translate->y + object_coll->bottom))
        {
            if ((D_ovl2_80130DFC < sp94.x) && (func_ovl2_800F41C0(wall_line_id, &sp94, NULL, &sp6C, &sp88) != 0))
            {
                func_ovl2_800D95A4(sp94.x, wall_line_id, sp6C, &sp88);
            }
        }
        else
        {
            func_ovl2_800F46B0(wall_line_id, &sp94);

            if ((translate->y + object_coll->top) < sp94.y)
            {
                if ((D_ovl2_80130DFC < sp94.x) && (func_ovl2_800F41C0(wall_line_id, &sp94, NULL, &sp6C, &sp88) != 0))
                {
                    func_ovl2_800D95A4(sp94.x, wall_line_id, sp6C, &sp88);
                }
            }
            else
            {
                sp94.x = translate->x;
                sp94.y = translate->y + object_coll->bottom;

                if (func_ovl2_800F41C0(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) > D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                sp94.x = translate->x - object_coll->width;
                sp94.y = translate->y + object_coll->center;

                if (func_ovl2_800F41C0(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) > D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                sp94.x = translate->x;
                sp94.y = translate->y + object_coll->top;

                if (func_ovl2_800F41C0(wall_line_id, &sp94, &sp64, &sp6C, &sp88) != 0)
                {
                    if ((translate->x + sp64) > D_ovl2_80130DFC)
                    {
                        func_ovl2_800D95A4((translate->x + sp64), wall_line_id, sp6C, &sp88);
                    }
                }
                temp_v0 = func_ovl2_800FA518(wall_line_id);

                for (j = 0; j < temp_v0; j++)
                {
                    func_ovl2_800FA5E8(wall_line_id, j, &sp7C);

                    if ((translate->y + object_coll->bottom) <= sp7C.y)
                    {
                        if (sp7C.y <= (translate->y + object_coll->center))
                        {
                            sp64 = sp7C.x + (((sp7C.y - (translate->y + object_coll->bottom)) * object_coll->width) / (object_coll->center - object_coll->bottom));

                            goto block_26;
                        }
                    }
                    if ((translate->y + object_coll->center) <= sp7C.y)
                    {
                        if (sp7C.y <= (translate->y + object_coll->top))
                        {
                            sp64 = sp7C.x + ((((translate->y + object_coll->top) - sp7C.y) * object_coll->width) / (object_coll->top - object_coll->center));

                        block_26:
                            if ((D_ovl2_80130DFC < sp64) && (func_ovl2_800F41C0(wall_line_id, &sp7C, NULL, &sp6C, &sp88) != 0))
                            {
                                func_ovl2_800D95A4(sp64, wall_line_id, sp6C, &sp88);
                            }
                        }
                    }
                }
            }
        }
        continue;
    }
    func_ovl2_800D95E0(&sp64, &coll_data->lwall_line_id, &coll_data->lwall_material, &coll_data->lwall_angle);

    if (translate->x < sp64)
    {
        translate->x = sp64;

        coll_data->coll_type |= MPCOLL_MASK_LWALL;
    }
    coll_data->unk_0x58 |= MPCOLL_MASK_LWALL;
}