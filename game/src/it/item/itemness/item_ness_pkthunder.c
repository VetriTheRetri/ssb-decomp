#include "item.h"
#include "fighter.h"
#include "ftness.h"

#define QUART_PI32 0.7853982F
#define HALF_PI32 1.5707964F
#define PI32 3.1415927F

#define pktGetGObj(ip, i) \
((GObj*)ip->item_vars.pk_thunder.trail_gobj[i])

#define pktTrailGetGObj(ip, i) \
((GObj*)ip->item_vars.pk_thunder_trail.trail_gobj[i])

#define pktGetTrailPosIndex(fp) \
(ARRAY_COUNT(fp->fighter_vars.ness.pk_thunder_trail_x) | ARRAY_COUNT(fp->fighter_vars.ness.pk_thunder_trail_y))

void func_ovl3_8016AD30(GObj *item_gobj, bool32 is_destroy)
{
    GObj *gobj;
    Fighter_Struct *fp;
    Item_Struct *ip, *ip2, *ip3;
    s32 i;

    ip = ItemGetStruct(item_gobj);

    if (!(ip->item_vars.pk_thunder.pk_thunder_state & itNessThunderStatus_Destroy))
    {
        fp = FighterGetStruct(ip->owner_gobj);

        if (fp->player_number == ip->player_number)
        {
            fp->fighter_vars.ness.is_thunder_destroy |= is_destroy;
        }
    }

    fp = FighterGetStruct(ip->owner_gobj);

    for (i = 0; i < ARRAY_COUNT(ip->item_vars.pk_thunder.trail_gobj) - 1; i++)
    {
        if (pktGetGObj(ip, i) != NULL)
        {
            ip2 = ItemGetStruct(pktGetGObj(ip, i));
            ip2->item_vars.pk_thunder_trail.pk_thunder_trail_state = itNessThunderStatus_Destroy;
            ip->item_vars.pk_thunder.trail_gobj[i] = NULL;
        }
    }

    if (pktGetGObj(ip, ARRAY_COUNT(ip->item_vars.pk_thunder.trail_gobj) - 1) != NULL)
    {
        ip3 = ItemGetStruct(pktGetGObj(ip, ARRAY_COUNT(ip->item_vars.pk_thunder.trail_gobj) - 1));
        ip3->lr = RIGHT;
        ip->item_vars.pk_thunder.trail_gobj[ARRAY_COUNT(ip->item_vars.pk_thunder.trail_gobj) - 1] = NULL;
    }
}

void func_ovl3_8016ADF4(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    if (fp->player_number == ip->player_number)
    {
        s32 trail_pos_id = fp->fighter_vars.ness.pk_thunder_trail_id - 1;

        if (trail_pos_id < 0)
        {
            trail_pos_id += (ARRAY_COUNT(fp->fighter_vars.ness.pk_thunder_trail_x) | ARRAY_COUNT(fp->fighter_vars.ness.pk_thunder_trail_y));
        }

        fp->fighter_vars.ness.pk_thunder_trail_x[trail_pos_id] = JObjGetStruct(item_gobj)->translate.x;
        fp->fighter_vars.ness.pk_thunder_trail_y[trail_pos_id] = JObjGetStruct(item_gobj)->translate.y;
    }
}

void func_ovl3_8016AE64(GObj *item_gobj, s32 trail_index)
{
    JObj *jobj = JObjGetStruct(item_gobj);
    Vec3f pos;

    pos.x = JObjGetStruct(item_gobj)->translate.x;
    pos.y = JObjGetStruct(item_gobj)->translate.y;
    pos.z = 0.0F;

    func_ovl3_8016B580(item_gobj, &pos, trail_index);
}

