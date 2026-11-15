#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad00[0x10];
    TI128 position;
    char state20;
    char pad21[0x30 - 0x21];
    unsigned char alpha;
    char visible;
    unsigned short timer;
    char pad34[0x68 - 0x34];
    char *vars;
} Moby_332590;

extern Moby_332590 *func_0029EFD0(int size);
extern int func_002FED90(Moby_332590 *object, TI128 *src, float x, float y, float z);
extern void func_00282CF0(void *dst, void *a, void *b);

Moby_332590 *func_00332590(int owner, TI128 *pos, void *a2, TI128 *a3)
{
    Moby_332590 *p;
    char *vars;

    p = CreateMoby(0xEAB);
    if (p != 0) {
        vars = p->vars;
        p->timer = 0xFF;
        p->alpha = 0xFF;
        p->state20 = 0;
        p->position = *pos;
        *(TI128 *)vars = *a3;
        *(int *)(vars + 0x30) = func_002FED90(p, 0, 1.0f, 1.0f, 1.0f);
        FastVecSub(vars + 0x20, a2, pos);
        *(int *)(vars + 0x34) = owner;
    }
    return p;
}
