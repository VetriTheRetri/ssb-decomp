#include "article.h"

bool32 func_ovl3_8017EBE0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Vec3f pos = DObjGetStruct(article_gobj)->translate;

    if (ap->at_multi == 0)
    {
        return TRUE;
    }
    if (ap->article_vars.mew.esper_gfx_int == 0)
    {
        ap->article_vars.mew.esper_gfx_int = ATMEW_GFX_SPAWN_INT;

        func_ovl2_80102E90(&pos);
    }
    ap->article_vars.mew.esper_gfx_int--;

    ap->at_multi--;

    ap->phys_info.vel.y += ATMEW_FLY_ADD_VEL_Y;

    return FALSE;
}

void func_ovl3_8017EC84(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->at_multi = ATMEW_LIFETIME;

    if (rand_u16_range(2) != 0)
    {
        ap->phys_info.vel.x = ATMEW_START_VEL_X;
    }
    else
    {
        ap->phys_info.vel.x = -ATMEW_START_VEL_X;
    }
    ap->phys_info.vel.y = ATMEW_START_VEL_Y;

    func_800269C0(0x89U);

    if (ap->at_kind == At_Kind_Mew)
    {
        func_800269C0(0x13BU);
    }
    func_ovl2_801014A8(&DObjGetStruct(article_gobj)->translate);

    ap->article_vars.mew.esper_gfx_int = 0;
}

extern ArticleStatusDesc Article_Mew_Status[];

void func_ovl3_8017ED20(GObj *article_gobj)
{
    func_ovl3_8017EC84(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Mew_Status, 0);
}

bool32 jtgt_ovl3_8017ED54(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_8017ED20(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_8017EDA4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

extern intptr_t D_NF_0000BCC0;
extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Mew_Data;

GObj *jtgt_ovl3_8017EDE4(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Mew_Data, pos, vel, flags);

    if (article_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(article_gobj);
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        ap->phys_info.vel.z = 0.0F;
        ap->phys_info.vel.x = 0.0F;
        ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        joint->translate.y -= ap->attributes->gfx_offset.y;

        func_8000BD1C(joint, ((uintptr_t)ap->attributes->unk_0x0 - (intptr_t)&D_NF_0000BCC0) + (intptr_t)&D_NF_00013624, 0.0F); // Linker thing
    }
    return article_gobj;
}