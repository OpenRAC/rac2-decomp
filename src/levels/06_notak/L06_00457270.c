#include "common.h"

typedef int L06_7270TI __attribute__((mode(TI)));

extern void moby_set_state(unsigned char *, int, int);
extern void mat_apply_offset_to_object(void *, float, float, float);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void part_spawn_masked_debris(char *, int, float *, unsigned char, float, float, float, float);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(void *);

/* A trigger that waits to be hit, remembers if a certain object hit it, then bursts and removes itself. */
void rotating_trigger_burst_update(unsigned char *obj)
{
    int *vars = *(int **)(obj + 0x68);
    int state_id = obj[0x20];
    float offset[4] __attribute__((aligned(16)));
    unsigned char *hit;
    unsigned char *hit_moby;

    switch (state_id) {
    case 0:
        *vars = 0;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        mat_apply_offset_to_object(obj, 0.0f, 0.0f, 0.017453296f);
        hit = part_find_owned_effect_slot(obj, 0x4010000, 0);
        if (hit != 0) {
            hit_moby = *(unsigned char **)(hit + 0x20);
            if (hit_moby != 0 && *(short *)(hit_moby + 0xAA) == 0x12C4 /* moby class 4804 */) {
                *vars = state_id;
            }
            moby_set_state(obj, 2, -1);
        }
        obj[0xA8] = 0xFF;
        break;
    case 2:
        *(L06_7270TI *)offset = 0;
        if (*vars != 0) {
            offset[0] = -0.16666667f;
        } else {
            offset[0] = 0.16666667f;
        }
        matrix_mul_vec3(offset, offset, obj + 0xC0);
        part_spawn_masked_debris((char *)obj, 7, offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, (char *)obj);
        moby_mark_spawned(obj);
        break;
    }
}
