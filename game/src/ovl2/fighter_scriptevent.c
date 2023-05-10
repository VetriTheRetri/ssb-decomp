#include "fighter.h"

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

        if (fp->status_info.pl_kind != 3)
        {
            hit_id = gmScriptEventCast(p_event, gmScriptEventCreateHit1)->hit_id;
            ft_hit = &fp->fighter_hit[hit_id];

            if ((ft_hit->update_state == gmHitCollision_UpdateState_Disable) || (ft_hit->unk_0x4 != gmScriptEventCast(p_event, gmScriptEventCreateHit1)->group_id))
            {
                ft_hit->unk_0x4 = gmScriptEventCast(p_event, gmScriptEventCreateHit1)->group_id;
                ft_hit->update_state = gmHitCollision_UpdateState_New;
                fp->is_hit_enable = TRUE;

                for (i = 0; i < ARRAY_COUNT(fp->fighter_hit); i++)
                {
                    if ((i != hit_id) && (fp->fighter_hit[i].update_state != gmHitCollision_UpdateState_Disable) && (ft_hit->unk_0x4 == fp->fighter_hit[i].unk_0x4))
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

        hit_id = gmScriptEventCast(p_event, gmScriptEventSetHitOff1)->hit_id;
        ft_hit = &fp->fighter_hit[hit_id];

        ft_hit->offset.x = gmScriptEventCast(p_event, gmScriptEventSetHitOff1)->off_x;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitOff1);

        ft_hit->offset.y = gmScriptEventCast(p_event, gmScriptEventSetHitOff2)->off_y;
        ft_hit->offset.z = gmScriptEventCast(p_event, gmScriptEventSetHitOff2)->off_z;

        gmScriptEventUpdatePtr(p_event, gmScriptEventSetHitOff2);
        break;

    case gmScriptEvent_Kind_SetHitDamage:

        if (fp->status_info.pl_kind != 3)
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

        if (!(fp->x18E_flag_b5))
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
        if (fp->status_info.pl_kind != 3)
        {
            func_ovl2_800E806C(fp, gmScriptEventCast(p_event, gmScriptEventUnk31)->value2, gmScriptEventCast(p_event, gmScriptEventUnk31)->value1);
        }
        gmScriptEventUpdatePtr(p_event, gmScriptEventUnk31);

        break;

    case gmScriptEvent_Kind_Unk16:
        if (fp->status_info.pl_kind != 3)
        {
            func_ovl2_80115630(fp->port_id, gmScriptEventCast(p_event, gmScriptEventUnk32)->value1);
        }
        gmScriptEventUpdatePtr(p_event, gmScriptEventUnk32);

        break;
    }
}