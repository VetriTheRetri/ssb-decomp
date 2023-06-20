#include "item.h"
#include "ftsamus.h"

wpSamusChargeShotAttributes wpSamus_ChargeShot_WeaponAttributes[FTSAMUS_CHARGE_MAX + 1] =
{
    // Level 0 (Uncharged)
    {
        150.0F,                     // Sprite size
        60.0F                       // X-Velocity
        3,                          // Damage
        100,                        // Hitbox size
        10,                         // Object collision size
        0xEE,                       // Shoot SFX
        0xEF,                       // Charge SFX
        0x18,                       // Hit SFX
        1,                          // Priority
    },

    // Level 1
    {
        230.0F,                     // Sprite size
        62.0F                       // X-Velocity
        6,                          // Damage
        120,                        // Hitbox size
        10,                         // Object collision size
        0xEE,                       // Shoot SFX
        0xF0,                       // Charge SFX
        0x18,                       // Hit SFX
        1,                          // Priority
    },

    // Level 2
    {
        280.0F,                     // Sprite size
        64.0F                       // X-Velocity
        9,                          // Damage
        140,                        // Hitbox size
        10,                         // Object collision size
        0xED,                       // Shoot SFX
        0xF1,                       // Charge SFX
        0x17,                       // Hit SFX
        1,                          // Priority
    },

    // Level 3
    {
        340.0F,                     // Sprite size
        66.0F                       // X-Velocity
        12,                         // Damage
        160,                        // Hitbox size
        10,                         // Object collision size
        0xED,                       // Shoot SFX
        0xF2,                       // Charge SFX
        0x17,                       // Hit SFX
        1,                          // Priority
    },

    // Level 4
    {
        410.0F,                     // Sprite size
        68.0F                       // X-Velocity
        15,                         // Damage
        180,                        // Hitbox size
        10,                         // Object collision size
        0xED,                       // Shoot SFX
        0xF3,                       // Charge SFX
        0x17,                       // Hit SFX
        1,                          // Priority
    },

    // Level 5
    {
        490.0F,                     // Sprite size
        70.0F                       // X-Velocity
        18,                         // Damage
        200,                        // Hitbox size
        10,                         // Object collision size
        0xEC,                       // Shoot SFX
        0xF4,                       // Charge SFX
        0x16,                       // Hit SFX
        1,                          // Priority
    },

    // Level 6
    {
        600.0F,                     // Sprite size
        72.0F                       // X-Velocity
        21,                         // Damage
        240,                        // Hitbox size
        10,                         // Object collision size
        0xEC,                       // Shoot SFX
        0xF5,                       // Charge SFX
        0x16,                       // Hit SFX
        1,                          // Priority
    },

    // Level 7 (Full charge)
    {
        700.0F,                     // Sprite size
        74.0F                       // X-Velocity
        26,                         // Damage
        260,                        // Hitbox size
        10,                         // Object collision size
        0xEB,                       // Shoot SFX
        0xF6,                       // Charge SFX
        0x16,                       // Hit SFX
        2,                          // Priority
    }
};

extern void *D_ovl2_80130F3C;

wpCreateDesc wpSamus_ChargeShot_WeaponDesc =
{
    0,                                      // Render flags?
    Wp_Kind_ChargeShot,                     // Weapon Kind
    &D_ovl2_80130F3C,                       // Pointer to character's loaded files?
    0x0,                                    // Offset of weapon attributes in loaded files
    0x12,                                   // ???
    0x2E,                                   // ???
    0,                                      // ???
    0,                                      // ???
    wpSamus_ChargeShot_ProcUpdate,          // Proc Update
    wpSamus_ChargeShot_ProcMap,             // Proc Map
    wpSamus_ChargeShot_ProcHit,             // Proc Hit
    wpSamus_ChargeShot_ProcHit,             // Proc Shield
    wpSamus_ChargeShot_ProcHop,             // Proc Hop
    wpSamus_ChargeShot_ProcHit,             // Proc Set-Off
    wpSamus_ChargeShot_ProcReflector,       // Proc Reflector
    wpSamus_ChargeShot_ProcHit              // Proc Absorb
};

// 0x80168B00
void wpSamus_ChargeShot_LaunchSetVars(GObj *weapon_gobj) // Set Charge Shot's attributes upon firing
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);
    f32 coll_size;

    wp->phys_info.vel.x = wpSamus_ChargeShot_WeaponAttributes[wp->item_vars.charge_shot.charge_size].vel_x * wp->lr;

    wp->item_hit.damage = wpSamus_ChargeShot_WeaponAttributes[wp->item_vars.charge_shot.charge_size].damage;
    wp->item_hit.size = wpSamus_ChargeShot_WeaponAttributes[wp->item_vars.charge_shot.charge_size].hit_size * 0.5F;

    coll_size = wpSamus_ChargeShot_WeaponAttributes[wp->item_vars.charge_shot.charge_size].coll_size * 0.5F;

    wp->coll_data.object_coll.width = coll_size;
    wp->coll_data.object_coll.top = coll_size;
    wp->coll_data.object_coll.bottom = -coll_size;

    func_800269C0(wpSamus_ChargeShot_WeaponAttributes[wp->item_vars.charge_shot.charge_size].shoot_sfx_id);

    wp->item_hit.hit_sfx = wpSamus_ChargeShot_WeaponAttributes[wp->item_vars.charge_shot.charge_size].hit_sfx_id;
    wp->item_hit.priority = wpSamus_ChargeShot_WeaponAttributes[wp->item_vars.charge_shot.charge_size].priority;

    wp->item_vars.charge_shot.owner_gobj = NULL;
}

