#include "item.h"
#include "fighter.h"

bool32 func_ovl3_8016DC00(GObj *item_gobj)
{
    if (wpMain_DecLifeCheckExpire(wpGetStruct(item_gobj)) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8016DC2C(GObj *item_gobj)
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);

    ip->item_hit.hit_sfx = 1;

    ip->item_hit.flags_0x48_b1 = TRUE;
    ip->item_hit.can_hop = FALSE;
    ip->item_hit.can_reflect = FALSE;

    ip->item_hit.element = 1;

    ip->lifetime = ITYUBIBULLET_EXPLODE_LIFETIME;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_hit.size = ITYUBIBULLET_EXPLODE_SIZE;

    DObjGetStruct(item_gobj)->display_list = NULL;

    ip->proc_update = func_ovl3_8016DC00;
    ip->proc_map = NULL;
    ip->proc_hit = NULL;
    ip->proc_shield = NULL;
    ip->proc_hop = NULL;
    ip->proc_setoff = NULL;
    ip->proc_reflector = NULL;
}

bool32 jtgt_ovl3_8016DCB0(GObj *item_gobj)
{
    if (func_ovl3_80167C04(item_gobj) != FALSE)
    {
        func_ovl3_8016DC2C(item_gobj);
        func_800269C0(0U);
        func_ovl2_801005C8(&DObjGetStruct(item_gobj)->translate);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016DD2C(GObj *item_gobj)
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    func_ovl3_80168428(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8016DD7C(GObj *item_gobj)
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);
    func_ovl3_80168428(item_gobj);

    return FALSE;
}

extern ItemSpawnData Item_YubiBullet_Easy;

GObj *func_ovl3_8016DDB4(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *item_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_YubiBullet_Easy, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(item_gobj);

    ip->phys_info.vel.x = ITYUBIBULLET_VEL_X * ip->lr;
    ip->phys_info.vel.y = ITYUBIBULLET_VEL_Y;

    func_ovl3_80168428(item_gobj);

    return item_gobj;
}

extern ItemSpawnData Item_YubiBullet_Hard;

GObj *func_ovl3_8016DE28(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *item_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_YubiBullet_Hard, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(item_gobj);

    ip->phys_info.vel.x = ITYUBIBULLET_VEL_X * ip->lr;
    ip->phys_info.vel.y = ITYUBIBULLET_VEL_Y;

    func_ovl3_80168428(item_gobj);

    return item_gobj;
}