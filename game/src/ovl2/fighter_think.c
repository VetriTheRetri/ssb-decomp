#include "fighter.h"
#include "item.h"
#include "article.h"
#include "ground.h"
#include "gmmatch.h"
#include "gmground.h"
#include "thread6.h"

void func_ovl2_800DF0F0(GObj *fighter_gobj, Fighter_Struct *fp, gmScriptEvent *p_event, u32 ev_kind)
{
    gmScriptPointer *p_goto;
    s32 gfx_id;
    s32 i, j;
    bool32 var_v0;
    Fighter_Hit *ft_hit;
    s32 hit_id;
    s32 group_id;
    u32 sfx_id;
    s32 joint_index;
    Vec3f gfx_offset;
    Vec3f gfx_scatter;
    u32 flag;
    Vec3f hurt_offset;
    Vec3f hurt_size;
    ftCommonAttributes *attributes;
    gmScriptEventDamage *p_damage;
    s32 ft_kind;
    s32 script_index;
    s32 flag2;
    gmScriptEventPlaySFX *plswork;

    switch (ev_kind)
    {
    case gmScriptEvent_Kind_End:
        p_event->p_script = NULL;
        break;

    case gmScriptEvent_Kind_SyncWait:

        p_event->frame_timer += gmScriptEventCast(p_event, gmScriptEventWait)->frames;

        gmScriptEventUpdatePtr(p_event, gmScriptEventWait);
        break;

    case gmScriptEvent_Kind_AsyncWait:

        p_event->frame_timer = gmScriptEventCast(p_event, gmScriptEventWait)->frames - fighter_gobj->anim_frame;

        gmScriptEventUpdatePtr(p_event, gmScriptEventWait);
        break;

    case gmScriptEvent_Kind_FighterHit:
    case gmScriptEvent_Kind_ItemSwingHit:

        if (fp->status_info.pl_kind != Pl_Kind_Result)
        {
            hit_id = gmScriptEventCast(p_event, gmScriptEventCreateHit1)->hit_id;
            ft_hit = &fp->fighter_hit[hit_id];

            if ((ft_hit->update_state == gmHitCollision_UpdateState_Disable) || (ft_hit->interact_mask != gmScriptEventCast(p_event, gmScriptEventCreateHit1)->interact_mask))
            {
                ft_hit->interact_mask = gmScriptEventCast(p_event, gmScriptEventCreateHit1)->interact_mask;
                ft_hit->update_state = gmHitCollision_UpdateState_New;
                fp->is_hit_enable = TRUE;

                for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
                {
                    if ((i != hit_id) && (fp->fighter_hit[i].update_state != gmHitCollision_UpdateState_Disable) && (ft_hit->interact_mask == fp->fighter_hit[i].interact_mask))
                    {
                        for (j = 0; j < ARRAY_COUNT(ft_hit->hit_targets); j++)
                        {
                            ft_hit->hit_targets[j] = fp->fighter_hit[i].hit_targets[j];
                        }
                        break;
                    }
                }
                if (i == ARRAY_COUNT(fp->fighter_hit))
                {
                    func_ovl2_800E853C(fp, hit_id);
                }
            }
            ft_hit->joint_index = func_ovl2_800E86D4(fp, gmScriptEventCast(p_event, gmScriptEventCreateHit1)->joint_index);
            ft_hit->joint = fp->joint[ft_hit->joint_index];
            ft_hit->damage = gmScriptEventCast(p_event, gmScriptEventCreateHit1)->damage;
            ft_hit->clang = gmScriptEventCast(p_event, gmScriptEventCreateHit1)->clang;
            ft_hit->element = gmScriptEventCast(p_event, gmScriptEventCreateHit1)->element;

            gmScriptEventUpdatePtr(p_event, gmScriptEventCreateHit1);

            ft_hit->size = gmScriptEventCast(p_event, gmScriptEventCreateHit2)->size * 0.5F;
            ft_hit->offset.x = gmScriptEventCast(p_event, gmScriptEventCreateHit2)->off_x;

            gmScriptEventUpdatePtr(p_event, gmScriptEventCreateHit2);

            ft_hit->offset.y = gmScriptEventCast(p_event, gmScriptEventCreateHit3)->off_y;
            ft_hit->offset.z = gmScriptEventCast(p_event, gmScriptEventCreateHit3)->off_z;

            gmScriptEventUpdatePtr(p_event, gmScriptEventCreateHit3);

            ft_hit->angle = gmScriptEventCast(p_event, gmScriptEventCreateHit4)->angle;
            ft_hit->knockback_scale = gmScriptEventCast(p_event, gmScriptEventCreateHit4)->knockback_scale;
            ft_hit->knockback_weight = gmScriptEventCast(p_event, gmScriptEventCreateHit4)->knockback_weight;

            ft_hit->is_hit_air = gmScriptEventCast(p_event, gmScriptEventCreateHit4)->is_hit_ground_air & 1;           // Why?
            ft_hit->is_hit_ground = (gmScriptEventCast(p_event, gmScriptEventCreateHit4)->is_hit_ground_air & 2) >> 1; // ???

            gmScriptEventUpdatePtr(p_event, gmScriptEventCreateHit4);

            ft_hit->shield_damage = gmScriptEventCast(p_event, gmScriptEventCreateHit5)->shield_damage;

            ft_hit->sfx_level = gmScriptEventCast(p_event, gmScriptEventCreateHit5)->sfx_level;
            ft_hit->sfx_kind = gmScriptEventCast(p_event, gmScriptEventCreateHit5)->sfx_kind;

            ft_hit->knockback_base = gmScriptEventCast(p_event, gmScriptEventCreateHit5)->knockback_base;

            gmScriptEventUpdatePtr(p_event, gmScriptEventCreateHit5);

            ft_hit->is_itemswing = (ev_kind == gmScriptEvent_Kind_ItemSwingHit) ? TRUE : FALSE;

            ft_hit->attack_id = fp->attack_id;

            ft_hit->flags_hi.halfword = fp->flags_hi.halfword;

            ft_hit->damage = func_ovl2_800EA54C(fp->port_id, ft_hit->damage, ft_hit->attack_id, ft_hit->flags_hi.halfword);
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventCreateHit);

        break;

    case gmScriptEvent_Kind_SetHitOffset:

        hit_id = gmScriptEventCast(p_event, gmScriptEventSetHitOffset1)->hit_id;
        ft_hit = &fp->fighter_hit[hit_id];

        ft_hit->offset.x = gmScriptEventCast(p_event, gmScriptEventSetHitOffset1)->off_x;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitOffset1);

        ft_hit->offset.y = gmScriptEventCast(p_event, gmScriptEventSetHitOffset2)->off_y;
        ft_hit->offset.z = gmScriptEventCast(p_event, gmScriptEventSetHitOffset2)->off_z;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitOffset2);
        break;

    case gmScriptEvent_Kind_SetHitDamage:

        if (fp->status_info.pl_kind != Pl_Kind_Result)
        {
            hit_id = gmScriptEventCast(p_event, gmScriptEventSetHitDamage)->hit_id;

            fp->fighter_hit[hit_id].damage = gmScriptEventCast(p_event, gmScriptEventSetHitDamage)->damage;

            gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitDamage);

            fp->fighter_hit[hit_id].damage = func_ovl2_800EA54C(fp->port_id, fp->fighter_hit[hit_id].damage, fp->fighter_hit[hit_id].attack_id, fp->fighter_hit[hit_id].flags_hi.halfword);
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitDamage);

        break;

    case gmScriptEvent_Kind_SetHitSize:

        hit_id = gmScriptEventCast(p_event, gmScriptEventSetHitSize)->hit_id;

        fp->fighter_hit[hit_id].size = gmScriptEventCast(p_event, gmScriptEventSetHitSize)->size * 0.5F;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitSize);
        break;

    case gmScriptEvent_Kind_SetHitSoundLevel:
        hit_id = gmScriptEventCast(p_event, gmScriptEventSetHitSound)->hit_id;

        fp->fighter_hit[hit_id].sfx_level = gmScriptEventCast(p_event, gmScriptEventSetHitSound)->sfx_level;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitSound);

        break;

    case gmScriptEvent_Kind_ResetHit:
        hit_id = gmScriptEventCast(p_event, gmScriptEventResetHit)->hit_id;

        gmScriptEventUpdatePtr(p_event, gmScriptEventResetHit);

        func_ovl2_800E8668(fighter_gobj, hit_id);
        break;

    case gmScriptEvent_Kind_ClearHitIndex:
        hit_id = gmScriptEventCast(p_event, gmScriptEventClearHitIndex)->hit_id;

        gmScriptEventUpdatePtr(p_event, gmScriptEventClearHitIndex);

        fp->fighter_hit[hit_id].update_state = gmHitCollision_UpdateState_Disable;
        break;

    case gmScriptEvent_Kind_ClearHitAll:
        func_ovl2_800E8518(fighter_gobj);

        gmScriptEventUpdatePtr(p_event, gmScriptEventClearHitAll);
        break;

    case gmScriptEvent_Kind_SetFighterThrow:
        gmScriptEventUpdatePtr(p_event, gmScriptEventSetFighterThrow1);

        fp->fighter_throw = gmScriptEventCast(p_event, gmScriptEventSetFighterThrow2)->fighter_throw;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetFighterThrow2);
        break;

    case gmScriptEvent_Kind_StorePlaySFX:
        if (!(fp->is_playing_sfx))
        {
            fp->p_sfx1 = func_800269C0(gmScriptEventCastUpdate(p_event, gmScriptEventPlaySFX)->sfx_id);

            fp->sfx1_id = (fp->p_sfx1 != NULL) ? fp->p_sfx1->sfx_id : 0;
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventPlaySFX);

        break;

    case gmScriptEvent_Kind_PlaySFX:
        if (!(fp->is_playing_sfx))
        {
            func_800269C0(gmScriptEventCastUpdate(p_event, gmScriptEventPlaySFX)->sfx_id);
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventPlaySFX);

        break;

    case gmScriptEvent_Kind_UnkPlaySFX1:

        if (!(fp->is_playing_sfx))
        {
            func_ovl2_800E8190(fp, gmScriptEventCastUpdate(p_event, gmScriptEventPlaySFX)->sfx_id);
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventPlaySFX);

        break;

    case gmScriptEvent_Kind_UnkPlaySFX2:

        func_ovl2_800E81E4(fp), gmScriptEventUpdatePtr(p_event, gmScriptEventPlaySFX);

        break;

    case gmScriptEvent_Kind_PlayVoice:

        if (!(fp->is_playing_sfx) && (fp->attributes->is_have_voice))
        {
            func_ovl2_800E80F0(fp, gmScriptEventCastUpdate(p_event, gmScriptEventPlaySFX)->sfx_id);
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventPlaySFX);

        break;

    case gmScriptEvent_Kind_UnkPlayVoice:
        if (!(fp->is_playing_sfx) && (fp->attributes->is_have_voice))
        {
            func_ovl2_800E8190(fp, gmScriptEventCastUpdate(p_event, gmScriptEventPlaySFX)->sfx_id);
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventPlaySFX);

        break;

    case gmScriptEvent_Kind_PlaySmashVoice:
        if (!(fp->is_playing_sfx))
        {
            func_ovl2_800E80F0(fp, fp->attributes->smash_sfx[rand_u16_range(ARRAY_COUNT(fp->attributes->smash_sfx))]);

            gmScriptEventUpdatePtr(p_event, gmScriptEventPlaySFX);
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventPlaySFX);

        break;

    case gmScriptEvent_Kind_SetAirJumpAdd:

        fp->ground_or_air = air;

        fp->phys_info.vel_air.z = DObjGetStruct(fighter_gobj)->translate.z = 0.0F;

        fp->jumps_used++;

        gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);

        break;

    case gmScriptEvent_Kind_SetAirJumpMax:

        attributes = fp->attributes;

        fp->ground_or_air = air;

        fp->phys_info.vel_air.z = DObjGetStruct(fighter_gobj)->translate.z = 0.0F;

        fp->jumps_used = attributes->jumps_max;

        gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);

        break;

    case gmScriptEvent_Kind_GFX:
    case gmScriptEvent_Kind_GFXPersist:

        if (!(fp->is_playing_gfx))
        {
            joint_index = func_ovl2_800E86D4(fp, gmScriptEventCast(p_event, gmScriptEventCreateGFX1)->joint_index);
            gfx_id = gmScriptEventCast(p_event, gmScriptEventCreateGFX1)->gfx_id;
            flag = gmScriptEventCast(p_event, gmScriptEventCreateGFX1)->flag;

            gmScriptEventUpdatePtr(p_event, gmScriptEventCreateGFX1);

            gfx_offset.x = gmScriptEventCast(p_event, gmScriptEventCreateGFX2)->off_x;
            gfx_offset.y = gmScriptEventCast(p_event, gmScriptEventCreateGFX2)->off_y;

            gmScriptEventUpdatePtr(p_event, gmScriptEventCreateGFX2);

            gfx_offset.z = gmScriptEventCast(p_event, gmScriptEventCreateGFX3)->off_z;
            gfx_scatter.x = gmScriptEventCast(p_event, gmScriptEventCreateGFX3)->rng_x;

            gmScriptEventUpdatePtr(p_event, gmScriptEventCreateGFX3);

            gfx_scatter.y = gmScriptEventCast(p_event, gmScriptEventCreateGFX4)->rng_y;
            gfx_scatter.z = gmScriptEventCast(p_event, gmScriptEventCreateGFX4)->rng_z;

            gmScriptEventUpdatePtr(p_event, gmScriptEventCreateGFX4);

            func_ovl2_800EABDC(fighter_gobj, gfx_id, joint_index, &gfx_offset, &gfx_scatter, fp->lr, (ev_kind == gmScriptEvent_Kind_GFXPersist) ? TRUE : FALSE, flag);
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventCreateGFX);

        break;

    case gmScriptEvent_Kind_ResetHitStatusAll:
        func_ovl2_800E880C(fighter_gobj, gmScriptEventCast(p_event, gmScriptEventSetHitStatusAll)->hit_status);

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitStatusAll);
        break;

    case gmScriptEvent_Kind_SetHitStatusPart:
        func_ovl2_800E8884(fighter_gobj, func_ovl2_800E86D4(fp, gmScriptEventCast(p_event, gmScriptEventSetHitStatusPart)->joint_index), gmScriptEventCast(p_event, gmScriptEventSetHitStatusPart)->hit_status);

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitStatusPart);
        break;

    case gmScriptEvent_Kind_SetHitStatusAll:
        func_ovl2_800E8A24(fighter_gobj, gmScriptEventCast(p_event, gmScriptEventSetHitStatusAll)->hit_status);

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitStatusAll);
        break;

    case gmScriptEvent_Kind_ResetHurtAll:
        func_ovl2_800E8B00(fighter_gobj);

        gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);
        break;

    case gmScriptEvent_Kind_SetHurtPart:
        joint_index = func_ovl2_800E86D4(fp, gmScriptEventCast(p_event, gmScriptEventSetHurtPart1)->joint_index);

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHurtPart1);

        hurt_offset.x = gmScriptEventCast(p_event, gmScriptEventSetHurtPart2)->off_x;
        hurt_offset.y = gmScriptEventCast(p_event, gmScriptEventSetHurtPart2)->off_y;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHurtPart2);

        hurt_offset.z = gmScriptEventCast(p_event, gmScriptEventSetHurtPart3)->off_z;
        hurt_size.x = gmScriptEventCast(p_event, gmScriptEventSetHurtPart3)->size_x;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHurtPart3);

        hurt_size.y = gmScriptEventCast(p_event, gmScriptEventSetHurtPart4)->size_y;
        hurt_size.z = gmScriptEventCast(p_event, gmScriptEventSetHurtPart4)->size_z;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHurtPart4);

        func_ovl2_800E8BC8(fighter_gobj, joint_index, &hurt_offset, &hurt_size);
        break;

    case gmScriptEvent_Kind_LoopBegin:

        p_event->p_goto[p_event->script_index] = (void*) ((uintptr_t)p_event->p_script + sizeof(gmScriptEventLoopBegin));

        p_event->script_index++;

        p_event->loop_count[p_event->script_index++ - 1] = gmScriptEventCast(p_event, gmScriptEventLoopBegin)->loop_count, gmScriptEventUpdatePtr(p_event, gmScriptEventLoopBegin);

        break;

    case gmScriptEvent_Kind_LoopEnd:

        if (--p_event->loop_count[p_event->script_index - 2] != 0)
        {
            p_event->p_script = p_event->p_goto[p_event->script_index - 2];
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventDefault), p_event->script_index -= 2; // Seems fake, but also impossible to match otherwise???

        break;

    case gmScriptEvent_Kind_Subroutine:

        gmScriptEventUpdatePtr(p_event, gmScriptEventSubroutine1);

        p_event->p_goto[p_event->script_index] = (void*) ((uintptr_t)p_event->p_script + sizeof(gmScriptEventSubroutine2));

        p_event->script_index++;

        p_event->p_script = gmScriptEventCast(p_event, gmScriptEventSubroutine2)->p_goto;

        break;

    case gmScriptEvent_Kind_SubroutineThrown:
        if (fp->throw_gobj != NULL)
        {
            ft_kind = fp->throw_ft_kind;

            gmScriptEventUpdatePtr(p_event, gmScriptEventDamageUnk1);

            p_damage = gmScriptEventCast(p_event, gmScriptEventDamageUnk2)->p_subroutine;

            if (p_damage->p_script[fp->status_vars.common.damage.script_index][ft_kind] != NULL)
            {
                p_event->p_goto[p_event->script_index] = (void*) ((uintptr_t)p_event->p_script + sizeof(gmScriptEventDamageUnk2));

                p_event->script_index++;

                p_event->p_script = p_damage->p_script[fp->status_vars.common.damage.script_index][ft_kind];
            }
            else gmScriptEventUpdatePtr(p_event, gmScriptEventDamageUnk2);
        }
        else gmScriptEventUpdatePtr(p_event, gmScriptEventDamageUnk);

        break;

    case gmScriptEvent_Kind_Return:

        p_event->p_script = p_event->p_goto[--p_event->script_index];
        break;

    case gmScriptEvent_Kind_Goto:
        gmScriptEventUpdatePtr(p_event, gmScriptEventGoto1);

        p_event->p_script = gmScriptEventCast(p_event, gmScriptEventGoto2)->p_goto;
        break;

    case gmScriptEvent_Kind_SetParallelScript:
        gmScriptEventUpdatePtr(p_event, gmScriptEventParallel1);

        if (fp->script_event[0][1].p_script == NULL)
        {
            fp->script_event[0][1].p_script = fp->script_event[1][1].p_script = gmScriptEventCast(p_event, gmScriptEventParallel2)->p_goto;

            fp->script_event[0][1].frame_timer = fp->script_event[1][1].frame_timer = DObjGetStruct(fighter_gobj)->unk_dobj_0x78 - fighter_gobj->anim_frame;

            fp->script_event[0][1].script_index = fp->script_event[1][1].script_index = 0;
        }
        gmScriptEventUpdatePtr(p_event, gmScriptEventParallel2);

        break;

    case gmScriptEvent_Kind_ScriptPause:
        gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);

        p_event->frame_timer = (f32)FLOAT_MAX;
        break;

    case gmScriptEvent_Kind_SetModelPart:
        func_ovl2_800E8C70(fighter_gobj, func_ovl2_800E86D4(fp, gmScriptEventCast(p_event, gmScriptEventSetModelPart)->joint_index), gmScriptEventCast(p_event, gmScriptEventSetModelPart)->mode);

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetModelPart);
        break;

    case gmScriptEvent_Kind_Unk10:
        func_ovl2_800E8ECC(fighter_gobj);
        gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);

        break;

    case gmScriptEvent_Kind_Unk11:
        func_ovl2_800E90F8(fighter_gobj);
        gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);

        break;

    case gmScriptEvent_Kind_SetTexturePart:

        func_ovl2_800E962C(fighter_gobj, gmScriptEventCast(p_event, gmScriptEventSetTexturePart)->obj_index, gmScriptEventCast(p_event, gmScriptEventSetTexturePart)->frame);

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetTexturePart);

        break;

    case gmScriptEvent_Kind_SetColAnim:
        func_ovl2_800E9814(fighter_gobj, gmScriptEventCast(p_event, gmScriptEventSetColAnim)->colanim_id, gmScriptEventCast(p_event, gmScriptEventSetColAnim)->length);

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetColAnim);

        break;

    case gmScriptEvent_Kind_ResetColAnim:
        func_ovl2_800E98D4(fighter_gobj);
        gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);

        break;

    case gmScriptEvent_Kind_SetFlag0:
        fp->command_vars.flags.flag0 = gmScriptEventCast(p_event, gmScriptEventSetFlag)->flag;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetFlag);
        break;

    case gmScriptEvent_Kind_SetFlag1:
        fp->command_vars.flags.flag1 = gmScriptEventCast(p_event, gmScriptEventSetFlag)->flag;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetFlag);
        break;

    case gmScriptEvent_Kind_SetFlag2:
        fp->command_vars.flags.flag2 = gmScriptEventCast(p_event, gmScriptEventSetFlag)->flag;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetFlag);
        break;

    case gmScriptEvent_Kind_SetFlag3:
        fp->command_vars.flags.flag3 = gmScriptEventCast(p_event, gmScriptEventSetFlag)->flag;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetFlag);
        break;


    case gmScriptEvent_Kind_SlopeContour:
        flag2 = fp->slope_contour;

        fp->slope_contour = gmScriptEventCastUpdate(p_event, gmScriptEventSlopeContour)->mode;

        if (!(flag2 & fp->slope_contour & 4))
        {
            DObjGetStruct(fighter_gobj)->rotate.x = 0.0F;
        }
        break;

    case gmScriptEvent_Kind_Unk14:
        fp->x190_flag_b6 = gmScriptEventCast(p_event, gmScriptEventUnkFlag)->flag;
        gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);
        return;


    case gmScriptEvent_Kind_AfterImage:
        fp->afterimage.is_itemswing = gmScriptEventCast(p_event, gmScriptEventAfterImage)->is_itemswing;
        fp->afterimage.render_state = gmScriptEventCast(p_event, gmScriptEventAfterImage)->render_state;

        gmScriptEventUpdatePtr(p_event, gmScriptEventAfterImage);
        break;

    case gmScriptEvent_Kind_Unk15:
        if (fp->status_info.pl_kind != Pl_Kind_Result)
        {
            func_ovl2_800E806C(fp, gmScriptEventCast(p_event, gmScriptEventUnk31)->value2, gmScriptEventCast(p_event, gmScriptEventUnk31)->value1);
        }
        gmScriptEventUpdatePtr(p_event, gmScriptEventUnk31);

        break;

    case gmScriptEvent_Kind_Unk16:
        if (fp->status_info.pl_kind != Pl_Kind_Result)
        {
            func_ovl2_80115630(fp->port_id, gmScriptEventCast(p_event, gmScriptEventUnk32)->value1);
        }
        gmScriptEventUpdatePtr(p_event, gmScriptEventUnk32);

        break;
    }
}

