#include "item.h"
#include "weapon.h"
#include "fighter.h"

bool32 jtgt_ovl3_80177E80(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATSTARROD_GRAVITY, ATSTARROD_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 func_ovl3_80177EBC(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80177F4C);

    return FALSE;
}

bool32 jtgt_ovl3_80177EE4(GObj *item_gobj)
{
    func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, func_ovl3_80177F18);

    return FALSE;
}

extern itStatusDesc Article_StarRod_Status;

void func_ovl3_80177F18(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_StarRod_Status, 0);
}

void func_ovl3_80177F4C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_StarRod_Status, 1);
}

void jtgt_ovl3_80177F90(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->rotate.y = 0.0F;

    itMain_SetItemStatus(item_gobj, Article_StarRod_Status, 2);
}

bool32 jtgt_ovl3_80177FC4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATSTARROD_GRAVITY, ATSTARROD_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80178000(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, func_ovl3_80177F18);
}

bool32 jtgt_ovl3_80178030(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

void jtgt_ovl3_80178058(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_StarRod_Status, 3);

    DObjGetStruct(item_gobj)->next->rotate.y = HALF_PI32;
}

bool32 jtgt_ovl3_8017809C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->it_multi == 0)
    {
        return func_ovl3_80173DF4(item_gobj, 0.2F);
    }
    else return func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, func_ovl3_80177F18);
}

void jtgt_ovl3_801780F0(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_StarRod_Status, 4);
    DObjGetStruct(item_gobj)->next->rotate.y = HALF_PI32;
}

extern itCreateDesc Article_StarRod_Data;

GObj* jtgt_ovl3_80178134(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_StarRod_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        ap->it_multi = ATSTARROD_AMMO_MAX;

        ap->is_unused_item_bool = TRUE;

        ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ap);
    }
    return item_gobj;
}

bool32 jtgt_ovl3_801781B0(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Vec3f pos;
    DObj *joint;

    if (ip->weapon_vars.star.lifetime == 0)
    {
        DObjGetStruct(weapon_gobj)->unk_0x54 = 2;

        func_ovl2_8010066C(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        return TRUE;
    }

    ip->weapon_vars.star.lifetime--;

    joint = DObjGetStruct(weapon_gobj);

    joint->rotate.z += (-0.2F * ip->lr);

    if (ip->weapon_vars.star.lifetime % 2)
    {
        pos.x = DObjGetStruct(weapon_gobj)->translate.x;
        pos.y = (s32)rand_u16_range(250) + (DObjGetStruct(weapon_gobj)->translate.y - 125.0F);
        pos.z = 0.0F;

        func_ovl2_800FFEA4(&pos, ip->lr * -1.0F, weapon_gobj);
    }
    return FALSE;
}

bool32 jtgt_ovl3_801782D4(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        func_ovl2_80102070(&DObjGetStruct(weapon_gobj)->translate, ip->lr);

        func_800269C0(0x35U);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8017832C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_ovl2_80102070(&DObjGetStruct(weapon_gobj)->translate, ip->lr);

    return TRUE;
}

bool32 jtgt_ovl3_8017835C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel_air.y, ip->phys_info.vel_air.x);

    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    if (ip->phys_info.vel_air.x > 0.0F)
    {
        ip->lr = RIGHT;
    }
    else ip->lr = LEFT;

    return FALSE;
}

bool32 jtgt_ovl3_80178404(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    wpMain_ReflectorInvertLR(ip, fp);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel_air.y, ip->phys_info.vel_air.x);
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern u8 StarRod_Linker_Unk;
extern wpCreateDesc Item_StarRod_Desc;
extern uintptr_t D_ovl3_8018A1D0;

GObj *func_ovl3_80178474(GObj *fighter_gobj, Vec3f *pos, u8 is_smash)
{
    GObj *weapon_gobj;
    DObj *joint;
    Weapon_Struct *ip;

    if (is_smash == TRUE)
    {
        D_ovl3_8018A1D0 = (uintptr_t)&StarRod_Linker_Unk;
    }
    weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_StarRod_Desc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    joint = DObjGetStruct(weapon_gobj);
    ip = wpGetStruct(weapon_gobj);

    ip->phys_info.vel_air.x = ((!(is_smash)) ? ATSTARROD_AMMO_TILT_VEL_X : ATSTARROD_AMMO_SMASH_VEL_X) * ip->lr;

    ip->weapon_vars.star.lifetime = (!(is_smash)) ? ATSTARROD_AMMO_TILT_LIFETIME : ATSTARROD_AMMO_SMASH_LIFETIME; // Why float lol

    func_80008CC0(joint, 0x2EU, 0U);

    joint->translate = *pos;

    joint->translate.z = 0.0F;

    return weapon_gobj;
}

void func_ovl3_80178594(GObj *fighter_gobj, Vec3f *pos, u8 is_smash)
{
    Item_Struct *ap = itGetStruct(ftGetStruct(fighter_gobj)->item_hold);

    func_ovl3_80178474(fighter_gobj, pos, is_smash);

    ap->it_multi--;
}