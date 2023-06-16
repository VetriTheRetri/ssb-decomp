#include "item.h"
#include "fighter.h"

bool32 jtgt_ovl3_801688D0(GObj *weapon_gobj)
{
    if (DObjGetStruct(weapon_gobj)->scale.x < 53.333332F)
    {
        DObjGetStruct(weapon_gobj)->scale.x += 5.3333335F;

        if (53.333332F < DObjGetStruct(weapon_gobj)->scale.x)
        {
            DObjGetStruct(weapon_gobj)->scale.x = (f32)53.333332F;
        }
    }
    return FALSE;
}

bool32 jtgt_ovl3_80168924(GObj *weapon_gobj)
{
    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        func_ovl2_80103320(&DObjGetStruct(weapon_gobj)->translate);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80168964(GObj *weapon_gobj)
{
    func_ovl2_80103320(&DObjGetStruct(weapon_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_8016898C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    func_ovl2_80103320(&DObjGetStruct(weapon_gobj)->translate);

    return FALSE;
}

bool32 jtgt_ovl3_80168A14(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    wpMain_ReflectorInvertLR(ip, fp);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    return FALSE;
}

extern WeaponSpawnData Item_Blaster_Desc;

GObj* func_ovl3_80168A74(GObj *fighter_gobj, Vec3f *pos)
{
    Weapon_Struct *ip;
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_Blaster_Desc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->phys_info.vel.x = ip->lr * ITBLASTER_VEL_X;

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);

    func_ovl2_80103320(pos);

    return weapon_gobj;
}