void func_ovl2_800E02A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    gmScriptEvent *p_event;
    u32 ev_kind;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->script_event); i++)
    {
        p_event = &fp->script_event[0][i];

        if (p_event->p_script != NULL)
        {
            if (p_event->frame_timer != (f32)FLOAT_MAX)
            {
                p_event->frame_timer -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;
            }
        loop:
            if (p_event->p_script != NULL)
            {
                if (p_event->frame_timer == (f32)FLOAT_MAX)
                {
                    if ((DObjGetStruct(fighter_gobj)->unk_dobj_0x78 <= fighter_gobj->anim_frame)) continue;

                    else p_event->frame_timer = -fighter_gobj->anim_frame;
                }
                else if (p_event->frame_timer > 0.0F) continue;

                ev_kind = gmScriptEventCast(p_event, gmScriptEventCreateGFX1)->opcode;

                if (((ev_kind == gmScriptEvent_Kind_GFX) || (ev_kind == gmScriptEvent_Kind_GFXPersist)) && (fp->x191_flag_b0))
                {
                    gmScriptEventUpdatePtr(p_event, gmScriptEventCreateGFX);
                }
                else func_ovl2_800DF0F0(fighter_gobj, fp, p_event, ev_kind);

                goto loop;
            }
        }
    }
    if (!fp->x191_flag_b0)
    {
        for (i = 0; i < ARRAY_COUNT(fp->script_event); i++)
        {
            fp->script_event[1][i] = fp->script_event[0][i];
        }
    }
}

// Fast Forward script?
void func_ovl2_800E02A8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    gmScriptEvent *p_event;
    u32 ev_kind;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->script_event); i++)
    {
        p_event = &fp->script_event[0][i];

        if (p_event->p_script != NULL)
        {
            if (p_event->frame_timer != (f32)FLOAT_MAX)
            {
                p_event->frame_timer -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;
            }
        loop:
            if (p_event->p_script != NULL)
            {
                if (p_event->frame_timer == (f32)FLOAT_MAX)
                {
                    if ((DObjGetStruct(fighter_gobj)->unk_dobj_0x78 <= fighter_gobj->anim_frame)) continue;

                    else p_event->frame_timer = -fighter_gobj->anim_frame;
                }
                else if (p_event->frame_timer > 0.0F) continue;

                ev_kind = gmScriptEventCast(p_event, gmScriptEventDefault)->opcode;

                switch (ev_kind)
                {
                case gmScriptEvent_Kind_ClearHitIndex:
                case gmScriptEvent_Kind_ClearHitAll:
                case gmScriptEvent_Kind_SetHitDamage:
                case gmScriptEvent_Kind_SetHitSize:
                case gmScriptEvent_Kind_SetHitSoundLevel:
                case gmScriptEvent_Kind_ResetHit:
                case gmScriptEvent_Kind_PlaySFX:
                case gmScriptEvent_Kind_UnkPlaySFX1:
                case gmScriptEvent_Kind_UnkPlaySFX2:
                case gmScriptEvent_Kind_PlayVoice:
                case gmScriptEvent_Kind_UnkPlayVoice:
                case gmScriptEvent_Kind_StorePlaySFX:
                case gmScriptEvent_Kind_PlaySmashVoice:
                case gmScriptEvent_Kind_SetFlag0:
                case gmScriptEvent_Kind_SetFlag1:
                case gmScriptEvent_Kind_SetFlag2:
                case gmScriptEvent_Kind_SetAirJumpAdd:
                case gmScriptEvent_Kind_SetAirJumpMax:
                case gmScriptEvent_Kind_SetColAnim:
                case gmScriptEvent_Kind_ResetColAnim:
                case gmScriptEvent_Kind_Unk15:
                case gmScriptEvent_Kind_Unk16:
                case gmScriptEvent_Kind_AfterImage:
                    gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);
                    break;

                case gmScriptEvent_Kind_GFX:
                case gmScriptEvent_Kind_GFXPersist:
                    gmScriptEventUpdatePtr(p_event, gmScriptEventCreateGFX);
                    break;

                case gmScriptEvent_Kind_FighterHit:
                case gmScriptEvent_Kind_ItemSwingHit:
                    gmScriptEventUpdatePtr(p_event, gmScriptEventCreateHit);
                    break;

                case gmScriptEvent_Kind_SetHitOffset:
                    gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitOffset);
                    break;

                default:
                    func_ovl2_800DF0F0(fighter_gobj, fp, p_event, ev_kind);
                    break;
                }
                goto loop;
            }
        }
    }
    for (i = 0; i < ARRAY_COUNT(fp->script_event); i++)
    {
        fp->script_event[1][i] = fp->script_event[0][i];
    }
}

void func_ovl2_800E0654(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    gmScriptEvent *p_event;
    u32 ev_kind;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(fp->script_event); i++)
    {
        p_event = &fp->script_event[1][i];

        if (p_event->p_script != NULL)
        {
            if (p_event->frame_timer != (f32)FLOAT_MAX)
            {
                p_event->frame_timer -= DObjGetStruct(fighter_gobj)->unk_dobj_0x78;
            }
        loop:
            if (p_event->p_script != NULL)
            {
                if (p_event->frame_timer == (f32)FLOAT_MAX)
                {
                    if ((DObjGetStruct(fighter_gobj)->unk_dobj_0x78 <= fighter_gobj->anim_frame)) continue;

                    else p_event->frame_timer = -fighter_gobj->anim_frame;
                }
                else if (p_event->frame_timer > 0.0F) continue;

                ev_kind = gmScriptEventCast(p_event, gmScriptEventDefault)->opcode;

                switch (ev_kind)
                {
                case gmScriptEvent_Kind_End:
                case gmScriptEvent_Kind_SyncWait:
                case gmScriptEvent_Kind_AsyncWait:
                case gmScriptEvent_Kind_SubroutineThrown:
                case gmScriptEvent_Kind_LoopBegin:
                case gmScriptEvent_Kind_LoopEnd:
                case gmScriptEvent_Kind_Subroutine:
                case gmScriptEvent_Kind_Return:
                case gmScriptEvent_Kind_Goto:
                case gmScriptEvent_Kind_ScriptPause:
                case gmScriptEvent_Kind_GFX:
                case gmScriptEvent_Kind_GFXPersist:
                    func_ovl2_800DF0F0(fighter_gobj, fp, p_event, ev_kind);
                    break;

                case gmScriptEvent_Kind_FighterHit:
                case gmScriptEvent_Kind_ItemSwingHit:
                    gmScriptEventUpdatePtr(p_event, gmScriptEventCreateHit);
                    break;

                case gmScriptEvent_Kind_SetHitOffset:
                case gmScriptEvent_Kind_SetFighterThrow:
                case gmScriptEvent_Kind_SetParallelScript:
                    gmScriptEventUpdatePtr(p_event, gmScriptEventDouble);
                    break;

                case gmScriptEvent_Kind_SetHurtPart:
                    gmScriptEventUpdatePtr(p_event, gmScriptEventSetHurtPart);
                    break;

                default:
                    gmScriptEventUpdatePtr(p_event, gmScriptEventDefault);
                    break;
                }
                goto loop;
            }
        }
    }
}

void func_ovl2_800E07D4(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->anim_flags.flags.is_use_transn_joint)
    {
        fp->anim_vel = fp->joint[1]->translate;
    }
    func_ovl2_800E82B8(fighter_gobj);
    func_ovl2_800EB648(fp->joint[0]);
}

void ftAnim_Update(GObj *fighter_gobj)
{
    func_ovl2_800E07D4(fighter_gobj);
    func_ovl2_800E02A8(fighter_gobj);
}

void func_ovl2_800E0858(GObj *fighter_gobj)
{
    func_ovl2_800E07D4(fighter_gobj);
    func_ovl2_800E0478(fighter_gobj);
}

