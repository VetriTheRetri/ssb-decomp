#include "article.h"
#include "gmmatch.h"

extern ArticleStatusDesc Article_Gr_Lucky_Status[];

void func_ovl3_8017C240(GObj *article_gobj)
{
    atCommon_UpdateArticleStatus(article_gobj, Article_Gr_Lucky_Status, 0);

    ArticleGetStruct(article_gobj)->proc_dead = func_ovl3_8017C524;
}

void func_ovl3_8017C280(GObj *lucky_gobj)
{
    Article_Struct *lucky_ap = ArticleGetStruct(lucky_gobj);
    Article_Struct *egg_ap;
    s32 unused;
    DObj *joint = DObjGetStruct(lucky_gobj);
    GObj *egg_gobj;
    Vec3f pos;
    Vec3f vel;

    if (lucky_ap->at_multi == 0)
    {
        if (lucky_ap->article_vars.gr_lucky.egg_spawn_wait != 0)
        {
            if ((Match_Info->item_toggles & 8) && (Match_Info->item_switch != 0)) // Return to this when 0x8 is mapped
            {
                pos = joint->translate;

                pos.x -= ATGRLUCKY_EGG_SPAWN_OFF_X;
                pos.y += ATGRLUCKY_EGG_SPAWN_OFF_Y;

                vel.x = -((rand_f32() * ATGRLUCKY_EGG_SPAWN_MUL) + ATGRLUCKY_EGG_SPAWN_ADD_X);
                vel.y = (rand_f32() * ATGRLUCKY_EGG_SPAWN_MUL) + ATGRLUCKY_EGG_SPAWN_ADD_Y;
                vel.z = 0.0F;

                egg_gobj = func_ovl3_8016EA78(lucky_gobj, At_Kind_Egg, &pos, &vel, (ARTICLE_FLAG_PROJECT | ARTICLE_MASK_SPAWN_ARTICLE));

                if (egg_gobj != NULL)
                {
                    egg_ap = ArticleGetStruct(egg_gobj);

                    func_800269C0(0xCAU);

                    lucky_ap->at_multi = 10;
                    lucky_ap->article_vars.gr_lucky.egg_spawn_wait--;

                    func_ovl2_800FF048(&pos, egg_ap->lr, 1.0F);
                }
            }
            else
            {
                lucky_ap->at_multi = 10;
                lucky_ap->article_vars.gr_lucky.egg_spawn_wait--;
            }
        }
    }
    if (lucky_ap->article_vars.gr_lucky.egg_spawn_wait != 0)
    {
        if (lucky_ap->at_multi > 0)
        {
            lucky_ap->at_multi--;
        }
    }
}

bool32 func_ovl3_8017C400(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    joint->translate.x += ap->article_vars.gr_lucky.pos.x;
    joint->translate.y += ap->article_vars.gr_lucky.pos.y;

    if ((joint->unk_dobj_0x7C >= ATGRLUCKY_EGG_SPAWN_BEGIN) && (joint->unk_dobj_0x7C <= ATGRLUCKY_EGG_SPAWN_END))
    {
        func_ovl3_8017C280(article_gobj);
    }
    if ((f32)FLOAT_NEG_MAX == joint->unk_dobj_0x74)
    {
        func_ovl2_8010B0B8();

        return TRUE;
    }
    else return FALSE;
}

bool32 func_ovl3_8017C4AC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    return FALSE;
}

bool32 jtgt_ovl3_8017C4BC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint;

    func_ovl3_80172558(ap, ATGRLUCKY_GRAVITY, ATGRLUCKY_T_VEL);

    joint = DObjGetStruct(article_gobj);

    joint->rotate.z -= ATGRLUCKY_HIT_ROTATE_Z * ap->lr;

    return FALSE;
}

bool32 func_ovl3_8017C524(GObj *article_gobj)
{
    return TRUE;
}

bool32 jtgt_ovl3_8017C530(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (ap->damage_knockback >= 100.0F)
    {
        f32 angle = func_ovl3_801409BC(ap->damage_angle, ap->ground_or_air, ap->damage_knockback);

        ap->phys_info.vel.x = (cosf(angle) * ap->damage_knockback * -ap->lr_damage);
        ap->phys_info.vel.y = (__sinf(angle) * ap->damage_knockback);

        ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;
        ap->article_hurt.hitstatus = gmHitCollision_HitStatus_None;

        joint->unk_dobj_0x74 = (f32)FLOAT_NEG_MAX;

        func_ovl2_8010B0AC();
        func_ovl3_8017C240(article_gobj);
    }
    return FALSE;
}

extern ArticleSpawnData Article_Gr_Lucky_Data;

GObj* jtgt_ovl3_8017C5F4(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Gr_Lucky_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        ap->article_hit.interact_mask = GMHITCOLLISION_MASK_FIGHTER;

        ap->article_vars.gr_lucky.pos = *pos;

        ap->x2D3_flag_b4 = TRUE;

        ap->at_multi = 0;

        ap->article_vars.gr_lucky.egg_spawn_wait = ATGRLUCKY_EGG_SPAWN_WAIT;

        func_800269C0(0x22AU);
    }
    return article_gobj;
}
