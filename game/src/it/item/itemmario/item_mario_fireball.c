#include "item.h"
#include "fighter.h"

extern const ItemFireballAttributes Item_Fireball_Attributes[2];
extern WeaponSpawnData Item_Fireball_Desc;

bool32 jtgt_ovl3_80168540(GObj *weapon_gobj) // Animation
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    DObj *joint;

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);
        return TRUE;
    }

    wpMain_UpdateGravityClampTVel(ip, Item_Fireball_Attributes[ip->item_vars.fireball.index].gravity, Item_Fireball_Attributes[ip->item_vars.fireball.index].fall_speed_max);

    joint = DObjGetStruct(weapon_gobj);

    joint->rotate.x += Item_Fireball_Attributes[ip->item_vars.fireball.index].rotate_speed;

    return FALSE;
}

bool32 jtgt_ovl3_801685F0(GObj *weapon_gobj) // Collision
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Vec3f pos;

    func_ovl3_80167A58(weapon_gobj);

    if (func_ovl3_80167C38(weapon_gobj, MPCOLL_MASK_MAIN_ALL, Item_Fireball_Attributes[ip->item_vars.fireball.index].collide_vel, &pos) != FALSE)
    {
        if (func_ovl0_800C7A84(&ip->phys_info.vel) < Item_Fireball_Attributes[ip->item_vars.fireball.index].collide_damage)
        {
            func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);
            return TRUE;
        }
        wpMain_VelSetModelYaw(weapon_gobj);
        func_ovl2_80102DEC(&DObjGetStruct(weapon_gobj)->translate);
    }
    return FALSE;
}

bool32 jtgt_ovl3_801686C0(GObj *weapon_gobj) // Hit target
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_801686F8(GObj *weapon_gobj) // Hit shield at deflect angle
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    wpMain_VelSetModelYaw(weapon_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80168748(GObj *weapon_gobj) // Hit reflector
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    ip->lifetime = Item_Fireball_Attributes[ip->item_vars.fireball.index].lifetime;

    wpMain_ReflectorInvertLR(ip, fp);
    wpMain_VelSetModelYaw(weapon_gobj);

    return FALSE;
}

GObj *func_ovl3_801687A0(GObj *fighter_gobj, Vec3f *pos, s32 index) // Create item
{

    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *weapon_gobj;
    Weapon_Struct *ip;
    f32 vel;

    Item_Fireball_Desc.p_item = Item_Fireball_Attributes[index].p_item;
    Item_Fireball_Desc.offset_wp_hit = Item_Fireball_Attributes[index].offset_wp_hit;

    weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_Fireball_Desc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->item_vars.fireball.index = index;

    ip->lifetime = Item_Fireball_Attributes[index].lifetime;

    vel = (fp->ground_or_air == air) ? Item_Fireball_Attributes[index].vel_air : Item_Fireball_Attributes[index].vel_ground;

    ip->phys_info.vel.z = 0.0F;

    ip->phys_info.vel.x = Item_Fireball_Attributes[index].vel_mul * cosf(vel) * fp->lr;
    ip->phys_info.vel.y = Item_Fireball_Attributes[index].vel_mul * __sinf(vel);

    DObjGetStruct(weapon_gobj)->mobj->anim_frame = (f32)Item_Fireball_Attributes[index].frame_begin;

    wpMain_VelSetModelYaw(weapon_gobj);
    return weapon_gobj;
}
