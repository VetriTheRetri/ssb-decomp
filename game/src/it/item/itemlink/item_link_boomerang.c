#include "item.h"
#include "fighter.h"
#include "gmmatch.h"

void func_ovl3_8016CC50(f32 *angle)
{
    if (DOUBLE_PI32 < *angle)
    {
        *angle -= DOUBLE_PI32;
    }
    else if (*angle < -DOUBLE_PI32)
    {
        *angle += DOUBLE_PI32;
    }
} 

bool32 func_ovl3_8016CCA0(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    f32 sp30;
    f32 sp2C;
    f32 temp_f0;
    f32 temp_f2;

    if (ip->item_vars.boomerang.homing_delay > 0)
    {
        ip->item_vars.boomerang.homing_delay--;

    }
    else
    {
        ip->item_vars.boomerang.adjust_angle_delay++;

        if (ip->item_vars.boomerang.adjust_angle_delay >= 9)
        {
            ip->item_vars.boomerang.adjust_angle_delay = 0;

            func_ovl2_800EB924(D_ovl2_80131460->unk_0x74, &D_ovl2_80131470, &DObjGetStruct(weapon_gobj)->translate, &sp30, &sp2C);

            temp_f0 = (D_ovl2_801314B0.unk_0x38.x / 2) + 40.0F;
            temp_f2 = (D_ovl2_801314B0.unk_0x38.y / 2) + 40.0F;

            if ((sp30 < -temp_f0) || (temp_f0 < sp30) || (sp2C < -temp_f2) || (temp_f2 < sp2C))
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void func_ovl3_8016CDC8(GObj *weapon_gobj, bool32 arg1)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    ip->item_vars.boomerang.flags |= 1;

    ip->item_hit.damage = 8;

    ip->item_vars.boomerang.unk_0x8 -= PI32;

    if (ip->item_vars.boomerang.unk_0x8 < 0.0F)
    {
        ip->item_vars.boomerang.unk_0x8 += DOUBLE_PI32;
    }
    ip->lr = -ip->lr;

    ip->item_vars.boomerang.unk_0x4 = 0x8C;

    ip->item_vars.boomerang.homing_angle = (arg1 == TRUE) ? ITBOOMERANG_HOMING_ANGLE_MAX : ITBOOMERANG_HOMING_ANGLE_MIN;

    DObjGetStruct(weapon_gobj)->next->next->unk_0x54 = 1;

    wpMain_PlayDestroySFX(ip, 0xCEU);
}

f32 func_ovl3_8016CE90(Weapon_Struct *ip, f32 vel_add)
{
    f32 sqrt_vel = sqrtf(SQUARE(ip->phys_info.vel.x) + SQUARE(ip->phys_info.vel.y)) + vel_add;

    if (sqrt_vel > 90.0F)
    {
        sqrt_vel = 90.0F;
    }
    return sqrt_vel;
}

f32 func_ovl3_8016CEEC(Weapon_Struct *ip, f32 vel_sub)
{
    f32 sqrt_vel = sqrtf(SQUARE(ip->phys_info.vel.x) + SQUARE(ip->phys_info.vel.y)) - vel_sub;

    if (sqrt_vel < 10.0F)
    {
        sqrt_vel = 10.0F;
    }
    return sqrt_vel;
}

void func_ovl3_8016CF48(Weapon_Struct *ip, f32 vel_mul)
{
    sqrtf(SQUARE(ip->phys_info.vel.x) + SQUARE(ip->phys_info.vel.y)); // Can we talk about how this doesn't do anything

    ip->phys_info.vel.x = cosf(ip->item_vars.boomerang.unk_0x8) * vel_mul;
    ip->phys_info.vel.y = __sinf(ip->item_vars.boomerang.unk_0x8) * vel_mul;

    ip->lr = ((HALF_PI32 < ip->item_vars.boomerang.unk_0x8) && (ip->item_vars.boomerang.unk_0x8 < 4.712389F)) ? LEFT : RIGHT;
}

void func_ovl3_8016CFFC(f32 *angle)
{
    if ((0.5235988F < *angle) && (*angle <= HALF_PI32))
    {
        *angle = 0.5235988F;
    }
    else if ((*angle < 2.6179938F) && (HALF_PI32 <= *angle))
    {
        *angle = 2.6179938F;
    }
    else if ((3.6651917F < *angle) && (*angle <= 4.712389F))
    {
        *angle = 3.6651917F;
    }
    else if ((*angle < 5.759587F) && (4.712389F <= *angle))
    {
        *angle = 5.759587F;
    }
}

f32 func_ovl3_8016D0E4(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    f32 unused;
    f32 temp_f14;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 var_f16 = 0.0F;

    if (ip->item_vars.boomerang.spawn_gobj != NULL)
    {
        temp_f14 = DObjGetStruct(ip->item_vars.boomerang.spawn_gobj)->translate.x - DObjGetStruct(weapon_gobj)->translate.x;
        temp_f0 = (DObjGetStruct(ip->item_vars.boomerang.spawn_gobj)->translate.y - DObjGetStruct(weapon_gobj)->translate.y) + 290.0F;

        var_f16 = sqrtf(SQUARE(temp_f14) + SQUARE(temp_f0));

        if (ip->item_vars.boomerang.flags & 4)
        {
            if (ip->item_vars.boomerang.unk_0x4 > 0)
            {
                ip->item_vars.boomerang.unk_0x4--;
            }
            else if (ip->item_vars.boomerang.unk_0x4 == 0)
            {
                return var_f16;
            }
        }
        if ((ip->item_vars.boomerang.flags & 0x10) && (((temp_f14 < 0.0F) && (ip->lr == RIGHT)) || ((temp_f14 > 0.0F) && (ip->lr == LEFT))))
        {
            return var_f16;
        }
        else
        {
            temp_f0_2 = atan2f(temp_f0, temp_f14);

            if (temp_f0_2 < -PI32)
            {
                temp_f0_2 += DOUBLE_PI32;
            }
            else if (PI32 < temp_f0_2)
            {
                temp_f0_2 -= DOUBLE_PI32;
            }

            temp_f0_2 -= ip->item_vars.boomerang.unk_0x8;

            if (temp_f0_2 < -PI32)
            {
                temp_f0_2 += DOUBLE_PI32;
            }
            else if (PI32 < temp_f0_2)
            {
                temp_f0_2 -= DOUBLE_PI32;
            }

            if (ip->item_vars.boomerang.homing_angle < temp_f0_2)
            {
                temp_f0_2 = ip->item_vars.boomerang.homing_angle;
            }
            else if (temp_f0_2 < -ip->item_vars.boomerang.homing_angle)
            {
                temp_f0_2 = -ip->item_vars.boomerang.homing_angle;
            }

            ip->item_vars.boomerang.unk_0x8 += temp_f0_2;

            func_ovl3_8016CC50(&ip->item_vars.boomerang.unk_0x8);

            if (ip->item_vars.boomerang.flags & 8)
            {
                func_ovl3_8016CFFC(&ip->item_vars.boomerang.unk_0x8);
            }
        }
    }
    return var_f16;
}

void func_ovl3_8016D31C(Weapon_Struct *ip)
{
    if (ip->item_vars.boomerang.spawn_gobj != NULL)
    {
        Fighter_Struct *fp = ftGetStruct(ip->item_vars.boomerang.spawn_gobj);

        if ((fp->ft_kind == Ft_Kind_Kirby) || (fp->ft_kind == Ft_Kind_PolyKirby))
        {
            fp->fighter_vars.kirby.copylink_boomerang_gobj = NULL;
        }
        else
        {
            fp->fighter_vars.link.boomerang_gobj = NULL;
        }
        ip->item_vars.boomerang.spawn_gobj = NULL;
    }
}

void func_ovl3_8016D35C(GObj *weapon_gobj, f32 distance)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if ((ip->item_vars.boomerang.flags & 1) && (distance < 180.0F))
    {
        if (ip->item_vars.boomerang.spawn_gobj != NULL)
        {
            Fighter_Struct *fp = ftGetStruct(ip->item_vars.boomerang.spawn_gobj);

            if (fp->x192_flag_b0)
            {
                if ((fp->ft_kind == Ft_Kind_Kirby) || (fp->ft_kind == Ft_Kind_PolyKirby))
                {
                    func_ovl3_80164A40(ip->item_vars.boomerang.spawn_gobj);
                }
                else
                {
                    ftLink_SpecialNReturn_SetStatus(ip->item_vars.boomerang.spawn_gobj);
                }
            }
        }
        func_ovl3_8016D31C(ip);
        wpMain_DestroyWeapon(weapon_gobj);
    }
}

bool32 func_ovl3_8016D40C(Weapon_Struct *ip, Vec3f *coll_angle)
{
    f32 angle = func_ovl0_800C7C0C(&ip->phys_info.vel, coll_angle);

    if (angle < 0.0F)
    {
        if (-__sinf(0.5235988F) < angle)
        {
            func_ovl0_800C7B08(&ip->phys_info.vel, coll_angle);

            ip->item_vars.boomerang.unk_0x8 = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);

            func_ovl3_8016CC50(&ip->item_vars.boomerang.unk_0x8);
        }
        else return TRUE;
    }
    return FALSE;
}

