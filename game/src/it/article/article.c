#include "article.h"
#include "fighter.h"
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
    gmGroundUnkBytes *unk_0x84_2;
    s32 item_count_2;
    s32 max_items;
    s32 item_toggles[30];
    u32 item_bits;
    s32 j;
    u32 item_bits_3;
    gmGroundUnkBytes *unk_0x84;
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
                        item_count += unk_0x84_2->byte[i];
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
                    if ((item_bits & 1) && (unk_0x84->byte[i] != 0))
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
                    if ((item_bits_3 & 1) && (unk_0x84->byte[i] != 0))
                    {
                        item_settings.unk_0x18[j] = i;
                        item_settings.unk_0x20[j] = item_count_2;
                        item_count_2 += unk_0x84->byte[i];

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

static Unk_8018D048 D_ovl3_8018D048;

void func_ovl3_8016EF40(void)
{
    s32 sp28;
    s32 sp1C;
    s32 item_count_2;
    gmGroundUnkBytes *temp_a3;
    s32 temp_f18;
    s32 j;
    s32 item_count_4;
    s32 k;
    gmGroundUnkBytes *temp_t1;
    s32 item_count_2_2;
    s32 temp_a0;
    s32 i;
    s32 item_count;
    u32 item_bits;
    u32 item_bits_2;
    u32 item_bits_3;

    if ((Match_Info->item_switch != 0) && (Match_Info->item_toggles != 0) && (Ground_Info->unk_0x84 != NULL))
    {
        item_bits = Match_Info->item_toggles >> 4;

        temp_a3 = Ground_Info->unk_0x84;

        item_count = 0;

        for (i = 4; i < 20; i++, item_bits >>= 1)
        {
            if (item_bits & 1)
            {
                item_count += temp_a3->byte[i];
            }
        }
        D_ovl3_8018D048.unk_0x10 = item_count;

        if (item_count != 0)
        {
            item_bits_2 = (u32)Match_Info->item_toggles >> 4;

            temp_t1 = Ground_Info->unk_0x84;

            for (j = 0, i = 4; i < 20; i++, item_bits_2 >>= 1)
            {
                if ((item_bits_2 & 1) && (temp_t1->byte[i] != 0))
                {
                    j++;
                }
            }
            j++;

            D_ovl3_8018D048.unk_0x8 = j;
            D_ovl3_8018D048.unk_0xC = hal_alloc(j * sizeof(*D_ovl3_8018D048.unk_0xC), 0U);
            D_ovl3_8018D048.unk_0x14 = hal_alloc(j * sizeof(*D_ovl3_8018D048.unk_0x14), 2U);

            item_bits_2 = Match_Info->item_toggles >> 4;

            item_count_2 = 0;

            for (j = 0, i = 4; i < 20; i += 4, item_bits_2 >>= 1)
            {
                if ((item_bits_2 & 1) && (temp_t1->byte[i] != 0))
                {
                    D_ovl3_8018D048.unk_0xC[j] = i;
                    D_ovl3_8018D048.unk_0x14[j] = item_count_2;
                    item_count_2 += temp_t1->byte[i];
                    j++;
                }
                item_bits_2 >>= 1;

                if ((item_bits_2 & 1) && (temp_t1->byte[i + 1] != 0))
                {
                    D_ovl3_8018D048.unk_0xC[j] = i + 1;
                    D_ovl3_8018D048.unk_0x14[j] = item_count_2;
                    item_count_2 += temp_t1->byte[i + 1];
                    j++;
                }
                item_bits_2 >>= 1;

                if ((item_bits_2 & 1) && (temp_t1->byte[i + 2] != 0))
                {

                    D_ovl3_8018D048.unk_0xC[j] = i + 2;
                    D_ovl3_8018D048.unk_0x14[j] = item_count_2;
                    item_count_2 += temp_t1->byte[i + 2];
                    j++;
                }
                item_bits_2 >>= 1;

                if ((item_bits_2 & 1) && (temp_t1->byte[i + 3] != 0))
                {
                    D_ovl3_8018D048.unk_0xC[j] = i + 3;
                    D_ovl3_8018D048.unk_0x14[j] = item_count_2;
                    item_count_2 += temp_t1->byte[i + 3];
                    j++;
                }
            }
            D_ovl3_8018D048.unk_0xC[j] = 32;
            D_ovl3_8018D048.unk_0x14[j] = item_count_2;

            temp_f18 = (s32)(D_ovl3_8018D048.unk_0x10 * 0.1F);

            if (temp_f18 != 0)
            {
                item_count_4 = temp_f18;
            }
            else item_count_4 = 1;

            D_ovl3_8018D048.unk_0x10 += item_count_4;
        }
    }
    else
    {
        D_ovl3_8018D048.unk_0x10 = 0U;
    }
}

typedef struct Unk_8018D060
{
    u8 unk_0x0;
    u8 unk_0x1;
    u8 filler_0x2[0x2E - 0x2];
    u8 unk_0x2E;

} Unk_8018D060;

static Unk_8018D060 D_ovl3_8018D060;

void func_ovl3_8016F218(void)
{
    D_ovl3_8018D060.unk_0x0 = D_ovl3_8018D060.unk_0x1 = U8_MAX;
    D_ovl3_8018D060.unk_0x2E = 0xC;
}

extern void* (*jtbl_ovl3_8018946C[20])(s32, s32, s32, s32);

void* func_ovl3_8016F238(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    return jtbl_ovl3_8018946C[arg1](arg0, arg2, arg3, arg4);
}

void func_ovl3_8016F280(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    s32 i;

    for (i = 0; i < ap->article_hit[0].hitbox_count; i++)
    {
        switch (ap->article_hit[0].update_state)
        {
        case gmHitCollision_UpdateState_Disable:
            break;

        case gmHitCollision_UpdateState_New:
            ap->article_hit[0].article_hit_unk[i].pos.x = ap->article_hit[0].offset[i].x + JObjGetStruct(article_gobj)->translate.x;
            ap->article_hit[0].article_hit_unk[i].pos.y = ap->article_hit[0].offset[i].y + JObjGetStruct(article_gobj)->translate.y;
            ap->article_hit[0].article_hit_unk[i].pos.z = ap->article_hit[0].offset[i].z + JObjGetStruct(article_gobj)->translate.z;

            ap->article_hit[0].update_state = gmHitCollision_UpdateState_Transfer;

            ap->article_hit[0].article_hit_unk[i].unk_0x18 = 0;
            ap->article_hit[0].article_hit_unk[i].unk_0x5C = 0;
            break;

        case gmHitCollision_UpdateState_Transfer:
            ap->article_hit[0].update_state = gmHitCollision_UpdateState_Interpolate;

        case gmHitCollision_UpdateState_Interpolate:
            ap->article_hit[0].article_hit_unk[i].pos_prev = ap->article_hit[0].article_hit_unk[i].pos;

            ap->article_hit[0].article_hit_unk[i].pos.x = ap->article_hit[0].offset[i].x + JObjGetStruct(article_gobj)->translate.x;
            ap->article_hit[0].article_hit_unk[i].pos.y = ap->article_hit[0].offset[i].y + JObjGetStruct(article_gobj)->translate.y;
            ap->article_hit[0].article_hit_unk[i].pos.z = ap->article_hit[0].offset[i].z + JObjGetStruct(article_gobj)->translate.z;

            ap->article_hit[0].article_hit_unk[i].unk_0x18 = 0;
            ap->article_hit[0].article_hit_unk[i].unk_0x5C = 0;
            break;
        }
    }
}

void func_ovl3_8016F3D4(GObj *article_gobj)
{
    Article_Struct *ip = ArticleGetStruct(article_gobj);
    ArticleHitArray *targets;
    Article_Hit *at_hit;
    s32 i;

    at_hit = &ip->article_hit[0];

    if (at_hit->update_state != gmHitCollision_UpdateState_Disable)
    {
        for (i = 0; i < ARRAY_COUNT(ip->article_hit[0].hit_targets); i++)
        {
            targets = &at_hit->hit_targets[i];

            if (targets->victim_gobj != NULL)
            {
                if (targets->victim_flags.timer_rehit > 0)
                {
                    targets->victim_flags.timer_rehit--;

                    if (targets->victim_flags.timer_rehit <= 0)
                    {
                        targets->victim_gobj = NULL;

                        targets->victim_flags.flags_b0 = targets->victim_flags.flags_b1 = targets->victim_flags.flags_b2 = FALSE;

                        targets->victim_flags.flags_b456 = 7;
                    }
                }
            }
        }
    }
}

void func_ovl3_8016F534(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    Vec3f *translate;
    JObj *joint;

    if (ap->hitlag_timer != 0)
    {
        ap->hitlag_timer--;
    }
    if (ap->hitlag_timer <= 0)
    {
        func_8000DF34(article_gobj);
    }
    if (ap->hitlag_timer <= 0)
    {
        if (ap->cb_anim != NULL)
        {
            if (ap->cb_anim(article_gobj) != FALSE)
            {
                func_ovl3_801728D4(article_gobj);
                return;
            }
        }
    }
    if (ap->x2CE_flag_b0)
    {
        ap->x2D2_flag_12bit--;

        if (ap->x2D2_flag_12bit <= ARTICLE_DESPAWN_FLASH_INT_DEFAULT)
        {
            if (ap->x2D2_flag_12bit == 0)
            {
                func_ovl2_8010066C(&JObjGetStruct(article_gobj)->translate, 1.0F);

                func_ovl3_801728D4(article_gobj);

                return;
            }
            if (ap->x2D2_flag_12bit & 1) // Make article invisible on odd frames
            {
                article_gobj->is_render ^= TRUE;
            }
        }

        if (ap->arrow_flash_timer == 0)
        {
            ap->arrow_flash_timer = ARTICLE_ARROW_BLINK_INT_DEFAULT;
        }
        ap->arrow_flash_timer--;
    }
    else article_gobj->is_render = FALSE;

    if (!(ap->is_hitlag_article))
    {
        joint = JObjGetStruct(article_gobj);

        translate = &JObjGetStruct(article_gobj)->translate;

        ap->coll_data.pos_curr = *translate;

        if (ap->hitlag_timer == 0)
        {
            translate->x += ap->phys_info.vel.x;
            translate->y += ap->phys_info.vel.y;
            translate->z += ap->phys_info.vel.z;
        }
        ap->coll_data.pos_prev.x = translate->x - ap->coll_data.pos_curr.x;
        ap->coll_data.pos_prev.y = translate->y - ap->coll_data.pos_curr.y;
        ap->coll_data.pos_prev.z = translate->z - ap->coll_data.pos_curr.z;

        if ((ap->x2CF_flag_b1) && (func_ovl2_800FC67C(ap->unk_0x2D0) != FALSE))
        {
            Coll_Data *coll_data = &ap->coll_data;

            func_ovl2_800FA7B8(ap->unk_0x2D0, &ap->coll_data.pos_correct);

            translate->x += coll_data->pos_correct.x;
            translate->y += coll_data->pos_correct.y;
            translate->z += coll_data->pos_correct.z;
        }

        else if ((ap->ground_or_air == ground) && (ap->coll_data.ground_line_id != -1) && (ap->coll_data.ground_line_id != -2) && (func_ovl2_800FC67C(ap->coll_data.ground_line_id) != FALSE))
        {
            func_ovl2_800FA7B8(ap->coll_data.ground_line_id, &ap->coll_data.pos_correct);

            translate->x += ap->coll_data.pos_correct.x;
            translate->y += ap->coll_data.pos_correct.y;
            translate->z += ap->coll_data.pos_correct.z;
        }
        else
        {
            ap->coll_data.pos_correct.z = 0.0F;
            ap->coll_data.pos_correct.y = 0.0F;
            ap->coll_data.pos_correct.x = 0.0F;
        }

        if ((translate->y < Ground_Info->blastzone_bottom) || (Ground_Info->blastzone_right < translate->x) || (translate->x < Ground_Info->blastzone_left) || (Ground_Info->blastzone_top < translate->y))
        {
            if ((ap->cb_destroy == NULL) || (ap->cb_destroy(article_gobj) != FALSE))
            {
                func_ovl3_801728D4(article_gobj);
                return;
            }
        }
        if (ap->cb_coll != NULL)
        {
            ap->coll_data.unk_0x54 = ap->coll_data.unk_0x56;
            ap->coll_data.unk_0x56 = 0U;
            ap->coll_data.unk_0x64 = 0;
            ap->coll_data.coll_type = 0;
            ap->coll_data.unk_0x58 = 0;

            if (ap->cb_coll(article_gobj) != FALSE)
            {
                func_ovl3_801728D4(article_gobj);
                return;
            }
        }
        func_ovl3_8016F280(article_gobj);
        func_ovl3_8016F3D4(article_gobj);
    }
    func_ovl3_801713B0(article_gobj);
}

void func_ovl3_8016F930(Article_Hit *at_hit, GObj *victim_gobj, s32 hitbox_type, s32 arg3)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(at_hit->hit_targets); i++)
    {
        if (victim_gobj == at_hit->hit_targets[i].victim_gobj) // Run this if the victim we're checking has already been hit
        {
            switch (hitbox_type)
            {
            case gmHitCollision_Type_Hurt:
                at_hit->hit_targets[i].victim_flags.flags_b0 = TRUE;
                break;

            case gmHitCollision_Type_Shield:
                at_hit->hit_targets[i].victim_flags.flags_b1 = TRUE;
                break;

            case gmHitCollision_Type_Unk:
                at_hit->hit_targets[i].victim_flags.flags_b1 = TRUE;
                at_hit->hit_targets[i].victim_flags.timer_rehit = ARTICLE_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Type_Reflect:
                at_hit->hit_targets[i].victim_flags.flags_b2 = TRUE;
                at_hit->hit_targets[i].victim_flags.timer_rehit = ARTICLE_REHIT_TIME_DEFAULT;
                break;

            case gmHitCollision_Type_Hit:
                at_hit->hit_targets[i].victim_flags.flags_b456 = arg3;
                break;

            case gmHitCollision_Type_ArticleHurt:
                at_hit->hit_targets[i].victim_flags.flags_b0 = TRUE;
                at_hit->hit_targets[i].victim_flags.timer_rehit = ARTICLE_REHIT_TIME_DEFAULT;
                break;

            default: break;
            }
            break;
        }
    }
    if (i == ARRAY_COUNT(at_hit->hit_targets)) // Check if all victim slots have been filled
    {
        for (i = 0; i < ARRAY_COUNT(at_hit->hit_targets); i++) // Reset hit count and increment until there is an empty slot
        {
            if (at_hit->hit_targets[i].victim_gobj == NULL) break;
        }

        if (i == ARRAY_COUNT(at_hit->hit_targets)) i = 0; // Reset hit count again if all victim slots are full

        at_hit->hit_targets[i].victim_gobj = victim_gobj; // Store victim's pointer to slot

        switch (hitbox_type)
        {
        case gmHitCollision_Type_Hurt:
            at_hit->hit_targets[i].victim_flags.flags_b0 = TRUE;
            break;

        case gmHitCollision_Type_Shield:
            at_hit->hit_targets[i].victim_flags.flags_b1 = TRUE;
            break;

        case gmHitCollision_Type_Unk:
            at_hit->hit_targets[i].victim_flags.flags_b1 = TRUE;
            at_hit->hit_targets[i].victim_flags.timer_rehit = ARTICLE_REHIT_TIME_DEFAULT;
            break;

        case gmHitCollision_Type_Reflect:
            at_hit->hit_targets[i].victim_flags.flags_b2 = TRUE;
            at_hit->hit_targets[i].victim_flags.timer_rehit = ARTICLE_REHIT_TIME_DEFAULT;
            break;


        case gmHitCollision_Type_Hit:
            at_hit->hit_targets[i].victim_flags.flags_b456 = arg3;
            break;

        case gmHitCollision_Type_ArticleHurt:
            at_hit->hit_targets[i].victim_flags.flags_b0 = TRUE;
            at_hit->hit_targets[i].victim_flags.timer_rehit = ARTICLE_REHIT_TIME_DEFAULT;
            break;

        default: break;
        }
    }
}

