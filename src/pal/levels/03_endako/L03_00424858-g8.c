#include "names.h"
/* func_PAL_L03_00424858, the PAL copy of func_L03_0041F410: the same C, where 0.016666668f becomes
 * 0.020000001f and the first random value is scaled to 50 Hz. The scale's extra insns keep loop.c from
 * hoisting 210000.0f on its own, so the loop's constants are locals, in retail's preheader order. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern float fast_vec_dist(void *, void *);
extern int math_fast_helper_a(void *, float);
extern int math_random_int_range(int, int);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern void vec_random_direction(void *, float, float);
extern void lerp_vector(void *, void *, void *, float);
extern u8 *part_spawn_burst(void *, void *, int, int, int, int, float, float, float, float, float);
extern int math_random_int_below(int);
extern u8 *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern int D_L03_001B1C40 __attribute__((sda));
extern int D_L03_001B1C44 __attribute__((sda));
extern int D_L03_001B1C48 __attribute__((sda));
extern int D_L03_001B1C58 __attribute__((sda));
/* Upper bounds are the second words of the measured min/max pairs.
 * Their unsized views keep the absolute accesses alongside GP lower bounds. */
extern int D_L03_001B1C58_1[] MACRO_ADDR;
extern float D_L03_001B1C68 __attribute__((sda));
extern float D_L03_001B1C68_1[] MACRO_ADDR;
extern float D_L03_001B1C50 __attribute__((sda));
extern float D_L03_001B1C50_1[] MACRO_ADDR;
extern float D_L03_001B1C70 __attribute__((sda));
extern int D_L03_001B1C60_1[] MACRO_ADDR;
extern int D_L03_001B1C60 __attribute__((sda));
extern float D_L03_001B1C70_1[] MACRO_ADDR;
/* Emits two particle families along the visible segment between from and to. */
void func_PAL_L03_00424858(u8 *entity, Vector *from, Vector *to, int enabled) {
    Vector test, velocity, point, aux;
    int i, count, color, rotation;
    float life, step;
    qcopy(&test, from);
    test.f[3] = fast_vec_dist(from, to);
    if (test.f[3] > 1.0f) return;
    if (math_fast_helper_a(&test, 32.0f) == -1) return;
    for (i=0; i<D_L03_001B1C40; i++) {
        float lo = 0.0f, dt = 0.020000001f, scale = 210000.0f;
        color = (math_random_int_range(D_L03_001B1C58, D_L03_001B1C58_1[1]) * 5 + 2) / 6;
        rotation = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        life = math_random_float_range(D_L03_001B1C68, D_L03_001B1C68_1[1]) * scale;
        vec_random_direction(&velocity, lo, dt);
        velocity.f[2] += math_random_float_range(D_L03_001B1C50, D_L03_001B1C50_1[1]) * dt;
        lerp_vector(&point, from, to, math_random_float_range(0, 1));
        part_spawn_burst(&point, &velocity, color, D_L03_001B1C48 >> 24,
                     D_L03_001B1C48 & 0xFFFFFF, rotation, life, 500.0f, 1.0f, 0.0f, 1.0f);
    }
    if (enabled) {
        int j;
        count = D_L03_001B1C44;
        if (entity[0x20] == 5) count = math_random_int_below(2);
        step = 1.0f / (float)D_L03_001B1C44;
        for (j=0; j<count; j++) {
            point.q = 0;
            aux.q = 0;
            point.f[3] = D_L03_001B1C70;
            aux.f[3] = D_L03_001B1C70_1[1];
            velocity.q = point.q;
            point.q = aux.q;
            life = math_random_float_range(0, step);
            lerp_vector(&aux, from, to, life + (float)j * step);
            aux.f[2] += 0.02f;
            {
                u8 *p = part_spawn_trail(&aux, &velocity, &point, 0x40000000, 0x10000000, 5,
                                    D_L03_001B1C60, D_L03_001B1C60_1[1], -1);
                if (p) p[1] = 1;
            }
        }
    }
}
