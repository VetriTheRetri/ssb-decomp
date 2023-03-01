#include "article.h"
#include "gmmatch.h"
#include "gmground.h"
#include "gbi.h"

extern Gfx *D_ovl3_8018D094;

Gfx* func_ovl3_8016DFAC(void) // Might not actually be Gfx, but data immediately following these pointers is a display list
{
    Gfx *next_gfx = D_ovl3_8018D094;
    Gfx *current_gfx;

    if (next_gfx == NULL)
    {
        return NULL;
    }
    current_gfx = next_gfx;

    D_ovl3_8018D094 = (Gfx*)(next_gfx->words.w0);

    return current_gfx;
}

void func_ovl3_8016DFDC(Gfx *display_list)
{
    display_list->words.w0 = (uintptr_t)D_ovl3_8018D094;

    D_ovl3_8018D094 = display_list;
}

void func_ovl3_8016DFF4(GObj *gobj, JObjDesc *joint_desc, JObj **p_ptr_jobj, u8 arg3)
{
    s32 i, index;
    JObj *joint, *jobj_array[18];

    for (i = 0; i < ARRAY_COUNT(jobj_array); i++)
    {
        jobj_array[i] = NULL;
    }
    for (i = 0; joint_desc->index != ARRAY_COUNT(jobj_array); i++, joint_desc++)
    {
        index = joint_desc->index & 0xFFF;

        if (index != 0)
        {
            joint = jobj_array[index] = func_800093F4(jobj_array[index - 1], joint_desc->x4);
        }
        else
        {
            joint = jobj_array[0] = func_800092D0(gobj, joint_desc->x4);
        }
        if (i == 1)
        {
            func_8000F364(joint, arg3, NULL, NULL, NULL);
        }
        else if (arg3 != 0)
        {
            func_80008CC0(joint, arg3, NULL);
        }
        joint->translate = joint_desc->translate;
        joint->rotate = joint_desc->rotate;
        joint->scale = joint_desc->scale;

        if (p_ptr_jobj != NULL) // I have yet to find a case where this point is actually reached
        {
            p_ptr_jobj[i] = joint;
        }
    }
}

// Don't forget the following two functions here, stashed until I better understand articles (idk and func_ovl3_8016EA78)

void* func_ovl3_8016EB00(void)
{
    return D_ovl3_8018D094;
}

extern u16 D_ovl3_80189454[6];
extern u16 D_ovl3_80189460[6];

extern gmItemSpawn item_settings; // Static (.bss)

void func_ovl3_8016EB0C(void)
{
    item_settings.item_spawn_timer = D_ovl3_80189454[Match_Info->item_switch] + rand_u16_range(D_ovl3_80189460[Match_Info->item_switch] - D_ovl3_80189454[Match_Info->item_switch]);
}

void func_ovl3_8016EB78(s32 unused)
{
    s32 padding;
    s32 sp40;
    Vec3f pos;
    Vec3f sp28;

    if (Match_Info->pause_status != gmPauseStatus_Disable)
    {
        if (item_settings.item_spawn_timer > 0)
        {
            item_settings.item_spawn_timer--;
            return;
        }
        if (func_ovl3_8016EB00() != NULL)
        {
            sp40 = func_ovl3_80173090(&item_settings.unk_0xC);

            func_ovl2_800FC894(item_settings.item_toggles[rand_u16_range(item_settings.max_items)], &pos);

            sp28.z = 0.0F;
            sp28.y = 0.0F;
            sp28.x = 0.0F;

            func_800269C0(0x3AU);

            func_ovl3_8016EA78(0, sp40, &pos, &sp28, 4);
        }
        func_ovl3_8016EB0C();
    }
}

GObj* func_ovl3_8016EC40(void)
{
    GObj *gobj;
    s32 i;
    s32 item_count;
    u8 *unk_0x84_2;
    s32 item_count_2;
    s32 max_items;
    s32 item_toggles[30];
    u32 item_bits;
    s32 j;
    u32 item_bits_3;
    u8 *unk_0x84;
    u32 item_bits_2;

    // TO DO: Figure out where the iterator limit of 20 is coming from


    if (Match_Info->item_switch != 0)
    {
        if (Match_Info->item_toggles != 0)
        {
            if (Ground_Info->unk_0x84 != NULL)
            {
                unk_0x84_2 = Ground_Info->unk_0x84;

                item_bits_2 = Match_Info->item_toggles;

                item_count = 0;

                for (i = 0; i < 20; i++, item_bits_2 >>= 1)
                {
                    if (item_bits_2 & 1)
                    {
                        item_count += unk_0x84_2[i];
                    }
                }
                if (item_count == 0)
                {
                    return NULL;
                }
                item_settings.unk_0x1C = item_count;

                max_items = func_ovl2_800FC7A4(4);

                if (max_items == 0)
                {
                    return NULL;
                }
                if (max_items > ARRAY_COUNT(item_toggles))
                {
                    while (TRUE)
                    {
                        fatal_printf("Item positions are over %d!\n", ARRAY_COUNT(item_toggles));
                        scnmgr_crash_print_gobj_state();
                    }
                }
                item_settings.max_items = max_items;
                item_settings.item_toggles = hal_alloc(max_items * sizeof(*item_settings.item_toggles), 0);

                func_ovl2_800FC814(4, &item_toggles[0]);

                for (i = 0; i < max_items; i++)
                {
                    item_settings.item_toggles[i] = item_toggles[i];
                }
                gobj = func_80009968(0x3F5U, NULL, 2U, 0x80000000U);

                func_80008188(gobj, func_ovl3_8016EB78, 1U, 3U);

                item_bits = Match_Info->item_toggles;

                unk_0x84 = Ground_Info->unk_0x84;

                for (i = 0, j = 0; i < 20; i++, item_bits >>= 1)
                {
                    if ((item_bits & 1) && (unk_0x84[i] != 0))
                    {
                        j++;
                    }
                }
                item_settings.unk_0x14 = j;
                item_settings.unk_0x18 = hal_alloc(j * sizeof(*item_settings.unk_0x18), 0);
                item_settings.unk_0x20 = hal_alloc(j * sizeof(*item_settings.unk_0x20), 2);

                item_bits_3 = Match_Info->item_toggles;

                item_count_2 = 0;

                for (i = 0, j = 0; i < 20; i++, item_bits_3 >>= 1)
                {
                    if ((item_bits_3 & 1) && (unk_0x84[i] != 0))
                    {
                        item_settings.unk_0x18[j] = i;
                        item_settings.unk_0x20[j] = item_count_2;
                        item_count_2 += unk_0x84[i];

                        j++;
                    }
                }
                func_ovl3_8016EB0C();
                return gobj;
            }
        }
    }
    return NULL;
}
