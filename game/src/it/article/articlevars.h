#ifndef _ARTICLEVARS_H_
#define _ARTICLEVARS_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

#define ARTICLE_CAPSULE_GRAVITY 1.2F
#define ARTICLE_CAPSULE_T_VEL 100.0F
#define ARTICLE_CAPSULE_EXPLODE_SCALE 1.4F // Size of explosion graphics

#define ARTICLE_TOMATO_GRAVITY 1.2F
#define ARTICLE_TOMATO_T_VEL 100.0F

#define ARTICLE_HEART_GRAVITY 0.25F
#define ARTICLE_HEART_T_VEL 30.0F

#define ARTICLE_STAR_INTERACT_DELAY 16 // Wait this many frames before becoming tangible
#define ARTICLE_STAR_GRAVITY 1.2F
#define ARTICLE_STAR_T_VEL 100.0F
#define ARTICLE_STAR_VEL_X 8.0F
#define ARTICLE_STAR_BOUNCE_Y 50.0F // Y-velocity added when Star Man touches the ground

#endif