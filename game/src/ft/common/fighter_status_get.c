#include "fighter.h"
#include "article.h"
#include "gmmatch.h"

struct gmSceneInfo {
    /* 0x00 */ u8 scene;
    /* 0x01 */ u8 previousScene;
    /* 0x02 */ u8 pad02[0x13 - 0x02];
    /* 0x13 */ u8 player_port; // Port index of player in 1P game?
    /* 0x14 */ u8 pad14[0x48 - 0x14];
}; // size == 0x48

extern struct gmSceneInfo Scene_Info;
extern u8 D_ovl65_801936A8;
extern u8 D_ovl65_801936A9;

GObj *func_ovl3_80145990(GObj *fighter_gobj, u8 pickup_mask)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *pickup_gobj = NULL;
    ftItemPickup *item_pickup = &fp->attributes->item_pickup;
    GObj *article_gobj = gOMObjCommonLinks[GObjLinkIndexArticle];
    f32 closest_item_dist = (f32)FLOAT_MAX;
    bool32 is_pickup;
    f32 current_item_dist;
    Vec2f pickup_range;

    while (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        if (ap->is_allow_pickup)
        {
            if (fp->coll_data.ground_line_id == ap->coll_data.ground_line_id)
            {
                Vec3f *ft_translate = &DObjGetStruct(fighter_gobj)->translate;
                Vec3f *at_translate = &DObjGetStruct(article_gobj)->translate;
                ObjectColl *object_coll = &ap->coll_data.object_coll;

                is_pickup = FALSE;

                if ((ap->is_light_throw == TRUE) && (pickup_mask & FTCOMMON_GET_MASK_LIGHT))
                {
                    pickup_range.x = ft_translate->x + (fp->lr * item_pickup->pickup_offset_light.x);
                    pickup_range.y = ft_translate->y + item_pickup->pickup_offset_light.y;

                    if ((((pickup_range.x - item_pickup->pickup_range_light.x) - object_coll->width) < at_translate->x) && (at_translate->x < (item_pickup->pickup_range_light.x + pickup_range.x + object_coll->width)))
                    {
                        if ((((pickup_range.y - item_pickup->pickup_range_light.y) - object_coll->top) < at_translate->y) && (at_translate->y < ((item_pickup->pickup_range_light.y + pickup_range.y) - object_coll->bottom)))
                        {
                            is_pickup = TRUE;
                        }
                    }
                }
                if ((ap->is_light_throw == FALSE) && (pickup_mask & FTCOMMON_GET_MASK_HEAVY))
                {
                    pickup_range.x = ft_translate->x + (fp->lr * item_pickup->pickup_offset_heavy.x);
                    pickup_range.y = ft_translate->y + item_pickup->pickup_offset_heavy.y;

                    if ((((pickup_range.x - item_pickup->pickup_range_heavy.x) - object_coll->width) < at_translate->x) && (at_translate->x < (item_pickup->pickup_range_heavy.x + pickup_range.x + object_coll->width)))
                    {
                        if ((((pickup_range.y - item_pickup->pickup_range_heavy.y) - object_coll->top) < at_translate->y) && (at_translate->y < ((item_pickup->pickup_range_heavy.y + pickup_range.y) - object_coll->bottom)))
                        {
                            is_pickup = TRUE;
                        }
                    }
                }
                if (is_pickup != FALSE)
                {
                    current_item_dist = (pickup_range.x < at_translate->x) ? -(pickup_range.x - at_translate->x) : (pickup_range.x - at_translate->x);

                    if (current_item_dist < closest_item_dist)
                    {
                        closest_item_dist = current_item_dist;
                        pickup_gobj = article_gobj;
                    }
                }
            }
        }
        article_gobj = article_gobj->group_gobj_next;
    }
    return pickup_gobj;
}

void func_ovl3_80145BE4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *article_gobj = fp->item_hold;

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        if (ap->type == At_Type_Special)
        {
            switch (ap->at_kind)
            {
            case At_Kind_Tomato:
                func_ovl2_800EA3D4(fp, ATTOMATO_DAMAGE_HEAL);
                func_ovl3_801728D4(article_gobj);

                if ((Match_Info->game_type == gmMatch_GameType_1PGame) && (fp->port_id == Scene_Info.player_port) && (D_ovl65_801936A8 < U8_MAX))
                {
                    D_ovl65_801936A8++;
                }
                break;

            case At_Kind_Heart:
                func_ovl2_800EA3D4(fp, ATHEART_DAMAGE_HEAL);
                func_ovl3_801728D4(article_gobj);

                if ((Match_Info->game_type == gmMatch_GameType_1PGame) && (fp->port_id == Scene_Info.player_port) && (D_ovl65_801936A9 < U8_MAX))
                {
                    D_ovl65_801936A9++;
                }
                break;

            case At_Kind_Hammer:
                fp->hammer_time = FTCOMMON_HAMMER_TIME_MAX;

                ftSpecialItem_BGMSetPlay(ATHAMMER_BGM_ID);
                break;

            default:
                break;
            }
        }
    }
}

void func_ovl3_80145D28(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->item_hold != NULL)
    {
        Vec3f vel;

        vel.x = vel.y = vel.z = 0.0F;

        func_ovl3_80172AEC(fp->item_hold, &vel, ARTICLE_STALE_DEFAULT);
    }
}

