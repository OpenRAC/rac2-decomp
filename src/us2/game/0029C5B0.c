#include "include_asm.h"
#include "names.h"
typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x7A18]; Pair pair[2]; } State;
extern char *g_resident_data_base[] __attribute__((sda));
int level_set_table_entry_us2(int a0, int a1, int a2)
{
    if (g_resident_data_base[0] != 0 && (unsigned int)a2 < 2) {
        State *s = (State *)(g_resident_data_base[0] + 0x38000);
        s->pair[a2].a = a0;
        s->pair[a2].b = a1;
        return 1;
    }
    return 0;
}
