#ifndef _GMMATCH_H_
#define _GMMATCH_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define DARIANTOU_CHR_PLAYABLE_MAX 12
#define GMMATCH_PLAYERS_MAX 4 // Global limit for simultaneous players in a match

#define gmSaveChrMask(kind) (1 << kind)

#define GMSAVEINFO_CHARACTER_MASK_ALL \
(                                     \
    gmSaveChrMask(Ft_Kind_Mario)  |   \
    gmSaveChrMask(Ft_Kind_Fox)    |   \
    gmSaveChrMask(Ft_Kind_Donkey) |   \
    gmSaveChrMask(Ft_Kind_Samus)  |   \
    gmSaveChrMask(Ft_Kind_Luigi)  |   \
    gmSaveChrMask(Ft_Kind_Link)   |   \
    gmSaveChrMask(Ft_Kind_Yoshi)  |   \
    gmSaveChrMask(Ft_Kind_Captain)|   \
    gmSaveChrMask(Ft_Kind_Kirby)  |   \
    gmSaveChrMask(Ft_Kind_Pikachu)|   \
    gmSaveChrMask(Ft_Kind_Purin)  |   \
    gmSaveChrMask(Ft_Kind_Ness)       \
)                                     \

typedef enum gmSaveUnlock
{
    gmSave_Unlock_Ness = 1,
    gmSave_Unlock_Captain,
    gmSave_Unlock_Purin,
    gmSave_Unlock_Unk,
    gmSave_Unlock_Luigi

} gmSaveUnlock;

#define GMSAVE_UNLOCK_MASK_NESS     (1 << gmSave_Unlock_Ness)
#define GMSAVE_UNLOCK_MASK_CAPTAIN  (1 << gmSave_Unlock_Captain)
#define GMSAVE_UNLOCK_MASK_PURIN    (1 << gmSave_Unlock_Purin)
#define GMSAVE_UNLOCK_MASK_LUIGI    (1 << gmSave_Unlock_Luigi)

typedef enum gmPauseStatus
{
    gmPauseStatus_Disable,        // Pausing not allowed
    gmPauseStatus_Enable,         // Pausing allowed
    gmPauseStatus_Paused,         // Player paused
    gmPauseStatus_Unpause         // Player unpaused

} gmPauseStatus;

typedef enum gmMatchGameType
{
    gmMatch_GameType_1PGame = 5

} gmMatchGameType;

typedef enum gmSceneIndex
{
    gmSceneIndex_Challenger_Ness = 0xF,
    gmSceneIndex_Challenger_Purin,
    gmSceneIndex_Challenger_Captain

} gmSceneIndex;

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

static gmUnkInfo_80131308 D_ovl2_80131308;

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

struct RecordCharCombo {
    /* 0x00 */ u16 gamesWith;
    /* 0x02 */ u16 playedAgainst;
}; // size == 4

struct VsRecordData {
    /* 0x00 */ u16 kos[DARIANTOU_CHR_PLAYABLE_MAX];
    /* 0x18 */ u32 timeUsed; //< in seconds
    /* 0x1C */ u32 damageDealt;
    /* 0x20 */ u32 damageReceived;
    /* 0x24 */ u16 totalSDs;
    /* 0x26 */ u16 gamesPlayed;
    /* 0x28 */ u16 gamesPlayedAgainst;
    /* 0x2C */ struct RecordCharCombo combinations[DARIANTOU_CHR_PLAYABLE_MAX];
}; // size == 0x5C

struct SinglePlayerData
{
    u32 spgame_hiscore;
    u32 spgame_continues;
    u32 spgame_bonuses;
    s8 spgame_best_difficulty;
    u32 tt_time; // Break the Targets high score
    u8 bt_target_count; // Targets broken
    u32 bp_time; // Board the Platforms high scoree
    u8 bp_platform_count; // Platforms boarded
    u8 unk_0x1D;
    u8 unk_0x1E;
    u8 unk_0x1F;
};

// is this the saved data structure?
struct gmSaveInfo {
    /* 0x000 */ struct VsRecordData vsRecords[DARIANTOU_CHR_PLAYABLE_MAX];
    u8 unk450;
    u8 unk451;
    u8 unk452;
    u8 unk453;
    u8 unk454;
    u8 unk455;
    u8 unk456;
    u8 unlock_mask;
    u16 unk458;
    u8 spgame_difficulty;
    u8 spgame_stock_count;
    struct SinglePlayerData spgame_records[DARIANTOU_CHR_PLAYABLE_MAX];
    u16 unk5DC;
    u8 unk5DE;
    u8 unk5DF;
    u8 unk5E0;
    u8 unk5E1;
    u8 unk5E2;
    u8 unk5E3;
    u8 unk5E4;
    u8 unk5E5;
    u8 unk5E6;
    u8 unk5E7;
    u32 unk5E8;
}; // size == 0x5EC

struct gmSceneInfo
{
    u8 scene_current;
    u8 scene_previous;
    u8 unk02;
    u8 pad03[0x09 - 0x03];
    u8 unk09;
    u8 unk0A;
    u8 pad0B[0xF - 0xB];
    u8 unk0F;
    u8 unk10;
    u8 is_select_continue;
    u8 unk12;
    u8 player_port;
    u8 ft_kind;
    u8 unk15;
    u8 pad16[0x17 - 0x16];
    u8 scene_queue; // Unconfirmed
    u8 cpu_port[3];
    u8 pad20[0x20 - 0x1B];
    u32 spgame_score;
    u32 continues_used;
    u32 bonuses; // Number of bonuses player acquired throughout the game
    u32 bonus_get_mask[5]; // Different bonuses the player has accumulated per match
    u8 pad2C[0x43 - 0x40];
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
}; // size == 0x48

extern gmMatchInfo *Match_Info;
extern struct gmSaveInfo Save_Info;
extern struct gmSceneInfo Scene_Info;

#endif