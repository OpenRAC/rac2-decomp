#include "include_asm.h"
#include "common.h"

/* func_PAL_L03_002EE460, the PAL copy of func_L03_002ECF08: the same C at 50 Hz (velocity * 0.02,
 * gravity 0.002, counts scaled by 5 and rounded over 6). */

extern float math_random_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_local_offset_to_world(float, float, float, void *, void *);
extern int FloatToInt(float);
extern int FastTweenColor(float, int, int);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);

typedef struct { float x, y, z, w; } SparkVector;
/* Spawns a burst of count sparks with random positions and velocities around the object, colored by style (PAL: 50 Hz motion and lifetimes). */
void part_spawn_particle_burst_l03_pal(unsigned char *object, float *min_position, float *max_position,
                      float *min_velocity, float *max_velocity, int count, unsigned char style) {
    SparkVector velocity, acceleration, position;
    int flags = 0x1003C;
    float scale;
    float gravity = 0.002f;
    int life1, life2, life3, start_color, end_color;
    int i;

    for (i = 0; i < count; i++) {
        velocity.x = math_random_float_range(min_velocity[0], max_velocity[0]) * 0.020000001f;
        velocity.y = math_random_float_range(min_velocity[1], max_velocity[1]) * 0.020000001f;
        velocity.z = math_random_float_range(min_velocity[2], max_velocity[2]) * 0.020000001f;
        position.x = math_random_float_range(min_position[0], max_position[0]);
        position.y = math_random_float_range(min_position[1], max_position[1]);
        position.z = math_random_float_range(min_position[2], max_position[2]);
        matrix_mul_vec3(&velocity, &velocity, object + 0xC0);
        vec_local_offset_to_world(position.x, position.y, position.z, object, &position);
        scale = math_random_float_range(0.5f, 1.5f);
        life1 = FloatToInt((scale * 50.0f + 2.0f) * 0.16666667f);
        life2 = FloatToInt((scale * 175.0f + 2.0f) * 0.16666667f);
        life3 = FloatToInt((scale * 35.0f + 2.0f) * 0.16666667f);
        velocity.w = math_random_float_range(0.1f, 0.4f);
        vec_clear_128(&acceleration);
        acceleration.z = -gravity * (float)(life1 + life2 + life3);
        FastVecAdd(&acceleration, &acceleration, &velocity);
        acceleration.w = 0.01f;
        switch (style) {
        case 1:
            start_color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x80102040, 0x801010A0);
            end_color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x102040, 0x1010A0);
            break;
        case 3:
            start_color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x80201608, 0x80402510);
            end_color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x201608, 0x402510);
            break;
        case 2:
            start_color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x80104010, 0x8020A020);
            end_color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x104010, 0x20A020);
            break;
        case 0:
        default:
            start_color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x80004080, 0x80408080);
            end_color = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x4080, 0x408080);
            break;
        }
        part_spawn_trail(&position, &velocity, &acceleration, start_color, end_color, life1, life2, life3, flags);
    }
}
