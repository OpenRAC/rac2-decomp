#include "common.h"

/* func_L20_0044AE58: mode 0 steers the velocity (0xF0..0xF8), moves by an interpolated
 * step with a contact test and emits particles; mode 1 calls func_002A8C28 and
 * func_0032C700 at the position and removes the object (func_0029F338).  Every other
 * mode, mode 0 included, ends with the common callback.
 * Built -G8: the body reaches level data through $gp.
 *
 * The position is the expression arg0 + 0x10 at its later uses, not a variable: gcse's
 * PRE then keeps a copy of the first computation for them (retail's $s1 and $s4).
 * The contact vector is an array, so its address is a constant that reload
 * rematerialises at every use (addiu ...,$sp,0x20), and it takes the first stack slot. */

extern int D_L20_001A8F00;

extern int D_L20_001C0418 NOT_SDA;

extern float D_L20_001B2468 __attribute__((sda));

extern int D_L20_001B2460 __attribute__((sda));

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

extern void SpawnExplosion(void *a0, int a1, int a2, int a3, int a4, int a5, int a6,
                          int a7, float f12, float f13, int s1, int s2, int s3,
                          int s4);

extern void gfx_add_draw_callback_third(void (*)(void *), void *);

extern void part_spawn_two_glow_effects(void *);

/* Update handler for moby class 4855, a homing shot: it steers and moves each frame, leaves a particle trail, and explodes when it hits something. */
void homing_l20_shot_update(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float newPos[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    float sparkVelocity[4] __attribute__((aligned(16)));
    float sparkScratch[4] __attribute__((aligned(16)));
    u8 mode;

    if (D_L20_001A8F00 == 2) {
        moby_mark_spawned(moby);
        return;
    }
    mode = *(u8 *)(moby + 0x20);
    switch (mode) {
    case 0: {
        char *base;
        float speed = *(float *)(state + 0x28);
        float startSize;
        float endSize;

        base = moby + 0x10;
        *(float *)(moby + 0xF0) =
            FastAddRotations(*(float *)(moby + 0xF0), speed * 0.7f);
        *(float *)(moby + 0xF4) = FastAddRotations(
            *(float *)(moby + 0xF4), *(float *)(state + 0x28) * 0.5f);
        *(float *)(moby + 0xF8) = FastAddRotations(
            *(float *)(moby + 0xF8), *(float *)(state + 0x28));
        lerp_vector(step, state, state + 0x10,
                      *(float *)(state + 0x30));
        ApproachValue((float *)(state + 0x30), 1.0f, *(float *)(state + 0x34));
        FastVecAdd(newPos, base, step);
        if (coll_test_point(newPos, 0, moby, D_L20_001B2468) != 0) {
            int id = D_L20_001C0418;

            if (id != 0 && id != *(int *)(moby + 0xB8)) {
                moby_set_state(moby, 1, -1);
                break;
            }
        }
        qcopy(moby + 0x10, newPos);
        FastVecScale(sparkVelocity, state, -0.5f);
        vec_clear_128(sparkScratch);
        startSize = math_random_float_range(2.5f, 3.0f) * 210000.0f;
        endSize = math_random_float_range(0.2f, 0.4f) * 210000.0f;
        part_spawn_gravity_fade(moby + 0x10, sparkVelocity, startSize, endSize, 0.0f, 0xF,
                      D_L20_001B2460, 3, 0x50, 0, 0);
    } break;
    case 1: {
        char *base;
        base = moby + 0x10;
        coll_sweep_from_object(moby, base, 0x10001, 0, 3.0f, *(float *)(state + 0x20),
                      1.0f, 1, 0);
        SpawnExplosion(base, 1, 0xA, 0xA, 0xA, 0xA, 0xA, 0, 2.0f, 20.0f, mode,
                      mode, 0, 0);
        moby_mark_spawned(moby);
        return;
    }
    }
    gfx_add_draw_callback_third(&part_spawn_two_glow_effects, moby);
}
