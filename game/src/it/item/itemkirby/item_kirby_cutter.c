#include "item.h"
#include "fighter.h"

bool32 jtgt_ovl3_8016BC50(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

        return TRUE;
    }
    else if (ip->ground_or_air == ground)
    {
        DObjGetStruct(item_gobj)->rotate.z = -atan2f(ip->coll_data.ground_angle.x, ip->coll_data.ground_angle.y);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016BCC8(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->ground_or_air == air)
    {
        if (func_ovl3_80167B58(item_gobj) == TRUE)
        {
            func_ovl3_80167E78(ip);
        }
    }
    else if (func_ovl3_8016796C(item_gobj) == FALSE)
    {
        func_ovl3_80167E9C(ip);

        ip->phys_info.vel.x = cosf(DObjGetStruct(item_gobj)->rotate.z) * ip->phys_info.vel_ground;
        ip->phys_info.vel.y = __sinf(DObjGetStruct(item_gobj)->rotate.z) * ip->phys_info.vel_ground;

        if (DObjGetStruct(item_gobj)->rotate.y < 0.0F)
        {
            ip->phys_info.vel.x = -ip->phys_info.vel.x;
            ip->phys_info.vel.y = -ip->phys_info.vel.y;
        }
    }

    if (ip->coll_data.coll_mask & (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016BDD0(GObj *item_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(item_gobj)->translate);

    return FALSE;
}

bool32 jtgt_ovl3_8016BE08(GObj *item_gobj)
{
    return FALSE;
}

bool32 jtgt_ovl3_8016BE14(GObj *item_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(item_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_8016BE4C(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    ip->lifetime = ITFINALCUTTER_LIFETIME;

    func_ovl3_801680EC(ip, fp);
    func_ovl3_80167FA0(item_gobj);

    return FALSE;
}

extern ItemSpawnData Item_FinalCutter_Desc;

GObj* func_ovl3_8016BE8C(GObj *fighter_gobj, Vec3f *pos)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_FinalCutter_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = itGetStruct(item_gobj);

    ip->lifetime = ITFINALCUTTER_LIFETIME;

    ip->phys_info.vel.x = ip->lr * ITFINALCUTTER_VEL;

    if (func_ovl2_800F3DD8(fp->coll_data.ground_line_id, pos, NULL, NULL, &ip->coll_data.ground_angle) != FALSE)
    {
        ip->coll_data.ground_line_id = fp->coll_data.ground_line_id;

        func_ovl3_80167E78(ip);
    }
    func_ovl3_80167FA0(item_gobj);

    return item_gobj;
}