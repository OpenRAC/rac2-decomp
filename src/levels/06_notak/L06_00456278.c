#include "include_asm.h"
#include "names.h"

/* Emit the collision burst and six fragments, then retire the triggering object. */
extern void func_002ABBB8(char *, char *, int, float, float, int, int, int,
                          float, float, float, float, int, float, int, int, int, int, int);
extern void func_002A7A00(float *, float, float);
extern float func_00282C48(float);
extern void func_002B0A68(char *, int, float *, float, float, float, float, int);

extern char *func_002A9640(char *, int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_0029F338(char *);
extern void func_00282CC0(char *, char *, char *);
extern char D_L06_001A8F20[] __attribute__((sda));
/* When hit, bursts the object into a flash and six flying fragments, then removes it. */
void func_L06_00456278(char *obj)
{
    float fragmentVel[4];
    char *hit = (char *)FindOwnedEffectSlot(obj, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        PlayMobySound(0, 0, obj);
        SpawnExplosionEffects(obj, obj + 0x10, 0, 0.0f, 0.0f, 10, 3, 9,
                      4.0f, 2.0f, 9.0f, 0.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        RandomDirectionVector(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = FloatAbs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        SpawnDebrisForMaskedParts(obj, 1, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        RandomDirectionVector(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = FloatAbs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        SpawnDebrisForMaskedParts(obj, 4, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        RandomDirectionVector(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = FloatAbs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        SpawnDebrisForMaskedParts(obj, 8, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        RandomDirectionVector(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = FloatAbs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        SpawnDebrisForMaskedParts(obj, 16, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        RandomDirectionVector(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = FloatAbs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        SpawnDebrisForMaskedParts(obj, 32, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        RandomDirectionVector(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = FloatAbs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        SpawnDebrisForMaskedParts(obj, 64, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        MarkMobySpawned(obj);
    }
    *(unsigned char *)(obj + 0xA8) = 255;
}
