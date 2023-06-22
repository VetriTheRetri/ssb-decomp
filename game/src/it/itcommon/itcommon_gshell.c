#include "item.h"

void func_ovl3_801785E0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f pos;

    if (ap->item_vars.shell.dust_gfx_int == 0)
    {
        pos = joint->translate;

        pos.y += ap->attributes->objectcoll_bottom;

        func_ovl2_800FF048(&pos, ap->lr, 1.0F);

        ap->item_vars.shell.dust_gfx_int = ATGSHELL_GFX_SPAWN_INT;
    }
    ap->item_vars.shell.dust_gfx_int--;
}

extern intptr_t D_NF_00005F88;
extern intptr_t D_NF_00006018;
extern intptr_t D_NF_00006048;

void func_ovl3_80178670(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    s32 unused[2];

    func_8000BD1C(joint, ArticleGetPData(ap, D_NF_00005F88, D_NF_00006018), 0.0F); // Linker thing
    func_8000BD54(joint->mobj, ArticleGetPData(ap, D_NF_00005F88, D_NF_00006048), 0.0F); // Linker thing
    func_8000DF34(item_gobj);
}

void func_ovl3_80178704(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->mobj->unk_mobj_0x94 = 0;
    DObjGetStruct(item_gobj)->unk_dobj_0x70 = 0;
}

bool32 jtgt_ovl3_8017871C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATGSHELL_GRAVITY, ATGSHELL_T_VEL);

    return FALSE;
}

bool32 func_ovl3_8017874C(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80178930);

    return FALSE;
}

bool32 jtgt_ovl3_80178774(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->item_vars.shell.health == FALSE)
    {
        return func_ovl3_80173DF4(item_gobj, 0.2F);
    }
    else func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, func_ovl3_80178910);

    return FALSE;
}

extern itStatusDesc Article_G_Shell_Status[];

void func_ovl3_801787CC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80173F54(ap);

    if (ABSF(ap->phys_info.vel.x) < ATGSHELL_STOP_VEL_X)
    {
        func_ovl3_80172E74(item_gobj);

        ap->item_vars.shell.is_damage = FALSE;

        ap->is_damage_all = TRUE;

        ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

        ap->phys_info.vel.x = 0.0F;

        func_ovl3_80178704(item_gobj);
        itMain_SetItemStatus(item_gobj, Article_G_Shell_Status, 0);
    }
    else if (ap->item_vars.shell.is_damage != FALSE)
    {
        ap->item_hit.update_state = gmHitCollision_UpdateState_New;

        itManager_UpdateHitPositions(item_gobj);
        func_ovl3_80178EDC(item_gobj);
    }
    else
    {
        func_ovl3_80172E74(item_gobj);

        ap->is_damage_all = TRUE;

        ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
        ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

        ap->phys_info.vel.x = 0.0F;

        func_ovl3_80178704(item_gobj);
        itMain_SetItemStatus(item_gobj, Article_G_Shell_Status, 0);
    }
}

void func_ovl3_80178910(GObj *item_gobj)
{
    func_ovl3_801787CC(item_gobj);
}

void func_ovl3_80178930(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    itMain_SetItemStatus(item_gobj, Article_G_Shell_Status, 1);
}

bool32 jtgt_ovl3_8017897C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->phys_info.vel.x = ap->damage_taken_recent * ATGSHELL_DAMAGE_MUL_NORMAL * (-ap->lr_damage);

    if (ABSF(ap->phys_info.vel.x) > ATGSHELL_STOP_VEL_X)
    {
        ap->item_vars.shell.is_damage = TRUE;

        ap->item_hit.update_state = gmHitCollision_UpdateState_New;

        itManager_UpdateHitPositions(item_gobj);

        ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

        func_ovl3_801727BC(item_gobj);

        if (ap->ground_or_air != ground)
        {
            func_ovl3_80178FA8(item_gobj);
        }
        else func_ovl3_80178EDC(item_gobj);

    }
    else
    {
        ap->phys_info.vel.x = 0.0F;

        if (ap->ground_or_air != ground)
        {
            func_ovl3_80178930(item_gobj);
        }
        else func_ovl3_80178910(item_gobj);
    }
    return FALSE;
}

void jtgt_ovl3_80178A90(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->rotate.y = 0.0F;

    itMain_SetItemStatus(item_gobj, Article_G_Shell_Status, 2);
}

bool32 jtgt_ovl3_80178AC4(GObj *item_gobj)
{
    func_ovl3_80173C68(item_gobj, 0.2F, 0.5F, func_ovl3_80178910);

    return FALSE;
}

bool32 jtgt_ovl3_80178AF8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATGSHELL_GRAVITY, ATGSHELL_T_VEL);

    return FALSE;
}

void jtgt_ovl3_80178B28(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_vars.shell.health = TRUE;
    ap->item_vars.shell.is_damage = TRUE;

    itMain_SetItemStatus(item_gobj, Article_G_Shell_Status, 3);
}

void jtgt_ovl3_80178B60(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_vars.shell.health = TRUE;
    ap->item_vars.shell.is_damage = TRUE;

    itMain_SetItemStatus(item_gobj, Article_G_Shell_Status, 4);
}

