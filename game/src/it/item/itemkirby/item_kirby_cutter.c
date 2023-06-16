#include "item.h"
#include "fighter.h"

bool32 jtgt_ovl3_8016BC50(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        return TRUE;
    }
    else if (ip->ground_or_air == ground)
    {
        DObjGetStruct(weapon_gobj)->rotate.z = -atan2f(ip->coll_data.ground_angle.x, ip->coll_data.ground_angle.y);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016BCC8(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (ip->ground_or_air == air)
    {
        if (func_ovl3_80167B58(weapon_gobj) == TRUE)
        {
            wpMap_SetGround(ip);
        }
    }
    else if (func_ovl3_8016796C(weapon_gobj) == FALSE)
    {
        wpMap_SetAir(ip);

        ip->phys_info.vel.x = cosf(DObjGetStruct(weapon_gobj)->rotate.z) * ip->phys_info.vel_ground;
        ip->phys_info.vel.y = __sinf(DObjGetStruct(weapon_gobj)->rotate.z) * ip->phys_info.vel_ground;

        if (DObjGetStruct(weapon_gobj)->rotate.y < 0.0F)
        {
            ip->phys_info.vel.x = -ip->phys_info.vel.x;
            ip->phys_info.vel.y = -ip->phys_info.vel.y;
        }
    }

    if (ip->coll_data.coll_mask & (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016BDD0(GObj *weapon_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

    return FALSE;
}

bool32 jtgt_ovl3_8016BE08(GObj *weapon_gobj)
{
    return FALSE;
}

bool32 jtgt_ovl3_8016BE14(GObj *weapon_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_8016BE4C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    ip->lifetime = ITFINALCUTTER_LIFETIME;

    wpMain_ReflectorInvertLR(ip, fp);
    func_ovl3_80167FA0(weapon_gobj);

    return FALSE;
}

extern WeaponSpawnData Item_FinalCutter_Desc;

GObj* func_ovl3_8016BE8C(GObj *fighter_gobj, Vec3f *pos)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_FinalCutter_Desc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->lifetime = ITFINALCUTTER_LIFETIME;

    ip->phys_info.vel.x = ip->lr * ITFINALCUTTER_VEL;

    if (func_ovl2_800F3DD8(fp->coll_data.ground_line_id, pos, NULL, NULL, &ip->coll_data.ground_angle) != FALSE)
    {
        ip->coll_data.ground_line_id = fp->coll_data.ground_line_id;

        wpMap_SetGround(ip);
    }
    func_ovl3_80167FA0(weapon_gobj);

    return weapon_gobj;
}