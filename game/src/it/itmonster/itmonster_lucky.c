#include "item.h"
#include "gmmatch.h"

extern intptr_t D_NF_00010000;
extern intptr_t D_NF_000100BC;

void func_ovl3_80180FC0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    if (ap->it_kind == It_Kind_Mb_Lucky)
    {
        func_8000BD1C(joint->next, itGetPData(ap, D_NF_00010000, D_NF_000100BC), 0.0F); // Linker thing
        func_8000DF34(item_gobj);
    }
    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    ap->item_vars.mb_lucky.egg_spawn_wait = ATMBLUCKY_EGG_SPAWN_WAIT_CONST;

    ap->it_multi = ATMBLUCKY_EGG_SPAWN_COUNT;
}

bool32 jtgt_ovl3_80181048(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATMBLUCKY_GRAVITY, ATMBLUCKY_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_80181074(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80173680(item_gobj);

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        ap->phys_info.vel.y = 0.0F;

        if (ap->it_multi != 0)
        {
            func_ovl3_801813A8(item_gobj);
        }
        else func_ovl3_801813F8(item_gobj);
    }
    return FALSE;
}

extern itStatusDesc Article_Mb_Lucky_Status[];

void func_ovl3_801810E0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_Mb_Lucky_Status, 0);
}

bool32 jtgt_ovl3_80181124(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATMBLUCKY_GRAVITY, ATMBLUCKY_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_80181150(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80173680(item_gobj);

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_801813A8(item_gobj);

        func_ovl3_80180FC0(item_gobj);
    }
    return FALSE;
}

void func_ovl3_801811AC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->it_kind == It_Kind_Mb_Lucky)
    {
        func_800269C0(0x13AU);
    }
    itMain_SetItemStatus(item_gobj, Article_Mb_Lucky_Status, 1);
}

bool32 jtgt_ovl3_80181200(GObj *lucky_gobj)
{
    Item_Struct *lucky_ap = itGetStruct(lucky_gobj), *egg_ap;
    DObj *joint = DObjGetStruct(lucky_gobj);
    GObj *egg_gobj;
    s32 unused;
    Vec3f pos;
    Vec3f vel;

    if (lucky_ap->it_multi == 0)
    {
        func_ovl3_801813F8(lucky_gobj);

        return FALSE;
    }
    else
    {
        if (!lucky_ap->item_vars.mb_lucky.egg_spawn_wait)
        {
            if ((Match_Info->item_toggles & 8) && (Match_Info->item_switch != 0))
            {
                pos = joint->translate;

                vel.x = (rand_f32() * ATMBLUCKY_EGG_SPAWN_BASE_VEL) + ATMBLUCKY_EGG_SPAWN_ADD_VEL_X;
                vel.y = (rand_f32() * ATMBLUCKY_EGG_SPAWN_BASE_VEL) + ATMBLUCKY_EGG_SPAWN_ADD_VEL_Y;
                vel.z = 0.0F;

                egg_gobj = func_ovl3_8016EA78(lucky_gobj, It_Kind_Egg, &pos, &vel, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_ARTICLE));

                if (egg_gobj != NULL)
                {
                    egg_ap = itGetStruct(egg_gobj);

                    func_800269C0(0xCAU);

                    lucky_ap->item_vars.mb_lucky.egg_spawn_wait = ATMBLUCKY_EGG_SPAWN_WAIT_CONST;
                    lucky_ap->it_multi--;

                    func_ovl2_800FF048(&pos, egg_ap->lr, 1.0F);
                }
            }
            else
            {
                lucky_ap->item_vars.mb_lucky.egg_spawn_wait = ATMBLUCKY_EGG_SPAWN_WAIT_CONST;

                lucky_ap->it_multi--;
            }
        }
        if (lucky_ap->item_vars.mb_lucky.egg_spawn_wait > 0)
        {
            lucky_ap->item_vars.mb_lucky.egg_spawn_wait--;
        }
    }
    return FALSE;
}

bool32 jtgt_ovl3_80181368(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_801810E0);

    return FALSE;
}

bool32 jtgt_ovl3_80181390(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_vars.mb_lucky.egg_spawn_wait += ATMBLUCKY_EGG_SPAWN_WAIT_ADD;

    return FALSE;
}

void func_ovl3_801813A8(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Mb_Lucky_Status, 2);
}

bool32 jtgt_ovl3_801813D0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->item_vars.mb_lucky.lifetime == 0)
    {
        return TRUE;
    }
    ap->item_vars.mb_lucky.lifetime--;

    return FALSE;
}

void func_ovl3_801813F8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_vars.mb_lucky.lifetime = ATMBLUCKY_LIFETIME;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    itMain_SetItemStatus(item_gobj, Article_Mb_Lucky_Status, 3);
}

bool32 jtgt_ovl3_80181430(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->it_multi == 0)
    {
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_801811AC(item_gobj);
    }
    ap->it_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80181480(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_801737B8(item_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_00013624;
extern itCreateDesc Article_Mb_Lucky_Data;

GObj *jtgt_ovl3_801814C0(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Mb_Lucky_Data, pos, vel, flags);
    DObj *joint;
    Item_Struct *ap;

    if (item_gobj != NULL)
    {
        joint = DObjGetStruct(item_gobj);

        func_80008CC0(joint->next, 0x2CU, 0U);

        joint->translate = *pos;

        ap = itGetStruct(item_gobj);

        ap->it_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        joint->translate.y -= ap->attributes->objectcoll_bottom;

        func_8000BD1C(joint->next, itGetPData(ap, D_NF_00010000, D_NF_00013624), 0.0F); // Linker thing
    }
    return item_gobj;
}