bool32 jtgt_ovl3_8016AEA8(GObj *item_gobj) // PK Thunder physics callback?
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp;
    f32 angle_diff;
    Vec3f stick_angle;
    Vec3f thunder_angle;

    if (ip->item_vars.pk_thunder.pk_thunder_state & itNessThunderStatus_Destroy)
    {
        func_ovl2_800FE068(&JObjGetStruct(item_gobj)->translate, ip->item_hit[0].damage);
        func_ovl3_8016AD30(item_gobj, TRUE);
        return TRUE;
    }

    fp = FighterGetStruct(ip->owner_gobj);

    if (ip->item_vars.pk_thunder.pk_thunder_state & itNessThunderStatus_Collide)
    {
        func_ovl2_800FE068(&JObjGetStruct(item_gobj)->translate, ip->item_hit[0].damage);
        func_ovl3_8016AD30(item_gobj, TRUE);
        return TRUE;
    }

    if (ip->lifetime == (ITPKTHUNDER_LIFETIME - ITPKTHUNDER_SPAWN_TRAIL_TIMER))
    {
        func_ovl3_8016AE64(item_gobj, 0);
    }

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        func_ovl2_800FF648(&JObjGetStruct(item_gobj)->translate, 1.0F);
        func_ovl3_8016AD30(item_gobj, TRUE);
        return TRUE;
    }

    func_ovl3_8016ADF4(item_gobj);

    if ((fp->status_info.status_id == ftStatus_Ness_SpecialHiHold) || (fp->status_info.status_id == ftStatus_Ness_SpecialAirHiHold))
    {
        if ((ABS(fp->input.stick_range.x) + ABS(fp->input.stick_range.y)) > ITPKTHUNDER_TURN_STICK_THRESHOLD)
        {
            stick_angle.x = fp->input.stick_range.x;
            stick_angle.y = fp->input.stick_range.y;
            stick_angle.z = 0.0F;

            angle_diff = vec3f_angle_diff(&ip->phys_info.vel, &stick_angle);

            vec3f_normalized_cross_product(&ip->phys_info.vel, &stick_angle, &thunder_angle);

            if (QUART_PI32 <= angle_diff)
            {
                ip->item_vars.pk_thunder.angle = (thunder_angle.z > 0.0F) ? ip->item_vars.pk_thunder.angle + ITPKTHUNDER_ANGLE_STEP : ip->item_vars.pk_thunder.angle - ITPKTHUNDER_ANGLE_STEP;
            }
            if (angle_diff < QUART_PI32)
            {
                ip->item_vars.pk_thunder.angle = (thunder_angle.z > 0.0F) ? ip->item_vars.pk_thunder.angle + (angle_diff / ITPKTHUNDER_ANGLE_DIV) : ip->item_vars.pk_thunder.angle - (angle_diff / ITPKTHUNDER_ANGLE_DIV);
            }
            ip->phys_info.vel.x = cosf(ip->item_vars.pk_thunder.angle) * ITPKTHUNDER_VEL;
            ip->phys_info.vel.y = __sinf(ip->item_vars.pk_thunder.angle) * ITPKTHUNDER_VEL;
            ip->phys_info.vel.z = 0.0F;

            JObjGetStruct(item_gobj)->rotate.z = ip->item_vars.pk_thunder.angle - HALF_PI32;
        }
    }
    else
    {
        func_ovl2_800FF648(&JObjGetStruct(item_gobj)->translate, 1.0F);
        func_ovl3_8016AD30(item_gobj, TRUE);
        return TRUE;
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016B198(GObj *item_gobj)
{
    if (func_ovl3_80167C04(item_gobj) != FALSE)
    {
        func_ovl2_800FF648(&JObjGetStruct(item_gobj)->translate, 1.0F);
        func_ovl3_8016AD30(item_gobj, TRUE);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016B1E8(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl2_800FE068(&JObjGetStruct(item_gobj)->translate, ip->item_hit[0].damage);
    func_ovl3_8016AD30(item_gobj, TRUE);

    return TRUE;
}

bool32 jtgt_ovl3_8016B22C(GObj *item_gobj) // Behold, PK Thunder's dangerous reflect callback
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp;
    Vec3f pos = JObjGetStruct(item_gobj)->translate; // Get current position

    func_ovl3_8016B898(item_gobj, &pos, ip->item_vars.pk_thunder.angle); // Spawn whole new PK Thunder instance

    ip->owner_gobj = ip->item_vars.pk_thunder.spawn_gobj;

    fp = FighterGetStruct(ip->item_vars.pk_thunder.spawn_gobj);

    ip->player_number = fp->player_number;

    func_ovl3_8016AD30(item_gobj, TRUE); // Clear current PK Thunder instance's variables

    return TRUE; // Return TRUE so PK Thunder gets destroyed
}

bool32 func_ovl3_8016B2A0(GObj *item_gobj)
{
    func_ovl3_8016AD30(item_gobj, TRUE);

    return TRUE;
}

extern ItemStatusDesc Item_PKThunder_Desc;

GObj *func_ovl3_8016B2C4(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel) // Create PK Thunder 
{
    GObj *item_gobj = func_ovl3_801655C8(fighter_gobj, &Item_PKThunder_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_FIGHTER));
    Item_Struct *ip;
    s32 i;

    if (item_gobj == NULL) return NULL;

    ip = ItemGetStruct(item_gobj);

    ip->cb_destroy = func_ovl3_8016B2A0;

    ip->lifetime = ITPKTHUNDER_LIFETIME;

    ip->phys_info.vel = *vel;

    ip->item_vars.pk_thunder.pk_thunder_state = itNessThunderStatus_Active;
    ip->item_vars.pk_thunder.angle = HALF_PI32;
    ip->item_vars.pk_thunder.spawn_gobj = fighter_gobj;

    ip->is_camera_follow = TRUE;

    for (i = 0; i < ARRAY_COUNT(ip->item_vars.pk_thunder.trail_gobj); i++)
    {
        ip->item_vars.pk_thunder.trail_gobj[i] = NULL;
    }

    JObjGetStruct(item_gobj)->rotate.z = ip->item_vars.pk_thunder.angle - HALF_PI32; // Bruh this effectively makes it 0.0F due to its init a few lines above

    return item_gobj;
}

bool32 func_ovl3_8016B398(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    s32 index;
    Fighter_Struct *fp;

    if (ip->item_vars.pk_thunder_trail.pk_thunder_trail_state & itNessThunderStatus_Destroy) return TRUE;

    fp = FighterGetStruct(ip->owner_gobj);

    index = (fp->fighter_vars.ness.pk_thunder_trail_id - (ip->item_vars.pk_thunder_trail.trail_index * 2)) - 2;

    if (index < 0)
    {
        index += (ARRAY_COUNT(fp->fighter_vars.ness.pk_thunder_trail_x) | ARRAY_COUNT(fp->fighter_vars.ness.pk_thunder_trail_y));
    }

    JObjGetStruct(item_gobj)->translate.x = fp->fighter_vars.ness.pk_thunder_trail_x[index];
    JObjGetStruct(item_gobj)->translate.y = fp->fighter_vars.ness.pk_thunder_trail_y[index];

    if (index > 0)
    {
        JObjGetStruct(item_gobj)->rotate.z = atan2f((fp->fighter_vars.ness.pk_thunder_trail_y[index] - fp->fighter_vars.ness.pk_thunder_trail_y[index - 1]), (fp->fighter_vars.ness.pk_thunder_trail_x[index] - fp->fighter_vars.ness.pk_thunder_trail_x[index - 1]));
    }
    else
    {
        JObjGetStruct(item_gobj)->rotate.z = atan2f((fp->fighter_vars.ness.pk_thunder_trail_y[index] - fp->fighter_vars.ness.pk_thunder_trail_y[pktGetTrailPosIndex(fp) - 1]), (fp->fighter_vars.ness.pk_thunder_trail_x[index] - fp->fighter_vars.ness.pk_thunder_trail_x[pktGetTrailPosIndex(fp) - 1]));
    }

    JObjGetStruct(item_gobj)->rotate.z -= HALF_PI32;


    if ((ip->item_vars.pk_thunder_trail.trail_index < (ARRAY_COUNT(ip->item_vars.pk_thunder_trail.trail_gobj) - 2)) && (ip->lifetime == (ITPKTHUNDER_LIFETIME - ITPKTHUNDER_SPAWN_TRAIL_TIMER)))
    {
        func_ovl3_8016AE64(item_gobj, ip->item_vars.pk_thunder_trail.trail_index + 1);
    }

    if ((ip->item_vars.pk_thunder_trail.trail_index == (ARRAY_COUNT(ip->item_vars.pk_thunder_trail.trail_gobj) - 2)) && (ip->lifetime == (ITPKTHUNDER_LIFETIME - ITPKTHUNDER_SPAWN_TRAIL_TIMER)))
    {
        func_ovl2_80102848(ip->owner_gobj);
    }

    func_ovl3_80167FE8(ip);

    JObjGetStruct(item_gobj)->mobj->index = rand_u16_range(ITPKTHUNDER_TEXTURE_COUNT - 1);

    return FALSE;
}

bool32 jtgt_ovl3_8016B550(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl2_800FE068(&JObjGetStruct(item_gobj)->translate, ip->item_hit[0].damage);

    return FALSE;
}

extern ItemStatusDesc Item_PKThunderTrail_Desc;

GObj* func_ovl3_8016B580(GObj *head_gobj, Vec3f *pos, s32 trail_index)
{
    GObj *trail_gobj;
    Item_Struct *trail_ip;
    Item_Struct *head_ip = ItemGetStruct(head_gobj);
    s32 i;

    trail_gobj = func_ovl3_801655C8(head_gobj, &Item_PKThunderTrail_Desc, pos, ITEM_MASK_SPAWN_ITEM);

    if (trail_gobj == NULL)
    {
        return NULL;
    }

    trail_ip = ItemGetStruct(trail_gobj);

    trail_gobj->renderer = func_ovl3_80167660;

    trail_ip->lifetime = ITPKTHUNDER_LIFETIME;

    if (trail_index == 0)
    {
        trail_ip->group_id = func_ovl3_801655A0(head_gobj, trail_gobj); // Bruh this doesn't take arguments but it doesn't match otherwise
    }
    else trail_ip->group_id = head_ip->group_id;

    trail_ip->item_vars.pk_thunder_trail.pk_thunder_trail_state = itNessThunderStatus_Active;
    trail_ip->item_vars.pk_thunder_trail.trail_index = trail_index;
    trail_ip->item_vars.pk_thunder_trail.spawn_gobj = head_gobj;

    if (trail_index != 0)
    {
        head_gobj = head_ip->item_vars.pk_thunder.trail_gobj[0];
        head_ip = ItemGetStruct(head_gobj);
    }

    trail_ip->item_vars.pk_thunder_trail.trail_gobj[0] = head_gobj;

    for (i = 0; i < ARRAY_COUNT(head_ip->item_vars.pk_thunder.trail_gobj); i++)
    {
        head_ip->item_vars.pk_thunder.trail_gobj[trail_index] = trail_gobj;
    }

    return trail_gobj;
}

void func_ovl3_8016B65C(GObj *item_gobj, s32 trail_index)
{
    Vec3f pos;

    pos.x = JObjGetStruct(item_gobj)->translate.x;
    pos.y = JObjGetStruct(item_gobj)->translate.y;
    pos.z = 0.0F;

    func_ovl3_8016BB6C(item_gobj, &pos, trail_index);
}

void func_ovl3_8016B6A0(GObj *item_gobj, s32 unused)
{
    Item_Struct *ip, *ip2, *ip3;
    s32 i;

    ip = ItemGetStruct(item_gobj);

    for (i = 0; i < ARRAY_COUNT(ip->item_vars.pk_thunder_trail.trail_gobj) - 1; i++)
    {
        if (pktTrailGetGObj(ip, i) != NULL)
        {
            ip2 = ItemGetStruct(pktTrailGetGObj(ip, i));
            ip2->item_vars.pk_thunder_trail.pk_thunder_trail_state = itNessThunderStatus_Destroy;
            ip->item_vars.pk_thunder_trail.trail_gobj[i] = NULL;
        }
    }

    if (pktTrailGetGObj(ip, ARRAY_COUNT(ip->item_vars.pk_thunder_trail.trail_gobj) - 1) != NULL)
    {
        ip3 = ItemGetStruct(pktTrailGetGObj(ip, ARRAY_COUNT(ip->item_vars.pk_thunder_trail.trail_gobj) - 1));
        ip3->lr = RIGHT;
        ip->item_vars.pk_thunder_trail.trail_gobj[ARRAY_COUNT(ip->item_vars.pk_thunder_trail.trail_gobj) - 1] = NULL;
    }
}

bool32 jtgt_ovl3_8016B734(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    if (ip->lifetime == (ITPKTHUNDER_LIFETIME - ITPKTHUNDER_SPAWN_TRAIL_TIMER))
    {
        func_ovl3_8016B65C(item_gobj, 0);
    }

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        func_ovl2_800FF648(&JObjGetStruct(item_gobj)->translate, 1.0F);
        func_ovl3_8016B6A0(item_gobj, TRUE);

        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016B7AC(GObj *item_gobj)
{
    if (func_ovl3_80167C04(item_gobj) != FALSE)
    {
        func_ovl2_800FF648(&JObjGetStruct(item_gobj)->translate, 1.0F);
        func_ovl3_8016B6A0(item_gobj, TRUE);
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_8016B7FC(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl2_800FE068(&JObjGetStruct(item_gobj)->translate, ip->item_hit[0].damage);
    func_ovl3_8016B6A0(item_gobj, TRUE);

    return TRUE;
}

bool32 jtgt_ovl3_8016B840(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    ip->lifetime = ITPKTHUNDER_LIFETIME; // This line is directly responsible for the PK Thunder double reflect crash; omitting it fixes the oversight

    func_ovl3_801680EC(ip, fp);

    return FALSE;
}

bool32 func_ovl3_8016B874(GObj *item_gobj)
{
    func_ovl3_8016B6A0(item_gobj, TRUE);

    return TRUE;
}

extern ItemStatusDesc Item_PKThunderReflect_Desc;

GObj *func_ovl3_8016B898(GObj *old_gobj, Vec3f *pos, Vec3f *vel)
{
    s32 i;
    GObj *new_gobj;
    Item_Struct *ip;
    Vec3f localvel;
    f32 unk_vec;

    new_gobj = func_ovl3_801655C8(old_gobj, &Item_PKThunderReflect_Desc, pos, (ITEM_FLAG_PROJECT | ITEM_MASK_SPAWN_ITEM));

    if (new_gobj == NULL) return NULL;

    ip = ItemGetStruct(new_gobj);

    ip->cb_destroy = func_ovl3_8016B874;

    ip->lifetime = ITPKTHUNDER_LIFETIME;

    ip->group_id = func_ovl3_801655A0();

    for (i = 0; i < ARRAY_COUNT(ip->item_vars.pk_thunder.trail_gobj); i++)
    {
        ip->item_vars.pk_thunder.trail_gobj[i] = NULL;
    }

    localvel.x = JObjGetStruct(new_gobj)->translate.x - JObjGetStruct(ip->owner_gobj)->translate.x;
    localvel.y = JObjGetStruct(new_gobj)->translate.y - (JObjGetStruct(ip->owner_gobj)->translate.y + ITPKTHUNDER_REFLECT_POS_Y_ADD);
    localvel.z = JObjGetStruct(new_gobj)->translate.z - JObjGetStruct(ip->owner_gobj)->translate.z;

    vec3f_normalize(&localvel);

    ip->phys_info.vel.x = (ITPKTHUNDER_VEL * localvel.x);
    ip->phys_info.vel.y = (ITPKTHUNDER_VEL * localvel.y);
    ip->phys_info.vel.z = 0.0F;

    JObjGetStruct(new_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);

    return new_gobj;
}

bool32 func_ovl3_8016B9E0(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    s32 trail_index;

    if (ip->item_vars.pk_thunder_trail.pk_thunder_trail_state & itNessThunderStatus_Destroy)
    {
        return TRUE;
    }

    // Game hangs on the following line when PK Thunder crash occurs (JObjGetStruct returns invalid pointer)

    JObjGetStruct(item_gobj)->translate.x = (JObjGetStruct(ip->item_vars.pk_thunder_trail.trail_gobj[0])->translate.x - (ip->phys_info.vel.x * (ip->item_vars.pk_thunder_trail.trail_index + 1.5) * 2.0F));
    JObjGetStruct(item_gobj)->translate.y = (JObjGetStruct(ip->item_vars.pk_thunder_trail.trail_gobj[0])->translate.y - (ip->phys_info.vel.y * (ip->item_vars.pk_thunder_trail.trail_index + 1.5) * 2.0F));

    trail_index = ip->item_vars.pk_thunder_trail.trail_index;

    if ((trail_index < (ARRAY_COUNT(ip->item_vars.pk_thunder_trail.trail_gobj) - 2)) && (ip->lifetime == (ITPKTHUNDER_LIFETIME - ITPKTHUNDER_SPAWN_TRAIL_TIMER)))
    {
        func_ovl3_8016B65C(item_gobj, trail_index + 1);

        trail_index = ip->item_vars.pk_thunder_trail.trail_index;
    }

    if ((trail_index == (ARRAY_COUNT(ip->item_vars.pk_thunder_trail.trail_gobj) - 2)) && (ip->lifetime == (ITPKTHUNDER_LIFETIME - ITPKTHUNDER_SPAWN_TRAIL_TIMER)))
    {
        func_ovl2_80102968(ip->item_vars.pk_thunder_trail.trail_gobj[0]);
    }

    func_ovl3_80167FE8(ip);

    JObjGetStruct(item_gobj)->mobj->index = rand_u16_range(ITPKTHUNDER_TEXTURE_COUNT - 1);

    return FALSE;
}

bool32 jtgt_ovl3_8016BB3C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl2_800FE068(&JObjGetStruct(item_gobj)->translate, ip->item_hit[0].damage);

    return FALSE;
}

extern ItemStatusDesc Item_PKThunderTrailReflect_Desc;

GObj* func_ovl3_8016BB6C(GObj *old_gobj, Vec3f *pos, s32 trail_index)
{
    GObj *new_gobj;
    s32 unused;
    Item_Struct *old_ip, *new_ip;

    old_ip = ItemGetStruct(old_gobj);

    new_gobj = func_ovl3_801655C8(old_gobj, &Item_PKThunderTrailReflect_Desc, pos, ITEM_MASK_SPAWN_ITEM);

    if (new_gobj == NULL) return NULL;

    new_ip = ItemGetStruct(new_gobj);

    new_gobj->renderer = func_ovl3_80167660;

    new_ip->lifetime = ITPKTHUNDER_LIFETIME;

    new_ip->group_id = old_ip->group_id;

    new_ip->item_vars.pk_thunder_trail.pk_thunder_trail_state = itNessThunderStatus_Active;
    new_ip->item_vars.pk_thunder_trail.trail_index = trail_index;
    new_ip->item_vars.pk_thunder_trail.spawn_gobj = old_gobj;

    if (trail_index != 0)
    {
        old_gobj = old_ip->item_vars.pk_thunder_trail.trail_gobj[0];
        old_ip = ItemGetStruct(old_gobj);
    }

    new_ip->item_vars.pk_thunder_trail.trail_gobj[0] = old_gobj;

    old_ip->item_vars.pk_thunder_trail.trail_gobj[trail_index] = new_gobj;

    new_ip->phys_info.vel.x = old_ip->phys_info.vel.x;
    new_ip->phys_info.vel.y = old_ip->phys_info.vel.y;

    JObjGetStruct(new_gobj)->rotate.z = JObjGetStruct(old_gobj)->rotate.z - HALF_PI32;

    func_ovl3_80165F60(new_gobj);

    return new_gobj;
}