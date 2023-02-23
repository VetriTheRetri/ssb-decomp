#ifndef _DEVELOP_H_
#define _DEVELOP_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef enum dbDisplayStatus
{
	dbObjDisplayStatus_Master,
	dbObjDisplayStatus_Hit_Fill,
	dbObjDisplayStatus_Hit_Outline,
	dbObjDisplayStatus_Env_Collision

} gmDevelopHitDisplayStatus;

#endif