// 0x80168BDC
bool32 wpSamus_ChargeShot_ProcDead(GObj *weapon_gobj) // Clear GObj pointers
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);

    if (wp->item_vars.charge_shot.owner_gobj != NULL) // Always NULL though?
    {
        Fighter_Struct *fp = ftGetStruct(wp->item_vars.charge_shot.owner_gobj);

        fp->status_vars.samus.specialn.charge_gobj = NULL; // This would quite problematic if Samus and Kirby's SpecialN statevar structs deviated...
    }
    return TRUE;
}

// 0x80168BFC
bool32 wpSamus_ChargeShot_ProcUpdate(GObj *weapon_gobj) // Animation
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);
    f32 scale;

    if (wp->item_vars.charge_shot.is_release == FALSE)
    {
        scale = wpSamus_ChargeShot_WeaponAttributes[wp->item_vars.charge_shot.charge_size].gfx_size / ITCHARGESHOT_GFX_SIZE_DIV;

        DObjGetStruct(weapon_gobj)->scale.y = scale;
        DObjGetStruct(weapon_gobj)->scale.x = scale;

        if (wp->item_vars.charge_shot.is_full_charge != FALSE)
        {
            wp->item_vars.charge_shot.is_release = TRUE;

            wpSamus_ChargeShot_LaunchSetVars(weapon_gobj);

            wp->item_hit.update_state = gmHitCollision_UpdateState_New;

            wpManager_UpdateHitPositions(weapon_gobj);
        }
    }
    DObjGetStruct(weapon_gobj)->rotate.z -= ITCHARGESHOT_ROTATE_SPEED * wp->lr;

    return FALSE;
}

// 0x80168CC4
bool32 wpSamus_ChargeShot_ProcMap(GObj *weapon_gobj) // Collision 
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);

    if (wp->item_vars.charge_shot.is_release != FALSE)
    {
        // If Charge Shot has been fired, begin checking for collision

        if (func_ovl3_80167C04(weapon_gobj) != FALSE) 
        {
            func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);
            return TRUE;
        }
        else return FALSE; // Redundant return here lol
    }
    else return FALSE;
}

// 0x80168D24
bool32 wpSamus_ChargeShot_ProcHit(GObj *weapon_gobj) // Hit target
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);

    func_ovl2_800FE068(&DObjGetStruct(weapon_gobj)->translate, wp->item_hit.damage);

    return TRUE;
}

// 0x80168D54
bool32 wpSamus_ChargeShot_ProcHop(GObj *weapon_gobj) // Hit shield at deflect angle
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);

    func_80019438(&wp->phys_info.vel, &wp->shield_collide_vec, wp->shield_collide_angle * 2);
    wpMain_VelSetLR(weapon_gobj);

    return FALSE;
}

// 0x80168DA4
bool32 wpSamus_ChargeShot_ProcReflector(GObj *weapon_gobj) // Hit reflector
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(wp->owner_gobj);

    wpMain_ReflectorInvertLR(wp, fp);
    wpMain_VelSetLR(weapon_gobj);

    return FALSE;
}

// 0x80168DDC
GObj* wpSamus_ChargeShot_CreateWeapon(GObj *fighter_gobj, Vec3f *pos, s32 charge_level, bool32 is_release) // Create item
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &wpSamus_ChargeShot_WeaponDesc, pos, ((is_release != FALSE) ? (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER) : WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *wp;
    f32 scale;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    wp = wpGetStruct(weapon_gobj);

    wp->item_vars.charge_shot.is_release = is_release;
    wp->item_vars.charge_shot.charge_size = charge_level;

    if (is_release != FALSE)
    {
        wpSamus_ChargeShot_LaunchSetVars(weapon_gobj);
    }
    else
    {
        wp->item_hit.update_state = gmHitCollision_UpdateState_Disable;
        wp->item_vars.charge_shot.is_full_charge = FALSE;

        wp->item_vars.charge_shot.owner_gobj = fighter_gobj;

        ftCommon_PlayLoopSFXStoreInfo(fp, wpSamus_ChargeShot_WeaponAttributes[wp->item_vars.charge_shot.charge_size].charge_sfx_id);
    }

    scale = wpSamus_ChargeShot_WeaponAttributes[charge_level].gfx_size / ITCHARGESHOT_GFX_SIZE_DIV;

    DObjGetStruct(weapon_gobj)->scale.y = scale;
    DObjGetStruct(weapon_gobj)->scale.x = scale;

    wp->proc_dead = wpSamus_ChargeShot_ProcDead;

    return weapon_gobj;
}