bool32 func_ovl2_800E0880(Color_Overlay *colanim, GObj *fighter_gobj, bool32 is_playing_sfx, bool32 is_playing_gfx)
{
    s32 i, j;
    Fighter_Struct *fp;
    Color_Script *cs;
    void *p_script;
    s32 gfx_id;
    s32 joint_index;
    u32 flag;
    gmColorEventDefault *def;
    Vec3f gfx_offset;
    Vec3f gfx_scatter;
    u32 ev_kind;
    s32 blend_frames;

    for (i = 0; i < ARRAY_COUNT(colanim->cs); i++)
    {
        cs = &colanim->cs[i]; // What's the point bruh

        if ((colanim->cs[i].p_script != NULL) && (colanim->cs[i].color_event_timer != 0))
        {
            colanim->cs[i].color_event_timer--;
        }
        while ((colanim->cs[i].p_script != NULL) && (cs->color_event_timer == 0))
        {
            ev_kind = gmColorEventCast(colanim->cs[i].p_script, gmColorEventDefault)->opcode;

            switch (ev_kind)
            {
            case gmColorEvent_Kind_End:
                for (j = 0; j < ARRAY_COUNT(colanim->cs); j++)
                {
                    if ((j != i) && (colanim->cs[j].p_script != NULL)) break;
                }

                if (j == ARRAY_COUNT(colanim->cs))
                {
                    return TRUE;
                }
                else colanim->cs[i].p_script = NULL;

                break;

            case gmColorEvent_Kind_Wait:
                colanim->cs[i].color_event_timer = gmColorEventCast(colanim->cs[i].p_script, gmColorEventDefault)->value1, gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventDefault);

                break;

            case gmColorEvent_Kind_Goto:
                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventGoto1);

                colanim->cs[i].p_script = gmColorEventCast(colanim->cs[i].p_script, gmColorEventGoto2)->p_goto;

                break;

            case gmColorEvent_Kind_LoopBegin:
                colanim->cs[i].p_subroutine[colanim->cs[i].script_index++] = (void*) ((uintptr_t)colanim->cs[i].p_script + sizeof(gmColorEventLoopBegin));
                colanim->cs[i].p_subroutine[colanim->cs[i].script_index++] = gmColorEventCast(colanim->cs[i].p_script, gmColorEventLoopBegin)->loop_count, gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventLoopBegin);

                break;

            case gmColorEvent_Kind_LoopEnd:
                if (--colanim->cs[i].loop_count[colanim->cs[i].script_index - 2] != 0)
                {
                    colanim->cs[i].p_script = colanim->cs[i].p_subroutine[colanim->cs[i].script_index - 2];
                }
                else gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventDefault), colanim->cs[i].script_index -= 2;

                break;

            case gmColorEvent_Kind_Subroutine:
                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventSubroutine1);

                colanim->cs[i].p_subroutine[colanim->cs[i].script_index++] = (void*) ((uintptr_t)colanim->cs[i].p_script + sizeof(gmColorEventSubroutine1));

                colanim->cs[i].p_script = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSubroutine2)->p_subroutine;

                break;

            case gmColorEvent_Kind_Return:
                colanim->cs[i].p_script = colanim->cs[i].p_subroutine[--colanim->cs[i].script_index];

                break;

            case gmColorEvent_Kind_SetParallelScript:
                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventParallel1);

                if (colanim->cs[1].p_script == NULL)
                {
                    colanim->cs[1].p_script = gmColorEventCast(colanim->cs[i].p_script, gmColorEventParallel2)->p_script;
                    colanim->cs[1].color_event_timer = 0;
                    colanim->cs[1].script_index = 0;
                }
                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventParallel2);

                break;

            case gmColorEvent_Kind_ToggleColorOff:

                colanim->is_use_color1 = colanim->is_use_color2 = colanim->unk_ca_0x60_b34 = 0;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventDefault);

                break;

            case gmColorEvent_Kind_SetColor1:
                colanim->is_use_color1 = TRUE;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventSetRGBA1);

                colanim->color1.r = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetRGBA2)->r;
                colanim->color1.g = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetRGBA2)->g;
                colanim->color1.b = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetRGBA2)->b;
                colanim->color1.a = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetRGBA2)->a;

                colanim->color1.ir = colanim->color1.ig = colanim->color1.ib = colanim->color1.ia = 0;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventSetRGBA2);

                break;

            case gmColorEvent_Kind_SetColor2:
                colanim->is_use_color2 = TRUE;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventSetRGBA1);

                colanim->color2.r = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetRGBA2)->r;
                colanim->color2.g = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetRGBA2)->g;
                colanim->color2.b = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetRGBA2)->b;
                colanim->color2.a = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetRGBA2)->a;

                colanim->color2.ir = colanim->color2.ig = colanim->color2.ib = colanim->color2.ia = 0;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventSetRGBA2);

                break;

            case gmColorEvent_Kind_BlendColor1:
                blend_frames = gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA1)->blend_frames;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventBlendRGBA1);

                colanim->color1.ir = (s32)(gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA2)->r - colanim->color1.r) / blend_frames;
                colanim->color1.ig = (s32)(gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA2)->g - colanim->color1.g) / blend_frames;
                colanim->color1.ib = (s32)(gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA2)->b - colanim->color1.b) / blend_frames;
                colanim->color1.ia = (s32)(gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA2)->a - colanim->color1.a) / blend_frames;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventBlendRGBA2);

                break;

            case gmColorEvent_Kind_BlendColor2:
                blend_frames = gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA1)->blend_frames;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventBlendRGBA1);

                colanim->color2.ir = (s32)(gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA2)->r - colanim->color2.r) / blend_frames;
                colanim->color2.ig = (s32)(gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA2)->g - colanim->color2.g) / blend_frames;
                colanim->color2.ib = (s32)(gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA2)->b - colanim->color2.b) / blend_frames;
                colanim->color2.ia = (s32)(gmColorEventCast(colanim->cs[i].p_script, gmColorEventBlendRGBA2)->a - colanim->color2.a) / blend_frames;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventBlendRGBA2);

                break;

            case gmColorEvent_Kind_GFX:
            case gmColorEvent_Kind_GFXPersist:
                if (is_playing_gfx == FALSE)
                {
                    fp = FighterGetStruct(fighter_gobj);

                    joint_index = func_ovl2_800E86D4(fp, gmColorEventCast(colanim->cs[i].p_script, gmColorEventCreateGFX1)->joint_index);
                    gfx_id = gmColorEventCast(colanim->cs[i].p_script, gmColorEventCreateGFX1)->gfx_id;
                    flag = gmColorEventCast(colanim->cs[i].p_script, gmColorEventCreateGFX1)->flag;

                    gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventCreateGFX1);

                    gfx_offset.x = gmColorEventCast(colanim->cs[i].p_script, gmColorEventCreateGFX2)->off_x;
                    gfx_offset.y = gmColorEventCast(colanim->cs[i].p_script, gmColorEventCreateGFX2)->off_y;

                    gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventCreateGFX2);

                    gfx_offset.z = gmColorEventCast(colanim->cs[i].p_script, gmColorEventCreateGFX3)->off_z;
                    gfx_scatter.x = gmColorEventCast(colanim->cs[i].p_script, gmColorEventCreateGFX3)->rng_x;

                    gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventCreateGFX3);

                    gfx_scatter.y = gmColorEventCast(colanim->cs[i].p_script, gmColorEventCreateGFX4)->rng_y;
                    gfx_scatter.z = gmColorEventCast(colanim->cs[i].p_script, gmColorEventCreateGFX4)->rng_z;

                    gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventCreateGFX4);

                    func_ovl2_800EABDC(fighter_gobj, gfx_id, joint_index, &gfx_offset, &gfx_scatter, fp->lr, (ev_kind == gmColorEvent_Kind_GFXPersist) ? TRUE : FALSE, flag);
                }
                else gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventCreateGFX);

                break;

            case gmColorEvent_Kind_SetLight:
                colanim->is_use_light = TRUE;

                colanim->light_angle1 = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetLight)->light1;
                colanim->light_angle2 = gmColorEventCast(colanim->cs[i].p_script, gmColorEventSetLight)->light2;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventSetLight);

                break;

            case gmColorEvent_Kind_ToggleLightOff:
                colanim->is_use_light = FALSE;

                gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventDefault);

                break;

            case gmColorEvent_Kind_PlaySFX:
                if (is_playing_sfx == FALSE)
                {
                    func_800269C0(gmColorEventCastUpdate(colanim->cs[i].p_script, gmColorEventPlaySFX)->sfx_id);
                }
                else gmColorEventUpdatePtr(colanim->cs[i].p_script, gmColorEventDefault);

                break;

            case gmColorEvent_Kind_SetUnk:
                colanim->unk_ca_0x60_b34 = gmColorEventCastUpdate(colanim->cs[i].p_script, gmColorEventDefault)->value1;

                break;

            default:
                break;
            }
        }
    }
    if (colanim->is_use_color1)
    {
        colanim->color1.r += colanim->color1.ir;
        colanim->color1.g += colanim->color1.ig;
        colanim->color1.b += colanim->color1.ib;
        colanim->color1.a += colanim->color1.ia;
    }
    if (colanim->is_use_color2)
    {
        colanim->color2.r += colanim->color2.ir;
        colanim->color2.g += colanim->color2.ig;
        colanim->color2.b += colanim->color2.ib;
        colanim->color2.a += colanim->color2.ia;
    }
    if (colanim->duration != 0)
    {
        colanim->duration--;

        if (colanim->duration == 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void func_ovl2_800E11C8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    while (func_ovl2_800E0880(&fp->colanim, fighter_gobj, fp->is_playing_sfx, fp->is_playing_gfx) != FALSE)
    {
        func_ovl2_800E98D4(fighter_gobj);
    }
}

void func_ovl2_800E1260(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *other_fp;
    ftCommonAttributes *this_attributes;
    ftCommonAttributes *other_attributes;
    gmPlayerInput *pl;
    gmComputerInput *cp;
    gControllerInput *p_controller;
    GObj *other_gobj;
    f32 jostle_dist_x;
    f32 dist_z;
    bool32 is_check_self;
    bool32 is_jostle;
    u16 button_tap_mask;
    u16 button_press;
    u16 button_press_com;
    f32 this_jostle;

    if (!this_fp->x18F_flag_b6)
    {
        this_fp->status_info.status_time_spent++;
    }
    if (!this_fp->x18F_flag_b6)
    {
        this_fp->input.pl.stick_prev.x = this_fp->input.pl.stick_range.x;
        this_fp->input.pl.stick_prev.y = this_fp->input.pl.stick_range.y;

        switch (this_fp->status_info.pl_kind)
        {
        default:
            pl = &this_fp->input.pl;
            break;

        case Pl_Kind_Human:
            p_controller = this_fp->input.p_controller;
            pl = &this_fp->input.pl;

            button_press = p_controller->button_press;

            if (button_press & HAL_BUTTON_R)
            {
                button_press |= (HAL_BUTTON_A | HAL_BUTTON_Z);
            }

            pl->stick_range.x = p_controller->stick_range.x;
            pl->stick_range.y = p_controller->stick_range.y;

            button_tap_mask = (button_press ^ pl->button_hold) & button_press;

            pl->button_tap = (this_fp->hitlag_timer != 0) ? pl->button_tap | button_tap_mask : button_tap_mask;

            button_tap_mask = (button_press ^ pl->button_hold) & pl->button_hold;

            pl->button_tap_prev = (this_fp->hitlag_timer != 0) ? pl->button_tap_prev | button_tap_mask : button_tap_mask;

            pl->button_hold = button_press;

            break;

        case Pl_Kind_CPU:
            func_unkmulti_8013A834(fighter_gobj);
            goto next;

        case Pl_Kind_Intro:
        case Pl_Kind_HowToPlay:
            func_ovl2_80115B10(fighter_gobj);

        next:
            cp = &this_fp->input.cp;
            pl = &this_fp->input.pl;

            button_press_com = this_fp->input.cp.button_inputs;

            if (button_press_com & HAL_BUTTON_R)
            {
                button_press_com |= (HAL_BUTTON_A | HAL_BUTTON_Z);
            }

            pl->stick_range.x = cp->stick_range.x;
            pl->stick_range.y = cp->stick_range.y;

            button_tap_mask = (button_press_com ^ pl->button_hold) & button_press_com;

            pl->button_tap = (this_fp->hitlag_timer != 0) ? pl->button_tap | button_tap_mask : button_tap_mask;

            button_tap_mask = (button_press_com ^ pl->button_hold) & pl->button_hold;

            pl->button_tap_prev = (this_fp->hitlag_timer != 0) ? pl->button_tap_prev | button_tap_mask : button_tap_mask;

            pl->button_hold = button_press_com;

            break;
        }
        if (pl->stick_range.x > GCONTROLLER_RANGE_MAX_I)
        {
            pl->stick_range.x = GCONTROLLER_RANGE_MAX_I;
        }
        if (pl->stick_range.x < -GCONTROLLER_RANGE_MAX_I)
        {
            pl->stick_range.x = -GCONTROLLER_RANGE_MAX_I;
        }
        if (pl->stick_range.y > GCONTROLLER_RANGE_MAX_I)
        {
            pl->stick_range.y = GCONTROLLER_RANGE_MAX_I;
        }
        if (pl->stick_range.y < -GCONTROLLER_RANGE_MAX_I)
        {
            pl->stick_range.y = -GCONTROLLER_RANGE_MAX_I;
        }
        if (Save_Info.unk5E2 & 2)
        {
            pl->stick_range.x *= 0.5F;
            pl->stick_range.y *= 0.5F;
        }
        if (pl->stick_range.x >= 0x14)
        {
            if (pl->stick_prev.x >= 0x14)
            {
                this_fp->tap_stick_x++, this_fp->hold_stick_x++;
            }
            else this_fp->tap_stick_x = this_fp->hold_stick_x = 1;

        }
        else if (pl->stick_range.x <= -0x14)
        {
            if (pl->stick_prev.x <= -0x14)
            {
                this_fp->tap_stick_x++, this_fp->hold_stick_x++;
            }
            else this_fp->tap_stick_x = this_fp->hold_stick_x = 1;

        }
        else this_fp->tap_stick_x = this_fp->hold_stick_x = U8_MAX - 1;

        if (this_fp->tap_stick_x > (U8_MAX - 1))
        {
            this_fp->tap_stick_x = U8_MAX - 1;
        }
        if (this_fp->hold_stick_x > (U8_MAX - 1))
        {
            this_fp->hold_stick_x = U8_MAX - 1;
        }
        if (pl->stick_range.y >= 20)
        {
            if (pl->stick_prev.y >= 20)
            {
                this_fp->tap_stick_y++, this_fp->hold_stick_y++;
            }
            else this_fp->tap_stick_y = this_fp->hold_stick_y = 1;
        }
        else if (pl->stick_range.y <= -20)
        {
            if (pl->stick_prev.y <= -20)
            {
                this_fp->tap_stick_y++, this_fp->hold_stick_y++;
            }
            else this_fp->tap_stick_y = this_fp->hold_stick_y = 1;
        }
        else this_fp->tap_stick_y = this_fp->hold_stick_y = U8_MAX - 1;

        if (this_fp->tap_stick_y > (U8_MAX - 1))
        {
            this_fp->tap_stick_y = U8_MAX - 1;
        }
        if (this_fp->hold_stick_y > (U8_MAX - 1))
        {
            this_fp->hold_stick_y = U8_MAX - 1;
        }
    }
    if (this_fp->time_since_last_z < (U16_MAX + 1))
    {
        this_fp->time_since_last_z++;
    }
    if (this_fp->input.pl.button_tap & this_fp->input.button_mask_z)
    {
        this_fp->time_since_last_z = 0;
    }
    if (this_fp->hitlag_timer != 0)
    {
        this_fp->hitlag_timer--;

        if (this_fp->hitlag_timer == 0)
        {
            this_fp->x192_flag_b6 = FALSE;

            if (this_fp->proc_lagend != NULL)
            {
                this_fp->proc_lagend(fighter_gobj);
            }
        }
    }
    this_fp->x191_flag_b0 = TRUE;

    if (this_fp->hitlag_timer == 0)
    {
        ftAnim_Update(fighter_gobj);
    }
    func_ovl2_800E11C8(fighter_gobj);

    if (this_fp->walldamage_nohit_timer != 0)
    {
        this_fp->walldamage_nohit_timer--;

        if (this_fp->walldamage_nohit_timer == 0)
        {
            this_fp->special_hit_status = (this_fp->invincible_timer != FALSE) ? gmHitCollision_HitStatus_Invincible : gmHitCollision_HitStatus_Normal;

            if (this_fp->colanim.colanim_id == 0xA)
            {
                func_ovl2_800E98D4(fighter_gobj);
            }
        }
    }
    if (this_fp->invincible_timer != 0)
    {
        this_fp->invincible_timer--;

        if ((this_fp->invincible_timer == 0) && (this_fp->walldamage_nohit_timer == 0))
        {
            this_fp->special_hit_status = gmHitCollision_HitStatus_Normal;

            if (this_fp->colanim.colanim_id == 0xA)
            {
                func_ovl2_800E98D4(fighter_gobj);
            }
        }
    }
    if (this_fp->star_invincible_timer != 0)
    {
        this_fp->star_invincible_timer--;

        if (this_fp->star_invincible_timer == 0)
        {
            this_fp->special_status = ftSpecialStatus_Normal;

            if (this_fp->colanim.colanim_id == 0x4A)
            {
                func_ovl2_800E98D4(fighter_gobj);
            }
        }
        else if (this_fp->star_invincible_timer == (ATSTAR_INVINCIBLE_TIME - ATSTAR_WARN_BEGIN_FRAME))
        {
            func_ovl2_800E7B54();
        }
    }
    if (this_fp->damage_heal != 0)
    {
        this_fp->damage_heal--;

        if (this_fp->percent_damage != 0)
        {
            this_fp->percent_damage--;

            func_800269C0(0x112U);

            Match_Info->player_block[this_fp->port_id].stock_damage_all = this_fp->percent_damage;
        }
        if (this_fp->percent_damage == 0)
        {
            this_fp->damage_heal = 0;
        }
        if ((this_fp->damage_heal == 0) && (this_fp->colanim.colanim_id == 9))
        {
            func_ovl2_800E98D4(fighter_gobj);
        }
    }
    if ((this_fp->item_hold != NULL) && (this_fp->status_info.status_id != ftStatus_Common_LightGet) && (ArticleGetStruct(this_fp->item_hold)->at_kind == At_Kind_Hammer))
    {
        func_ovl2_800F36E0(fighter_gobj);
    }
    if (this_fp->shuffle_timer != 0)
    {
        this_fp->shuffle_timer--;

        this_fp->unk_ft_0x272++;

        if (this_fp->unk_ft_0x272 == this_fp->unk_ft_0x273)
        {
            this_fp->unk_ft_0x272 = 0U;
        }
    }
    if (this_fp->proc_gfx != NULL)
    {
        this_fp->proc_gfx(fighter_gobj);
    }
    if (this_fp->hitlag_timer == 0)
    {
        if ((this_fp->unk_0x174 > 1) && !(this_fp->x18F_flag_b6))
        {
            this_fp->unk_0x174--;
        }
        if (this_fp->proc_update != NULL)
        {
            this_fp->proc_update(fighter_gobj);
        }
        if (this_fp->proc_interrupt != NULL)
        {
            this_fp->proc_interrupt(fighter_gobj);
        }
        if (!(this_fp->is_hitstun))
        {
            Match_Info->player_block[this_fp->port_id].combo_damage_foe = 0;
            Match_Info->player_block[this_fp->port_id].combo_count_foe = 0;
        }
        is_jostle = FALSE;

        this_fp->phys_info.vel_jostle_x = this_fp->phys_info.vel_jostle_z = 0.0F;

        if ((this_fp->ground_or_air == ground) && !(this_fp->x18F_flag_b4))
        {
            other_gobj = gOMObjCommonLinks[GObjLinkIndex_Fighter];

            is_check_self = FALSE;

            while (other_gobj != NULL)
            {

                other_fp = FighterGetStruct(other_gobj);

                if ((fighter_gobj != other_gobj) && (other_fp->capture_gobj == NULL))
                {
                    if ((other_fp->ground_or_air == ground) && (this_fp->coll_data.ground_line_id == other_fp->coll_data.ground_line_id))
                    {
                        this_attributes = this_fp->attributes;
                        other_attributes = other_fp->attributes;

                        this_jostle = this_fp->attributes->jostle_width;

                        jostle_dist_x = (DObjGetStruct(fighter_gobj)->translate.x + (this_attributes->jostle_x * this_fp->lr)) - (DObjGetStruct(other_gobj)->translate.x + (other_attributes->jostle_x * other_fp->lr));

                        if (ABS(jostle_dist_x) < (this_jostle + other_attributes->jostle_width))
                        {
                            is_jostle = TRUE;

                            if (jostle_dist_x == 0.0F)
                            {
                                this_fp->phys_info.vel_jostle_x += (6.75F * ((is_check_self != FALSE) ? -1 : 1));
                            }
                            else this_fp->phys_info.vel_jostle_x += (6.75F * ((jostle_dist_x < 0.0F) ? -1 : 1));

                            dist_z = DObjGetStruct(fighter_gobj)->translate.z - DObjGetStruct(other_gobj)->translate.z;

                            if (dist_z == 0.0F)
                            {
                                if (jostle_dist_x == 0.0F)
                                {
                                    this_fp->phys_info.vel_jostle_z += (3.0F * ((is_check_self != FALSE) ? -1 : 1));
                                }
                                else this_fp->phys_info.vel_jostle_z += (3.0F * ((jostle_dist_x < 0.0F) ? 1 : -1));
                            }
                            else this_fp->phys_info.vel_jostle_z += (3.0F * ((dist_z < 0.0F) ? -1 : 1));
                        }
                    }
                }
                else is_check_self = TRUE;

                other_gobj = other_gobj->group_gobj_next;

            }
            if ((is_jostle == FALSE) && (DObjGetStruct(fighter_gobj)->translate.z != 0.0F))
            {
                this_fp->phys_info.vel_jostle_z = ((DObjGetStruct(fighter_gobj)->translate.z < 0.0F) ? RIGHT : LEFT) * 3.0F;
            }
        }
    }
    this_fp->coll_data.pos_push.x = this_fp->coll_data.pos_push.y = this_fp->coll_data.pos_push.z = 0.0F;
}

void func_ovl2_800E1CF0(void)
{
    s32 i;

    D_ovl2_80131198 = D_ovl2_8013119C = 0;

    for (i = 0; i < ARRAY_COUNT(D_ovl2_80131180); i++)
    {
        D_ovl2_80131180[i].ogobj = NULL;
    }
    for (i = 0; i < ARRAY_COUNT(D_ovl2_80131190); i++)
    {
        D_ovl2_80131190[i].egobj = NULL;
    }
}

bool32 func_ovl2_800E1D48(GObj *ogobj, bool32(*proc_update)(GObj*, GObj*, s32*))
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_ovl2_80131180); i++)
    {
        if (D_ovl2_80131180[i].ogobj == NULL)
        {
            D_ovl2_80131180[i].ogobj = ogobj;
            D_ovl2_80131180[i].proc_update = proc_update;
            D_ovl2_80131198++;

            return TRUE;
        }
    }
    return FALSE;
}

void func_ovl2_800E1D9C(GObj *ogobj)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_ovl2_80131180); i++)
    {
        if (D_ovl2_80131180[i].ogobj == ogobj)
        {
            D_ovl2_80131180[i].ogobj = NULL;
            D_ovl2_80131198--;

            return;
        }
    }
}

bool32 func_ovl2_800E1DE8(GObj *ogobj, bool32(*proc_update)(GObj*, GObj*, Ground_Hit*, s32*))
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_ovl2_80131190); i++)
    {
        if (D_ovl2_80131190[i].egobj == NULL)
        {
            D_ovl2_80131190[i].egobj = ogobj;
            D_ovl2_80131190[i].proc_update = proc_update;
            D_ovl2_8013119C++;

            return TRUE;
        }
    }
    return FALSE;
}

void func_ovl2_800E1E3C(GObj *ogobj)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_ovl2_80131190); i++)
    {
        if (D_ovl2_80131190[i].egobj == ogobj)
        {
            D_ovl2_80131190[i].egobj = NULL;
            D_ovl2_8013119C--;

            return;
        }
    }
}

void func_ovl2_800E1E88(GObj *ogobj, GObj *fighter_gobj, void *unused, s32 kind)
{
    switch (kind)
    {
    case 2:
        func_ovl3_80143BC4(fighter_gobj, ogobj);
        break;

    case 3:
        func_ovl3_80143F30(fighter_gobj, ogobj);
        break;
    }
}

void func_ovl2_800E1EE8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    grMapObject *mo = &D_ovl2_80131180[0];
    s32 i;

    if (!fp->is_stat_nodamage)
    {
        if (!fp->hitlag_timer)
        {
            if (fp->tornado_wait)
            {
                fp->tornado_wait--;
            }
            if (fp->tarucann_wait)
            {
                fp->tarucann_wait--;
            }
        }
        for (i = 0; i < D_ovl2_80131198; i++, mo++)
        {
            if (mo->ogobj != NULL)
            {
                s32 okind;

                if (mo->proc_update(mo->ogobj, fighter_gobj, &okind) != FALSE)
                {
                    func_ovl2_800E1E88(mo->ogobj, fighter_gobj, fp, okind);
                }
            }
        }
    }
}

void func_ovl2_800E1FE0(Fighter_Struct *fp, f32 move)
{
    if (fp->phys_info.vel_damage_ground < 0.0F)
    {
        fp->phys_info.vel_damage_ground += move;

        if (fp->phys_info.vel_damage_ground > 0.0F)
        {
            fp->phys_info.vel_damage_ground = 0.0F;
        }
    }
    else
    {
        fp->phys_info.vel_damage_ground -= move;

        if (fp->phys_info.vel_damage_ground < 0.0F)
        {
            fp->phys_info.vel_damage_ground = 0.0F;
        }
    }
}

void func_ovl2_800E2048(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f *topn_translate = &fp->joint[0]->translate;
    Vec3f *coll_translate = &fp->coll_data.pos_curr;
    Vec3f *ground_angle = &fp->coll_data.ground_angle;
    Vec3f *vel_damage_air;
    s32 unused[2];
    f32 size_mul;
    f32 tan;
    Vec3f vel_damage_new;
    s32 i;

    *coll_translate = *topn_translate;

    if (fp->hitlag_timer == 0)
    {
        if (fp->cliffcatch_wait != 0)
        {
            fp->cliffcatch_wait--;
        }
        if (fp->proc_physics != NULL)
        {
            fp->proc_physics(fighter_gobj);
        }
        vel_damage_air = &fp->phys_info.vel_damage_air;

        if ((fp->phys_info.vel_damage_air.x != 0.0F) || (vel_damage_air->y != 0.0F))
        {
            if (fp->ground_or_air == air)
            {
                vel_damage_new.z = atan2f(vel_damage_air->y, vel_damage_air->x);
                vel_damage_new.y = vel_damage_air->x;
                vel_damage_new.x = vel_damage_air->y;

                vel_damage_air->x -= (1.7F * cosf(vel_damage_new.z));
                vel_damage_air->y -= (1.7F * __sinf(vel_damage_new.z));

                if (((vel_damage_air->x * vel_damage_new.y) < 0.0F) || ((vel_damage_air->y * vel_damage_new.x) < 0.0F))
                {
                    vel_damage_air->x = vel_damage_air->y = 0.0F;
                }
                fp->phys_info.vel_damage_ground = 0.0F;
            }
            else
            {
                if (fp->phys_info.vel_damage_ground == 0.0F)
                {
                    fp->phys_info.vel_damage_ground = fp->phys_info.vel_damage_air.x;
                }
                func_ovl2_800E1FE0(fp, D_ovl2_8012C4E0[fp->coll_data.ground_flags & 0xFFFF00FF] * fp->attributes->traction * 0.25F);

                vel_damage_air->x = (ground_angle->y * fp->phys_info.vel_damage_ground);
                vel_damage_air->y = (-ground_angle->x * fp->phys_info.vel_damage_ground);
            }
        }
        vec3f_add_to(topn_translate, &fp->phys_info.vel_air);

        topn_translate->x += vel_damage_air->x;
        topn_translate->y += vel_damage_air->y;
    }
    if (fp->proc_lagupdate != NULL)
    {
        fp->proc_lagupdate(fighter_gobj);
    }
    vec3f_sub(&fp->coll_data.pos_prev, topn_translate, coll_translate);

    if ((fp->ground_or_air == ground) && (fp->coll_data.ground_line_id != -1) && (fp->coll_data.ground_line_id != -2) && (func_ovl2_800FC67C(fp->coll_data.ground_line_id) != 0))
    {
        func_ovl2_800FA7B8(fp->coll_data.ground_line_id, &fp->coll_data.pos_correct);
        vec3f_add_to(topn_translate, &fp->coll_data.pos_correct);
    }
    else fp->coll_data.pos_correct.x = fp->coll_data.pos_correct.y = fp->coll_data.pos_correct.z = 0.0F;

    func_ovl3_8013CB7C(fighter_gobj);

    if ((Ground_Info->unk_groundinfo_0x88 <= fp->coll_data.pos_curr.y) && (topn_translate->y < Ground_Info->unk_groundinfo_0x88) && (fp->ft_kind != Ft_Kind_MasterHand))
    {
        func_800269C0(0x99U);
    }
    if (fp->publicity_knockback != 0)
    {
        if (((D_ovl2_80131308.unk_80131308_0x2C + 450.0F) < fp->joint[0]->translate.x) && (fp->joint[0]->translate.x < (D_ovl2_80131308.unk_80131308_0x28 - 450.0F)))
        {
            fp->publicity_knockback = 0.0F;
        }
    }
    if (fp->proc_map != NULL)
    {
        fp->coll_data.coll_mask_prev = fp->coll_data.coll_mask;
        fp->coll_data.coll_mask = 0U;
        fp->coll_data.unk_0x64 = FALSE;
        fp->coll_data.coll_type = 0;
        fp->coll_data.unk_0x58 = 0;

        fp->proc_map(fighter_gobj);

        if (fp->ft_kind == Ft_Kind_Kirby)
        {
            func_ovl2_800EB39C(fighter_gobj);
        }
    }
    if (fp->proc_slope != NULL)
    {
        fp->proc_slope(fighter_gobj);
    }
    func_ovl2_800EB528(fp->joint[0]);

    if (fp->hitlag_timer == 0)
    {
        func_ovl2_800E0654(fighter_gobj);
    }
    if (fp->hitlag_timer == 0)
    {
        if (fp->proc_accessory != NULL)
        {
            fp->proc_accessory(fighter_gobj);
        }
    }
    fp->x191_flag_b0 = FALSE;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
    {
        Fighter_Hit *ft_hit = &fp->fighter_hit[i];

        switch (ft_hit->update_state)
        {
        case gmHitCollision_UpdateState_Disable:
            break;

        case gmHitCollision_UpdateState_New:

            ft_hit->pos = ft_hit->offset;

            if (ft_hit->is_itemswing)
            {
                size_mul = 1.0F / fp->attributes->size_mul;

                ft_hit->pos.x *= size_mul;
                ft_hit->pos.y *= size_mul;
                ft_hit->pos.z *= size_mul;
            }
            func_ovl2_800EDF24(ft_hit->joint, &ft_hit->pos);

            ft_hit->update_state = gmHitCollision_UpdateState_Transfer;

            ft_hit->unk_fthit_0x7C = 0;
            ft_hit->unk_fthit_0xC0 = 0.0F;

            break;

        case gmHitCollision_UpdateState_Transfer:
            ft_hit->update_state = gmHitCollision_UpdateState_Interpolate;

        case gmHitCollision_UpdateState_Interpolate:

            ft_hit->pos_prev = ft_hit->pos;
            ft_hit->pos = ft_hit->offset;

            if (ft_hit->is_itemswing)
            {
                size_mul = 1.0F / fp->attributes->size_mul;

                ft_hit->pos.x *= size_mul;
                ft_hit->pos.y *= size_mul;
                ft_hit->pos.z *= size_mul;
            }
            func_ovl2_800EDF24(ft_hit->joint, &ft_hit->pos);

            ft_hit->unk_fthit_0x7C = 0;
            ft_hit->unk_fthit_0xC0 = 0.0F;

            break;
        }
    }
}

