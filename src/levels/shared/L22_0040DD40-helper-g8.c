#include "common.h"


typedef int TI128_L22 __attribute__((mode(TI)));

extern void func_L22_0040E098(char *object);

extern void func_00282CC0(char *out, char *first, char *second);

extern void func_L22_0040DF28(char *a0, char *a1);

extern int func_00282948(char *a0);

extern void func_0029F338(char *a0);

extern void func_L00_002E6EF8(void (*callback)(char *), char *object);

/* Three-state gate on the record's byte 0x20. State 0 stamps itself state 1 and falls into the
 * state-1 body (a 16-byte copy of the record's vector, the pair update and the shared sub-object
 * test that promotes the record to state 2); state 2 destroys the record and returns; every other
 * state, and the end of the state-1 body, re-arms the record through the level callback. */
/* Per-frame update for moby class 3933 (also used for 4494): moves the object, hands it to the level callback and removes it once its sub-object finishes. */
void func_L22_0040DD40(char *a0)
{
    char *handle = *(char **)(a0 + 0x68);
    char local[16];

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(unsigned char *)(a0 + 0x20) = 1;
    case 1: {
        char *p = a0 + 0x10;

        qcopy(local, p);
        FastVecAdd(p, handle, p);
        CheckProjectileHitAndExplode(a0, local);
        if (FastFloatHelperD(handle + 0x10) != 0)
            *(unsigned char *)(a0 + 0x20) = 2;
        break;
    }
    case 2:
        MarkMobySpawned(a0);
        return;
    default:
        break;
    }
    AddDrawCallbackToList3(UpdateScrollingParticleEffect, a0);
}
