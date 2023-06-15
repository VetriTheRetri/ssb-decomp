#include "article.h"
#include "item.h"

bool32 func_ovl3_80185350(GObj *article_gobj)
{
    func_ovl3_8018579C(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80185374(GObj *article_gobj)
{
    s32 unused1[4];
    Article_Struct *ap = atGetStruct(article_gobj);
    Effect_Info *effect = ap->article_vars.pk_fire.effect;
    atCommonAttributes *attributes;
    f32 lifetime_scale = ((ap->lifetime * (f32)0.5) / 100.0F) + (f32)0.5;

    DObjGetStruct(article_gobj)->scale.x = DObjGetStruct(article_gobj)->scale.y = DObjGetStruct(article_gobj)->scale.z = lifetime_scale;

    attributes = ap->attributes;

    ap->article_hit.offset[0].x = attributes->hit_offset1_x * lifetime_scale;
    ap->article_hit.offset[0].y = attributes->hit_offset1_y * lifetime_scale;
    ap->article_hit.offset[0].z = attributes->hit_offset1_z * lifetime_scale;
    ap->article_hit.offset[1].x = attributes->hit_offset2_x * lifetime_scale;
    ap->article_hit.offset[1].y = attributes->hit_offset2_y * lifetime_scale;
    ap->article_hit.offset[1].z = attributes->hit_offset2_z * lifetime_scale;

    ap->article_hit.size = attributes->size * (f32)0.5F * lifetime_scale;

    ap->article_hurt.offset.x = attributes->hurt_offset.x * lifetime_scale;
    ap->article_hurt.offset.y = attributes->hurt_offset.y * lifetime_scale;
    ap->article_hurt.offset.z = attributes->hurt_offset.z * lifetime_scale;
    ap->article_hurt.size.x = attributes->hurt_size.x * (f32)0.5F * lifetime_scale;
    ap->article_hurt.size.y = attributes->hurt_size.y * (f32)0.5F * lifetime_scale;
    ap->article_hurt.size.z = attributes->hurt_size.z * (f32)0.5F * lifetime_scale;

    if (effect != NULL)
    {
        effect->scale.x = DObjGetStruct(article_gobj)->scale.x;
        effect->scale.y = DObjGetStruct(article_gobj)->scale.y;
        effect->scale.z = DObjGetStruct(article_gobj)->scale.z;

        effect->translate = DObjGetStruct(article_gobj)->translate;
    }
    ap->lifetime--;

    if (ap->lifetime < 0)
    {
        func_ovl2_800FF648(&DObjGetStruct(article_gobj)->translate, 1.0F);

        if (effect != NULL)
        {
            func_ovl0_800D39D4(effect->unk_effect_0xB8, 0);
        }
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_801855E4(GObj *article_gobj)
{
    if (func_ovl3_80185374(article_gobj) == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}

bool32 jtgt_ovl3_80185614(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (func_ovl3_80185374(article_gobj) == TRUE)
    {
        return TRUE;
    }
    else func_ovl3_80172558(ap, ATPKFIRE_GRAVITY, ATPKFIRE_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_80185660(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_8018579C);

    return FALSE;
}

bool32 jtgt_ovl3_80185688(GObj *article_gobj)
{
    func_ovl3_80173C68(article_gobj, 0.2F, 0.5F, func_ovl3_80185710);

    return FALSE;
}

bool32 jtgt_ovl3_801856BC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->lifetime > 0)
    {
        ap->lifetime -= ap->damage_last * ATPKFIRE_HURT_DAMAGE_MUL;
    }
    if (func_ovl3_80185374(article_gobj) == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}

extern ArticleStatusDesc Article_PK_Fire_Status[];

void func_ovl3_80185710(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    gmAttackFlags flags_hi;
    u16 flags_lw;

    func_ovl3_80173F54(ap);

    ap->phys_info.vel_ground = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.x = 0.0F;

    flags_hi = ap->article_hit.stat_flags;
    flags_lw = ap->article_hit.stat_count;

    atCommon_UpdateArticleStatus(article_gobj, Article_PK_Fire_Status, 0);

    ap->article_hit.stat_flags = flags_hi;
    ap->article_hit.stat_count = flags_lw;
}

void func_ovl3_8018579C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    gmAttackFlags flags_hi;
    u16 flags_lw;

    func_ovl3_80173F78(ap);

    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.x = 0.0F;

    flags_hi = ap->article_hit.stat_flags;
    flags_lw = ap->article_hit.stat_count;

    atCommon_UpdateArticleStatus(article_gobj, Article_PK_Fire_Status, 1);

    ap->article_hit.stat_flags = flags_hi;
    ap->article_hit.stat_count = flags_lw;
}

extern s32 D_ovl2_80131148;
extern ArticleSpawnData Article_PK_Fire_Data;

GObj* func_ovl3_80185824(GObj *item_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *article_gobj;
    Weapon_Struct *ip = wpGetStruct(item_gobj);
    Article_Struct *ap;
    Effect_Unk *effect_unk;
    Effect_Info *effect_info;

    article_gobj = func_ovl3_8016E174(item_gobj, &Article_PK_Fire_Data, pos, vel, (ARTICLE_FLAG_PROJECT | ARTICLE_MASK_SPAWN_ITEM));

    if (article_gobj == NULL)
    {
        return NULL;
    }
    ap = atGetStruct(article_gobj);

    ap->owner_gobj = ip->owner_gobj;

    ap->is_allow_pickup = FALSE;
    ap->is_hold = FALSE;

    ap->team = ip->team;
    ap->port_id = ip->port_id;
    ap->handicap = ip->handicap;
    ap->player_number = ip->player_number;

    ap->article_hit.can_rehit = TRUE;
    ap->article_hit.throw_mul = ip->item_hit.stale;
    ap->article_hit.attack_id = ip->item_hit.attack_id;
    ap->article_hit.motion_count = ip->item_hit.motion_count;
    ap->article_hit.stat_flags = ip->item_hit.stat_flags;
    ap->article_hit.stat_count = ip->item_hit.stat_count;

    func_ovl3_80173F78(ap);
    func_ovl3_8016F280(article_gobj);

    ap->lifetime = ATPKFIRE_LIFETIME;

    effect_unk = func_ovl0_800CE9E8(D_ovl2_80131148, 0);

    if (effect_unk != NULL)
    {
        effect_info = func_ovl0_800CE1DC(effect_unk, 0);

        if (effect_info != NULL)
        {
            ap->article_vars.pk_fire.effect = effect_info;

            func_ovl0_800CEA14(effect_unk);

            if (effect_info->unk_effect_0x2A == 0)
            {
                ap->article_vars.pk_fire.effect = NULL;

            }
            else effect_info->translate = *pos;
        }
        else
        {
            func_ovl0_800CEA40(effect_unk);

            ap->article_vars.pk_fire.effect = NULL;
        }
    }
    else
    {
        ap->article_vars.pk_fire.effect = NULL;
    }
    return article_gobj;
}
