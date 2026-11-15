#include "common.h"

typedef int L06_7270TI __attribute__((mode(TI)));

extern void func_002A7750(unsigned char *, int, int);
extern void func_L00_00322A18(void *, float, float, float);
extern void *func_002A9640(void *, unsigned int, int);
extern void func_00283098(void *, const void *, const void *);
extern void func_002B0A68(char *, int, float *, unsigned char, float, float, float, float);
extern int func_002E5CF8(int, int, char *);
extern void func_0029F338(void *);

/* A trigger that waits to be hit, remembers if a certain object hit it, then bursts and removes itself. */
void func_L06_00457270(unsigned char *obj)
{
    int *vars = *(int **)(obj + 0x68);
    int stateId = obj[0x20];
    float offset[4] __attribute__((aligned(16)));
    unsigned char *hit;
    unsigned char *hitMoby;

    switch (stateId) {
    case 0:
        *vars = 0;
        SetMobyState(obj, 1, -1);
        break;
    case 1:
        ApplyOffsetToObjectMatrix(obj, 0.0f, 0.0f, 0.017453296f);
        hit = FindOwnedEffectSlot(obj, 0x4010000, 0);
        if (hit != 0) {
            hitMoby = *(unsigned char **)(hit + 0x20);
            if (hitMoby != 0 && *(short *)(hitMoby + 0xAA) == 0x12C4 /* moby class 4804 */) {
                *vars = stateId;
            }
            SetMobyState(obj, 2, -1);
        }
        obj[0xA8] = 0xFF;
        break;
    case 2:
        *(L06_7270TI *)offset = 0;
        if (*vars != 0) {
            offset[0] = -0.16666667f;
        } else {
            offset[0] = 0.16666667f;
        }
        matrix_mul_vec3(offset, offset, obj + 0xC0);
        SpawnDebrisForMaskedParts((char *)obj, 7, offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, (char *)obj);
        MarkMobySpawned(obj);
        break;
    }
}
