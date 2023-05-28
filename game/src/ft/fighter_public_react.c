#include "fighter.h"
#include "gmmatch.h"

extern const u16 D_ovl2_8012C9A8[28];
static s32 D_ovl3_8018CF90;
static u32 D_ovl3_8018CF94; // Either this...
static f32 ftPublicReact_Damage_Knockback;
static gmSoundEffect *D_ovl3_8018CF9C;
static u16 D_ovl3_8018CFA0;
static s32 D_ovl3_8018CFA4; 
static s32 D_ovl3_8018CFA8;
static s32 ftPublicReact_Player_Number; // Or this is u32 and the other s32, not entirely sure which
static gmSoundEffect *D_ovl3_8018CFB0;
static u16 D_ovl3_8018CFB4;
static s32 D_ovl3_8018CFB8;
static u32 D_ovl3_8018CFBC;
static s32 D_ovl3_8018CFC0; // Struct of 8 bytes? Why is there no 0x8018CFC4?
static u16 D_ovl3_8018CFC8[10];
static u32 D_ovl3_8018CFE0;
static gmSoundEffect *D_ovl3_8018CFE4;
static u16 D_ovl3_8018CFE8;

bool32 func_ovl3_80164AB0(s32 unused, f32 knockback, s32 player_id)
{
    Fighter_Struct *fp;
    GObj *fighter_gobj = ftCommon_GetPlayerNumGObj(player_id);
    u16 sfx_id;

    if (fighter_gobj == NULL)
    {
        return FALSE;
    }

    if ((FighterGetStruct(fighter_gobj)->percent_damage < 100) || (D_ovl3_8018CFA8 < 1200))
    {
        return FALSE;
    }
    if (player_id == ftPublicReact_Player_Number)
    {
        return FALSE;
    }
    D_ovl3_8018CFBC = D_ovl2_8012C9A8[FighterGetStruct(fighter_gobj)->ft_kind];

    if (D_ovl3_8018CFBC == 0x2B7)
    {
        return FALSE;
    }
    if (D_ovl3_8018CFB0 != NULL)
    {
        sfx_id = D_ovl3_8018CFB0->sfx_id;
        if ((sfx_id != 0) && (sfx_id == D_ovl3_8018CFB4))
        {
            func_80026738(D_ovl3_8018CFB0);
        }
    }

    D_ovl3_8018CFB0 = func_800269C0(((knockback >= FTCOMMON_DAMAGE_PUBLIC_REACT_GASP_KNOCKBACK_UNK) ? 0x26A : 0x26B));

    if (D_ovl3_8018CFB0 != NULL)
    {
        D_ovl3_8018CFB4 = D_ovl3_8018CFB0->sfx_id;
        ftPublicReact_Player_Number = player_id;
        D_ovl3_8018CFB8 = 0;

        return TRUE;
    }
    return FALSE;
}

void func_ovl3_80164C18(void)
{
    if ((D_ovl3_8018CFB8 < 9) && (D_ovl3_8018CFB8 >= 3))
    {
        D_ovl3_8018CFA4 = 1;
    }
}

void func_ovl3_80164C44(u16 new_sfx)
{
    if (D_ovl3_8018CF9C != NULL)
    {
        u16 current_sfx = D_ovl3_8018CF9C->sfx_id;

        if ((current_sfx != 0) && (current_sfx == D_ovl3_8018CFA0))
        {
            func_80026738(D_ovl3_8018CF9C);
        }
    }
    D_ovl3_8018CF9C = func_800269C0(new_sfx);

    if (D_ovl3_8018CF9C != NULL)
    {
        D_ovl3_8018CFA0 = D_ovl3_8018CF9C->sfx_id;
    }
}

void func_ovl3_80164CBC(void)
{
    if (D_ovl3_8018CF9C != NULL)
    {
        u16 sfx_id = D_ovl3_8018CF9C->sfx_id;

        if ((sfx_id != 0) && (sfx_id == D_ovl3_8018CFA0))
        {
            func_80026738(D_ovl3_8018CF9C);
        }
    }
}

