#include "article.h"

extern intptr_t Porygon_Event;
extern itCreateDesc Article_Porygon_Data;

void func_ovl3_80183B10(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    ArticleHitDesc *hit_desc = (ArticleHitDesc*) ((uintptr_t)*Article_Porygon_Data.p_file + (intptr_t)&Porygon_Event); // Linker thing

    if (ap->at_multi == hit_desc[ap->x340_flag_b0123].timer)
    {
        ap->item_hit.angle = hit_desc[ap->x340_flag_b0123].angle;
        ap->item_hit.damage = hit_desc[ap->x340_flag_b0123].damage;
        ap->item_hit.size = hit_desc[ap->x340_flag_b0123].size;
        ap->item_hit.knockback_scale = hit_desc[ap->x340_flag_b0123].knockback_scale;
        ap->item_hit.knockback_weight = hit_desc[ap->x340_flag_b0123].knockback_weight;
        ap->item_hit.knockback_base = hit_desc[ap->x340_flag_b0123].knockback_base;
        ap->item_hit.element = hit_desc[ap->x340_flag_b0123].element;
        ap->item_hit.clang = hit_desc[ap->x340_flag_b0123].clang;
        ap->item_hit.shield_damage = hit_desc[ap->x340_flag_b0123].shield_damage;
        ap->item_hit.hit_sfx = hit_desc[ap->x340_flag_b0123].hit_sfx;

        ap->x340_flag_b0123++;

        if (ap->x340_flag_b0123 == 2)
        {
            ap->x340_flag_b0123 = 1;
        }
    }
    ap->at_multi++;

    if (ap->at_multi == ATPORYGON_SHAKE_STOP_WAIT)
    {
        Vec3f pos = DObjGetStruct(item_gobj)->translate;

        pos.y = 0.0F;

        func_ovl2_800FF048(&pos, LEFT, 1.0F);
    }
}

bool32 func_ovl3_80183C84(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->translate.x += ap->article_vars.porygon.offset.x;
    joint->translate.y += ap->article_vars.porygon.offset.y;

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
        Item_Struct *ap = itGetStruct(item_gobj);

        ap->article_vars.porygon.offset = *pos;

        ap->x2D3_flag_b4 = TRUE;

        ap->at_multi = 0;

        ap->x340_flag_b0123 = 0;

        func_800269C0(0x22CU);
    }
    return item_gobj;
}