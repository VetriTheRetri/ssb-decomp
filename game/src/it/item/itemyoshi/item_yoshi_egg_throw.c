#include "item.h"
#include "fighter.h"

#include <game/src/sys/obj_renderer.h>
#include <game/include/PR/gu.h>
#include <game/include/PR/mbi.h>
#include <game/include/PR/sp.h>

extern void *D_ovl2_80130FF0;

wpCreateDesc wpYoshi_EggThrow_WeaponDesc =
{
    0,                                      // Render flags?
    Wp_Kind_EggThrow,                       // Weapon Kind
    &D_ovl2_80130FF0,                       // Pointer to character's loaded files?
    0xC,                                    // Offset of weapon attributes in loaded files
    0x1C,                                   // ???
    0x2E,                                   // ???
    0,                                      // ???
    0,                                      // ???
    wpYoshi_EggThrow_ProcUpdate,            // Proc Update
    wpYoshi_EggThrow_ProcMap,               // Proc Map
    wpYoshi_EggThrow_ProcHit,               // Proc Hit
    wpYoshi_EggThrow_ProcHit,               // Proc Shield
    wpYoshi_EggThrow_ProcHop,               // Proc Hop
    wpYoshi_EggThrow_ProcHit,               // Proc Set-Off
    wpYoshi_EggThrow_ProcReflector,         // Proc Reflector
    NULL                                    // Proc Absorb
};

// 0x8016BF50
bool32 wpYoshi_EggThrow_ProcDead(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (ip->item_vars.egg_throw.is_throw == FALSE)
    {
        return FALSE;
    }
    else return TRUE;
}

// 0x8016BF74
bool32 wpYoshi_EggExplode_ProcUpdate(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

// 0x8016BFA0
void wpYoshi_EggHit_InitWeaponVars(GObj *weapon_gobj) // Egg Throw explodes from landing successfully
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    ip->lifetime = ITEGGTHROW_EXPLODE_LIFETIME;

    ip->item_hit.can_hop = FALSE;
    ip->item_hit.can_reflect = FALSE;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_hit.size = ITEGGTHROW_EXPLODE_SIZE;

    DObjGetStruct(weapon_gobj)->display_list = NULL;

    ip->proc_update = wpYoshi_EggExplode_ProcUpdate;
    ip->proc_map = NULL;
    ip->proc_hit = NULL;
    ip->proc_shield = NULL;
    ip->proc_hop = NULL;
    ip->proc_setoff = NULL;
    ip->proc_reflector = NULL;
}

// 0x8016C00C
void wpYoshi_EggExpire_InitWeaponVars(GObj *weapon_gobj) // Egg Throw explodes from expiring 
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    ip->lifetime = ITEGGTHROW_EXPLODE_LIFETIME;

    ip->item_hit.can_reflect = FALSE;
    ip->item_hit.can_shield = FALSE;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_hit.size = ITEGGTHROW_EXPLODE_SIZE;

    DObjGetStruct(weapon_gobj)->display_list = NULL;

    ip->proc_update = wpYoshi_EggExplode_ProcUpdate;
    ip->proc_map = NULL;
    ip->proc_hit = NULL;
    ip->proc_shield = NULL;
    ip->proc_hop = NULL;
    ip->proc_setoff = NULL;
    ip->proc_reflector = NULL;
}

// 0x8016C07C
void wpYoshi_EggThrow_InitWeaponVars(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    f32 angle = ABS(ip->item_vars.egg_throw.stick_range) / ITEGGTHROW_TRAJECTORY_DIV;

    if (angle > 1.0F)
    {
        angle = 1.0F;
    }

    angle *= ITEGGTHROW_ANGLE_MUL;

    if (angle < ITEGGTHROW_ANGLE_CLAMP)
    {
        angle = 0.0F;
    }

    angle *= ((ip->item_vars.egg_throw.stick_range < 0) ? LEFT : RIGHT);

    angle = (ip->item_vars.egg_throw.lr > 0) ? (ITEGGTHROW_TRAJECTORY_SUB_RIGHT - angle) : (ITEGGTHROW_TRAJECTORY_SUB_LEFT - angle);

    ip->phys_info.vel.y = __sinf(angle) * ((ip->item_vars.egg_throw.throw_force * ITEGGTHROW_VEL_FORCE_MUL) + ITEGGTHROW_VEL_ADD);
    ip->phys_info.vel.x = cosf(angle) * ((ip->item_vars.egg_throw.throw_force * ITEGGTHROW_VEL_FORCE_MUL) + ITEGGTHROW_VEL_ADD);

    ip->item_vars.egg_throw.angle = F_DEG_TO_RAD((ip->item_vars.egg_throw.throw_force * ITEGGTHROW_ANGLE_FORCE_MUL) + ITEGGTHROW_ANGLE_ADD);

    DObjGetStruct(weapon_gobj)->translate.z = 0.0F;

    ip->item_hit.update_state = gmHitCollision_UpdateState_New;

    wpManager_UpdateHitPositions(weapon_gobj);
}

