#include "item.h"
#include "fighter.h"



#define THREEQUART_PI32 2.3561945F

bool32 jtgt_ovl3_80169390(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
        return TRUE;
    }
    else func_ovl3_80168088(ip, ITPIKACHUJOLT_GRAVITY, ITPIKACHUJOLT_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_801693EC(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Vec3f pos;
    u32 unused[2];

    if (func_ovl3_80167B58(item_gobj) != FALSE)
    {
        func_ovl3_8016A42C(item_gobj, &DObjGetStruct(item_gobj)->translate, 0);

        return TRUE;
    }

    else if (ip->coll_data.coll_mask & MPCOLL_MASK_RWALL)
    {
        func_ovl2_800F4650(ip->coll_data.rwall_line_id, &pos);

        if (pos.y < DObjGetStruct(item_gobj)->translate.y)
        {
            DObjGetStruct(item_gobj)->translate.y = pos.y;
        }

        func_ovl2_800F4670(ip->coll_data.rwall_line_id, &pos);

        if (DObjGetStruct(item_gobj)->translate.y < pos.y)
        {
            DObjGetStruct(item_gobj)->translate.y = pos.y;
        }
        func_ovl3_8016A42C(item_gobj, &DObjGetStruct(item_gobj)->translate, 3);

        return TRUE;
    }

    else if (ip->coll_data.coll_mask & MPCOLL_MASK_LWALL)
    {
        func_ovl2_800F4690(ip->coll_data.lwall_line_id, &pos);

        if (pos.y < DObjGetStruct(item_gobj)->translate.y)
        {
            DObjGetStruct(item_gobj)->translate.y = pos.y;
        }
        func_ovl2_800F46B0(ip->coll_data.lwall_line_id, &pos);

        if (DObjGetStruct(item_gobj)->translate.y < pos.y)
        {
            DObjGetStruct(item_gobj)->translate.y = pos.y;
        }
        func_ovl3_8016A42C(item_gobj, &DObjGetStruct(item_gobj)->translate, 1);

        return TRUE;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016953C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl2_800FE068(&DObjGetStruct(item_gobj)->translate, ip->item_hit.damage);

    return TRUE;
}

bool32 jtgt_ovl3_8016956C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    return FALSE;
}

bool32 jtgt_ovl3_801695B0(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    ip->lifetime = ITPIKACHUJOLT_LIFETIME;

    func_ovl3_801680EC(ip, fp);

    return FALSE;
}

extern ItemSpawnData Item_ThunderJoltAir_Desc;

GObj* func_ovl3_801695E4(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_ThunderJoltAir_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->lifetime = ITPIKACHUJOLT_LIFETIME;

    ip->phys_info.vel = *vel;

    return item_gobj;
}

extern u8 D_NF_00001A20;
extern u8 D_NF_00001AE0;
extern void *D_ovl2_801310C4;

void func_ovl3_80169654(GObj *item_gobj)
{
    func_8000BED8(item_gobj, (uintptr_t)D_ovl2_801310C4 + &D_NF_00001A20, (uintptr_t)D_ovl2_801310C4 + &D_NF_00001AE0, 0.0F); // Linker thing
    func_8000DF34(item_gobj);
}

bool32 jtgt_ovl3_801696A0(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (item_gobj->anim_frame == ITPIKACHUJOLT_ANIM_PUSH_FRAME)
    {
        func_ovl2_80101C34(&DObjGetStruct(item_gobj)->translate, DObjGetStruct(item_gobj)->rotate.z);
        func_ovl3_80169654(item_gobj);
    }
    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
        return TRUE;
    }

    ip->phys_info.vel.x = cosf(DObjGetStruct(item_gobj)->rotate.z) * ITPIKACHUJOLT_VEL;
    ip->phys_info.vel.y = __sinf(DObjGetStruct(item_gobj)->rotate.z) * ITPIKACHUJOLT_VEL;

    switch (ip->item_vars.thunder_jolt.coll_type)
    {
    case CENTER:
        ip->phys_info.vel.x *= ip->lr;
        break;

    case WALL_UP:
    case WALL_DOWN:
        if (ip->lr == WALL_UP)
        {
            if (ip->phys_info.vel.y < 0.0F)
            {
                ip->phys_info.vel.y *= -1.0F;
            }
        }
        if (ip->lr == WALL_DOWN)
        {
            if (ip->phys_info.vel.y > 0.0F)
            {
                ip->phys_info.vel.y *= -1.0F;
            }
        }
        break;
    }
    return FALSE;
}

