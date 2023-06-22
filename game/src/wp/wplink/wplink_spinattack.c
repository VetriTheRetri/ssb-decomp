#include "weapon.h"
#include "fighter.h"

extern void *D_ovl2_80130FB0;

wpCreateDesc wpLink_SpinAttack_WeaponDesc =
{
    3,                                      // Render flags?
    Wp_Kind_SpinAttack,                     // Weapon Kind
    &D_ovl2_80130FB0,                       // Pointer to character's loaded files?
    0xC,                                    // Offset of weapon attributes in loaded files
    0x1C,                                   // ???
    0,                                      // ???
    0,                                      // ???
    0,                                      // ???
    wpLink_SpinAttack_ProcUpdate,           // Proc Update
    wpLink_SpinAttack_ProcMap,              // Proc Map
    wpLink_SpinAttack_ProcHit,              // Proc Hit
    wpLink_SpinAttack_ProcHit,              // Proc Shield
    NULL,                                   // Proc Hop
    wpLink_SpinAttack_ProcHit,              // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Absorb
};

void func_ovl3_8016C9A0(void) // Unused
{
    return;
}

// 0x8016C9A8
bool32 wpLink_SpinAttack_ProcDead(GObj *weapon_gobj)
{
    return FALSE;
}

// 0x8016C9B4
bool32 wpLink_SpinAttack_ProcUpdate(GObj *weapon_gobj)
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);
    f32 sqrt_vel;
    f32 mod_vel;

    if (wp->weapon_vars.spin_attack.is_destroy != FALSE)
    {
        return TRUE;
    }

    sqrt_vel = sqrtf(SQUARE(wp->weapon_vars.spin_attack.vel.x) + SQUARE(wp->weapon_vars.spin_attack.vel.y));

    if (sqrt_vel > 0.0F)
    {
        if (sqrt_vel < ITSPINATTACK_VEL_CLAMP)
        {
            mod_vel = 0.0F;
        }
        else
        {
            mod_vel = sqrt_vel - ITSPINATTACK_VEL_CLAMP;
        }
        wp->weapon_vars.spin_attack.vel.x = (wp->weapon_vars.spin_attack.vel.x * mod_vel) / sqrt_vel;
        wp->weapon_vars.spin_attack.vel.y = (wp->weapon_vars.spin_attack.vel.y * mod_vel) / sqrt_vel;

        wp->weapon_hit.offset[0].x += wp->weapon_vars.spin_attack.vel.x; // TO DO: this might not be an array at all, loops don't match when indexed with iterator
        wp->weapon_hit.offset[0].y += wp->weapon_vars.spin_attack.vel.y;
        wp->weapon_hit.offset[1].x -= wp->weapon_vars.spin_attack.vel.x;
        wp->weapon_hit.offset[1].y += wp->weapon_vars.spin_attack.vel.y;
    }
    return FALSE;
}

// 0x8016CA9C
bool32 wpLink_SpinAttack_ProcMap(GObj *weapon_gobj)
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);
    f32 pos_x, pos_y;
    s32 index = (wp->weapon_vars.spin_attack.pos_index + 1) % ITSPINATTACK_EXTEND_POS_COUNT;

    pos_x = wp->weapon_vars.spin_attack.pos_x[index];
    pos_y = wp->weapon_vars.spin_attack.pos_y[index];

    pos_y += ITSPINATTACK_OFF_Y;

    wp->phys_info.vel.x = pos_x - DObjGetStruct(weapon_gobj)->translate.x;
    wp->phys_info.vel.y = pos_y - DObjGetStruct(weapon_gobj)->translate.y;

    return FALSE;
}

// 0x8016CB10
bool32 wpLink_SpinAttack_ProcHit(GObj *weapon_gobj)
{
    return FALSE;
}

// 0x8016CB1C
GObj* wpLink_SpinAttack_CreateWeapon(GObj *fighter_gobj, Vec3f *pos)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *weapon_gobj;
    Weapon_Struct *wp;
    Vec3f offset = *pos;
    s32 unused;

    offset.y += ITSPINATTACK_OFF_Y;

    weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &wpLink_SpinAttack_WeaponDesc, &offset, WEAPON_MASK_SPAWN_FIGHTER);

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    wp = wpGetStruct(weapon_gobj);

    wp->weapon_hit.offset[0].x = ITSPINATTACK_OFF_X;
    wp->weapon_hit.offset[0].y = 0.0F;
    wp->weapon_hit.offset[1].x = -ITSPINATTACK_OFF_X;
    wp->weapon_hit.offset[1].y = 0.0F;

    wp->lr = fp->lr;

    wp->lifetime = ITSPINATTACK_LIFETIME;

    wp->proc_dead = wpLink_SpinAttack_ProcDead;

    _bzero(&wp->weapon_vars.spin_attack, sizeof(wp->weapon_vars));

    wp->weapon_vars.spin_attack.vel.x = cosf(ITSPINATTACK_ANGLE) * ITSPINATTACK_VEL;
    wp->weapon_vars.spin_attack.vel.y = __sinf(ITSPINATTACK_ANGLE) * ITSPINATTACK_VEL;

    wp->phys_info.vel.z = 0.0F;
    wp->phys_info.vel.y = 0.0F;
    wp->phys_info.vel.x = 0.0F;

    wpManager_UpdateHitPositions(weapon_gobj);

    return weapon_gobj;
}