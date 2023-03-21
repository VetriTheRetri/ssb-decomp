#include "item.h"
#include "fighter.h"

extern const ItemFireballAttributes Item_Fireball_Attributes[2];
extern ItemSpawnData Item_Fireball_Desc;

bool32 jtgt_ovl3_80168540(GObj *item_gobj) // Animation
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    DObj *joint;

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
        return TRUE;
    }

    func_ovl3_80168088(ip, Item_Fireball_Attributes[ip->item_vars.fireball.index].gravity, Item_Fireball_Attributes[ip->item_vars.fireball.index].fall_speed_max);

    joint = DObjGetStruct(item_gobj);

    joint->rotate.x += Item_Fireball_Attributes[ip->item_vars.fireball.index].rotate_speed;

    return FALSE;
}

bool32 jtgt_ovl3_801685F0(GObj *item_gobj) // Collision
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Vec3f pos;

    func_ovl3_80167A58(item_gobj);

    if (func_ovl3_80167C38(item_gobj, MPCOLL_MASK_ALL, Item_Fireball_Attributes[ip->item_vars.fireball.index].collide_vel, &pos) != FALSE)
    {
        if (func_ovl0_800C7A84(&ip->phys_info.vel) < Item_Fireball_Attributes[ip->item_vars.fireball.index].collide_damage)
        {
            func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
            return TRUE;
        }
        func_ovl3_80167FA0(item_gobj);
        func_ovl2_80102DEC(&DObjGetStruct(item_gobj)->translate);
    }
    return FALSE;
}

bool32 jtgt_ovl3_801686C0(GObj *item_gobj) // Hit target
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(item_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_801686F8(GObj *item_gobj) // Hit shield at deflect angle
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    func_ovl3_80167FA0(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80168748(GObj *item_gobj) // Hit reflector
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    ip->lifetime = Item_Fireball_Attributes[ip->item_vars.fireball.index].lifetime;

    func_ovl3_801680EC(ip, fp);
    func_ovl3_80167FA0(item_gobj);

    return FALSE;
}

GObj *func_ovl3_801687A0(GObj *fighter_gobj, Vec3f *pos, s32 index) // Create item
{

    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *item_gobj;
    Item_Struct *ip;
    f32 vel;

    Item_Fireball_Desc.p_item = Item_Fireball_Attributes[index].p_item;
    Item_Fireball_Desc.offset_it_hit = Item_Fireball_Attributes[index].offset_it_hit;

    item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_Fireball_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->item_vars.fireball.index = index;

    ip->lifetime = Item_Fireball_Attributes[index].lifetime;

    vel = (fp->ground_or_air == air) ? Item_Fireball_Attributes[index].vel_air : Item_Fireball_Attributes[index].vel_ground;

    ip->phys_info.vel.z = 0.0F;

    ip->phys_info.vel.x = Item_Fireball_Attributes[index].vel_mul * cosf(vel) * fp->lr;
    ip->phys_info.vel.y = Item_Fireball_Attributes[index].vel_mul * __sinf(vel);

    DObjGetStruct(item_gobj)->mobj->anim_frame = (f32)Item_Fireball_Attributes[index].frame_begin;

    func_ovl3_80167FA0(item_gobj);
    return item_gobj;
}
