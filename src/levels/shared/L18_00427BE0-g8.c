#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef signed short s16;

typedef signed int s32;

typedef float f32;

/* Small-data controls this level reads through $gp in ordinary flow. */
extern s32 D_L18_001B1254 __attribute__((sda));

extern s32 D_L18_001B1258 __attribute__((sda));

extern s32 D_L18_001B125C __attribute__((sda));

extern f32 D_L18_001B12FC __attribute__((sda));

extern f32 D_L18_001B12C0 __attribute__((sda));

extern f32 D_L18_001B1C4C __attribute__((sda));

extern f32 D_L18_001B1C48 __attribute__((sda));

extern f32 D_L18_001B1C44 __attribute__((sda));

extern f32 D_L18_001B1C40 __attribute__((sda));

extern s32 math_random_int_range(s32, s32);

extern int FastDecTimer(void *);

extern int math_fast_float_d(s32);

extern void value_set_and_smooth(void *, void *, s32, s32, f32);

extern void moby_transform_joint_to_world(void *, s32, void *);

extern s32 func_00337AD8(s32, s32, f32);

extern void gfx_l00_draw_billboard_quad(void *, s32, f32, f32);

/* Renews the state's 0x39A banner: resamples the 0x390 countdown, refreshes the two
   clearings and bumps the object's own 0x96 counter before the shared follow-up. */
/* Asks the shared vertex probe for the object's 0x78 mask and places the resulting
   height with the state's own 0x158 rise. */
void probe_place_at_height(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    if (D_L18_001B1C4C < *(f32 *)(state + 0x15C)) {
        s32 probe = func_00337AD8(*(s32 *)(obj + 0x78) & 0xFFFFFF, *(s32 *)(obj + 0x78),
                                  *(f32 *)(state + 0x15C));
        gfx_l00_draw_billboard_quad(obj + 0x10, probe,
                          D_L18_001B1C44 + D_L18_001B1C48 * *(f32 *)(state + 0x158),
                          D_L18_001B1C40);
    }
}

/* hands the two sampled buffers and the measured flag pair to the shared placement. */
extern s32 coll_cast_object_line(void *, void *, void *, s32, f32, f32, s32, s32, s32);

/* The state's banner timer: the shared helper refits the object's height against the
   state's own rise, and the two ends of the countdown are eased into the frame rate. */
extern f32 D_L18_001B1C50 __attribute__((sda));

extern f32 D_L18_001B1C54[] __attribute__((sda));

extern s32 D_L18_001B1C58 __attribute__((sda));

extern f32 D_L18_001B1C5C __attribute__((sda));

extern void gfx_set_gs_register_constant(void);

extern f32 math_lerp_float(f32, f32, f32);

extern s32 FloatToInt(f32);

extern void gfx_draw_lens_flare_quad(void *, void *, s32, s32, f32, f32, f32);

/* Emits a burst of effect particles whose number and size depend on the fade level at +0x158. */
void part_emit_fade_burst(u8 *obj) {
    u8 *state;
    f32 intensity;
    s32 particleCount;

    gfx_set_gs_register_constant();
    state = *(u8 **)(obj + 0x68);
    intensity = math_lerp_float(D_L18_001B1C50, D_L18_001B1C54[0], *(f32 *)(state + 0x158));
    if (*(f32 *)(state + 0x158) < 0.1f) {
        particleCount = FloatToInt((f32)D_L18_001B1C58 * *(f32 *)(state + 0x158) * 10.0f);
    } else {
        particleCount = FloatToInt((f32)D_L18_001B1C58 * (1.0f - *(f32 *)(state + 0x158)));
    }
    gfx_draw_lens_flare_quad(obj + 0x10, obj + 0xC0, particleCount, 0, intensity, D_L18_001B1C5C, 0.08f);
}

extern int D_L18_001B1C60 __attribute__((sda));
extern float D_L18_001B1C64 __attribute__((sda));
extern float D_L18_001B1C78 __attribute__((sda));
extern float D_L18_001B1C7C __attribute__((sda));
extern float D_L18_001B1C80 __attribute__((sda));
extern float D_L18_001B1C84 __attribute__((sda));
extern int D_L18_001B1C88 __attribute__((sda));
extern int D_L18_001B1C8C __attribute__((sda));
extern float D_L18_001B1C90 __attribute__((sda));
extern int D_L18_001B1C98 __attribute__((sda));
extern int D_L18_001B1C9C __attribute__((sda));
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void part_build_jittered_curve(void *, int, void *, float);
extern void ribbon_draw_along_points(void *, int, int, int, int, float, float);
extern void part_draw_billboard_sprite(void *, int, float, int, float, int, int);

