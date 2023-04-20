#include "fighter.h"
#include "article.h"
#include "gmmatch.h"

struct UnkA4AD0 {
    /* 0x00 */ u8 scene;
    /* 0x01 */ u8 previousScene;
    /* 0x02 */ u8 pad02[0x13 - 0x02];
    /* 0x13 */ u8 player_port; // Port index of player in 1P game?
    /* 0x14 */ u8 pad14[0x48 - 0x14];
}; // size == 0x48

extern struct UnkA4AD0 D_800A4AD0;
extern u8 D_ovl65_801936A8;
extern u8 D_ovl65_801936A9;

GObj *func_ovl3_80145990(GObj *fighter_gobj, u8 pickup_mask)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *pickup_gobj = NULL;
    ftItemPickup *item_pickup = &fp->attributes->item_pickup;
    GObj *article_gobj = gOMObjCommonLinks[GObjLinkIndex_Article];
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

                if ((ap->is_light_throw == TRUE) && (pickup_mask & 1))
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
                if ((ap->is_light_throw == FALSE) && (pickup_mask & 2))
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
    GObj *article_gobj = fp->article_hold;

    if (article_gobj != NULL)
    {
        Article_Struct *ap = ArticleGetStruct(article_gobj);

        if (ap->unk_0x10 == 5)
        {
            switch (ap->at_kind)
            {
            case At_Kind_Tomato:
                func_ovl2_800EA3D4(fp, ATTOMATO_DAMAGE_HEAL);
                func_ovl3_801728D4(article_gobj);

                if ((Match_Info->game_type == 5) && (fp->port_id == D_800A4AD0.player_port) && (D_ovl65_801936A8 < U8_MAX))
                {
                    D_ovl65_801936A8++;
                }
                break;

            case At_Kind_Heart:
                func_ovl2_800EA3D4(fp, ATHEART_DAMAGE_HEAL);
                func_ovl3_801728D4(article_gobj);

                if ((Match_Info->game_type == 5) && (fp->port_id == D_800A4AD0.player_port) && (D_ovl65_801936A9 < U8_MAX))
                {
                    D_ovl65_801936A9++;
                }
                break;

            case At_Kind_Hammer:
                fp->hammer_time = 720;

                func_ovl2_800E7AFC(0x2D);
                break;

            default:
                break;
            }
        }
    }
}