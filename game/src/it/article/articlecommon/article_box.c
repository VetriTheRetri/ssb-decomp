#include "article.h"
#include "gmmatch.h"




void func_ovl3_80179120(GObj *effect_gobj) // Barrel/Crate smash GFX process
{
    Effect_Struct *ep = EffectGetStruct(effect_gobj);
    DObj *joint = DObjGetStruct(effect_gobj);

    ep->lifetime--;

    if (ep->lifetime == 0)
    {
        func_ovl2_800FD4F8(ep);
        func_80009A84(effect_gobj);
    }
    else if (joint != NULL)
    {
        do
        {
            joint->scale.y -= 1.3F;

            joint->translate.x += joint->scale.x; // This makes no sense, seems this custom effect is very... custom
            joint->translate.y += joint->scale.y;
            joint->translate.z += joint->scale.z;

            joint->rotate.x += joint->unk_dobj_0x74; // ??? Seems to be rotation step, but only in this case? Otherwise -FLOAT32_MAX?
            joint->rotate.y += joint->unk_dobj_0x78;
            joint->rotate.z += joint->unk_dobj_0x7C;

            joint = joint->unk_0x8;
        } 
        while (joint != NULL);
    }
}

extern u8 D_NF_00006778;
extern u8 D_NF_000068F0;
extern ArticleSpawnData Article_Box_Data;

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

            temp_s4 = (*(uintptr_t*)((uintptr_t)*Article_Box_Data.p_file + Article_Box_Data.offset) - (uintptr_t)&D_NF_00006778) + (uintptr_t)&D_NF_000068F0; // Linker thing

            for (i = 0; i < ATCONTAINER_GFX_COUNT; i++)
            {
                joint = func_800092D0(effect_gobj, temp_s4);

                func_80008CC0(joint, 0x1BU, 0U);

                joint->translate = *pos;

                joint->scale.x = (f32)((rand_f32() * 48.0F) + -24.0F);
                joint->scale.y = (f32)((rand_f32() * 50.0F) + 10.0F);
                joint->scale.z = (f32)((rand_f32() * 32.0F) + -16.0F);

                joint->unk_dobj_0x74 = (f32)((((rand_f32() * 100.0F) + -50.0F) * PI32) / 180.0F);
                joint->unk_dobj_0x78 = (f32)((((rand_f32() * 100.0F) + -50.0F) * PI32) / 180.0F);
                joint->unk_dobj_0x7C = (f32)((((rand_f32() * 100.0F) + -50.0F) * PI32) / 180.0F);
            }
            ep->lifetime = ATCONTAINER_GFX_LIFETIME;

            effect_gobj->user_data = ep;

            func_80008188(effect_gobj, func_ovl3_80179120, 1U, 3U);
        }
    }
}

extern Vec2f D_ovl3_8018A320[6];

static Unk_8018D048 D_ovl3_8018D048;

bool32 func_ovl3_80179424(GObj *article_gobj)
{
    s32 random, spawn_item_num, index;
    s32 i, j;
    Vec2f *spawn_pos;
    Vec3f pos1;
    s32 unused;
    s32 sp64;
    s32 var;
    Vec3f pos2;

    func_800269C0(0x3BU);

    func_ovl3_801791F4(&DObjGetStruct(article_gobj)->translate);

    if (D_ovl3_8018D048.unk_0x10 != 0)
    {
        index = func_ovl3_80173090(&D_ovl3_8018D048);

        if (index < 20)
        {
            random = rand_u16_range(5);

            if (random < 2)
            {
                spawn_item_num = 1;

                spawn_pos = &D_ovl3_8018A320[0];
            }
            else if (random < 3)
            {
                spawn_item_num = 2;

                spawn_pos = &D_ovl3_8018A320[1];
            }
            else
            {
                spawn_item_num = 3;

                spawn_pos = &D_ovl3_8018A320[3];
            }

            if (rand_u16_range(0x20) == 0)
            {
                pos1.z = 0.0F;

                for (i = 0; i < spawn_item_num; i++)
                {
                    pos1.x = spawn_pos[i].x;
                    pos1.y = spawn_pos[i].y;

                    func_ovl3_8016EA78(article_gobj, index, &DObjGetStruct(article_gobj)->translate, &pos1, (ARTICLE_FLAG_PROJECT | ARTICLE_MASK_SPAWN_ARTICLE));
                }
            }
            else
            {
                sp64 = (s32)D_ovl3_8018D048.unk_0x10;

                var = D_ovl3_8018D048.unk_0x8 - 1;

                D_ovl3_8018D048.unk_0x10 = D_ovl3_8018D048.unk_0x14[var];
                D_ovl3_8018D048.unk_0x8--;

                pos2.z = 0.0F;

                for (j = 0; j < spawn_item_num; j++)
                {
                    if (j != 0)
                    {
                        index = func_ovl3_80173090(&D_ovl3_8018D048);
                    }
                    pos2.x = spawn_pos[j].x;
                    pos2.y = spawn_pos[j].y;

                    func_ovl3_8016EA78(article_gobj, index, &DObjGetStruct(article_gobj)->translate, &pos2, (ARTICLE_FLAG_PROJECT | ARTICLE_MASK_SPAWN_ARTICLE));
                }
                D_ovl3_8018D048.unk_0x8++;
                D_ovl3_8018D048.unk_0x10 = (u16)sp64;
            }
            func_800269C0(0x3CU);

            return TRUE;
        }
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017963C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATBOX_GRAVITY, ATBOX_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80179674(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_801797A4);

    return FALSE;
}

bool32 func_ovl3_8017969C(GObj *article_gobj)
{
    if (func_ovl3_80179424(article_gobj) != FALSE)
    {
        return TRUE;
    }
    else func_ovl3_80179B08(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801796D8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->percent_damage >= ATBOX_HEALTH_MAX)
    {
        return func_ovl3_8017969C(article_gobj);
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80179718(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80179748);
}

extern ArticleStatusDesc Article_Box_Status[];

void func_ovl3_80179748(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    DObjGetStruct(article_gobj)->rotate.z = atan2f(ap->coll_data.ground_angle.y, ap->coll_data.ground_angle.x) - HALF_PI32;

    func_ovl3_80172E74(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Box_Status, 0);
}

void func_ovl3_801797A4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_Box_Status, 1);
}

