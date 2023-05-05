#include "mpcoll.h"
#include "obj.h"

extern s32 D_ovl2_80130DE0;
extern s32 D_ovl2_80130DE8[5];
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

        if (func_ovl2_800F4BD8(&sp44, &sp38, &coll_data->ground_to_air_pos_last, 0, 0, 0) != 0)
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