void func_ovl3_80164D08(s32 arg0, s32 arg1, f32 arg2)
{
    if (arg2 >= 130.0F)
    {
        if (func_ovl3_80164AB0(arg0, arg2, arg1) != FALSE)
        {
            func_ovl3_80164CBC();
            return;
        }
        else if (arg2 >= 160.0F)
        {
            func_ovl3_80164C18();
            func_ovl3_80164C44(0x26A);
            return;
        }
        else if (arg1 == D_ovl2_8018CFAC)
        {
            func_ovl3_80164C18();
        }
        func_ovl3_80164C44(0x26B);
    }
    else if (arg2 >= 100.0F)
    {
        func_ovl3_80164C44(0x26C);
    }
}

void func_ovl3_80164DE4(f32 arg0, s32 arg1, f32 knockback, s32 arg3)
{
    f32 var_f2;

    if (arg3 != 0)
    {
        func_ovl3_80164D08(arg0, arg1, knockback);
    }
    else if ((arg1 == D_ovl3_8018CF94) && (D_ovl3_8018CF90 < 0x3C))
    {
        if (ftPublicReact_Damage_Knockback < knockback)
        {
            var_f2 = knockback;
        }
        else
        {
            var_f2 = ftPublicReact_Damage_Knockback;
        }
        func_ovl3_80164D08(arg0, arg1, var_f2);
    }
    else if (knockback >= 160.0F)
    {
        func_ovl3_80164C18();
        func_ovl3_80164C44(0x26E);
    }
    else if (knockback >= 130.0F)
    {
        if (arg1 == ftPublicReact_Player_Number)
        {
            func_ovl3_80164C18();
        }
        func_ovl3_80164C44(0x26F);
    }
    else if (knockback >= 100.0F)
    {
        func_ovl3_80164C44(0x271);
    }
    D_ovl3_8018CF90 = 0;
    D_ovl3_8018CF94 = arg1;
    ftPublicReact_Damage_Knockback = knockback;
}

void func_ovl3_80164F2C(GObj *fighter_gobj, f32 knockback, bool32 arg2)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (knockback >= 100.0F) // Check if knockback is over 100 units
    {
        func_ovl3_80164DE4(fighter_gobj, fp->damage_player_number, knockback, arg2); // Play crowd SFX
    }
}

void func_ovl3_80164F70(GObj *fighter_gobj, f32 knockback)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (ftPublicReact_Player_Number == fp->player_number)
    {
        func_ovl3_80164C18();
    }
    if (knockback >= 160.0F)
    {
        func_ovl3_80164C44(0x267);
    }
    else if (knockback >= 130.0F)
    {
        func_ovl3_80164C44(0x268);
    }
    else if (knockback >= 100.0F)
    {
        func_ovl3_80164C44(0x269);
    }
}

static f32 D_ovl2_8013132C; // Extern

void func_ovl3_80165024(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    f32 pos_y = fp->joint[0]->translate.y;

    if (!(D_ovl2_8013132C <= pos_y) && !(pos_y < -2400.0F))
    {
        if (pos_y >= -300.0F)
        {
            func_ovl3_80164C44(0x267);
        }
        else if (pos_y >= -900.0F)
        {
            func_ovl3_80164C44(0x268);
        }
        else
        {
            func_ovl3_80164C44(0x269);
        }
        if (ftPublicReact_Player_Number == fp->player_number)
        {
            func_ovl3_80164C18();
        }
    }
}

static u16 D_ovl3_8018CFC8[10];
static u32 D_ovl3_8018CFDC;
static u32 D_ovl3_8018CFE0;
static gmSoundEffect *D_ovl3_8018CFE4;
static u16 D_ovl3_8018CFE8;
extern gmUnkInfo_80131308 D_ovl2_80131308;

