#include "include_asm.h"
#include "names.h"
extern unsigned char D_001A7AFA;
extern char g_hero_position[];
extern unsigned short D_0018C31C[];
extern int IsPointInCuboid(void *, int);
extern void hero_trigger_spawn_effect(void);
extern void moby_set_state(char *, int, int);
extern void moby_set_state();

void func_PAL_L02_003E0110(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        *(unsigned char *)(arg0 + 0x30) = 0xFF;
        if (D_001A7AFA == 0)
            D_0018C31C[0] = 1;
        moby_set_state(arg0, 1, -1);
        break;
    case 1:
        hero_trigger_spawn_effect();
        if (IsPointInCuboid(g_hero_position, *(int *)state))
            *(unsigned short *)(g_hero_position + 0x19A) = 4;
        break;
    }
}
