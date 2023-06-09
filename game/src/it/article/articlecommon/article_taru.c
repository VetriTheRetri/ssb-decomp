#include "article.h"



bool32 jtgt_ovl3_80179BA0(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATTARU_GRAVITY, ATTARU_T_VEL);

    DObjGetStruct(article_gobj)->rotate.z += ap->article_vars.taru.roll_rotate_speed;

    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80179BF8(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80179D1C);

    return FALSE;
}

bool32 func_ovl3_80179C20(GObj *article_gobj)
{
    func_800269C0(0x3BU);

    func_ovl3_801791F4(&DObjGetStruct(article_gobj)->translate);

    if (func_ovl3_801730D4(article_gobj) != FALSE)
    {
        return TRUE;
    }
    else func_ovl3_8017A30C(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80179C78(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (ap->percent_damage >= ATTARU_HEALTH_MAX)
    {
        return func_ovl3_80179C20(article_gobj);
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80179CB8(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.5F, 0.2F, func_ovl3_80179CE8);
}

extern ArticleStatusDesc Article_Taru_Status[];

void func_ovl3_80179CE8(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_Taru_Status, 0);
}

void func_ovl3_80179D1C(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    atCommon_UpdateArticleStatus(article_gobj, Article_Taru_Status, 1);
}

void jtgt_ovl3_80179D60(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Taru_Status, 2);
}

bool32 func_ovl3_80179D88(GObj *article_gobj, f32 vel_mod)
{
    s32 unused;
    Article_Struct *ap;
    bool32 is_collide_ground = func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND);

    if (func_ovl3_801737EC(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), vel_mod, NULL) != FALSE)
    {
        func_ovl3_80172508(article_gobj);
    }
    if (is_collide_ground != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_80179DEC(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->lifetime = ATTARU_LIFETIME;

    ap->phys_info.vel.y = 0.0F;

    atCommon_UpdateArticleStatus(article_gobj, Article_Taru_Status, 6);
}

bool32 jtgt_ovl3_80179E28(GObj *article_gobj)
{
    if (func_ovl3_80179D88(article_gobj, 0.5F) != FALSE)
    {
        Article_Struct *ap = atGetStruct(article_gobj);

        if (ap->phys_info.vel.y >= 90.0F) // Is it even possible to meet this condition? Didn't they mean ABSF(ap->phys_info.vel.y)?
        {
            func_ovl3_80179C20(article_gobj); // This causes the barrel to smash on impact when landing from too high; doesn't seem possible to trigger

            return TRUE;
        }
        else if (ap->phys_info.vel.y < 30.0F)
        {
            func_ovl3_80179DEC(article_gobj);
        }
        else
        {
            func_ovl0_800C7B08(&ap->phys_info.vel, &ap->coll_data.ground_angle);

            ap->phys_info.vel.y *= 0.2F;

            func_ovl3_80172508(article_gobj);
        }
        func_ovl3_8017279C(article_gobj);
    }
    return FALSE;
}

void func_ovl3_80179EF0(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    DObjGetStruct(article_gobj)->next->rotate.x = HALF_PI32;

    ap->coll_data.object_coll.top = ap->coll_data.object_coll.width;
    ap->coll_data.object_coll.bottom = -ap->coll_data.object_coll.width;
}

void jtgt_ovl3_80179F1C(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Taru_Status, 3);
    func_ovl3_80179EF0(article_gobj);
}

bool32 func_ovl3_80179F40(GObj *article_gobj)
{
    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

void jtgt_ovl3_80179F74(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Taru_Status, 4);
    func_ovl3_80179EF0(article_gobj);
}

extern intptr_t Article_Taru_Hit;
extern ArticleSpawnData Article_Taru_Data;

bool32 jtgt_ovl3_80179FA8(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->at_multi++;

    if (ap->at_multi == ATTARU_EXPLODE_LIFETIME)
    {
        return TRUE;
    }
    else func_ovl3_80173180(article_gobj, (ArticleHitEvent*)((uintptr_t)*Article_Taru_Data.p_file + (intptr_t)&Article_Taru_Hit)); // Linker thing

    return FALSE;
}

bool32 jtgt_ovl3_8017A004(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);
    f32 roll_rotate_speed;
    f32 sqrt_vel;

    ap->phys_info.vel.x += (-(atan2f(ap->coll_data.ground_angle.y, ap->coll_data.ground_angle.x) - HALF_PI32) * ATTARU_MUL_VEL_X);

    ap->lr = (ap->phys_info.vel.x >= 0.0F) ? RIGHT : LEFT;

    sqrt_vel = sqrtf(SQUARE(ap->phys_info.vel.x) + SQUARE(ap->phys_info.vel.y));

    if (sqrt_vel < ATTARU_MIN_VEL_XY)
    {
        ap->lifetime--;

        if (ap->lifetime < ATTARU_DESPAWN_FLASH_START)
        {
            if (ap->lifetime == 0)
            {
                return TRUE;
            }
            else if (ap->lifetime & 1)
            {
                DObjGetStruct(article_gobj)->unk_0x54 ^= 2;
            }
        }
    }
    roll_rotate_speed = ((ap->lr == LEFT) ? ATTARU_ROLL_ROTATE_MUL : -ATTARU_ROLL_ROTATE_MUL) * sqrt_vel;

    ap->article_vars.taru.roll_rotate_speed = roll_rotate_speed;

    DObjGetStruct(article_gobj)->rotate.z += roll_rotate_speed;

    return FALSE;
}

bool32 jtgt_ovl3_8017A148(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    if (func_ovl3_8017356C(article_gobj) == FALSE)
    {
        atCommon_UpdateArticleStatus(article_gobj, Article_Taru_Status, 4);
    }
    else if (ap->coll_data.coll_mask & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
    {
        return func_ovl3_80179C20(article_gobj);
    }
    return FALSE;
}

GObj* jtgt_ovl3_8017A1B8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Taru_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = atGetStruct(article_gobj);

        ap->article_vars.taru.roll_rotate_speed = 0.0F;

        ap->is_damage_all = TRUE;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}

void func_ovl3_8017A240(GObj *article_gobj)
{
    Article_Struct *ap = atGetStruct(article_gobj);

    ap->at_multi = 0;
    ap->x340_flag_b0123 = 0;

    ap->article_hit.hit_sfx = 1;

    ap->article_hit.flags_0x4C_b1 = TRUE;
    ap->article_hit.can_reflect = FALSE;

    ap->article_hit.stale = ARTICLE_STALE_DEFAULT;
    ap->article_hit.element = gmHitCollision_Element_Fire;

    ap->article_hit.clang = FALSE;

    ap->article_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_ovl3_8017279C(article_gobj);
    func_ovl3_8017275C(article_gobj);
    func_ovl3_80173180(article_gobj, (ArticleHitEvent*)((uintptr_t)*Article_Taru_Data.p_file + (intptr_t)&Article_Taru_Hit));
}

void func_ovl3_8017A2D8(GObj *article_gobj)
{
    func_ovl3_8017A240(article_gobj);
    atCommon_UpdateArticleStatus(article_gobj, Article_Taru_Status, 5);
}

void func_ovl3_8017A30C(GObj *article_gobj)
{
    Effect_Unk *effect_unk;
    Article_Struct *ap = atGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    effect_unk = func_ovl2_801005C8(&joint->translate);

    if (effect_unk != NULL)
    {
        effect_unk->effect_info->scale.x =
        effect_unk->effect_info->scale.y =
        effect_unk->effect_info->scale.z = ATTARU_EXPLODE_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(article_gobj)->unk_0x54 = 2;

    func_ovl3_8017A2D8(article_gobj);
}