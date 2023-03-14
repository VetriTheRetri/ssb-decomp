#include "article.h"

#define HALF_PI32 1.5707964F

void func_ovl3_8017A3A0(GObj *article_gobj, GObj *fighter_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    f32 vel_x;
    f32 dist_x;
    s32 lr_vel;
    s32 lr_dist;

    if (ap->ground_or_air == ground)
    {
        dist_x = (DObjGetStruct(fighter_gobj)->translate.x - DObjGetStruct(article_gobj)->translate.x);

        lr_dist = (dist_x < 0.0F) ? LEFT : RIGHT;

        vel_x = lr_dist * ATRSHELL_MUL_VEL_X;

        ap->article_vars.shell.vel_x = vel_x;

        ap->phys_info.vel.x += vel_x;

        lr_vel = (ap->phys_info.vel.x < 0.0F) ? LEFT : RIGHT;

        lr_dist = (ap->article_vars.shell.vel_x < 0.0F) ? LEFT : RIGHT;

        if (lr_dist == lr_vel)
        {
            if (ABSF(ap->phys_info.vel.x) > ATRSHELL_CLAMP_VEL_X)
            {
                ap->phys_info.vel.x = ap->lr * ATRSHELL_CLAMP_VEL_X;
            }
        }
        if (ap->article_hit[0].update_state == gmHitCollision_UpdateState_Disable)
        {
            if (ABSF(ap->phys_info.vel.x) <= ATRSHELL_HIT_INIT_VEL_X)
            {
                ap->article_hit[0].update_state = gmHitCollision_UpdateState_New;

                func_ovl3_8016F280(article_gobj);
            }
        }
        ap->lr = (ap->phys_info.vel.x < 0.0F) ? LEFT : RIGHT;
    }
}

void func_ovl3_8017A534(GObj *article_gobj)
{
    s32 unused;
    GObj *fighter_gobj = gOMObjCommonLinks[3];
    GObj *victim_gobj;
    DObj *joint = DObjGetStruct(article_gobj);
    Vec3f *translate = &joint->translate;
    s32 ft_count = 0;
    f32 square_xy;
    f32 dist_xy;
    Vec3f dist;

    if (fighter_gobj != NULL)
    {
        do
        {
            vec3f_sub(&dist, &DObjGetStruct(fighter_gobj)->translate, translate);

            if (ft_count == 0)
            {
                dist_xy = SQUARE(dist.x) + SQUARE(dist.y);
            }
            square_xy = (SQUARE(dist.x) + SQUARE(dist.y));

            if (square_xy <= dist_xy)
            {
                dist_xy = square_xy;

                victim_gobj = fighter_gobj;
            }
            fighter_gobj = fighter_gobj->group_gobj_next;

            ft_count++;
        }
        while (fighter_gobj != NULL);
    }
    func_ovl3_8017A3A0(article_gobj, victim_gobj); // victim_gobj is not always initialized??? Undefined behavior
}

void func_ovl3_8017A610(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (ap->article_vars.shell.dust_gfx_int == 0)
    {
        Vec3f pos = joint->translate;

        pos.y += ap->attributes->gfx_offset.y;

        func_ovl2_800FF048(&pos, ap->lr, 1.0F);

        ap->article_vars.shell.dust_gfx_int = ATRSHELL_GFX_SPAWN_INT;
    }
    ap->article_vars.shell.dust_gfx_int--;
}

extern intptr_t D_NF_00005F88;
extern intptr_t D_NF_00006018;
extern intptr_t D_NF_00006048;

void func_ovl3_8017A6A0(GObj *article_gobj) // Identical to Green Shell function
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    s32 unused[2];

    func_8000BD1C(joint, (((uintptr_t)ap->attributes->unk_0x0 - (intptr_t)&D_NF_00005F88)) + (intptr_t)&D_NF_00006018, 0.0F); // Linker thing
    func_8000BD54(joint->mobj, (((uintptr_t)ap->attributes->unk_0x0 - (intptr_t)&D_NF_00005F88)) + (intptr_t)&D_NF_00006048, 0.0F); // Linker thing
    func_8000DF34(article_gobj);
}