void func_ovl3_8016FB18(Fighter_Struct *fp, Fighter_Hit *ft_hit, Article_Struct *ap, Article_Hurt *arg3, GObj *fighter_gobj, GObj *article_gobj)
{
    s32 damage;
    f32 temp_f0;
    Vec3f sp4C;

    func_ovl2_800E26BC(fp, ft_hit->unk_0x4, article_gobj, 0, 0, 0);

    damage = ft_hit->damage;

    if (fp->unk_0x7B0 < damage)
    {
        fp->unk_0x7B0 = damage;
    }
    if (arg3->hitstatus == gmHitCollision_Status_Normal)
    {
        ap->damage_taken += damage;

        if (ap->unk_0x290 < damage)
        {
            ap->unk_0x290 = damage;
            ap->unk_0x29C = ft_hit->unk_0x28;
            ap->unk_0x2A0 = ft_hit->unk_0x10;

            ap->lr_hit = (JObjGetStruct(article_gobj)->translate.x < JObjGetStruct(fighter_gobj)->translate.x) ? RIGHT : LEFT;

            ap->damage_gobj = fighter_gobj;
            ap->damage_team = fp->team;
            ap->damage_port = fp->player_id;
            ap->damage_player_number = fp->player_number;
            ap->unk_0x70 = fp->offset_hit_type;
            ap->damage_display_state = fp->display_state;
        }
        if (ap->x2D2_flag_b4)
        {
            temp_f0 = func_ovl2_800E9D78(ap->unk_0x1C, ap->damage_taken, damage, ft_hit->unk_0x30, ft_hit->unk_0x2C, ft_hit->unk_0x34, 1.0F, fp->offset_hit_type, (s32)ap->unk_0x16);

            if (ap->unk_0x294 < temp_f0)
            {
                ap->unk_0x294 = temp_f0;
            }
        }
        func_ovl2_800F0AF8(&sp4C, ft_hit, arg3, article_gobj);

        switch (ft_hit->unk_0x10)
        {
        case 1:
            func_ovl2_800FE2F4(&sp4C, ft_hit->damage);
            break;
        case 2:
            func_ovl2_800FE4EC(&sp4C, ft_hit->damage);
            break;
        case 4:
            func_ovl2_80100ACC(&sp4C);
            break;
        case 3:
            func_ovl2_800FE6E4(&sp4C, ft_hit->damage, func_ovl2_800F0FC0(fp, ft_hit));
            break;
        default:
            func_ovl2_800FDC04(&sp4C, fp->player_id, ft_hit->damage, 0);
            break;
        }
    }
    func_ovl2_800E2C24(fp, ft_hit);
}

