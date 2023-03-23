#include "article.h"
#include "fighter.h"

extern intptr_t Article_Link_Bomb_Scale;
extern ArticleSpawnData Article_Link_Bomb_Data;

void func_ovl3_801859C0(GObj *article_gobj)
{
    DObj *joint = DObjGetStruct(article_gobj);
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->article_vars.link_bomb.scale_int == 0)
    {
        f32 *p_scale = (f32*) ((uintptr_t)*Article_Link_Bomb_Data.p_file + (intptr_t)&Article_Link_Bomb_Scale); // Linker thing

        s32 index = (ap->article_vars.link_bomb.scale_index >= ATLINKBOMB_SCALE_INDEX_REWIND) ? ATLINKBOMB_SCALE_INDEX_MAX - ap->article_vars.link_bomb.scale_index : ap->article_vars.link_bomb.scale_index;

        if (ap->is_pickup)
        {
            joint->next->scale.x = joint->next->scale.y = p_scale[index];
        }
        else
        {
            joint->scale.x = joint->scale.y = p_scale[index];
        }
        ap->article_vars.link_bomb.scale_int = ATLINKBOMB_SCALE_INT;

        if (ap->article_vars.link_bomb.scale_index >= ATLINKBOMB_SCALE_INDEX_MAX)
        {
            ap->article_vars.link_bomb.scale_index = 0;
        }
        else ap->article_vars.link_bomb.scale_index += 1; // Doesn't match with "++" lol
    }
    ap->article_vars.link_bomb.scale_int--;
}

void func_ovl3_80185A80(GObj *article_gobj)
{
    s32 unused;
    DObj *joint = DObjGetStruct(article_gobj);
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Effect_Unk *ep;

    func_ovl3_80185CE4(article_gobj);

    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ATLINKBOMB_EXPLODE_GFX_SCALE;
        ep->effect_info->scale.y = ATLINKBOMB_EXPLODE_GFX_SCALE;
        ep->effect_info->scale.z = ATLINKBOMB_EXPLODE_GFX_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(article_gobj)->unk_0x54 = 2;

    ap->article_hit.hit_sfx = 1;

    func_ovl3_8017275C(article_gobj);
    func_ovl3_8018656C(article_gobj);
}

void func_ovl3_80185B18(GObj *article_gobj)
{
    s32 unused[5];
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    atCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(article_gobj);
    Vec3f pos = joint->translate;

    pos.y += attributes->gfx_offset.y;

    func_ovl2_800FF3F4(&pos, ap->lr, 1.0F);
}

bool32 func_ovl3_80185B84(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->damage_taken_recent >= ATLINKBOMB_HEALTH)
    {
        func_ovl3_80186368(article_gobj);
    }
    else
    {
        ap->lr = -ap->lr_damage;

        ap->phys_info.vel.x = -ap->lr_damage * ATLINKBOMB_DAMAGE_RECOIL_VEL_X;
        ap->phys_info.vel.y = -ap->lr_damage * ATLINKBOMB_DAMAGE_RECOIL_VEL_Y;
    }
    return FALSE;
}

bool32 func_ovl3_80185BFC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if ((ABSF(ap->phys_info.vel.x) > ATLINKBOMB_EXPLODE_THRESHOLD_VEL_X) || (ABSF(ap->phys_info.vel.y) > ATLINKBOMB_EXPLODE_THRESHOLD_VEL_Y))
    {
        func_ovl3_80186368(article_gobj);
    }
    else
    {
        ap->lr = -ap->lr_attack;

        ap->phys_info.vel.x = -ap->lr_attack * ATLINKBOMB_HIT_RECOIL_VEL_X;
        ap->phys_info.vel.y = ATLINKBOMB_HIT_RECOIL_VEL_Y;

        func_ovl3_80185FD8(article_gobj);
    }
    return FALSE;
}

void func_ovl3_80185CD4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_Normal;
}

void func_ovl3_80185CD4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hurt.hit_status = gmHitCollision_HitStatus_None;
}

