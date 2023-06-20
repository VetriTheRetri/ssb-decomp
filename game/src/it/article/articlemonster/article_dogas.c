#include "article.h"
#include "item.h"

bool32 func_ovl3_80182C80(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return TRUE;
    }
    ap->at_multi--;

    return FALSE;
}

extern ArticleStatusDesc Article_Dogas_Status[];

void func_ovl3_80182CA8(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->at_multi = ATDOGAS_DESPAWN_WAIT;

    atCommon_UpdateArticleStatus(article_gobj, Article_Dogas_Status, 1);
}

void func_ovl3_80182CDC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    Vec3f pos;
    Vec3f vel;

    if (ap->article_vars.dogas.smog_spawn_wait <= 0)
    {
        vel.x = ATDOGAS_SMOG_VEL_XY;
        vel.y = ATDOGAS_SMOG_VEL_XY;
        vel.z = 0.0F;

        pos = joint->translate;

        pos.x += (rand_f32() * ATDOGAS_SMOG_MUL_OFF_X) - ATDOGAS_SMOG_SUB_OFF_X;
        pos.y += (rand_f32() * ATDOGAS_SMOG_MUL_OFF_Y) - ATDGOAS_SMOG_SUB_OFF_Y;

        if (pos.x < joint->translate.x)
        {
            vel.x = -vel.x;
        }
        if (pos.y < joint->translate.y)
        {
            vel.y = -vel.y;
        }
        func_ovl3_80183144(article_gobj, &pos, &vel);
        func_800269C0(0x83U);

        ap->article_vars.dogas.smog_spawn_wait = ATDOGAS_SMOG_SPAWN_WAIT;

        ap->at_multi--;
    }
}

bool32 func_ovl3_80182E1C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80182CDC(article_gobj);

    if (ap->at_multi == 0)
    {
        func_ovl3_80182CA8(article_gobj);

        return FALSE;
    }
    ap->article_vars.dogas.smog_spawn_wait--;

    return FALSE;
}

extern intptr_t D_NF_00012820;
extern intptr_t D_NF_000128DC;

void func_ovl3_80182E78(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    ap->at_multi = ATDOGAS_SMOG_SPAWN_COUNT;

    ap->article_vars.dogas.smog_spawn_wait = 0;

    if (ap->at_kind == At_Kind_Dogas)
    {
        ap->article_vars.dogas.pos = joint->translate;

        func_8000BD1C(joint->next, ArticleGetPData(ap, D_NF_00012820, D_NF_000128DC), 0.0F); // Linker thing

        func_8000DF34(article_gobj);
        func_800269C0(0x135U);
    }
}

void func_ovl3_80182F0C(GObj *article_gobj)
{
    func_ovl3_80182E78(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_Dogas_Status, 0);
}

bool32 jtgt_ovl3_80182F40(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        ap->phys_info.vel.y = 0.0F;
        ap->phys_info.vel.x = 0.0F;

        func_ovl3_80182F0C(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80182F94(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Dogas_Data;

GObj *jtgt_ovl3_80182FD4(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = itManager_CreateItem(spawn_gobj, &Article_Dogas_Data, pos, vel, flags);
    DObj *joint;
    Article_Struct *ap;

    if (article_gobj != NULL)
    {
        joint = article_gobj->obj;

        func_80008CC0(joint, 0x28U, 0U);
        func_80008CC0(joint->next, 0x1CU, 0U);

        joint->translate = *pos;

        ap = atGetStruct(article_gobj);

        joint->translate.y -= ap->attributes->objectcoll_bottom;

        ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        func_8000BD1C(joint->next, ArticleGetPData(ap, D_NF_00012820, D_NF_00013624), 0.0F); // Linker thing
    }
    return article_gobj;
}

bool32 func_ovl3_801830DC(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    DObj *joint = DObjGetStruct(weapon_gobj)->next;

    ip->item_hit.size = joint->scale.x * ip->item_vars.smog.hit_desc->size;

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

extern wpCreateDesc Item_Smog_Data;

GObj* func_ovl3_80183144(GObj *article_gobj, Vec3f *pos, Vec3f *vel)
{
    wpCreateDesc *p_data = &Item_Smog_Data;
    GObj *weapon_gobj = wpManager_CreateWeapon(article_gobj, &Item_Smog_Data, pos, WEAPON_MASK_SPAWN_ARTICLE);
    DObj *joint;
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->lifetime = ATDOGAS_SMOG_LIFETIME;

    ip->item_vars.smog.hit_desc = (wpCommonAttributes*) (*(uintptr_t*)p_data->p_item + (intptr_t)p_data->offset_wp_hit); // Dude I had a stroke trying to match this

    joint = DObjGetStruct(weapon_gobj);

    ip->phys_info.vel = *vel;

    func_80008CC0(joint->next, 0x2CU, 0U);

    joint->translate = *pos;

    return weapon_gobj;
}