s32 func_ovl3_8016981C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Vec3f pos;
    Vec3f rotate;
    s32 line_id;

    switch (ip->item_vars.thunder_jolt.coll_type)
    {
    case 0:

        if (ip->lr == RIGHT)
        {
            if ((func_ovl2_800F8974(&ip->coll_data.pos_curr, ip->coll_data.p_translate, &pos, &line_id, NULL, NULL) != FALSE) && (func_ovl2_800FAA24(ip->coll_data.ground_line_id) != line_id))
            {
                if (func_ovl2_800F4194(line_id, &pos, NULL, NULL, &rotate) != FALSE)
                {
                    ip->item_vars.thunder_jolt.coll_type = 3;
                    ip->coll_data.rwall_line_id = line_id;
                    ip->lr = WALL_UP;

                    DObjGetStruct(item_gobj)->translate = pos;

                    func_ovl3_80169654(item_gobj);

                    DObjGetStruct(item_gobj)->rotate.z = atan2f(-rotate.x, rotate.y);

                    return 1;
                }
                return 2;
            }
            break;
        }
        else if ((func_ovl2_800F769C(&ip->coll_data.pos_curr, ip->coll_data.p_translate, &pos, &line_id, NULL, NULL) != FALSE) && (func_ovl2_800FA964(ip->coll_data.ground_line_id) != line_id))
        {
            if (func_ovl2_800F41C0(line_id, &pos, NULL, NULL, &rotate) != FALSE)
            {
                ip->item_vars.thunder_jolt.coll_type = 2;
                ip->coll_data.lwall_line_id = line_id;
                ip->lr = WALL_UP;

                DObjGetStruct(item_gobj)->translate = pos;

                func_ovl3_80169654(item_gobj);

                DObjGetStruct(item_gobj)->rotate.z = atan2f(-rotate.x, rotate.y);

                return 1;
            }
            return 2;
        }
        break;

    case 3:

        if (ip->lr == WALL_DOWN)
        {
            if ((func_ovl2_800F521C(&ip->coll_data.pos_curr, ip->coll_data.p_translate, &pos, &line_id, NULL, NULL) != FALSE) && (func_ovl2_800FAC64(ip->coll_data.rwall_line_id) != line_id))
            {
                if (func_ovl2_800F3DD8(line_id, &pos, NULL, NULL, &rotate) != FALSE)
                {
                    ip->item_vars.thunder_jolt.coll_type = 0;
                    ip->coll_data.ground_line_id = line_id;
                    ip->lr = LEFT;

                    DObjGetStruct(item_gobj)->translate = pos;

                    func_ovl3_80169654(item_gobj);

                    DObjGetStruct(item_gobj)->rotate.z = atan2f(-rotate.x, rotate.y);
                    return 1;
                }
                return 2;
            }
            break;
        }
        else if (func_ovl2_800F64D4(&ip->coll_data.pos_curr, ip->coll_data.p_translate, &pos, &line_id, NULL, NULL) != FALSE)
        {
            return 2;
        }
        break;

    case 2:

        if (ip->lr == WALL_DOWN)
        {
            if ((func_ovl2_800F521C(&ip->coll_data.pos_curr, ip->coll_data.p_translate, &pos, &line_id, NULL, NULL) != FALSE) && (func_ovl2_800FADE4(ip->coll_data.lwall_line_id) != line_id))
            {
                if (func_ovl2_800F3DD8(line_id, &pos, NULL, NULL, &rotate) != FALSE)
                {
                    ip->item_vars.thunder_jolt.coll_type = 0;
                    ip->coll_data.ground_line_id = line_id;
                    ip->lr = RIGHT;

                    DObjGetStruct(item_gobj)->translate = pos;

                    func_ovl3_80169654(item_gobj);

                    DObjGetStruct(item_gobj)->rotate.z = atan2f(-rotate.x, rotate.y);
                    return 1;
                }
                return 2;
            }
        }
        else if (func_ovl2_800F64D4(&ip->coll_data.pos_curr, ip->coll_data.p_translate, &pos, &line_id, NULL, NULL) != FALSE)
        {
            return 2;
        }
        break;

    default: break;
    }
    DObjGetStruct(item_gobj)->rotate.z = atan2f(-ip->item_vars.thunder_jolt.rotate.x, ip->item_vars.thunder_jolt.rotate.y);

    return 0;
}

