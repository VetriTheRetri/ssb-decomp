#include "item.h"

extern intptr_t Porygon_Event;
extern itCreateDesc Article_Porygon_Data;

void func_ovl3_80183B10(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);
    itHitParty *hit_desc = (itHitParty*) ((uintptr_t)*Article_Porygon_Data.p_file + (intptr_t)&Porygon_Event); // Linker thing

    if (ap->it_multi == hit_desc[ap->item_event_index].timer)
    {
        ap->item_hit.angle = hit_desc[ap->item_event_index].angle;
        ap->item_hit.damage = hit_desc[ap->item_event_index].damage;
        ap->item_hit.size = hit_desc[ap->item_event_index].size;
        ap->item_hit.knockback_scale = hit_desc[ap->item_event_index].knockback_scale;
        ap->item_hit.knockback_weight = hit_desc[ap->item_event_index].knockback_weight;
        ap->item_hit.knockback_base = hit_desc[ap->item_event_index].knockback_base;
        ap->item_hit.element = hit_desc[ap->item_event_index].element;
        ap->item_hit.rebound = hit_desc[ap->item_event_index].rebound;
        ap->item_hit.shield_damage = hit_desc[ap->item_event_index].shield_damage;
        ap->item_hit.hit_sfx = hit_desc[ap->item_event_index].hit_sfx;

        ap->item_event_index++;

        if (ap->item_event_index == 2)
        {
            ap->item_event_index = 1;
        }
    }
    ap->it_multi++;

    if (ap->it_multi == ITPORYGON_SHAKE_STOP_WAIT)
    {
        Vec3f pos = DObjGetStruct(item_gobj)->translate;

        pos.y = 0.0F;

        func_ovl2_800FF048(&pos, LEFT, 1.0F);
    }
}

bool32 func_ovl3_80183C84(GObj *item_gobj)
{
    itStruct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->translate.x += ap->item_vars.porygon.offset.x;
    joint->translate.y += ap->item_vars.porygon.offset.y;

    func_ovl3_80183B10(item_gobj);

    if ((f32)FLOAT_NEG_MAX == joint->dobj_f0)
    {
        func_ovl2_8010B0B8();

        return TRUE;
    }
    else return FALSE;
}

GObj* jtgt_ovl3_80183D00(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Porygon_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        itStruct *ap = itGetStruct(item_gobj);

        ap->item_vars.porygon.offset = *pos;

        ap->is_allow_knockback = TRUE;

        ap->it_multi = 0;

        ap->item_event_index = 0;

        func_800269C0(0x22CU);
    }
    return item_gobj;
}