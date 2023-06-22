#include "item.h"

void func_ovl3_801837A0(GObj *item_gobj)
{
    s32 unused;
    Effect_Unk *ep;
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ATMARUMINE_EXPLODE_GFX_SCALE;
        ep->effect_info->scale.y = ATMARUMINE_EXPLODE_GFX_SCALE;
        ep->effect_info->scale.z = ATMARUMINE_EXPLODE_GFX_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(item_gobj)->unk_0x54 = 2;

    ap->item_hit.hit_sfx = 1;

    func_ovl3_8017275C(item_gobj);
    func_ovl3_80183A20(item_gobj);
}

extern intptr_t Marumine_Event;
extern itCreateDesc Article_Marumine_Data;

void func_ovl3_80183830(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    itHitEvent *ev = (itHitEvent*) ((uintptr_t)*Article_Marumine_Data.p_file + (intptr_t)&Marumine_Event); // Linker thing

    if (ap->it_multi == ev[ap->item_event_index].timer)
    {
        ap->item_hit.angle = ev[ap->item_event_index].angle;
        ap->item_hit.damage = ev[ap->item_event_index].damage;
        ap->item_hit.size = ev[ap->item_event_index].size;

        ap->item_hit.can_reflect = FALSE;
        ap->item_hit.can_shield = FALSE;

        ap->item_hit.element = gmHitCollision_Element_Fire;

        ap->item_hit.clang = FALSE;

        ap->item_event_index++;

        if (ap->item_event_index == 4)
        {
            ap->item_event_index = 3;
        }
    }
}

bool32 func_ovl3_80183914(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->translate.x += ap->item_vars.marumine.offset.x;
    joint->translate.y += ap->item_vars.marumine.offset.y;

    if ((f32)FLOAT_NEG_MAX == joint->dobj_f0)
    {
        func_ovl3_8017275C(item_gobj);
        func_ovl3_8017279C(item_gobj);

        ap->item_vars.marumine.offset.x = 0.0F;
        ap->item_vars.marumine.offset.y = 0.0F;

        func_ovl3_801837A0(item_gobj);
        func_800269C0(1U);
    }
    return FALSE;
}

bool32 func_ovl3_801839A8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->translate.x += ap->item_vars.marumine.offset.x;
    joint->translate.y += ap->item_vars.marumine.offset.y;

    func_ovl3_80183830(item_gobj);

    ap->it_multi++;

    if (ap->it_multi == ATMARUMINE_EXPLODE_LIFETIME)
    {
        func_ovl2_8010B0B8();

        return TRUE;
    }
    else return FALSE;
}

extern itStatusDesc Article_Marumine_Status[];

void func_ovl3_80183A20(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->it_multi = 0;

    ap->item_hit.stale = ITEM_STALE_DEFAULT;

    ap->item_event_index = 0;

    func_ovl3_80183830(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Marumine_Status, 0);
}

GObj* jtgt_ovl3_80183A74(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Marumine_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);
        DObj *joint = DObjGetStruct(item_gobj);

        ap->item_vars.marumine.offset = *pos;

        ap->is_allow_knockback = TRUE;

        func_80008CC0(joint, 0x46U, 0U);
        func_800269C0(0x22BU);
    }
    return item_gobj;
}