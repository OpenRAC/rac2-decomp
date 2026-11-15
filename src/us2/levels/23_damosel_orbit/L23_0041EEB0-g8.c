#include "include_asm.h"
#include "names.h"
extern char *g_mothership_boss_moby __attribute__((sda));
extern int D_L23_001B1424 __attribute__((sda));
extern unsigned char D_001395B8[];
extern void level_store_value_pair(int, int);
extern void level_set_dependent_value(void);
extern void moby_mark_spawned(void *);

/* Releases the five slot objects and the level object, then raises three flags. The flags are
 * written through a pointer set after the calls, as retail's `lui`/`addiu` base with the 0x88 and
 * 0xA1 displacements; written as D_001395B8[0xA1] and [0x88], the high half is hoisted into a
 * saved register (160 bytes). */
void func_US2_L23_0041EEB0(void) {
    char **p = (char **)(*(char **)(g_mothership_boss_moby + 0x68) + 0x358);
    unsigned char *flags;
    int i;

    for (i = 4; i >= 0; i--) {
        if (*p != 0) {
            moby_mark_spawned(*p);
            *p = 0;
        }
        p++;
    }
    if (g_mothership_boss_moby != 0) {
        level_store_value_pair(0, 0);
        level_set_dependent_value();
        moby_mark_spawned(g_mothership_boss_moby);
        g_mothership_boss_moby = 0;
    }
    flags = D_001395B8;
    D_L23_001B1424 = 1;
    flags[0xA1] = 1;
    flags[0x88] = 1;
}
