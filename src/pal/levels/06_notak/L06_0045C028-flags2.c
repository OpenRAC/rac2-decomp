#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void moby_set_state(char *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void mat_apply_offset_to_object(void *, float, float, float);
extern void part_spawn_masked_debris_pal(char *, int, char *, float, float, float, float, int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *);

/* A rotating trigger that waits to be hit, remembers if a certain object hit it, then bursts and removes itself. */
void spinning_trigger_burst_update_pal(char *moby)
{
    int state = *(unsigned char *)(moby + 0x20);
    char *vars = *(char **)(moby + 0x68);
    float vec[4];
    char *effect_slot;
    char *hit_moby;

    switch (state) {
    case 0:
        *(int *)(vars + 4) = 0;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        mat_apply_offset_to_object(moby, 0.0f, 0.0f, -(*(float *)vars * 0.0003490659f));
        effect_slot = part_find_owned_effect_slot(moby, 0x4010000, 0);
        if (effect_slot != 0) {
            hit_moby = *(char **)(effect_slot + 0x20);
            if (hit_moby != 0 && *(short *)(hit_moby + 0xAA) == 0x12C4) {
                *(int *)(vars + 4) = state;
            }
            moby_set_state(moby, 2, -1);
        }
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    case 2:
        *(TI128 *)vec = 0;
        if (*(int *)(vars + 4) != 0) {
            vec[0] = -0.20000002f;
        } else {
            vec[0] = 0.20000002f;
        }
        part_spawn_masked_debris_pal(moby, 0x1FE, (char *)vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        PlayMobySound(0, 0, moby);
        moby_mark_spawned(moby);
        break;
    }
}
