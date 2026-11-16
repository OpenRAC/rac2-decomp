#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern unsigned char *g_moby_array_base __attribute__((sda));
extern void moby_set_state(char *, int, int);
extern void part_spawn_masked_debris_pal(char *, int, void *, unsigned char, float, float, float, float);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *);

/* Waits for either of two linked mobys to be removed, then plays a sound and effect and marks itself spawned (PAL). */
void linked_pair_watcher_update_pal(char *moby) {
    char *pair;
    char *linked_moby;
    unsigned int link_state;
    union { TI128 q; float f[4]; } effect_params;

    pair = *(char **)(moby + 0x68);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        if (*(int *)(pair + 4) > 0 && *(int *)(pair + 8) > 0) {
            linked_moby = g_moby_array_base + (*(int *)(pair + 4) << 8);
            if (linked_moby == 0 || (link_state = *(unsigned char *)(linked_moby + 0x20)) == 0xFE || link_state == 0xFD) {
                moby_set_state(moby, 2, -1);
            } else {
                linked_moby = g_moby_array_base + (*(int *)(pair + 8) << 8);
                if (linked_moby == 0 || (link_state = *(unsigned char *)(linked_moby + 0x20)) == 0xFE || link_state == 0xFD) moby_set_state(moby, 2, -1);
            }
        }
        return;
    case 2:
        effect_params.q = 0;
        effect_params.f[1] = 0.120000005f;
        part_spawn_masked_debris_pal(moby, 1, &effect_params, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, moby);
        moby_mark_spawned(moby);
        return;
    default:
        return;
    }
}
