/* func_PAL_L16_0040B0C8, the PAL copy of func_L16_00406550: the same C, where the emitter count
 * D_L16_001B1510 and every func_002A7820 lifetime take the 50 Hz scale, the per-frame floats grow
 * by 6/5 (0.0040555 by 36/25), 16 becomes 13, and the two fire loops count up.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define I(p, o) (*(int *)((u8 *)(p) + (o)))

typedef struct { u8 pad[0x140]; float target[4]; } CameraView;
typedef struct { u8 pad[0xD4]; u8 *sparkColors; u8 pad2[0x98]; u8 *fireColors; } EffectTables;

extern float g_explosion_l16_inner_scale __attribute__((sda));
extern float g_explosion_l16_outer_scale __attribute__((sda));
extern int g_explosion_texture __attribute__((sda));
extern float g_particle_template[4] MACRO_ADDR;
extern CameraView g_snivelak_hero_state;
extern EffectTables g_scene_effect_material;

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
extern u8 *part_spawn_trail_2_pal(void *, void *, int, float);
extern char *func_PAL_003096D0(void *, void *, void *, int, int, int, int, int, float);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, int, int, int, int, int, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern u8 *func_PAL_002BE9A8(void *, float, float, int, void *, int, int, float, float);
extern float IntToFloat(int);

void func_PAL_L16_0040B0C8(u8 *object, void *unused)
{
    Vec4 position;
    Vec4 velocity;
    Vec4 rotation;
    u8 *state = *(u8 **)(object + 0x68);
    float inner, outer, angle, speed;
    u8 *effect;
    int na, nb, nc, ne, ng, nh, nk, sign;

    inner = g_explosion_l16_inner_scale * F(state, 0x14) * 210000.0f;
    outer = g_explosion_l16_outer_scale * F(state, 0x14) * 210000.0f;
    effect = part_spawn_gravity_fade(object + 0x10, g_particle_template, ((s32)(g_explosion_texture) * 5 + 2) / 6, 0x388EF7, 0, 100, 0, inner, outer, 0.0f, 0);
    if (effect)
        effect[2] = g_scene_effect_material.fireColors[0];
    effect = part_spawn_gravity_fade(object + 0x10, g_particle_template, ((s32)(g_explosion_texture) * 5 + 2) / 6, 0x14F700, 0, 100, 0, inner, outer, 0.0f, 0);
    if (effect)
        effect[2] = g_scene_effect_material.fireColors[0];
    for (na = 0; na < 2; na++) {
        effect = part_spawn_gravity_fade(object + 0x10, g_particle_template, ((s32)(g_explosion_texture) * 5 + 2) / 6, 0x38F738, 0, 127, 0, inner, outer, 0.0f, 0);
        if (effect)
            effect[2] = g_scene_effect_material.fireColors[5];
    }
    for (nb = 0; nb < 2; nb++) {
        effect = part_spawn_gravity_fade(object + 0x10, g_particle_template, ((s32)(g_explosion_texture) * 5 + 2) / 6, 0x38F738, 0, 127, 0, inner, outer, 0.0f, 0);
        if (effect)
            effect[2] = g_scene_effect_material.fireColors[6];
    }
    for (nc = 0; nc < I(state, 0x20); nc++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = mat_fast_helper_a(g_snivelak_hero_state.target[0] - F(object, 0x10), g_snivelak_hero_state.target[1] - F(object, 0x14));
        phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
        lifetime = math_random_int_range(30, 50);
        position[0] = F(object, 0x10) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        size = math_random_float_range(0.6f, 1.0f) * F(state, 0x14);
        speed = math_random_float_range(9.0f, 12.0f) * F(state, 0x14);
        angle = FastAddRotations(heading, math_random_signed_float_range(0.0f, 1.3962636f));
        velocity[0] = math_fast_sin_or_cos_a(angle) * 0.020000001f * speed;
        velocity[1] = math_fast_sin_or_cos_b(angle) * 0.020000001f * speed;
        velocity[2] = 0.0f;
        speed = math_random_float_range(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.020000001f;
        part_spawn_fading_drift(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0xFF7F40, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 1);
        {
            u8 *effect = part_spawn_fading_drift(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x20FF00, -(phase * 2), 48, 48, size * 1260000.0f, F(state, 0x14) * 4200.0f, 0.00584f, 0);
            if (effect)
                effect[2] = g_scene_effect_material.sparkColors[0];
        }
    }
    for (ne = 0; ne < I(state, 0x24); ne++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = mat_fast_helper_a(g_snivelak_hero_state.target[0] - F(object, 0x10), g_snivelak_hero_state.target[1] - F(object, 0x14));
        phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
        lifetime = math_random_int_range(30, 50);
        position[0] = F(object, 0x10) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        size = math_random_float_range(0.75f, 1.5f) * F(state, 0x14);
        speed = math_random_float_range(9.0f, 12.0f) * F(state, 0x14);
        angle = FastAddRotations(heading, math_random_signed_float_range(0.0f, 1.3962636f));
        velocity[0] = math_fast_sin_or_cos_a(angle) * 0.020000001f * speed;
        velocity[1] = math_fast_sin_or_cos_b(angle) * 0.020000001f * speed;
        velocity[2] = 0.0f;
        speed = math_random_float_range(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.020000001f;
        part_spawn_fading_drift(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x20FF00, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 5);
    }
    for (ng = 0; ng < I(state, 0x28); ng++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = mat_fast_helper_a(g_snivelak_hero_state.target[0] - F(object, 0x10), g_snivelak_hero_state.target[1] - F(object, 0x14));
        phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
        lifetime = math_random_int_range(30, 50);
        position[0] = F(object, 0x10) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
        size = math_random_float_range(0.6f, 1.0f) * F(state, 0x14);
        speed = math_random_float_range(9.0f, 12.0f) * F(state, 0x14);
        angle = FastAddRotations(heading, math_random_signed_float_range(0.0f, 1.3962636f));
        velocity[0] = math_fast_sin_or_cos_a(angle) * 0.020000001f * speed;
        velocity[1] = math_fast_sin_or_cos_b(angle) * 0.020000001f * speed;
        velocity[2] = 0.0f;
        speed = math_random_float_range(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.020000001f;
        part_spawn_fading_drift(position, velocity, ((s32)(lifetime) * 5 + 2) / 6, 0x64FF30, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 3);
    }
    for (nh = 0; nh < I(state, 0x30); nh++) {
        float roll, turn;
        speed = math_random_float_range(15.0f, 20.0f) * F(state, 0x14) * 0.020000001f;
        FastVecScale(position, object + 0xC0, speed);
        roll = math_random_signed_float_range(0.261799425f, 1.3962636f);
        turn = math_random_signed_float_range(0.261799425f, 1.3962636f);
        math_build_axis_angle_quat(rotation, object + 0xD0, roll);
        vec_rotate_by_quaternion(velocity, position, rotation);
        math_build_axis_angle_quat(rotation, object + 0xC0, turn);
        vec_rotate_by_quaternion(velocity, velocity, rotation);
        part_spawn_trail_2_pal(object + 0x10, velocity, ((s32)(math_random_int_range(20, 35)) * 5 + 2) / 6, 0.00584f);
    }
    if (I(state, 0x34)) {
        *(Quad *)velocity = 0;
        velocity[2] = F(state, 0x14) * 0.16000001f;
        *(Quad *)position = *(Quad *)velocity;
        func_PAL_003096D0(object, object + 0x10, position, 13, 0, 0, 255, 40, F(state, 0x14) * 3.5f);
    }
    SpawnExplosionEffects_pal(object, g_particle_template, object + 0x10, 0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 9.0f, 0.0f, -1, 0, 0, -1, 0, 0x810001, F(state, 0x14) * 20.0f);
    sign = 1;
    angle = mat_fast_helper_a(g_snivelak_hero_state.target[0] - F(object, 0x10), g_snivelak_hero_state.target[1] - F(object, 0x14));
    for (nk = 0; nk < I(state, 0x2C); nk++) {
        float radius, roll, turn;
        position[0] = F(object, 0x10) + math_random_signed_float_range(0.0f, 1.0f) * F(state, 0x14);
        sign = -sign;
        position[1] = F(object, 0x14) + math_random_signed_float_range(0.0f, 1.0f) * F(state, 0x14);
        position[2] = F(object, 0x18) + math_random_signed_float_range(0.0f, 1.0f) * F(state, 0x14);
        radius = math_random_float_range(0.020000001f, 0.040000003f) * F(state, 0x14);
        roll = math_random_signed_float_range(0.0f, 1.3962636f);
        turn = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.5707965f));
        vec_build_spherical_offset(velocity, radius, turn, roll);
        {
            u8 *effect = func_PAL_002BE9A8(position, 0.0f, 1.0f, sign, velocity, 0x7F20FF60, 0, 1.01f, F(state, 0x14) * 315000.0f);
            if (effect) {
                u8 *extra = effect + 0x20;
                *(u16 *)(effect + 0xA) = ((s32)(math_random_int_range(40, 70)) * 5 + 2) / 6;
                effect[9] = FloatToInt(4.0f) + 64;
                I(extra, 0x4) = 3;
                F(extra, 0x1C) = IntToFloat(((s32)(math_random_int_range(1, 10)) * 5 + 2) / 6);
                extra[0xA] = 64;
                extra[0xB] = effect[0xA];
            }
        }
    }
}