void func_ovl2_800E2604(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->capture_gobj == NULL) || (fp->x192_flag_b3)) && ((fp->catch_gobj == NULL) || !(fp->x192_flag_b3)))
    {
        func_ovl2_800E2048(fighter_gobj);
    }
}

void func_ovl2_800E2660(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (((fp->capture_gobj != NULL) && !(fp->x192_flag_b3)) || ((fp->catch_gobj != NULL) && (fp->x192_flag_b3)))
    {
        func_ovl2_800E2048(fighter_gobj);
    }
}

static s32 D_ovl2_801311A0[4];
static s32 D_ovl2_801311B0[4];

void func_ovl2_800E26BC(Fighter_Struct *fp, u32 attacker_mask, GObj *victim_gobj, s32 hitbox_type, u32 victim_mask, bool32 unk_bool)
{
    s32 i, j;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
    {
        if (i == ARRAY_COUNT(fp->fighter_hit)); // WAT

        if ((fp->fighter_hit[i].update_state != gmHitCollision_UpdateState_Disable) && (attacker_mask == fp->fighter_hit[i].interact_mask))
        {
            for (j = 0; j < ARRAY_COUNT(fp->fighter_hit[i].hit_targets); j++)
            {
                if (victim_gobj == fp->fighter_hit[i].hit_targets[j].victim_gobj)
                {
                    switch (hitbox_type)
                    {
                    case gmHitCollision_Type_Hurt:
                        fp->fighter_hit[i].hit_targets[j].victim_flags.is_interact_hurt = TRUE;
                        break;

                    case gmHitCollision_Type_Shield:
                        fp->fighter_hit[i].hit_targets[j].victim_flags.is_interact_shield = TRUE;
                        break;

                    case gmHitCollision_Type_Hit:
                        fp->fighter_hit[i].hit_targets[j].victim_flags.interact_mask = victim_mask;
                        break;

                    default:
                        break;
                    }
                    break;
                }
            }
            if (j == ARRAY_COUNT(fp->fighter_hit[i].hit_targets))
            {
                for (j = 0; j < ARRAY_COUNT(fp->fighter_hit[i].hit_targets); j++)
                {
                    if (fp->fighter_hit[i].hit_targets[j].victim_gobj == NULL) break;
                }
                if (j == ARRAY_COUNT(fp->fighter_hit[i].hit_targets)) j = 0;

                fp->fighter_hit[i].hit_targets[j].victim_gobj = victim_gobj;

                switch (hitbox_type)
                {
                case gmHitCollision_Type_Hurt:
                    fp->fighter_hit[i].hit_targets[j].victim_flags.is_interact_hurt = TRUE;
                    break;

                case gmHitCollision_Type_Shield:
                    fp->fighter_hit[i].hit_targets[j].victim_flags.is_interact_shield = TRUE;
                    break;

                case gmHitCollision_Type_Hit:
                    fp->fighter_hit[i].hit_targets[j].victim_flags.interact_mask = victim_mask;
                    break;

                default:
                    break;
                }
            }
            if (unk_bool == FALSE)
            {
                D_ovl2_801311A0[i] = 0;
            }
            else D_ovl2_801311B0[i] = 0;
        }
    }
}

void func_ovl2_800E287C(GObj *attacker_gobj, Fighter_Struct *fp, Fighter_Hit *ft_hit, GObj *victim_gobj)
{
    if (fp->shield_attack_damage < ft_hit->damage)
    {
        fp->shield_attack_damage = ft_hit->damage;

        if ((ft_hit->clang) && (fp->ground_or_air == ground))
        {
            fp->attack_rebound = (fp->shield_attack_damage * 1.62F) + 4.0F;

            fp->lr_attack = (DObjGetStruct(attacker_gobj)->translate.x < DObjGetStruct(victim_gobj)->translate.x) ? RIGHT : LEFT;
        }
    }
}

extern s8 D_ovl65_801936AC;

void func_ovl2_800E2910(Fighter_Struct *other_fp, Fighter_Hit *other_hit, Fighter_Struct *this_fp, Fighter_Hit *this_hit, GObj *other_gobj, GObj *this_gobj)
{
    Vec3f sp2C;

    func_ovl2_800F0BC4(&sp2C, this_hit, other_hit);

    if ((this_hit->damage - 10) < other_hit->damage)
    {
        func_ovl2_800E26BC(this_fp, this_hit->interact_mask, other_gobj, gmHitCollision_Type_Hit, other_hit->interact_mask, TRUE);
        func_ovl2_800E287C(this_gobj, this_fp, this_hit, other_gobj);
        func_ovl2_80100BF0(&sp2C, this_hit->damage);

        if ((Match_Info->game_type == gmMatch_GameType_1PGame) && (this_hit->damage >= 20) && (other_fp->port_id == Scene_Info.player_port))
        {
            D_ovl65_801936AC = TRUE;
        }
    }
    if ((other_hit->damage - 10) < this_hit->damage)
    {
        func_ovl2_800E26BC(other_fp, other_hit->interact_mask, this_gobj, gmHitCollision_Type_Hit, this_hit->interact_mask, FALSE);
        func_ovl2_800E287C(other_gobj, other_fp, other_hit, this_gobj);
        func_ovl2_80100BF0(&sp2C, other_hit->damage);

        if ((Match_Info->game_type == gmMatch_GameType_1PGame) && (other_hit->damage >= 20) && (this_fp->port_id == Scene_Info.player_port))
        {
            D_ovl65_801936AC = TRUE;
        }
    }
}

void func_ovl2_800E2A90(Fighter_Struct *attacker_fp, Fighter_Hit *attacker_hit, Fighter_Struct *victim_fp, GObj *attacker_gobj, GObj *victim_gobj)
{
    Vec3f sp2C;

    func_ovl2_800E26BC(attacker_fp, attacker_hit->interact_mask, victim_gobj, gmHitCollision_Type_Shield, 0U, FALSE);

    if (attacker_fp->shield_attack_damage < attacker_hit->damage)
    {
        attacker_fp->shield_attack_damage = attacker_hit->damage;
    }
    victim_fp->shield_damage_total += (attacker_hit->damage + attacker_hit->shield_damage);

    if (victim_fp->shield_damage < attacker_hit->damage)
    {
        victim_fp->shield_damage = attacker_hit->damage;

        victim_fp->lr_shield = (DObjGetStruct(victim_gobj)->translate.x < DObjGetStruct(attacker_gobj)->translate.x) ? RIGHT : LEFT;

        victim_fp->shield_port_id = attacker_fp->port_id;
    }
    func_ovl2_800F0B78(&sp2C, attacker_hit, victim_gobj, victim_fp->joint[3]);
    func_ovl2_80100BF0(&sp2C, attacker_hit->damage);
}

void func_ovl2_800E2B88(Fighter_Struct *attacker_fp, Fighter_Hit *attacker_hit, Fighter_Struct *victim_fp, GObj *attacker_gobj, GObj *victim_gobj)
{
    f32 dist;

    func_ovl2_800E26BC(attacker_fp, attacker_hit->interact_mask, victim_gobj, gmHitCollision_Type_Hurt, 0U, TRUE);

    if (DObjGetStruct(victim_gobj)->translate.x < DObjGetStruct(attacker_gobj)->translate.x)
    {
        dist = -(DObjGetStruct(victim_gobj)->translate.x - DObjGetStruct(attacker_gobj)->translate.x);
    }
    else dist = DObjGetStruct(victim_gobj)->translate.x - DObjGetStruct(attacker_gobj)->translate.x;

    if (dist < attacker_fp->search_gobj_dist)
    {
        attacker_fp->search_gobj_dist = dist;
        attacker_fp->search_gobj = victim_gobj;
    }
}

// Hitbox sound effects
// Rows = SFX type
// Columns = SFX level

u16 D_ovl2_80128D00[gmHitCollision_SoundEffect_EnumMax][gmHitCollision_SoundLevel_EnumMax] =
{
    {  0x28,  0x26,  0x25 }, // Punch
    {  0x22,  0x20,  0x1F }, // Kick
    {  0xD8,  0xD8,  0xD8 }, // Coin
    {  0x1C,  0x1B,  0x19 }, // Burn
    {  0x18,  0x17,  0x16 }, // Zap
    { 0x107, 0x106, 0x105 }, // Slash
    {  0x33,  0x33,  0x33 }, // Fan / Slap
    {  0x26,  0x25,  0x34 }  // Bat
};

void func_ovl2_800E2C24(Fighter_Struct *fp, Fighter_Hit *ft_hit)
{
    if ((fp->p_sfx1 != NULL) && (fp->p_sfx1->sfx_id != 0) && (fp->p_sfx1->sfx_id == fp->sfx1_id))
    {
        func_80026738(fp->p_sfx1);
    }
    fp->p_sfx1 = NULL, fp->sfx1_id = 0;

    func_ovl0_800C8654(D_ovl2_80128D00[ft_hit->sfx_kind][ft_hit->sfx_level], fp->joint[0]->translate.x);
}

bool32 func_ovl2_800E2CC0(Fighter_Struct *fp, s32 *damage)
{
    if (fp->is_damage_resist)
    {
        fp->damage_resist -= *damage;

        if (fp->damage_resist <= 0)
        {
            fp->is_damage_resist = FALSE;

            *damage = -fp->damage_resist;
        }
    }
    if (!(fp->is_damage_resist))
    {
        fp->damage_taken_recent += *damage;

        if (fp->unk_ft_0x7DC < *damage)
        {
            fp->unk_ft_0x7DC = *damage;
        }
        return TRUE;
    }
    else return FALSE;
}

static s32 ftHitCollisionLogIndex;
static ftHitCollisionLog ftHitCollisionLogTable[10];

void func_ovl2_800E2D44(Fighter_Struct *attacker_fp, Fighter_Hit *attacker_hit, Fighter_Struct *victim_fp, Fighter_Hurt *victim_hurt, GObj *attacker_gobj, GObj *victim_gobj)
{
    s32 damage;
    s32 attacker_port_id;
    s32 attacker_player_number;
    s32 unused;
    Vec3f sp3C;

    func_ovl2_800E26BC(attacker_fp, attacker_hit->interact_mask, victim_gobj, gmHitCollision_Type_Hurt, 0U, FALSE);

    damage = func_ovl2_800EA40C(victim_fp, attacker_hit->damage);

    if (attacker_fp->attack_damage < damage)
    {
        attacker_fp->attack_damage = damage;
    }
    if
    (
        (victim_fp->special_hit_status == gmHitCollision_HitStatus_Normal)  &&
        (victim_fp->special_status == ftSpecialStatus_Normal)               &&
        (victim_fp->hit_status == gmHitCollision_HitStatus_Normal)          &&
        (victim_hurt->hit_status == gmHitCollision_HitStatus_Normal)
    )
    {
        if (func_ovl2_800E2CC0(victim_fp, &damage) != FALSE)
        {
            if (attacker_fp->throw_gobj != NULL)
            {
                attacker_port_id = attacker_fp->throw_port_id;
                attacker_player_number = attacker_fp->throw_player_number;
            }
            else
            {
                attacker_port_id = attacker_fp->port_id;
                attacker_player_number = attacker_fp->player_number;
            }
            if (ftHitCollisionLogIndex < ARRAY_COUNT(ftHitCollisionLogTable))
            {
                ftHitCollisionLog *hitlog = &ftHitCollisionLogTable[ftHitCollisionLogIndex];

                hitlog->hit_source = ftHitCollision_LogKind_Fighter;
                hitlog->attacker_hit = attacker_hit;
                hitlog->attacker_gobj = attacker_gobj;
                hitlog->victim_hurt = victim_hurt;
                hitlog->attacker_port_id = attacker_port_id;
                hitlog->attacker_player_number = attacker_player_number;

                ftHitCollisionLogIndex++;
            }
            func_ovl2_800EA98C(attacker_port_id, victim_fp->port_id, damage);
            func_ovl2_800EA614(attacker_port_id, victim_fp->port_id, attacker_hit->attack_id, attacker_hit->flags_hi.halfword);
        }
        else
        {
            func_ovl2_800F0A90(&sp3C, attacker_hit, victim_hit);
            func_ovl2_80100BF0(&sp3C, damage);
        }
    }
    else
    {
        func_ovl2_800F0A90(&sp3C, attacker_hit, victim_hit);
        func_ovl2_80100BF0(&sp3C, damage);
    }
    func_ovl2_800E2C24(attacker_fp, attacker_hit);
}

void func_ovl2_800E2F04(Item_Struct *ip, Item_Hit *it_hit, s32 index, Fighter_Struct *fp, Fighter_Hit *ft_hit, GObj *item_gobj, GObj *fighter_gobj)
{
    s32 damage = func_ovl3_80168128(ip);
    Vec3f sp30;

    func_ovl2_800F0C08(&sp30, it_hit, index, ft_hit);

    if ((ft_hit->damage - 10) < damage)
    {
        func_ovl2_800E26BC(fp, ft_hit->interact_mask, item_gobj, gmHitCollision_Type_Hit, 0U, TRUE);
        func_ovl2_800E287C(fighter_gobj, fp, ft_hit, item_gobj);
        func_ovl2_80100BF0(&sp30, ft_hit->damage);
    }

    if ((damage - 10) < ft_hit->damage)
    {
        func_ovl3_8016679C(ip, it_hit, fighter_gobj, gmHitCollision_Type_Hit, ft_hit->interact_mask);

        if (ip->hit_attack_damage < damage)
        {
            ip->hit_attack_damage = damage;
        }
        func_ovl2_80100BF0(&sp30, damage);

        if ((Match_Info->game_type == gmMatch_GameType_1PGame) && ((damage - 10) >= 10) && (fp->port_id == Scene_Info.player_port))
        {
            D_ovl65_801936AC = TRUE;
        }
    }
}

void func_ovl2_800E3048(Item_Struct *ip, Item_Hit *it_hit, s32 arg2, Fighter_Struct *fp, void *arg4, GObj *fighter_gobj, f32 angle, f32 *arg7)
{
    s32 damage = func_ovl3_80168128(ip);
    Vec3f sp30;

    func_ovl3_8016679C(ip, it_hit, fighter_gobj, (it_hit->can_rehit) ? gmHitCollision_Type_ShieldRehit : gmHitCollision_Type_Shield, 0);

    if (ip->hit_shield_damage < damage)
    {
        ip->hit_shield_damage = damage;

        ip->shield_collide_angle = angle;

        ip->shield_collide_vec.x = 0.0F;
        ip->shield_collide_vec.y = 0.0F;

        ip->shield_collide_vec.z = (fp->lr == RIGHT) ? -(*arg7) : *arg7;

        vec3f_normalize(&ip->shield_collide_vec);
    }
    fp->shield_damage_total += damage + it_hit->shield_damage;

    if (fp->shield_damage < damage)
    {
        fp->shield_damage = damage;

        fp->lr_shield = (ip->phys_info.vel.x < 0.0F) ? RIGHT : LEFT;

        fp->shield_port_id = ip->port_id;
    }
    func_ovl2_800F0C4C(&sp30, it_hit, arg2, fighter_gobj, fp->joint[3]);
    func_ovl2_80100BF0(&sp30, it_hit->shield_damage + damage);
}

void func_ovl2_800E31B4(Item_Struct *ip, Item_Hit *it_hit, Fighter_Struct *fp, GObj *fighter_gobj)
{
    s32 damage = func_ovl3_80168128(ip);

    func_ovl3_8016679C(ip, it_hit, fighter_gobj, gmHitCollision_Type_Reflect, 0);

    if (fp->special_hit->damage_resist < damage)
    {
        if (it_hit->flags_0x48_b2)
        {
            if (ip->hit_reflect_damage < damage)
            {
                ip->hit_reflect_damage = damage;
            }
        }
        else if (ip->hit_victim_damage < damage)
        {
            ip->hit_victim_damage = damage;
        }
        fp->reflect_damage = damage;

        fp->lr_reflect = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(ip->item_gobj)->translate.x) ? RIGHT : LEFT;
    }
    else
    {
        ip->reflect_gobj = fighter_gobj;

        ip->unk_0x258 = fp->flags_lw;
        ip->unk_0x25A.halfword = fp->unk_0x290.halfword;

        fp->lr_reflect = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(ip->item_gobj)->translate.x) ? RIGHT : LEFT;
    }
}

void func_ovl2_800E3308(Item_Struct *ip, Item_Hit *it_hit, Fighter_Struct *fp, GObj *fighter_gobj)
{
    s32 damage = func_ovl3_80168128(ip);

    func_ovl3_8016679C(ip, it_hit, fighter_gobj, gmHitCollision_Type_Absorb, 0);

    ip->absorb_gobj = fighter_gobj;

    fp->lr_absorb = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(ip->item_gobj)->translate.x) ? RIGHT : LEFT;

    if (!(it_hit->noheal))
    {
        fp->percent_damage -= (s32)(damage * 2.0F);

        if (fp->percent_damage < 0)
        {
            fp->percent_damage = 0;
        }
        Match_Info->player_block[fp->port_id].stock_damage_all = fp->percent_damage;
    }
}

void func_ovl2_800E3418(Item_Struct *ip, Item_Hit *it_hit, s32 arg2, Fighter_Struct *fp, Fighter_Hurt *ft_hurt, GObj *item_gobj, GObj *fighter_gobj)
{
    s32 unk = func_ovl3_80168128(ip);
    s32 damage;

    func_ovl3_8016679C(ip, it_hit, fighter_gobj, (it_hit->flags_0x48_b2) ? gmHitCollision_Type_HurtRehit : gmHitCollision_Type_Hurt, 0U);

    damage = func_ovl2_800EA40C(fp, unk);

    if (it_hit->flags_0x48_b2)
    {
        if (ip->hit_reflect_damage < damage)
        {
            ip->hit_reflect_damage = damage;
        }
    }
    else if (ip->hit_victim_damage < damage)
    {
        ip->hit_victim_damage = damage;
    }
    if
    (
        (fp->special_hit_status == ftSpecialStatus_Normal)      &&
        (fp->special_status == gmHitCollision_HitStatus_Normal) &&
        (fp->hit_status == gmHitCollision_HitStatus_Normal)     &&
        (ft_hurt->hit_status == gmHitCollision_HitStatus_Normal)&&
        (func_ovl2_800E2CC0(fp, &damage) != 0)
    )
    {
        if (ftHitCollisionLogIndex < ARRAY_COUNT(ftHitCollisionLogTable))
        {
            ftHitCollisionLog *hitlog = &ftHitCollisionLogTable[ftHitCollisionLogIndex];

            hitlog->hit_source = ftHitCollision_LogKind_Item;
            hitlog->attacker_hit = it_hit;
            hitlog->hitbox_id = arg2;
            hitlog->attacker_gobj = item_gobj;
            hitlog->victim_hurt = ft_hurt;
            hitlog->attacker_port_id = ip->port_id;
            hitlog->attacker_player_number = ip->player_number;

            ftHitCollisionLogIndex++;
        }
        func_ovl2_800EA98C(ip->port_id, fp->port_id, damage);
        func_ovl2_800EA614(ip->port_id, fp->port_id, it_hit->attack_id, it_hit->flags_0x4A.halfword);
    }
    func_800269C0(it_hit->hit_sfx);
}

