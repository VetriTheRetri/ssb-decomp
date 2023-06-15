#include "item.h"
#include "fighter.h"

extern ItemChargeShotAttributes Item_ChargeShot_Attributes[];

void func_ovl3_80168B00(GObj *item_gobj) // Set Charge Shot's attributes on fire
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);
    f32 coll_size;

    ip->phys_info.vel.x = Item_ChargeShot_Attributes[ip->item_vars.charge_shot.charge_size].vel_x * ip->lr;

    ip->item_hit.damage = Item_ChargeShot_Attributes[ip->item_vars.charge_shot.charge_size].damage;
    ip->item_hit.size = Item_ChargeShot_Attributes[ip->item_vars.charge_shot.charge_size].hit_size * 0.5F;

    coll_size = Item_ChargeShot_Attributes[ip->item_vars.charge_shot.charge_size].coll_size * 0.5F;

    ip->coll_data.object_coll.width = coll_size;
    ip->coll_data.object_coll.top = coll_size;
    ip->coll_data.object_coll.bottom = -coll_size;

    func_800269C0(Item_ChargeShot_Attributes[ip->item_vars.charge_shot.charge_size].shoot_sfx_id);

    ip->item_hit.hit_sfx = Item_ChargeShot_Attributes[ip->item_vars.charge_shot.charge_size].hit_sfx_id;
    ip->item_hit.priority = Item_ChargeShot_Attributes[ip->item_vars.charge_shot.charge_size].priority;

    ip->item_vars.charge_shot.owner_gobj = NULL;
}

bool32 func_ovl3_80168BDC(GObj *item_gobj) // Clear GObj pointers
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);

    if (ip->item_vars.charge_shot.owner_gobj != NULL) // Always NULL though?
    {
        Fighter_Struct *fp = ftGetStruct(ip->item_vars.charge_shot.owner_gobj);

        fp->status_vars.samus.specialn.charge_gobj = NULL; // This would quite problematic if Samus and Kirby's SpecialN statevar structs deviated...
    }
    return TRUE;
}

bool32 jtgt_ovl3_80168BFC(GObj *item_gobj) // Animation
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);
    f32 scale;

    if (ip->item_vars.charge_shot.is_release == FALSE)
    {
        scale = Item_ChargeShot_Attributes[ip->item_vars.charge_shot.charge_size].gfx_size / ITCHARGESHOT_GFX_SIZE_DIV;

        DObjGetStruct(item_gobj)->scale.y = scale;
        DObjGetStruct(item_gobj)->scale.x = scale;

        if (ip->item_vars.charge_shot.is_full_charge != FALSE)
        {
            ip->item_vars.charge_shot.is_release = TRUE;

            func_ovl3_80168B00(item_gobj);

            ip->item_hit.update_state = gmHitCollision_UpdateState_New;

            func_ovl3_80165F60(item_gobj);
        }
    }
    DObjGetStruct(item_gobj)->rotate.z -= ITCHARGESHOT_ROTATE_SPEED * ip->lr;

    return FALSE;
}

bool32 jtgt_ovl3_80168CC4(GObj *item_gobj) // Collision 
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);

    if (ip->item_vars.charge_shot.is_release != FALSE)
    {
        // If Charge Shot has been fired, begin checking for collision

        if (func_ovl3_80167C04(item_gobj) != FALSE) 
        {
            func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
            return TRUE;
        }
        else return FALSE; // Redundant return here lol
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80168D24(GObj *item_gobj) // Hit target
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);

    func_ovl2_800FE068(&DObjGetStruct(item_gobj)->translate, ip->item_hit.damage);

    return TRUE;
}

bool32 jtgt_ovl3_80168D54(GObj *item_gobj) // Hit shield at deflect angle
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    wpMain_VelSetLR(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80168DA4(GObj *item_gobj) // Hit reflector
{
    Weapon_Struct *ip = wpGetStruct(item_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);
    wpMain_VelSetLR(item_gobj);

    return FALSE;
}

extern ItemSpawnData Item_ChargeShot_Desc;

GObj* func_ovl3_80168DDC(GObj *fighter_gobj, Vec3f *pos, s32 charge_level, bool32 is_release) // Create item
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *item_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_ChargeShot_Desc, pos, ((is_release != FALSE) ? (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER) : WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *ip;
    f32 scale;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(item_gobj);

    ip->item_vars.charge_shot.is_release = is_release;
    ip->item_vars.charge_shot.charge_size = charge_level;

    if (is_release != FALSE)
    {
        func_ovl3_80168B00(item_gobj);
    }
    else
    {
        ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;
        ip->item_vars.charge_shot.is_full_charge = FALSE;

        ip->item_vars.charge_shot.owner_gobj = fighter_gobj;

        ftCommon_PlayLoopSFXStoreInfo(fp, Item_ChargeShot_Attributes[ip->item_vars.charge_shot.charge_size].charge_sfx_id);
    }

    scale = Item_ChargeShot_Attributes[charge_level].gfx_size / ITCHARGESHOT_GFX_SIZE_DIV;

    DObjGetStruct(item_gobj)->scale.y = scale;
    DObjGetStruct(item_gobj)->scale.x = scale;

    ip->proc_dead = func_ovl3_80168BDC;

    return item_gobj;
}
