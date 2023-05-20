#include "item.h"
#include "fighter.h"



void func_ovl3_80167EB0(Item_Struct *ip) // Stop item's ongoing SFX
{
    if (ip->p_sfx != NULL)
    {
        if ((ip->p_sfx->sfx_id != 0) && (ip->p_sfx->sfx_id == ip->sfx_id))
        {
            func_80026738(ip->p_sfx);
        }
    }
    ip->p_sfx = NULL;
    ip->sfx_id = 0U;
}

void func_ovl3_80167F08(Item_Struct *ip, u16 sfx_id) // Play OnDestroy SFX if applicable
{
    if (ip->p_sfx != NULL)
    {
        func_ovl3_80167EB0(ip);
    }

    ip->p_sfx = func_800269C0(sfx_id);

    if (ip->p_sfx != NULL)
    {
        ip->sfx_id = ip->p_sfx->sfx_id;
    }
    else ip->sfx_id = 0;
}

void func_ovl3_80167F68(GObj *item_gobj) // Set item's facing direction based on velocity
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    ip->lr = (ip->phys_info.vel.x >= 0.0F) ? RIGHT : LEFT;
}

void func_ovl3_80167FA0(GObj *item_gobj) // Set yaw rotation based on velocity
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    DObjGetStruct(item_gobj)->rotate.y = (ip->phys_info.vel.x >= 0.0F) ? HALF_PI32 : -HALF_PI32;
}

bool32 func_ovl3_80167FE8(Item_Struct *ip) // Decrement lifetime and check whether item has expired
{
    ip->lifetime--;

    if (ip->lifetime == 0)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8016800C(GObj *item_gobj) // Destroy item?
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl3_80167EB0(ip);     // Stop item's SFX
    func_ovl3_80165588(ip);     // Eject item's user_data from memory?
    func_80009A84(item_gobj);   // Eject GObj from memory?
}

void func_ovl3_80168044(GObj *item_gobj) // Transfer item's base ground velocity to aerial velocity
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    ip->phys_info.vel.x = ip->lr * ip->coll_data.ground_angle.y * ip->phys_info.vel_ground;
    ip->phys_info.vel.y = ip->lr * -ip->coll_data.ground_angle.x * ip->phys_info.vel_ground;
}

void func_ovl3_80168088(Item_Struct *ip, f32 gravity, f32 terminal_velocity) // Subtract vertical velocity every frame and clamp to terminal velocity
{
    ip->phys_info.vel.y -= gravity;

    if (terminal_velocity < func_ovl0_800C7A84(&ip->phys_info.vel))
    {
        func_ovl0_800C7A00(&ip->phys_info.vel);
        func_ovl0_800C7AE0(&ip->phys_info.vel, terminal_velocity);
    }
}

void func_ovl3_801680EC(Item_Struct *ip, Fighter_Struct *fp) // Invert direction on reflect
{
    if ((ip->phys_info.vel.x * fp->lr) < 0.0F)
    {
        ip->phys_info.vel.x = -ip->phys_info.vel.x;
    }
}

s32 func_ovl3_80168128(Item_Struct *ip) // Return final damage after applying staling and bonus 0.999%
{
    return (ip->item_hit.stale * ip->item_hit.damage) + 0.999F;
}

void func_ovl3_80168158(Item_Struct *ip) // Clear hit victims array
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(ip->item_hit.hit_targets); i++)
    {
        ItemHitArray *targets = &ip->item_hit.hit_targets[i];

        targets->victim_gobj = NULL;

        targets->victim_flags.is_interact_hurt = targets->victim_flags.is_interact_shield = targets->victim_flags.is_interact_reflect = targets->victim_flags.is_interact_absorb = FALSE;

        targets->victim_flags.timer_rehit = 0;

        targets->victim_flags.interact_mask = GMHITCOLLISION_MASK_ALL;
    }
}

// Missing an unused function at 0x8016830C, some matrix stuff, no idea how to map it or where to begin

void func_ovl3_80168428(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Vec3f vel = ip->phys_info.vel, direction, angle, *rotate;

    direction.x = 0;
    direction.y = 0;
    direction.z = (vel.x > 0.0F) ? LEFT : RIGHT;

    vec3f_normalize(&vel);

    func_ovl0_800CD5AC(&vel, &direction, &angle);

    rotate = &DObjGetStruct(item_gobj)->rotate;

    if (direction.z == LEFT)
    {
        rotate->y = HALF_PI32;
        rotate->x = atan2f(angle.x, angle.y);
    }
    else
    {
        rotate->y = -HALF_PI32;
        rotate->x = atan2f(-angle.x, angle.y);
    }

    rotate->z = 0.0F;
}