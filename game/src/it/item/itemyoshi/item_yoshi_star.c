#include "item.h"
#include "fighter.h"

f32 func_ovl3_8016C540(Weapon_Struct *ip)
{
    f32 scale = (ip->lifetime * ITYOSHISTAR_LIFETIME_SCALE_MUL) + ITYOSHISTAR_LIFETIME_SCALE_ADD;

    if (scale > 1.0F)
    {
        scale = 1.0F;
    }
    return scale;
}

bool32 jtgt_ovl3_8016C588(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    f32 scale;
    f32 vel_sqrt;
    f32 vel_mul;

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        return TRUE;
    }
    scale = func_ovl3_8016C540(ip);

    DObjGetStruct(weapon_gobj)->scale.x = scale;
    DObjGetStruct(weapon_gobj)->scale.y = scale;

    DObjGetStruct(weapon_gobj)->rotate.z += (ITYOSHISTAR_ROTATE_SPEED * ip->lr);

    vel_sqrt = sqrtf(SQUARE(ip->phys_info.vel.x) + SQUARE(ip->phys_info.vel.y));

    if (vel_sqrt > 0.0F)
    {
        if (vel_sqrt < ITYOSHISTAR_VEL_CLAMP)
        {
            vel_mul = 0.0F;
        }
        else
        {
            vel_mul = vel_sqrt - ITYOSHISTAR_VEL_CLAMP;
        }
        ip->phys_info.vel.x = (ip->phys_info.vel.x * vel_mul) / vel_sqrt;
        ip->phys_info.vel.y = (ip->phys_info.vel.y * vel_mul) / vel_sqrt;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016C6A0(GObj *weapon_gobj)
{
    return FALSE;
}

bool32 jtgt_ovl3_8016C6AC(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

    if (ip->hit_victim_damage != 0)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016C6F0(GObj *weapon_gobj)
{
    func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_8016C718(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);

    if (ip->phys_info.vel.x > 0.0F)
    {
        ip->lr = RIGHT;
    }
    else ip->lr = LEFT;

    return FALSE;
}

bool32 jtgt_ovl3_8016C7B0(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    ip->lifetime = ITYOSHISTAR_LIFETIME;

    wpMain_ReflectorInvertLR(ip, fp);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);

    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;
    DObjGetStruct(weapon_gobj)->scale.y = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern WeaponSpawnData Item_YoshiStar_Desc;

GObj* func_ovl3_8016C834(GObj *fighter_gobj, Vec3f *pos, s32 lr)
{
    GObj *weapon_gobj;
    Weapon_Struct *ip;
    Vec3f offset = *pos;

    offset.y += ITYOSHISTAR_OFF_Y;

    if (lr == RIGHT)
    {
        offset.x += ITYOSHISTAR_OFF_X;
    }
    else
    {
        offset.x -= ITYOSHISTAR_OFF_X;
    }

    weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_YoshiStar_Desc, &offset, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->lr = lr;

    ip->lifetime = ITYOSHISTAR_LIFETIME;

    ip->phys_info.vel.x = (cosf(ITYOSHISTAR_ANGLE) * (ITYOSHISTAR_VEL * ip->lr));
    ip->phys_info.vel.y = (__sinf(ITYOSHISTAR_ANGLE) * ITYOSHISTAR_VEL);

    return; // Undefined behavior here, no return value
}

bool32 func_ovl3_8016C954(GObj *fighter_gobj, Vec3f *pos)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    func_ovl3_8016C834(fighter_gobj, pos, fp->lr);
    func_ovl3_8016C834(fighter_gobj, pos, -fp->lr);

    return FALSE;
}