void func_ovl3_8017A734(GObj *article_gobj)
{
    DObjGetStruct(article_gobj)->mobj->unk_image_0x94 = 0;
    DObjGetStruct(article_gobj)->unk_dobj_0x70 = 0;
}

bool32 jtgt_ovl3_8017A74C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATRSHELL_GRAVITY, ATRSHELL_T_VEL);

    if (!(ap->article_vars.shell.damage_all_delay))
    {
        func_ovl3_8017279C(article_gobj);

        ap->article_vars.shell.damage_all_delay = -1;
    }
    if (ap->article_vars.shell.damage_all_delay != -1)
    {
        ap->article_vars.shell.damage_all_delay--;
    }
    return FALSE;
}

bool32 func_ovl3_8017A7C4(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_8017A984);

    return FALSE;
}

bool32 jtgt_ovl3_8017A7EC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->article_vars.shell.health == 0)
    {
        return func_ovl3_80173DF4(article_gobj, 0.25F);
    }
    func_ovl3_80173B24(article_gobj, 0.25F, 0.5F, func_ovl3_8017A964);

    return FALSE;
}

extern ArticleStatusDesc Article_R_Shell_Status[];

void func_ovl3_8017A83C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80173F54(ap);

    if (ABSF(ap->phys_info.vel.x) < 8.0F)
    {
        func_ovl3_80172E74(article_gobj);

        ap->article_vars.shell.is_damage = FALSE;
        ap->phys_info.vel.x = 0.0F;

        func_ovl3_8017279C(article_gobj);

        ap->article_hurt.hit_status = gmHitCollision_HitStatus_Normal;
        ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

        func_ovl3_8017A734(article_gobj);
        func_ovl3_80172EC8(article_gobj, Article_R_Shell_Status, 0);
    }
    else if (ap->article_vars.shell.is_damage != FALSE)
    {
        ap->article_hit[0].update_state = gmHitCollision_UpdateState_New;

        func_ovl3_8016F280(article_gobj);
        func_ovl3_8017B0D4(article_gobj);
    }
    else
    {
        func_ovl3_80172E74(article_gobj);

        ap->phys_info.vel.x = 0.0F;

        func_ovl3_8017279C(article_gobj);

        ap->article_hurt.hit_status = gmHitCollision_HitStatus_Normal;
        ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

        func_ovl3_8017A734(article_gobj);
        func_ovl3_80172EC8(article_gobj, Article_R_Shell_Status, 0);
    }
}

void func_ovl3_8017A964(GObj *article_gobj) // Unused
{
    func_ovl3_8017A83C(article_gobj);
}

void func_ovl3_8017A984(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_Normal;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_R_Shell_Status, 1);
}

bool32 jtgt_ovl3_8017A9D0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->phys_info.vel.x = ap->damage_taken_recent * ATRSHELL_DAMAGE_MUL_NORMAL * (-ap->lr_damage);

    if (ABSF(ap->phys_info.vel.x) > ATRSHELL_STOP_VEL_X)
    {
        ap->article_vars.shell.is_damage = TRUE;

        ap->article_hit[0].update_state = gmHitCollision_UpdateState_New;

        func_ovl3_8016F280(article_gobj);

        func_ovl3_801727BC(article_gobj);

        if (ap->ground_or_air != ground)
        {
            func_ovl3_8017B1A4(article_gobj);
        }
        else func_ovl3_8017B0D4(article_gobj);

    }
    else
    {
        ap->phys_info.vel.x = 0.0F;

        ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;
    }
    return FALSE;
}

void jtgt_ovl3_8017AABC(GObj *article_gobj)
{
    DObjGetStruct(article_gobj)->rotate.y = 0.0F;

    func_ovl3_80172EC8(article_gobj, Article_R_Shell_Status, 2);
}

void jtgt_ovl3_8017AAF0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_vars.shell.health = 1;
    ap->article_vars.shell.is_damage = TRUE;
    ap->article_vars.shell.damage_all_delay = ATRSHELL_DAMAGE_ALL_WAIT;

    ap->times_thrown = 0;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_R_Shell_Status, 3);
}

