#include "item.h"

bool32 func_ovl3_80167C38(GObj *item_gobj, u32 check_flags, f32 mod_vel, Vec3f *pos)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Coll_Data *coll_data = &ip->coll_data;

    bool32 return_bool = FALSE;

    Vec3f mod_pos, *translate = &JObjGetStruct(item_gobj)->translate;

    u16 coll_flags = (ip->coll_data.unk_0x54 ^ ip->coll_data.unk_0x56) & ip->coll_data.unk_0x56 & (MPCOLL_MASK_GROUND | MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL);

    u32 unused;

    if (coll_flags & check_flags & MPCOLL_MASK_RWALL)
    {
        if (func_ovl0_800C7C0C(&ip->phys_info.vel, &coll_data->rwall_angle) < 0.0F)
        {
            func_ovl0_800C7B08(&ip->phys_info.vel, &coll_data->rwall_angle);

            return_bool = TRUE;

            mod_pos.x = translate->x + coll_data->object_coll.width;
            mod_pos.y = translate->y + coll_data->object_coll.center;
        }
    }

    if (coll_flags & check_flags & MPCOLL_MASK_LWALL)
    {
        if (func_ovl0_800C7C0C(&ip->phys_info.vel, &coll_data->lwall_angle) < 0.0F)
        {
            return_bool = TRUE;

            func_ovl0_800C7B08(&ip->phys_info.vel, &coll_data->lwall_angle);

            mod_pos.x = translate->x - coll_data->object_coll.width;
            mod_pos.y = translate->y + coll_data->object_coll.center;
        }
    }

    if (coll_flags & check_flags & MPCOLL_MASK_CEIL)
    {
        if (func_ovl0_800C7C0C(&ip->phys_info.vel, &coll_data->ceil_angle) < 0.0F)
        {
            return_bool = TRUE;

            func_ovl0_800C7B08(&ip->phys_info.vel, &coll_data->ceil_angle);

            mod_pos.x = translate->x;
            mod_pos.y = translate->y + coll_data->object_coll.top;
        }
    }

    if (coll_flags & check_flags & MPCOLL_MASK_GROUND)
    {
        if (func_ovl0_800C7C0C(&ip->phys_info.vel, &coll_data->ground_angle) < 0.0F)
        {
            return_bool = TRUE;

            func_ovl0_800C7B08(&ip->phys_info.vel, &coll_data->ground_angle);

            mod_pos.x = translate->x;
            mod_pos.y = translate->y + coll_data->object_coll.bottom;
        }
    }
    if (return_bool != FALSE)
    {
        func_ovl0_800C7AE0(&ip->phys_info.vel, mod_vel);

        if (pos != NULL)
        {
            pos->x = mod_pos.x;
            pos->y = mod_pos.y;
            pos->z = translate->z;
        }
    }
    return return_bool;
}