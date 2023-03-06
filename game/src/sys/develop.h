#ifndef _DEVELOP_H_
#define _DEVELOP_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef enum gmDevelopDisplayStatus
{
	dbObjDisplayStatus_Master,
	dbObjDisplayStatus_HitCollision_Fill,
	dbObjDisplayStatus_HitCollision_Outline,
	dbObjDisplayStatus_EnvCollision

} gmDevelopDisplayStatus;

#endif