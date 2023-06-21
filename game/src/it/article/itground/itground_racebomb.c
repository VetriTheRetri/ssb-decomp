#include "article.h"

void func_ovl3_80184A70(GObj *effect_gobj) // RTTF bomb explode GFX process
{
    Effect_Struct *ep = efGetStruct(effect_gobj);
    DObj *joint = DObjGetStruct(effect_gobj);

    ep->lifetime--;

    if (ep->lifetime == 0)
    {
        func_ovl2_800FD4F8(ep);
        gOMObj_EjectGObjCommon(effect_gobj);
    }
    else if (joint != NULL)
    {
        do
        {
            joint->scale.y -= 1.3F;

            joint->translate.x += joint->scale.x; // This makes no sense, seems this custom effect is very... custom
            joint->translate.y += joint->scale.y;
            joint->translate.z += joint->scale.z;

            joint->rotate.x += joint->dobj_f0; // ??? Seems to be rotation step, but only in this case? Otherwise -FLOAT32_MAX?
            joint->rotate.y += joint->dobj_f1;
            joint->rotate.z += joint->dobj_f2;

            joint = joint->unk_0x8;
        } 
        while (joint != NULL);
    }
}

extern intptr_t D_NF_00000788;
extern intptr_t D_NF_000008A0;
extern intptr_t D_NF_8000007C;
extern itCreateDesc Article_Gr_Bomb_Data;

void func_ovl3_801791F4(Vec3f *pos)
{
    GObj *effect_gobj;
    Effect_Struct *ep = func_ovl2_800FD4B8();
    DObj *joint;
    s32 i;
    void *temp_s4;
    u32 var = 0x80000000;

    if (ep != NULL)
    {
        effect_gobj = func_80009968(0x3F3U, NULL, 6U, var);

        if (effect_gobj != NULL)
        {
            func_80009DF4(effect_gobj, func_80014038, 0xB, var, -1);

            temp_s4 = (*(uintptr_t *)((uintptr_t)*Article_Gr_Bomb_Data.p_file + Article_Gr_Bomb_Data.offset) - (uintptr_t)&D_NF_00000788) + (uintptr_t)&D_NF_000008A0; // Linker thing

            for (i = 0; i < ATGRBOMB_GFX_COUNT; i++)
            {
                joint = func_800092D0(effect_gobj, temp_s4);

                func_80008CC0(joint, 0x1BU, 0U);

                joint->translate = *pos;

                joint->scale.x = (f32)((rand_f32() * 48.0F) + -24.0F);
                joint->scale.y = (f32)((rand_f32() * 50.0F) + 10.0F);
                joint->scale.z = (f32)((rand_f32() * 32.0F) + -16.0F);

                joint->dobj_f0 = (f32)((((rand_f32() * 100.0F) + -50.0F) * PI32) / 180.0F);
                joint->dobj_f1 = (f32)((((rand_f32() * 100.0F) + -50.0F) * PI32) / 180.0F);
                joint->dobj_f2 = (f32)((((rand_f32() * 100.0F) + -50.0F) * PI32) / 180.0F);
            }
            ep->lifetime = ATGRBOMB_GFX_LIFETIME;

            effect_gobj->user_data = ep;

            func_80008188(effect_gobj, func_ovl3_80184A70, 1U, 3U);
        }
    }
}

bool32 jtgt_ovl3_80184D74(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint;

    func_ovl3_80172558(ap, ATGRBOMB_GRAVITY, ATGRBOMB_T_VEL);

    joint = DObjGetStruct(item_gobj);
    joint->rotate.z += ap->article_vars.gr_bomb.roll_rotate_speed;

    return FALSE;
}

