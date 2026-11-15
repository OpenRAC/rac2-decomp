#include "names.h"
extern void FastVecSub(void *, void *, void *);
extern unsigned int moby_get_motion_params(unsigned int);
extern float moby_turn_toward_direction(void *, unsigned int, void *, int);

/* Turns the object to face its target object. */
void moby_turn_toward_target(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *other = *(char **)(data + 0x30);
    if (other != 0) {
        float vector[4];
        FastVecSub(vector, (float *)(other + 0x10), (float *)(object + 0x10));
        moby_turn_toward_direction(object, moby_get_motion_params((unsigned int)object), vector, 0);
    }
}
