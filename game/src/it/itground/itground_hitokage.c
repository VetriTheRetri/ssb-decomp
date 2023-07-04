#include "item.h"
#include "weapon.h"
#include "fighter.h"

extern itStatusDesc Item_Hitokage_Status[];

void func_ovl3_80183DA0(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Item_Hitokage_Status, 0);

    itGetStruct(item_gobj)->proc_dead = func_ovl3_80183F88;
}

bool32 func_ovl3_80183DE0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f pos;

    joint->translate.x += ap->item_vars.hitokage.offset.x;
    joint->translate.y += ap->item_vars.hitokage.offset.y;

    pos = joint->translate;

    pos.x += ITHITOKAGE_FLAME_SPAWN_OFF_X;

    if ((ap->item_vars.hitokage.flags == 2) || 
    ((ap->item_vars.hitokage.flags & 1) && (joint->dobj_f2 >= ITHITOKAGE_FLAME_SPAWN_BEGIN)) && 
    (joint->dobj_f2 <= ITHITOKAGE_FLAME_SPAWN_END))
    {
        joint->mobj->index = 1;

        if (ap->item_vars.hitokage.flame_spawn_wait <= 0)
        {
            func_ovl3_801843C4(item_gobj, &pos);

            ap->item_vars.hitokage.flame_spawn_wait = ITHITOKAGE_FLAME_SPAWN_WAIT;
        }
        else
        {
            ap->item_vars.hitokage.flame_spawn_wait--;
        }
    }
    else
    {
        joint->mobj->index = 0;
    }

    if ((f32)FLOAT_NEG_MAX == joint->dobj_f0)
    {
        func_ovl2_8010B0B8();

        return TRUE;
    }
    return FALSE;
}

bool32 jtgt_ovl3_80183F20(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint;

    itMain_UpdatePhysicsAir(ap, ITHITOKAGE_GRAVITY, ITHITOKAGE_T_VEL);

    joint = DObjGetStruct(item_gobj);

    joint->rotate.z -= (ITHITOKAGE_HIT_ROTATE_Z * ap->lr);

    return FALSE;
}

bool32 func_ovl3_80183F88(GObj *item_gobj)
{
    return TRUE;
}

bool32 jtgt_ovl3_80183F94(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    if (ap->damage_knockback >= 100.0F)
    {
        f32 angle = gmCommon_Damage_GetKnockbackAngle(ap->damage_angle, ap->ground_or_air, ap->damage_knockback);

        ap->phys_info.vel_air.x = cosf(angle) * ap->damage_knockback * -ap->lr_damage;
        ap->phys_info.vel_air.y = __sinf(angle) * ap->damage_knockback;

        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;
        ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

        joint->dobj_f0 = (f32)FLOAT_NEG_MAX;

        func_ovl2_8010B0AC();
        func_ovl3_80183DA0(item_gobj);
    }
    return FALSE;
}

extern s32 D_ovl2_8012EB60;
extern itCreateDesc Item_Hitokage_Data;

GObj* jtgt_ovl3_80184058(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Item_Hitokage_Data, pos, vel, flags);
    s32 unused;
    DObj *joint;
    Item_Struct *ap;

    if (item_gobj != NULL)
    {
        ap = itGetStruct(item_gobj);
        joint = DObjGetStruct(item_gobj);

        ap->item_vars.hitokage.flame_spawn_wait = 0;
        ap->item_vars.hitokage.offset = *pos;

        ap->is_allow_knockback = TRUE;

        ap->item_vars.hitokage.flags = rand_u16_range(4);

        if ((D_ovl2_8012EB60 == ap->item_vars.hitokage.flags) || (ap->item_vars.hitokage.flags & D_ovl2_8012EB60))
        {
            ap->item_vars.hitokage.flags++;

            ap->item_vars.hitokage.flags &= 3;
        }
        if (ap->item_vars.hitokage.flags == 2)
        {
            joint->mobj->index = 1;
        }
        D_ovl2_8012EB60 = ap->item_vars.hitokage.flags;

        func_800269C0(0x229U);
    }
    return item_gobj;
}

bool32 jtgt_ovl3_8018415C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80184188(GObj *weapon_gobj)
{
    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_801841CC(GObj *weapon_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

    return FALSE;
}

extern s32 D_ovl3_8018D044;

bool32 jtgt_ovl3_80184204(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);
    Vec3f *translate;

    ip->lifetime = ITHITOKAGE_FLAME_LIFETIME;

    wpMain_ReflectorInvertLR(ip, fp);

    translate = &DObjGetStruct(weapon_gobj)->translate;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, translate->x, translate->y, 0.0F, ip->phys_info.vel_air.x, ip->phys_info.vel_air.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, translate->x, translate->y, 0.0F, ip->phys_info.vel_air.x, ip->phys_info.vel_air.y, 0.0F);

    return FALSE;
}

extern wpCreateDesc Weapon_Hitokage_Flame_Data;

GObj *func_ovl3_801842C8(GObj *item_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(item_gobj, &Weapon_Hitokage_Flame_Data, pos, WEAPON_MASK_SPAWN_ARTICLE);
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->phys_info.vel = *vel;

    ip->lifetime = ITHITOKAGE_FLAME_LIFETIME;

    ip->lr = LEFT;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, pos->x, pos->y, 0.0F, ip->phys_info.vel_air.x, ip->phys_info.vel_air.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, pos->x, pos->y, 0.0F, ip->phys_info.vel_air.x, ip->phys_info.vel_air.y, 0.0F);

    return weapon_gobj;
}

void func_ovl3_801843C4(GObj *item_gobj, Vec3f *pos)
{
    Item_Struct *ap;
    Vec3f vel;

    vel.x = cosf(ITHITOKAGE_FLAME_SPAWN_ANGLE) * -ITHITOKAGE_FLAME_VEL_XY;
    vel.y = __sinf(ITHITOKAGE_FLAME_SPAWN_ANGLE) * ITHITOKAGE_FLAME_VEL_XY;
    vel.z = 0.0F;

    func_ovl3_801842C8(item_gobj, pos, &vel);
    func_800269C0(0x88U);
}