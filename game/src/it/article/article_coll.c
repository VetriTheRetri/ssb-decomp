#include "article.h"

bool32 func_ovl3_80173480(Coll_Data *coll_data, s32 arg1, s32 arg2)
{
    s32 ground_line_id = coll_data->ground_line_id;
    bool32 is_collide_ground = FALSE;

    if (func_ovl2_800DA294(coll_data) != FALSE)
    {
        func_ovl2_800DA658(coll_data);
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DAAA8(coll_data) != FALSE)
    {
        func_ovl2_800DAE6C(coll_data);
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DB2BC(coll_data) != FALSE)
    {
        if (coll_data->coll_type & MPCOLL_MASK_GROUND)
        {
            func_ovl2_800D9F84(coll_data);
            is_collide_ground = TRUE;
        }
    }
    else
    {
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DB474(coll_data, ground_line_id) != FALSE)
    {
        func_ovl2_800DD59C(coll_data);

        if (coll_data->coll_type & MPCOLL_MASK_GROUND)
        {
            func_ovl2_800D9F84(coll_data);
            is_collide_ground = TRUE;
        }
        coll_data->unk_0x64 = FALSE;
    }
    return is_collide_ground;
}

bool32 func_ovl3_8017356C(GObj *article_gobj)
{
    func_ovl2_800DA034(&ArticleGetStruct(article_gobj)->coll_data, func_ovl3_80173480, article_gobj, FALSE);
}

bool32 func_ovl3_801735A0(GObj *article_gobj, void (*cb_coll)(GObj*))
{
    if (func_ovl3_8017356C(article_gobj) == FALSE)
    {
        cb_coll(article_gobj);

        return FALSE;
    }
    else return TRUE;
}

bool32 func_ovl3_801735E0(Coll_Data *coll_data, GObj *article_gobj, s32 arg2)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    JObj *joint = JObjGetStruct(article_gobj);

    if (func_ovl2_800DB838(coll_data) != FALSE)
    {
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DC3C8(coll_data) != FALSE)
    {
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DCF58(coll_data) != FALSE)
    {
        coll_data->unk_0x64 = TRUE;
    }
    if (func_ovl2_800DD578(coll_data) != FALSE)
    {
        coll_data->unk_0x64 = TRUE;

        func_800269C0(0x2EU);

        ap->rotate_speed = 0.0F;
        joint->rotate.z = 0.0F;
    }
    return coll_data->unk_0x64;
}

bool32 func_ovl3_80173680(GObj *article_gobj)
{
    func_ovl2_800DA034(&ArticleGetStruct(article_gobj)->coll_data, func_ovl3_801735E0, article_gobj, FALSE);
}