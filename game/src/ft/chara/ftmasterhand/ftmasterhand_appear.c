#include "ftmasterhand.h"

void func_ovl3_8015AEE0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = ftGetStruct(fighter_gobj);

    DObj *joint_topn = fp->joint[0], *joint_transn = fp->joint[1];

    joint_topn->translate = joint_transn->translate;
}
