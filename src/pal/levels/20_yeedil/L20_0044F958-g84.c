#include "include_asm.h"

#include "common.h"
extern int g_hero_vehicle_mode;
extern int g_hit_l20_result NOT_SDA;
extern float g_homing_shot_radius __attribute__((sda));
extern int g_homing_shot_trail_param __attribute__((sda));
extern void moby_mark_spawned(void *object);
extern float FastAddRotations(float, float);
extern void lerp_vector(float *out, char *a, char *b, float k);
extern float ApproachValue(float *p, float v, float w);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void moby_set_state(char *object, int a1, int a2);
extern void FastVecScale(void *dst, void *src, float value);
extern void vec_clear_128(void *target);
extern float math_random_float_range(float lo, float hi);
extern void *part_spawn_gravity_fade(void *, void *, float, float, float, int, int, int, int, int,
                           int);
extern int coll_sweep_from_object(char *, char *, int, int, float, float, float, int, int);
extern char *SpawnExplosion_pal(void *a0, int a1, int a2, int a3, int a4, int a5, int a6,
                          int a7, float f12, float f13, int s1, int s2, int s3,
                          int s4);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void part_spawn_two_glow_effects(void *);

/* Update handler for moby class 4855, a homing shot: it steers and moves each frame, leaves a particle trail, and explodes when it hits something. */
void homing_l20_shot_update_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float new_pos[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float trail_vel[4] __attribute__((aligned(16)));
    float zero_vec[4] __attribute__((aligned(16)));
    u8 mode;

    if (g_hero_vehicle_mode == 2) {
        moby_mark_spawned(moby);
        return;
    }
    mode = *(u8 *)(moby + 0x20);
    switch (mode) {
    case 0: {
        char *base;
        float v = *(float *)(state + 0x28);
        float a;
        float b;

        base = moby + 0x10;
        *(float *)(moby + 0xF0) =
            FastAddRotations(*(float *)(moby + 0xF0), v * 0.7f);
        *(float *)(moby + 0xF4) = FastAddRotations(
            *(float *)(moby + 0xF4), *(float *)(state + 0x28) * 0.5f);
        *(float *)(moby + 0xF8) = FastAddRotations(
            *(float *)(moby + 0xF8), *(float *)(state + 0x28));
        lerp_vector(offset, state, state + 0x10,
                      *(float *)(state + 0x30));
        ApproachValue((float *)(state + 0x30), 1.0f, *(float *)(state + 0x34));
        FastVecAdd(new_pos, base, offset);
        if (coll_test_point(new_pos, 0, moby, g_homing_shot_radius) != 0) {
            int id = g_hit_l20_result;

            if (id != 0 && id != *(int *)(moby + 0xB8)) {
                moby_set_state(moby, 1, -1);
                break;
            }
        }
        qcopy(moby + 0x10, new_pos);
        FastVecScale(trail_vel, state, -0.5f);
        vec_clear_128(zero_vec);
        a = math_random_float_range(2.5f, 3.0f) * 210000.0f;
        b = math_random_float_range(0.2f, 0.4f) * 210000.0f;
        part_spawn_gravity_fade(moby + 0x10, trail_vel, a, b, 0.0f, 0xF,
                      g_homing_shot_trail_param, 3, 0x50, 0, 0);
    } break;
    case 1: {
        char *base;
        base = moby + 0x10;
        coll_sweep_from_object(moby, base, 0x10001, 0, 3.0f, *(float *)(state + 0x20),
                      1.0f, 1, 0);
        SpawnExplosion_pal(base, 1, 0xA, 0xA, 0xA, 0xA, 0xA, 0, 2.0f, 20.0f, mode,
                      mode, 0, 0);
        moby_mark_spawned(moby);
        return;
    }
    }
    gfx_add_draw_callback_third(&part_spawn_two_glow_effects, moby);
}
