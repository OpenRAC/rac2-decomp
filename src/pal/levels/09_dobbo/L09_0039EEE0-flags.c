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
extern unsigned char *D_L09_001B285C MACRO_ADDR;
extern void gfx_free_point_light(int);
extern void moby_mark_spawned(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern unsigned char D_L09_001C7B80[];

#define S(p, o) (*(signed char *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define H(p, o) (*(short *)((p) + (o)))

void func_PAL_L09_0039EEE0(unsigned char *object)
{
    unsigned char *s, *p, *sound, *m;
    Vec pos, origin, delta;
    int length;
    float r, g, b, pitch, num, den, t, nr, ng, nb, np, r2, g2, b2, pitch2;

    if (!object)
        return;
    s = *(unsigned char **)(object + 0x68);
    if (!s)
        return;
    if (H(s, 0x28) != -1 && FastDecTimer((unsigned short *)(s + 0x28))) {
        if (S(s, 0x2E) != -1) {
            gfx_free_point_light(S(s, 0x2E));
            S(s, 0x2E) = -1;
        }
        moby_mark_spawned(object);
        return;
    }
    switch (object[0x20]) {
    case 0:
        object[0x30] = 255;
        qcopy(s + 0x10, object + 0x10);
        I(s, 0xC) = I(s, 0x24);
        S(s, 0x2E) = -1;
        if (I(s, 0x20) != -1)
            *(unsigned char **)(s + 0x34) = D_L09_001B285C + (I(s, 0x20) << 8);
        I(s, 0x30) = ((s32)(s[0x2F]) * 5 + 2) / 6;
        s[0x2D] = 0;
        object[0x20] = 1;
        break;
    case 1:
        if (math_fast_float_d((char *)(s + 0x30)))
            object[0x20] = 2;
        break;
    case 2:
        p = s + 0x38 + s[0x2D] * 5;
        r = IntToFloat(*p++) * 0.01f;
        g = IntToFloat(*p++) * 0.01f;
        b = IntToFloat(*p++) * 0.01f;
        pitch = IntToFloat(*p++);
        length = ((s32)(*p++) * 5 + 2) / 6;
        num = IntToFloat(I(s, 0x30));
        den = IntToFloat(length);
        t = num / den;
        if (s[0x2C] < s[0x2D] + 1) {
            if (I(s, 0x24) & 0x4000)
                p = s + 0x38;
            else
                p -= 5;
        }
        nr = IntToFloat(*p++) * 0.01f;
        ng = IntToFloat(*p++) * 0.01f;
        nb = IntToFloat(*p++) * 0.01f;
        np = IntToFloat(*p);
        r2 = r + (nr - r) * t;
        g2 = g + (ng - g) * t;
        b2 = b + (nb - b) * t;
        pitch2 = pitch + (np - pitch) * t;
        qcopy(&pos, object + 0x10);
        pos.f[3] = pitch2;
        if (math_fast_helper_a(&pos, 255.0f) != -1) {
            m = *(unsigned char **)(s + 0x34);
            if ((I(s, 0x24) & 0x1000000) && m && !((*(unsigned short *)(m + 0x34) ^ 1) & 1))
                goto stop;
            if (m)
                qcopy_nc(&origin, m + 0x10);
            else
                qcopy_nc(&origin, s + 0x10);
            if (!(I(s, 0x24) & 0x800000)) {
                if (I(s, 0x24) & 0x100000) {
                    if (I(s, 0x24) & 0x200000) {
                        delta.f[0] = math_random_float_range(-F(s, 0), F(s, 0));
                        delta.f[1] = math_random_float_range(-F(s, 4), F(s, 4));
                        delta.f[2] = math_random_float_range(-F(s, 8), F(s, 8));
                    } else {
                        int saved = I(s, 0xC);
                        I(s, 0xC) = 0;
                        FastVecScale(&delta, s, math_random_float_range(F(s, 0xC), 1.0f));
                        I(s, 0xC) = saved;
                    }
                } else {
                    int saved = I(s, 0xC);
                    I(s, 0xC) = 0;
                    qcopy(&delta, s);
                    I(s, 0xC) = saved;
                }
                if ((I(s, 0x24) & 0x400000) && *(unsigned char **)(s + 0x34))
                    matrix_mul_vec3(&delta, &delta, *(unsigned char **)(s + 0x34) + 0xC0);
                FastVecAdd((char *)(object + 0x10), (char *)&origin, (char *)&delta);
            } else {
                qcopy(object + 0x10, &origin);
            }
            if (S(s, 0x2E) == -1) {
                s[0x2E] = part_l00_alloc_effect_slot_2(object + 0x10, pitch2, IntToFloat(s[0x2A]) * 0.01f, r2, g2, b2);
            } else {
                sound = D_L09_001C7B80 + (S(s, 0x2E) << 5);
                qcopy(sound + 0x10, object + 0x10);
                F(sound, 0x1C) = pitch2;
                F(sound, 0) = r2;
                F(sound, 4) = g2;
                F(sound, 8) = b2;
                F(sound, 0xC) = IntToFloat(s[0x2A]) * 0.01f;
            }
        } else {
        stop:
            if (S(s, 0x2E) != -1) {
                gfx_free_point_light(S(s, 0x2E));
                S(s, 0x2E) = -1;
            }
        }
        if (++I(s, 0x30) >= length) {
            I(s, 0x30) = 0;
            if (++s[0x2D] > s[0x2C]) {
                if (I(s, 0x24) & 0x4000)
                    s[0x2D] = 0;
                else
                    object[0x20] = 3;
            }
        }
        break;
    case 3:
        if (S(s, 0x2E) != -1) {
            gfx_free_point_light(S(s, 0x2E));
            S(s, 0x2E) = -1;
            moby_mark_spawned(object);
        }
        break;
    }
}
