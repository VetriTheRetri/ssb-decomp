#include "ftmasterhand.h"

void func_ovl3_8015AEE0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    DObj *joint_topn = fp->joint[ftParts_TopN_Joint], *joint_transn = fp->joint[ftParts_TransN_Joint];

    joint_topn->translate = joint_transn->translate;
}
