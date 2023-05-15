#include "article.h"
#include "gmmatch.h"

bool32 func_ovl3_80173480(Coll_Data *coll_data, s32 arg1, s32 arg2)
{
    s32 ground_line_id = coll_data->ground_line_id;
    bool32 is_collide_ground = FALSE;

    if (func_ovl2_800DA294(coll_data) != FALSE)
    {
        func_ovl2_800DA658(coll_data);
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DAAA8(coll_data) != FALSE)
    {
        func_ovl2_800DAE6C(coll_data);
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DB2BC(coll_data) != FALSE)
    {
        if (coll_data->coll_type & MPCOLL_MASK_GROUND)
        {
            func_ovl2_800D9F84(coll_data);
            is_collide_ground = TRUE;
        }
    }
    else
    {
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DB474(coll_data, ground_line_id) != FALSE)
    {
        func_ovl2_800DD59C(coll_data);

        if (coll_data->coll_type & MPCOLL_MASK_GROUND)
        {
            func_ovl2_800D9F84(coll_data);
            is_collide_ground = TRUE;
        }
        coll_data->unk_0x64 = FALSE;
    }
    return is_collide_ground;
}

bool32 func_ovl3_8017356C(GObj *article_gobj)
{
    return func_ovl2_800DA034(&ArticleGetStruct(article_gobj)->coll_data, func_ovl3_80173480, article_gobj, FALSE);
}

bool32 func_ovl3_801735A0(GObj *article_gobj, void (*cb_coll)(GObj*))
{
    if (func_ovl3_8017356C(article_gobj) == FALSE)
    {
        cb_coll(article_gobj);

        return FALSE;
    }
    else return TRUE;
}

bool32 func_ovl3_801735E0(Coll_Data *coll_data, GObj *article_gobj, s32 arg2)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (func_ovl2_800DB838(coll_data) != FALSE)
    {
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DC3C8(coll_data) != FALSE)
    {
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DCF58(coll_data) != FALSE)
    {
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DD578(coll_data) != FALSE)
    {
        coll_data->unk_0x64 = TRUE;

        func_800269C0(0x2EU);

        ap->rotate_speed = 0.0F;
        joint->rotate.z = 0.0F;
    }
    return coll_data->unk_0x64;
}

bool32 func_ovl3_80173680(GObj *article_gobj)
{
    return func_ovl2_800DA034(&ArticleGetStruct(article_gobj)->coll_data, func_ovl3_801735E0, article_gobj, FALSE);
}

bool32 func_ovl3_801736B4(Coll_Data *coll_data, GObj *article_gobj, u32 coll_flags)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (func_ovl2_800DB838(coll_data) != FALSE)
    {
        func_ovl2_800DBF58(coll_data);
    }
    if (func_ovl2_800DC3C8(coll_data) != FALSE)
    {
        func_ovl2_800DCAE8(coll_data);
    }
    if (func_ovl2_800DCF58(coll_data) != FALSE)
    {
        func_ovl2_800DD160(coll_data);

        if (coll_data->coll_type & MPCOLL_MASK_CEIL)
        {
            func_ovl2_800D99B8(coll_data);
        }
    }
    if (func_ovl2_800DD578(coll_data) != FALSE)
    {
        func_ovl2_800DD59C(coll_data);

        if (coll_data->coll_type & MPCOLL_MASK_GROUND)
        {
            func_ovl2_800D9F84(coll_data);
            func_800269C0(0x2EU);

            ap->rotate_speed = 0.0F;

            joint->rotate.z = 0.0F;

            coll_data->unk_0x64 = TRUE;
        }
    }
    if (coll_data->coll_mask & coll_flags)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_801737B8(GObj *article_gobj, bool32 flag)
{
    return func_ovl2_800DA034(&ArticleGetStruct(article_gobj)->coll_data, func_ovl3_801736B4, article_gobj, flag);
}

