#include "include_asm.h"
#include "names.h"

extern void func_00282CC0(void *a, void *b, void *c);

extern float func_00282E48(char *a, char *b);

extern char D_L05_001B3510[];

extern char D_L05_001B34F0[];

extern float D_L05_001B3500;

/* Adds this object's position to the shared light spot when the object it belongs to is of a certain kind and is close enough. */
void func_L05_00418440(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *owner = *(char **)(state + 4);
    char *position;

    if (*(short *)(owner + 0xAA) != 0x957 /* moby class 2391 */)
        return;
    position = object + 0x10;
    if (fast_vec_dist(position, D_L05_001B3510) > 15.0f)
        return;
    FastVecAdd(gLightSpotSum, gLightSpotSum, position);
    gLightSpotCount = gLightSpotCount + 1.0f;
}
