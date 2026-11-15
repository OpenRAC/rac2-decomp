/* func_PAL_0030E0E0, the PAL copy of func_0030CCD0: the same C, where D_L00_001AF384 is scaled by 1.2f, the second
 * arguments 15, 15 and 12 of func_002C2210 become 12, 12 and 10, and s is declared before i, which puts i << 2 after
 * &s->end in gcse's buckets and so swaps their spill slots. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct {
    Vector start, end;
    void *target;
    float length;
    int unknown28, timer, light, fade;
    short segment;
} BeamState;
typedef struct { char pad[0x10]; Vector pos; } Thing;
typedef struct { char pad[0x10]; float height; } ThingInfo;
typedef struct { char pad[0x68]; BeamState *vars; } Actor;

extern int g_current_map_index;
extern int D_L00_001A8F00;
extern BeamState D_L00_001C5890[], D_L00_001C58E0[];
typedef union { u8 b[0x2600]; s32 i[0x980]; void *ptr[0x980]; } Hero;
extern char g_hero_state[];
extern float D_L00_001AF2E4 __attribute__((sda));
extern float D_L00_001AF2F0 __attribute__((sda)), D_L00_001AF2F4 __attribute__((sda)), D_L00_001AF2F8 __attribute__((sda));
extern float D_L00_001AF2FC __attribute__((sda)), D_L00_001AF300 __attribute__((sda)), D_L00_001AF304 __attribute__((sda));
extern float D_L00_001AF308 __attribute__((sda)), D_L00_001AF30C __attribute__((sda)), D_L00_001AF310 __attribute__((sda));
extern float D_L00_001AF314 __attribute__((sda)), D_L00_001AF318 __attribute__((sda)), D_L00_001AF31C __attribute__((sda));
extern float D_L00_001AF320 __attribute__((sda)), D_L00_001AF334 __attribute__((sda)), D_L00_001AF338 __attribute__((sda));
extern float D_L00_001AF384 __attribute__((sda));
extern Vector D_L00_0023A210[2][20], D_L00_0023A340[], D_L00_0023A4E0[];
extern float D_L00_0023A490[], D_L00_0023A620[];
extern char D_L00_001A8F20[] MACRO_ADDR;

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float IntToFloat(int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern ThingInfo *moby_get_private_value_0(void *);
extern float math_wrap_angle_to_pi(float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern float FastVecLength(void *);
extern float math_fast_sin_or_cos_a(float);
extern unsigned int beam_get_glow_color(void);

void func_PAL_0030E0E0(Actor *actor)
{
    Vector goal, dir, side, step, last, delta, tip;
    BeamState *s = actor->vars;
    float angle;
    float len;
    float *p;
    int off4;
    float dist;
    void *target;
    float was;
    int spin;
    float d1;
    float weight;
    float wave;
    int i;
    float sway;
    void *other;
    float zero;
    Vector *to;
    ThingInfo *info;
    float h;

    if (g_current_map_index == 1 && D_L00_001A8F00 == 2)
        s = D_L00_001C5890;
    if (g_current_map_index == 0x14 && D_L00_001A8F00 == 2)
        s = D_L00_001C58E0;
    len = D_L00_001AF2E4 * 0.05f;
    D_L00_001AF2FC = FastAddRotations(D_L00_001AF2FC, D_L00_001AF300);
    D_L00_001AF304 = fast_subtract_rotations(D_L00_001AF304, D_L00_001AF308);
    D_L00_001AF318 = FastAddRotations(D_L00_001AF318, D_L00_001AF31C);
    other = 0;
    if (s->target == 0)
        other = ((Hero *)g_hero_state)->ptr[0x5C0 / 4];
    if (other != 0) {
        if (s->target == 0)
            s->target = other;
    }
    target = s->target;
    if (target != 0) {
        info = 0;
        if (D_L00_001A8F00 != 2)
            info = moby_get_private_value_0(target);
        qcopy(&goal, &((Thing *)s->target)->pos);
        if (info != 0)
            goal.f[2] += info->height;
        else
            goal.f[2] += 0.2f;
        len = fast_vec_dist(s, &goal) * 0.05f;
    }
    s->segment = 0x14;
    FastVecSub(&dir, &s->end, s);
    vec_scale_to_length(&dir, &dir, 1.0f);
    if (s->target != 0) {
        FastVecCross(&side, &dir, g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(&dir, &dir, &side, 0.17453295f);
    }
    FastVecScale(&last, &dir, len);
    qcopy(D_L00_0023A210[0], s);
    qcopy(D_L00_0023A210[1], s);
    i = 1;
    do {
        float fi = i;
        off4 = i * 4;
        weight = IntToFloat(i) * 0.05f;
        wave = D_L00_001AF2F4 + (D_L00_001AF2F8 - D_L00_001AF2F4) * weight;
        wave = wave * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L00_001AF2FC + fi * D_L00_001AF2F0));
        wave = wave + math_random_signed_float_range(D_L00_001AF334, D_L00_001AF338);
        p = (float *)(off4 + (char *)D_L00_0023A490);
        was = *p;
        *p = wave;
        D_L00_0023A210[0][i].f[2] -= was;
        FastVecSub(&side, &D_L00_0023A210[0][i], &D_L00_0023A210[0][i - 1]);
        lerp_vector(&step, &side, &last, 0.85f);
        zero = 0.0f;
        d1 = FastVecLength(&step);
        if (d1 == zero) {
            qcopy(&D_L00_0023A210[0][i], &D_L00_0023A210[0][i - 1]);
        } else {
            FastVecScale(&step, &step, len / d1);
            FastVecAdd(&D_L00_0023A210[0][i], &D_L00_0023A210[0][i - 1], &step);
            qcopy(&last, &step);
        }
        D_L00_0023A210[0][i].f[2] += wave;
        FastVecSub(&side, &D_L00_0023A210[0][i], &D_L00_0023A210[0][i - 1]);
        if (s->target != 0) {
            FastVecSub(&tip, &goal, &D_L00_0023A210[0][i]);
            dist = FastVecLength(&tip);
            if (dist != zero) {
                if (i == 0x13) {
                    sway = 0.5f;
                    len = dist;
                } else if (i >= 0x10) {
                    sway = 0.5f;
                    h = IntToFloat(0x13 - i);
                    len = dist / h;
                } else {
                    sway = 0.1f;
                }
                /* Live across the next call: loop.c hoists this copy, which retail's preheader order shows. */
                to = &last;
                FastVecScale(&tip, &tip, len / dist);
                lerp_vector(to, to, &tip, sway);
            }
        }
        angle = math_wrap_angle_to_pi(D_L00_001AF304 + (float)i * D_L00_001AF30C);
        wave = D_L00_001AF310 * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L00_001AF318 + (float)i * D_L00_001AF320));
        qcopy(&D_L00_0023A210[1][i], &D_L00_0023A210[0][i]);
        wave = wave * math_fast_sin_or_cos_b(angle);
        D_L00_0023A620[i] = wave;
        D_L00_0023A210[1][i].f[2] += wave;
        wave = FastAddRotations(mat_fast_helper_a(side.f[0], side.f[1]), 1.5707965f);
        {
            float r2 = D_L00_001AF314 * math_fast_sin_or_cos_a(angle);
            delta.f[0] = math_fast_sin_or_cos_a(wave) * r2;
            delta.f[1] = math_fast_sin_or_cos_b(wave) * r2;
        }
        delta.f[2] = 0.0f;
        qcopy(&D_L00_0023A4E0[i], &delta);
        FastVecAdd(&D_L00_0023A210[1][i], &D_L00_0023A210[1][i], &delta);
        i++;
    } while (i < 0x14);
    qcopy(&s->end, D_L00_0023A340);
    {
        float pitch = math_random_signed_float_range(0.52359885f, 1.0471977f);
        float yaw = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(&tip, &dir, D_L00_001AF384 * 1.2f);
        math_apply_axis_rotation_to_quat(&tip, &tip, g_hero_state + 0x740, yaw);
        math_apply_axis_rotation_to_quat(&tip, &tip, g_hero_state + 0x750, pitch);
    }
    spin = math_random_int_range(1, 8);
    if (math_random_int_below(2))
        spin = -spin;
    wave = math_random_float_range(0.2f, 0.6f);
    part_spawn_ground_effect(s, 0xC, wave * 0.3f, wave, beam_get_glow_color() | 0x7F000000, 0, spin, &tip, 0, 0.0f);
    part_spawn_ground_effect(s, 0xC, wave * 0.15f, wave * 0.5f, 0x307F7F7F, 0, -spin, &tip, 0, 0.0f);
    spin = math_random_int_range(1, 8);
    if (math_random_int_below(2))
        spin = -spin;
    wave = math_random_float_range(0.15f, 3.0f);
    part_spawn_ground_effect(&s->end, 0xA, wave * 0.1f, wave, beam_get_glow_color() | 0x7F000000, 0, spin, D_L00_001A8F20, 0, 0.0f);
}
