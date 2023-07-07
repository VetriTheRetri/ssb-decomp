#include "item.h"
#include "weapon.h"

bool32 func_ovl3_80182C80(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);

    if (ap->it_multi == 0)
    {
        return TRUE;
    }
    ap->it_multi--;

    return FALSE;
}

extern itStatusDesc Article_Dogas_Status[];

void func_ovl3_80182CA8(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);

    ap->it_multi = ITDOGAS_DESPAWN_WAIT;

    itMain_SetItemStatus(item_gobj, Article_Dogas_Status, 1);
}

void func_ovl3_80182CDC(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f pos;
    Vec3f vel;

    if (ap->item_vars.dogas.smog_spawn_wait <= 0)
    {
        vel.x = ITDOGAS_SMOG_VEL_XY;
        vel.y = ITDOGAS_SMOG_VEL_XY;
        vel.z = 0.0F;

        pos = joint->translate;

        pos.x += (rand_f32() * ITDOGAS_SMOG_MUL_OFF_X) - ITDOGAS_SMOG_SUB_OFF_X;
        pos.y += (rand_f32() * ITDOGAS_SMOG_MUL_OFF_Y) - ATDGOAS_SMOG_SUB_OFF_Y;

        if (pos.x < joint->translate.x)
        {
            vel.x = -vel.x;
        }
        if (pos.y < joint->translate.y)
        {
            vel.y = -vel.y;
        }
        func_ovl3_80183144(item_gobj, &pos, &vel);
        func_800269C0(0x83U);

        ap->item_vars.dogas.smog_spawn_wait = ITDOGAS_SMOG_SPAWN_WAIT;

        ap->it_multi--;
    }
}

bool32 func_ovl3_80182E1C(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);

    func_ovl3_80182CDC(item_gobj);

    if (ap->it_multi == 0)
    {
        func_ovl3_80182CA8(item_gobj);

        return FALSE;
    }
    ap->item_vars.dogas.smog_spawn_wait--;

    return FALSE;
}

extern intptr_t D_NF_00012820;
extern intptr_t D_NF_000128DC;

void func_ovl3_80182E78(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    ap->it_multi = ITDOGAS_SMOG_SPAWN_COUNT;

    ap->item_vars.dogas.smog_spawn_wait = 0;

    if (ap->it_kind == It_Kind_Dogas)
    {
        ap->item_vars.dogas.pos = joint->translate;

        func_8000BD1C(joint->next, itGetPData(ap, D_NF_00012820, D_NF_000128DC), 0.0F); // Linker thing

        func_8000DF34(item_gobj);
        func_800269C0(0x135U);
    }
}

void func_ovl3_80182F0C(GObj *item_gobj)
{
    func_ovl3_80182E78(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Dogas_Status, 0);
}

bool32 jtgt_ovl3_80182F40(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);

    if (ap->it_multi == 0)
    {
        ap->phys_info.vel_air.y = 0.0F;
        ap->phys_info.vel_air.x = 0.0F;

        func_ovl3_80182F0C(item_gobj);
    }
    ap->it_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80182F94(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);

    if (func_ovl3_801737B8(item_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel_air.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_00013624;
extern itCreateDesc Article_Dogas_Data;

GObj *jtgt_ovl3_80182FD4(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Dogas_Data, pos, vel, flags);
    DObj *joint;
    itStruct *ap;

    if (item_gobj != NULL)
    {
        joint = item_gobj->obj;

        func_80008CC0(joint, 0x28U, 0U);
        func_80008CC0(joint->next, 0x1CU, 0U);

        joint->translate = *pos;

        ap = itGetStruct(item_gobj);

        joint->translate.y -= ap->attributes->objectcoll_bottom;

        ap->it_multi = ITMONSTER_RISE_STOP_WAIT;

        ap->phys_info.vel_air.x = 0.0F;
        ap->phys_info.vel_air.z = 0.0F;
        ap->phys_info.vel_air.y = ITMONSTER_RISE_VEL_Y;

        func_8000BD1C(joint->next, itGetPData(ap, D_NF_00012820, D_NF_00013624), 0.0F); // Linker thing
    }
    return item_gobj;
}

bool32 func_ovl3_801830DC(GObj *weapon_gobj)
{
    wpStruct *ip = wpGetStruct(weapon_gobj);
    DObj *joint = DObjGetStruct(weapon_gobj)->next;

    ip->weapon_hit.size = joint->scale.x * ip->weapon_vars.smog.hit_desc->size;

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

extern wpCreateDesc Item_Smog_Data;

GObj* func_ovl3_80183144(GObj *item_gobj, Vec3f *pos, Vec3f *vel)
{
    wpCreateDesc *p_data = &Item_Smog_Data;
    GObj *weapon_gobj = wpManager_CreateWeapon(item_gobj, &Item_Smog_Data, pos, WEAPON_MASK_SPAWN_ITEM);
    DObj *joint;
    wpStruct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->lifetime = ITDOGAS_SMOG_LIFETIME;

    ip->weapon_vars.smog.hit_desc = (wpCommonAttributes*) (*(uintptr_t*)p_data->p_item + (intptr_t)p_data->offset); // Dude I had a stroke trying to match this

    joint = DObjGetStruct(weapon_gobj);

    ip->phys_info.vel = *vel;

    func_80008CC0(joint->next, 0x2C, 0);

    joint->translate = *pos;

    return weapon_gobj;
}