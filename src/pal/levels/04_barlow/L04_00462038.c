#include "include_asm.h"

#include "common.h"
extern void *part_find_owned_effect_slot(unsigned char *moby, int a1, int a2);
extern int PlayMobySound(int a0, int a1, unsigned char *moby);
extern void vec_random_direction(float *vec, float f12, float f13);
extern float math_fabs(float value);
extern void part_spawn_glow_fade_effects_pal(unsigned char *moby, float *position, int a2, int a3, float *velocity, float f12, float f13, float f14, float f15, int color, int t2);
extern void moby_mark_spawned(unsigned char *moby);

/* Throws two puffs of the effect at the object's position, lifted by 0.75, then flags the object and updates it twice. */
void barlow_puff_update_pal(unsigned char *moby)
{
    float velocity[4];
    float position[4];

    if (part_find_owned_effect_slot(moby, 0x10000, 0) != 0) {
        PlayMobySound(0, 0, moby);
        qcopy(position, moby + 0x10);
        position[2] += 0.75f;
        vec_random_direction(velocity, 0.080000006f, 0.120000005f);
        velocity[2] = math_fabs(velocity[2]) * 1.5f;
        part_spawn_glow_fade_effects_pal(moby, position, 15, 1, velocity, 0.5f, 3.0f, 0.75f, 1.25f, 0x50404040, 0);
        vec_random_direction(velocity, 0.080000006f, 0.120000005f);
        velocity[2] = math_fabs(velocity[2]) * 1.5f;
        part_spawn_glow_fade_effects_pal(moby, position, 15, 1, velocity, 0.5f, 3.0f, 0.75f, 1.25f, 0x50404040, 0);
        moby[0xA8] = 0xFF;
        moby_mark_spawned(moby);
        moby_mark_spawned(moby);
    }
}