bool32 func_ovl3_801737EC(GObj *article_gobj, u32 check_flags, f32 mod_vel, Vec3f *pos) // Modify velocity based on angle of collision
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Coll_Data *coll_data = &ap->coll_data;
    Vec3f *translate = &DObjGetStruct(article_gobj)->translate;
    Vec3f mod_pos;
    bool32 return_bool = FALSE;
    u16 coll_flags = (ap->coll_data.coll_mask_prev ^ ap->coll_data.coll_mask) & ap->coll_data.coll_mask & MPCOLL_MASK_MAIN_ALL;

    if (coll_flags & check_flags & MPCOLL_MASK_RWALL)
    {
        if (func_ovl0_800C7C0C(&ap->phys_info.vel, &coll_data->rwall_angle) < 0.0F)
        {
            func_ovl0_800C7B08(&ap->phys_info.vel, &coll_data->rwall_angle);

            mod_pos.x = translate->x + coll_data->object_coll.width;
            mod_pos.y = translate->y + coll_data->object_coll.center;

            return_bool = TRUE;

            func_800269C0(0x2EU);
        }
    }

    if (coll_flags & check_flags & MPCOLL_MASK_LWALL)
    {
        if (func_ovl0_800C7C0C(&ap->phys_info.vel, &coll_data->lwall_angle) < 0.0F)
        {
            func_ovl0_800C7B08(&ap->phys_info.vel, &coll_data->lwall_angle);

            mod_pos.x = translate->x - coll_data->object_coll.width;
            mod_pos.y = translate->y + coll_data->object_coll.center;

            return_bool = TRUE;

            func_800269C0(0x2EU);
        }
    }

    if (coll_flags & check_flags & MPCOLL_MASK_CEIL)
    {
        if (func_ovl0_800C7C0C(&ap->phys_info.vel, &coll_data->ceil_angle) < 0.0F)
        {
            func_ovl0_800C7B08(&ap->phys_info.vel, &coll_data->ceil_angle);

            mod_pos.x = translate->x;
            mod_pos.y = translate->y + coll_data->object_coll.top;

            return_bool = TRUE;
        }
    }

    if (coll_flags & check_flags & MPCOLL_MASK_GROUND)
    {
        if (func_ovl0_800C7C0C(&ap->phys_info.vel, &coll_data->ground_angle) < 0.0F)
        {
            func_ovl0_800C7B08(&ap->phys_info.vel, &coll_data->ground_angle);

            mod_pos.x = translate->x;
            mod_pos.y = translate->y + coll_data->object_coll.bottom;

            return_bool = TRUE;

            func_800269C0(0x2EU);
        }
    }
    if (return_bool != FALSE)
    {
        func_ovl0_800C7AE0(&ap->phys_info.vel, mod_vel);

        if (pos != NULL)
        {
            pos->x = mod_pos.x;
            pos->y = mod_pos.y;
            pos->z = translate->z;
        }
    }
    return return_bool;
}

void func_ovl3_80173A48(Vec3f *arg0, Vec3f *arg1, f32 arg2)
{
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;

    temp_f0 = func_ovl0_800C7A84(arg0);

    if (temp_f0 != 0.0F)
    {
        temp_f0_2 = 1.0F / temp_f0;
        temp_f12 = temp_f0 * arg2 * 0.5F;

        func_ovl0_800C7B08(arg0, arg1);

        arg0->x *= temp_f0_2;
        arg0->y *= temp_f0_2;
        arg0->x += arg1->x;
        arg0->y += arg1->y;
        arg0->x *= temp_f12;
        arg0->y *= temp_f12;
    }
}

