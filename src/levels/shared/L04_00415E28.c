#include "include_asm.h"
#include "names.h"
typedef struct {
    char pad[0x138];
    int f138;
    int pad13C;
    int f140;
    int f144;
    char pad2[0x150 - 0x148];
} Ent;
extern Ent g_racer_trail_pool[];
extern void func_0030C948(Ent *a0, int a1, int a2, int a3, int a4, int a5);

/* Goes through all 140 table entries and starts the effect call for each entry that is active. */
void trail_update_active_entries(void)
{
    int i;
    for (i = 0; i < 140; i++) {
        Ent *e = &g_racer_trail_pool[i];
        if (e->f144 != 0 && e->f138 >= 2)
            func_0030C948(e, 0x43, 0x44, 0x45, e->f138, e->f140);
    }
}
