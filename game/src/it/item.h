#ifndef _ITEM_H_
#define _ITEM_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/it/itemvars.h>
#include <game/src/gm/gmmisc.h>
#include <game/src/gm/gmsound.h>
#include <game/src/ef/effect.h>

#define ARTICLE_ALLOC_MAX 16

#define ARTICLE_FLAG_PROJECT (1U << 31)            // Perform initial collision check when spawning item?

#define ARTICLE_MASK_SPAWN_FIGHTER 0               // Article spawned by fighter
#define ARTICLE_MASK_SPAWN_GROUND 1                // Article spawned by stage 
#define ARTICLE_MASK_SPAWN_ITEM 2                  // Article spawned by another item
#define ARTICLE_MASK_SPAWN_ARTICLE 3               // Article spawned by Pokémon / misc entity class(es?)
#define ARTICLE_MASK_SPAWN_DEFAULT 4

#define ARTICLE_MASK_SPAWN_ALL 0xF                 // Mask all GObj classes that can spawn items?

#define ARTICLE_TEAM_DEFAULT 4U // Article is teamless; deals damage to any eligible target
#define ARTICLE_PORT_DEFAULT 4U
#define ARTICLE_UNK_DEFAULT 9U // Handicap?
#define ARTICLE_STALE_DEFAULT 1.0F

#define ARTICLE_PICKUP_WAIT_DEFAULT 1400           // "Lifetime" while item is not being carried

#define ARTICLE_REFLECT_MAX_DEFAULT 100            // Maximum damage cap for reflected articles
#define ARTICLE_REFLECT_MUL_DEFAULT 1.8F           // Universal reflect damage multiplier
#define ARTICLE_REFLECT_ADD_DEFAULT 0.99F          // Added after multiplying article's hitbox damage

#define ARTICLE_DESPAWN_FLASH_START_DEFAULT 180U // Article starts flashing rapidly once its lifetime (?) drops below this value
#define ARTICLE_ARROW_BLINK_INT_DEFAULT 45 // Red arrow pointing downward at article "blinks" at this frequency (45 frames visible, 45 frames invisible)

#define ARTICLE_REHIT_TIME_DEFAULT 16

#define ARTICLE_DEFLECT_ANGLE_DEFAULT F_DEG_TO_RAD(135.0F) // 2.3561945F

#define ARTICLE_SPIN_SPEED_MUL_DEFAULT 0.31415927F
#define ARTICLE_SPIN_SPEED_MUL_NEW_SPAWN 0.17453294F
#define ARTICLE_SPIN_SPEED_MUL_PREV_SPAWN 0.27925268F

#define ARTICLE_SPIN_SPEED_SET_SMASH_THROW -0.36651915F
#define ARTICLE_SPIN_SPEED_SET_NORMAL_THROW -0.17453294F

#define ARTICLE_SPIN_SPEED_FRACTION_DEFAULT 0.01F // Also multiplies spin speed

