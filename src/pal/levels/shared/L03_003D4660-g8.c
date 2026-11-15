#include "include_asm.h"

#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern int D_L03_001A8F00;
extern char D_L03_001A8F20[] __attribute__((sda)), D_L03_001BFDE0[], g_sound_state[];
extern float D_L03_001B0590 __attribute__((sda)), D_L03_001B0594 __attribute__((sda));
extern void moby_mark_spawned(void *);
extern int moby_transform_point_and_rotation_by_parent(void *,void *,void *,void *,void *,void *);
extern void FastVecSub(void *,void *,void *),vec_transform_by_object_or_given(void *,void *,void *,int);
extern void lerp_vector(void *,void *,void *,float),FastVecAdd(void *,void *,void *);
extern float ApproachValue(void *,float,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void moby_set_state(void *,int,int),make_hit_descriptor(void *,void *,int,void *,float);
extern int CollLine(void *,void *,int,void *,void *);
extern float math_random_angle(void),math_random_float_range(float,float),math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern void func_PAL_L03_003D5148(void *,void *,void *),vec_random_direction(void *,float,float);
extern int math_random_int_below(int),PlayMobySound(int,int,void *),math_fast_float_d(void *);
extern void snd_stop_voice(int),gfx_add_draw_callback_first(void *,void *),gfx_l03_draw_glowing_beam(void *);

/* Interpolates the emitter position, keeps it relative to its attachment,
 * emits particles while active, and releases its sound and object after fading. */
void func_PAL_L03_003D4660(char *m) {
    float tmp[4], a[4], b[4], hit[12], pos[4], vel[4];
    char *v = P(m, 0x68), *p, *e;
    float angle, speed;

    if (D_L03_001A8F00 == 2) {
        moby_mark_spawned(m);
        return;
    }
    p = m + 0x10;
    if (P(v, 0x40)) {
        moby_transform_point_and_rotation_by_parent(m, P(v, 0x40), p, m + 0xF0, p, m + 0xF0);
        FastVecSub(p, p, P(v, 0x40) + 0x10);
        vec_transform_by_object_or_given(P(v, 0x40), p, p, 0);
    }
    lerp_vector(tmp, v, v + 0x10, F(v, 0x20));
    FastVecAdd(p, p, tmp);
    ApproachValue(v + 0x20, 1.0f, F(v, 0x24));
    if (P(v, 0x40)) {
        matrix_mul_vec3(p, p, P(v, 0x40) + 0xC0);
        FastVecAdd(p, p, P(v, 0x40) + 0x10);
    }
    switch ((unsigned char)m[0x20]) {
    case 0:
        I(v, 0x3C) = -1;
        if (F(v, 0x20) > 0.5f)
            moby_set_state(m, 1, -1);
        break;
    case 1:
        qcopy(a, p);
        qcopy(b, p);
        b[2] -= F(v, 0x20) * 5.0f;
        make_hit_descriptor(hit, m, 0x10001, D_L03_001A8F20, (float)I(v, 0x38));
        if (CollLine(a, b, 0, m, hit) && !P(v, 0x40)) {
            angle = math_random_angle();
            speed = math_random_float_range(0, 0.5f) * (0.020000001f);
            pos[0] = math_fast_sin_or_cos_a(angle) * speed;
            pos[1] = math_fast_sin_or_cos_b(angle) * speed;
            pos[2] = 0;
            pos[2] = math_random_float_range(1, 2) * (0.020000001f);
            func_PAL_L03_003D5148(m, D_L03_001BFDE0, pos);
        }
        if (!P(v, 0x40) && !math_random_int_below(2)) {
            qcopy(pos, p);
            pos[2] -= math_random_float_range(0, 5);
            vec_random_direction(vel, 0, 0.040000003f);
            func_PAL_L03_003D5148(m, pos, vel);
        }
        e = (char *)(I(v, 0x3C) * 0x70);
        e = (char *)((int)e + (int)g_sound_state);
        if (P(e, 0x88) != m || !((unsigned char *)e)[0x74])
            I(v, 0x3C) = PlayMobySound(0, 4, m);
        if (F(v, 0x34) < 1)
            ApproachValue(v + 0x34, 1, 0.080000006f);
        if (math_fast_float_d(v + 0x28))
            moby_set_state(m, 2, -1);
        break;
    case 2:
        ApproachValue(v + 0x34, 0, 0.040000003f);
        if (F(v, 0x34) <= 0) {
            int handle = I(v, 0x3C);
            if (handle != -1) {
                int offset = handle * 0x70;
                char *slot = g_sound_state + offset;
                if (P(slot, 0x88) == m && ((unsigned char *)slot)[0x74])
                    snd_stop_voice(handle);
            }
            I(v, 0x3C) = -1;
            moby_mark_spawned(m);
            return;
        }
        break;
    }
    F(v, 0x2C) += D_L03_001B0590 * (0.020000001f);
    if (F(v, 0x2C) > 1)
        F(v, 0x2C) -= 1;
    else if (F(v, 0x2C) < 1)
        F(v, 0x2C) += 1;
    F(v, 0x30) += D_L03_001B0594 * (0.020000001f);
    if (F(v, 0x30) > 1)
        F(v, 0x30) -= 1;
    gfx_add_draw_callback_first(gfx_l03_draw_glowing_beam, m);
}
