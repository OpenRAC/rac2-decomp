#include "include_asm.h"
#include "names.h"
typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x7390]; Pair pair[2]; } State;
extern char *D_001A8CFC __attribute__((sda));
/* Clears entry 0 or 1 of the level object table. */
void level_clear_table_entry(int index)
{
    if ((unsigned int)index < 2) {
        State *s = (State *)(D_001A8CFC + 0x38000);
        s->pair[index].a = 0;
        s->pair[index].b = 0;
    }
}
