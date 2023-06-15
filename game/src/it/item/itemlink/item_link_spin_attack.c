#include "item.h"
#include "fighter.h"

void func_ovl3_8016C9A0(void) // Unused
{
    return;
}

bool32 func_ovl3_8016C9A8(GObj *item_gobj)
{
    return FALSE;
}

bool32 jtgt_ovl3_8016C9B4(GObj *item_gobj)
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);
    f32 sqrt_vel;
    f32 mod_vel;

    if (ip->item_vars.spin_attack.is_destroy != FALSE)
    {
        return TRUE;
    }

    sqrt_vel = sqrtf(SQUARE(ip->item_vars.spin_attack.vel.x) + SQUARE(ip->item_vars.spin_attack.vel.y));

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
        ip->item_vars.spin_attack.vel.x = (ip->item_vars.spin_attack.vel.x * mod_vel) / sqrt_vel;
        ip->item_vars.spin_attack.vel.y = (ip->item_vars.spin_attack.vel.y * mod_vel) / sqrt_vel;

        ip->item_hit.offset[0].x += ip->item_vars.spin_attack.vel.x; // TO DO: this might not be an array at all, loops don't match when indexed with iterator
        ip->item_hit.offset[0].y += ip->item_vars.spin_attack.vel.y;
        ip->item_hit.offset[1].x -= ip->item_vars.spin_attack.vel.x;
        ip->item_hit.offset[1].y += ip->item_vars.spin_attack.vel.y;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016CA9C(GObj *item_gobj)
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);
    f32 pos_x, pos_y;
    s32 index = (ip->item_vars.spin_attack.pos_index + 1) % (ARRAY_COUNT(ip->item_vars.spin_attack.pos_x) | ARRAY_COUNT(ip->item_vars.spin_attack.pos_y));

    pos_x = ip->item_vars.spin_attack.pos_x[index];
    pos_y = ip->item_vars.spin_attack.pos_y[index];

    pos_y += ITSPINATTACK_OFF_Y;

    ip->phys_info.vel.x = pos_x - DObjGetStruct(item_gobj)->translate.x;
    ip->phys_info.vel.y = pos_y - DObjGetStruct(item_gobj)->translate.y;

    return FALSE;
}

bool32 jtgt_ovl3_8016CB10(GObj *item_gobj)
{
    return FALSE;
}

extern ItemSpawnData Item_SpinAttack_Desc;

GObj *func_ovl3_8016CB1C(GObj *fighter_gobj, Vec3f *pos)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *item_gobj;
    Weapon_Struct *ip;
    Vec3f offset = *pos;
    s32 unused;

    offset.y += ITSPINATTACK_OFF_Y;

    item_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_SpinAttack_Desc, &offset, WEAPON_MASK_SPAWN_FIGHTER);

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(item_gobj);

    ip->item_hit.offset[0].x = ITSPINATTACK_OFF_X;
    ip->item_hit.offset[0].y = 0.0F;
    ip->item_hit.offset[1].x = -ITSPINATTACK_OFF_X;
    ip->item_hit.offset[1].y = 0.0F;

    ip->lr = fp->lr;

    ip->lifetime = ITSPINATTACK_LIFETIME;

    ip->proc_dead = func_ovl3_8016C9A8;

    _bzero(&ip->item_vars.spin_attack, sizeof(ip->item_vars));

    ip->item_vars.spin_attack.vel.x = cosf(ITSPINATTACK_ANGLE) * ITSPINATTACK_VEL;
    ip->item_vars.spin_attack.vel.y = __sinf(ITSPINATTACK_ANGLE) * ITSPINATTACK_VEL;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    func_ovl3_80165F60(item_gobj);

    return item_gobj;
}