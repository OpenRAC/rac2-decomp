#include "include_asm.h"

#include "common.h"
typedef int L06_7270TI __attribute__((mode(TI)));
extern void moby_set_state(unsigned char *, int, int);
extern void mat_apply_offset_to_object(void *, float, float, float);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void part_spawn_masked_debris_pal(char *, int, float *, unsigned char, float, float, float, float);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(void *);

/* A trigger that waits to be hit, remembers if a certain object hit it, then bursts and removes itself. */
void rotating_trigger_burst_update_pal(unsigned char *moby)
{
    int *vars = *(int **)(moby + 0x68);
    int state = moby[0x20];
    float impulse[4] __attribute__((aligned(16)));
    unsigned char *effect_slot;
    unsigned char *hit_moby;

    switch (state) {
    case 0:
        *vars = 0;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        mat_apply_offset_to_object(moby, 0.0f, 0.0f, 0.020943955f);
        effect_slot = part_find_owned_effect_slot(moby, 0x4010000, 0);
        if (effect_slot != 0) {
            hit_moby = *(unsigned char **)(effect_slot + 0x20);
            if (hit_moby != 0 && *(short *)(hit_moby + 0xAA) == 0x12C4) {
                *vars = state;
            }
            moby_set_state(moby, 2, -1);
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        *(L06_7270TI *)impulse = 0;
        if (*vars != 0) {
            impulse[0] = -0.20000002f;
        } else {
            impulse[0] = 0.20000002f;
        }
        matrix_mul_vec3(impulse, impulse, moby + 0xC0);
        part_spawn_masked_debris_pal((char *)moby, 7, impulse, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, (char *)moby);
        moby_mark_spawned(moby);
        break;
    }
}