/* Builds and draws the state's two ribbons (control points at +0 and +0xA0, faded by the
   0x158 level), then emits the paired particle bursts at +0, +0x10, +0xA0 and +0xB0. The
   point buffer is sized by the level's count control. */
void ribbon_draw_with_bursts(char *object)
{
    char *state = *(char **)(object + 0x68);
    int count = D_L18_001B1C60;
    typedef struct { float values[4]; } Point __attribute__((aligned(16)));
    Point points[count];
    float step = D_L18_001B1C64;
    int life;
    float first, second, large, small;

    life = math_random_int_range(48, 128);
    first = (1.0f - *(float *)(state + 0x158)) * math_random_float_range(D_L18_001B1C78, D_L18_001B1C7C);
    second = (1.0f - *(float *)(state + 0x158)) * math_random_float_range(D_L18_001B1C80, D_L18_001B1C84);
    part_build_jittered_curve(points, count, state, step);
    ribbon_draw_along_points(points, count, life, D_L18_001B1C88, D_L18_001B1C8C, first, second);
    life = math_random_int_range(48, 128);
    first = (1.0f - *(float *)(state + 0x158)) * math_random_float_range(D_L18_001B1C78, D_L18_001B1C7C);
    second = (1.0f - *(float *)(state + 0x158)) * math_random_float_range(D_L18_001B1C80, D_L18_001B1C84);
    part_build_jittered_curve(points, count, state + 0xA0, step);
    ribbon_draw_along_points(points, count, life, D_L18_001B1C88, D_L18_001B1C8C, first, second);
    small = D_L18_001B1C90 * (1.0f - *(float *)(state + 0x158));
    large = small * 0.5f;
    part_draw_billboard_sprite(state, D_L18_001B1C98, large, math_random_int_range(80, 96), math_random_angle(), 49, 2);
    small *= 0.7f;
    part_draw_billboard_sprite(state, D_L18_001B1C9C, small, math_random_int_range(8, 22), math_random_angle(), 11, 2);
    part_draw_billboard_sprite(state + 0x10, D_L18_001B1C98, large, math_random_int_range(80, 96), math_random_angle(), 49, 2);
    part_draw_billboard_sprite(state + 0x10, D_L18_001B1C9C, small, math_random_int_range(8, 22), math_random_angle(), 11, 2);
    part_draw_billboard_sprite(state + 0xA0, D_L18_001B1C98, large, math_random_int_range(80, 96), math_random_angle(), 49, 2);
    part_draw_billboard_sprite(state + 0xA0, D_L18_001B1C9C, small, math_random_int_range(8, 22), math_random_angle(), 11, 2);
    part_draw_billboard_sprite(state + 0xB0, D_L18_001B1C98, large, math_random_int_range(80, 96), math_random_angle(), 49, 2);
    part_draw_billboard_sprite(state + 0xB0, D_L18_001B1C9C, small, math_random_int_range(8, 22), math_random_angle(), 11, 2);
}

typedef float L18_EDE8f32;

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

extern void vec_random_direction(void *, L18_EDE8f32, L18_EDE8f32);
extern int math_random_int_below(int);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void FastVecAdd(void *, void *, void *);
extern unsigned char D_L18_002BD9B0[];
extern L18_EDE8f32 D_L18_001B1C68 __attribute__((sda));
extern L18_EDE8f32 D_L18_001B1C6C __attribute__((sda));
extern L18_EDE8f32 D_L18_001B1C70 __attribute__((sda));
extern L18_EDE8f32 D_L18_001B1C74 __attribute__((sda));

/* Sets up the two ribbon emitters with random settings and a random starting point near the object. */
void ribbon_init_emitters(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    L18_EDE8f32 point[4] __attribute__((aligned(16)));
    s32 i;

    for (i = 0; i < 2; i++) {
        u8 *emitter = state + i * 0xA0;

        vec_random_direction(emitter + 0x60, D_L18_001B1C68 * 0.00029088824f, D_L18_001B1C6C * 0.00029088824f);
        vec_random_direction(emitter + 0x70, D_L18_001B1C68 * 0.00029088824f, D_L18_001B1C6C * 0.00029088824f);
        vec_random_direction(emitter + 0x80, D_L18_001B1C70, D_L18_001B1C74);
        vec_random_direction(emitter + 0x90, D_L18_001B1C70, D_L18_001B1C74);
        qcopy(state, state + 0x140);
        qcopy(state + 0xA0, state + 0x140);
        matrix_mul_vec3(point, D_L18_002BD9B0 + math_random_int_below(6) * 16, obj + 0xC0);
        FastVecAdd(point, obj + 0x10, point);
        qcopy(state + 0x10, point);
    }
}
