#ifndef _FTMASTERHAND_STATUSVARS_H_
#define _FTMASTERHAND_STATUSVARS_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef struct MasterHand_Struct
{
    GObj *target_gobj; // (Fighter) GObj pointer of Master Hand's target
    void *unk_0x4;
    s32 unk_0x8;
    f32 unk_0xC;
    u32 wait_timer; // Wait this many frames until next attack
    s8 unk_0x14;
    u8 unk_0x15;
    u8 unk_0x16; // Struct probably ends here
    u8 unk_0x17;

} MasterHand_Struct;

typedef struct ftMasterHand_FighterVars
{
    MasterHand_Struct *p_masterhand;
    MasterHand_Struct s;

} ftMasterHand_FighterVars;

typedef struct ftMasterHand_Wait_StatusVars
{
    Vec3f pos;

} ftMasterHand_Wait_StatusVars;

typedef struct ftMasterHand_Move_StatusVars
{
    void (*cb)(GObj*);
    Vec3f vel;
    f32 magnitude;

} ftMasterHand_Move_StatusVars;

typedef struct ftMasterHand_Okhuikouki_StatusVars
{
    Vec3f pos;

} ftMasterHand_Okuhikouki_StatusVars;

typedef struct ftMasterHand_Gootsubu_StatusVars
{
    s16 wait_timer;
    f32 pos_x1;
    f32 pos_x2;

} ftMasterHand_Gootsubu_StatusVars;

typedef struct ftMasterHand_Tsutsuku_StatusVars
{
    s16 wait_timer;

} ftMasterHand_Tsutsuku_StatusVars;

typedef struct ftMasterHand_Drill_StatusVars
{
    s16 follow_timer; // Follow player for this many frames?
    f32 pos_x1;
    f32 pos_x2;

} ftMasterHand_Drill_StatusVars;

typedef struct ftMasterHand_Yubideppou_StatusVars
{
    s16 wait_timer;
    s16 bullet_count;
    u8 shoot_timer;

} ftMasterHand_Yubideppou_StatusVars;

typedef struct ftMasterHand_Okupunch_StatusVars
{
    Vec3f pos;

} ftMasterHand_Okupunch_StatusVars;

typedef struct ftMasterHand_Okutsubushi_StatusVars
{
    Vec3f pos;
    u16 follow_timer;

} ftMasterHand_Okutsubushi_StatusVars;

typedef struct ftMasterHand_Dead_StatusVars
{
    s16 dead_timer;

} ftMasterHand_Dead_StatusVars;

typedef union ftMasterHand_StatusVars
{
    ftMasterHand_Wait_StatusVars wait;
    ftMasterHand_Move_StatusVars move;
    ftMasterHand_Okuhikouki_StatusVars okuhikouki;
    ftMasterHand_Gootsubu_StatusVars gootsubu;
    ftMasterHand_Drill_StatusVars drill;
    ftMasterHand_Yubideppou_StatusVars yubideppou;
    ftMasterHand_Okupunch_StatusVars okupunch;
    ftMasterHand_Okutsubushi_StatusVars okutsubushi;
    ftMasterHand_Dead_StatusVars dead;

} ftMasterHand_StatusVars;

#endif