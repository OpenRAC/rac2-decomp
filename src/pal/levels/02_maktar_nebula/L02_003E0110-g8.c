#include "include_asm.h"
#include "names.h"
extern unsigned char g_barlow_hint_inside_flag;
extern char g_hero_position[];
extern unsigned short g_hud_offset_flag[];
extern int IsPointInCuboid(void *, int);
extern void hero_trigger_spawn_effect(void);
extern void moby_set_state(char *, int, int);
extern void moby_set_state();

void trigger_l02_update_pal(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        *(unsigned char *)(arg0 + 0x30) = 0xFF;
        if (g_barlow_hint_inside_flag == 0)
            g_hud_offset_flag[0] = 1;
        moby_set_state(arg0, 1, -1);
        break;
    case 1:
        hero_trigger_spawn_effect();
        if (IsPointInCuboid(g_hero_position, *(int *)state))
            *(unsigned short *)(g_hero_position + 0x19A) = 4;
        break;
    }
}
