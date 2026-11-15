#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(char *, int, int);
extern void *func_002A9640(void *, int, int);
extern void func_L00_00322A18(void *, float, float, float);
extern void func_002B0A68(char *, int, char *, float, float, float, float, int);
extern int func_002E5CF8(int, int, char *);
extern void func_0029F338(char *);

/* A rotating trigger that waits to be hit, remembers if a certain object hit it, then bursts and removes itself. */
void func_L06_00457100(char *obj)
{
    int stateId = *(unsigned char *)(obj + 0x20);
    char *vars = *(char **)(obj + 0x68);
    float vec[4];
    char *hit;
    char *hitMoby;

    switch (stateId) {
    case 0:
        *(int *)(vars + 4) = 0;
        SetMobyState(obj, 1, -1);
        break;
    case 1:
        ApplyOffsetToObjectMatrix(obj, 0.0f, 0.0f, -(*(float *)vars * 0.0002908882452175021f));
        hit = FindOwnedEffectSlot(obj, 0x4010000, 0);
        if (hit != 0) {
            hitMoby = *(char **)(hit + 0x20);
            if (hitMoby != 0 && *(short *)(hitMoby + 0xAA) == 0x12C4 /* moby class 4804 */) {
                *(int *)(vars + 4) = stateId;
            }
            SetMobyState(obj, 2, -1);
        }
        *(unsigned char *)(obj + 0xA8) = 0xFF;
        break;
    case 2:
        *(TI128 *)vec = 0;
        if (*(int *)(vars + 4) != 0) {
            vec[0] = -0.16666667f;
        } else {
            vec[0] = 0.16666667f;
        }
        SpawnDebrisForMaskedParts(obj, 0x1FE, (char *)vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        PlayMobySound(0, 0, obj);
        MarkMobySpawned(obj);
        break;
    }
}