void func_ovl3_80145D70(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *article_gobj;

    if (fp->command_vars.flags.flag1 != 0)
    {
        fp->command_vars.flags.flag1 = 0;

        article_gobj = func_ovl3_80145990(fighter_gobj, ((fp->status_info.status_id == ftStatus_Common_HeavyGet) ? FTCOMMON_GET_MASK_HEAVY : FTCOMMON_GET_MASK_LIGHT));

        if (article_gobj != NULL)
        {
            func_ovl3_80172CA4(article_gobj, fighter_gobj);
        }
    }
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        if (fp->status_info.status_id == ftStatus_Common_HeavyGet)
        {
            if (fp->item_hold != NULL)
            {
                if ((fp->ft_kind == Ft_Kind_Donkey) || (fp->ft_kind == Ft_Kind_PolyDonkey) || (fp->ft_kind == Ft_Kind_GiantDonkey))
                {
                    func_ovl3_8014D49C(fighter_gobj);
                }
                else func_ovl3_801460E8(fighter_gobj);
            }
            else func_ovl3_8013E1C8(fighter_gobj);
        }
        else
        {
            article_gobj = fp->item_hold;

            if (article_gobj != NULL)
            {
                Article_Struct *ap = ArticleGetStruct(article_gobj);

                if (ap->type == 5)
                {
                    func_ovl3_80145BE4(fighter_gobj);

                    if (ap->at_kind == At_Kind_Hammer)
                    {
                        func_ovl2_800F3938(fighter_gobj);

                        return;
                    }
                }
            }
            func_ovl3_8013E1C8(fighter_gobj);
        }
    }
}

void func_ovl3_80145ED8(GObj *fighter_gobj)
{
    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        func_ovl3_80145BE4(fighter_gobj);
        func_ovl3_8013F9E0(fighter_gobj);
    }
}

void func_ovl3_80145F10(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DDDA8(fighter_gobj) == FALSE)
    {
        if (fp->item_hold != NULL)
        {
            Vec3f vel;

            vel.x = vel.y = vel.z = 0.0F;

            func_ovl3_80172AEC(fp->item_hold, &vel, ARTICLE_STALE_DEFAULT);
        }
        func_ovl3_8013F9E0(fighter_gobj);
    }
}

void func_ovl3_80145F74(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800DDE50(fighter_gobj) == FALSE)
    {
        if (fp->item_hold != NULL)
        {
            Vec3f vel;

            vel.x = vel.y = vel.z = 0.0F;

            func_ovl3_80172AEC(fp->item_hold, &vel, ARTICLE_STALE_DEFAULT);
        }
        func_ovl3_8013F9E0(fighter_gobj);
    }
}

void func_ovl3_80145FD8(GObj *fighter_gobj, GObj *article_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    fp->command_vars.flags.flag1 = 0;

    ftStatus_Update(fighter_gobj, (!(ap->is_light_throw) ? ftStatus_Common_HeavyGet : ftStatus_Common_LightGet), 0.0F, 1.0F, 0U);
    ftAnim_Update(fighter_gobj);

    if (fp->status_info.status_id == ftStatus_Common_HeavyGet)
    {
        fp->proc_damage = func_ovl3_80145D28;
    }
    else fp->proc_damage = func_ovl3_80145BE4;
}

bool32 func_ovl3_80146064(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->item_hold == NULL)
    {
        GObj *article_gobj = func_ovl3_80145990(fighter_gobj, (FTCOMMON_GET_MASK_LIGHT | FTCOMMON_GET_MASK_HEAVY));

        if (article_gobj != NULL)
        {
            func_ovl3_80145FD8(fighter_gobj, article_gobj);

            return TRUE;
        }
    }
    return FALSE;
}

void func_ovl3_801460B8(GObj *fighter_gobj)
{
    if (func_ovl3_80146BE0(fighter_gobj) == FALSE)
    {
        func_ovl3_8014625C(fighter_gobj);
    }
}

void func_ovl3_801460E8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_LiftWait, 0.0F, 1.0F, 0x40U);

    fp->proc_damage = func_ovl3_80145D28;
}

void func_ovl3_80146130(Fighter_Struct *fp)
{
    fp->status_vars.common.lift.turn_frames--;

    fp->joint[0]->rotate.y += FTCOMMON_LIFT_TURN_STEP;

    func_ovl2_800EB528(fp->joint[0]);

    if (fp->status_vars.common.lift.turn_frames == (FTCOMMON_LIFT_TURN_FRAMES / 2))
    {
        fp->lr = -fp->lr;
        fp->phys_info.vel_ground.x = -fp->phys_info.vel_ground.x;
    }
}

void func_ovl3_801461A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_80146130(fp);

    if (fp->status_vars.common.lift.turn_frames == 0)
    {
        func_ovl3_801460E8(fighter_gobj);
    }
}

void func_ovl3_801461E8(GObj *fighter_gobj)
{
    func_ovl3_80146BE0(fighter_gobj);
}

void func_ovl3_80146208(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    ftStatus_Update(fighter_gobj, ftStatus_Common_LiftTurn, 0.0F, 1.0F, 0x40U);

    fp->proc_damage = func_ovl3_80145D28;

    fp->status_vars.common.lift.turn_frames = FTCOMMON_LIFT_TURN_FRAMES;

    func_ovl3_80146130(fp);
}

bool32 func_ovl3_8014625C(GObj *fighter_gobj)
{
    if (func_ovl3_8013E9D0(fighter_gobj) != FALSE)
    {
        func_ovl3_80146208(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}