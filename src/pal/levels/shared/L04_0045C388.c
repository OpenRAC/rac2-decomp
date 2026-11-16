#include "include_asm.h"
#include "names.h"

extern void moby_set_state(char *a0, int a1, int a2);
extern void *part_find_owned_effect_slot(char *a0, int a1, int a2);
extern void part_spawn_scaled_bolts_pal(char *a0, int a1, float f12);
extern int PlayMobySound(int a0, int a1, char *a2);
extern void debris_spawn_ring(char *a0, int a1, float f12, float f13, float f14, float f15);
extern void moby_mark_spawned(char *a0);

/* Waits for its effect slot to be claimed, then bursts bolts, plays a sound and spawns a debris ring
   before removing itself (PAL: 50 Hz timings). */
void triggered_effect_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0 && *(int *)vars == 0)
            moby_set_state(moby, 2, -1);
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    case 2:
        part_spawn_scaled_bolts_pal(moby, 1, 0.0f);
        PlayMobySound(0, 0, moby);
        debris_spawn_ring(moby, 0x1E, 0.4f, 4.4f, 1.0f, 0.10000001f);
        moby_mark_spawned(moby);
        break;
    }
}

