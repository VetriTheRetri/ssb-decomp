#ifndef _GMMATCH_H_
#define _GMMATCH_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define GMMATCH_PLAYERS_MAX 4 // Global limit for simultaneous players in a match

typedef enum gmPauseStatus
{
    gmPauseStatus_Disable,        // Pausing not allowed
    gmPauseStatus_Enable,         // Pausing allowed
    gmPauseStatus_Paused,         // Player paused
    gmPauseStatus_Unpause         // Player unpaused

} gmPauseStatus;

typedef struct gmItemSpawn
{
    u8 max_items; // Maximum number of items allowed to spawn?
    u8 *item_toggles; // Pointer to array of item on/off toggles
    u32 item_spawn_timer; // Spawn a random new item when this reaches 0
    void *unk_0xC;
    u32 unk_0x10;
    s8 unk_0x14;
    u8 *unk_0x18;
    u16 unk_0x1C; // Also max items?
    u16 *unk_0x20;

} gmItemSpawn;

typedef struct Unk_8017301C_Halfword // CODE RED, return to this later (it matches but NEEDS cleanup)
{
    u16 unk_0x0[1];

} Unk_8017301C_Halfword;

typedef struct Unk_8018D048
{
    u8 filler_0x0[0x8];
    u8 unk_0x8;
    u8 *unk_0xC;
    u16 unk_0x10;
    u16 *unk_0x14;

} Unk_8018D048; // Found in func_ovl3_8016EF40, very similar similar to gmItemSpawn

typedef struct Unk_80131460_Ptr74
{
    u8 filler_0x0[0x3C];
    Vec3f unk_p_80131460_vec;
    f32 unk_0x48;

} Unk_80131460_Ptr74;

typedef struct Unk_80131460
{
    u8 filler_0x0[0x74];
    Unk_80131460_Ptr74 *unk_0x74;

} Unk_80131460;

typedef struct Unk_801314B0
{
    u8 filler_0x0[0x38];
    Vec3i unk_0x38;

} Unk_801314B0;

extern Unk_80131460 *D_ovl2_80131460;
extern void *D_ovl2_80131470;
extern Unk_801314B0 D_ovl2_801314B0;

typedef struct gmUnkInfo_80131308
{
    u8 filler_0x0[0x24];
    f32 unk_80131308_0x24;
    f32 unk_80131308_0x28;
    f32 unk_80131308_0x2C;
    f32 unk_80131308_0x30;

} gmUnkInfo_80131308;

typedef struct gmPlayerBlock
{
    u8 level; // Actually begins at 1 instead of 0
    u8 handicap; // Master Hand's handicap value is 35!?
    u8 player_kind; // 0 = HMN, 1 = CPU, 5 = How to Play (?)
    u8 character_kind; // Same as ftKind
    u8 team_index;
    u8 port_id; // Identical to team index if team battle is on?
    u8 costume_index;
    u8 shade_index; // Color overlay applied when several players use the same costume
    u8 unk_0x8;
    u8 unk_0x9;
    u8 unk_0xA;
    s8 stock_count; // -1 = player has no stocks
    u8 is_rebirth_multi; // Respawn flag of multi-man enemy teams (Yoshi, Kirby, Fighting Polygons) in 1P mode
    s32 falls;
    s32 score; // Caps at positive 999, crashes if way too low
    s32 total_ko_player[GMMATCH_PLAYERS_MAX]; // KOs scored on other players
    u8 filler_0x28[0x30 - 0x28];
    s32 total_self_destruct; // Applied when damaging player's ID is -1 or GMMATCH_PLAYERS_MAX
    s32 total_damage_dealt; // Total damage dealt to all players
    s32 total_damage_all; // Damage received from all hazards
    s32 total_damage_player[GMMATCH_PLAYERS_MAX]; // Total damage received from each player present
    s32 stock_damage_all;  // All damage received per current stock, from any hazard
    s32 combo_damage_foe; // Total damage from consecutive hits dealt by foes (Resets when hitstun ends)
    s32 combo_count_foe; // Number of consecutive hits received from foes (Resets when hitstun ends)
    GObj *fighter_gobj; // Pointer to player's fighter GObj
    u32 stale_index; // Current position in stale queue?
    u16 stale_flags[5][2];

} gmPlayerBlock;

typedef struct gmMatchInfo
{
    u8 game_type;
    u8 gr_kind;
    u8 is_team_battle;
    u8 match_type; // 1 = stock, 2 = time
    u8 unk_0x4;
    u8 unk_0x5;
    u8 unk_0x6;
    u8 stock_setting; // Number of stocks set in game rules
    u8 handicap_setting; // 0 = OFF, 1 = ON, 2 = AUTO
    u8 is_team_attack; // Boolean for friendly fire
    u8 unk_0xA;
    u8 unk_0xB;
    u32 item_toggles; // Bits = item's on/off switch from match settings
    u8 unk_0x10;
    u8 pause_status;
    u8 unk_0x12;
    u8 unk_0x13;
    u32 match_time_remain; // Frames remaining until timeout
    u32 match_time_current; // Current match frame, counts up from 0
    u8 item_switch; // Has various settings (0x0 on Master Hand and Giant DK (?), 0x1 on Metal Mario battle, 0x2 on Hyrule Castle, 0x3 on various stages, 0x4 on Polygon Team? 
    u32 unk_minfo_0x1D_b0 : 1;
    u32 unk_minfo_0x1D_b1 : 1;
    u32 unk_minfo_0x1D_b2 : 1;
    u32 unk_minfo_0x1D_b3 : 1;
    u32 unk_minfo_0x1D_b4 : 1;
    u32 unk_minfo_0x1D_b5 : 1;
    u32 unk_minfo_0x1D_b6 : 1;
    u32 unk_minfo_0x1D_b7 : 1;
    u32 unk_0x1E : 8;
    u32 unk_0x1F : 8;
    gmPlayerBlock player_block[GMMATCH_PLAYERS_MAX]; // Holds data for each player

} gmMatchInfo;

extern gmMatchInfo *Match_Info;

#endif