void func_ovl3_8016FD4C(Article_Struct *this_ap, Article_Hit *this_hit, s32 this_hit_id, Article_Struct *victim_ap, Article_Hit *victim_hit, s32 victim_hit_id, GObj *this_gobj, GObj *victim_gobj)
{
    s32 victim_hit_damage;
    s32 this_hit_damage;
    Vec3f sp2C;
    s32 victim_hit_priority;
    s32 this_hit_priority;

    victim_hit_damage = func_ovl3_801727F4(victim_ap);
    this_hit_damage = func_ovl3_801727F4(this_ap);

    func_ovl2_800F0EFC(&sp2C, victim_hit, victim_hit_id, this_hit, this_hit_id);

    this_hit_priority = this_hit->priority;
    victim_hit_priority = victim_hit->priority;

    if (this_hit_priority >= victim_hit->priority)
    {
        func_ovl3_8016F930(victim_hit, this_gobj, gmHitCollision_Type_Hit, 0);

        if (victim_ap->hit_attack_damage < victim_hit_damage)
        {
            victim_ap->hit_attack_damage = victim_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, victim_hit_damage);

        this_hit_priority = this_hit->priority;
        victim_hit_priority = victim_hit->priority;
    }
    if (victim_hit_priority >= this_hit_priority)
    {
        func_ovl3_8016F930(this_hit, victim_gobj, gmHitCollision_Type_Hit, 0);

        if (this_ap->hit_attack_damage < this_hit_damage)
        {
            this_ap->hit_attack_damage = this_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, this_hit_damage);
    }
}

