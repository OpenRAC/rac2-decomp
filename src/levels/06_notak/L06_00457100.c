#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(char *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void mat_apply_offset_to_object(void *, float, float, float);
extern void part_spawn_masked_debris(char *, int, char *, float, float, float, float, int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *);

/* A rotating trigger that waits to be hit, remembers if a certain object hit it, then bursts and removes itself. */
void spinning_trigger_burst_update(char *obj)
{
    int stateId = *(unsigned char *)(obj + 0x20);
    char *vars = *(char **)(obj + 0x68);
    float vec[4];
    char *hit;
    char *hitMoby;

    switch (stateId) {
    case 0:
        *(int *)(vars + 4) = 0;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        mat_apply_offset_to_object(obj, 0.0f, 0.0f, -(*(float *)vars * 0.0002908882452175021f));
        hit = part_find_owned_effect_slot(obj, 0x4010000, 0);
        if (hit != 0) {
            hitMoby = *(char **)(hit + 0x20);
            if (hitMoby != 0 && *(short *)(hitMoby + 0xAA) == 0x12C4 /* moby class 4804 */) {
                *(int *)(vars + 4) = stateId;
            }
            moby_set_state(obj, 2, -1);
        }
        *(unsigned char *)(obj + 0xA8) = 0xFF;
        break;
    case 2:
        *(TI128 *)vec = 0;
        if (*(int *)(vars + 4) != 0) {
            vec[0] = -0.16666667f;
        } else {
            vec[0] = 0.16666667f;
        }
        part_spawn_masked_debris(obj, 0x1FE, (char *)vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        PlayMobySound(0, 0, obj);
        moby_mark_spawned(obj);
        break;
    }
}
