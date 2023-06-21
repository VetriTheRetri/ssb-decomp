#include "article.h"

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
    ArticleHitEvent *ev = (ArticleHitEvent*) ((uintptr_t)*Article_Marumine_Data.p_file + (intptr_t)&Marumine_Event); // Linker thing

    if (ap->at_multi == ev[ap->x340_flag_b0123].timer)
    {
        ap->item_hit.angle = ev[ap->x340_flag_b0123].angle;
        ap->item_hit.damage = ev[ap->x340_flag_b0123].damage;
        ap->item_hit.size = ev[ap->x340_flag_b0123].size;

        ap->item_hit.can_reflect = FALSE;
        ap->item_hit.can_shield = FALSE;

        ap->item_hit.element = gmHitCollision_Element_Fire;

        ap->item_hit.clang = FALSE;

        ap->x340_flag_b0123++;

        if (ap->x340_flag_b0123 == 4)
        {
            ap->x340_flag_b0123 = 3;
        }
    }
}

bool32 func_ovl3_80183914(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->translate.x += ap->article_vars.marumine.offset.x;
    joint->translate.y += ap->article_vars.marumine.offset.y;

    if ((f32)FLOAT_NEG_MAX == joint->dobj_f0)
    {
        func_ovl3_8017275C(item_gobj);
        func_ovl3_8017279C(item_gobj);

        ap->article_vars.marumine.offset.x = 0.0F;
        ap->article_vars.marumine.offset.y = 0.0F;

        func_ovl3_801837A0(item_gobj);
        func_800269C0(1U);
    }
    return FALSE;
}

bool32 func_ovl3_801839A8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    joint->translate.x += ap->article_vars.marumine.offset.x;
    joint->translate.y += ap->article_vars.marumine.offset.y;

    func_ovl3_80183830(item_gobj);

    ap->at_multi++;

    if (ap->at_multi == ATMARUMINE_EXPLODE_LIFETIME)
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

    ap->at_multi = 0;

    ap->item_hit.stale = ARTICLE_STALE_DEFAULT;

    ap->x340_flag_b0123 = 0;

    func_ovl3_80183830(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_Marumine_Status, 0);
}

GObj* jtgt_ovl3_80183A74(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Marumine_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);
        DObj *joint = DObjGetStruct(item_gobj);

        ap->article_vars.marumine.offset = *pos;

        ap->x2D3_flag_b4 = TRUE;

        func_80008CC0(joint, 0x46U, 0U);
        func_800269C0(0x22BU);
    }
    return item_gobj;
}