typedef enum atKind
{
    // Common articles

    It_Kind_CommonStart,                        // Start of common item IDs
    It_Kind_Box = It_Kind_CommonStart,          // Crate
    It_Kind_Taru,                               // Barrel
    It_Kind_Capsule,                            // Capsule
    It_Kind_Egg,                                // Egg
    It_Kind_Tomato,                             // Maxim Tomato
    It_Kind_Heart,                              // Heart
    It_Kind_Star,                               // Star Man
    It_Kind_Sword,                              // Beam Sword
    It_Kind_Bat,                                // Home-Run Bat
    It_Kind_Harisen,                            // Fan
    It_Kind_StarRod,                            // Star Rod
    It_Kind_L_Gun,                              // Ray Gun
    It_Kind_F_Flower,                           // Fire Flower
    It_Kind_Hammer,                             // Hammer
    It_Kind_MSBomb,                             // Motion-Sensor Bomb
    It_Kind_BombHei,                            // Bob-Omb
    It_Kind_It_Bumper,                          // Bumper (Item)
    It_Kind_G_Shell,                            // Green Shell
    It_Kind_R_Shell,                            // Red Shell
    It_Kind_M_Ball,                             // Poké Ball
    It_Kind_CommonEnd = It_Kind_M_Ball,         // End of common item IDs

    // Character articles

    It_Kind_FighterStart,                       // Start of fighter item IDs
    It_Kind_PKFire = It_Kind_FighterStart,     // PK Fire pillar
    It_Kind_Link_Bomb,                          // Link's Bomb
    It_Kind_FighterEnd = It_Kind_Link_Bomb,     // End of fighter item IDs

    // Stage hazards

    It_Kind_GroundStart,                        // Start of stage hazard IDs
    It_Kind_PowerBlock = It_Kind_GroundStart,   // POW block
    It_Kind_Gr_Bumper,                          // Bumper (Peach's Castle)
    It_Kind_Pakkun,                             // Pirahna Plant
    It_Kind_Mato,                               // Target
    It_Kind_RaceBomb,                           // Race to the Finish bomb

    It_Kind_GrMonsterStart,                     // Start of stage Pokémon
    It_Kind_Gr_Lucky = It_Kind_GrMonsterStart,  // Chansey (Saffron City)
    It_Kind_Marumine,                           // Electrode
    It_Kind_Hitokage,                           // Charmander
    It_Kind_Fushigibana,                        // Venusaur
    It_Kind_Porygon,                            // Porygon
    It_Kind_GroundEnd = It_Kind_Porygon,        // End of stage hazard IDs
    It_Kind_GrMonsterEnd = It_Kind_GroundEnd,   // End of stage Pokémon

    // Pokémon

    It_Kind_MbMonsterStart,                     // Start of Pokémon item IDs
    It_Kind_Iwark = It_Kind_MbMonsterStart,     // Onix
    It_Kind_Kabigon,                            // Snorlax
    It_Kind_Tosakinto,                          // Goldeen
    It_Kind_Nyars,                              // Meowth
    It_Kind_Lizardon,                           // Charizard
    It_Kind_Spear,                              // Beedrill
    It_Kind_Kamex,                              // Blastoise
    It_Kind_Mb_Lucky,                           // Chansey (Poké Ball)
    It_Kind_Starmie,                            // Starmie
    It_Kind_Sawamura,                           // Hitmonlee
    It_Kind_Dogas,                              // Koffing
    It_Kind_Pippi,                              // Clefairy
    It_Kind_Mew,                                // Mew
    It_Kind_MbMonsterEnd = It_Kind_Mew,         // End of Pokémon item IDs

    It_Kind_CustomStart                         // Start of custom item IDs (future modding?)

} atKind;

typedef enum itWeight
{
    It_Weight_Heavy,
    It_Weight_Light

} itWeight;

typedef enum atType
{
    It_Type_Ground,     // Item is spawned by the stage (?)
    It_Type_Swing,      // Item can be thrown and swung
    It_Type_Shoot,      // Item can be fired
    It_Type_Throw,      // Item can only be thrown
    It_Type_Touch,      // Item has special properties on interaction
    It_Type_Special,    // Hammer, Heart and Maxim Tomato?
    It_Type_Fighter     // Item spawned by fighter's item (projectile) ?

} atType; 

typedef struct gmMonsterInfo
{
    u8 monster_curr;
    u8 monster_prev;
    u8 monster_index[44];
    u8 monster_count;

} gmMonsterInfo;

static gmMonsterInfo Monster_Info; // Static (.bss) (0x8018D060)

typedef struct ArticleFileData
{
    f32 spawn_vel_y[20];

} ArticleFileData;

typedef struct itCreateDesc
{
    s32 it_kind;
    void **p_file;
    intptr_t offset;
    u8 unk_aspd_0xC;
    u8 unk_aspd_0xD;
    u8 unk_aspd_0xE;
    s32 update_state;
    bool32 (*proc_update)(GObj*);
    bool32 (*proc_map)(GObj*);
    bool32 (*proc_hit)(GObj*);
    bool32 (*proc_shield)(GObj*);
    bool32 (*proc_hop)(GObj*);
    bool32 (*proc_setoff)(GObj*);
    bool32 (*proc_reflector)(GObj*);
    bool32 (*proc_damage)(GObj*);

} itCreateDesc;

extern void *gItemFileData; // WARNING: This pointer exists in multiple areas and appears not to be exclusive to the Article section of Overlay 3 (0x8018D040)

typedef struct ArticleHitUnk
{
    Vec3f pos;
    Vec3f pos_prev;
    s32 unk_0x18;
    u8 filler_0x1C[0x5C - 0x1C];
    f32 unk_0x5C;

} ArticleHitUnk;

typedef struct _ArticleHitArray
{
    GObj *victim_gobj;
    gmHitCollisionFlags victim_flags;

} ArticleHitArray;

typedef struct itStatusDesc
{
    bool32 (*proc_update)(GObj*);
    bool32 (*proc_map)(GObj*);
    bool32 (*proc_hit)(GObj*);
    bool32 (*proc_shield)(GObj*);
    bool32 (*proc_hop)(GObj*);
    bool32 (*proc_setoff)(GObj*);
    bool32 (*proc_reflector)(GObj*);
    bool32 (*proc_damage)(GObj*);

} itStatusDesc;