// 0x8016C218
bool32 wpYoshi_EggThrow_ProcUpdate(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (ip->item_vars.egg_throw.is_spin != FALSE)
    {
        if (wpMain_DecLifeCheckExpire(ip) != FALSE)
        {
            func_800269C0(0xFC);

            func_ovl2_80103A88(&DObjGetStruct(weapon_gobj)->translate);
            func_ovl2_801041A0(&DObjGetStruct(weapon_gobj)->translate);

            wpYoshi_EggExpire_InitWeaponVars(weapon_gobj);

            return FALSE;
        }
        else
        {
            DObjGetStruct(weapon_gobj)->rotate.z += ip->item_vars.egg_throw.angle;
            wpMain_UpdateGravityClampTVel(ip, ITEGGTHROW_GRAVITY, ITEGGTHROW_T_VEL);

            return FALSE;
        }
    }
    else if (ip->item_vars.egg_throw.is_throw != FALSE)
    {
        ip->item_vars.egg_throw.is_spin = TRUE;

        wpYoshi_EggThrow_InitWeaponVars(weapon_gobj);
    }
    return FALSE;
}

// 0x8016C2E0
bool32 wpYoshi_EggThrow_ProcMap(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if ((ip->item_vars.egg_throw.is_spin != FALSE) && (func_ovl3_80167C04(weapon_gobj) != FALSE))
    {
        func_ovl2_801008F4(2);

        func_800269C0(0xFC);

        func_ovl2_80103A88(&DObjGetStruct(weapon_gobj)->translate);
        func_ovl2_801041A0(&DObjGetStruct(weapon_gobj)->translate);

        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        wpYoshi_EggHit_InitWeaponVars(weapon_gobj);
    }
    return FALSE;
}

// 0x8016C374
bool32 wpYoshi_EggThrow_ProcHit(GObj *weapon_gobj)
{
    func_800269C0(0xFC);

    func_ovl2_80103A88(&DObjGetStruct(weapon_gobj)->translate);
    func_ovl2_801041A0(&DObjGetStruct(weapon_gobj)->translate);

    wpYoshi_EggHit_InitWeaponVars(weapon_gobj);

    return FALSE;
}

// 0x8016C3B4
bool32 wpYoshi_EggThrow_ProcHop(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    wpMain_VelSetModelYaw(weapon_gobj);

    return FALSE;
}

// 0x8016C404
bool32 wpYoshi_EggThrow_ProcReflector(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    ip->lifetime = ITEGGTHROW_LIFETIME;

    wpMain_ReflectorInvertLR(ip, fp);
    wpMain_VelSetModelYaw(weapon_gobj);

    return FALSE;
}

// 0x8016C444
void wpYoshi_EggThrow_ProcRender(GObj *weapon_gobj)
{
    gDPPipeSync(D_800465B0[1]++);

    gDPSetEnvColor(D_800465B0[1]++, 0, 0, 0, 0);

    func_ovl3_801675D0(weapon_gobj);
}

// 0x8016C498
GObj* wpYoshi_EggThrow_CreateWeapon(GObj *fighter_gobj, Vec3f *pos)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &wpYoshi_EggThrow_WeaponDesc, pos, WEAPON_MASK_SPAWN_FIGHTER);
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }

    ip = wpGetStruct(weapon_gobj);

    weapon_gobj->renderer = wpYoshi_EggThrow_ProcRender;

    ip->item_vars.egg_throw.is_throw = FALSE;

    ip->proc_dead = wpYoshi_EggThrow_ProcDead;

    ip->lifetime = ITEGGTHROW_LIFETIME;

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ip->is_camera_follow = TRUE;

    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_vars.egg_throw.is_spin = ip->item_vars.egg_throw.is_throw;
    ip->item_vars.egg_throw.lr = fp->lr;

    return weapon_gobj;
}