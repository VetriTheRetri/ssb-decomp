#include "article.h"

void func_ovl3_80172310(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->rotate_speed = (ap->attributes->spin_speed != 0) ? (ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ARTICLE_SPIN_SPEED_MUL_DEFAULT) : 0.0F;

    if (ap->lr == LEFT)
    {
        ap->rotate_speed = -ap->rotate_speed;
    }
}

void func_ovl3_80172394(GObj *article_gobj, bool32 is_prev_spawn)
{
    // is_prev_spawn = whether article is newly spawned or previously spawned; 0 = new, 1 = old

    Article_Struct *ap = ArticleGetStruct(article_gobj); // Ternary doesn't match here smh

    if (is_prev_spawn == FALSE)
    {
        if (ap->attributes->spin_speed != 0)
        {
            ap->rotate_speed = ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ARTICLE_SPIN_SPEED_MUL_NEW_SPAWN;
        }
        else ap->rotate_speed = 0.0F;
    }
    else if (ap->attributes->spin_speed != 0)
    {
        ap->rotate_speed = ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ARTICLE_SPIN_SPEED_MUL_PREV_SPAWN;
    }
    else ap->rotate_speed = 0.0F;
}

void func_ovl3_8017245C(GObj *article_gobj, f32 *spin_speed, bool32 is_smash_throw)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->rotate_speed = (is_smash_throw != FALSE) ? ARTICLE_SPIN_SPEED_SET_SMASH_THROW : ARTICLE_SPIN_SPEED_SET_NORMAL_THROW;

    if (*spin_speed < 0) // Facing direction, sort of
    {
        ap->rotate_speed = -ap->rotate_speed;
    }

    ap->rotate_speed = (ap->attributes->spin_speed != 0) ? (ap->attributes->spin_speed * ARTICLE_SPIN_SPEED_FRACTION_DEFAULT * ap->rotate_speed) : 0.0F;
}

void func_ovl3_80172508(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->lr = (ap->phys_info.vel.x >= 0.0F) ? RIGHT : LEFT;

    func_ovl3_80172310(article_gobj);
}

void func_ovl3_80172558(Article_Struct *ap, f32 vel_y_sub, f32 gravity)
{
    ap->phys_info.vel.y -= vel_y_sub;

    if (gravity < func_ovl0_800C7A84(&ap->phys_info.vel))
    {
        func_ovl0_800C7A00(&ap->phys_info.vel);
        func_ovl0_800C7AE0(&ap->phys_info.vel, gravity);
    }
}

extern s32 dbObjDisplayStatus_Global_Article; // Static (.bss)

void func_ovl3_801725BC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->owner_gobj = NULL;
    ap->team = ARTICLE_TEAM_DEFAULT;
    ap->port_index = ARTICLE_PORT_DEFAULT;
    ap->unk_0x16 = ARTICLE_UNK_DEFAULT;
    ap->player_number = 0;
    ap->article_hit[0].stale = ARTICLE_STALE_DEFAULT;

    ap->display_state = dbObjDisplayStatus_Global_Article;
}

void func_ovl3_801725F8(Article_Struct *ap)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(ap->article_hit[0].hit_targets); i++)
    {
        ArticleHitArray *targets = &ap->article_hit[0].hit_targets[i];

        targets->victim_gobj = NULL;

        targets->victim_flags.flags_b0 = targets->victim_flags.flags_b1 = targets->victim_flags.flags_b2 = FALSE;

        targets->victim_flags.timer_rehit = 0;

        targets->victim_flags.flags_b456 = 7;
    }
}

void func_ovl3_8017275C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_801725F8(ap);

    ap->article_hit[0].update_state = gmHitCollision_UpdateState_New;

    func_ovl3_8016F280(article_gobj);
}

void func_ovl3_8017279C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_damage_all = TRUE;

    ap->owner_gobj = NULL;

    ap->team = ARTICLE_TEAM_DEFAULT;
}

void func_ovl3_801727BC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->owner_gobj = ap->damage_gobj;
    ap->team = ap->damage_team;
    ap->port_index = ap->damage_port;
    ap->player_number = ap->player_number; // Could potentially cause a bug? Didn't they mean damage_player_number?
    ap->unk_0x16 = ap->unk_0x2B4;
    ap->display_state = ap->damage_display_state;
}

s32 func_ovl3_801727F4(Article_Struct *ap)
{
    s32 damage;
    f32 f;

    if (ap->x2CF_flag_b2)
    {
        f32 mag = (vec3f_mag(&ap->phys_info.vel) * 0.1F); // Wat

        damage = ap->article_hit[0].stale * (ap->article_hit[0].damage + mag); // Wat
    }
    else
    {
        damage = ap->article_hit[0].damage;
    }

    f = damage; // Wat!

    f *= ap->article_hit[0].throw_mul; // WAT!

    return (ap->article_hit[0].throw_mul * damage) + 0.999F; // WAT!!! (It doesn't match otherwise???)
}

bool32 func_ovl3_80172890(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (((ap->at_kind == At_Kind_StarRod) || (ap->at_kind == At_Kind_L_Gun) || (ap->at_kind == At_Kind_F_Flower)) && (ap->unk_0x33E == 0))
    {
        return TRUE;
    }
    else return FALSE;
}