bool32 func_ovl3_80169BF0(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Vec3f rotate;

    func_ovl3_80169654(item_gobj);

    switch (ip->item_vars.thunder_jolt.coll_type)
    {
    case 0:
        func_ovl2_800F3DD8(ip->coll_data.ground_line_id, &DObjGetStruct(item_gobj)->translate, NULL, NULL, &rotate);
        break;
    case 3:
        func_ovl2_800F4194(ip->coll_data.rwall_line_id, &DObjGetStruct(item_gobj)->translate, NULL, NULL, &rotate);
        break;
    case 2:
        func_ovl2_800F41C0(ip->coll_data.lwall_line_id, &DObjGetStruct(item_gobj)->translate, NULL, NULL, &rotate);
        break;
    }

    if (ITPIKACHUJOLT_ROTATE_ANGLE_MAX < vec3f_angle_diff(&rotate, &ip->item_vars.thunder_jolt.rotate))
    {
        func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

        return TRUE;
    }
    else DObjGetStruct(item_gobj)->rotate.z = atan2f(-rotate.x, rotate.y);

    return FALSE;
}

bool32 func_ovl3_80169D08(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    s32 coll_type;
    Vec3f pos;
    s32 line_id;
    s32 unused;

    switch (ip->item_vars.thunder_jolt.coll_type)
    {
    case 0:

        if (func_ovl2_800FC67C(ip->coll_data.ground_line_id) == FALSE)
        {
            func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
            return TRUE;
        }

        if (func_ovl2_800F3DD8(ip->coll_data.ground_line_id, &DObjGetStruct(item_gobj)->translate, &pos, NULL, &ip->item_vars.thunder_jolt.rotate) != FALSE)
        {
            DObjGetStruct(item_gobj)->translate.y += pos.x;

            if (func_ovl3_8016981C(item_gobj) == 2)
            {
                func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

                return TRUE;
            }
            return FALSE;
        }

        if (ip->lr == RIGHT)
        {
            line_id = func_ovl2_800FA964(ip->coll_data.ground_line_id);
        }
        else
        {
            if (ip->lr == LEFT)
            {
                line_id = func_ovl2_800FAA24(ip->coll_data.ground_line_id);
            }
            else line_id = -1;
        }
        if ((line_id == -1) || (line_id == -2))
        {
            if (func_ovl3_8016981C(item_gobj) != 1)
            {
                func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);

                return TRUE;
            }
            return FALSE;
        }

        coll_type = func_ovl2_800FA8A4(line_id);

        if (ip->lr == RIGHT)
        {
            if (coll_type == 3)
            {
                ip->coll_data.rwall_line_id = line_id;
                ip->item_vars.thunder_jolt.coll_type = coll_type;
                ip->lr = WALL_UP;

                func_ovl2_800F4670(line_id, &DObjGetStruct(item_gobj)->translate);

                return func_ovl3_80169BF0(item_gobj);
            }
            if (coll_type == 2)
            {
                ip->coll_data.lwall_line_id = line_id;
                ip->item_vars.thunder_jolt.coll_type = coll_type;
                ip->lr = WALL_DOWN;

                func_ovl2_800F4690(line_id, &DObjGetStruct(item_gobj)->translate);

                return func_ovl3_80169BF0(item_gobj);
            }
        }
        else if (coll_type == 3)
        {
            ip->coll_data.rwall_line_id = line_id;
            ip->item_vars.thunder_jolt.coll_type = coll_type;
            ip->lr = WALL_DOWN;

            func_ovl2_800F4650(line_id, &DObjGetStruct(item_gobj)->translate);

            return func_ovl3_80169BF0(item_gobj);
        }
        else if (coll_type == 2)
        {
            ip->coll_data.lwall_line_id = line_id;
            ip->item_vars.thunder_jolt.coll_type = coll_type;
            ip->lr = WALL_UP;

            func_ovl2_800F46B0(line_id, &DObjGetStruct(item_gobj)->translate);

            return func_ovl3_80169BF0(item_gobj);
        }

        if (func_ovl3_8016981C(item_gobj) != 1)
        {
            func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
            return TRUE;
        }
        return FALSE;

        break;

    case 3:

        if (func_ovl2_800FC67C(ip->coll_data.rwall_line_id) == 0)
        {
            func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
            return TRUE;
        }

        if (func_ovl2_800F4194(ip->coll_data.rwall_line_id, &DObjGetStruct(item_gobj)->translate, &pos, NULL, &ip->item_vars.thunder_jolt.rotate) != FALSE)
        {
            DObjGetStruct(item_gobj)->translate.x += pos.x;

            if (func_ovl3_8016981C(item_gobj) == 2)
            {
                func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
                return TRUE;
            }
            return FALSE;
        }
        if (ip->lr == WALL_UP)
        {
            line_id = func_ovl2_800FAC64(ip->coll_data.rwall_line_id);
        }
        else
        {
            line_id = func_ovl2_800FAD24(ip->coll_data.rwall_line_id);
        }
        if ((line_id == -1) || (line_id == -2))
        {
            if (func_ovl3_8016981C(item_gobj) != 1)
            {
                func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
                return TRUE;
            }
            return FALSE;
        }

        coll_type = func_ovl2_800FA8A4(line_id);

        if (ip->lr == WALL_UP)
        {
            if (coll_type == At_Type_Ground)
            {
                ip->coll_data.ground_line_id = line_id;
                ip->item_vars.thunder_jolt.coll_type = coll_type;
                ip->lr = RIGHT;

                func_ovl2_800F4428(line_id, &DObjGetStruct(item_gobj)->translate);

                return func_ovl3_80169BF0(item_gobj);
            }
        }
        else if (coll_type == At_Type_Ground)
        {
            ip->coll_data.ground_line_id = line_id;
            ip->item_vars.thunder_jolt.coll_type = coll_type;
            ip->lr = LEFT;

            func_ovl2_800F4408(line_id, &DObjGetStruct(item_gobj)->translate);

            return func_ovl3_80169BF0(item_gobj);
        }

        if (func_ovl3_8016981C(item_gobj) != 1)
        {
            func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
            return TRUE;
        }
        return FALSE;

        break;

    case 2:

        if (func_ovl2_800FC67C(ip->coll_data.lwall_line_id) == FALSE)
        {
            func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
            return TRUE;
        }

        if (func_ovl2_800F41C0(ip->coll_data.lwall_line_id, &DObjGetStruct(item_gobj)->translate, &pos, NULL, &ip->item_vars.thunder_jolt.rotate) != FALSE)
        {
            DObjGetStruct(item_gobj)->translate.x += pos.x;

            if (func_ovl3_8016981C(item_gobj) == 2)
            {
                func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0f);
                return TRUE;
            }
            return FALSE;
        }
        if (ip->lr == WALL_UP)
        {
            line_id = func_ovl2_800FADE4(ip->coll_data.lwall_line_id);
        }
        else
        {
            line_id = func_ovl2_800FAEA4(ip->coll_data.lwall_line_id);
        }
        if ((line_id == -1) || (line_id == -2))
        {
            if (func_ovl3_8016981C(item_gobj) != 1)
            {
                func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
                return TRUE;
            }
            return FALSE;
        }

        coll_type = func_ovl2_800FA8A4(line_id);

        if (ip->lr == WALL_UP)
        {
            if (coll_type == At_Type_Ground)
            {
                ip->coll_data.ground_line_id = line_id;
                ip->item_vars.thunder_jolt.coll_type = coll_type;
                ip->lr = LEFT;

                func_ovl2_800F4408(line_id, &DObjGetStruct(item_gobj)->translate);

                return func_ovl3_80169BF0(item_gobj);
            }
        }
        else if (coll_type == At_Type_Ground)
        {
            ip->coll_data.ground_line_id = line_id;
            ip->item_vars.thunder_jolt.coll_type = coll_type;
            ip->lr = RIGHT;

            func_ovl2_800F4428(line_id, &DObjGetStruct(item_gobj)->translate);

            return func_ovl3_80169BF0(item_gobj);
        }

        if (func_ovl3_8016981C(item_gobj) != 1)
        {
            func_ovl2_800FF648(&DObjGetStruct(item_gobj)->translate, 1.0F);
            return TRUE;
        }
        return FALSE;

    default:
        return FALSE;
    }
}