void jtgt_ovl3_8017AB48(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_vars.shell.health = 1;
    ap->article_vars.shell.is_damage = TRUE;
    ap->article_vars.shell.damage_all_delay = ATRSHELL_DAMAGE_ALL_WAIT;

    ap->times_thrown = 0;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_R_Shell_Status, 4);
}

bool32 jtgt_ovl3_8017ABA0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_80173C68(article_gobj, 0.25F, 0.5F, func_ovl3_8017B0D4) != FALSE)
    {
        if (ap->phys_info.vel.x < 0.0F) ap->lr = LEFT;

        else ap->lr = RIGHT;

        ap->phys_info.vel.x = (((ap->lr * -8.0F) + -10.0F) * 0.7F);
    }
    return FALSE;
}

void func_ovl3_8017AC40(GObj *article_gobj, u8 lr)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->phys_info.vel.x = -ap->phys_info.vel.x;

    ap->article_vars.shell.vel_x = -ap->article_vars.shell.vel_x;

    if (lr != 0)
    {
        ap->lr = RIGHT;
    }
    else ap->lr = LEFT;
}

void func_ovl3_8017AC84(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    atCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(article_gobj);
    Vec3f pos;

    if (func_ovl2_800FC67C(ap->coll_data.ground_line_id) != FALSE)
    {
        if (ap->lr == LEFT)
        {
            func_ovl2_800F4428(ap->coll_data.ground_line_id, &pos);

            if ((joint->translate.x - attributes->ledge_stop_width) <= pos.x)
            {
                func_ovl3_8017AC40(article_gobj, 1);
            }
        }
        else
        {
            func_ovl2_800F4408(ap->coll_data.ground_line_id, &pos);

            if (pos.x <= (joint->translate.x + attributes->ledge_stop_width))
            {
                func_ovl3_8017AC40(article_gobj, 0);
            }
        }
    }
}

bool32 jtgt_ovl3_8017AD7C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_8017A610(article_gobj);
    func_ovl3_8017A534(article_gobj);
    func_ovl3_8017AC84(article_gobj);

    if (ap->lifetime == 0)
    {
        return TRUE;
    }
    else ap->lifetime--;

    return FALSE;
}