void func_ovl3_8016FE4C(Item_Struct *ip, Item_Hit *it_hit, s32 it_hit_id, Article_Struct *ap, Article_Hit *at_hit, s32 at_hit_id, GObj *item_gobj, GObj *article_gobj)
{
    s32 it_hit_damage = func_ovl3_80168128(ip);
    s32 at_hit_damage = func_ovl3_801727F4(ap);
    Vec3f sp2C;
    s32 at_hit_priority;
    s32 it_hit_priority;

    func_ovl2_800F0CDC(&sp2C, it_hit, it_hit_id, at_hit, at_hit_id);

    it_hit_priority = it_hit->priority;
    at_hit_priority = at_hit->priority;

    if (it_hit_priority >= at_hit->priority)
    {
        func_ovl3_8016F930(at_hit, item_gobj, gmHitCollision_Type_Hit, 0);

        if (ap->hit_attack_damage < at_hit_damage)
        {
            ap->hit_attack_damage = at_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, at_hit_damage);

        it_hit_priority = it_hit->priority;
        at_hit_priority = at_hit->priority;
    }
    if (at_hit_priority >= it_hit_priority)
    {
        func_ovl3_8016679C(ip, it_hit, article_gobj, gmHitCollision_Type_Hit, 0);

        if (ip->hit_attack_damage < it_hit_damage)
        {
            ip->hit_attack_damage = it_hit_damage;
        }
        func_ovl2_80100BF0(&sp2C, it_hit_damage);
    }
}
