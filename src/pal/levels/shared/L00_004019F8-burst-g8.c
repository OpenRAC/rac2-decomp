#include "include_asm.h"

#include "common.h"
typedef int SpawnVectorWord __attribute__((mode(TI)));
extern char g_camera_l00_position[];
extern void FastVecSub(char *, char *, char *);
extern float mat_fast_helper_a(float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern void vec_random_direction(float *, float, float);
extern void *part_spawn_burst_pal(void *, void *, int, u32, int, int, float, float, float, float, float);
extern void *part_spawn_ground_effect(float, void *, int, float, u32, int, int, void *, int, float);

/* Fifteen particles thrown from the point, as in func_L00_003FC820, then five pairs of trail
   effects around it, differently coloured and with opposite random signs. */
void SpawnParticleTrailBurst_pal(float *point)
{
    float delta[4];
    float direction[4];
    float position[4];
    float base_angle;
    float scale;
    float angle;
    float elevation;
    float speed;
    float trail_scale;
    int kind;
    int sign;
    int i;
    int j;
    char *effect;

    FastVecSub((char *)delta, g_camera_l00_position, (char *)point);
    base_angle = mat_fast_helper_a(delta[0], delta[1]);
    for (i = 0; i < 15; i++) {
        scale = math_random_float_range(0.5f, 1.25f);
        kind = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        elevation = math_random_float_range(0.0f, 1.3962636f);
        angle = FastAddRotations(base_angle, math_random_signed_float_range(0.0f, 1.3962636f));
        vec_build_spherical_offset(direction, scale * 0.020000001f, angle, elevation);
        position[0] = point[0] + math_random_signed_float_range(0.0f, 0.2f);
        position[1] = point[1] + math_random_signed_float_range(0.0f, 0.2f);
        position[2] = point[2] + math_random_signed_float_range(0.0f, 0.2f);
        part_spawn_burst_pal(position, direction, 25, 127, 0x007F7F7F, kind,
                      math_random_float_range(0.1f, 0.3f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
    }
    for (j = 0; j < 5; j++) {
        trail_scale = math_random_float_range(0.25f, 0.75f);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        speed = math_random_float_range(1.0f, 4.0f);
        vec_random_direction(direction, speed * 0.020000001f, speed * 0.020000001f);
        *(SpawnVectorWord *)position = *(SpawnVectorWord *)point;
        position[0] += math_random_signed_float_range(0.0f, 0.15f);
        position[1] += math_random_signed_float_range(0.0f, 0.15f);
        position[2] += math_random_signed_float_range(0.0f, 0.15f);
        effect = part_spawn_ground_effect(trail_scale * 0.1f, position, 50, trail_scale,
                               0x7FFF1010, 0, sign, direction, 0, 0.0043200003f);
        if (effect != 0)
            effect[9] = FloatToInt(4.0f) + 112;
        effect = part_spawn_ground_effect(trail_scale * 0.05f, position, 50, trail_scale * 0.5f,
                               0x7F7F7F7F, 1, -sign, direction, 0, 0.0043200003f);
        if (effect != 0)
            effect[9] = FloatToInt(4.0f) + 112;
    }
}
