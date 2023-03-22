#include "item.h"
#include "fighter.h"

#include <game/src/sys/obj_renderer.h>
#include <game/include/PR/gu.h>
#include <game/include/PR/mbi.h>
#include <game/include/PR/sp.h>



bool32 func_ovl3_8016BF50(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (ip->item_vars.egg_throw.is_throw == FALSE)
    {
        return FALSE;
    }
    else return TRUE;
}

bool32 func_ovl3_8016BF74(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8016BFA0(GObj *item_gobj) // Egg Throw explodes from landing successfully
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    ip->lifetime = ITEGGTHROW_EXPLODE_LIFETIME;

    ip->item_hit.can_deflect = FALSE;
    ip->item_hit.can_reflect = FALSE;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_hit.size = ITEGGTHROW_EXPLODE_SIZE;

    DObjGetStruct(item_gobj)->display_list = NULL;

    ip->cb_anim = func_ovl3_8016BF74;
    ip->cb_coll = NULL;
    ip->cb_give_damage = NULL;
    ip->cb_shield_block = NULL;
    ip->cb_shield_deflect = NULL;
    ip->cb_attack = NULL;
    ip->cb_reflect = NULL;
}

void func_ovl3_8016C00C(GObj *item_gobj) // Egg Throw explodes from expiring 
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    ip->lifetime = ITEGGTHROW_EXPLODE_LIFETIME;

    ip->item_hit.can_reflect = FALSE;
    ip->item_hit.can_shield = FALSE;

    ip->phys_info.vel.z = 0.0F;
    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_hit.size = ITEGGTHROW_EXPLODE_SIZE;

    DObjGetStruct(item_gobj)->display_list = NULL;

    ip->cb_anim = func_ovl3_8016BF74;
    ip->cb_coll = NULL;
    ip->cb_give_damage = NULL;
    ip->cb_shield_block = NULL;
    ip->cb_shield_deflect = NULL;
    ip->cb_attack = NULL;
    ip->cb_reflect = NULL;
}

void func_ovl3_8016C07C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    f32 angle = ABS(ip->item_vars.egg_throw.stick_range) / ITEGGTHROW_TRAJECTORY_DIV;

    if (angle > 1.0F)
    {
        angle = 1.0F;
    }

    angle *= ITEGGTHROW_ANGLE_MUL;

    if (angle < ITEGGTHROW_ANGLE_CLAMP)
    {
        angle = 0.0F;
    }

    angle *= ((ip->item_vars.egg_throw.stick_range < 0) ? LEFT : RIGHT);

    angle = (ip->item_vars.egg_throw.lr > 0) ? ITEGGTHROW_TRAJECTORY_SUB_RIGHT - angle : ITEGGTHROW_TRAJECTORY_SUB_LEFT - angle;

    ip->phys_info.vel.y = __sinf(angle) * ((ip->item_vars.egg_throw.throw_force * ITEGGTHROW_VEL_FORCE_MUL) + ITEGGTHROW_VEL_ADD);
    ip->phys_info.vel.x = cosf(angle) * ((ip->item_vars.egg_throw.throw_force * ITEGGTHROW_VEL_FORCE_MUL) + ITEGGTHROW_VEL_ADD);

    ip->item_vars.egg_throw.angle = ((((ip->item_vars.egg_throw.throw_force * ITEGGTHROW_ANGLE_FORCE_MUL) + ITEGGTHROW_ANGLE_ADD) * PI32) / 180.0F); // Deg2Rad macro pls

    DObjGetStruct(item_gobj)->translate.z = 0.0F;

    ip->item_hit.update_state = gmHitCollision_UpdateState_New;

    func_ovl3_80165F60(item_gobj);
}

bool32 jtgt_ovl3_8016C218(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (ip->item_vars.egg_throw.is_spin != FALSE)
    {
        if (func_ovl3_80167FE8(ip) != FALSE)
        {
            func_800269C0(0xFCU);

            func_ovl2_80103A88(&DObjGetStruct(item_gobj)->translate);
            func_ovl2_801041A0(&DObjGetStruct(item_gobj)->translate);

            func_ovl3_8016C00C(item_gobj);

            return FALSE;
        }
        else
        {
            DObjGetStruct(item_gobj)->rotate.z += ip->item_vars.egg_throw.angle;
            func_ovl3_80168088(ip, ITEGGTHROW_GRAVITY, ITEGGTHROW_T_VEL);

            return FALSE;
        }
    }
    else if (ip->item_vars.egg_throw.is_throw != FALSE)
    {
        ip->item_vars.egg_throw.is_spin = TRUE;

        func_ovl3_8016C07C(item_gobj);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016C2E0(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if ((ip->item_vars.egg_throw.is_spin != FALSE) && (func_ovl3_80167C04(item_gobj) != FALSE))
    {
        func_ovl2_801008F4(2);

        func_800269C0(0xFCU);

        func_ovl2_80103A88(&DObjGetStruct(item_gobj)->translate);
        func_ovl2_801041A0(&DObjGetStruct(item_gobj)->translate);

        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

        func_ovl3_8016BFA0(item_gobj);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016C364(GObj *item_gobj)
{
    func_800269C0(0xFCU);

    func_ovl2_80103A88(&DObjGetStruct(item_gobj)->translate);
    func_ovl2_801041A0(&DObjGetStruct(item_gobj)->translate);

    func_ovl3_8016BFA0(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8016C3B4(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    func_ovl3_80167FA0(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8016C404(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    ip->lifetime = ITEGGTHROW_LIFETIME;

    func_ovl3_801680EC(ip, fp);
    func_ovl3_80167FA0(item_gobj);

    return FALSE;
}

void func_ovl3_8016C444(GObj *item_gobj)
{
    gDPPipeSync(D_800465B0[1]++);

    gDPSetEnvColor(D_800465B0[1]++, 0, 0, 0, 0);

    func_ovl3_801675D0(item_gobj);
}

extern ItemSpawnData Item_EggThrow_Desc;

GObj* func_ovl3_8016C498(GObj *fighter_gobj, Vec3f *pos)
{
    Fighter_Struct *fp = fighter_gobj->user_data;
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_EggThrow_Desc, pos, ITEM_MASK_SPAWN_FIGHTER);
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }

    ip = ItemGetStruct(item_gobj);

    item_gobj->renderer = func_ovl3_8016C444;

    ip->item_vars.egg_throw.is_throw = FALSE;

    ip->cb_destroy = func_ovl3_8016BF50;

    ip->lifetime = ITEGGTHROW_LIFETIME;

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ip->is_camera_follow = TRUE;

    ip->phys_info.vel.y = 0.0F;
    ip->phys_info.vel.x = 0.0F;

    ip->item_vars.egg_throw.is_spin = ip->item_vars.egg_throw.is_throw;
    ip->item_vars.egg_throw.lr = fp->lr;

    return item_gobj;
}