#include "item.h"
#include "fighter.h"
#include "gmmatch.h"

extern intptr_t D_NF_00009430;
extern intptr_t D_NF_00009520;

void func_ovl3_8017C690(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    void *t = (void*) (((uintptr_t)ip->attributes->unk_0x0 - (intptr_t)&D_NF_00009430) + (intptr_t)&D_NF_00009520); // Linker thing

    func_8000BD54(joint->next->next->unk_0x8->mobj, t, 0.0F);
    func_8000DF34(item_gobj);
}

void func_ovl3_8017C6F8(GObj *item_gobj)
{
    DObj *joint = DObjGetStruct(item_gobj);

    joint->next->unk_0x8->mobj->unk_mobj_0x94 = 0;
}

bool32 jtgt_ovl3_8017C710(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    func_ovl3_80172558(ip, ATMBALL_GRAVITY, ATMBALL_T_VEL);
    func_ovl3_801713F4(item_gobj);

    joint->next->unk_0x8->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 func_ovl3_8017C768(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_8017C7FC);

    return FALSE;
}

bool32 jtgt_ovl3_8017C790(GObj *item_gobj)
{
    func_ovl3_80173B24(item_gobj, 0.2F, 0.2F, func_ovl3_8017C7C8);

    return FALSE;
}

extern itStatusDesc Article_M_Ball_Status[];

void func_ovl3_8017C7C8(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_M_Ball_Status, 0);
}

void func_ovl3_8017C7FC(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ip);
    itMain_SetItemStatus(item_gobj, Article_M_Ball_Status, 1);
}

void jtgt_ovl3_8017C840(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    DObjGetStruct(item_gobj)->rotate.y = 0.0F;

    ip->item_vars.m_ball.owner_gobj = ip->owner_gobj;

    itMain_SetItemStatus(item_gobj, Article_M_Ball_Status, 2);
}

bool32 jtgt_ovl3_8017C880(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    func_ovl3_80172558(ip, ATMBALL_GRAVITY, ATMBALL_T_VEL);
    func_ovl3_801713F4(item_gobj);

    joint->next->unk_0x8->rotate.z = joint->rotate.z;

    return FALSE;
}

