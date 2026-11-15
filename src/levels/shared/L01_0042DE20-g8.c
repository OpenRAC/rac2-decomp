#include "common.h"

extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float coll_get_heightmap_height(void *);
extern int snd_set_slot_field(int, int);
extern int snd_start_from_table_entry(int, int, void *, int);

extern struct {
    char prefix[0x140];
    float pos[4];
} D_L01_001B9380;

typedef struct {
    char prefix[0x74];
    unsigned char active;
    char pad[0x17];
    char *owner;
    float pos[4];
    char tail[0x40];
} TransitionSoundSlot;

extern char g_sound_state[];
extern float D_L01_001B1D7C __attribute__((sda));
extern float D_001A7928 __attribute__((sda));

/* Fades an ambient sound by how open to the sky the player's surroundings are. */
void snd_update_open_air_blend(char *moby)
{
    float sample[4], radius[4], axis[4];
    char *state = *(char **)(moby + 8);
    float exposedFraction = 0, angle = 0;

    radius[0] = 4;
    radius[1] = 0;
    radius[2] = 0;
    radius[3] = 1;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1;
    do {
        math_apply_axis_rotation_to_quat(sample, radius, axis, angle);
        FastVecAdd(sample, D_L01_001B9380.pos, sample);
        if (coll_get_heightmap_height(sample) < D_L01_001B9380.pos[2])
            exposedFraction += 0.05f;
        angle += 0.3141592741012573f;
    } while (angle < 6.2831854820251465f);

    if (D_L01_001B1D7C < exposedFraction)
        D_L01_001B1D7C += D_001A7928 * 0.2f;
    else
        D_L01_001B1D7C -= D_001A7928 * 0.75f;
    if (D_L01_001B1D7C > 1)
        D_L01_001B1D7C = 1;
    else if (D_L01_001B1D7C < 0)
        D_L01_001B1D7C = 0;

    if (((TransitionSoundSlot *)(g_sound_state + *(int *)(state + 8) * 0x70))->owner == moby &&
        ((TransitionSoundSlot *)(g_sound_state + *(int *)(state + 8) * 0x70))->active)
        snd_set_slot_field(*(int *)(state + 8),
                         (int)((*(float *)(state + 4) + D_L01_001B1D7C) /
                               (*(float *)(state + 4) + 1) * 1024));
    qcopy_nc(((TransitionSoundSlot *)(g_sound_state + *(int *)(state + 8) * 0x70))->pos,
             D_L01_001B9380.pos);
    if (((TransitionSoundSlot *)(g_sound_state + *(int *)(state + 8) * 0x70))->owner != moby ||
        !((TransitionSoundSlot *)(g_sound_state + *(int *)(state + 8) * 0x70))->active)
        *(int *)(state + 8) = snd_start_from_table_entry(*(int *)state, 0x15, moby, 0x400);
}
