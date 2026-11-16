#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { int color[6]; } EffectPalette;
extern EffectPalette g_tether_impact_palette_a, g_tether_impact_palette_b;
extern char g_camera_l00_position[];
extern float g_effect_fade_value_a MACRO_ADDR;
extern void *part_spawn_flash(void *, int, int, float, float, float, float, float);
extern void FastVecSub(void *, void *, void *), vec_clear_128(Quad *);
extern float FastVecLength(void *), math_random_float_range(float, float);
extern int FloatToInt(float), math_random_int_below(s32), math_random_int_range(s32, s32);
extern void *part_spawn_firework_spark(void *, void *, int, int, int, int, int, int, float, float);
extern char *part_spawn_shockwave_ring(void *, void *, void *, int, int, int, int, int, float);
/* Emits the tether's impact smoke, distance-weighted sparks and colored fragments. */
void tether_spawn_impact_effects(char *actor, int fragments) {
    float point[4] __attribute__((aligned(16)));
    float delta[4], velocity[4];
    EffectPalette first, second;
    int i, k, count, startLife, endLife;
    int *firstColor, *lastColor;
    float distance, nearPenalty, speed;
    qcopy(point, actor + 0x10);
    point[2] += 0.3f;
    part_spawn_flash(point, 1, 0x40808080, 0.3f, 1.01f, 1.075f, 0.05f, 50000.0f);
    for (k = 0; k < 5; k++)
        part_spawn_flash(point, 1, 0x40808080, 0.3f, 1.01f, 1.07f, 0.05f, 50000.0f);
    if (!fragments) return;
    FastVecSub(delta, g_camera_l00_position, actor + 0x10);
    vec_clear_128((Quad *)velocity);
    distance = FastVecLength(delta);
    if (distance < 8.0f) count = FloatToInt(distance) + 2;
    else count = 10;
    nearPenalty = 0;
    if (distance < 7.0f) nearPenalty = 7.0f - distance;
    for (i = 0; i < count; i++) {
        speed = math_random_float_range(8.0f, 10.0f) * 0.016666668f;
        speed -= nearPenalty * 0.016666668f;
        first = g_tether_impact_palette_a;
        second = g_tether_impact_palette_b;
        firstColor = first.color + math_random_int_below(6);
        lastColor = second.color + math_random_int_below(6);
        startLife = math_random_int_range(15, 20);
        endLife = math_random_int_range(25, 30);
        part_spawn_firework_spark(actor + 0x10, velocity, *firstColor, *lastColor, startLife, endLife, 0, 0,
                      400000.0f, speed);
    }
    if (g_effect_fade_value_a < 0.95f) {
        part_spawn_shockwave_ring(actor, actor + 0x10, velocity, 15, 0x7F, 0x7F, 0x7F, 0x20, 3.0f);
        part_spawn_shockwave_ring(actor, actor + 0x10, velocity, 24, 0x7F, 0x20, 0, 0x20, 2.0f);
    }
    part_spawn_shockwave_ring(actor, actor + 0x10, velocity, 20, 0x7F, 0x40, 0, 0x30, 3.0f);
    part_spawn_shockwave_ring(actor, actor + 0x10, velocity, 27, 0x60, 0x10, 0, 0x40, 2.0f);
    part_spawn_shockwave_ring(actor, actor + 0x10, velocity, 29, 0x20, 0, 0, 0x20, 1.0f);
}
