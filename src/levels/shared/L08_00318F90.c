#include "include_asm.h"
typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x7370]; Pair pair[4]; } State;
extern char *D_L08_001A904C[] __attribute__((sda));
/* Stores a pair of values in one of four slots of the global game state, if it exists. Returns 1 on success. */
int func_L08_00318F90(int valueA, int valueB, unsigned int index)
{
    if (D_L08_001A904C[0] != 0 && index < 4) {
        State *state = (State *)(D_L08_001A904C[0] + 0x38000);
        state->pair[index].a = valueA;
        state->pair[index].b = valueB;
        return 1;
    }
    return 0;
}