bool32 func_ovl3_8016D4B8(GObj *weapon_gobj)
{
    func_ovl3_8016D31C(wpGetStruct(weapon_gobj));

    return TRUE;
}

bool32 jtgt_ovl3_8016D4DC(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if ((wpMain_DecLifeCheckExpire(ip) != FALSE) || (func_ovl3_8016CCA0(weapon_gobj) == TRUE))
    {
        func_ovl3_8016D31C(ip);

        return TRUE;
    }
    if (ip->item_vars.boomerang.flags & 2)
    {
        func_ovl3_8016D31C(ip);

        return TRUE;
    }
    if (ip->item_vars.boomerang.flags & 0x20)
    {
        return FALSE;
    }
    else if (ip->item_vars.boomerang.flags & 1)
    {
        func_ovl3_8016CF48(ip, func_ovl3_8016CE90(ip, 1.0F));

        func_ovl3_8016D35C(weapon_gobj, func_ovl3_8016D0E4(weapon_gobj));
    }
    else
    {
        f32 vel = func_ovl3_8016CEEC(ip, 1.4F);

        func_ovl3_8016CF48(ip, vel);

        if (vel == 10.0F)
        {
            func_ovl3_8016CDC8(weapon_gobj, FALSE);
        }
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016D5EC(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    bool32 unk_bool = FALSE;
    u16 coll_flags;

    if (!(ip->item_vars.boomerang.flags & 0x21))
    {
        func_ovl3_80167A58(weapon_gobj);

        coll_flags = (ip->coll_data.coll_mask_prev ^ ip->coll_data.coll_mask) & ip->coll_data.coll_mask & MPCOLL_MASK_MAIN_ALL;

        if (coll_flags)
        {
            func_ovl2_800FECBC(&DObjGetStruct(weapon_gobj)->translate);

            if (coll_flags & MPCOLL_MASK_RWALL)
            {
                unk_bool |= func_ovl3_8016D40C(ip, &ip->coll_data.rwall_angle);
            }
            if (coll_flags & MPCOLL_MASK_LWALL)
            {
                unk_bool |= func_ovl3_8016D40C(ip, &ip->coll_data.lwall_angle);
            }
            if (coll_flags & MPCOLL_MASK_CEIL)
            {
                unk_bool |= func_ovl3_8016D40C(ip, &ip->coll_data.ceil_angle);
            }
            if (coll_flags & MPCOLL_MASK_GROUND)
            {
                unk_bool |= func_ovl3_8016D40C(ip, &ip->coll_data.ground_angle);
            }
            if (unk_bool == TRUE)
            {
                func_ovl3_8016CDC8(weapon_gobj, TRUE);
            }
        }
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016D714(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (!(ip->item_vars.boomerang.flags & 0x21) && (ip->hit_victim_damage != 0))
    {
        func_ovl3_8016CF48(ip, func_ovl3_8016CEEC(ip, 5.0F));
        func_ovl3_8016CDC8(weapon_gobj, TRUE);
    }
    return FALSE;
}

bool32 func_ovl3_8016D77C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (!(ip->item_vars.boomerang.flags & 0x21))
    {
        func_ovl3_8016CDC8(weapon_gobj, TRUE);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016D7B4(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (!(ip->item_vars.boomerang.flags & 0x21))
    {
        func_ovl3_8016CDC8(weapon_gobj, TRUE);
    }
    return FALSE;
}

bool32 jtgt_ovl3_8016D7EC(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (ip->shield_collide_vec.z > 0.0F)
    {
        ip->item_vars.boomerang.unk_0x8 += (ip->shield_collide_angle * 2);
    }
    else
    {
        ip->item_vars.boomerang.unk_0x8 -= (ip->shield_collide_angle * 2);
    }
    func_ovl3_8016CC50(&ip->item_vars.boomerang.unk_0x8);

    return FALSE;
}

bool32 jtgt_ovl3_8016D868(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    f32 dist_x, dist_y;

    if (!(ip->item_vars.boomerang.flags & 0x20))
    {
        ip->item_vars.boomerang.flags = 0x20;
        ip->lifetime = ITBOOMERANG_LIFETIME_REFLECT;
    }

    dist_x = DObjGetStruct(weapon_gobj)->translate.x - DObjGetStruct(ip->owner_gobj)->translate.x;
    dist_y = DObjGetStruct(weapon_gobj)->translate.y - (DObjGetStruct(ip->owner_gobj)->translate.y + 250.0F);

    ip->item_vars.boomerang.unk_0x8 = atan2f(dist_y, dist_x);

    func_ovl3_8016CC50(&ip->item_vars.boomerang.unk_0x8);

    func_ovl3_8016CF48(ip, sqrtf(SQUARE(ip->phys_info.vel.x) + SQUARE(ip->phys_info.vel.y)));

    return FALSE;
}

f32 func_ovl3_8016D914(Vec3f *vel, Fighter_Struct *fp, s32 lr, f32 vel_mul)
{
    f32 angle;

    if (ABS(fp->input.pl.stick_range.y) > ITBOOMERANG_ANGLE_STICK_THRESHOLD)
    {
        angle = atan2f(fp->input.pl.stick_range.y, ABS(fp->input.pl.stick_range.x));

        if (0.5235988F < angle)
        {
            angle = 0.5235988F;

        }
        else if (angle < -0.5235988F)
        {
            angle = -0.5235988F;
        }
    }
    else
    {
        angle = 0.0F;
    }
    vel->x = (f32)(cosf(angle) * vel_mul * lr);
    vel->y = (f32)(__sinf(angle) * vel_mul * lr);
    vel->z = 0.0F;

    if (lr == LEFT)
    {
        if (angle < 0.0F)
        {
            angle = PI32 - angle;
        }
        else
        {
            angle = (-PI32) - angle;
        }
    }
    if (angle < 0.0F)
    {
        angle += DOUBLE_PI32;
    }
    return angle;
}

extern WeaponSpawnData Item_Boomerang_Desc;

GObj *func_ovl3_8016DA78(GObj *fighter_gobj, Vec3f *pos)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);
    GObj *weapon_gobj;
    Weapon_Struct *ip;
    Vec3f offset;
    s32 unused;

    offset = *pos;

    offset.y += ITBOOMERANG_OFF_Y;

    offset.x = (fp->lr == RIGHT) ? offset.x + ITBOOMERANG_OFF_X : offset.x - ITBOOMERANG_OFF_X;

    weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_Boomerang_Desc, &offset, WEAPON_MASK_SPAWN_FIGHTER);

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->lr = fp->lr;

    if (fp->status_vars.link.specialn.is_smash == TRUE)
    {
        ip->lifetime = ITBOOMERANG_LIFETIME_SMASH;
        ip->item_vars.boomerang.unk_0x8 = func_ovl3_8016D914(&ip->phys_info.vel, fp, ip->lr, ITBOOMERANG_VEL_SMASH);
    }
    else
    {
        ip->lifetime = ITBOOMERANG_LIFETIME_TILT;
        ip->item_vars.boomerang.unk_0x8 = func_ovl3_8016D914(&ip->phys_info.vel, fp, ip->lr, ITBOOMERANG_VEL_TILT);
    }
    ip->proc_setoff = func_ovl3_8016D77C;
    ip->proc_dead = func_ovl3_8016D4B8;

    ip->is_camera_follow = TRUE;

    wpMain_PlayDestroySFX(ip, 0xCFU);

    ip->item_vars.boomerang.spawn_gobj = fighter_gobj;
    ip->item_vars.boomerang.flags = 4;
    ip->item_vars.boomerang.homing_delay = 0x82;
    ip->item_vars.boomerang.adjust_angle_delay = 0;

    wpMain_VelSetModelYaw(weapon_gobj);

    ip->is_hitlag_victim = TRUE;

    return weapon_gobj;
}