void jtgt_ovl3_801797E8(GObj *article_gobj)
{
    DObjGetStruct(article_gobj)->next->rotate.z = 0.0F;
    DObjGetStruct(article_gobj)->next->rotate.y = 0.0F;

    func_ovl3_80172EC8(article_gobj, Article_Box_Status, 2);
}

bool32 jtgt_ovl3_8017982C(GObj *article_gobj)
{
    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_MAIN_ALL) != FALSE)
    {
        if (func_ovl3_80179424(article_gobj) != FALSE)
        {
            return TRUE;
        }
        else func_ovl3_80179B08(article_gobj);
    }
    return FALSE;
}

void jtgt_ovl3_8017987C(GObj *article_gobj)
{
    DObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;

    func_ovl3_80172EC8(article_gobj, Article_Box_Status, 3);
}

bool32 func_ovl3_801798B8(GObj *article_gobj) // Unused
{
    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801798DC(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.2F, 0.5F, func_ovl3_80179748);
}

void jtgt_ovl3_8017990C(GObj *article_gobj)
{
    DObjGetStruct(article_gobj)->next->rotate.y = HALF_PI32;

    func_ovl3_80172EC8(article_gobj, Article_Box_Status, 4);
}

extern u8 Article_Box_Hit; // 0x614

bool32 jtgt_ovl3_80179948(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->at_multi--;

    if (ap->at_multi == 8)
    {
        return TRUE;
    }
    else func_ovl3_80173180(article_gobj, (ArticleHitEvent*)((uintptr_t)*Article_Box_Data.p_file + &Article_Box_Hit)); // Linker thing

    return FALSE;
}

GObj *jtgt_ovl3_801799A4(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Box_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        DObjGetStruct(article_gobj)->rotate.y = HALF_PI32;

        ap->is_damage_all = TRUE;
        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}

void func_ovl3_80179A34(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->x340_flag_b0123 = 0;
    ap->at_multi = 0;

    ap->article_hit.hit_sfx = 1;

    ap->article_hit.flags_0x4C_b1 = TRUE;
    ap->article_hit.can_deflect = FALSE;
    ap->article_hit.can_reflect = FALSE;

    ap->article_hit.stale = ARTICLE_STALE_DEFAULT;
    ap->article_hit.element = gmHitCollision_Element_Fire;

    ap->article_hit.clang = FALSE;

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_None;

    func_ovl3_8017279C(article_gobj);
    func_ovl3_8017275C(article_gobj);
    func_ovl3_80173180(article_gobj, (ArticleHitEvent*)((uintptr_t)*Article_Box_Data.p_file + (uintptr_t)&Article_Box_Hit));
}

void func_ovl3_80179AD4(GObj *article_gobj)
{
    func_ovl3_80179A34(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Box_Status, 5);
}

void func_ovl3_80179B08(GObj *article_gobj)
{
    Effect_Unk *effect_unk;
    Article_Struct *ap = ArticleGetStruct(article_gobj);
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
        effect_unk->effect_info->scale.z = ATBOX_EXPLODE_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(article_gobj)->unk_0x54 = 2;

    func_ovl3_80179AD4(article_gobj);
}