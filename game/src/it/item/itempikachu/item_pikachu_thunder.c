#include "item.h"
#include "fighter.h"

void func_ovl3_8016A640(GObj *weapon_gobj, bool32 thunder_state)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (!(ip->item_vars.thunder.thunder_state & wpPikachuThunderStatus_Destroy))
    {
        Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

        if (fp->player_number == ip->player_number) // Check number of player that spawned Thunder
        {
            fp->fighter_vars.pikachu.is_thunder_destroy |= thunder_state;
        }
    }
}

void func_ovl3_8016A680(GObj *weapon_gobj, s32 arg1)
{
    s32 unused;
    Vec3f pos;

    pos.x = DObjGetStruct(weapon_gobj)->translate.x;
    pos.y = DObjGetStruct(weapon_gobj)->translate.y;
    pos.z = 0.0F;

    if (arg1 == 3)
    {
        func_ovl2_80101B88(&pos, 0xA, 3);
    }
    else if (arg1 == -1)
    {
        func_ovl2_80101B88(&pos, 6, 0);
    }
    else func_ovl3_8016A980(weapon_gobj, &pos);
}

bool32 jtgt_ovl3_8016A700(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (ip->item_vars.thunder.thunder_state == wpPikachuThunderStatus_Collide)
    {
        func_ovl3_8016A680(weapon_gobj, 3);

        return TRUE;
    }
    else if (wpMain_DecLifeCheckExpire(ip) != 0)
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);
        func_ovl3_8016A640(weapon_gobj, TRUE);
        func_ovl3_8016A680(weapon_gobj, 3);

        return TRUE;
    }
    else func_ovl3_8016A680(weapon_gobj, 0);

    return FALSE;
}

bool32 jtgt_ovl3_8016A794(GObj *weapon_gobj)
{
    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        func_ovl3_8016A640(weapon_gobj, TRUE);
        func_ovl2_801008F4(1);
        func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

        return TRUE;
    }
    return FALSE;
}

bool32 func_ovl3_8016A7E8(GObj *weapon_gobj)
{
    func_ovl3_8016A640(weapon_gobj, TRUE);

    return TRUE;
}

extern WeaponSpawnData Item_ThunderSpawn_Desc;

GObj *func_ovl3_8016A80C(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel)
{
    s32 unused;
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &Item_ThunderSpawn_Desc, pos, WEAPON_MASK_SPAWN_FIGHTER);
    Weapon_Struct *ip;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }

    ip = wpGetStruct(weapon_gobj);

    ip->proc_dead = func_ovl3_8016A7E8;

    ip->lifetime = ITPIKACHUTHUNDER_SPAWN_LIFETIME;

    ip->phys_info.vel = *vel;

    ip->item_hit.update_state = 0;
    ip->item_vars.thunder.thunder_state = wpPikachuThunderStatus_Active;

    ip->group_id = func_ovl3_801655A0();

    DObjGetStruct(weapon_gobj)->mobj->index = 3;

    DObjGetStruct(weapon_gobj)->scale.x = 0.5F;
    DObjGetStruct(weapon_gobj)->scale.y = 0.5F;
    DObjGetStruct(weapon_gobj)->scale.z = 0.5F;

    return weapon_gobj;
}

bool32 func_ovl3_8016A8D8(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        return TRUE;
    }
    else if (ip->lifetime < ITPIKACHUTHUNDER_EXPIRE)
    {
        func_ovl3_8016A680(weapon_gobj, -1);

        return TRUE;
    }
    else DObjGetStruct(weapon_gobj)->mobj->index = rand_u16_range(ITPIKACHUTHUNDER_TEXTURE_COUNT - 1);

    return FALSE;
}

bool32 jtgt_ovl3_8016A950(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);

    func_ovl2_800FE068(&DObjGetStruct(weapon_gobj)->translate, ip->item_hit.damage);

    return FALSE;
}

extern WeaponSpawnData Item_ThunderChain_Desc;

GObj* func_ovl3_8016A980(GObj *weapon_gobj, Vec3f *pos)
{
    s32 unused[2];
    Weapon_Struct *spawn_ip = wpGetStruct(weapon_gobj);
    GObj *chain_gobj = wpManager_CreateWeapon(weapon_gobj, &Item_ThunderChain_Desc, pos, WEAPON_MASK_SPAWN_WEAPON);
    Weapon_Struct *chain_ip;
    s32 i;

    if (chain_gobj == NULL)
    {
        return NULL;
    }
    chain_ip = wpGetStruct(chain_gobj);

    chain_ip->lifetime = ITPIKACHUTHUNDER_CHAIN_LIFETIME;
    chain_ip->group_id = spawn_ip->group_id;

    for (i = 0; i < (ARRAY_COUNT(spawn_ip->item_hit.hit_targets) | ARRAY_COUNT(chain_ip->item_hit.hit_targets)); i++)
    {
        chain_ip->item_hit.hit_targets[i] = spawn_ip->item_hit.hit_targets[i];
    }

    DObjGetStruct(chain_gobj)->scale.x = 0.5F;
    DObjGetStruct(chain_gobj)->scale.y = 0.5F;
    DObjGetStruct(chain_gobj)->scale.z = 0.5F;

    return chain_gobj;
}
