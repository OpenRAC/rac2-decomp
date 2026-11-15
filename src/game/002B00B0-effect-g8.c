#include "common.h"

typedef int EffectVector __attribute__((mode(TI)));

extern int D_001B1A20[] __attribute__((sda));
extern float D_001B1A18[] __attribute__((sda));
extern EffectVector D_001BAFA0 NOT_SDA;
extern float g_camera_eye_state[4] NOT_SDA;
extern float D_001A9FCC __attribute__((sda));
extern void *D_001A9E74 __attribute__((sda));

extern float coll_get_heightmap_height(void *);
extern int CollLine(void *, void *, int, int, int);
extern int GetCollHitMaterial(void);
extern float math_random_float_range(float, float);
extern void *part_spawn_drifting(void *, float, void *, float, int);
extern void FastVecSub(void *, void *, void *);
extern float vec_length_xy(void *);
extern void part_spawn_glow(void *, int, int);

/* Looks for the ground below a position and spawns a splash or impact effect there. */
void part_spawn_ground_impact_effect(float *position)
{
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float *hit = start;
    float active = 0.0f;
    int kind;

    *(EffectVector *)start = *(EffectVector *)position;
    if (D_001B1A20[0]) {
        start[2] = coll_get_heightmap_height(&start) + D_001B1A18[0];
        if (start[2] < g_camera_eye_state[2] + 5.0f) {
            *(EffectVector *)end = *(EffectVector *)start;
            active = 1.0f;
            end[2] = end[2] - (D_001B1A18[0] + D_001B1A18[0]) - 2.0f;
        }
    } else if (start[0] > 0.0f && start[1] > 0.0f &&
               start[0] < 1024.0f && start[1] < 1024.0f) {
        *(EffectVector *)end = *(EffectVector *)position;
        end[2] = g_camera_eye_state[2] - 20.0f;
        active = 1.0f;
    }

    if (active != 0.0f) {
        if (CollLine(hit, &end, 18, 0, 0)) {
            kind = GetCollHitMaterial();
            if (kind == 0 || kind == 4 || kind == 3) {
                float scale;

                *(EffectVector *)hit = D_001BAFA0;
                hit[2] += D_001A9FCC;
                scale = math_random_float_range(0.4f, 0.6f);
                part_spawn_drifting(hit, scale, D_001A9E74, 5250.0f, -1);
            } else {
                FastVecSub(&offset, &D_001BAFA0, &g_camera_eye_state);
                part_spawn_glow(&D_001BAFA0,
                    (unsigned char)(int)(vec_length_xy(&offset) * 3.1833334f + 64.0f), 0);
            }
        }
    }
}