bool32 func_ovl3_80173B24(GObj *article_gobj, f32 mod_vel, f32 arg2, void (*cb)(GObj*))
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    s32 unused;
    bool32 is_collide_ground = func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND);

    if (func_ovl3_801737EC(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), mod_vel, NULL) != FALSE)
    {
        func_ovl3_80172508(article_gobj);
    }
    if (is_collide_ground != FALSE)
    {
        func_ovl3_80173A48(&ap->phys_info.vel, &ap->coll_data.ground_angle, arg2);
        func_ovl3_80172508(article_gobj);

        ap->times_landed++;

        if (ap->times_landed == 1)
        {
            if ((Match_Info->game_type != 3) && (ap->times_thrown != 0) && ((ap->times_thrown == 4) || (rand_u16_range(4) == 0)))
            {
                return TRUE;
            }
        }
        if ((ap->times_landed == 2) && (cb != NULL))
        {
            cb(article_gobj);
        }
    }
    return FALSE;
}

bool32 func_ovl3_80173C68(GObj *article_gobj, f32 mod_vel, f32 arg2, void (*cb)(GObj*))
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    s32 unused;
    bool32 is_collide_ground = func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND);

    if (func_ovl3_801737EC(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), mod_vel, NULL) != FALSE)
    {
        func_ovl3_80172508(article_gobj);
    }
    if (is_collide_ground != FALSE)
    {
        func_ovl0_800C7B08(&ap->phys_info.vel, &ap->coll_data.ground_angle);
        func_ovl0_800C7AE0(&ap->phys_info.vel, arg2);
        func_ovl3_80172508(article_gobj);

        if (cb != NULL)
        {
            cb(article_gobj);
        }
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80173D24(GObj *article_gobj, f32 mod_vel, f32 arg2, void (*cb)(GObj*))
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Coll_Data *coll_data = &ap->coll_data;
    bool32 is_collide_any = func_ovl3_801737B8(article_gobj, MPCOLL_MASK_MAIN_ALL);

    if (func_ovl3_801737EC(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), mod_vel, NULL) != FALSE)
    {
        func_ovl3_80172508(article_gobj);
    }
    if (coll_data->coll_mask & MPCOLL_MASK_GROUND)
    {
        func_ovl0_800C7B08(&ap->phys_info.vel, &coll_data->ground_angle);
        func_ovl0_800C7AE0(&ap->phys_info.vel, arg2);
        func_ovl3_80172508(article_gobj);
    }
    if (is_collide_any != FALSE)
    {
        if (cb != NULL)
        {
            cb(article_gobj);
        }
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80173DF4(GObj *article_gobj, f32 mod_vel)
{
    bool32 is_collide_ground = func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND);

    if (func_ovl3_801737EC(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), mod_vel, NULL) != FALSE)
    {
        func_ovl3_80172508(article_gobj);
    }
    if (is_collide_ground != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80173E58(GObj *article_gobj, void (*cb)(GObj*))
{
    if ((func_ovl3_801737B8(article_gobj, MPCOLL_MASK_MAIN_ALL) != FALSE) && (cb != NULL))
    {
        cb(article_gobj);
    }
    return FALSE;
}

bool32 func_ovl3_80173E9C(GObj *article_gobj, void (*cb)(GObj*)) // Unused
{
    if ((func_ovl3_801737B8(article_gobj, MPCOLL_MASK_MAIN_ALL) != FALSE))
    {
        if (cb != NULL)
        {
            cb(article_gobj);
        }
        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_80173EE8(GObj *article_gobj, f32 mod_vel, void (*cb)(GObj*))
{
    if ((func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE) && (cb != NULL))
    {
        cb(article_gobj);
    }
    if (func_ovl3_801737EC(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), mod_vel, NULL) != FALSE)
    {
        func_ovl3_80172508(article_gobj);
    }
    return FALSE;
}

void func_ovl3_80173F54(Article_Struct *ap)
{
    ap->ground_or_air = ground;
    ap->phys_info.vel_ground = ap->phys_info.vel.x * ap->lr;
}

void func_ovl3_80173F78(Article_Struct *ap)
{
    ap->ground_or_air = air;
}