bool32 jtgt_ovl3_8017C8D8(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->item_vars.m_ball.is_rebound != FALSE)
    {
        func_ovl3_80173C68(item_gobj, 0.2F, 0.2F, func_ovl3_8017CC88);
    }
    else
    {
        func_ovl3_80173B24(item_gobj, 0.2F, 0.2F, func_ovl3_8017CC88);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017C94C(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ip->item_vars.m_ball.is_rebound = TRUE;

    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_8017C97C(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    Fighter_Struct *fp;
    GObj *fighter_gobj;

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ip->item_vars.m_ball.is_rebound = TRUE;

    func_ovl3_80172FE0(item_gobj);

    fighter_gobj = ip->item_vars.m_ball.owner_gobj;
    ip->owner_gobj = fighter_gobj;
    fp = ftGetStruct(fighter_gobj);

    ip->team = fp->team;
    ip->port_id = fp->port_id;
    ip->player_number = fp->player_number;
    ip->handicap = fp->handicap;

    return FALSE;
}

void jtgt_ovl3_8017C9E0(GObj *item_gobj)
{
    func_ovl3_8017C690(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_M_Ball_Status, 3);
}

void jtgt_ovl3_8017CA14(GObj *item_gobj)
{
    func_ovl3_8017C690(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_M_Ball_Status, 4);
}

extern s32 D_ovl3_80189450;

bool32 jtgt_ovl3_8017CA48(GObj *m_ball_gobj)
{
    Item_Struct *m_ball_ip = itGetStruct(m_ball_gobj);
    Item_Struct *monster_ip;
    GObj *monster_gobj;
    Vec3f vel;
    s32 unused[2];

    if (m_ball_ip->it_multi == 0)
    {
        vel.z = 0.0F;
        vel.y = 0.0F;
        vel.x = 0.0F;

        if (D_ovl3_80189450 == 0)
        {
            func_ovl3_80173228(m_ball_gobj);

            return TRUE;
        }
        monster_gobj = func_ovl3_8016F238(m_ball_gobj, D_ovl3_80189450 + (It_Kind_MbMonsterStart - 1), &DObjGetStruct(m_ball_gobj)->translate, &vel, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_ITEM));

        if (monster_gobj != NULL)
        {
            monster_ip = itGetStruct(monster_gobj);

            monster_ip->owner_gobj = m_ball_ip->owner_gobj;
            monster_ip->team = m_ball_ip->team;
            monster_ip->port_id = m_ball_ip->port_id;
            monster_ip->handicap = m_ball_ip->handicap;
            monster_ip->player_number = m_ball_ip->player_number;
            monster_ip->display_state = m_ball_ip->display_state;
        }
        return TRUE;
    }
    m_ball_ip->it_multi--;

    if (m_ball_ip->item_vars.m_ball.effect_gobj != NULL)
    {
        DObjGetStruct(m_ball_ip->item_vars.m_ball.effect_gobj)->translate = DObjGetStruct(m_ball_gobj)->translate;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017CB38(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (func_ovl2_800FC67C(ip->attach_line_id) == FALSE)
    {
        ip->is_attach_surface = FALSE;

        func_ovl3_8017CDE4(item_gobj);
    }
    return FALSE;
}

void func_ovl3_8017CB84(GObj *item_gobj)
{
    s32 unused[2];
    DObj *joint = DObjGetStruct(item_gobj);
    Item_Struct *ip = itGetStruct(item_gobj);
    DObj *next;
    DObj *child;

    ip->phys_info.vel_air.x = 0.0F;
    ip->phys_info.vel_air.y = 0.0F;
    ip->phys_info.vel_air.z = 0.0F;

    next = joint->next;
    next->unk_0x54 ^= 2;

    child = joint->next->unk_0x8;
    child->unk_0x54 ^= 2;

    func_800269C0(0x8BU);

    ip->attach_line_id = ip->coll_data.ground_line_id;

    ip->is_attach_surface = TRUE;

    if ((ip->port_id != -1) && (ip->port_id != GMMATCH_PLAYERS_MAX))
    {
        GObj *fighter_gobj = Match_Info->player_block[ip->port_id].fighter_gobj;

        if (fighter_gobj != NULL)
        {
            Fighter_Struct *fp = ftGetStruct(fighter_gobj);

            func_ovl2_800E806C(fp, 8, 20);
        }
    }
    ip->item_vars.m_ball.effect_gobj = func_ovl2_80102C28(&joint->translate);

    func_ovl3_8017C6F8(item_gobj);

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;
    ip->item_hit.can_reflect = FALSE;
}

void func_ovl3_8017CC88(GObj *item_gobj)
{
    func_ovl3_8017CB84(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_M_Ball_Status, 5);
}

bool32 jtgt_ovl3_8017CCBC(GObj *m_ball_gobj)
{
    Item_Struct *m_ball_ip = itGetStruct(m_ball_gobj);
    Item_Struct *monster_ip;
    GObj *monster_gobj;
    Vec3f vel;
    s32 unused[2];

    if (m_ball_ip->it_multi == 0)
    {
        vel.z = 0.0F;
        vel.y = 0.0F;
        vel.x = 0.0F;

        if (D_ovl3_80189450 == 0)
        {
            func_ovl3_80173228(m_ball_gobj);

            return TRUE;
        }
        monster_gobj = func_ovl3_8016F238(m_ball_gobj, D_ovl3_80189450 + (It_Kind_MbMonsterStart - 1), &DObjGetStruct(m_ball_gobj)->translate, &vel, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_ITEM));

        if (monster_gobj != NULL)
        {
            monster_ip = itGetStruct(monster_gobj);

            monster_ip->owner_gobj = m_ball_ip->owner_gobj;
            monster_ip->team = m_ball_ip->team;
            monster_ip->port_id = m_ball_ip->port_id;
            monster_ip->handicap = m_ball_ip->handicap;
            monster_ip->player_number = m_ball_ip->player_number;
            monster_ip->display_state = m_ball_ip->display_state;
        }
        return TRUE;
    }
    m_ball_ip->it_multi--;

    if (m_ball_ip->item_vars.m_ball.effect_gobj != NULL)
    {
        DObjGetStruct(m_ball_ip->item_vars.m_ball.effect_gobj)->translate = DObjGetStruct(m_ball_gobj)->translate;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8017CDAC(GObj *item_gobj)
{
    func_ovl3_80173B24(item_gobj, 0.2F, 0.2F, func_ovl3_8017CC88);

    return FALSE;
}

void func_ovl3_8017CDE4(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_M_Ball_Status, 6);
}

extern itCreateDesc Article_M_Ball_Data;

GObj* jtgt_ovl3_8017CE0C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_M_Ball_Data, pos, vel, flags);

    if (item_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(item_gobj);
        Item_Struct *ip = itGetStruct(item_gobj);
        Vec3f translate = joint->translate;

        joint->next->unk_0x54 = 2;
        joint->next->unk_0x8->unk_0x54 = 0;

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint->next->unk_0x8, 0x46U, 0U);

        joint->translate = translate;

        ip->it_multi = ATMBALL_SPAWN_WAIT;

        ip->item_vars.m_ball.is_rebound = FALSE;

        ip->is_unused_item_bool = TRUE;

        joint->rotate.z = 0.0F;

        ip->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ip);
    }
    return item_gobj;
}