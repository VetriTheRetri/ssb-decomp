#include "fighter.h"
#include "item.h"

Item_Struct* func_ovl3_80131B00(Fighter_Struct *fp)
{
    GObj *item_gobj = gOMObjCommonLinks[GObjLinkIndex_Item];

    if (item_gobj != NULL)
    {
        do
        {
            Item_Struct *ip = ItemGetStruct(item_gobj);

            if (ip->owner_gobj == fp->this_fighter)
            {
                return ip;
            }
            item_gobj = item_gobj->group_gobj_next;
        } 
        while (item_gobj != NULL);
    }
    return NULL;
}

Vec3f* func_ovl3_80131B44(Fighter_Struct *fp, s32 it_kind)
{
    GObj *item_gobj = gOMObjCommonLinks[GObjLinkIndex_Item];

    if (item_gobj != NULL)
    {
        do
        {
            Item_Struct *ip = ItemGetStruct(item_gobj);

            if ((ip->owner_gobj == fp->this_fighter) && (ip->it_kind == it_kind))
            {
                return &DObjGetStruct(ip->item_gobj)->translate;
            }
            item_gobj = item_gobj->group_gobj_next;
        } 
        while (item_gobj != NULL);
    }
    return NULL;
}

void func_ovl3_80131BA0(Fighter_Struct *fp)
{
    Vec3f *pos = func_ovl3_80131B44(fp, It_Kind_PKThunder_Trail);
    Fighter_Com *ft_com = &fp->fighter_com;

    if (pos != NULL)
    {
        f32 dist_x = ft_com->target_pos.x - pos->x;
        f32 dist_y = ft_com->target_pos.y - pos->y;

        f32 sqrt = 1.0F / sqrtf(SQUARE(dist_x) + SQUARE(dist_y));

        fp->input.stick_com.x = (GMCONTROLLER_RANGE_MAX_F * dist_x * sqrt);
        fp->input.stick_com.y = (GMCONTROLLER_RANGE_MAX_F * dist_y * sqrt);
    }
    else
    {
        fp->input.stick_com.x = 0;
        fp->input.stick_com.y = 0;
    }
}
