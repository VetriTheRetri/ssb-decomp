#include "item.h"
#include "fighter.h"

bool32 func_ovl3_80168F00(GObj *item_gobj)
{
    if (func_ovl3_80167FE8(ItemGetStruct(item_gobj)) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}