#include "item.h"
#include "fighter.h"

extern intptr_t Article_Link_Bomb_Scale;
extern itCreateDesc Article_Link_Bomb_Data;

// 0x801859C0;
void func_ovl3_801859C0(GObj *item_gobj)
{
    DObj *joint = DObjGetStruct(item_gobj);
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->item_vars.link_bomb.scale_int == 0)
    {
        f32 *p_scale = (f32*) ((uintptr_t)*Article_Link_Bomb_Data.p_file + (intptr_t)&Article_Link_Bomb_Scale); // Linker thing

        s32 index = (ip->item_vars.link_bomb.scale_index >= ITLINKBOMB_SCALE_INDEX_REWIND) ? ITLINKBOMB_SCALE_INDEX_MAX - ip->item_vars.link_bomb.scale_index : ip->item_vars.link_bomb.scale_index;

        if (ip->is_hold)
        {
            joint->next->scale.x = joint->next->scale.y = p_scale[index];
        }
        else
        {
            joint->scale.x = joint->scale.y = p_scale[index];
        }
        ip->item_vars.link_bomb.scale_int = ITLINKBOMB_SCALE_INT;

        if (ip->item_vars.link_bomb.scale_index >= ITLINKBOMB_SCALE_INDEX_MAX)
        {
            ip->item_vars.link_bomb.scale_index = 0;
        }
        else ip->item_vars.link_bomb.scale_index += 1; // Doesn't match with "++" lol
    }
    ip->item_vars.link_bomb.scale_int--;
}

void func_ovl3_80185A80(GObj *item_gobj)
{
    s32 unused;
    DObj *joint = DObjGetStruct(item_gobj);
    Item_Struct *ip = itGetStruct(item_gobj);
    Effect_Unk *ep;

    itLinkBomb_SDefault_SetHitStatusNone(item_gobj);

    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ITLINKBOMB_EXPLODE_GFX_SCALE;
        ep->effect_info->scale.y = ITLINKBOMB_EXPLODE_GFX_SCALE;
        ep->effect_info->scale.z = ITLINKBOMB_EXPLODE_GFX_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(item_gobj)->unk_0x54 = 2;

    ip->item_hit.hit_sfx = 1;

    itMain_RefreshHit(item_gobj);
    func_ovl3_8018656C(item_gobj);
}

void func_ovl3_80185B18(GObj *item_gobj)
{
    s32 unused[5];
    Item_Struct *ip = itGetStruct(item_gobj);
    itCommonAttributes *attributes = ip->attributes;
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f pos = joint->translate;

    pos.y += attributes->objectcoll_bottom;

    func_ovl2_800FF3F4(&pos, ip->lr, 1.0F);
}

bool32 func_ovl3_80185B84(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->damage_taken_recent >= ITLINKBOMB_HEALTH)
    {
        func_ovl3_80186368(item_gobj);
    }
    else
    {
        ip->lr = -ip->lr_damage;

        ip->phys_info.vel_air.x = -ip->lr_damage * ITLINKBOMB_DAMAGE_RECOIL_VEL_X;
        ip->phys_info.vel_air.y = -ip->lr_damage * ITLINKBOMB_DAMAGE_RECOIL_VEL_Y;
    }
    return FALSE;
}

bool32 func_ovl3_80185BFC(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if ((ABSF(ip->phys_info.vel_air.x) > ITLINKBOMB_EXPLODE_THRESHOLD_VEL_X) || (ABSF(ip->phys_info.vel_air.y) > ITLINKBOMB_EXPLODE_THRESHOLD_VEL_Y))
    {
        func_ovl3_80186368(item_gobj);
    }
    else
    {
        ip->lr = -ip->lr_attack;

        ip->phys_info.vel_air.x = -ip->lr_attack * ITLINKBOMB_HIT_RECOIL_VEL_X;
        ip->phys_info.vel_air.y = ITLINKBOMB_HIT_RECOIL_VEL_Y;

        itLinkBomb_AFall_SetStatus(item_gobj);
    }
    return FALSE;
}

// 0x80185CD4
void itLinkBomb_SDefault_SetHitStatusNormal(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
}

// 0x80185CE4
void itLinkBomb_SDefault_SetHitStatusNone(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_None;
}

