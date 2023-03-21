#include "item.h"
#include "fighter.h"

bool32 func_ovl3_80168F00(GObj *item_gobj)
{
    if (func_ovl3_80167FE8(ItemGetStruct(item_gobj)) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80168F2C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    ip->lifetime = ITSAMUSBOMB_EXPLODE_LIFETIME;

    ip->item_hit.flags_0x48_b1 = TRUE;
    ip->item_hit.can_deflect = FALSE;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_hit.size = ITSAMUSBOMB_EXPLODE_RADIUS;

    DObjGetStruct(item_gobj)->display_list = NULL;

    ip->cb_anim = func_ovl3_80168F00;
    ip->cb_coll = NULL;
    ip->cb_give_damage = NULL;
    ip->cb_shield_block = NULL;
    ip->cb_shield_deflect = NULL;
    ip->cb_attack = NULL;
    ip->cb_reflect = NULL;
}

bool32 jtgt_ovl3_80168F98(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        func_ovl2_801005C8(&DObjGetStruct(item_gobj)->translate);
        func_ovl3_80168F2C(item_gobj);
        func_800269C0(0U);

        return FALSE;
    }
    else
    {
        if (ip->ground_or_air == air)
        {
            func_ovl3_80168088(ip, ITSAMUSBOMB_WAIT_GRAVITY, ITSAMUSBOMB_WAIT_T_VEL);
            DObjGetStruct(item_gobj)->rotate.z -= (ITSAMUSBOMB_WAIT_ROTATE_SPEED_AIR * ip->lr);
        }
        else
        {
            func_ovl3_80168044(item_gobj);
            DObjGetStruct(item_gobj)->rotate.z -= (ITSAMUSBOMB_WAIT_ROTATE_SPEED_GROUND * ip->lr);
        }

        ip->item_vars.samus_bomb.bomb_blink_timer--;

        if (ip->item_vars.samus_bomb.bomb_blink_timer == 0)
        {
            MObj *image = DObjGetStruct(item_gobj)->mobj;

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

bool32 jtgt_ovl3_80169108(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Vec3f *vel;
    bool32 is_collide;

    if (ip->ground_or_air == air)
    {
        is_collide = func_ovl3_80167B58(item_gobj);

        if (func_ovl3_80167C38(item_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), ITSAMUSBOMB_WAIT_COLLIDE_MOD_VEL, NULL) != FALSE)
        {
            func_ovl3_80167F68(item_gobj);
        }
        if (is_collide != FALSE)
        {
            vel = &ip->phys_info.vel;

            func_ovl0_800C7B08(vel, &ip->coll_data.ground_angle);
            func_ovl0_800C7AE0(vel, 0.6F);
            func_ovl3_80167F68(item_gobj);

            if (func_ovl0_800C7A84(vel) < 8.0F)
            {
                func_ovl3_80167E78(ip);
            }
        }
    }
    else if (func_ovl3_8016796C(item_gobj) == FALSE)
    {
        func_ovl3_80167E9C(ip);
    }
    return FALSE;
}

bool32 jtgt_ovl3_801691FC(GObj *item_gobj)
{
    func_800269C0(0U);
    func_ovl2_801005C8(&DObjGetStruct(item_gobj)->translate);
    func_ovl3_80168F2C(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8016923C(GObj *item_gobj)
{
    func_800269C0(0U);
    func_ovl2_801005C8(&DObjGetStruct(item_gobj)->translate);

    return TRUE;
}

bool32 jtgt_ovl3_80169274(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);
    func_ovl3_80167F68(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801692C4(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    ip->lifetime = ITSAMUSBOMB_WAIT_LIFETIME;

    if (ip->ground_or_air == air)
    {
        func_ovl3_801680EC(ip, fp);
        func_ovl3_80167F68(item_gobj);
    }
    else
    {
        ip->lr = fp->lr;
    }
    return FALSE;
}

extern ItemSpawnData Item_SamusBomb_Desc;

GObj* func_ovl3_80169328(GObj *fighter_gobj, Vec3f *pos)
{
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_SamusBomb_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->lifetime = ITSAMUSBOMB_WAIT_LIFETIME;

    ip->item_vars.samus_bomb.bomb_blink_timer = ITSAMUSBOMB_WAIT_BLINK_TIMER_SLOW;

    ip->phys_info.vel.y = ITSAMUSBOMB_WAIT_VEL_Y;

    return item_gobj;
}