bool32 func_ovl3_80185CF0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATLINKBOMB_GRAVITY, ATLINKBOMB_T_VEL);

    if (ap->lifetime == 0)
    {
        func_ovl3_80186368(article_gobj);
    }
    if (ap->lifetime == ATLINKBOMB_BLOAT_BEGIN)
    {
        func_ovl3_80172F98(article_gobj, ATLINKBOMB_BLOAT_COLANIM_ID, ATLINKBOMB_BLOAT_COLANIM_LENGTH);

        ap->article_vars.link_bomb.scale_index = 1;
    }
    if (ap->lifetime < ATLINKBOMB_BLOAT_BEGIN)
    {
        func_ovl3_801859C0(article_gobj);
    }
    ap->lifetime--;

    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80185DCC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->phys_info.vel.x != 0.0F)
    {
        ap->phys_info.vel.x += (-1.0F) * ap->lr;
    }
    if (ABSF(ap->phys_info.vel.x) < 1.0F)
    {
        ap->phys_info.vel.x = 0;
    }
    if (ap->lifetime == 0)
    {
        func_ovl3_80186368(article_gobj);
    }
    if (ap->lifetime == ATLINKBOMB_BLOAT_BEGIN)
    {
        func_ovl3_80172F98(article_gobj, ATLINKBOMB_BLOAT_COLANIM_ID, ATLINKBOMB_BLOAT_COLANIM_LENGTH);

        ap->article_vars.link_bomb.scale_index = 1;
    }
    if (ap->lifetime < ATLINKBOMB_BLOAT_BEGIN)
    {
        func_ovl3_801859C0(article_gobj);
    }
    ap->lifetime--;

    return FALSE;
}

bool32 jtgt_ovl3_80185F10(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_80185FD8);

    return FALSE;
}

bool32 jtgt_ovl3_80185F38(GObj *article_gobj)
{
    func_ovl3_80173B24(article_gobj, 0.4F, 0.3F, func_ovl3_80185F70);

    return FALSE;
}

extern ArticleStatusDesc Article_Link_Bomb_Status[];

void func_ovl3_80185F70(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->article_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->is_show_indicator = TRUE;

    ap->times_landed = 0;

    ap->phys_info.vel.z = 0.0F;
    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.x = 0.0F;

    func_ovl3_80173F54(ap);
    func_ovl3_80185CD4(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Link_Bomb_Status, 0);
}

void func_ovl3_80185FD8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80185CD4(article_gobj);
    func_ovl3_80172EC8(article_gobj, &Article_Link_Bomb_Status, 1);
}

bool32 func_ovl3_80186024(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Fighter_Struct *fp = FighterGetStruct(ap->owner_gobj);

    if (fp->status_info.status_id == ftStatus_Common_DokanWait) // Odd but go off
    {
        return FALSE;
    }
    else
    {
        if (ap->lifetime == 0)
        {
            func_ovl3_80172984(article_gobj, &ap->phys_info.vel, 1.0F); // Ok, WHAT? This function takes 5 arguments, but it doesn't match otherwise???
                                                                        // Did they actually redefine this? Passes pointer in a3 instead of u16...
                                                                        // Do we leave this out of the header and declare it separately to match?
                                                                        // Update 3/23/2023: matches as variadic. No comment.
            func_ovl3_8017279C(article_gobj);
            func_ovl3_80186368(article_gobj);
        }
        if (ap->lifetime == ATLINKBOMB_BLOAT_BEGIN)
        {
            func_ovl3_80172F98(article_gobj, ATLINKBOMB_BLOAT_COLANIM_ID, ATLINKBOMB_BLOAT_COLANIM_LENGTH);

            ap->article_vars.link_bomb.scale_index = 1;
        }
        if (ap->lifetime < ATLINKBOMB_BLOAT_BEGIN)
        {
            func_ovl3_801859C0(article_gobj);
        }
        ap->lifetime--;

        return FALSE;
    }
}