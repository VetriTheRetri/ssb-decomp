#include "article.h"
#include "fighter.h"

#define PI32 3.1415927F

extern ArticleStatusDesc Article_Pakkun_Status[];

void func_ovl3_8017CF20(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Pakkun_Status, 0);

    ArticleGetStruct(article_gobj)->cb_destroy = NULL;
}

void func_ovl3_8017CF58(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Pakkun_Status, 1);
}

void func_ovl3_8017CF80(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Pakkun_Status, 2);

    ArticleGetStruct(article_gobj)->cb_destroy = func_ovl3_8017D460;
}

void func_ovl3_8017CFC0(GObj *article_gobj)
{
    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        ap->article_vars.pakkun.is_wait_fighter = TRUE;
    }
}

bool32 func_ovl3_8017CFDC(GObj *article_gobj)
{
    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        GObj *fighter_gobj = gOMObjCommonLinks[GObjLinkIndex_Fighter];

        f32 pos_x = ap->article_vars.pakkun.pos.x, pos_y = ap->article_vars.pakkun.pos.y;

        while (fighter_gobj != NULL)
        {
            Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
            DObj *joint = fp->joint[0];
            f32 dist_x, translate_y;

            if (joint->translate.x < pos_x)
            {
                dist_x = -(joint->translate.x - pos_x);
            }
            else
            {
                dist_x = joint->translate.x - pos_x;
            }
            translate_y = joint->translate.y;

            if ((dist_x < ATPAKKUN_DETECT_SIZE_WIDTH) && (pos_y + ATPAKKUN_DETECT_SIZE_BOTTOM < translate_y) && (translate_y < (pos_y + ATPAKKUN_DETECT_SIZE_TOP)))
            {
                return FALSE;
            }
            fighter_gobj = fighter_gobj->group_gobj_next;
        }
    }
    return TRUE;
}

extern intptr_t D_NF_00000CC8;
extern intptr_t D_NF_00000CF8;
extern void *D_ovl2_801313F0;

bool32 func_ovl3_8017D0A4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->article_vars.pakkun.is_wait_fighter != FALSE)
    {
        ap->at_multi = ATPAKKUN_APPEAR_WAIT;
        ap->article_vars.pakkun.is_wait_fighter = FALSE;
    }
    ap->at_multi--;

    if (ap->at_multi == 0)
    {
        if (func_ovl3_8017CFDC(article_gobj) != FALSE)
        {
            DObj *joint = DObjGetStruct(article_gobj);

            func_8000BD1C(joint, (uintptr_t)D_ovl2_801313F0 + (intptr_t)&D_NF_00000CC8, 0.0F);
            func_8000BD54(joint->mobj, (uintptr_t)D_ovl2_801313F0 + (intptr_t)&D_NF_00000CF8, 0.0F);
            func_8000DF34(article_gobj);

            joint->translate.y += ap->article_vars.pakkun.pos.y;

            func_ovl3_8017CF58(article_gobj);
        }
        else
        {
            ap->at_multi = ATPAKKUN_APPEAR_WAIT;
        }
    }
    return FALSE;
}

void func_ovl3_8017D190(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->at_multi = ATPAKKUN_APPEAR_WAIT;

    func_ovl3_8017CF20(article_gobj);

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_None;
    ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

    DObjGetStruct(article_gobj)->translate.y = ap->article_vars.pakkun.pos.y;
}

void func_ovl3_8017D1DC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    f32 pos_y = DObjGetStruct(article_gobj)->translate.y - ap->article_vars.pakkun.pos.y;
    f32 off_y = pos_y + ATPAKKUN_APPEAR_OFF_Y;

    if (off_y <= ATPAKKUN_CLAMP_OFF_Y)
    {
        ap->article_hurt.hit_status = gmHitCollision_HitStatus_None;
        ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

    }
    else
    {
        if (ap->article_hurt.hit_status == gmHitCollision_HitStatus_None)
        {
            ap->article_hurt.hit_status = gmHitCollision_HitStatus_Normal;

            func_ovl3_8017275C(article_gobj);
        }
        ap->article_hurt.size.y = (off_y - ATPAKKUN_CLAMP_OFF_Y) * ATPAKKUN_HURT_SIZE_MUL_Y;
        ap->article_hurt.offset.y = (ap->article_hurt.size.y + ATPAKKUN_CLAMP_OFF_Y) - pos_y;
    }
}

bool32 func_ovl3_8017D298(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint;

    if (ap->article_vars.pakkun.is_wait_fighter != FALSE)
    {
        DObjGetStruct(article_gobj)->unk_dobj_0x74 = (f32)FLOAT_NEG_MAX;

        func_ovl3_8017D190(article_gobj);

        ap->article_vars.pakkun.is_wait_fighter = FALSE;
    }

    joint = DObjGetStruct(article_gobj);

    if ((f32)FLOAT_NEG_MAX == joint->unk_dobj_0x74)
    {
        func_ovl3_8017D190(article_gobj);
    }
    else
    {
        joint->translate.y += ap->article_vars.pakkun.pos.y;
    }

    func_ovl3_8017D1DC(article_gobj);

    return FALSE;
}

extern intptr_t D_NF_00000E04;

bool32 jtgt_ovl3_8017D334(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->damage_knockback >= 100.0F)
    {
        DObj *joint = DObjGetStruct(article_gobj);
        f32 angle;

        joint->om_mtx[0]->unk04 = 0x46;

        joint->rotate.z = PI32;

        angle = func_ovl3_801409BC(ap->damage_angle, ap->ground_or_air, ap->damage_knockback);

        ap->phys_info.vel.x = (f32)(cosf(angle) * ap->damage_knockback * -ap->lr_damage);
        ap->phys_info.vel.y = __sinf(angle) * ap->damage_knockback;

        ap->article_hurt.hit_status = gmHitCollision_HitStatus_None;
        ap->article_hit[0].update_state = gmHitCollision_UpdateState_Disable;

        func_ovl3_8017CF80(article_gobj);

        joint->unk_dobj_0x74 = (f32)FLOAT_NEG_MAX;

        func_8000BD54(joint->mobj, (uintptr_t)D_ovl2_801313F0 + (intptr_t)&D_NF_00000E04, 0.0f);
        func_8000DF34(article_gobj);
    }
    return FALSE;
}

bool32 func_ovl3_8017D460(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    joint->translate = ap->article_vars.pakkun.pos;

    ap->at_multi = ATPAKKUN_REBIRTH_WAIT;

    ap->phys_info.vel.x = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.z = 0.0F;

    joint->rotate.z = 0.0F;

    joint->mobj->unk_mobj_0x98 = (f32)FLOAT_NEG_MAX;

    func_ovl3_8017CF20(article_gobj);

    ap->article_vars.pakkun.is_wait_fighter = FALSE;

    return FALSE;
}

extern ArticleSpawnData Article_Pakkun_Data;

GObj* jtgt_ovl3_8017D4D8(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Pakkun_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        ap->article_vars.pakkun.pos = *pos;

        DObjGetStruct(article_gobj)->translate = *pos;

        ap->at_multi = ATPAKKUN_APPEAR_WAIT;

        ap->x2D3_flag_b4 = TRUE;

        ap->article_vars.pakkun.is_wait_fighter = FALSE;

        ap->article_hit[0].can_rehit = TRUE;
    }
    return article_gobj;
}
