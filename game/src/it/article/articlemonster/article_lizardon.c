#include "article.h"
#include "item.h"
#include "fighter.h"

bool32 jtgt_ovl3_8017F470(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATLIZARDON_GRAVITY, ATLIZARDON_T_VEL);

    return FALSE;
}

extern ArticleStatusDesc Article_Lizardon_Status[];

bool32 jtgt_ovl3_8017F49C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80173C68(article_gobj, 0.2F, 1.0F, func_ovl3_8017F8E4);

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

bool32 func_ovl3_8017F49C(GObj *article_gobj) // Unused
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    atCommon_UpdateArticleStatus(article_gobj, Article_Lizardon_Status, 0);
}

bool32 jtgt_ovl3_8017F53C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATLIZARDON_GRAVITY, ATLIZARDON_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_8017F568(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80173680(article_gobj);

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_8017F8E4(article_gobj);
        func_ovl3_8017F810(article_gobj);
    }
    return FALSE;
}

void func_ovl3_8017F5C4(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Lizardon_Status, 1);
}

bool32 jtgt_ovl3_8017F5EC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    Vec3f pos = joint->translate;

    if (ap->at_kind == At_Kind_Lizardon)
    {
        pos.y += ATLIZARDON_LIZARDON_FLAME_OFF_Y;

        pos.x += (ATLIZARDON_LIZARDON_FLAME_OFF_X * ap->lr);
    }
    else
    {
        pos.x += (ATLIZARDON_OTHER_FLAME_OFF_X * ap->lr);
    }
    if (ap->article_vars.lizardon.flame_spawn_wait == 0)
    {
        func_ovl3_8017FD2C(article_gobj, &pos, ap->lr);

        ap->article_vars.lizardon.flame_spawn_wait = ATLIZARDON_FLAME_SPAWN_WAIT;
    }
    ap->article_vars.lizardon.flame_spawn_wait--;

    if (ap->at_multi == 0)
    {
        return TRUE;
    }
    if (ap->article_vars.lizardon.turn_wait == 0)
    {
        ap->article_vars.lizardon.turn_wait = ATLIZARDON_TURN_WAIT;

        ap->lr = -ap->lr;

        pos = joint->translate;

        pos.y += ap->attributes->objectcoll_bottom;

        pos.x += (ap->attributes->objectcoll_width + ATLIZARDON_DUST_GFX_OFF_X) * -ap->lr;

        func_ovl2_800FF278(&pos, -ap->lr);

        if (ap->at_kind == At_Kind_Pippi)
        {
            joint->rotate.y += PI32;
        }
    }
    ap->article_vars.lizardon.turn_wait--;

    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_8017F7E8(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_8017F5C4);

    return FALSE;
}

extern intptr_t D_NF_0000D5C0;
extern intptr_t D_NF_0000D658;
extern intptr_t D_NF_0000D688;

void func_ovl3_8017F810(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    s32 unused[2];
    void *s;
    Vec3f pos;


    ap->article_vars.lizardon.turn_wait = ATLIZARDON_TURN_WAIT;

    pos = joint->translate;

    ap->article_vars.lizardon.pos = pos;

    ap->article_vars.lizardon.flame_spawn_wait = 0;

    ap->lr = LEFT;

    if (ap->at_kind == At_Kind_Lizardon)
    {
        s = (void*) ((uintptr_t)ap->attributes->unk_0x0 - (intptr_t)&D_NF_0000D5C0); // Linker thing

        func_8000BD1C(joint, (uintptr_t)s + (intptr_t)&D_NF_0000D658, 0.0F); // Linker thing
        func_8000BD54(joint->mobj, (uintptr_t)s + (intptr_t)&D_NF_0000D688, 0.0F); // Linker thing
        func_8000DF34(article_gobj);
    }
}

void func_ovl3_8017F8E4(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Lizardon_Status, 2);
}

bool32 jtgt_ovl3_8017F90C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        ap->at_multi = ATLIZARDON_LIFETIME;
        ap->phys_info.vel.y = 0.0F;

        if (ap->at_kind == At_Kind_Lizardon)
        {
            func_800269C0(0x13DU);
        }
        func_ovl3_8017F5C4(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_8017F98C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_0000D5C0;
extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Lizardon_Data;

GObj *jtgt_ovl3_8017F9CC(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Lizardon_Data, pos, vel, flags);
    DObj *joint;
    Article_Struct *ap;

    if (article_gobj != NULL)
    {
        joint = DObjGetStruct(article_gobj);

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = *pos;

        ap = atGetStruct(article_gobj);

        ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        joint->translate.y -= ap->attributes->objectcoll_bottom;

        func_8000BD1C(joint, ArticleGetPData(ap, D_NF_0000D5C0, D_NF_00013624), 0.0F);
    }
    return article_gobj;
}

bool32 jtgt_ovl3_8017FACC(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8017FAF8(GObj *weapon_gobj)
{
    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8017FB3C(GObj *weapon_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

    return FALSE;
}

extern s32 D_ovl3_8018D044;

bool32 jtgt_ovl3_8017FB74(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);
    Vec3f *translate;

    ip->lifetime = ATLIZARDON_FLAME_LIFETIME;

    wpMain_ReflectorInvertLR(ip, fp);

    translate = &DObjGetStruct(weapon_gobj)->translate;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, translate->x, translate->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, translate->x, translate->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);

    return FALSE;
}

extern WeaponSpawnData Item_Lizardon_Flame_Data;

GObj *func_ovl3_8017FC38(GObj *article_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(article_gobj, &Item_Lizardon_Flame_Data, pos, WEAPON_MASK_SPAWN_ARTICLE);
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->phys_info.vel = *vel;

    ip->lifetime = ATLIZARDON_FLAME_LIFETIME;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, pos->x, pos->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F); // This needs to something in v0 to match
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, pos->x, pos->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);

    return weapon_gobj;
}

void func_ovl3_8017FD2C(GObj *article_gobj, Vec3f *pos, s32 lr)
{
    s32 unused;
    Vec3f vel;

    vel.x = cosf(ATLIZARDON_FLAME_SPAWN_ANGLE) * ATLIZARDON_FLAME_VEL_XY * lr;
    vel.y = __sinf(ATLIZARDON_FLAME_SPAWN_ANGLE) * ATLIZARDON_FLAME_VEL_XY;
    vel.z = 0.0F;

    func_ovl3_8017FC38(article_gobj, pos, &vel);

    func_800269C0(0x88U);
}