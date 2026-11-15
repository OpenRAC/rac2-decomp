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

/* Creates a moby of class 3755 at the given position and fills in its start vector, direction and owner. */
Moby_332590 *func_00332590(int owner, TI128 *pos, void *targetPos, TI128 *startVec)
{
    Moby_332590 *moby;
    char *vars;

    moby = CreateMoby(0xEAB /* moby class 3755 */);
    if (moby != 0) {
        vars = moby->vars;
        moby->timer = 0xFF;
        moby->alpha = 0xFF;
        moby->state20 = 0;
        moby->position = *pos;
        *(TI128 *)vars = *startVec;
        *(int *)(vars + 0x30) = AllocEffectSlot_002FED90(moby, 0, 1.0f, 1.0f, 1.0f);
        FastVecSub(vars + 0x20, targetPos, pos);
        *(int *)(vars + 0x34) = owner;
    }
    return moby;
}
