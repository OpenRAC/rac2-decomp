#include "include_asm.h"
#include "names.h"

extern float IntToFloat(int);
extern float moby_move_and_collide(void *, void *, float, float, float, int);

/* Calls the engine blend helper with a count scaled down by 1024. */
float math_blend_scaled_count(void *objA, void *objB, int stepCount, int modeFlag, float valueA, float valueB)
{
    return moby_move_and_collide(objA, objB, valueA, IntToFloat(stepCount) * 0.0009765625f, valueB, modeFlag);
}
