#include "include_asm.h"
typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x7390]; Pair pair[2]; } State;
extern char *D_001A8CFC __attribute__((sda));
/* Clears entry index (0 or 1) of the menu block's pair table. */
void func_0029B810(int index)
{
    if ((unsigned int)index < 2) {
        State *s = (State *)(D_001A8CFC + 0x38000);
        s->pair[index].a = 0;
        s->pair[index].b = 0;
    }
}