void func_ovl2_800E35BC(Article_Struct *ap, Article_Hit *at_hit, s32 arg2, Fighter_Struct *fp, Fighter_Hit *ft_hit, GObj *article_gobj, GObj *fighter_gobj)
{
    s32 damage = func_ovl3_801727F4(ap);
    Vec3f sp30;

    func_ovl2_800F0E70(&sp30, at_hit, arg2, ft_hit);

    if ((ft_hit->damage - 10) < damage)
    {
        func_ovl2_800E26BC(fp, ft_hit->interact_mask, article_gobj, gmHitCollision_Type_Hit, 0U, TRUE);
        func_ovl2_800E287C(fighter_gobj, fp, ft_hit, article_gobj);
        func_ovl2_80100BF0(&sp30, ft_hit->damage);
    }
    if ((damage - 10) < ft_hit->damage)
    {
        func_ovl3_8016F930(at_hit, fighter_gobj, gmHitCollision_Type_Hit, ft_hit->interact_mask);

        if (ap->hit_attack_damage < damage)
        {
            ap->hit_attack_damage = damage;
        }
        func_ovl2_80100BF0(&sp30, damage);

        if ((Match_Info->game_type == gmMatch_GameType_1PGame) && ((damage - 10) >= 10) && (fp->port_id == Scene_Info.player_port))
        {
            D_ovl65_801936AC = TRUE;
        }
    }
}

void func_ovl2_800E35BC(Article_Struct *ap, Article_Hit *at_hit, s32 arg2, Fighter_Struct *fp, Fighter_Hit *ft_hit, GObj *article_gobj, GObj *fighter_gobj)
{
    s32 damage = func_ovl3_801727F4(ap);
    Vec3f sp30;

    func_ovl2_800F0E70(&sp30, at_hit, arg2, ft_hit);

    if ((ft_hit->damage - 10) < damage)
    {
        func_ovl2_800E26BC(fp, ft_hit->interact_mask, article_gobj, gmHitCollision_Type_Hit, 0U, TRUE);
        func_ovl2_800E287C(fighter_gobj, fp, ft_hit, article_gobj);
        func_ovl2_80100BF0(&sp30, ft_hit->damage);
    }
    if ((damage - 10) < ft_hit->damage)
    {
        func_ovl3_8016F930(at_hit, fighter_gobj, gmHitCollision_Type_Hit, ft_hit->interact_mask);

        if (ap->hit_attack_damage < damage)
        {
            ap->hit_attack_damage = damage;
        }
        func_ovl2_80100BF0(&sp30, damage);

        if ((Match_Info->game_type == gmMatch_GameType_1PGame) && ((damage - 10) >= 10) && (fp->port_id == Scene_Info.player_port))
        {
            D_ovl65_801936AC = TRUE;
        }
    }
}

void func_ovl2_800E36F8(Article_Struct *ap, Article_Hit *at_hit, s32 hitbox_id, Fighter_Struct *fp, void *arg4, GObj *fighter_gobj, f32 angle, f32 *lr)
{
    s32 damage = func_ovl3_801727F4(ap);
    Vec3f sp30;

    func_ovl3_8016F930(at_hit, fighter_gobj, (at_hit->can_rehit) ? gmHitCollision_Type_ShieldRehit : gmHitCollision_Type_Shield, 0);

    if (ap->hit_shield_damage < damage)
    {
        ap->hit_shield_damage = damage;

        ap->shield_collide_angle = angle;

        ap->shield_collide_vec.x = 0.0F;
        ap->shield_collide_vec.y = 0.0F;

        ap->shield_collide_vec.z = (fp->lr == RIGHT) ? -(*lr) : *lr;

        vec3f_normalize(&ap->shield_collide_vec);
    }
    fp->shield_damage_total += damage + at_hit->shield_damage;

    if (fp->shield_damage < damage)
    {
        fp->shield_damage = damage;

        fp->lr_shield = (ap->phys_info.vel.x < 0.0F) ? RIGHT : LEFT;

        fp->shield_port_id = ap->port_id;
    }
    func_ovl2_800F0EB4(&sp30, at_hit, hitbox_id, fighter_gobj, fp->joint[3]);
    func_ovl2_80100BF0(&sp30, at_hit->shield_damage + damage);
}

void func_ovl2_800E3860(Article_Struct *ap, Article_Hit *at_hit, Fighter_Struct *fp, GObj *fighter_gobj)
{
    s32 damage = func_ovl3_801727F4(ap);

    func_ovl3_8016F930(at_hit, fighter_gobj, gmHitCollision_Type_Reflect, 0);

    if (fp->special_hit->damage_resist < damage)
    {
        if (at_hit->flags_0x4C_b2)
        {
            if (ap->hit_reflect_damage < damage)
            {
                ap->hit_reflect_damage = damage;
            }
        }
        else if (ap->hit_victim_damage < damage)
        {
            ap->hit_victim_damage = damage;
        }
        fp->reflect_damage = damage;

        fp->lr_reflect = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(ap->article_gobj)->translate.x) ? RIGHT : LEFT;
    }
    else
    {
        ap->reflect_gobj = fighter_gobj;

        ap->unk_0x28C = fp->flags_lw;
        ap->unk_0x28E.halfword = fp->unk_0x290.halfword;

        fp->lr_reflect = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(ap->article_gobj)->translate.x) ? RIGHT : LEFT;
    }
}

extern u8 D_ovl65_801936AA;

void func_ovl2_800E39B0(Article_Struct *ap, Article_Hit *at_hit, s32 arg2, Fighter_Struct *fp, Fighter_Hurt *ft_hurt, GObj *article_gobj, GObj *fighter_gobj)
{
    s32 damage = func_ovl3_801727F4(ap);
    s32 damage_again;
    s32 lr_attack;

    func_ovl3_8016F930(at_hit, fighter_gobj, (at_hit->flags_0x4C_b2) ? gmHitCollision_Type_HurtRehit : gmHitCollision_Type_Hurt, 0);

    if (ap->type == At_Type_Touch)
    {
        switch (ap->at_kind)
        {
        case At_Kind_Star:

            at_hit->update_state = gmHitCollision_UpdateState_Disable;
            ap->hit_victim_damage = 1;

            func_ovl2_800EA8B0(fp, ATSTAR_INVINCIBLE_TIME);
            func_ovl2_800E7AFC(0x2E);
            func_800269C0(0x36U);

            if ((Match_Info->game_type == gmMatch_GameType_1PGame) && (fp->port_id == Scene_Info.player_port) && (D_ovl65_801936AA < U8_MAX))
            {
                D_ovl65_801936AA++;
            }
            break;

        case At_Kind_Gr_Lucky:
            func_ovl2_800EA3D4(fp, at_hit->damage);

            break;
        }
    }
    else
    {
        damage_again = func_ovl2_800EA40C(fp, damage);

        if (at_hit->flags_0x4C_b2)
        {
            if (ap->hit_reflect_damage < damage_again)
            {
                ap->hit_reflect_damage = damage_again;
            }
        }
        else if (ap->hit_victim_damage < damage_again)
        {
            ap->hit_victim_damage = damage_again;
        }
        if (ABSF(ap->phys_info.vel.x) < 5.0F)
        {
            ap->lr_attack = lr_attack = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(article_gobj)->translate.x) ? LEFT : RIGHT;
        }
        else
        {
            lr_attack = (ap->phys_info.vel.x < 0) ? LEFT : RIGHT;

            ap->lr_attack = lr_attack;
        }
        if 
        (
            (fp->special_hit_status == ftSpecialStatus_Normal)      &&
            (fp->special_status == gmHitCollision_HitStatus_Normal) &&
            (fp->hit_status == gmHitCollision_HitStatus_Normal)     &&
            (ft_hurt->hit_status == gmHitCollision_HitStatus_Normal)&&
            (func_ovl2_800E2CC0(fp, &damage) != 0)
        )
        {
            if (ftHitCollisionLogIndex < ARRAY_COUNT(ftHitCollisionLogTable))
            {
                ftHitCollisionLog *hitlog = &ftHitCollisionLogTable[ftHitCollisionLogIndex];

                hitlog->hit_source = ftHitCollision_LogKind_Article;
                hitlog->attacker_hit = at_hit;
                hitlog->hitbox_id = arg2;
                hitlog->attacker_gobj = article_gobj;
                hitlog->victim_hurt = ft_hurt;
                hitlog->attacker_port_id = ap->port_id;
                hitlog->attacker_player_number = ap->player_number;

                ftHitCollisionLogIndex++;
            }
            func_ovl2_800EA98C(ap->port_id, fp->port_id, damage_again);
            func_ovl2_800EA614(ap->port_id, fp->port_id, at_hit->attack_id, at_hit->flags_0x4E.halfword);
        }
        func_800269C0(at_hit->hit_sfx);
    }
}

void func_ovl2_800E3CAC(GObj *special_gobj, GObj *fighter_gobj, Fighter_Struct *fp, Ground_Hit *gr_hit, s32 target_kind)
{
    s32 damage = func_ovl2_800EA40C(fp, gr_hit->damage);
    s32 temp_v0 = func_ovl2_800E2CC0(fp, &damage);

    if ((temp_v0 != 0) && (ftHitCollisionLogIndex < ARRAY_COUNT(ftHitCollisionLogTable)))
    {
        ftHitCollisionLog *hitlog = &ftHitCollisionLogTable[ftHitCollisionLogIndex];

        hitlog->hit_source = ftHitCollision_LogKind_Special;
        hitlog->attacker_hit = gr_hit;
        hitlog->attacker_gobj = special_gobj;

        ftHitCollisionLogIndex++;
    }
    switch (target_kind)
    {
    case 0:
        fp->acid_wait = 30;
        func_800269C0(0x11EU);

        break;

    case 1:
        if (temp_v0 != 0)
        {
            func_ovl2_800EA98C(ArticleGetStruct(special_gobj)->damage_port, fp->port_id, damage);
        }
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        fp->hotfloor_wait = 16;

        if (target_kind == 7)
        {
            func_800269C0(0x1DU);
        }
        else func_800269C0(0x11EU);

        break;

    default:
        break;
    }
}

void func_ovl2_800E3DD0(GObj *fighter_gobj, GObj *attacker_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->damage_angle == 362)
    {
        f32 dist_x = DObjGetStruct(fighter_gobj)->translate.x - DObjGetStruct(attacker_gobj)->translate.x;
        f32 dist_y;

        fp->lr_damage = (dist_x < 0) ? RIGHT : LEFT;

        if (dist_x < 0.0F)
        {
            dist_x = -dist_x;
        }
        dist_y = (DObjGetStruct(fighter_gobj)->translate.y + fp->coll_data.object_coll.center) - DObjGetStruct(attacker_gobj)->translate.y;

        fp->damage_angle = (dist_x == 0) ? 0 : F_RAD_TO_DEG(atanf(dist_y / dist_x));
    }
}

void func_ovl2_800E3EBC(GObj *fighter_gobj)
{
    Fighter_Struct *this_fp = FighterGetStruct(fighter_gobj);
    Fighter_Struct *attacker_fp;
    Item_Struct *ip;
    Article_Struct *ap;
    ftCommonAttributes *attributes = this_fp->attributes;
    ftHitCollisionLog *hitlog;
    s32 i, j;
    f32 var_f20;
    f32 knockback;
    Fighter_Hit *ft_hit;
    Item_Hit *it_hit;
    Article_Hit *at_hit;
    Ground_Hit *gr_hit;
    Vec3f sp84;
    s32 damage;
    u8 gr_handicap;
    GObj *attacker_gobj;
    s32 lr_damage;

    knockback = -1.0F;

    for (i = 0; i < ftHitCollisionLogIndex; i++)
    {
        hitlog = &ftHitCollisionLogTable[i];

        switch (hitlog->hit_source)
        {
        case ftHitCollision_LogKind_Fighter:
            ft_hit = hitlog->attacker_hit;
            attacker_fp = FighterGetStruct(hitlog->attacker_gobj);
            var_f20 = func_ovl2_800E9D78(this_fp->percent_damage, this_fp->damage_taken_recent, ft_hit->damage, ft_hit->knockback_weight, ft_hit->knockback_scale, ft_hit->knockback_base, attributes->weight, attacker_fp->handicap, this_fp->handicap);

            func_ovl2_800F0A90(&sp84, ft_hit, hitlog->victim_hurt);

            switch (ft_hit->element)
            {
            case gmHitCollision_Element_Fire:
                func_ovl2_800FE2F4(&sp84, ft_hit->damage);
                break;

            case gmHitCollision_Element_Electric:
                func_ovl2_800FE4EC(&sp84, ft_hit->damage);
                break;

            case gmHitCollision_Element_Coin:
                func_ovl2_80100ACC(&sp84);
                break;

            case gmHitCollision_Element_Slash:
                func_ovl2_800FE6E4(&sp84, ft_hit->damage, func_ovl2_800F0FC0(attacker_fp, ft_hit));
                break;

            default:
                if (var_f20 < 180.0F)
                {
                    func_ovl2_800FDC04(&sp84, hitlog->attacker_port_id, ft_hit->damage, NULL);
                }
                else func_ovl2_800FDEAC(&sp84, hitlog->attacker_port_id, ft_hit->damage);

                if (ft_hit->sfx_level != 0)
                {
                    func_ovl2_800FFB38(&sp84);

                    switch (this_fp->attributes->unk_ftca_0x88)
                    {
                    case 0:
                        func_ovl2_80100218(&sp84, this_fp->lr);
                        break;

                    case 1:
                        func_ovl2_80100440(&sp84, this_fp->lr);
                        break;

                    default:
                        break;
                    }
                }
                break;
            }
            break;

        case ftHitCollision_LogKind_Item:
            it_hit = hitlog->attacker_hit;
            ip = ItemGetStruct(hitlog->attacker_gobj);
            damage = func_ovl3_80168128(ip);

            var_f20 = func_ovl2_800E9D78(this_fp->percent_damage, this_fp->damage_taken_recent, damage, it_hit->knockback_weight, it_hit->knockback_scale, it_hit->knockback_base, attributes->weight, ip->handicap, this_fp->handicap);

            if (ip->is_hitlag_victim)
            {
                func_ovl2_800F0D24(&sp84, it_hit, hitlog->hitbox_id, hitlog->victim_hurt);

                switch (it_hit->element)
                {
                case gmHitCollision_Element_Fire:
                    func_ovl2_800FE2F4(&sp84, damage);
                    break;
                case gmHitCollision_Element_Electric:
                    func_ovl2_800FE4EC(&sp84, damage);
                    break;
                case gmHitCollision_Element_Coin:
                    func_ovl2_80100ACC(&sp84);
                    break;

                default:
                    if (var_f20 < 180.0F)
                    {
                        func_ovl2_800FDC04(&sp84, hitlog->attacker_port_id, damage, NULL);
                    }
                    else func_ovl2_800FDEAC(&sp84, hitlog->attacker_port_id, damage);

                    break;
                }
            }
            break;

        case ftHitCollision_LogKind_Article:
            at_hit = hitlog->attacker_hit;
            ap = ArticleGetStruct(hitlog->attacker_gobj);

            damage = func_ovl3_801727F4(ap);

            var_f20 = func_ovl2_800E9D78(this_fp->percent_damage, this_fp->damage_taken_recent, damage, at_hit->knockback_weight, at_hit->knockback_scale, at_hit->knockback_base, attributes->weight, ap->handicap, this_fp->handicap);

            if (ap->is_hitlag_victim)
            {
                func_ovl2_800F0E08(&sp84, at_hit, hitlog->hitbox_id, hitlog->victim_hurt);

                switch (at_hit->element)
                {
                case gmHitCollision_Element_Fire:
                    func_ovl2_800FE2F4(&sp84, damage);
                    break;
                case gmHitCollision_Element_Electric:
                    func_ovl2_800FE4EC(&sp84, damage);
                    break;
                case gmHitCollision_Element_Coin:
                    func_ovl2_80100ACC(&sp84);
                    break;

                default:
                    if (var_f20 < 180.0F)
                    {
                        func_ovl2_800FDC04(&sp84, hitlog->attacker_port_id, damage, NULL);
                    }
                    else func_ovl2_800FDEAC(&sp84, hitlog->attacker_port_id, damage);

                    break;
                }
            }
            break;

        case ftHitCollision_LogKind_Special:
            gr_hit = hitlog->attacker_hit;

            if (gr_hit->env_kind == 1)
            {
                gr_handicap = ArticleGetStruct(hitlog->attacker_gobj)->damage_handicap;
            }
            else gr_handicap = 9;

            var_f20 = func_ovl2_800E9D78(this_fp->percent_damage, this_fp->damage_taken_recent, gr_hit->damage, gr_hit->knockback_weight, gr_hit->knockback_scale, gr_hit->knockback_base, attributes->weight, gr_handicap, this_fp->handicap);

            break;

        default:
            break;
        }
        if (knockback < var_f20)
        {
            knockback = var_f20;

            j = i;
        }
    }
    hitlog = &ftHitCollisionLogTable[j];
    attacker_gobj = hitlog->attacker_gobj;

    switch (hitlog->hit_source)
    {
    case ftHitCollision_LogKind_Fighter:
        ft_hit = hitlog->attacker_hit;
        attacker_fp = FighterGetStruct(attacker_gobj);
        this_fp->damage_angle = ft_hit->angle;
        this_fp->damage_element = ft_hit->element;

        this_fp->lr_damage = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(attacker_gobj)->translate.x) ? RIGHT : LEFT;

        this_fp->damage_player_number = hitlog->attacker_player_number;

        func_ovl2_800EAA2C(this_fp, hitlog->attacker_port_id, hitlog->hit_source, attacker_fp->ft_kind, attacker_fp->flags_lw.halfword & ~0x400, attacker_fp->unk_0x290.halfword);

        this_fp->damage_joint_index = hitlog->victim_hurt->joint_index;
        this_fp->damage_index = hitlog->victim_hurt->unk_ftht_0xC;

        if (this_fp->damage_element == gmHitCollision_Element_Electric)
        {
            attacker_fp->hitlag_mul = 1.5F;
        }
        break;

    case ftHitCollision_LogKind_Item:
        it_hit = hitlog->attacker_hit;
        ip = ItemGetStruct(attacker_gobj);
        this_fp->damage_angle = it_hit->angle;
        this_fp->damage_element = it_hit->element;

        if (ABSF(ip->phys_info.vel.x) < 5.0F)
        {
            this_fp->lr_damage = lr_damage = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(attacker_gobj)->translate.x) ? RIGHT : LEFT;
        }
        else
        {
            lr_damage = (ip->phys_info.vel.x < 0) ? RIGHT : LEFT;

            this_fp->lr_damage = lr_damage;
        }
        if (this_fp->port_id == hitlog->attacker_port_id)
        {
            this_fp->damage_player_number = 0;
            func_ovl2_800EAA2C(this_fp, GMMATCH_PLAYERS_MAX, hitlog->hit_source, ip->it_kind, 0, 0);
        }
        else
        {
            this_fp->damage_player_number = hitlog->attacker_player_number;

            func_ovl2_800EAA2C(this_fp, hitlog->attacker_port_id, hitlog->hit_source, ip->it_kind, it_hit->flags_0x4C.halfword, it_hit->flags_0x4E.halfword);
        }
        this_fp->damage_joint_index = hitlog->victim_hurt->joint_index;
        this_fp->damage_index = hitlog->victim_hurt->unk_ftht_0xC;

        func_ovl2_800E3DD0(fighter_gobj, attacker_gobj);
        break;

    case ftHitCollision_LogKind_Article:
        at_hit = hitlog->attacker_hit;
        ap = ArticleGetStruct(attacker_gobj);

        this_fp->damage_angle = at_hit->angle;
        this_fp->damage_element = at_hit->element;

        if (ABSF(ap->phys_info.vel.x) < 5.0F)
        {
            this_fp->lr_damage = lr_damage = (DObjGetStruct(fighter_gobj)->translate.x < DObjGetStruct(attacker_gobj)->translate.x) ? RIGHT : LEFT;
        }
        else
        {
            lr_damage = (ap->phys_info.vel.x < 0) ? RIGHT : LEFT;

            this_fp->lr_damage = lr_damage;
        }

        if (this_fp->port_id == hitlog->attacker_port_id)
        {
            this_fp->damage_player_number = 0;

            func_ovl2_800EAA2C(this_fp, GMMATCH_PLAYERS_MAX, hitlog->hit_source, ap->at_kind, 0, 0);
        }
        else
        {
            this_fp->damage_player_number = hitlog->attacker_player_number;
            func_ovl2_800EAA2C(this_fp, hitlog->attacker_port_id, hitlog->hit_source, ap->at_kind, at_hit->flags_hi.halfword, at_hit->flags_lw.halfword);
        }
        this_fp->damage_joint_index = hitlog->victim_hurt->joint_index;
        this_fp->damage_index = hitlog->victim_hurt->unk_ftht_0xC;

        func_ovl2_800E3DD0(fighter_gobj, attacker_gobj);
        break;

    case ftHitCollision_LogKind_Special:
        gr_hit = hitlog->attacker_hit;

        this_fp->damage_angle = gr_hit->angle;
        this_fp->damage_element = gr_hit->element;

        this_fp->lr_damage = this_fp->lr;

        switch (gr_hit->env_kind)
        {
        case 0:
            this_fp->damage_player_number = 0;

            if (this_fp->damage_port_id == -1)
            {
                this_fp->damage_port_id = GMMATCH_PLAYERS_MAX;
            }
            func_ovl2_800EAA2C(this_fp, this_fp->damage_port_id, hitlog->hit_source, gr_hit->env_kind, 0, 0);
            break;

        case 1:
            ap = ArticleGetStruct(attacker_gobj);

            this_fp->damage_player_number = ap->damage_player_number;

            func_ovl2_800EAA2C(this_fp, ap->damage_port, hitlog->hit_source, gr_hit->env_kind, 0, 0);

            break;

        default:
            this_fp->damage_player_number = 0;

            func_ovl2_800EAA2C(this_fp, GMMATCH_PLAYERS_MAX, hitlog->hit_source, gr_hit->env_kind, 0, 0);
            break;
        }
        this_fp->damage_joint_index = 0;
        this_fp->damage_index = 0;

        break;

    default:
        break;
    }
    this_fp->damage_knockback = knockback;

    if (this_fp->damage_element == gmHitCollision_Element_Electric)
    {
        this_fp->hitlag_mul = 1.5F;
    }
}

