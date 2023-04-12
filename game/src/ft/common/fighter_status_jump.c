#include "fighter.h"

void func_ovl3_8013F9A0(GObj *fighter_gobj)
{
    if ((func_ovl3_80150F08(fighter_gobj) == FALSE) && (func_ovl3_80150B00(fighter_gobj) == FALSE))
    {
        func_ovl3_8014019C(fighter_gobj);
    }
}

void func_ovl3_8013F9E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl2_800F3794(fighter_gobj) != FALSE)
    {
        func_ovl3_80147C50(fighter_gobj);
    }
    else
    {
        if (fp->ground_or_air == ground)
        {
            func_ovl2_800DEEC8(fp);
        }
        func_ovl2_800E6F24(fighter_gobj, ((fp->jumps_used >= fp->attributes->jumps_max) ? ftStatus_Common_FallAerial : ftStatus_Common_Fall), 0.0F, 1.0F, 8U);

        func_ovl2_800D8EB8(fp);

        fp->x192_flag_b0 = TRUE;
    }
}