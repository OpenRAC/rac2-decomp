#include "include_asm.h"

typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x79F8]; Pair pair[4]; } State;
extern char *D_L08_001A904C[] __attribute__((sda));

int func_US2_L08_0031A090(int a0, int a1, unsigned int index)
{
    if (D_L08_001A904C[0] != 0 && index < 4) {
        State *s = (State *)(D_L08_001A904C[0] + 0x38000);
        s->pair[index].a = a0;
        s->pair[index].b = a1;
        return 1;
    }
    return 0;
}

