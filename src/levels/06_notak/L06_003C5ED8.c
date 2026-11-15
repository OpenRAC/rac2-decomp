#include "names.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword whole; float lane[4]; } Vector;
extern void moby_set_state(unsigned char *, unsigned char, int);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern void SpawnTintedEffects(void *, void *, int, int, void *, unsigned int, void *, float, float, float, float);
extern void part_spawn_scaled_bolts(void *, int, float);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(void *);

/* Idle, active, and terminal states of an effect emitter. */
/* Updates an effect object (moby class 4808): it waits to be hit, then throws out a burst of particles and disappears. */
void particle_burst_update(unsigned char *object)
{
    int *state = *(int **)(object + 0x68);
    Vector velocity;
    switch (object[0x20]) {
    case 0:
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(object, 0x4010000, 0) != 0 && state[0] == 0)
            moby_set_state(object, 2, -1);
        object[0xa8] = 0xff;
        break;
    case 2:
        velocity.whole = 0;
        velocity.lane[2] = -0.050000004470348358154f;
        SpawnTintedEffects(object, object + 0x10, 0x12, 1, &velocity, 0x80404040, 0,
                          1.5f, 3.0f, 0.75f, 1.5f);
        part_spawn_scaled_bolts(object, 1, 0.0f);
        PlayMobySound(0, 0, (char *)object);
        moby_mark_spawned(object);
        break;
    }
}