// My brain hurts
void func_ovl2_800E4870(GObj *this_gobj)
{
    GObj *other_gobj;
    Fighter_Struct *this_fp;
    Fighter_Struct *other_fp;
    s32 i, j, k, l, m, n;
    gmHitCollisionFlags those_flags;
    gmHitCollisionFlags these_flags;
    Fighter_Hit *this_ft_hit;
    f32 angle;
    Fighter_Hit *other_ft_hit;
    Fighter_Hurt *ft_hurt;
    bool32 is_check_self;

    this_fp = FighterGetStruct(this_gobj);
    other_gobj = gOMObjCommonLinks[GObjLinkIndex_Fighter];
    is_check_self = FALSE;

    while (other_gobj != NULL)
    {
        if (other_gobj == this_gobj)
        {
            is_check_self = TRUE;

            goto next_gobj;
        }
        else if (other_gobj == this_fp->capture_gobj) goto next_gobj;

        other_fp = FighterGetStruct(other_gobj);

        if (((Match_Info->is_team_battle == TRUE) && (Match_Info->is_team_attack == FALSE)) && (((other_fp->throw_gobj != NULL) ? other_fp->throw_team : other_fp->team) == this_fp->team))
        {
            goto next_gobj;
        }
        if (!(other_fp->x192_flag_b2))
        {
            if ((other_fp->throw_gobj != NULL) && (this_gobj == other_fp->throw_gobj))
            {
                goto next_gobj;
            }
            else
            {
                k = 0;

                for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++)
                {
                    other_ft_hit = &other_fp->fighter_hit[i];

                    if (other_ft_hit->update_state != gmHitCollision_UpdateState_Disable)
                    {
                        if ((this_fp->ground_or_air == air) && (other_ft_hit->is_hit_air) || (this_fp->ground_or_air == ground) && (other_ft_hit->is_hit_ground))
                        {
                            these_flags.is_interact_hurt = these_flags.is_interact_shield = FALSE;

                            these_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                            for (m = 0; m < ARRAY_COUNT(other_ft_hit->hit_targets); m++)
                            {
                                if (this_gobj == other_ft_hit->hit_targets[m].victim_gobj)
                                {
                                    these_flags = other_ft_hit->hit_targets[m].victim_flags;

                                    break;
                                }
                            }
                            if ((!(these_flags.is_interact_hurt)) && (!(these_flags.is_interact_shield)) && (these_flags.interact_mask == GMHITCOLLISION_MASK_ALL))
                            {
                                D_ovl2_801311A0[i] = TRUE;

                                k++;

                                continue;
                            }
                        }
                    }
                    D_ovl2_801311A0[i] = FALSE;
                }
                if (k == 0) goto next_gobj;

                else
                {
                    k = 0;

                    if ((is_check_self != FALSE) && (this_gobj != other_fp->capture_gobj) && (other_fp->ground_or_air == ground) && (this_fp->ground_or_air == ground) && !(this_fp->x192_flag_b2))
                    {
                        if ((this_fp->throw_gobj == NULL) || (other_gobj != this_fp->throw_gobj) && (((Match_Info->is_team_battle != TRUE) || (Match_Info->is_team_attack != FALSE)) || (((other_fp->throw_gobj != NULL) ? other_fp->throw_team : other_fp->team) != this_fp->throw_team)))
                        {
                            l = 0;

                            for (i = 0; i < ARRAY_COUNT(this_fp->fighter_hit); i++)
                            {
                                this_ft_hit = &this_fp->fighter_hit[i];

                                if (this_ft_hit->update_state != gmHitCollision_UpdateState_Disable)
                                {
                                    if ((other_fp->ground_or_air == air) && (this_ft_hit->is_hit_air) || (other_fp->ground_or_air == ground) && (this_ft_hit->is_hit_ground))
                                    {
                                        those_flags.is_interact_hurt = those_flags.is_interact_shield = FALSE;

                                        those_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                                        for (n = 0; n < ARRAY_COUNT(this_ft_hit->hit_targets); n++)
                                        {
                                            if (other_gobj == this_ft_hit->hit_targets[n].victim_gobj)
                                            {
                                                those_flags = this_ft_hit->hit_targets[n].victim_flags;

                                                break;
                                            }
                                        }
                                        if ((!(those_flags.is_interact_hurt)) && (!(those_flags.is_interact_shield)) && (those_flags.interact_mask == GMHITCOLLISION_MASK_ALL))
                                        {
                                            D_ovl2_801311B0[i] = TRUE;

                                            l++;

                                            continue;
                                        }
                                    }
                                }
                                D_ovl2_801311B0[i] = FALSE;
                            }
                            if (l != 0)
                            {
                                for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++)
                                {
                                    other_ft_hit = &other_fp->fighter_hit[i];

                                    if (D_ovl2_801311A0[i] == FALSE) continue;

                                    else for (j = 0; j < ARRAY_COUNT(this_fp->fighter_hit); j++)
                                    {
                                        this_ft_hit = &this_fp->fighter_hit[j];

                                        if (D_ovl2_801311B0[j] == FALSE) continue;

                                        else if (func_ovl2_800EFABC(other_ft_hit, this_ft_hit) != FALSE)
                                        {
                                            func_ovl2_800E2910(other_fp, other_ft_hit, this_fp, this_ft_hit, other_gobj, this_gobj);

                                            if (D_ovl2_801311A0[i] == FALSE)
                                            {
                                                break;
                                            }
                                            else continue;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++) // 175 here
                    {
                        other_ft_hit = &other_fp->fighter_hit[i];

                        if (D_ovl2_801311A0[i] == FALSE) continue;

                        D_ovl2_801311A0[i] = func_ovl2_800EF364(other_ft_hit, this_gobj);

                        if (D_ovl2_801311A0[i] != FALSE) k++;
                    }
                    if (k != 0)
                    {
                        if (this_fp->is_shield)
                        {
                            for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++)
                            {
                                other_ft_hit = &other_fp->fighter_hit[i];

                                if (D_ovl2_801311A0[i] == FALSE) continue;

                                else if (func_ovl2_800EFCC0(other_ft_hit, this_gobj, this_fp->joint[3], &angle) != FALSE)
                                {
                                    func_ovl2_800E2A90(other_fp, other_ft_hit, this_fp, other_gobj, this_gobj);
                                }
                            }
                        }
                        if ((this_fp->special_hit_status != gmHitCollision_HitStatus_Intangible) && (this_fp->special_status != ftSpecialStatus_Intangible) && (this_fp->hit_status != gmHitCollision_HitStatus_Intangible))
                        {
                            for (i = 0; i < ARRAY_COUNT(other_fp->fighter_hit); i++)
                            {
                                other_ft_hit = &other_fp->fighter_hit[i];

                                if (D_ovl2_801311A0[i] == FALSE) continue;

                                else for (j = 0; j < ARRAY_COUNT(this_fp->fighter_hurt); j++)
                                {
                                    ft_hurt = &this_fp->fighter_hurt[j];

                                    if (ft_hurt->hit_status == gmHitCollision_HitStatus_None) break;

                                    if (ft_hurt->hit_status != gmHitCollision_HitStatus_Intangible)
                                    {
                                        if (func_ovl2_800EFBA4(other_ft_hit, ft_hurt) != FALSE)
                                        {
                                            func_ovl2_800E2D44(other_fp, other_ft_hit, this_fp, ft_hurt, other_gobj, this_gobj);

                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    next_gobj:
        other_gobj = other_gobj->group_gobj_next;
    }
}

void func_ovl2_800E4ED4(GObj *fighter_gobj)
{
    GObj *item_gobj;
    s32 i, j, k, l, m, n;
    gmHitCollisionFlags fighter_flags;
    gmHitCollisionFlags item_flags;
    Fighter_Struct *fp;
    Item_Struct *ip;
    Item_Hit *it_hit;
    f32 angle;
    Fighter_Hurt *ft_hurt;
    Fighter_Hit *ft_hit;
    f32 lr;
    s32 unused1[4];

    fp = FighterGetStruct(fighter_gobj);
    item_gobj = gOMObjCommonLinks[GObjLinkIndex_Item];

    while (item_gobj != NULL)
    {
        ip = ItemGetStruct(item_gobj);
        it_hit = &ip->item_hit;

        if ((fighter_gobj != ip->owner_gobj) && ((Match_Info->is_team_battle != TRUE) || (Match_Info->is_team_attack != FALSE) || (fp->team != ip->team)) && (it_hit->update_state != gmHitCollision_UpdateState_Disable))
        {
            if (it_hit->interact_mask & GMHITCOLLISION_MASK_FIGHTER)
            {
                item_flags.is_interact_hurt = item_flags.is_interact_shield = item_flags.is_interact_reflect = item_flags.is_interact_absorb = FALSE;

                item_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                for (m = 0; m < ARRAY_COUNT(it_hit->hit_targets); m++)
                {
                    if (fighter_gobj == it_hit->hit_targets[m].victim_gobj)
                    {
                        item_flags = it_hit->hit_targets[m].victim_flags;

                        break;
                    }
                }
                if (!(item_flags.is_interact_hurt) && !(item_flags.is_interact_shield) && !(item_flags.is_interact_reflect) && !(item_flags.is_interact_absorb) && (item_flags.interact_mask == GMHITCOLLISION_MASK_ALL))
                {
                    if ((it_hit->clang) && !(fp->x192_flag_b2) && ((fp->throw_gobj == NULL) || (fp->throw_gobj != ip->owner_gobj) && ((Match_Info->is_team_battle != TRUE) || (Match_Info->is_team_attack != FALSE) || (fp->throw_team != ip->team))))
                    {

                        if (!(fp->is_reflect) || !(it_hit->can_reflect))
                        {
                            k = 0;

                            for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
                            {
                                ft_hit = &fp->fighter_hit[i];

                                if ((ft_hit->update_state != gmHitCollision_UpdateState_Disable) && ((ip->ground_or_air == air) && (ft_hit->is_hit_air) || (ip->ground_or_air == ground) && (ft_hit->is_hit_ground)))
                                {
                                    fighter_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                                    for (n = 0; n < ARRAY_COUNT(ft_hit->hit_targets); n++)
                                    {
                                        if (item_gobj == ft_hit->hit_targets[n].victim_gobj)
                                        {
                                            fighter_flags = ft_hit->hit_targets[n].victim_flags;

                                            break;
                                        }
                                    }
                                    if (fighter_flags.interact_mask == GMHITCOLLISION_MASK_ALL)
                                    {
                                        D_ovl2_801311B0[i] = TRUE;

                                        k++;

                                        continue;
                                    }
                                }
                                D_ovl2_801311B0[i] = FALSE;
                            }
                            if (k != 0)
                            {
                                for (i = 0; i < it_hit->hitbox_count; i++)
                                {
                                    for (j = 0; j < ARRAY_COUNT(fp->fighter_hit); j++)
                                    {
                                        ft_hit = &fp->fighter_hit[j];

                                        if (D_ovl2_801311B0[j] == FALSE) continue;

                                        else if (func_ovl2_800EFD70(it_hit, i, ft_hit) != FALSE)
                                        {
                                            func_ovl2_800E2F04(ip, it_hit, i, fp, ft_hit, item_gobj, fighter_gobj);

                                            if (ip->hit_attack_damage != 0) goto next_gobj;
                                        }
                                    }
                                }
                            }
                        }

                    }
                    for (i = 0, l = 0; i < it_hit->hitbox_count; i++)
                    {
                        D_ovl2_801311A0[i] = func_ovl2_800EF414(it_hit, i, fighter_gobj);

                        if (D_ovl2_801311A0[i] != 0)
                        {
                            l++;
                        }
                    }
                    if (l != 0)
                    {
                        if ((fp->is_reflect) && (it_hit->can_reflect))
                        {
                            for (i = 0; i < it_hit->hitbox_count; i++)
                            {
                                if (D_ovl2_801311A0[i] == FALSE) continue;

                                else if (func_ovl2_800EFFCC(it_hit, i, fp, fp->special_hit) != FALSE)
                                {
                                    func_ovl2_800E31B4(ip, it_hit, fp, fighter_gobj);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->is_absorb) && (it_hit->can_absorb))
                        {
                            for (i = 0; i < it_hit->hitbox_count; i++)
                            {
                                if (D_ovl2_801311A0[i] == FALSE) continue;

                                else if (func_ovl2_800EFFCC(it_hit, i, fp, fp->special_hit) != FALSE)
                                {
                                    func_ovl2_800E3308(ip, it_hit, fp, fighter_gobj);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->is_shield) && (it_hit->can_shield))
                        {
                            for (i = 0; i < it_hit->hitbox_count; i++)
                            {
                                if (D_ovl2_801311A0[i] == FALSE) continue;

                                else if (func_ovl2_800EFF00(it_hit, i, fighter_gobj, fp->joint[3], &angle, &lr) != FALSE)
                                {
                                    func_ovl2_800E3048(ip, it_hit, i, fp, item_gobj, fighter_gobj, angle, &lr);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->special_hit_status != gmHitCollision_HitStatus_Intangible) && (fp->special_status != ftSpecialStatus_Intangible) && (fp->hit_status != gmHitCollision_HitStatus_Intangible))
                        {
                            for (i = 0; i < it_hit->hitbox_count; i++)
                            {
                                if (D_ovl2_801311A0[i] == FALSE) continue;

                                else for (j = 0; j < ARRAY_COUNT(fp->fighter_hurt); j++)
                                {
                                    ft_hurt = &fp->fighter_hurt[j];

                                    if (ft_hurt->hit_status == gmHitCollision_HitStatus_None) break;

                                    if (ft_hurt->hit_status != gmHitCollision_HitStatus_Intangible)
                                    {
                                        if (func_ovl2_800EFE6C(it_hit, i, ft_hurt) != FALSE)
                                        {
                                            func_ovl2_800E3418(ip, it_hit, i, fp, ft_hurt, item_gobj, fighter_gobj);

                                            goto next_gobj;
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }
    next_gobj:
        item_gobj = item_gobj->group_gobj_next;
    }
}

void func_ovl2_800E55DC(GObj *fighter_gobj)
{
    GObj *article_gobj;
    s32 i, j, k, l, m, n;
    gmHitCollisionFlags fighter_flags;
    gmHitCollisionFlags article_flags;
    Fighter_Struct *fp;
    Article_Struct *ap;
    Article_Hit *at_hit;
    f32 angle;
    Fighter_Hurt *ft_hurt;
    Fighter_Hit *ft_hit;
    f32 lr;
    s32 unused1[4];

    fp = FighterGetStruct(fighter_gobj);
    article_gobj = gOMObjCommonLinks[GObjLinkIndex_Article];

    while (article_gobj != NULL)
    {
        ap = ArticleGetStruct(article_gobj);
        at_hit = &ap->article_hit;

        if ((fighter_gobj != ap->owner_gobj) && ((Match_Info->is_team_battle != TRUE) || (Match_Info->is_team_attack != FALSE) || (fp->team != ap->team)) && (at_hit->update_state != gmHitCollision_UpdateState_Disable))
        {
            if (at_hit->interact_mask & GMHITCOLLISION_MASK_FIGHTER)
            {
                article_flags.is_interact_hurt = article_flags.is_interact_shield = article_flags.is_interact_reflect = FALSE;

                article_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                for (m = 0; m < ARRAY_COUNT(at_hit->hit_targets); m++)
                {
                    if (fighter_gobj == at_hit->hit_targets[m].victim_gobj)
                    {
                        article_flags = at_hit->hit_targets[m].victim_flags;

                        break;
                    }
                }
                if (!(article_flags.is_interact_hurt) && !(article_flags.is_interact_shield) && !(article_flags.is_interact_reflect) && (article_flags.interact_mask == GMHITCOLLISION_MASK_ALL))
                {
                    if ((at_hit->clang) && !(fp->x192_flag_b2) && ((fp->throw_gobj == NULL) || (fp->throw_gobj != ap->owner_gobj) && ((Match_Info->is_team_battle != TRUE) || (Match_Info->is_team_attack != FALSE) || (fp->throw_team != ap->team))))
                    {

                        if (!(fp->is_reflect) || !(at_hit->can_reflect))
                        {
                            k = 0;

                            for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
                            {
                                ft_hit = &fp->fighter_hit[i];

                                if ((ft_hit->update_state != gmHitCollision_UpdateState_Disable) && ((ap->ground_or_air == air) && (ft_hit->is_hit_air) || (ap->ground_or_air == ground) && (ft_hit->is_hit_ground)))
                                {
                                    fighter_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                                    for (n = 0; n < ARRAY_COUNT(ft_hit->hit_targets); n++)
                                    {
                                        if (article_gobj == ft_hit->hit_targets[n].victim_gobj)
                                        {
                                            fighter_flags = ft_hit->hit_targets[n].victim_flags;

                                            break;
                                        }
                                    }
                                    if (fighter_flags.interact_mask == GMHITCOLLISION_MASK_ALL)
                                    {
                                        D_ovl2_801311B0[i] = TRUE;

                                        k++;

                                        continue;
                                    }
                                }
                                D_ovl2_801311B0[i] = FALSE;
                            }
                            if (k != 0)
                            {
                                for (i = 0; i < at_hit->hitbox_count; i++)
                                {
                                    for (j = 0; j < ARRAY_COUNT(fp->fighter_hit); j++)
                                    {
                                        ft_hit = &fp->fighter_hit[j];

                                        if (D_ovl2_801311B0[j] == FALSE) continue;

                                        else if (func_ovl2_800F02BC(at_hit, i, ft_hit) != FALSE)
                                        {
                                            func_ovl2_800E35BC(ap, at_hit, i, fp, ft_hit, article_gobj, fighter_gobj);

                                            if (ap->hit_attack_damage != 0) goto next_gobj;
                                        }
                                    }
                                }
                            }
                        }

                    }
                    for (i = 0, l = 0; i < at_hit->hitbox_count; i++)
                    {
                        D_ovl2_801311A0[i] = func_ovl2_800EF4F4(at_hit, i, fighter_gobj);

                        if (D_ovl2_801311A0[i] != 0)
                        {
                            l++;
                        }
                    }
                    if (l != 0)
                    {
                        if ((fp->is_reflect) && (at_hit->can_reflect))
                        {
                            for (i = 0; i < at_hit->hitbox_count; i++)
                            {
                                if (D_ovl2_801311A0[i] == FALSE) continue;

                                else if (func_ovl2_800F0518(at_hit, i, fp, fp->special_hit) != FALSE)
                                {
                                    func_ovl2_800E3860(ap, at_hit, fp, fighter_gobj);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->is_shield) && (at_hit->can_shield))
                        {
                            for (i = 0; i < at_hit->hitbox_count; i++)
                            {
                                if (D_ovl2_801311A0[i] == FALSE) continue;

                                else if (func_ovl2_800F044C(at_hit, i, fighter_gobj, fp->joint[3], &angle, &lr) != FALSE)
                                {
                                    func_ovl2_800E36F8(ap, at_hit, i, fp, article_gobj, fighter_gobj, angle, &lr);

                                    goto next_gobj;
                                }
                            }
                        }
                        if ((fp->special_hit_status != gmHitCollision_HitStatus_Intangible) && (fp->special_status != ftSpecialStatus_Intangible) && (fp->hit_status != gmHitCollision_HitStatus_Intangible))
                        {
                            for (i = 0; i < at_hit->hitbox_count; i++)
                            {
                                if (D_ovl2_801311A0[i] == FALSE) continue;

                                else for (j = 0; j < ARRAY_COUNT(fp->fighter_hurt); j++)
                                {
                                    ft_hurt = &fp->fighter_hurt[j];

                                    if (ft_hurt->hit_status == gmHitCollision_HitStatus_None) break;

                                    if (ft_hurt->hit_status != gmHitCollision_HitStatus_Intangible)
                                    {
                                        if (func_ovl2_800F03B8(at_hit, i, ft_hurt) != FALSE)
                                        {
                                            func_ovl2_800E39B0(ap, at_hit, i, fp, ft_hurt, article_gobj, fighter_gobj);

                                            goto next_gobj;
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }
    next_gobj:
        article_gobj = article_gobj->group_gobj_next;
    }
}

extern Ground_Hit D_ovl2_80128D30[6] = 
{
    {  4,  1, 361, 100, 100, 0, gmHitCollision_Element_Fire  },
    {  5, 10,  90, 100, 200, 0, gmHitCollision_Element_Fire  },
    {  6, 10,  90, 100, 100, 0, gmHitCollision_Element_Fire  },
    {  7, 10, 361, 100,  80, 0, gmHitCollision_Element_Slash },
    {  8,  1,  90, 100, 100, 0, gmHitCollision_Element_Fire  },
    {  9,  1,  90, 100, 100, 0, gmHitCollision_Element_Fire  }
};

bool32 func_ovl2_800E5C30(Fighter_Struct *fp, Ground_Hit **p_gr_hit)
{
    if ((fp->hotfloor_wait == 0) && (fp->ground_or_air == ground) && (fp->coll_data.ground_line_id != -1) && (fp->coll_data.ground_line_id != -2))
    {
        switch (fp->coll_data.ground_flags & 0xFFFF00FF)
        {
        case 7:
            *p_gr_hit = &D_ovl2_80128D30[0];
            return TRUE;

        case 8:
            *p_gr_hit = &D_ovl2_80128D30[1];
            return TRUE;

        case 9:
            *p_gr_hit = &D_ovl2_80128D30[2];
            return TRUE;

        case 10:
            *p_gr_hit = &D_ovl2_80128D30[3];
            return TRUE;

        case 11:
            *p_gr_hit = &D_ovl2_80128D30[4];
            return TRUE;

        case 15:
            *p_gr_hit = &D_ovl2_80128D30[5];
            return TRUE;

        default:
            return FALSE;
        }
    }
    else return FALSE;
}

void func_ovl2_800E5D20(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    grMapEnvironment *me = &D_ovl2_80131190[0];
    s32 i;
    Ground_Hit *gr_hit;
    s32 sp44;

    if (fp->hitlag_timer == 0)
    {
        if (fp->acid_wait != 0)
        {
            fp->acid_wait--;
        }
        if (fp->hotfloor_wait != 0)
        {
            fp->hotfloor_wait--;
        }
    }
    if (func_ovl2_800E8AAC(fighter_gobj) == TRUE)
    {
        for (i = 0; i < D_ovl2_8013119C; i++, me++)
        {
            if ((me->egobj != NULL) && (me->proc_update(me->egobj, fighter_gobj, &gr_hit, &sp44) != FALSE))
            {
                func_ovl2_800E3CAC(me->egobj, fighter_gobj, fp, gr_hit, sp44);
            }
        }
        if (func_ovl2_800E5C30(fp, &gr_hit) != FALSE)
        {
            func_ovl2_800E3CAC(NULL, fighter_gobj, fp, gr_hit, gr_hit->env_kind);
        }
    }
}

// Meth
void func_ovl2_800E5E58(GObj *this_gobj)
{
    GObj *other_gobj;
    Fighter_Struct *this_fp;
    Fighter_Struct *other_fp;
    s32 i, j, m;
    Fighter_Hurt *ft_hurt;
    gmHitCollisionFlags catch_flags;
    Fighter_Hit *ft_hit;

    this_fp = FighterGetStruct(this_gobj);

    this_fp->search_gobj = NULL;
    this_fp->search_gobj_dist = (f32)FLOAT_MAX;

    other_gobj = gOMObjCommonLinks[GObjLinkIndex_Fighter];

    while (other_gobj != NULL)
    {
        if (other_gobj == this_gobj) goto next_gobj;

        other_fp = FighterGetStruct(other_gobj);

        if ((other_fp->is_stat_nodamage)) goto next_gobj;

        if (other_fp->ft_kind == Ft_Kind_MasterHand) goto next_gobj;

        if ((Match_Info->is_team_battle == TRUE) && (Match_Info->is_team_attack == FALSE) && (this_fp->team == other_fp->team)) goto next_gobj;

        if ((other_fp->capture_flags & this_fp->catch_flags)) goto next_gobj;

        if ((other_fp->special_hit_status != gmHitCollision_HitStatus_Normal) || (other_fp->special_status != ftSpecialStatus_Normal) || (other_fp->hit_status != gmHitCollision_HitStatus_Normal)) goto next_gobj;

        for (i = 0; i < ARRAY_COUNT(this_fp->fighter_hit) ^ 0; i++) // XOR 0 ???
        {
            ft_hit = &this_fp->fighter_hit[i];

            if (ft_hit->update_state != gmHitCollision_UpdateState_Disable)
            {
                if ((other_fp->ground_or_air == air) && (!ft_hit->is_hit_air)) continue; // Why is it breaking the previously established standard for this type of check now???

                if ((other_fp->ground_or_air == ground) && (!ft_hit->is_hit_ground)) continue; // ???

                catch_flags.is_interact_hurt = catch_flags.is_interact_shield = 0, catch_flags.interact_mask = GMHITCOLLISION_MASK_ALL;

                for (m = 0; m < ARRAY_COUNT(ft_hit->hit_targets); m++)
                {
                    if (other_gobj == ft_hit->hit_targets[m].victim_gobj)
                    {
                        catch_flags = ft_hit->hit_targets[m].victim_flags;

                        break;
                    }
                }
                if (!(catch_flags.is_interact_hurt) && !(catch_flags.is_interact_shield) && (catch_flags.interact_mask == GMHITCOLLISION_MASK_ALL))
                {
                    for (j = 0; j < ARRAY_COUNT(other_fp->fighter_hurt); j++)
                    {
                        ft_hurt = &other_fp->fighter_hurt[j];

                        if (ft_hurt->hit_status == gmHitCollision_HitStatus_None) break;

                        else if ((ft_hurt->hit_status != gmHitCollision_HitStatus_Intangible) && (ft_hurt->hit_status != gmHitCollision_HitStatus_Invincible))
                        {
                            if ((ft_hurt->unk_ftht_0x10 != 0) && (func_ovl2_800EFBA4(ft_hit, ft_hurt) != FALSE))
                            {
                                func_ovl2_800E2B88(this_fp, ft_hit, other_fp, this_gobj, other_gobj);

                                goto next_gobj;
                            }
                        }
                    }
                    continue; // Believe it or not, necessary (for now)
                }
            }
        }
    next_gobj:
        other_gobj = other_gobj->group_gobj_next;
    }
}

void func_ovl2_800E6100(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E1EE8(fighter_gobj);

    if (fp->x192_flag_b2)
    {
        func_ovl2_800E5E58(fighter_gobj);

        if (fp->search_gobj != NULL)
        {
            fp->proc_catch(fighter_gobj);
            fp->proc_capture(fp->search_gobj, fighter_gobj);
        }
    }
}

void func_ovl2_800E6178(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (!(fp->is_stat_nodamage))
    {
        ftHitCollisionLogIndex = 0;

        func_ovl2_800E4870(fighter_gobj);
        func_ovl2_800E55DC(fighter_gobj);
        func_ovl2_800E4ED4(fighter_gobj);
        func_ovl2_800E5D20(fighter_gobj);

        if (ftHitCollisionLogIndex != 0)
        {
            func_ovl2_800E3EBC(fighter_gobj);
        }
    }
}

void func_ovl2_800E61EC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 damage;
    s32 status_id;
    f32 knockback_resist;
    bool32 is_shieldbreak;
    u32 hitlag_timer;
    s32 sp84;
    s32 element;

    damage = 0;
    is_shieldbreak = FALSE;
    status_id = fp->status_info.status_id;
    hitlag_timer = fp->hitlag_timer;
    sp84 = 0;

    if (fp->unk_ft_0x7AC != 0)
    {
        fp->x3C_unk += fp->unk_ft_0x7AC;
    }
    if (!(fp->is_shield) && (fp->shield_health < 55))
    {
        fp->shield_lifeup_wait--;

        if (fp->shield_lifeup_wait == 0.0F)
        {
            fp->shield_health++;

            fp->shield_lifeup_wait = 10.0F;
        }
    }
    fp->shield_health -= fp->shield_damage_total;

    if (fp->shield_health <= 0)
    {
        fp->shield_health = (fp->ft_kind == Ft_Kind_Yoshi) ? 30 : 30;

        is_shieldbreak = TRUE;
    }
    if (fp->damage_knockback != 0.0F)
    {
        if ((fp->status_info.status_id == ftStatus_Common_Squat) || (fp->status_info.status_id == ftStatus_Common_SquatWait))
        {
            fp->damage_knockback *= 0.6666667F;
        }
        if (fp->status_info.status_id == ftStatus_Common_Tornado)
        {
            fp->unk_ft_0x814 = 2;
        }
        if (fp->knockback_resist_status < fp->knockback_resist_passive)
        {
            knockback_resist = fp->knockback_resist_passive;
        }
        else knockback_resist = fp->knockback_resist_status;

        fp->damage_knockback -= knockback_resist;

        if (fp->damage_knockback <= 0)
        {
            fp->damage_knockback = 0;
        }
        func_ovl2_800EA248(fp, fp->damage_taken_recent);

        if (fp->proc_trap != NULL)
        {
            fp->proc_trap(fighter_gobj);
        }
        if (fp->ft_kind != Ft_Kind_MasterHand)
        {
            switch (fp->unk_ft_0x814)
            {
            case 4:
                break;

            case 1:
                func_ovl2_800E823C(fighter_gobj);
                func_ovl3_80141560(fighter_gobj);
                break;

            case 2:
                func_ovl3_80141648(fighter_gobj);
                break;

            case 3:
                func_ovl2_800E823C(fighter_gobj);
                func_ovl3_80140E2C(fighter_gobj);
                break;

            default:
                func_ovl3_80141670(fighter_gobj);
                break;
            }
        }
        else
        {
            func_ovl3_80141648(fighter_gobj);
            func_ovl3_801586A0(fighter_gobj);
        }
        damage = fp->unk_ft_0x7DC;
        sp84 = 1;

        func_ovl2_800E7F88(fp, (fp->damage_element == gmHitCollision_Element_Electric) ? TRUE : FALSE, damage, status_id, fp->hitlag_mul);

        if ((s32)((fp->damage_taken_recent * 0.75F) + 4.0F) > 0)
        {
            func_ovl2_800E806C(fp, 0, (s32)((fp->damage_taken_recent * 0.75F) + 4.0F));
        }
    }
    else if (fp->shield_damage != 0)
    {
        if (is_shieldbreak != FALSE)
        {
            func_ovl3_80149510(fighter_gobj);
        }
        else func_ovl3_80149108(fighter_gobj);

        damage = fp->shield_damage;
    }
    else if (fp->shield_attack_damage != 0)
    {
        if (fp->proc_shield != NULL)
        {
            fp->proc_shield(fighter_gobj);
        }
        if ((fp->attack_rebound != 0) && (fp->catch_gobj == NULL) && (fp->capture_gobj == NULL))
        {
            func_ovl2_800E823C(fighter_gobj);
            func_ovl3_80144AB0(fighter_gobj);
        }
        damage = fp->shield_attack_damage;
    }
    else if (fp->attack_damage != 0)
    {
        if (fp->proc_hit != NULL)
        {
            fp->proc_hit(fighter_gobj);
        }
        damage = fp->attack_damage;

        if (fp->flags_lw.flags_0x3FF == 0x2B)
        {
            func_ovl2_800E806C(fp, 10, 0);
        }
        else if ((s32)((fp->attack_damage * 0.5F) + 2.0F) > 0)
        {
            func_ovl2_800E806C(fp, 5, (s32)((fp->attack_damage * 0.5F) + 2.0F));
        }
    }
    else if (fp->reflect_damage != 0)
    {
        func_ovl3_80149608(fighter_gobj);
    }
    else if (fp->lr_reflect != CENTER)
    {
        switch (fp->special_hit->hit_type)
        {
        case 0:
            func_ovl3_8015CEE8(fighter_gobj);
            break;

        case 2:
            func_800269C0(0x34U);
            break;
        }
    }
    else if (fp->lr_absorb != CENTER)
    {
        ftNess_SpecialLw_Proc_Absorb(fighter_gobj);
    }
    if (damage != 0)
    {
        fp->hitlag_timer = func_ovl2_800EA1C0(damage, status_id, fp->hitlag_mul);

        if ((fp->hitlag_timer != 0) && (sp84 != 0))
        {
            fp->x192_flag_b6 = TRUE;
        }
        fp->input.pl.button_tap = fp->input.pl.button_tap_prev = 0;

        if (fp->proc_lagstart != NULL)
        {
            fp->proc_lagstart(fighter_gobj);
        }
    }
    fp->unk_ft_0x7AC = 0;
    fp->attack_damage = 0;
    fp->shield_attack_damage = 0;
    fp->shield_damage = 0;
    fp->shield_damage_total = 0;
    fp->unk_ft_0x7DC = 0;
    fp->damage_taken_recent = 0;
    fp->unk_ft_0x814 = 0;

    fp->lr_reflect = CENTER;
    fp->reflect_damage = 0;
    fp->lr_absorb = CENTER;

    fp->unk_ft_0x7A0 = 0;
    fp->attack_rebound = 0;
    fp->damage_knockback = 0;
    fp->hitlag_mul = 1.0F;

    if ((hitlag_timer == 0) && (fp->afterimage.render_state != -1))
    {
        switch (fp->afterimage.is_itemswing)
        {
        case FALSE:
            if ((fp->ft_kind == Ft_Kind_Link) && (fp->joint_render_state[7][1] == 0))
            {
                UnkDObjData *unk_dobj = fp->joint[11]->unk_0x84;

                func_ovl2_800EDBA4(fp->joint[11]);

                fp->afterimage.desc[fp->afterimage.desc_index].unk_afid_0x0 = unk_dobj->unk_dobjdata_0x80.x;
                fp->afterimage.desc[fp->afterimage.desc_index].unk_afid_0x2 = unk_dobj->unk_dobjdata_0x80.y;
                fp->afterimage.desc[fp->afterimage.desc_index].unk_afid_0x4 = unk_dobj->unk_dobjdata_0x80.z;
                fp->afterimage.desc[fp->afterimage.desc_index].vec.x = unk_dobj->unk_dobjdata_0x70.x;
                fp->afterimage.desc[fp->afterimage.desc_index].vec.y = unk_dobj->unk_dobjdata_0x70.y;
                fp->afterimage.desc[fp->afterimage.desc_index].vec.z = unk_dobj->unk_dobjdata_0x70.z;

                if (fp->afterimage.desc_index == 2)
                {
                    fp->afterimage.desc_index = 0;
                }
                else fp->afterimage.desc_index++;

                if (fp->afterimage.render_state <= 2)
                {
                    fp->afterimage.render_state++;
                }
            }
            break;

        case TRUE:

            if ((fp->item_hold != NULL) && (fp->x190_flag_b6) && (ArticleGetStruct(fp->item_hold)->at_kind == At_Kind_Sword))
            {
                s32 unused;
                HAL_Bitmap bitmap;

                func_ovl0_800C9A38(&bitmap, fp->joint[fp->attributes->joint_itemhold_light]);

                fp->afterimage.desc[fp->afterimage.desc_index].unk_afid_0x0 = bitmap.unk_bitmap_0x30.x;
                fp->afterimage.desc[fp->afterimage.desc_index].unk_afid_0x2 = bitmap.unk_bitmap_0x30.y;
                fp->afterimage.desc[fp->afterimage.desc_index].unk_afid_0x4 = bitmap.unk_bitmap_0x30.z;
                fp->afterimage.desc[fp->afterimage.desc_index].vec.x = bitmap.unk_bitmap_0x10.x;
                fp->afterimage.desc[fp->afterimage.desc_index].vec.y = bitmap.unk_bitmap_0x10.y;
                fp->afterimage.desc[fp->afterimage.desc_index].vec.z = bitmap.unk_bitmap_0x10.z;

                vec3f_normalize(&fp->afterimage.desc[fp->afterimage.desc_index].vec);

                if (fp->afterimage.desc_index == 2)
                {
                    fp->afterimage.desc_index = 0;
                }
                else fp->afterimage.desc_index++;

                if (fp->afterimage.render_state <= 2)
                {
                    fp->afterimage.render_state++;
                }
            }
            break;
        }
    }
}

void func_ovl2_800E69C4(Fighter_Struct *fp, s32 index)
{
    ftPartIndex *part_index;
    void *sp38;
    DObj *joint;
    DObj *j2;
    DObj *j1;
    ftCommonAttributes *attributes;
    DObjDescContainer *container;
    DObj *part_joint;
    UnkDObjData *unk_dobj;

    attributes = fp->attributes;
    part_index = &attributes->p_ftpart_lookup[index];

    if (part_index->partindex_0x0 > 3)
    {
        if (fp->lod_current == 1)
        {
            container = &fp->attributes->dobj_desc_container[0];
        }
        else if (attributes->dobj_desc_container[1].dobj_desc[part_index->partindex_0x0 - 4].unk_dobjdesc_0x4 != NULL)
        {
            container = &attributes->dobj_desc_container[1];
        }
        else container = &attributes->dobj_desc_container[0];
    }
    else container = NULL;

    sp38 = (container != NULL) ? container->dobj_desc[part_index->partindex_0x0 - 4].unk_dobjdesc_0x4 : NULL;

    joint = func_800092D0(fp->fighter_gobj, sp38);
    joint->unk_0xC->unk_0x8 = NULL;
    joint->unk_0xC = NULL;

    if (sp38 != NULL)
    {
        func_ovl0_800C8CB8(joint, container->d2[part_index->partindex_0x0 - 4], container->d3[part_index->partindex_0x0 - 4], 0, fp->costume_id);
    }
    if (container != NULL)
    {
        fp->joint_render_state[part_index->partindex_0x0 - 4][0] = fp->joint_render_state[part_index->partindex_0x0 - 4][1] = (sp38 != NULL) ? 0 : -1;
    }
    part_joint = fp->joint[part_index->partindex_0x4];

    switch (part_index->partindex_0xC)
    {
    case 0:
        if (part_joint->next != NULL)
        {
            j1 = part_joint->next->unk_0x8;
            j2 = part_joint->next;

            while (j1 != NULL)
            {
                j2 = j1;
                j1 = j1->unk_0x8;
            }
            j2->unk_0x8 = joint;
            joint->unk_0xC = j2;
        }
        else part_joint->next = joint;

        joint->prev = part_joint;

        break;

    case 1:
        if (part_joint->next != NULL)
        {
            j2 = part_joint->next;
            j2->unk_0xC = joint;
            joint->unk_0x8 = j2;
        }
        part_joint->next = joint;

        joint->prev = part_joint;

        break;

    case 2:
        j2 = part_joint->next->unk_0x8;
        j2->unk_0xC = joint;
        joint->unk_0x8 = j2;
        j2 = part_joint->next;
        j2->unk_0x8 = joint;
        joint->prev = part_joint;
        joint->unk_0xC = j2;

        break;

    case 3:
        if (part_joint->next != NULL)
        {
            j2 = part_joint->next;
            joint->next = j2;

            do
            {
                j2->prev = joint;
                j2 = j2->unk_0x8;
            }
            while (j2 != NULL);
        }
        part_joint->next = joint;

        joint->prev = part_joint;

        break;
    }
    fp->joint[part_index->partindex_0x0] = joint;

    joint->unk_0x84 = unk_dobj = func_ovl2_800D7604();

    unk_dobj->unk_0xC = attributes->dobj_desc_container[fp->lod_current - 1].unk_dobjcontain_0xC;
    unk_dobj->unk_0xD = part_index->partindex_0x0;

    if (part_index->partindex_0x8 != 0)
    {
        func_ovl0_800C8A58(joint, 0x4B, 0, 0, fp->unk_ft_0x149);
    }
}

void func_ovl2_800E6CE0(Fighter_Struct *fp, s32 index)
{
    DObj *temp_a1;
    DObj *temp_t0;
    ftPartIndex *part_index;
    DObj *joint;
    DObj *var_a2;
    DObj *var_a3;
    DObj *new_var;

    part_index = &fp->attributes->p_ftpart_lookup[index];
    joint = fp->joint[part_index->partindex_0x0];

    if (part_index->partindex_0x0 == 1)
    {
        new_var = joint->prev;
        var_a2 = joint->next;
        temp_a1 = new_var;
        var_a3 = var_a2;

        if (var_a3 != NULL)
        {
            temp_t0 = joint->unk_0xC;

            var_a3 = var_a2;
            var_a2 = temp_t0;

            if (temp_t0 == NULL)
            {
                temp_a1->next = var_a3;
            }
            else
            {
                var_a2->unk_0x8 = var_a3;
                var_a3->unk_0xC = joint->unk_0xC;
            }
            var_a2 = var_a3->unk_0x8;
            var_a3->prev = temp_a1;

            while (var_a2 != NULL)
            {
                var_a3 = var_a2;
                var_a2->prev = temp_a1;
                var_a2 = var_a2->unk_0x8;
            }

            var_a3->unk_0x8 = joint->unk_0x8;
            temp_a1 = joint->unk_0x8;

            if (temp_a1 != NULL)
            {
                temp_a1->unk_0xC = var_a3;
            }
        }
        else
        {
            temp_t0 = joint->unk_0xC;

            if (temp_t0 == NULL)
            {
                temp_a1->next = joint->unk_0x8;
            }
            else temp_t0->unk_0x8 = joint->unk_0x8;

            temp_a1 = joint->unk_0x8;

            if (temp_a1 != NULL)
            {
                temp_a1->unk_0xC = joint->unk_0xC;
            }
        }
        joint->next = NULL;
        joint->unk_0xC = NULL;
        joint->unk_0x8 = NULL;
        joint->prev = NULL;

        temp_a1 = fp->joint[part_index->partindex_0x4];

        if (temp_a1->next != NULL)
        {
            var_a3 = temp_a1->next;
            joint->next = temp_a1->next;

            do
            {
                var_a3->prev = joint;
                var_a3 = var_a3->unk_0x8;
            } 
            while (var_a3 != NULL);
        }
        temp_a1->next = joint;
        joint->prev = temp_a1;
    }
}

void func_ovl2_800E6E00(Fighter_Struct *fp, s32 index)
{
    ftPartIndex *part_index;
    DObj *joint;
    DObj *temp_a0;
    DObj *temp_a1;
    DObj *var_v1;
    DObj *var_v0;

    part_index = &fp->attributes->p_ftpart_lookup[index];
    joint = fp->joint[part_index->partindex_0x0];

    func_ovl2_800D767C(joint->unk_0x84);

    temp_a1 = joint->next;
    temp_a0 = joint->prev;

    if (temp_a1 != NULL)
    {
        var_v1 = temp_a1;

        if (joint->unk_0xC == NULL)
        {
            temp_a0->next = temp_a1;
        }
        else
        {
            joint->unk_0xC->unk_0x8 = var_v1;
            var_v1->unk_0xC = (temp_a1 = joint)->unk_0xC;
        }
        var_v0 = var_v1->unk_0x8;
        var_v1->prev = temp_a0;

        while (var_v0 != NULL)
        {
            var_v1 = var_v0;
            var_v0->prev = temp_a0;
            var_v0 = var_v0->unk_0x8;
        }
        var_v1->unk_0x8 = joint->unk_0x8;
        var_v0 = joint->unk_0x8;

        if (var_v0 != NULL)
        {
            var_v0->unk_0xC = var_v1;
        }
    }
    else
    {
        if (joint->unk_0xC == NULL)
        {
            temp_a0->next = joint->unk_0x8;
        }
        else
        {
            joint->unk_0xC->unk_0x8 = joint->unk_0x8;
        }
        if (joint->unk_0x8 != NULL)
        {
            joint->unk_0x8->unk_0xC = joint->unk_0xC;
        }
    }
    fp->joint[part_index->partindex_0x0] = NULL;
    joint->unk_0x8 = NULL;
    joint->unk_0xC = NULL;
    joint->next = NULL;

    func_8000948C(joint);
}

extern ftIntroStatusDesc *D_ovl1_80390D20[];
extern ftIntroStatusDesc D_ovl1_80390BE8;
extern ftStatusDesc D_ovl2_80128DD8;
extern ftStatusDesc D_ovl2_80128E50;
extern ftStatusDesc *D_ovl2_8012FE90;
extern ftStatusDesc *D_ovl2_8012B740[];
extern ColAnimDesc D_ovl2_8012DBD4[];

void func_ovl2_800E6F24(GObj *fighter_gobj, s32 status_id, f32 frame_begin, f32 anim_rate, u32 flags)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    s32 event_ptr;
    ftCommonAttributes *attributes = fp->attributes;
    ftStatusDesc *status_struct;
    ftIntroStatusDesc *unk_callback;
    f32 anim_frame;
    s32 status_struct_id;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_s0_2;
    gmAttackFlags status_flags;
    gmAttackFlags attack_flags;
    s32 var_v0;
    s32 anim_id;
    void *event_script_ptr;
    DObjDesc *dobj_desc;
    s32 temp_t8;
    ftStatusDesc *status_desc;
    ftScriptInfoArray *script_array;
    ftScriptInfo *script_info;
    DObj *joint;
    DObj *temp_a1_3;
    DObj *temp_v1_2;
    ftData *temp_v1_3;
    s32 i;

    status_struct = NULL;
    unk_callback = NULL;

    status_flags = fp->flags_lw;

    if (fp->x191_flag_b0)
    {
        func_ovl2_800E0654(fighter_gobj);

        if (fp->proc_accessory != NULL)
        {
            fp->proc_accessory(fighter_gobj);
        }
    }

    fp->status_info.status_id = status_id;

    if (fp->lod_current != fp->lod_match)
    {
        func_ovl2_800E9198(fighter_gobj, fp->lod_match);
        fp->lod_current = fp->lod_match;
    }
    if (!(flags & 1) && (fp->is_hit_enable))
    {
        func_ovl2_800E8518(fighter_gobj);
    }
    if (!(flags & 0x200))
    {
        fp->throw_gobj = NULL;
    }
    if (!(flags & 0x10))
    {
        if (fp->x18C_flag_b1)
        {
            func_ovl2_800E880C(fighter_gobj, gmHitCollision_HitStatus_Normal);
        }
        if (fp->hit_status != gmHitCollision_HitStatus_Normal)
        {
            func_ovl2_800E8A24(fighter_gobj, gmHitCollision_HitStatus_Normal);
        }
    }
    if (fp->x18C_flag_b2)
    {
        func_ovl2_800E8B00(fighter_gobj);
    }
    if (!(flags & 0x20) && (fp->x18C_flag_b3))
    {
        func_ovl2_800E8ECC(fighter_gobj);
    }
    if (!(flags & 0x80) && (fp->x18C_flag_b4))
    {
        func_ovl2_800E96B0(fighter_gobj);
    }
    if (!(flags & 2) && (D_ovl2_8012DBD4[fp->colanim.colanim_id].unk_colanimdesc_0x1 != FALSE))
    {
        func_ovl2_800E98D4(fighter_gobj);
    }
    if (!(flags & 4) && (fp->is_statupdate_stop_gfx))
    {
        func_ovl2_800E9C3C(fighter_gobj);
    }
    fp->is_reflect = FALSE;
    fp->is_absorb = FALSE;
    fp->is_shield = FALSE;

    if (!(flags & 8))
    {
        fp->is_fast_fall = FALSE;
    }

    fp->is_invisible = FALSE;
    fp->x18E_flag_b0 = FALSE;
    fp->x18E_flag_b1 = FALSE;
    fp->x18E_flag_b3 = FALSE;
    fp->is_playing_gfx = FALSE;

    if (fp->status_info.pl_kind != Pl_Kind_Result)
    {
        func_ovl2_80115630(fp->port_id, 2);
        func_ovl2_80115630(fp->port_id, 3);

        if (!(flags & 0x4000))
        {
            func_ovl2_80115630(fp->port_id, 7);
        }
        fp->joint[0]->rotate.y = fp->lr * HALF_PI32;

        DObjGetStruct(fighter_gobj)->rotate.z = 0.0F;

        fp->joint[0]->rotate.x = DObjGetStruct(fighter_gobj)->rotate.z;

        fp->phys_info.vel_air.z = 0.0F;
        fp->phys_info.vel_ground.z = 0.0F;
    }

    fp->x18F_flag_b4 = FALSE;
    fp->is_hitstun = FALSE;

    fp->damage_mul = 1.0F;

    if ((fp->ground_or_air == ground) && !(flags & 0x1000))
    {
        fp->damage_port_id = -1;
    }
    if (!(flags & 0x40))
    {
        fp->slope_contour = 0;
    }
    fp->coll_data.ignore_line_id = -1;

    fp->x190_flag_b6 = TRUE;
    fp->x190_flag_b7 = FALSE;

    func_ovl2_800E8098(fp, 0);

    fp->is_stat_nodamage = FALSE;
    fp->is_damage_resist = FALSE;
    fp->x191_flag_b3 = FALSE;

    if (fp->x191_flag_b4567 != 3)
    {
        fp->x191_flag_b4567 = 0;
    }
    fp->fighter_cam_zoom_range = 1.0F;

    if (!(flags & 0x100))
    {
        fp->unk_0x174 = 0;
    }

    fp->x192_flag_b0 = FALSE;
    fp->x192_flag_b2 = FALSE;
    fp->x192_flag_b1 = FALSE;

    if (!(flags & 0x400))
    {
        fp->shuffle_timer = 0;
    }
    if (!(flags & 0x800))
    {
        func_ovl2_800E81E4(fp);
    }
    fp->knockback_resist_status = 0.0F;
    fp->damage_knockback_again = 0.0F;

    if (!(flags & 0x2000))
    {
        fp->afterimage.render_state = -1;
    }

    if ((status_id != ftStatus_Common_Wait) && (status_id != ftStatus_Common_WalkSlow) && (status_id != ftStatus_Common_WalkMiddle) && (status_id != ftStatus_Common_WalkFast))
    {
        fp->attack1_followup_frames = 0.0F;
    }
    if ((fp->status_info.pl_kind != 3) && (fp->unk_0x16 != 9))
    {
        func_ovl2_800E827C(fighter_gobj, 9);
    }
    fp->status_info.status_time_spent = 0;

    if (status_id >= 0x20000) // Check if Character Data status ID
    {
        status_id -= 0x20000;
    }
    if (status_id >= 0x1000F) // Check if Opening status ID 1
    {
        unk_callback = D_ovl1_80390D20[fp->ft_kind];
        status_struct_id = status_id - 0x1000F;
    }
    else if (status_id >= 0x10000) // Check if Opening status ID 2
    {
        unk_callback = &D_ovl1_80390BE8;
        status_struct_id = status_id - 0x10000;
    }
    else if (status_id >= 0xDC)
    {
        status_struct = D_ovl2_8012B740[fp->ft_kind];
        status_struct_id = status_id - 0xDC;
    }
    else if (status_id >= 6)
    {
        status_struct = &D_ovl2_80128E50;
        status_struct_id = status_id - 6;
    }
    else
    {
        status_struct = &D_ovl2_80128DD8;
        status_struct_id = status_id;
    }
    status_desc = &status_struct[status_struct_id];

    if (fp->status_info.pl_kind != 3)
    {
        if ((status_struct[status_struct_id].flags_h.flags_hi_0x3F == 0) || (status_struct[status_struct_id].flags_h.flags_hi_0x3F != fp->attack_id))
        {
            func_ovl2_800EA5E8(fp, status_struct[status_struct_id].flags_h.flags_hi_0x3F);
        }
        attack_flags = status_desc->flags_l;

        if ((attack_flags.flags_0x3FF == 0) || (attack_flags.flags_0x3FF != fp->flags_lw.flags_0x3FF))
        {
            func_ovl2_800EA778(fp, status_struct[status_struct_id].flags_l.halfword);
        }
    }

    if (fp->proc_status != NULL)
    {
        fp->proc_status(fighter_gobj);
        fp->proc_status = NULL;
    }
    func_ovl2_800EA7B0(fp, status_flags.halfword);

    if (status_struct != NULL)
    {
        anim_id = status_struct[status_struct_id].flags_h.anim_id;
        fp->status_info.script_id = anim_id;
        script_array = fp->ft_data->script1;
    }
    else
    {
        anim_id = unk_callback[status_struct_id].anim_id - 0x10000;
        fp->status_info.script_id = anim_id;
        script_array = fp->ft_data->script2;
    }

    if ((anim_id != -1) && (anim_id != -2))
    {
        script_info = &script_array->script_info[anim_id];

        if (script_info->anim_flags.flags.x19B_flag_b6)
        {
            fp->x9CC = (void*)((s32)script_info->anim_id + (u32)fp->ft_data->unk_0x38);
        }
        else
        {
            if (script_info->anim_id != 0)
            {
                rldm_get_file_external_force(script_info->anim_id, fp->x9D0);
                fp->x9CC = fp->x9D0;
            }
            else
            {
                fp->x9CC = NULL;
            }
        }

        if (fp->x9CC != NULL)
        {
            var_v1 = fp->anim_flags.word & 0xFFFFFFE0;
            fp->anim_flags.word = script_info->anim_flags.word;
            var_v0_3 = fp->anim_flags.word & 0xFFFFFFE0;

            for (i = 0; ((var_v1 != 0) || (var_v0_3 != 0)); i++, var_v0_3 <<= 1, var_v1 <<= 1)
            {
                if (!(var_v1 & (1 << 31)))
                {
                    if (var_v0_3 & (1 << 31))
                    {
                        func_ovl2_800E69C4(fp, i);
                    }
                }
                else if (var_v0_3 & (1 << 31))
                {
                    func_ovl2_800E6CE0(fp, i);
                }
                else func_ovl2_800E6E00(fp, i);
            }

            dobj_desc = attributes->dobj_desc_container[fp->lod_current - 1].dobj_desc;

            for (i = 4; dobj_desc->index != ARRAY_COUNT(fp->joint) / 2; i++, dobj_desc++)
            {
                joint = fp->joint[i];

                if (joint != NULL)
                {
                    joint->translate = dobj_desc->translate;
                    joint->rotate = dobj_desc->rotate;
                    joint->scale = dobj_desc->scale;
                    joint->unk_0x54 = 0;
                }
            }
            if (fp->anim_flags.flags.is_use_transn_joint)
            {
                joint = fp->joint[1];
                joint->unk_0x54 = 0;
                joint->translate.z = 0.0F;
                joint->translate.y = 0.0F;
                joint->translate.x = 0.0F;
                joint->rotate.z = 0.0F;
            }
            if (fp->anim_flags.flags.is_use_xrotn_joint)
            {
                joint = fp->joint[2];
                joint->translate.z = 0.0F;
                joint->translate.y = 0.0F;
                joint->translate.x = 0.0F;
                joint->rotate.z = 0.0F;
                joint->rotate.y = 0.0F;
                joint->rotate.x = 0.0F;
                joint->unk_0x54 = 0;
                joint->scale.z = 1.0F;
                joint->scale.y = 1.0F;
                joint->scale.x = 1.0F;
            }
            if (fp->anim_flags.flags.is_use_yrotn_joint)
            {
                joint = fp->joint[3];
                joint->translate.z = 0.0F;
                joint->translate.y = 0.0F;
                joint->translate.x = 0.0F;
                joint->rotate.z = 0.0F;
                joint->rotate.y = 0.0F;
                joint->rotate.x = 0.0F;
                joint->unk_0x54 = 0;
                joint->scale.z = 1.0F;
                joint->scale.y = 1.0F;
                joint->scale.x = 1.0F;
            }
            func_ovl0_800C87F4(fp->joint[0]->next, fp->x9CC, frame_begin);

            if (anim_rate != DObjGetStruct(fighter_gobj)->unk_dobj_0x78)
            {
                func_8000BB04(fighter_gobj, anim_rate);
            }
            if (fp->anim_flags.flags.is_use_transn_joint)
            {
                joint = fp->joint[1];

                temp_a1_3 = joint->prev;
                temp_v1_2 = joint->next;
                temp_a1_3->next = temp_v1_2;
                temp_v1_2->prev = temp_a1_3;
                temp_v1_2->prev = temp_a1_3;
                temp_v1_2->unk_0x8 = joint;
                joint->unk_0xC = temp_v1_2;
                joint->prev = temp_v1_2->prev;
                joint->next = NULL;
            }

            if (fp->x190_flag_b3)
            {
                if (!(fp->anim_flags.flags.x19B_flag_b7))
                {
                    func_ovl2_800EB6EC(fp);
                }
            }
            else if (fp->anim_flags.flags.x19B_flag_b7)
            {
                func_ovl2_800EB7F4(fp);
            }

            fp->x190_flag_b3 = fp->anim_flags.flags.x19B_flag_b7;

            if (attributes->unk_0x324 != NULL)
            {
                if (fp->anim_flags.flags.x19B_flag_b5)
                {
                    fp->x18F_flag_b5 = FALSE;
                }
                else fp->x18F_flag_b5 = TRUE;
            }
        }
        if (status_struct != NULL)
        {
            if (script_info->offset != 0x80000000)
            {
                // Actually subaction scripts?
                if (fp->anim_flags.flags.x19B_flag_b3)
                {
                    event_ptr = fp->ft_data->unk_0x30->x0;

                    event_script_ptr = (void*)((uintptr_t)script_info->offset + (intptr_t)event_ptr);
                }
                else
                {
                    event_ptr = fp->ft_data->unk_0x2C->x0;

                    event_script_ptr = (void*)((uintptr_t)script_info->offset + (intptr_t)event_ptr);
                }
            }
            else event_script_ptr = NULL;

            fp->script_event[0][0].p_script = fp->script_event[1][0].p_script = event_script_ptr;
        }
        else
        {
            if (script_info->offset != 0x80000000)
            {
                event_script_ptr = (void*)script_info->offset;
            }
            else event_script_ptr = NULL;

            fp->script_event[0][0].p_script = fp->script_event[1][0].p_script = event_script_ptr;
        }
        anim_frame = DObjGetStruct(fighter_gobj)->unk_dobj_0x78 - frame_begin;

        fp->script_event[0][0].frame_timer = fp->script_event[1][0].frame_timer = anim_frame;

        fp->script_event[0][0].script_index = fp->script_event[1][0].script_index = 0;

        for (i = 1; i < ARRAY_COUNT(fp->script_event); i++)
        {
            fp->script_event[0][i].p_script = fp->script_event[1][i].p_script = NULL;
        }

        if (frame_begin != 0.0F)
        {
            func_ovl2_800E0858(fighter_gobj);
        }
        else
        {
            func_ovl2_800E0830(fighter_gobj);
            func_ovl2_800E11C8(fighter_gobj);
        }
    }
    else for (i = 0; i < ARRAY_COUNT(fp->script_event); i++)
    {
        fp->script_event[0][i].p_script = fp->script_event[1][i].p_script = NULL;
    }
    if (fp->status_info.pl_kind != Pl_Kind_Result)
    {
        fp->proc_update = status_struct[status_struct_id].proc_update;
        fp->proc_interrupt = status_struct[status_struct_id].proc_interrupt;
        fp->proc_physics = status_struct[status_struct_id].proc_physics;
        fp->proc_map = status_struct[status_struct_id].proc_map;
        fp->proc_slope = func_ovl2_800DE150;
        fp->proc_accessory = NULL;
        fp->proc_damage = NULL;
        fp->proc_trap = NULL;
        fp->proc_hit = NULL;
        fp->proc_shield = NULL;
        fp->proc_gfx = NULL;
        fp->proc_lagupdate = NULL;
        fp->proc_lagstart = NULL;
        fp->proc_lagend = NULL;
    }
    else if (unk_callback != NULL)
    {
        fp->proc_update = unk_callback[status_struct_id].proc_update;
    }
    else fp->proc_update = NULL;
}
