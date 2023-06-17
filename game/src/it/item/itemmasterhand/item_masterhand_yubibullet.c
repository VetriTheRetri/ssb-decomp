#include "item.h"
#include "fighter.h"

bool32 func_ovl3_8016DC00(GObj *weapon_gobj)
{
    if (wpMain_DecLifeCheckExpire(wpGetStruct(weapon_gobj)) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8016DC2C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    ip->item_hit.hit_sfx = 1;

    ip->item_hit.can_rehit_hurt = TRUE;
    ip->item_hit.can_hop = FALSE;
    ip->item_hit.can_reflect = FALSE;

    ip->item_hit.element = 1;

    ip->lifetime = ITYUBIBULLET_EXPLODE_LIFETIME;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_hit.size = ITYUBIBULLET_EXPLODE_SIZE;

    DObjGetStruct(weapon_gobj)->display_list = NULL;

    ip->proc_update = func_ovl3_8016DC00;
    ip->proc_map = NULL;
    ip->proc_hit = NULL;
    ip->proc_shield = NULL;
    ip->proc_hop = NULL;
    ip->proc_setoff = NULL;
    ip->proc_reflector = NULL;
}

bool32 jtgt_ovl3_8016DCB0(GObj *weapon_gobj)
{
    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        func_ovl3_8016DC2C(weapon_gobj);
        func_800269C0(0U);
        func_ovl2_801005C8(&DObjGetStruct(weapon_gobj)->translate);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016DD2C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    func_ovl3_80168428(weapon_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8016DD7C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    wpMain_ReflectorInvertLR(ip, fp);
    func_ovl3_80168428(weapon_gobj);

    return FALSE;
}

extern WeaponSpawnData Item_YubiBullet_Easy;

GObj *func_ovl3_8016DDB4(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_YubiBullet_Easy, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->phys_info.vel.x = ITYUBIBULLET_VEL_X * ip->lr;
    ip->phys_info.vel.y = ITYUBIBULLET_VEL_Y;

    func_ovl3_80168428(weapon_gobj);

    return weapon_gobj;
}

extern WeaponSpawnData Item_YubiBullet_Hard;

GObj *func_ovl3_8016DE28(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_YubiBullet_Hard, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->phys_info.vel.x = ITYUBIBULLET_VEL_X * ip->lr;
    ip->phys_info.vel.y = ITYUBIBULLET_VEL_Y;

    func_ovl3_80168428(weapon_gobj);

    return weapon_gobj;
}