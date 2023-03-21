#include "item.h"
#include "fighter.h"

bool32 func_ovl3_8016DC00(GObj *item_gobj)
{
    if (func_ovl3_80167FE8(ItemGetStruct(item_gobj)) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8016DC2C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    ip->item_hit.hit_sfx = 1;

    ip->item_hit.flags_0x48_b1 = TRUE;
    ip->item_hit.can_deflect = FALSE;
    ip->item_hit.can_reflect = FALSE;

    ip->item_hit.element = 1;

    ip->lifetime = ITYUBIBULLET_EXPLODE_LIFETIME;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_hit.size = ITYUBIBULLET_EXPLODE_SIZE;

    DObjGetStruct(item_gobj)->display_list = NULL;

    ip->cb_anim = func_ovl3_8016DC00;
    ip->cb_coll = NULL;
    ip->cb_give_damage = NULL;
    ip->cb_shield_block = NULL;
    ip->cb_shield_deflect = NULL;
    ip->cb_attack = NULL;
    ip->cb_reflect = NULL;
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
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    func_ovl3_80168428(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8016DD7C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);
    func_ovl3_80168428(item_gobj);

    return FALSE;
}

extern ItemSpawnData Item_YubiBullet_Easy;

GObj *func_ovl3_8016DDB4(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_YubiBullet_Easy, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->phys_info.vel.x = ITYUBIBULLET_VEL_X * ip->lr;
    ip->phys_info.vel.y = ITYUBIBULLET_VEL_Y;

    func_ovl3_80168428(item_gobj);

    return item_gobj;
}

extern ItemSpawnData Item_YubiBullet_Hard;

GObj *func_ovl3_8016DE28(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_YubiBullet_Hard, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->phys_info.vel.x = ITYUBIBULLET_VEL_X * ip->lr;
    ip->phys_info.vel.y = ITYUBIBULLET_VEL_Y;

    func_ovl3_80168428(item_gobj);

    return item_gobj;
}