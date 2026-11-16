#include "include_asm.h"
#include "names.h"
typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x7AC8]; Pair pair[2]; } State;
extern char *g_resident_data_base[] __attribute__((sda));
/* Stores two values in entry 0 or 1 of the level object table. Returns 1 on success. */
int level_set_table_entry_pal(int first, int second, int index)
{
    if (g_resident_data_base[0] != 0 && (unsigned int)index < 2) {
        State *state = (State *)(g_resident_data_base[0] + 0x38000);
        state->pair[index].a = first;
        state->pair[index].b = second;
        return 1;
    }
    return 0;
}
