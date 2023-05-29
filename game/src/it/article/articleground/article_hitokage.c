#include "article.h"
#include "item.h"
#include "fighter.h"

extern ArticleStatusDesc Article_Hitokage_Status[];

void func_ovl3_80183DA0(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Hitokage_Status, 0);

    ArticleGetStruct(article_gobj)->proc_dead = func_ovl3_80183F88;
}

bool32 func_ovl3_80183DE0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    Vec3f pos;

    joint->translate.x += ap->article_vars.hitokage.offset.x;
    joint->translate.y += ap->article_vars.hitokage.offset.y;

    pos = joint->translate;

    pos.x += ATHITOKAGE_FLAME_SPAWN_OFF_X;

    if ((ap->article_vars.hitokage.flags == 2) || 
    ((ap->article_vars.hitokage.flags & 1) && (joint->unk_dobj_0x7C >= ATHITOKAGE_FLAME_SPAWN_BEGIN)) && 
    (joint->unk_dobj_0x7C <= ATHITOKAGE_FLAME_SPAWN_END))
    {
        joint->mobj->index = 1;

        if (ap->article_vars.hitokage.flame_spawn_wait <= 0)
        {
            func_ovl3_801843C4(article_gobj, &pos);

            ap->article_vars.hitokage.flame_spawn_wait = ATHITOKAGE_FLAME_SPAWN_WAIT;
        }
        else
        {
            ap->article_vars.hitokage.flame_spawn_wait--;
        }
    }
    else
    {
        joint->mobj->index = 0;
    }

    if ((f32)FLOAT_NEG_MAX == joint->unk_dobj_0x74)
    {
        func_ovl2_8010B0B8();

        return TRUE;
    }
    return FALSE;
}

bool32 jtgt_ovl3_80183F20(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint;

    func_ovl3_80172558(ap, ATHITOKAGE_GRAVITY, ATHITOKAGE_T_VEL);

    joint = DObjGetStruct(article_gobj);

    joint->rotate.z -= (ATHITOKAGE_HIT_ROTATE_Z * ap->lr);

    return FALSE;
}

bool32 func_ovl3_80183F88(GObj *article_gobj)
{
    return TRUE;
}

bool32 jtgt_ovl3_80183F94(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (ap->damage_knockback >= 100.0F)
    {
        f32 angle = func_ovl3_801409BC(ap->damage_angle, ap->ground_or_air, ap->damage_knockback);

        ap->phys_info.vel.x = cosf(angle) * ap->damage_knockback * -ap->lr_damage;
        ap->phys_info.vel.y = __sinf(angle) * ap->damage_knockback;

        ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;
        ap->article_hurt.hitstatus = gmHitCollision_HitStatus_None;

        joint->unk_dobj_0x74 = (f32)FLOAT_NEG_MAX;

        func_ovl2_8010B0AC();
        func_ovl3_80183DA0(article_gobj);
    }
    return FALSE;
}

extern s32 D_ovl2_8012EB60;
extern ArticleSpawnData Article_Hitokage_Data;

GObj* jtgt_ovl3_80184058(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Hitokage_Data, pos, vel, flags);
    s32 unused;
    DObj *joint;
    Article_Struct *ap;

    if (article_gobj != NULL)
    {
        ap = ArticleGetStruct(article_gobj);
        joint = DObjGetStruct(article_gobj);

        ap->article_vars.hitokage.flame_spawn_wait = 0;
        ap->article_vars.hitokage.offset = *pos;

        ap->x2D3_flag_b4 = TRUE;

        ap->article_vars.hitokage.flags = rand_u16_range(4);

        if ((D_ovl2_8012EB60 == ap->article_vars.hitokage.flags) || (ap->article_vars.hitokage.flags & D_ovl2_8012EB60))
        {
            ap->article_vars.hitokage.flags++;

            ap->article_vars.hitokage.flags &= 3;
        }
        if (ap->article_vars.hitokage.flags == 2)
        {
            joint->mobj->index = 1;
        }
        D_ovl2_8012EB60 = ap->article_vars.hitokage.flags;

        func_800269C0(0x229U);
    }
    return article_gobj;
}

bool32 jtgt_ovl3_8018415C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80184188(GObj *item_gobj)
{
    if (func_ovl3_80167C04(item_gobj) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_801841CC(GObj *item_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(item_gobj)->translate);

    return FALSE;
}

extern s32 D_ovl3_8018D044;

bool32 jtgt_ovl3_80184204(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);
    Vec3f *translate;

    ip->lifetime = ATHITOKAGE_FLAME_LIFETIME;

    func_ovl3_801680EC(ip, fp);

    translate = &DObjGetStruct(item_gobj)->translate;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, translate->x, translate->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, translate->x, translate->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);

    return FALSE;
}

extern ItemSpawnData Item_Hitokage_Flame_Data;

GObj *func_ovl3_801842C8(GObj *article_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *item_gobj = func_ovl3_801655C8(article_gobj, &Item_Hitokage_Flame_Data, pos, ITEM_MASK_SPAWN_ARTICLE);
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->phys_info.vel = *vel;

    ip->lifetime = ATHITOKAGE_FLAME_LIFETIME;

    ip->lr = LEFT;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, pos->x, pos->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, pos->x, pos->y, 0.0F, ip->phys_info.vel.x, ip->phys_info.vel.y, 0.0F);

    return item_gobj;
}

void func_ovl3_801843C4(GObj *article_gobj, Vec3f *pos)
{
    Article_Struct *ap;
    Vec3f vel;

    vel.x = cosf(ATHITOKAGE_FLAME_SPAWN_ANGLE) * -ATHITOKAGE_FLAME_VEL_XY;
    vel.y = __sinf(ATHITOKAGE_FLAME_SPAWN_ANGLE) * ATHITOKAGE_FLAME_VEL_XY;
    vel.z = 0.0F;

    func_ovl3_801842C8(article_gobj, pos, &vel);
    func_800269C0(0x88U);
}