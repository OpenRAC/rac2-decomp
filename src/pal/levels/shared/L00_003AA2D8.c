#include "include_asm.h"

#include "common.h"
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern char *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
typedef struct { char prefix[0xD4]; unsigned char *material; } SceneMaterialPrefix;
extern SceneMaterialPrefix g_effect_definitions;
extern char g_default_vector[] __attribute__((sda));

/* Emit the two layers of a short particle trail. */
void EmitParticleTrailLayers_pal(char *moby)
{
    float point[3], offset[3], step[3], jitter[3];
    float *state = (float *)(*(char **)(moby + 0x68) + 0x14);
    float size = 0.175f;
    int i;
    point[0] = state[0];
    point[1] = state[1];
    point[2] = state[2];
    point[3] = 0.0f;
    FastVecScale(offset, moby + 0xD0, -0.1f);
    FastVecAdd(point, point, offset);
    FastVecScale(step, moby + 0xE0, 0.15f);
    FastVecAdd(point, point, step);
    FastVecScale(step, moby + 0xE0, -0.03333333507f);
    for (i = 8; i >= 0; i--) {
        char *particle;
        int rotation;
        jitter[0] = point[0] + math_random_signed_float_range(0.0f, 0.1f);
        jitter[1] = point[1] + math_random_signed_float_range(0.0f, 0.1f);
        jitter[2] = point[2] + math_random_signed_float_range(0.0f, 0.1f);
        rotation = math_random_int_below(255);
        part_spawn_gravity_fade(jitter, g_default_vector, 3, 0x808080, rotation, 127, 127,
                      size * 210000.0f, size * 210000.0f, 0.0f, 1);
        particle = part_spawn_gravity_fade(point, g_default_vector, 3, 0x203080, rotation, 16, 16,
                                 262500.0f, 262500.0f, 0.0f, 1);
        if (particle)
            *(unsigned char *)(particle + 2) = *g_effect_definitions.material;
        FastVecAdd(point, point, step);
    }
}




