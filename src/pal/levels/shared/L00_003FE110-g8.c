#include "names.h"
/* func_PAL_L00_003FE110, the PAL copy of func_L00_003F9A30: the same C, with its timers and
 * per-frame rates scaled to 50 Hz and each spark id local to its own loop. */
#include "common.h"

extern void vec_transform_or_copy(void *, void *);
extern void func_PAL_L00_004007B0(void);
extern float FastAddRotations(float, float);
extern int FastDecTimer(void *);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern void gfx_register_final_draw_callback(void *, void *);
extern void func_PAL_L00_003FF050(void);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecScale(void *, void *, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void vec_add_transformed_or_copy(void *, void *, void *);
extern void *part_spawn_trail_2(void *, void *, int, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void *part_spawn_spinning_particle(void *, void *, unsigned, unsigned, float, int, int, int, int, int, float);
extern char *SpawnSpinningSparkParticle(float, float, void *, int, void *, unsigned, int, float, float);
extern char g_default_vector[] __attribute__((sda));
extern float g_effect_spin_speed_a __attribute__((sda));
extern float g_effect_spin_speed_b __attribute__((sda));
extern float g_effect_spin_speed_c __attribute__((sda));
extern float g_effect_spin_speed_d __attribute__((sda));
extern int g_effect_timer_limit __attribute__((sda));
extern int g_screen_fade_timer __attribute__((sda));
extern int g_effect_id_min __attribute__((sda));
extern int g_effect_id_max __attribute__((sda));
extern float g_effect_dir_speed_min __attribute__((sda));
extern float g_effect_dir_speed_max __attribute__((sda));
extern float g_effect_trail_speed_scale __attribute__((sda));
extern float g_glow_radius_max __attribute__((sda));
extern float g_glow_radius_min __attribute__((sda));

typedef int EffectQuad __attribute__((mode(TI)));

/* Private state of the emitter, as far as this function uses it. */
typedef struct EffectState {
    float angles[6];
    float height;
    short timer1, timer2;
    u8 pad20[4];
    float scale;
    u8 pad28[0x34 - 0x28];
    short timer3;
    u8 pad36[0x40 - 0x36];
    int f40;
} EffectState;

/* The emitter moby, as far as this function uses it. */
typedef struct Emitter {
    u8 pad00[0x10];
    float pos[4];
    u8 pad20[0x68 - 0x20];
    EffectState *state;
    u8 pad6C[0xC0 - 0x6C];
    float dirC0[4];
    float dirD0[4];
} Emitter;

/* Advance the emitter's angles and timers, emit its initial burst, then spread
 * spinning sparks along a height-dependent segment above the stored ground height.
 */
void func_PAL_L00_003FE110(Emitter *self)
{
    EffectState *state = self->state;
    float a[4], b[4], c[4], d[4], e[4], f[4];
    float x, y, radius, height, ratio;
    char *spark;
    int i, count, remaining;

    vec_transform_or_copy(self->pos, self->pos);
    func_PAL_L00_004007B0();
    state->angles[0] = FastAddRotations(state->angles[0], g_effect_spin_speed_a * 0.01745329424738884f);
    state->angles[1] = FastAddRotations(state->angles[1], g_effect_spin_speed_b * 0.01745329424738884f);
    state->angles[2] = FastAddRotations(state->angles[2], 0.00436332356184721f);
    state->angles[3] = FastAddRotations(state->angles[3], -0.00436332356184721f);
    state->angles[4] = FastAddRotations(state->angles[4], g_effect_spin_speed_c * 0.01745329424738884f);
    state->angles[5] = FastAddRotations(state->angles[5], g_effect_spin_speed_d * 0.01745329424738884f);
    FastDecTimer(&state->timer2);
    FastDecTimer(&state->timer3);
    math_fast_float_d(&state->f40);
    if (FastDecTimer(&state->timer1) && state->timer2 == 0) {
        if (!g_screen_fade_timer)
            moby_mark_spawned(self);
        return;
    }

    gfx_register_final_draw_callback((void *)func_PAL_L00_003FF050, self);

    if (state->timer2 >= ((g_effect_timer_limit - 6) * 5 + 2) / 6) {
        for (i = 0; i < 20; i++) {
            float angle1, angle2;
            int id;

            FastVecScale(a, self->dirC0, math_random_float_range(g_effect_dir_speed_min, g_effect_dir_speed_max) * 0.020000001f);
            angle1 = math_random_signed_float_range(0.2617994248867035f, 1.396263599395752f);
            angle2 = math_random_signed_float_range(0.2617994248867035f, 1.396263599395752f);
            math_build_axis_angle_quat(c, self->dirD0, angle1);
            vec_rotate_by_quaternion(b, a, c);
            math_build_axis_angle_quat(c, self->dirC0, angle2);
            vec_rotate_by_quaternion(b, b, c);
            id = (math_random_int_range(g_effect_id_min, g_effect_id_max) * 5 + 2) / 6;
            vec_add_transformed_or_copy(b, b, self->pos);
            part_spawn_trail_2(self->pos, b, id, g_effect_trail_speed_scale * 0.00040000002f);
        }
    }

    if ((unsigned)((unsigned short)state->timer2 - 11) < 22) {
        float z, x, speed;

        z = math_random_float_range(-0.9599311947822571f, -1.396263599395752f);
        x = math_random_angle();
        vec_build_spherical_offset(a, math_random_float_range(0.0f, 0.5f) * 0.020000001f, x, z);
        speed = math_random_float_range(0.25f, 0.75f) * 210000.0f;
        FastVecScale(b, self->dirC0, -0.45f);
        FastVecAdd(b, self->pos, b);
        c[0] = b[0] + math_random_signed_float_range(0.0f, 0.25f);
        c[1] = b[1] + math_random_signed_float_range(0.0f, 0.25f);
        c[2] = b[2] + math_random_signed_float_range(0.0f, 0.25f);
        vec_add_transformed_or_copy(a, a, c);
        part_spawn_spinning_particle(c, a, 0x4F93E5FF, 0x102434EE, speed, math_random_int_range(25, 37), 1, -1, -1, 0, 0.5f);
    }

    x = IntToFloat(state->timer2);
    radius = (g_glow_radius_min + (g_glow_radius_max - g_glow_radius_min) * (x * state->scale)) * 1.5f;
    height = state->height;
    y = self->pos[2] - height;
    if (y > 0.0f && y < radius && state->timer2 >= 22) {
        float factor;

        ratio = y / radius;
        factor = ratio * -0.65f + 0.75f;
        count = FloatToInt((1.0f - ratio) * 30.0f);
        if (count <= 0)
            count = 1;

        *(EffectQuad *)a = 0;
        a[2] = 1.0f;
        a[3] = 1.0f;
        FastVecCross(b, a, self->dirC0);
        vec_scale_to_length(b, b, radius * factor);
        qcopy(c, self->pos);
        c[2] = height + 0.25f;
        FastVecAdd(d, c, b);
        FastVecSub(e, c, b);
        FastVecSub(f, e, d);
        FastVecScale(f, f, 1.0f / (float)count);

        for (remaining = 0; remaining < count; remaining++) {
            float speed;
            int id;

            id = math_random_int_below(16);
            if (math_random_int_below(2))
                id = -id;
            speed = math_random_float_range(0.2f, 1.5f) * 210000.0f;
            spark = SpawnSpinningSparkParticle(0.3f, 1.0f, d, id, g_default_vector, 0x7F204080, 1, 0.9f, speed);
            FastVecAdd(d, d, f);
            if (spark) {
                char *ext = spark + 0x20;

                *(short *)(spark + 0xA) = (math_random_int_range(8, 25) * 5 + 2) / 6;
                spark[9] = FloatToInt(4.0f) + 64;
                *(int *)(ext + 4) = 2;
                ext[0xA] = math_random_int_range(80, 127);
                ext[0xB] = *(unsigned char *)(spark + 0xA);
            }
        }
    }
}
