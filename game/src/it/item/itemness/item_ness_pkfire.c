#include "item.h"
#include "fighter.h"



bool32 jtgt_ovl3_8016AA40(GObj *item_gobj)
{
    if (func_ovl3_80167FE8(ItemGetStruct(item_gobj)) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016AA88(GObj *item_gobj)
{
    if (func_ovl3_80167C04(item_gobj) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016AACC(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Vec3f vel;
    Vec3f pos;

    pos.x = 0.0F;
    pos.y = 0.0F;
    pos.z = 0.0F;

    vel = ip->phys_info.vel;

    vec3f_normalize(&vel);

    vel.x = (vel.x * ITPKFIRE_VEL_MUL) + DObjGetStruct(item_gobj)->translate.x;
    vel.y = (vel.y * ITPKFIRE_VEL_MUL) + DObjGetStruct(item_gobj)->translate.y;
    vel.z = (vel.z * ITPKFIRE_VEL_MUL) + DObjGetStruct(item_gobj)->translate.z;

    func_ovl3_80185824(item_gobj, &vel, &pos);

    return TRUE;
}

bool32 jtgt_ovl3_8016AB84(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    func_ovl3_80167F68(item_gobj);

    DObjGetStruct(item_gobj)->rotate.z *= -1.0F;

    return FALSE;
}

bool32 jtgt_ovl3_8016ABF0(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    ip->lifetime = ITPKFIRE_LIFETIME;

    func_ovl3_801680EC(ip, fp);
    func_ovl3_80167F68(item_gobj);

    DObjGetStruct(item_gobj)->rotate.z *= -1.0F;

    return FALSE;
}

bool32 jtgt_ovl3_8016AC4C(GObj *item_gobj)
{
    func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

    return TRUE;
}

extern ItemSpawnDesc Item_PKFire_Desc;

GObj* func_ovl3_8016AC78(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel, f32 angle)
{
    s32 unused;
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_PKFire_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->lifetime = ITPKFIRE_LIFETIME;

    ip->phys_info.vel = *vel;

    func_ovl3_80167F68(item_gobj);

    DObjGetStruct(item_gobj)->rotate.z = (angle + HALF_PI32) * ip->lr;

    return item_gobj;
}