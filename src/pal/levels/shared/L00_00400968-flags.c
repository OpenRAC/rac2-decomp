#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern char * CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern void part_l00_spawn_spark_spray_2_pal(void *);

/* Creates a short-lived trail object and sprays sparks at its position (PAL: same as v1.01). */
void *spark_trail_create_pal(char *origin, char *direction, TI128 *position, char *owner)
{
    char *object = CreateMoby(0xD5E);

    if (object != 0) {
        char *vars = *(char **)(object + 0x68);
        float offset[4];

        *(unsigned char *)(object + 0x30) = 0xFF;
        *(unsigned short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned char *)(object + 0x20) = 0;
        *(unsigned short *)(object + 0x34) |= 0x41;
        vec_scale_to_length(vars + 0x20, direction, 0.16000001f);
        *(TI128 *)(object + 0x10) = *position;
        vec_scale_to_length(offset, vars + 0x20, -1.5f);
        FastVecAdd(vars + 0x50, origin, offset);
        *(int *)(vars + 0x38) = 0x11;
        *(float *)(vars + 0x3C) = 1.0f / IntToFloat(0x11);
        *(char **)(vars + 0x34) = owner;
        part_l00_spawn_spark_spray_2_pal(object + 0x10);
    }
    return object;
}
