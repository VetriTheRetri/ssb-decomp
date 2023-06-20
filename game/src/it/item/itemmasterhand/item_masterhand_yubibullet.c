#include "item.h"
#include "fighter.h"

extern void *D_ovl2_80131174;

wpCreateDesc wpMasterHand_YubiBulletSingle_WeaponDesc =
{
    1,                                      // Render flags?
    Wp_Kind_YubiBulletSingle,               // Weapon Kind
    &D_ovl2_80131174,                       // Pointer to character's loaded files?
    0x774,                                  // Offset of weapon attributes in loaded files
    0x1C,                                   // ???
    0,                                      // ???
    0,                                      // ???
    0,                                      // ???
    NULL,                                   // Proc Update
    wpMasterHand_YubiBullet_ProcMap,        // Proc Map
    wpMasterHand_YubiBullet_ProcHit,        // Proc Hit
    wpMasterHand_YubiBullet_ProcHit,        // Proc Shield
    wpMasterHand_YubiBullet_ProcHop,        // Proc Hop
    wpMasterHand_YubiBullet_ProcHit,        // Proc Set-Off
    wpMasterHand_YubiBullet_ProcReflector,  // Proc Reflector
    wpMasterHand_YubiBullet_ProcHit         // Proc Absorb
};

wpCreateDesc wpMasterHand_YubiBulletTriple_WeaponDesc =
{
    1,                                      // Render flags?
    Wp_Kind_YubiBulletTriple,               // Weapon Kind
    &D_ovl2_80131174,                       // Pointer to character's loaded files?
    0x7A8,                                  // Offset of weapon attributes in loaded files
    0x1C,                                   // ???
    0,                                      // ???
    0,                                      // ???
    0,                                      // ???
    NULL,                                   // Proc Update
    wpMasterHand_YubiBullet_ProcMap,        // Proc Map
    wpMasterHand_YubiBullet_ProcHit,        // Proc Hit
    wpMasterHand_YubiBullet_ProcHit,        // Proc Shield
    wpMasterHand_YubiBullet_ProcHop,        // Proc Hop
    wpMasterHand_YubiBullet_ProcHit,        // Proc Set-Off
    wpMasterHand_YubiBullet_ProcReflector,  // Proc Reflector
    wpMasterHand_YubiBullet_ProcHit         // Proc Absorb
};

// 0x8016DC00
bool32 wpMasterHand_YubiExplode_ProcUpdate(GObj *weapon_gobj)
{
    if (wpMain_DecLifeCheckExpire(wpGetStruct(weapon_gobj)) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
} 

// 0x8016DC2C
void wpMasterHand_YubiExplode_InitWeaponVars(GObj *weapon_gobj)
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);

    wp->item_hit.hit_sfx = 1;

    wp->item_hit.can_rehit_hurt = TRUE;
    wp->item_hit.can_hop = FALSE;
    wp->item_hit.can_reflect = FALSE;

    wp->item_hit.element = gmHitCollision_Element_Fire;

    wp->lifetime = ITYUBIBULLET_EXPLODE_LIFETIME;

    wp->phys_info.vel.z = 0.0F;
    wp->phys_info.vel.y = 0.0F;
    wp->phys_info.vel.x = 0.0F;

    wp->item_hit.size = ITYUBIBULLET_EXPLODE_SIZE;

    DObjGetStruct(weapon_gobj)->display_list = NULL;

    wp->proc_update = wpMasterHand_YubiExplode_ProcUpdate;
    wp->proc_map = NULL;
    wp->proc_hit = NULL;
    wp->proc_shield = NULL;
    wp->proc_hop = NULL;
    wp->proc_setoff = NULL;
    wp->proc_reflector = NULL;
}

// 0x8016DCB0
bool32 wpMasterHand_YubiBullet_ProcMap(GObj *weapon_gobj)
{
    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        wpMasterHand_YubiExplode_InitWeaponVars(weapon_gobj);
        func_800269C0(0U);
        func_ovl2_801005C8(&DObjGetStruct(weapon_gobj)->translate);

        return TRUE;
    }
    else return FALSE;
}

// 0x8016DD04
bool32 wpMasterHand_YubiBullet_ProcHit(GObj *weapon_gobj)
{
    func_ovl2_801005C8(&DObjGetStruct(weapon_gobj)->translate);

    return TRUE;
}

// 0x8016DD2C
bool32 wpMasterHand_YubiBullet_ProcHop(GObj *weapon_gobj)
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);

    func_80019438(&wp->phys_info.vel, &wp->shield_collide_vec, wp->shield_collide_angle * 2);
    func_ovl3_80168428(weapon_gobj);

    return FALSE;
}

// 0x8016DD7C
bool32 wpMasterHand_YubiBullet_ProcReflector(GObj *weapon_gobj)
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(wp->owner_gobj);

    wpMain_ReflectorInvertLR(wp, fp);
    func_ovl3_80168428(weapon_gobj);

    return FALSE;
}

// 0x8016DDB4
GObj* wpMasterHand_YubiBulletSingle_CreateWeapon(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &wpMasterHand_YubiBulletSingle_WeaponDesc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *wp;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    wp = wpGetStruct(weapon_gobj);

    wp->phys_info.vel.x = ITYUBIBULLET_VEL_X * wp->lr;
    wp->phys_info.vel.y = ITYUBIBULLET_VEL_Y;

    func_ovl3_80168428(weapon_gobj);

    return weapon_gobj;
}

// 0x8016DE28
GObj* wpMasterHand_YubiBulletTriple_CreateWeapon(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &wpMasterHand_YubiBulletTriple_WeaponDesc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *wp;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    wp = wpGetStruct(weapon_gobj);

    wp->phys_info.vel.x = ITYUBIBULLET_VEL_X * wp->lr;
    wp->phys_info.vel.y = ITYUBIBULLET_VEL_Y;

    func_ovl3_80168428(weapon_gobj);

    return weapon_gobj;
}