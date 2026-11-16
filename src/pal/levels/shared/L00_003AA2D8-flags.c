#include "include_asm.h"

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
extern int save_is_record_value(int, int);
extern void moby_mark_spawned(void *);
extern void vec_transform_or_copy(void *, void *);
extern void beam_l00_effect_update(char *);
extern void FastVecAdd(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void beam_spawn_particle_pal(void *, int);
extern int beam_test_segment_hit_pal(char *, void *);
extern int FastDecTimer(void *);

/* Advance a moving effect, clip its path and schedule its next update. */
void moving_beam_update_pal(char *moby)
{
    float previous[4], midpoint[4];
    char *state = *(char **)(moby + 0x68);
    char *position;
    if (!save_is_record_value(0x5CB, *(short *)(state + 0x1A))) {
        moby_mark_spawned(moby);
        return;
    }
    if (*(unsigned char *)(moby + 0x20) == 2) {
        vec_transform_or_copy(moby + 0x10, moby + 0x10);
        beam_l00_effect_update(moby);
        return;
    }
    if (*(short *)(state + 0x12) == 1) {
        *(VectorBits *)previous = *(VectorBits *)(state + 0x30);
        position = moby + 0x10;
    } else {
        *(VectorBits *)previous = *(VectorBits *)(moby + 0x10);
        position = moby + 0x10;
    }
    FastVecAdd(position, position, state);
    if (*(short *)(state + 0x12) == 1)
        FastVecAdd(state + 0x30, state + 0x30, state + 0x20);
    if (*(unsigned char *)(moby + 0x20) == 0)
        *(unsigned char *)(moby + 0x20) = 1;
    else
        beam_spawn_particle_pal(previous, *(short *)(state + 0x1A));
    lerp_vector(midpoint, previous, position, 0.5f);
    beam_spawn_particle_pal(midpoint, *(short *)(state + 0x1A));
    if (*(float *)(moby + 0x10) < 2.0f || *(float *)(moby + 0x10) > 1021.0f ||
        *(float *)(moby + 0x14) < 2.0f || *(float *)(moby + 0x14) > 1021.0f ||
        *(float *)(moby + 0x18) < 2.0f || *(float *)(moby + 0x18) > 1021.0f ||
        beam_test_segment_hit_pal(moby, previous) || FastDecTimer(state + 0x10))
        *(unsigned char *)(moby + 0x20) = 2;
    else
        beam_l00_effect_update(moby);
}
