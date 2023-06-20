#include "ftmasterhand.h"

// 0x8015AEE0
void ftMasterHand_Appear_ProcPhysics(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    DObj *topn_joint = fp->joint[ftParts_TopN_Joint], *transn_joint = fp->joint[ftParts_TransN_Joint];

    topn_joint->translate = transn_joint->translate;
}
