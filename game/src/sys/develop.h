#ifndef _DEVELOP_H_
#define _DEVELOP_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef enum gmDevelopDisplayStatus
{
	dbObject_DisplayMode_Master,
	dbObject_DisplayMode_HitCollisionFill,
	dbObject_DisplayMode_HitAttackOutline,
	dbObject_DisplayMode_MapCollision

} gmDevelopDisplayStatus;

#endif