// 0x80185CF0
bool32 itLinkBomb_SDefault_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    itMain_UpdatePhysicsAir(ip, ITLINKBOMB_GRAVITY, ITLINKBOMB_T_VEL);

    if (ip->lifetime == 0)
    {
        func_ovl3_80186368(item_gobj);
    }
    if (ip->lifetime == ITLINKBOMB_BLOAT_BEGIN)
    {
        itMain_CheckSetColAnimIndex(item_gobj, ITLINKBOMB_BLOAT_COLANIM_ID, ITLINKBOMB_BLOAT_COLANIM_LENGTH);

        ip->item_vars.link_bomb.scale_index = 1;
    }
    if (ip->lifetime < ITLINKBOMB_BLOAT_BEGIN)
    {
        func_ovl3_801859C0(item_gobj);
    }
    ip->lifetime--;

    itManager_UpdateSpin(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80185DCC(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->phys_info.vel_air.x != 0.0F)
    {
        ip->phys_info.vel_air.x += (-1.0F) * ip->lr;
    }
    if (ABSF(ip->phys_info.vel_air.x) < 1.0F)
    {
        ip->phys_info.vel_air.x = 0;
    }
    if (ip->lifetime == 0)
    {
        func_ovl3_80186368(item_gobj);
    }
    if (ip->lifetime == ITLINKBOMB_BLOAT_BEGIN)
    {
        itMain_CheckSetColAnimIndex(item_gobj, ITLINKBOMB_BLOAT_COLANIM_ID, ITLINKBOMB_BLOAT_COLANIM_LENGTH);

        ip->item_vars.link_bomb.scale_index = 1;
    }
    if (ip->lifetime < ITLINKBOMB_BLOAT_BEGIN)
    {
        func_ovl3_801859C0(item_gobj);
    }
    ip->lifetime--;

    return FALSE;
}

bool32 jtgt_ovl3_80185F10(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, itLinkBomb_AFall_SetStatus);

    return FALSE;
}

bool32 jtgt_ovl3_80185F38(GObj *item_gobj)
{
    itMap_CheckMapCollideThrownLanding(item_gobj, 0.4F, 0.3F, itLinkBomb_GWait_SetStatus);

    return FALSE;
}

extern itStatusDesc Article_Link_Bomb_Status[];

// 0x80185F70
void itLinkBomb_GWait_SetStatus(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ip->is_allow_pickup = TRUE;

    ip->times_landed = 0;

    ip->phys_info.vel_air.x = ip->phys_info.vel_air.y = ip->phys_info.vel_air.z = 0.0F;

    itMap_SetGround(ip);
    itLinkBomb_SDefault_SetHitStatusNormal(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 0);
}

// 0x80185FD8
void itLinkBomb_AFall_SetStatus(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    itMap_SetAir(ip);
    itLinkBomb_SDefault_SetHitStatusNormal(item_gobj);
    itMain_SetItemStatus(item_gobj, &Article_Link_Bomb_Status, 1);
}

// 0x80186024
bool32 itLinkBomb_AFall_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    if (fp->status_info.status_id == ftStatus_Common_DokanWait) // Odd but go off
    {
        return FALSE;
    }
    else
    {
        if (ip->lifetime == 0)
        {
            itMain_SetFighterRelease(item_gobj, &ip->phys_info.vel, 1.0F);  // Ok, WHAT? This function takes 5 arguments, but it doesn't match otherwise???
                                                                            // Did they actually redefine this? Passes pointer in a3 instead of u16...
                                                                            // Do we leave this out of the header and declare it separately to match?
                                                                            // Update 3/23/2023: matches as variadic. No comment.
                                                                            // Update  7/2/2023: variadic match confirmed fake, so does this file use an erroneous decleration?
            itMain_ClearOwnerStats(item_gobj);
            func_ovl3_80186368(item_gobj);
        }
        if (ip->lifetime == ITLINKBOMB_BLOAT_BEGIN)
        {
            itMain_CheckSetColAnimIndex(item_gobj, ITLINKBOMB_BLOAT_COLANIM_ID, ITLINKBOMB_BLOAT_COLANIM_LENGTH);

            ip->item_vars.link_bomb.scale_index = 1;
        }
        if (ip->lifetime < ITLINKBOMB_BLOAT_BEGIN)
        {
            func_ovl3_801859C0(item_gobj);
        }
        ip->lifetime--;

        return FALSE;
    }
}

// 0x8018611C
void itLinkBomb_FHold_SetStatus(GObj *item_gobj)
{
    itLinkBomb_SDefault_SetHitStatusNone(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 2);
}

