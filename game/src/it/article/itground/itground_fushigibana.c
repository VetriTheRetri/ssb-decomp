#include "article.h"
#include "item.h"
#include "fighter.h"

extern intptr_t Fushigibana_Event;
extern itCreateDesc Article_Fushigibana_Data;

void func_ovl3_80184440(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    ArticleHitDesc *hit_desc = (ArticleHitDesc *)((uintptr_t)*Article_Fushigibana_Data.p_file + (intptr_t)&Fushigibana_Event); // Linker thing

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

    if (ap->at_multi == ATFUSHIGIBANA_RETURN_WAIT)
    {
        Vec3f pos = DObjGetStruct(item_gobj)->translate;

        pos.y = 0.0F;

        func_ovl2_800FF048(&pos, LEFT, 1.0F);
    }
}

bool32 func_ovl3_801845B4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f pos;

    joint->translate.x += ap->article_vars.fushigibana.offset.x;
    joint->translate.y += ap->article_vars.fushigibana.offset.y;

    func_ovl3_80184440(item_gobj);

    pos = joint->translate;

    pos.x += ATFUSHIGIBANA_RAZOR_SPAWN_OFF_X;

    if ((ap->article_vars.fushigibana.flags == 2) ||
        ((ap->article_vars.fushigibana.flags & 1) && (joint->dobj_f2 >= ATFUSHIGIBANA_RAZOR_SPAWN_BEGIN)) &&
        (joint->dobj_f2 <= ATFUSHIGIBANA_RAZOR_SPAWN_END))
    {
        joint->mobj->index = 1;

        if (!ap->article_vars.fushigibana.razor_spawn_wait)
        {
            func_ovl3_801849EC(item_gobj, &pos);

            ap->article_vars.fushigibana.razor_spawn_wait = ATFUSHIGIBANA_RAZOR_SPAWN_WAIT;

            func_800269C0(0x8CU);

            func_ovl2_800FECBC(&pos);
        }
        if (ap->article_vars.fushigibana.razor_spawn_wait > 0)
        {
            ap->article_vars.fushigibana.razor_spawn_wait--;
        }
    }
    else joint->mobj->index = 0;

    if ((f32)FLOAT_NEG_MAX == joint->dobj_f0)
    {
        func_ovl2_8010B0B8();

        return TRUE;
    }
    return FALSE;
}

extern itCreateDesc Article_Fushigibana_Data;
extern s32 D_ovl2_8012EB60;

GObj *jtgt_ovl3_8018470C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Fushigibana_Data, pos, vel, flags);
    s32 unused;
    DObj *joint;
    Item_Struct *ap;

    if (item_gobj != NULL)
    {
        ap = itGetStruct(item_gobj);
        joint = DObjGetStruct(item_gobj);

        ap->x340_flag_b0123 = 0;

        ap->at_multi = 0;

        ap->article_vars.fushigibana.razor_spawn_wait = 0;
        ap->article_vars.fushigibana.offset = *pos;

        ap->x2D3_flag_b4 = TRUE;

        ap->article_vars.hitokage.flags = rand_u16_range(4);

        if ((D_ovl2_8012EB60 == ap->article_vars.fushigibana.flags) || (ap->article_vars.fushigibana.flags & D_ovl2_8012EB60))
        {
            ap->article_vars.fushigibana.flags++;

            ap->article_vars.fushigibana.flags &= 3;
        }
        if (ap->article_vars.fushigibana.flags == 2)
        {
            joint->mobj->index = 1;
        }
        D_ovl2_8012EB60 = ap->article_vars.fushigibana.flags;

        func_800269C0(0x228U);
    }
    return item_gobj;
}

bool32 func_ovl3_80184820(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    ip->phys_info.vel.x += ATFUSHIGIBANA_RAZOR_ADD_VEL_X * ip->lr;

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80184874(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_ovl2_800FE6E4(&DObjGetStruct(weapon_gobj)->translate, ip->weapon_hit.damage, ip->lr);

    return TRUE;
}

bool32 jtgt_ovl3_801848BC(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x) + PI32;
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    if (ip->phys_info.vel.x > 0.0F)
    {
        ip->lr = RIGHT;
    }
    else ip->lr = LEFT;

    return FALSE;
}

bool32 jtgt_ovl3_80184970(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    wpMain_ReflectorInvertLR(ip, fp);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x) + PI32;
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern wpCreateDesc Item_Razor_Data;

GObj *func_ovl3_801849EC(GObj *item_gobj, Vec3f *pos)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(item_gobj, &Item_Razor_Data, pos, WEAPON_MASK_SPAWN_ARTICLE);
    DObj *joint;
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->lr = LEFT;

    ip->phys_info.vel.x = ATFUSHIGIBANA_RAZOR_VEL_X;

    joint = DObjGetStruct(weapon_gobj);

    joint->translate = *pos;

    ip->lifetime = ATFUSHIGIBANA_RAZOR_LIFETIME;

    return weapon_gobj;
}
