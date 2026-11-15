#include "include_asm.h"
typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x7390]; Pair pair[2]; } State;
extern char *D_001A8CFC[] __attribute__((sda));
/* Stores two values in entry a2 (0 or 1) of the menu block; returns 1 if the block exists and a2 is valid, otherwise 0. */
int func_0029B7C0(int a0, int a1, int a2)
{
    if (D_001A8CFC[0] != 0 && (unsigned int)a2 < 2) {
        State *s = (State *)(D_001A8CFC[0] + 0x38000);
        s->pair[a2].a = a0;
        s->pair[a2].b = a1;
        return 1;
    }
    return 0;
}