bool32 jtgt_ovl3_80178B98(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_801785E0(item_gobj);

    if (!(ap->item_vars.shell.damage_all_delay))
    {
        ap->is_damage_all = TRUE;

        ap->item_vars.shell.damage_all_delay = -1;
    }

    if (ap->item_vars.shell.damage_all_delay != -1)
    {
        ap->item_vars.shell.damage_all_delay--;
    }

    if (ap->lifetime == 0)
    {
        return TRUE;
    }
    else ap->lifetime--;

    return FALSE;
}

bool32 jtgt_ovl3_80178C10(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80178930);

    if (itMap_CheckCollideAllModifiyVel(item_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL), 0.2F, NULL) != FALSE)
    {
        func_ovl3_80172508(item_gobj);
        func_ovl3_8017279C(item_gobj);
    }
    return FALSE;
}

bool32 jtgt_ovl3_80178C6C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    ap->item_vars.shell.health = rand_u16_range(ATGSHELL_HEALTH_MAX);

    ap->phys_info.vel.y = ATGSHELL_REBOUND_VEL_Y;

    ap->phys_info.vel.x = rand_f32() * (-ap->phys_info.vel.x * ATGSHELL_REBOUND_MUL_X);

    func_ovl3_8017279C(item_gobj);
    func_ovl3_80178704(item_gobj);
    func_ovl3_80178930(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80178CF8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->phys_info.vel.x += (ap->damage_taken_recent * ATGSHELL_DAMAGE_MUL_ADD * (-ap->lr_damage));

    if (ABSF(ap->phys_info.vel.x) > ATGSHELL_STOP_VEL_X)
    {
        ap->item_hit.update_state = gmHitCollision_UpdateState_New;

        itManager_UpdateHitPositions(item_gobj);
        func_ovl3_801727BC(item_gobj);

        if (ap->ground_or_air != FALSE)
        {
            func_ovl3_80178FA8(item_gobj);
        }
        else func_ovl3_80178EDC(item_gobj);
    }
    else
    {
        ap->phys_info.vel.x = 0.0F;

        if (ap->ground_or_air != ground)
        {
            func_ovl3_80178930(item_gobj);
        }
        else func_ovl3_80178910(item_gobj);
    }
    return FALSE;
}

void func_ovl3_80178E04(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    ap->pickup_wait = ARTICLE_PICKUP_WAIT_DEFAULT;

    if (ap->phys_info.vel.x > ATGSHELL_CLAMP_VEL_X)
    {
        ap->phys_info.vel.x = ATGSHELL_CLAMP_VEL_X;
    }
    if (ap->phys_info.vel.x < -ATGSHELL_CLAMP_VEL_X)
    {
        ap->phys_info.vel.x = -ATGSHELL_CLAMP_VEL_X;
    }
    ap->phys_info.vel.y = 0.0F;

    if (ap->phys_info.vel.x < 0.0F)
    {
        ap->lr = LEFT;
    }
    else ap->lr = RIGHT;

    ap->item_vars.shell.dust_gfx_int = ATGSHELL_GFX_SPAWN_INT;
    ap->item_vars.shell.damage_all_delay = ATGSHELL_DAMAGE_ALL_WAIT;

    func_ovl3_80178670(item_gobj);

    ap->is_damage_all = FALSE;

    func_ovl3_8017275C(item_gobj);
    func_800269C0(0x37U);
}

void func_ovl3_80178EDC(GObj *item_gobj)
{
    func_ovl3_80178E04(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_G_Shell_Status, 5);
}

void func_ovl3_80178F10(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->phys_info.vel.x > ATGSHELL_CLAMP_VEL_X)
    {
        ap->phys_info.vel.x = ATGSHELL_CLAMP_VEL_X;
    }
    if (ap->phys_info.vel.x < -ATGSHELL_CLAMP_VEL_X)
    {
        ap->phys_info.vel.x = -ATGSHELL_CLAMP_VEL_X;
    }
    if (ap->phys_info.vel.x < 0.0F)
    {
        ap->lr = LEFT;
    }
    else ap->lr = RIGHT;

    ap->is_damage_all = FALSE;

    func_ovl3_8017275C(item_gobj);
}

void func_ovl3_80178FA8(GObj *item_gobj)
{
    func_ovl3_80178F10(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_G_Shell_Status, 6);
}

extern itCreateDesc Article_G_Shell_Data;

GObj* jtgt_ovl3_80178FDC(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_G_Shell_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(item_gobj);
        Item_Struct *ap;
        Vec3f translate = joint->translate;

        joint->rotate.y = HALF_PI32;

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = translate;

        joint->mobj->anim_frame = 1.0F;

        ap = itGetStruct(item_gobj);

        ap->item_hit.can_rehit_shield = TRUE;

        ap->item_vars.shell.health = 1;
        ap->item_vars.shell.is_damage = FALSE;

        ap->x2D3_flag_b5 = TRUE;

        ap->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ap);

        ap->lifetime = ATGSHELL_LIFETIME;
    }
    return item_gobj;
}

bool32 jtgt_ovl3_801790F4(GObj *item_gobj)
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}