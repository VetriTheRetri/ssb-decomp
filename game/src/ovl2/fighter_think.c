#include "fighter.h"
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

            if ((ft_hit->update_state == gmHitCollision_UpdateState_Disable) || (ft_hit->group_id != gmScriptEventCast(p_event, gmScriptEventCreateHit1)->group_id))
            {
                ft_hit->group_id = gmScriptEventCast(p_event, gmScriptEventCreateHit1)->group_id;
                ft_hit->update_state = gmHitCollision_UpdateState_New;
                fp->is_hit_enable = TRUE;

                for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
                {
                    if ((i != hit_id) && (fp->fighter_hit[i].update_state != gmHitCollision_UpdateState_Disable) && (ft_hit->group_id == fp->fighter_hit[i].group_id))
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
        if (pl->stick_range.y >= 0x14)
        {
            if (pl->stick_prev.y >= 0x14)
            {
                this_fp->tap_stick_y++, this_fp->hold_stick_y++;
            }
            else this_fp->tap_stick_y = this_fp->hold_stick_y = 1;
        }
        else if (pl->stick_range.y <= -0x14)
        {
            if (pl->stick_prev.y <= -0x14)
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

            if (this_fp->cb_hitlag_end != NULL)
            {
                this_fp->cb_hitlag_end(fighter_gobj);
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
            this_fp->special_status = 1;

            if (this_fp->colanim.colanim_id == 0x4A)
            {
                func_ovl2_800E98D4(fighter_gobj);
            }
        }
        else if (this_fp->star_invincible_timer == 120)
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
    if (this_fp->cb_update_gfx != NULL)
    {
        this_fp->cb_update_gfx(fighter_gobj);
    }
    if (this_fp->hitlag_timer == 0)
    {
        if ((this_fp->unk_0x174 > 1) && !(this_fp->x18F_flag_b6))
        {
            this_fp->unk_0x174--;
        }
        if (this_fp->cb_anim != NULL)
        {
            this_fp->cb_anim(fighter_gobj);
        }
        if (this_fp->cb_interrupt != NULL)
        {
            this_fp->cb_interrupt(fighter_gobj);
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
        D_ovl2_80131190[i].ogobj = NULL;
    }
}

bool32 func_ovl2_800E1D48(GObj *ogobj, bool32(*proc_update)(GObj *, GObj *, s32 *))
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

bool32 func_ovl2_800E1DE8(GObj *ogobj, bool32(*proc_update)(GObj *, GObj *, s32 *))
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_ovl2_80131190); i++)
    {
        if (D_ovl2_80131190[i].ogobj == NULL)
        {
            D_ovl2_80131190[i].ogobj = ogobj;
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
        if (D_ovl2_80131190[i].ogobj == ogobj)
        {
            D_ovl2_80131190[i].ogobj = NULL;
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

    if (!fp->is_ignore_blastzone_top)
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
        if (fp->cb_physics != NULL)
        {
            fp->cb_physics(fighter_gobj);
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
    if (fp->unk_0xA00 != NULL)
    {
        fp->unk_0xA00(fighter_gobj);
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
    if (fp->cb_coll != NULL)
    {
        fp->coll_data.coll_mask_prev = fp->coll_data.coll_mask;
        fp->coll_data.coll_mask = 0U;
        fp->coll_data.unk_0x64 = FALSE;
        fp->coll_data.coll_type = 0;
        fp->coll_data.unk_0x58 = 0;

        fp->cb_coll(fighter_gobj);

        if (fp->ft_kind == Ft_Kind_Kirby)
        {
            func_ovl2_800EB39C(fighter_gobj);
        }
    }
    if (fp->cb_update_ik != NULL)
    {
        fp->cb_update_ik(fighter_gobj);
    }
    func_ovl2_800EB528(fp->joint[0]);

    if (fp->hitlag_timer == 0)
    {
        func_ovl2_800E0654(fighter_gobj);
    }
    if (fp->hitlag_timer == 0)
    {
        if (fp->cb_accessory != NULL)
        {
            fp->cb_accessory(fighter_gobj);
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

void func_ovl2_800E26BC(Fighter_Struct *fp, s32 group_id, GObj *victim_gobj, s32 hitbox_type, u32 interact_mask, bool32 is_shield_hit)
{
    s32 i, j;

    for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
    {
        if (i == ARRAY_COUNT(fp->fighter_hit));

        if ((fp->fighter_hit[i].update_state != gmHitCollision_UpdateState_Disable) && (group_id == fp->fighter_hit[i].group_id))
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
                        fp->fighter_hit[i].hit_targets[j].victim_flags.interact_mask = interact_mask;
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
                    fp->fighter_hit[i].hit_targets[j].victim_flags.interact_mask = interact_mask;
                    break;

                default:
                    break;
                }
            }
            if (is_shield_hit == FALSE)
            {
                D_ovl2_801311A0[i] = 0;
            }
            else D_ovl2_801311B0[i] = 0;
        }
    }
}