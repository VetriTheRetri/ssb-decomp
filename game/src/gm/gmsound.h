#ifndef _GMSOUND_H_
#define _GMSOUND_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef struct gmSoundEffect
{
    void *unk_0x0;
    void *unk_0x4;
    void *unk_0x8;
    void *unk_0xC;
    u16 unk_0x10;
    u16 unk_0x12;
    u16 unk_0x14;
    u16 unk_0x16;
    u16 unk_0x18;
    u16 unk_0x1A;
    u16 unk_0x1C;
    u16 unk_0x1E;
    u16 unk_0x20;
    u16 unk_0x22;
    u16 unk_0x24;
    u16 sfx_id;

} gmSoundEffect;

typedef enum gmSoundEffectSFX
{
    gmSound_SFX_ExplodeS,
    gmSound_SFX_ExplodeL,
    gmSound_SFX_FireShoot1,
    gmSound_SFX_UnkShoot1,
    gmSound_SFX_UnkDial1,
    gmSound_SFX_ChargeShotAll,
    gmSound_SFX_UnkSmallPing1,
    gmSound_SFX_Blaster,
    gmSound_SFX_SamusJump1,
    gmSound_SFX_DonkeySlap1,
    gmSound_SFX_DonkeySlap2,
    gmSound_SFX_Escape,         // Roll
    gmSound_SFX_DeadUpStar,     // Star KO spark
    gmSound_SFX_GuardOn,        // Put up shield
    gmSound_SFX_GuardOff,
    gmSound_SFX_ShieldBreak,
    gmSound_SFX_ShieldBreakPitchLw,
    gmSound_SFX_HeavySwing1,
    gmSound_SFX_LightSwingLw1,
    gmSound_SFX_Catch,          // Grab
    gmSound_SFX_DoorClose,
    gmSound_SFX_TModeSel,
    gmSound_SFX_ShockL,
    gmSound_SFX_ShockM,
    gmSound_SFX_ShockS,
    gmSound_SFX_BurnL,
    gmSound_SFX_BurnML,
    gmSound_SFX_BurnM,
    gmSound_SFX_BurnS,
    gmSound_SFX_ShockML,
    gmSound_SFX_Firefox,
    gmSound_SFX_KickL,
    gmSound_SFX_KickM,
    gmSound_SFX_DeadFall,       // Plays when dying in a blast zone?
    gmSound_SFX_KickS,
    gmSound_SFX_UnkTap1,
    gmSound_SFX_FireShoot2,
    gmSound_SFX_PunchL,
    gmSound_SFX_PunchM,
    gmSound_SFX_UnkSlam1,
    gmSound_SFX_PunchS,
    gmSound_SFX_LightSwingL,
    gmSound_SFX_LightSwingM,
    gmSound_SFX_LightSwingS,
    gmSound_SFX_MSBombAttach,
    gmSound_SFX_Thunder1,
    gmSound_SFX_ItemGroundCollide,   // Item falls on ground
    gmSound_SFX_BumperHit,
    gmSound_SFX_UnkGrind1,
    gmSound_SFX_ItemPickup,
    gmSound_SFX_HammerSwing,
    gmSound_SFX_HarisenHit,
    gmSound_SFX_BatL,
    gmSound_SFX_StarMapCollide,
    gmSound_SFX_StarCollect,
    gmSound_SFX_BombHeiWalkStart,
    gmSound_SFX_ShellHit,
    gmSound_SFX_ItemThrow,
    gmSound_SFX_ItemSpawn,
    gmSound_SFX_ContainerSmash,
    gmSound_SFX_FireFlowerShoot,
    gmSound_SFX_LGunShoot,
    gmSound_SFX_LGunEmpty,
    gmSound_SFX_StarRodSwing4,
    gmSound_SFX_StarRodSwing3,
    gmSound_SFX_StarRodSwing1,
    gmSound_SFX_UnkWhirr1,
    gmSound_SFX_SwordSwing4,
    gmSound_SFX_SwordSwing3,
    gmSound_SFX_SwordSwing1,
    gmSound_SFX_RBombHit,           // Race to the Finish bomb hit?
    gmSound_SFX_UnkHeavyHit1,       
    gmSound_SFX_UnkLightSwing1,     // All empty?
    gmSound_SFX_UnkLightSwing2,
    gmSound_SFX_UnkLightSwing3,
    gmSound_SFX_UnkLightSwing4,
    gmSound_SFX_UnkLightSwing5,
    gmSound_SFX_UnkLightSwing6,
    gmSound_SFX_UnkLightSwing7,
    gmSound_SFX_UnkLightSwing8,
    gmSound_SFX_UnkLightSwing9,
    gmSound_SFX_SamusLandingClick,
    gmSound_SFX_UnkLightSwing10,
    gmSound_SFX_UnkGrind2,
    gmSound_SFX_UnkGrind3,
    gmSound_SFX_UnkGrind4,
    gmSound_SFX_InflateJump1,
    gmSound_SFX_UnkGrind5,
    gmSound_SFX_SamusJump1,
    gmSound_SFX_NessPSI,
    gmSound_SFX_InflateJump2,
    gmSound_SFX_InflateJump3,
    gmSound_SFX_SamusJumpAerial,
    gmSound_SFX_InflateJump4,
    gmSound_SFX_KirbyPurinJump,
    gmSound_SFX_GroundGrind1,
    gmSound_SFX_GroundGrind2,
    gmSound_SFX_InflateJump5,
    gmSound_SFX_GroundGrind3,
    gmSound_SFX_InflateJump6,
    gmSound_SFX_NessJump,
    gmSound_SFX_InflateJump7,
    gmSound_SFX_InflateJump8,
    gmSound_SFX_GroundGrind4,
    gmSound_SFX_InflateJump9,
    gmSound_SFX_UnkLightSwing10,    // Might be footsteps? They are very quiet
    gmSound_SFX_UnkLightSwing11,
    gmSound_SFX_UnkLightSwing12,
    gmSound_SFX_UnkLightSwing13,
    gmSound_SFX_UnkLightSwing14,
    gmSound_SFX_UnkLightSwing15,
    gmSound_SFX_UnkLightSwing16,
    gmSound_SFX_UnkLightSwing17,
    gmSound_SFX_UnkLightSwing18,
    gmSound_SFX_UnkLightSwing19,
    gmSound_SFX_UnkLightSwing20,
    gmSound_SFX_UnkLightSwing21,
    gmSound_SFX_MetalMarioFoot = 0x7A,
    gmSound_SFX_MetalMarioLanding,  // Unconfirmed
    gmSound_SFX_SamusTurnClick = 0x7F,
    gmSound_SFX_GroundBrakeGrind,
    gmSound_SFX_UnkEchoHit1,
    gmSound_SFX_IwarkRockCreate = 0x84,
    gmSound_SFX_KabigonFall,
    gmSound_SFX_KabigonJump, // ???

} gmSoundEffectSFX;

#endif