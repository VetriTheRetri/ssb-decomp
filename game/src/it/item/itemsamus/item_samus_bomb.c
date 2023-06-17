#include "item.h"
#include "fighter.h"

bool32 func_ovl3_80168F00(GObj *weapon_gobj)
{
    if (wpMain_DecLifeCheckExpire(wpGetStruct(weapon_gobj)) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80168F2C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    ip->lifetime = ITSAMUSBOMB_EXPLODE_LIFETIME;

    ip->item_hit.can_rehit_hurt = TRUE;
    ip->item_hit.can_hop = FALSE;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_hit.size = ITSAMUSBOMB_EXPLODE_RADIUS;

    DObjGetStruct(weapon_gobj)->display_list = NULL;

    ip->proc_update = func_ovl3_80168F00;
    ip->proc_map = NULL;
    ip->proc_hit = NULL;
    ip->proc_shield = NULL;
    ip->proc_hop = NULL;
    ip->proc_setoff = NULL;
    ip->proc_reflector = NULL;
}

bool32 jtgt_ovl3_80168F98(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        func_ovl2_801005C8(&DObjGetStruct(weapon_gobj)->translate);
        func_ovl3_80168F2C(weapon_gobj);
        func_800269C0(0U);

        return FALSE;
    }
    else
    {
        if (ip->ground_or_air == air)
        {
            wpMain_UpdateGravityClampTVel(ip, ITSAMUSBOMB_WAIT_GRAVITY, ITSAMUSBOMB_WAIT_T_VEL);
            DObjGetStruct(weapon_gobj)->rotate.z -= (ITSAMUSBOMB_WAIT_ROTATE_SPEED_AIR * ip->lr);
        }
        else
        {
            func_ovl3_80168044(weapon_gobj);
            DObjGetStruct(weapon_gobj)->rotate.z -= (ITSAMUSBOMB_WAIT_ROTATE_SPEED_GROUND * ip->lr);
        }

        ip->item_vars.samus_bomb.bomb_blink_timer--;

        if (ip->item_vars.samus_bomb.bomb_blink_timer == 0)
        {
            MObj *image = DObjGetStruct(weapon_gobj)->mobj;

            image->anim_frame = (image->anim_frame != 0) ? 0.0F : 1.0F;

            if (ip->lifetime > ITSAMUSBOMB_WAIT_BLINK_SLOW)
            {
                ip->item_vars.samus_bomb.bomb_blink_timer = ITSAMUSBOMB_WAIT_BLINK_TIMER_SLOW;
            }
            else if (ip->lifetime > ITSAMUSBOMB_WAIT_BLINK_MID)
            {
                ip->item_vars.samus_bomb.bomb_blink_timer = ITSAMUSBOMB_WAIT_BLINK_TIMER_MID;
            }
            else
            {
                ip->item_vars.samus_bomb.bomb_blink_timer = ITSAMUSBOMB_WAIT_BLINK_TIMER_FAST;
            }
        }
    }
    return FALSE;
}

bool32 jtgt_ovl3_80169108(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Vec3f *vel;
    bool32 is_collide;

    if (ip->ground_or_air == air)
    {
        is_collide = func_ovl3_80167B58(weapon_gobj);

        if (func_ovl3_80167C38(weapon_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), ITSAMUSBOMB_WAIT_COLLIDE_MOD_VEL, NULL) != FALSE)
        {
            wpMain_VelSetLR(weapon_gobj);
        }
        if (is_collide != FALSE)
        {
            vel = &ip->phys_info.vel;

            func_ovl0_800C7B08(vel, &ip->coll_data.ground_angle);
            func_ovl0_800C7AE0(vel, 0.6F);
            wpMain_VelSetLR(weapon_gobj);

            if (func_ovl0_800C7A84(vel) < 8.0F)
            {
                wpMap_SetGround(ip);
            }
        }
    }
    else if (func_ovl3_8016796C(weapon_gobj) == FALSE)
    {
        wpMap_SetAir(ip);
    }
    return FALSE;
}

bool32 jtgt_ovl3_801691FC(GObj *weapon_gobj)
{
    func_800269C0(0U);
    func_ovl2_801005C8(&DObjGetStruct(weapon_gobj)->translate);
    func_ovl3_80168F2C(weapon_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8016923C(GObj *weapon_gobj)
{
    func_800269C0(0U);
    func_ovl2_801005C8(&DObjGetStruct(weapon_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_80169274(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    wpMain_VelSetLR(weapon_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801692C4(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    ip->lifetime = ITSAMUSBOMB_WAIT_LIFETIME;

    if (ip->ground_or_air == air)
    {
        wpMain_ReflectorInvertLR(ip, fp);
        wpMain_VelSetLR(weapon_gobj);
    }
    else
    {
        ip->lr = fp->lr;
    }
    return FALSE;
}

extern WeaponSpawnData Item_SamusBomb_Desc;

GObj* func_ovl3_80169328(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_SamusBomb_Desc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->lifetime = ITSAMUSBOMB_WAIT_LIFETIME;

    ip->item_vars.samus_bomb.bomb_blink_timer = ITSAMUSBOMB_WAIT_BLINK_TIMER_SLOW;

    ip->phys_info.vel.y = ITSAMUSBOMB_WAIT_VEL_Y;

    return weapon_gobj;
}
