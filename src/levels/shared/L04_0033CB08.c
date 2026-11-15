#include "include_asm.h"
#include "names.h"

extern float func_00283CE0(int);
extern float func_002A8240(void *, void *, float, float, float, int);

/* Calls the engine blend helper with a count scaled down by 1024. */
float func_L04_0033CB08(void *objA, void *objB, int stepCount, int modeFlag, float valueA, float valueB)
{
    return MoveAndCollideObject(objA, objB, valueA, IntToFloat(stepCount) * 0.0009765625f, valueB, modeFlag);
}
