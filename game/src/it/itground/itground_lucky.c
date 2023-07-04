#include "item.h"
#include "gmmatch.h"

extern itStatusDesc Article_Gr_Lucky_Status[];

void func_ovl3_8017C240(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Gr_Lucky_Status, 0);

    itGetStruct(item_gobj)->proc_dead = func_ovl3_8017C524;
}

void func_ovl3_8017C280(GObj *lucky_gobj)
{
    Item_Struct *lucky_ap = itGetStruct(lucky_gobj);
    Item_Struct *egg_ap;
    s32 unused;
    DObj *joint = DObjGetStruct(lucky_gobj);
    GObj *egg_gobj;
    Vec3f pos;
    Vec3f vel;

    if (lucky_ap->it_multi == 0)
    {
        if (lucky_ap->item_vars.gr_lucky.egg_spawn_wait != 0)
        {
            if ((Match_Info->item_toggles & 8) && (Match_Info->item_switch != 0)) // Return to this when 0x8 is mapped
            {
                pos = joint->translate;

                pos.x -= ITGRLUCKY_EGG_SPAWN_OFF_X;
                pos.y += ITGRLUCKY_EGG_SPAWN_OFF_Y;

                vel.x = -((rand_f32() * ITGRLUCKY_EGG_SPAWN_MUL) + ITGRLUCKY_EGG_SPAWN_ADD_X);
                vel.y = (rand_f32() * ITGRLUCKY_EGG_SPAWN_MUL) + ITGRLUCKY_EGG_SPAWN_ADD_Y;
                vel.z = 0.0F;

                egg_gobj = func_ovl3_8016EA78(lucky_gobj, It_Kind_Egg, &pos, &vel, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_ITEM));

                if (egg_gobj != NULL)
                {
                    egg_ap = itGetStruct(egg_gobj);

                    func_800269C0(0xCAU);

                    lucky_ap->it_multi = 10;
                    lucky_ap->item_vars.gr_lucky.egg_spawn_wait--;

                    func_ovl2_800FF048(&pos, egg_ap->lr, 1.0F);
                }
            }
            else
            {
                lucky_ap->it_multi = 10;
                lucky_ap->item_vars.gr_lucky.egg_spawn_wait--;
            }
        }
    }
    if (lucky_ap->item_vars.gr_lucky.egg_spawn_wait != 0)
    {
        if (lucky_ap->it_multi > 0)
        {
            lucky_ap->it_multi--;
        }
    }
}

bool32 func_ovl3_8017C400(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->translate.x += ap->item_vars.gr_lucky.pos.x;
    joint->translate.y += ap->item_vars.gr_lucky.pos.y;

    if ((joint->dobj_f2 >= ITGRLUCKY_EGG_SPAWN_BEGIN) && (joint->dobj_f2 <= ITGRLUCKY_EGG_SPAWN_END))
    {
        func_ovl3_8017C280(item_gobj);
    }
    if ((f32)FLOAT_NEG_MAX == joint->dobj_f0)
    {
        func_ovl2_8010B0B8();

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_8017C4AC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    return FALSE;
}

bool32 jtgt_ovl3_8017C4BC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint;

    itMain_UpdatePhysicsAir(ap, ITGRLUCKY_GRAVITY, ITGRLUCKY_T_VEL);

    joint = DObjGetStruct(item_gobj);

    joint->rotate.z -= ITGRLUCKY_HIT_ROTATE_Z * ap->lr;

    return FALSE;
}

bool32 func_ovl3_8017C524(GObj *item_gobj)
{
    return TRUE;
}

bool32 jtgt_ovl3_8017C530(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    if (ap->damage_knockback >= 100.0F)
    {
        f32 angle = gmCommon_Damage_GetKnockbackAngle(ap->damage_angle, ap->ground_or_air, ap->damage_knockback);

        ap->phys_info.vel_air.x = (cosf(angle) * ap->damage_knockback * -ap->lr_damage);
        ap->phys_info.vel_air.y = (__sinf(angle) * ap->damage_knockback);

        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;
        ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

        joint->dobj_f0 = (f32)FLOAT_NEG_MAX;

        func_ovl2_8010B0AC();
        func_ovl3_8017C240(item_gobj);
    }
    return FALSE;
}

extern itCreateDesc Article_Gr_Lucky_Data;

GObj* jtgt_ovl3_8017C5F4(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Gr_Lucky_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        ap->item_hit.interact_mask = GMHITCOLLISION_MASK_FIGHTER;

        ap->item_vars.gr_lucky.pos = *pos;

        ap->is_allow_knockback = TRUE;

        ap->it_multi = 0;

        ap->item_vars.gr_lucky.egg_spawn_wait = ITGRLUCKY_EGG_SPAWN_WAIT;

        func_800269C0(0x22AU);
    }
    return item_gobj;
}
