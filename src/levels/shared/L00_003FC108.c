#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern char * func_0029EFD0(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_L00_003FC820(void *);

/* Creates a short-lived trail object and sprays sparks at its position. */
void *func_L00_003FC108(char *origin, char *direction, TI128 *position, char *owner)
{
    char *object = CreateMoby(0xD5E /* moby class 3422 */);

    if (object != 0) {
        char *vars = *(char **)(object + 0x68);
        float tmp[4];

        *(unsigned char *)(object + 0x30) = 0xFF;
        *(unsigned short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x31) = 1;
        *(unsigned char *)(object + 0x20) = 0;
        *(unsigned short *)(object + 0x34) |= 0x41;
        vec_scale_to_length(vars + 0x20, direction, 0.13333334f);
        *(TI128 *)(object + 0x10) = *position;
        vec_scale_to_length(tmp, vars + 0x20, -1.5f);
        FastVecAdd(vars + 0x50, origin, tmp);
        *(int *)(vars + 0x38) = 0x14;
        *(float *)(vars + 0x3C) = 1.0f / IntToFloat(0x14);
        *(char **)(vars + 0x34) = owner;
        SpawnSparkSpray_L00_2(object + 0x10);
    }
    return object;
}