void func_ovl3_80165134(s32 arg0)
{
    s32 D_8018CFC0_prev;
    s32 temp_t5;
    u16 temp_v0;
    GObj *var_gobj;
    GObj *gobj;

    if (D_ovl3_8018CF90 < 0x10000)
    {
        D_ovl3_8018CF90++;
    }
    D_8018CFC0_prev = D_ovl3_8018CFC0;
    D_ovl3_8018CFC0 = 0;
    gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];

    var_gobj = NULL;

    if (gobj != NULL)
    {
        do
        {
            Fighter_Struct *fp = FighterGetStruct(gobj);

            if (!(Match_Info->match_rules & GMMATCH_GAMERULE_STOCK) || (fp->stock_count != -1))
            {
                if (DObjGetStruct(gobj)->translate.y < (D_ovl2_80131308.unk_80131308_0x24 - 100.0F)) // 0x80131308 = stage data?
                {
                    D_ovl3_8018CFC0++;
                }
                else
                {
                    var_gobj = gobj;
                }
            }
            gobj = (GObj *)gobj->group_gobj_next;
        } 
        while (gobj != NULL);
    }
    if ((D_8018CFC0_prev < 3) && (D_ovl3_8018CFC0 >= 3))
    {
        func_ovl3_80164C44(0x267);

        if ((var_gobj != NULL) && (ftPublicReact_Player_Number == FighterGetStruct(var_gobj)->player_number))
        {
            func_ovl3_80164C18();
        }
    }
    if (D_ovl3_8018CFB8 < 9) // Might be (ARRAY_COUNT(D_ovl3_8018CFC8) - 1)
    {
        if ((D_ovl3_8018CFB0 == NULL) || (D_ovl3_8018CFB0->sfx_id == 0) || (D_ovl3_8018CFB0->sfx_id != D_ovl3_8018CFB4))
        {
            D_ovl3_8018CFB8++;

            if (D_ovl3_8018CFB8 < 9)
            {
                if (D_ovl3_8018CFA4 != 0)
                {
                    D_ovl3_8018CFA4 = 0;
                    D_ovl3_8018CFA8 = 0;
                    D_ovl3_8018CFB8 = 9;
                }
                else
                {
                    D_ovl3_8018CFB0 = func_800269C0(D_ovl3_8018CFBC);

                    if (D_ovl3_8018CFB0 != NULL)
                    {
                        D_ovl3_8018CFB4 = D_ovl3_8018CFB0->sfx_id;
                    }
                }
            }
            else
            {
                D_ovl3_8018CFA8 = 0;

                func_ovl3_80164C44(0x26A);
            }
        }
    }
    else if (D_ovl3_8018CFA8 < 0x4B0)
    {
        D_ovl3_8018CFA8++;
    }

    if (D_ovl3_8018CFDC != D_ovl3_8018CFE0)
    {
        if ((D_ovl3_8018CFE4 == NULL) || (D_ovl3_8018CFE8 == 0) || (D_ovl3_8018CFE4->sfx_id != D_ovl3_8018CFE8))
        {
            D_ovl3_8018CFE4 = func_800269C0(D_ovl3_8018CFC8[D_ovl3_8018CFDC]);
            if (D_ovl3_8018CFE4 != NULL)
            {
                D_ovl3_8018CFE8 = D_ovl3_8018CFE4->sfx_id;
            }
            else
            {
                D_ovl3_8018CFE8 = 0;
            }
            D_ovl3_8018CFDC++;

            if (D_ovl3_8018CFDC == ARRAY_COUNT(D_ovl3_8018CFC8))
            {
                D_ovl3_8018CFDC = 0;
            }
        }
    }
}

void *func_ovl3_801653E0(void)
{
    void *gobj_process = func_80008188(func_80009968(0x3FA, NULL, 0xD, 0x80000000), func_ovl3_80165134, 1, 0); 
    D_ovl3_8018CF90 = U16_MAX + 1;
    D_ovl3_8018CF94 = U32_MAX;
    ftPublicReact_Damage_Knockback = 0.0F;
    D_ovl3_8018CF9C = 0;
    D_ovl3_8018CFA0 = 0;
    D_ovl3_8018CFA4 = 0;
    D_ovl3_8018CFA8 = 1200;
    ftPublicReact_Player_Number = -1;
    D_ovl3_8018CFB8 = 9;
    D_ovl3_8018CFC0 = 0;
    D_ovl3_8018CFE4 = 0;
    D_ovl3_8018CFE8 = 0;
    D_ovl3_8018CFE0 = 0;
    D_ovl3_8018CFDC = D_ovl3_8018CFE0;

    return gobj_process;
}