typedef struct _Item_Hit
{
    s32 update_state; // 0x0
    s32 damage; // 0x4
    f32 stale; // Might be swapped with throw_mul
    f32 throw_mul; // Might be swapped with stale
    s32 element; // 0xC // Placed AFTER offset?
    Vec3f offset[2]; // 0x10 - 0x28    
    f32 size;
    s32 angle;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    s32 shield_damage; // Shield damage?
    s32 priority; // Priority?
    u8 interact_mask; // Mask of object classes hitbox can interact with; 0x1 = fighters, 0x2 = items, 0x4 = articles
    u16 hit_sfx;
    u32 clang : 1;
    u32 can_rehit_item : 1;
    u32 can_rehit_fighter : 1;
    u32 can_rehit_shield : 1; // Article can rehit targets after default rehit cooldown expires
    u32 can_hop : 1;
    u32 can_reflect : 1;
    u32 can_shield : 1; // Not actually absorb but not yet known either
    u32 attack_id : 6; // Unconfirmed
    u16 motion_count;
    gmAttackFlags stat_flags;
    u16 stat_count;
    s32 hitbox_count;
    ArticleHitUnk item_hit_unk[2];
    ArticleHitArray hit_targets[4];

} Item_Hit;

typedef struct itHitEvent // Hitbox subaction event?
{
    u8 timer;
    s32 angle : 10;
    u32 damage : 8;
    u16 size;

} itHitEvent;

typedef struct itHitDesc
{
    u8 timer;
    s32 angle : 10;
    u32 damage : 8;
    u16 size;
    u32 knockback_scale;
    u32 knockback_weight;
    u32 knockback_base;
    s32 element;
    u32 clang : 1;
    s32 shield_damage;
    u16 hit_sfx;

} itHitDesc;

typedef struct Item_Hurt
{
    u8 interact_mask; // 0x1 = interact with fighters, 0x2 = interact with weapons, 0x4 = interact with other items
    s32 hitstatus;
    Vec3f offset; // Added to TopN joint
    Vec3f size;

} Item_Hurt;

typedef struct itCommonAttributes
{
    void *unk_0x0;
    void *unk_0x4;
    void *unk_atca_0x8;
    void *unk_atca_0xC;
    u32 unk_0x10_b0 : 1;
    u32 unk_0x10_b1 : 1;
    u32 unk_0x10_b2 : 1;
    u32 is_give_hitlag : 1;
    u32 weight : 1;         // Heavy = 0, Light = 1
    s32 hit_offset1_x : 16;
    s32 hit_offset1_y : 16; // When in doubt, make these raw s16
    s32 hit_offset1_z : 16;
    s32 hit_offset2_x : 16;
    s32 hit_offset2_y : 16;
    s32 hit_offset2_z : 16;
    Vec3h hurt_offset;
    Vec3h hurt_size;
    s16 objectcoll_top;
    s16 objectcoll_center;
    s16 objectcoll_bottom;
    s16 objectcoll_width;
    u16 size;
    s32 angle : 10;
    u32 knockback_scale : 10;
    u32 damage : 8;
    u32 element : 4;
    u32 knockback_weight : 10;
    s32 shield_damage : 8;
    u32 hitbox_count : 2;
    u32 clang : 1;
    u32 hit_sfx : 10;
    u32 priority : 3;
    u32 can_rehit_item : 1;
    u32 can_rehit_fighter : 1;
    u32 can_hop : 1;
    u32 can_reflect : 1;
    u32 can_shield : 1;
    u32 knockback_base : 10;
    u32 type : 4;
    u32 hitstatus : 4;
    u32 unk_atca_0x3C_b6 : 1;
    u32 unk_atca_0x3C_b7 : 1;
    u32 unk_atca_sfx : 10;
    u32 drop_sfx : 10;
    u32 throw_sfx : 10;
    u32 vel_scale : 9;
    u16 spin_speed;

} itCommonAttributes;

