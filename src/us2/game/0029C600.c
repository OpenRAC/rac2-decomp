#include "include_asm.h"
#include "names.h"
typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x7A18]; Pair pair[2]; } State;
extern char *g_resident_data_base __attribute__((sda));
void level_clear_table_entry_us2(int index)
{
    if ((unsigned int)index < 2) {
        State *s = (State *)(g_resident_data_base + 0x38000);
        s->pair[index].a = 0;
        s->pair[index].b = 0;
    }
}
