#include "names.h"
/* func_PAL_L09_0039EEE0, the PAL copy of func_L09_0039BA18: the same C, where the start delay and each frame length get the 50 Hz scale. */
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int FastDecTimer(unsigned short *);
extern int math_fast_float_d(char *);
extern float IntToFloat(int);
extern int math_fast_helper_a(void *, float);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(char *, char *, char *);
extern unsigned char *g_moby_record_table MACRO_ADDR;
extern void gfx_free_point_light(int);
extern void moby_mark_spawned(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern unsigned char g_sound_effect_table[];

#define S(p, o) (*(signed char *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define H(p, o) (*(short *)((p) + (o)))

/* Updates a pulsing light with a looping sound: fades its colour and pitch between two settings and plays its sound at the right spot. */
void pulsing_l09_light_update_pal(unsigned char *moby)
{
    unsigned char *vars, *key_data, *sound, *target;
    Vec pos, origin, delta;
    int length;
    float r, g, b, pitch, num, den, t, nr, ng, nb, np, r2, g2, b2, pitch2;

    if (!moby)
        return;
    vars = *(unsigned char **)(moby + 0x68);
    if (!vars)
        return;
    if (H(vars, 0x28) != -1 && FastDecTimer((unsigned short *)(vars + 0x28))) {
        if (S(vars, 0x2E) != -1) {
            gfx_free_point_light(S(vars, 0x2E));
            S(vars, 0x2E) = -1;
        }
        moby_mark_spawned(moby);
        return;
    }
    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 255;
        qcopy(vars + 0x10, moby + 0x10);
        I(vars, 0xC) = I(vars, 0x24);
        S(vars, 0x2E) = -1;
        if (I(vars, 0x20) != -1)
            *(unsigned char **)(vars + 0x34) = g_moby_record_table + (I(vars, 0x20) << 8);
        I(vars, 0x30) = ((s32)(vars[0x2F]) * 5 + 2) / 6;
        vars[0x2D] = 0;
        moby[0x20] = 1;
        break;
    case 1:
        if (math_fast_float_d((char *)(vars + 0x30)))
            moby[0x20] = 2;
        break;
    case 2:
        key_data = vars + 0x38 + vars[0x2D] * 5;
        r = IntToFloat(*key_data++) * 0.01f;
        g = IntToFloat(*key_data++) * 0.01f;
        b = IntToFloat(*key_data++) * 0.01f;
        pitch = IntToFloat(*key_data++);
        length = ((s32)(*key_data++) * 5 + 2) / 6;
        num = IntToFloat(I(vars, 0x30));
        den = IntToFloat(length);
        t = num / den;
        if (vars[0x2C] < vars[0x2D] + 1) {
            if (I(vars, 0x24) & 0x4000)
                key_data = vars + 0x38;
            else
                key_data -= 5;
        }
        nr = IntToFloat(*key_data++) * 0.01f;
        ng = IntToFloat(*key_data++) * 0.01f;
        nb = IntToFloat(*key_data++) * 0.01f;
        np = IntToFloat(*key_data);
        r2 = r + (nr - r) * t;
        g2 = g + (ng - g) * t;
        b2 = b + (nb - b) * t;
        pitch2 = pitch + (np - pitch) * t;
        qcopy(&pos, moby + 0x10);
        pos.f[3] = pitch2;
        if (math_fast_helper_a(&pos, 255.0f) != -1) {
            target = *(unsigned char **)(vars + 0x34);
            if ((I(vars, 0x24) & 0x1000000) && target && !((*(unsigned short *)(target + 0x34) ^ 1) & 1))
                goto stop;
            if (target)
                qcopy_nc(&origin, target + 0x10);
            else
                qcopy_nc(&origin, vars + 0x10);
            if (!(I(vars, 0x24) & 0x800000)) {
                if (I(vars, 0x24) & 0x100000) {
                    if (I(vars, 0x24) & 0x200000) {
                        delta.f[0] = math_random_float_range(-F(vars, 0), F(vars, 0));
                        delta.f[1] = math_random_float_range(-F(vars, 4), F(vars, 4));
                        delta.f[2] = math_random_float_range(-F(vars, 8), F(vars, 8));
                    } else {
                        int saved = I(vars, 0xC);
                        I(vars, 0xC) = 0;
                        FastVecScale(&delta, vars, math_random_float_range(F(vars, 0xC), 1.0f));
                        I(vars, 0xC) = saved;
                    }
                } else {
                    int saved = I(vars, 0xC);
                    I(vars, 0xC) = 0;
                    qcopy(&delta, vars);
                    I(vars, 0xC) = saved;
                }
                if ((I(vars, 0x24) & 0x400000) && *(unsigned char **)(vars + 0x34))
                    matrix_mul_vec3(&delta, &delta, *(unsigned char **)(vars + 0x34) + 0xC0);
                FastVecAdd((char *)(moby + 0x10), (char *)&origin, (char *)&delta);
            } else {
                qcopy(moby + 0x10, &origin);
            }
            if (S(vars, 0x2E) == -1) {
                vars[0x2E] = part_l00_alloc_effect_slot_2(moby + 0x10, pitch2, IntToFloat(vars[0x2A]) * 0.01f, r2, g2, b2);
            } else {
                sound = g_sound_effect_table + (S(vars, 0x2E) << 5);
                qcopy(sound + 0x10, moby + 0x10);
                F(sound, 0x1C) = pitch2;
                F(sound, 0) = r2;
                F(sound, 4) = g2;
                F(sound, 8) = b2;
                F(sound, 0xC) = IntToFloat(vars[0x2A]) * 0.01f;
            }
        } else {
        stop:
            if (S(vars, 0x2E) != -1) {
                gfx_free_point_light(S(vars, 0x2E));
                S(vars, 0x2E) = -1;
            }
        }
        if (++I(vars, 0x30) >= length) {
            I(vars, 0x30) = 0;
            if (++vars[0x2D] > vars[0x2C]) {
                if (I(vars, 0x24) & 0x4000)
                    vars[0x2D] = 0;
                else
                    moby[0x20] = 3;
            }
        }
        break;
    case 3:
        if (S(vars, 0x2E) != -1) {
            gfx_free_point_light(S(vars, 0x2E));
            S(vars, 0x2E) = -1;
            moby_mark_spawned(moby);
        }
        break;
    }
}
