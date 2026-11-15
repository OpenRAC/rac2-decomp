/* func_L00_00414540: explosion burst with a drift velocity (family F6, the drift-carrying sibling
 * of func_L16_00406550 and func_L00_00415DE8). The emitters take their float parameters interleaved
 * with the ints; one effect pointer serves the four leading fire emitters.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define I(p, o) (*(int *)((u8 *)(p) + (o)))

typedef struct { u8 pad[0x140]; float target[4]; } CameraView;
typedef struct { u8 pad[0xD4]; u8 *sparkColors; u8 pad2[0x98]; u8 *fireColors; } EffectTables;

extern float D_L00_001B13E0 __attribute__((sda));
extern float D_L00_001B13E4 __attribute__((sda));
extern int D_L00_001B13E8 __attribute__((sda));
extern float D_L00_001A8F20[4] MACRO_ADDR;
extern CameraView D_L00_001B8C80;
extern EffectTables D_L00_001FE940;

extern u8 *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern u8 *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern void FastVecScale(void *, void *, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern u8 *part_spawn_trail_2(void *, void *, int, float);
extern void part_spawn_shockwave_ring(void *, void *, void *, int, int, int, int, int, float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, int, int, int, int, int, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern u8 *SpawnSpinningSparkParticle(void *, float, float, int, void *, int, int, float, float);
extern float IntToFloat(int);

/* Sets off an explosion with fire, sparks, smoke and a shockwave. All the pieces also drift with the given speed. */
void part_spawn_explosion_burst_with_drift(u8 *object, void *unused, float *drift)
{
    Vec4 position;
    Vec4 velocity;
    Vec4 rotation;
    u8 *state = *(u8 **)(object + 0x68);
    float inner, outer, angle, speed;
    u8 *effect;
    int coreIdx, glowIdx, brightIdx, largeIdx, smallIdx, debrisIdx, smokeIdx, sign;

    inner = D_L00_001B13E0 * F(state, 0x14) * 210000.0f;
    outer = D_L00_001B13E4 * F(state, 0x14) * 210000.0f;
    {
        effect = part_spawn_gravity_fade(object + 0x10, drift, D_L00_001B13E8, 0xF78E38, 0, 100, 0, inner, outer, 0.0f, 0);
        if (effect)
            effect[2] = D_L00_001FE940.fireColors[0];
    }
    {
        effect = part_spawn_gravity_fade(object + 0x10, drift, D_L00_001B13E8, 0xF76300, 0, 100, 0, inner, outer, 0.0f, 0);
        if (effect)
            effect[2] = D_L00_001FE940.fireColors[0];
    }
    for (coreIdx = 1; coreIdx >= 0; coreIdx--) {
        {
            effect = part_spawn_gravity_fade(object + 0x10, drift, D_L00_001B13E8, 0xF78E38, 0, 127, 0, inner, outer, 0.0f, 0);
            if (effect)
                effect[2] = D_L00_001FE940.fireColors[5];
        }
    }
    for (glowIdx = 1; glowIdx >= 0; glowIdx--) {
        {
            effect = part_spawn_gravity_fade(object + 0x10, drift, D_L00_001B13E8, 0xF78E38, 0, 127, 0, inner, outer, 0.0f, 0);
            if (effect)
                effect[2] = D_L00_001FE940.fireColors[6];
        }
    }
    for (brightIdx = 0; brightIdx < I(state, 0x20); brightIdx++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = mat_fast_helper_a(D_L00_001B8C80.target[0] - F(object, 0x10), D_L00_001B8C80.target[1] - F(object, 0x14));
        phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
        lifetime = math_random_int_range(30, 50);
        position[0] = F(object, 0x10) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        size = math_random_float_range(0.6f, 1.0f) * F(state, 0x14);
        speed = math_random_float_range(9.0f, 12.0f) * F(state, 0x14);
        angle = FastAddRotations(heading, math_random_signed_float_range(0.0f, 1.3962636f));
        velocity[0] = math_fast_sin_or_cos_a(angle) * 0.016666668f * speed;
        velocity[1] = math_fast_sin_or_cos_b(angle) * 0.016666668f * speed;
        velocity[2] = 0.0f;
        speed = math_random_float_range(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.016666668f;
        FastVecAdd(velocity, velocity, drift);
        part_spawn_fading_drift(position, velocity, lifetime, 0xFF7F40, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00405555591f, 1);
        {
            u8 *effect = part_spawn_fading_drift(position, velocity, lifetime, 0xFF2000, -(phase * 2), 48, 48, size * 1260000.0f, F(state, 0x14) * 4200.0f, 0.00405555591f, 0);
            if (effect)
                effect[2] = D_L00_001FE940.sparkColors[0];
        }
    }
    for (largeIdx = 0; largeIdx < I(state, 0x24); largeIdx++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = mat_fast_helper_a(D_L00_001B8C80.target[0] - F(object, 0x10), D_L00_001B8C80.target[1] - F(object, 0x14));
        phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
        lifetime = math_random_int_range(30, 50);
        position[0] = F(object, 0x10) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        size = math_random_float_range(0.75f, 1.5f) * F(state, 0x14);
        speed = math_random_float_range(9.0f, 12.0f) * F(state, 0x14);
        angle = FastAddRotations(heading, math_random_signed_float_range(0.0f, 1.3962636f));
        velocity[0] = math_fast_sin_or_cos_a(angle) * 0.016666668f * speed;
        velocity[1] = math_fast_sin_or_cos_b(angle) * 0.016666668f * speed;
        velocity[2] = 0.0f;
        speed = math_random_float_range(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.016666668f;
        FastVecAdd(velocity, velocity, drift);
        part_spawn_fading_drift(position, velocity, lifetime, 0xFF8F00, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00405555591f, 5);
    }
    for (smallIdx = 0; smallIdx < I(state, 0x28); smallIdx++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = mat_fast_helper_a(D_L00_001B8C80.target[0] - F(object, 0x10), D_L00_001B8C80.target[1] - F(object, 0x14));
        phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
        lifetime = math_random_int_range(30, 50);
        position[0] = F(object, 0x10) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        size = math_random_float_range(0.6f, 1.0f) * F(state, 0x14);
        speed = math_random_float_range(9.0f, 12.0f) * F(state, 0x14);
        angle = FastAddRotations(heading, math_random_signed_float_range(0.0f, 1.3962636f));
        velocity[0] = math_fast_sin_or_cos_a(angle) * 0.016666668f * speed;
        velocity[1] = math_fast_sin_or_cos_b(angle) * 0.016666668f * speed;
        velocity[2] = 0.0f;
        speed = math_random_float_range(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.016666668f;
        FastVecAdd(velocity, velocity, drift);
        part_spawn_fading_drift(position, velocity, lifetime, 0xFF6430, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00405555591f, 3);
    }
    for (debrisIdx = 0; debrisIdx < I(state, 0x30); debrisIdx++) {
        float roll, turn;
        speed = math_random_float_range(15.0f, 20.0f) * F(state, 0x14) * 0.016666668f;
        FastVecScale(position, object + 0xC0, speed);
        roll = math_random_signed_float_range(0.261799425f, 1.3962636f);
        turn = math_random_signed_float_range(0.261799425f, 1.3962636f);
        math_build_axis_angle_quat(rotation, object + 0xD0, roll);
        vec_rotate_by_quaternion(velocity, position, rotation);
        math_build_axis_angle_quat(rotation, object + 0xC0, turn);
        vec_rotate_by_quaternion(velocity, velocity, rotation);
        FastVecAdd(velocity, velocity, drift);
        part_spawn_trail_2(object + 0x10, velocity, math_random_int_range(20, 35), 0.00405555591f);
    }
    if (I(state, 0x34) && !I(state, 0x3C)) {
        *(Quad *)velocity = 0;
        velocity[2] = F(state, 0x14) * 0.13333334f;
        *(Quad *)position = *(Quad *)velocity;
        FastVecAdd(position, position, drift);
        part_spawn_shockwave_ring(object, object + 0x10, position, 16, 255, 0, 0, 40, F(state, 0x14) * 3.5f);
    }
    if (I(state, 0x38))
        SpawnExplosionEffects(object, D_L00_001A8F20, object + 0x10, 0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 9.0f, 0.0f, -1, 0, 0, -1, 0, 0x810001, F(state, 0x14) * 20.0f);
    sign = 1;
    angle = mat_fast_helper_a(D_L00_001B8C80.target[0] - F(object, 0x10), D_L00_001B8C80.target[1] - F(object, 0x14));
    for (smokeIdx = 0; smokeIdx < I(state, 0x2C); smokeIdx++) {
        float radius, roll, turn;
        position[0] = F(object, 0x10) + math_random_signed_float_range(0.0f, 1.0f) * F(state, 0x14);
        sign = -sign;
        position[1] = F(object, 0x14) + math_random_signed_float_range(0.0f, 1.0f) * F(state, 0x14);
        position[2] = F(object, 0x18) + math_random_signed_float_range(0.0f, 1.0f) * F(state, 0x14);
        radius = math_random_float_range(0.016666668f, 0.033333335f) * F(state, 0x14);
        roll = math_random_signed_float_range(0.0f, 1.3962636f);
        turn = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.5707965f));
        vec_build_spherical_offset(velocity, radius, turn, roll);
        FastVecAdd(velocity, velocity, drift);
        {
            u8 *effect = SpawnSpinningSparkParticle(position, 0.0f, 1.0f, sign, velocity, 0x7F60A0FF, 0, 1.01f, F(state, 0x14) * 315000.0f);
            if (effect) {
                u8 *extra = effect + 0x20;
                *(u16 *)(effect + 0xA) = math_random_int_range(40, 70);
                effect[9] = FloatToInt(4.0f) + 64;
                I(extra, 0x4) = 3;
                F(extra, 0x1C) = IntToFloat(math_random_int_range(1, 10));
                extra[0xA] = 64;
                extra[0xB] = effect[0xA];
            }
        }
    }
}
