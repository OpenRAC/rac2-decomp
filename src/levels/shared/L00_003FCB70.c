#include "common.h"
typedef int EffectQuadword __attribute__((mode(TI)));
extern void func_002AFFD8(char *, char *, int);
extern void func_00300190(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00282948(int *);
extern void func_0029F338(void *);
extern int func_002A77E0(int);
extern void *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void ref_L00_003FCB70_00(void *, void *);
extern char D_L00_001A8F20[] MACRO_ADDR;
extern unsigned char *D_L00_001FEA14;
extern void func_L00_003FC468(char *);
extern void func_L00_003FCDB0(char *);

/* Advance the emitter, spawn its paired particles, and discard out-of-bounds owners. */

void func_L00_003FCB70(char *object) {
    EffectQuadword before;
    EffectQuadword scratch;
    EffectQuadword after;
    char *state = *(char **)(object + 0x68);
    char *position = object + 0x10;
    unsigned char *particle;
    int phase;
    qcopy(&before, position);
    ComputeViewDirection(position, (char *)&scratch, 1);
    qcopy(&after, position);
    TransformVectorOrCopy(position, position);
    TransformVectorOrCopy(state + 0x50, state + 0x50);
    if (*(unsigned char *)(object + 0x20) == 0) {
        FastVecAdd(state + 0x50, state + 0x50, state + 0x20);
        if (FastFloatHelperD((int *)(state + 0x38))) {
            MarkMobySpawned(object);
            return;
        }
        phase = RandomIntBelow(255);
        particle = SpawnGravityFadeParticle(position, D_L00_001A8F20, 2, 0x00802020,
                               phase, 64, 16, 630000.0f, 630000.0f, 0.0f, 0);
        if (particle != 0) particle[2] = *D_L00_001FEA14;
        particle = SpawnGravityFadeParticle(position, D_L00_001A8F20, 2, 0x00802020,
                               (phase + 128) % 255, 64, 16, 630000.0f, 630000.0f, 0.0f, 0);
        if (particle != 0) particle[2] = *D_L00_001FEA14;
        ref_L00_003FCB70_00(DrawLargeSparkTrailRibbon, object);
    }
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f)
        MarkMobySpawned(object);
}