bool32 jtgt_ovl3_8017ADD4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if ((func_ovl3_801735A0(article_gobj, func_ovl3_8017B1A4) != FALSE) && (ap->coll_data.unk_0x56 & (MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL)))
    {
        ap->phys_info.vel.x = -ap->phys_info.vel.x;

        func_ovl3_80172508(article_gobj);
        func_ovl3_8017279C(article_gobj);

        ap->article_vars.shell.vel_x = -ap->article_vars.shell.vel_x;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017AE48(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_vars.shell.interact--;

    if (ap->article_vars.shell.interact == 0)
    {
        return TRUE;
    }
    ap->article_hurt.hit_status = gmHitCollision_HitStatus_Normal;

    ap->article_vars.shell.health = rand_u16_range(ATRSHELL_HEALTH_MAX);

    ap->phys_info.vel.x = (((ap->phys_info.vel.x * -1.0F) + (ATRSHELL_RECOIL_VEL_X * ap->lr_attack)) * ATRSHELL_RECOIL_MUL_X);

    func_ovl3_8017A734(article_gobj);

    if (ap->ground_or_air != ground)
    {
        func_ovl3_8017B1A4(article_gobj);
    }
    else
    {
        func_ovl3_8017B0D4(article_gobj);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017AF18(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_vars.shell.interact--;

    if (ap->article_vars.shell.interact == 0)
    {
        return TRUE;
    }
    ap->phys_info.vel.x += (ap->damage_taken_recent * 2.0F) * -ap->lr_damage;

    if (ABSF(ap->phys_info.vel.x) > ATRSHELL_STOP_VEL_X)
    {
        ap->article_hit[0].update_state = gmHitCollision_UpdateState_New;

        func_ovl3_8016F280(article_gobj);
        func_ovl3_801727BC(article_gobj);
        func_ovl3_8017B0D4(article_gobj);
    }
    else
    {
        ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;
    }
    return FALSE;
}

void func_ovl3_8017AFEC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;
    ap->pickup_wait = ARTICLE_PICKUP_WAIT_DEFAULT;

    if (ap->phys_info.vel.x > ATRSHELL_CLAMP_VEL_X)
    {
        ap->phys_info.vel.x = ATRSHELL_CLAMP_VEL_X;
    }
    if (ap->phys_info.vel.x < -ATRSHELL_CLAMP_VEL_X)
    {
        ap->phys_info.vel.x = -ATRSHELL_CLAMP_VEL_X;
    }
    ap->phys_info.vel.y = 0.0F;

    if (ap->phys_info.vel.x < 0.0F)
    {
        ap->lr = LEFT;
    }
    else ap->lr = RIGHT;

    if (ap->article_vars.shell.is_setup_vars == FALSE)
    {
        ap->lifetime = ATRSHELL_LIFETIME;

        ap->article_vars.shell.is_setup_vars = TRUE;

        ap->article_vars.shell.interact = ATRSHELL_INTERACT_MAX;
    }
    ap->article_vars.shell.dust_gfx_int = ATRSHELL_GFX_SPAWN_INT;

    func_ovl3_8017A6A0(article_gobj);
    func_800269C0(0x37U);
    func_ovl3_8017279C(article_gobj);
    func_ovl3_80173F54(ap);
}

void func_ovl3_8017B0D4(GObj *article_gobj)
{
    func_ovl3_8017AFEC(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_R_Shell_Status, 5);
}

void func_ovl3_8017B108(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    if (ap->phys_info.vel.x > ATRSHELL_CLAMP_AIR_X)
    {
        ap->phys_info.vel.x = ATRSHELL_CLAMP_AIR_X;
    }
    if (ap->phys_info.vel.x < -ATRSHELL_CLAMP_AIR_X)
    {
        ap->phys_info.vel.x = -ATRSHELL_CLAMP_AIR_X;
    }
    if (ap->phys_info.vel.x < 0.0F)
    {
        ap->lr = LEFT;
    }
    else ap->lr = RIGHT;

    func_ovl3_8017279C(article_gobj);
    func_ovl3_80173F78(ap);
}

void func_ovl3_8017B1A4(GObj *article_gobj)
{
    func_ovl3_8017B108(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_R_Shell_Status, 6);
}

extern ArticleSpawnData Article_R_Shell_Data;

GObj *jtgt_ovl3_8017B1D8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_R_Shell_Data, pos, vel, flags);


    if (article_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(article_gobj);
        Article_Struct *ap;
        Vec3f translate = joint->translate;

        joint->rotate.y = HALF_PI32;

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = translate;

        joint->mobj->anim_frame = 0.0F;

        ap = ArticleGetStruct(article_gobj);

        ap->article_hit[0].flags_0x4C_b3 = TRUE;

        ap->article_vars.shell.health = 1;
        ap->article_vars.shell.is_setup_vars = FALSE;
        ap->article_vars.shell.is_damage = FALSE;
        ap->article_vars.shell.damage_all_delay = -1;
        ap->article_vars.shell.vel_x = 0;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return article_gobj;
}

bool32 jtgt_ovl3_8017B2F8(GObj *article_gobj)
{
    func_ovl3_80172FE0(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8017B31C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *aj = DObjGetStruct(article_gobj), *fj = DObjGetStruct(ap->owner_gobj);

    ap->article_vars.shell.interact--;

    if (ap->article_vars.shell.interact == 0)
    {
        return TRUE;
    }

    if (aj->translate.x < fj->translate.x)
    {
        ap->lr = LEFT;

        if (ap->phys_info.vel.x >= 0.0F)
        {
            ap->phys_info.vel.x = -ap->phys_info.vel.x;
            ap->article_vars.shell.vel_x = -ap->article_vars.shell.vel_x;
        }
    }
    else
    {
        ap->lr = RIGHT;

        if (ap->phys_info.vel.x < 0.0F)
        {
            ap->phys_info.vel.x = -ap->phys_info.vel.x;
            ap->article_vars.shell.vel_x = -ap->article_vars.shell.vel_x;
        }
    }
    ap->phys_info.vel.x += (ATRSHELL_ADD_VEL_X * ap->lr);

    func_ovl3_8017279C(article_gobj);

    return FALSE;
}