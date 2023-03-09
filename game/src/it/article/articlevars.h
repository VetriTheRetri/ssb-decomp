#ifndef _ARTICLEVARS_H_
#define _ARTICLEVARS_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define ATCAPSULE_GRAVITY 1.2F
#define ATCAPSULE_T_VEL 100.0F
#define ATCAPSULE_EXPLODE_SCALE 1.4F // Size of explosion graphics

#define ATTOMATO_GRAVITY 1.2F
#define ATTOMATO_T_VEL 100.0F

#define ATHEART_GRAVITY 0.25F
#define ATHEART_T_VEL 30.0F

#define ATSTAR_INTERACT_DELAY 16 // Wait this many frames before becoming tangible
#define ATSTAR_GRAVITY 1.2F
#define ATSTAR_T_VEL 100.0F
#define ATSTAR_VEL_X 8.0F
#define ATSTAR_BOUNCE_Y 50.0F // Y-velocity added when Star Man touches the ground

#define ATSWORD_GRAVITY 1.2F
#define ATSWORD_T_VEL 100.0F

#define ATBAT_GRAVITY 1.5F
#define ATBAT_T_VEL 120.0F

#define ATHARISEN_GRAVITY 1.0F
#define ATHARISEN_T_VEL 80.0F

#define ATLGUN_AMMO_MAX 16
#define ATLGUN_GRAVITY 1.5F
#define ATLGUN_T_VEL 130.0F
#define ATLGUN_AMMO_VEL_X 300.0F
#define ATLGUN_AMMO_STEP_SCALE_X 10.0F
#define ATLGUN_AMMO_CLAMP_SCALE_X 53.333332F

#define ATFFLOWER_AMMO_MAX 60
#define ATFFLOWER_AMMO_LIFETIME 30
#define ATFFLOWER_AMMO_VEL 30.0F
#define ATFFLOWER_GRAVITY 1.2F
#define ATFFLOWER_T_VEL 100.0F

#define ATHAMMER_COLANIM_ID 0x4E
#define ATHAMMER_GRAVITY 1.5F
#define ATHAMMER_T_VEL 120.0F

#endif