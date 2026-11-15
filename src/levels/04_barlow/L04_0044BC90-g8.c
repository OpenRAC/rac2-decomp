#include "common.h"
typedef int BarlowEffectQuad __attribute__((mode(TI)));
typedef union { BarlowEffectQuad q; float f[4]; } BarlowEffectVector;
extern void FastVecScale(void *, void *, float);
extern char *part_spawn_object_following_effect(void *, void *, unsigned int, int, int, int, int, int, float, float);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int, int, unsigned char, void *);
extern void SpawnParticleBurst(void *, void *, void *, void *, void *, int, unsigned char);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void moby_mark_spawned(void *);
extern float D_L04_001B1830[] SDATA(D_L04_001B1830);
extern float D_L04_001B1828[] SDATA(D_L04_001B1828);
extern float D_L04_001B1820[] SDATA(D_L04_001B1820);
extern int D_L04_001B1850 SDATA(D_L04_001B1850);

/* Launches a burst of effects from the object: it spawns a stream, waits, then fires the main burst and removes itself. */
void barlow_effect_emitter_update(unsigned char *object)
{
    BarlowEffectVector velocity, lower, upper, minOffset, maxOffset;
    char *state = *(char **)(object + 0x68);
    velocity.q = 0;
    velocity.f[0] = -21.5f;
    switch (object[0x20]) {
    case 0:
        FastVecScale(&velocity, &velocity, *(float *)(object + 0x2c));
        *(char **)(state + 4) = part_spawn_object_following_effect(&velocity, object, 0x40208080, -1, 1, -1, 0, -1,
                                                *(float *)(object + 0x2c) * 5250000.0f, *(float *)(object + 0x2c) * 15.0f);
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(object, 0x4010000, 0) && !*(int *)state) moby_set_state(object, 2, -1);
        object[0xa8] = 255;
        break;
    case 2:
        part_explode_object_into_pieces(object, D_L04_001B1830, D_L04_001B1828, D_L04_001B1820, 65535, 0, D_L04_001B1850, 8, 65535, 255, 0);
        minOffset.q = 0;
        maxOffset.q = 0;
        lower.q = 0;
        upper.q = 0;
        upper.f[0] = lower.f[0] = -15.0f;
        minOffset.f[0] = -10.0f;
        minOffset.f[2] = minOffset.f[1] = -4.0f;
        maxOffset.f[0] = -3.0f;
        maxOffset.f[1] = 5.0f;
        maxOffset.f[2] = 4.0f;
        SpawnParticleBurst(object, &lower, &upper, &minOffset, &maxOffset, 45, 0);
        vec_local_offset_to_world(object, &velocity, -21.5f, 0.0f, 0.0f);
        SpawnExplosion(object + 0x10, 0, 25, 20, 20, 20, 45, 1,
                     *(float *)(object + 0x2c) * 5.0f, 20.0f, 1, 1, 0, 0);
        moby_mark_spawned(object);
        break;
    }
}
