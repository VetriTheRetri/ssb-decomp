#include "item.h"
#include "fighter.h"

bool32 jtgt_ovl3_801688D0(GObj *item_gobj)
{
    if (DObjGetStruct(item_gobj)->scale.x < 53.333332F)
    {
        DObjGetStruct(item_gobj)->scale.x += 5.3333335F;

        if (53.333332F < DObjGetStruct(item_gobj)->scale.x)
        {
            DObjGetStruct(item_gobj)->scale.x = (f32)53.333332F;
        }
    }
    return FALSE;
}

bool32 jtgt_ovl3_80168924(GObj *item_gobj)
{
    if (func_ovl3_80167C04(item_gobj) != FALSE)
    {
        func_ovl2_80103320(&DObjGetStruct(item_gobj)->translate);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80168964(GObj *item_gobj)
{
    func_ovl2_80103320(&DObjGetStruct(item_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_8016898C(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    func_ovl2_80103320(&DObjGetStruct(item_gobj)->translate);

    return FALSE;
}

bool32 jtgt_ovl3_80168A14(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    return FALSE;
}

extern ItemSpawnData Item_Blaster_Desc;

GObj* func_ovl3_80168A74(GObj *fighter_gobj, Vec3f *pos)
{
    Item_Struct *ip;
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_Blaster_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = itGetStruct(item_gobj);

    ip->phys_info.vel.x = ip->lr * ITBLASTER_VEL_X;

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);

    func_ovl2_80103320(pos);

    return item_gobj;
}