bool32 func_ovl3_80184DC4(GObj *item_gobj)
{
    func_800269C0(0x46U);
    func_ovl3_80184B44(&DObjGetStruct(item_gobj)->translate);
    func_ovl3_801852B8(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80184E04(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->percent_damage >= ATGRBOMB_HEALTH_MAX)
    {
        return func_ovl3_80184DC4(item_gobj);
    }
    return FALSE;
}

extern itStatusDesc Article_Gr_Bomb_Status[];

void func_ovl3_80184E44(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->phys_info.vel.y = 0.0F;

    atCommon_UpdateArticleStatus(item_gobj, Article_Gr_Bomb_Status, 2);
}

bool32 func_ovl3_80184E78(GObj *item_gobj, f32 vel_mod)
{
    s32 unused;
    Item_Struct *ap;
    bool32 is_collide_ground = func_ovl3_801737B8(item_gobj, MPCOLL_MASK_GROUND);

    if (itMap_CheckCollideAllModifiyVel(item_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), vel_mod, NULL) != FALSE)
    {
        func_ovl3_80172508(item_gobj);
    }
    if (is_collide_ground != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80184EDC(GObj *item_gobj)
{
    if (func_ovl3_80184E78(item_gobj, 0.5F) != FALSE)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        if (ap->phys_info.vel.y >= 90.0F) // Is it even possible to meet this condition? Didn't they mean ABSF(ap->phys_info.vel.y)?
        {
            func_ovl3_80184DC4(item_gobj); // This causes the bomb to smash on impact when landing from too high; doesn't seem possible to trigger

            return TRUE;
        }
        else if (ap->phys_info.vel.y < 30.0F)
        {
            func_ovl3_80184E44(item_gobj);
        }
        else
        {
            func_ovl0_800C7B08(&ap->phys_info.vel, &ap->coll_data.ground_angle);

            ap->phys_info.vel.y *= 0.2F;

            func_ovl3_80172508(item_gobj);
        }
        func_800269C0(0x47U);
        func_ovl3_8017279C(item_gobj);
    }
    return FALSE;
}

extern intptr_t Article_Gr_Bomb_Hit;

void func_ovl3_80184FAC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    DObjGetStruct(item_gobj)->rotate.x = HALF_PI32;

    ap->coll_data.object_coll.top = ap->coll_data.object_coll.width;
    ap->coll_data.object_coll.bottom = -ap->coll_data.object_coll.width;
}

bool32 jtgt_ovl3_80184FD4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->at_multi++;

    if (ap->at_multi == ATGRBOMB_EXPLODE_LIFETIME)
    {
        return TRUE;
    }
    else func_ovl3_80173180(item_gobj, (ArticleHitEvent*) ((uintptr_t)*Article_Gr_Bomb_Data.p_file + (intptr_t)&Article_Gr_Bomb_Hit)); // Linker thing

    return FALSE;
}

bool32 jtgt_ovl3_80185030(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    f32 roll_rotate_speed;
    f32 sqrt_vel;

    ap->phys_info.vel.x += (-(atan2f(ap->coll_data.ground_angle.y, ap->coll_data.ground_angle.x) - HALF_PI32) * ATGRBOMB_MUL_VEL_X);

    ap->lr = (ap->phys_info.vel.x >= 0.0F) ? RIGHT : LEFT;

    sqrt_vel = sqrtf(SQUARE(ap->phys_info.vel.x) + SQUARE(ap->phys_info.vel.y));

    roll_rotate_speed = ((ap->lr == LEFT) ? ATGRBOMB_ROLL_ROTATE_MUL : -ATGRBOMB_ROLL_ROTATE_MUL) * sqrt_vel;

    ap->article_vars.gr_bomb.roll_rotate_speed = roll_rotate_speed;

    DObjGetStruct(item_gobj)->rotate.z += roll_rotate_speed;

    return FALSE;
}

bool32 jtgt_ovl3_8018511C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_8017356C(item_gobj) == FALSE)
    {
        atCommon_UpdateArticleStatus(item_gobj, Article_Gr_Bomb_Status, 0);
    }
    else if (ap->coll_data.coll_mask & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL))
    {
        return func_ovl3_80184DC4(item_gobj);
    }
    return FALSE;
}

GObj* jtgt_ovl3_8018518C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Gr_Bomb_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ap = itGetStruct(item_gobj);

        ap->article_vars.gr_bomb.roll_rotate_speed = 0.0F;

        func_ovl3_80184FAC(item_gobj);
    }
    return item_gobj;
}

void func_ovl3_801851F4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->at_multi = 0;
    ap->x340_flag_b0123 = 0;

    ap->item_hit.hit_sfx = 1;

    ap->item_hit.can_rehit_item = TRUE;
    ap->item_hit.can_reflect = FALSE;

    ap->item_hit.stale = ARTICLE_STALE_DEFAULT;
    ap->item_hit.element = gmHitCollision_Element_Fire;

    ap->item_hit.clang = FALSE;

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    func_ovl3_8017275C(item_gobj);
    func_ovl3_80173180(item_gobj, (ArticleHitEvent*) ((uintptr_t)*Article_Gr_Bomb_Data.p_file + (intptr_t)&Article_Gr_Bomb_Hit));
}

void func_ovl3_80185284(GObj *item_gobj)
{
    func_ovl3_801851F4(item_gobj);
    atCommon_UpdateArticleStatus(item_gobj, Article_Gr_Bomb_Status, 1);
}

void func_ovl3_801852B8(GObj *item_gobj)
{
    Effect_Unk *effect_unk;
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    effect_unk = func_ovl2_801005C8(&joint->translate);

    if (effect_unk != NULL)
    {
        effect_unk->effect_info->scale.x =
            effect_unk->effect_info->scale.y =
            effect_unk->effect_info->scale.z = ATGRBOMB_EXPLODE_GFX_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(item_gobj)->unk_0x54 = 2;

    func_ovl3_80185284(item_gobj);
}