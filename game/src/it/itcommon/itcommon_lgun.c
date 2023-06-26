#include "item.h"
#include "weapon.h"
#include "fighter.h"



bool32 jtgt_ovl3_801754F0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATLGUN_GRAVITY, ATLGUN_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 func_ovl3_80175528(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_801755B8);

    return FALSE;
}

bool32 jtgt_ovl3_80175550(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.1F, func_ovl3_80175584);
}

extern itStatusDesc Article_L_Gun_Status[];

void func_ovl3_80175584(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_L_Gun_Status, 0);
}

void func_ovl3_801755B8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_L_Gun_Status, 1);
}

void jtgt_ovl3_801755FC(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->rotate.y = 0.0F;

    itMain_SetItemStatus(item_gobj, Article_L_Gun_Status, 2);
}

bool32 jtgt_ovl3_80175630(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->it_multi == 0)
    {
        return func_ovl3_80173DF4(item_gobj, 0.2F);
    }
    else return func_ovl3_80173B24(item_gobj, 0.2F, 0.1F, func_ovl3_80175584);
}

bool32 jtgt_ovl3_80175684(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

void jtgt_ovl3_801756AC(GObj *item_gobj)
{
    s32 lr = ftGetStruct(itGetStruct(item_gobj)->owner_gobj)->lr;

    itMain_SetItemStatus(item_gobj, Article_L_Gun_Status, 3);

    DObjGetStruct(item_gobj)->next->rotate.y = (lr == LEFT) ? -HALF_PI32 : HALF_PI32;
}

bool32 jtgt_ovl3_8017572C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->it_multi == 0)
    {
        return func_ovl3_80173DF4(item_gobj, 0.2F);
    }
    else return func_ovl3_80173B24(item_gobj, 0.2F, 0.1F, func_ovl3_80175584);
}

void jtgt_ovl3_80175780(GObj *item_gobj)
{
    s32 lr = ftGetStruct(itGetStruct(item_gobj)->owner_gobj)->lr;

    itMain_SetItemStatus(item_gobj, Article_L_Gun_Status, 4);

    DObjGetStruct(item_gobj)->next->rotate.y = (lr == LEFT) ? -HALF_PI32 : HALF_PI32;
}

extern itCreateDesc Article_L_Gun_Data;

GObj* jtgt_ovl3_80175800(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_L_Gun_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        ap->it_multi = ATLGUN_AMMO_MAX;

        DObjGetStruct(item_gobj)->rotate.y = (rand_u16() & 1) ? HALF_PI32 : -HALF_PI32;

        ap->is_unused_item_bool = TRUE;

        ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ap);
    }
    return item_gobj;
}

// Ray Gun ammo functions

bool32 jtgt_ovl3_801758BC(GObj *weapon_gobj)
{
    DObj *joint = DObjGetStruct(weapon_gobj);

    if (joint->scale.x < ATLGUN_AMMO_CLAMP_SCALE_X)
    {
        joint->scale.x += ATLGUN_AMMO_STEP_SCALE_X;

        joint = DObjGetStruct(weapon_gobj); // Y tho lol

        if (ATLGUN_AMMO_CLAMP_SCALE_X < joint->scale.x)
        {
            joint->scale.x = ATLGUN_AMMO_CLAMP_SCALE_X;
        }
    }
    return FALSE;
}

bool32 jtgt_ovl3_80175914(GObj *weapon_gobj)
{
    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80175958(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_ovl2_800FE068(&DObjGetStruct(weapon_gobj)->translate, ip->weapon_hit.damage);

    return TRUE;
}

bool32 jtgt_ovl3_80175988(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel_air.y, ip->phys_info.vel_air.x);
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    return FALSE;
}

bool32 jtgt_ovl3_80175A00(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    wpMain_ReflectorInvertLR(ip, fp);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel_air.y, ip->phys_info.vel_air.x);
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    return FALSE;
}

extern wpCreateDesc Item_L_Gun_Ammo_Desc;

GObj* func_ovl3_80175A60(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_L_Gun_Ammo_Desc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->phys_info.vel_air.x = ip->lr * ATLGUN_AMMO_VEL_X;

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel_air.y, ip->phys_info.vel_air.x);

    return weapon_gobj;
}

void func_ovl3_80175AD8(GObj *fighter_gobj, Vec3f *pos)
{
    Item_Struct *ap = itGetStruct(ftGetStruct(fighter_gobj)->item_hold);

    func_ovl3_80175A60(fighter_gobj, pos);

    ap->it_multi--;
}