typedef struct Item_Struct // Common items, stage hazards and Pokémon
{
    void *ip_alloc_next; // Region allocated for next Item_Struct
    GObj *item_gobj;
    GObj *owner_gobj;
    atKind it_kind;
    s32 type;
    u8 team;
    u8 port_id;
    u8 handicap;
    s32 player_number;
    s32 percent_damage;
    u32 hitlag_timer;
    s32 lr;

    struct phys_info
    {
        f32 vel_ground;
        Vec3f vel;

    } phys_info;

    Coll_Data coll_data;

    Ground_Air ground_or_air;

    Item_Hit item_hit;
    Item_Hurt item_hurt;

    s32 hit_victim_damage;
    s32 lr_attack; // Direction of outgoing attack?
    s32 hit_reflect_damage;
    s32 hit_attack_damage;
    s32 hit_shield_damage;
    f32 shield_collide_angle;
    Vec3f shield_collide_vec;
    GObj *reflect_gobj;
    gmAttackFlags reflect_stat_flags;
    u16 reflect_stat_count;
    s32 damage_last; // Last 
    f32 damage_knockback; // Angle at which article will be launched when getting hit?
    s32 damage_taken_recent;
    s32 damage_angle;
    s32 damage_element;
    s32 lr_damage; // Direction of incoming attack?
    GObj *damage_gobj; // GObj that last dealt damage to this article?
    u8 damage_team;
    u8 damage_port;
    s32 damage_player_number;
    u8 damage_handicap;
    s32 damage_display_state;
    s32 damage_taken_last;
    s32 lifetime;
    f32 vel_scale;
    u16 unk_sfx;
    u16 drop_sfx;
    u16 throw_sfx;

    u32 is_allow_pickup : 1;    // Bool to check whether item can be picked up or not
    u32 is_hold : 1;            // I think this is used to tell if a fighter is holding this article?
    u32 times_landed : 2;       // Number of times item has touched the ground while not grabbed; overflows after 3
    u32 times_thrown : 3;       // Number of times item has been dropped or thrown; overflows after 7
    u32 weight : 1;     // 0 = item is heavy, 1 = item is light
    u32 is_damage_all : 1;      // Item ignores ownership and can damage anything?
    u32 is_attach_surface : 1;  // Item is "sticking" to a surface? Related to attach_line_id, but if it remains TRUE when there is no collision, it still falls?
    u32 is_apply_mag_stale : 1; // Apply magnitude and stale multiplier to damage output
    u16 attach_line_id;         // Line ID that item is attached to? I don't understand how this works
    u32 pickup_wait : 12;       // Number of frames article can last without being picked up (if applicable)
    u32 is_allow_knockback : 1; // Item can receive knockback velocity?
    u32 x2D3_flag_b5 : 1;       // Unused? Set various times, but no item process makes use of it
    u32 is_static_damage : 1;   // Ignore reflect multiplier if TRUE

    itCommonAttributes *attributes;

    Color_Overlay colanim;

    u32 is_hitlag_victim : 1;
    u16 it_multi; // Some sort of universal multi-purpose variable, e.g. it is used as intangibility delay for Star Man and ammo count for Ray Gun

    u32 item_event_index : 4; // Item hitbox script index? When in doubt, make this u8 : 4
    f32 rotate_speed;
    GObj *indicator_gobj; // Red arrow pickup indicator GObj
    u8 arrow_flash_timer; // Frequency of red arrow indicator flash

    union item_vars
    {
        BombHei_ItemVars bombhei;
        Shell_ItemVars shell;
        Taru_ItemVars taru;
        Bumper_ItemVars bumper;
        Gr_Lucky_ItemVars gr_lucky;
        M_Ball_ItemVars m_ball;
        Pakkun_ItemVars pakkun;
        Iwark_ItemVars iwark;
        Kabigon_ItemVars kabigon;
        Tosakinto_ItemVars tosakinto;
        Mew_ItemVars mew;
        Nyars_ItemVars nyars;
        Lizardon_ItemVars lizardon;
        Spear_ItemVars spear;
        Kamex_ItemVars kamex;
        Mb_Lucky_ItemVars mb_lucky;
        Starmie_ItemVars starmie;
        Dogas_ItemVars dogas;
        Marumine_ItemVars marumine;
        Porygon_ItemVars porygon;
        Hitokage_ItemVars hitokage;
        Fushigibana_ItemVars fushigibana;
        RaceBomb_ItemVars gr_bomb;
        PKFire_ItemVars pkfire;
        Link_Bomb_ItemVars link_bomb;

    } item_vars;

    s32 display_state;

    bool32 (*proc_update)(GObj*);
    bool32 (*proc_map)(GObj*);
    bool32 (*proc_hit)(GObj*);
    bool32 (*proc_shield)(GObj*);
    bool32 (*proc_hop)(GObj*);
    bool32 (*proc_setoff)(GObj*);
    bool32 (*proc_reflector)(GObj*);
    bool32 (*proc_damage)(GObj*);
    bool32 (*proc_dead)(GObj*);

} Item_Struct;

#define itGetStruct(item_gobj) \
((Item_Struct*)item_gobj->user_data) \


// Points to all sorts of data

#define ArticleGetPData(ap, off1, off2) \
( (void*) ( ((uintptr_t)ap->attributes->unk_0x0 - (intptr_t)&off1 ) + (intptr_t)&off2) ) \

#endif