bool32 jtgt_ovl3_8016A374(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl2_800FE068(&DObjGetStruct(item_gobj)->translate, ip->item_hit.damage);

    return TRUE;
}

bool32 jtgt_ovl3_8016A3A4(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    ip->lifetime = ITPIKACHUJOLT_LIFETIME;

    func_ovl3_801680EC(ip, fp);

    DObjGetStruct(item_gobj)->rotate.y = (ip->phys_info.vel.x >= 0.0F) ? PI32 : 0;

    func_ovl3_80167F68(item_gobj);

    return FALSE;
}

extern ItemSpawnData Item_ThunderJoltGround_Desc;

GObj* func_ovl3_8016A42C(GObj *prev_gobj, Vec3f *pos, s32 coll_type)
{
    s32 unused[2];
    Item_Struct *prev_ip = prev_gobj->user_data;
    Item_Struct *new_ip;
    GObj *new_gobj = func_ovl3_801655C8(prev_gobj, &Item_ThunderJoltGround_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_ITEM));

    if (new_gobj == NULL)
    {
        return NULL;
    }
    new_ip = ItemGetStruct(new_gobj);

    new_ip->item_vars.thunder_jolt.coll_type = coll_type;

    new_ip->lifetime = prev_ip->lifetime;

    new_ip->coll_data.ground_line_id = prev_ip->coll_data.ground_line_id;
    new_ip->coll_data.rwall_line_id = prev_ip->coll_data.rwall_line_id;
    new_ip->coll_data.lwall_line_id = prev_ip->coll_data.lwall_line_id;

    func_8000BB4C(new_gobj, 0.5F);

    func_ovl3_80169D08(new_gobj);

    switch (new_ip->item_vars.thunder_jolt.coll_type)
    {
    case 0:
        new_ip->lr = (prev_ip->phys_info.vel.x >= 0.0F) ? RIGHT : LEFT;

        DObjGetStruct(new_gobj)->rotate.y = (new_ip->lr >= 0.0F) ? PI32 : 0;
        break;

    case 3:
        if (THREEQUART_PI32 < atan2f(new_ip->item_vars.thunder_jolt.rotate.y, new_ip->item_vars.thunder_jolt.rotate.x))
        {
            DObjGetStruct(new_gobj)->rotate.y = 0;
            new_ip->lr = WALL_DOWN;
        }
        else
        {
            DObjGetStruct(new_gobj)->rotate.y = PI32;
            new_ip->lr = WALL_UP;
        }
        break;

    case 2:
        if (QUART_PI32 < atan2f(new_ip->item_vars.thunder_jolt.rotate.y, new_ip->item_vars.thunder_jolt.rotate.x))
        {
            DObjGetStruct(new_gobj)->rotate.y = 0;
            new_ip->lr = WALL_UP;
        }
        else
        {
            DObjGetStruct(new_gobj)->rotate.y = PI32;
            new_ip->lr = WALL_DOWN;
        }
        break;
    }
    func_ovl2_80101C34(&DObjGetStruct(new_gobj)->translate, DObjGetStruct(new_gobj)->rotate.z);
    func_ovl3_80167F08(new_ip, 0xE6);

    return new_gobj;
}