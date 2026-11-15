#include "include_asm.h"
#include "names.h"

extern void FastVecAdd(void *a, void *b, void *c);

extern float fast_vec_dist(char *a, char *b);

extern char D_L05_001B3510[];

extern char g_light_spot_sum[];

extern float g_light_spot_count;

/* Adds this object's position to the shared light spot when the object it belongs to is of a certain kind and is close enough. */
void light_spot_add_nearby_object(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *owner = *(char **)(state + 4);
    char *position;

    if (*(short *)(owner + 0xAA) != 0x957 /* moby class 2391 */)
        return;
    position = object + 0x10;
    if (fast_vec_dist(position, D_L05_001B3510) > 15.0f)
        return;
    FastVecAdd(g_light_spot_sum, g_light_spot_sum, position);
    g_light_spot_count = g_light_spot_count + 1.0f;
}