bool32 jtgt_ovl3_80186150(GObj *item_gobj)
{
    s32 unused;
    Item_Struct *ip = itGetStruct(item_gobj);
    Vec3f vel = ip->phys_info.vel;

    if (itMap_CheckMapCollideAny(item_gobj, 0.4F, 0.3F, itLinkBomb_AFall_SetStatus) != FALSE)
    {
        if ((ABSF(vel.x) > ITLINKBOMB_EXPLODE_THRESHOLD_VEL_X) || (ABSF(vel.y) > ITLINKBOMB_EXPLODE_THRESHOLD_VEL_Y))
        {
            func_ovl3_80186368(item_gobj);
        }
    }
    return FALSE;
}

void jtgt_ovl3_80186224(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    itLinkBomb_SDefault_SetHitStatusNormal(item_gobj);

    ip->is_damage_all = TRUE;

    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 3);
}

bool32 jtgt_ovl3_80186270(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->item_vars.link_bomb.unk_0x2 != 0)
    {
        ip->item_vars.link_bomb.unk_0x2--;
    }
    else itLinkBomb_SDefault_ProcUpdate(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801862AC(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->item_vars.link_bomb.unk_0x2 == 0)
    {
        func_ovl3_80185BFC(item_gobj);
    }
    return FALSE;
}

bool32 jtgt_ovl3_801862E0(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->item_vars.link_bomb.unk_0x2 == 0)
    {
        func_ovl3_80185B84(item_gobj);
    }
    return FALSE;
}

void jtgt_ovl3_80186314(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    itLinkBomb_SDefault_SetHitStatusNormal(item_gobj);

    ip->item_vars.link_bomb.unk_0x2 = 10;

    ip->is_damage_all = TRUE;

    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 4);
}

void func_ovl3_80186368(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->phys_info.vel_air.x = ip->phys_info.vel_air.y = ip->phys_info.vel_air.z = 0.0F;

    itMain_ClearOwnerStats(item_gobj);
    func_ovl3_80185A80(item_gobj);
    func_800269C0(1);
}

extern intptr_t Link_Bomb_Event;

void func_ovl3_801863AC(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    itHitEvent *ev = (itHitEvent*) ((uintptr_t)*Article_Link_Bomb_Data.p_file + (intptr_t)&Link_Bomb_Event); // Linker thing

    if (ip->it_multi == ev[ip->item_event_index].timer)
    {
        ip->item_hit.angle = ev[ip->item_event_index].angle;
        ip->item_hit.damage = ev[ip->item_event_index].damage;
        ip->item_hit.size = ev[ip->item_event_index].size;

        ip->item_hit.can_rehit_item = TRUE;
        ip->item_hit.can_hop = FALSE;
        ip->item_hit.can_reflect = FALSE;
        ip->item_hit.rebound = FALSE;

        ip->item_hit.element = gmHitCollision_Element_Fire;

        ip->item_event_index++;

        if (ip->item_event_index == 4)
        {
            ip->item_event_index = 3;
        }
    }
}

bool32 jtgt_ovl3_80186498(GObj *item_gobj)
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

bool32 func_ovl3_801864BC(GObj *item_gobj) // Unused
{
    func_ovl3_80185B18(item_gobj);
    func_ovl3_80186368(item_gobj);

    return FALSE;
}

void func_ovl3_801864E8(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->it_multi = 0;
    ip->item_event_index = 0;

    ip->item_hit.stale = ITEM_STALE_DEFAULT;

    func_ovl3_801863AC(item_gobj);
}

bool32 jtgt_ovl3_80186524(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_801863AC(item_gobj);

    ip->it_multi++;

    if (ip->it_multi == ITLINKBOMB_EXPLODE_LIFETIME)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8018656C(GObj *item_gobj)
{
    func_ovl3_801864E8(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 5);
}

GObj* func_ovl3_801865A0(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *item_gobj = itManager_CreateItem(fighter_gobj, &Article_Link_Bomb_Data, pos, vel, 0);
    DObj *joint;
    Item_Struct *ip;

    if (item_gobj != NULL)
    {
        ip = itGetStruct(item_gobj);
        joint = DObjGetStruct(item_gobj);

        func_80008CC0(joint, 0x2EU, 0U);
        func_80008CC0(joint->next, 0x2EU, 0U);

        ip->it_multi = 0;

        ip->lifetime = ITLINKBOMB_LIFETIME;

        ip->item_vars.link_bomb.scale_index = 0;
        ip->item_vars.link_bomb.scale_int = ITLINKBOMB_SCALE_INT;

        ip->item_hit.can_rehit_shield = TRUE;

        ip->phys_info.vel_air.x = ip->phys_info.vel_air.y = ip->phys_info.vel_air.z = 0.0F;

        itMain_SetFighterPickup(item_gobj, fighter_gobj);
    }
    return item_gobj;
}